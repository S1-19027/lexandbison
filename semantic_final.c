#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "semantic.h"
#include "ast.h"

// 全局变量
SemanticError semantic_errors[256];
int semantic_error_count = 0;
Scope *global_scope = NULL;
Scope *current_scope = NULL;
bool in_loop = false;
DataType current_func_return_type = TYPE_VOID;

// 前向声明
static DataType get_btype(ASTNode *node);

static DataType get_func_return_type(ASTNode *func_node)
{
    if (!func_node)
        return TYPE_INT;

    for (int i = 0; i < func_node->child_count; i++)
    {
        ASTNode *child = func_node->children[i];
        if (strcmp(child->name, "FuncType") == 0 && child->child_count > 0)
        {
            if (strcmp(child->children[0]->value, "int") == 0)
                return TYPE_INT;
            if (strcmp(child->children[0]->value, "float") == 0)
                return TYPE_FLOAT;
            if (strcmp(child->children[0]->value, "void") == 0)
                return TYPE_VOID;
        }
        else if (strcmp(child->name, "INTTK") == 0)
            return TYPE_INT;
        else if (strcmp(child->name, "FLOATTK") == 0)
            return TYPE_FLOAT;
        else if (strcmp(child->name, "VOIDTK") == 0)
            return TYPE_VOID;
    }
    return TYPE_INT;
}

// 将函数形参加入当前作用域
static void add_func_params(ASTNode *func_node, Scope *scope)
{
    if (!func_node || !scope)
        return;

    for (int i = 0; i < func_node->child_count; i++)
    {
        ASTNode *child = func_node->children[i];
        if (strcmp(child->name, "FuncFParams") != 0)
            continue;

        for (int p = 0; p < child->child_count; p++)
        {
            ASTNode *param = child->children[p];
            if (!param || strcmp(param->name, "FuncFParam") != 0 || param->child_count == 0)
                continue;

            DataType dtype = get_btype(param->children[0]);
            const char *pname = NULL;
            int dims = 0;

            for (int k = 0; k < param->child_count; k++)
            {
                if (!pname && (strcmp(param->children[k]->name, "ID") == 0 || strcmp(param->children[k]->name, "Ident") == 0))
                {
                    pname = param->children[k]->value;
                }
                if (strcmp(param->children[k]->name, "LBRACKET") == 0)
                {
                    dims++;
                }
            }

            if (!pname)
                continue;

            if (lookup_symbol_local(scope, pname))
            {
                char msg[256];
                snprintf(msg, sizeof(msg), "parameter \"%s\" redeclared", pname);
                check_semantic_error(2, param->line, msg);
                continue;
            }

            add_symbol(scope, pname, SYM_VAR, dtype, param->line);
            if (dims > 0)
            {
                scope->symbols[scope->count - 1].is_array = true;
                scope->symbols[scope->count - 1].array_dims = dims;
            }
        }
    }
}

void precollect_functions(ASTNode *node)
{
    if (!node)
        return;

    if (strcmp(node->name, "FuncDef") == 0)
    {
        const char *func_name = NULL;
        for (int i = 0; i < node->child_count; i++)
        {
            if (strcmp(node->children[i]->name, "ID") == 0 || strcmp(node->children[i]->name, "Ident") == 0)
            {
                func_name = node->children[i]->value;
                break;
            }
        }

        if (func_name)
        {
            Symbol *existing = lookup_symbol_local(global_scope, func_name);
            if (!existing)
            {
                DataType ret_type = get_func_return_type(node);
                // 统计参数个数
                int param_count = 0;
                for (int j = 0; j < node->child_count; j++)
                {
                    ASTNode *c = node->children[j];
                    if (strcmp(c->name, "FuncFParams") == 0)
                    {
                        for (int p = 0; p < c->child_count; p++)
                        {
                            if (strcmp(c->children[p]->name, "FuncFParam") == 0)
                                param_count++;
                        }
                    }
                }

                add_symbol(global_scope, func_name, SYM_FUNC, ret_type, node->line);
                global_scope->symbols[global_scope->count - 1].is_defined = true;
                global_scope->symbols[global_scope->count - 1].param_count = param_count;
            }
        }
    }

    for (int i = 0; i < node->child_count; i++)
    {
        precollect_functions(node->children[i]);
    }
}

// 作用域管理
Scope *create_scope(Scope *parent)
{
    Scope *scope = (Scope *)malloc(sizeof(Scope));
    scope->symbols = (Symbol *)malloc(sizeof(Symbol) * 100);
    scope->count = 0;
    scope->capacity = 100;
    scope->parent = parent;
    return scope;
}

void push_scope(Scope *scope)
{
    scope->parent = current_scope;
    current_scope = scope;
}

void pop_scope(void)
{
    if (current_scope && current_scope->parent)
    {
        current_scope = current_scope->parent;
    }
}

void free_scope(Scope *scope)
{
    if (!scope)
        return;
    for (int i = 0; i < scope->count; i++)
    {
        if (scope->symbols[i].param_types)
        {
            free(scope->symbols[i].param_types);
        }
    }
    free(scope->symbols);
    free(scope);
}

// 添加符号到符号表
void add_symbol(Scope *scope, const char *name, SymbolType type, DataType data_type, int line)
{
    if (scope->count >= scope->capacity)
    {
        scope->capacity *= 2;
        scope->symbols = (Symbol *)realloc(scope->symbols, sizeof(Symbol) * scope->capacity);
    }

    Symbol *sym = &scope->symbols[scope->count++];
    strncpy(sym->name, name, sizeof(sym->name) - 1);
    sym->name[sizeof(sym->name) - 1] = '\0';
    sym->type = type;
    sym->data_type = data_type;
    sym->line = line;
    sym->is_array = false;
    sym->array_dims = 0;
    sym->array_size1 = 0;
    sym->array_size2 = 0;
    sym->param_count = 0;
    sym->param_types = NULL;
    sym->is_defined = false;
}

// 在本作用域查找符号
Symbol *lookup_symbol_local(Scope *scope, const char *name)
{
    if (!scope)
        return NULL;
    for (int i = 0; i < scope->count; i++)
    {
        if (strcmp(scope->symbols[i].name, name) == 0)
        {
            return &scope->symbols[i];
        }
    }
    return NULL;
}

// 在当前及父作用域查找符号
Symbol *lookup_symbol(const char *name)
{
    Scope *scope = current_scope;
    while (scope)
    {
        Symbol *sym = lookup_symbol_local(scope, name);
        if (sym)
            return sym;
        scope = scope->parent;
    }
    return NULL;
}

// 记录语义错误
void check_semantic_error(int type, int line, const char *msg)
{
    if (semantic_error_count >= 256)
        return;

    // 避免同一行同一类型的重复错误
    for (int i = 0; i < semantic_error_count; i++)
    {
        if (semantic_errors[i].line == line && semantic_errors[i].error_type == type)
        {
            return;
        }
    }

    semantic_errors[semantic_error_count].line = line;
    semantic_errors[semantic_error_count].error_type = type;
    strncpy(semantic_errors[semantic_error_count].message, msg, 255);
    semantic_errors[semantic_error_count].message[255] = '\0';
    semantic_error_count++;
}

// 从节点获取标识符名称
const char *get_identifier_name(ASTNode *node)
{
    if (!node)
        return NULL;

    if (strcmp(node->name, "Ident") == 0 || strcmp(node->name, "ID") == 0)
    {
        return node->value;
    }

    // 递归查找子节点
    for (int i = 0; i < node->child_count; i++)
    {
        const char *name = get_identifier_name(node->children[i]);
        if (name)
            return name;
    }

    return NULL;
}

// 检查表达式中是否包含浮点数
bool has_float_literal(ASTNode *node)
{
    if (!node)
        return false;

    // 直接检查FLOATCON节点
    if (strcmp(node->name, "FLOATCON") == 0)
    {
        return true;
    }

    for (int i = 0; i < node->child_count; i++)
    {
        if (has_float_literal(node->children[i]))
        {
            return true;
        }
    }

    return false;
}

// 获取表达式的数据类型
DataType get_expression_type(ASTNode *node)
{
    if (!node)
        return TYPE_UNKNOWN;

    // 数字字面量
    if (strcmp(node->name, "Number") == 0)
    {
        if (has_float_literal(node))
        {
            return TYPE_FLOAT;
        }
        return TYPE_INT;
    }

    // 左值（变量）
    if (strcmp(node->name, "LVal") == 0)
    {
        const char *var_name = get_identifier_name(node);
        if (var_name)
        {
            Symbol *sym = lookup_symbol(var_name);
            if (sym)
            {
                // 如果是数组访问，返回元素类型
                bool has_index = false;
                for (int i = 0; i < node->child_count; i++)
                {
                    if (strcmp(node->children[i]->name, "LBRACKET") == 0)
                    {
                        has_index = true;
                        break;
                    }
                }

                if (sym->is_array && !has_index)
                {
                    // 数组名本身
                    return TYPE_ARRAY;
                }
                else if (sym->is_array && has_index)
                {
                    // 数组元素
                    return sym->data_type;
                }
                else
                {
                    return sym->data_type;
                }
            }
        }
        return TYPE_UNKNOWN;
    }

    // 函数调用 - 在UnaryExp中
    if (strcmp(node->name, "UnaryExp") == 0 && node->child_count >= 2)
    {
        const char *func_name = get_identifier_name(node->children[0]);
        if (func_name)
        {
            Symbol *sym = lookup_symbol(func_name);
            if (sym && sym->type == SYM_FUNC)
            {
                return sym->data_type;
            }
        }
    }

    // 递归处理表达式节点
    if (strcmp(node->name, "Exp") == 0 || strcmp(node->name, "AddExp") == 0 ||
        strcmp(node->name, "MulExp") == 0 || strcmp(node->name, "UnaryExp") == 0 ||
        strcmp(node->name, "PrimaryExp") == 0 || strcmp(node->name, "RelExp") == 0 ||
        strcmp(node->name, "EqExp") == 0 || strcmp(node->name, "Cond") == 0)
    {

        if (node->child_count > 0)
        {
            DataType type1 = get_expression_type(node->children[0]);
            if (node->child_count >= 3)
            {
                // 二元运算符 - 返回操作数类型
                DataType type2 = get_expression_type(node->children[2]);
                // int/float 不允许混合运算（错误类型11）
                if ((type1 == TYPE_INT && type2 == TYPE_FLOAT) ||
                    (type1 == TYPE_FLOAT && type2 == TYPE_INT))
                {
                    check_semantic_error(11, node->line, "type mismatched for operands");
                    return TYPE_UNKNOWN;
                }

                // 如果有一个是float，结果就是float
                if (type1 == TYPE_FLOAT || type2 == TYPE_FLOAT)
                {
                    return TYPE_FLOAT;
                }

                return type1 != TYPE_UNKNOWN ? type1 : type2;
            }
            return type1;
        }
    }

    return TYPE_UNKNOWN;
}

// 获取BType的数据类型
DataType get_btype(ASTNode *node)
{
    if (!node || strcmp(node->name, "BType") != 0)
        return TYPE_INT;

    for (int i = 0; i < node->child_count; i++)
    {
        if (strcmp(node->children[i]->name, "Type") == 0)
        {
            if (strcmp(node->children[i]->value, "int") == 0)
                return TYPE_INT;
            if (strcmp(node->children[i]->value, "float") == 0)
                return TYPE_FLOAT;
        }
        if (strcmp(node->children[i]->name, "FLOATTK") == 0)
            return TYPE_FLOAT;
        if (strcmp(node->children[i]->name, "INTTK") == 0)
            return TYPE_INT;
    }
    return TYPE_INT;
}

static void process_single_vardef(ASTNode *vardef, DataType dtype, int fallback_line)
{
    if (!vardef || strcmp(vardef->name, "VarDef") != 0 || vardef->child_count == 0)
        return;

    const char *var_name = get_identifier_name(vardef->children[0]);
    if (!var_name)
        return;

    // 检查是否在本作用域重复声明（错误类型2）
    Symbol *existing = lookup_symbol_local(current_scope, var_name);
    if (existing)
    {
        char msg[256];
        snprintf(msg, sizeof(msg), "variable \"%s\" redeclared", var_name);
        check_semantic_error(2, vardef->line > 0 ? vardef->line : fallback_line, msg);
        return;
    }

    // 添加到符号表
    add_symbol(current_scope, var_name, SYM_VAR, dtype, fallback_line);

    // 检查是否是数组
    bool is_array = false;
    int dims = 0;
    for (int i = 1; i < vardef->child_count; i++)
    {
        if (strcmp(vardef->children[i]->name, "LBRACKET") == 0)
        {
            is_array = true;
            dims++;
        }
    }

    if (is_array)
    {
        current_scope->symbols[current_scope->count - 1].is_array = true;
        current_scope->symbols[current_scope->count - 1].array_dims = dims;
    }
}

// 递归处理 VarDefList
static void process_vardef_list(ASTNode *node, DataType dtype, int fallback_line)
{
    if (!node)
        return;

    if (strcmp(node->name, "VarDef") == 0)
    {
        process_single_vardef(node, dtype, fallback_line);
        return;
    }

    if (strcmp(node->name, "VarDefList") == 0)
    {
        for (int i = 0; i < node->child_count; i++)
        {
            process_vardef_list(node->children[i], dtype, fallback_line);
        }
    }
}

// 检查变量声明
void analyze_var_decl(ASTNode *node)
{
    if (!node || strcmp(node->name, "VarDecl") != 0)
        return;

    // VarDecl -> BType VarDef [VarDefList] SEMICN
    if (node->child_count >= 2)
    {
        DataType dtype = get_btype(node->children[0]);

        for (int i = 1; i < node->child_count; i++)
        {
            if (strcmp(node->children[i]->name, "VarDef") == 0 ||
                strcmp(node->children[i]->name, "VarDefList") == 0)
            {
                process_vardef_list(node->children[i], dtype, node->line);
            }
        }
    }
}

// 检查LVal（变量使用）
void analyze_lval(ASTNode *node)
{
    if (!node || strcmp(node->name, "LVal") != 0)
        return;

    const char *var_name = get_identifier_name(node);
    if (!var_name)
        return;

    Symbol *sym = lookup_symbol(var_name);

    if (!sym)
    {
        // 错误类型1：变量未声明
        char msg[256];
        snprintf(msg, sizeof(msg), "undefined variable \"%s\"", var_name);
        check_semantic_error(1, node->line, msg);
        return;
    }

    if (sym->type == SYM_FUNC)
    {
        // 错误类型6：对函数名的不当引用
        char msg[256];
        snprintf(msg, sizeof(msg), "\"%s\" is a function", var_name);
        check_semantic_error(6, node->line, msg);
        return;
    }

    // 检查数组访问
    bool has_array_access = false;
    for (int i = 1; i < node->child_count; i++)
    {
        if (strcmp(node->children[i]->name, "LBRACKET") == 0)
        {
            has_array_access = true;

            // 检查数组下标是否是整数类型（错误类型7）
            if (i + 1 < node->child_count)
            {
                ASTNode *index_exp = node->children[i + 1];
                DataType index_type = get_expression_type(index_exp);

                if (index_type == TYPE_FLOAT)
                {
                    char msg[256];
                    snprintf(msg, sizeof(msg), "array index must be integer");
                    check_semantic_error(7, node->line, msg);
                }
            }
            break;
        }
    }

    if (has_array_access && !sym->is_array)
    {
        // 错误类型8：对非数组变量使用数组访问
        char msg[256];
        snprintf(msg, sizeof(msg), "\"%s\" is not an array", var_name);
        check_semantic_error(8, node->line, msg);
    }
}

// 检查函数调用
void analyze_func_call(ASTNode *node)
{
    if (!node || strcmp(node->name, "UnaryExp") != 0)
        return;

    // UnaryExp -> ID LPARENT FuncRParamsOpt RPARENT
    if (node->child_count >= 2 && strcmp(node->children[1]->name, "LPARENT") == 0)
    {
        const char *func_name = get_identifier_name(node->children[0]);
        if (!func_name)
            return;

        Symbol *sym = lookup_symbol(func_name);

        if (!sym)
        {
            // 错误类型3：函数未定义
            char msg[256];
            snprintf(msg, sizeof(msg), "function \"%s\" not defined", func_name);
            check_semantic_error(3, node->line, msg);
            return;
        }

        if (sym->type != SYM_FUNC)
        {
            // 错误类型5：把变量当做函数调用
            char msg[256];
            snprintf(msg, sizeof(msg), "\"%s\" is not a function", func_name);
            check_semantic_error(5, node->line, msg);
            return;
        }

        // 检查参数个数和类型（错误类型9）
        int actual_param_count = 0;
        ASTNode *func_rparams = NULL;

        for (int i = 0; i < node->child_count; i++)
        {
            if (strcmp(node->children[i]->name, "FuncRParams") == 0)
            {
                func_rparams = node->children[i];
                // 计算实参个数
                for (int j = 0; j < func_rparams->child_count; j++)
                {
                    if (strcmp(func_rparams->children[j]->name, "Exp") == 0)
                    {
                        actual_param_count++;
                    }
                }
                break;
            }
        }

        if (actual_param_count != sym->param_count)
        {
            char msg[256];
            snprintf(msg, sizeof(msg), "function \"%s\" expects %d arguments but %d provided",
                     func_name, sym->param_count, actual_param_count);
            check_semantic_error(9, node->line, msg);
        }
    }
}

// 检查赋值语句的类型匹配（错误类型11）
void analyze_assignment(ASTNode *node)
{
    if (!node || strcmp(node->name, "Stmt") != 0)
        return;

    // 查找赋值语句：LVal ASSIGN Exp
    if (node->child_count >= 3)
    {
        ASTNode *lval = NULL, *exp = NULL;

        for (int i = 0; i < node->child_count - 1; i++)
        {
            if (strcmp(node->children[i]->name, "LVal") == 0 &&
                strcmp(node->children[i + 1]->name, "ASSIGN") == 0)
            {
                lval = node->children[i];
                if (i + 2 < node->child_count && strcmp(node->children[i + 2]->name, "Exp") == 0)
                {
                    exp = node->children[i + 2];
                }
                break;
            }
        }

        if (lval && exp)
        {
            DataType lval_type = get_expression_type(lval);
            DataType exp_type = get_expression_type(exp);

            // 检查类型不匹配
            if (lval_type != TYPE_UNKNOWN && exp_type != TYPE_UNKNOWN)
            {
                if ((lval_type == TYPE_INT && exp_type == TYPE_FLOAT) ||
                    (lval_type == TYPE_FLOAT && exp_type == TYPE_INT))
                {
                    char msg[256];
                    snprintf(msg, sizeof(msg), "type mismatch in assignment");
                    check_semantic_error(11, node->line, msg);
                }

                // 检查数组相关的不当操作
                if (lval_type == TYPE_ARRAY || exp_type == TYPE_ARRAY)
                {
                    char msg[256];
                    snprintf(msg, sizeof(msg), "invalid operation on array");
                    check_semantic_error(11, node->line, msg);
                }
            }
        }
    }
}

// 检查return语句
void analyze_return_stmt(ASTNode *node)
{
    if (!node || strcmp(node->name, "Stmt") != 0)
        return;

    // 查找return语句
    for (int i = 0; i < node->child_count; i++)
    {
        if (strcmp(node->children[i]->name, "RETURNTK") == 0)
        {
            // 检查是否有返回值
            DataType return_type = TYPE_VOID;

            for (int j = i + 1; j < node->child_count; j++)
            {
                if (strcmp(node->children[j]->name, "Exp") == 0)
                {
                    return_type = get_expression_type(node->children[j]);
                    break;
                }
            }

            // 检查返回类型是否匹配（错误类型10）
            if ((current_func_return_type == TYPE_VOID && return_type != TYPE_VOID) ||
                (current_func_return_type != TYPE_VOID && return_type == TYPE_VOID))
            {
                char msg[256];
                snprintf(msg, sizeof(msg), "return type mismatch");
                check_semantic_error(10, node->line, msg);
            }
            else if (current_func_return_type == TYPE_INT && return_type == TYPE_FLOAT)
            {
                char msg[256];
                snprintf(msg, sizeof(msg), "return type mismatch");
                check_semantic_error(10, node->line, msg);
            }
            else if (current_func_return_type == TYPE_FLOAT && return_type == TYPE_INT)
            {
                char msg[256];
                snprintf(msg, sizeof(msg), "return type mismatch");
                check_semantic_error(10, node->line, msg);
            }

            break;
        }
    }
}

// 检查break和continue语句
void analyze_break_continue(ASTNode *node)
{
    if (!node || strcmp(node->name, "Stmt") != 0)
        return;

    for (int i = 0; i < node->child_count; i++)
    {
        if (strcmp(node->children[i]->name, "BREAKTK") == 0)
        {
            if (!in_loop)
            {
                // 错误类型12：break不在循环体内
                char msg[256];
                snprintf(msg, sizeof(msg), "break statement not in loop");
                check_semantic_error(12, node->line, msg);
            }
        }
        else if (strcmp(node->children[i]->name, "CONTINUETK") == 0)
        {
            if (!in_loop)
            {
                // 错误类型13：continue不在循环体内
                char msg[256];
                snprintf(msg, sizeof(msg), "continue statement not in loop");
                check_semantic_error(13, node->line, msg);
            }
        }
    }
}

// 检查函数定义
void analyze_func_def(ASTNode *node)
{
    if (!node || strcmp(node->name, "FuncDef") != 0)
        return;

    // 确定返回类型
    DataType ret_type = TYPE_INT;
    const char *func_name = NULL;
    int param_count = 0;

    for (int i = 0; i < node->child_count; i++)
    {
        ASTNode *child = node->children[i];
        if (strcmp(child->name, "FuncType") == 0 && child->child_count > 0)
        {
            if (strcmp(child->children[0]->value, "int") == 0)
                ret_type = TYPE_INT;
            else if (strcmp(child->children[0]->value, "float") == 0)
                ret_type = TYPE_FLOAT;
            else if (strcmp(child->children[0]->value, "void") == 0)
                ret_type = TYPE_VOID;
        }
        else if (strcmp(child->name, "INTTK") == 0)
        {
            ret_type = TYPE_INT;
        }
        else if (strcmp(child->name, "FLOATTK") == 0)
        {
            ret_type = TYPE_FLOAT;
        }
        else if (strcmp(child->name, "VOIDTK") == 0)
        {
            ret_type = TYPE_VOID;
        }

        if (!func_name && (strcmp(child->name, "ID") == 0 || strcmp(child->name, "Ident") == 0))
        {
            func_name = child->value;
        }

        if (strcmp(child->name, "FuncFParams") == 0)
        {
            for (int p = 0; p < child->child_count; p++)
            {
                if (strcmp(child->children[p]->name, "FuncFParam") == 0)
                {
                    param_count++;
                }
            }
        }
    }

    if (!func_name)
        return;

    Symbol *existing = lookup_symbol_local(current_scope, func_name);
    if (existing)
    {
        // 错误类型4：函数重复定义
        char msg[256];
        snprintf(msg, sizeof(msg), "function \"%s\" redefined", func_name);
        check_semantic_error(4, node->line, msg);
        return;
    }

    // 添加函数符号
    add_symbol(current_scope, func_name, SYM_FUNC, ret_type, node->line);
    current_scope->symbols[current_scope->count - 1].is_defined = true;
    current_scope->symbols[current_scope->count - 1].param_count = param_count;

    // 设置当前函数返回类型供return检查
    current_func_return_type = ret_type;
}

// 递归分析AST
void analyze_ast(ASTNode *node)
{
    if (!node)
        return;

    // 进入函数时设置当前返回类型
    if (strcmp(node->name, "FuncDef") == 0)
    {
        DataType old_ret = current_func_return_type;
        current_func_return_type = get_func_return_type(node);

        // 函数作用域
        Scope *func_scope = create_scope(current_scope);
        push_scope(func_scope);
        add_func_params(node, func_scope);

        for (int i = 0; i < node->child_count; i++)
        {
            analyze_ast(node->children[i]);
        }

        pop_scope();
        current_func_return_type = old_ret;
        return;
    }

    // 处理while循环
    if (strcmp(node->name, "Stmt") == 0)
    {
        for (int i = 0; i < node->child_count; i++)
        {
            if (strcmp(node->children[i]->name, "WHILETK") == 0)
            {
                bool old_in_loop = in_loop;
                in_loop = true;

                // 分析子节点
                for (int j = 0; j < node->child_count; j++)
                {
                    analyze_ast(node->children[j]);
                }

                in_loop = old_in_loop;
                return;
            }
        }
    }

    // 处理块的作用域
    if (strcmp(node->name, "Block") == 0)
    {
        Scope *block_scope = create_scope(current_scope);
        push_scope(block_scope);

        for (int i = 0; i < node->child_count; i++)
        {
            analyze_ast(node->children[i]);
        }

        pop_scope();
        return;
    }

    // 检查各种语义
    analyze_func_def(node);
    analyze_var_decl(node);
    analyze_lval(node);
    analyze_func_call(node);
    analyze_return_stmt(node);
    analyze_break_continue(node);
    analyze_assignment(node);

    // 主动检查表达式类型，用于捕获操作数类型不匹配（错误类型11）
    if (strcmp(node->name, "Exp") == 0 || strcmp(node->name, "AddExp") == 0 ||
        strcmp(node->name, "MulExp") == 0 || strcmp(node->name, "RelExp") == 0 ||
        strcmp(node->name, "EqExp") == 0)
    {
        get_expression_type(node);
    }

    // 递归处理子节点
    for (int i = 0; i < node->child_count; i++)
    {
        analyze_ast(node->children[i]);
    }
}

// 输出语义错误
void print_semantic_errors(void)
{
    // 按行号排序错误
    for (int i = 0; i < semantic_error_count - 1; i++)
    {
        for (int j = i + 1; j < semantic_error_count; j++)
        {
            if (semantic_errors[i].line > semantic_errors[j].line)
            {
                SemanticError tmp = semantic_errors[i];
                semantic_errors[i] = semantic_errors[j];
                semantic_errors[j] = tmp;
            }
        }
    }

    // 输出错误
    for (int i = 0; i < semantic_error_count; i++)
    {
        printf("Error type %d at Line %d: %s\n",
               semantic_errors[i].error_type,
               semantic_errors[i].line,
               semantic_errors[i].message);
    }
}

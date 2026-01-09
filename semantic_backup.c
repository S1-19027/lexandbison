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

// 获取表达式的数据类型
DataType get_expression_type(ASTNode *node)
{
    if (!node)
        return TYPE_UNKNOWN;

    // 数字字面量
    if (strcmp(node->name, "Number") == 0)
    {
        for (int i = 0; i < node->child_count; i++)
        {
            if (strcmp(node->children[i]->name, "INTCON") == 0)
            {
                return TYPE_INT;
            }
            if (strcmp(node->children[i]->name, "FLOATCON") == 0)
            {
                return TYPE_FLOAT;
            }
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
                return sym->data_type;
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
        strcmp(node->name, "EqExp") == 0)
    {

        if (node->child_count > 0)
        {
            DataType type1 = get_expression_type(node->children[0]);
            if (node->child_count >= 3)
            {
                // 二元运算符 - 检查类型一致性
                DataType type2 = get_expression_type(node->children[2]);
                if (type1 != TYPE_UNKNOWN && type2 != TYPE_UNKNOWN && type1 != type2)
                {
                    // 类型不匹配
                    return TYPE_UNKNOWN;
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

// 检查变量声明
void analyze_var_decl(ASTNode *node)
{
    if (!node || strcmp(node->name, "VarDecl") != 0)
        return;

    // VarDecl -> BType VarDef SEMICN
    if (node->child_count >= 2)
    {
        DataType dtype = get_btype(node->children[0]);
        ASTNode *vardef = node->children[1];

        if (strcmp(vardef->name, "VarDef") == 0 && vardef->child_count > 0)
        {
            const char *var_name = get_identifier_name(vardef->children[0]);
            if (var_name)
            {
                // 检查是否在本作用域重复声明
                Symbol *existing = lookup_symbol_local(current_scope, var_name);
                if (existing)
                {
                    char msg[256];
                    snprintf(msg, sizeof(msg), "variable \"%s\" redeclared", var_name);
                    check_semantic_error(2, node->line, msg);
                }
                else
                {
                    // 添加到符号表
                    add_symbol(current_scope, var_name, SYM_VAR, dtype, node->line);

                    // 检查是否是数组
                    bool is_array = false;
                    for (int i = 1; i < vardef->child_count; i++)
                    {
                        if (strcmp(vardef->children[i]->name, "LBRACKET") == 0)
                        {
                            is_array = true;
                            break;
                        }
                    }

                    if (is_array)
                    {
                        current_scope->symbols[current_scope->count - 1].is_array = true;
                        current_scope->symbols[current_scope->count - 1].data_type = TYPE_ARRAY;
                    }
                }
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
    if (node->child_count >= 2)
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
                actual_param_count = 0;
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
            if (return_type != current_func_return_type)
            {
                char msg[256];
                snprintf(msg, sizeof(msg), "return type mismatch");
                check_semantic_error(10, node->line, msg);
            }

            break;
        }
    }
}

// 检查函数定义
void analyze_func_def(ASTNode *node)
{
    if (!node)
        return;
    if (strcmp(node->name, "CompUnit") != 0 &&
        strcmp(node->name, "DeclOrFuncDef") != 0)
        return;

    // 查找函数定义模式：INTTK/VOIDTK/FLOATTK ID LPARENT ...
    for (int i = 0; i < node->child_count; i++)
    {
        ASTNode *child = node->children[i];

        // 检查是否是函数类型关键字
        if (strcmp(child->name, "INTTK") == 0 ||
            strcmp(child->name, "VOIDTK") == 0 ||
            strcmp(child->name, "FLOATTK") == 0 ||
            strcmp(child->name, "Type") == 0)
        {

            // 查找函数名
            for (int j = i + 1; j < node->child_count; j++)
            {
                const char *func_name = get_identifier_name(node->children[j]);
                if (func_name)
                {
                    // 检查后面是否有LPARENT（函数调用标志）
                    if (j + 1 < node->child_count &&
                        strcmp(node->children[j + 1]->name, "LPARENT") == 0)
                    {

                        // 这是一个函数定义
                        Symbol *existing = lookup_symbol_local(current_scope, func_name);

                        if (existing)
                        {
                            // 错误类型4：函数重复定义
                            char msg[256];
                            snprintf(msg, sizeof(msg), "function \"%s\" redefined", func_name);
                            check_semantic_error(4, node->line, msg);
                        }
                        else
                        {
                            // 确定返回类型
                            DataType ret_type = TYPE_INT;
                            if (strcmp(child->name, "VOIDTK") == 0)
                                ret_type = TYPE_VOID;
                            else if (strcmp(child->name, "FLOATTK") == 0)
                                ret_type = TYPE_FLOAT;
                            else if (strcmp(child->value, "int") == 0)
                                ret_type = TYPE_INT;
                            else if (strcmp(child->value, "float") == 0)
                                ret_type = TYPE_FLOAT;

                            // 添加函数到符号表
                            add_symbol(current_scope, func_name, SYM_FUNC, ret_type, node->line);
                            current_scope->symbols[current_scope->count - 1].is_defined = true;

                            // 保存当前函数返回类型
                            current_func_return_type = ret_type;

                            // 计算参数个数
                            int param_count = 0;
                            for (int k = j + 2; k < node->child_count; k++)
                            {
                                if (strcmp(node->children[k]->name, "FuncFParams") == 0)
                                {
                                    ASTNode *params = node->children[k];
                                    for (int p = 0; p < params->child_count; p++)
                                    {
                                        if (strcmp(params->children[p]->name, "FuncFParam") == 0)
                                        {
                                            param_count++;
                                        }
                                    }
                                    break;
                                }
                            }

                            current_scope->symbols[current_scope->count - 1].param_count = param_count;
                        }
                    }
                    break;
                }
            }
            break;
        }
    }
}

// 递归分析AST
void analyze_ast(ASTNode *node)
{
    if (!node)
        return;

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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "semantic.h"

// 全局变量
SemanticError semantic_errors[256];
int semantic_error_count = 0;
Scope *global_scope = NULL;
Scope *current_scope = NULL;
bool in_loop = false;

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

// 获取表达式的类型
DataType get_expression_type(ASTNode *node)
{
    if (!node)
        return TYPE_UNKNOWN;

    if (strcmp(node->name, "Number") == 0)
    {
        // 检查是否是整数或浮点数
        if (node->child_count > 0)
        {
            ASTNode *num_node = node->children[0];
            if (strcmp(num_node->name, "INTCON") == 0)
            {
                return TYPE_INT;
            }
        }
        return TYPE_INT; // 默认整数
    }

    if (strcmp(node->name, "LVal") == 0)
    {
        // 查找变量定义
        if (node->child_count > 0)
        {
            ASTNode *id_node = node->children[0];
            Symbol *sym = lookup_symbol(id_node->value);
            if (sym && sym->type == SYM_VAR)
            {
                return sym->data_type;
            }
        }
        return TYPE_UNKNOWN;
    }

    if (strcmp(node->name, "Exp") == 0 || strcmp(node->name, "AddExp") == 0 ||
        strcmp(node->name, "MulExp") == 0 || strcmp(node->name, "UnaryExp") == 0 ||
        strcmp(node->name, "PrimaryExp") == 0)
    {
        if (node->child_count > 0)
        {
            return get_expression_type(node->children[0]);
        }
    }

    return TYPE_UNKNOWN;
}

// 检查函数定义、变量声明等
void analyze_decl(ASTNode *node)
{
    if (!node || strcmp(node->name, "Decl") != 0)
        return;

    // Decl -> ConstDecl | VarDecl
    if (node->child_count > 0)
    {
        ASTNode *child = node->children[0];
        if (strcmp(child->name, "VarDecl") == 0)
        {
            // VarDecl -> BType VarDef SEMICN
            if (child->child_count >= 2)
            {
                ASTNode *vardef = child->children[1];
                if (strcmp(vardef->name, "VarDef") == 0)
                {
                    // VarDef -> ID | ID LBRACKET ... 等多种形式
                    if (vardef->child_count > 0)
                    {
                        ASTNode *id_node = vardef->children[0];
                        const char *var_name = id_node->value;

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
                            DataType dtype = TYPE_INT; // 默认类型
                            if (child->children[0] && strcmp(child->children[0]->name, "BType") == 0)
                            {
                                // 检查类型
                            }

                            bool is_array = (vardef->child_count > 1 &&
                                             strcmp(vardef->children[1]->name, "LBRACKET") == 0);

                            add_symbol(current_scope, var_name, SYM_VAR, dtype, node->line);
                            if (is_array)
                            {
                                current_scope->symbols[current_scope->count - 1].is_array = true;
                                current_scope->symbols[current_scope->count - 1].array_dims = 1;
                            }
                        }
                    }
                }
            }
        }
    }
}

// 检查函数调用
void analyze_func_call(ASTNode *node)
{
    if (!node)
        return;

    // 在 UnaryExp 中查找函数调用: ID LPARENT FuncRParamsOpt RPARENT
    if (strcmp(node->name, "UnaryExp") == 0)
    {
        if (node->child_count >= 2 && strcmp(node->children[0]->name, "ID") == 0)
        {
            const char *func_name = node->children[0]->value;
            Symbol *sym = lookup_symbol(func_name);

            if (!sym)
            {
                // 错误类型3：函数未定义
                char msg[256];
                snprintf(msg, sizeof(msg), "undefined function \"%s\". ", func_name);
                check_semantic_error(3, node->line, msg);
            }
            else if (sym->type != SYM_FUNC)
            {
                // 错误类型5：把变量当做函数调用
                char msg[256];
                snprintf(msg, sizeof(msg), "\"%s\" is not a function", func_name);
                check_semantic_error(5, node->line, msg);
            }
        }
    }
}

// 检查数组访问
void analyze_lval(ASTNode *node)
{
    if (!node || strcmp(node->name, "LVal") != 0)
        return;

    if (node->child_count > 0)
    {
        ASTNode *id_node = node->children[0];
        if (strcmp(id_node->name, "ID") == 0 || strcmp(id_node->name, "Ident") == 0)
        {
            const char *var_name = id_node->value;
            Symbol *sym = lookup_symbol(var_name);

            if (!sym)
            {
                // 错误类型1：变量未声明
                char msg[256];
                snprintf(msg, sizeof(msg), "undefined variable \"%s\"", var_name);
                check_semantic_error(1, node->line, msg);
            }
            else if (sym->type == SYM_FUNC)
            {
                // 错误类型6：对函数名的不当引用
                char msg[256];
                snprintf(msg, sizeof(msg), "\"%s\" is a function, cannot be used as variable", var_name);
                check_semantic_error(6, node->line, msg);
            }

            // 检查数组访问
            if (node->child_count > 1 && strcmp(node->children[1]->name, "LBRACKET") == 0)
            {
                if (sym && !sym->is_array)
                {
                    // 错误类型8：对非数组变量使用数组访问
                    char msg[256];
                    snprintf(msg, sizeof(msg), "\"%s\" is not an array", var_name);
                    check_semantic_error(8, node->line, msg);
                }

                // 检查数组下标是否是整数表达式（错误类型7）
                if (node->child_count > 2)
                {
                    ASTNode *index = node->children[2];
                    DataType index_type = get_expression_type(index);
                    if (index_type != TYPE_INT && index_type != TYPE_UNKNOWN)
                    {
                        char msg[256];
                        snprintf(msg, sizeof(msg), "array index must be integer");
                        check_semantic_error(7, node->line, msg);
                    }
                }
            }
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

        // 分析块内的语句
        for (int i = 0; i < node->child_count; i++)
        {
            analyze_ast(node->children[i]);
        }

        pop_scope();
        return;
    }

    // 处理函数定义
    if (strcmp(node->name, "FuncDef") == 0)
    {
        // 从AST中提取函数名
        // 这里需要根据具体的AST结构来实现
    }

    // 检查声明
    analyze_decl(node);

    // 检查函数调用
    analyze_func_call(node);

    // 检查左值（变量使用）
    analyze_lval(node);

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

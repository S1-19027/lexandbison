#ifndef SEMANTIC_H
#define SEMANTIC_H

#include "ast.h"
#include <stdbool.h>

// 符号类型
typedef enum
{
    SYM_VAR,   // 变量
    SYM_CONST, // 常量
    SYM_FUNC   // 函数
} SymbolType;

// 数据类型
typedef enum
{
    TYPE_INT,
    TYPE_FLOAT,
    TYPE_VOID,
    TYPE_ARRAY, // 数组类型
    TYPE_UNKNOWN
} DataType;

// 符号表项
typedef struct
{
    char name[256];
    SymbolType type;    // 变量、常量、函数
    DataType data_type; // int、float、void等
    int line;           // 定义行号
    bool is_array;      // 是否是数组
    int array_dims;     // 数组维度（1=一维，2=二维）
    int array_size1;    // 第一维大小
    int array_size2;    // 第二维大小（如果是二维）

    // 函数相关
    int param_count;       // 参数个数
    DataType *param_types; // 参数类型数组
    bool is_defined;       // 函数是否已定义（区分声明和定义）
} Symbol;

// 符号表（作用域）
typedef struct Scope
{
    Symbol *symbols;
    int count;
    int capacity;
    struct Scope *parent; // 父作用域
} Scope;

// 语义错误列表
typedef struct
{
    int line;
    int error_type; // 1-13
    char message[256];
} SemanticError;

// 全局变量声明
extern SemanticError semantic_errors[256];
extern int semantic_error_count;
extern Scope *global_scope;
extern Scope *current_scope;
extern bool in_loop; // 是否在循环体内

// 函数声明

// 作用域管理
Scope *create_scope(Scope *parent);
void push_scope(Scope *scope);
void pop_scope(void);
void free_scope(Scope *scope);

// 符号表操作
void add_symbol(Scope *scope, const char *name, SymbolType type, DataType data_type, int line);
Symbol *lookup_symbol(const char *name);                     // 在当前和父作用域中查找
Symbol *lookup_symbol_local(Scope *scope, const char *name); // 仅在本作用域查找

// 语义分析
void analyze_ast(ASTNode *node);
void precollect_functions(ASTNode *node);
void check_semantic_error(int type, int line, const char *msg);
void print_semantic_errors(void);

#endif

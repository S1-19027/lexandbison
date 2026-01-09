# SysY语言语法分析器详细设计

## 1. 语法分析器架构设计

### 1.1 整体架构
```
词法单元流 → Bison语法分析器 → 语法分析树 → 先序遍历输出
```

### 1.2 技术选型
- **语法分析器生成器**：GNU Bison
- **与词法分析器集成**：Flex + Bison
- **语法树结构**：抽象语法树（AST）

## 2. Bison语法规则设计

### 2.1 语法单元定义
基于SysY语言的EBNF文法，定义以下语法单元：

```
CompUnit        - 编译单元
Decl            - 声明
ConstDecl       - 常量声明
VarDecl         - 变量声明
FuncDef         - 函数定义
Block           - 语句块
Stmt            - 语句
Exp             - 表达式
Cond            - 条件表达式
LVal            - 左值表达式
PrimaryExp      - 基本表达式
UnaryExp        - 一元表达式
MulExp          - 乘除模表达式
AddExp          - 加减表达式
RelExp          - 关系表达式
EqExp           - 相等性表达式
LAndExp         - 逻辑与表达式
LOrExp          - 逻辑或表达式
ConstExp        - 常量表达式
```

### 2.2 Bison语法文件结构

#### 定义部分
```c
%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lexer.h"  // 词法分析器头文件

// 语法树节点定义
typedef struct ASTNode {
    char* type;           // 节点类型
    int line_no;          // 行号
    char* value;          // 节点值（用于词法单元）
    struct ASTNode** children; // 子节点数组
    int child_count;      // 子节点数量
} ASTNode;

// 函数声明
ASTNode* create_ast_node(char* type, int line_no, char* value);
void add_child(ASTNode* parent, ASTNode* child);
void print_ast_preorder(ASTNode* node, int depth);
void free_ast(ASTNode* node);

// 全局变量
extern int yylineno;
%}

// 词法单元声明
%token INTTK FLOATTK VOIDTK CONSTTK IFTK ELSETK WHILETK BREAKTK CONTINUETK RETURNTK
%token ID INTCON FLOATCON
%token PLUS MINUS MUL DIV MOD ASSIGN EQ NEQ LT GT LEQ GEQ AND OR NOT
%token LPARENT RPARENT LBRACKET RBRACKET LBRACE RBRACE SEMICN COMMA

// 语法单元声明
%type <node> CompUnit Decl ConstDecl VarDecl FuncDef Block Stmt Exp Cond LVal
%type <node> PrimaryExp UnaryExp MulExp AddExp RelExp EqExp LAndExp LOrExp ConstExp

%start CompUnit
```

#### 语法规则部分

##### 编译单元规则
```c
CompUnit:
    /* ε */
    {
        $$ = create_ast_node("CompUnit", yylineno, NULL);
    }
    | CompUnit Decl
    {
        $$ = $1;
        add_child($$, $2);
    }
    | CompUnit FuncDef
    {
        $$ = $1;
        add_child($$, $2);
    }
    ;
```

##### 函数定义规则
```c
FuncDef:
    FuncType ID LPARENT FuncFParams RPARENT Block
    {
        $$ = create_ast_node("FuncDef", @1.first_line, NULL);
        add_child($$, $1);  // FuncType
        ASTNode* id_node = create_ast_node("Ident", @2.first_line, $2);
        add_child($$, id_node);
        add_child($$, $4);  // FuncFParams
        add_child($$, $6);  // Block
    }
    ;

FuncType:
    INTTK
    {
        $$ = create_ast_node("FuncType", @1.first_line, "int");
    }
    | FLOATTK
    {
        $$ = create_ast_node("FuncType", @1.first_line, "float");
    }
    | VOIDTK
    {
        $$ = create_ast_node("FuncType", @1.first_line, "void");
    }
    ;
```

##### 语句块和语句规则
```c
Block:
    LBRACE BlockItems RBRACE
    {
        $$ = create_ast_node("Block", @1.first_line, NULL);
        add_child($$, $2);
    }
    ;

BlockItems:
    /* ε */
    {
        $$ = create_ast_node("BlockItems", yylineno, NULL);
    }
    | BlockItems BlockItem
    {
        $$ = $1;
        add_child($$, $2);
    }
    ;

BlockItem:
    Decl
    {
        $$ = create_ast_node("BlockItem", @1.first_line, NULL);
        add_child($$, $1);
    }
    | Stmt
    {
        $$ = create_ast_node("BlockItem", @1.first_line, NULL);
        add_child($$, $1);
    }
    ;
```

##### 表达式规则
```c
Exp:
    AddExp
    {
        $$ = create_ast_node("Exp", @1.first_line, NULL);
        add_child($$, $1);
    }
    ;

AddExp:
    MulExp
    {
        $$ = create_ast_node("AddExp", @1.first_line, NULL);
        add_child($$, $1);
    }
    | AddExp PLUS MulExp
    {
        $$ = create_ast_node("AddExp", @1.first_line, NULL);
        add_child($$, $1);
        ASTNode* op_node = create_ast_node("PLUS", @2.first_line, "+");
        add_child($$, op_node);
        add_child($$, $3);
    }
    | AddExp MINUS MulExp
    {
        $$ = create_ast_node("AddExp", @1.first_line, NULL);
        add_child($$, $1);
        ASTNode* op_node = create_ast_node("MINUS", @2.first_line, "-");
        add_child($$, op_node);
        add_child($$, $3);
    }
    ;
```

## 3. 语法树节点设计

### 3.1 AST节点结构
```c
typedef struct ASTNode {
    char* type;           // 节点类型（语法单元名称）
    int line_no;          // 行号（从词法分析器获取）
    char* value;          // 节点值（用于词法单元）
    struct ASTNode** children; // 子节点数组
    int child_count;      // 子节点数量
    int capacity;         // 数组容量
} ASTNode;
```

### 3.2 AST节点创建和管理函数
```c
ASTNode* create_ast_node(char* type, int line_no, char* value) {
    ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
    node->type = strdup(type);
    node->line_no = line_no;
    node->value = value ? strdup(value) : NULL;
    node->children = NULL;
    node->child_count = 0;
    node->capacity = 0;
    return node;
}

void add_child(ASTNode* parent, ASTNode* child) {
    if (parent->child_count >= parent->capacity) {
        parent->capacity = parent->capacity == 0 ? 4 : parent->capacity * 2;
        parent->children = realloc(parent->children, 
                                  parent->capacity * sizeof(ASTNode*));
    }
    parent->children[parent->child_count++] = child;
}
```

## 4. 错误处理设计

### 4.1 语法错误类型（错误类型B）
1. **缺少分号**：语句末尾缺少分号
2. **括号不匹配**：左右括号数量不匹配
3. **数组访问错误**：错误的数组下标语法
4. **表达式错误**：操作符使用错误

### 4.2 错误恢复策略
```c
// 在Bison规则中添加错误恢复
Stmt:
    LVal ASSIGN Exp SEMICN
    {
        $$ = create_ast_node("AssignStmt", @1.first_line, NULL);
        add_child($$, $1);
        add_child($$, $3);
    }
    | LVal ASSIGN Exp error SEMICN
    {
        printf("Error type B at Line %d: Missing ';'\n", @4.first_line);
        $$ = create_ast_node("AssignStmt", @1.first_line, NULL);
        add_child($$, $1);
        add_child($$, $3);
    }
    ;
```

## 5. 输出格式规范

### 5.1 先序遍历输出规则
```c
void print_ast_preorder(ASTNode* node, int depth) {
    if (node == NULL) return;
    
    // 缩进
    for (int i = 0; i < depth; i++) {
        printf("  ");
    }
    
    // 打印节点信息
    if (node->value) {
        // 词法单元：只打印名称
        printf("%s\n", node->type);
    } else {
        // 语法单元：打印名称和行号
        printf("%s (%d)\n", node->type, node->line_no);
    }
    
    // 递归打印子节点
    for (int i = 0; i < node->child_count; i++) {
        print_ast_preorder(node->children[i], depth + 1);
    }
}
```

### 5.2 特殊处理规则
- **ε产生式**：不打印语法单元信息
- **词法单元**：只打印名称，不打印行号
- **标识符**：额外打印词素（符号串）
- **类型关键词**：额外打印类型说明
- **常数**：打印十进制值

## 6. 集成设计

### 6.1 Flex和Bison集成
```c
// main.c
#include "lexer.h"
#include "parser.h"

extern FILE* yyin;
extern ASTNode* root;

int main(int argc, char** argv) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <input_file>\n", argv[0]);
        return 1;
    }
    
    yyin = fopen(argv[1], "r");
    if (!yyin) {
        perror("Failed to open file");
        return 1;
    }
    
    // 进行语法分析
    int result = yyparse();
    
    if (result == 0 && root != NULL) {
        // 无错误，打印语法树
        print_ast_preorder(root, 0);
    }
    
    fclose(yyin);
    if (root) free_ast(root);
    return result;
}
```

### 6.2 错误信息输出
```c
void yyerror(const char* msg) {
    fprintf(stderr, "Error type B at Line %d: %s\n", yylineno, msg);
}
```

## 7. 测试策略

### 7.1 测试用例分类
1. **正确程序**：验证语法树构建正确性
2. **语法错误程序**：验证错误检测和恢复
3. **复杂结构程序**：测试嵌套和复杂语法

### 7.2 验证方法
- 手动检查语法树输出格式
- 与示例输出对比
- 验证错误信息准确性

这个设计文档为语法分析器的实现提供了完整的技术规范和实现指导。
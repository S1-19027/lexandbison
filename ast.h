// ast.h
#ifndef AST_H
#define AST_H

// 语法树节点类型
typedef enum
{
    Node_CompUnit,
    Node_Decl,
    Node_ConstDecl,
    Node_BType,
    Node_ConstDef,
    Node_ConstInitVal,
    Node_VarDecl,
    Node_VarDef,
    Node_VarDefList,
    Node_InitVal,
    Node_FuncDef,
    Node_FuncFParams,
    Node_FuncFParam,
    Node_FuncType,
    Node_BlockItem,
    Node_Block,
    Node_Stmt,
    Node_Exp,
    Node_Cond,
    Node_LVal,
    Node_PrimaryExp,
    Node_Number,
    Node_UnaryExp,
    Node_UnaryOp,
    Node_FuncRParam,
    Node_FuncRParams,
    Node_FuncFParamDims,
    Node_MulExp,
    Node_AddExp,
    Node_RelExp,
    Node_EqExp,
    Node_LAndExp,
    Node_LOrExp,
    Node_ConstExp,
    Node_DeclList, // 添加
    Node_Array,    // 添加
    Node_Token     // 词法单元/终结符节点
} NodeType;
// 语法树结构
typedef struct ASTNode
{
    NodeType type;             // 节点类型
    char name[64];             // 节点名称
    int line;                  // 所在行号
    int token_type;            // 词法单元类型（仅对终结符节点有效）
    char value[256];           // 词法单元值（仅对终结符节点有效）
    struct ASTNode **children; // 子节点数组
    int child_count;           // 子节点数量
    int is_epsilon;            // 是否为空节点标志

    // 语义分析相关属性
    int data_type;  // 数据类型：0=int, 1=float, 2=void, 3=array
    int is_array;   // 是否是数组
    int array_dims; // 数组维度
} ASTNode;

typedef struct
{
    int line;          // 错误行号
    char message[100]; // 错误信息
} Error;

typedef struct
{
    int line;          // 错误行号
    char message[100]; // 错误信息
} SyntaxError;

#endif

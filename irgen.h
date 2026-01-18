// irgen.h - 中间代码生成器头文件
#ifndef IRGEN_H
#define IRGEN_H

#include "ast.h"
#include "semantic.h"

// 三地址码指令类型
typedef enum
{
    // 算术运算
    IR_ADD, // t = a + b
    IR_SUB, // t = a - b
    IR_MUL, // t = a * b
    IR_DIV, // t = a / b
    IR_MOD, // t = a % b
    IR_NEG, // t = -a

    // 关系运算
    IR_LT, // t = a < b
    IR_GT, // t = a > b
    IR_LE, // t = a <= b
    IR_GE, // t = a >= b
    IR_EQ, // t = a == b
    IR_NE, // t = a != b

    // 逻辑运算
    IR_AND, // t = a && b
    IR_OR,  // t = a || b
    IR_NOT, // t = !a

    // 赋值
    IR_ASSIGN, // t = a

    // 跳转
    IR_GOTO,  // goto L
    IR_IF,    // if a goto L
    IR_IFNOT, // ifnot a goto L

    // 函数调用
    IR_PARAM,  // param a
    IR_CALL,   // t = call f, n
    IR_RETURN, // return [a]

    // 数组访问
    IR_ARRAY_LOAD,  // t = a[i]
    IR_ARRAY_STORE, // a[i] = t

    // 标签
    IR_LABEL, // label L:

    // 函数定义
    IR_FUNC_BEGIN, // function f:
    IR_FUNC_END    // end function
} IROpcode;

// 操作数类型
typedef enum
{
    OP_TEMP,  // 临时变量 t1, t2, ...
    OP_VAR,   // 用户变量
    OP_CONST, // 常量
    OP_LABEL, // 标签
    OP_FUNC   // 函数名
} OperandType;

// 操作数
typedef struct
{
    OperandType type;
    union
    {
        int temp_no;        // 临时变量编号
        char var_name[64];  // 变量名
        int const_val;      // 整型常量值
        float const_fval;   // 浮点常量值
        char label[32];     // 标签名
        char func_name[64]; // 函数名
    };
    bool is_float; // 是否为浮点数
} Operand;

// 三地址码指令
typedef struct IRCode
{
    IROpcode opcode;
    Operand result; // 结果操作数
    Operand arg1;   // 第一个操作数
    Operand arg2;   // 第二个操作数
    struct IRCode *next;
} IRCode;

// 全局变量
extern IRCode *ir_code_head;
extern IRCode *ir_code_tail;
extern int temp_count;
extern int label_count;

// 函数声明
void init_irgen(void);
void generate_ir(ASTNode *root);
void print_ir_code(void);
void free_ir_code(void);

// 辅助函数
int new_temp(void);
int new_label(void);
IRCode *create_ir_code(IROpcode op);
void append_ir_code(IRCode *code);
Operand make_temp(int no);
Operand make_var(const char *name);
Operand make_const(int val);
Operand make_float_const(float val);
Operand make_label(int label_no);
Operand make_func(const char *name);

// 代码生成函数
void gen_compunit(ASTNode *node);
void gen_decl(ASTNode *node);
void gen_const_decl(ASTNode *node);
void gen_var_decl(ASTNode *node);
void gen_func_def(ASTNode *node);
void gen_block(ASTNode *node);
void gen_stmt(ASTNode *node);
Operand gen_exp(ASTNode *node);
Operand gen_cond(ASTNode *node, int true_label, int false_label);
Operand gen_lval(ASTNode *node);

#endif // IRGEN_H

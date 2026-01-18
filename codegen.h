// codegen.h - RISC-V 32位代码生成器头文件
#ifndef CODEGEN_H
#define CODEGEN_H

#include "irgen.h"

// RISC-V寄存器定义
typedef enum
{
    REG_ZERO = 0, // x0: 硬件零寄存器
    REG_RA = 1,   // x1: 返回地址
    REG_SP = 2,   // x2: 栈指针
    REG_GP = 3,   // x3: 全局指针
    REG_TP = 4,   // x4: 线程指针
    REG_T0 = 5,   // x5-x7: 临时寄存器
    REG_T1 = 6,
    REG_T2 = 7,
    REG_S0 = 8, // x8-x9: 保存寄存器/帧指针
    REG_S1 = 9,
    REG_A0 = 10, // x10-x17: 函数参数/返回值
    REG_A1 = 11,
    REG_A2 = 12,
    REG_A3 = 13,
    REG_A4 = 14,
    REG_A5 = 15,
    REG_A6 = 16,
    REG_A7 = 17,
    REG_S2 = 18, // x18-x27: 保存寄存器
    REG_S3 = 19,
    REG_S4 = 20,
    REG_S5 = 21,
    REG_S6 = 22,
    REG_S7 = 23,
    REG_S8 = 24,
    REG_S9 = 25,
    REG_S10 = 26,
    REG_S11 = 27,
    REG_T3 = 28, // x28-x31: 临时寄存器
    REG_T4 = 29,
    REG_T5 = 30,
    REG_T6 = 31
} RISCVRegister;

// 寄存器名称
extern const char *reg_names[];

// 变量到栈位置的映射
typedef struct VarLocation
{
    char name[64];
    int stack_offset; // 相对于fp的偏移量
    struct VarLocation *next;
} VarLocation;

// 临时变量到寄存器的映射
typedef struct TempRegMap
{
    int temp_no;
    RISCVRegister reg;
    bool in_use;
} TempRegMap;

// 代码生成上下文
typedef struct CodeGenContext
{
    VarLocation *var_locations;
    TempRegMap temp_regs[32];
    int stack_size;
    char current_func[64];
    int temp_reg_count;
    FILE *output;
} CodeGenContext;

// 函数声明
void init_codegen(FILE *output);
void generate_riscv(IRCode *ir_head, FILE *output);
void free_codegen(void);

// 辅助函数
RISCVRegister alloc_temp_reg(CodeGenContext *ctx, int temp_no);
void free_temp_reg(CodeGenContext *ctx, int temp_no);
int get_var_offset(CodeGenContext *ctx, const char *var_name);
void add_var_location(CodeGenContext *ctx, const char *var_name, int offset);

// 指令生成函数
void gen_riscv_prologue(CodeGenContext *ctx, const char *func_name);
void gen_riscv_epilogue(CodeGenContext *ctx, const char *func_name);
void gen_riscv_arithmetic(CodeGenContext *ctx, IRCode *code);
void gen_riscv_load(CodeGenContext *ctx, IRCode *code);
void gen_riscv_store(CodeGenContext *ctx, IRCode *code);
void gen_riscv_branch(CodeGenContext *ctx, IRCode *code);
void gen_riscv_call(CodeGenContext *ctx, IRCode *code);
void gen_riscv_return(CodeGenContext *ctx, IRCode *code);

#endif // CODEGEN_H

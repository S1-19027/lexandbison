// codegen.c - RISC-V 32位代码生成器实现
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "codegen.h"
#include "irgen.h"

// RISC-V寄存器名称
const char *reg_names[] = {
    "zero", "ra", "sp", "gp", "tp", "t0", "t1", "t2",
    "s0", "s1", "a0", "a1", "a2", "a3", "a4", "a5",
    "a6", "a7", "s2", "s3", "s4", "s5", "s6", "s7",
    "s8", "s9", "s10", "s11", "t3", "t4", "t5", "t6"};

// 全局上下文
static CodeGenContext global_ctx;

// 初始化代码生成器
void init_codegen(FILE *output)
{
    global_ctx.var_locations = NULL;
    global_ctx.stack_size = 0;
    global_ctx.temp_reg_count = 0;
    global_ctx.output = output;
    global_ctx.current_func[0] = '\0';

    // 初始化临时寄存器映射
    for (int i = 0; i < 32; i++)
    {
        global_ctx.temp_regs[i].temp_no = -1;
        global_ctx.temp_regs[i].reg = REG_ZERO;
        global_ctx.temp_regs[i].in_use = false;
    }
}

// 释放代码生成器资源
void free_codegen(void)
{
    VarLocation *loc = global_ctx.var_locations;
    while (loc)
    {
        VarLocation *next = loc->next;
        free(loc);
        loc = next;
    }
    global_ctx.var_locations = NULL;
}

// 分配临时寄存器
RISCVRegister alloc_temp_reg(CodeGenContext *ctx, int temp_no)
{
    // 首先查找是否已经分配
    for (int i = 0; i < ctx->temp_reg_count; i++)
    {
        if (ctx->temp_regs[i].temp_no == temp_no)
        {
            return ctx->temp_regs[i].reg;
        }
    }

    // 分配新的临时寄存器 (使用t0-t6)
    RISCVRegister available_regs[] = {REG_T0, REG_T1, REG_T2, REG_T3, REG_T4, REG_T5, REG_T6};
    int num_available = sizeof(available_regs) / sizeof(available_regs[0]);

    for (int i = 0; i < num_available; i++)
    {
        bool used = false;
        for (int j = 0; j < ctx->temp_reg_count; j++)
        {
            if (ctx->temp_regs[j].reg == available_regs[i] && ctx->temp_regs[j].in_use)
            {
                used = true;
                break;
            }
        }

        if (!used)
        {
            if (ctx->temp_reg_count < 32)
            {
                ctx->temp_regs[ctx->temp_reg_count].temp_no = temp_no;
                ctx->temp_regs[ctx->temp_reg_count].reg = available_regs[i];
                ctx->temp_regs[ctx->temp_reg_count].in_use = true;
                ctx->temp_reg_count++;
                return available_regs[i];
            }
        }
    }

    // 如果没有可用寄存器，返回t0
    return REG_T0;
}

// 释放临时寄存器
void free_temp_reg(CodeGenContext *ctx, int temp_no)
{
    for (int i = 0; i < ctx->temp_reg_count; i++)
    {
        if (ctx->temp_regs[i].temp_no == temp_no)
        {
            ctx->temp_regs[i].in_use = false;
            return;
        }
    }
}

// 获取变量的栈偏移
int get_var_offset(CodeGenContext *ctx, const char *var_name)
{
    VarLocation *loc = ctx->var_locations;
    while (loc)
    {
        if (strcmp(loc->name, var_name) == 0)
        {
            return loc->stack_offset;
        }
        loc = loc->next;
    }

    // 如果变量不存在，分配新的栈空间
    int offset = ctx->stack_size + 4;
    add_var_location(ctx, var_name, offset);
    ctx->stack_size = offset;
    return offset;
}

// 添加变量位置
void add_var_location(CodeGenContext *ctx, const char *var_name, int offset)
{
    VarLocation *loc = (VarLocation *)malloc(sizeof(VarLocation));
    strncpy(loc->name, var_name, sizeof(loc->name) - 1);
    loc->stack_offset = offset;
    loc->next = ctx->var_locations;
    ctx->var_locations = loc;
}

// 加载操作数到寄存器
RISCVRegister load_operand(CodeGenContext *ctx, Operand op, RISCVRegister target)
{
    FILE *out = ctx->output;

    switch (op.type)
    {
    case OP_CONST:
        // 加载立即数
        fprintf(out, "    li %s, %d\n", reg_names[target], op.const_val);
        return target;

    case OP_TEMP:
        // 临时变量已经在寄存器中
        return alloc_temp_reg(ctx, op.temp_no);

    case OP_VAR:
    {
        // 从栈中加载变量
        int offset = get_var_offset(ctx, op.var_name);
        fprintf(out, "    lw %s, -%d(s0)\n", reg_names[target], offset);
        return target;
    }

    default:
        return target;
    }
}

// 存储寄存器到操作数
void store_operand(CodeGenContext *ctx, RISCVRegister src, Operand dest)
{
    FILE *out = ctx->output;

    switch (dest.type)
    {
    case OP_TEMP:
        // 临时变量保持在寄存器中
        break;

    case OP_VAR:
    {
        // 存储到栈中
        int offset = get_var_offset(ctx, dest.var_name);
        fprintf(out, "    sw %s, -%d(s0)\n", reg_names[src], offset);
        break;
    }

    default:
        break;
    }
}

// 生成函数序言
void gen_riscv_prologue(CodeGenContext *ctx, const char *func_name)
{
    FILE *out = ctx->output;

    fprintf(out, "\n.globl %s\n", func_name);
    fprintf(out, "%s:\n", func_name);
    fprintf(out, "    # 函数序言\n");
    fprintf(out, "    addi sp, sp, -128\n"); // 分配栈帧
    fprintf(out, "    sw ra, 124(sp)\n");    // 保存返回地址
    fprintf(out, "    sw s0, 120(sp)\n");    // 保存帧指针
    fprintf(out, "    addi s0, sp, 128\n");  // 设置帧指针
}

// 生成函数尾声
void gen_riscv_epilogue(CodeGenContext *ctx, const char *func_name)
{
    FILE *out = ctx->output;

    fprintf(out, "    # 函数尾声\n");
    fprintf(out, "    lw ra, 124(sp)\n");   // 恢复返回地址
    fprintf(out, "    lw s0, 120(sp)\n");   // 恢复帧指针
    fprintf(out, "    addi sp, sp, 128\n"); // 释放栈帧
    fprintf(out, "    ret\n");
}

// 生成算术运算指令
void gen_riscv_arithmetic(CodeGenContext *ctx, IRCode *code)
{
    FILE *out = ctx->output;
    RISCVRegister rd, rs1, rs2;

    // 加载操作数
    rs1 = load_operand(ctx, code->arg1, REG_T3);
    rs2 = load_operand(ctx, code->arg2, REG_T4);

    // 分配目标寄存器
    if (code->result.type == OP_TEMP)
    {
        rd = alloc_temp_reg(ctx, code->result.temp_no);
    }
    else
    {
        rd = REG_T5;
    }

    // 生成指令
    switch (code->opcode)
    {
    case IR_ADD:
        fprintf(out, "    add %s, %s, %s\n", reg_names[rd], reg_names[rs1], reg_names[rs2]);
        break;
    case IR_SUB:
        fprintf(out, "    sub %s, %s, %s\n", reg_names[rd], reg_names[rs1], reg_names[rs2]);
        break;
    case IR_MUL:
        fprintf(out, "    mul %s, %s, %s\n", reg_names[rd], reg_names[rs1], reg_names[rs2]);
        break;
    case IR_DIV:
        fprintf(out, "    div %s, %s, %s\n", reg_names[rd], reg_names[rs1], reg_names[rs2]);
        break;
    case IR_MOD:
        fprintf(out, "    rem %s, %s, %s\n", reg_names[rd], reg_names[rs1], reg_names[rs2]);
        break;
    case IR_LT:
        fprintf(out, "    slt %s, %s, %s\n", reg_names[rd], reg_names[rs1], reg_names[rs2]);
        break;
    case IR_GT:
        fprintf(out, "    slt %s, %s, %s\n", reg_names[rd], reg_names[rs2], reg_names[rs1]);
        break;
    case IR_LE:
        fprintf(out, "    slt %s, %s, %s\n", reg_names[rd], reg_names[rs2], reg_names[rs1]);
        fprintf(out, "    xori %s, %s, 1\n", reg_names[rd], reg_names[rd]);
        break;
    case IR_GE:
        fprintf(out, "    slt %s, %s, %s\n", reg_names[rd], reg_names[rs1], reg_names[rs2]);
        fprintf(out, "    xori %s, %s, 1\n", reg_names[rd], reg_names[rd]);
        break;
    case IR_EQ:
        fprintf(out, "    sub %s, %s, %s\n", reg_names[rd], reg_names[rs1], reg_names[rs2]);
        fprintf(out, "    seqz %s, %s\n", reg_names[rd], reg_names[rd]);
        break;
    case IR_NE:
        fprintf(out, "    sub %s, %s, %s\n", reg_names[rd], reg_names[rs1], reg_names[rs2]);
        fprintf(out, "    snez %s, %s\n", reg_names[rd], reg_names[rd]);
        break;
    case IR_AND:
        fprintf(out, "    and %s, %s, %s\n", reg_names[rd], reg_names[rs1], reg_names[rs2]);
        break;
    case IR_OR:
        fprintf(out, "    or %s, %s, %s\n", reg_names[rd], reg_names[rs1], reg_names[rs2]);
        break;
    case IR_NEG:
        rs1 = load_operand(ctx, code->arg1, REG_T3);
        fprintf(out, "    neg %s, %s\n", reg_names[rd], reg_names[rs1]);
        break;
    case IR_NOT:
        rs1 = load_operand(ctx, code->arg1, REG_T3);
        fprintf(out, "    seqz %s, %s\n", reg_names[rd], reg_names[rs1]);
        break;
    default:
        break;
    }

    // 存储结果
    if (code->result.type != OP_TEMP)
    {
        store_operand(ctx, rd, code->result);
    }
}

// 生成赋值指令
void gen_riscv_assign(CodeGenContext *ctx, IRCode *code)
{
    FILE *out = ctx->output;
    RISCVRegister rs;

    // 加载源操作数
    rs = load_operand(ctx, code->arg1, REG_T3);

    // 存储到目标
    if (code->result.type == OP_TEMP)
    {
        RISCVRegister rd = alloc_temp_reg(ctx, code->result.temp_no);
        if (rd != rs)
        {
            fprintf(out, "    mv %s, %s\n", reg_names[rd], reg_names[rs]);
        }
    }
    else
    {
        store_operand(ctx, rs, code->result);
    }
}

// 生成跳转指令
void gen_riscv_branch(CodeGenContext *ctx, IRCode *code)
{
    FILE *out = ctx->output;

    switch (code->opcode)
    {
    case IR_GOTO:
        fprintf(out, "    j %s\n", code->arg1.label);
        break;

    case IR_IF:
    {
        RISCVRegister rs = load_operand(ctx, code->arg1, REG_T3);
        fprintf(out, "    bnez %s, %s\n", reg_names[rs], code->arg2.label);
        break;
    }

    case IR_IFNOT:
    {
        RISCVRegister rs = load_operand(ctx, code->arg1, REG_T3);
        fprintf(out, "    beqz %s, %s\n", reg_names[rs], code->arg2.label);
        break;
    }

    case IR_LABEL:
        fprintf(out, "%s:\n", code->arg1.label);
        break;

    default:
        break;
    }
}

// 生成函数调用指令
void gen_riscv_call(CodeGenContext *ctx, IRCode *code)
{
    FILE *out = ctx->output;

    if (code->opcode == IR_PARAM)
    {
        // 参数传递（简化处理：通过栈传递）
        RISCVRegister rs = load_operand(ctx, code->arg1, REG_T3);
        fprintf(out, "    addi sp, sp, -4\n");
        fprintf(out, "    sw %s, 0(sp)\n", reg_names[rs]);
    }
    else if (code->opcode == IR_CALL)
    {
        // 调用函数
        fprintf(out, "    call %s\n", code->arg1.func_name);

        // 清理参数（如果有）
        if (code->arg2.type == OP_CONST && code->arg2.const_val > 0)
        {
            fprintf(out, "    addi sp, sp, %d\n", code->arg2.const_val * 4);
        }

        // 保存返回值
        if (code->result.type == OP_TEMP)
        {
            RISCVRegister rd = alloc_temp_reg(ctx, code->result.temp_no);
            fprintf(out, "    mv %s, a0\n", reg_names[rd]);
        }
        else if (code->result.type == OP_VAR)
        {
            store_operand(ctx, REG_A0, code->result);
        }
    }
}

// 生成返回指令
void gen_riscv_return(CodeGenContext *ctx, IRCode *code)
{
    FILE *out = ctx->output;

    if (code->arg1.type != OP_TEMP || code->arg1.temp_no >= 0)
    {
        // 有返回值
        RISCVRegister rs = load_operand(ctx, code->arg1, REG_A0);
        if (rs != REG_A0)
        {
            fprintf(out, "    mv a0, %s\n", reg_names[rs]);
        }
    }

    // 跳转到函数尾声（使用唯一标签）
    if (ctx->current_func[0] != '\0')
    {
        fprintf(out, "    j .L_%s_epilogue\n", ctx->current_func);
    }
    else
    {
        fprintf(out, "    ret\n");
    }
}

// 主代码生成函数
void generate_riscv(IRCode *ir_head, FILE *output)
{
    init_codegen(output);
    CodeGenContext *ctx = &global_ctx;

    fprintf(output, "# RISC-V 32位汇编代码\n");
    fprintf(output, "    .text\n");

    IRCode *code = ir_head;
    char current_func[64] = "";
    bool in_function = false;

    while (code != NULL)
    {
        switch (code->opcode)
        {
        case IR_FUNC_BEGIN:
            strcpy(current_func, code->arg1.func_name);
            strncpy(ctx->current_func, current_func, sizeof(ctx->current_func) - 1);
            ctx->current_func[sizeof(ctx->current_func) - 1] = '\0';
            gen_riscv_prologue(ctx, current_func);
            in_function = true;
            break;

        case IR_FUNC_END:
            if (ctx->current_func[0] != '\0')
            {
                fprintf(output, ".L_%s_epilogue:\n", ctx->current_func);
            }
            gen_riscv_epilogue(ctx, current_func);
            in_function = false;
            // 重置上下文
            ctx->stack_size = 0;
            ctx->temp_reg_count = 0;
            ctx->current_func[0] = '\0';
            break;

        case IR_ADD:
        case IR_SUB:
        case IR_MUL:
        case IR_DIV:
        case IR_MOD:
        case IR_LT:
        case IR_GT:
        case IR_LE:
        case IR_GE:
        case IR_EQ:
        case IR_NE:
        case IR_AND:
        case IR_OR:
        case IR_NEG:
        case IR_NOT:
            gen_riscv_arithmetic(ctx, code);
            break;

        case IR_ASSIGN:
            gen_riscv_assign(ctx, code);
            break;

        case IR_GOTO:
        case IR_IF:
        case IR_IFNOT:
        case IR_LABEL:
            gen_riscv_branch(ctx, code);
            break;

        case IR_PARAM:
        case IR_CALL:
            gen_riscv_call(ctx, code);
            break;

        case IR_RETURN:
            gen_riscv_return(ctx, code);
            break;

        default:
            break;
        }

        code = code->next;
    }

    fprintf(output, "\n# 代码生成完成\n");
}

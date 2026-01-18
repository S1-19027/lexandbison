// irgen.c - 中间代码生成器实现
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "irgen.h"
#include "ast.h"
#include "semantic.h"

// 全局变量
IRCode *ir_code_head = NULL;
IRCode *ir_code_tail = NULL;
int temp_count = 0;
int label_count = 0;

// 初始化中间代码生成器
void init_irgen(void)
{
    ir_code_head = NULL;
    ir_code_tail = NULL;
    temp_count = 0;
    label_count = 0;
}

// 创建新的临时变量
int new_temp(void)
{
    return temp_count++;
}

// 创建新的标签
int new_label(void)
{
    return label_count++;
}

// 创建IR指令
IRCode *create_ir_code(IROpcode op)
{
    IRCode *code = (IRCode *)malloc(sizeof(IRCode));
    code->opcode = op;
    code->next = NULL;
    memset(&code->result, 0, sizeof(Operand));
    memset(&code->arg1, 0, sizeof(Operand));
    memset(&code->arg2, 0, sizeof(Operand));
    return code;
}

// 添加IR指令到链表
void append_ir_code(IRCode *code)
{
    if (ir_code_tail == NULL)
    {
        ir_code_head = ir_code_tail = code;
    }
    else
    {
        ir_code_tail->next = code;
        ir_code_tail = code;
    }
}

// 创建临时变量操作数
Operand make_temp(int no)
{
    Operand op;
    op.type = OP_TEMP;
    op.temp_no = no;
    op.is_float = false;
    return op;
}

// 创建变量操作数
Operand make_var(const char *name)
{
    Operand op;
    op.type = OP_VAR;
    strncpy(op.var_name, name, sizeof(op.var_name) - 1);
    op.is_float = false;
    return op;
}

// 创建整型常量操作数
Operand make_const(int val)
{
    Operand op;
    op.type = OP_CONST;
    op.const_val = val;
    op.is_float = false;
    return op;
}

// 创建浮点常量操作数
Operand make_float_const(float val)
{
    Operand op;
    op.type = OP_CONST;
    op.const_fval = val;
    op.is_float = true;
    return op;
}

// 创建标签操作数
Operand make_label(int label_no)
{
    Operand op;
    op.type = OP_LABEL;
    snprintf(op.label, sizeof(op.label), "L%d", label_no);
    return op;
}

// 创建函数名操作数
Operand make_func(const char *name)
{
    Operand op;
    op.type = OP_FUNC;
    strncpy(op.func_name, name, sizeof(op.func_name) - 1);
    return op;
}

// 打印操作数
void print_operand(Operand op)
{
    switch (op.type)
    {
    case OP_TEMP:
        printf("t%d", op.temp_no);
        break;
    case OP_VAR:
        printf("%s", op.var_name);
        break;
    case OP_CONST:
        if (op.is_float)
        {
            printf("%.2f", op.const_fval);
        }
        else
        {
            printf("%d", op.const_val);
        }
        break;
    case OP_LABEL:
        printf("%s", op.label);
        break;
    case OP_FUNC:
        printf("%s", op.func_name);
        break;
    }
}

// 打印三地址码
void print_ir_code(void)
{
    printf("\n=== 中间代码 (三地址码) ===\n");
    IRCode *code = ir_code_head;
    while (code != NULL)
    {
        switch (code->opcode)
        {
        case IR_ADD:
            printf("  ");
            print_operand(code->result);
            printf(" = ");
            print_operand(code->arg1);
            printf(" + ");
            print_operand(code->arg2);
            printf("\n");
            break;
        case IR_SUB:
            printf("  ");
            print_operand(code->result);
            printf(" = ");
            print_operand(code->arg1);
            printf(" - ");
            print_operand(code->arg2);
            printf("\n");
            break;
        case IR_MUL:
            printf("  ");
            print_operand(code->result);
            printf(" = ");
            print_operand(code->arg1);
            printf(" * ");
            print_operand(code->arg2);
            printf("\n");
            break;
        case IR_DIV:
            printf("  ");
            print_operand(code->result);
            printf(" = ");
            print_operand(code->arg1);
            printf(" / ");
            print_operand(code->arg2);
            printf("\n");
            break;
        case IR_MOD:
            printf("  ");
            print_operand(code->result);
            printf(" = ");
            print_operand(code->arg1);
            printf(" %% ");
            print_operand(code->arg2);
            printf("\n");
            break;
        case IR_NEG:
            printf("  ");
            print_operand(code->result);
            printf(" = -");
            print_operand(code->arg1);
            printf("\n");
            break;
        case IR_LT:
            printf("  ");
            print_operand(code->result);
            printf(" = ");
            print_operand(code->arg1);
            printf(" < ");
            print_operand(code->arg2);
            printf("\n");
            break;
        case IR_GT:
            printf("  ");
            print_operand(code->result);
            printf(" = ");
            print_operand(code->arg1);
            printf(" > ");
            print_operand(code->arg2);
            printf("\n");
            break;
        case IR_LE:
            printf("  ");
            print_operand(code->result);
            printf(" = ");
            print_operand(code->arg1);
            printf(" <= ");
            print_operand(code->arg2);
            printf("\n");
            break;
        case IR_GE:
            printf("  ");
            print_operand(code->result);
            printf(" = ");
            print_operand(code->arg1);
            printf(" >= ");
            print_operand(code->arg2);
            printf("\n");
            break;
        case IR_EQ:
            printf("  ");
            print_operand(code->result);
            printf(" = ");
            print_operand(code->arg1);
            printf(" == ");
            print_operand(code->arg2);
            printf("\n");
            break;
        case IR_NE:
            printf("  ");
            print_operand(code->result);
            printf(" = ");
            print_operand(code->arg1);
            printf(" != ");
            print_operand(code->arg2);
            printf("\n");
            break;
        case IR_AND:
            printf("  ");
            print_operand(code->result);
            printf(" = ");
            print_operand(code->arg1);
            printf(" && ");
            print_operand(code->arg2);
            printf("\n");
            break;
        case IR_OR:
            printf("  ");
            print_operand(code->result);
            printf(" = ");
            print_operand(code->arg1);
            printf(" || ");
            print_operand(code->arg2);
            printf("\n");
            break;
        case IR_NOT:
            printf("  ");
            print_operand(code->result);
            printf(" = !");
            print_operand(code->arg1);
            printf("\n");
            break;
        case IR_ASSIGN:
            printf("  ");
            print_operand(code->result);
            printf(" = ");
            print_operand(code->arg1);
            printf("\n");
            break;
        case IR_GOTO:
            printf("  goto ");
            print_operand(code->arg1);
            printf("\n");
            break;
        case IR_IF:
            printf("  if ");
            print_operand(code->arg1);
            printf(" goto ");
            print_operand(code->arg2);
            printf("\n");
            break;
        case IR_IFNOT:
            printf("  ifnot ");
            print_operand(code->arg1);
            printf(" goto ");
            print_operand(code->arg2);
            printf("\n");
            break;
        case IR_PARAM:
            printf("  param ");
            print_operand(code->arg1);
            printf("\n");
            break;
        case IR_CALL:
            printf("  ");
            if (code->result.type != OP_TEMP || code->result.temp_no >= 0)
            {
                print_operand(code->result);
                printf(" = ");
            }
            printf("call ");
            print_operand(code->arg1);
            if (code->arg2.type == OP_CONST)
            {
                printf(", %d", code->arg2.const_val);
            }
            printf("\n");
            break;
        case IR_RETURN:
            printf("  return");
            if (code->arg1.type != OP_TEMP || code->arg1.temp_no >= 0)
            {
                printf(" ");
                print_operand(code->arg1);
            }
            printf("\n");
            break;
        case IR_LABEL:
            print_operand(code->arg1);
            printf(":\n");
            break;
        case IR_FUNC_BEGIN:
            printf("FUNCTION ");
            print_operand(code->arg1);
            printf(" :\n");
            break;
        case IR_FUNC_END:
            printf("END FUNCTION ");
            print_operand(code->arg1);
            printf("\n\n");
            break;
        default:
            printf("  <unknown opcode>\n");
            break;
        }
        code = code->next;
    }
}

// 释放IR代码内存
void free_ir_code(void)
{
    IRCode *code = ir_code_head;
    while (code != NULL)
    {
        IRCode *next = code->next;
        free(code);
        code = next;
    }
    ir_code_head = ir_code_tail = NULL;
}

// 获取子节点
static ASTNode *get_child(ASTNode *node, const char *name)
{
    if (!node)
        return NULL;
    for (int i = 0; i < node->child_count; i++)
    {
        if (strcmp(node->children[i]->name, name) == 0)
        {
            return node->children[i];
        }
    }
    return NULL;
}

// 生成表达式的IR代码
Operand gen_exp(ASTNode *node)
{
    if (!node)
    {
        return make_const(0);
    }

    // 处理数字常量
    if (strcmp(node->name, "Number") == 0 || strcmp(node->name, "INTCON") == 0)
    {
        if (node->child_count > 0)
        {
            int val = atoi(node->children[0]->value);
            return make_const(val);
        }
        else if (node->token_type > 0)
        {
            int val = atoi(node->value);
            return make_const(val);
        }
        return make_const(0);
    }

    // 处理左值
    if (strcmp(node->name, "LVal") == 0)
    {
        return gen_lval(node);
    }

    // 处理一元表达式
    if (strcmp(node->name, "UnaryExp") == 0)
    {
        // 检查是否是函数调用
        for (int i = 0; i < node->child_count; i++)
        {
            if (strcmp(node->children[i]->name, "FuncRParams") == 0 ||
                strcmp(node->children[i]->name, "LPARENT") == 0)
            {
                // 函数调用
                char func_name[64] = "";
                for (int j = 0; j < node->child_count; j++)
                {
                    if (strcmp(node->children[j]->name, "ID") == 0)
                    {
                        strcpy(func_name, node->children[j]->value);
                        break;
                    }
                }

                // 处理参数
                ASTNode *params = get_child(node, "FuncRParams");
                int param_count = 0;
                if (params)
                {
                    for (int j = 0; j < params->child_count; j++)
                    {
                        if (strcmp(params->children[j]->name, "Exp") == 0)
                        {
                            Operand arg = gen_exp(params->children[j]);
                            IRCode *param_code = create_ir_code(IR_PARAM);
                            param_code->arg1 = arg;
                            append_ir_code(param_code);
                            param_count++;
                        }
                    }
                }

                // 生成函数调用
                int t = new_temp();
                IRCode *call_code = create_ir_code(IR_CALL);
                call_code->result = make_temp(t);
                call_code->arg1 = make_func(func_name);
                call_code->arg2 = make_const(param_count);
                append_ir_code(call_code);
                return make_temp(t);
            }
        }

        // 检查一元运算符
        for (int i = 0; i < node->child_count; i++)
        {
            if (strcmp(node->children[i]->name, "UnaryOp") == 0)
            {
                ASTNode *op_node = node->children[i];
                Operand arg = gen_exp(node->children[i + 1]);
                int t = new_temp();

                if (op_node->child_count > 0)
                {
                    const char *op = op_node->children[0]->value;
                    if (strcmp(op, "-") == 0)
                    {
                        IRCode *code = create_ir_code(IR_NEG);
                        code->result = make_temp(t);
                        code->arg1 = arg;
                        append_ir_code(code);
                        return make_temp(t);
                    }
                    else if (strcmp(op, "!") == 0)
                    {
                        IRCode *code = create_ir_code(IR_NOT);
                        code->result = make_temp(t);
                        code->arg1 = arg;
                        append_ir_code(code);
                        return make_temp(t);
                    }
                    else if (strcmp(op, "+") == 0)
                    {
                        return arg; // 正号不做处理
                    }
                }
            }
        }

        // 递归处理子节点
        if (node->child_count > 0)
        {
            return gen_exp(node->children[0]);
        }
    }

    // 处理基本表达式
    if (strcmp(node->name, "PrimaryExp") == 0)
    {
        if (node->child_count > 0)
        {
            return gen_exp(node->children[0]);
        }
    }

    // 处理乘除表达式
    if (strcmp(node->name, "MulExp") == 0)
    {
        if (node->child_count >= 3)
        {
            Operand left = gen_exp(node->children[0]);
            Operand right = gen_exp(node->children[2]);
            int t = new_temp();
            IRCode *code = NULL;

            const char *op = node->children[1]->value;
            if (strcmp(op, "*") == 0)
            {
                code = create_ir_code(IR_MUL);
            }
            else if (strcmp(op, "/") == 0)
            {
                code = create_ir_code(IR_DIV);
            }
            else if (strcmp(op, "%") == 0)
            {
                code = create_ir_code(IR_MOD);
            }

            if (code)
            {
                code->result = make_temp(t);
                code->arg1 = left;
                code->arg2 = right;
                append_ir_code(code);
                return make_temp(t);
            }
        }
        else if (node->child_count > 0)
        {
            return gen_exp(node->children[0]);
        }
    }

    // 处理加减表达式
    if (strcmp(node->name, "AddExp") == 0)
    {
        if (node->child_count >= 3)
        {
            Operand left = gen_exp(node->children[0]);
            Operand right = gen_exp(node->children[2]);
            int t = new_temp();
            IRCode *code = NULL;

            const char *op = node->children[1]->value;
            if (strcmp(op, "+") == 0)
            {
                code = create_ir_code(IR_ADD);
            }
            else if (strcmp(op, "-") == 0)
            {
                code = create_ir_code(IR_SUB);
            }

            if (code)
            {
                code->result = make_temp(t);
                code->arg1 = left;
                code->arg2 = right;
                append_ir_code(code);
                return make_temp(t);
            }
        }
        else if (node->child_count > 0)
        {
            return gen_exp(node->children[0]);
        }
    }

    // 处理关系表达式
    if (strcmp(node->name, "RelExp") == 0)
    {
        if (node->child_count >= 3)
        {
            Operand left = gen_exp(node->children[0]);
            Operand right = gen_exp(node->children[2]);
            int t = new_temp();
            IRCode *code = NULL;

            const char *op = node->children[1]->value;
            if (strcmp(op, "<") == 0)
            {
                code = create_ir_code(IR_LT);
            }
            else if (strcmp(op, ">") == 0)
            {
                code = create_ir_code(IR_GT);
            }
            else if (strcmp(op, "<=") == 0)
            {
                code = create_ir_code(IR_LE);
            }
            else if (strcmp(op, ">=") == 0)
            {
                code = create_ir_code(IR_GE);
            }

            if (code)
            {
                code->result = make_temp(t);
                code->arg1 = left;
                code->arg2 = right;
                append_ir_code(code);
                return make_temp(t);
            }
        }
        else if (node->child_count > 0)
        {
            return gen_exp(node->children[0]);
        }
    }

    // 处理相等表达式
    if (strcmp(node->name, "EqExp") == 0)
    {
        if (node->child_count >= 3)
        {
            Operand left = gen_exp(node->children[0]);
            Operand right = gen_exp(node->children[2]);
            int t = new_temp();
            IRCode *code = NULL;

            const char *op = node->children[1]->value;
            if (strcmp(op, "==") == 0)
            {
                code = create_ir_code(IR_EQ);
            }
            else if (strcmp(op, "!=") == 0)
            {
                code = create_ir_code(IR_NE);
            }

            if (code)
            {
                code->result = make_temp(t);
                code->arg1 = left;
                code->arg2 = right;
                append_ir_code(code);
                return make_temp(t);
            }
        }
        else if (node->child_count > 0)
        {
            return gen_exp(node->children[0]);
        }
    }

    // 处理逻辑与表达式
    if (strcmp(node->name, "LAndExp") == 0)
    {
        if (node->child_count >= 3)
        {
            Operand left = gen_exp(node->children[0]);
            Operand right = gen_exp(node->children[2]);
            int t = new_temp();
            IRCode *code = create_ir_code(IR_AND);
            code->result = make_temp(t);
            code->arg1 = left;
            code->arg2 = right;
            append_ir_code(code);
            return make_temp(t);
        }
        else if (node->child_count > 0)
        {
            return gen_exp(node->children[0]);
        }
    }

    // 处理逻辑或表达式
    if (strcmp(node->name, "LOrExp") == 0)
    {
        if (node->child_count >= 3)
        {
            Operand left = gen_exp(node->children[0]);
            Operand right = gen_exp(node->children[2]);
            int t = new_temp();
            IRCode *code = create_ir_code(IR_OR);
            code->result = make_temp(t);
            code->arg1 = left;
            code->arg2 = right;
            append_ir_code(code);
            return make_temp(t);
        }
        else if (node->child_count > 0)
        {
            return gen_exp(node->children[0]);
        }
    }

    // 处理Exp节点
    if (strcmp(node->name, "Exp") == 0 || strcmp(node->name, "ConstExp") == 0)
    {
        if (node->child_count > 0)
        {
            return gen_exp(node->children[0]);
        }
    }

    // 默认返回0
    return make_const(0);
}

// 生成左值的IR代码
Operand gen_lval(ASTNode *node)
{
    if (!node)
        return make_const(0);

    for (int i = 0; i < node->child_count; i++)
    {
        if (strcmp(node->children[i]->name, "ID") == 0 ||
            strcmp(node->children[i]->name, "Ident") == 0)
        {
            return make_var(node->children[i]->value);
        }
    }

    return make_const(0);
}

// 生成语句的IR代码
void gen_stmt(ASTNode *node)
{
    if (!node)
        return;

    // 赋值语句
    for (int i = 0; i < node->child_count; i++)
    {
        if (strcmp(node->children[i]->name, "ASSIGN") == 0)
        {
            Operand lval = gen_lval(node->children[0]);
            Operand rval = gen_exp(node->children[i + 1]);
            IRCode *code = create_ir_code(IR_ASSIGN);
            code->result = lval;
            code->arg1 = rval;
            append_ir_code(code);
            return;
        }
    }

    // return语句
    for (int i = 0; i < node->child_count; i++)
    {
        if (strcmp(node->children[i]->name, "RETURNTK") == 0)
        {
            IRCode *code = create_ir_code(IR_RETURN);
            if (i + 1 < node->child_count && strcmp(node->children[i + 1]->name, "Exp") == 0)
            {
                code->arg1 = gen_exp(node->children[i + 1]);
            }
            else
            {
                code->arg1.type = OP_TEMP;
                code->arg1.temp_no = -1; // 表示无返回值
            }
            append_ir_code(code);
            return;
        }
    }

    // if语句
    for (int i = 0; i < node->child_count; i++)
    {
        if (strcmp(node->children[i]->name, "IFTK") == 0)
        {
            // 获取条件
            ASTNode *cond = NULL;
            ASTNode *then_stmt = NULL;
            ASTNode *else_stmt = NULL;

            for (int j = 0; j < node->child_count; j++)
            {
                if (strcmp(node->children[j]->name, "Cond") == 0)
                {
                    cond = node->children[j];
                }
                else if (strcmp(node->children[j]->name, "Stmt") == 0)
                {
                    if (then_stmt == NULL)
                    {
                        then_stmt = node->children[j];
                    }
                    else
                    {
                        else_stmt = node->children[j];
                    }
                }
                else if (strcmp(node->children[j]->name, "ELSETK") == 0 && j + 1 < node->child_count)
                {
                    else_stmt = node->children[j + 1];
                }
            }

            int true_label = new_label();
            int false_label = new_label();
            int end_label = new_label();

            // 生成条件代码
            if (cond)
            {
                Operand cond_result = gen_exp(cond->child_count > 0 ? cond->children[0] : cond);
                IRCode *if_code = create_ir_code(IR_IF);
                if_code->arg1 = cond_result;
                if_code->arg2 = make_label(true_label);
                append_ir_code(if_code);

                IRCode *goto_false = create_ir_code(IR_GOTO);
                goto_false->arg1 = make_label(false_label);
                append_ir_code(goto_false);
            }

            // true分支
            IRCode *true_lab = create_ir_code(IR_LABEL);
            true_lab->arg1 = make_label(true_label);
            append_ir_code(true_lab);

            if (then_stmt)
            {
                gen_stmt(then_stmt);
            }

            if (else_stmt)
            {
                IRCode *goto_end = create_ir_code(IR_GOTO);
                goto_end->arg1 = make_label(end_label);
                append_ir_code(goto_end);
            }

            // false分支
            IRCode *false_lab = create_ir_code(IR_LABEL);
            false_lab->arg1 = make_label(false_label);
            append_ir_code(false_lab);

            if (else_stmt)
            {
                gen_stmt(else_stmt);

                IRCode *end_lab = create_ir_code(IR_LABEL);
                end_lab->arg1 = make_label(end_label);
                append_ir_code(end_lab);
            }
            return;
        }
    }

    // while语句
    for (int i = 0; i < node->child_count; i++)
    {
        if (strcmp(node->children[i]->name, "WHILETK") == 0)
        {
            int start_label = new_label();
            int body_label = new_label();
            int end_label = new_label();

            // 开始标签
            IRCode *start_lab = create_ir_code(IR_LABEL);
            start_lab->arg1 = make_label(start_label);
            append_ir_code(start_lab);

            // 获取条件
            ASTNode *cond = NULL;
            ASTNode *body = NULL;
            for (int j = 0; j < node->child_count; j++)
            {
                if (strcmp(node->children[j]->name, "Cond") == 0)
                {
                    cond = node->children[j];
                }
                else if (strcmp(node->children[j]->name, "Stmt") == 0)
                {
                    body = node->children[j];
                }
            }

            // 生成条件代码
            if (cond)
            {
                Operand cond_result = gen_exp(cond->child_count > 0 ? cond->children[0] : cond);
                IRCode *if_code = create_ir_code(IR_IF);
                if_code->arg1 = cond_result;
                if_code->arg2 = make_label(body_label);
                append_ir_code(if_code);

                IRCode *goto_end = create_ir_code(IR_GOTO);
                goto_end->arg1 = make_label(end_label);
                append_ir_code(goto_end);
            }

            // 循环体标签
            IRCode *body_lab = create_ir_code(IR_LABEL);
            body_lab->arg1 = make_label(body_label);
            append_ir_code(body_lab);

            // 生成循环体
            if (body)
            {
                gen_stmt(body);
            }

            // 跳回开始
            IRCode *goto_start = create_ir_code(IR_GOTO);
            goto_start->arg1 = make_label(start_label);
            append_ir_code(goto_start);

            // 结束标签
            IRCode *end_lab = create_ir_code(IR_LABEL);
            end_lab->arg1 = make_label(end_label);
            append_ir_code(end_lab);
            return;
        }
    }

    // break语句
    for (int i = 0; i < node->child_count; i++)
    {
        if (strcmp(node->children[i]->name, "BREAKTK") == 0)
        {
            // break需要在while中记录end_label，这里简化处理
            return;
        }
    }

    // continue语句
    for (int i = 0; i < node->child_count; i++)
    {
        if (strcmp(node->children[i]->name, "CONTINUETK") == 0)
        {
            // continue需要在while中记录start_label，这里简化处理
            return;
        }
    }

    // 表达式语句
    for (int i = 0; i < node->child_count; i++)
    {
        if (strcmp(node->children[i]->name, "Exp") == 0)
        {
            gen_exp(node->children[i]);
            return;
        }
    }

    // Block语句
    for (int i = 0; i < node->child_count; i++)
    {
        if (strcmp(node->children[i]->name, "Block") == 0)
        {
            gen_block(node->children[i]);
            return;
        }
    }
}

// 生成代码块的IR代码
void gen_block(ASTNode *node)
{
    if (!node)
        return;

    for (int i = 0; i < node->child_count; i++)
    {
        ASTNode *child = node->children[i];
        if (strcmp(child->name, "BlockItem") == 0 || strcmp(child->name, "BlockItem_list") == 0)
        {
            gen_block(child);
        }
        else if (strcmp(child->name, "Stmt") == 0)
        {
            gen_stmt(child);
        }
        else if (strcmp(child->name, "Decl") == 0)
        {
            gen_decl(child);
        }
    }
}

// 生成声明的IR代码
void gen_decl(ASTNode *node)
{
    if (!node)
        return;

    for (int i = 0; i < node->child_count; i++)
    {
        if (strcmp(node->children[i]->name, "ConstDecl") == 0)
        {
            gen_const_decl(node->children[i]);
        }
        else if (strcmp(node->children[i]->name, "VarDecl") == 0)
        {
            gen_var_decl(node->children[i]);
        }
    }
}

// 生成常量声明的IR代码
void gen_const_decl(ASTNode *node)
{
    if (!node)
        return;

    // 遍历所有ConstDef
    for (int i = 0; i < node->child_count; i++)
    {
        if (strcmp(node->children[i]->name, "ConstDef") == 0)
        {
            ASTNode *def = node->children[i];
            char var_name[64] = "";
            Operand init_val = make_const(0);

            for (int j = 0; j < def->child_count; j++)
            {
                if (strcmp(def->children[j]->name, "ID") == 0 ||
                    strcmp(def->children[j]->name, "Ident") == 0)
                {
                    strcpy(var_name, def->children[j]->value);
                }
                else if (strcmp(def->children[j]->name, "ConstInitVal") == 0)
                {
                    if (def->children[j]->child_count > 0)
                    {
                        init_val = gen_exp(def->children[j]->children[0]);
                    }
                }
            }

            if (strlen(var_name) > 0)
            {
                IRCode *code = create_ir_code(IR_ASSIGN);
                code->result = make_var(var_name);
                code->arg1 = init_val;
                append_ir_code(code);
            }
        }
    }
}

// 生成变量声明的IR代码
void gen_var_decl(ASTNode *node)
{
    if (!node)
        return;

    // 遍历所有VarDef
    for (int i = 0; i < node->child_count; i++)
    {
        if (strcmp(node->children[i]->name, "VarDef") == 0 ||
            strcmp(node->children[i]->name, "VarDefList") == 0)
        {
            ASTNode *def = node->children[i];

            // 递归处理VarDefList
            if (strcmp(def->name, "VarDefList") == 0)
            {
                gen_var_decl(def);
                continue;
            }

            char var_name[64] = "";
            bool has_init = false;
            Operand init_val = make_const(0);

            for (int j = 0; j < def->child_count; j++)
            {
                if (strcmp(def->children[j]->name, "ID") == 0 ||
                    strcmp(def->children[j]->name, "Ident") == 0)
                {
                    strcpy(var_name, def->children[j]->value);
                }
                else if (strcmp(def->children[j]->name, "InitVal") == 0)
                {
                    has_init = true;
                    if (def->children[j]->child_count > 0)
                    {
                        init_val = gen_exp(def->children[j]->children[0]);
                    }
                }
            }

            if (strlen(var_name) > 0 && has_init)
            {
                IRCode *code = create_ir_code(IR_ASSIGN);
                code->result = make_var(var_name);
                code->arg1 = init_val;
                append_ir_code(code);
            }
        }
    }
}

// 生成函数定义的IR代码
void gen_func_def(ASTNode *node)
{
    if (!node)
        return;

    // 获取函数名
    char func_name[64] = "";
    for (int i = 0; i < node->child_count; i++)
    {
        if (strcmp(node->children[i]->name, "ID") == 0 ||
            strcmp(node->children[i]->name, "Ident") == 0)
        {
            strcpy(func_name, node->children[i]->value);
            break;
        }
    }

    // 生成函数开始标记
    IRCode *func_begin = create_ir_code(IR_FUNC_BEGIN);
    func_begin->arg1 = make_func(func_name);
    append_ir_code(func_begin);

    // 生成函数体
    for (int i = 0; i < node->child_count; i++)
    {
        if (strcmp(node->children[i]->name, "Block") == 0)
        {
            gen_block(node->children[i]);
        }
    }

    // 生成函数结束标记
    IRCode *func_end = create_ir_code(IR_FUNC_END);
    func_end->arg1 = make_func(func_name);
    append_ir_code(func_end);
}

// 生成编译单元的IR代码
void gen_compunit(ASTNode *node)
{
    if (!node)
        return;

    for (int i = 0; i < node->child_count; i++)
    {
        ASTNode *child = node->children[i];
        if (strcmp(child->name, "Decl") == 0)
        {
            gen_decl(child);
        }
        else if (strcmp(child->name, "FuncDef") == 0)
        {
            gen_func_def(child);
        }
        else if (strcmp(child->name, "CompUnit") == 0 ||
                 strcmp(child->name, "DeclOrFuncDef") == 0 ||
                 strcmp(child->name, "DeclOrFuncDefList") == 0)
        {
            gen_compunit(child);
        }
    }
}

// 主生成函数
void generate_ir(ASTNode *root)
{
    init_irgen();
    gen_compunit(root);
}

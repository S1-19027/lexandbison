# RISC-V 32位汇编代码
    .text

.globl main
main:
    # 函数序言
    addi sp, sp, -128
    sw ra, 124(sp)
    sw s0, 120(sp)
    addi s0, sp, 128
    li t3, 5
    sw t3, -4(s0)
    lw t3, -4(s0)
    lw t3, -4(s0)
    neg t0, t3
    sw t0, -8(s0)
    lw t3, -4(s0)
    sw t3, -8(s0)
    li t3, 0
    li t3, 0
    seqz t1, t3
    bnez t1, L0
    j L1
L0:
    li t3, 1
    sw t3, -8(s0)
L1:
    lw a0, -8(s0)
    j .L_epilogue
.L_epilogue:
    # 函数尾声
    lw ra, 124(sp)
    lw s0, 120(sp)
    addi sp, sp, 128
    ret

# 代码生成完成

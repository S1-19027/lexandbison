# RISC-V 32位汇编代码
    .text

.globl main
main:
    # 函数序言
    addi sp, sp, -128
    sw ra, 124(sp)
    sw s0, 120(sp)
    addi s0, sp, 128
    li t3, 0
    sw t3, -4(s0)
    li t3, 0
    sw t3, -8(s0)
L0:
    lw t3, -4(s0)
    li t4, 5
    slt t0, t3, t4
    bnez t0, L1
    j L2
L1:
    li t3, 0
    sw t3, -12(s0)
L3:
    lw t3, -12(s0)
    li t4, 3
    slt t1, t3, t4
    bnez t1, L4
    j L5
L4:
    lw t3, -4(s0)
    lw t4, -12(s0)
    slt t2, t4, t3
    bnez t2, L6
    j L7
L6:
    lw t3, -8(s0)
    lw t4, -4(s0)
    add t3, t3, t4
    lw t4, -12(s0)
    sub t4, t3, t4
    sw t4, -8(s0)
    j L8
L7:
    lw t3, -8(s0)
    lw t4, -12(s0)
    add t5, t3, t4
    lw t4, -4(s0)
    sub t6, t5, t4
    sw t6, -8(s0)
L8:
    lw t3, -12(s0)
    li t4, 1
    add t0, t3, t4
    sw t0, -12(s0)
    j L3
L5:
    lw t3, -4(s0)
    li t4, 1
    add t0, t3, t4
    sw t0, -4(s0)
    j L0
L2:
    lw a0, -8(s0)
    j .L_epilogue
.L_epilogue:
    # 函数尾声
    lw ra, 124(sp)
    lw s0, 120(sp)
    addi sp, sp, 128
    ret

# 代码生成完成

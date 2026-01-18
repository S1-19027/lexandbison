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
    li t3, 3
    sw t3, -8(s0)
    li t3, 2
    sw t3, -12(s0)
    lw t3, -4(s0)
    lw t4, -8(s0)
    mul t0, t3, t4
    lw t4, -12(s0)
    add t1, t0, t4
    sw t1, -16(s0)
    li t3, 0
    lw t4, -12(s0)
    mul t2, t3, t4
    lw t3, -4(s0)
    lw t4, -8(s0)
    div t3, t3, t4
    sub t4, t2, t3
    sw t4, -16(s0)
    lw t3, -4(s0)
    lw t4, -8(s0)
    rem t5, t3, t4
    sw t5, -16(s0)
    lw a0, -16(s0)
    j .L_epilogue
.L_epilogue:
    # 函数尾声
    lw ra, 124(sp)
    lw s0, 120(sp)
    addi sp, sp, 128
    ret

# 代码生成完成

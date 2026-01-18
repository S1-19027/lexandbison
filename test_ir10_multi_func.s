# RISC-V 32位汇编代码
    .text

.globl multiply
multiply:
    # 函数序言
    addi sp, sp, -128
    sw ra, 124(sp)
    sw s0, 120(sp)
    addi s0, sp, 128
    lw t3, -4(s0)
    lw t4, -8(s0)
    mul t0, t3, t4
    mv a0, t0
    j .L_epilogue
.L_epilogue:
    # 函数尾声
    lw ra, 124(sp)
    lw s0, 120(sp)
    addi sp, sp, 128
    ret

.globl calculate
calculate:
    # 函数序言
    addi sp, sp, -128
    sw ra, 124(sp)
    sw s0, 120(sp)
    addi s0, sp, 128
    lw t3, -4(s0)
    addi sp, sp, -4
    sw t3, 0(sp)
    lw t3, -8(s0)
    addi sp, sp, -4
    sw t3, 0(sp)
    call multiply
    addi sp, sp, 8
    mv t0, a0
    lw t3, -8(s0)
    addi sp, sp, -4
    sw t3, 0(sp)
    lw t3, -4(s0)
    addi sp, sp, -4
    sw t3, 0(sp)
    call multiply
    addi sp, sp, 8
    mv t1, a0
    add t2, t0, t1
    sw t2, -12(s0)
    lw a0, -12(s0)
    j .L_epilogue
.L_epilogue:
    # 函数尾声
    lw ra, 124(sp)
    lw s0, 120(sp)
    addi sp, sp, 128
    ret

.globl main
main:
    # 函数序言
    addi sp, sp, -128
    sw ra, 124(sp)
    sw s0, 120(sp)
    addi s0, sp, 128
    li t3, 3
    sw t3, -4(s0)
    li t3, 4
    sw t3, -8(s0)
    lw t3, -4(s0)
    addi sp, sp, -4
    sw t3, 0(sp)
    lw t3, -8(s0)
    addi sp, sp, -4
    sw t3, 0(sp)
    call calculate
    addi sp, sp, 8
    mv t0, a0
    sw t0, -4(s0)
    lw a0, -4(s0)
    j .L_epilogue
.L_epilogue:
    # 函数尾声
    lw ra, 124(sp)
    lw s0, 120(sp)
    addi sp, sp, 128
    ret

# 代码生成完成

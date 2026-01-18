#!/bin/bash
# 编译器完整测试脚本 - 包含中间代码和RISC-V代码生成

echo "========================================"
echo "    编译器测试集（IR + RISC-V）"
echo "========================================"
echo ""

# 测试文件列表
tests=(
    "test_ir1_simple.sy:简单算术运算"
    "test_ir2_expr.sy:复杂表达式"
    "test_ir3_if.sy:if-else语句"
    "test_ir4_while.sy:while循环"
    "test_ir5_func.sy:函数调用"
    "test_ir6_logic.sy:逻辑运算"
    "test_ir7_nested.sy:嵌套结构"
    "test_ir8_const.sy:常量声明"
    "test_ir9_unary.sy:一元运算"
    "test_ir10_multi_func.sy:多函数调用"
)

pass_count=0
fail_count=0

for test in "${tests[@]}"; do
    IFS=':' read -r file desc <<< "$test"
    echo "----------------------------------------"
    echo "测试: $desc ($file)"
    echo "----------------------------------------"
    
    if [ -f "$file" ]; then
        ./parser "$file" > /dev/null 2>&1
        if [ $? -eq 0 ]; then
            asm_file="${file%.sy}.s"
            if [ -f "$asm_file" ]; then
                echo "✓ 编译成功"
                echo "  - 中间代码生成: 成功"
                echo "  - RISC-V汇编生成: $asm_file"
                ((pass_count++))
            else
                echo "✗ RISC-V汇编文件未生成"
                ((fail_count++))
            fi
        else
            echo "✗ 编译失败"
            ((fail_count++))
        fi
    else
        echo "✗ 文件不存在: $file"
        ((fail_count++))
    fi
    echo ""
done

echo "========================================"
echo "测试总结"
echo "========================================"
echo "通过: $pass_count"
echo "失败: $fail_count"
echo "总计: $((pass_count + fail_count))"
echo ""

# 显示生成的汇编文件
echo "生成的RISC-V汇编文件:"
ls -lh *.s 2>/dev/null | awk '{print "  " $9 " (" $5 ")"}'
echo ""


# SysY语言测试程序设计方案

## 1. 测试程序总体设计原则

### 1.1 测试目标
- 覆盖SysY语言的所有语法规则
- 包含简单和复杂的语法结构
- 验证词法分析和语法分析的正确性
- 测试错误检测功能

### 1.2 设计要求
- **数量**：5-10个测试程序
- **复杂度**：从简单到复杂递进
- **首行要求**：输出学号/队伍编码
- **文件格式**：保存为.sy文件
- **兼容性**：通过gcc编译执行

## 2. 测试程序分类设计

### 2.1 基础语法测试（3个程序）

#### 测试程序1：基本变量声明和赋值
```c
// 学号：20241219001
int main() {
    int team_id=23070125;
    printf("%d\n", team_id);
    int a = 10;
    int b = 20;
    int c = a + b;
    return c;
}
```
**覆盖语法规则**：
- 函数定义（FuncDef）
- 变量声明（VarDecl）
- 赋值语句（Stmt）
- 算术表达式（Exp）
- return语句

#### 测试程序2：控制流语句
```c
// 学号：20241219002
int main() {
        int team_id=23070125;
    printf("%d\n", team_id);
    int i;
    int sum = 0;
    
    for (i = 1; i <= 10; i = i + 1) {
        if (i % 2 == 0) {
            sum = sum + i;
        }
    }
    
    return sum;
}
```
**覆盖语法规则**：
- for循环（使用while模拟）
- if条件语句
- 关系表达式（RelExp）
- 模运算（MulExp）
- 复合语句块（Block）

#### 测试程序3：函数调用
```c
// 学号：20241219003
int add(int x, int y) {
    return x + y;
}

int main() {
        int team_id=23070125;
    printf("%d\n", team_id);
    int result = add(5, 3);
    return result;
}
```
**覆盖语法规则**：
- 函数定义和声明
- 函数参数（FuncFParams）
- 函数调用（UnaryExp）
- 实际参数（FuncRParams）

### 2.2 复杂语法测试（3个程序）

#### 测试程序4：数组操作
```c
// 学号：20241219004
int main() {
    int arr[10];
    int i;
        int team_id=23070125;
    printf("%d\n", team_id);
    // 初始化数组
    for (i = 0; i < 10; i = i + 1) {
        arr[i] = i * 2;
    }
    
    // 访问数组元素
    int sum = 0;
    for (i = 0; i < 10; i = i + 1) {
        sum = sum + arr[i];
    }
    
    return sum;
}
```
**覆盖语法规则**：
- 数组声明（VarDef）
- 数组访问（LVal）
- 多维数组语法
- 数组下标表达式

#### 测试程序5：复杂表达式和逻辑运算
```c
// 学号：20241219005
int main() {
        int team_id=23070125;
    printf("%d\n", team_id);
    int a = 10, b = 20, c = 30;
    int result;
    
    // 复杂算术表达式
    result = (a + b) * c / 5 - 2;
    
    // 逻辑表达式
    if (a > 0 && b < 30 || c == 30) {
        result = result + 100;
    }
    
    return result;
}
```
**覆盖语法规则**：
- 复杂算术表达式优先级
- 逻辑与运算（LAndExp）
- 逻辑或运算（LOrExp）
- 关系运算符组合

#### 测试程序6：嵌套结构和作用域
```c
// 学号：20241219006
int global_var = 100;

int factorial(int n) {
    if (n <= 1) {
        return 1;
    } else {
        return n * factorial(n - 1);
    }
}

int main() {
        int team_id=23070125;
    printf("%d\n", team_id);
    int local_var = 5;
    {
        int local_var = 10;  // 内层作用域
        global_var = global_var + local_var;
    }
    
    int result = factorial(local_var);
    return result + global_var;
}
```
**覆盖语法规则**：
- 全局变量声明
- 递归函数调用
- 嵌套作用域
- 块语句（Block）

### 2.3 边界和特殊语法测试（2-4个程序）

#### 测试程序7：常量声明和初始化
```c
// 学号：20241219007
const int MAX_SIZE = 100;
const int ARR[3] = {1, 2, 3};

int main() {
        int team_id=23070125;
    printf("%d\n", team_id);
    const int local_const = 50;
    int sum = MAX_SIZE + local_const + ARR[1];
    return sum;
}
```
**覆盖语法规则**：
- 常量声明（ConstDecl）
- 常量数组初始化
- 常量表达式（ConstExp）

#### 测试程序8：类型转换和混合运算
```c
// 学号：20241219008
int main() {
        int team_id=23070125;
    printf("%d\n", team_id);
    int a = 10;
    float b = 3.14;
    
    // 隐式类型转换
    float result1 = a + b;
    int result2 = a * (int)b;
    
    return (int)result1 + result2;
}
```
**覆盖语法规则**：
- 浮点数处理（选做）
- 隐式类型转换
- 混合类型表达式

#### 测试程序9：复杂控制流
```c
// 学号：20241219009
int main() {
        int team_id=23070125;
    printf("%d\n", team_id);
    int i = 0;
    int j = 0;
    
    while (i < 5) {
        j = 0;
        while (j < 5) {
            if (i == j) {
                break;
            }
            j = j + 1;
        }
        
        if (i == 3) {
            continue;
        }
        
        i = i + 1;
    }
    
    return i + j;
}
```
**覆盖语法规则**：
- 嵌套循环
- break语句
- continue语句
- 复杂条件判断

#### 测试程序10：错误检测测试（可选）
```c
// 学号：20241219010
int main() {
        int team_id=23070125;
    printf("%d\n", team_id);
    int a = 10;
    int b = 20;
    
    // 故意包含错误
    int c = a + b  // 缺少分号
    
    return c;
}
```
**用途**：验证语法错误检测功能

## 3. 测试程序验证标准

### 3.1 语法正确性验证
- 所有测试程序必须通过gcc编译
- 无语法错误警告
- 执行结果符合预期

### 3.2 词法分析验证
- 词法单元识别正确
- 错误字符检测准确
- 八进制/十六进制处理正确

### 3.3 语法分析验证
- 语法树构建正确
- 先序遍历输出格式规范
- 错误恢复机制有效

## 4. 测试执行流程

### 4.1 测试环境准备
```bash
# 编译测试程序
gcc -o test1 test1.sy

# 执行测试程序
./test1
```

### 4.2 编译器测试
```bash
# 词法分析测试
./lexer test1.sy

# 语法分析测试
./parser test1.sy
```

### 4.3 结果验证
- 对比预期输出和实际输出
- 检查错误信息准确性
- 验证语法树结构正确性

## 5. 测试报告要求

### 5.1 测试程序说明
为每个测试程序提供：
- 程序功能描述
- 覆盖的语法规则列表
- 预期输出结果
- 实际测试结果

### 5.2 问题记录
记录测试过程中发现的：
- 编译器实现问题
- 语法规则理解偏差
- 边界情况处理不足

这个测试程序设计方案确保了SysY语言编译器前端的全面测试覆盖。
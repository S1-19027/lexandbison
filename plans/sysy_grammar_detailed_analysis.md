# SysY语言文法分析

# 文法定义

SysY 语言的文法采用扩展的 Backus 范式 (EBNF, Extended Backus-Naur Form) 表示, 其中:

- 符号 `[...]` 表示方括号内包含的项可被重复 0 次或 1 次.
- 符号 `{...}` 表示花括号内包含的项可被重复 0 次或多次.
- 终结符是由双引号括起的串, 或者是 `IDENT`, `INT_CONST` 这样的大写记号. 其余均为非终结符.

SysY 语言的文法表示如下, `CompUnit` 为开始符号:

```ebnf
CompUnit      ::= [CompUnit] (Decl | FuncDef);

Decl          ::= ConstDecl | VarDecl;
ConstDecl     ::= "const" BType ConstDef {"," ConstDef} ";";
BType         ::= "int";
ConstDef      ::= IDENT {"[" ConstExp "]"} "=" ConstInitVal;
ConstInitVal  ::= ConstExp | "{" [ConstInitVal {"," ConstInitVal}] "}";
VarDecl       ::= BType VarDef {"," VarDef} ";";
VarDef        ::= IDENT {"[" ConstExp "]"}
                | IDENT {"[" ConstExp "]"} "=" InitVal;
InitVal       ::= Exp | "{" [InitVal {"," InitVal}] "}";

FuncDef       ::= FuncType IDENT "(" [FuncFParams] ")" Block;
FuncType      ::= "void" | "int";
FuncFParams   ::= FuncFParam {"," FuncFParam};
FuncFParam    ::= BType IDENT ["[" "]" {"[" ConstExp "]"}];

Block         ::= "{" {BlockItem} "}";
BlockItem     ::= Decl | Stmt;
Stmt          ::= LVal "=" Exp ";"
                | [Exp] ";"
                | Block
                | "if" "(" Exp ")" Stmt ["else" Stmt]
                | "while" "(" Exp ")" Stmt
                | "break" ";"
                | "continue" ";"
                | "return" [Exp] ";";

Exp           ::= LOrExp;
LVal          ::= IDENT {"[" Exp "]"};
PrimaryExp    ::= "(" Exp ")" | LVal | Number;
Number        ::= INT_CONST;
UnaryExp      ::= PrimaryExp | IDENT "(" [FuncRParams] ")" | UnaryOp UnaryExp;
UnaryOp       ::= "+" | "-" | "!";
FuncRParams   ::= Exp {"," Exp};
MulExp        ::= UnaryExp | MulExp ("*" | "/" | "%") UnaryExp;
AddExp        ::= MulExp | AddExp ("+" | "-") MulExp;
RelExp        ::= AddExp | RelExp ("<" | ">" | "<=" | ">=") AddExp;
EqExp         ::= RelExp | EqExp ("==" | "!=") RelExp;
LAndExp       ::= EqExp | LAndExp "&&" EqExp;
LOrExp        ::= LAndExp | LOrExp "||" LAndExp;
ConstExp      ::= Exp;
```

其中, 各符号的含义如下:

| 符号        | 含义         | 符号         | 含义         |
| :---------- | :----------- | :----------- | :----------- |
| CompUnit    | 编译单元     | Decl         | 声明         |
| ConstDecl   | 常量声明     | BType        | 基本类型     |
| ConstDef    | 常数定义     | ConstInitVal | 常量初值     |
| VarDecl     | 变量声明     | VarDef       | 变量定义     |
| InitVal     | 变量初值     | FuncDef      | 函数定义     |
| FuncType    | 函数类型     | FuncFParams  | 函数形参表   |
| FuncFParam  | 函数形参     | Block        | 语句块       |
| BlockItem   | 语句块项     | Stmt         | 语句         |
| Exp         | 表达式       | LVal         | 左值表达式   |
| PrimaryExp  | 基本表达式   | Number       | 数值         |
| UnaryExp    | 一元表达式   | UnaryOp      | 单目运算符   |
| FuncRParams | 函数实参表   | MulExp       | 乘除模表达式 |
| AddExp      | 加减表达式   | RelExp       | 关系表达式   |
| EqExp       | 相等性表达式 | LAndExp      | 逻辑与表达式 |
| LOrExp      | 逻辑或表达式 | ConstExp     | 常量表达式   |

需要注意的是:

- `Exp`: SysY 中表达式的类型均为 `int` 型. 当 `Exp` 出现在表示条件判断的位置时 (例如 `if` 和 `while`), 表达式值为 0 时为假, 非 0 时为真.
- `ConstExp`: 其中使用的 `IDENT` 必须是常量.

# 语义约束

## 1. 编译单元 (CompUnit)

### 文法规则
```
CompUnit → [ CompUnit ] ( Decl | FuncDef )
```

### 作用
- **功能目的**：定义整个SysY程序的结构，是文法的开始符号
- **在语言中的角色**：表示一个完整的源代码文件

### 限定条件
- 必须包含且仅包含一个名为`main`、无参数、返回类型为`int`的函数定义
- 顶层声明（变量/常量/函数）不能重复定义同名标识符
- 作用域从声明处开始到文件结尾

### 组合情况
- 可以由零个或多个声明（Decl）和函数定义（FuncDef）组成
- 声明和函数定义可以任意顺序出现
- 支持递归定义，允许多个编译单元的组合

### 示例句子
```c
int global_var = 10;

int main() {
    return global_var;
}
```

## 2. 声明 (Decl)

### 文法规则
```
Decl → ConstDecl | VarDecl
```

### 作用
- **功能目的**：定义程序中的常量或变量声明
- **在语言中的角色**：引入新的标识符到当前作用域

### 限定条件
- 常量声明必须使用`const`关键字
- 变量声明可以带或不带初始化表达式
- 全局声明中的初值必须是常量表达式

### 组合情况
- 可以出现在编译单元顶层或语句块内部
- 常量声明和变量声明可以混合出现

### 示例句子
```c
const int MAX_SIZE = 100;  // ConstDecl
int count = 0;            // VarDecl
```

## 3. 常量声明 (ConstDecl)

### 文法规则
```
ConstDecl → 'const' BType ConstDef { ',' ConstDef } ';'
```

### 作用
- **功能目的**：定义不可修改的符号常量
- **在语言中的角色**：提供编译时常量值

### 限定条件
- 必须以`const`关键字开头
- 常量定义必须包含初始化表达式
- 数组维度长度必须是常量表达式

### 组合情况
- 支持单个或多个常量定义
- 可以定义标量常量或数组常量

### 示例句子
```c
const int SIZE = 10, COUNT = 5;
const int ARR[3] = {1, 2, 3};
```

## 4. 变量声明 (VarDecl)

### 文法规则
```
VarDecl → BType VarDef { ',' VarDef } ';'
```

### 作用
- **功能目的**：定义可修改的变量
- **在语言中的角色**：存储程序运行时的数据

### 限定条件
- 可以带或不带初始化表达式
- 局部变量未初始化时值不确定
- 全局变量未初始化时初始化为0

### 组合情况
- 支持单个或多个变量定义
- 可以定义标量变量或数组变量

### 示例句子
```c
int a, b = 10;
float arr[5];
```

## 5. 函数定义 (FuncDef)

### 文法规则
```
FuncDef → FuncType Ident '(' [FuncFParams] ')' Block
```

### 作用
- **功能目的**：定义可重用的代码块
- **在语言中的角色**：封装逻辑和实现模块化

### 限定条件
- 必须包含函数体（Block）
- 返回类型为`int`/`float`的函数必须有return语句
- 返回类型为`void`的函数不能有返回值的return语句

### 组合情况
- 可以带参数或不带参数
- 参数可以是基本类型或数组类型
- 函数体包含声明和语句

### 示例句子
```c
int add(int x, int y) {
    return x + y;
}
```

## 6. 语句块 (Block)

### 文法规则
```
Block → '{' { BlockItem } '}'
BlockItem -> Decl | Stmt;
```

### 作用
- **功能目的**：创建新的作用域
- **在语言中的角色**：组织相关语句和声明

### 限定条件
- 会创建新的作用域
- 内部声明的变量生存期在块内
- 可以隐藏外部同名变量

### 组合情况
- 可以包含零个或多个块项
- 块项可以是声明或语句

### 示例句子
```c
{
    int local_var = 10;
    local_var = local_var + 1;
}
```

## 7. 语句 (Stmt)

### 文法规则
```
Stmt → LVal '=' Exp ';' | [Exp] ';' | Block
     | 'if' '(' Cond ')' Stmt [ 'else' Stmt ]
     | 'while' '(' Cond ')' Stmt
     | 'break' ';' | 'continue' ';'
     | 'return' [Exp] ';'
```

### 作用
- **功能目的**：执行操作和控制程序流程
- **在语言中的角色**：实现算法逻辑

### 限定条件
- 赋值语句的左值必须是变量
- break/continue必须在循环体内
- return类型必须与函数返回类型匹配

### 组合情况
- 支持多种控制结构
- 可以嵌套使用

### 示例句子
```c
x = x + 1;           // 赋值语句
if (x > 0) x = 0;    // 条件语句
while (x < 10) x++;  // 循环语句
```

## 8. 表达式体系分析

### 8.1 表达式层次结构
```
Exp → AddExp
AddExp → MulExp | AddExp ('+' | '−') MulExp
MulExp → UnaryExp | MulExp ('*' | '/' | '%') UnaryExp
UnaryExp → PrimaryExp | Ident '(' [FuncRParams] ')' | UnaryOp UnaryExp
PrimaryExp → '(' Exp ')' | LVal | Number
```

### 8.2 运算符优先级（从高到低）
1. **括号**：`( )`
2. **函数调用**：`Ident( )`
3. **单目运算符**：`+`, `-`, `!`
4. **乘除模**：`*`, `/`, `%`
5. **加减**：`+`, `-`
6. **关系运算**：`<`, `>`, `<=`, `>=`
7. **相等性**：`==`, `!=`
8. **逻辑与**：`&&`
9. **逻辑或**：`||`

### 8.3 特殊表达式规则

#### 条件表达式 (Cond)
```
Cond → LOrExp
```
- **特殊限制**：允许使用`!`运算符
- **用途**：作为if/while的条件

#### 常量表达式 (ConstExp)
```
ConstExp → AddExp
```
- **特殊限制**：只能使用常量标识符
- **用途**：数组维度、常量初始化

## 9. 左值表达式 (LVal)

### 文法规则

```
LVal → Ident {'[' Exp ']'}
```

### 作用

- **功能目的**：表示可以出现在赋值语句左边的表达式
- **在语言中的角色**：标识可以被修改的存储位置

### 限定条件

1. **基本要求**：必须是变量或数组元素
2. **数组访问**：方括号个数必须与数组维数相同
3. **变量访问**：单个变量不能有方括号
4. **函数参数特例**：作为数组参数时方括号个数可以不匹配

## 10. 函数形参 (FuncFParam)

### 文法规则

```
FuncFParam → BType Ident ['[' ']' { '[' ConstExp ']' }]
```

### 作用

- **功能目的**：定义函数的形式参数
- **在语言中的角色**：指定函数调用时传递的数据接口

### 限定条件

1. **基本类型参数**：Ident后没有方括号部分
2. **数组类型参数**：Ident后有方括号部分
3. **第一维省略**：数组参数的第一维长度可以省略
4. **后续维固定**：数组参数的后续维长度必须指定



## 11. 函数实参 (FuncRParams)

### 文法规则

```
FuncRParams → Exp { ',' Exp }
```

### 作用

- **功能目的**：提供函数调用时的实际参数
- **在语言中的角色**：向函数传递具体的数据值

### 限定条件

1. **参数个数**：必须与形参个数完全匹配
2. **参数类型**：必须与形参类型完全匹配
3. **表达式求值**：在函数调用前完成求值



## 12. 常量定义 (ConstDef)

### 文法规则

```
ConstDef → Ident { '[' ConstExp ']' } '=' ConstInitVal
```

### 作用

- **功能目的**：定义在编译时就能确定值的不可修改符号
- **在语言中的角色**：提供编译时常量，类似于C++的consteval或Rust的const

### 限定条件

1. **标识符要求**：Ident必须是有效的标识符
2. **数组维度**：各维长度必须是ConstExp（常量表达式）
3. **初始化要求**：必须提供ConstInitVal（常量初值）
4. **编译时求值**：所有表达式必须在编译时能计算出确定值





##  13. 变量定义 (VarDef)

### 文法规则

```
VarDef → Ident { '[' ConstExp ']' }
        | Ident { '[' ConstExp ']' } '=' InitVal
```

### 作用

- **功能目的**：定义运行时可以修改的存储单元
- **在语言中的角色**：存储程序执行过程中的数据

### 限定条件

1. **数组维度**：各维长度必须是ConstExp
2. **初始化可选**：可以带或不带初始化表达式
3. **初值类型**：InitVal可以是运行时表达式



## 14. 初值 (ConstInitVal/InitVal)

### 文法规则

```
ConstInitVal → ConstExp | '{' [ ConstInitVal { ',' ConstInitVal } ] '}'
InitVal → Exp | '{' [ InitVal { ',' InitVal } ] '}'
```

### 作用

- **功能目的**：为常量或变量提供初始值
- **在语言中的角色**：确定存储单元的初始状态

### 语义约束详细分析

#### 类型一致性约束

- **常量初值**：必须与常量类型一致
- **变量初值**：必须与变量类型一致
- **数组元素**：初值类型必须与数组元素类型一致

#### 初始化列表约束

- **元素个数**：不能超过数组总元素个数
- **值范围**：不能超出数据类型的表示范围
- **浮点数组**：允许整型常量作为初值

## 15. 语义约束总结

### 15.1 作用域规则
- **全局作用域**：从声明处到文件结尾
- **局部作用域**：块内声明，生存期在块内
- **重叠规则**：局部变量隐藏全局同名变量

### 15.2 类型系统
- **基本类型**：int, float, void
- **数组类型**：按行优先存储的多维数组
- **类型转换**：支持int和float间的隐式转换

### 15.3 函数规则
- **定义要求**：每个函数只定义一次
- **参数传递**：基本类型按值，数组类型按地址
- **返回要求**：非void函数必须有return语句

### 15.4 数组规则
- **维度要求**：各维长度必须显式给出
- **访问要求**：下标个数必须与维数相同
- **初始化**：支持多种初始化形式

# 求值顺序

在 SysY 中, 可能出现如下三种求值顺序影响运行结果的例子 

类型 1, 表达式操作数/函数参数的求值顺序影响结果:

```c
int f(int x) {
  putint(x);
  return x;
}

void g(int x, int y) {}

int main() {
  g(f(1), f(2));      // 可能输出 12 或 21
  return f(3) + f(4); // 可能输出 34 或 43
}
```

类型 2, 数组下标的求值顺序影响结果:

```c
int i = 0, a[10][10];

int g() {
  i = i + 1;
  return i;
}

int main() {
  a[i][g()] = 2;
  putint(a[0][1]);
  putint(a[1][1]);
  return 0;         // 可能输出 02 或 20
}
```

类型 3, 赋值运算符的左右操作数求值顺序影响结果:

```c
int i = 0, a[10];

int g() {
  i = i + 1;
  return i;
}

int main() {
  a[i] = g();
  putint(a[0]);
  putint(a[1]);
  return 0;     // 可能输出 01 或 10
}
```
# SysY语言词法分析器详细设计

## 1. 词法单元类型定义

### 1.1 关键字（Keywords）
```
INTTK     - "int"
FLOATTK   - "float" (选做)
VOIDTK    - "void"
CONSTTK   - "const"
IFTK      - "if"
ELSETK    - "else"
WHILETK   - "while"
BREAKTK   - "break"
CONTINUETK - "continue"
RETURNTK  - "return"
```

### 1.2 标识符（Identifiers）
```
ID - 符合C语言标识符规范的名称
```

### 1.3 常数（Constants）
```
INTCON    - 整型常数（十进制、八进制、十六进制）
FLOATCON  - 浮点型常数（选做）
```

### 1.4 运算符（Operators）
```
PLUS      - "+"
MINUS     - "-"
MUL       - "*"
DIV       - "/"
MOD       - "%"
ASSIGN    - "="
EQ        - "=="
NEQ       - "!="
LT        - "<"
GT        - ">"
LEQ       - "<="
GEQ       - ">="
AND       - "&&"
OR        - "||"
NOT       - "!"
```

### 1.5 分隔符（Delimiters）
```
LPARENT   - "("
RPARENT   - ")"
LBRACKET  - "["
RBRACKET  - "]"
LBRACE    - "{"
RBRACE    - "}"
SEMICN    - ";"
COMMA     - ","
```

## 2. 正则表达式设计

### 2.1 基础模式定义
```
DIGIT     [0-9]
NONZERO   [1-9]
LETTER    [a-zA-Z_]
OCTAL     [0-7]
HEX       [0-9a-fA-F]
WHITESPACE [ \t\r\n]
```

### 2.2 具体词法规则

#### 标识符
```
{LETTER}({LETTER}|{DIGIT})*
```

#### 整型常数
```
十进制: {NONZERO}{DIGIT}* | "0"
八进制: "0"{OCTAL}+
十六进制: "0"[xX]{HEX}+
```

#### 浮点型常数（选做）
```
{DIGIT}+"."{DIGIT}*([eE][+-]?{DIGIT}+)?
{DIGIT}*"."{DIGIT}+([eE][+-]?{DIGIT}+)?
{DIGIT}+[eE][+-]?{DIGIT}+
```

#### 运算符和分隔符
```
"+" | "-" | "*" | "/" | "%" | "=" | "==" | "!=" | "<" | ">" | "<=" | ">=" | "&&" | "||" | "!"
"(" | ")" | "[" | "]" | "{" | "}" | ";" | ","
```

#### 注释处理
```
单行注释: "//".*\n
多行注释: "/*"(.|\n)*?"*/"
```

## 3. Flex源代码结构设计

### 3.1 定义部分（Definitions）


### 3.2 规则部分（Rules）

#### 关键字匹配


#### 标识符和常数

#### 运算符和分隔符


#### 错误处理


### 3.3 用户自定义代码部分


## 4. 错误检测策略

### 4.1 词法错误类型（错误类型A）
1. **未定义字符**：匹配任何不在规则中的字符
2. **非法八进制数**：以0开头但包含8或9的数字
3. **非法十六进制数**：以0x开头但包含非十六进制字符

### 4.2 错误恢复
- 跳过错误字符，继续分析后续内容
- 确保同一行最多只报告一个错误
- 提供清晰的错误信息，包括错误类型和行号

## 5. 输出格式规范

### 5.1 正常输出（无错误）
```

INTTK int
ID inc
LPARENT (
RPARENT )
LBRACE {
INTTK int
ID i
SEMICN ;
ID i
ASSIGN =
ID i
PLUS +
INTCON 1
SEMICN ;
RBRACE }

```

### 5.2 错误输出
```
Error type A at Line [行号]: [说明文字]
例如：
Error type A at Line 4: Invalid character "~"
```

## 6. 测试策略

### 6.1 测试用例设计
- 简单程序：基本语法结构
- 复杂程序：嵌套结构、数组、函数调用
- 错误程序：包含各种词法错误
- 边界情况：最大/最小整数、特殊字符

### 6.2 验证方法
- 手动检查输出格式
- 与预期结果对比
- 使用gcc验证测试程序的语法正确性

这个设计文档为词法分析器的实现提供了详细的技术规范和实现指导。
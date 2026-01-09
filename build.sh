#!/bin/bash

set -e  # 出错立即退出

echo "Running bison..."
bison -d parser.y

echo "Running flex..."
flex lexer.l

echo "Compiling..."
gcc -g -o parser \
    parser.tab.c \
    lex.yy.c \
    semantic.c \
    -lfl

echo "Done! Generated ./parser"


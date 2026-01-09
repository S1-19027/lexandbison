%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "ast.h"
#include "parser.tab.h"
#define MAX_ERRORS 100

//语法树结构

//全局变量
extern FILE *yyin;
extern int yylineno;
extern Error error_list[];
extern int error_count;
int has_error = 0;
SyntaxError syntax_error_list[MAX_ERRORS];  // 语法错误数组
int syntax_error_count = 0;                  // 语法错误计数器
ASTNode* root = NULL;
//函数声明
ASTNode* create_ast_node(NodeType type, const char* name, int line);
ASTNode* create_token_node(int token_type, const char* name, const char* value) ;
void add_child(ASTNode* parent, ASTNode* child);
void print_ast(ASTNode* node, int depth);
void yyerror(const char* s);
int yylex(void);

%}

//Bison声明部分
%union {
    ASTNode* node;
    char* str;
    int intval;
}

//终结符声明
%token <str> INTTK FLOATTK VOIDTK CONSTTK IFTK ELSETK WHILETK BREAKTK CONTINUETK RETURNTK
%token <str> ID 
%token <intval> INTCON 
%token <str> PLUS MINUS MUL DIV MOD ASSIGN EQ NEQ LT GT LEQ GEQ AND OR NOT
%token <str> LPARENT RPARENT LBRACKET RBRACKET LBRACE RBRACE SEMICN COMMA 
%token ENDFILE

//非终结符声明
%type <node> CompUnit Decl ConstDecl BType ConstDef ConstInitVal VarDecl VarDef InitVal
%type <node> FuncDef FuncType FuncFParams FuncFParam Block BlockItem Stmt Exp Cond LVal
%type <node> PrimaryExp Number UnaryExp UnaryOp FuncRParams MulExp AddExp FuncFParamDims DeclOrFuncDef DeclOrFuncDefList FuncFParamsOpt FuncRParamsOpt
%type <node> RelExp EqExp LAndExp LOrExp ConstExp BlockItem_list
%start CompUnit

%left LPARENT RPARENT
%left LBRACE RBRACE
%left SEMICN COMMA
%left ASSIGN
%left OR
%left AND
%left EQ NEQ
%left LT GT LEQ GEQ
%left PLUS MINUS
%left MUL DIV MOD
%left NOT
%left LBRACKET RBRACKET


%%

//文法规则定义
CompUnit
    : DeclOrFuncDefList {
        root = $1;
    }
    ;

DeclOrFuncDefList
    : DeclOrFuncDef {
        $$ = create_ast_node(Node_CompUnit, "CompUnit", yylineno);
        add_child($$, $1);
    }
    | DeclOrFuncDefList DeclOrFuncDef {
        $$ = $1;
        add_child($$, $2);
    }
    ;


DeclOrFuncDef
    : VOIDTK ID LPARENT FuncFParamsOpt RPARENT Block {
        $$ = create_ast_node(Node_FuncDef, "FuncDef", yylineno);
        add_child($$, create_token_node(VOIDTK, "VOIDTK", $1));
        add_child($$, create_token_node(ID, "ID", $2));
        add_child($$, create_token_node(LPARENT, "LPARENT", $3));
         if ($4) add_child($$, $4);
        add_child($$, create_token_node(RPARENT, "RPARENT", $5));
        add_child($$, $6);
    }
    | INTTK ID LPARENT FuncFParamsOpt RPARENT Block {
        $$ = create_ast_node(Node_FuncDef, "FuncDef", yylineno);
        add_child($$, create_token_node(INTTK, "INTTK", $1));
        add_child($$, create_token_node(ID, "ID", $2));
        add_child($$, create_token_node(LPARENT, "LPARENT", $3));
         if ($4) add_child($$, $4);
        add_child($$, create_token_node(RPARENT, "RPARENT", $5));
        add_child($$, $6);
    }
    | FLOATTK ID LPARENT FuncFParamsOpt RPARENT Block {
        $$ = create_ast_node(Node_FuncDef, "FuncDef", yylineno);
        add_child($$, create_token_node(FLOATTK, "FLOATTK", $1));
        add_child($$, create_token_node(ID, "ID", $2));
        add_child($$, create_token_node(LPARENT, "LPARENT", $3));
         if ($4) add_child($$, $4);
        add_child($$, create_token_node(RPARENT, "RPARENT", $5));
        add_child($$, $6);
    }
    | Decl { $$ = $1; }
    ;

Decl:
    ConstDecl {
        $$ = create_ast_node(Node_Decl, "Decl", yylineno);
        add_child($$, $1);
    }
    | VarDecl {
        $$ = create_ast_node(Node_Decl, "Decl", yylineno);
        add_child($$, $1);
    }
    ;

ConstDecl:
    CONSTTK BType ConstDef SEMICN {
        $$ = create_ast_node(Node_ConstDecl, "ConstDecl", yylineno);
        add_child($$, create_token_node(CONSTTK, "CONSTTK", $1));
        add_child($$, $2);
        add_child($$, $3);
        add_child($$, create_token_node(SEMICN, "SEMICN", $4));
    }
    ;

BType:
    INTTK {
        $$ = create_ast_node(Node_BType, "BType", yylineno);
        add_child($$, create_token_node(INTTK, "INTTK", $1));
    }
    | FLOATTK {
        $$ = create_ast_node(Node_BType, "BType", yylineno);
        add_child($$, create_token_node(FLOATTK, "FLOATTK", $1));
    }
    ;

ConstDef:
    ID ASSIGN ConstInitVal {
        $$ = create_ast_node(Node_ConstDef, "ConstDef", yylineno);
        add_child($$, create_token_node(ID, "ID", $1));
        add_child($$, create_token_node(ASSIGN, "ASSIGN", $2));
        add_child($$, $3);
    }
    ;

ConstInitVal:
    ConstExp {
        $$ = create_ast_node(Node_ConstInitVal, "ConstInitVal", yylineno);
        add_child($$, $1);
    }
    ;

VarDecl:
    BType VarDef SEMICN {
        $$ = create_ast_node(Node_VarDecl, "VarDecl", yylineno);
        add_child($$, $1);
        add_child($$, $2);
        add_child($$, create_token_node(SEMICN, "SEMICN", $3));
    }
    ;

VarDef:
    ID {
        $$ = create_ast_node(Node_VarDef, "VarDef", yylineno);
        add_child($$, create_token_node(ID, "ID", $1));
    }
    | ID LBRACKET ConstExp RBRACKET {
        $$ = create_ast_node(Node_VarDef, "VarDef", yylineno);
        add_child($$, create_token_node(ID, "ID", $1));
        add_child($$, create_token_node(LBRACKET, "LBRACKET", $2));
        add_child($$, $3);
        add_child($$, create_token_node(RBRACKET, "RBRACKET", $4));
    }
    | ID LBRACKET ConstExp RBRACKET LBRACKET ConstExp RBRACKET {
        $$ = create_ast_node(Node_VarDef, "VarDef", yylineno);
        add_child($$, create_token_node(ID, "ID", $1));
        add_child($$, create_token_node(LBRACKET, "LBRACKET", $2));
        add_child($$, $3);
        add_child($$, create_token_node(RBRACKET, "RBRACKET", $4));
        add_child($$, create_token_node(LBRACKET, "LBRACKET", $5));
        add_child($$, $6);
        add_child($$, create_token_node(RBRACKET, "RBRACKET", $7));
    }
    | ID ASSIGN InitVal {
        $$ = create_ast_node(Node_VarDef, "VarDef", yylineno);
        add_child($$, create_token_node(ID, "ID", $1));
        add_child($$, create_token_node(ASSIGN, "ASSIGN", $2));
        add_child($$, $3);
    }
    ;

InitVal:
    Exp {
        $$ = create_ast_node(Node_InitVal, "InitVal", yylineno);
        add_child($$, $1);
    }
    ;
FuncFParamsOpt
    : /* empty */{
        $$ = NULL;
    }
    | FuncFParams {$$ = $1;}
    ;


FuncType:
    VOIDTK {
        $$ = create_ast_node(Node_FuncType, "FuncType", yylineno);
        add_child($$, create_token_node(VOIDTK, "VOIDTK", $1));
    }
    | INTTK {
        $$ = create_ast_node(Node_FuncType, "FuncType", yylineno);
        add_child($$, create_token_node(INTTK, "INTTK", $1));
    }
    | FLOATTK {
        $$ = create_ast_node(Node_FuncType, "FuncType", yylineno);
        add_child($$, create_token_node(FLOATTK, "FLOATTK", $1));
    }
    ;
FuncFParams:
    FuncFParam {
        $$ = create_ast_node(Node_FuncFParams, "FuncFParams", yylineno);
        add_child($$, $1);
    }
  | FuncFParams COMMA FuncFParam {
        $$ = $1;
        add_child($$, $3);
    }
;


FuncRParamsOpt
    : /* empty */{
        $$ = NULL;
    }
    | FuncRParams {$$ = $1;}
    ;

FuncRParams:
    Exp {
        $$ = create_ast_node(Node_FuncRParams, "FuncRParams", yylineno);
        add_child($$, $1);
    }
  | FuncRParams COMMA Exp {
        $$ = $1;
        add_child($$, $3);
    }
;

FuncFParam:
    BType ID {
        $$ = create_ast_node(Node_FuncFParam, "FuncFParam", yylineno);
        add_child($$, $1);
        add_child($$, create_token_node(ID, "Ident", $2));
    }
  | BType ID LBRACKET RBRACKET FuncFParamDims {
        $$ = create_ast_node(Node_FuncFParam, "FuncFParam", yylineno);
        add_child($$, $1);
        add_child($$, create_token_node(ID, "Ident", $2));
        add_child($$, create_token_node(LBRACKET, "LBRACKET", $3));
        add_child($$, create_token_node(RBRACKET, "RBRACKET", $4));
        add_child($$, $5);
    }
;
FuncFParamDims:
    LBRACKET RBRACKET {
        $$ = create_ast_node(Node_FuncFParamDims, "FuncFParamDims", yylineno);
        add_child($$, create_token_node(LBRACKET, "LBRACKET", $1));
        add_child($$, create_token_node(RBRACKET, "RBRACKET", $2));
    }
    | FuncFParamDims LBRACKET RBRACKET {
        $$ = $1;
        add_child($$, create_token_node(LBRACKET, "LBRACKET", $2));
        add_child($$, create_token_node(RBRACKET, "RBRACKET", $3));
    }
    ;
Block:
    LBRACE BlockItem_list RBRACE {
        $$ = create_ast_node(Node_Block, "Block", yylineno);
        add_child($$, create_token_node(LBRACE, "LBRACE", $1));
        add_child($$, $2);
        add_child($$, create_token_node(RBRACE, "RBRACE", $3));
    }
    ;

BlockItem_list:
    /* empty */ {
        $$ = create_ast_node(Node_BlockItem, "BlockItem_list", yylineno);
        $$->is_epsilon = 1;
    }
    | BlockItem_list BlockItem {
        $$ = create_ast_node(Node_BlockItem, "BlockItem_list", yylineno);
        add_child($$, $1);
        add_child($$, $2);
    }
    ;

BlockItem:
    Decl {
        $$ = create_ast_node(Node_BlockItem, "BlockItem", yylineno);
        add_child($$, $1);
    }
    | Stmt {
        $$ = create_ast_node(Node_BlockItem, "BlockItem", yylineno);
        add_child($$, $1);
    }
    ;

Stmt:
    LVal ASSIGN Exp SEMICN {
        $$ = create_ast_node(Node_Stmt, "Stmt", yylineno);
        add_child($$, $1);
        add_child($$, create_token_node(ASSIGN, "ASSIGN", $2));
        add_child($$, $3);
        add_child($$, create_token_node(SEMICN, "SEMICN", $4));
    }
    | Exp SEMICN {
        $$ = create_ast_node(Node_Stmt, "Stmt", yylineno);
        add_child($$, $1);
        add_child($$, create_token_node(SEMICN, "SEMICN", $2));
    }
    | SEMICN {
        $$ = create_ast_node(Node_Stmt, "Stmt", yylineno);
        add_child($$, create_token_node(SEMICN, "SEMICN", $1));
    }
    | Block {
        $$ = create_ast_node(Node_Stmt, "Stmt", yylineno);
        add_child($$, $1);
    }
    | IFTK LPARENT Cond RPARENT Stmt {
        $$ = create_ast_node(Node_Stmt, "Stmt", yylineno);
        add_child($$, create_token_node(IFTK, "IFTK", $1));
        add_child($$, create_token_node(LPARENT, "LPARENT", $2));
        add_child($$, $3);
        add_child($$, create_token_node(RPARENT, "RPARENT", $4));
        add_child($$, $5);
    }
    | IFTK LPARENT Cond RPARENT Stmt ELSETK Stmt {
        $$ = create_ast_node(Node_Stmt, "Stmt", yylineno);
        add_child($$, create_token_node(IFTK, "IFTK", $1));
        add_child($$, create_token_node(LPARENT, "LPARENT", $2));
        add_child($$, $3);
        add_child($$, create_token_node(RPARENT, "RPARENT", $4));
        add_child($$, $5);
        add_child($$, create_token_node(ELSETK, "ELSETK", $6));
        add_child($$, $7);
    }
    | WHILETK LPARENT Cond RPARENT Stmt {
        $$ = create_ast_node(Node_Stmt, "Stmt", yylineno);
        add_child($$, create_token_node(WHILETK, "WHILETK", $1));
        add_child($$, create_token_node(LPARENT, "LPARENT", $2));
        add_child($$, $3);
        add_child($$, create_token_node(RPARENT, "RPARENT", $4));
        add_child($$, $5);
    }
    | BREAKTK SEMICN {
        $$ = create_ast_node(Node_Stmt, "Stmt", yylineno);
        add_child($$, create_token_node(BREAKTK, "BREAKTK", $1));
        add_child($$, create_token_node(SEMICN, "SEMICN", $2));
    }
    | CONTINUETK SEMICN {
        $$ = create_ast_node(Node_Stmt, "Stmt", yylineno);
        add_child($$, create_token_node(CONTINUETK, "CONTINUETK", $1));
        add_child($$, create_token_node(SEMICN, "SEMICN", $2));
    }
    | RETURNTK SEMICN {
        $$ = create_ast_node(Node_Stmt, "Stmt", yylineno);
        add_child($$, create_token_node(RETURNTK, "RETURNTK", $1));
        add_child($$, create_token_node(SEMICN, "SEMICN", $2));
    }
    | RETURNTK Exp SEMICN {
        $$ = create_ast_node(Node_Stmt, "Stmt", yylineno);
        add_child($$, create_token_node(RETURNTK, "RETURNTK", $1));
        add_child($$, $2);
        add_child($$, create_token_node(SEMICN, "SEMICN", $3));
    }
        | LVal ASSIGN Exp {  // 处理赋值语句缺少分号的情况
        // 使用当前行号来报告错误
        int error_line = yylineno;  // 在此时手动保存 yylineno，确保行号不被后续解析影响
        syntax_error_list[syntax_error_count].line = error_line;
        snprintf(syntax_error_list[syntax_error_count].message, sizeof(syntax_error_list[syntax_error_count].message),
                 "Error type B at Line %d: Missing \";\".", error_line);
        syntax_error_count++;
        $$ = create_ast_node(Node_Stmt, "Stmt", yylineno);
        add_child($$, $1);
        add_child($$, create_token_node(ASSIGN, "ASSIGN", $2));
        add_child($$, $3);
    }
    ;

Exp:
    AddExp {
        $$ = create_ast_node(Node_Exp, "Exp", yylineno);
        add_child($$, $1);
    }
    ;

Cond:
    LOrExp {
        $$ = create_ast_node(Node_Cond, "Cond", yylineno);
        add_child($$, $1);
    }
    ;

LVal:
    ID {
        $$ = create_ast_node(Node_LVal, "LVal", yylineno);
        add_child($$, create_token_node(ID, "ID", $1));
    }
    | ID LBRACKET Exp RBRACKET {
        $$ = create_ast_node(Node_LVal, "LVal", yylineno);
        add_child($$, create_token_node(ID, "ID", $1));
        add_child($$, create_token_node(LBRACKET, "LBRACKET", $2));
        add_child($$, $3);
        add_child($$, create_token_node(RBRACKET, "RBRACKET", $4));
    }
    | ID LBRACKET Exp RBRACKET LBRACKET Exp RBRACKET {
        $$ = create_ast_node(Node_LVal, "LVal", yylineno);
        add_child($$, create_token_node(ID, "ID", $1));
        add_child($$, create_token_node(LBRACKET, "LBRACKET", $2));
        add_child($$, $3);
        add_child($$, create_token_node(RBRACKET, "RBRACKET", $4));
        add_child($$, create_token_node(LBRACKET, "LBRACKET", $5));
        add_child($$, $6);
        add_child($$, create_token_node(RBRACKET, "RBRACKET", $7));
    }
     | ID LBRACKET Exp COMMA Exp RBRACKET {  // 处理 a[5, 3] 错误
        // 使用当前行号来报告错误
        int error_line = yylineno;  // 在此时手动保存 yylineno，确保行号不被后续解析影响
        syntax_error_list[syntax_error_count].line = error_line;
        snprintf(syntax_error_list[syntax_error_count].message, sizeof(syntax_error_list[syntax_error_count].message),
                 "Error type B at Line %d: Missing \"]\".", error_line);
        syntax_error_count++;
        $$ = create_ast_node(Node_LVal, "LVal", yylineno);  // 创建空的节点避免后续分析崩溃
        add_child($$, create_token_node(ID, "ID", $1));
        add_child($$, create_token_node(LBRACKET, "LBRACKET", $2));
        add_child($$, $3);
        add_child($$, create_token_node(COMMA, "COMMA", $4));
        add_child($$, $5);
        add_child($$, create_token_node(RBRACKET, "RBRACKET", $6));
    }
    ;

PrimaryExp:
    LPARENT Exp RPARENT {
        $$ = create_ast_node(Node_PrimaryExp, "PrimaryExp", yylineno);
        add_child($$, create_token_node(LPARENT, "LPARENT", $1));
        add_child($$, $2);
        add_child($$, create_token_node(RPARENT, "RPARENT", $3));
    }
    | LVal {
        $$ = create_ast_node(Node_PrimaryExp, "PrimaryExp", yylineno);
        add_child($$, $1);
    }
    | Number {
        $$ = create_ast_node(Node_PrimaryExp, "PrimaryExp", yylineno);
        add_child($$, $1);
    }
    ;

Number:
    INTCON {
        $$ = create_ast_node(Node_Number, "Number", yylineno);
                char buf[32];
        sprintf(buf, "%d", $1);   // ⭐ int → string
        add_child($$, create_token_node(INTCON, "INTCON", buf));
    }

    ;

UnaryExp:
    PrimaryExp {
        $$ = create_ast_node(Node_UnaryExp, "UnaryExp", yylineno);
        add_child($$, $1);
    }
    | ID LPARENT FuncRParamsOpt RPARENT {
        $$ = create_ast_node(Node_UnaryExp, "UnaryExp", yylineno);
        add_child($$, create_token_node(ID, "ID", $1));
        add_child($$, create_token_node(LPARENT, "LPARENT", $2));
        if ($3) add_child($$, $3);
        add_child($$, create_token_node(RPARENT, "RPARENT", $4));
    }
    | UnaryOp UnaryExp {
        $$ = create_ast_node(Node_UnaryExp, "UnaryExp", yylineno);
        add_child($$, $1);
        add_child($$, $2);
    }
    ;

UnaryOp:
    PLUS {
        $$ = create_ast_node(Node_UnaryOp, "UnaryOp", yylineno);
        add_child($$, create_token_node(PLUS, "PLUS", $1));
    }
    | MINUS {
        $$ = create_ast_node(Node_UnaryOp, "UnaryOp", yylineno);
        add_child($$, create_token_node(MINUS, "MINUS", $1));
    }
    | NOT {
        $$ = create_ast_node(Node_UnaryOp, "UnaryOp", yylineno);
        add_child($$, create_token_node(NOT, "NOT", $1));
    }
    ;

MulExp:
    UnaryExp {
        $$ = create_ast_node(Node_MulExp, "MulExp", yylineno);
        add_child($$, $1);
    }
    | MulExp MUL UnaryExp {
        $$ = create_ast_node(Node_MulExp, "MulExp", yylineno);
        add_child($$, $1);
        add_child($$, create_token_node(MUL, "MUL", $2));
        add_child($$, $3);
    }
    | MulExp DIV UnaryExp {
        $$ = create_ast_node(Node_MulExp, "MulExp", yylineno);
        add_child($$, $1);
        add_child($$, create_token_node(DIV, "DIV", $2));
        add_child($$, $3);
    }
    | MulExp MOD UnaryExp {
        $$ = create_ast_node(Node_MulExp, "MulExp", yylineno);
        add_child($$, $1);
        add_child($$, create_token_node(MOD, "MOD", $2));
        add_child($$, $3);
    }
    ;

AddExp:
    MulExp {
        $$ = create_ast_node(Node_AddExp, "AddExp", yylineno);
        add_child($$, $1);
    }
    | AddExp PLUS MulExp {
        $$ = create_ast_node(Node_AddExp, "AddExp", yylineno);
        add_child($$, $1);
        add_child($$, create_token_node(PLUS, "PLUS", $2));
        add_child($$, $3);
    }
    | AddExp MINUS MulExp {
        $$ = create_ast_node(Node_AddExp, "AddExp", yylineno);
        add_child($$, $1);
        add_child($$, create_token_node(MINUS, "MINUS", $2));
        add_child($$, $3);
    }
    ;

RelExp:
    AddExp {
        $$ = create_ast_node(Node_RelExp, "RelExp", yylineno);
        add_child($$, $1);
    }
    | RelExp LT AddExp {
        $$ = create_ast_node(Node_RelExp, "RelExp", yylineno);
        add_child($$, $1);
        add_child($$, create_token_node(LT, "LT", $2));
        add_child($$, $3);
    }
    | RelExp GT AddExp {
        $$ = create_ast_node(Node_RelExp, "RelExp", yylineno);
        add_child($$, $1);
        add_child($$, create_token_node(GT, "GT", $2));
        add_child($$, $3);
    }
    | RelExp LEQ AddExp {
        $$ = create_ast_node(Node_RelExp, "RelExp", yylineno);
        add_child($$, $1);
        add_child($$, create_token_node(LEQ, "LEQ", $2));
        add_child($$, $3);
    }
    | RelExp GEQ AddExp {
        $$ = create_ast_node(Node_RelExp, "RelExp", yylineno);
        add_child($$, $1);
        add_child($$, create_token_node(GEQ, "GEQ", $2));
        add_child($$, $3);
    }
    ;

EqExp:
    RelExp {
        $$ = create_ast_node(Node_EqExp, "EqExp", yylineno);
        add_child($$, $1);
    }
    | EqExp EQ RelExp {
        $$ = create_ast_node(Node_EqExp, "EqExp", yylineno);
        add_child($$, $1);
        add_child($$, create_token_node(EQ, "EQ", $2));
        add_child($$, $3);
    }
    | EqExp NEQ RelExp {
        $$ = create_ast_node(Node_EqExp, "EqExp", yylineno);
        add_child($$, $1);
        add_child($$, create_token_node(NEQ, "NEQ", $2));
        add_child($$, $3);
    }
    ;

LAndExp:
    EqExp {
        $$ = create_ast_node(Node_LAndExp, "LAndExp", yylineno);
        add_child($$, $1);
    }
    | LAndExp AND EqExp {
        $$ = create_ast_node(Node_LAndExp, "LAndExp", yylineno);
        add_child($$, $1);
        add_child($$, create_token_node(AND, "AND", $2));
        add_child($$, $3);
    }
    ;

LOrExp:
    LAndExp {
        $$ = create_ast_node(Node_LOrExp, "LOrExp", yylineno);
        add_child($$, $1);
    }
    | LOrExp OR LAndExp {
        $$ = create_ast_node(Node_LOrExp, "LOrExp", yylineno);
        add_child($$, $1);
        add_child($$, create_token_node(OR, "OR", $2));
        add_child($$, $3);
    }
    ;

ConstExp:
    AddExp {
        $$ = create_ast_node(Node_ConstExp, "ConstExp", yylineno);
        add_child($$, $1);
    }
    ;

%%

//C代码部分
ASTNode* create_ast_node(NodeType type, const char* name, int line) {
    ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
    node->type = type;
    strcpy(node->name, name);
    node->line = line;
    node->token_type = ENDFILE;
    node->value[0] = '\0';
    node->children = NULL;
    node->child_count = 0;
    node->is_epsilon = 0;
    return node;
}

ASTNode* create_token_node(int token_type, const char* name, const char* value) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = Node_Token;
    strcpy(node->name, name);
    node->line = -1;
    node->token_type = token_type;   // ⭐ Bison token
    if (value)
        strncpy(node->value, value, sizeof(node->value) - 1);
    else
        node->value[0] = '\0';
    node->value[sizeof(node->value) - 1] = '\0';
    node->children = NULL;
    node->child_count = 0;
    node->is_epsilon = 0;
    return node;
}


void add_child(ASTNode* parent, ASTNode* child) {
    if (!parent || !child) return;
    
    ASTNode** new_children = (ASTNode**)realloc(parent->children,
                                        (parent->child_count + 1) * sizeof(ASTNode*));
    if (!new_children) {
        fprintf(stderr, "Memory allocation failed in add_child\n");
        return;
    }
    parent->children = new_children;
    parent->children[parent->child_count] = child;
    parent->child_count++;
}

void print_ast(ASTNode* node, int depth) {
    if (!node) return;
    
    // 缩进
    for (int i = 0; i < depth; i++) {
        printf("  ");
    }
    
    if (node->type == Node_Token) {
        // 词法单元节点
        printf("%s", node->name);
        
        // 特殊处理不同类型的词法单元
        if (node->token_type == ID) {
            printf(": %s", node->value);
        } else if (node->token_type == INTTK || node->token_type == FLOATTK || node->token_type == VOIDTK) {
            printf(": %s", node->value);
        } else if (node->token_type == INTCON) {
            printf(": %s", node->value);
        }
        printf("\n");
    } else {
        // 语法单元节点
        if (!node->is_epsilon) {
            printf("%s (%d)\n", node->name, node->line);
        } else {
            printf("%s\n", node->name);
        }
    }
    
    // 递归打印子节点
    for (int i = 0; i < node->child_count; i++) {
        print_ast(node->children[i], depth + 1);
    }
}

void yyerror(const char* s) {
    if (syntax_error_count < MAX_ERRORS) {
        syntax_error_list[syntax_error_count].line = yylineno;  // 记录语法错误所在的行号
        snprintf(syntax_error_list[syntax_error_count].message, sizeof(syntax_error_list[syntax_error_count].message), 
                 "Error type B at Line %d: %s", yylineno, s);
        syntax_error_count++;  // 语法错误计数器加1
    } else {
        fprintf(stderr, "Too many syntax errors, stopping parsing...\n");
        has_error = 1;  // 如果错误过多，则中止分析
    }
}


int main(int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <input_file>\n", argv[0]);
        return 1;
    }
    
    FILE* file = fopen(argv[1], "r");
    if (!file) {
        fprintf(stderr, "Error: Cannot open file %s\n", argv[1]);
        return 1;
    }
    
    yyin = file;
    

    yyparse();
    
    if (error_count > 0) {
        for (int i = 0; i < error_count; i++) {
            fprintf(stderr, "%s", error_list[i].message);
        }
        return 0;
    }
    if (syntax_error_count > 0) {
        for (int i = 0; i < syntax_error_count; i++) {
            fprintf(stderr, "%s\n", syntax_error_list[i].message);
        }
        return 0;
    }

    print_ast(root, 0);
  
    return 0;
}

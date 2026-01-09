%option noyywrap
%option nounput
%option noinput
%option yylineno

%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "ast.h"
#include "parser.tab.h"
#define MAX_ERROR 100
#define MAX_TOKEN_PRINT_LENGTH 100
#define MAX_PRINT_TOKENS 256




Error error_list[MAX_ERROR];
char *print_buffer[MAX_TOKEN_PRINT_LENGTH];
int error_count = 0;
int print_count = 0;
int has_lexical_error = 0;
extern FILE *yyin;
extern int yylineno;
void add_error(int line, const char *msg);
int yylex(void);
void print_token(int token, char *value);
int convert_octal(char *str);
int convert_hex(char *str);
int is_valid_octal(char *str);
int is_valid_hex(char *str);
%}

DIGIT      [0-9]
NONZERO    [1-9]
LETTER     [a-zA-Z_]
HEX        [0-9a-fA-F]
OCTAL      [0-7]
WHITESPACE [ \t\r]+
NEWLINE    \n
LineComment   "//".*
BlockComment  "/*"(.|\n)*?"*/"
Identifier    {LETTER}({LETTER}|{DIGIT})*
Decimal       (0|{NONZERO}{DIGIT}*)
Hexadecimal  0[xX]{HEX}+
Octal         0{OCTAL}+
Float         {DIGIT}+"."{DIGIT}*
InvalidHex    0[xX][^0-9a-fA-F]*
InvalidOctal  0[8-9][0-9]*
InvalidIdentifier  {DIGIT}+({LETTER}|_)+({LETTER}|{DIGIT}|_)*

%%

{WHITESPACE}    { }
{NEWLINE}       { }
{LineComment}   { }
{BlockComment}  { }

"int"       { yylval.str= strdup(yytext); return (INTTK); }
"float"     {  yylval.str= strdup(yytext); return (FLOATTK); }
"void"      {  yylval.str= strdup(yytext); return (VOIDTK); }
"const"     {  yylval.str= strdup(yytext); return (CONSTTK); }
"if"        {  yylval.str= strdup(yytext); return (IFTK); }
"else"      {  yylval.str= strdup(yytext); return (ELSETK); }
"while"     {  yylval.str= strdup(yytext); return (WHILETK); }
"break"     {  yylval.str= strdup(yytext); return (BREAKTK); }
"continue"  {  yylval.str= strdup(yytext); return (CONTINUETK); }
"return"    {  yylval.str= strdup(yytext); return (RETURNTK); }
{Hexadecimal} { 
yylval.intval = convert_hex(yytext);

return INTCON;
}

{InvalidHex} {
char err_msg[100];
snprintf(err_msg,sizeof(err_msg),"Error type A at Line %d: Invalid character \"%s\"\n", yylineno, yytext);
add_error(yylineno, err_msg);
}



{InvalidOctal} {
char err_msg[100];
snprintf(err_msg,sizeof(err_msg),"Error type A at Line %d: Invalid character \"%s\"\n", yylineno, yytext);
add_error(yylineno, err_msg);
}



{InvalidIdentifier} {
char err_msg[100];
snprintf(err_msg,sizeof(err_msg),"Error type A at Line %d: Invalid character \"%s\"\n", yylineno, yytext);
add_error(yylineno, err_msg);
}





{Octal} {
yylval.intval = convert_octal(yytext);

return INTCON;

}

{Decimal} { yylval.intval = atoi(yytext); return INTCON; }
{Float} { yylval.str = strdup(yytext);  return INTCON; }

{Identifier} { yylval.str = strdup(yytext); return ID; }
"+" {  yylval.str = strdup(yytext); return PLUS; }
"-" {  yylval.str = strdup(yytext); return MINUS; }
"*" {  yylval.str = strdup(yytext); return MUL; }
"/" {  yylval.str = strdup(yytext); return DIV; }
"%" {  yylval.str = strdup(yytext); return MOD; }
"=" {  yylval.str = strdup(yytext); return ASSIGN; }
"==" {  yylval.str = strdup(yytext); return EQ; }
"!=" {      yylval.str = strdup(yytext); return NEQ; }
"<" {  yylval.str = strdup(yytext); return LT; }
">" {  yylval.str = strdup(yytext); return GT; }
"<=" {  yylval.str = strdup(yytext); return LEQ; }
">=" {  yylval.str = strdup(yytext); return GEQ; }
"&&" {  yylval.str = strdup(yytext); return AND; }
"||" {  yylval.str = strdup(yytext); return OR; }
"!" {  yylval.str = strdup(yytext); return NOT; }
"(" {  yylval.str = strdup(yytext); return LPARENT; }
")" {  yylval.str = strdup(yytext); return RPARENT; }
"[" {  yylval.str = strdup(yytext); return LBRACKET; }
"]" {  yylval.str = strdup(yytext); return RBRACKET; }
"{" {  yylval.str = strdup(yytext); return LBRACE; }
"}" {  yylval.str = strdup(yytext); return RBRACE; }
";" {  yylval.str = strdup(yytext); return SEMICN; }
"," {  yylval.str = strdup(yytext); return COMMA; }

. {
char err_msg[100];
snprintf(err_msg,sizeof(err_msg),"Error type A at Line %d: Invalid character \"%s\"\n", yylineno, yytext);
add_error(yylineno, err_msg);
}

%%


int is_valid_octal(char *str) {
    if (str[0] != '0') return 0;
    for (int i = 1; str[i]; i++)
        if (str[i] < '0' || str[i] > '7') return 0;
    return 1;
}

int is_valid_hex(char *str) {
    if (str[0] != '0' || (str[1] != 'x' && str[1] != 'X')) return 0;
    for (int i = 2; str[i]; i++)
        if (!((str[i] >= '0' && str[i] <= '9') ||
              (str[i] >= 'a' && str[i] <= 'f') ||
              (str[i] >= 'A' && str[i] <= 'F')))
            return 0;
    return 1;
}

int convert_octal(char *str) {
    int result = 0;
    for (int i = 1; str[i]; i++)
        result = result * 8 + (str[i] - '0');
    return result;
}

int convert_hex(char *str) {
    int result = 0;
    for (int i = 2; str[i]; i++) {
        int digit;
        if (str[i] >= '0' && str[i] <= '9') digit = str[i] - '0';
        else if (str[i] >= 'a' && str[i] <= 'f') digit = str[i] - 'a' + 10;
        else if (str[i] >= 'A' && str[i] <= 'F') digit = str[i] - 'A' + 10;
        else continue;
        result = result * 16 + digit;
    }
    return result;
}
void add_error(int line, const char *msg) {
    if (error_count < MAX_ERROR) {
        error_list[error_count].line = line;
        strcpy(error_list[error_count].message, msg);
        error_count++;
        has_lexical_error = 1;
    }
}

/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "parser.y"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "ast.h"
#include "parser.tab.h"
#include "semantic.h"
#include "irgen.h"
#include "codegen.h"
#define MAX_ERRORS 100

//语法树结构

//全局变量
extern FILE *yyin;
extern int yylineno;
extern Error error_list[];
extern int yyaccept;
extern int yychar;  // 添加这个声明，用于错误恢复
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
int yylex(void);
void yyerror(const char* s) ;
void add_syntax_error(int line, const char *msg);


#line 107 "parser.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "parser.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_INTTK = 3,                      /* INTTK  */
  YYSYMBOL_FLOATTK = 4,                    /* FLOATTK  */
  YYSYMBOL_VOIDTK = 5,                     /* VOIDTK  */
  YYSYMBOL_CONSTTK = 6,                    /* CONSTTK  */
  YYSYMBOL_IFTK = 7,                       /* IFTK  */
  YYSYMBOL_ELSETK = 8,                     /* ELSETK  */
  YYSYMBOL_WHILETK = 9,                    /* WHILETK  */
  YYSYMBOL_BREAKTK = 10,                   /* BREAKTK  */
  YYSYMBOL_CONTINUETK = 11,                /* CONTINUETK  */
  YYSYMBOL_RETURNTK = 12,                  /* RETURNTK  */
  YYSYMBOL_ID = 13,                        /* ID  */
  YYSYMBOL_INTCON = 14,                    /* INTCON  */
  YYSYMBOL_FLOATCON = 15,                  /* FLOATCON  */
  YYSYMBOL_PLUS = 16,                      /* PLUS  */
  YYSYMBOL_MINUS = 17,                     /* MINUS  */
  YYSYMBOL_MUL = 18,                       /* MUL  */
  YYSYMBOL_DIV = 19,                       /* DIV  */
  YYSYMBOL_MOD = 20,                       /* MOD  */
  YYSYMBOL_ASSIGN = 21,                    /* ASSIGN  */
  YYSYMBOL_EQ = 22,                        /* EQ  */
  YYSYMBOL_NEQ = 23,                       /* NEQ  */
  YYSYMBOL_LT = 24,                        /* LT  */
  YYSYMBOL_GT = 25,                        /* GT  */
  YYSYMBOL_LEQ = 26,                       /* LEQ  */
  YYSYMBOL_GEQ = 27,                       /* GEQ  */
  YYSYMBOL_AND = 28,                       /* AND  */
  YYSYMBOL_OR = 29,                        /* OR  */
  YYSYMBOL_NOT = 30,                       /* NOT  */
  YYSYMBOL_LPARENT = 31,                   /* LPARENT  */
  YYSYMBOL_RPARENT = 32,                   /* RPARENT  */
  YYSYMBOL_LBRACKET = 33,                  /* LBRACKET  */
  YYSYMBOL_RBRACKET = 34,                  /* RBRACKET  */
  YYSYMBOL_LBRACE = 35,                    /* LBRACE  */
  YYSYMBOL_RBRACE = 36,                    /* RBRACE  */
  YYSYMBOL_SEMICN = 37,                    /* SEMICN  */
  YYSYMBOL_COMMA = 38,                     /* COMMA  */
  YYSYMBOL_YYACCEPT = 39,                  /* $accept  */
  YYSYMBOL_CompUnit = 40,                  /* CompUnit  */
  YYSYMBOL_DeclOrFuncDefList = 41,         /* DeclOrFuncDefList  */
  YYSYMBOL_DeclOrFuncDef = 42,             /* DeclOrFuncDef  */
  YYSYMBOL_Decl = 43,                      /* Decl  */
  YYSYMBOL_ConstDecl = 44,                 /* ConstDecl  */
  YYSYMBOL_BType = 45,                     /* BType  */
  YYSYMBOL_ConstDef = 46,                  /* ConstDef  */
  YYSYMBOL_ConstInitVal = 47,              /* ConstInitVal  */
  YYSYMBOL_VarDecl = 48,                   /* VarDecl  */
  YYSYMBOL_VarDefListOpt = 49,             /* VarDefListOpt  */
  YYSYMBOL_VarDefList = 50,                /* VarDefList  */
  YYSYMBOL_VarDef = 51,                    /* VarDef  */
  YYSYMBOL_InitVal = 52,                   /* InitVal  */
  YYSYMBOL_FuncFParamsOpt = 53,            /* FuncFParamsOpt  */
  YYSYMBOL_FuncFParams = 54,               /* FuncFParams  */
  YYSYMBOL_FuncRParamsOpt = 55,            /* FuncRParamsOpt  */
  YYSYMBOL_FuncRParams = 56,               /* FuncRParams  */
  YYSYMBOL_FuncFParam = 57,                /* FuncFParam  */
  YYSYMBOL_FuncFParamDims = 58,            /* FuncFParamDims  */
  YYSYMBOL_Block = 59,                     /* Block  */
  YYSYMBOL_BlockItem_list = 60,            /* BlockItem_list  */
  YYSYMBOL_BlockItem = 61,                 /* BlockItem  */
  YYSYMBOL_Stmt = 62,                      /* Stmt  */
  YYSYMBOL_Exp = 63,                       /* Exp  */
  YYSYMBOL_Cond = 64,                      /* Cond  */
  YYSYMBOL_LVal = 65,                      /* LVal  */
  YYSYMBOL_PrimaryExp = 66,                /* PrimaryExp  */
  YYSYMBOL_Number = 67,                    /* Number  */
  YYSYMBOL_UnaryExp = 68,                  /* UnaryExp  */
  YYSYMBOL_UnaryOp = 69,                   /* UnaryOp  */
  YYSYMBOL_MulExp = 70,                    /* MulExp  */
  YYSYMBOL_AddExp = 71,                    /* AddExp  */
  YYSYMBOL_RelExp = 72,                    /* RelExp  */
  YYSYMBOL_EqExp = 73,                     /* EqExp  */
  YYSYMBOL_LAndExp = 74,                   /* LAndExp  */
  YYSYMBOL_LOrExp = 75,                    /* LOrExp  */
  YYSYMBOL_ConstExp = 76                   /* ConstExp  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  18
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   192

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  39
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  38
/* YYNRULES -- Number of rules.  */
#define YYNRULES  93
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  171

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   293


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    78,    78,    84,    88,    96,   105,   116,   125,   129,
     133,   140,   150,   154,   161,   170,   177,   187,   188,   192,
     197,   205,   209,   216,   226,   235,   241,   244,   263,   267,
     275,   278,   282,   286,   293,   298,   308,   313,   320,   334,
     338,   345,   349,   353,   366,   374,   386,   392,   400,   410,
     414,   419,   427,   437,   445,   450,   455,   460,   469,   476,
     483,   487,   494,   509,   515,   519,   526,   532,   540,   544,
     551,   559,   563,   567,   574,   578,   584,   590,   599,   603,
     609,   618,   622,   628,   634,   640,   649,   653,   659,   668,
     672,   681,   685,   694
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "INTTK", "FLOATTK",
  "VOIDTK", "CONSTTK", "IFTK", "ELSETK", "WHILETK", "BREAKTK",
  "CONTINUETK", "RETURNTK", "ID", "INTCON", "FLOATCON", "PLUS", "MINUS",
  "MUL", "DIV", "MOD", "ASSIGN", "EQ", "NEQ", "LT", "GT", "LEQ", "GEQ",
  "AND", "OR", "NOT", "LPARENT", "RPARENT", "LBRACKET", "RBRACKET",
  "LBRACE", "RBRACE", "SEMICN", "COMMA", "$accept", "CompUnit",
  "DeclOrFuncDefList", "DeclOrFuncDef", "Decl", "ConstDecl", "BType",
  "ConstDef", "ConstInitVal", "VarDecl", "VarDefListOpt", "VarDefList",
  "VarDef", "InitVal", "FuncFParamsOpt", "FuncFParams", "FuncRParamsOpt",
  "FuncRParams", "FuncFParam", "FuncFParamDims", "Block", "BlockItem_list",
  "BlockItem", "Stmt", "Exp", "Cond", "LVal", "PrimaryExp", "Number",
  "UnaryExp", "UnaryOp", "MulExp", "AddExp", "RelExp", "EqExp", "LAndExp",
  "LOrExp", "ConstExp", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-133)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      60,    20,    31,    35,    36,    17,    60,  -133,  -133,  -133,
      46,  -133,    43,    52,    80,  -133,  -133,    64,  -133,  -133,
      28,    48,    36,    36,    36,    75,    77,    87,    87,    46,
      91,    97,   103,   108,   104,  -133,   111,   112,    87,  -133,
      79,  -133,  -133,  -133,  -133,  -133,    87,  -133,  -133,  -133,
    -133,  -133,  -133,    87,    50,    89,    89,   107,  -133,  -133,
      46,   113,   114,    36,   114,   114,  -133,  -133,    87,    87,
     115,  -133,    87,    87,    87,    87,    87,   117,  -133,   118,
    -133,  -133,  -133,  -133,  -133,   116,   119,  -133,   -25,  -133,
    -133,  -133,  -133,    50,    50,    87,   120,    15,  -133,    87,
    -133,    87,   121,   122,   125,   123,   128,   130,   126,   127,
      41,  -133,  -133,  -133,  -133,  -133,  -133,    10,   124,  -133,
     131,  -133,  -133,   132,  -133,    87,    87,  -133,  -133,  -133,
     133,  -133,  -133,    87,   150,  -133,   135,    89,    55,   109,
     134,   139,   137,  -133,     4,  -133,    78,    87,    87,    87,
      87,    87,    87,    87,    87,    78,  -133,  -133,  -133,   146,
      89,    89,    89,    89,    55,    55,   109,   134,  -133,    78,
    -133
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     0,     0,     0,     0,     2,     3,     8,     9,
       0,    10,     0,     0,     0,    12,    13,     0,     1,     4,
      21,    17,    26,    26,    26,     0,     0,     0,     0,     0,
       0,    18,     0,     0,    27,    28,     0,     0,     0,    11,
      60,    66,    67,    71,    72,    73,     0,    24,    25,    64,
      68,    65,    74,     0,    78,    58,    93,     0,    19,    16,
       0,    34,     0,     0,     0,     0,    14,    15,    30,     0,
       0,    70,     0,     0,     0,     0,     0,    22,    20,     0,
      39,     6,    29,     7,     5,     0,    31,    32,     0,    63,
      75,    76,    77,    79,    80,     0,     0,     0,    69,     0,
      61,     0,     0,     0,    35,     0,     0,     0,     0,     0,
       0,    38,    49,    41,    50,    40,    42,     0,    64,    33,
       0,    23,    36,     0,    43,     0,     0,    54,    55,    56,
       0,    47,    46,     0,     0,    37,     0,    81,    86,    89,
      91,    59,     0,    57,     0,    62,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    48,    45,    44,    51,
      82,    83,    84,    85,    87,    88,    90,    92,    53,     0,
      52
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -133,  -133,  -133,   165,    76,  -133,     2,  -133,  -133,  -133,
    -133,  -133,   -22,  -133,   110,  -133,  -133,  -133,   129,  -133,
      65,  -133,  -133,  -132,   -26,    49,   -93,  -133,  -133,   -38,
    -133,    61,   -28,   -13,    19,    22,  -133,   -35
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     5,     6,     7,     8,     9,    32,    26,    66,    11,
      30,    31,    21,    47,    33,    34,    85,    86,    35,   104,
     114,    97,   115,   116,   117,   136,    49,    50,    51,    52,
      53,    54,    55,   138,   139,   140,   141,    57
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      56,    48,    10,    67,   118,   156,    17,    58,    10,   100,
      56,   131,   157,   101,   159,    71,   105,    18,    15,    16,
      70,     4,   106,   168,   107,   108,   109,   110,    40,    41,
      42,    43,    44,    12,    90,    91,    92,   170,    78,    15,
      16,   158,    87,    88,    13,    45,    46,   132,    14,    27,
      80,   111,   112,   118,    40,    41,    42,    43,    44,    20,
     102,    28,   118,     1,     2,     3,     4,    56,    72,    73,
      74,    45,    46,   119,    22,   120,   118,    25,   129,   147,
     148,   149,   150,    23,   130,   106,    29,   107,   108,   109,
     110,    40,    41,    42,    43,    44,    38,   137,   137,    10,
      40,    41,    42,    43,    44,    75,    76,   144,    45,    46,
      68,    24,    69,    80,    39,   112,    61,    45,    46,   160,
     161,   162,   163,   137,   137,   137,   137,    81,    59,    83,
      84,   151,   152,    36,    37,    60,    93,    94,   164,   165,
      62,    77,    63,    64,    65,   133,    79,    89,    98,    80,
      95,   145,    96,   103,   169,   121,   122,    99,   123,   125,
     124,   126,   153,   127,   128,   134,   135,   146,   154,   155,
     143,    19,   166,   113,     0,   142,   167,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    82
};

static const yytype_int16 yycheck[] =
{
      28,    27,     0,    38,    97,     1,     4,    29,     6,    34,
      38,     1,     8,    38,   146,    53,     1,     0,     3,     4,
      46,     6,     7,   155,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    13,    72,    73,    74,   169,    60,     3,
       4,    37,    68,    69,    13,    30,    31,    37,    13,    21,
      35,    36,    37,   146,    13,    14,    15,    16,    17,    13,
      95,    33,   155,     3,     4,     5,     6,    95,    18,    19,
      20,    30,    31,    99,    31,   101,   169,    13,    37,    24,
      25,    26,    27,    31,   110,     7,    38,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    21,   125,   126,    97,
      13,    14,    15,    16,    17,    16,    17,   133,    30,    31,
      31,    31,    33,    35,    37,    37,    13,    30,    31,   147,
     148,   149,   150,   151,   152,   153,   154,    62,    37,    64,
      65,    22,    23,    23,    24,    38,    75,    76,   151,   152,
      32,    34,    38,    32,    32,    21,    33,    32,    32,    35,
      33,     1,    34,    33,     8,    34,    34,    38,    33,    31,
      37,    31,    28,    37,    37,    34,    34,    32,    29,    32,
      37,     6,   153,    97,    -1,   126,   154,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    63
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,     4,     5,     6,    40,    41,    42,    43,    44,
      45,    48,    13,    13,    13,     3,     4,    45,     0,    42,
      13,    51,    31,    31,    31,    13,    46,    21,    33,    38,
      49,    50,    45,    53,    54,    57,    53,    53,    21,    37,
      13,    14,    15,    16,    17,    30,    31,    52,    63,    65,
      66,    67,    68,    69,    70,    71,    71,    76,    51,    37,
      38,    13,    32,    38,    32,    32,    47,    76,    31,    33,
      63,    68,    18,    19,    20,    16,    17,    34,    51,    33,
      35,    59,    57,    59,    59,    55,    56,    63,    63,    32,
      68,    68,    68,    70,    70,    33,    34,    60,    32,    38,
      34,    38,    76,    33,    58,     1,     7,     9,    10,    11,
      12,    36,    37,    43,    59,    61,    62,    63,    65,    63,
      63,    34,    34,    33,    37,    31,    31,    37,    37,    37,
      63,     1,    37,    21,    34,    34,    64,    71,    72,    73,
      74,    75,    64,    37,    63,     1,    32,    24,    25,    26,
      27,    22,    23,    28,    29,    32,     1,     8,    37,    62,
      71,    71,    71,    71,    72,    72,    73,    74,    62,     8,
      62
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    39,    40,    41,    41,    42,    42,    42,    42,    43,
      43,    44,    45,    45,    46,    47,    48,    49,    49,    50,
      50,    51,    51,    51,    51,    52,    53,    53,    54,    54,
      55,    55,    56,    56,    57,    57,    58,    58,    59,    60,
      60,    61,    61,    61,    62,    62,    62,    62,    62,    62,
      62,    62,    62,    62,    62,    62,    62,    62,    63,    64,
      65,    65,    65,    66,    66,    66,    67,    67,    68,    68,
      68,    69,    69,    69,    70,    70,    70,    70,    71,    71,
      71,    72,    72,    72,    72,    72,    73,    73,    73,    74,
      74,    75,    75,    76
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     1,     2,     6,     6,     6,     1,     1,
       1,     4,     1,     1,     3,     1,     4,     0,     1,     2,
       3,     1,     4,     7,     3,     1,     0,     1,     1,     3,
       0,     1,     1,     3,     2,     5,     2,     3,     3,     0,
       2,     1,     1,     2,     4,     4,     2,     2,     4,     1,
       1,     5,     7,     5,     2,     2,     2,     3,     1,     1,
       1,     4,     7,     3,     1,     1,     1,     1,     1,     4,
       2,     1,     1,     1,     1,     3,     3,     3,     1,     3,
       3,     1,     3,     3,     3,     3,     1,     3,     3,     1,
       3,     1,     3,     1
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* CompUnit: DeclOrFuncDefList  */
#line 78 "parser.y"
                        {
        root = (yyvsp[0].node);
    }
#line 1295 "parser.tab.c"
    break;

  case 3: /* DeclOrFuncDefList: DeclOrFuncDef  */
#line 84 "parser.y"
                    {
        (yyval.node) = create_ast_node(Node_CompUnit, "CompUnit", 1);
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 1304 "parser.tab.c"
    break;

  case 4: /* DeclOrFuncDefList: DeclOrFuncDefList DeclOrFuncDef  */
#line 88 "parser.y"
                                      {
        (yyval.node) = (yyvsp[-1].node);
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 1313 "parser.tab.c"
    break;

  case 5: /* DeclOrFuncDef: VOIDTK ID LPARENT FuncFParamsOpt RPARENT Block  */
#line 96 "parser.y"
                                                     {
        (yyval.node) = create_ast_node(Node_FuncDef, "FuncDef", yylineno);
        add_child((yyval.node), create_token_node(VOIDTK, "VOIDTK", (yyvsp[-5].str)));
        add_child((yyval.node), create_token_node(ID, "ID", (yyvsp[-4].str)));
        add_child((yyval.node), create_token_node(LPARENT, "LPARENT", (yyvsp[-3].str)));
         if ((yyvsp[-2].node)) add_child((yyval.node), (yyvsp[-2].node));
        add_child((yyval.node), create_token_node(RPARENT, "RPARENT", (yyvsp[-1].str)));
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 1327 "parser.tab.c"
    break;

  case 6: /* DeclOrFuncDef: INTTK ID LPARENT FuncFParamsOpt RPARENT Block  */
#line 105 "parser.y"
                                                    {
        (yyval.node) = create_ast_node(Node_FuncDef, "FuncDef", 1);
        ASTNode* func_type = create_ast_node(Node_FuncType, "FuncType", 1);
        add_child(func_type, create_token_node(INTTK, "Type", "int"));
        add_child((yyval.node), func_type);
        add_child((yyval.node), create_token_node(ID, "Ident", (yyvsp[-4].str)));
        add_child((yyval.node), create_token_node(LPARENT, "LPARENT", (yyvsp[-3].str)));
         if ((yyvsp[-2].node)) add_child((yyval.node), (yyvsp[-2].node));
        add_child((yyval.node), create_token_node(RPARENT, "RPARENT", (yyvsp[-1].str)));
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 1343 "parser.tab.c"
    break;

  case 7: /* DeclOrFuncDef: FLOATTK ID LPARENT FuncFParamsOpt RPARENT Block  */
#line 116 "parser.y"
                                                      {
        (yyval.node) = create_ast_node(Node_FuncDef, "FuncDef", yylineno);
        add_child((yyval.node), create_token_node(FLOATTK, "FLOATTK", (yyvsp[-5].str)));
        add_child((yyval.node), create_token_node(ID, "ID", (yyvsp[-4].str)));
        add_child((yyval.node), create_token_node(LPARENT, "LPARENT", (yyvsp[-3].str)));
         if ((yyvsp[-2].node)) add_child((yyval.node), (yyvsp[-2].node));
        add_child((yyval.node), create_token_node(RPARENT, "RPARENT", (yyvsp[-1].str)));
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 1357 "parser.tab.c"
    break;

  case 8: /* DeclOrFuncDef: Decl  */
#line 125 "parser.y"
           { (yyval.node) = (yyvsp[0].node); }
#line 1363 "parser.tab.c"
    break;

  case 9: /* Decl: ConstDecl  */
#line 129 "parser.y"
              {
        (yyval.node) = create_ast_node(Node_Decl, "Decl", 3);
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 1372 "parser.tab.c"
    break;

  case 10: /* Decl: VarDecl  */
#line 133 "parser.y"
              {
        (yyval.node) = create_ast_node(Node_Decl, "Decl", 3);
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 1381 "parser.tab.c"
    break;

  case 11: /* ConstDecl: CONSTTK BType ConstDef SEMICN  */
#line 140 "parser.y"
                                  {
        (yyval.node) = create_ast_node(Node_ConstDecl, "ConstDecl", yylineno);
        add_child((yyval.node), create_token_node(CONSTTK, "CONSTTK", (yyvsp[-3].str)));
        add_child((yyval.node), (yyvsp[-2].node));
        add_child((yyval.node), (yyvsp[-1].node));
        add_child((yyval.node), create_token_node(SEMICN, "SEMICN", (yyvsp[0].str)));
    }
#line 1393 "parser.tab.c"
    break;

  case 12: /* BType: INTTK  */
#line 150 "parser.y"
          {
        (yyval.node) = create_ast_node(Node_BType, "BType", yylineno);
        add_child((yyval.node), create_token_node(INTTK, "Type", "int"));
    }
#line 1402 "parser.tab.c"
    break;

  case 13: /* BType: FLOATTK  */
#line 154 "parser.y"
              {
        (yyval.node) = create_ast_node(Node_BType, "BType", yylineno);
        add_child((yyval.node), create_token_node(FLOATTK, "FLOATTK", (yyvsp[0].str)));
    }
#line 1411 "parser.tab.c"
    break;

  case 14: /* ConstDef: ID ASSIGN ConstInitVal  */
#line 161 "parser.y"
                           {
        (yyval.node) = create_ast_node(Node_ConstDef, "ConstDef", yylineno);
        add_child((yyval.node), create_token_node(ID, "ID", (yyvsp[-2].str)));
        add_child((yyval.node), create_token_node(ASSIGN, "ASSIGN", (yyvsp[-1].str)));
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 1422 "parser.tab.c"
    break;

  case 15: /* ConstInitVal: ConstExp  */
#line 170 "parser.y"
             {
        (yyval.node) = create_ast_node(Node_ConstInitVal, "ConstInitVal", yylineno);
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 1431 "parser.tab.c"
    break;

  case 16: /* VarDecl: BType VarDef VarDefListOpt SEMICN  */
#line 177 "parser.y"
                                      {
        (yyval.node) = create_ast_node(Node_VarDecl, "VarDecl", 3);
        add_child((yyval.node), (yyvsp[-3].node));
        add_child((yyval.node), (yyvsp[-2].node));
        if ((yyvsp[-1].node)) add_child((yyval.node), (yyvsp[-1].node));
        add_child((yyval.node), create_token_node(SEMICN, "SEMICN", (yyvsp[0].str)));
    }
#line 1443 "parser.tab.c"
    break;

  case 17: /* VarDefListOpt: %empty  */
#line 187 "parser.y"
                { (yyval.node) = NULL; }
#line 1449 "parser.tab.c"
    break;

  case 18: /* VarDefListOpt: VarDefList  */
#line 188 "parser.y"
                 { (yyval.node) = (yyvsp[0].node); }
#line 1455 "parser.tab.c"
    break;

  case 19: /* VarDefList: COMMA VarDef  */
#line 192 "parser.y"
                 {
        (yyval.node) = create_ast_node(Node_VarDefList, "VarDefList", yylineno);
        add_child((yyval.node), create_token_node(COMMA, "COMMA", (yyvsp[-1].str)));
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 1465 "parser.tab.c"
    break;

  case 20: /* VarDefList: VarDefList COMMA VarDef  */
#line 197 "parser.y"
                              {
        (yyval.node) = (yyvsp[-2].node);
        add_child((yyval.node), create_token_node(COMMA, "COMMA", (yyvsp[-1].str)));
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 1475 "parser.tab.c"
    break;

  case 21: /* VarDef: ID  */
#line 205 "parser.y"
       {
        (yyval.node) = create_ast_node(Node_VarDef, "VarDef", yylineno);
        add_child((yyval.node), create_token_node(ID, "Ident", (yyvsp[0].str)));
    }
#line 1484 "parser.tab.c"
    break;

  case 22: /* VarDef: ID LBRACKET ConstExp RBRACKET  */
#line 209 "parser.y"
                                    {
        (yyval.node) = create_ast_node(Node_VarDef, "VarDef", yylineno);
        add_child((yyval.node), create_token_node(ID, "ID", (yyvsp[-3].str)));
        add_child((yyval.node), create_token_node(LBRACKET, "LBRACKET", (yyvsp[-2].str)));
        add_child((yyval.node), (yyvsp[-1].node));
        add_child((yyval.node), create_token_node(RBRACKET, "RBRACKET", (yyvsp[0].str)));
    }
#line 1496 "parser.tab.c"
    break;

  case 23: /* VarDef: ID LBRACKET ConstExp RBRACKET LBRACKET ConstExp RBRACKET  */
#line 216 "parser.y"
                                                               {
        (yyval.node) = create_ast_node(Node_VarDef, "VarDef", yylineno);
        add_child((yyval.node), create_token_node(ID, "ID", (yyvsp[-6].str)));
        add_child((yyval.node), create_token_node(LBRACKET, "LBRACKET", (yyvsp[-5].str)));
        add_child((yyval.node), (yyvsp[-4].node));
        add_child((yyval.node), create_token_node(RBRACKET, "RBRACKET", (yyvsp[-3].str)));
        add_child((yyval.node), create_token_node(LBRACKET, "LBRACKET", (yyvsp[-2].str)));
        add_child((yyval.node), (yyvsp[-1].node));
        add_child((yyval.node), create_token_node(RBRACKET, "RBRACKET", (yyvsp[0].str)));
    }
#line 1511 "parser.tab.c"
    break;

  case 24: /* VarDef: ID ASSIGN InitVal  */
#line 226 "parser.y"
                        {
        (yyval.node) = create_ast_node(Node_VarDef, "VarDef", yylineno);
        add_child((yyval.node), create_token_node(ID, "ID", (yyvsp[-2].str)));
        add_child((yyval.node), create_token_node(ASSIGN, "ASSIGN", (yyvsp[-1].str)));
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 1522 "parser.tab.c"
    break;

  case 25: /* InitVal: Exp  */
#line 235 "parser.y"
        {
        (yyval.node) = create_ast_node(Node_InitVal, "InitVal", yylineno);
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 1531 "parser.tab.c"
    break;

  case 26: /* FuncFParamsOpt: %empty  */
#line 241 "parser.y"
                 {
        (yyval.node) = NULL;
    }
#line 1539 "parser.tab.c"
    break;

  case 27: /* FuncFParamsOpt: FuncFParams  */
#line 244 "parser.y"
                  {(yyval.node) = (yyvsp[0].node);}
#line 1545 "parser.tab.c"
    break;

  case 28: /* FuncFParams: FuncFParam  */
#line 263 "parser.y"
               {
        (yyval.node) = create_ast_node(Node_FuncFParams, "FuncFParams", yylineno);
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 1554 "parser.tab.c"
    break;

  case 29: /* FuncFParams: FuncFParams COMMA FuncFParam  */
#line 267 "parser.y"
                                 {
        (yyval.node) = (yyvsp[-2].node);
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 1563 "parser.tab.c"
    break;

  case 30: /* FuncRParamsOpt: %empty  */
#line 275 "parser.y"
                 {
        (yyval.node) = NULL;
    }
#line 1571 "parser.tab.c"
    break;

  case 31: /* FuncRParamsOpt: FuncRParams  */
#line 278 "parser.y"
                  {(yyval.node) = (yyvsp[0].node);}
#line 1577 "parser.tab.c"
    break;

  case 32: /* FuncRParams: Exp  */
#line 282 "parser.y"
        {
        (yyval.node) = create_ast_node(Node_FuncRParams, "FuncRParams", yylineno);
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 1586 "parser.tab.c"
    break;

  case 33: /* FuncRParams: FuncRParams COMMA Exp  */
#line 286 "parser.y"
                          {
        (yyval.node) = (yyvsp[-2].node);
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 1595 "parser.tab.c"
    break;

  case 34: /* FuncFParam: BType ID  */
#line 293 "parser.y"
             {
        (yyval.node) = create_ast_node(Node_FuncFParam, "FuncFParam", yylineno);
        add_child((yyval.node), (yyvsp[-1].node));
        add_child((yyval.node), create_token_node(ID, "Ident", (yyvsp[0].str)));
    }
#line 1605 "parser.tab.c"
    break;

  case 35: /* FuncFParam: BType ID LBRACKET RBRACKET FuncFParamDims  */
#line 298 "parser.y"
                                              {
        (yyval.node) = create_ast_node(Node_FuncFParam, "FuncFParam", yylineno);
        add_child((yyval.node), (yyvsp[-4].node));
        add_child((yyval.node), create_token_node(ID, "Ident", (yyvsp[-3].str)));
        add_child((yyval.node), create_token_node(LBRACKET, "LBRACKET", (yyvsp[-2].str)));
        add_child((yyval.node), create_token_node(RBRACKET, "RBRACKET", (yyvsp[-1].str)));
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 1618 "parser.tab.c"
    break;

  case 36: /* FuncFParamDims: LBRACKET RBRACKET  */
#line 308 "parser.y"
                      {
        (yyval.node) = create_ast_node(Node_FuncFParamDims, "FuncFParamDims", yylineno);
        add_child((yyval.node), create_token_node(LBRACKET, "LBRACKET", (yyvsp[-1].str)));
        add_child((yyval.node), create_token_node(RBRACKET, "RBRACKET", (yyvsp[0].str)));
    }
#line 1628 "parser.tab.c"
    break;

  case 37: /* FuncFParamDims: FuncFParamDims LBRACKET RBRACKET  */
#line 313 "parser.y"
                                       {
        (yyval.node) = (yyvsp[-2].node);
        add_child((yyval.node), create_token_node(LBRACKET, "LBRACKET", (yyvsp[-1].str)));
        add_child((yyval.node), create_token_node(RBRACKET, "RBRACKET", (yyvsp[0].str)));
    }
#line 1638 "parser.tab.c"
    break;

  case 38: /* Block: LBRACE BlockItem_list RBRACE  */
#line 320 "parser.y"
                                 {
        (yyval.node) = create_ast_node(Node_Block, "Block", 2);
        add_child((yyval.node), create_token_node(LBRACE, "LBRACE", (yyvsp[-2].str)));
        // 直接将BlockItem_list的子节点添加到Block中
        if ((yyvsp[-1].node) && (yyvsp[-1].node)->child_count > 0) {
            for (int i = 0; i < (yyvsp[-1].node)->child_count; i++) {
                add_child((yyval.node), (yyvsp[-1].node)->children[i]);
            }
        }
        add_child((yyval.node), create_token_node(RBRACE, "RBRACE", (yyvsp[0].str)));
    }
#line 1654 "parser.tab.c"
    break;

  case 39: /* BlockItem_list: %empty  */
#line 334 "parser.y"
                {
        (yyval.node) = create_ast_node(Node_BlockItem, "BlockItem_list", yylineno);
        (yyval.node)->is_epsilon = 1;
    }
#line 1663 "parser.tab.c"
    break;

  case 40: /* BlockItem_list: BlockItem_list BlockItem  */
#line 338 "parser.y"
                               {
        (yyval.node) = (yyvsp[-1].node);
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 1672 "parser.tab.c"
    break;

  case 41: /* BlockItem: Decl  */
#line 345 "parser.y"
         {
        (yyval.node) = create_ast_node(Node_BlockItem, "BlockItem", 3);
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 1681 "parser.tab.c"
    break;

  case 42: /* BlockItem: Stmt  */
#line 349 "parser.y"
           {
        (yyval.node) = create_ast_node(Node_BlockItem, "BlockItem", 4);
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 1690 "parser.tab.c"
    break;

  case 43: /* BlockItem: error SEMICN  */
#line 353 "parser.y"
                   {  // 错误恢复：跳过错误的语句直到分号
        // Bison 错误恢复会读取多个 token，导致 yylineno 推进多行
        // 对于缺少分号的错误，通常是前两行的某处，这里回溯2行
        int error_line = yylineno >= 2 ? yylineno - 2 : yylineno;
        // 确保不会回到第0行或负数
        if (error_line < 1) error_line = 1;
        add_syntax_error(error_line, "Missing \";\"");
        (yyval.node) = create_ast_node(Node_BlockItem, "BlockItem", error_line);
        yyerrok;  // 恢复解析状态
    }
#line 1705 "parser.tab.c"
    break;

  case 44: /* Stmt: LVal ASSIGN Exp SEMICN  */
#line 366 "parser.y"
                           {
        int stmt_line = ((yyvsp[-3].node) && (yyvsp[-3].node)->line > 0) ? (yyvsp[-3].node)->line : yylineno;
        (yyval.node) = create_ast_node(Node_Stmt, "Stmt", stmt_line);
        add_child((yyval.node), (yyvsp[-3].node));
        add_child((yyval.node), create_token_node(ASSIGN, "ASSIGN", (yyvsp[-2].str)));
        add_child((yyval.node), (yyvsp[-1].node));
        add_child((yyval.node), create_token_node(SEMICN, "SEMICN", (yyvsp[0].str)));
    }
#line 1718 "parser.tab.c"
    break;

  case 45: /* Stmt: LVal ASSIGN Exp ELSETK  */
#line 374 "parser.y"
                             {  // 缺少分号，后面跟 else
        // 关键：使用 LVal 的行号（第1个符号），而不是当前 yylineno
        // 因为当解析器看到 else 时，yylineno 已经推进了
        int error_line = ((yyvsp[-3].node) && (yyvsp[-3].node)->line > 0) ? (yyvsp[-3].node)->line : yylineno;
        add_syntax_error(error_line, "Missing \";\"");
        (yyval.node) = create_ast_node(Node_Stmt, "Stmt", error_line);
        add_child((yyval.node), (yyvsp[-3].node));
        add_child((yyval.node), create_token_node(ASSIGN, "ASSIGN", (yyvsp[-2].str)));
        add_child((yyval.node), (yyvsp[-1].node));
        yyerrok;  // 恢复错误状态，继续解析
    }
#line 1734 "parser.tab.c"
    break;

  case 46: /* Stmt: Exp SEMICN  */
#line 386 "parser.y"
                 {
        int stmt_line = ((yyvsp[-1].node) && (yyvsp[-1].node)->line > 0) ? (yyvsp[-1].node)->line : yylineno;
        (yyval.node) = create_ast_node(Node_Stmt, "Stmt", stmt_line);
        add_child((yyval.node), (yyvsp[-1].node));
        add_child((yyval.node), create_token_node(SEMICN, "SEMICN", (yyvsp[0].str)));
    }
#line 1745 "parser.tab.c"
    break;

  case 47: /* Stmt: Exp error  */
#line 392 "parser.y"
                {  // 通用的错误恢复：表达式语句缺少分号
        // 使用表达式的行号而不是当前 yylineno（已推进）
        int error_line = ((yyvsp[-1].node) && (yyvsp[-1].node)->line > 0) ? (yyvsp[-1].node)->line : yylineno;
        add_syntax_error(error_line, "Missing \";\"");
        (yyval.node) = create_ast_node(Node_Stmt, "Stmt", error_line);
        add_child((yyval.node), (yyvsp[-1].node));
        yyerrok;  // 恢复解析状态
    }
#line 1758 "parser.tab.c"
    break;

  case 48: /* Stmt: LVal ASSIGN Exp error  */
#line 400 "parser.y"
                            {  // 通用的错误恢复：缺少分号
        // 使用 LVal 的行号（最开始解析该语句时的行号）
        int error_line = ((yyvsp[-3].node) && (yyvsp[-3].node)->line > 0) ? (yyvsp[-3].node)->line : yylineno;
        add_syntax_error(error_line, "Missing \";\"");
        (yyval.node) = create_ast_node(Node_Stmt, "Stmt", error_line);
        add_child((yyval.node), (yyvsp[-3].node));
        add_child((yyval.node),create_token_node(ASSIGN, "ASSIGN", (yyvsp[-2].str)));
        add_child((yyval.node), (yyvsp[-1].node));
        yyerrok;  // 恢复错误状态，继续解析
    }
#line 1773 "parser.tab.c"
    break;

  case 49: /* Stmt: SEMICN  */
#line 410 "parser.y"
             {
        (yyval.node) = create_ast_node(Node_Stmt, "Stmt", yylineno);
        add_child((yyval.node), create_token_node(SEMICN, "SEMICN", (yyvsp[0].str)));
    }
#line 1782 "parser.tab.c"
    break;

  case 50: /* Stmt: Block  */
#line 414 "parser.y"
            {
        (yyval.node) = create_ast_node(Node_Stmt, "Stmt", yylineno);
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 1791 "parser.tab.c"
    break;

  case 51: /* Stmt: IFTK LPARENT Cond RPARENT Stmt  */
#line 419 "parser.y"
                                     {
        (yyval.node) = create_ast_node(Node_Stmt, "Stmt", yylineno);
        add_child((yyval.node), create_token_node(IFTK, "IFTK", (yyvsp[-4].str)));
        add_child((yyval.node), create_token_node(LPARENT, "LPARENT", (yyvsp[-3].str)));
        add_child((yyval.node), (yyvsp[-2].node));
        add_child((yyval.node), create_token_node(RPARENT, "RPARENT", (yyvsp[-1].str)));
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 1804 "parser.tab.c"
    break;

  case 52: /* Stmt: IFTK LPARENT Cond RPARENT Stmt ELSETK Stmt  */
#line 427 "parser.y"
                                                 {
        (yyval.node) = create_ast_node(Node_Stmt, "Stmt", yylineno);
        add_child((yyval.node), create_token_node(IFTK, "IFTK", (yyvsp[-6].str)));
        add_child((yyval.node), create_token_node(LPARENT, "LPARENT", (yyvsp[-5].str)));
        add_child((yyval.node), (yyvsp[-4].node));
        add_child((yyval.node), create_token_node(RPARENT, "RPARENT", (yyvsp[-3].str)));
        add_child((yyval.node), (yyvsp[-2].node));
        add_child((yyval.node), create_token_node(ELSETK, "ELSETK", (yyvsp[-1].str)));
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 1819 "parser.tab.c"
    break;

  case 53: /* Stmt: WHILETK LPARENT Cond RPARENT Stmt  */
#line 437 "parser.y"
                                        {
        (yyval.node) = create_ast_node(Node_Stmt, "Stmt", yylineno);
        add_child((yyval.node), create_token_node(WHILETK, "WHILETK", (yyvsp[-4].str)));
        add_child((yyval.node), create_token_node(LPARENT, "LPARENT", (yyvsp[-3].str)));
        add_child((yyval.node), (yyvsp[-2].node));
        add_child((yyval.node), create_token_node(RPARENT, "RPARENT", (yyvsp[-1].str)));
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 1832 "parser.tab.c"
    break;

  case 54: /* Stmt: BREAKTK SEMICN  */
#line 445 "parser.y"
                     {
        (yyval.node) = create_ast_node(Node_Stmt, "Stmt", yylineno);
        add_child((yyval.node), create_token_node(BREAKTK, "BREAKTK", (yyvsp[-1].str)));
        add_child((yyval.node), create_token_node(SEMICN, "SEMICN", (yyvsp[0].str)));
    }
#line 1842 "parser.tab.c"
    break;

  case 55: /* Stmt: CONTINUETK SEMICN  */
#line 450 "parser.y"
                        {
        (yyval.node) = create_ast_node(Node_Stmt, "Stmt", yylineno);
        add_child((yyval.node), create_token_node(CONTINUETK, "CONTINUETK", (yyvsp[-1].str)));
        add_child((yyval.node), create_token_node(SEMICN, "SEMICN", (yyvsp[0].str)));
    }
#line 1852 "parser.tab.c"
    break;

  case 56: /* Stmt: RETURNTK SEMICN  */
#line 455 "parser.y"
                      {
        (yyval.node) = create_ast_node(Node_Stmt, "Stmt", yylineno);
        add_child((yyval.node), create_token_node(RETURNTK, "RETURNTK", (yyvsp[-1].str)));
        add_child((yyval.node), create_token_node(SEMICN, "SEMICN", (yyvsp[0].str)));
    }
#line 1862 "parser.tab.c"
    break;

  case 57: /* Stmt: RETURNTK Exp SEMICN  */
#line 460 "parser.y"
                          {
        (yyval.node) = create_ast_node(Node_Stmt, "Stmt", yylineno);
        add_child((yyval.node), create_token_node(RETURNTK, "RETURNTK", (yyvsp[-2].str)));
        add_child((yyval.node), (yyvsp[-1].node));
        add_child((yyval.node), create_token_node(SEMICN, "SEMICN", (yyvsp[0].str)));
    }
#line 1873 "parser.tab.c"
    break;

  case 58: /* Exp: AddExp  */
#line 469 "parser.y"
           {
        (yyval.node) = create_ast_node(Node_Exp, "Exp", yylineno);
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 1882 "parser.tab.c"
    break;

  case 59: /* Cond: LOrExp  */
#line 476 "parser.y"
           {
        (yyval.node) = create_ast_node(Node_Cond, "Cond", yylineno);
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 1891 "parser.tab.c"
    break;

  case 60: /* LVal: ID  */
#line 483 "parser.y"
       {
        (yyval.node) = create_ast_node(Node_LVal, "LVal", yylineno);
        add_child((yyval.node), create_token_node(ID, "Ident", (yyvsp[0].str)));
    }
#line 1900 "parser.tab.c"
    break;

  case 61: /* LVal: ID LBRACKET Exp RBRACKET  */
#line 487 "parser.y"
                               {
        (yyval.node) = create_ast_node(Node_LVal, "LVal", yylineno);
        add_child((yyval.node), create_token_node(ID, "ID", (yyvsp[-3].str)));
        add_child((yyval.node), create_token_node(LBRACKET, "LBRACKET", (yyvsp[-2].str)));
        add_child((yyval.node), (yyvsp[-1].node));
        add_child((yyval.node), create_token_node(RBRACKET, "RBRACKET", (yyvsp[0].str)));
    }
#line 1912 "parser.tab.c"
    break;

  case 62: /* LVal: ID LBRACKET Exp COMMA Exp RBRACKET error  */
#line 494 "parser.y"
                                              {  // 错误：a[5,3] 应该是 a[5][3]
    int err_line = yylineno;  // 这里依然用当前行号
        add_syntax_error(err_line, "Missing \"]\"");
        (yyval.node) = create_ast_node(Node_LVal, "LVal", yylineno);
        add_child((yyval.node), create_token_node(ID, "ID", (yyvsp[-6].str)));
        add_child((yyval.node), create_token_node(LBRACKET, "LBRACKET", (yyvsp[-5].str)));
        add_child((yyval.node), (yyvsp[-4].node));
        add_child((yyval.node), create_token_node(COMMA, "COMMA", (yyvsp[-3].str)));
        add_child((yyval.node), (yyvsp[-2].node));
        add_child((yyval.node), create_token_node(RBRACKET, "RBRACKET", (yyvsp[-1].str)));
        yyerrok;  // 恢复错误状态，继续解析
    }
#line 1929 "parser.tab.c"
    break;

  case 63: /* PrimaryExp: LPARENT Exp RPARENT  */
#line 509 "parser.y"
                        {
        (yyval.node) = create_ast_node(Node_PrimaryExp, "PrimaryExp", yylineno);
        add_child((yyval.node), create_token_node(LPARENT, "LPARENT", (yyvsp[-2].str)));
        add_child((yyval.node), (yyvsp[-1].node));
        add_child((yyval.node), create_token_node(RPARENT, "RPARENT", (yyvsp[0].str)));
    }
#line 1940 "parser.tab.c"
    break;

  case 64: /* PrimaryExp: LVal  */
#line 515 "parser.y"
           {
        (yyval.node) = create_ast_node(Node_PrimaryExp, "PrimaryExp", yylineno);
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 1949 "parser.tab.c"
    break;

  case 65: /* PrimaryExp: Number  */
#line 519 "parser.y"
             {
        (yyval.node) = create_ast_node(Node_PrimaryExp, "PrimaryExp", yylineno);
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 1958 "parser.tab.c"
    break;

  case 66: /* Number: INTCON  */
#line 526 "parser.y"
           {
        (yyval.node) = create_ast_node(Node_Number, "Number", yylineno);
                char buf[32];
        sprintf(buf, "%d", (yyvsp[0].intval));   // ⭐ int → string
        add_child((yyval.node), create_token_node(INTCON, "INTCON", buf));
    }
#line 1969 "parser.tab.c"
    break;

  case 67: /* Number: FLOATCON  */
#line 532 "parser.y"
               {
        (yyval.node) = create_ast_node(Node_Number, "Number", yylineno);
        add_child((yyval.node), create_token_node(FLOATCON, "FLOATCON", (yyvsp[0].str)));
    }
#line 1978 "parser.tab.c"
    break;

  case 68: /* UnaryExp: PrimaryExp  */
#line 540 "parser.y"
               {
        (yyval.node) = create_ast_node(Node_UnaryExp, "UnaryExp", yylineno);
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 1987 "parser.tab.c"
    break;

  case 69: /* UnaryExp: ID LPARENT FuncRParamsOpt RPARENT  */
#line 544 "parser.y"
                                        {
        (yyval.node) = create_ast_node(Node_UnaryExp, "UnaryExp", yylineno);
        add_child((yyval.node), create_token_node(ID, "ID", (yyvsp[-3].str)));
        add_child((yyval.node), create_token_node(LPARENT, "LPARENT", (yyvsp[-2].str)));
        if ((yyvsp[-1].node)) add_child((yyval.node), (yyvsp[-1].node));
        add_child((yyval.node), create_token_node(RPARENT, "RPARENT", (yyvsp[0].str)));
    }
#line 1999 "parser.tab.c"
    break;

  case 70: /* UnaryExp: UnaryOp UnaryExp  */
#line 551 "parser.y"
                       {
        (yyval.node) = create_ast_node(Node_UnaryExp, "UnaryExp", yylineno);
        add_child((yyval.node), (yyvsp[-1].node));
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 2009 "parser.tab.c"
    break;

  case 71: /* UnaryOp: PLUS  */
#line 559 "parser.y"
         {
        (yyval.node) = create_ast_node(Node_UnaryOp, "UnaryOp", yylineno);
        add_child((yyval.node), create_token_node(PLUS, "PLUS", (yyvsp[0].str)));
    }
#line 2018 "parser.tab.c"
    break;

  case 72: /* UnaryOp: MINUS  */
#line 563 "parser.y"
            {
        (yyval.node) = create_ast_node(Node_UnaryOp, "UnaryOp", yylineno);
        add_child((yyval.node), create_token_node(MINUS, "MINUS", (yyvsp[0].str)));
    }
#line 2027 "parser.tab.c"
    break;

  case 73: /* UnaryOp: NOT  */
#line 567 "parser.y"
          {
        (yyval.node) = create_ast_node(Node_UnaryOp, "UnaryOp", yylineno);
        add_child((yyval.node), create_token_node(NOT, "NOT", (yyvsp[0].str)));
    }
#line 2036 "parser.tab.c"
    break;

  case 74: /* MulExp: UnaryExp  */
#line 574 "parser.y"
             {
        (yyval.node) = create_ast_node(Node_MulExp, "MulExp", yylineno);
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 2045 "parser.tab.c"
    break;

  case 75: /* MulExp: MulExp MUL UnaryExp  */
#line 578 "parser.y"
                          {
        (yyval.node) = create_ast_node(Node_MulExp, "MulExp", yylineno);
        add_child((yyval.node), (yyvsp[-2].node));
        add_child((yyval.node), create_token_node(MUL, "MUL", (yyvsp[-1].str)));
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 2056 "parser.tab.c"
    break;

  case 76: /* MulExp: MulExp DIV UnaryExp  */
#line 584 "parser.y"
                          {
        (yyval.node) = create_ast_node(Node_MulExp, "MulExp", yylineno);
        add_child((yyval.node), (yyvsp[-2].node));
        add_child((yyval.node), create_token_node(DIV, "DIV", (yyvsp[-1].str)));
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 2067 "parser.tab.c"
    break;

  case 77: /* MulExp: MulExp MOD UnaryExp  */
#line 590 "parser.y"
                          {
        (yyval.node) = create_ast_node(Node_MulExp, "MulExp", yylineno);
        add_child((yyval.node), (yyvsp[-2].node));
        add_child((yyval.node), create_token_node(MOD, "MOD", (yyvsp[-1].str)));
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 2078 "parser.tab.c"
    break;

  case 78: /* AddExp: MulExp  */
#line 599 "parser.y"
           {
        (yyval.node) = create_ast_node(Node_AddExp, "AddExp", yylineno);
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 2087 "parser.tab.c"
    break;

  case 79: /* AddExp: AddExp PLUS MulExp  */
#line 603 "parser.y"
                         {
        (yyval.node) = create_ast_node(Node_AddExp, "AddExp", yylineno);
        add_child((yyval.node), (yyvsp[-2].node));
        add_child((yyval.node), create_token_node(PLUS, "PLUS", (yyvsp[-1].str)));
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 2098 "parser.tab.c"
    break;

  case 80: /* AddExp: AddExp MINUS MulExp  */
#line 609 "parser.y"
                          {
        (yyval.node) = create_ast_node(Node_AddExp, "AddExp", yylineno);
        add_child((yyval.node), (yyvsp[-2].node));
        add_child((yyval.node), create_token_node(MINUS, "MINUS", (yyvsp[-1].str)));
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 2109 "parser.tab.c"
    break;

  case 81: /* RelExp: AddExp  */
#line 618 "parser.y"
           {
        (yyval.node) = create_ast_node(Node_RelExp, "RelExp", yylineno);
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 2118 "parser.tab.c"
    break;

  case 82: /* RelExp: RelExp LT AddExp  */
#line 622 "parser.y"
                       {
        (yyval.node) = create_ast_node(Node_RelExp, "RelExp", yylineno);
        add_child((yyval.node), (yyvsp[-2].node));
        add_child((yyval.node), create_token_node(LT, "LT", (yyvsp[-1].str)));
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 2129 "parser.tab.c"
    break;

  case 83: /* RelExp: RelExp GT AddExp  */
#line 628 "parser.y"
                       {
        (yyval.node) = create_ast_node(Node_RelExp, "RelExp", yylineno);
        add_child((yyval.node), (yyvsp[-2].node));
        add_child((yyval.node), create_token_node(GT, "GT", (yyvsp[-1].str)));
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 2140 "parser.tab.c"
    break;

  case 84: /* RelExp: RelExp LEQ AddExp  */
#line 634 "parser.y"
                        {
        (yyval.node) = create_ast_node(Node_RelExp, "RelExp", yylineno);
        add_child((yyval.node), (yyvsp[-2].node));
        add_child((yyval.node), create_token_node(LEQ, "LEQ", (yyvsp[-1].str)));
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 2151 "parser.tab.c"
    break;

  case 85: /* RelExp: RelExp GEQ AddExp  */
#line 640 "parser.y"
                        {
        (yyval.node) = create_ast_node(Node_RelExp, "RelExp", yylineno);
        add_child((yyval.node), (yyvsp[-2].node));
        add_child((yyval.node), create_token_node(GEQ, "GEQ", (yyvsp[-1].str)));
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 2162 "parser.tab.c"
    break;

  case 86: /* EqExp: RelExp  */
#line 649 "parser.y"
           {
        (yyval.node) = create_ast_node(Node_EqExp, "EqExp", yylineno);
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 2171 "parser.tab.c"
    break;

  case 87: /* EqExp: EqExp EQ RelExp  */
#line 653 "parser.y"
                      {
        (yyval.node) = create_ast_node(Node_EqExp, "EqExp", yylineno);
        add_child((yyval.node), (yyvsp[-2].node));
        add_child((yyval.node), create_token_node(EQ, "EQ", (yyvsp[-1].str)));
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 2182 "parser.tab.c"
    break;

  case 88: /* EqExp: EqExp NEQ RelExp  */
#line 659 "parser.y"
                       {
        (yyval.node) = create_ast_node(Node_EqExp, "EqExp", yylineno);
        add_child((yyval.node), (yyvsp[-2].node));
        add_child((yyval.node), create_token_node(NEQ, "NEQ", (yyvsp[-1].str)));
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 2193 "parser.tab.c"
    break;

  case 89: /* LAndExp: EqExp  */
#line 668 "parser.y"
          {
        (yyval.node) = create_ast_node(Node_LAndExp, "LAndExp", yylineno);
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 2202 "parser.tab.c"
    break;

  case 90: /* LAndExp: LAndExp AND EqExp  */
#line 672 "parser.y"
                        {
        (yyval.node) = create_ast_node(Node_LAndExp, "LAndExp", yylineno);
        add_child((yyval.node), (yyvsp[-2].node));
        add_child((yyval.node), create_token_node(AND, "AND", (yyvsp[-1].str)));
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 2213 "parser.tab.c"
    break;

  case 91: /* LOrExp: LAndExp  */
#line 681 "parser.y"
            {
        (yyval.node) = create_ast_node(Node_LOrExp, "LOrExp", yylineno);
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 2222 "parser.tab.c"
    break;

  case 92: /* LOrExp: LOrExp OR LAndExp  */
#line 685 "parser.y"
                        {
        (yyval.node) = create_ast_node(Node_LOrExp, "LOrExp", yylineno);
        add_child((yyval.node), (yyvsp[-2].node));
        add_child((yyval.node), create_token_node(OR, "OR", (yyvsp[-1].str)));
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 2233 "parser.tab.c"
    break;

  case 93: /* ConstExp: AddExp  */
#line 694 "parser.y"
           {
        (yyval.node) = create_ast_node(Node_ConstExp, "ConstExp", yylineno);
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 2242 "parser.tab.c"
    break;


#line 2246 "parser.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 700 "parser.y"


//C代码部分
ASTNode* create_ast_node(NodeType type, const char* name, int line) {
    ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
    node->type = type;
    strcpy(node->name, name);
    node->line = line;
    node->token_type = 0; // non-terminal by default
    node->value[0] = '\0';
    node->children = NULL;
    node->child_count = 0;
    node->is_epsilon = 0;
    node->data_type = 0;      // 默认int类型
    node->is_array = 0;
    node->array_dims = 0;
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
    node->data_type = 0;
    node->is_array = 0;
    node->array_dims = 0;
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
        printf(" ");
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
        } else if (node->token_type == PLUS) {
            printf(":+");
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
    // 禁用Bison的默认错误处理，避免重复报告
    // 我们已经在规则中手动处理了错误
}
void add_syntax_error(int line, const char *msg) {
    if (syntax_error_count < MAX_ERRORS) {
        char full_msg[100];
        snprintf(full_msg, sizeof(full_msg), "Error type B at Line %d: %s", line, msg);
        
        // 确保错误信息不重复
        for (int i = 0; i < syntax_error_count; i++) {
            if (syntax_error_list[i].line == line &&
                strcmp(syntax_error_list[i].message, full_msg) == 0) {
                return; // 如果相同的错误已经记录，直接跳过
            }
        }
        
        syntax_error_list[syntax_error_count].line = line;
        strcpy(syntax_error_list[syntax_error_count].message, full_msg);
        syntax_error_count++;
        has_error = 1;
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
       // printf("syntax errors:\n");
        for (int i = 0; i < syntax_error_count; i++) {

            fprintf(stderr, "%s\n", syntax_error_list[i].message);
        }
        return 0;
    }

    // 执行语义分析
    if (root) {
        global_scope = create_scope(NULL);
        current_scope = global_scope;
        precollect_functions(root);
        analyze_ast(root);
        
        // 输出语义错误
        if (semantic_error_count > 0) {
            print_semantic_errors();
        } else {
            // 如果没有语义错误，则生成中间代码
            printf("\n语义分析通过，开始生成中间代码...\n");
            generate_ir(root);
            print_ir_code();
            
            // 生成RISC-V汇编代码
            printf("\n开始生成RISC-V汇编代码...\n");
            
            // 生成输出文件名
            char output_filename[256];
            strncpy(output_filename, argv[1], sizeof(output_filename) - 3);
            char *dot = strrchr(output_filename, '.');
            if (dot) {
                strcpy(dot, ".s");
            } else {
                strcat(output_filename, ".s");
            }
            
            FILE *asm_file = fopen(output_filename, "w");
            if (asm_file) {
                generate_riscv(ir_code_head, asm_file);
                fclose(asm_file);
                printf("RISC-V汇编代码已生成: %s\n", output_filename);
            } else {
                fprintf(stderr, "无法创建输出文件: %s\n", output_filename);
            }
        }
    }

    // 调试：打印AST（可选，需要时启用）
    // print_ast(root, 0);
  
    return 0;
}


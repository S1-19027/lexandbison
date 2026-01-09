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
int yylex(void);
void yyerror(const char* s) ;
void add_syntax_error(int line, const char *msg);


#line 102 "parser.tab.c"

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
  YYSYMBOL_PLUS = 15,                      /* PLUS  */
  YYSYMBOL_MINUS = 16,                     /* MINUS  */
  YYSYMBOL_MUL = 17,                       /* MUL  */
  YYSYMBOL_DIV = 18,                       /* DIV  */
  YYSYMBOL_MOD = 19,                       /* MOD  */
  YYSYMBOL_ASSIGN = 20,                    /* ASSIGN  */
  YYSYMBOL_EQ = 21,                        /* EQ  */
  YYSYMBOL_NEQ = 22,                       /* NEQ  */
  YYSYMBOL_LT = 23,                        /* LT  */
  YYSYMBOL_GT = 24,                        /* GT  */
  YYSYMBOL_LEQ = 25,                       /* LEQ  */
  YYSYMBOL_GEQ = 26,                       /* GEQ  */
  YYSYMBOL_AND = 27,                       /* AND  */
  YYSYMBOL_OR = 28,                        /* OR  */
  YYSYMBOL_NOT = 29,                       /* NOT  */
  YYSYMBOL_LPARENT = 30,                   /* LPARENT  */
  YYSYMBOL_RPARENT = 31,                   /* RPARENT  */
  YYSYMBOL_LBRACKET = 32,                  /* LBRACKET  */
  YYSYMBOL_RBRACKET = 33,                  /* RBRACKET  */
  YYSYMBOL_LBRACE = 34,                    /* LBRACE  */
  YYSYMBOL_RBRACE = 35,                    /* RBRACE  */
  YYSYMBOL_SEMICN = 36,                    /* SEMICN  */
  YYSYMBOL_COMMA = 37,                     /* COMMA  */
  YYSYMBOL_ENDFILE = 38,                   /* ENDFILE  */
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
  YYSYMBOL_VarDef = 49,                    /* VarDef  */
  YYSYMBOL_InitVal = 50,                   /* InitVal  */
  YYSYMBOL_FuncFParamsOpt = 51,            /* FuncFParamsOpt  */
  YYSYMBOL_FuncFParams = 52,               /* FuncFParams  */
  YYSYMBOL_FuncRParamsOpt = 53,            /* FuncRParamsOpt  */
  YYSYMBOL_FuncRParams = 54,               /* FuncRParams  */
  YYSYMBOL_FuncFParam = 55,                /* FuncFParam  */
  YYSYMBOL_FuncFParamDims = 56,            /* FuncFParamDims  */
  YYSYMBOL_Block = 57,                     /* Block  */
  YYSYMBOL_BlockItem_list = 58,            /* BlockItem_list  */
  YYSYMBOL_BlockItem = 59,                 /* BlockItem  */
  YYSYMBOL_Stmt = 60,                      /* Stmt  */
  YYSYMBOL_Exp = 61,                       /* Exp  */
  YYSYMBOL_Cond = 62,                      /* Cond  */
  YYSYMBOL_LVal = 63,                      /* LVal  */
  YYSYMBOL_PrimaryExp = 64,                /* PrimaryExp  */
  YYSYMBOL_Number = 65,                    /* Number  */
  YYSYMBOL_UnaryExp = 66,                  /* UnaryExp  */
  YYSYMBOL_UnaryOp = 67,                   /* UnaryOp  */
  YYSYMBOL_MulExp = 68,                    /* MulExp  */
  YYSYMBOL_AddExp = 69,                    /* AddExp  */
  YYSYMBOL_RelExp = 70,                    /* RelExp  */
  YYSYMBOL_EqExp = 71,                     /* EqExp  */
  YYSYMBOL_LAndExp = 72,                   /* LAndExp  */
  YYSYMBOL_LOrExp = 73,                    /* LOrExp  */
  YYSYMBOL_ConstExp = 74                   /* ConstExp  */
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
#define YYLAST   175

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  39
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  36
/* YYNRULES -- Number of rules.  */
#define YYNRULES  86
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  158

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
       0,    72,    72,    78,    82,    90,    99,   108,   117,   121,
     125,   132,   142,   146,   153,   162,   169,   178,   182,   189,
     199,   208,   214,   217,   236,   240,   248,   251,   255,   259,
     266,   271,   281,   286,   293,   302,   306,   314,   318,   325,
     331,   337,   342,   347,   351,   355,   363,   373,   381,   386,
     391,   396,   405,   412,   419,   423,   430,   443,   449,   453,
     460,   470,   474,   481,   489,   493,   497,   504,   508,   514,
     520,   529,   533,   539,   548,   552,   558,   564,   570,   579,
     583,   589,   598,   602,   611,   615,   624
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
  "CONTINUETK", "RETURNTK", "ID", "INTCON", "PLUS", "MINUS", "MUL", "DIV",
  "MOD", "ASSIGN", "EQ", "NEQ", "LT", "GT", "LEQ", "GEQ", "AND", "OR",
  "NOT", "LPARENT", "RPARENT", "LBRACKET", "RBRACKET", "LBRACE", "RBRACE",
  "SEMICN", "COMMA", "ENDFILE", "$accept", "CompUnit", "DeclOrFuncDefList",
  "DeclOrFuncDef", "Decl", "ConstDecl", "BType", "ConstDef",
  "ConstInitVal", "VarDecl", "VarDef", "InitVal", "FuncFParamsOpt",
  "FuncFParams", "FuncRParamsOpt", "FuncRParams", "FuncFParam",
  "FuncFParamDims", "Block", "BlockItem_list", "BlockItem", "Stmt", "Exp",
  "Cond", "LVal", "PrimaryExp", "Number", "UnaryExp", "UnaryOp", "MulExp",
  "AddExp", "RelExp", "EqExp", "LAndExp", "LOrExp", "ConstExp", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-131)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      58,    46,    56,    62,    31,    78,    58,  -131,  -131,  -131,
      74,  -131,    66,    68,    73,  -131,  -131,    79,  -131,  -131,
      20,    86,    31,    31,    31,    85,    87,   103,   103,  -131,
      94,    93,    88,  -131,    95,    96,   103,  -131,    35,  -131,
    -131,  -131,  -131,   103,  -131,  -131,  -131,  -131,  -131,  -131,
     103,    38,    26,    26,    97,    99,   100,    31,   100,   100,
    -131,  -131,   103,   103,    98,  -131,   103,   103,   103,   103,
     103,   104,   102,  -131,  -131,  -131,  -131,  -131,   106,    91,
    -131,   -27,  -131,  -131,  -131,  -131,    38,    38,   103,   107,
       9,  -131,   103,  -131,   103,   105,   108,   110,   113,   114,
     109,   111,    17,  -131,  -131,  -131,  -131,  -131,  -131,   112,
     120,  -131,   116,  -131,  -131,   117,   103,   103,  -131,  -131,
    -131,   115,  -131,   103,  -131,  -131,   121,    26,    48,    69,
     119,   125,   123,  -131,   122,    70,   103,   103,   103,   103,
     103,   103,   103,   103,    70,  -131,   147,    26,    26,    26,
      26,    48,    48,    69,   119,  -131,    70,  -131
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     0,     0,     0,     0,     2,     3,     8,     9,
       0,    10,     0,     0,     0,    12,    13,     0,     1,     4,
      17,     0,    22,    22,    22,     0,     0,     0,     0,    16,
       0,     0,    23,    24,     0,     0,     0,    11,    54,    60,
      64,    65,    66,     0,    20,    21,    58,    61,    59,    67,
       0,    71,    52,    86,     0,    30,     0,     0,     0,     0,
      14,    15,    26,     0,     0,    63,     0,     0,     0,     0,
       0,    18,     0,    35,     6,    25,     7,     5,     0,    27,
      28,     0,    57,    68,    69,    70,    72,    73,     0,     0,
       0,    62,     0,    55,     0,     0,     0,    31,     0,     0,
       0,     0,     0,    34,    43,    37,    44,    36,    38,    42,
      58,    29,     0,    19,    32,     0,     0,     0,    48,    49,
      50,     0,    41,     0,    56,    33,     0,    74,    79,    82,
      84,    53,     0,    51,    40,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    39,    45,    75,    76,    77,
      78,    80,    81,    83,    85,    47,     0,    46
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -131,  -131,  -131,   150,    67,  -131,     3,  -131,  -131,  -131,
    -131,  -131,    71,  -131,  -131,  -131,   118,  -131,    -8,  -131,
    -131,  -130,   -26,    42,   -86,  -131,  -131,   -39,  -131,    32,
     -28,   -20,    18,    19,  -131,   -34
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     5,     6,     7,     8,     9,    30,    26,    60,    11,
      21,    44,    31,    32,    78,    79,    33,    97,   106,    90,
     107,   108,   109,   126,    46,    47,    48,    49,    50,    51,
      52,   128,   129,   130,   131,    54
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      53,    45,    61,    10,   110,   146,    93,    17,    53,    10,
      94,    65,    15,    16,   155,     4,    98,    64,    99,   100,
     101,   102,    38,    39,    40,    41,   157,    83,    84,    85,
      38,    39,    40,    41,    15,    16,    80,    81,    42,    43,
      27,    69,    70,    73,   103,   104,    42,    43,    74,   110,
      76,    77,    28,   120,    95,    66,    67,    68,   110,    12,
      53,     1,     2,     3,     4,    62,   111,    63,   112,    13,
     110,   136,   137,   138,   139,    14,   121,    98,    18,    99,
     100,   101,   102,    38,    39,    40,    41,    20,   127,   127,
     140,   141,    25,    10,    34,    35,    22,   134,    23,    42,
      43,    86,    87,    24,    73,    36,   104,    55,   147,   148,
     149,   150,   127,   127,   127,   127,    38,    39,    40,    41,
     151,   152,    29,    37,    56,    57,    58,    59,    92,    82,
      71,    72,    42,    43,    73,    89,    88,    91,   113,    96,
     123,   114,   115,   116,   117,   118,   142,   119,   122,   124,
     125,   133,   135,   143,   144,   156,    19,   105,   145,   132,
     153,     0,   154,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    75
};

static const yytype_int16 yycheck[] =
{
      28,    27,    36,     0,    90,   135,    33,     4,    36,     6,
      37,    50,     3,     4,   144,     6,     7,    43,     9,    10,
      11,    12,    13,    14,    15,    16,   156,    66,    67,    68,
      13,    14,    15,    16,     3,     4,    62,    63,    29,    30,
      20,    15,    16,    34,    35,    36,    29,    30,    56,   135,
      58,    59,    32,    36,    88,    17,    18,    19,   144,    13,
      88,     3,     4,     5,     6,    30,    92,    32,    94,    13,
     156,    23,    24,    25,    26,    13,   102,     7,     0,     9,
      10,    11,    12,    13,    14,    15,    16,    13,   116,   117,
      21,    22,    13,    90,    23,    24,    30,   123,    30,    29,
      30,    69,    70,    30,    34,    20,    36,    13,   136,   137,
     138,   139,   140,   141,   142,   143,    13,    14,    15,    16,
     140,   141,    36,    36,    31,    37,    31,    31,    37,    31,
      33,    32,    29,    30,    34,    33,    32,    31,    33,    32,
      20,    33,    32,    30,    30,    36,    27,    36,    36,    33,
      33,    36,    31,    28,    31,     8,     6,    90,    36,   117,
     142,    -1,   143,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    57
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,     4,     5,     6,    40,    41,    42,    43,    44,
      45,    48,    13,    13,    13,     3,     4,    45,     0,    42,
      13,    49,    30,    30,    30,    13,    46,    20,    32,    36,
      45,    51,    52,    55,    51,    51,    20,    36,    13,    14,
      15,    16,    29,    30,    50,    61,    63,    64,    65,    66,
      67,    68,    69,    69,    74,    13,    31,    37,    31,    31,
      47,    74,    30,    32,    61,    66,    17,    18,    19,    15,
      16,    33,    32,    34,    57,    55,    57,    57,    53,    54,
      61,    61,    31,    66,    66,    66,    68,    68,    32,    33,
      58,    31,    37,    33,    37,    74,    32,    56,     7,     9,
      10,    11,    12,    35,    36,    43,    57,    59,    60,    61,
      63,    61,    61,    33,    33,    32,    30,    30,    36,    36,
      36,    61,    36,    20,    33,    33,    62,    69,    70,    71,
      72,    73,    62,    36,    61,    31,    23,    24,    25,    26,
      21,    22,    27,    28,    31,    36,    60,    69,    69,    69,
      69,    70,    70,    71,    72,    60,     8,    60
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    39,    40,    41,    41,    42,    42,    42,    42,    43,
      43,    44,    45,    45,    46,    47,    48,    49,    49,    49,
      49,    50,    51,    51,    52,    52,    53,    53,    54,    54,
      55,    55,    56,    56,    57,    58,    58,    59,    59,    60,
      60,    60,    60,    60,    60,    60,    60,    60,    60,    60,
      60,    60,    61,    62,    63,    63,    63,    64,    64,    64,
      65,    66,    66,    66,    67,    67,    67,    68,    68,    68,
      68,    69,    69,    69,    70,    70,    70,    70,    70,    71,
      71,    71,    72,    72,    73,    73,    74
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     1,     2,     6,     6,     6,     1,     1,
       1,     4,     1,     1,     3,     1,     3,     1,     4,     7,
       3,     1,     0,     1,     1,     3,     0,     1,     1,     3,
       2,     5,     2,     3,     3,     0,     2,     1,     1,     4,
       3,     2,     1,     1,     1,     5,     7,     5,     2,     2,
       2,     3,     1,     1,     1,     4,     6,     3,     1,     1,
       1,     1,     4,     2,     1,     1,     1,     1,     3,     3,
       3,     1,     3,     3,     1,     3,     3,     3,     3,     1,
       3,     3,     1,     3,     1,     3,     1
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
#line 72 "parser.y"
                        {
        root = (yyvsp[0].node);
    }
#line 1274 "parser.tab.c"
    break;

  case 3: /* DeclOrFuncDefList: DeclOrFuncDef  */
#line 78 "parser.y"
                    {
        (yyval.node) = create_ast_node(Node_CompUnit, "CompUnit", yylineno);
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 1283 "parser.tab.c"
    break;

  case 4: /* DeclOrFuncDefList: DeclOrFuncDefList DeclOrFuncDef  */
#line 82 "parser.y"
                                      {
        (yyval.node) = (yyvsp[-1].node);
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 1292 "parser.tab.c"
    break;

  case 5: /* DeclOrFuncDef: VOIDTK ID LPARENT FuncFParamsOpt RPARENT Block  */
#line 90 "parser.y"
                                                     {
        (yyval.node) = create_ast_node(Node_FuncDef, "FuncDef", yylineno);
        add_child((yyval.node), create_token_node(VOIDTK, "VOIDTK", (yyvsp[-5].str)));
        add_child((yyval.node), create_token_node(ID, "ID", (yyvsp[-4].str)));
        add_child((yyval.node), create_token_node(LPARENT, "LPARENT", (yyvsp[-3].str)));
         if ((yyvsp[-2].node)) add_child((yyval.node), (yyvsp[-2].node));
        add_child((yyval.node), create_token_node(RPARENT, "RPARENT", (yyvsp[-1].str)));
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 1306 "parser.tab.c"
    break;

  case 6: /* DeclOrFuncDef: INTTK ID LPARENT FuncFParamsOpt RPARENT Block  */
#line 99 "parser.y"
                                                    {
        (yyval.node) = create_ast_node(Node_FuncDef, "FuncDef", yylineno);
        add_child((yyval.node), create_token_node(INTTK, "INTTK", (yyvsp[-5].str)));
        add_child((yyval.node), create_token_node(ID, "ID", (yyvsp[-4].str)));
        add_child((yyval.node), create_token_node(LPARENT, "LPARENT", (yyvsp[-3].str)));
         if ((yyvsp[-2].node)) add_child((yyval.node), (yyvsp[-2].node));
        add_child((yyval.node), create_token_node(RPARENT, "RPARENT", (yyvsp[-1].str)));
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 1320 "parser.tab.c"
    break;

  case 7: /* DeclOrFuncDef: FLOATTK ID LPARENT FuncFParamsOpt RPARENT Block  */
#line 108 "parser.y"
                                                      {
        (yyval.node) = create_ast_node(Node_FuncDef, "FuncDef", yylineno);
        add_child((yyval.node), create_token_node(FLOATTK, "FLOATTK", (yyvsp[-5].str)));
        add_child((yyval.node), create_token_node(ID, "ID", (yyvsp[-4].str)));
        add_child((yyval.node), create_token_node(LPARENT, "LPARENT", (yyvsp[-3].str)));
         if ((yyvsp[-2].node)) add_child((yyval.node), (yyvsp[-2].node));
        add_child((yyval.node), create_token_node(RPARENT, "RPARENT", (yyvsp[-1].str)));
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 1334 "parser.tab.c"
    break;

  case 8: /* DeclOrFuncDef: Decl  */
#line 117 "parser.y"
           { (yyval.node) = (yyvsp[0].node); }
#line 1340 "parser.tab.c"
    break;

  case 9: /* Decl: ConstDecl  */
#line 121 "parser.y"
              {
        (yyval.node) = create_ast_node(Node_Decl, "Decl", yylineno);
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 1349 "parser.tab.c"
    break;

  case 10: /* Decl: VarDecl  */
#line 125 "parser.y"
              {
        (yyval.node) = create_ast_node(Node_Decl, "Decl", yylineno);
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 1358 "parser.tab.c"
    break;

  case 11: /* ConstDecl: CONSTTK BType ConstDef SEMICN  */
#line 132 "parser.y"
                                  {
        (yyval.node) = create_ast_node(Node_ConstDecl, "ConstDecl", yylineno);
        add_child((yyval.node), create_token_node(CONSTTK, "CONSTTK", (yyvsp[-3].str)));
        add_child((yyval.node), (yyvsp[-2].node));
        add_child((yyval.node), (yyvsp[-1].node));
        add_child((yyval.node), create_token_node(SEMICN, "SEMICN", (yyvsp[0].str)));
    }
#line 1370 "parser.tab.c"
    break;

  case 12: /* BType: INTTK  */
#line 142 "parser.y"
          {
        (yyval.node) = create_ast_node(Node_BType, "BType", yylineno);
        add_child((yyval.node), create_token_node(INTTK, "INTTK", (yyvsp[0].str)));
    }
#line 1379 "parser.tab.c"
    break;

  case 13: /* BType: FLOATTK  */
#line 146 "parser.y"
              {
        (yyval.node) = create_ast_node(Node_BType, "BType", yylineno);
        add_child((yyval.node), create_token_node(FLOATTK, "FLOATTK", (yyvsp[0].str)));
    }
#line 1388 "parser.tab.c"
    break;

  case 14: /* ConstDef: ID ASSIGN ConstInitVal  */
#line 153 "parser.y"
                           {
        (yyval.node) = create_ast_node(Node_ConstDef, "ConstDef", yylineno);
        add_child((yyval.node), create_token_node(ID, "ID", (yyvsp[-2].str)));
        add_child((yyval.node), create_token_node(ASSIGN, "ASSIGN", (yyvsp[-1].str)));
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 1399 "parser.tab.c"
    break;

  case 15: /* ConstInitVal: ConstExp  */
#line 162 "parser.y"
             {
        (yyval.node) = create_ast_node(Node_ConstInitVal, "ConstInitVal", yylineno);
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 1408 "parser.tab.c"
    break;

  case 16: /* VarDecl: BType VarDef SEMICN  */
#line 169 "parser.y"
                        {
        (yyval.node) = create_ast_node(Node_VarDecl, "VarDecl", yylineno);
        add_child((yyval.node), (yyvsp[-2].node));
        add_child((yyval.node), (yyvsp[-1].node));
        add_child((yyval.node), create_token_node(SEMICN, "SEMICN", (yyvsp[0].str)));
    }
#line 1419 "parser.tab.c"
    break;

  case 17: /* VarDef: ID  */
#line 178 "parser.y"
       {
        (yyval.node) = create_ast_node(Node_VarDef, "VarDef", yylineno);
        add_child((yyval.node), create_token_node(ID, "ID", (yyvsp[0].str)));
    }
#line 1428 "parser.tab.c"
    break;

  case 18: /* VarDef: ID LBRACKET ConstExp RBRACKET  */
#line 182 "parser.y"
                                    {
        (yyval.node) = create_ast_node(Node_VarDef, "VarDef", yylineno);
        add_child((yyval.node), create_token_node(ID, "ID", (yyvsp[-3].str)));
        add_child((yyval.node), create_token_node(LBRACKET, "LBRACKET", (yyvsp[-2].str)));
        add_child((yyval.node), (yyvsp[-1].node));
        add_child((yyval.node), create_token_node(RBRACKET, "RBRACKET", (yyvsp[0].str)));
    }
#line 1440 "parser.tab.c"
    break;

  case 19: /* VarDef: ID LBRACKET ConstExp RBRACKET LBRACKET ConstExp RBRACKET  */
#line 189 "parser.y"
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
#line 1455 "parser.tab.c"
    break;

  case 20: /* VarDef: ID ASSIGN InitVal  */
#line 199 "parser.y"
                        {
        (yyval.node) = create_ast_node(Node_VarDef, "VarDef", yylineno);
        add_child((yyval.node), create_token_node(ID, "ID", (yyvsp[-2].str)));
        add_child((yyval.node), create_token_node(ASSIGN, "ASSIGN", (yyvsp[-1].str)));
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 1466 "parser.tab.c"
    break;

  case 21: /* InitVal: Exp  */
#line 208 "parser.y"
        {
        (yyval.node) = create_ast_node(Node_InitVal, "InitVal", yylineno);
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 1475 "parser.tab.c"
    break;

  case 22: /* FuncFParamsOpt: %empty  */
#line 214 "parser.y"
                 {
        (yyval.node) = NULL;
    }
#line 1483 "parser.tab.c"
    break;

  case 23: /* FuncFParamsOpt: FuncFParams  */
#line 217 "parser.y"
                  {(yyval.node) = (yyvsp[0].node);}
#line 1489 "parser.tab.c"
    break;

  case 24: /* FuncFParams: FuncFParam  */
#line 236 "parser.y"
               {
        (yyval.node) = create_ast_node(Node_FuncFParams, "FuncFParams", yylineno);
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 1498 "parser.tab.c"
    break;

  case 25: /* FuncFParams: FuncFParams COMMA FuncFParam  */
#line 240 "parser.y"
                                 {
        (yyval.node) = (yyvsp[-2].node);
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 1507 "parser.tab.c"
    break;

  case 26: /* FuncRParamsOpt: %empty  */
#line 248 "parser.y"
                 {
        (yyval.node) = NULL;
    }
#line 1515 "parser.tab.c"
    break;

  case 27: /* FuncRParamsOpt: FuncRParams  */
#line 251 "parser.y"
                  {(yyval.node) = (yyvsp[0].node);}
#line 1521 "parser.tab.c"
    break;

  case 28: /* FuncRParams: Exp  */
#line 255 "parser.y"
        {
        (yyval.node) = create_ast_node(Node_FuncRParams, "FuncRParams", yylineno);
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 1530 "parser.tab.c"
    break;

  case 29: /* FuncRParams: FuncRParams COMMA Exp  */
#line 259 "parser.y"
                          {
        (yyval.node) = (yyvsp[-2].node);
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 1539 "parser.tab.c"
    break;

  case 30: /* FuncFParam: BType ID  */
#line 266 "parser.y"
             {
        (yyval.node) = create_ast_node(Node_FuncFParam, "FuncFParam", yylineno);
        add_child((yyval.node), (yyvsp[-1].node));
        add_child((yyval.node), create_token_node(ID, "Ident", (yyvsp[0].str)));
    }
#line 1549 "parser.tab.c"
    break;

  case 31: /* FuncFParam: BType ID LBRACKET RBRACKET FuncFParamDims  */
#line 271 "parser.y"
                                              {
        (yyval.node) = create_ast_node(Node_FuncFParam, "FuncFParam", yylineno);
        add_child((yyval.node), (yyvsp[-4].node));
        add_child((yyval.node), create_token_node(ID, "Ident", (yyvsp[-3].str)));
        add_child((yyval.node), create_token_node(LBRACKET, "LBRACKET", (yyvsp[-2].str)));
        add_child((yyval.node), create_token_node(RBRACKET, "RBRACKET", (yyvsp[-1].str)));
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 1562 "parser.tab.c"
    break;

  case 32: /* FuncFParamDims: LBRACKET RBRACKET  */
#line 281 "parser.y"
                      {
        (yyval.node) = create_ast_node(Node_FuncFParamDims, "FuncFParamDims", yylineno);
        add_child((yyval.node), create_token_node(LBRACKET, "LBRACKET", (yyvsp[-1].str)));
        add_child((yyval.node), create_token_node(RBRACKET, "RBRACKET", (yyvsp[0].str)));
    }
#line 1572 "parser.tab.c"
    break;

  case 33: /* FuncFParamDims: FuncFParamDims LBRACKET RBRACKET  */
#line 286 "parser.y"
                                       {
        (yyval.node) = (yyvsp[-2].node);
        add_child((yyval.node), create_token_node(LBRACKET, "LBRACKET", (yyvsp[-1].str)));
        add_child((yyval.node), create_token_node(RBRACKET, "RBRACKET", (yyvsp[0].str)));
    }
#line 1582 "parser.tab.c"
    break;

  case 34: /* Block: LBRACE BlockItem_list RBRACE  */
#line 293 "parser.y"
                                 {
        (yyval.node) = create_ast_node(Node_Block, "Block", yylineno);
        add_child((yyval.node), create_token_node(LBRACE, "LBRACE", (yyvsp[-2].str)));
        add_child((yyval.node), (yyvsp[-1].node));
        add_child((yyval.node), create_token_node(RBRACE, "RBRACE", (yyvsp[0].str)));
    }
#line 1593 "parser.tab.c"
    break;

  case 35: /* BlockItem_list: %empty  */
#line 302 "parser.y"
                {
        (yyval.node) = create_ast_node(Node_BlockItem, "BlockItem_list", yylineno);
        (yyval.node)->is_epsilon = 1;
    }
#line 1602 "parser.tab.c"
    break;

  case 36: /* BlockItem_list: BlockItem_list BlockItem  */
#line 306 "parser.y"
                               {
        (yyval.node) = create_ast_node(Node_BlockItem, "BlockItem_list", yylineno);
        add_child((yyval.node), (yyvsp[-1].node));
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 1612 "parser.tab.c"
    break;

  case 37: /* BlockItem: Decl  */
#line 314 "parser.y"
         {
        (yyval.node) = create_ast_node(Node_BlockItem, "BlockItem", yylineno);
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 1621 "parser.tab.c"
    break;

  case 38: /* BlockItem: Stmt  */
#line 318 "parser.y"
           {
        (yyval.node) = create_ast_node(Node_BlockItem, "BlockItem", yylineno);
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 1630 "parser.tab.c"
    break;

  case 39: /* Stmt: LVal ASSIGN Exp SEMICN  */
#line 325 "parser.y"
                           {
        (yyval.node) = create_ast_node(Node_Stmt, "Stmt", yylineno);
        add_child((yyval.node), (yyvsp[-3].node));
        add_child((yyval.node), create_token_node(ASSIGN, "ASSIGN", (yyvsp[-2].str)));
        add_child((yyval.node), (yyvsp[-1].node));
        add_child((yyval.node), create_token_node(SEMICN, "SEMICN", (yyvsp[0].str)));
    }
#line 1642 "parser.tab.c"
    break;

  case 40: /* Stmt: LVal ASSIGN Exp  */
#line 331 "parser.y"
                                        {  // 缺少分号的赋值语句（低优先级）
        add_syntax_error(yylineno, "Missing \";\"");
        (yyval.node) = create_ast_node(Node_Stmt, "Stmt", yylineno);
        add_child((yyval.node), (yyvsp[-2].node));
        add_child((yyval.node), create_token_node(ASSIGN, "ASSIGN", (yyvsp[-1].str)));
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 1654 "parser.tab.c"
    break;

  case 41: /* Stmt: Exp SEMICN  */
#line 337 "parser.y"
                      {
        (yyval.node) = create_ast_node(Node_Stmt, "Stmt", yylineno);
        add_child((yyval.node), (yyvsp[-1].node));
        add_child((yyval.node), create_token_node(SEMICN, "SEMICN", (yyvsp[0].str)));
    }
#line 1664 "parser.tab.c"
    break;

  case 42: /* Stmt: Exp  */
#line 342 "parser.y"
                       {  // 缺少分号的表达式语句（低优先级）
        add_syntax_error(yylineno, "Missing \";\"");
        (yyval.node) = create_ast_node(Node_Stmt, "Stmt", yylineno);
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 1674 "parser.tab.c"
    break;

  case 43: /* Stmt: SEMICN  */
#line 347 "parser.y"
             {
        (yyval.node) = create_ast_node(Node_Stmt, "Stmt", yylineno);
        add_child((yyval.node), create_token_node(SEMICN, "SEMICN", (yyvsp[0].str)));
    }
#line 1683 "parser.tab.c"
    break;

  case 44: /* Stmt: Block  */
#line 351 "parser.y"
            {
        (yyval.node) = create_ast_node(Node_Stmt, "Stmt", yylineno);
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 1692 "parser.tab.c"
    break;

  case 45: /* Stmt: IFTK LPARENT Cond RPARENT Stmt  */
#line 355 "parser.y"
                                     {
        (yyval.node) = create_ast_node(Node_Stmt, "Stmt", yylineno);
        add_child((yyval.node), create_token_node(IFTK, "IFTK", (yyvsp[-4].str)));
        add_child((yyval.node), create_token_node(LPARENT, "LPARENT", (yyvsp[-3].str)));
        add_child((yyval.node), (yyvsp[-2].node));
        add_child((yyval.node), create_token_node(RPARENT, "RPARENT", (yyvsp[-1].str)));
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 1705 "parser.tab.c"
    break;

  case 46: /* Stmt: IFTK LPARENT Cond RPARENT Stmt ELSETK Stmt  */
#line 363 "parser.y"
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
#line 1720 "parser.tab.c"
    break;

  case 47: /* Stmt: WHILETK LPARENT Cond RPARENT Stmt  */
#line 373 "parser.y"
                                        {
        (yyval.node) = create_ast_node(Node_Stmt, "Stmt", yylineno);
        add_child((yyval.node), create_token_node(WHILETK, "WHILETK", (yyvsp[-4].str)));
        add_child((yyval.node), create_token_node(LPARENT, "LPARENT", (yyvsp[-3].str)));
        add_child((yyval.node), (yyvsp[-2].node));
        add_child((yyval.node), create_token_node(RPARENT, "RPARENT", (yyvsp[-1].str)));
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 1733 "parser.tab.c"
    break;

  case 48: /* Stmt: BREAKTK SEMICN  */
#line 381 "parser.y"
                     {
        (yyval.node) = create_ast_node(Node_Stmt, "Stmt", yylineno);
        add_child((yyval.node), create_token_node(BREAKTK, "BREAKTK", (yyvsp[-1].str)));
        add_child((yyval.node), create_token_node(SEMICN, "SEMICN", (yyvsp[0].str)));
    }
#line 1743 "parser.tab.c"
    break;

  case 49: /* Stmt: CONTINUETK SEMICN  */
#line 386 "parser.y"
                        {
        (yyval.node) = create_ast_node(Node_Stmt, "Stmt", yylineno);
        add_child((yyval.node), create_token_node(CONTINUETK, "CONTINUETK", (yyvsp[-1].str)));
        add_child((yyval.node), create_token_node(SEMICN, "SEMICN", (yyvsp[0].str)));
    }
#line 1753 "parser.tab.c"
    break;

  case 50: /* Stmt: RETURNTK SEMICN  */
#line 391 "parser.y"
                      {
        (yyval.node) = create_ast_node(Node_Stmt, "Stmt", yylineno);
        add_child((yyval.node), create_token_node(RETURNTK, "RETURNTK", (yyvsp[-1].str)));
        add_child((yyval.node), create_token_node(SEMICN, "SEMICN", (yyvsp[0].str)));
    }
#line 1763 "parser.tab.c"
    break;

  case 51: /* Stmt: RETURNTK Exp SEMICN  */
#line 396 "parser.y"
                          {
        (yyval.node) = create_ast_node(Node_Stmt, "Stmt", yylineno);
        add_child((yyval.node), create_token_node(RETURNTK, "RETURNTK", (yyvsp[-2].str)));
        add_child((yyval.node), (yyvsp[-1].node));
        add_child((yyval.node), create_token_node(SEMICN, "SEMICN", (yyvsp[0].str)));
    }
#line 1774 "parser.tab.c"
    break;

  case 52: /* Exp: AddExp  */
#line 405 "parser.y"
           {
        (yyval.node) = create_ast_node(Node_Exp, "Exp", yylineno);
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 1783 "parser.tab.c"
    break;

  case 53: /* Cond: LOrExp  */
#line 412 "parser.y"
           {
        (yyval.node) = create_ast_node(Node_Cond, "Cond", yylineno);
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 1792 "parser.tab.c"
    break;

  case 54: /* LVal: ID  */
#line 419 "parser.y"
       {
        (yyval.node) = create_ast_node(Node_LVal, "LVal", yylineno);
        add_child((yyval.node), create_token_node(ID, "ID", (yyvsp[0].str)));
    }
#line 1801 "parser.tab.c"
    break;

  case 55: /* LVal: ID LBRACKET Exp RBRACKET  */
#line 423 "parser.y"
                               {
        (yyval.node) = create_ast_node(Node_LVal, "LVal", yylineno);
        add_child((yyval.node), create_token_node(ID, "ID", (yyvsp[-3].str)));
        add_child((yyval.node), create_token_node(LBRACKET, "LBRACKET", (yyvsp[-2].str)));
        add_child((yyval.node), (yyvsp[-1].node));
        add_child((yyval.node), create_token_node(RBRACKET, "RBRACKET", (yyvsp[0].str)));
    }
#line 1813 "parser.tab.c"
    break;

  case 56: /* LVal: ID LBRACKET Exp COMMA Exp RBRACKET  */
#line 430 "parser.y"
                                         {  // 错误：a[5,3] 应该是 a[5][3]
        add_syntax_error(yylineno, "Missing \"]\"");
        (yyval.node) = create_ast_node(Node_LVal, "LVal", yylineno);
        add_child((yyval.node), create_token_node(ID, "ID", (yyvsp[-5].str)));
        add_child((yyval.node), create_token_node(LBRACKET, "LBRACKET", (yyvsp[-4].str)));
        add_child((yyval.node), (yyvsp[-3].node));
        add_child((yyval.node), create_token_node(COMMA, "COMMA", (yyvsp[-2].str)));
        add_child((yyval.node), (yyvsp[-1].node));
        add_child((yyval.node), create_token_node(RBRACKET, "RBRACKET", (yyvsp[0].str)));
    }
#line 1828 "parser.tab.c"
    break;

  case 57: /* PrimaryExp: LPARENT Exp RPARENT  */
#line 443 "parser.y"
                        {
        (yyval.node) = create_ast_node(Node_PrimaryExp, "PrimaryExp", yylineno);
        add_child((yyval.node), create_token_node(LPARENT, "LPARENT", (yyvsp[-2].str)));
        add_child((yyval.node), (yyvsp[-1].node));
        add_child((yyval.node), create_token_node(RPARENT, "RPARENT", (yyvsp[0].str)));
    }
#line 1839 "parser.tab.c"
    break;

  case 58: /* PrimaryExp: LVal  */
#line 449 "parser.y"
           {
        (yyval.node) = create_ast_node(Node_PrimaryExp, "PrimaryExp", yylineno);
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 1848 "parser.tab.c"
    break;

  case 59: /* PrimaryExp: Number  */
#line 453 "parser.y"
             {
        (yyval.node) = create_ast_node(Node_PrimaryExp, "PrimaryExp", yylineno);
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 1857 "parser.tab.c"
    break;

  case 60: /* Number: INTCON  */
#line 460 "parser.y"
           {
        (yyval.node) = create_ast_node(Node_Number, "Number", yylineno);
                char buf[32];
        sprintf(buf, "%d", (yyvsp[0].intval));   // ⭐ int → string
        add_child((yyval.node), create_token_node(INTCON, "INTCON", buf));
    }
#line 1868 "parser.tab.c"
    break;

  case 61: /* UnaryExp: PrimaryExp  */
#line 470 "parser.y"
               {
        (yyval.node) = create_ast_node(Node_UnaryExp, "UnaryExp", yylineno);
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 1877 "parser.tab.c"
    break;

  case 62: /* UnaryExp: ID LPARENT FuncRParamsOpt RPARENT  */
#line 474 "parser.y"
                                        {
        (yyval.node) = create_ast_node(Node_UnaryExp, "UnaryExp", yylineno);
        add_child((yyval.node), create_token_node(ID, "ID", (yyvsp[-3].str)));
        add_child((yyval.node), create_token_node(LPARENT, "LPARENT", (yyvsp[-2].str)));
        if ((yyvsp[-1].node)) add_child((yyval.node), (yyvsp[-1].node));
        add_child((yyval.node), create_token_node(RPARENT, "RPARENT", (yyvsp[0].str)));
    }
#line 1889 "parser.tab.c"
    break;

  case 63: /* UnaryExp: UnaryOp UnaryExp  */
#line 481 "parser.y"
                       {
        (yyval.node) = create_ast_node(Node_UnaryExp, "UnaryExp", yylineno);
        add_child((yyval.node), (yyvsp[-1].node));
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 1899 "parser.tab.c"
    break;

  case 64: /* UnaryOp: PLUS  */
#line 489 "parser.y"
         {
        (yyval.node) = create_ast_node(Node_UnaryOp, "UnaryOp", yylineno);
        add_child((yyval.node), create_token_node(PLUS, "PLUS", (yyvsp[0].str)));
    }
#line 1908 "parser.tab.c"
    break;

  case 65: /* UnaryOp: MINUS  */
#line 493 "parser.y"
            {
        (yyval.node) = create_ast_node(Node_UnaryOp, "UnaryOp", yylineno);
        add_child((yyval.node), create_token_node(MINUS, "MINUS", (yyvsp[0].str)));
    }
#line 1917 "parser.tab.c"
    break;

  case 66: /* UnaryOp: NOT  */
#line 497 "parser.y"
          {
        (yyval.node) = create_ast_node(Node_UnaryOp, "UnaryOp", yylineno);
        add_child((yyval.node), create_token_node(NOT, "NOT", (yyvsp[0].str)));
    }
#line 1926 "parser.tab.c"
    break;

  case 67: /* MulExp: UnaryExp  */
#line 504 "parser.y"
             {
        (yyval.node) = create_ast_node(Node_MulExp, "MulExp", yylineno);
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 1935 "parser.tab.c"
    break;

  case 68: /* MulExp: MulExp MUL UnaryExp  */
#line 508 "parser.y"
                          {
        (yyval.node) = create_ast_node(Node_MulExp, "MulExp", yylineno);
        add_child((yyval.node), (yyvsp[-2].node));
        add_child((yyval.node), create_token_node(MUL, "MUL", (yyvsp[-1].str)));
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 1946 "parser.tab.c"
    break;

  case 69: /* MulExp: MulExp DIV UnaryExp  */
#line 514 "parser.y"
                          {
        (yyval.node) = create_ast_node(Node_MulExp, "MulExp", yylineno);
        add_child((yyval.node), (yyvsp[-2].node));
        add_child((yyval.node), create_token_node(DIV, "DIV", (yyvsp[-1].str)));
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 1957 "parser.tab.c"
    break;

  case 70: /* MulExp: MulExp MOD UnaryExp  */
#line 520 "parser.y"
                          {
        (yyval.node) = create_ast_node(Node_MulExp, "MulExp", yylineno);
        add_child((yyval.node), (yyvsp[-2].node));
        add_child((yyval.node), create_token_node(MOD, "MOD", (yyvsp[-1].str)));
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 1968 "parser.tab.c"
    break;

  case 71: /* AddExp: MulExp  */
#line 529 "parser.y"
           {
        (yyval.node) = create_ast_node(Node_AddExp, "AddExp", yylineno);
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 1977 "parser.tab.c"
    break;

  case 72: /* AddExp: AddExp PLUS MulExp  */
#line 533 "parser.y"
                         {
        (yyval.node) = create_ast_node(Node_AddExp, "AddExp", yylineno);
        add_child((yyval.node), (yyvsp[-2].node));
        add_child((yyval.node), create_token_node(PLUS, "PLUS", (yyvsp[-1].str)));
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 1988 "parser.tab.c"
    break;

  case 73: /* AddExp: AddExp MINUS MulExp  */
#line 539 "parser.y"
                          {
        (yyval.node) = create_ast_node(Node_AddExp, "AddExp", yylineno);
        add_child((yyval.node), (yyvsp[-2].node));
        add_child((yyval.node), create_token_node(MINUS, "MINUS", (yyvsp[-1].str)));
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 1999 "parser.tab.c"
    break;

  case 74: /* RelExp: AddExp  */
#line 548 "parser.y"
           {
        (yyval.node) = create_ast_node(Node_RelExp, "RelExp", yylineno);
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 2008 "parser.tab.c"
    break;

  case 75: /* RelExp: RelExp LT AddExp  */
#line 552 "parser.y"
                       {
        (yyval.node) = create_ast_node(Node_RelExp, "RelExp", yylineno);
        add_child((yyval.node), (yyvsp[-2].node));
        add_child((yyval.node), create_token_node(LT, "LT", (yyvsp[-1].str)));
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 2019 "parser.tab.c"
    break;

  case 76: /* RelExp: RelExp GT AddExp  */
#line 558 "parser.y"
                       {
        (yyval.node) = create_ast_node(Node_RelExp, "RelExp", yylineno);
        add_child((yyval.node), (yyvsp[-2].node));
        add_child((yyval.node), create_token_node(GT, "GT", (yyvsp[-1].str)));
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 2030 "parser.tab.c"
    break;

  case 77: /* RelExp: RelExp LEQ AddExp  */
#line 564 "parser.y"
                        {
        (yyval.node) = create_ast_node(Node_RelExp, "RelExp", yylineno);
        add_child((yyval.node), (yyvsp[-2].node));
        add_child((yyval.node), create_token_node(LEQ, "LEQ", (yyvsp[-1].str)));
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 2041 "parser.tab.c"
    break;

  case 78: /* RelExp: RelExp GEQ AddExp  */
#line 570 "parser.y"
                        {
        (yyval.node) = create_ast_node(Node_RelExp, "RelExp", yylineno);
        add_child((yyval.node), (yyvsp[-2].node));
        add_child((yyval.node), create_token_node(GEQ, "GEQ", (yyvsp[-1].str)));
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 2052 "parser.tab.c"
    break;

  case 79: /* EqExp: RelExp  */
#line 579 "parser.y"
           {
        (yyval.node) = create_ast_node(Node_EqExp, "EqExp", yylineno);
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 2061 "parser.tab.c"
    break;

  case 80: /* EqExp: EqExp EQ RelExp  */
#line 583 "parser.y"
                      {
        (yyval.node) = create_ast_node(Node_EqExp, "EqExp", yylineno);
        add_child((yyval.node), (yyvsp[-2].node));
        add_child((yyval.node), create_token_node(EQ, "EQ", (yyvsp[-1].str)));
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 2072 "parser.tab.c"
    break;

  case 81: /* EqExp: EqExp NEQ RelExp  */
#line 589 "parser.y"
                       {
        (yyval.node) = create_ast_node(Node_EqExp, "EqExp", yylineno);
        add_child((yyval.node), (yyvsp[-2].node));
        add_child((yyval.node), create_token_node(NEQ, "NEQ", (yyvsp[-1].str)));
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 2083 "parser.tab.c"
    break;

  case 82: /* LAndExp: EqExp  */
#line 598 "parser.y"
          {
        (yyval.node) = create_ast_node(Node_LAndExp, "LAndExp", yylineno);
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 2092 "parser.tab.c"
    break;

  case 83: /* LAndExp: LAndExp AND EqExp  */
#line 602 "parser.y"
                        {
        (yyval.node) = create_ast_node(Node_LAndExp, "LAndExp", yylineno);
        add_child((yyval.node), (yyvsp[-2].node));
        add_child((yyval.node), create_token_node(AND, "AND", (yyvsp[-1].str)));
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 2103 "parser.tab.c"
    break;

  case 84: /* LOrExp: LAndExp  */
#line 611 "parser.y"
            {
        (yyval.node) = create_ast_node(Node_LOrExp, "LOrExp", yylineno);
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 2112 "parser.tab.c"
    break;

  case 85: /* LOrExp: LOrExp OR LAndExp  */
#line 615 "parser.y"
                        {
        (yyval.node) = create_ast_node(Node_LOrExp, "LOrExp", yylineno);
        add_child((yyval.node), (yyvsp[-2].node));
        add_child((yyval.node), create_token_node(OR, "OR", (yyvsp[-1].str)));
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 2123 "parser.tab.c"
    break;

  case 86: /* ConstExp: AddExp  */
#line 624 "parser.y"
           {
        (yyval.node) = create_ast_node(Node_ConstExp, "ConstExp", yylineno);
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 2132 "parser.tab.c"
    break;


#line 2136 "parser.tab.c"

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

#line 630 "parser.y"


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
    // 禁用Bison的默认错误处理，避免重复报告
    // 我们已经在规则中手动处理了错误
}

void add_syntax_error(int line, const char *msg) {
    // 防止重复报告相同错误
    for (int i = 0; i < syntax_error_count; i++) {
        if (syntax_error_list[i].line == line &&
            strstr(syntax_error_list[i].message, msg) != NULL) {
            return;  // 如果已经报告过相同的错误，直接跳过
        }
    }
    if (syntax_error_count < MAX_ERRORS) {
        char full_msg[100];
        snprintf(full_msg, sizeof(full_msg), "Error type B at Line %d: %s", line, msg);
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
        for (int i = 0; i < syntax_error_count; i++) {
            fprintf(stderr, "%s\n", syntax_error_list[i].message);
        }
        return 0;
    }

    print_ast(root, 0);
  
    return 0;
}

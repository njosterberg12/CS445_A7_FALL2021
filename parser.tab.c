/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
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
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.5.1"

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

//Parser.y Bison File
//*************************************************************
// To send to course server, tar work into file (ex. tar cvf file.tar *)
// Then run scp file.tar oste1799@cs-445.cs.uidaho.edu:/home/oste1799/CS445v2/directory of assignment
//*************************************************************/
#include "scanType.h" // tokenData type
#include "treeNodes.h"
#include <getopt.h>
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string.h>
#include "semantic.h"
#include "IO.h"
#include "yyerror.h"

#define YYERROR_VERBOSE

extern int yylex();
extern int yydebug;
extern FILE *yyin;      
extern int line; // ERR line number from the scanner
int numErrors;
int numWarnings;   // ERR err count
static TreeNode *syntaxTree;
bool PAST; // PAST value is used in treeNodes.c
SymbolTable st;
int Loffset = -2;
int Goffset = 0;

bool displayOffset = false;

bool m;
/*void yyerror(const char *msg)
{
   printf("ERROR(%d): %s\n", line, msg);
   numErrors++;
}*/

int i = 0;


#line 115 "parser.tab.c"

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

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
#ifndef YY_YY_PARSER_TAB_H_INCLUDED
# define YY_YY_PARSER_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    BOOL = 258,
    NUMCONST = 259,
    CHARCONST = 260,
    STRINGCONST = 261,
    ID = 262,
    STATIC = 263,
    BOOLKW = 264,
    CHAR = 265,
    INT = 266,
    IF = 267,
    THEN = 268,
    ELSE = 269,
    WHILE = 270,
    DO = 271,
    FOR = 272,
    TO = 273,
    BY = 274,
    RETURN = 275,
    BREAK = 276,
    OR = 277,
    AND = 278,
    NOT = 279,
    NEQ = 280,
    GEQ = 281,
    LEQ = 282,
    INC = 283,
    DEC = 284,
    ADDASS = 285,
    SUBASS = 286,
    MULASS = 287,
    DIVASS = 288,
    ASGN = 289,
    EQ = 290,
    LQ = 291,
    GQ = 292,
    PLUS = 293,
    MINUS = 294,
    STAR = 295,
    DIV = 296,
    MOD = 297,
    LPAREN = 298,
    RPAREN = 299,
    SEMICOLON = 300,
    COMMA = 301,
    COLON = 302,
    QMARK = 303,
    LBRACKET = 304,
    RBRACKET = 305,
    LBRACE = 306,
    RBRACE = 307
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 47 "parser.y"

   ExpType type;           // For passing types (ie pass a type in a decl like int or bool)
   TokenData *tokenData;   // For terminals. Token data comes from yylex() in the $ vars
   TreeNode *tree;        // For nonterminals. Add these nodes as you build the tree.

#line 226 "parser.tab.c"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_TAB_H_INCLUDED  */



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
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
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

#if ! defined yyoverflow || YYERROR_VERBOSE

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
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


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
#define YYLAST   745

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  53
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  46
/* YYNRULES -- Number of rules.  */
#define YYNRULES  159
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  256

#define YYUNDEFTOK  2
#define YYMAXUTOK   307


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

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
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    74,    74,    76,    77,    79,    80,    81,    83,    86,
      87,    89,    95,   101,   104,   105,   106,   110,   111,   118,
     122,   126,   136,   137,   139,   140,   141,   143,   149,   156,
     157,   158,   159,   161,   162,   164,   165,   166,   167,   169,
     172,   174,   176,   177,   178,   180,   184,   191,   192,   194,
     195,   196,   200,   207,   208,   210,   211,   213,   214,   221,
     222,   223,   224,   230,   231,   232,   244,   245,   247,   252,
     255,   261,   264,   275,   278,   279,   283,   287,   288,   289,
     290,   292,   300,   301,   302,   303,   312,   316,   323,   327,
     332,   339,   342,   343,   350,   351,   358,   359,   366,   367,
     374,   375,   381,   384,   390,   393,   395,   402,   403,   405,
     412,   413,   415,   421,   422,   424,   428,   429,   431,   435,
     439,   443,   447,   451,   456,   460,   461,   463,   468,   474,
     478,   479,   481,   486,   491,   497,   500,   501,   503,   510,
     517,   525,   526,   528,   532,   547,   550,   551,   552,   554,
     558,   562,   563,   565,   566,   567,   569,   577,   588,   597
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "BOOL", "NUMCONST", "CHARCONST",
  "STRINGCONST", "ID", "STATIC", "BOOLKW", "CHAR", "INT", "IF", "THEN",
  "ELSE", "WHILE", "DO", "FOR", "TO", "BY", "RETURN", "BREAK", "OR", "AND",
  "NOT", "NEQ", "GEQ", "LEQ", "INC", "DEC", "ADDASS", "SUBASS", "MULASS",
  "DIVASS", "ASGN", "EQ", "LQ", "GQ", "PLUS", "MINUS", "STAR", "DIV",
  "MOD", "LPAREN", "RPAREN", "SEMICOLON", "COMMA", "COLON", "QMARK",
  "LBRACKET", "RBRACKET", "LBRACE", "RBRACE", "$accept", "program",
  "declList", "decl", "varDecl", "scopedVarDecl", "varDeclList",
  "varDeclInit", "varDeclId", "typeSpec", "funDecl", "parms", "parmList",
  "parmTypeList", "parmIdList", "parmId", "stmt", "expStmt",
  "compoundStmt", "localDecls", "stmtList", "matched", "unmatched",
  "endStmt", "iterRange", "returnStmt", "breakStmt", "exp", "simpleExp",
  "andExp", "unaryRelExp", "relExp", "relop", "sumExp", "sumop", "mulExp",
  "mulop", "unaryExp", "unaryop", "factor", "mutable", "immutable", "call",
  "args", "argList", "constant", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307
};
# endif

#define YYPACT_NINF (-134)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-153)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     165,   264,   -32,  -134,  -134,  -134,    19,   361,  -134,  -134,
      94,  -134,   -24,   -19,    -4,  -134,    27,    28,  -134,  -134,
     209,    -9,   102,   184,  -134,   110,  -134,   106,   184,   149,
     115,    49,    55,  -134,  -134,    77,  -134,    80,  -134,  -134,
    -134,  -134,   112,   297,  -134,  -134,   304,  -134,   103,   136,
    -134,  -134,   706,   189,  -134,   658,  -134,  -134,  -134,  -134,
    -134,  -134,   121,   -24,  -134,   103,   174,   176,   190,  -134,
       3,    58,   149,   204,  -134,     9,   326,    80,  -134,    81,
     213,   103,   105,   352,   374,  -134,  -134,  -134,  -134,  -134,
    -134,  -134,  -134,   665,   680,  -134,  -134,  -134,   687,    80,
    -134,  -134,   210,   156,  -134,  -134,  -134,  -134,  -134,   211,
      81,  -134,   224,   223,   222,  -134,  -134,   326,  -134,  -134,
    -134,   381,   403,   429,   451,   458,    80,   136,    80,  -134,
      80,   202,    80,   189,    80,  -134,  -134,  -134,  -134,   430,
    -134,  -134,   480,  -134,  -134,    81,  -134,    81,  -134,    81,
    -134,    81,  -134,    81,  -134,   392,  -134,   177,   194,    81,
    -134,   177,   158,   117,   506,   528,   185,   125,   232,  -134,
    -134,  -134,  -134,  -134,  -134,  -134,  -134,  -134,  -134,   238,
     198,  -134,  -134,    30,    76,    12,   180,  -134,   250,   124,
    -134,   243,  -134,  -134,  -134,   246,   246,   275,   275,   275,
     535,  -134,  -134,   557,   583,   212,   279,  -134,  -134,   292,
    -134,  -134,  -134,  -134,     2,   296,   199,    33,    90,    15,
     200,  -134,   282,   275,   275,   275,   312,   275,   605,   246,
     246,   246,   246,   612,  -134,  -134,  -134,  -134,  -134,  -134,
    -134,  -134,  -134,    80,   216,   303,   305,     8,   306,   634,
     246,   246,   246,   246,    80,   103
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,    25,    26,    24,     0,     0,     4,     5,
       0,     6,    16,    20,     0,    15,    17,     0,     1,     3,
      29,    20,     0,     0,    23,     0,     9,     0,     0,    31,
       0,     0,    33,    36,    10,     0,     8,     0,   159,   156,
     157,   158,   143,     0,   138,   139,     0,   140,    19,   108,
     111,   114,   116,   126,   131,     0,   137,   141,   142,   147,
     148,    22,     0,    14,    13,    18,    40,    45,    39,    42,
       0,     0,    30,     0,   150,     0,     0,   113,   112,   146,
       0,   105,   141,     0,     0,   123,   121,   119,   122,   118,
     120,   127,   128,     0,     0,   132,   133,   134,     0,   136,
     135,    21,     0,     0,    32,    54,    28,    37,    35,     0,
       0,   154,     0,   151,     0,   102,   104,     0,   145,   101,
     103,     0,     0,     0,     0,     0,   107,   106,   110,   109,
     117,   115,   125,   124,   130,   129,    46,    43,    41,    56,
      27,   149,     0,   144,    91,    94,    93,    96,    95,    98,
      97,   100,    99,    92,    90,     0,    53,     0,     0,   155,
     153,     0,     0,     0,     0,     0,     0,     0,     0,    50,
      52,    55,    77,    78,    47,    48,    57,    79,    80,     0,
       0,    12,    51,    59,     0,    64,     0,    67,     0,     0,
      86,     0,    89,    49,    11,     0,     0,     0,     0,     0,
       0,    88,    87,     0,     0,     0,    76,    60,    75,    47,
      63,    71,    62,    70,     0,     0,     0,    59,     0,    64,
       0,    67,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    61,    69,    58,    68,    66,    73,
      83,    65,    72,    82,    81,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    84,    85
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -134,  -134,  -134,   317,  -134,  -134,    -7,   298,  -134,     1,
    -134,   299,  -134,   267,  -134,   236,   138,  -134,   -53,  -134,
    -134,  -133,  -119,  -134,   108,  -134,  -134,   -40,   -21,   259,
     -34,  -134,  -134,   253,  -134,   254,  -134,   -33,  -134,  -134,
     -23,  -134,  -134,  -134,  -134,  -134
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     6,     7,     8,     9,   156,    14,    15,    16,    30,
      11,    31,    32,    33,    68,    69,   171,   172,   173,   139,
     158,   210,   175,   176,   215,   177,   178,   179,    81,    49,
      50,    51,    93,    52,    94,    53,    98,    54,    55,    56,
      82,    58,    59,   112,   113,    60
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      57,    10,    48,    22,   104,    57,    80,    65,    10,    78,
     110,    17,    38,    39,    40,    41,    42,   106,   225,    18,
      57,   226,   100,    23,   252,   174,    24,   226,   198,    29,
      25,   231,    57,    43,    35,   111,   114,     3,     4,     5,
      25,    26,    27,   195,   196,    74,   229,   196,    44,    45,
     129,    74,    46,  -152,   105,    74,   140,    47,    74,   107,
      57,    57,   206,   207,   209,   135,   212,     3,     4,     5,
      57,    57,   -34,    74,    28,    57,    74,   144,    72,   211,
     213,   146,   148,   150,   152,   154,     3,     4,     5,   197,
     234,   236,   238,    70,   241,    20,   245,   246,    83,   212,
      71,    21,   160,   230,   235,   237,   239,    63,   242,   115,
     116,    61,    83,    13,    62,   117,    66,   234,   236,   238,
     241,   -34,    67,    74,    74,    83,   189,   191,    38,    39,
      40,    41,    42,   119,   120,   121,   122,   123,   124,   125,
     157,    57,    57,   184,   186,   115,   116,    36,    27,    43,
     162,   117,   115,   116,   180,    75,   161,   137,   117,    84,
      74,    76,   182,    67,    44,    45,     1,    74,    46,   201,
     190,   101,     2,    47,     3,     4,     5,    57,    12,   216,
      57,    57,   218,   220,    13,    37,   187,    38,    39,    40,
      41,    42,   188,   -38,   -38,   163,   199,    38,    39,    40,
      41,    42,    83,   181,    27,    57,   164,   244,    43,   165,
      57,   166,   216,   221,   167,   168,   232,   228,    43,   222,
     -44,    83,    83,    44,    45,   102,    57,    46,   255,    95,
      96,    97,    47,    44,    45,   249,   103,    46,    83,   169,
      91,    92,    47,   194,    27,   105,   170,   163,   109,    38,
      39,    40,    41,    42,    34,   -16,    23,   118,   203,    24,
     136,   204,   105,   205,    -7,    12,   167,   168,   141,   142,
      43,    13,   143,    -7,    -7,    -7,   163,   192,    38,    39,
      40,    41,    42,   193,   200,    44,    45,   164,   202,    46,
     165,   169,   166,   223,    47,   167,   168,   105,    77,    43,
      38,    39,    40,    41,    42,    79,   224,    38,    39,    40,
      41,    42,   227,   240,    44,    45,   233,   250,    46,   251,
     169,    43,   253,    47,    19,    64,   105,   110,    43,    38,
      39,    40,    41,    42,    73,   208,    44,    45,   108,   138,
      46,   248,   127,    44,    45,    47,   131,    46,   133,     0,
      43,     0,    47,   126,     0,    38,    39,    40,    41,    42,
       0,    -2,     1,     0,     0,    44,    45,     0,     2,    46,
       3,     4,     5,     0,    47,   128,    43,    38,    39,    40,
      41,    42,   145,     0,    38,    39,    40,    41,    42,     0,
       0,    44,    45,     0,     0,    46,     0,     0,    43,     0,
      47,     3,     4,     5,   147,    43,    38,    39,    40,    41,
      42,     0,     0,    44,    45,     0,     0,    46,     0,     0,
      44,    45,    47,     0,    46,     0,     0,    43,     0,    47,
     149,     0,    38,    39,    40,    41,    42,     0,   155,     3,
       4,     5,    44,    45,     0,     0,    46,     0,     0,     0,
       0,    47,   151,    43,    38,    39,    40,    41,    42,   153,
       0,    38,    39,    40,    41,    42,     0,     0,    44,    45,
       0,     0,    46,     0,     0,    43,     0,    47,     0,     0,
       0,   159,    43,    38,    39,    40,    41,    42,     0,     0,
      44,    45,     0,     0,    46,     0,     0,    44,    45,    47,
       0,    46,     0,     0,    43,     0,    47,   183,     0,    38,
      39,    40,    41,    42,     0,     0,     0,     0,     0,    44,
      45,     0,     0,    46,     0,     0,     0,     0,    47,   185,
      43,    38,    39,    40,    41,    42,   214,     0,    38,    39,
      40,    41,    42,     0,     0,    44,    45,     0,     0,    46,
       0,     0,    43,     0,    47,     0,     0,     0,   217,    43,
      38,    39,    40,    41,    42,     0,     0,    44,    45,     0,
       0,    46,     0,     0,    44,    45,    47,     0,    46,     0,
       0,    43,     0,    47,   219,     0,    38,    39,    40,    41,
      42,     0,     0,     0,     0,     0,    44,    45,     0,     0,
      46,     0,     0,     0,     0,    47,   243,    43,    38,    39,
      40,    41,    42,   247,     0,    38,    39,    40,    41,    42,
       0,     0,    44,    45,     0,     0,    46,     0,     0,    43,
       0,    47,     0,     0,     0,   254,    43,    38,    39,    40,
      41,    42,     0,     0,    44,    45,     0,     0,    46,     0,
       0,    44,    45,    47,     0,    46,     0,     0,    43,    99,
      47,    38,    39,    40,    41,    42,   130,     0,    38,    39,
      40,    41,    42,    44,    45,     0,     0,    46,     0,     0,
       0,   132,    47,    38,    39,    40,    41,    42,   134,     0,
      38,    39,    40,    41,    42,     0,     0,    44,    45,     0,
       0,    46,     0,     0,    44,    45,    47,     0,    46,     0,
       0,     0,     0,    47,     0,     0,     0,     0,     0,    44,
      45,     0,     0,    46,     0,     0,    44,    45,    47,     0,
      46,    85,    86,    87,     0,    47,     0,     0,     0,     0,
       0,    88,    89,    90,    91,    92
};

static const yytype_int16 yycheck[] =
{
      23,     0,    23,    10,     1,    28,    46,    28,     7,    43,
       1,    43,     3,     4,     5,     6,     7,    70,    16,     0,
      43,    19,    55,    47,    16,   158,    50,    19,    16,     1,
      49,    16,    55,    24,    43,    75,    76,     9,    10,    11,
      49,    45,    46,    13,    14,    43,    13,    14,    39,    40,
      84,    43,    43,    44,    51,    43,   109,    48,    43,     1,
      83,    84,   195,   196,   197,    98,   199,     9,    10,    11,
      93,    94,    44,    43,    47,    98,    43,   117,     1,   198,
     199,   121,   122,   123,   124,   125,     9,    10,    11,    13,
     223,   224,   225,    44,   227,     1,   229,   230,    22,   232,
      45,     7,   142,    13,   223,   224,   225,     1,   227,    28,
      29,     1,    22,     7,     4,    34,     1,   250,   251,   252,
     253,    44,     7,    43,    43,    22,     1,   167,     3,     4,
       5,     6,     7,    28,    29,    30,    31,    32,    33,    34,
     139,   164,   165,   164,   165,    28,    29,    45,    46,    24,
     157,    34,    28,    29,   161,    43,   155,     1,    34,    23,
      43,    49,    45,     7,    39,    40,     1,    43,    43,    45,
      45,    50,     7,    48,     9,    10,    11,   200,     1,   200,
     203,   204,   203,   204,     7,     1,     1,     3,     4,     5,
       6,     7,     7,    44,    45,     1,    16,     3,     4,     5,
       6,     7,    22,    45,    46,   228,    12,   228,    24,    15,
     233,    17,   233,     1,    20,    21,    16,    18,    24,     7,
      46,    22,    22,    39,    40,    49,   249,    43,   249,    40,
      41,    42,    48,    39,    40,    19,    46,    43,    22,    45,
      38,    39,    48,    45,    46,    51,    52,     1,    44,     3,
       4,     5,     6,     7,    45,    46,    47,    44,    12,    50,
      50,    15,    51,    17,     0,     1,    20,    21,    44,    46,
      24,     7,    50,     9,    10,    11,     1,    45,     3,     4,
       5,     6,     7,    45,    34,    39,    40,    12,    45,    43,
      15,    45,    17,    14,    48,    20,    21,    51,     1,    24,
       3,     4,     5,     6,     7,     1,    14,     3,     4,     5,
       6,     7,    16,     1,    39,    40,    34,    14,    43,    14,
      45,    24,    16,    48,     7,    27,    51,     1,    24,     3,
       4,     5,     6,     7,    35,   197,    39,    40,    71,   103,
      43,   233,    83,    39,    40,    48,    93,    43,    94,    -1,
      24,    -1,    48,     1,    -1,     3,     4,     5,     6,     7,
      -1,     0,     1,    -1,    -1,    39,    40,    -1,     7,    43,
       9,    10,    11,    -1,    48,     1,    24,     3,     4,     5,
       6,     7,     1,    -1,     3,     4,     5,     6,     7,    -1,
      -1,    39,    40,    -1,    -1,    43,    -1,    -1,    24,    -1,
      48,     9,    10,    11,     1,    24,     3,     4,     5,     6,
       7,    -1,    -1,    39,    40,    -1,    -1,    43,    -1,    -1,
      39,    40,    48,    -1,    43,    -1,    -1,    24,    -1,    48,
       1,    -1,     3,     4,     5,     6,     7,    -1,     8,     9,
      10,    11,    39,    40,    -1,    -1,    43,    -1,    -1,    -1,
      -1,    48,     1,    24,     3,     4,     5,     6,     7,     1,
      -1,     3,     4,     5,     6,     7,    -1,    -1,    39,    40,
      -1,    -1,    43,    -1,    -1,    24,    -1,    48,    -1,    -1,
      -1,     1,    24,     3,     4,     5,     6,     7,    -1,    -1,
      39,    40,    -1,    -1,    43,    -1,    -1,    39,    40,    48,
      -1,    43,    -1,    -1,    24,    -1,    48,     1,    -1,     3,
       4,     5,     6,     7,    -1,    -1,    -1,    -1,    -1,    39,
      40,    -1,    -1,    43,    -1,    -1,    -1,    -1,    48,     1,
      24,     3,     4,     5,     6,     7,     1,    -1,     3,     4,
       5,     6,     7,    -1,    -1,    39,    40,    -1,    -1,    43,
      -1,    -1,    24,    -1,    48,    -1,    -1,    -1,     1,    24,
       3,     4,     5,     6,     7,    -1,    -1,    39,    40,    -1,
      -1,    43,    -1,    -1,    39,    40,    48,    -1,    43,    -1,
      -1,    24,    -1,    48,     1,    -1,     3,     4,     5,     6,
       7,    -1,    -1,    -1,    -1,    -1,    39,    40,    -1,    -1,
      43,    -1,    -1,    -1,    -1,    48,     1,    24,     3,     4,
       5,     6,     7,     1,    -1,     3,     4,     5,     6,     7,
      -1,    -1,    39,    40,    -1,    -1,    43,    -1,    -1,    24,
      -1,    48,    -1,    -1,    -1,     1,    24,     3,     4,     5,
       6,     7,    -1,    -1,    39,    40,    -1,    -1,    43,    -1,
      -1,    39,    40,    48,    -1,    43,    -1,    -1,    24,     1,
      48,     3,     4,     5,     6,     7,     1,    -1,     3,     4,
       5,     6,     7,    39,    40,    -1,    -1,    43,    -1,    -1,
      -1,     1,    48,     3,     4,     5,     6,     7,     1,    -1,
       3,     4,     5,     6,     7,    -1,    -1,    39,    40,    -1,
      -1,    43,    -1,    -1,    39,    40,    48,    -1,    43,    -1,
      -1,    -1,    -1,    48,    -1,    -1,    -1,    -1,    -1,    39,
      40,    -1,    -1,    43,    -1,    -1,    39,    40,    48,    -1,
      43,    25,    26,    27,    -1,    48,    -1,    -1,    -1,    -1,
      -1,    35,    36,    37,    38,    39
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     1,     7,     9,    10,    11,    54,    55,    56,    57,
      62,    63,     1,     7,    59,    60,    61,    43,     0,    56,
       1,     7,    59,    47,    50,    49,    45,    46,    47,     1,
      62,    64,    65,    66,    45,    43,    45,     1,     3,     4,
       5,     6,     7,    24,    39,    40,    43,    48,    81,    82,
      83,    84,    86,    88,    90,    91,    92,    93,    94,    95,
      98,     1,     4,     1,    60,    81,     1,     7,    67,    68,
      44,    45,     1,    64,    43,    43,    49,     1,    83,     1,
      80,    81,    93,    22,    23,    25,    26,    27,    35,    36,
      37,    38,    39,    85,    87,    40,    41,    42,    89,     1,
      90,    50,    49,    46,     1,    51,    71,     1,    66,    44,
       1,    80,    96,    97,    80,    28,    29,    34,    44,    28,
      29,    30,    31,    32,    33,    34,     1,    82,     1,    83,
       1,    86,     1,    88,     1,    90,    50,     1,    68,    72,
      71,    44,    46,    50,    80,     1,    80,     1,    80,     1,
      80,     1,    80,     1,    80,     8,    58,    62,    73,     1,
      80,    62,    59,     1,    12,    15,    17,    20,    21,    45,
      52,    69,    70,    71,    74,    75,    76,    78,    79,    80,
      59,    45,    45,     1,    81,     1,    81,     1,     7,     1,
      45,    80,    45,    45,    45,    13,    14,    13,    16,    16,
      34,    45,    45,    12,    15,    17,    74,    74,    69,    74,
      74,    75,    74,    75,     1,    77,    81,     1,    81,     1,
      81,     1,     7,    14,    14,    16,    19,    16,    18,    13,
      13,    16,    16,    34,    74,    75,    74,    75,    74,    75,
       1,    74,    75,     1,    81,    74,    74,     1,    77,    19,
      14,    14,    16,    16,     1,    81
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    53,    54,    55,    55,    56,    56,    56,    57,    57,
      57,    58,    58,    59,    59,    59,    59,    60,    60,    60,
      61,    61,    61,    61,    62,    62,    62,    63,    63,    63,
      63,    63,    63,    64,    64,    65,    65,    65,    65,    66,
      66,    67,    67,    67,    67,    68,    68,    69,    69,    70,
      70,    70,    71,    72,    72,    73,    73,    74,    74,    74,
      74,    74,    74,    74,    74,    74,    74,    74,    75,    75,
      75,    75,    75,    75,    75,    75,    75,    76,    76,    76,
      76,    77,    77,    77,    77,    77,    78,    78,    78,    79,
      80,    80,    80,    80,    80,    80,    80,    80,    80,    80,
      80,    80,    80,    80,    80,    80,    81,    81,    81,    82,
      82,    82,    83,    83,    83,    84,    84,    84,    85,    85,
      85,    85,    85,    85,    86,    86,    86,    87,    87,    88,
      88,    88,    89,    89,    89,    90,    90,    90,    91,    91,
      91,    92,    92,    93,    93,    94,    94,    94,    94,    95,
      95,    96,    96,    97,    97,    97,    98,    98,    98,    98
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     1,     1,     1,     1,     3,     3,
       3,     4,     3,     3,     3,     1,     1,     1,     3,     3,
       1,     4,     3,     2,     1,     1,     1,     6,     5,     2,
       4,     3,     5,     1,     0,     3,     1,     3,     1,     2,
       2,     3,     1,     3,     1,     1,     3,     1,     1,     2,
       1,     2,     4,     2,     0,     2,     0,     1,     6,     2,
       4,     6,     4,     4,     2,     6,     6,     2,     6,     6,
       4,     4,     6,     6,     2,     4,     4,     1,     1,     1,
       1,     3,     3,     3,     5,     5,     2,     3,     3,     2,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     2,     2,     2,     2,     1,     3,     3,     1,     3,
       3,     1,     2,     2,     1,     3,     1,     3,     1,     1,
       1,     1,     1,     1,     3,     3,     1,     1,     1,     3,
       3,     1,     1,     1,     1,     2,     2,     1,     1,     1,
       1,     1,     1,     1,     4,     3,     2,     1,     1,     4,
       2,     1,     0,     3,     1,     3,     1,     1,     1,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


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

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



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

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yytype], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyo, yytype, yyvaluep);
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, int yyrule)
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
                       yystos[+yyssp[yyi + 1 - yynrhs]],
                       &yyvsp[(yyi + 1) - (yynrhs)]
                                              );
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
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
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


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
#  else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            else
              goto append;

          append:
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                yy_state_t *yyssp, int yytoken)
{
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Actual size of YYARG. */
  int yycount = 0;
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[+*yyssp];
      YYPTRDIFF_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
      yysize = yysize0;
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYPTRDIFF_T yysize1
                    = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
                    yysize = yysize1;
                  else
                    return 2;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    /* Don't count the "%s"s in the final size, but reserve room for
       the terminator.  */
    YYPTRDIFF_T yysize1 = yysize + (yystrlen (yyformat) - 2 * yycount) + 1;
    if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
      yysize = yysize1;
    else
      return 2;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
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
    yy_state_fast_t yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss;
    yy_state_t *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYPTRDIFF_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
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

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
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
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
# undef YYSTACK_RELOCATE
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

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
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
  case 2:
#line 74 "parser.y"
                                                               {  syntaxTree = (yyvsp[0].tree); }
#line 1687 "parser.tab.c"
    break;

  case 3:
#line 76 "parser.y"
                                                               {  (yyval.tree) = addSibling((yyvsp[-1].tree), (yyvsp[0].tree)); }
#line 1693 "parser.tab.c"
    break;

  case 4:
#line 77 "parser.y"
                                                               {  (yyval.tree) = (yyvsp[0].tree); }
#line 1699 "parser.tab.c"
    break;

  case 5:
#line 79 "parser.y"
                                                               {  (yyval.tree) = (yyvsp[0].tree); }
#line 1705 "parser.tab.c"
    break;

  case 6:
#line 80 "parser.y"
                                                               {  (yyval.tree) = (yyvsp[0].tree); }
#line 1711 "parser.tab.c"
    break;

  case 7:
#line 81 "parser.y"
                                                               {  (yyval.tree) = NULL; }
#line 1717 "parser.tab.c"
    break;

  case 8:
#line 83 "parser.y"
                                                               {  (yyval.tree) = (yyvsp[-1].tree);
                                                                  typeToSibling((yyval.tree), (yyvsp[-2].type));
                                                               }
#line 1725 "parser.tab.c"
    break;

  case 9:
#line 86 "parser.y"
                                                               {  (yyval.tree) = NULL; yyerrok; }
#line 1731 "parser.tab.c"
    break;

  case 10:
#line 87 "parser.y"
                                                               {  (yyval.tree) = NULL; yyerrok; yyerrok; }
#line 1737 "parser.tab.c"
    break;

  case 11:
#line 89 "parser.y"
                                                               {  (yyval.tree) = (yyvsp[-1].tree);
                                                                  //$$->expType = $2;
                                                                  (yyval.tree)->isStatic = true; 
                                                                  typeToStatic((yyval.tree), (yyvsp[-2].type));
                                                                  yyerrok;
                                                               }
#line 1748 "parser.tab.c"
    break;

  case 12:
#line 95 "parser.y"
                                                               {  (yyval.tree) = (yyvsp[-1].tree);
                                                                  //$$->expType = $1;
                                                                  typeToSibling((yyval.tree), (yyvsp[-2].type));
                                                                  yyerrok; 
                                                               }
#line 1758 "parser.tab.c"
    break;

  case 13:
#line 101 "parser.y"
                                                               {  (yyval.tree) = addSibling((yyvsp[-2].tree), (yyvsp[0].tree)); 
                                                                  yyerrok;
                                                               }
#line 1766 "parser.tab.c"
    break;

  case 14:
#line 104 "parser.y"
                                                               {  (yyval.tree) = NULL; }
#line 1772 "parser.tab.c"
    break;

  case 15:
#line 105 "parser.y"
                                                               {  (yyval.tree) = (yyvsp[0].tree); }
#line 1778 "parser.tab.c"
    break;

  case 16:
#line 106 "parser.y"
                                                               {  //if($0 != NULL)
                                                                     (yyval.tree) = NULL; 
                                                               }
#line 1786 "parser.tab.c"
    break;

  case 17:
#line 110 "parser.y"
                                                               {  (yyval.tree) = (yyvsp[0].tree); }
#line 1792 "parser.tab.c"
    break;

  case 18:
#line 111 "parser.y"
                                                               {
                                                                  (yyval.tree) = (yyvsp[-2].tree);
                                                                  if((yyvsp[-2].tree) != NULL)
                                                                  {
                                                                     (yyval.tree)->child[0] = (yyvsp[0].tree);
                                                                  } 
                                                               }
#line 1804 "parser.tab.c"
    break;

  case 19:
#line 118 "parser.y"
                                                               {  (yyval.tree) = NULL;
                                                                  yyerrok;
                                                               }
#line 1812 "parser.tab.c"
    break;

  case 20:
#line 122 "parser.y"
                                                               {  (yyval.tree) = newDeclNode(VarK, (yyvsp[0].tokenData));
                                                                  (yyval.tree)->attr.name = (yyvsp[0].tokenData)->tokenstr;
                                                                  (yyval.tree)->isInit = true; 
                                                               }
#line 1821 "parser.tab.c"
    break;

  case 21:
#line 126 "parser.y"
                                                               {  (yyval.tree) = newDeclNode(VarK, (yyvsp[-3].tokenData)); 
                                                                  (yyval.tree)->attr.name = (yyvsp[-3].tokenData)->tokenstr;
                                                                  (yyval.tree)->isArray = true;
                                                                  (yyval.tree)->TD = (yyvsp[-3].tokenData);
                                                                  (yyval.tree)->isInit = true; 
                                                                  //$$->attr.value = $3->nvalue;
                                                                  //$$->attr.op = $2->tokenclass;
                                                                  (yyval.tree)->expType = UndefinedType;
                                                                  (yyval.tree)->memSize = (yyvsp[-1].tokenData)->nvalue + 1;
                                                               }
#line 1836 "parser.tab.c"
    break;

  case 22:
#line 136 "parser.y"
                                                               {  (yyval.tree) = NULL; }
#line 1842 "parser.tab.c"
    break;

  case 23:
#line 137 "parser.y"
                                                               {  (yyval.tree) = NULL; yyerrok; }
#line 1848 "parser.tab.c"
    break;

  case 24:
#line 139 "parser.y"
                                                               {  (yyval.type) = Integer; }
#line 1854 "parser.tab.c"
    break;

  case 25:
#line 140 "parser.y"
                                                               {  (yyval.type) = Boolean; }
#line 1860 "parser.tab.c"
    break;

  case 26:
#line 141 "parser.y"
                                                               {  (yyval.type) = Char; }
#line 1866 "parser.tab.c"
    break;

  case 27:
#line 143 "parser.y"
                                                               {  (yyval.tree) = newDeclNode(FuncK, (yyvsp[-4].tokenData));
                                                                  (yyval.tree)->attr.name = strdup((yyvsp[-4].tokenData)->tokenstr);
                                                                  (yyval.tree)->expType = (yyvsp[-5].type);
                                                                  (yyval.tree)->child[0] = (yyvsp[-2].tree);
                                                                  (yyval.tree)->child[1] = (yyvsp[0].tree);
                                                               }
#line 1877 "parser.tab.c"
    break;

  case 28:
#line 149 "parser.y"
                                                               {  (yyval.tree) = newDeclNode(FuncK, (yyvsp[-4].tokenData));
                                                                  (yyval.tree)->attr.name = strdup((yyvsp[-4].tokenData)->tokenstr);
                                                                  //$$->expType = Void;
                                                                  (yyval.tree)->TD = (yyvsp[-4].tokenData);
                                                                  (yyval.tree)->child[0] = (yyvsp[-2].tree);
                                                                  (yyval.tree)->child[1] = (yyvsp[0].tree);
                                                               }
#line 1889 "parser.tab.c"
    break;

  case 29:
#line 156 "parser.y"
                                                               {  (yyval.tree) = NULL; }
#line 1895 "parser.tab.c"
    break;

  case 30:
#line 157 "parser.y"
                                                               {  (yyval.tree) = NULL; }
#line 1901 "parser.tab.c"
    break;

  case 31:
#line 158 "parser.y"
                                                               {  (yyval.tree) = NULL; }
#line 1907 "parser.tab.c"
    break;

  case 32:
#line 159 "parser.y"
                                                               {  (yyval.tree) = NULL; }
#line 1913 "parser.tab.c"
    break;

  case 33:
#line 161 "parser.y"
                                                               {  (yyval.tree) = (yyvsp[0].tree); }
#line 1919 "parser.tab.c"
    break;

  case 34:
#line 162 "parser.y"
                                                               {  (yyval.tree) = NULL; }
#line 1925 "parser.tab.c"
    break;

  case 35:
#line 164 "parser.y"
                                                               {  (yyval.tree) = addSibling((yyvsp[-2].tree), (yyvsp[0].tree)); }
#line 1931 "parser.tab.c"
    break;

  case 36:
#line 165 "parser.y"
                                                               {  (yyval.tree) = (yyvsp[0].tree); }
#line 1937 "parser.tab.c"
    break;

  case 37:
#line 166 "parser.y"
                                                               {  (yyval.tree) = NULL; }
#line 1943 "parser.tab.c"
    break;

  case 38:
#line 167 "parser.y"
                                                               {  (yyval.tree) = NULL; }
#line 1949 "parser.tab.c"
    break;

  case 39:
#line 169 "parser.y"
                                                               {  (yyval.tree) = (yyvsp[0].tree); 
                                                                  typeToSibling((yyval.tree), (yyvsp[-1].type));
                                                               }
#line 1957 "parser.tab.c"
    break;

  case 40:
#line 172 "parser.y"
                                                               {  (yyval.tree) = NULL; }
#line 1963 "parser.tab.c"
    break;

  case 41:
#line 174 "parser.y"
                                                               {  (yyval.tree) = addSibling((yyvsp[-2].tree), (yyvsp[0].tree));
                                                                  yyerrok; }
#line 1970 "parser.tab.c"
    break;

  case 42:
#line 176 "parser.y"
                                                               {  (yyval.tree) = (yyvsp[0].tree); }
#line 1976 "parser.tab.c"
    break;

  case 43:
#line 177 "parser.y"
                                                               {  (yyval.tree) = NULL; }
#line 1982 "parser.tab.c"
    break;

  case 44:
#line 178 "parser.y"
                                                               {  (yyval.tree) = NULL; }
#line 1988 "parser.tab.c"
    break;

  case 45:
#line 180 "parser.y"
                                                               {  (yyval.tree) = newDeclNode(ParamK, (yyvsp[0].tokenData)); 
                                                                  (yyval.tree)->attr.name = strdup((yyvsp[0].tokenData)->tokenstr);
                                                                  //$$->isInit = true;
                                                               }
#line 1997 "parser.tab.c"
    break;

  case 46:
#line 184 "parser.y"
                                                               {  (yyval.tree) = newDeclNode(ParamK, (yyvsp[-2].tokenData));
                                                                  (yyval.tree)->attr.name = strdup((yyvsp[-2].tokenData)->tokenstr);
                                                                  (yyval.tree)->isArray = true;
                                                                  //$$->isInit = true;
                                                                  //$$->expType = UndefinedType;
                                                               }
#line 2008 "parser.tab.c"
    break;

  case 47:
#line 191 "parser.y"
                                                               {  (yyval.tree) = (yyvsp[0].tree); }
#line 2014 "parser.tab.c"
    break;

  case 48:
#line 192 "parser.y"
                                                               {  (yyval.tree) = (yyvsp[0].tree); }
#line 2020 "parser.tab.c"
    break;

  case 49:
#line 194 "parser.y"
                                                               {  (yyval.tree) = (yyvsp[-1].tree); }
#line 2026 "parser.tab.c"
    break;

  case 50:
#line 195 "parser.y"
                                                               {  (yyval.tree) = NULL; }
#line 2032 "parser.tab.c"
    break;

  case 51:
#line 196 "parser.y"
                                                               {  (yyval.tree) = NULL;
                                                                  yyerrok;
                                                               }
#line 2040 "parser.tab.c"
    break;

  case 52:
#line 200 "parser.y"
                                                               {  (yyval.tree) = newStmtNode(CompoundK, (yyvsp[-3].tokenData));
                                                                  (yyval.tree)->isCompound = true;
                                                                  (yyval.tree)->child[0] = (yyvsp[-2].tree);
                                                                  (yyval.tree)->child[1] = (yyvsp[-1].tree);
                                                                  yyerrok;
                                                               }
#line 2051 "parser.tab.c"
    break;

  case 53:
#line 207 "parser.y"
                                                               {  (yyval.tree) = addSibling((yyvsp[-1].tree), (yyvsp[0].tree)); /*$2->isStatic = true;*/ }
#line 2057 "parser.tab.c"
    break;

  case 54:
#line 208 "parser.y"
                                                               {  (yyval.tree) = NULL; }
#line 2063 "parser.tab.c"
    break;

  case 55:
#line 210 "parser.y"
                                                               {  (yyval.tree) = addSibling((yyvsp[-1].tree), (yyvsp[0].tree)); }
#line 2069 "parser.tab.c"
    break;

  case 56:
#line 211 "parser.y"
                                                               {  (yyval.tree) = NULL; }
#line 2075 "parser.tab.c"
    break;

  case 57:
#line 213 "parser.y"
                                                               {  (yyval.tree) = (yyvsp[0].tree); }
#line 2081 "parser.tab.c"
    break;

  case 58:
#line 214 "parser.y"
                                                               {  (yyval.tree) = newStmtNode(IfK, (yyvsp[-5].tokenData)); 
                                                                  (yyval.tree)->child[0] = (yyvsp[-4].tree); 
                                                                  //$$->child[0]->expType = Boolean;
                                                                  // $1->child[0]->attr.value; //////////////////////////
                                                                  (yyval.tree)->child[1] = (yyvsp[-2].tree);
                                                                  (yyval.tree)->child[2] = (yyvsp[0].tree);   
                                                               }
#line 2093 "parser.tab.c"
    break;

  case 59:
#line 221 "parser.y"
                                                               {  (yyval.tree) = NULL; }
#line 2099 "parser.tab.c"
    break;

  case 60:
#line 222 "parser.y"
                                                               {  (yyval.tree) = NULL; yyerrok; }
#line 2105 "parser.tab.c"
    break;

  case 61:
#line 223 "parser.y"
                                                               {  (yyval.tree) = NULL; yyerrok; }
#line 2111 "parser.tab.c"
    break;

  case 62:
#line 224 "parser.y"
                                                               {  (yyval.tree) = newStmtNode(WhileK, (yyvsp[-3].tokenData));
                                                                  (yyval.tree)->attr.name = (yyvsp[-3].tokenData)->tokenstr;
                                                                  (yyval.tree)->child[0] = (yyvsp[-2].tree);
                                                                  //$$->child[0]->expType = Boolean;
                                                                  (yyval.tree)->child[1] = (yyvsp[0].tree);
                                                               }
#line 2122 "parser.tab.c"
    break;

  case 63:
#line 230 "parser.y"
                                                               {  (yyval.tree) = NULL; yyerrok; }
#line 2128 "parser.tab.c"
    break;

  case 64:
#line 231 "parser.y"
                                                               {  (yyval.tree) = NULL; }
#line 2134 "parser.tab.c"
    break;

  case 65:
#line 232 "parser.y"
                                                               {  (yyval.tree) = newStmtNode(ForK, (yyvsp[-5].tokenData));
                                                                  (yyval.tree)->child[0] = newDeclNode(VarK, (yyvsp[-4].tokenData));
                                                                  (yyval.tree)->child[0]->expType = Integer;
                                                                  //$$->attr.op = $3->tokenclass;
                                                                  //$$->child[0]->expType = UndefinedType;
                                                                  (yyval.tree)->attr.name = (yyvsp[-3].tokenData)->tokenstr;
                                                                  //printf("attr.name: %s\n", $$->attr.name);
                                                                  //$$->child[1]->expType = UndefinedType;
                                                                  (yyval.tree)->child[1] = (yyvsp[-2].tree);
                                                                  (yyval.tree)->child[2] = (yyvsp[0].tree);
                                                                  //$$->child[2]->expType = Integer;
                                                               }
#line 2151 "parser.tab.c"
    break;

  case 66:
#line 244 "parser.y"
                                                               {  (yyval.tree) = NULL; yyerrok; }
#line 2157 "parser.tab.c"
    break;

  case 67:
#line 245 "parser.y"
                                                               {  (yyval.tree) = NULL; }
#line 2163 "parser.tab.c"
    break;

  case 68:
#line 247 "parser.y"
                                                               {  (yyval.tree) = newStmtNode(IfK, (yyvsp[-5].tokenData)); 
                                                                  (yyval.tree)->child[0] = (yyvsp[-4].tree);
                                                                  (yyval.tree)->child[1] = (yyvsp[-2].tree);
                                                                  (yyval.tree)->child[2] = (yyvsp[0].tree);
                                                               }
#line 2173 "parser.tab.c"
    break;

  case 69:
#line 252 "parser.y"
                                                               {  (yyval.tree) = NULL;
                                                                  yyerrok;
                                                               }
#line 2181 "parser.tab.c"
    break;

  case 70:
#line 255 "parser.y"
                                                               {  (yyval.tree) = newStmtNode(WhileK, (yyvsp[-3].tokenData));
                                                                  (yyval.tree)->attr.name = (yyvsp[-3].tokenData)->tokenstr;
                                                                  (yyval.tree)->child[0] = (yyvsp[-2].tree);
                                                                  //$$->child[0]->expType = Boolean;
                                                                  (yyval.tree)->child[1] = (yyvsp[0].tree);
                                                               }
#line 2192 "parser.tab.c"
    break;

  case 71:
#line 261 "parser.y"
                                                               {  (yyval.tree) = NULL;
                                                                  yyerrok;
                                                               }
#line 2200 "parser.tab.c"
    break;

  case 72:
#line 264 "parser.y"
                                                               {  (yyval.tree) = newStmtNode(ForK, (yyvsp[-5].tokenData));
                                                                  (yyval.tree)->child[0] = newDeclNode(VarK, (yyvsp[-4].tokenData));
                                                                  (yyval.tree)->child[0]->expType = Integer;
                                                                  //$$->child[0]->expType = UndefinedType;
                                                                  //$$->attr.op = $3->tokenclass;
                                                                  (yyval.tree)->attr.name = (yyvsp[-3].tokenData)->tokenstr;
                                                                  (yyval.tree)->child[1] = (yyvsp[-2].tree);
                                                                  //$$->child[1]->expType = UndefinedType;
                                                                  (yyval.tree)->child[2] = (yyvsp[0].tree);
                                                                  //$$->child[2]->expType = Integer;
                                                               }
#line 2216 "parser.tab.c"
    break;

  case 73:
#line 275 "parser.y"
                                                               {  (yyval.tree) = NULL;
                                                                  yyerrok;
                                                               }
#line 2224 "parser.tab.c"
    break;

  case 74:
#line 278 "parser.y"
                                                               {  (yyval.tree) = NULL; }
#line 2230 "parser.tab.c"
    break;

  case 75:
#line 279 "parser.y"
                                                               {  (yyval.tree) = newStmtNode(IfK, (yyvsp[-3].tokenData)); 
                                                                  (yyval.tree)->child[0] = (yyvsp[-2].tree);
                                                                  (yyval.tree)->child[1] = (yyvsp[0].tree);
                                                               }
#line 2239 "parser.tab.c"
    break;

  case 76:
#line 283 "parser.y"
                                                               {  (yyval.tree) = NULL;
                                                                  yyerrok;
                                                               }
#line 2247 "parser.tab.c"
    break;

  case 77:
#line 287 "parser.y"
                                                               {  (yyval.tree) = (yyvsp[0].tree); }
#line 2253 "parser.tab.c"
    break;

  case 78:
#line 288 "parser.y"
                                                               {  (yyval.tree) = (yyvsp[0].tree); }
#line 2259 "parser.tab.c"
    break;

  case 79:
#line 289 "parser.y"
                                                               {  (yyval.tree) = (yyvsp[0].tree); }
#line 2265 "parser.tab.c"
    break;

  case 80:
#line 290 "parser.y"
                                                               {  (yyval.tree) = (yyvsp[0].tree); }
#line 2271 "parser.tab.c"
    break;

  case 81:
#line 292 "parser.y"
                                                               {  (yyval.tree) = newStmtNode(RangeK, (yyvsp[-1].tokenData));
                                                                  (yyval.tree)->child[0] = (yyvsp[-2].tree);
                                                                  (yyval.tree)->child[1] = (yyvsp[0].tree);
                                                                  //$$->child[0]->expType = UndefinedType;
                                                                  //$$->child[1]->expType = UndefinedType;
                                                                  //$$->child[2] = newExpNode(ConstantK, $1);
                                                                  //$$->child[2]->attr.value = 1;
                                                               }
#line 2284 "parser.tab.c"
    break;

  case 82:
#line 300 "parser.y"
                                                               {  (yyval.tree) = NULL; }
#line 2290 "parser.tab.c"
    break;

  case 83:
#line 301 "parser.y"
                                                               {  (yyval.tree) = NULL; yyerrok; }
#line 2296 "parser.tab.c"
    break;

  case 84:
#line 302 "parser.y"
                                                               {  (yyval.tree) = NULL; }
#line 2302 "parser.tab.c"
    break;

  case 85:
#line 303 "parser.y"
                                                               {  (yyval.tree) = newStmtNode(RangeK, (yyvsp[-3].tokenData));
                                                                  (yyval.tree)->child[0] = (yyvsp[-4].tree);
                                                                  (yyval.tree)->child[1] = (yyvsp[-2].tree);
                                                                  (yyval.tree)->child[2] = (yyvsp[0].tree);
                                                                  //$$->child[0]->expType = UndefinedType;
                                                                  //$$->child[1]->expType = UndefinedType;
                                                                  //$$->child[2]->expType = UndefinedType;
                                                               }
#line 2315 "parser.tab.c"
    break;

  case 86:
#line 312 "parser.y"
                                                               {  (yyval.tree) = newStmtNode(ReturnK, (yyvsp[-1].tokenData)); 
                                                                  //$$->attr.op = $1->tokenclass; 
                                                                  (yyval.tree)->attr.name = (yyvsp[-1].tokenData)->tokenstr;
                                                               }
#line 2324 "parser.tab.c"
    break;

  case 87:
#line 316 "parser.y"
                                                               {  (yyval.tree) = newStmtNode(ReturnK, (yyvsp[-2].tokenData));
                                                                  //$$->attr.op = $1->tokenclass;
                                                                  (yyval.tree)->attr.name = (yyvsp[-2].tokenData)->tokenstr;
                                                                  (yyval.tree)->expType = (yyvsp[-1].tree)->expType;
                                                                  (yyval.tree)->child[0] = (yyvsp[-1].tree);
                                                                  yyerrok;
                                                               }
#line 2336 "parser.tab.c"
    break;

  case 88:
#line 323 "parser.y"
                                                               {  (yyval.tree) = NULL;
                                                                  yyerrok;
                                                               }
#line 2344 "parser.tab.c"
    break;

  case 89:
#line 327 "parser.y"
                                                               {  (yyval.tree) = newStmtNode(BreakK, (yyvsp[-1].tokenData));
                                                                  //$$->attr.op = $1->tokenclass;
                                                                  (yyval.tree)->attr.name = (yyvsp[-1].tokenData)->tokenstr;
                                                               }
#line 2353 "parser.tab.c"
    break;

  case 90:
#line 332 "parser.y"
                                                               {  (yyval.tree) = newExpNode(AssignK, (yyvsp[-1].tokenData));
                                                                  //$$->attr.op = $2->tokenclass;
                                                                  (yyval.tree)->attr.name = (yyvsp[-1].tokenData)->tokenstr;
                                                                  //$$->expType = UndefinedType;
                                                                  (yyval.tree)->child[0] = (yyvsp[-2].tree);
                                                                  (yyval.tree)->child[1] = (yyvsp[0].tree);
                                                               }
#line 2365 "parser.tab.c"
    break;

  case 91:
#line 339 "parser.y"
                                                               {  (yyval.tree) = NULL;
                                                                  yyerrok;
                                                               }
#line 2373 "parser.tab.c"
    break;

  case 92:
#line 342 "parser.y"
                                                               {  (yyval.tree) = NULL; }
#line 2379 "parser.tab.c"
    break;

  case 93:
#line 343 "parser.y"
                                                               {  (yyval.tree) = newExpNode(AssignK, (yyvsp[-1].tokenData));
                                                                  //$$->attr.op = $2->tokenclass;
                                                                  (yyval.tree)->attr.name = (yyvsp[-1].tokenData)->tokenstr;
                                                                  //$$->expType = Integer;
                                                                  (yyval.tree)->child[0] = (yyvsp[-2].tree);
                                                                  (yyval.tree)->child[1] = (yyvsp[0].tree);
                                                               }
#line 2391 "parser.tab.c"
    break;

  case 94:
#line 350 "parser.y"
                                                               {  (yyval.tree) = NULL; }
#line 2397 "parser.tab.c"
    break;

  case 95:
#line 351 "parser.y"
                                                               {  (yyval.tree) = newExpNode(AssignK, (yyvsp[-1].tokenData));
                                                                  //$$->attr.op = $2->tokenclass;
                                                                  (yyval.tree)->attr.name = (yyvsp[-1].tokenData)->tokenstr;
                                                                  //$$->expType = Integer;
                                                                  (yyval.tree)->child[0] = (yyvsp[-2].tree);
                                                                  (yyval.tree)->child[1] = (yyvsp[0].tree);
                                                               }
#line 2409 "parser.tab.c"
    break;

  case 96:
#line 358 "parser.y"
                                                               {  (yyval.tree) = NULL; }
#line 2415 "parser.tab.c"
    break;

  case 97:
#line 359 "parser.y"
                                                               {  (yyval.tree) = newExpNode(AssignK, (yyvsp[-1].tokenData));
                                                                  //$$->attr.op = $2->tokenclass;
                                                                  (yyval.tree)->attr.name = (yyvsp[-1].tokenData)->tokenstr;
                                                                  //$$->expType = Integer;
                                                                  (yyval.tree)->child[0] = (yyvsp[-2].tree);
                                                                  (yyval.tree)->child[1] = (yyvsp[0].tree);
                                                               }
#line 2427 "parser.tab.c"
    break;

  case 98:
#line 366 "parser.y"
                                                               {  (yyval.tree) = NULL; }
#line 2433 "parser.tab.c"
    break;

  case 99:
#line 367 "parser.y"
                                                               {  (yyval.tree) = newExpNode(AssignK, (yyvsp[-1].tokenData));
                                                                  //$$->attr.op = $2->tokenclass;
                                                                  (yyval.tree)->attr.name = (yyvsp[-1].tokenData)->tokenstr;
                                                                  //$$->expType = Integer;
                                                                  (yyval.tree)->child[0] = (yyvsp[-2].tree);
                                                                  (yyval.tree)->child[1] = (yyvsp[0].tree);
                                                               }
#line 2445 "parser.tab.c"
    break;

  case 100:
#line 374 "parser.y"
                                                               {  (yyval.tree) = NULL; }
#line 2451 "parser.tab.c"
    break;

  case 101:
#line 375 "parser.y"
                                                               {  (yyval.tree) = newExpNode(AssignK, (yyvsp[0].tokenData));
                                                                  //$$->attr.op = $2->tokenclass;
                                                                  (yyval.tree)->attr.name = (yyvsp[0].tokenData)->tokenstr;
                                                                  (yyval.tree)->expType = Integer;
                                                                  (yyval.tree)->child[0] = (yyvsp[-1].tree);
                                                               }
#line 2462 "parser.tab.c"
    break;

  case 102:
#line 381 "parser.y"
                                                               {  (yyval.tree) = NULL;
                                                                  yyerrok;
                                                               }
#line 2470 "parser.tab.c"
    break;

  case 103:
#line 384 "parser.y"
                                                               {  (yyval.tree) = newExpNode(AssignK, (yyvsp[0].tokenData));
                                                                  (yyval.tree)->attr.name = (yyvsp[0].tokenData)->tokenstr;
                                                                  //$$->attr.op = $2->tokenclass;
                                                                  (yyval.tree)->expType = Integer;
                                                                  (yyval.tree)->child[0] = (yyvsp[-1].tree);
                                                               }
#line 2481 "parser.tab.c"
    break;

  case 104:
#line 390 "parser.y"
                                                               {  (yyval.tree) = NULL;
                                                                  yyerrok;
                                                               }
#line 2489 "parser.tab.c"
    break;

  case 105:
#line 393 "parser.y"
                                                               {  (yyval.tree) = (yyvsp[0].tree); }
#line 2495 "parser.tab.c"
    break;

  case 106:
#line 395 "parser.y"
                                                               {  (yyval.tree) = newExpNode(OpK, (yyvsp[-1].tokenData)); 
                                                                  //$$->attr.op = $2->tokenclass;
                                                                  (yyval.tree)->attr.name = (yyvsp[-1].tokenData)->tokenstr;
                                                                  (yyval.tree)->expType = Boolean;
                                                                  (yyval.tree)->child[0] = (yyvsp[-2].tree);
                                                                  (yyval.tree)->child[1] = (yyvsp[0].tree);
                                                               }
#line 2507 "parser.tab.c"
    break;

  case 107:
#line 402 "parser.y"
                                                               {  (yyval.tree) = (yyvsp[-2].tree); }
#line 2513 "parser.tab.c"
    break;

  case 108:
#line 403 "parser.y"
                                                               {  (yyval.tree) = (yyvsp[0].tree); }
#line 2519 "parser.tab.c"
    break;

  case 109:
#line 405 "parser.y"
                                                               {  (yyval.tree) = newExpNode(OpK, (yyvsp[-1].tokenData));
                                                                  //$$->attr.op = $2->tokenclass;
                                                                  (yyval.tree)->attr.name = (yyvsp[-1].tokenData)->tokenstr;
                                                                  (yyval.tree)->expType = Boolean;
                                                                  (yyval.tree)->child[0] = (yyvsp[-2].tree);
                                                                  (yyval.tree)->child[1] = (yyvsp[0].tree);
                                                               }
#line 2531 "parser.tab.c"
    break;

  case 110:
#line 412 "parser.y"
                                                               {  (yyval.tree) = NULL; }
#line 2537 "parser.tab.c"
    break;

  case 111:
#line 413 "parser.y"
                                                               {  (yyval.tree) = (yyvsp[0].tree); }
#line 2543 "parser.tab.c"
    break;

  case 112:
#line 415 "parser.y"
                                                               {  (yyval.tree) = newExpNode(OpK, (yyvsp[-1].tokenData)); 
                                                                  (yyval.tree)->attr.name = (yyvsp[-1].tokenData)->tokenstr;
                                                                  //$$->attr.op = $1->tokenclass;
                                                                  (yyval.tree)->expType = Boolean;
                                                                  (yyval.tree)->child[0] = (yyvsp[0].tree);
                                                               }
#line 2554 "parser.tab.c"
    break;

  case 113:
#line 421 "parser.y"
                                                               {  (yyval.tree) = NULL; }
#line 2560 "parser.tab.c"
    break;

  case 114:
#line 422 "parser.y"
                                                               {  (yyval.tree) = (yyvsp[0].tree); }
#line 2566 "parser.tab.c"
    break;

  case 115:
#line 424 "parser.y"
                                                               {  (yyval.tree) = (yyvsp[-1].tree);
                                                                  (yyval.tree)->child[0] = (yyvsp[-2].tree);
                                                                  (yyval.tree)->child[1] = (yyvsp[0].tree);
                                                               }
#line 2575 "parser.tab.c"
    break;

  case 116:
#line 428 "parser.y"
                                                               {  (yyval.tree) = (yyvsp[0].tree); }
#line 2581 "parser.tab.c"
    break;

  case 117:
#line 429 "parser.y"
                                                               {  (yyval.tree) = NULL; }
#line 2587 "parser.tab.c"
    break;

  case 118:
#line 431 "parser.y"
                                                               {  (yyval.tree) = newExpNode(OpK, (yyvsp[0].tokenData)); 
                                                                  (yyval.tree)->attr.name = (yyvsp[0].tokenData)->tokenstr;
                                                                  (yyval.tree)->expType = Boolean;
                                                               }
#line 2596 "parser.tab.c"
    break;

  case 119:
#line 435 "parser.y"
                                                               {  (yyval.tree) = newExpNode(OpK, (yyvsp[0].tokenData)); 
                                                                  (yyval.tree)->attr.name = (yyvsp[0].tokenData)->tokenstr;
                                                                  (yyval.tree)->expType = Boolean;
                                                               }
#line 2605 "parser.tab.c"
    break;

  case 120:
#line 439 "parser.y"
                                                               {  (yyval.tree) = newExpNode(OpK, (yyvsp[0].tokenData)); 
                                                                  (yyval.tree)->attr.name = (yyvsp[0].tokenData)->tokenstr;
                                                                  (yyval.tree)->expType = Boolean;
                                                               }
#line 2614 "parser.tab.c"
    break;

  case 121:
#line 443 "parser.y"
                                                               {  (yyval.tree) = newExpNode(OpK, (yyvsp[0].tokenData)); 
                                                                  (yyval.tree)->attr.name = (yyvsp[0].tokenData)->tokenstr;
                                                                  (yyval.tree)->expType = Boolean;
                                                               }
#line 2623 "parser.tab.c"
    break;

  case 122:
#line 447 "parser.y"
                                                               {  (yyval.tree) = newExpNode(OpK, (yyvsp[0].tokenData)); 
                                                                  (yyval.tree)->attr.name = (yyvsp[0].tokenData)->tokenstr;
                                                                  (yyval.tree)->expType = Boolean;
                                                               }
#line 2632 "parser.tab.c"
    break;

  case 123:
#line 451 "parser.y"
                                                               {  (yyval.tree) = newExpNode(OpK, (yyvsp[0].tokenData)); 
                                                                  (yyval.tree)->attr.name = (yyvsp[0].tokenData)->tokenstr;
                                                                  (yyval.tree)->expType = Boolean;
                                                               }
#line 2641 "parser.tab.c"
    break;

  case 124:
#line 456 "parser.y"
                                                               {  (yyval.tree) = (yyvsp[-1].tree);
                                                                  (yyval.tree)->child[0] = (yyvsp[-2].tree);
                                                                  (yyval.tree)->child[1] = (yyvsp[0].tree);
                                                               }
#line 2650 "parser.tab.c"
    break;

  case 125:
#line 460 "parser.y"
                                                               {  (yyval.tree) = NULL; }
#line 2656 "parser.tab.c"
    break;

  case 126:
#line 461 "parser.y"
                                                               {  (yyval.tree) = (yyvsp[0].tree); }
#line 2662 "parser.tab.c"
    break;

  case 127:
#line 463 "parser.y"
                                                               {  (yyval.tree) = newExpNode(OpK, (yyvsp[0].tokenData));
                                                                  (yyval.tree)->attr.name = (yyvsp[0].tokenData)->tokenstr;
                                                                  //$$->attr.op = $1->tokenclass;
                                                                  (yyval.tree)->expType = Integer;
                                                               }
#line 2672 "parser.tab.c"
    break;

  case 128:
#line 468 "parser.y"
                                                               {  (yyval.tree) = newExpNode(OpK, (yyvsp[0].tokenData));
                                                                  (yyval.tree)->attr.name = (yyvsp[0].tokenData)->tokenstr;
                                                                  //$$->attr.op = $1->tokenclass;
                                                                  (yyval.tree)->expType = Integer;
                                                               }
#line 2682 "parser.tab.c"
    break;

  case 129:
#line 474 "parser.y"
                                                               {  (yyval.tree) = (yyvsp[-1].tree);
                                                                  (yyval.tree)->child[0] = (yyvsp[-2].tree);
                                                                  (yyval.tree)->child[1] = (yyvsp[0].tree);
                                                               }
#line 2691 "parser.tab.c"
    break;

  case 130:
#line 478 "parser.y"
                                                               {  (yyval.tree) = NULL; }
#line 2697 "parser.tab.c"
    break;

  case 131:
#line 479 "parser.y"
                                                               {  (yyval.tree) = (yyvsp[0].tree); }
#line 2703 "parser.tab.c"
    break;

  case 132:
#line 481 "parser.y"
                                                               {  (yyval.tree) = newExpNode(OpK, (yyvsp[0].tokenData));
                                                                  (yyval.tree)->attr.name = (yyvsp[0].tokenData)->tokenstr;
                                                                  //$$->attr.op = $1->tokenclass;
                                                                  (yyval.tree)->expType = Integer;
                                                               }
#line 2713 "parser.tab.c"
    break;

  case 133:
#line 486 "parser.y"
                                                               {  (yyval.tree) = newExpNode(OpK, (yyvsp[0].tokenData));
                                                                  (yyval.tree)->attr.name = (yyvsp[0].tokenData)->tokenstr;
                                                                  //$$->attr.op = $1->tokenclass;
                                                                  (yyval.tree)->expType = Integer;
                                                               }
#line 2723 "parser.tab.c"
    break;

  case 134:
#line 491 "parser.y"
                                                               {  (yyval.tree) = newExpNode(OpK, (yyvsp[0].tokenData));
                                                                  (yyval.tree)->attr.name = (yyvsp[0].tokenData)->tokenstr;
                                                                 // $$->attr.op = $1->tokenclass;
                                                                  (yyval.tree)->expType = Integer;
                                                               }
#line 2733 "parser.tab.c"
    break;

  case 135:
#line 497 "parser.y"
                                                               {  (yyval.tree) = (yyvsp[-1].tree);
                                                                  (yyval.tree)->child[0] = (yyvsp[0].tree);
                                                               }
#line 2741 "parser.tab.c"
    break;

  case 136:
#line 500 "parser.y"
                                                               {  (yyval.tree) = NULL; }
#line 2747 "parser.tab.c"
    break;

  case 137:
#line 501 "parser.y"
                                                               {  (yyval.tree) = (yyvsp[0].tree); }
#line 2753 "parser.tab.c"
    break;

  case 138:
#line 503 "parser.y"
                                                               {  yyerrok;
                                                                  (yyval.tree) = newExpNode(OpK, (yyvsp[0].tokenData));
                                                                  (yyval.tree)->attr.name = (yyvsp[0].tokenData)->tokenstr;
                                                                  //$$->attr.op = $1->tokenclass;
                                                                  (yyval.tree)->expType = Integer;
                                                                  (yyval.tree)->isUnary = true;
                                                               }
#line 2765 "parser.tab.c"
    break;

  case 139:
#line 510 "parser.y"
                                                               {  yyerrok;
                                                                  (yyval.tree) = newExpNode(OpK, (yyvsp[0].tokenData));
                                                                  (yyval.tree)->attr.name = (yyvsp[0].tokenData)->tokenstr;
                                                                  //$$->attr.op = $1->tokenclass;
                                                                  //$$->expType = Integer;
                                                                  (yyval.tree)->isUnary = true;
                                                               }
#line 2777 "parser.tab.c"
    break;

  case 140:
#line 517 "parser.y"
                                                               {  yyerrok;
                                                                  (yyval.tree) = newExpNode(OpK, (yyvsp[0].tokenData));
                                                                  (yyval.tree)->attr.name = (yyvsp[0].tokenData)->tokenstr;
                                                                  (yyval.tree)->expType = Integer;
                                                                  //$$->attr.op = $1->tokenclass;
                                                                  //$$->expType = Integer;
                                                               }
#line 2789 "parser.tab.c"
    break;

  case 141:
#line 525 "parser.y"
                                                               {  (yyval.tree) = (yyvsp[0].tree); }
#line 2795 "parser.tab.c"
    break;

  case 142:
#line 526 "parser.y"
                                                               {  (yyval.tree) = (yyvsp[0].tree); }
#line 2801 "parser.tab.c"
    break;

  case 143:
#line 528 "parser.y"
                                                               {  (yyval.tree) = newExpNode(IdK, (yyvsp[0].tokenData));
                                                                  (yyval.tree)->attr.name = strdup((yyvsp[0].tokenData)->tokenstr);
                                                                  //$$->expType = UndefinedType;
                                                               }
#line 2810 "parser.tab.c"
    break;

  case 144:
#line 532 "parser.y"
                                                               {  //$$->child[0] = newExpNode(IdK, $1);
                                                                  //printf("Here\n");
                                                                  (yyval.tree) = newExpNode(OpK, (yyvsp[-2].tokenData));
                                                                  //$$->attr.op = $2->tokenclass;
                                                                  //printf("Here2\n");
                                                                  (yyval.tree)->attr.name = (yyvsp[-2].tokenData)->tokenstr;
                                                                  (yyval.tree)->child[0] = newExpNode(IdK, (yyvsp[-3].tokenData));
                                                                  //printf("Here3\n");
                                                                  //$$->child[0] = $1;
                                                                  (yyval.tree)->child[0]->attr.name = (yyvsp[-3].tokenData)->tokenstr;
                                                                  (yyval.tree)->child[0]->isArray = true;
                                                                  (yyval.tree)->child[1] = (yyvsp[-1].tree);
                                                                  //$$->expType = UndefinedType;
                                                               }
#line 2829 "parser.tab.c"
    break;

  case 145:
#line 547 "parser.y"
                                                               {  (yyval.tree) = (yyvsp[-1].tree); 
                                                                  yyerrok;
                                                               }
#line 2837 "parser.tab.c"
    break;

  case 146:
#line 550 "parser.y"
                                                               {  (yyval.tree) = NULL; }
#line 2843 "parser.tab.c"
    break;

  case 147:
#line 551 "parser.y"
                                                               {  (yyval.tree) = (yyvsp[0].tree); }
#line 2849 "parser.tab.c"
    break;

  case 148:
#line 552 "parser.y"
                                                               {  (yyval.tree) = (yyvsp[0].tree); }
#line 2855 "parser.tab.c"
    break;

  case 149:
#line 554 "parser.y"
                                                               {  (yyval.tree) = newExpNode(CallK, (yyvsp[-3].tokenData));
                                                                  (yyval.tree)->attr.name = strdup((yyvsp[-3].tokenData)->tokenstr);
                                                                  (yyval.tree)->child[0] = (yyvsp[-1].tree);
                                                               }
#line 2864 "parser.tab.c"
    break;

  case 150:
#line 558 "parser.y"
                                                               {  (yyval.tree) = NULL;
                                                                  yyerrok;
                                                               }
#line 2872 "parser.tab.c"
    break;

  case 151:
#line 562 "parser.y"
                                                               {  (yyval.tree) = (yyvsp[0].tree); }
#line 2878 "parser.tab.c"
    break;

  case 152:
#line 563 "parser.y"
                                                               {  (yyval.tree) = NULL; }
#line 2884 "parser.tab.c"
    break;

  case 153:
#line 565 "parser.y"
                                                               {  (yyval.tree) = addSibling((yyvsp[-2].tree), (yyvsp[0].tree));  yyerrok; }
#line 2890 "parser.tab.c"
    break;

  case 154:
#line 566 "parser.y"
                                                               {  (yyval.tree) = (yyvsp[0].tree); }
#line 2896 "parser.tab.c"
    break;

  case 155:
#line 567 "parser.y"
                                                               {  (yyval.tree) = NULL; }
#line 2902 "parser.tab.c"
    break;

  case 156:
#line 569 "parser.y"
                                                               {  yyerrok;
                                                                  (yyval.tree) = newExpNode(ConstantK, (yyvsp[0].tokenData)); 
                                                                  (yyval.tree)->attr.value = (yyvsp[0].tokenData)->nvalue;
                                                                  (yyval.tree)->expType = Integer;
                                                                  (yyval.tree)->isInit = true;
                                                                  (yyval.tree)->isConstant = true;
                                                                  (yyval.tree)->memSize = 1;
                                                               }
#line 2915 "parser.tab.c"
    break;

  case 157:
#line 577 "parser.y"
                                                               {  yyerrok;
                                                                  (yyval.tree) = newExpNode(ConstantK, (yyvsp[0].tokenData));
                                                                  (yyval.tree)->TD = (yyvsp[0].tokenData);
                                                                  (yyval.tree)->attr.name = (yyvsp[0].tokenData)->tokenstr;
                                                                  //$$->attr.cvalue = $1->cvalue;
                                                                  (yyval.tree)->expType = Char;
                                                                  (yyval.tree)->isInit = true;
                                                                  (yyval.tree)->isCharacter = true;
                                                                  (yyval.tree)->isConstant;
                                                                  (yyval.tree)->memSize = 1;
                                                               }
#line 2931 "parser.tab.c"
    break;

  case 158:
#line 588 "parser.y"
                                                               {  yyerrok;
                                                                  (yyval.tree) = newExpNode(ConstantK, (yyvsp[0].tokenData));
                                                                  (yyval.tree)->attr.string = strdup((yyvsp[0].tokenData)->svalue);
                                                                  (yyval.tree)->isArray = true;
                                                                  (yyval.tree)->expType = Char;
                                                                  (yyval.tree)->isCharacter = false;
                                                                  (yyval.tree)->isConstant = true;
                                                                  (yyval.tree)->memSize = (yyvsp[0].tokenData)->stringLength + 1;
                                                               }
#line 2945 "parser.tab.c"
    break;

  case 159:
#line 597 "parser.y"
                                                               {  yyerrok;
                                                                  (yyval.tree) = newExpNode(ConstantK, (yyvsp[0].tokenData));
                                                                  (yyval.tree)->attr.value = (yyvsp[0].tokenData)->nvalue;
                                                                  (yyval.tree)->attr.name = (yyvsp[0].tokenData)->tokenstr;
                                                                  (yyval.tree)->expType = Boolean;
                                                                  (yyval.tree)->isInit = true;
                                                                  (yyval.tree)->isConstant = true;
                                                                  (yyval.tree)->memSize = 1;
                                                               }
#line 2959 "parser.tab.c"
    break;


#line 2963 "parser.tab.c"

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
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

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
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *, YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
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

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
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
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;


#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif


/*-----------------------------------------------------.
| yyreturn -- parsing is finished, return the result.  |
`-----------------------------------------------------*/
yyreturn:
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
                  yystos[+*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 608 "parser.y"

extern int yydebug;
int main(int argc, char *argv[])
{
   extern int optind;
   int c = 0;
   bool printSyntaxTree = 0;
   TreeNode *tmp;
   int selectOption;
   numErrors = 0;
   numWarnings = 0;
   m = false;
   Loffset = 0;
   Goffset = 0;

   while((c = getopt(argc, argv, "dDhMpP")) != -1)
   {
      switch(c)
      {
         case 'c':
            //do nothing
            break;
         case 'd':
            yydebug=1;
            break;
         case 'D':
            st.debug(1);
            break;
         case 'h':
            printf("usage: -c [options] [sourcefile]\n");
            printf("options:\n");
            printf("-d     - turn on parser debugging\n");
            printf("-D     - turn on symbol table debugging\n");
            printf("-h     - print this usage message\n");
            printf("-M     - print the abstract syntax tree with memory locations\n");
            printf("-p     - print the abstract syntax tree\n");
            printf("-P     - print the abstract syntax tree plus type information\n");
            break;
         case 'M':
            printSyntaxTree = true;
            selectOption = 1;
            m = true;
            PAST = true;
            displayOffset = true;
            break;
         case 'p':
            //yyparse();
            printSyntaxTree = true;
            selectOption = 0;
            break;
         case 'P':
            // printAST with type information added.
            //yyparse();
            //analyze(syntaxTree);

            printSyntaxTree = true;
            selectOption = 1;
            PAST = true;
            break;
         default:
            exit(1);
      }
   }


   if(argc > optind)
   {
      if((yyin = fopen(argv[argc - 1], "r")))
      {
         // file open successful
         // if(!strcmp(argv[argc - 1], "syntaxerr-logic.c-"))
         // {
            //yydebug = 1;
         //}
      }
      else
      {
         // failed to open file
         printf("ERROR(ARGLIST): source file \"%s\" could not be opened.\n", argv[1]);
         numErrors++;
         printf("Number of warnings: 0\n");
         printf("Number of errors: %i\n", numErrors);
         exit(1);
      }
   }

   initErrorProcessing();
   yyparse();

   if(printSyntaxTree && selectOption == 0 && numErrors == 0)
   {
      printTree(syntaxTree, 0);
   }
   else if(printSyntaxTree && selectOption == 1 && numErrors == 0)
   {
      prototype();
      analyze(syntaxTree);
      tmp = (TreeNode *)st.lookup("main");

      if(tmp != NULL && tmp->nodekind == DeclK && (tmp->subkind.decl != FuncK && tmp->subkind.decl == ParamK) || tmp == NULL)
      {
         printf("ERROR(LINKER): A function named 'main' with no parameters must be defined.\n");
         numErrors++;
      }
      else if(tmp != NULL && tmp->nodekind == DeclK && tmp->subkind.decl != FuncK)
      {
         if(tmp->child[0] != NULL)
         {
            printf("ERROR(LINKER): A function named 'main' with no parameters must be defined.\n");
            numErrors++;
         }
      }
      else if(tmp->child[0] != NULL && tmp->child[0]->subkind.decl == ParamK && tmp != NULL)
      {
         printf("ERROR(LINKER): A function named 'main' with no parameters must be defined.\n");
         numErrors++;
      }
      if(numErrors < 1)
         printTree(syntaxTree, 0);
   }
   //printTree(syntaxTree, 0);

   if(displayOffset == true)
      printf("Offset for end of global space: %d\n", Goffset);
   printf("Number of warnings: %d\n", numWarnings);
   printf("Number of errors: %d\n", numErrors);
   return 0;
}
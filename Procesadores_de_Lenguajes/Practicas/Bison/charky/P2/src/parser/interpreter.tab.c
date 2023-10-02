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
#line 6 "interpreter.y"

#include <iostream>
#include <string>

/* pow */
#include <math.h>

/* Use for recovery of runtime errors */
#include <setjmp.h>
#include <signal.h>

/* Error recovery functions */
#include "../error/error.hpp"

/* Macros for the screen */
#include "../includes/macros.hpp"

/* IMPORTANT: this file must be before init.hpp */
#include "../ast/ast.hpp"

/* Table of symbol */
#include "../table/table.hpp"

#include "../table/numericVariable.hpp"

#include "../table/logicalVariable.hpp"

#include "../table/numericConstant.hpp"

#include "../table/logicalConstant.hpp"

#include "../table/builtinParameter1.hpp"

#include "../table/builtinParameter0.hpp"
#include "../table/builtinParameter2.hpp"

#include "../table/init.hpp"

/*! 
	\brief  Lexical or scanner function
	\return int
	\note   C++ requires that yylex returns an int value
	\sa     yyparser
*/
int yylex();

extern int lineNumber; //!< External line counter

extern bool interactiveMode; //!< Control the interactive mode of execution of the interpreter

extern int control; //!< External: to control the interactive mode in "if" and "while" sentences 

extern std::string progname; //!<  Program name

/*
	jhmp_buf
	This is an array type capable of storing the information of a calling environment to be restored later.
	This information is filled by calling macro setjmp and can be restored by calling function longjmp.
*/
jmp_buf begin; //!<  It enables recovery of runtime errors 

extern lp::Table table; //!< Extern Table of Symbols

extern lp::AST *root; //!< External root of the abstract syntax tree AST


#line 137 "interpreter.tab.c"

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
# define YYERROR_VERBOSE 1
#endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
#ifndef YY_YY_INTERPRETER_TAB_H_INCLUDED
# define YY_YY_INTERPRETER_TAB_H_INCLUDED
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
    PLACECURSOR = 258,
    CLEAR = 259,
    SEMICOLON = 260,
    TWO_POINTS = 261,
    ASK_FOR_KEY = 262,
    PRINT = 263,
    READ = 264,
    READ_STRING = 265,
    IF = 266,
    THEN = 267,
    END_IF = 268,
    ELSE = 269,
    WHILE = 270,
    DO = 271,
    END_WHILE = 272,
    DO_WHILE = 273,
    UNTIL = 274,
    FOR = 275,
    FROM = 276,
    STEP = 277,
    END_FOR = 278,
    SWITCH = 279,
    VALUE = 280,
    DEFAULT = 281,
    END_SWITCH = 282,
    LETFCURLYBRACKET = 283,
    RIGHTCURLYBRACKET = 284,
    ASSIGNMENT = 285,
    COMMA = 286,
    NUMBER = 287,
    STRING = 288,
    BOOL = 289,
    VARIABLE = 290,
    UNDEFINED = 291,
    CONSTANT = 292,
    BUILTIN = 293,
    OR = 294,
    AND = 295,
    GREATER_OR_EQUAL = 296,
    LESS_OR_EQUAL = 297,
    GREATER_THAN = 298,
    LESS_THAN = 299,
    EQUAL = 300,
    NOT_EQUAL = 301,
    NOT = 302,
    PLUS = 303,
    MINUS = 304,
    CONCATENATION = 305,
    MULTIPLICATION = 306,
    DIVISION = 307,
    INTEGER_DIVISION = 308,
    MODULO = 309,
    LPAREN = 310,
    RPAREN = 311,
    UNARY = 312,
    POWER = 313
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 80 "interpreter.y"

  char * identifier;
  double number;  
  bool logic;
  lp::ExpNode *expNode;
  std::list<lp::ExpNode *>  *parameters;    // NOTE: #include<list> must be in interpreter.l, init.cpp, interpreter.cpp
  std::list<lp::Statement *> *stmts;
  std::list<lp::Value *> *switchValues;
  lp::Statement *st;
  lp::AST *prog;

#line 260 "interpreter.tab.c"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_INTERPRETER_TAB_H_INCLUDED  */



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
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   1698

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  59
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  24
/* YYNRULES -- Number of rules.  */
#define YYNRULES  92
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  253

#define YYUNDEFTOK  2
#define YYMAXUTOK   313


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
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   152,   152,   164,   168,   189,   200,   205,   210,   211,
     212,   213,   214,   215,   216,   217,   218,   219,   220,   221,
     225,   233,   240,   248,   252,   257,   264,   269,   276,   281,
     288,   293,   298,   302,   306,   310,   314,   318,   322,   326,
     330,   334,   338,   342,   349,   357,   364,   375,   378,   385,
     395,   402,   406,   410,   414,   421,   425,   432,   439,   443,
     450,   456,   462,   466,   473,   475,   477,   479,   481,   483,
     485,   487,   489,   491,   493,   495,   497,   499,   501,   503,
     505,   507,   509,   511,   513,   515,   517,   519,   521,   568,
     571,   580,   583
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 1
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "PLACECURSOR", "CLEAR", "SEMICOLON",
  "TWO_POINTS", "ASK_FOR_KEY", "PRINT", "READ", "READ_STRING", "IF",
  "THEN", "END_IF", "ELSE", "WHILE", "DO", "END_WHILE", "DO_WHILE",
  "UNTIL", "FOR", "FROM", "STEP", "END_FOR", "SWITCH", "VALUE", "DEFAULT",
  "END_SWITCH", "LETFCURLYBRACKET", "RIGHTCURLYBRACKET", "ASSIGNMENT",
  "COMMA", "NUMBER", "STRING", "BOOL", "VARIABLE", "UNDEFINED", "CONSTANT",
  "BUILTIN", "OR", "AND", "GREATER_OR_EQUAL", "LESS_OR_EQUAL",
  "GREATER_THAN", "LESS_THAN", "EQUAL", "NOT_EQUAL", "NOT", "PLUS",
  "MINUS", "CONCATENATION", "MULTIPLICATION", "DIVISION",
  "INTEGER_DIVISION", "MODULO", "LPAREN", "RPAREN", "UNARY", "POWER",
  "$accept", "program", "stmtlist", "stmt", "block", "controlSymbol", "if",
  "while", "do_while", "for", "switch", "listOfValues",
  "restOfListOfValues", "cond", "asgn", "ask_for_key", "print", "read",
  "placecursor", "clear", "read_string", "exp", "listOfExp",
  "restOfListOfExp", YY_NULLPTR
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
     305,   306,   307,   308,   309,   310,   311,   312,   313
};
# endif

#define YYPACT_NINF (-216)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-48)

#define yytable_value_is_error(Yyn) \
  ((Yyn) == YYTABLE_NINF)

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -216,     5,   583,  -216,  -216,   -42,  -216,  -216,    13,  1449,
      17,    18,  -216,  -216,  -216,  -216,  -216,  -216,     6,    44,
    -216,  -216,    70,    71,    73,    74,    85,    93,    94,    95,
      97,    99,   100,   101,  1449,   211,  -216,  -216,  -216,  -216,
      52,  1449,  1449,  1449,  1449,  1585,   -31,   -19,    53,    53,
    -216,    29,    55,   723,  1468,  1468,  -216,  -216,  -216,  -216,
    -216,  -216,  -216,  -216,  -216,  -216,  -216,  -216,  1401,  -216,
    1485,  1449,   125,    57,    57,  1505,  1449,  1449,  1449,  1449,
    1449,  1449,  1449,  1449,  1449,  1449,  1449,  1449,  1449,  1449,
    1449,  1449,    60,    61,    64,    66,  1449,   111,   109,   217,
     -18,    92,  1449,  -216,     6,    44,  -216,  1585,  -216,  1585,
    1449,  -216,  1425,    76,  -216,  1604,  1622,  1640,  1640,  1640,
    1640,  1640,  1640,   -26,   -26,   -26,    57,    57,    57,    57,
      57,  -216,  -216,  -216,  -216,  1525,  -216,   618,  -216,   758,
      53,  -216,  1382,   499,  1449,  1545,  1565,  1449,  -216,  -216,
    -216,   653,  -216,  -216,   793,  -216,  -216,  1449,   234,  1449,
     527,   102,  -216,  1425,  -216,  -216,   828,  -216,    43,  -216,
      96,  1449,   273,  1449,    -9,   104,  -216,   863,  -216,  -216,
    1449,   898,  -216,  1449,   312,   371,  -216,  1449,   351,   129,
     133,   135,  -216,   933,   391,  -216,   968,   411,  -216,  1449,
    1003,  -216,  1038,   431,  -216,  1449,  -216,  -216,  -216,  -216,
    -216,  -216,  -216,  1073,   451,  -216,  1108,  -216,  -216,  1143,
     471,   688,   688,  1178,  1213,  1248,  -216,  -216,  1283,  -216,
    1318,  -216,  -216,    28,  -216,  -216,  -216,  -216,  -216,  1353,
    -216,  -216,  1388,   136,   140,  -216,  -216,  -216,  -216,   688,
     688,  -216,  -216
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       3,     0,     0,     1,     5,     0,    61,     6,     0,     0,
       0,     0,    21,    21,    21,    21,    21,     3,     0,     0,
       4,    17,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    64,    65,    77,    78,
       0,     0,     0,     0,     0,    57,     0,     0,     0,     0,
       3,     0,     0,     0,     0,     0,    12,    13,    14,    15,
      16,     7,     8,     9,    10,    18,    19,    11,     0,    56,
       0,    89,    87,    73,    74,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     3,     3,     0,
       0,     0,     0,    20,    77,    78,    52,    51,    54,    53,
       0,    55,    91,     0,    72,    86,    85,    80,    82,    79,
      81,    83,    84,    66,    67,    71,    68,    69,    70,    75,
      76,    58,    59,    62,    63,     0,     3,     0,     3,     0,
       0,    29,     0,     0,     0,     0,     0,     0,    90,    88,
      50,     0,    23,     3,     0,    27,    28,     0,     0,     0,
       0,     0,    60,    91,    22,     3,     0,    26,     0,     3,
       0,     0,     0,     0,     0,     0,    92,     0,    25,     3,
       0,     0,     3,     0,     3,     0,     3,     0,     0,     0,
       0,     0,    24,     0,     0,    38,     0,     0,     3,     0,
       0,     3,     0,     0,     3,     0,     3,     3,     3,    42,
       3,    43,     3,     0,     3,    39,     0,    37,     3,     0,
       0,     0,     0,     0,     0,     0,    31,     3,     0,    35,
       0,    33,     3,     0,    45,    46,    44,    40,    41,     0,
      36,    34,     0,     0,     0,    30,    32,     3,     3,     0,
       0,    48,    49
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -216,  -216,   -17,  -216,  -216,    26,  -216,  -216,  -216,  -216,
    -216,  -216,  -215,   -37,    16,  -216,  -216,  -216,  -216,  -216,
    -216,   -33,  -216,   -14
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     2,    20,    21,    48,    22,    23,    24,    25,
      26,   175,   234,    97,    27,    28,    29,    30,    31,    32,
      33,    45,   113,   148
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      53,    68,    70,   142,    92,     3,    93,   235,    72,    73,
      74,    75,    98,    34,    36,    37,    94,    38,    95,    39,
      40,   107,   109,   189,   190,    87,    88,    89,    90,    41,
      42,    43,    91,    99,   251,   252,    54,    44,   112,    49,
      50,    51,    52,   115,   116,   117,   118,   119,   120,   121,
     122,   123,   124,   125,   126,   127,   128,   129,   130,   179,
     243,   244,   141,   135,   100,   180,   101,   143,    35,   145,
     106,   108,    46,    47,    55,    56,    57,   146,    58,    59,
     137,   139,    76,    77,    78,    79,    80,    81,    82,    83,
      60,    84,    85,    86,    87,    88,    89,    90,    61,    62,
      63,    91,    64,   156,    65,    66,    67,    71,    96,   158,
     102,   160,   182,   144,   163,    91,   131,   132,   183,   151,
     133,   154,   134,   136,   168,   138,   172,   174,    36,    37,
     191,    38,   149,    39,    40,   206,   166,   184,   185,   207,
     188,   208,   247,    41,    42,    43,   248,   194,   177,   176,
     197,    44,   181,     0,   203,     0,     0,     0,     0,     0,
       0,     0,   193,     0,     0,   196,   214,   200,     0,   202,
       0,     0,   220,    84,    85,    86,    87,    88,    89,    90,
       0,   213,     0,    91,   216,     0,     0,   219,     0,   221,
     222,   223,     0,   224,     0,   225,     0,   228,     0,     0,
       0,   230,     0,     0,     0,     0,     0,     0,     0,     0,
     239,     0,     0,     0,     0,   242,     0,     0,     4,     0,
       5,     6,     7,     0,     8,     9,    10,    11,    12,     0,
     249,   250,    13,     0,     0,    14,   140,    15,     0,     0,
       0,    16,     0,    36,    37,    17,    38,     0,    39,    40,
     169,     0,    18,   170,    19,     0,   171,     0,    41,    42,
      43,     0,     0,     0,     0,     0,    44,    69,     0,     0,
       0,     0,    96,    76,    77,    78,    79,    80,    81,    82,
      83,     0,    84,    85,    86,    87,    88,    89,    90,   186,
       0,     0,    91,     0,     0,   187,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    76,    77,    78,    79,    80,    81,    82,    83,
       0,    84,    85,    86,    87,    88,    89,    90,   198,     0,
       0,    91,     0,     0,   199,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    76,    77,    78,    79,    80,    81,    82,    83,     0,
      84,    85,    86,    87,    88,    89,    90,   204,     0,     0,
      91,     0,     0,   205,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   201,     0,     0,
      76,    77,    78,    79,    80,    81,    82,    83,     0,    84,
      85,    86,    87,    88,    89,    90,     0,   210,     0,    91,
      76,    77,    78,    79,    80,    81,    82,    83,     0,    84,
      85,    86,    87,    88,    89,    90,     0,   212,     0,    91,
      76,    77,    78,    79,    80,    81,    82,    83,     0,    84,
      85,    86,    87,    88,    89,    90,     0,   218,     0,    91,
      76,    77,    78,    79,    80,    81,    82,    83,     0,    84,
      85,    86,    87,    88,    89,    90,     0,   227,     0,    91,
      76,    77,    78,    79,    80,    81,    82,    83,     0,    84,
      85,    86,    87,    88,    89,    90,     0,   232,     0,    91,
      76,    77,    78,    79,    80,    81,    82,    83,     0,    84,
      85,    86,    87,    88,    89,    90,     0,     0,     0,    91,
      76,    77,    78,    79,    80,    81,    82,    83,   159,    84,
      85,    86,    87,    88,    89,    90,     0,     0,     0,    91,
       0,     0,     0,     0,     0,     0,     0,     0,    76,    77,
      78,    79,    80,    81,    82,    83,   173,    84,    85,    86,
      87,    88,    89,    90,     0,     0,     0,    91,     0,     0,
       0,     0,     0,     0,     0,     0,    76,    77,    78,    79,
      80,    81,    82,    83,     0,    84,    85,    86,    87,    88,
      89,    90,     0,    -2,     4,    91,     5,     6,     7,     0,
       8,     9,    10,    11,    12,     0,     0,     0,    13,     0,
       0,    14,     0,    15,     0,     0,     0,    16,     0,     0,
       0,    17,     0,     0,     0,     0,     0,     0,    18,     4,
      19,     5,     6,     7,     0,     8,     9,    10,    11,    12,
       0,   152,   153,    13,     0,     0,    14,     0,    15,     0,
       0,     0,    16,     0,     0,     0,    17,     0,     0,     0,
       0,     0,     0,    18,     4,    19,     5,     6,     7,     0,
       8,     9,    10,    11,    12,     0,   164,   165,    13,     0,
       0,    14,     0,    15,     0,     0,     0,    16,     0,     0,
       0,    17,     0,     0,     0,     0,     0,     0,    18,     4,
      19,     5,     6,     7,     0,     8,     9,    10,    11,    12,
       0,     0,     0,    13,     0,     0,    14,     0,    15,     0,
       0,     0,    16,   233,   -47,     0,    17,     0,     0,     0,
       0,     0,     0,    18,     4,    19,     5,     6,     7,     0,
       8,     9,    10,    11,    12,     0,     0,     0,    13,     0,
       0,    14,     0,    15,     0,     0,     0,    16,     0,     0,
       0,    17,   103,     0,     0,     0,     0,     0,    18,     4,
      19,     5,     6,     7,     0,     8,     9,    10,    11,    12,
       0,     0,     0,    13,     0,   155,    14,     0,    15,     0,
       0,     0,    16,     0,     0,     0,    17,     0,     0,     0,
       0,     0,     0,    18,     4,    19,     5,     6,     7,     0,
       8,     9,    10,    11,    12,     0,     0,     0,    13,     0,
     167,    14,     0,    15,     0,     0,     0,    16,     0,     0,
       0,    17,     0,     0,     0,     0,     0,     0,    18,     4,
      19,     5,     6,     7,     0,     8,     9,    10,    11,    12,
       0,   178,     0,    13,     0,     0,    14,     0,    15,     0,
       0,     0,    16,     0,     0,     0,    17,     0,     0,     0,
       0,     0,     0,    18,     4,    19,     5,     6,     7,     0,
       8,     9,    10,    11,    12,     0,   192,     0,    13,     0,
       0,    14,     0,    15,     0,     0,     0,    16,     0,     0,
       0,    17,     0,     0,     0,     0,     0,     0,    18,     4,
      19,     5,     6,     7,     0,     8,     9,    10,    11,    12,
       0,     0,     0,    13,     0,     0,    14,     0,    15,     0,
       0,   195,    16,     0,     0,     0,    17,     0,     0,     0,
       0,     0,     0,    18,     4,    19,     5,     6,     7,     0,
       8,     9,    10,    11,    12,     0,     0,     0,    13,     0,
       0,    14,     0,    15,     0,     0,   209,    16,     0,     0,
       0,    17,     0,     0,     0,     0,     0,     0,    18,     4,
      19,     5,     6,     7,     0,     8,     9,    10,    11,    12,
       0,     0,     0,    13,     0,     0,    14,     0,    15,     0,
       0,   211,    16,     0,     0,     0,    17,     0,     0,     0,
       0,     0,     0,    18,     4,    19,     5,     6,     7,     0,
       8,     9,    10,    11,    12,     0,     0,     0,    13,     0,
       0,    14,     0,    15,     0,     0,   215,    16,     0,     0,
       0,    17,     0,     0,     0,     0,     0,     0,    18,     4,
      19,     5,     6,     7,     0,     8,     9,    10,    11,    12,
       0,     0,     0,    13,     0,     0,    14,     0,    15,     0,
       0,   217,    16,     0,     0,     0,    17,     0,     0,     0,
       0,     0,     0,    18,     4,    19,     5,     6,     7,     0,
       8,     9,    10,    11,    12,     0,     0,     0,    13,     0,
       0,    14,     0,    15,     0,     0,   226,    16,     0,     0,
       0,    17,     0,     0,     0,     0,     0,     0,    18,     4,
      19,     5,     6,     7,     0,     8,     9,    10,    11,    12,
       0,     0,     0,    13,     0,     0,    14,     0,    15,     0,
       0,   229,    16,     0,     0,     0,    17,     0,     0,     0,
       0,     0,     0,    18,     4,    19,     5,     6,     7,     0,
       8,     9,    10,    11,    12,     0,     0,     0,    13,     0,
       0,    14,     0,    15,     0,     0,   231,    16,     0,     0,
       0,    17,     0,     0,     0,     0,     0,     0,    18,     4,
      19,     5,     6,     7,     0,     8,     9,    10,    11,    12,
       0,     0,     0,    13,     0,     0,    14,     0,    15,     0,
       0,     0,    16,     0,     0,   236,    17,     0,     0,     0,
       0,     0,     0,    18,     4,    19,     5,     6,     7,     0,
       8,     9,    10,    11,    12,     0,     0,     0,    13,     0,
       0,    14,     0,    15,     0,     0,   237,    16,     0,     0,
       0,    17,     0,     0,     0,     0,     0,     0,    18,     4,
      19,     5,     6,     7,     0,     8,     9,    10,    11,    12,
       0,     0,     0,    13,     0,     0,    14,     0,    15,     0,
       0,   238,    16,     0,     0,     0,    17,     0,     0,     0,
       0,     0,     0,    18,     4,    19,     5,     6,     7,     0,
       8,     9,    10,    11,    12,     0,     0,     0,    13,     0,
       0,    14,     0,    15,     0,     0,   240,    16,     0,     0,
       0,    17,     0,     0,     0,     0,     0,     0,    18,     4,
      19,     5,     6,     7,     0,     8,     9,    10,    11,    12,
       0,     0,     0,    13,     0,     0,    14,     0,    15,     0,
       0,   241,    16,     0,     0,     0,    17,     0,     0,     0,
       0,     0,     0,    18,     4,    19,     5,     6,     7,     0,
       8,     9,    10,    11,    12,     0,     0,     0,    13,     0,
       0,    14,     0,    15,     0,     0,   245,    16,     0,     0,
       0,    17,     0,     0,     0,     0,     0,     0,    18,     4,
      19,     5,     6,     7,     0,     8,     9,    10,    11,    12,
       0,   157,     0,    13,     0,     0,    14,     0,    15,     0,
       0,   246,    16,     0,    36,    37,    17,    38,     0,    39,
      40,     0,     0,    18,     0,    19,     0,     0,     0,    41,
      42,    43,   110,     0,     0,     0,     0,    44,     0,     0,
      76,    77,    78,    79,    80,    81,    82,    83,     0,    84,
      85,    86,    87,    88,    89,    90,   147,     0,     0,    91,
       0,     0,     0,     0,    76,    77,    78,    79,    80,    81,
      82,    83,     0,    84,    85,    86,    87,    88,    89,    90,
       0,    36,    37,    91,    38,     0,    39,    40,     0,     0,
       0,     0,     0,     0,     0,     0,    41,    42,    43,     0,
      36,    37,     0,   104,    44,   105,    40,     0,     0,     0,
       0,     0,     0,     0,     0,    41,    42,    43,     0,     0,
       0,     0,     0,    44,    76,    77,    78,    79,    80,    81,
      82,    83,     0,    84,    85,    86,    87,    88,    89,    90,
       0,   111,     0,    91,    76,    77,    78,    79,    80,    81,
      82,    83,     0,    84,    85,    86,    87,    88,    89,    90,
       0,   114,     0,    91,    76,    77,    78,    79,    80,    81,
      82,    83,     0,    84,    85,    86,    87,    88,    89,    90,
       0,   150,     0,    91,    76,    77,    78,    79,    80,    81,
      82,    83,     0,    84,    85,    86,    87,    88,    89,    90,
       0,   161,     0,    91,    76,    77,    78,    79,    80,    81,
      82,    83,     0,    84,    85,    86,    87,    88,    89,    90,
       0,   162,     0,    91,    76,    77,    78,    79,    80,    81,
      82,    83,     0,    84,    85,    86,    87,    88,    89,    90,
       0,     0,     0,    91,    77,    78,    79,    80,    81,    82,
      83,     0,    84,    85,    86,    87,    88,    89,    90,     0,
       0,     0,    91,    78,    79,    80,    81,    82,    83,     0,
      84,    85,    86,    87,    88,    89,    90,     0,     0,     0,
      91,   -48,   -48,   -48,   -48,   -48,   -48,     0,    84,    85,
      86,    87,    88,    89,    90,     0,     0,     0,    91
};

static const yytype_int16 yycheck[] =
{
      17,    34,    35,    21,    35,     0,    37,   222,    41,    42,
      43,    44,    49,    55,    32,    33,    35,    35,    37,    37,
      38,    54,    55,    32,    33,    51,    52,    53,    54,    47,
      48,    49,    58,    50,   249,   250,    30,    55,    71,    13,
      14,    15,    16,    76,    77,    78,    79,    80,    81,    82,
      83,    84,    85,    86,    87,    88,    89,    90,    91,    16,
      32,    33,    99,    96,    35,    22,    37,   100,    55,   102,
      54,    55,    55,    55,    30,     5,     5,   110,     5,     5,
      97,    98,    39,    40,    41,    42,    43,    44,    45,    46,
       5,    48,    49,    50,    51,    52,    53,    54,     5,     5,
       5,    58,     5,   140,     5,     5,     5,    55,    55,   142,
      55,   144,    16,    21,   147,    58,    56,    56,    22,   136,
      56,   138,    56,    12,   157,    16,   159,    25,    32,    33,
      26,    35,    56,    37,    38,     6,   153,   170,   171,     6,
     173,     6,     6,    47,    48,    49,     6,   180,   165,   163,
     183,    55,   169,    -1,   187,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   179,    -1,    -1,   182,   199,   184,    -1,   186,
      -1,    -1,   205,    48,    49,    50,    51,    52,    53,    54,
      -1,   198,    -1,    58,   201,    -1,    -1,   204,    -1,   206,
     207,   208,    -1,   210,    -1,   212,    -1,   214,    -1,    -1,
      -1,   218,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     227,    -1,    -1,    -1,    -1,   232,    -1,    -1,     1,    -1,
       3,     4,     5,    -1,     7,     8,     9,    10,    11,    -1,
     247,   248,    15,    -1,    -1,    18,    19,    20,    -1,    -1,
      -1,    24,    -1,    32,    33,    28,    35,    -1,    37,    38,
      16,    -1,    35,    19,    37,    -1,    22,    -1,    47,    48,
      49,    -1,    -1,    -1,    -1,    -1,    55,    56,    -1,    -1,
      -1,    -1,    55,    39,    40,    41,    42,    43,    44,    45,
      46,    -1,    48,    49,    50,    51,    52,    53,    54,    16,
      -1,    -1,    58,    -1,    -1,    22,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    39,    40,    41,    42,    43,    44,    45,    46,
      -1,    48,    49,    50,    51,    52,    53,    54,    16,    -1,
      -1,    58,    -1,    -1,    22,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    39,    40,    41,    42,    43,    44,    45,    46,    -1,
      48,    49,    50,    51,    52,    53,    54,    16,    -1,    -1,
      58,    -1,    -1,    22,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    16,    -1,    -1,
      39,    40,    41,    42,    43,    44,    45,    46,    -1,    48,
      49,    50,    51,    52,    53,    54,    -1,    16,    -1,    58,
      39,    40,    41,    42,    43,    44,    45,    46,    -1,    48,
      49,    50,    51,    52,    53,    54,    -1,    16,    -1,    58,
      39,    40,    41,    42,    43,    44,    45,    46,    -1,    48,
      49,    50,    51,    52,    53,    54,    -1,    16,    -1,    58,
      39,    40,    41,    42,    43,    44,    45,    46,    -1,    48,
      49,    50,    51,    52,    53,    54,    -1,    16,    -1,    58,
      39,    40,    41,    42,    43,    44,    45,    46,    -1,    48,
      49,    50,    51,    52,    53,    54,    -1,    16,    -1,    58,
      39,    40,    41,    42,    43,    44,    45,    46,    -1,    48,
      49,    50,    51,    52,    53,    54,    -1,    -1,    -1,    58,
      39,    40,    41,    42,    43,    44,    45,    46,    19,    48,
      49,    50,    51,    52,    53,    54,    -1,    -1,    -1,    58,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    39,    40,
      41,    42,    43,    44,    45,    46,    19,    48,    49,    50,
      51,    52,    53,    54,    -1,    -1,    -1,    58,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    39,    40,    41,    42,
      43,    44,    45,    46,    -1,    48,    49,    50,    51,    52,
      53,    54,    -1,     0,     1,    58,     3,     4,     5,    -1,
       7,     8,     9,    10,    11,    -1,    -1,    -1,    15,    -1,
      -1,    18,    -1,    20,    -1,    -1,    -1,    24,    -1,    -1,
      -1,    28,    -1,    -1,    -1,    -1,    -1,    -1,    35,     1,
      37,     3,     4,     5,    -1,     7,     8,     9,    10,    11,
      -1,    13,    14,    15,    -1,    -1,    18,    -1,    20,    -1,
      -1,    -1,    24,    -1,    -1,    -1,    28,    -1,    -1,    -1,
      -1,    -1,    -1,    35,     1,    37,     3,     4,     5,    -1,
       7,     8,     9,    10,    11,    -1,    13,    14,    15,    -1,
      -1,    18,    -1,    20,    -1,    -1,    -1,    24,    -1,    -1,
      -1,    28,    -1,    -1,    -1,    -1,    -1,    -1,    35,     1,
      37,     3,     4,     5,    -1,     7,     8,     9,    10,    11,
      -1,    -1,    -1,    15,    -1,    -1,    18,    -1,    20,    -1,
      -1,    -1,    24,    25,    26,    -1,    28,    -1,    -1,    -1,
      -1,    -1,    -1,    35,     1,    37,     3,     4,     5,    -1,
       7,     8,     9,    10,    11,    -1,    -1,    -1,    15,    -1,
      -1,    18,    -1,    20,    -1,    -1,    -1,    24,    -1,    -1,
      -1,    28,    29,    -1,    -1,    -1,    -1,    -1,    35,     1,
      37,     3,     4,     5,    -1,     7,     8,     9,    10,    11,
      -1,    -1,    -1,    15,    -1,    17,    18,    -1,    20,    -1,
      -1,    -1,    24,    -1,    -1,    -1,    28,    -1,    -1,    -1,
      -1,    -1,    -1,    35,     1,    37,     3,     4,     5,    -1,
       7,     8,     9,    10,    11,    -1,    -1,    -1,    15,    -1,
      17,    18,    -1,    20,    -1,    -1,    -1,    24,    -1,    -1,
      -1,    28,    -1,    -1,    -1,    -1,    -1,    -1,    35,     1,
      37,     3,     4,     5,    -1,     7,     8,     9,    10,    11,
      -1,    13,    -1,    15,    -1,    -1,    18,    -1,    20,    -1,
      -1,    -1,    24,    -1,    -1,    -1,    28,    -1,    -1,    -1,
      -1,    -1,    -1,    35,     1,    37,     3,     4,     5,    -1,
       7,     8,     9,    10,    11,    -1,    13,    -1,    15,    -1,
      -1,    18,    -1,    20,    -1,    -1,    -1,    24,    -1,    -1,
      -1,    28,    -1,    -1,    -1,    -1,    -1,    -1,    35,     1,
      37,     3,     4,     5,    -1,     7,     8,     9,    10,    11,
      -1,    -1,    -1,    15,    -1,    -1,    18,    -1,    20,    -1,
      -1,    23,    24,    -1,    -1,    -1,    28,    -1,    -1,    -1,
      -1,    -1,    -1,    35,     1,    37,     3,     4,     5,    -1,
       7,     8,     9,    10,    11,    -1,    -1,    -1,    15,    -1,
      -1,    18,    -1,    20,    -1,    -1,    23,    24,    -1,    -1,
      -1,    28,    -1,    -1,    -1,    -1,    -1,    -1,    35,     1,
      37,     3,     4,     5,    -1,     7,     8,     9,    10,    11,
      -1,    -1,    -1,    15,    -1,    -1,    18,    -1,    20,    -1,
      -1,    23,    24,    -1,    -1,    -1,    28,    -1,    -1,    -1,
      -1,    -1,    -1,    35,     1,    37,     3,     4,     5,    -1,
       7,     8,     9,    10,    11,    -1,    -1,    -1,    15,    -1,
      -1,    18,    -1,    20,    -1,    -1,    23,    24,    -1,    -1,
      -1,    28,    -1,    -1,    -1,    -1,    -1,    -1,    35,     1,
      37,     3,     4,     5,    -1,     7,     8,     9,    10,    11,
      -1,    -1,    -1,    15,    -1,    -1,    18,    -1,    20,    -1,
      -1,    23,    24,    -1,    -1,    -1,    28,    -1,    -1,    -1,
      -1,    -1,    -1,    35,     1,    37,     3,     4,     5,    -1,
       7,     8,     9,    10,    11,    -1,    -1,    -1,    15,    -1,
      -1,    18,    -1,    20,    -1,    -1,    23,    24,    -1,    -1,
      -1,    28,    -1,    -1,    -1,    -1,    -1,    -1,    35,     1,
      37,     3,     4,     5,    -1,     7,     8,     9,    10,    11,
      -1,    -1,    -1,    15,    -1,    -1,    18,    -1,    20,    -1,
      -1,    23,    24,    -1,    -1,    -1,    28,    -1,    -1,    -1,
      -1,    -1,    -1,    35,     1,    37,     3,     4,     5,    -1,
       7,     8,     9,    10,    11,    -1,    -1,    -1,    15,    -1,
      -1,    18,    -1,    20,    -1,    -1,    23,    24,    -1,    -1,
      -1,    28,    -1,    -1,    -1,    -1,    -1,    -1,    35,     1,
      37,     3,     4,     5,    -1,     7,     8,     9,    10,    11,
      -1,    -1,    -1,    15,    -1,    -1,    18,    -1,    20,    -1,
      -1,    -1,    24,    -1,    -1,    27,    28,    -1,    -1,    -1,
      -1,    -1,    -1,    35,     1,    37,     3,     4,     5,    -1,
       7,     8,     9,    10,    11,    -1,    -1,    -1,    15,    -1,
      -1,    18,    -1,    20,    -1,    -1,    23,    24,    -1,    -1,
      -1,    28,    -1,    -1,    -1,    -1,    -1,    -1,    35,     1,
      37,     3,     4,     5,    -1,     7,     8,     9,    10,    11,
      -1,    -1,    -1,    15,    -1,    -1,    18,    -1,    20,    -1,
      -1,    23,    24,    -1,    -1,    -1,    28,    -1,    -1,    -1,
      -1,    -1,    -1,    35,     1,    37,     3,     4,     5,    -1,
       7,     8,     9,    10,    11,    -1,    -1,    -1,    15,    -1,
      -1,    18,    -1,    20,    -1,    -1,    23,    24,    -1,    -1,
      -1,    28,    -1,    -1,    -1,    -1,    -1,    -1,    35,     1,
      37,     3,     4,     5,    -1,     7,     8,     9,    10,    11,
      -1,    -1,    -1,    15,    -1,    -1,    18,    -1,    20,    -1,
      -1,    23,    24,    -1,    -1,    -1,    28,    -1,    -1,    -1,
      -1,    -1,    -1,    35,     1,    37,     3,     4,     5,    -1,
       7,     8,     9,    10,    11,    -1,    -1,    -1,    15,    -1,
      -1,    18,    -1,    20,    -1,    -1,    23,    24,    -1,    -1,
      -1,    28,    -1,    -1,    -1,    -1,    -1,    -1,    35,     1,
      37,     3,     4,     5,    -1,     7,     8,     9,    10,    11,
      -1,    19,    -1,    15,    -1,    -1,    18,    -1,    20,    -1,
      -1,    23,    24,    -1,    32,    33,    28,    35,    -1,    37,
      38,    -1,    -1,    35,    -1,    37,    -1,    -1,    -1,    47,
      48,    49,    31,    -1,    -1,    -1,    -1,    55,    -1,    -1,
      39,    40,    41,    42,    43,    44,    45,    46,    -1,    48,
      49,    50,    51,    52,    53,    54,    31,    -1,    -1,    58,
      -1,    -1,    -1,    -1,    39,    40,    41,    42,    43,    44,
      45,    46,    -1,    48,    49,    50,    51,    52,    53,    54,
      -1,    32,    33,    58,    35,    -1,    37,    38,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    47,    48,    49,    -1,
      32,    33,    -1,    35,    55,    37,    38,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    47,    48,    49,    -1,    -1,
      -1,    -1,    -1,    55,    39,    40,    41,    42,    43,    44,
      45,    46,    -1,    48,    49,    50,    51,    52,    53,    54,
      -1,    56,    -1,    58,    39,    40,    41,    42,    43,    44,
      45,    46,    -1,    48,    49,    50,    51,    52,    53,    54,
      -1,    56,    -1,    58,    39,    40,    41,    42,    43,    44,
      45,    46,    -1,    48,    49,    50,    51,    52,    53,    54,
      -1,    56,    -1,    58,    39,    40,    41,    42,    43,    44,
      45,    46,    -1,    48,    49,    50,    51,    52,    53,    54,
      -1,    56,    -1,    58,    39,    40,    41,    42,    43,    44,
      45,    46,    -1,    48,    49,    50,    51,    52,    53,    54,
      -1,    56,    -1,    58,    39,    40,    41,    42,    43,    44,
      45,    46,    -1,    48,    49,    50,    51,    52,    53,    54,
      -1,    -1,    -1,    58,    40,    41,    42,    43,    44,    45,
      46,    -1,    48,    49,    50,    51,    52,    53,    54,    -1,
      -1,    -1,    58,    41,    42,    43,    44,    45,    46,    -1,
      48,    49,    50,    51,    52,    53,    54,    -1,    -1,    -1,
      58,    41,    42,    43,    44,    45,    46,    -1,    48,    49,
      50,    51,    52,    53,    54,    -1,    -1,    -1,    58
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    60,    61,     0,     1,     3,     4,     5,     7,     8,
       9,    10,    11,    15,    18,    20,    24,    28,    35,    37,
      62,    63,    65,    66,    67,    68,    69,    73,    74,    75,
      76,    77,    78,    79,    55,    55,    32,    33,    35,    37,
      38,    47,    48,    49,    55,    80,    55,    55,    64,    64,
      64,    64,    64,    61,    30,    30,     5,     5,     5,     5,
       5,     5,     5,     5,     5,     5,     5,     5,    80,    56,
      80,    55,    80,    80,    80,    80,    39,    40,    41,    42,
      43,    44,    45,    46,    48,    49,    50,    51,    52,    53,
      54,    58,    35,    37,    35,    37,    55,    72,    72,    61,
      35,    37,    55,    29,    35,    37,    73,    80,    73,    80,
      31,    56,    80,    81,    56,    80,    80,    80,    80,    80,
      80,    80,    80,    80,    80,    80,    80,    80,    80,    80,
      80,    56,    56,    56,    56,    80,    12,    61,    16,    61,
      19,    72,    21,    80,    21,    80,    80,    31,    82,    56,
      56,    61,    13,    14,    61,    17,    72,    19,    80,    19,
      80,    56,    56,    80,    13,    14,    61,    17,    80,    16,
      19,    22,    80,    19,    25,    70,    82,    61,    13,    16,
      22,    61,    16,    22,    80,    80,    16,    22,    80,    32,
      33,    26,    13,    61,    80,    23,    61,    80,    16,    22,
      61,    16,    61,    80,    16,    22,     6,     6,     6,    23,
      16,    23,    16,    61,    80,    23,    61,    23,    16,    61,
      80,    61,    61,    61,    61,    61,    23,    16,    61,    23,
      61,    23,    16,    25,    71,    71,    27,    23,    23,    61,
      23,    23,    61,    32,    33,    23,    23,     6,     6,    61,
      61,    71,    71
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    59,    60,    61,    61,    61,    62,    62,    62,    62,
      62,    62,    62,    62,    62,    62,    62,    62,    62,    62,
      63,    64,    65,    65,    65,    65,    66,    66,    67,    67,
      68,    68,    68,    68,    68,    68,    68,    68,    68,    68,
      68,    68,    68,    68,    69,    70,    70,    71,    71,    71,
      72,    73,    73,    73,    73,    74,    74,    75,    76,    76,
      77,    78,    79,    79,    80,    80,    80,    80,    80,    80,
      80,    80,    80,    80,    80,    80,    80,    80,    80,    80,
      80,    80,    80,    80,    80,    80,    80,    80,    80,    81,
      81,    82,    82
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     0,     2,     2,     1,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     1,     2,     2,
       3,     0,     6,     5,     8,     7,     6,     5,     5,     4,
      12,    10,    12,    10,    11,    10,    11,     9,     8,     9,
      11,    11,     9,     9,    10,     5,     5,     0,     5,     5,
       3,     3,     3,     3,     3,     4,     3,     2,     4,     4,
       6,     1,     4,     4,     1,     1,     3,     3,     3,     3,
       3,     3,     3,     2,     2,     3,     3,     1,     1,     3,
       3,     3,     3,     3,     3,     3,     3,     2,     4,     0,
       2,     0,     3
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
#line 153 "interpreter.y"
          { 
            // Create a new AST
            (yyval.prog) = new lp::AST((yyvsp[0].stmts)); 

            // Assign the AST to the root
            root = (yyval.prog); 
          }
#line 1896 "interpreter.tab.c"
    break;

  case 3:
#line 164 "interpreter.y"
          { 
            // create an empty list of statements
            (yyval.stmts) = new std::list<lp::Statement *>(); 
          }
#line 1905 "interpreter.tab.c"
    break;

  case 4:
#line 169 "interpreter.y"
          { 
            // copy up the list and add the stmt to it
            (yyval.stmts) = (yyvsp[-1].stmts);
            (yyval.stmts)->push_back((yyvsp[0].st));

            // Control the interative mode of execution of the interpreter
            if (interactiveMode == true && control == 0)
            {
              for(std::list<lp::Statement *>::iterator it = (yyval.stmts)->begin(); 
                  it != (yyval.stmts)->end(); 
                  it++)
              {
                (*it)->print(); 
                (*it)->evaluate();
              }

              // Delete the AST code, because it has already run in the interactive mode.
              (yyval.stmts)->clear();
            }
          }
#line 1930 "interpreter.tab.c"
    break;

  case 5:
#line 190 "interpreter.y"
          { 
            // just copy up the stmtlist when an error occurs
            (yyval.stmts) = (yyvsp[-1].stmts);

            // The previous look-ahead token ought to be discarded with `yyclearin;'
            yyclearin; 
          }
#line 1942 "interpreter.tab.c"
    break;

  case 6:
#line 201 "interpreter.y"
      {
        // Create a new empty statement node
        (yyval.st) = new lp::EmptyStmt(); 
      }
#line 1951 "interpreter.tab.c"
    break;

  case 7:
#line 206 "interpreter.y"
      {
        // Default action
        // $$ = $1;
      }
#line 1960 "interpreter.tab.c"
    break;

  case 8:
#line 210 "interpreter.y"
                                  {}
#line 1966 "interpreter.tab.c"
    break;

  case 9:
#line 211 "interpreter.y"
                      {}
#line 1972 "interpreter.tab.c"
    break;

  case 10:
#line 212 "interpreter.y"
                     {}
#line 1978 "interpreter.tab.c"
    break;

  case 11:
#line 213 "interpreter.y"
                                  {}
#line 1984 "interpreter.tab.c"
    break;

  case 12:
#line 214 "interpreter.y"
                         {}
#line 1990 "interpreter.tab.c"
    break;

  case 13:
#line 215 "interpreter.y"
                            {}
#line 1996 "interpreter.tab.c"
    break;

  case 14:
#line 216 "interpreter.y"
                               {}
#line 2002 "interpreter.tab.c"
    break;

  case 15:
#line 217 "interpreter.y"
                          {}
#line 2008 "interpreter.tab.c"
    break;

  case 16:
#line 218 "interpreter.y"
                       {}
#line 2014 "interpreter.tab.c"
    break;

  case 17:
#line 219 "interpreter.y"
                  {}
#line 2020 "interpreter.tab.c"
    break;

  case 18:
#line 220 "interpreter.y"
                                  {}
#line 2026 "interpreter.tab.c"
    break;

  case 19:
#line 221 "interpreter.y"
                                {}
#line 2032 "interpreter.tab.c"
    break;

  case 20:
#line 226 "interpreter.y"
      {
        (yyval.st) = new lp::BlockStmt((yyvsp[-1].stmts)); 
      }
#line 2040 "interpreter.tab.c"
    break;

  case 21:
#line 233 "interpreter.y"
              {
                // To control the interactive mode in "if" and "while" sentences
                control++;
              }
#line 2049 "interpreter.tab.c"
    break;

  case 22:
#line 241 "interpreter.y"
    {
      // Create a new if statement node
      (yyval.st) = new lp::IfStmt((yyvsp[-3].expNode), (yyvsp[-1].stmts));
        
      // To control the interactive mode
      control--;
  	}
#line 2061 "interpreter.tab.c"
    break;

  case 23:
#line 249 "interpreter.y"
    {
		  execerror("Syntax error: missing ENTONCES symbol of if statement", "si cond ENTONCES ..");
    }
#line 2069 "interpreter.tab.c"
    break;

  case 24:
#line 253 "interpreter.y"
          {
      (yyval.st) = new lp::IfStmt((yyvsp[-5].expNode), (yyvsp[-3].stmts), (yyvsp[-1].stmts));
      control--;
	  }
#line 2078 "interpreter.tab.c"
    break;

  case 25:
#line 258 "interpreter.y"
    {
		  execerror("Syntax error: missing ENTONCES symbol of if statement", "si cond ENTONCES ..");
	  }
#line 2086 "interpreter.tab.c"
    break;

  case 26:
#line 265 "interpreter.y"
      {
        (yyval.st) = new lp::WhileStmt((yyvsp[-3].expNode), (yyvsp[-1].stmts));
        control--;
      }
#line 2095 "interpreter.tab.c"
    break;

  case 27:
#line 270 "interpreter.y"
      {
        execerror("Syntax error: missing HACER symbol of while statement", "mientras cond HACER ..");
      }
#line 2103 "interpreter.tab.c"
    break;

  case 28:
#line 277 "interpreter.y"
          {
            (yyval.st) = new lp::DoWhileStmt((yyvsp[0].expNode), (yyvsp[-2].stmts));
            control--;
    	    }
#line 2112 "interpreter.tab.c"
    break;

  case 29:
#line 282 "interpreter.y"
          {
            execerror("Syntax error: missing HASTA symbol of do while statement", "repetir stmtlist HASTA cond ..");
          }
#line 2120 "interpreter.tab.c"
    break;

  case 30:
#line 289 "interpreter.y"
    {
      (yyval.st) = new lp::ForStmt((yyvsp[-9].identifier), (yyvsp[-7].expNode), (yyvsp[-5].expNode), (yyvsp[-3].expNode), (yyvsp[-1].stmts));
      control--;
    }
#line 2129 "interpreter.tab.c"
    break;

  case 31:
#line 294 "interpreter.y"
    {
      (yyval.st) = new lp::ForStmt((yyvsp[-7].identifier), (yyvsp[-5].expNode), (yyvsp[-3].expNode), (yyvsp[-1].stmts));
      control--;
    }
#line 2138 "interpreter.tab.c"
    break;

  case 32:
#line 299 "interpreter.y"
    {
      execerror("Semantic error in for statement: it is not allowed to modify a constant ", (yyvsp[-9].identifier));
    }
#line 2146 "interpreter.tab.c"
    break;

  case 33:
#line 303 "interpreter.y"
    {
      execerror("Semantic error in for statement: it is not allowed to modify a constant ", (yyvsp[-7].identifier));
    }
#line 2154 "interpreter.tab.c"
    break;

  case 34:
#line 307 "interpreter.y"
    {
      execerror("Syntax error: missing DESDE symbol of for statement", "para id DESDE ..");
    }
#line 2162 "interpreter.tab.c"
    break;

  case 35:
#line 311 "interpreter.y"
    {
      execerror("Syntax error: missing HASTA symbol of for statement", "para id DESDE exp HASTA ..");
    }
#line 2170 "interpreter.tab.c"
    break;

  case 36:
#line 315 "interpreter.y"
    {
      execerror("Syntax error: missing HACER symbol of for statement", "para id DESDE exp HASTA exp PASO exp HACER ..");
    }
#line 2178 "interpreter.tab.c"
    break;

  case 37:
#line 319 "interpreter.y"
    {
      execerror("Syntax error: missing DESDE symbol of for statement", "para id DESDE ..");
    }
#line 2186 "interpreter.tab.c"
    break;

  case 38:
#line 323 "interpreter.y"
    {
      execerror("Syntax error: missing HASTA symbol of for statement", "para id DESDE exp HASTA ..");
    }
#line 2194 "interpreter.tab.c"
    break;

  case 39:
#line 327 "interpreter.y"
    {
      execerror("Syntax error: missing HACER symbol of for statement", "para id DESDE exp HASTA exp HACER ..");
    }
#line 2202 "interpreter.tab.c"
    break;

  case 40:
#line 331 "interpreter.y"
    {
      execerror("Syntax error: missing from EXP argument of for statement", "para id desde EXP ..");
    }
#line 2210 "interpreter.tab.c"
    break;

  case 41:
#line 335 "interpreter.y"
    {
      execerror("Syntax error: missing until EXP argument of for statement", "para id desde exp hasta EXP ..");
    }
#line 2218 "interpreter.tab.c"
    break;

  case 42:
#line 339 "interpreter.y"
    {
      execerror("Syntax error: missing from EXP argument of for statement", "para id desde EXP ..");
    }
#line 2226 "interpreter.tab.c"
    break;

  case 43:
#line 343 "interpreter.y"
    {
      execerror("Syntax error: missing until EXP argument of for statement", "para id desde exp hasta EXP ..");
    }
#line 2234 "interpreter.tab.c"
    break;

  case 44:
#line 350 "interpreter.y"
        {
          (yyval.st) = new lp::SwitchStmt((yyvsp[-6].expNode), (yyvsp[-4].switchValues), (yyvsp[-1].stmts));
          control --;
        }
#line 2243 "interpreter.tab.c"
    break;

  case 45:
#line 358 "interpreter.y"
              {
                (yyval.switchValues) = (yyvsp[0].switchValues);
                lp::ExpNode *e = new lp::NumberNode((yyvsp[-3].number));
                lp::Value *v = new lp::Value(e, (yyvsp[-1].stmts));
                (yyval.switchValues)->push_front(v);
              }
#line 2254 "interpreter.tab.c"
    break;

  case 46:
#line 365 "interpreter.y"
              {
                (yyval.switchValues) = (yyvsp[0].switchValues);
                lp::ExpNode *e = new lp::StringNode((yyvsp[-3].identifier));
                lp::Value *v = new lp::Value(e, (yyvsp[-1].stmts));
                (yyval.switchValues)->push_front(v);
              }
#line 2265 "interpreter.tab.c"
    break;

  case 47:
#line 375 "interpreter.y"
                    {
                      (yyval.switchValues) = new std::list<lp::Value *>(); 
                    }
#line 2273 "interpreter.tab.c"
    break;

  case 48:
#line 379 "interpreter.y"
                    {
                      (yyval.switchValues) = (yyvsp[0].switchValues);
                      lp::ExpNode *e = new lp::NumberNode((yyvsp[-3].number));
                      lp::Value *v = new lp::Value(e, (yyvsp[-1].stmts));
                      (yyval.switchValues)->push_front(v);
                    }
#line 2284 "interpreter.tab.c"
    break;

  case 49:
#line 386 "interpreter.y"
                    {
                      (yyval.switchValues) = (yyvsp[0].switchValues);
                      lp::ExpNode *e = new lp::StringNode((yyvsp[-3].identifier));
                      lp::Value *v = new lp::Value(e, (yyvsp[-1].stmts));
                      (yyval.switchValues)->push_front(v);
                    }
#line 2295 "interpreter.tab.c"
    break;

  case 50:
#line 396 "interpreter.y"
      { 
        (yyval.expNode) = (yyvsp[-1].expNode);
      }
#line 2303 "interpreter.tab.c"
    break;

  case 51:
#line 403 "interpreter.y"
      { 
        (yyval.st) = new lp::AssignmentStmt((yyvsp[-2].identifier), (yyvsp[0].expNode));
      }
#line 2311 "interpreter.tab.c"
    break;

  case 52:
#line 407 "interpreter.y"
      {
        (yyval.st) = new lp::AssignmentStmt((yyvsp[-2].identifier), (lp::AssignmentStmt *) (yyvsp[0].st));
      }
#line 2319 "interpreter.tab.c"
    break;

  case 53:
#line 411 "interpreter.y"
      {   
        execerror("Semantic error in assignment: it is not allowed to modify a constant ", (yyvsp[-2].identifier));
      }
#line 2327 "interpreter.tab.c"
    break;

  case 54:
#line 415 "interpreter.y"
      {   
        execerror("Semantic error in multiple assignment: it is not allowed to modify a constant ",(yyvsp[-2].identifier));
      }
#line 2335 "interpreter.tab.c"
    break;

  case 55:
#line 422 "interpreter.y"
            {
              (yyval.st) = new lp::AskForKeyStmt((yyvsp[-1].expNode));
            }
#line 2343 "interpreter.tab.c"
    break;

  case 56:
#line 426 "interpreter.y"
            {
              (yyval.st) = new lp::AskForKeyStmt(new lp::StringNode("Pulsa INTRO para continuar"));
            }
#line 2351 "interpreter.tab.c"
    break;

  case 57:
#line 433 "interpreter.y"
      {
        (yyval.st) = new lp::PrintStmt((yyvsp[0].expNode));
      }
#line 2359 "interpreter.tab.c"
    break;

  case 58:
#line 440 "interpreter.y"
      {
        (yyval.st) = new lp::ReadStmt((yyvsp[-1].identifier));
      }
#line 2367 "interpreter.tab.c"
    break;

  case 59:
#line 444 "interpreter.y"
      {   
        execerror("Semantic error in \"read statement\": it is not allowed to modify a constant ",(yyvsp[-1].identifier));
      }
#line 2375 "interpreter.tab.c"
    break;

  case 60:
#line 451 "interpreter.y"
            {
              (yyval.st) = new lp::PlaceStmt((yyvsp[-3].expNode), (yyvsp[-1].expNode));
            }
#line 2383 "interpreter.tab.c"
    break;

  case 61:
#line 457 "interpreter.y"
      {
        (yyval.st) = new lp::ClearStmt();
      }
#line 2391 "interpreter.tab.c"
    break;

  case 62:
#line 463 "interpreter.y"
            {
              (yyval.st) = new lp::ReadStmtString((yyvsp[-1].identifier));
            }
#line 2399 "interpreter.tab.c"
    break;

  case 63:
#line 467 "interpreter.y"
            {   
              execerror("Semantic error in \"read string statement\": it is not allowed to modify a constant ",(yyvsp[-1].identifier));
            }
#line 2407 "interpreter.tab.c"
    break;

  case 64:
#line 474 "interpreter.y"
    { (yyval.expNode) = new lp::NumberNode((yyvsp[0].number)); }
#line 2413 "interpreter.tab.c"
    break;

  case 65:
#line 476 "interpreter.y"
    { (yyval.expNode) = new lp::StringNode((yyvsp[0].identifier)); }
#line 2419 "interpreter.tab.c"
    break;

  case 66:
#line 478 "interpreter.y"
    { (yyval.expNode) = new lp::PlusNode((yyvsp[-2].expNode), (yyvsp[0].expNode)); }
#line 2425 "interpreter.tab.c"
    break;

  case 67:
#line 480 "interpreter.y"
    { (yyval.expNode) = new lp::MinusNode((yyvsp[-2].expNode), (yyvsp[0].expNode)); }
#line 2431 "interpreter.tab.c"
    break;

  case 68:
#line 482 "interpreter.y"
                { (yyval.expNode) = new lp::MultiplicationNode((yyvsp[-2].expNode), (yyvsp[0].expNode)); }
#line 2437 "interpreter.tab.c"
    break;

  case 69:
#line 484 "interpreter.y"
    { (yyval.expNode) = new lp::DivisionNode((yyvsp[-2].expNode), (yyvsp[0].expNode)); }
#line 2443 "interpreter.tab.c"
    break;

  case 70:
#line 486 "interpreter.y"
                { (yyval.expNode) = new lp::IntegerDivisionNode((yyvsp[-2].expNode), (yyvsp[0].expNode)); }
#line 2449 "interpreter.tab.c"
    break;

  case 71:
#line 488 "interpreter.y"
    { (yyval.expNode) = new lp::ConcatenationNode((yyvsp[-2].expNode), (yyvsp[0].expNode)); }
#line 2455 "interpreter.tab.c"
    break;

  case 72:
#line 490 "interpreter.y"
    { (yyval.expNode) = (yyvsp[-1].expNode); }
#line 2461 "interpreter.tab.c"
    break;

  case 73:
#line 492 "interpreter.y"
                { (yyval.expNode) = new lp::UnaryPlusNode((yyvsp[0].expNode)); }
#line 2467 "interpreter.tab.c"
    break;

  case 74:
#line 494 "interpreter.y"
                { (yyval.expNode) = new lp::UnaryMinusNode((yyvsp[0].expNode)); }
#line 2473 "interpreter.tab.c"
    break;

  case 75:
#line 496 "interpreter.y"
                { (yyval.expNode) = new lp::ModuloNode((yyvsp[-2].expNode), (yyvsp[0].expNode)); }
#line 2479 "interpreter.tab.c"
    break;

  case 76:
#line 498 "interpreter.y"
    { (yyval.expNode) = new lp::PowerNode((yyvsp[-2].expNode), (yyvsp[0].expNode)); }
#line 2485 "interpreter.tab.c"
    break;

  case 77:
#line 500 "interpreter.y"
                { (yyval.expNode) = new lp::VariableNode((yyvsp[0].identifier)); }
#line 2491 "interpreter.tab.c"
    break;

  case 78:
#line 502 "interpreter.y"
                { (yyval.expNode) = new lp::ConstantNode((yyvsp[0].identifier)); }
#line 2497 "interpreter.tab.c"
    break;

  case 79:
#line 504 "interpreter.y"
                { (yyval.expNode) = new lp::GreaterThanNode((yyvsp[-2].expNode),(yyvsp[0].expNode)); }
#line 2503 "interpreter.tab.c"
    break;

  case 80:
#line 506 "interpreter.y"
                { (yyval.expNode) = new lp::GreaterOrEqualNode((yyvsp[-2].expNode),(yyvsp[0].expNode)); }
#line 2509 "interpreter.tab.c"
    break;

  case 81:
#line 508 "interpreter.y"
                { (yyval.expNode) = new lp::LessThanNode((yyvsp[-2].expNode),(yyvsp[0].expNode)); }
#line 2515 "interpreter.tab.c"
    break;

  case 82:
#line 510 "interpreter.y"
                { (yyval.expNode) = new lp::LessOrEqualNode((yyvsp[-2].expNode),(yyvsp[0].expNode)); }
#line 2521 "interpreter.tab.c"
    break;

  case 83:
#line 512 "interpreter.y"
                { (yyval.expNode) = new lp::EqualNode((yyvsp[-2].expNode),(yyvsp[0].expNode)); }
#line 2527 "interpreter.tab.c"
    break;

  case 84:
#line 514 "interpreter.y"
                { (yyval.expNode) = new lp::NotEqualNode((yyvsp[-2].expNode),(yyvsp[0].expNode)); }
#line 2533 "interpreter.tab.c"
    break;

  case 85:
#line 516 "interpreter.y"
                { (yyval.expNode) = new lp::AndNode((yyvsp[-2].expNode),(yyvsp[0].expNode)); }
#line 2539 "interpreter.tab.c"
    break;

  case 86:
#line 518 "interpreter.y"
                { (yyval.expNode) = new lp::OrNode((yyvsp[-2].expNode),(yyvsp[0].expNode)); }
#line 2545 "interpreter.tab.c"
    break;

  case 87:
#line 520 "interpreter.y"
                { (yyval.expNode) = new lp::NotNode((yyvsp[0].expNode)); }
#line 2551 "interpreter.tab.c"
    break;

  case 88:
#line 522 "interpreter.y"
                { 
			// Get the identifier in the table of symbols as Builtin
			lp::Builtin *f= (lp::Builtin *) table.getSymbol((yyvsp[-3].identifier));

			// Check the number of parameters 
			if (f->getNParameters() ==  (int) (yyvsp[-1].parameters)->size())
			{
				switch(f->getNParameters())
				{
					case 0:
						{
							// Create a new Builtin Function with 0 parameters node	
							(yyval.expNode) = new lp::BuiltinFunctionNode_0((yyvsp[-3].identifier));
						}
						break;
					case 1:
						{
							// Get the expression from the list of expressions
							lp::ExpNode *e = (yyvsp[-1].parameters)->front();

							// Create a new Builtin Function with 1 parameter node	
							(yyval.expNode) = new lp::BuiltinFunctionNode_1((yyvsp[-3].identifier),e);
						}
						break;
					case 2:
						{
							// Get the expressions from the list of expressions
							lp::ExpNode *e1 = (yyvsp[-1].parameters)->front();
							(yyvsp[-1].parameters)->pop_front();
							lp::ExpNode *e2 = (yyvsp[-1].parameters)->front();

							// Create a new Builtin Function with 2 parameters node	
							(yyval.expNode) = new lp::BuiltinFunctionNode_2((yyvsp[-3].identifier),e1,e2);
						}
						break;
					default:
				  			 execerror("Syntax error: too many parameters for function ", (yyvsp[-3].identifier));
				} 
			}
			else
        execerror("Syntax error: incompatible number of parameters for function", (yyvsp[-3].identifier));
		}
#line 2598 "interpreter.tab.c"
    break;

  case 89:
#line 568 "interpreter.y"
          {
            (yyval.parameters) = new std::list<lp::ExpNode *>(); 
          }
#line 2606 "interpreter.tab.c"
    break;

  case 90:
#line 572 "interpreter.y"
          {
            (yyval.parameters) = (yyvsp[0].parameters);
            (yyval.parameters)->push_front((yyvsp[-1].expNode));
          }
#line 2615 "interpreter.tab.c"
    break;

  case 91:
#line 580 "interpreter.y"
                {
                  (yyval.parameters) = new std::list<lp::ExpNode *>(); 
                }
#line 2623 "interpreter.tab.c"
    break;

  case 92:
#line 584 "interpreter.y"
                {
                  // Get the list of expressions
                  (yyval.parameters) = (yyvsp[0].parameters);

                  // Insert the expression in the list of expressions
                  (yyval.parameters)->push_front((yyvsp[-1].expNode));
                }
#line 2635 "interpreter.tab.c"
    break;


#line 2639 "interpreter.tab.c"

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
#line 594 "interpreter.y"


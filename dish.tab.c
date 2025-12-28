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
#line 3 "dish.y"

#include <cassert>
#include <climits>
#include <cmath>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <list>
#include <regex>
#include <unistd.h>
#include <unordered_set>
#include <vector>

#include <sys/wait.h>

#include "Dimension_Swapper.hpp"
#include "MultiArray.hpp"
#include "Number.hpp"
#include "rtolvalue.hpp"
#include "spawn.hpp"
#include "StringFunctions.h"
#include "xmacroplay.h"

using namespace std;

int yylex();
void yyerror(const char* e_str);

struct Coordinates
{
  Number x;
  Number y;
};

struct Options
{
  int ordinal;
  enum Direction { LEFT, RIGHT, TOP, BOTTOM } direction;
  Coordinates offset;
  bool case_sensitive;
};

Coordinates get_coordinates(string text, Options options);
void xmacroplay(const string& x);
void dump_ocr_to_txt();


#line 120 "dish.tab.c"

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

#include "dish.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_CLICK = 3,                      /* CLICK  */
  YYSYMBOL_SEEK = 4,                       /* SEEK  */
  YYSYMBOL_TYPE = 5,                       /* TYPE  */
  YYSYMBOL_KEY = 6,                        /* KEY  */
  YYSYMBOL_SLEEP = 7,                      /* SLEEP  */
  YYSYMBOL_PRINT = 8,                      /* PRINT  */
  YYSYMBOL_WAIT = 9,                       /* WAIT  */
  YYSYMBOL_CASE = 10,                      /* CASE  */
  YYSYMBOL_FROM = 11,                      /* FROM  */
  YYSYMBOL_NUMBER = 12,                    /* NUMBER  */
  YYSYMBOL_INTEGER = 13,                   /* INTEGER  */
  YYSYMBOL_ORDINAL = 14,                   /* ORDINAL  */
  YYSYMBOL_STRING = 15,                    /* STRING  */
  YYSYMBOL_KEY_LIST = 16,                  /* KEY_LIST  */
  YYSYMBOL_17_ = 17,                       /* '['  */
  YYSYMBOL_18_ = 18,                       /* ']'  */
  YYSYMBOL_19_ = 19,                       /* '+'  */
  YYSYMBOL_20_ = 20,                       /* ','  */
  YYSYMBOL_YYACCEPT = 21,                  /* $accept  */
  YYSYMBOL_Command = 22,                   /* Command  */
  YYSYMBOL_Options = 23,                   /* Options  */
  YYSYMBOL_Disambiguator = 24,             /* Disambiguator  */
  YYSYMBOL_Offset = 25,                    /* Offset  */
  YYSYMBOL_Number = 26                     /* Number  */
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
typedef yytype_int8 yy_state_t;

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

#if 1

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
#endif /* 1 */

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
#define YYFINAL  20
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   38

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  21
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  6
/* YYNRULES -- Number of rules.  */
#define YYNRULES  17
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  38

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   271


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
       2,     2,     2,    19,    20,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    17,     2,    18,     2,     2,     2,     2,     2,     2,
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
      15,    16
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    80,    80,    87,    92,   118,   122,   135,   141,   143,
     146,   151,   157,   163,   169,   174,   178,   182
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if 1
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "CLICK", "SEEK",
  "TYPE", "KEY", "SLEEP", "PRINT", "WAIT", "CASE", "FROM", "NUMBER",
  "INTEGER", "ORDINAL", "STRING", "KEY_LIST", "'['", "']'", "'+'", "','",
  "$accept", "Command", "Options", "Disambiguator", "Offset", "Number", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-16)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int8 yypact[] =
{
      15,    -9,    -9,   -12,    -5,    -6,   -16,    -4,    12,   -15,
       0,    -3,     1,   -16,   -16,    10,   -16,   -16,   -16,    -9,
     -16,   -16,     4,    -7,   -16,   -16,    11,    13,   -16,   -16,
       8,   -16,    14,    -7,    16,    18,   -16,   -16
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       9,    15,    15,     0,     0,     0,     8,     0,     0,    15,
       0,     0,     0,    11,    13,     0,     5,     6,     7,    15,
       1,    10,     0,     0,     2,     3,     0,     0,    16,    17,
       0,     4,     0,     0,    15,     0,    12,    14
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -16,   -16,    -2,    20,    -1,     5
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     8,    12,    13,    14,    30
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      15,     9,    10,    16,    11,    28,    29,    18,    10,    19,
      11,    17,    20,    22,    23,    27,    24,    26,     1,     2,
       3,     4,     5,     6,     7,    25,    31,    32,    33,    21,
       0,     0,    34,    36,     0,    11,    37,     0,    35
};

static const yytype_int8 yycheck[] =
{
       2,    10,    17,    15,    19,    12,    13,    13,    17,    13,
      19,    16,     0,    13,    17,    11,    15,    19,     3,     4,
       5,     6,     7,     8,     9,    15,    15,    14,    20,     9,
      -1,    -1,    18,    34,    -1,    19,    18,    -1,    33
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,     4,     5,     6,     7,     8,     9,    22,    10,
      17,    19,    23,    24,    25,    23,    15,    16,    13,    13,
       0,    24,    13,    17,    15,    15,    23,    11,    12,    13,
      26,    15,    14,    20,    18,    26,    25,    18
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    21,    22,    22,    22,    22,    22,    22,    22,    22,
      23,    23,    24,    24,    25,    25,    26,    26
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     3,     3,     4,     2,     2,     2,     1,     0,
       2,     1,     6,     1,     6,     0,     1,     1
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


/* Context of a parse error.  */
typedef struct
{
  yy_state_t *yyssp;
  yysymbol_kind_t yytoken;
} yypcontext_t;

/* Put in YYARG at most YYARGN of the expected tokens given the
   current YYCTX, and return the number of tokens stored in YYARG.  If
   YYARG is null, return the number of expected tokens (guaranteed to
   be less than YYNTOKENS).  Return YYENOMEM on memory exhaustion.
   Return 0 if there are more than YYARGN expected tokens, yet fill
   YYARG up to YYARGN. */
static int
yypcontext_expected_tokens (const yypcontext_t *yyctx,
                            yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  int yyn = yypact[+*yyctx->yyssp];
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
        if (yycheck[yyx + yyn] == yyx && yyx != YYSYMBOL_YYerror
            && !yytable_value_is_error (yytable[yyx + yyn]))
          {
            if (!yyarg)
              ++yycount;
            else if (yycount == yyargn)
              return 0;
            else
              yyarg[yycount++] = YY_CAST (yysymbol_kind_t, yyx);
          }
    }
  if (yyarg && yycount == 0 && 0 < yyargn)
    yyarg[0] = YYSYMBOL_YYEMPTY;
  return yycount;
}




#ifndef yystrlen
# if defined __GLIBC__ && defined _STRING_H
#  define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
# else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
# endif
#endif

#ifndef yystpcpy
# if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#  define yystpcpy stpcpy
# else
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
# endif
#endif

#ifndef yytnamerr
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
#endif


static int
yy_syntax_error_arguments (const yypcontext_t *yyctx,
                           yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
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
  if (yyctx->yytoken != YYSYMBOL_YYEMPTY)
    {
      int yyn;
      if (yyarg)
        yyarg[yycount] = yyctx->yytoken;
      ++yycount;
      yyn = yypcontext_expected_tokens (yyctx,
                                        yyarg ? yyarg + 1 : yyarg, yyargn - 1);
      if (yyn == YYENOMEM)
        return YYENOMEM;
      else
        yycount += yyn;
    }
  return yycount;
}

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return -1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return YYENOMEM if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                const yypcontext_t *yyctx)
{
  enum { YYARGS_MAX = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  yysymbol_kind_t yyarg[YYARGS_MAX];
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* Actual size of YYARG. */
  int yycount = yy_syntax_error_arguments (yyctx, yyarg, YYARGS_MAX);
  if (yycount == YYENOMEM)
    return YYENOMEM;

  switch (yycount)
    {
#define YYCASE_(N, S)                       \
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
#undef YYCASE_
    }

  /* Compute error message size.  Don't count the "%s"s, but reserve
     room for the terminator.  */
  yysize = yystrlen (yyformat) - 2 * yycount + 1;
  {
    int yyi;
    for (yyi = 0; yyi < yycount; ++yyi)
      {
        YYPTRDIFF_T yysize1
          = yysize + yytnamerr (YY_NULLPTR, yytname[yyarg[yyi]]);
        if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
          yysize = yysize1;
        else
          return YYENOMEM;
      }
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return -1;
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
          yyp += yytnamerr (yyp, yytname[yyarg[yyi++]]);
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

  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;

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
  case 2: /* Command: CLICK Options STRING  */
#line 81 "dish.y"
                {
                    Coordinates c = get_coordinates((yyvsp[0].text_literal),(yyvsp[-1].options));
                    xmacroplay("MotionNotify "+to_string(c.x)+" "+to_string(c.y));
                    xmacroplay("ButtonPress 1");
                    xmacroplay("ButtonRelease 1");
                }
#line 1416 "dish.tab.c"
    break;

  case 3: /* Command: SEEK Options STRING  */
#line 88 "dish.y"
                {
                    Coordinates c = get_coordinates((yyvsp[0].text_literal),(yyvsp[-1].options));
                    xmacroplay("MotionNotify "+to_string(c.x)+" "+to_string(c.y));
                }
#line 1425 "dish.tab.c"
    break;

  case 4: /* Command: WAIT INTEGER Options STRING  */
#line 93 "dish.y"
                {
                    time_t expiration = time(NULL) + (yyvsp[-2].integral_literal);
                    while(time(NULL) < expiration)
                      if(pid_t child_pid = fork())
                      {
                        int status;
                        waitpid(child_pid,&status,0);
                        if(!WEXITSTATUS(status))
                        {
                          expiration = UINT64_MAX;
                          break;
                        }
                      }
                      else
                      {
                        Coordinates c = get_coordinates((yyvsp[0].text_literal),(yyvsp[-1].options));
                        exit(0);                      
                      }
                    
                    if(expiration!=UINT64_MAX)
                    {
                      cerr << "Timed out waiting for text to appear." << endl;
                      exit(1);
                    }
                }
#line 1455 "dish.tab.c"
    break;

  case 5: /* Command: TYPE STRING  */
#line 119 "dish.y"
                {
                    xmacroplay(string{"String "}+(yyvsp[0].text_literal));
                }
#line 1463 "dish.tab.c"
    break;

  case 6: /* Command: KEY KEY_LIST  */
#line 123 "dish.y"
                {
                    for(const char* command : { "KeyStrPress ", "KeyStrRelease " } )
                    {
                      char* cur_ptr = (yyvsp[0].key_list).begin_ptr;
                      while(cur_ptr < (yyvsp[0].key_list).end_ptr)
                      {
                        string x = cur_ptr;
                        xmacroplay(command+x);
                        cur_ptr += x.length()+1;
                      }
                    }
                }
#line 1480 "dish.tab.c"
    break;

  case 7: /* Command: SLEEP INTEGER  */
#line 136 "dish.y"
                {
#ifndef PARSER_TEST
                    sleep((yyvsp[0].integral_literal));
#endif
                }
#line 1490 "dish.tab.c"
    break;

  case 8: /* Command: PRINT  */
#line 141 "dish.y"
                      { dump_ocr_to_txt(); }
#line 1496 "dish.tab.c"
    break;

  case 9: /* Command: %empty  */
#line 143 "dish.y"
                {
                }
#line 1503 "dish.tab.c"
    break;

  case 10: /* Options: CASE Disambiguator  */
#line 147 "dish.y"
                {
                    (yyval.options) = (yyvsp[0].options);
                    (yyval.options).case_sensitive = true;
                }
#line 1512 "dish.tab.c"
    break;

  case 11: /* Options: Disambiguator  */
#line 152 "dish.y"
                {
                    (yyval.options) = (yyvsp[0].options);
                    (yyval.options).case_sensitive = false;
                }
#line 1521 "dish.tab.c"
    break;

  case 12: /* Disambiguator: '[' INTEGER FROM ORDINAL ']' Offset  */
#line 158 "dish.y"
                {
                    (yyval.options) = (yyvsp[0].options);
                    (yyval.options).ordinal = (yyvsp[-4].integral_literal);
                    (yyval.options).direction = (Options::Direction)(yyvsp[-2].integral_literal);
                }
#line 1531 "dish.tab.c"
    break;

  case 13: /* Disambiguator: Offset  */
#line 164 "dish.y"
                {
                    (yyval.options) = (yyvsp[0].options);
                    (yyval.options).ordinal = -1;
                }
#line 1540 "dish.tab.c"
    break;

  case 14: /* Offset: '+' '[' Number ',' Number ']'  */
#line 170 "dish.y"
                {
                    (yyval.options).offset = Coordinates{(yyvsp[-3].numeric_literal), (yyvsp[-1].numeric_literal)};
                }
#line 1548 "dish.tab.c"
    break;

  case 15: /* Offset: %empty  */
#line 174 "dish.y"
                {
                    (yyval.options).offset = Coordinates{0,0};
                }
#line 1556 "dish.tab.c"
    break;

  case 16: /* Number: NUMBER  */
#line 179 "dish.y"
                {
                    (yyval.numeric_literal) = (yyvsp[0].numeric_literal);
                }
#line 1564 "dish.tab.c"
    break;

  case 17: /* Number: INTEGER  */
#line 183 "dish.y"
                {
                    (yyval.numeric_literal) = (yyvsp[0].integral_literal);
                }
#line 1572 "dish.tab.c"
    break;


#line 1576 "dish.tab.c"

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
      {
        yypcontext_t yyctx
          = {yyssp, yytoken};
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == -1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *,
                             YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (yymsg)
              {
                yysyntax_error_status
                  = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
                yymsgp = yymsg;
              }
            else
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = YYENOMEM;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == YYENOMEM)
          YYNOMEM;
      }
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
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
  return yyresult;
}

#line 187 "dish.y"


static FILE* yyin = stdin;
int yylex()
{
  static enum { SEEN_NOTHING = 0, SEEN_WAIT, SEEN_CASE, SEEN_ORDINAL_BEGIN, SEEN_ORDINAL_END, SEEN_OFFSET_BEGIN, SEEN_OFFSET_END, SEEN_KEY_CMD, SEEN_SLEEP_CMD } line_state;
  static char* buffer;
  static char* buffer_end;
  static char* saveptr;
  const static regex INTEGRAL("-?[0-9]+",regex_constants::extended);
  const static regex NUMERIC("[-+]?[0-9]+(\\.[0-9]+)?",regex_constants::extended);
  const unordered_set<string> DIRECTIONS { "left", "right", "top", "bottom" };

  char* token = NULL;
  size_t ignored;

  if(!buffer)
  {
    line_state = SEEN_NOTHING;
    if(saveptr)
    {
      free(saveptr);
      saveptr = nullptr;
      return 0;
    }
    if(getline(&buffer,&ignored,yyin)==-1)
      return 0;
    
    buffer_end = buffer + strlen(buffer);
    while(*(buffer_end-1)=='\n' || *(buffer_end-1)==' ' || *(buffer_end-1)=='\t')
    {
      buffer_end--;
      *buffer_end = '\0';
    }
    
    token = strtok_r(buffer," \t",&saveptr);
  }
  else if(!(token = strtok_r(NULL," \t",&saveptr)))
  {
    free(buffer);
    line_state = SEEN_NOTHING;
    buffer = NULL;
    return 0;
  }

  if(token+strlen(token)==buffer_end)
  {
    saveptr = buffer;
    buffer = nullptr;
  }

  if(!strcmp(token,"click") && line_state==SEEN_NOTHING)
    return CLICK;
  else if(!strcmp(token,"seek") && line_state==SEEN_NOTHING)
    return SEEK;
  else if(!strcmp(token,"type") && line_state==SEEN_NOTHING)
    return TYPE;
  else if(!strcmp(token,"print") && line_state==SEEN_NOTHING)
    return PRINT;
  else if(!strcmp(token,"wait") && line_state==SEEN_NOTHING)
  {
    line_state = SEEN_WAIT;
    return WAIT;
  }
  else if(!strcmp(token,"key") && line_state==SEEN_NOTHING)
  {
    line_state = SEEN_KEY_CMD;
    return KEY;
  }
  else if(!strcmp(token,"sleep") && line_state==SEEN_NOTHING)
  {
    line_state = SEEN_SLEEP_CMD;
    return SLEEP;
  }
  else if(!strcmp(token,"-case") && line_state < SEEN_CASE)
  {
    line_state = SEEN_CASE;
    return CASE;
  }
  else if(!strcmp(token,"from") && line_state==SEEN_ORDINAL_BEGIN)
    return FROM;
  else if(!strcmp(token,"[") && line_state < SEEN_OFFSET_BEGIN)
  {
    line_state = line_state < SEEN_ORDINAL_BEGIN ? SEEN_ORDINAL_BEGIN : SEEN_OFFSET_BEGIN;
    return '[';
  }
  else if(!strcmp(token,"]") && line_state < SEEN_OFFSET_END)
  {
    line_state = line_state < SEEN_ORDINAL_END ? SEEN_ORDINAL_END : SEEN_OFFSET_END;
    return ']';
  }
  else if(!strcmp(token,"+") && line_state < SEEN_OFFSET_BEGIN)
  {
    line_state = SEEN_ORDINAL_END;
    return '+';
  }
  else if(!strcmp(token,",") && line_state==SEEN_OFFSET_BEGIN)
    return ',';
  else if((line_state==SEEN_ORDINAL_BEGIN || line_state==SEEN_OFFSET_BEGIN || line_state==SEEN_SLEEP_CMD || line_state==SEEN_WAIT) && regex_match(token,NUMERIC))
  {
    if(*token=='+')
      token++;

    if(regex_match(token,INTEGRAL))
    {
      yylval.integral_literal = atoi(token);
      return INTEGER;
    }

    yylval.numeric_literal = Number{token};
    return NUMBER;
  }
  else if(line_state==SEEN_ORDINAL_BEGIN && DIRECTIONS.count(token))
  {
    if(!strcmp(token,"left"))
      yylval.integral_literal = Options::LEFT;
    else if(!strcmp(token,"right"))
      yylval.integral_literal = Options::RIGHT;
    else if(!strcmp(token,"top"))
      yylval.integral_literal = Options::TOP;
    else
    {
      assert(!strcmp(token,"bottom"));
      yylval.integral_literal = Options::BOTTOM;
    }
    return ORDINAL;
  }
  //No match, but special because of previously seen key command
  else if(line_state==SEEN_KEY_CMD)
  {
    yylval.key_list.begin_ptr = token;
    while(*token)
    {
      if(*token=='+')
        *token = '\0';
      token++;
    }
    yylval.key_list.end_ptr = token;

    return KEY_LIST;
  }

  //Okay, nothing special found, so just return the remainder of the line as a single STRING token
  char* token_end = token + strlen(token);
  if(token_end!=buffer_end)
  {
    *token_end = ' ';
    saveptr = buffer;
    buffer = nullptr;
  }

  yylval.text_literal = token;
  return STRING;
}

void yyerror(const char* e_str)
{
  cerr << e_str << endl;
}

struct Paddle_Entry
{
  unsigned x_left, x_right, y_top, y_bottom;
  string characters;

  Coordinates center() const { return Coordinates{(x_left+x_right)/2,(y_top+y_bottom)/2}; }
  Coordinates left() const { return Coordinates{x_left,(y_top+y_bottom)/2}; }
  Coordinates right() const { return Coordinates{x_right,(y_top+y_bottom)/2}; }
  Coordinates top() const { return Coordinates{(x_left+x_right)/2,y_top}; }
  Coordinates bottom() const { return Coordinates{(x_left+x_right)/2,y_bottom}; }
  unsigned width() const { return x_right - x_left; }
  unsigned height() const { return y_bottom - y_top; }
  Paddle_Entry subentry(string to_match) const;
  unsigned intersects(const Paddle_Entry& other) const; //returns number of pixels

  void merge_with(const Paddle_Entry& other);
};

Paddle_Entry Paddle_Entry::subentry(string to_match) const
{
  Paddle_Entry to_return{};
  int idx;
  if((idx=characters.find(to_match))==-1)
    return to_return;

  Number pixels_per_char = Number{width()}/characters.length();
  pixels_per_char.round(Number{1,8});
  to_return.x_left = x_left + (int64_t)(idx*pixels_per_char);
  to_return.x_right = x_left + (int64_t)((idx+to_match.length())*pixels_per_char);
  to_return.y_top = y_top;
  to_return.y_bottom = y_bottom;
  to_return.characters = to_match;
  return to_return;
}

unsigned Paddle_Entry::intersects(const Paddle_Entry& other) const
{
  int x_left_interect = max(x_left,other.x_left);
  int x_right_intersect = min(x_right,other.x_right);
  int y_top_intersect = max(y_top,other.y_top);
  int y_bottom_intersect = min(y_bottom,other.y_bottom);

  if(x_right_intersect - x_left_interect > 0 && y_bottom_intersect - y_top_intersect > 0)
    return (x_right_intersect-x_left_interect)*(y_bottom_intersect-y_top_intersect);
  return 0;
}

void Paddle_Entry::merge_with(const Paddle_Entry& other)
{
  x_left = min(x_left,other.x_left);
  x_right = max(x_right,other.x_right);
  y_top = min(y_top,other.y_top);
  y_bottom = max(y_bottom,other.y_bottom);
  characters += '\n'+other.characters;
}

static pair<unsigned,unsigned> parse_paddle_token(string token)
{
  token = StringFunctions::slice(token,1,INT_MAX);
  vector<string> tokens;
  StringFunctions::strsplit(tokens,token,", ");
  return make_pair(stoi(tokens[0]),stoi(tokens[1]));
}

static Paddle_Entry get_paddle_entry_for_line(string line)
{
  vector<string> tokens;
  StringFunctions::strsplit(tokens,line,": [[");
  if(tokens.size()==1)
    return Paddle_Entry{};

  line = tokens[1];
  tokens.clear();
  StringFunctions::strsplit(tokens,line,"], ");
  if(tokens.size() < 5)
    return Paddle_Entry{};

  for(unsigned i=5; i<tokens.size(); i++)
    tokens[4]+="], "+tokens[i];
  tokens.resize(5);

  tokens[3] = StringFunctions::slice(tokens[3],0,-1);
  Paddle_Entry to_return{UINT_MAX,0,UINT_MAX,0};
  for(unsigned i=0; i<4; i++)
  {
    pair<unsigned,unsigned> bound = parse_paddle_token(tokens[i]);
    to_return.x_left = min(to_return.x_left,bound.first);
    to_return.x_right = max(to_return.x_right,bound.first);
    to_return.y_top = min(to_return.y_top,bound.second);
    to_return.y_bottom = max(to_return.y_bottom,bound.second);
  }

  tokens[4] = StringFunctions::slice(tokens[4],2,tokens[4].rfind(", ")-1);
  bool backslash_escape = 0;
  for(unsigned i=0; i<tokens[4].size(); i++)
    if(tokens[4][i]=='\\')
    {
      if(backslash_escape)
        to_return.characters+=tokens[4][i];
      backslash_escape = !backslash_escape;
    }
    else
      to_return.characters+=tokens[4][i];

  return to_return;
}

string process_escape_sequences(const string& text)
{
  string new_body;
  bool backslash_active = false;
  for(char c : text)
    if(backslash_active)
    {
      if(c=='n')
        new_body+='\n';
      else if(c=='\\')
        new_body+='\\';
      else
      {
        cerr << "Invalid escape sequence in text: " << text << endl;
        exit(3);
      }
      backslash_active = false;
    }
    else
      if(c!='\\')
        new_body+=c;
      else
        backslash_active = True;
  return new_body;
}

template<class T>
T get_matches(string text, const Options& options, istream& paddle_in)
{
  if(!options.case_sensitive)
    text = StringFunctions::upperCase(text);
  
  T matches;
  string line;
  while(getline(paddle_in,line))
  {
    if(line.find("INFO: [[[")==-1)
      continue;

    Paddle_Entry entry = get_paddle_entry_for_line(line);
    if(!options.case_sensitive)
      entry.characters = StringFunctions::upperCase(entry.characters);
    entry = entry.subentry(text);
    if(entry.characters.length())
      matches.push_back(entry);
  }
  
  return matches;
}

Coordinates disambiguate_matches(const string& text, Options options, vector<Paddle_Entry>& matches)
{
  if(matches.empty())
  {
    cerr << "Could not find text: " << text << endl;
    exit(1);
  }

  Paddle_Entry entry;
  if(options.ordinal==-1)
    if(matches.size()==1)
      entry = matches[0];
    else
    {
      cerr << "Multiple matches for text: " << text << endl;
      exit(2);
    }
  else
  {
    if(matches.size() < options.ordinal)
    {
      cerr << "Too few matches for text: " << text << endl;
      exit(1);
    }

    auto paddle_entry_comparator = [&options,&text](const Paddle_Entry& left, const Paddle_Entry& right)
      {
        switch(options.direction)
        {
        case Options::LEFT: return left.center().x < right.center().x;
        case Options::RIGHT: return left.center().x > right.center().x;
        case Options::TOP: return left.center().y < right.center().y;
        case Options::BOTTOM: return left.center().y > right.center().y;
        }
      };
    
    sort(matches.begin(),matches.end(),paddle_entry_comparator);

    unsigned match_idx = options.ordinal-1;
    entry = matches[match_idx];
    
    if(matches.size() > match_idx+1 && !paddle_entry_comparator(entry,matches[match_idx+1]))
    {
      cerr << "Could not disambiguate matches for text: " << text << endl;
      exit(2);
    }
    
    if(match_idx && !paddle_entry_comparator(matches[match_idx-1],entry))
    {
      cerr << "Could not disambiguate matches for text: " << text << endl;
      exit(2);
    }
  }

  options.offset.x *= entry.width();
  options.offset.y *= entry.height();

  Coordinates offset_point = entry.center();
  if(options.offset.x != 0)
    offset_point.x = options.offset.x < 0 ? entry.x_left : entry.x_right;
  if(options.offset.y != 0)
    offset_point.y = options.offset.y < 0 ? entry.y_top : entry.y_bottom;

  offset_point.x += options.offset.x;
  offset_point.y += options.offset.y;
  offset_point.x.round(1);
  offset_point.y.round(1);
  return offset_point;
}

static vector<string> backend_cmd = {"paddleocr", "--lang", "en", "--det_db_score_mode", "slow", "--image_dir", "dish_current_screenshot.png"};
void dump_ocr_to_txt()
{
  system("import -window root dish_current_screenshot.png");
  auto paddle = spawn(backend_cmd);
  get_streams(paddle);

  vector<Paddle_Entry> all_entries;
  string line;
  while(getline(paddle_in,line))
  {
    if(line.find("INFO: [[[")==-1)
      continue;

    all_entries.push_back(get_paddle_entry_for_line(line));
  }

  unsigned max_x = 0, max_y = 0;
  for(const Paddle_Entry& entry : all_entries)
  {
    max_x = max(max_x,entry.x_right+1);
    max_y = max(max_y,entry.y_bottom+1);
  }

  unsigned resolution = 16;
  while(resolution)
  {
    unsigned width = max_x/resolution;
    unsigned height = max_y/resolution;
    char* linear_ptr = (char*)alloca(width*height);
    MultiArray<char,2> text_map_(linear_ptr,height,width);
    stack<int> s;
    Array_Index_Swapper<MultiArray<char,2>,int,2> text_map(text_map_,s);
    bzero(linear_ptr,width*height);
    for(const Paddle_Entry& entry : all_entries)
    {
      unsigned x_coord = entry.x_left/resolution;
      unsigned y_coord = entry.y_top/resolution;
      for(char c : entry.characters)
      {
        if(text_map[x_coord][y_coord])
          goto fail;
        text_map[x_coord++][y_coord] = c;
      }
    }

    for(unsigned j=0; j<height; j++)
      for(int i=width-1; i>=0; i--)
        if(text_map[i][j])
        {
          for(i=i-1; i>=0; i--)
            if(!text_map[i][j])
              text_map[i][j]=' ';
          break;
        }

    for(unsigned j=0; j<height; j++)
        if(text_map[0][j])
          cout << &text_map[0][j] << endl;
    
    return;

  fail:
    resolution/=2;
  }
}

Coordinates get_coordinates(string text, Options options)
{
  #ifdef PARSER_TEST
  return Coordinates{0,0};
  #endif
  
  system("import -window root dish_current_screenshot.png");
  auto paddle = spawn(backend_cmd);
  get_streams(paddle);

  text = process_escape_sequences(text);
  vector<string> result;
  StringFunctions::tokenize(result,text,"\n");

  //Common case: only matching single line
  if(result.size()==1)
    return disambiguate_matches(text,options,rtolvalue<vector<Paddle_Entry>>(get_matches<vector<Paddle_Entry>>(text,options,paddle_in)));

  //Complex case: attemping to match multiple lines of text
  string paddle_str;
  getline(paddle_in,paddle_str,'\0');
  istringstream stream_in{paddle_str};
  vector<vector<Paddle_Entry>> match_table;
  match_table.reserve(result.size()-1);
  list<Paddle_Entry> final_matches = get_matches<list<Paddle_Entry>>(result[0],options,stream_in);
  for(int i=1; i<result.size(); i++)
  {
    stream_in.clear(); stream_in.seekg(0);
    match_table.push_back(get_matches<vector<Paddle_Entry>>(result[i],options,stream_in));
  }

  //Now, iteratively attempt to match against the next line until all lines have been considered.

  /*Y Axis bounding box tolerance of 10 pixels.  Theoretically, the top of the
    next line's bounding box should be on the exact same Y coordinate as the
    bottom of the current line's bounding box, but we live in a dark and twisted
    world.*/
  const static unsigned Y_BB_TOLERANCE = 10;
  for(auto& row : match_table)
    for(auto& entry : row)
      entry.y_top -= min(entry.y_top,Y_BB_TOLERANCE);

  for(auto& row : match_table)
    for(list<Paddle_Entry>::iterator f_it=final_matches.begin(), next; f_it!=final_matches.end(); f_it=next)
    {
      next = std::next(f_it);
      
      Paddle_Entry* best_intersector;
      unsigned best_intersection = 0;
      for(Paddle_Entry& entry : row)
      {
        unsigned intersection = f_it->intersects(entry);
        if(intersection > best_intersection)
        {
          best_intersector = &entry;
          best_intersection = intersection;
        }
      }

      if(best_intersection)
      {
        f_it->merge_with(*best_intersector);
        row.erase(row.begin()+(best_intersector-&row[0]));
      }
      else
        final_matches.erase(f_it);
    }

  return disambiguate_matches(text,options,rtolvalue<vector<Paddle_Entry>>(vector<Paddle_Entry>(final_matches.begin(),final_matches.end())));
}

void xmacroplay(const string& x)
{
  #ifdef PARSER_TEST
  cout << x << endl;
  return;
  #endif
  
  static Display* display;
  static int screen;
  if(!display)
  {
    display = remoteDisplay(NULL);
    screen = DefaultScreen(display);
  }
  xmacro_command(display,screen,x.c_str());
}

int main(int argc, char** argv)
{
  int retval;
  
  string single_command;
  if(argc > 1)
  {
    unsigned command_idx = 1;
    if(!strcmp(argv[1],"--backend"))
    {
      
      command_idx+=2;
      backend_cmd.clear();
      backend_cmd.push_back(argv[2]);
    }

    if(command_idx < argc)
    {
      single_command = argv[command_idx];
      for(unsigned i=command_idx+1; i<argc; i++)
        single_command += string(" ") + argv[i];
      yyin = fmemopen(&single_command[0],single_command.length(),"r");
    }
  }
  
  while(!feof(yyin) && !(retval = yyparse()));
  
  return retval;
}

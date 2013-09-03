/* A Bison parser, made by GNU Bison 2.7.12-4996.  */

/* Bison implementation for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2013 Free Software Foundation, Inc.
   
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

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.7.12-4996"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 1

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
/* Line 371 of yacc.c  */
#line 38 "../../../mutabor-git/src/kernel/mut.yy"


/* BEGIN MUT_TAB.C */

/* MUTABOR / Version 2.1 */

//#pragma warn -cln
//#pragma warn -aus
//#pragma warn -sig
//#pragma warn -par


#include <ctype.h>
#include <limits.h>
#include <errno.h>
#include "src/kernel/box.h"
#include "src/kernel/Global.h"
#include "src/kernel/Parser.h"
#include "src/kernel/Hilfs.h"
#include "src/kernel/Execute.h"

#ifdef _
#undef _
#endif
#define _ _mut

#ifdef __cplusplus
	namespace mutabor {
		namespace hidden {
			extern "C" {
#endif

#define MAX_IDENTIFIER_LEN 80

#define FEHLERZEILE yylloc.first_line+1

#ifdef alloca
#undef alloca
#define alloca make_an_error ---
#endif
#define YYERROR_VERBOSE 1
#define YYMALLOC(size) xmalloc(box,size)
#define YYFREE(X) do { /* empty */; } while (YYID (0))
#define YYMAXLIMIT (HEAP_PORTION_SYNTAX / sizeof(YYLTYPE) - 1)
                   /* wegen fehlendem alloca in PUREC */

/* Line 371 of yacc.c  */
#line 115 "../../../mutabor-git/src/kernel/mut.cc"

# ifndef YY_NULL
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULL nullptr
#  else
#   define YY_NULL 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 1
#endif

/* In a future release of Bison, this section will be replaced
   by #include "y.tab.h".  */
#ifndef YY_YY__MUTABOR_GIT_SRC_KERNEL_MUT_HH_INCLUDED
# define YY_YY__MUTABOR_GIT_SRC_KERNEL_MUT_HH_INCLUDED
/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     MUTABOR_TOKEN_IDENTIFIER = 258,
     MUTABOR_TOKEN_F_NUMBER = 259,
     MUTABOR_TOKEN_INTEGER = 260,
     MUTABOR_TOKEN_INTERVAL = 261,
     MUTABOR_TOKEN_TONE = 262,
     MUTABOR_TOKEN_TONESYSTEM = 263,
     MUTABOR_TOKEN_RETUNING = 264,
     MUTABOR_TOKEN_HARMONY = 265,
     MUTABOR_TOKEN_LOGIC = 266,
     MUTABOR_TOKEN_MIDICHANNEL = 267,
     MUTABOR_TOKEN_KEY = 268,
     MUTABOR_TOKEN_FORM = 269,
     MUTABOR_TOKEN_ROOT = 270,
     MUTABOR_TOKEN_MIDI_IN = 271,
     MUTABOR_TOKEN_MIDI_OUT = 272,
     MUTABOR_TOKEN_HARMONY_ANALYSIS = 273,
     MUTABOR_TOKEN_CALLS = 274,
     MUTABOR_TOKEN_ELSE = 275,
     MUTABOR_TOKEN_PARAMETER = 276,
     MUTABOR_TOKEN_ENDOFFILE = 277,
     MUTABOR_TOKEN_ERROR = 278,
     MUTABOR_TOKEN_SPACES = 279,
     MUTABOR_TOKEN_COMMENT = 280,
     MUTABOR_TOKEN_COMMENT_START = 281,
     MUTABOR_TOKEN_COMMENT_END = 282,
     MUTABOR_TOKEN_OTHER = 283
   };
#endif
/* Tokens.  */
#define MUTABOR_TOKEN_IDENTIFIER 258
#define MUTABOR_TOKEN_F_NUMBER 259
#define MUTABOR_TOKEN_INTEGER 260
#define MUTABOR_TOKEN_INTERVAL 261
#define MUTABOR_TOKEN_TONE 262
#define MUTABOR_TOKEN_TONESYSTEM 263
#define MUTABOR_TOKEN_RETUNING 264
#define MUTABOR_TOKEN_HARMONY 265
#define MUTABOR_TOKEN_LOGIC 266
#define MUTABOR_TOKEN_MIDICHANNEL 267
#define MUTABOR_TOKEN_KEY 268
#define MUTABOR_TOKEN_FORM 269
#define MUTABOR_TOKEN_ROOT 270
#define MUTABOR_TOKEN_MIDI_IN 271
#define MUTABOR_TOKEN_MIDI_OUT 272
#define MUTABOR_TOKEN_HARMONY_ANALYSIS 273
#define MUTABOR_TOKEN_CALLS 274
#define MUTABOR_TOKEN_ELSE 275
#define MUTABOR_TOKEN_PARAMETER 276
#define MUTABOR_TOKEN_ENDOFFILE 277
#define MUTABOR_TOKEN_ERROR 278
#define MUTABOR_TOKEN_SPACES 279
#define MUTABOR_TOKEN_COMMENT 280
#define MUTABOR_TOKEN_COMMENT_START 281
#define MUTABOR_TOKEN_COMMENT_END 282
#define MUTABOR_TOKEN_OTHER 283



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{
/* Line 387 of yacc.c  */
#line 85 "../../../mutabor-git/src/kernel/mut.yy"

    double      f_value;        /* f〉 Gleitkommazahlen */
    int         integer;        /* F〉 integers */
    char        *identifier;    /* F〉 Namen */


/* Line 387 of yacc.c  */
#line 221 "../../../mutabor-git/src/kernel/mut.cc"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
} YYLTYPE;
# define yyltype YYLTYPE /* obsolescent; will be withdrawn */
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif


#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (mutabor_box_type * box);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */

#endif /* !YY_YY__MUTABOR_GIT_SRC_KERNEL_MUT_HH_INCLUDED  */

/* Copy the second part of user declarations.  */
/* Line 390 of yacc.c  */
#line 136 "../../../mutabor-git/src/kernel/mut.yy"

int yylex(YYSTYPE* lvalp, YYLTYPE* llocp,  mutabor_box_type * box);
void yyerror(YYLTYPE* locp, mutabor_box_type * box, const char* err)
{
	mutabor_error_message(box,
			      false,
			      _("%s at line %d"),
			      err,
			      locp->first_line);
}

#define YYLEX_PARAM box
//#define scanner box

/* Line 390 of yacc.c  */
#line 276 "../../../mutabor-git/src/kernel/mut.cc"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

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

#ifndef __attribute__
/* This feature is available in gcc versions 2.5 and later.  */
# if (! defined __GNUC__ || __GNUC__ < 2 \
      || (__GNUC__ == 2 && __GNUC_MINOR__ < 5))
#  define __attribute__(Spec) /* empty */
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif


/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(N) (N)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
#endif

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
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
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
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
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
#   if ! defined malloc && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
	     && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE) + sizeof (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (YYID (0))
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  2
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   342

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  47
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  98
/* YYNRULES -- Number of rules.  */
#define YYNRULES  205
/* YYNRULES -- Number of states.  */
#define YYNSTATES  377

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   283

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      37,    38,    42,    32,    36,    31,    45,    33,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    30,     2,
      40,    29,    41,     2,    39,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    34,     2,    35,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    43,     2,    44,    46,     2,     2,     2,
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
      25,    26,    27,    28
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     4,     7,    10,    13,    16,    19,    22,
      25,    28,    31,    32,    35,    36,    39,    45,    51,    55,
      59,    62,    65,    66,    69,    70,    73,    77,    83,    87,
      93,    97,   100,   101,   104,   107,   110,   114,   118,   123,
     128,   134,   140,   142,   145,   149,   154,   157,   158,   161,
     162,   165,   166,   175,   176,   186,   188,   192,   194,   195,
     197,   199,   203,   205,   207,   211,   213,   215,   217,   220,
     223,   224,   227,   228,   229,   235,   236,   237,   246,   248,
     250,   252,   254,   256,   258,   260,   262,   264,   266,   268,
     272,   276,   282,   288,   294,   300,   308,   316,   326,   336,
     346,   356,   366,   376,   386,   396,   397,   402,   404,   408,
     409,   413,   415,   419,   420,   422,   424,   426,   427,   432,
     433,   438,   439,   444,   445,   450,   451,   456,   457,   463,
     464,   471,   472,   479,   480,   485,   487,   491,   493,   494,
     500,   501,   507,   509,   510,   516,   517,   523,   525,   528,
     529,   535,   536,   543,   544,   550,   551,   557,   560,   561,
     564,   565,   573,   577,   578,   581,   583,   587,   589,   592,
     595,   596,   597,   601,   602,   610,   611,   620,   621,   624,
     625,   633,   634,   640,   646,   650,   654,   656,   658,   660,
     663,   666,   667,   673,   675,   679,   681,   684,   685,   688,
     693,   700,   707,   715,   725,   727
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
      48,     0,    -1,    -1,    48,    49,    -1,    48,    54,    -1,
      48,    63,    -1,    48,    75,    -1,    48,   120,    -1,    48,
     127,    -1,    48,   141,    -1,    48,     1,    -1,     6,    50,
      -1,    -1,    50,    51,    -1,    -1,    52,    53,    -1,     3,
      29,   144,    30,   144,    -1,     3,    29,   144,    15,   144,
      -1,     3,    29,    59,    -1,     3,    29,     1,    -1,     3,
       1,    -1,     7,    55,    -1,    -1,    55,    56,    -1,    -1,
      57,    58,    -1,     3,    29,   144,    -1,     3,    29,     3,
      31,    59,    -1,     3,    29,     3,    -1,     3,    29,     3,
      32,    59,    -1,     3,    29,     1,    -1,    62,    60,    -1,
      -1,    60,    61,    -1,    32,     3,    -1,    31,     3,    -1,
      32,   144,     3,    -1,    31,   144,     3,    -1,    32,    33,
     144,     3,    -1,    31,    33,   144,     3,    -1,    32,   144,
      33,   144,     3,    -1,    31,   144,    33,   144,     3,    -1,
       3,    -1,   144,     3,    -1,    33,   144,     3,    -1,   144,
      33,   144,     3,    -1,     8,    64,    -1,    -1,    64,    65,
      -1,    -1,    66,    67,    -1,    -1,     3,    29,     5,    34,
      70,    35,    68,    59,    -1,    -1,     3,    29,     5,    34,
      70,    35,    69,    31,    59,    -1,    71,    -1,    70,    36,
      71,    -1,     3,    -1,    -1,     1,    -1,     3,    -1,    72,
      36,     3,    -1,     1,    -1,    74,    -1,    73,    36,    74,
      -1,     1,    -1,     3,    -1,     5,    -1,    31,     5,    -1,
       9,    76,    -1,    -1,    76,    77,    -1,    -1,    -1,     3,
      78,    29,    79,    82,    -1,    -1,    -1,     3,    80,    37,
      72,    38,    29,    81,    82,    -1,    83,    -1,    84,    -1,
      85,    -1,    86,    -1,    87,    -1,    98,    -1,   101,    -1,
     104,    -1,   110,    -1,   118,    -1,     1,    -1,     5,    34,
      35,    -1,     3,    34,    35,    -1,    39,    32,     5,    34,
      35,    -1,    39,    32,     3,    34,    35,    -1,    39,    31,
       5,    34,    35,    -1,    39,    31,     3,    34,    35,    -1,
      34,    40,    40,     5,    41,    41,    35,    -1,    34,    40,
      40,     3,    41,    41,    35,    -1,    34,    40,    40,    39,
      32,     5,    41,    41,    35,    -1,    34,    40,    40,    39,
      32,     3,    41,    41,    35,    -1,    34,    40,    40,    39,
      31,     5,    41,    41,    35,    -1,    34,    40,    40,    39,
      31,     3,    41,    41,    35,    -1,    34,    40,    40,    39,
      42,     5,    41,    41,    35,    -1,    34,    40,    40,    39,
      42,     3,    41,    41,    35,    -1,    34,    40,    40,    39,
      33,     5,    41,    41,    35,    -1,    34,    40,    40,    39,
      33,     3,    41,    41,    35,    -1,    -1,    34,    88,    89,
      35,    -1,    93,    -1,    93,    36,    91,    -1,    -1,    36,
      90,    91,    -1,    92,    -1,    91,    36,    92,    -1,    -1,
      93,    -1,     3,    -1,    39,    -1,    -1,     3,    32,    94,
      59,    -1,    -1,    39,    32,    95,    59,    -1,    -1,     3,
      31,    96,    59,    -1,    -1,    39,    31,    97,    59,    -1,
      -1,    34,    35,    99,    59,    -1,    -1,    34,    35,   100,
      31,    59,    -1,    -1,    34,    35,    39,    32,   102,    59,
      -1,    -1,    34,    35,    39,    31,   103,    59,    -1,    -1,
      43,   105,   106,    44,    -1,   107,    -1,   106,    36,   107,
      -1,     3,    -1,    -1,     3,    37,   108,    73,    38,    -1,
      -1,    17,    37,   109,   140,    38,    -1,    18,    -1,    -1,
       5,    43,   111,   113,    44,    -1,    -1,     3,    43,   112,
     113,    44,    -1,   114,    -1,   113,   114,    -1,    -1,     5,
      31,    41,   115,   106,    -1,    -1,    31,     5,    31,    41,
     116,   106,    -1,    -1,    20,    31,    41,   117,   106,    -1,
      -1,    17,    37,   119,   140,    38,    -1,    10,   121,    -1,
      -1,   121,   122,    -1,    -1,     3,    29,    43,   123,   125,
      44,   124,    -1,     3,    29,     1,    -1,    -1,    45,     5,
      -1,   126,    -1,   125,    36,   126,    -1,     5,    -1,    42,
       5,    -1,    11,   128,    -1,    -1,    -1,   128,   129,   130,
      -1,    -1,     3,   138,    29,    34,   131,   133,    35,    -1,
      -1,     3,   138,    29,     3,    34,   132,   133,    35,    -1,
      -1,   133,   134,    -1,    -1,   138,    31,    41,    43,   135,
     106,    44,    -1,    -1,   138,    31,    41,   136,   107,    -1,
       5,    46,     3,    46,     5,    -1,     3,    46,     5,    -1,
       5,    46,     3,    -1,     3,    -1,    20,    -1,   137,    -1,
      14,   137,    -1,    13,     3,    -1,    -1,    16,    37,   139,
     140,    38,    -1,     5,    -1,   140,    36,     5,    -1,     1,
      -1,    12,   142,    -1,    -1,   142,   143,    -1,     5,    31,
      41,     5,    -1,     5,    31,    41,     5,    31,     5,    -1,
       5,    31,    41,    34,     5,    35,    -1,     5,    31,    41,
       5,    34,     5,    35,    -1,     5,    31,    41,     5,    31,
       5,    34,     5,    35,    -1,     4,    -1,     5,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   154,   154,   155,   156,   157,   158,   159,   160,   161,
     162,   169,   171,   173,   177,   177,   181,   189,   200,   202,
     209,   218,   220,   222,   226,   226,   230,   233,   237,   241,
     245,   255,   259,   261,   264,   267,   270,   273,   276,   286,
     296,   306,   331,   339,   342,   352,   382,   384,   386,   390,
     390,   395,   394,   399,   398,   404,   404,   407,   408,   409,
     418,   419,   421,   431,   432,   433,   443,   444,   445,   451,
     453,   455,   460,   462,   459,   467,   470,   466,   476,   477,
     478,   479,   480,   481,   482,   483,   484,   485,   486,   496,
     498,   503,   505,   507,   509,   514,   516,   521,   523,   525,
     527,   529,   531,   533,   535,   541,   540,   550,   551,   553,
     553,   560,   561,   566,   570,   574,   575,   577,   577,   580,
     580,   583,   583,   586,   586,   593,   593,   596,   596,   602,
     602,   605,   605,   611,   611,   617,   618,   622,   624,   624,
     628,   627,   631,   635,   635,   638,   638,   644,   645,   650,
     649,   654,   653,   658,   657,   665,   664,   672,   676,   677,
     682,   681,   686,   696,   697,   701,   702,   706,   707,   711,
     715,   716,   716,   724,   723,   729,   728,   736,   737,   742,
     742,   746,   746,   752,   754,   756,   758,   763,   764,   765,
     766,   767,   767,   773,   775,   777,   787,   791,   792,   796,
     798,   800,   802,   804,   809,   810
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 1
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "MUTABOR_TOKEN_IDENTIFIER",
  "MUTABOR_TOKEN_F_NUMBER", "MUTABOR_TOKEN_INTEGER",
  "MUTABOR_TOKEN_INTERVAL", "MUTABOR_TOKEN_TONE",
  "MUTABOR_TOKEN_TONESYSTEM", "MUTABOR_TOKEN_RETUNING",
  "MUTABOR_TOKEN_HARMONY", "MUTABOR_TOKEN_LOGIC",
  "MUTABOR_TOKEN_MIDICHANNEL", "MUTABOR_TOKEN_KEY", "MUTABOR_TOKEN_FORM",
  "MUTABOR_TOKEN_ROOT", "MUTABOR_TOKEN_MIDI_IN", "MUTABOR_TOKEN_MIDI_OUT",
  "MUTABOR_TOKEN_HARMONY_ANALYSIS", "MUTABOR_TOKEN_CALLS",
  "MUTABOR_TOKEN_ELSE", "MUTABOR_TOKEN_PARAMETER",
  "MUTABOR_TOKEN_ENDOFFILE", "MUTABOR_TOKEN_ERROR", "MUTABOR_TOKEN_SPACES",
  "MUTABOR_TOKEN_COMMENT", "MUTABOR_TOKEN_COMMENT_START",
  "MUTABOR_TOKEN_COMMENT_END", "MUTABOR_TOKEN_OTHER", "'='", "':'", "'-'",
  "'+'", "'/'", "'['", "']'", "','", "'('", "')'", "'@'", "'<'", "'>'",
  "'*'", "'{'", "'}'", "'.'", "'~'", "$accept", "start",
  "intervalldeklaration", "intervalldekl1", "intervalldekl2_1", "$@1",
  "intervalldekl2", "tondeklaration", "tondekl1", "tondekl2_1", "$@2",
  "tondekl2", "KOMPLEX_TON_LIST", "KOMPLEX_TON_LIST_2", "KOMPLEX_TON_1",
  "KOMPLEX_TON_START", "tonsystemdeklaration", "tonsystemdekl1",
  "tonsystemdekl2_1", "$@3", "tonsystemdekl2", "$@4", "$@5", "tonliste",
  "ton_element", "parameter_liste", "argument_liste",
  "argument_listenelement", "umstimmungdeklaration", "umstimmungs_dekl_1",
  "umstimmungs_dekl_2", "$@6", "$@7", "$@8", "$@9", "umstimmungs_dekl_3",
  "umstimmungs_dekl_taste_abs", "umstimmungs_dekl_taste_rel",
  "umstimmungs_dekl_breite_abs", "umstimmungs_dekl_breite_rel",
  "umstimmungs_dekl_tonhoehe_veraendert", "$@10",
  "nonempty_umstimm_expression_list", "$@11", "umstimm_expression_list",
  "umstimm_expression", "nonempty_umstimm_expression", "$@12", "$@13",
  "$@14", "$@15", "umstimmungs_dekl_wiederholung_abs", "$@16", "$@17",
  "umstimmungs_dekl_wiederholung_rel", "$@18", "$@19",
  "umstimmungs_dekl_umstimmungs_bund", "$@20", "aktions_liste", "aktion",
  "$@21", "$@22", "umstimmungs_dekl_umstimmungs_case", "$@23", "$@24",
  "umstimmungs_case_liste", "umstimmungs_case_element", "$@25", "$@26",
  "$@27", "umstimmungs_dekl_midi_out", "$@28", "harmoniedeklaration",
  "harmonie_dekl_1", "harmonie_dekl_2", "$@29", "bezugs_taste",
  "tasten_liste", "taste", "logikdeklaration", "logik_dekl_1", "$@30",
  "logik_dekl_2", "$@31", "$@32", "anweisungs_liste", "anweisung", "$@33",
  "$@34", "harmoniebezeichner", "ausloeser", "$@35", "integersequenz",
  "instrumentdeklaration", "instrument_dekl_1", "instrument_dekl_2",
  "GLEITKOMMA_ZAHL", YY_NULL
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,    61,
      58,    45,    43,    47,    91,    93,    44,    40,    41,    64,
      60,    62,    42,   123,   125,    46,   126
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    47,    48,    48,    48,    48,    48,    48,    48,    48,
      48,    49,    50,    50,    52,    51,    53,    53,    53,    53,
      53,    54,    55,    55,    57,    56,    58,    58,    58,    58,
      58,    59,    60,    60,    61,    61,    61,    61,    61,    61,
      61,    61,    62,    62,    62,    62,    63,    64,    64,    66,
      65,    68,    67,    69,    67,    70,    70,    71,    71,    71,
      72,    72,    72,    73,    73,    73,    74,    74,    74,    75,
      76,    76,    78,    79,    77,    80,    81,    77,    82,    82,
      82,    82,    82,    82,    82,    82,    82,    82,    82,    83,
      83,    84,    84,    84,    84,    85,    85,    86,    86,    86,
      86,    86,    86,    86,    86,    88,    87,    89,    89,    90,
      89,    91,    91,    92,    92,    93,    93,    94,    93,    95,
      93,    96,    93,    97,    93,    99,    98,   100,    98,   102,
     101,   103,   101,   105,   104,   106,   106,   107,   108,   107,
     109,   107,   107,   111,   110,   112,   110,   113,   113,   115,
     114,   116,   114,   117,   114,   119,   118,   120,   121,   121,
     123,   122,   122,   124,   124,   125,   125,   126,   126,   127,
     128,   129,   128,   131,   130,   132,   130,   133,   133,   135,
     134,   136,   134,   137,   137,   137,   137,   138,   138,   138,
     138,   139,   138,   140,   140,   140,   141,   142,   142,   143,
     143,   143,   143,   143,   144,   144
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     0,     2,     0,     2,     5,     5,     3,     3,
       2,     2,     0,     2,     0,     2,     3,     5,     3,     5,
       3,     2,     0,     2,     2,     2,     3,     3,     4,     4,
       5,     5,     1,     2,     3,     4,     2,     0,     2,     0,
       2,     0,     8,     0,     9,     1,     3,     1,     0,     1,
       1,     3,     1,     1,     3,     1,     1,     1,     2,     2,
       0,     2,     0,     0,     5,     0,     0,     8,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     3,
       3,     5,     5,     5,     5,     7,     7,     9,     9,     9,
       9,     9,     9,     9,     9,     0,     4,     1,     3,     0,
       3,     1,     3,     0,     1,     1,     1,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     5,     0,
       6,     0,     6,     0,     4,     1,     3,     1,     0,     5,
       0,     5,     1,     0,     5,     0,     5,     1,     2,     0,
       5,     0,     6,     0,     5,     0,     5,     2,     0,     2,
       0,     7,     3,     0,     2,     1,     3,     1,     2,     2,
       0,     0,     3,     0,     7,     0,     8,     0,     2,     0,
       7,     0,     5,     5,     3,     3,     1,     1,     1,     2,
       2,     0,     5,     1,     3,     1,     2,     0,     2,     4,
       6,     6,     7,     9,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,     0,     1,    10,    12,    22,    47,    70,   158,   170,
     197,     3,     4,     5,     6,     7,     8,     9,    11,    21,
      46,    69,   157,   169,   196,    13,     0,    23,     0,    48,
       0,    72,    71,     0,   159,     0,     0,   198,     0,    15,
       0,    25,     0,    50,     0,     0,     0,     0,   172,     0,
      20,     0,     0,     0,    73,     0,   162,   160,   186,     0,
       0,     0,     0,   187,   188,     0,     0,    19,    42,   204,
     205,     0,    18,    32,     0,    30,    28,    26,     0,     0,
      62,    60,     0,     0,     0,     0,   190,   189,   191,     0,
     199,     0,     0,    31,    43,     0,     0,     0,     0,     0,
       0,    88,     0,     0,     0,   105,     0,   133,    74,    78,
      79,    80,    81,    82,    83,    84,    85,    86,    87,     0,
       0,   167,     0,     0,   165,   184,   185,     0,     0,   173,
       0,     0,     0,    44,     0,     0,    33,    17,    16,     0,
      27,     0,    29,    59,    57,     0,    55,     0,   145,     0,
     143,   155,   125,     0,     0,     0,     0,     0,    61,    76,
     168,     0,   163,     0,   195,   193,     0,   175,   177,   200,
       0,   201,    35,     0,     0,    34,     0,     0,    45,    51,
       0,    90,     0,    89,     0,     0,     0,     0,     0,     0,
     115,   109,   116,     0,   107,     0,     0,     0,     0,   137,
       0,   142,     0,   135,     0,   166,     0,   161,   183,     0,
     192,   177,     0,     0,   202,     0,    37,     0,     0,    36,
       0,     0,     0,    56,     0,     0,     0,     0,   147,     0,
       0,   131,   129,   126,     0,     0,     0,     0,   121,   117,
     113,   123,   119,   106,   113,     0,     0,     0,     0,   138,
     140,     0,   134,    77,   164,   194,     0,   174,   178,     0,
       0,    39,     0,    38,     0,    52,     0,     0,     0,     0,
     146,   148,   144,   156,     0,     0,   128,     0,     0,     0,
       0,     0,     0,     0,     0,   110,   111,   114,     0,     0,
     108,    94,    93,    92,    91,     0,     0,   136,   176,     0,
     203,    41,    40,    54,   149,   153,     0,   132,   130,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   122,
     118,   113,   124,   120,    65,    66,    67,     0,     0,    63,
       0,   181,     0,     0,   151,    96,    95,     0,     0,     0,
       0,     0,     0,     0,     0,   112,    68,     0,   139,   141,
     179,     0,   150,   154,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    64,     0,   182,   152,   100,    99,    98,
      97,   104,   103,   102,   101,     0,   180
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,    11,    18,    25,    26,    39,    12,    19,    27,
      28,    41,    72,    93,   136,    73,    13,    20,    29,    30,
      43,   221,   222,   145,   146,    82,   328,   329,    14,    21,
      32,    44,    79,    45,   204,   108,   109,   110,   111,   112,
     113,   154,   193,   240,   285,   286,   287,   284,   289,   283,
     288,   114,   187,   188,   115,   275,   274,   116,   157,   202,
     203,   295,   296,   117,   184,   182,   227,   228,   332,   354,
     333,   118,   185,    15,    22,    34,    83,   207,   123,   124,
      16,    23,    35,    48,   168,   211,   212,   258,   364,   351,
      64,   259,   127,   166,    17,    24,    37,   141
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -264
static const yytype_int16 yypact[] =
{
    -264,   134,  -264,  -264,  -264,  -264,  -264,  -264,  -264,  -264,
    -264,  -264,  -264,  -264,  -264,  -264,  -264,  -264,    35,    99,
     112,   136,   150,   167,   178,  -264,   202,  -264,   204,  -264,
     215,   182,  -264,   159,  -264,   217,   190,  -264,    10,  -264,
     195,  -264,   196,  -264,   197,   186,     8,   113,  -264,   187,
    -264,    32,   156,   222,  -264,   161,  -264,  -264,   188,   191,
     219,   160,   192,  -264,  -264,   201,    83,  -264,  -264,  -264,
    -264,   127,  -264,  -264,    70,  -264,   143,  -264,   198,     7,
    -264,  -264,   135,     2,   226,   230,  -264,  -264,  -264,    23,
     120,   231,   232,   177,  -264,   127,   127,   127,    77,    77,
      24,  -264,    41,    56,   203,   115,   179,  -264,  -264,  -264,
    -264,  -264,  -264,  -264,  -264,  -264,  -264,  -264,  -264,   235,
     210,  -264,   236,    68,  -264,  -264,   199,   151,   208,  -264,
     238,   239,   211,  -264,    91,   104,  -264,  -264,  -264,   244,
    -264,    31,  -264,  -264,  -264,   131,  -264,   213,  -264,   214,
    -264,  -264,    80,   212,    16,   175,   176,   103,  -264,  -264,
    -264,     2,   205,   246,  -264,  -264,   146,  -264,  -264,   220,
     218,  -264,  -264,   127,    59,  -264,   127,    64,  -264,   224,
      24,  -264,    11,  -264,    11,   151,   181,    77,   225,    15,
     183,  -264,   185,   223,   221,   227,   228,   229,   233,   234,
     237,  -264,    78,  -264,     7,  -264,   254,  -264,  -264,   255,
    -264,  -264,    58,   259,  -264,   262,  -264,   127,   263,  -264,
     127,    77,   241,  -264,   242,   245,   264,     1,  -264,     9,
     157,  -264,  -264,  -264,    77,   240,   243,   116,  -264,  -264,
      19,  -264,  -264,  -264,    19,   247,   248,   250,   251,  -264,
    -264,   103,  -264,  -264,  -264,  -264,    63,  -264,  -264,   249,
     252,  -264,   265,  -264,   267,  -264,    77,   253,   256,   257,
    -264,  -264,  -264,  -264,    77,    77,  -264,   258,   260,   184,
     189,   193,   194,    77,    77,   266,  -264,  -264,    77,    77,
     266,  -264,  -264,  -264,  -264,    12,   151,  -264,  -264,   268,
    -264,  -264,  -264,  -264,  -264,  -264,   269,  -264,  -264,   261,
     270,   271,   272,   273,   274,   275,   276,   277,   278,  -264,
    -264,    19,  -264,  -264,  -264,  -264,  -264,   284,   164,  -264,
     165,   279,   103,   103,  -264,  -264,  -264,   280,   282,   283,
     285,   286,   287,   288,   289,  -264,  -264,    25,  -264,  -264,
    -264,   103,   295,   295,   103,   290,   297,   298,   299,   300,
     301,   302,   303,  -264,   103,  -264,   295,  -264,  -264,  -264,
    -264,  -264,  -264,  -264,  -264,    94,  -264
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -264,  -264,  -264,  -264,  -264,  -264,  -264,  -264,  -264,  -264,
    -264,  -264,   -98,  -264,  -264,  -264,  -264,  -264,  -264,  -264,
    -264,  -264,  -264,  -264,    95,  -264,  -264,   -70,  -264,  -264,
    -264,  -264,  -264,  -264,  -264,    74,  -264,  -264,  -264,  -264,
    -264,  -264,  -264,  -264,    46,   -42,   137,  -264,  -264,  -264,
    -264,  -264,  -264,  -264,  -264,  -264,  -264,  -264,  -264,  -263,
    -246,  -264,  -264,  -264,  -264,  -264,   108,   -23,  -264,  -264,
    -264,  -264,  -264,  -264,  -264,  -264,  -264,  -264,  -264,   132,
    -264,  -264,  -264,  -264,  -264,  -264,    84,  -264,  -264,  -264,
     281,   292,  -264,  -183,  -264,  -264,  -264,   -48
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -172
static const yytype_int16 yytable[] =
{
     140,   142,   230,    74,    77,   297,   224,   121,   101,    56,
     102,    50,   103,   324,   224,   325,   224,   326,   235,   190,
     236,   225,   190,    92,   104,   143,   128,   144,   325,   225,
     326,   225,   226,    67,    94,    68,    69,    70,   -14,    51,
     226,   105,   226,   327,   122,   270,   106,   137,   138,   139,
     107,    57,   191,   272,   237,   192,   327,   129,   192,   -58,
     -58,    58,   216,    59,    97,    71,    58,   219,    59,   352,
     353,    60,    61,    94,    62,   147,    60,    61,    63,    62,
      68,    69,    70,    63,   148,    95,   174,   177,    90,   233,
     149,   366,   217,   257,   172,    69,    70,   220,   298,   150,
      96,   375,   -24,    97,   161,   365,   199,   175,    69,    70,
      71,  -127,   162,   330,   251,   -49,    58,    91,    59,   186,
     200,   201,   252,   265,   173,   215,    60,    61,   218,    62,
     251,    69,    70,    63,     2,     3,   276,   176,   376,    31,
       4,     5,     6,     7,     8,     9,    10,   279,   280,   281,
     152,   130,   164,    33,   131,   153,   165,    75,   282,    76,
      69,    70,    80,    58,    81,    59,   179,   180,   303,   262,
    -171,   119,   264,   120,    98,    99,   307,   308,   195,   197,
     196,   198,   209,    36,   210,   319,   320,   311,    46,   312,
     322,   323,   313,   209,   314,   273,   315,   317,   316,   318,
     347,   209,   348,   349,   271,    38,   271,    40,   134,   135,
     155,   156,   231,   232,   238,   239,   241,   242,    42,   -75,
      47,    49,    86,    55,    52,    53,    54,    78,    66,    88,
      89,   125,   100,   126,    84,   133,   132,    85,   158,   159,
     151,   160,   167,   169,   170,   163,   171,   178,   181,   183,
     206,   208,   189,   214,   213,   -53,   234,   244,   243,   254,
     255,   245,   246,   247,   260,   261,   263,   248,   301,   269,
     302,   249,   266,   267,   250,   223,   268,   363,   253,   345,
     299,   277,   291,   292,   278,   293,   294,   300,   306,   346,
     290,   194,   229,   205,   304,   256,   335,   305,     0,   309,
       0,   310,   321,     0,     0,   336,     0,     0,     0,   331,
     334,     0,   337,   338,   339,   340,   341,   342,   343,   344,
       0,   355,   350,   356,   357,   367,   358,   359,   360,   361,
     362,   251,   368,   369,   370,   371,   372,   373,   374,    65,
       0,     0,    87
};

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-264)))

#define yytable_value_is_error(Yytable_value) \
  YYID (0)

static const yytype_int16 yycheck[] =
{
      98,    99,   185,    51,    52,   251,     5,     5,     1,     1,
       3,     1,     5,     1,     5,     3,     5,     5,     3,     3,
       5,    20,     3,    71,    17,     1,     3,     3,     3,    20,
       5,    20,    31,     1,     3,     3,     4,     5,     3,    29,
      31,    34,    31,    31,    42,    44,    39,    95,    96,    97,
      43,    43,    36,    44,    39,    39,    31,    34,    39,    35,
      36,     3,     3,     5,    33,    33,     3,     3,     5,   332,
     333,    13,    14,     3,    16,    34,    13,    14,    20,    16,
       3,     4,     5,    20,    43,    15,   134,   135,     5,   187,
      34,   354,    33,    35,     3,     4,     5,    33,    35,    43,
      30,   364,     3,    33,    36,   351,     3,     3,     4,     5,
      33,    31,    44,   296,    36,     3,     3,    34,     5,    39,
      17,    18,    44,   221,    33,   173,    13,    14,   176,    16,
      36,     4,     5,    20,     0,     1,   234,    33,    44,     3,
       6,     7,     8,     9,    10,    11,    12,    31,    32,    33,
      35,    31,     1,     3,    34,    40,     5,     1,    42,     3,
       4,     5,     1,     3,     3,     5,    35,    36,   266,   217,
       3,    36,   220,    38,    31,    32,   274,   275,     3,     3,
       5,     5,    36,     5,    38,   283,   284,     3,    29,     5,
     288,   289,     3,    36,     5,    38,     3,     3,     5,     5,
      36,    36,    38,    38,   227,     3,   229,     3,    31,    32,
      31,    32,    31,    32,    31,    32,    31,    32,     3,    37,
       3,    31,     3,    37,    29,    29,    29,     5,    41,    37,
      29,     5,    34,     3,    46,     3,     5,    46,     3,    29,
      37,     5,    34,     5,     5,    46,    35,     3,    35,    35,
      45,     5,    40,    35,    34,    31,    31,    36,    35,     5,
       5,    34,    34,    34,     5,     3,     3,    34,     3,     5,
       3,    37,    31,    31,    37,   180,    31,   347,   204,   321,
      31,    41,    35,    35,    41,    35,    35,    35,    31,     5,
     244,   154,   184,   161,    41,   211,    35,    41,    -1,    41,
      -1,    41,    36,    -1,    -1,    35,    -1,    -1,    -1,    41,
      41,    -1,    41,    41,    41,    41,    41,    41,    41,    41,
      -1,    41,    43,    41,    41,    35,    41,    41,    41,    41,
      41,    36,    35,    35,    35,    35,    35,    35,    35,    47,
      -1,    -1,    61
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    48,     0,     1,     6,     7,     8,     9,    10,    11,
      12,    49,    54,    63,    75,   120,   127,   141,    50,    55,
      64,    76,   121,   128,   142,    51,    52,    56,    57,    65,
      66,     3,    77,     3,   122,   129,     5,   143,     3,    53,
       3,    58,     3,    67,    78,    80,    29,     3,   130,    31,
       1,    29,    29,    29,    29,    37,     1,    43,     3,     5,
      13,    14,    16,    20,   137,   138,    41,     1,     3,     4,
       5,    33,    59,    62,   144,     1,     3,   144,     5,    79,
       1,     3,    72,   123,    46,    46,     3,   137,    37,    29,
       5,    34,   144,    60,     3,    15,    30,    33,    31,    32,
      34,     1,     3,     5,    17,    34,    39,    43,    82,    83,
      84,    85,    86,    87,    98,   101,   104,   110,   118,    36,
      38,     5,    42,   125,   126,     5,     3,   139,     3,    34,
      31,    34,     5,     3,    31,    32,    61,   144,   144,   144,
      59,   144,    59,     1,     3,    70,    71,    34,    43,    34,
      43,    37,    35,    40,    88,    31,    32,   105,     3,    29,
       5,    36,    44,    46,     1,     5,   140,    34,   131,     5,
       5,    35,     3,    33,   144,     3,    33,   144,     3,    35,
      36,    35,   112,    35,   111,   119,    39,    99,   100,    40,
       3,    36,    39,    89,    93,     3,     5,     3,     5,     3,
      17,    18,   106,   107,    81,   126,    45,   124,     5,    36,
      38,   132,   133,    34,    35,   144,     3,    33,   144,     3,
      33,    68,    69,    71,     5,    20,    31,   113,   114,   113,
     140,    31,    32,    59,    31,     3,     5,    39,    31,    32,
      90,    31,    32,    35,    36,    34,    34,    34,    34,    37,
      37,    36,    44,    82,     5,     5,   133,    35,   134,   138,
       5,     3,   144,     3,   144,    59,    31,    31,    31,     5,
      44,   114,    44,    38,   103,   102,    59,    41,    41,    31,
      32,    33,    42,    96,    94,    91,    92,    93,    97,    95,
      91,    35,    35,    35,    35,   108,   109,   107,    35,    31,
      35,     3,     3,    59,    41,    41,    31,    59,    59,    41,
      41,     3,     5,     3,     5,     3,     5,     3,     5,    59,
      59,    36,    59,    59,     1,     3,     5,    31,    73,    74,
     140,    41,   115,   117,    41,    35,    35,    41,    41,    41,
      41,    41,    41,    41,    41,    92,     5,    36,    38,    38,
      43,   136,   106,   106,   116,    41,    41,    41,    41,    41,
      41,    41,    41,    74,   135,   107,   106,    35,    35,    35,
      35,    35,    35,    35,    35,   106,    44
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  However,
   YYFAIL appears to be in use.  Nevertheless, it is formally deprecated
   in Bison 2.4.2's NEWS entry, where a plan to phase it out is
   discussed.  */

#define YYFAIL		goto yyerrlab
#if defined YYFAIL
  /* This is here to suppress warnings from the GCC cpp's
     -Wunused-macros.  Normally we don't worry about that warning, but
     some users do, and we want to make it easy for users to remove
     YYFAIL uses, which will produce warnings from Bison 2.5.  */
#endif

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
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
      yyerror (&yylloc, box, YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))

/* Error token number */
#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (YYID (N))                                                     \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (YYID (0))
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

__attribute__((__unused__))
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static unsigned
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
#else
static unsigned
yy_location_print_ (yyo, yylocp)
    FILE *yyo;
    YYLTYPE const * const yylocp;
#endif
{
  unsigned res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += fprintf (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += fprintf (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += fprintf (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += fprintf (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += fprintf (yyo, "-%d", end_col);
    }
  return res;
 }

#  define YY_LOCATION_PRINT(File, Loc)          \
  yy_location_print_ (File, &(Loc))

# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */
#ifdef YYLEX_PARAM
# define YYLEX yylex (&yylval, &yylloc, YYLEX_PARAM)
#else
# define YYLEX yylex (&yylval, &yylloc, scanner)
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value, Location, box); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, mutabor_box_type * box)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp, box)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    YYLTYPE const * const yylocationp;
    mutabor_box_type * box;
#endif
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
  YYUSE (yylocationp);
  YYUSE (box);
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, mutabor_box_type * box)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep, yylocationp, box)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    YYLTYPE const * const yylocationp;
    mutabor_box_type * box;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  YY_LOCATION_PRINT (yyoutput, *yylocationp);
  YYFPRINTF (yyoutput, ": ");
  yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp, box);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, YYLTYPE *yylsp, int yyrule, mutabor_box_type * box)
#else
static void
yy_reduce_print (yyvsp, yylsp, yyrule, box)
    YYSTYPE *yyvsp;
    YYLTYPE *yylsp;
    int yyrule;
    mutabor_box_type * box;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       , &(yylsp[(yyi + 1) - (yynrhs)])		       , box);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, yylsp, Rule, box); \
} while (YYID (0))

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
#ifndef	YYINITDEPTH
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
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
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
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
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
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
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
	    /* Fall through.  */
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

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
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
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULL, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULL;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - Assume YYFAIL is not used.  It's too flawed to consider.  See
       <http://lists.gnu.org/archive/html/bison-patches/2009-12/msg00024.html>
       for details.  YYERROR is fine as it does not invoke this
       function.
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
      int yyn = yypact[*yyssp];
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
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULL, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
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
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
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
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp, mutabor_box_type * box)
#else
static void
yydestruct (yymsg, yytype, yyvaluep, yylocationp, box)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
    YYLTYPE *yylocationp;
    mutabor_box_type * box;
#endif
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);
  YYUSE (box);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YYUSE (yytype);
}




/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (mutabor_box_type * box)
#else
int
yyparse (box)
    mutabor_box_type * box;
#endif
#endif
{
/* The lookahead symbol.  */
int yychar;


#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
/* Default value used for initialization, for pacifying older GCCs
   or non-GCC compilers.  */
static YYSTYPE yyval_default;
# define YY_INITIAL_VALUE(Value) = Value
#endif
static YYLTYPE yyloc_default
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval YY_INITIAL_VALUE(yyval_default);

/* Location data for the lookahead symbol.  */
YYLTYPE yylloc = yyloc_default;


    /* Number of syntax errors so far.  */
    int yynerrs;

    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.
       `yyls': related to locations.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    /* The location stack.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls;
    YYLTYPE *yylsp;

    /* The locations where the error started and ended.  */
    YYLTYPE yyerror_range[3];

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yylsp = yyls = yylsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  yylsp[0] = yylloc;
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;
	YYLTYPE *yyls1 = yyls;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yyls1, yysize * sizeof (*yylsp),
		    &yystacksize);

	yyls = yyls1;
	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
	YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

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
      yychar = YYLEX;
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

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END
  *++yylsp = yylloc;
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
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];

  /* Default location.  */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 10:
/* Line 1787 of yacc.c  */
#line 162 "../../../mutabor-git/src/kernel/mut.yy"
    {  mutabor_error_message(box,
					       false,
					       _("Syntax error in line %d."),
					       FEHLERZEILE); }
    break;

  case 14:
/* Line 1787 of yacc.c  */
#line 177 "../../../mutabor-git/src/kernel/mut.yy"
    { init_komplex_ton_list (box); }
    break;

  case 16:
/* Line 1787 of yacc.c  */
#line 182 "../../../mutabor-git/src/kernel/mut.yy"
    { if ( fabs((yyvsp[(5) - (5)].f_value)) > 0.001 )
				    get_new_intervall (box, (yyvsp[(1) - (5)].identifier), (yyvsp[(3) - (5)].f_value) / (yyvsp[(5) - (5)].f_value));
                      else
			      mutabor_error_message (box,false,
					   _("Bad interval value in %s"),
					   ((yyvsp[(1) - (5)].identifier)) ); }
    break;

  case 17:
/* Line 1787 of yacc.c  */
#line 190 "../../../mutabor-git/src/kernel/mut.yy"
    { if ( fabs ((yyvsp[(3) - (5)].f_value)) > 0.001 )
				    get_new_intervall (box, (yyvsp[(1) - (5)].identifier), pow ((yyvsp[(5) - (5)].f_value), 1 / (yyvsp[(3) - (5)].f_value)));
                      else
			      mutabor_error_message (box,false,
						     _("Bad interval value in %s"),
						     ((yyvsp[(1) - (5)].identifier))); }
    break;

  case 18:
/* Line 1787 of yacc.c  */
#line 201 "../../../mutabor-git/src/kernel/mut.yy"
    { get_new_intervall_komplex (box,(yyvsp[(1) - (3)].identifier)); }
    break;

  case 19:
/* Line 1787 of yacc.c  */
#line 202 "../../../mutabor-git/src/kernel/mut.yy"
    { 
		mutabor_error_message(box,
				      false,
				      _("Bad interval declaration of intervall %s in line %d."),
				      ((yyvsp[(1) - (3)].identifier)),
				      FEHLERZEILE); 
	  }
    break;

  case 20:
/* Line 1787 of yacc.c  */
#line 209 "../../../mutabor-git/src/kernel/mut.yy"
    { 
		mutabor_error_message(box,
				      false,
				      _("Wrong character. Expecting %s in line %d."),
				      mutT("="),FEHLERZEILE); 
	  }
    break;

  case 24:
/* Line 1787 of yacc.c  */
#line 226 "../../../mutabor-git/src/kernel/mut.yy"
    { init_komplex_ton_list (box); }
    break;

  case 26:
/* Line 1787 of yacc.c  */
#line 231 "../../../mutabor-git/src/kernel/mut.yy"
    { get_new_ton_absolut (box, (yyvsp[(1) - (3)].identifier), (yyvsp[(3) - (3)].f_value)); }
    break;

  case 27:
/* Line 1787 of yacc.c  */
#line 235 "../../../mutabor-git/src/kernel/mut.yy"
    { get_new_ton_komplex_negative (box, (yyvsp[(1) - (5)].identifier), (yyvsp[(3) - (5)].identifier)); }
    break;

  case 28:
/* Line 1787 of yacc.c  */
#line 239 "../../../mutabor-git/src/kernel/mut.yy"
    { get_new_ton_komplex_positive (box, (yyvsp[(1) - (3)].identifier), (yyvsp[(3) - (3)].identifier)); }
    break;

  case 29:
/* Line 1787 of yacc.c  */
#line 243 "../../../mutabor-git/src/kernel/mut.yy"
    { get_new_ton_komplex_positive (box, (yyvsp[(1) - (5)].identifier), (yyvsp[(3) - (5)].identifier)); }
    break;

  case 30:
/* Line 1787 of yacc.c  */
#line 245 "../../../mutabor-git/src/kernel/mut.yy"
    { 
	      mutabor_error_message(box,
				    false,
				    _("Bad tone declaration of tone %s in line %d."),
				    ((yyvsp[(1) - (3)].identifier)),
				    FEHLERZEILE); 
	}
    break;

  case 34:
/* Line 1787 of yacc.c  */
#line 265 "../../../mutabor-git/src/kernel/mut.yy"
    { get_new_faktor_anteil ( box, (double) 1, (yyvsp[(2) - (2)].identifier)); }
    break;

  case 35:
/* Line 1787 of yacc.c  */
#line 268 "../../../mutabor-git/src/kernel/mut.yy"
    { get_new_faktor_anteil ( box,  (double) -1, (yyvsp[(2) - (2)].identifier)); }
    break;

  case 36:
/* Line 1787 of yacc.c  */
#line 271 "../../../mutabor-git/src/kernel/mut.yy"
    { get_new_faktor_anteil (box, (yyvsp[(2) - (3)].f_value), (yyvsp[(3) - (3)].identifier)); }
    break;

  case 37:
/* Line 1787 of yacc.c  */
#line 274 "../../../mutabor-git/src/kernel/mut.yy"
    { get_new_faktor_anteil (box, -((yyvsp[(2) - (3)].f_value)), (yyvsp[(3) - (3)].identifier)); }
    break;

  case 38:
/* Line 1787 of yacc.c  */
#line 277 "../../../mutabor-git/src/kernel/mut.yy"
    { if ( fabs((yyvsp[(3) - (4)].f_value)) > 0.001 )
				   get_new_faktor_anteil (box, (double) 1 / ((yyvsp[(3) - (4)].f_value)), (yyvsp[(4) - (4)].identifier));
			   else
				   mutabor_error_message(box,
							 false,
							 _("Division by (nearly) 0 in line %d."),
							 FEHLERZEILE);  
		   }
    break;

  case 39:
/* Line 1787 of yacc.c  */
#line 287 "../../../mutabor-git/src/kernel/mut.yy"
    { if ( fabs((yyvsp[(3) - (4)].f_value)) > 0.001 )
				   get_new_faktor_anteil (box, (double) -1 / ((yyvsp[(3) - (4)].f_value)), (yyvsp[(4) - (4)].identifier));
                     else
				   mutabor_error_message(box,
							 false,
							 _("Division by (nearly) 0 in line %d."),
							 FEHLERZEILE);  
		   }
    break;

  case 40:
/* Line 1787 of yacc.c  */
#line 297 "../../../mutabor-git/src/kernel/mut.yy"
    { if ( fabs((yyvsp[(4) - (5)].f_value)) > 0.001 )
				   get_new_faktor_anteil (box, ((yyvsp[(2) - (5)].f_value)) / ((yyvsp[(4) - (5)].f_value)), (yyvsp[(5) - (5)].identifier));
                     else
			     mutabor_error_message(box,
						   false,
						   _("Division by (nearly) 0 in line %d."),
						   FEHLERZEILE);  
		   }
    break;

  case 41:
/* Line 1787 of yacc.c  */
#line 307 "../../../mutabor-git/src/kernel/mut.yy"
    { if ( fabs((yyvsp[(4) - (5)].f_value)) > 0.001 )
				   get_new_faktor_anteil (box, -((yyvsp[(2) - (5)].f_value)) / ((yyvsp[(4) - (5)].f_value)), (yyvsp[(5) - (5)].identifier));
                     else
			     mutabor_error_message(box,
						   false,
						   _("Division by (nearly) 0 in line %d."),
						   FEHLERZEILE);  
		   }
    break;

  case 42:
/* Line 1787 of yacc.c  */
#line 332 "../../../mutabor-git/src/kernel/mut.yy"
    { get_new_faktor_anteil (box, (double) 1.0 , (yyvsp[(1) - (1)].identifier)); }
    break;

  case 43:
/* Line 1787 of yacc.c  */
#line 340 "../../../mutabor-git/src/kernel/mut.yy"
    { get_new_faktor_anteil (box, (yyvsp[(1) - (2)].f_value), (yyvsp[(2) - (2)].identifier)); }
    break;

  case 44:
/* Line 1787 of yacc.c  */
#line 343 "../../../mutabor-git/src/kernel/mut.yy"
    { if ( fabs((yyvsp[(2) - (3)].f_value)) > 0.001 )
				   get_new_faktor_anteil (box, (double) 1 / ((yyvsp[(2) - (3)].f_value)), (yyvsp[(3) - (3)].identifier));
                     else
			     mutabor_error_message(box,
						   false,
						   _("Division by (nearly) 0 in line %d."),
						   FEHLERZEILE);  
		   }
    break;

  case 45:
/* Line 1787 of yacc.c  */
#line 353 "../../../mutabor-git/src/kernel/mut.yy"
    { if ( fabs((yyvsp[(3) - (4)].f_value)) > 0.001 )
				   get_new_faktor_anteil (box, ((yyvsp[(1) - (4)].f_value)) / ((yyvsp[(3) - (4)].f_value)), (yyvsp[(4) - (4)].identifier));
                     else
			     mutabor_error_message(box,
						   false,
						   _("Division by (nearly) 0 in line %d."),
						   FEHLERZEILE);  
		   }
    break;

  case 49:
/* Line 1787 of yacc.c  */
#line 390 "../../../mutabor-git/src/kernel/mut.yy"
    { init_ton_liste (box); }
    break;

  case 51:
/* Line 1787 of yacc.c  */
#line 395 "../../../mutabor-git/src/kernel/mut.yy"
    { init_komplex_ton_list (box); }
    break;

  case 52:
/* Line 1787 of yacc.c  */
#line 397 "../../../mutabor-git/src/kernel/mut.yy"
    { get_new_tonsystem (box, (yyvsp[(1) - (8)].identifier), (yyvsp[(3) - (8)].integer)); }
    break;

  case 53:
/* Line 1787 of yacc.c  */
#line 399 "../../../mutabor-git/src/kernel/mut.yy"
    { init_komplex_ton_list (box); }
    break;

  case 54:
/* Line 1787 of yacc.c  */
#line 401 "../../../mutabor-git/src/kernel/mut.yy"
    { get_new_tonsystem_negative (box, (yyvsp[(1) - (9)].identifier), (yyvsp[(3) - (9)].integer)); }
    break;

  case 57:
/* Line 1787 of yacc.c  */
#line 407 "../../../mutabor-git/src/kernel/mut.yy"
    { get_new_ton_in_tonsystem (box, (yyvsp[(1) - (1)].identifier)); }
    break;

  case 58:
/* Line 1787 of yacc.c  */
#line 408 "../../../mutabor-git/src/kernel/mut.yy"
    { get_new_ton_in_tonsystem (box, NULL); }
    break;

  case 59:
/* Line 1787 of yacc.c  */
#line 409 "../../../mutabor-git/src/kernel/mut.yy"
    { 
		mutabor_error_message(box,
				      false,
				      _("Bad tonesystem declaration in line %d."),		      
				      FEHLERZEILE);
	  }
    break;

  case 60:
/* Line 1787 of yacc.c  */
#line 418 "../../../mutabor-git/src/kernel/mut.yy"
    { get_new_name_in_parameterlist (box, (yyvsp[(1) - (1)].identifier)); }
    break;

  case 61:
/* Line 1787 of yacc.c  */
#line 420 "../../../mutabor-git/src/kernel/mut.yy"
    { get_new_name_in_parameterlist (box, (yyvsp[(3) - (3)].identifier)); }
    break;

  case 62:
/* Line 1787 of yacc.c  */
#line 421 "../../../mutabor-git/src/kernel/mut.yy"
    {
		mutabor_error_message(box,
				      false,
				      _("Bad parameter list in call to %s in line %d"),
				      FEHLERZEILE); 
	  }
    break;

  case 63:
/* Line 1787 of yacc.c  */
#line 431 "../../../mutabor-git/src/kernel/mut.yy"
    {}
    break;

  case 64:
/* Line 1787 of yacc.c  */
#line 432 "../../../mutabor-git/src/kernel/mut.yy"
    {}
    break;

  case 65:
/* Line 1787 of yacc.c  */
#line 433 "../../../mutabor-git/src/kernel/mut.yy"
    { 
		mutabor_error_message(box,
				      false,
				      _("Bad parameter list in call to %s in line %d"),
				      FEHLERZEILE); 
	  }
    break;

  case 66:
/* Line 1787 of yacc.c  */
#line 443 "../../../mutabor-git/src/kernel/mut.yy"
    { get_new_name_in_argument_list (box, (yyvsp[(1) - (1)].identifier)) ;  }
    break;

  case 67:
/* Line 1787 of yacc.c  */
#line 444 "../../../mutabor-git/src/kernel/mut.yy"
    { get_new_number_in_argument_list (box, (yyvsp[(1) - (1)].integer)) ;  }
    break;

  case 68:
/* Line 1787 of yacc.c  */
#line 445 "../../../mutabor-git/src/kernel/mut.yy"
    { get_new_number_in_argument_list (box, -((yyvsp[(2) - (2)].integer))); }
    break;

  case 72:
/* Line 1787 of yacc.c  */
#line 460 "../../../mutabor-git/src/kernel/mut.yy"
    { init_umstimmung (box, (yyvsp[(1) - (1)].identifier));
                      init_parameter_liste (box); }
    break;

  case 73:
/* Line 1787 of yacc.c  */
#line 462 "../../../mutabor-git/src/kernel/mut.yy"
    { eintrage_parameterliste_in_umstimmung (box); }
    break;

  case 74:
/* Line 1787 of yacc.c  */
#line 464 "../../../mutabor-git/src/kernel/mut.yy"
    { get_new_umstimmung (box); }
    break;

  case 75:
/* Line 1787 of yacc.c  */
#line 467 "../../../mutabor-git/src/kernel/mut.yy"
    { init_umstimmung (box,(yyvsp[(1) - (1)].identifier));
		init_parameter_liste (box); }
    break;

  case 76:
/* Line 1787 of yacc.c  */
#line 470 "../../../mutabor-git/src/kernel/mut.yy"
    { eintrage_parameterliste_in_umstimmung (box); }
    break;

  case 77:
/* Line 1787 of yacc.c  */
#line 472 "../../../mutabor-git/src/kernel/mut.yy"
    { get_new_umstimmung (box); }
    break;

  case 78:
/* Line 1787 of yacc.c  */
#line 476 "../../../mutabor-git/src/kernel/mut.yy"
    {}
    break;

  case 79:
/* Line 1787 of yacc.c  */
#line 477 "../../../mutabor-git/src/kernel/mut.yy"
    {}
    break;

  case 80:
/* Line 1787 of yacc.c  */
#line 478 "../../../mutabor-git/src/kernel/mut.yy"
    {}
    break;

  case 81:
/* Line 1787 of yacc.c  */
#line 479 "../../../mutabor-git/src/kernel/mut.yy"
    {}
    break;

  case 82:
/* Line 1787 of yacc.c  */
#line 480 "../../../mutabor-git/src/kernel/mut.yy"
    {}
    break;

  case 83:
/* Line 1787 of yacc.c  */
#line 481 "../../../mutabor-git/src/kernel/mut.yy"
    {}
    break;

  case 84:
/* Line 1787 of yacc.c  */
#line 482 "../../../mutabor-git/src/kernel/mut.yy"
    {}
    break;

  case 85:
/* Line 1787 of yacc.c  */
#line 483 "../../../mutabor-git/src/kernel/mut.yy"
    {}
    break;

  case 86:
/* Line 1787 of yacc.c  */
#line 484 "../../../mutabor-git/src/kernel/mut.yy"
    {}
    break;

  case 87:
/* Line 1787 of yacc.c  */
#line 485 "../../../mutabor-git/src/kernel/mut.yy"
    {}
    break;

  case 88:
/* Line 1787 of yacc.c  */
#line 486 "../../../mutabor-git/src/kernel/mut.yy"
    {
		mutabor_error_message(box,
				      false,
				      _("Bad retuning in line %d."),
				      FEHLERZEILE);
	  }
    break;

  case 89:
/* Line 1787 of yacc.c  */
#line 497 "../../../mutabor-git/src/kernel/mut.yy"
    { get_umstimmung_taste_abs (box, zahl, (yyvsp[(1) - (3)].integer), NULL); }
    break;

  case 90:
/* Line 1787 of yacc.c  */
#line 499 "../../../mutabor-git/src/kernel/mut.yy"
    { get_umstimmung_taste_abs (box, parameter, 0.0, (yyvsp[(1) - (3)].identifier)); }
    break;

  case 91:
/* Line 1787 of yacc.c  */
#line 504 "../../../mutabor-git/src/kernel/mut.yy"
    { get_umstimmung_taste_rel (box, zahl, (yyvsp[(3) - (5)].integer), NULL, '+'); }
    break;

  case 92:
/* Line 1787 of yacc.c  */
#line 506 "../../../mutabor-git/src/kernel/mut.yy"
    { get_umstimmung_taste_rel (box, parameter, 0.0, (yyvsp[(3) - (5)].identifier), '+'); }
    break;

  case 93:
/* Line 1787 of yacc.c  */
#line 508 "../../../mutabor-git/src/kernel/mut.yy"
    { get_umstimmung_taste_rel (box, zahl, (yyvsp[(3) - (5)].integer), NULL, '-'); }
    break;

  case 94:
/* Line 1787 of yacc.c  */
#line 510 "../../../mutabor-git/src/kernel/mut.yy"
    { get_umstimmung_taste_rel (box, parameter, 0.0, (yyvsp[(3) - (5)].identifier), '-'); }
    break;

  case 95:
/* Line 1787 of yacc.c  */
#line 515 "../../../mutabor-git/src/kernel/mut.yy"
    { get_umstimmung_breite_abs (box, zahl, (yyvsp[(4) - (7)].integer), NULL); }
    break;

  case 96:
/* Line 1787 of yacc.c  */
#line 517 "../../../mutabor-git/src/kernel/mut.yy"
    { get_umstimmung_breite_abs (box, parameter, 0.0, (yyvsp[(4) - (7)].identifier)); }
    break;

  case 97:
/* Line 1787 of yacc.c  */
#line 522 "../../../mutabor-git/src/kernel/mut.yy"
    { get_umstimmung_breite_rel (box, zahl, (yyvsp[(6) - (9)].integer), NULL, '+'); }
    break;

  case 98:
/* Line 1787 of yacc.c  */
#line 524 "../../../mutabor-git/src/kernel/mut.yy"
    { get_umstimmung_breite_rel (box, parameter, 0.0, (yyvsp[(6) - (9)].identifier), '+'); }
    break;

  case 99:
/* Line 1787 of yacc.c  */
#line 526 "../../../mutabor-git/src/kernel/mut.yy"
    { get_umstimmung_breite_rel (box, zahl, (yyvsp[(6) - (9)].integer), NULL, '-'); }
    break;

  case 100:
/* Line 1787 of yacc.c  */
#line 528 "../../../mutabor-git/src/kernel/mut.yy"
    { get_umstimmung_breite_rel (box, parameter, 0.0, (yyvsp[(6) - (9)].identifier), '-'); }
    break;

  case 101:
/* Line 1787 of yacc.c  */
#line 530 "../../../mutabor-git/src/kernel/mut.yy"
    { get_umstimmung_breite_rel (box, zahl, (yyvsp[(6) - (9)].integer), NULL, '*'); }
    break;

  case 102:
/* Line 1787 of yacc.c  */
#line 532 "../../../mutabor-git/src/kernel/mut.yy"
    { get_umstimmung_breite_rel (box, parameter, 0.0, (yyvsp[(6) - (9)].identifier), '*'); }
    break;

  case 103:
/* Line 1787 of yacc.c  */
#line 534 "../../../mutabor-git/src/kernel/mut.yy"
    { get_umstimmung_breite_rel (box, zahl, (yyvsp[(6) - (9)].integer), NULL, '/'); }
    break;

  case 104:
/* Line 1787 of yacc.c  */
#line 536 "../../../mutabor-git/src/kernel/mut.yy"
    { get_umstimmung_breite_rel (box, parameter, 0.0, (yyvsp[(6) - (9)].identifier), '/'); }
    break;

  case 105:
/* Line 1787 of yacc.c  */
#line 541 "../../../mutabor-git/src/kernel/mut.yy"
    { init_umstimm_expression_list (box); }
    break;

  case 106:
/* Line 1787 of yacc.c  */
#line 543 "../../../mutabor-git/src/kernel/mut.yy"
    { get_umstimmung_tonhoehe_veraendert (box); }
    break;

  case 107:
/* Line 1787 of yacc.c  */
#line 550 "../../../mutabor-git/src/kernel/mut.yy"
    {}
    break;

  case 108:
/* Line 1787 of yacc.c  */
#line 551 "../../../mutabor-git/src/kernel/mut.yy"
    {}
    break;

  case 109:
/* Line 1787 of yacc.c  */
#line 553 "../../../mutabor-git/src/kernel/mut.yy"
    { init_komplex_ton_list(box);
		  get_new_umstimm_expression (box,NULL);
                   }
    break;

  case 110:
/* Line 1787 of yacc.c  */
#line 556 "../../../mutabor-git/src/kernel/mut.yy"
    {}
    break;

  case 111:
/* Line 1787 of yacc.c  */
#line 560 "../../../mutabor-git/src/kernel/mut.yy"
    {}
    break;

  case 112:
/* Line 1787 of yacc.c  */
#line 561 "../../../mutabor-git/src/kernel/mut.yy"
    {}
    break;

  case 113:
/* Line 1787 of yacc.c  */
#line 566 "../../../mutabor-git/src/kernel/mut.yy"
    { init_komplex_ton_list(box);
		  get_new_umstimm_expression (box, NULL);
                   }
    break;

  case 115:
/* Line 1787 of yacc.c  */
#line 574 "../../../mutabor-git/src/kernel/mut.yy"
    { get_new_umstimm_expression (box,(yyvsp[(1) - (1)].identifier)); }
    break;

  case 116:
/* Line 1787 of yacc.c  */
#line 575 "../../../mutabor-git/src/kernel/mut.yy"
    { get_new_umstimm_expression (box, "@"); }
    break;

  case 117:
/* Line 1787 of yacc.c  */
#line 577 "../../../mutabor-git/src/kernel/mut.yy"
    { init_komplex_ton_list (box); }
    break;

  case 118:
/* Line 1787 of yacc.c  */
#line 579 "../../../mutabor-git/src/kernel/mut.yy"
    { get_new_umstimm_expression_positive (box, (yyvsp[(1) - (4)].identifier)); }
    break;

  case 119:
/* Line 1787 of yacc.c  */
#line 580 "../../../mutabor-git/src/kernel/mut.yy"
    { init_komplex_ton_list (box); }
    break;

  case 120:
/* Line 1787 of yacc.c  */
#line 582 "../../../mutabor-git/src/kernel/mut.yy"
    { get_new_umstimm_expression_positive (box, "@" ); }
    break;

  case 121:
/* Line 1787 of yacc.c  */
#line 583 "../../../mutabor-git/src/kernel/mut.yy"
    { init_komplex_ton_list (box); }
    break;

  case 122:
/* Line 1787 of yacc.c  */
#line 585 "../../../mutabor-git/src/kernel/mut.yy"
    { get_new_umstimm_expression_negative (box,(yyvsp[(1) - (4)].identifier)); }
    break;

  case 123:
/* Line 1787 of yacc.c  */
#line 586 "../../../mutabor-git/src/kernel/mut.yy"
    { init_komplex_ton_list (box); }
    break;

  case 124:
/* Line 1787 of yacc.c  */
#line 588 "../../../mutabor-git/src/kernel/mut.yy"
    { get_new_umstimm_expression_negative (box, "@" ); }
    break;

  case 125:
/* Line 1787 of yacc.c  */
#line 593 "../../../mutabor-git/src/kernel/mut.yy"
    { init_komplex_ton_list (box); }
    break;

  case 126:
/* Line 1787 of yacc.c  */
#line 595 "../../../mutabor-git/src/kernel/mut.yy"
    { get_umstimmung_wiederholung_abs (box); }
    break;

  case 127:
/* Line 1787 of yacc.c  */
#line 596 "../../../mutabor-git/src/kernel/mut.yy"
    { init_komplex_ton_list (box); }
    break;

  case 128:
/* Line 1787 of yacc.c  */
#line 598 "../../../mutabor-git/src/kernel/mut.yy"
    { get_umstimmung_wiederholung_abs_negative (box); }
    break;

  case 129:
/* Line 1787 of yacc.c  */
#line 602 "../../../mutabor-git/src/kernel/mut.yy"
    { init_komplex_ton_list (box); }
    break;

  case 130:
/* Line 1787 of yacc.c  */
#line 604 "../../../mutabor-git/src/kernel/mut.yy"
    { get_umstimmung_wiederholung_rel_positive (box); }
    break;

  case 131:
/* Line 1787 of yacc.c  */
#line 605 "../../../mutabor-git/src/kernel/mut.yy"
    { init_komplex_ton_list (box); }
    break;

  case 132:
/* Line 1787 of yacc.c  */
#line 607 "../../../mutabor-git/src/kernel/mut.yy"
    { get_umstimmung_wiederholung_rel_negative (box); }
    break;

  case 133:
/* Line 1787 of yacc.c  */
#line 611 "../../../mutabor-git/src/kernel/mut.yy"
    { init_aktions_liste (box); }
    break;

  case 134:
/* Line 1787 of yacc.c  */
#line 613 "../../../mutabor-git/src/kernel/mut.yy"
    { get_umstimmung_umstimmungs_bund (box); }
    break;

  case 135:
/* Line 1787 of yacc.c  */
#line 617 "../../../mutabor-git/src/kernel/mut.yy"
    {}
    break;

  case 136:
/* Line 1787 of yacc.c  */
#line 618 "../../../mutabor-git/src/kernel/mut.yy"
    {}
    break;

  case 137:
/* Line 1787 of yacc.c  */
#line 622 "../../../mutabor-git/src/kernel/mut.yy"
    { init_argument_liste (box); 
		  get_new_aktion_aufruf_element (box,(yyvsp[(1) - (1)].identifier)); }
    break;

  case 138:
/* Line 1787 of yacc.c  */
#line 624 "../../../mutabor-git/src/kernel/mut.yy"
    { init_argument_liste (box); }
    break;

  case 139:
/* Line 1787 of yacc.c  */
#line 626 "../../../mutabor-git/src/kernel/mut.yy"
    { get_new_aktion_aufruf_element (box,(yyvsp[(1) - (5)].identifier)); }
    break;

  case 140:
/* Line 1787 of yacc.c  */
#line 628 "../../../mutabor-git/src/kernel/mut.yy"
    { init_integersequenz (box);}
    break;

  case 141:
/* Line 1787 of yacc.c  */
#line 630 "../../../mutabor-git/src/kernel/mut.yy"
    { get_new_aktion_midi_out_element (box); }
    break;

  case 142:
/* Line 1787 of yacc.c  */
#line 631 "../../../mutabor-git/src/kernel/mut.yy"
    { get_new_aktion_harmony_analysis(box); }
    break;

  case 143:
/* Line 1787 of yacc.c  */
#line 635 "../../../mutabor-git/src/kernel/mut.yy"
    { init_umstimmungs_case_liste (box); }
    break;

  case 144:
/* Line 1787 of yacc.c  */
#line 637 "../../../mutabor-git/src/kernel/mut.yy"
    { get_umstimmung_umstimm_case_zahl (box,(yyvsp[(1) - (5)].integer)); }
    break;

  case 145:
/* Line 1787 of yacc.c  */
#line 638 "../../../mutabor-git/src/kernel/mut.yy"
    { init_umstimmungs_case_liste (box); }
    break;

  case 146:
/* Line 1787 of yacc.c  */
#line 640 "../../../mutabor-git/src/kernel/mut.yy"
    { get_umstimmung_umstimm_case_parameter (box,(yyvsp[(1) - (5)].identifier)); }
    break;

  case 147:
/* Line 1787 of yacc.c  */
#line 644 "../../../mutabor-git/src/kernel/mut.yy"
    {}
    break;

  case 148:
/* Line 1787 of yacc.c  */
#line 645 "../../../mutabor-git/src/kernel/mut.yy"
    {}
    break;

  case 149:
/* Line 1787 of yacc.c  */
#line 650 "../../../mutabor-git/src/kernel/mut.yy"
    { init_aktions_liste (box); }
    break;

  case 150:
/* Line 1787 of yacc.c  */
#line 652 "../../../mutabor-git/src/kernel/mut.yy"
    { get_umstimmungs_case_zahl_element (box,(yyvsp[(1) - (5)].integer)); }
    break;

  case 151:
/* Line 1787 of yacc.c  */
#line 654 "../../../mutabor-git/src/kernel/mut.yy"
    { init_aktions_liste (box); }
    break;

  case 152:
/* Line 1787 of yacc.c  */
#line 656 "../../../mutabor-git/src/kernel/mut.yy"
    { get_umstimmungs_case_zahl_element (box,-((yyvsp[(2) - (6)].integer))); }
    break;

  case 153:
/* Line 1787 of yacc.c  */
#line 658 "../../../mutabor-git/src/kernel/mut.yy"
    { init_aktions_liste (box); }
    break;

  case 154:
/* Line 1787 of yacc.c  */
#line 660 "../../../mutabor-git/src/kernel/mut.yy"
    { get_umstimmungs_case_default_element (box); }
    break;

  case 155:
/* Line 1787 of yacc.c  */
#line 665 "../../../mutabor-git/src/kernel/mut.yy"
    { init_integersequenz (box);}
    break;

  case 156:
/* Line 1787 of yacc.c  */
#line 667 "../../../mutabor-git/src/kernel/mut.yy"
    { get_umstimmung_midi_out (box); }
    break;

  case 157:
/* Line 1787 of yacc.c  */
#line 672 "../../../mutabor-git/src/kernel/mut.yy"
    {}
    break;

  case 158:
/* Line 1787 of yacc.c  */
#line 676 "../../../mutabor-git/src/kernel/mut.yy"
    {}
    break;

  case 159:
/* Line 1787 of yacc.c  */
#line 677 "../../../mutabor-git/src/kernel/mut.yy"
    {}
    break;

  case 160:
/* Line 1787 of yacc.c  */
#line 682 "../../../mutabor-git/src/kernel/mut.yy"
    { init_tastenliste (box); }
    break;

  case 161:
/* Line 1787 of yacc.c  */
#line 684 "../../../mutabor-git/src/kernel/mut.yy"
    { get_new_harmonie (box, (yyvsp[(1) - (7)].identifier), (yyvsp[(7) - (7)].integer)); }
    break;

  case 162:
/* Line 1787 of yacc.c  */
#line 686 "../../../mutabor-git/src/kernel/mut.yy"
    { 
		mutabor_error_message(box,
				      false,
				      _("Bad pattern declaration “%s” at line %d"),
				      ((yyvsp[(1) - (3)].identifier)),
				      FEHLERZEILE); 
	  }
    break;

  case 163:
/* Line 1787 of yacc.c  */
#line 696 "../../../mutabor-git/src/kernel/mut.yy"
    { (yyval.integer) = -1; }
    break;

  case 164:
/* Line 1787 of yacc.c  */
#line 697 "../../../mutabor-git/src/kernel/mut.yy"
    { (yyval.integer) = (yyvsp[(2) - (2)].integer); }
    break;

  case 165:
/* Line 1787 of yacc.c  */
#line 701 "../../../mutabor-git/src/kernel/mut.yy"
    {}
    break;

  case 166:
/* Line 1787 of yacc.c  */
#line 702 "../../../mutabor-git/src/kernel/mut.yy"
    {}
    break;

  case 167:
/* Line 1787 of yacc.c  */
#line 706 "../../../mutabor-git/src/kernel/mut.yy"
    { get_new_taste (box, (yyvsp[(1) - (1)].integer), '+'); }
    break;

  case 168:
/* Line 1787 of yacc.c  */
#line 707 "../../../mutabor-git/src/kernel/mut.yy"
    { get_new_taste (box, (yyvsp[(2) - (2)].integer), '*'); }
    break;

  case 169:
/* Line 1787 of yacc.c  */
#line 711 "../../../mutabor-git/src/kernel/mut.yy"
    {}
    break;

  case 170:
/* Line 1787 of yacc.c  */
#line 715 "../../../mutabor-git/src/kernel/mut.yy"
    {}
    break;

  case 171:
/* Line 1787 of yacc.c  */
#line 716 "../../../mutabor-git/src/kernel/mut.yy"
    { init_ausloeser (box);
                         /* f〉 die Anfangsausloesung der Logik */
                       }
    break;

  case 172:
/* Line 1787 of yacc.c  */
#line 719 "../../../mutabor-git/src/kernel/mut.yy"
    {}
    break;

  case 173:
/* Line 1787 of yacc.c  */
#line 724 "../../../mutabor-git/src/kernel/mut.yy"
    { get_new_logik (box, (yyvsp[(1) - (4)].identifier), NULL);
                init_anweisungs_liste (box); }
    break;

  case 174:
/* Line 1787 of yacc.c  */
#line 727 "../../../mutabor-git/src/kernel/mut.yy"
    { vervollstaendige_logik (box); }
    break;

  case 175:
/* Line 1787 of yacc.c  */
#line 729 "../../../mutabor-git/src/kernel/mut.yy"
    { get_new_logik (box, (yyvsp[(1) - (5)].identifier), (yyvsp[(4) - (5)].identifier));
                init_anweisungs_liste (box); }
    break;

  case 176:
/* Line 1787 of yacc.c  */
#line 732 "../../../mutabor-git/src/kernel/mut.yy"
    { vervollstaendige_logik (box); }
    break;

  case 177:
/* Line 1787 of yacc.c  */
#line 736 "../../../mutabor-git/src/kernel/mut.yy"
    {}
    break;

  case 178:
/* Line 1787 of yacc.c  */
#line 737 "../../../mutabor-git/src/kernel/mut.yy"
    {}
    break;

  case 179:
/* Line 1787 of yacc.c  */
#line 742 "../../../mutabor-git/src/kernel/mut.yy"
    { init_aktions_liste (box); }
    break;

  case 180:
/* Line 1787 of yacc.c  */
#line 744 "../../../mutabor-git/src/kernel/mut.yy"
    { get_new_anweisung (box); }
    break;

  case 181:
/* Line 1787 of yacc.c  */
#line 746 "../../../mutabor-git/src/kernel/mut.yy"
    { init_aktions_liste (box); }
    break;

  case 182:
/* Line 1787 of yacc.c  */
#line 748 "../../../mutabor-git/src/kernel/mut.yy"
    { get_new_anweisung (box); }
    break;

  case 183:
/* Line 1787 of yacc.c  */
#line 753 "../../../mutabor-git/src/kernel/mut.yy"
    { get_harmoniebezeichner (box, (yyvsp[(1) - (5)].integer), (yyvsp[(3) - (5)].identifier),  (yyvsp[(5) - (5)].integer)); }
    break;

  case 184:
/* Line 1787 of yacc.c  */
#line 755 "../../../mutabor-git/src/kernel/mut.yy"
    { get_harmoniebezeichner (box, MUTABOR_NO_KEY, (yyvsp[(1) - (3)].identifier),  (yyvsp[(3) - (3)].integer)); }
    break;

  case 185:
/* Line 1787 of yacc.c  */
#line 757 "../../../mutabor-git/src/kernel/mut.yy"
    { get_harmoniebezeichner (box, (yyvsp[(1) - (3)].integer), (yyvsp[(3) - (3)].identifier), MUTABOR_NO_KEY); }
    break;

  case 186:
/* Line 1787 of yacc.c  */
#line 759 "../../../mutabor-git/src/kernel/mut.yy"
    { get_harmoniebezeichner (box,  MUTABOR_NO_KEY, (yyvsp[(1) - (1)].identifier), MUTABOR_NO_KEY); }
    break;

  case 187:
/* Line 1787 of yacc.c  */
#line 763 "../../../mutabor-git/src/kernel/mut.yy"
    { get_ausloeser_default (box); }
    break;

  case 188:
/* Line 1787 of yacc.c  */
#line 764 "../../../mutabor-git/src/kernel/mut.yy"
    { get_ausloeser_harmonie (box); }
    break;

  case 189:
/* Line 1787 of yacc.c  */
#line 765 "../../../mutabor-git/src/kernel/mut.yy"
    { get_ausloeser_harmonie_form (box); }
    break;

  case 190:
/* Line 1787 of yacc.c  */
#line 766 "../../../mutabor-git/src/kernel/mut.yy"
    { get_ausloeser_taste (box,(yyvsp[(2) - (2)].identifier)); }
    break;

  case 191:
/* Line 1787 of yacc.c  */
#line 767 "../../../mutabor-git/src/kernel/mut.yy"
    { init_integersequenz (box); }
    break;

  case 192:
/* Line 1787 of yacc.c  */
#line 769 "../../../mutabor-git/src/kernel/mut.yy"
    { get_ausloeser_midi_in (box); }
    break;

  case 193:
/* Line 1787 of yacc.c  */
#line 774 "../../../mutabor-git/src/kernel/mut.yy"
    { get_new_integer_in_integersequenz (box,(yyvsp[(1) - (1)].integer));}
    break;

  case 194:
/* Line 1787 of yacc.c  */
#line 776 "../../../mutabor-git/src/kernel/mut.yy"
    { get_new_integer_in_integersequenz (box,(yyvsp[(3) - (3)].integer));}
    break;

  case 195:
/* Line 1787 of yacc.c  */
#line 777 "../../../mutabor-git/src/kernel/mut.yy"
    { 
		mutabor_error_message(box,
				      false,
				      _("Bad MIDI list in line %d"),  
				      FEHLERZEILE );
	  }
    break;

  case 196:
/* Line 1787 of yacc.c  */
#line 787 "../../../mutabor-git/src/kernel/mut.yy"
    {}
    break;

  case 197:
/* Line 1787 of yacc.c  */
#line 791 "../../../mutabor-git/src/kernel/mut.yy"
    {}
    break;

  case 198:
/* Line 1787 of yacc.c  */
#line 792 "../../../mutabor-git/src/kernel/mut.yy"
    {}
    break;

  case 199:
/* Line 1787 of yacc.c  */
#line 797 "../../../mutabor-git/src/kernel/mut.yy"
    { get_instrument_dekl (box, (yyvsp[(1) - (4)].integer), (yyvsp[(4) - (4)].integer), (yyvsp[(4) - (4)].integer), 0, & box->file->list_of_instrumente); }
    break;

  case 200:
/* Line 1787 of yacc.c  */
#line 799 "../../../mutabor-git/src/kernel/mut.yy"
    { get_instrument_dekl (box, (yyvsp[(1) - (6)].integer), (yyvsp[(4) - (6)].integer), (yyvsp[(6) - (6)].integer), 0, & box->file->list_of_instrumente); }
    break;

  case 201:
/* Line 1787 of yacc.c  */
#line 801 "../../../mutabor-git/src/kernel/mut.yy"
    { get_instrument_dekl (box, (yyvsp[(1) - (6)].integer), 0, 0, (yyvsp[(5) - (6)].integer), & box->file->list_of_instrumente); }
    break;

  case 202:
/* Line 1787 of yacc.c  */
#line 803 "../../../mutabor-git/src/kernel/mut.yy"
    { get_instrument_dekl (box, (yyvsp[(1) - (7)].integer), (yyvsp[(4) - (7)].integer), (yyvsp[(4) - (7)].integer), (yyvsp[(6) - (7)].integer), & box->file->list_of_instrumente); }
    break;

  case 203:
/* Line 1787 of yacc.c  */
#line 805 "../../../mutabor-git/src/kernel/mut.yy"
    { get_instrument_dekl (box, (yyvsp[(1) - (9)].integer), (yyvsp[(4) - (9)].integer), (yyvsp[(6) - (9)].integer), (yyvsp[(8) - (9)].integer), & box->file->list_of_instrumente); }
    break;

  case 204:
/* Line 1787 of yacc.c  */
#line 809 "../../../mutabor-git/src/kernel/mut.yy"
    { (yyval.f_value) = (yyvsp[(1) - (1)].f_value) ; }
    break;

  case 205:
/* Line 1787 of yacc.c  */
#line 810 "../../../mutabor-git/src/kernel/mut.yy"
    { (yyval.f_value) = (double) (yyvsp[(1) - (1)].integer) ; }
    break;


/* Line 1787 of yacc.c  */
#line 3137 "../../../mutabor-git/src/kernel/mut.cc"
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
  *++yylsp = yyloc;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (&yylloc, box, YY_("syntax error"));
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
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
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
        yyerror (&yylloc, box, yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }

  yyerror_range[1] = yylloc;

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
		      yytoken, &yylval, &yylloc, box);
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

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  yyerror_range[1] = yylsp[1-yylen];
  /* Do not reclaim the symbols of the rule which action triggered
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
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

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

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp, yylsp, box);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  /* Using YYLLOC is tempting, but would change the location of
     the lookahead.  YYLOC is available though.  */
  YYLLOC_DEFAULT (yyloc, yyerror_range, 2);
  *++yylsp = yyloc;

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
  yyerror (&yylloc, box, YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, &yylloc, box);
    }
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp, yylsp, box);
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
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}


/* Line 2050 of yacc.c  */
#line 814 "../../../mutabor-git/src/kernel/mut.yy"

/// \todo check whether this function is necessary for any system but windows
#ifdef __WXMSW__
inline int mutabor_toupper(int c) {
	if (c == EOF) return c;
	else return toupper(c);
}
#ifdef toupper
#undef toupper
#endif
#define toupper mutabor_toupper
#endif

int yylex(YYSTYPE* lvalp, YYLTYPE* llocp,  mutabor_box_type * box)
{
    int c;

start_lex:
    /* Ignore whitespace, get first nonwhitespace character */
    while ( box->scanner->anzahl_eingelesene_zeichen ++,
            isspace(c = *(box->scanner->pos++)) ) {
	    DEBUGLOG2(other,_T("char %x"),c);
	    if (c == '\n') {
		    DEBUGLOG2(other,_T("New line"));
		    if (!(llocp->first_line ++ % LINE_DRAW_QUANTUM)) 
			    show_line_number(box,llocp->first_line);
	    }
    }
    
    if (c == '"') {
	    while (box->scanner->anzahl_eingelesene_zeichen ++,
		   (c= *(box->scanner->pos++)) != '"' && c != EOF )
                    if (c == '\n') llocp->first_line ++;
        
       goto start_lex;
    }

    if (c == 0) {
	    show_line_number(box,llocp->first_line);
	    return 0;
    }

        
    /* char starts a number => parse the number. */
    if (isdigit(c)) {
	    double zahl = 0.0;
	    while (isdigit(c)) {
		    zahl *= 10;
		    zahl += ( c - '0' );
		    box->scanner->anzahl_eingelesene_zeichen ++;
		    c = *(box->scanner->pos++);
	    }
	    if (c == '.') {    /* dann nachkommastellen */
		    double faktor = 1.0;
		    while (box->scanner->anzahl_eingelesene_zeichen ++,
			   isdigit (c = *(box->scanner->pos++))) {
			    faktor /= 10;
			    zahl += faktor * ( c - '0' );
		    }
		    --(box->scanner->pos);
		    mutASSERT(*(box->scanner->pos) == c);
		    mutASSERT((box->scanner->pos) >= (box->scanner->data));
		    box->scanner->anzahl_eingelesene_zeichen --;
		    lvalp->f_value = zahl;
		    return MUTABOR_TOKEN_F_NUMBER;
	    }
	    else {
		    --(box->scanner->pos);
		    mutASSERT(*(box->scanner->pos) == c);
		    mutASSERT((box->scanner->pos) >= (box->scanner->data));
		    box->scanner->anzahl_eingelesene_zeichen --;
            
		    if (zahl > INT_MAX) {
			    lvalp->f_value = zahl;
			    return MUTABOR_TOKEN_F_NUMBER;
		    }
		    else {
			    lvalp->integer = (int)zahl;
			    return MUTABOR_TOKEN_INTEGER;
		    }
	    }

      
    }
    
    /* # starts a HEX-number => parse the number. */
    if (c == '#') {
        unsigned int help;
	char * newpos;
	int len;
	errno = 0;
	help = strtoull(box->scanner->pos, &newpos, 16);
        if (errno || newpos == box->scanner->pos) {
		mutabor_error_message(box,
				      false,
				      _("No hex number after # (line %d)"),
				      llocp->first_line + 1);
		return MUTABOR_TOKEN_ERROR;
        }
	len = newpos - box->scanner->pos;
        box->scanner->pos = newpos;
        box->scanner->anzahl_eingelesene_zeichen += len;
	lvalp->integer = help;
        return MUTABOR_TOKEN_INTEGER;

/* printf("f_number:%lf:\n", lvalp->f_value); */

    }
    
    /* Test auf reserved word oder einen Identifier */
    if (isalpha (c) || (c == '_') || (c == '\'') ) {

static struct { 
    const char *word;
    int token;
} reserved_words [] = {
/* German keywords : */
{ "INTERVALL"  , MUTABOR_TOKEN_INTERVAL  },
{ "WURZEL"     , MUTABOR_TOKEN_ROOT     },
{ "TON"        , MUTABOR_TOKEN_TONE        },
{ "TONSYSTEM"  , MUTABOR_TOKEN_TONESYSTEM  },
{ "UMSTIMMUNG" , MUTABOR_TOKEN_RETUNING },
{ "HARMONIE"   , MUTABOR_TOKEN_HARMONY   },
{ "LOGIK"      , MUTABOR_TOKEN_LOGIC      },
{ "FORM"       , MUTABOR_TOKEN_FORM       },
{ "HARMONIEANALYSE", MUTABOR_TOKEN_HARMONY_ANALYSIS },
{ "MIDIKANAL"  , MUTABOR_TOKEN_MIDICHANNEL },
{ "TASTE"      , MUTABOR_TOKEN_KEY      },
{ "MIDIIN"     , MUTABOR_TOKEN_MIDI_IN    },
{ "MIDIOUT"    , MUTABOR_TOKEN_MIDI_OUT   },
{ "ANSONSTEN"  , MUTABOR_TOKEN_ELSE  },
/* English keywords : */
{ "INTERVAL"   , MUTABOR_TOKEN_INTERVAL  },
{ "ROOT"       , MUTABOR_TOKEN_ROOT     },
{ "TONE"       , MUTABOR_TOKEN_TONE        },
{ "TONESYSTEM" , MUTABOR_TOKEN_TONESYSTEM  },
{ "RETUNING"   , MUTABOR_TOKEN_RETUNING },
{ "PATTERN"    , MUTABOR_TOKEN_HARMONY   },
{ "HARMONY_ANALYSIS", MUTABOR_TOKEN_HARMONY_ANALYSIS },
{ "LOGIC"      , MUTABOR_TOKEN_LOGIC      },
{ "SHIFTED"    , MUTABOR_TOKEN_FORM       },
{ "MIDICHANNEL", MUTABOR_TOKEN_MIDICHANNEL },
{ "KEY"        , MUTABOR_TOKEN_KEY      },
{ "ELSE"       , MUTABOR_TOKEN_ELSE  },
{ NULL         , 0          }
};


#if 0
        char *symbuffer = xmalloc ((size_t)(MAX_IDENTIFIER_LEN + 1));
        int i=0;
        
        do {
            if (c == '\'') c = 'i';
            symbuffer[i++] = c;
            c = *(box->scanner->pos++);
        } while (c != EOF                && 
                 i < MAX_IDENTIFIER_LEN  && 
                 (isalnum (c) || (c == '_') || (c == '\'') ) );
        
        --(box->scanner->pos);
	mutASSERT(*(box->scanner->pos) == c);
	mutASSERT((box->scanner->pos) >= (box->scanner->data));
        symbuffer[i] = '\0';
#else
        int i = 0;
        int max_identifier_len = 10;
        char *symbuffer = (char*) xmalloc (box, (size_t) max_identifier_len);

        do {
            if (c == '\'') c = 'i';

            if ( i + 1 == max_identifier_len ) {
		    char * help = (char*) xrealloc (box, symbuffer, (size_t) (max_identifier_len += 10));
		    memmove (help, symbuffer, (size_t) max_identifier_len);
		    symbuffer = help;
            }

            symbuffer[i++] = c;
	    DEBUGLOG2(other,_T("character #%d = %x"),i,c);
	    c = *(box->scanner->pos++);
	    DEBUGLOG2(other,_T("character #%d = %x"),i,c);
            box->scanner->anzahl_eingelesene_zeichen ++;

        } while ((c) && 
                 (isalnum (c) || (c == '_') || (c == '\'') ) );
        
        --(box->scanner->pos);
	mutASSERT(*(box->scanner->pos) == c);
	mutASSERT((box->scanner->pos) >= (box->scanner->data));
        box->scanner->anzahl_eingelesene_zeichen --;
        symbuffer[i] = '\0';

#endif

/* printf("symbuffer:%s:\n", symbuffer); */
        
        for (i=0; reserved_words[i].word; i++) {
            if ( ! strcasecmp (symbuffer, reserved_words[i].word)) {
                xfree (symbuffer);
                return reserved_words[i].token;
            }
        }
        
        lvalp->identifier = symbuffer;
        return MUTABOR_TOKEN_IDENTIFIER;
    }
    
    /* Any other character is a token by itself */
    switch (c) {
        case '+':
        case '-':
        case '*':
        case '/':
        case '[':
        case ']':
        case ':':
        case '=':
        case '(':
        case ')':
        case ',':
        case '~':
        case '@':
        case '<':
        case '>':
        case '{':
        case '}':
        case ';':
               return c;
    }

    
    mutabor_error_message(box,
			  false,
			  _("Invalid character: “%c” = %x at line %d."),
			  c,c,llocp->first_line + 1);
    
    return 0;  /* um Compilerwarnungen zu vermeiden */

    
} /* yylex */

void init_yylex ()
{
	//    llocp->first_line = 0;
	//    box->scanner->anzahl_eingelesene_zeichen = 0;
}


#ifdef __cplusplus
		}
	}
 }
#endif

/* END MUT_TAB.C */

/* 
 * \}
 */

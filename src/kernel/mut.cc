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
     MUTABOR_TOKEN_ANCHOR = 277,
     MUTABOR_TOKEN_DISTANCE = 278,
     MUTABOR_TOKEN_ENDOFFILE = 279,
     MUTABOR_TOKEN_ERROR = 280,
     MUTABOR_TOKEN_SPACES = 281,
     MUTABOR_TOKEN_COMMENT = 282,
     MUTABOR_TOKEN_COMMENT_START = 283,
     MUTABOR_TOKEN_COMMENT_END = 284,
     MUTABOR_TOKEN_OTHER = 285
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
#define MUTABOR_TOKEN_ANCHOR 277
#define MUTABOR_TOKEN_DISTANCE 278
#define MUTABOR_TOKEN_ENDOFFILE 279
#define MUTABOR_TOKEN_ERROR 280
#define MUTABOR_TOKEN_SPACES 281
#define MUTABOR_TOKEN_COMMENT 282
#define MUTABOR_TOKEN_COMMENT_START 283
#define MUTABOR_TOKEN_COMMENT_END 284
#define MUTABOR_TOKEN_OTHER 285



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{
/* Line 387 of yacc.c  */
#line 85 "../../../mutabor-git/src/kernel/mut.yy"

			double      f_value;        /* floating point numbers */
			int         integer;        /* integers */
			char        *identifier;    /* names/identifiers */
			struct argument_list * arguments;  /* argument list */
			struct parameter_list * parameters; /* parameter list */


/* Line 387 of yacc.c  */
#line 227 "../../../mutabor-git/src/kernel/mut.cc"
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
#line 147 "../../../mutabor-git/src/kernel/mut.yy"

int yylex(YYSTYPE* lvalp, YYLTYPE* llocp,  mutabor_box_type * box);
void yyerror(YYLTYPE* locp, mutabor_box_type * box, const char* err)
{
	mutabor_error_message(box,
			      compiler_error,
			      _("%s at line %d"),
			      err,
			      locp->first_line);
}

#define YYLEX_PARAM box
//#define scanner box

/* Line 390 of yacc.c  */
#line 282 "../../../mutabor-git/src/kernel/mut.cc"

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
#define YYFINAL  29
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   332

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  49
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  106
/* YYNRULES -- Number of rules.  */
#define YYNRULES  212
/* YYNRULES -- Number of states.  */
#define YYNSTATES  349

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   285

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      42,    43,    33,    31,    41,    32,    47,    34,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    38,     2,
      35,    37,    36,     2,    44,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    39,     2,    40,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    45,     2,    46,    48,     2,     2,     2,
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
      25,    26,    27,    28,    29,    30
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     4,     6,     8,    10,    12,    14,    16,
      18,    21,    24,    26,    29,    30,    32,    34,    36,    38,
      40,    42,    44,    47,    50,    51,    54,    55,    58,    64,
      70,    74,    78,    81,    84,    85,    88,    89,    92,    96,
     102,   106,   112,   116,   119,   120,   123,   126,   129,   133,
     137,   142,   147,   153,   159,   161,   164,   168,   173,   176,
     177,   180,   181,   184,   185,   194,   195,   205,   207,   211,
     213,   214,   216,   217,   219,   221,   225,   227,   229,   231,
     232,   234,   236,   240,   242,   244,   247,   249,   251,   254,
     255,   258,   259,   264,   265,   273,   274,   282,   283,   289,
     291,   293,   295,   297,   299,   301,   303,   305,   307,   309,
     311,   315,   321,   327,   335,   336,   341,   343,   347,   348,
     352,   354,   358,   359,   361,   363,   365,   366,   371,   372,
     377,   378,   383,   384,   389,   390,   395,   396,   402,   403,
     410,   411,   418,   419,   424,   426,   430,   432,   437,   443,
     444,   450,   452,   453,   459,   461,   464,   465,   471,   472,
     479,   480,   486,   487,   493,   496,   497,   500,   501,   509,
     513,   514,   517,   519,   523,   525,   528,   531,   532,   533,
     537,   538,   546,   547,   556,   557,   560,   561,   569,   570,
     576,   582,   586,   590,   592,   594,   596,   599,   602,   603,
     609,   611,   615,   617,   620,   621,   624,   629,   636,   643,
     651,   661,   663
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
      50,     0,    -1,    -1,    56,    -1,    31,    -1,    32,    -1,
      33,    -1,    34,    -1,    51,    -1,    52,    -1,    35,    35,
      -1,    36,    36,    -1,    57,    -1,    56,    57,    -1,    -1,
      58,    -1,    63,    -1,    72,    -1,    87,    -1,   130,    -1,
     137,    -1,   151,    -1,     1,    57,    -1,     6,    59,    -1,
      -1,    59,    60,    -1,    -1,    61,    62,    -1,     3,    37,
     154,    38,   154,    -1,     3,    37,   154,    15,   154,    -1,
       3,    37,    68,    -1,     3,    37,     1,    -1,     3,     1,
      -1,     7,    64,    -1,    -1,    64,    65,    -1,    -1,    66,
      67,    -1,     3,    37,   154,    -1,     3,    37,     3,    32,
      68,    -1,     3,    37,     3,    -1,     3,    37,     3,    31,
      68,    -1,     3,    37,     1,    -1,    71,    69,    -1,    -1,
      69,    70,    -1,    31,     3,    -1,    32,     3,    -1,    31,
     154,     3,    -1,    32,   154,     3,    -1,    31,    34,   154,
       3,    -1,    32,    34,   154,     3,    -1,    31,   154,    34,
     154,     3,    -1,    32,   154,    34,   154,     3,    -1,     3,
      -1,   154,     3,    -1,    34,   154,     3,    -1,   154,    34,
     154,     3,    -1,     8,    73,    -1,    -1,    73,    74,    -1,
      -1,    75,    76,    -1,    -1,     3,    37,     5,    39,    79,
      40,    77,    68,    -1,    -1,     3,    37,     5,    39,    79,
      40,    78,    32,    68,    -1,    80,    -1,    79,    41,    80,
      -1,     3,    -1,    -1,     1,    -1,    -1,    82,    -1,    83,
      -1,    83,    41,    82,    -1,     3,    -1,    23,    -1,    22,
      -1,    -1,    85,    -1,    86,    -1,    86,    41,    85,    -1,
       3,    -1,     5,    -1,    32,     5,    -1,    23,    -1,    22,
      -1,     9,    88,    -1,    -1,    89,    88,    -1,    -1,     3,
      37,    90,    94,    -1,    -1,     3,    42,    81,    43,    37,
      91,    94,    -1,    -1,     3,    42,    81,     1,    37,    92,
      94,    -1,    -1,     3,     1,    37,    93,    94,    -1,    95,
      -1,    96,    -1,    97,    -1,    98,    -1,    99,    -1,   110,
      -1,   113,    -1,   116,    -1,   121,    -1,   128,    -1,     1,
      -1,    86,    39,    40,    -1,    44,    51,    86,    39,    40,
      -1,    39,    54,    86,    55,    40,    -1,    39,    54,    44,
      53,    86,    55,    40,    -1,    -1,    39,   100,   101,    40,
      -1,   105,    -1,   105,    41,   103,    -1,    -1,    41,   102,
     103,    -1,   104,    -1,   103,    41,   104,    -1,    -1,   105,
      -1,     3,    -1,    44,    -1,    -1,     3,    31,   106,    68,
      -1,    -1,    44,    31,   107,    68,    -1,    -1,     3,    32,
     108,    68,    -1,    -1,    44,    32,   109,    68,    -1,    -1,
      39,    40,   111,    68,    -1,    -1,    39,    40,   112,    32,
      68,    -1,    -1,    39,    40,    44,    31,   114,    68,    -1,
      -1,    39,    40,    44,    32,   115,    68,    -1,    -1,    45,
     117,   118,    46,    -1,   119,    -1,   118,    41,   119,    -1,
       3,    -1,     3,    42,    84,    43,    -1,     3,    42,    84,
       1,    43,    -1,    -1,    17,    42,   120,   150,    43,    -1,
      18,    -1,    -1,    86,    45,   122,   123,    46,    -1,   124,
      -1,   123,   124,    -1,    -1,     5,    32,    36,   125,   118,
      -1,    -1,    32,     5,    32,    36,   126,   118,    -1,    -1,
      20,    32,    36,   127,   118,    -1,    -1,    17,    42,   129,
     150,    43,    -1,    10,   131,    -1,    -1,   131,   132,    -1,
      -1,     3,    37,    45,   133,   135,    46,   134,    -1,     3,
      37,     1,    -1,    -1,    47,     5,    -1,   136,    -1,   135,
      41,   136,    -1,     5,    -1,    33,     5,    -1,    11,   138,
      -1,    -1,    -1,   138,   139,   140,    -1,    -1,     3,   148,
      37,    39,   141,   143,    40,    -1,    -1,     3,   148,    37,
       3,    39,   142,   143,    40,    -1,    -1,   143,   144,    -1,
      -1,   148,    32,    36,    45,   145,   118,    46,    -1,    -1,
     148,    32,    36,   146,   119,    -1,     5,    48,     3,    48,
       5,    -1,     3,    48,     5,    -1,     5,    48,     3,    -1,
       3,    -1,    20,    -1,   147,    -1,    14,   147,    -1,    13,
       3,    -1,    -1,    16,    42,   149,   150,    43,    -1,     5,
      -1,   150,    41,     5,    -1,     1,    -1,    12,   152,    -1,
      -1,   152,   153,    -1,     5,    32,    36,     5,    -1,     5,
      32,    36,     5,    32,     5,    -1,     5,    32,    36,    39,
       5,    40,    -1,     5,    32,    36,     5,    39,     5,    40,
      -1,     5,    32,    36,     5,    32,     5,    39,     5,    40,
      -1,     4,    -1,     5,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   165,   165,   166,   170,   171,   175,   176,   180,   181,
     184,   185,   187,   188,   191,   192,   193,   194,   195,   196,
     197,   198,   199,   207,   209,   211,   215,   215,   219,   227,
     238,   240,   247,   256,   258,   260,   264,   264,   268,   271,
     275,   279,   283,   293,   297,   299,   302,   305,   308,   311,
     314,   324,   334,   344,   369,   377,   380,   390,   420,   422,
     424,   428,   428,   433,   432,   437,   436,   442,   442,   445,
     446,   447,   455,   456,   462,   463,   474,   477,   484,   504,
     505,   511,   514,   530,   532,   534,   536,   538,   544,   548,
     550,   554,   554,   565,   564,   575,   574,   588,   588,   602,
     603,   604,   605,   606,   607,   608,   609,   610,   611,   612,
     622,   627,   632,   637,   643,   642,   652,   653,   655,   655,
     662,   663,   668,   672,   676,   677,   679,   679,   682,   682,
     685,   685,   688,   688,   695,   695,   698,   698,   704,   704,
     707,   707,   713,   713,   719,   720,   724,   727,   729,   738,
     737,   741,   745,   745,   751,   752,   757,   756,   761,   760,
     765,   764,   772,   771,   779,   783,   784,   789,   788,   793,
     803,   804,   808,   809,   813,   814,   818,   822,   823,   823,
     831,   830,   836,   835,   843,   844,   849,   849,   853,   853,
     859,   861,   863,   865,   870,   871,   872,   873,   874,   874,
     880,   882,   884,   894,   898,   899,   903,   905,   907,   909,
     911,   916,   917
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 1
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "\"identifier\"",
  "\"floating point number\"", "\"integer number\"",
  "\"interval declaration\"", "\"tone declaration\"", "\"tone system\"",
  "\"retuning declaration\"", "\"harmony declaration\"",
  "\"logic declaration\"", "\"MIDI channel declaration\"",
  "\"key trigger\"", "\"harmonic form trigger\"", "\"n-th root operator\"",
  "\"MIDIIN\"", "\"MIDIOUT\"", "\"HARMONY_ANALYSIS\"", "\"calls\"",
  "\"else path\"", "\"parameter\"", "\"ANCHOR\"", "\"DISTANCE\"",
  "\"end of file\"", "\"error\"", "\"space\"", "\"comment\"",
  "\"comment start character (“\\\"”)\"",
  "\"comment end character (“\\\"”)\"", "\"other token\"", "'+'",
  "'-'", "'*'", "'/'", "'<'", "'>'", "'='", "':'", "'['", "']'", "','",
  "'('", "')'", "'@'", "'{'", "'}'", "'.'", "'~'", "$accept", "start",
  "addition_or_subtraction", "multiplication_or_division",
  "basic_binary_operator", "ll", "gg", "blocks", "block",
  "intervalldeklaration", "intervalldekl1", "intervalldekl2_1", "$@1",
  "intervalldekl2", "tondeklaration", "tondekl1", "tondekl2_1", "$@2",
  "tondekl2", "KOMPLEX_TON_LIST", "KOMPLEX_TON_LIST_2", "KOMPLEX_TON_1",
  "KOMPLEX_TON_START", "tonsystemdeklaration", "tonsystemdekl1",
  "tonsystemdekl2_1", "$@3", "tonsystemdekl2", "$@4", "$@5", "tonliste",
  "ton_element", "parameter_list", "nonempty_parameter_list", "parameter",
  "argument_list", "nonempty_argument_list", "argument_list_element",
  "umstimmungdeklaration", "retuning_definitions", "retuning_definition",
  "$@6", "$@7", "$@8", "$@9", "retuning_term",
  "umstimmungs_dekl_taste_abs", "umstimmungs_dekl_taste_rel",
  "umstimmungs_dekl_breite_abs", "umstimmungs_dekl_breite_rel",
  "umstimmungs_dekl_tonhoehe_veraendert", "$@10",
  "nonempty_umstimm_expression_list", "$@11", "umstimm_expression_list",
  "umstimm_expression", "nonempty_umstimm_expression", "$@12", "$@13",
  "$@14", "$@15", "umstimmungs_dekl_wiederholung_abs", "$@16", "$@17",
  "umstimmungs_dekl_wiederholung_rel", "$@18", "$@19",
  "umstimmungs_dekl_umstimmungs_bund", "$@20", "aktions_liste", "aktion",
  "$@21", "umstimmungs_dekl_umstimmungs_case", "$@22",
  "umstimmungs_case_liste", "umstimmungs_case_element", "$@23", "$@24",
  "$@25", "umstimmungs_dekl_midi_out", "$@26", "harmoniedeklaration",
  "harmonie_dekl_1", "harmonie_dekl_2", "$@27", "bezugs_taste",
  "tasten_liste", "taste", "logikdeklaration", "logik_dekl_1", "$@28",
  "logik_dekl_2", "$@29", "$@30", "anweisungs_liste", "anweisung", "$@31",
  "$@32", "harmoniebezeichner", "ausloeser", "$@33", "integersequenz",
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
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,    43,    45,    42,    47,    60,    62,    61,    58,    91,
      93,    44,    40,    41,    64,   123,   125,    46,   126
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    49,    50,    50,    51,    51,    52,    52,    53,    53,
      54,    55,    56,    56,    57,    57,    57,    57,    57,    57,
      57,    57,    57,    58,    59,    59,    61,    60,    62,    62,
      62,    62,    62,    63,    64,    64,    66,    65,    67,    67,
      67,    67,    67,    68,    69,    69,    70,    70,    70,    70,
      70,    70,    70,    70,    71,    71,    71,    71,    72,    73,
      73,    75,    74,    77,    76,    78,    76,    79,    79,    80,
      80,    80,    81,    81,    82,    82,    83,    83,    83,    84,
      84,    85,    85,    86,    86,    86,    86,    86,    87,    88,
      88,    90,    89,    91,    89,    92,    89,    93,    89,    94,
      94,    94,    94,    94,    94,    94,    94,    94,    94,    94,
      95,    96,    97,    98,   100,    99,   101,   101,   102,   101,
     103,   103,   104,   104,   105,   105,   106,   105,   107,   105,
     108,   105,   109,   105,   111,   110,   112,   110,   114,   113,
     115,   113,   117,   116,   118,   118,   119,   119,   119,   120,
     119,   119,   122,   121,   123,   123,   125,   124,   126,   124,
     127,   124,   129,   128,   130,   131,   131,   133,   132,   132,
     134,   134,   135,   135,   136,   136,   137,   138,   139,   138,
     141,   140,   142,   140,   143,   143,   145,   144,   146,   144,
     147,   147,   147,   147,   148,   148,   148,   148,   149,   148,
     150,   150,   150,   151,   152,   152,   153,   153,   153,   153,
     153,   154,   154
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     1,     1,     1,     1,     1,     1,     1,
       2,     2,     1,     2,     0,     1,     1,     1,     1,     1,
       1,     1,     2,     2,     0,     2,     0,     2,     5,     5,
       3,     3,     2,     2,     0,     2,     0,     2,     3,     5,
       3,     5,     3,     2,     0,     2,     2,     2,     3,     3,
       4,     4,     5,     5,     1,     2,     3,     4,     2,     0,
       2,     0,     2,     0,     8,     0,     9,     1,     3,     1,
       0,     1,     0,     1,     1,     3,     1,     1,     1,     0,
       1,     1,     3,     1,     1,     2,     1,     1,     2,     0,
       2,     0,     4,     0,     7,     0,     7,     0,     5,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       3,     5,     5,     7,     0,     4,     1,     3,     0,     3,
       1,     3,     0,     1,     1,     1,     0,     4,     0,     4,
       0,     4,     0,     4,     0,     4,     0,     5,     0,     6,
       0,     6,     0,     4,     1,     3,     1,     4,     5,     0,
       5,     1,     0,     5,     1,     2,     0,     5,     0,     6,
       0,     5,     0,     5,     2,     0,     2,     0,     7,     3,
       0,     2,     1,     3,     1,     2,     2,     0,     0,     3,
       0,     7,     0,     8,     0,     2,     0,     7,     0,     5,
       5,     3,     3,     1,     1,     1,     2,     2,     0,     5,
       1,     3,     1,     2,     0,     2,     4,     6,     6,     7,
       9,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,    24,    34,    59,    89,   165,   177,   204,     0,
       0,    12,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    33,    58,     0,    88,    89,   164,   176,   203,     1,
      13,    25,     0,    35,     0,    60,     0,     0,    91,    72,
      90,     0,   166,     0,     0,   205,     0,    27,     0,    37,
       0,    62,    97,     0,    76,    78,    77,     0,    73,    74,
       0,     0,   179,     0,    32,     0,     0,     0,     0,   109,
      83,    84,     0,    87,    86,     0,   114,     0,   142,     0,
      92,    99,   100,   101,   102,   103,   104,   105,   106,   107,
     108,     0,     0,     0,   169,   167,   193,     0,     0,     0,
       0,   194,   195,     0,     0,    31,    54,   211,   212,     0,
      30,    44,     0,    42,    40,    38,     0,    98,   162,    85,
       0,   134,     0,     0,     4,     5,     0,     0,     0,   152,
      95,    93,    75,     0,     0,     0,   197,   196,   198,     0,
     206,     0,     0,    43,    55,     0,     0,     0,     0,     0,
       0,     0,    10,     0,     0,     0,     0,     0,   124,   118,
     125,     0,   116,     0,   146,     0,   151,     0,   144,   110,
       0,     0,     0,   174,     0,     0,   172,   191,   192,     0,
       0,   180,     0,     0,     0,    56,     0,     0,    45,    29,
       0,    28,    41,     0,    39,    71,    69,     0,    67,   202,
     200,     0,   138,   140,   135,     0,     6,     7,     8,     9,
       0,     0,     0,   126,   130,   122,   128,   132,   115,   122,
       0,    79,   149,     0,   143,     0,     0,     0,     0,   154,
      96,    94,   175,     0,   170,     0,     0,   182,   184,   207,
       0,   208,    46,     0,     0,    47,     0,     0,    57,    63,
       0,     0,   163,     0,     0,   137,     0,    11,   112,     0,
       0,   119,   120,   123,     0,     0,   117,   111,     0,    80,
      81,     0,   145,     0,     0,     0,   153,   155,   173,     0,
     168,   190,   199,   184,     0,     0,   209,     0,    48,     0,
       0,    49,     0,     0,     0,    68,   201,   139,   141,     0,
     127,   131,   122,   129,   133,     0,   147,     0,     0,   156,
     160,     0,   171,     0,   181,   185,     0,     0,    50,     0,
      51,     0,    64,     0,   113,   121,   148,    82,   150,     0,
       0,   158,   183,     0,   210,    52,    53,    66,   157,   161,
       0,   188,   159,   186,     0,     0,   189,     0,   187
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     9,   126,   209,   210,   122,   212,    10,    11,    12,
      20,    31,    32,    47,    13,    21,    33,    34,    49,   110,
     143,   188,   111,    14,    22,    35,    36,    51,   293,   294,
     197,   198,    57,    58,    59,   268,   269,    79,    15,    24,
      25,    53,   172,   171,    68,    80,    81,    82,    83,    84,
      85,   123,   161,   215,   261,   262,   263,   259,   264,   260,
     265,    86,   154,   155,    87,   253,   254,    88,   127,   167,
     168,   271,    89,   170,   228,   229,   329,   340,   330,    90,
     151,    16,    26,    42,   133,   280,   175,   176,    17,    27,
      43,    62,   238,   283,   284,   315,   345,   344,   102,   316,
     179,   201,    18,    28,    45,   193
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -220
static const yytype_int16 yypact[] =
{
     183,   196,  -220,  -220,  -220,    18,  -220,  -220,  -220,    49,
     209,  -220,  -220,  -220,  -220,  -220,  -220,  -220,  -220,  -220,
      75,    83,    91,    21,  -220,    18,   104,   107,   112,  -220,
    -220,  -220,   117,  -220,   129,  -220,   132,   110,  -220,    66,
    -220,   121,  -220,   177,   141,  -220,    33,  -220,   175,  -220,
     188,  -220,  -220,     9,  -220,  -220,  -220,     8,  -220,   144,
      10,   148,  -220,   178,  -220,   126,   225,   238,     9,  -220,
    -220,  -220,   203,  -220,  -220,   239,    98,   138,  -220,   -16,
    -220,  -220,  -220,  -220,  -220,  -220,  -220,  -220,  -220,  -220,
    -220,   210,   211,    66,  -220,  -220,   198,   205,   246,   171,
     212,  -220,  -220,   213,    11,  -220,  -220,  -220,  -220,   218,
    -220,  -220,    64,  -220,   200,  -220,   216,  -220,  -220,  -220,
     217,    -8,    15,    24,  -220,  -220,   143,    25,   219,  -220,
    -220,  -220,  -220,    12,   251,   248,  -220,  -220,  -220,    36,
      60,   252,   255,   202,  -220,   218,   218,   218,   100,   100,
      32,    95,  -220,   204,   100,   228,   167,   226,   206,  -220,
     208,   221,   222,   227,   223,   229,  -220,   103,  -220,  -220,
      51,     9,     9,  -220,   259,   109,  -220,  -220,   220,    95,
     230,  -220,   262,   265,   232,  -220,   111,   137,  -220,  -220,
     270,  -220,  -220,    27,  -220,  -220,  -220,   201,  -220,  -220,
    -220,   136,  -220,  -220,  -220,   100,  -220,  -220,  -220,  -220,
     143,   240,   234,  -220,  -220,    16,  -220,  -220,  -220,    16,
     235,   143,  -220,    25,  -220,   245,   247,   273,    20,  -220,
    -220,  -220,  -220,    12,   233,   276,   145,  -220,  -220,   243,
     244,  -220,  -220,   218,    43,  -220,   218,    59,  -220,   253,
      32,   278,  -220,   100,   100,  -220,   226,  -220,  -220,   100,
     100,   249,  -220,  -220,   100,   100,   249,  -220,    14,  -220,
     250,    95,  -220,   256,   257,   254,  -220,  -220,  -220,   282,
    -220,  -220,  -220,  -220,    71,   283,  -220,   286,  -220,   218,
     291,  -220,   218,   100,   263,  -220,  -220,  -220,  -220,   258,
    -220,  -220,    16,  -220,  -220,   260,  -220,   143,   170,  -220,
    -220,   261,  -220,   123,  -220,  -220,   264,   266,  -220,   296,
    -220,   297,  -220,   100,  -220,  -220,  -220,  -220,  -220,    25,
      25,  -220,  -220,   268,  -220,  -220,  -220,  -220,   267,   267,
      25,   269,   267,  -220,    25,    25,  -220,   113,  -220
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -220,  -220,   146,  -220,  -220,  -220,    45,  -220,    96,  -220,
    -220,  -220,  -220,  -220,  -220,  -220,  -220,  -220,  -220,  -141,
    -220,  -220,  -220,  -220,  -220,  -220,  -220,  -220,  -220,  -220,
    -220,    55,  -220,   214,  -220,  -220,     2,  -120,  -220,   285,
    -220,  -220,  -220,  -220,  -220,   -63,  -220,  -220,  -220,  -220,
    -220,  -220,  -220,  -220,    92,    13,   189,  -220,  -220,  -220,
    -220,  -220,  -220,  -220,  -220,  -220,  -220,  -220,  -220,  -173,
    -219,  -220,  -220,  -220,  -220,    85,  -220,  -220,  -220,  -220,
    -220,  -220,  -220,  -220,  -220,  -220,  -220,    84,  -220,  -220,
    -220,  -220,  -220,  -220,    35,  -220,  -220,  -220,   224,   271,
    -220,  -176,  -220,  -220,  -220,   -65
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -179
static const yytype_int16 yytable[] =
{
     112,   115,   157,   236,   272,   117,   163,   192,   194,    91,
      69,    94,    70,   204,    71,   305,   140,   173,    70,   158,
      71,    23,    37,   128,  -136,   225,    72,   158,   164,   129,
     144,    73,    74,   195,    64,   196,   153,    73,    74,   180,
     226,    75,   165,   166,   142,   174,   288,    75,    76,    29,
     141,    92,   227,    77,    78,    95,   225,   306,    38,   156,
     160,   146,   291,    39,   255,   159,   276,   144,   160,    54,
      65,   226,   -70,   -70,    96,   181,    97,   289,   -26,   145,
     189,   190,   191,   227,    98,    99,   -36,   100,    55,    56,
     256,   101,   182,   292,   -61,   308,   199,    19,   146,   183,
     200,   270,   147,   106,   107,   108,    30,    41,   230,   231,
    -178,   314,   297,   298,   242,   107,   108,    44,   300,   301,
      46,   244,   247,   303,   304,   346,    96,   105,    97,   106,
     107,   108,    48,   120,   109,    50,    98,    99,   121,   100,
     245,   107,   108,   101,   223,   243,    70,    52,    71,   224,
     233,    96,   322,    97,   223,   234,   338,   339,    60,   348,
     109,    98,    99,   332,   100,    73,    74,   342,   101,   124,
     125,   246,   347,    63,    96,    75,    97,   251,   287,   252,
      61,   290,   337,    -2,     1,    93,   251,   270,   282,     2,
       3,     4,     5,     6,     7,     8,   -14,     1,   124,   125,
     206,   207,     2,     3,     4,     5,     6,     7,     8,    -3,
       1,   251,    66,   328,   104,     2,     3,     4,     5,     6,
       7,     8,   107,   108,   319,    67,   113,   321,   114,   107,
     108,   148,   149,   186,   187,   202,   203,   213,   214,   216,
     217,   249,   250,   116,   119,   118,   134,   130,   131,   136,
     139,   178,   152,   135,   138,   150,   177,   184,   185,   169,
     205,   218,   211,   219,   232,   221,   220,   239,   235,   237,
     240,   222,   241,   248,   258,   267,   257,   273,   275,   274,
     279,   281,   285,   296,   286,   -65,   311,   312,   317,   318,
     302,   307,   309,   310,   320,   323,   333,   331,   324,   335,
     336,   299,   208,   326,   341,   295,   334,   132,   223,   327,
      40,   266,   162,   277,   343,   325,     0,   278,   313,     0,
       0,     0,     0,   137,     0,     0,     0,     0,     0,     0,
       0,     0,   103
};

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-220)))

#define yytable_value_is_error(Yytable_value) \
  YYID (0)

static const yytype_int16 yycheck[] =
{
      65,    66,   122,   179,   223,    68,   126,   148,   149,     1,
       1,     1,     3,   154,     5,     1,     5,     5,     3,     3,
       5,     3,     1,    39,    32,     5,    17,     3,     3,    45,
       3,    22,    23,     1,     1,     3,    44,    22,    23,     3,
      20,    32,    17,    18,   109,    33,     3,    32,    39,     0,
      39,    43,    32,    44,    45,    45,     5,    43,    37,    44,
      44,    34,     3,    42,   205,    41,    46,     3,    44,     3,
      37,    20,    40,    41,     3,    39,     5,    34,     3,    15,
     145,   146,   147,    32,    13,    14,     3,    16,    22,    23,
     210,    20,    32,    34,     3,   271,     1,     1,    34,    39,
       5,   221,    38,     3,     4,     5,    10,     3,   171,   172,
       3,    40,   253,   254,     3,     4,     5,     5,   259,   260,
       3,   186,   187,   264,   265,   344,     3,     1,     5,     3,
       4,     5,     3,    35,    34,     3,    13,    14,    40,    16,
       3,     4,     5,    20,    41,    34,     3,    37,     5,    46,
      41,     3,   293,     5,    41,    46,   329,   330,    37,    46,
      34,    13,    14,    40,    16,    22,    23,   340,    20,    31,
      32,    34,   345,    32,     3,    32,     5,    41,   243,    43,
       3,   246,   323,     0,     1,    41,    41,   307,    43,     6,
       7,     8,     9,    10,    11,    12,     0,     1,    31,    32,
      33,    34,     6,     7,     8,     9,    10,    11,    12,     0,
       1,    41,    37,    43,    36,     6,     7,     8,     9,    10,
      11,    12,     4,     5,   289,    37,     1,   292,     3,     4,
       5,    31,    32,    31,    32,    31,    32,    31,    32,    31,
      32,    40,    41,     5,     5,    42,    48,    37,    37,     3,
      37,     3,    35,    48,    42,    39,     5,     5,     3,    40,
      32,    40,    36,    41,     5,    42,    39,     5,    48,    39,
       5,    42,    40,     3,    40,    40,    36,    32,     5,    32,
      47,     5,    39,     5,    40,    32,    32,     5,     5,     3,
      41,    41,    36,    36,     3,    32,    32,    36,    40,     3,
       3,   256,   156,    43,    36,   250,    40,    93,    41,   307,
      25,   219,   123,   228,    45,   302,    -1,   233,   283,    -1,
      -1,    -1,    -1,    99,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    61
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     1,     6,     7,     8,     9,    10,    11,    12,    50,
      56,    57,    58,    63,    72,    87,   130,   137,   151,    57,
      59,    64,    73,     3,    88,    89,   131,   138,   152,     0,
      57,    60,    61,    65,    66,    74,    75,     1,    37,    42,
      88,     3,   132,   139,     5,   153,     3,    62,     3,    67,
       3,    76,    37,    90,     3,    22,    23,    81,    82,    83,
      37,     3,   140,    32,     1,    37,    37,    37,    93,     1,
       3,     5,    17,    22,    23,    32,    39,    44,    45,    86,
      94,    95,    96,    97,    98,    99,   110,   113,   116,   121,
     128,     1,    43,    41,     1,    45,     3,     5,    13,    14,
      16,    20,   147,   148,    36,     1,     3,     4,     5,    34,
      68,    71,   154,     1,     3,   154,     5,    94,    42,     5,
      35,    40,    54,   100,    31,    32,    51,   117,    39,    45,
      37,    37,    82,   133,    48,    48,     3,   147,    42,    37,
       5,    39,   154,    69,     3,    15,    34,    38,    31,    32,
      39,   129,    35,    44,   111,   112,    44,    86,     3,    41,
      44,   101,   105,    86,     3,    17,    18,   118,   119,    40,
     122,    92,    91,     5,    33,   135,   136,     5,     3,   149,
       3,    39,    32,    39,     5,     3,    31,    32,    70,   154,
     154,   154,    68,   154,    68,     1,     3,    79,    80,     1,
       5,   150,    31,    32,    68,    32,    33,    34,    51,    52,
      53,    36,    55,    31,    32,   102,    31,    32,    40,    41,
      39,    42,    42,    41,    46,     5,    20,    32,   123,   124,
      94,    94,     5,    41,    46,    48,   150,    39,   141,     5,
       5,    40,     3,    34,   154,     3,    34,   154,     3,    40,
      41,    41,    43,   114,   115,    68,    86,    36,    40,   106,
     108,   103,   104,   105,   107,   109,   103,    40,    84,    85,
      86,   120,   119,    32,    32,     5,    46,   124,   136,    47,
     134,     5,    43,   142,   143,    39,    40,   154,     3,    34,
     154,     3,    34,    77,    78,    80,     5,    68,    68,    55,
      68,    68,    41,    68,    68,     1,    43,    41,   150,    36,
      36,    32,     5,   143,    40,   144,   148,     5,     3,   154,
       3,   154,    68,    32,    40,   104,    43,    85,    43,   125,
     127,    36,    40,    32,    40,     3,     3,    68,   118,   118,
     126,    36,   118,    45,   146,   145,   119,   118,    46
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
        case 4:
/* Line 1787 of yacc.c  */
#line 170 "../../../mutabor-git/src/kernel/mut.yy"
    { (yyval.integer) = '+' ; }
    break;

  case 5:
/* Line 1787 of yacc.c  */
#line 171 "../../../mutabor-git/src/kernel/mut.yy"
    { (yyval.integer) = '-' ; }
    break;

  case 6:
/* Line 1787 of yacc.c  */
#line 175 "../../../mutabor-git/src/kernel/mut.yy"
    { (yyval.integer) = '*' ; }
    break;

  case 7:
/* Line 1787 of yacc.c  */
#line 176 "../../../mutabor-git/src/kernel/mut.yy"
    { (yyval.integer) = '/' ; }
    break;

  case 8:
/* Line 1787 of yacc.c  */
#line 180 "../../../mutabor-git/src/kernel/mut.yy"
    { (yyval.integer) = (yyvsp[(1) - (1)].integer); }
    break;

  case 9:
/* Line 1787 of yacc.c  */
#line 181 "../../../mutabor-git/src/kernel/mut.yy"
    { (yyval.integer) = (yyvsp[(1) - (1)].integer); }
    break;

  case 22:
/* Line 1787 of yacc.c  */
#line 199 "../../../mutabor-git/src/kernel/mut.yy"
    {  mutabor_error_message(box,
		compiler_error,
		_("Syntax error in line %d."),
		FEHLERZEILE); 
		}
    break;

  case 26:
/* Line 1787 of yacc.c  */
#line 215 "../../../mutabor-git/src/kernel/mut.yy"
    { init_komplex_ton_list (box); }
    break;

  case 28:
/* Line 1787 of yacc.c  */
#line 220 "../../../mutabor-git/src/kernel/mut.yy"
    { if ( fabs((yyvsp[(5) - (5)].f_value)) > 0.001 )
				    get_new_intervall (box, (yyvsp[(1) - (5)].identifier), (yyvsp[(3) - (5)].f_value) / (yyvsp[(5) - (5)].f_value));
                      else
			      mutabor_error_message (box,compiler_error,
					   _("Bad interval value in %s"),
					   ((yyvsp[(1) - (5)].identifier)) ); }
    break;

  case 29:
/* Line 1787 of yacc.c  */
#line 228 "../../../mutabor-git/src/kernel/mut.yy"
    { if ( fabs ((yyvsp[(3) - (5)].f_value)) > 0.001 )
				    get_new_intervall (box, (yyvsp[(1) - (5)].identifier), pow ((yyvsp[(5) - (5)].f_value), 1 / (yyvsp[(3) - (5)].f_value)));
                      else
			      mutabor_error_message (box,compiler_error,
						     _("Bad interval value in %s"),
						     ((yyvsp[(1) - (5)].identifier))); }
    break;

  case 30:
/* Line 1787 of yacc.c  */
#line 239 "../../../mutabor-git/src/kernel/mut.yy"
    { get_new_intervall_komplex (box,(yyvsp[(1) - (3)].identifier)); }
    break;

  case 31:
/* Line 1787 of yacc.c  */
#line 240 "../../../mutabor-git/src/kernel/mut.yy"
    { 
		  mutabor_error_message(box,
		                        compiler_error,
		                        _("Bad interval declaration of intervall %s in line %d."),
				        ((yyvsp[(1) - (3)].identifier)),
				        FEHLERZEILE); 
		}
    break;

  case 32:
/* Line 1787 of yacc.c  */
#line 247 "../../../mutabor-git/src/kernel/mut.yy"
    { 
		mutabor_error_message(box,
				      compiler_error,
				      _("Wrong character. Expecting %s in line %d."),
				      mutT("="),FEHLERZEILE); 
	  }
    break;

  case 36:
/* Line 1787 of yacc.c  */
#line 264 "../../../mutabor-git/src/kernel/mut.yy"
    { init_komplex_ton_list (box); }
    break;

  case 38:
/* Line 1787 of yacc.c  */
#line 269 "../../../mutabor-git/src/kernel/mut.yy"
    { get_new_ton_absolut (box, (yyvsp[(1) - (3)].identifier), (yyvsp[(3) - (3)].f_value)); }
    break;

  case 39:
/* Line 1787 of yacc.c  */
#line 273 "../../../mutabor-git/src/kernel/mut.yy"
    { get_new_ton_komplex_negative (box, (yyvsp[(1) - (5)].identifier), (yyvsp[(3) - (5)].identifier)); }
    break;

  case 40:
/* Line 1787 of yacc.c  */
#line 277 "../../../mutabor-git/src/kernel/mut.yy"
    { get_new_ton_komplex_positive (box, (yyvsp[(1) - (3)].identifier), (yyvsp[(3) - (3)].identifier)); }
    break;

  case 41:
/* Line 1787 of yacc.c  */
#line 281 "../../../mutabor-git/src/kernel/mut.yy"
    { get_new_ton_komplex_positive (box, (yyvsp[(1) - (5)].identifier), (yyvsp[(3) - (5)].identifier)); }
    break;

  case 42:
/* Line 1787 of yacc.c  */
#line 283 "../../../mutabor-git/src/kernel/mut.yy"
    { 
	      mutabor_error_message(box,
				    compiler_error,
				    _("Bad tone declaration of tone %s in line %d."),
				    ((yyvsp[(1) - (3)].identifier)),
				    FEHLERZEILE); 
	}
    break;

  case 46:
/* Line 1787 of yacc.c  */
#line 303 "../../../mutabor-git/src/kernel/mut.yy"
    { get_new_faktor_anteil ( box, (double) 1, (yyvsp[(2) - (2)].identifier)); }
    break;

  case 47:
/* Line 1787 of yacc.c  */
#line 306 "../../../mutabor-git/src/kernel/mut.yy"
    { get_new_faktor_anteil ( box,  (double) -1, (yyvsp[(2) - (2)].identifier)); }
    break;

  case 48:
/* Line 1787 of yacc.c  */
#line 309 "../../../mutabor-git/src/kernel/mut.yy"
    { get_new_faktor_anteil (box, (yyvsp[(2) - (3)].f_value), (yyvsp[(3) - (3)].identifier)); }
    break;

  case 49:
/* Line 1787 of yacc.c  */
#line 312 "../../../mutabor-git/src/kernel/mut.yy"
    { get_new_faktor_anteil (box, -((yyvsp[(2) - (3)].f_value)), (yyvsp[(3) - (3)].identifier)); }
    break;

  case 50:
/* Line 1787 of yacc.c  */
#line 315 "../../../mutabor-git/src/kernel/mut.yy"
    { if ( fabs((yyvsp[(3) - (4)].f_value)) > 0.001 )
				   get_new_faktor_anteil (box, (double) 1 / ((yyvsp[(3) - (4)].f_value)), (yyvsp[(4) - (4)].identifier));
			   else
				   mutabor_error_message(box,
							 compiler_error,
							 _("Division by (nearly) 0 in line %d."),
							 FEHLERZEILE);  
		   }
    break;

  case 51:
/* Line 1787 of yacc.c  */
#line 325 "../../../mutabor-git/src/kernel/mut.yy"
    { if ( fabs((yyvsp[(3) - (4)].f_value)) > 0.001 )
				   get_new_faktor_anteil (box, (double) -1 / ((yyvsp[(3) - (4)].f_value)), (yyvsp[(4) - (4)].identifier));
                     else
				   mutabor_error_message(box,
							 compiler_error,
							 _("Division by (nearly) 0 in line %d."),
							 FEHLERZEILE);  
		   }
    break;

  case 52:
/* Line 1787 of yacc.c  */
#line 335 "../../../mutabor-git/src/kernel/mut.yy"
    { if ( fabs((yyvsp[(4) - (5)].f_value)) > 0.001 )
				   get_new_faktor_anteil (box, ((yyvsp[(2) - (5)].f_value)) / ((yyvsp[(4) - (5)].f_value)), (yyvsp[(5) - (5)].identifier));
                     else
			     mutabor_error_message(box,
						   compiler_error,
						   _("Division by (nearly) 0 in line %d."),
						   FEHLERZEILE);  
		   }
    break;

  case 53:
/* Line 1787 of yacc.c  */
#line 345 "../../../mutabor-git/src/kernel/mut.yy"
    { if ( fabs((yyvsp[(4) - (5)].f_value)) > 0.001 )
				   get_new_faktor_anteil (box, -((yyvsp[(2) - (5)].f_value)) / ((yyvsp[(4) - (5)].f_value)), (yyvsp[(5) - (5)].identifier));
                     else
			     mutabor_error_message(box,
						   compiler_error,
						   _("Division by (nearly) 0 in line %d."),
						   FEHLERZEILE);  
		   }
    break;

  case 54:
/* Line 1787 of yacc.c  */
#line 370 "../../../mutabor-git/src/kernel/mut.yy"
    { get_new_faktor_anteil (box, (double) 1.0 , (yyvsp[(1) - (1)].identifier)); }
    break;

  case 55:
/* Line 1787 of yacc.c  */
#line 378 "../../../mutabor-git/src/kernel/mut.yy"
    { get_new_faktor_anteil (box, (yyvsp[(1) - (2)].f_value), (yyvsp[(2) - (2)].identifier)); }
    break;

  case 56:
/* Line 1787 of yacc.c  */
#line 381 "../../../mutabor-git/src/kernel/mut.yy"
    { if ( fabs((yyvsp[(2) - (3)].f_value)) > 0.001 )
				   get_new_faktor_anteil (box, (double) 1 / ((yyvsp[(2) - (3)].f_value)), (yyvsp[(3) - (3)].identifier));
                     else
			     mutabor_error_message(box,
						   compiler_error,
						   _("Division by (nearly) 0 in line %d."),
						   FEHLERZEILE);  
		   }
    break;

  case 57:
/* Line 1787 of yacc.c  */
#line 391 "../../../mutabor-git/src/kernel/mut.yy"
    { if ( fabs((yyvsp[(3) - (4)].f_value)) > 0.001 )
				   get_new_faktor_anteil (box, ((yyvsp[(1) - (4)].f_value)) / ((yyvsp[(3) - (4)].f_value)), (yyvsp[(4) - (4)].identifier));
                     else
			     mutabor_error_message(box,
						   compiler_error,
						   _("Division by (nearly) 0 in line %d."),
						   FEHLERZEILE);  
		   }
    break;

  case 61:
/* Line 1787 of yacc.c  */
#line 428 "../../../mutabor-git/src/kernel/mut.yy"
    { init_ton_liste (box); }
    break;

  case 63:
/* Line 1787 of yacc.c  */
#line 433 "../../../mutabor-git/src/kernel/mut.yy"
    { init_komplex_ton_list (box); }
    break;

  case 64:
/* Line 1787 of yacc.c  */
#line 435 "../../../mutabor-git/src/kernel/mut.yy"
    { get_new_tonsystem (box, (yyvsp[(1) - (8)].identifier), (yyvsp[(3) - (8)].integer)); }
    break;

  case 65:
/* Line 1787 of yacc.c  */
#line 437 "../../../mutabor-git/src/kernel/mut.yy"
    { init_komplex_ton_list (box); }
    break;

  case 66:
/* Line 1787 of yacc.c  */
#line 439 "../../../mutabor-git/src/kernel/mut.yy"
    { get_new_tonsystem_negative (box, (yyvsp[(1) - (9)].identifier), (yyvsp[(3) - (9)].integer)); }
    break;

  case 69:
/* Line 1787 of yacc.c  */
#line 445 "../../../mutabor-git/src/kernel/mut.yy"
    { get_new_ton_in_tonsystem (box, (yyvsp[(1) - (1)].identifier)); }
    break;

  case 70:
/* Line 1787 of yacc.c  */
#line 446 "../../../mutabor-git/src/kernel/mut.yy"
    { get_new_ton_in_tonsystem (box, NULL); }
    break;

  case 71:
/* Line 1787 of yacc.c  */
#line 447 "../../../mutabor-git/src/kernel/mut.yy"
    {     mutabor_error_message(box,
		compiler_error,
		_("Bad tonesystem declaration in line %d."),		      
		FEHLERZEILE);
		}
    break;

  case 72:
/* Line 1787 of yacc.c  */
#line 455 "../../../mutabor-git/src/kernel/mut.yy"
    { (yyval.parameters) = NULL; }
    break;

  case 73:
/* Line 1787 of yacc.c  */
#line 456 "../../../mutabor-git/src/kernel/mut.yy"
    { (yyval.parameters) = (yyvsp[(1) - (1)].parameters); 
                    enumerate_parameters(box,(yyval.parameters));
		}
    break;

  case 75:
/* Line 1787 of yacc.c  */
#line 464 "../../../mutabor-git/src/kernel/mut.yy"
    {
		    if ((yyvsp[(1) - (3)].parameters) != NULL) {
			(yyval.parameters) = (yyvsp[(1) - (3)].parameters);
		        (yyval.parameters)->next = (yyvsp[(3) - (3)].parameters);
   		    } else {(yyval.parameters) = (yyvsp[(3) - (3)].parameters);}
		}
    break;

  case 76:
/* Line 1787 of yacc.c  */
#line 474 "../../../mutabor-git/src/kernel/mut.yy"
    { 
			(yyval.parameters) = get_new_name_in_parameterlist (box, (yyvsp[(1) - (1)].identifier)); 
		}
    break;

  case 77:
/* Line 1787 of yacc.c  */
#line 477 "../../../mutabor-git/src/kernel/mut.yy"
    { 
		    (yyval.parameters) = NULL;
		    mutabor_error_message(box,
					  compiler_warning,
		                          _("Arguments named “DISTANCE” or “ABSTAND” have a fixed meaning. Using them as parameters as in line %d is not supported. Expect undexpected behaviour."),
		                          FEHLERZEILE);
		}
    break;

  case 78:
/* Line 1787 of yacc.c  */
#line 484 "../../../mutabor-git/src/kernel/mut.yy"
    { 
			(yyval.parameters) = NULL;
		        mutabor_error_message(box,
					  compiler_warning,
		                          _("Arguments named “DISTANCE” or “ABSTAND” have a fixed meaning. Using them as parameters as in line %d is not supported. Expect undexpected behaviour."),
 		                          FEHLERZEILE);
		}
    break;

  case 79:
/* Line 1787 of yacc.c  */
#line 504 "../../../mutabor-git/src/kernel/mut.yy"
    { (yyval.arguments) = NULL; }
    break;

  case 80:
/* Line 1787 of yacc.c  */
#line 505 "../../../mutabor-git/src/kernel/mut.yy"
    { 
			(yyval.arguments) = (yyvsp[(1) - (1)].arguments); 
		}
    break;

  case 81:
/* Line 1787 of yacc.c  */
#line 511 "../../../mutabor-git/src/kernel/mut.yy"
    { 
			(yyval.arguments) = (yyvsp[(1) - (1)].arguments); 
		}
    break;

  case 82:
/* Line 1787 of yacc.c  */
#line 514 "../../../mutabor-git/src/kernel/mut.yy"
    { 
			(yyval.arguments) = (yyvsp[(1) - (3)].arguments); 
		        (yyvsp[(1) - (3)].arguments)->next = (yyvsp[(3) - (3)].arguments);
		}
    break;

  case 83:
/* Line 1787 of yacc.c  */
#line 531 "../../../mutabor-git/src/kernel/mut.yy"
    { (yyval.arguments) = get_new_name_in_argument_list (box, (yyvsp[(1) - (1)].identifier)) ;  }
    break;

  case 84:
/* Line 1787 of yacc.c  */
#line 533 "../../../mutabor-git/src/kernel/mut.yy"
    { (yyval.arguments) = get_new_number_in_argument_list (box, (yyvsp[(1) - (1)].integer)) ;  }
    break;

  case 85:
/* Line 1787 of yacc.c  */
#line 535 "../../../mutabor-git/src/kernel/mut.yy"
    { (yyval.arguments) = get_new_number_in_argument_list (box, -((yyvsp[(2) - (2)].integer))); }
    break;

  case 86:
/* Line 1787 of yacc.c  */
#line 537 "../../../mutabor-git/src/kernel/mut.yy"
    { (yyval.arguments) = get_new_distance_in_argument_list (box); }
    break;

  case 87:
/* Line 1787 of yacc.c  */
#line 539 "../../../mutabor-git/src/kernel/mut.yy"
    { (yyval.arguments) = get_new_anchor_in_argument_list (box); }
    break;

  case 91:
/* Line 1787 of yacc.c  */
#line 554 "../../../mutabor-git/src/kernel/mut.yy"
    { 
			init_umstimmung (box, (yyvsp[(1) - (2)].identifier)); 
		eintrage_parameterliste_in_umstimmung (box, 
                                                       box->file->tmp_umstimmung,
 		                                       NULL);  
		}
    break;

  case 92:
/* Line 1787 of yacc.c  */
#line 560 "../../../mutabor-git/src/kernel/mut.yy"
    { 
			get_new_umstimmung (box); 
		}
    break;

  case 93:
/* Line 1787 of yacc.c  */
#line 565 "../../../mutabor-git/src/kernel/mut.yy"
    {
			init_umstimmung (box,(yyvsp[(1) - (5)].identifier)); 
		        eintrage_parameterliste_in_umstimmung (box, 
                                                       box->file->tmp_umstimmung,
 		                                       (yyvsp[(3) - (5)].parameters)); 
		}
    break;

  case 94:
/* Line 1787 of yacc.c  */
#line 570 "../../../mutabor-git/src/kernel/mut.yy"
    { 
			get_new_umstimmung (box); 
		}
    break;

  case 95:
/* Line 1787 of yacc.c  */
#line 575 "../../../mutabor-git/src/kernel/mut.yy"
    { 
			init_umstimmung (box,(yyvsp[(1) - (5)].identifier));
		        eintrage_parameterliste_in_umstimmung (box, 
                                                       box->file->tmp_umstimmung,
 		                                       (yyvsp[(3) - (5)].parameters));
		        mutabor_error_message(box,
		                              compiler_error,
		                              _("Invalid parameter list in retuning %s line %d"),
		                              (yyvsp[(1) - (5)].identifier), FEHLERZEILE); 
		}
    break;

  case 96:
/* Line 1787 of yacc.c  */
#line 584 "../../../mutabor-git/src/kernel/mut.yy"
    { 
			get_new_umstimmung (box); 
		}
    break;

  case 97:
/* Line 1787 of yacc.c  */
#line 588 "../../../mutabor-git/src/kernel/mut.yy"
    {
			init_umstimmung (box,(yyvsp[(1) - (3)].identifier)); 
		        eintrage_parameterliste_in_umstimmung (box, 
                                                       box->file->tmp_umstimmung,
 		                                       NULL);
		        mutabor_error_message(box,
		                              compiler_error,
		                              _("Error while reading %s line %d"),
                               		      (yyvsp[(1) - (3)].identifier), FEHLERZEILE); 
		}
    break;

  case 98:
/* Line 1787 of yacc.c  */
#line 598 "../../../mutabor-git/src/kernel/mut.yy"
    { get_new_umstimmung (box); }
    break;

  case 99:
/* Line 1787 of yacc.c  */
#line 602 "../../../mutabor-git/src/kernel/mut.yy"
    {}
    break;

  case 100:
/* Line 1787 of yacc.c  */
#line 603 "../../../mutabor-git/src/kernel/mut.yy"
    {}
    break;

  case 101:
/* Line 1787 of yacc.c  */
#line 604 "../../../mutabor-git/src/kernel/mut.yy"
    {}
    break;

  case 102:
/* Line 1787 of yacc.c  */
#line 605 "../../../mutabor-git/src/kernel/mut.yy"
    {}
    break;

  case 103:
/* Line 1787 of yacc.c  */
#line 606 "../../../mutabor-git/src/kernel/mut.yy"
    {}
    break;

  case 104:
/* Line 1787 of yacc.c  */
#line 607 "../../../mutabor-git/src/kernel/mut.yy"
    {}
    break;

  case 105:
/* Line 1787 of yacc.c  */
#line 608 "../../../mutabor-git/src/kernel/mut.yy"
    {}
    break;

  case 106:
/* Line 1787 of yacc.c  */
#line 609 "../../../mutabor-git/src/kernel/mut.yy"
    {}
    break;

  case 107:
/* Line 1787 of yacc.c  */
#line 610 "../../../mutabor-git/src/kernel/mut.yy"
    {}
    break;

  case 108:
/* Line 1787 of yacc.c  */
#line 611 "../../../mutabor-git/src/kernel/mut.yy"
    {}
    break;

  case 109:
/* Line 1787 of yacc.c  */
#line 612 "../../../mutabor-git/src/kernel/mut.yy"
    {
		mutabor_error_message(box,
				      compiler_error,
				      _("Bad retuning in line %d."),
				      FEHLERZEILE);
	  }
    break;

  case 110:
/* Line 1787 of yacc.c  */
#line 623 "../../../mutabor-git/src/kernel/mut.yy"
    { get_umstimmung_taste_abs (box, (yyvsp[(1) - (3)].arguments)); }
    break;

  case 111:
/* Line 1787 of yacc.c  */
#line 628 "../../../mutabor-git/src/kernel/mut.yy"
    { get_umstimmung_taste_rel (box, (yyvsp[(3) - (5)].arguments), (yyvsp[(2) - (5)].integer)); }
    break;

  case 112:
/* Line 1787 of yacc.c  */
#line 633 "../../../mutabor-git/src/kernel/mut.yy"
    { get_umstimmung_breite_abs (box, (yyvsp[(3) - (5)].arguments)); }
    break;

  case 113:
/* Line 1787 of yacc.c  */
#line 638 "../../../mutabor-git/src/kernel/mut.yy"
    { get_umstimmung_breite_rel (box, (yyvsp[(5) - (7)].arguments), (yyvsp[(4) - (7)].integer)); }
    break;

  case 114:
/* Line 1787 of yacc.c  */
#line 643 "../../../mutabor-git/src/kernel/mut.yy"
    { init_umstimm_expression_list (box); }
    break;

  case 115:
/* Line 1787 of yacc.c  */
#line 645 "../../../mutabor-git/src/kernel/mut.yy"
    { get_umstimmung_tonhoehe_veraendert (box); }
    break;

  case 116:
/* Line 1787 of yacc.c  */
#line 652 "../../../mutabor-git/src/kernel/mut.yy"
    {}
    break;

  case 117:
/* Line 1787 of yacc.c  */
#line 653 "../../../mutabor-git/src/kernel/mut.yy"
    {}
    break;

  case 118:
/* Line 1787 of yacc.c  */
#line 655 "../../../mutabor-git/src/kernel/mut.yy"
    { init_komplex_ton_list(box);
		  get_new_umstimm_expression (box,NULL);
                   }
    break;

  case 119:
/* Line 1787 of yacc.c  */
#line 658 "../../../mutabor-git/src/kernel/mut.yy"
    {}
    break;

  case 120:
/* Line 1787 of yacc.c  */
#line 662 "../../../mutabor-git/src/kernel/mut.yy"
    {}
    break;

  case 121:
/* Line 1787 of yacc.c  */
#line 663 "../../../mutabor-git/src/kernel/mut.yy"
    {}
    break;

  case 122:
/* Line 1787 of yacc.c  */
#line 668 "../../../mutabor-git/src/kernel/mut.yy"
    { init_komplex_ton_list(box);
		  get_new_umstimm_expression (box, NULL);
                   }
    break;

  case 124:
/* Line 1787 of yacc.c  */
#line 676 "../../../mutabor-git/src/kernel/mut.yy"
    { get_new_umstimm_expression (box,(yyvsp[(1) - (1)].identifier)); }
    break;

  case 125:
/* Line 1787 of yacc.c  */
#line 677 "../../../mutabor-git/src/kernel/mut.yy"
    { get_new_umstimm_expression (box, "@"); }
    break;

  case 126:
/* Line 1787 of yacc.c  */
#line 679 "../../../mutabor-git/src/kernel/mut.yy"
    { init_komplex_ton_list (box); }
    break;

  case 127:
/* Line 1787 of yacc.c  */
#line 681 "../../../mutabor-git/src/kernel/mut.yy"
    { get_new_umstimm_expression_positive (box, (yyvsp[(1) - (4)].identifier)); }
    break;

  case 128:
/* Line 1787 of yacc.c  */
#line 682 "../../../mutabor-git/src/kernel/mut.yy"
    { init_komplex_ton_list (box); }
    break;

  case 129:
/* Line 1787 of yacc.c  */
#line 684 "../../../mutabor-git/src/kernel/mut.yy"
    { get_new_umstimm_expression_positive (box, "@" ); }
    break;

  case 130:
/* Line 1787 of yacc.c  */
#line 685 "../../../mutabor-git/src/kernel/mut.yy"
    { init_komplex_ton_list (box); }
    break;

  case 131:
/* Line 1787 of yacc.c  */
#line 687 "../../../mutabor-git/src/kernel/mut.yy"
    { get_new_umstimm_expression_negative (box,(yyvsp[(1) - (4)].identifier)); }
    break;

  case 132:
/* Line 1787 of yacc.c  */
#line 688 "../../../mutabor-git/src/kernel/mut.yy"
    { init_komplex_ton_list (box); }
    break;

  case 133:
/* Line 1787 of yacc.c  */
#line 690 "../../../mutabor-git/src/kernel/mut.yy"
    { get_new_umstimm_expression_negative (box, "@" ); }
    break;

  case 134:
/* Line 1787 of yacc.c  */
#line 695 "../../../mutabor-git/src/kernel/mut.yy"
    { init_komplex_ton_list (box); }
    break;

  case 135:
/* Line 1787 of yacc.c  */
#line 697 "../../../mutabor-git/src/kernel/mut.yy"
    { get_umstimmung_wiederholung_abs (box); }
    break;

  case 136:
/* Line 1787 of yacc.c  */
#line 698 "../../../mutabor-git/src/kernel/mut.yy"
    { init_komplex_ton_list (box); }
    break;

  case 137:
/* Line 1787 of yacc.c  */
#line 700 "../../../mutabor-git/src/kernel/mut.yy"
    { get_umstimmung_wiederholung_abs_negative (box); }
    break;

  case 138:
/* Line 1787 of yacc.c  */
#line 704 "../../../mutabor-git/src/kernel/mut.yy"
    { init_komplex_ton_list (box); }
    break;

  case 139:
/* Line 1787 of yacc.c  */
#line 706 "../../../mutabor-git/src/kernel/mut.yy"
    { get_umstimmung_wiederholung_rel_positive (box); }
    break;

  case 140:
/* Line 1787 of yacc.c  */
#line 707 "../../../mutabor-git/src/kernel/mut.yy"
    { init_komplex_ton_list (box); }
    break;

  case 141:
/* Line 1787 of yacc.c  */
#line 709 "../../../mutabor-git/src/kernel/mut.yy"
    { get_umstimmung_wiederholung_rel_negative (box); }
    break;

  case 142:
/* Line 1787 of yacc.c  */
#line 713 "../../../mutabor-git/src/kernel/mut.yy"
    { init_aktions_liste (box); }
    break;

  case 143:
/* Line 1787 of yacc.c  */
#line 715 "../../../mutabor-git/src/kernel/mut.yy"
    { get_umstimmung_umstimmungs_bund (box); }
    break;

  case 144:
/* Line 1787 of yacc.c  */
#line 719 "../../../mutabor-git/src/kernel/mut.yy"
    {}
    break;

  case 145:
/* Line 1787 of yacc.c  */
#line 720 "../../../mutabor-git/src/kernel/mut.yy"
    {}
    break;

  case 146:
/* Line 1787 of yacc.c  */
#line 724 "../../../mutabor-git/src/kernel/mut.yy"
    { 
		  get_new_aktion_aufruf_element (box,(yyvsp[(1) - (1)].identifier),NULL); 
	  }
    break;

  case 147:
/* Line 1787 of yacc.c  */
#line 728 "../../../mutabor-git/src/kernel/mut.yy"
    { get_new_aktion_aufruf_element (box,(yyvsp[(1) - (4)].identifier), (yyvsp[(3) - (4)].arguments)); }
    break;

  case 148:
/* Line 1787 of yacc.c  */
#line 730 "../../../mutabor-git/src/kernel/mut.yy"
    { get_new_aktion_aufruf_element (box,(yyvsp[(1) - (5)].identifier), (yyvsp[(3) - (5)].arguments));
			    mutabor_error_message(box,
						 compiler_error,
						 _("Invalid argument list for call to %s in line %d"),
						 (yyvsp[(1) - (5)].identifier),
						 FEHLERZEILE);
		    }
    break;

  case 149:
/* Line 1787 of yacc.c  */
#line 738 "../../../mutabor-git/src/kernel/mut.yy"
    { init_integersequenz (box);}
    break;

  case 150:
/* Line 1787 of yacc.c  */
#line 740 "../../../mutabor-git/src/kernel/mut.yy"
    { get_new_aktion_midi_out_element (box); }
    break;

  case 151:
/* Line 1787 of yacc.c  */
#line 741 "../../../mutabor-git/src/kernel/mut.yy"
    { get_new_aktion_harmony_analysis(box); }
    break;

  case 152:
/* Line 1787 of yacc.c  */
#line 745 "../../../mutabor-git/src/kernel/mut.yy"
    { init_umstimmungs_case_liste (box); }
    break;

  case 153:
/* Line 1787 of yacc.c  */
#line 747 "../../../mutabor-git/src/kernel/mut.yy"
    { get_umstimmung_umstimm_case (box,(yyvsp[(1) - (5)].arguments)); }
    break;

  case 154:
/* Line 1787 of yacc.c  */
#line 751 "../../../mutabor-git/src/kernel/mut.yy"
    {}
    break;

  case 155:
/* Line 1787 of yacc.c  */
#line 752 "../../../mutabor-git/src/kernel/mut.yy"
    {}
    break;

  case 156:
/* Line 1787 of yacc.c  */
#line 757 "../../../mutabor-git/src/kernel/mut.yy"
    { init_aktions_liste (box); }
    break;

  case 157:
/* Line 1787 of yacc.c  */
#line 759 "../../../mutabor-git/src/kernel/mut.yy"
    { get_umstimmungs_case_zahl_element (box,(yyvsp[(1) - (5)].integer)); }
    break;

  case 158:
/* Line 1787 of yacc.c  */
#line 761 "../../../mutabor-git/src/kernel/mut.yy"
    { init_aktions_liste (box); }
    break;

  case 159:
/* Line 1787 of yacc.c  */
#line 763 "../../../mutabor-git/src/kernel/mut.yy"
    { get_umstimmungs_case_zahl_element (box,-((yyvsp[(2) - (6)].integer))); }
    break;

  case 160:
/* Line 1787 of yacc.c  */
#line 765 "../../../mutabor-git/src/kernel/mut.yy"
    { init_aktions_liste (box); }
    break;

  case 161:
/* Line 1787 of yacc.c  */
#line 767 "../../../mutabor-git/src/kernel/mut.yy"
    { get_umstimmungs_case_default_element (box); }
    break;

  case 162:
/* Line 1787 of yacc.c  */
#line 772 "../../../mutabor-git/src/kernel/mut.yy"
    { init_integersequenz (box);}
    break;

  case 163:
/* Line 1787 of yacc.c  */
#line 774 "../../../mutabor-git/src/kernel/mut.yy"
    { get_umstimmung_midi_out (box); }
    break;

  case 164:
/* Line 1787 of yacc.c  */
#line 779 "../../../mutabor-git/src/kernel/mut.yy"
    {}
    break;

  case 165:
/* Line 1787 of yacc.c  */
#line 783 "../../../mutabor-git/src/kernel/mut.yy"
    {}
    break;

  case 166:
/* Line 1787 of yacc.c  */
#line 784 "../../../mutabor-git/src/kernel/mut.yy"
    {}
    break;

  case 167:
/* Line 1787 of yacc.c  */
#line 789 "../../../mutabor-git/src/kernel/mut.yy"
    { init_tastenliste (box); }
    break;

  case 168:
/* Line 1787 of yacc.c  */
#line 791 "../../../mutabor-git/src/kernel/mut.yy"
    { get_new_harmonie (box, (yyvsp[(1) - (7)].identifier), (yyvsp[(7) - (7)].integer)); }
    break;

  case 169:
/* Line 1787 of yacc.c  */
#line 793 "../../../mutabor-git/src/kernel/mut.yy"
    { 
		mutabor_error_message(box,
				      compiler_error,
				      _("Bad pattern declaration “%s” at line %d"),
				      ((yyvsp[(1) - (3)].identifier)),
				      FEHLERZEILE); 
	  }
    break;

  case 170:
/* Line 1787 of yacc.c  */
#line 803 "../../../mutabor-git/src/kernel/mut.yy"
    { (yyval.integer) = -1; }
    break;

  case 171:
/* Line 1787 of yacc.c  */
#line 804 "../../../mutabor-git/src/kernel/mut.yy"
    { (yyval.integer) = (yyvsp[(2) - (2)].integer); }
    break;

  case 172:
/* Line 1787 of yacc.c  */
#line 808 "../../../mutabor-git/src/kernel/mut.yy"
    {}
    break;

  case 173:
/* Line 1787 of yacc.c  */
#line 809 "../../../mutabor-git/src/kernel/mut.yy"
    {}
    break;

  case 174:
/* Line 1787 of yacc.c  */
#line 813 "../../../mutabor-git/src/kernel/mut.yy"
    { get_new_taste (box, (yyvsp[(1) - (1)].integer), '+'); }
    break;

  case 175:
/* Line 1787 of yacc.c  */
#line 814 "../../../mutabor-git/src/kernel/mut.yy"
    { get_new_taste (box, (yyvsp[(2) - (2)].integer), '*'); }
    break;

  case 176:
/* Line 1787 of yacc.c  */
#line 818 "../../../mutabor-git/src/kernel/mut.yy"
    {}
    break;

  case 177:
/* Line 1787 of yacc.c  */
#line 822 "../../../mutabor-git/src/kernel/mut.yy"
    {}
    break;

  case 178:
/* Line 1787 of yacc.c  */
#line 823 "../../../mutabor-git/src/kernel/mut.yy"
    { init_ausloeser (box);
                         /* f〉 die Anfangsausloesung der Logik */
                       }
    break;

  case 179:
/* Line 1787 of yacc.c  */
#line 826 "../../../mutabor-git/src/kernel/mut.yy"
    {}
    break;

  case 180:
/* Line 1787 of yacc.c  */
#line 831 "../../../mutabor-git/src/kernel/mut.yy"
    { get_new_logik (box, (yyvsp[(1) - (4)].identifier), NULL);
                init_anweisungs_liste (box); }
    break;

  case 181:
/* Line 1787 of yacc.c  */
#line 834 "../../../mutabor-git/src/kernel/mut.yy"
    { vervollstaendige_logik (box); }
    break;

  case 182:
/* Line 1787 of yacc.c  */
#line 836 "../../../mutabor-git/src/kernel/mut.yy"
    { get_new_logik (box, (yyvsp[(1) - (5)].identifier), (yyvsp[(4) - (5)].identifier));
                init_anweisungs_liste (box); }
    break;

  case 183:
/* Line 1787 of yacc.c  */
#line 839 "../../../mutabor-git/src/kernel/mut.yy"
    { vervollstaendige_logik (box); }
    break;

  case 184:
/* Line 1787 of yacc.c  */
#line 843 "../../../mutabor-git/src/kernel/mut.yy"
    {}
    break;

  case 185:
/* Line 1787 of yacc.c  */
#line 844 "../../../mutabor-git/src/kernel/mut.yy"
    {}
    break;

  case 186:
/* Line 1787 of yacc.c  */
#line 849 "../../../mutabor-git/src/kernel/mut.yy"
    { init_aktions_liste (box); }
    break;

  case 187:
/* Line 1787 of yacc.c  */
#line 851 "../../../mutabor-git/src/kernel/mut.yy"
    { get_new_anweisung (box); }
    break;

  case 188:
/* Line 1787 of yacc.c  */
#line 853 "../../../mutabor-git/src/kernel/mut.yy"
    { init_aktions_liste (box); }
    break;

  case 189:
/* Line 1787 of yacc.c  */
#line 855 "../../../mutabor-git/src/kernel/mut.yy"
    { get_new_anweisung (box); }
    break;

  case 190:
/* Line 1787 of yacc.c  */
#line 860 "../../../mutabor-git/src/kernel/mut.yy"
    { get_harmoniebezeichner (box, (yyvsp[(1) - (5)].integer), (yyvsp[(3) - (5)].identifier),  (yyvsp[(5) - (5)].integer)); }
    break;

  case 191:
/* Line 1787 of yacc.c  */
#line 862 "../../../mutabor-git/src/kernel/mut.yy"
    { get_harmoniebezeichner (box, MUTABOR_NO_KEY, (yyvsp[(1) - (3)].identifier),  (yyvsp[(3) - (3)].integer)); }
    break;

  case 192:
/* Line 1787 of yacc.c  */
#line 864 "../../../mutabor-git/src/kernel/mut.yy"
    { get_harmoniebezeichner (box, (yyvsp[(1) - (3)].integer), (yyvsp[(3) - (3)].identifier), MUTABOR_NO_KEY); }
    break;

  case 193:
/* Line 1787 of yacc.c  */
#line 866 "../../../mutabor-git/src/kernel/mut.yy"
    { get_harmoniebezeichner (box,  MUTABOR_NO_KEY, (yyvsp[(1) - (1)].identifier), MUTABOR_NO_KEY); }
    break;

  case 194:
/* Line 1787 of yacc.c  */
#line 870 "../../../mutabor-git/src/kernel/mut.yy"
    { get_ausloeser_default (box); }
    break;

  case 195:
/* Line 1787 of yacc.c  */
#line 871 "../../../mutabor-git/src/kernel/mut.yy"
    { get_ausloeser_harmonie (box); }
    break;

  case 196:
/* Line 1787 of yacc.c  */
#line 872 "../../../mutabor-git/src/kernel/mut.yy"
    { get_ausloeser_harmonie_form (box); }
    break;

  case 197:
/* Line 1787 of yacc.c  */
#line 873 "../../../mutabor-git/src/kernel/mut.yy"
    { get_ausloeser_taste (box,(yyvsp[(2) - (2)].identifier)); }
    break;

  case 198:
/* Line 1787 of yacc.c  */
#line 874 "../../../mutabor-git/src/kernel/mut.yy"
    { init_integersequenz (box); }
    break;

  case 199:
/* Line 1787 of yacc.c  */
#line 876 "../../../mutabor-git/src/kernel/mut.yy"
    { get_ausloeser_midi_in (box); }
    break;

  case 200:
/* Line 1787 of yacc.c  */
#line 881 "../../../mutabor-git/src/kernel/mut.yy"
    { get_new_integer_in_integersequenz (box,(yyvsp[(1) - (1)].integer));}
    break;

  case 201:
/* Line 1787 of yacc.c  */
#line 883 "../../../mutabor-git/src/kernel/mut.yy"
    { get_new_integer_in_integersequenz (box,(yyvsp[(3) - (3)].integer));}
    break;

  case 202:
/* Line 1787 of yacc.c  */
#line 884 "../../../mutabor-git/src/kernel/mut.yy"
    { 
		mutabor_error_message(box,
				      compiler_error,
				      _("Bad MIDI list in line %d"),  
				      FEHLERZEILE );
	  }
    break;

  case 203:
/* Line 1787 of yacc.c  */
#line 894 "../../../mutabor-git/src/kernel/mut.yy"
    {}
    break;

  case 204:
/* Line 1787 of yacc.c  */
#line 898 "../../../mutabor-git/src/kernel/mut.yy"
    {}
    break;

  case 205:
/* Line 1787 of yacc.c  */
#line 899 "../../../mutabor-git/src/kernel/mut.yy"
    {}
    break;

  case 206:
/* Line 1787 of yacc.c  */
#line 904 "../../../mutabor-git/src/kernel/mut.yy"
    { get_instrument_dekl (box, (yyvsp[(1) - (4)].integer), (yyvsp[(4) - (4)].integer), (yyvsp[(4) - (4)].integer), 0, & box->file->list_of_instrumente); }
    break;

  case 207:
/* Line 1787 of yacc.c  */
#line 906 "../../../mutabor-git/src/kernel/mut.yy"
    { get_instrument_dekl (box, (yyvsp[(1) - (6)].integer), (yyvsp[(4) - (6)].integer), (yyvsp[(6) - (6)].integer), 0, & box->file->list_of_instrumente); }
    break;

  case 208:
/* Line 1787 of yacc.c  */
#line 908 "../../../mutabor-git/src/kernel/mut.yy"
    { get_instrument_dekl (box, (yyvsp[(1) - (6)].integer), 0, 0, (yyvsp[(5) - (6)].integer), & box->file->list_of_instrumente); }
    break;

  case 209:
/* Line 1787 of yacc.c  */
#line 910 "../../../mutabor-git/src/kernel/mut.yy"
    { get_instrument_dekl (box, (yyvsp[(1) - (7)].integer), (yyvsp[(4) - (7)].integer), (yyvsp[(4) - (7)].integer), (yyvsp[(6) - (7)].integer), & box->file->list_of_instrumente); }
    break;

  case 210:
/* Line 1787 of yacc.c  */
#line 912 "../../../mutabor-git/src/kernel/mut.yy"
    { get_instrument_dekl (box, (yyvsp[(1) - (9)].integer), (yyvsp[(4) - (9)].integer), (yyvsp[(6) - (9)].integer), (yyvsp[(8) - (9)].integer), & box->file->list_of_instrumente); }
    break;

  case 211:
/* Line 1787 of yacc.c  */
#line 916 "../../../mutabor-git/src/kernel/mut.yy"
    { (yyval.f_value) = (yyvsp[(1) - (1)].f_value) ; }
    break;

  case 212:
/* Line 1787 of yacc.c  */
#line 917 "../../../mutabor-git/src/kernel/mut.yy"
    { (yyval.f_value) = (double) (yyvsp[(1) - (1)].integer) ; }
    break;


/* Line 1787 of yacc.c  */
#line 3191 "../../../mutabor-git/src/kernel/mut.cc"
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
#line 921 "../../../mutabor-git/src/kernel/mut.yy"

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
				      compiler_error,
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
{ "ABSTAND"    , MUTABOR_TOKEN_DISTANCE  },
{ "ZENTRUM"    , MUTABOR_TOKEN_ANCHOR  },
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
{ "DISTANCE"   , MUTABOR_TOKEN_DISTANCE  },
{ "CENTER"     , MUTABOR_TOKEN_ANCHOR  },
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
			  compiler_error,
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

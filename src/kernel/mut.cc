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
#line 144 "../../../mutabor-git/src/kernel/mut.yy"

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
#define YYLAST   392

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  49
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  104
/* YYNRULES -- Number of rules.  */
#define YYNRULES  220
/* YYNRULES -- Number of states.  */
#define YYNSTATES  396

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
      39,    40,    44,    34,    38,    33,    47,    35,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    32,     2,
      42,    31,    43,     2,    41,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    36,     2,    37,     2,     2,     2,     2,     2,     2,
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
       0,     0,     3,     4,     6,     8,    11,    12,    14,    16,
      18,    20,    22,    24,    26,    29,    32,    33,    36,    37,
      40,    46,    52,    56,    60,    63,    66,    67,    70,    71,
      74,    78,    84,    88,    94,    98,   101,   102,   105,   108,
     111,   115,   119,   124,   129,   135,   141,   143,   146,   150,
     155,   158,   159,   162,   163,   166,   167,   176,   177,   187,
     189,   193,   195,   196,   198,   199,   201,   203,   207,   209,
     211,   213,   214,   216,   218,   222,   224,   226,   229,   231,
     233,   236,   237,   240,   241,   242,   248,   249,   257,   258,
     266,   267,   268,   275,   277,   279,   281,   283,   285,   287,
     289,   291,   293,   295,   297,   301,   305,   311,   317,   323,
     329,   337,   345,   355,   365,   375,   385,   395,   405,   415,
     425,   426,   431,   433,   437,   438,   442,   444,   448,   449,
     451,   453,   455,   456,   461,   462,   467,   468,   473,   474,
     479,   480,   485,   486,   492,   493,   500,   501,   508,   509,
     514,   516,   520,   522,   527,   533,   534,   540,   542,   543,
     549,   550,   556,   558,   561,   562,   568,   569,   576,   577,
     583,   584,   590,   593,   594,   597,   598,   606,   610,   611,
     614,   616,   620,   622,   625,   628,   629,   630,   634,   635,
     643,   644,   653,   654,   657,   658,   666,   667,   673,   679,
     683,   687,   689,   691,   693,   696,   699,   700,   706,   708,
     712,   714,   717,   718,   721,   726,   733,   740,   748,   758,
     760
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
      50,     0,    -1,    -1,    51,    -1,    52,    -1,    51,    52,
      -1,    -1,    53,    -1,    58,    -1,    67,    -1,    82,    -1,
     128,    -1,   135,    -1,   149,    -1,     1,    52,    -1,     6,
      54,    -1,    -1,    54,    55,    -1,    -1,    56,    57,    -1,
       3,    31,   152,    32,   152,    -1,     3,    31,   152,    15,
     152,    -1,     3,    31,    63,    -1,     3,    31,     1,    -1,
       3,     1,    -1,     7,    59,    -1,    -1,    59,    60,    -1,
      -1,    61,    62,    -1,     3,    31,   152,    -1,     3,    31,
       3,    33,    63,    -1,     3,    31,     3,    -1,     3,    31,
       3,    34,    63,    -1,     3,    31,     1,    -1,    66,    64,
      -1,    -1,    64,    65,    -1,    34,     3,    -1,    33,     3,
      -1,    34,   152,     3,    -1,    33,   152,     3,    -1,    34,
      35,   152,     3,    -1,    33,    35,   152,     3,    -1,    34,
     152,    35,   152,     3,    -1,    33,   152,    35,   152,     3,
      -1,     3,    -1,   152,     3,    -1,    35,   152,     3,    -1,
     152,    35,   152,     3,    -1,     8,    68,    -1,    -1,    68,
      69,    -1,    -1,    70,    71,    -1,    -1,     3,    31,     5,
      36,    74,    37,    72,    63,    -1,    -1,     3,    31,     5,
      36,    74,    37,    73,    33,    63,    -1,    75,    -1,    74,
      38,    75,    -1,     3,    -1,    -1,     1,    -1,    -1,    77,
      -1,    78,    -1,    78,    38,    77,    -1,     3,    -1,    23,
      -1,    22,    -1,    -1,    80,    -1,    81,    -1,    81,    38,
      80,    -1,     3,    -1,     5,    -1,    33,     5,    -1,    23,
      -1,    22,    -1,     9,    83,    -1,    -1,    84,    83,    -1,
      -1,    -1,     3,    85,    31,    86,    91,    -1,    -1,     3,
      39,    76,    40,    31,    87,    91,    -1,    -1,     3,    39,
      76,     1,    31,    88,    91,    -1,    -1,    -1,     3,    89,
       1,    31,    90,    91,    -1,    92,    -1,    93,    -1,    94,
      -1,    95,    -1,    96,    -1,   107,    -1,   110,    -1,   113,
      -1,   118,    -1,   126,    -1,     1,    -1,     5,    36,    37,
      -1,     3,    36,    37,    -1,    41,    34,     5,    36,    37,
      -1,    41,    34,     3,    36,    37,    -1,    41,    33,     5,
      36,    37,    -1,    41,    33,     3,    36,    37,    -1,    36,
      42,    42,     5,    43,    43,    37,    -1,    36,    42,    42,
       3,    43,    43,    37,    -1,    36,    42,    42,    41,    34,
       5,    43,    43,    37,    -1,    36,    42,    42,    41,    34,
       3,    43,    43,    37,    -1,    36,    42,    42,    41,    33,
       5,    43,    43,    37,    -1,    36,    42,    42,    41,    33,
       3,    43,    43,    37,    -1,    36,    42,    42,    41,    44,
       5,    43,    43,    37,    -1,    36,    42,    42,    41,    44,
       3,    43,    43,    37,    -1,    36,    42,    42,    41,    35,
       5,    43,    43,    37,    -1,    36,    42,    42,    41,    35,
       3,    43,    43,    37,    -1,    -1,    36,    97,    98,    37,
      -1,   102,    -1,   102,    38,   100,    -1,    -1,    38,    99,
     100,    -1,   101,    -1,   100,    38,   101,    -1,    -1,   102,
      -1,     3,    -1,    41,    -1,    -1,     3,    34,   103,    63,
      -1,    -1,    41,    34,   104,    63,    -1,    -1,     3,    33,
     105,    63,    -1,    -1,    41,    33,   106,    63,    -1,    -1,
      36,    37,   108,    63,    -1,    -1,    36,    37,   109,    33,
      63,    -1,    -1,    36,    37,    41,    34,   111,    63,    -1,
      -1,    36,    37,    41,    33,   112,    63,    -1,    -1,    45,
     114,   115,    46,    -1,   116,    -1,   115,    38,   116,    -1,
       3,    -1,     3,    39,    79,    40,    -1,     3,    39,    79,
       1,    40,    -1,    -1,    17,    39,   117,   148,    40,    -1,
      18,    -1,    -1,     5,    45,   119,   121,    46,    -1,    -1,
       3,    45,   120,   121,    46,    -1,   122,    -1,   121,   122,
      -1,    -1,     5,    33,    43,   123,   115,    -1,    -1,    33,
       5,    33,    43,   124,   115,    -1,    -1,    20,    33,    43,
     125,   115,    -1,    -1,    17,    39,   127,   148,    40,    -1,
      10,   129,    -1,    -1,   129,   130,    -1,    -1,     3,    31,
      45,   131,   133,    46,   132,    -1,     3,    31,     1,    -1,
      -1,    47,     5,    -1,   134,    -1,   133,    38,   134,    -1,
       5,    -1,    44,     5,    -1,    11,   136,    -1,    -1,    -1,
     136,   137,   138,    -1,    -1,     3,   146,    31,    36,   139,
     141,    37,    -1,    -1,     3,   146,    31,     3,    36,   140,
     141,    37,    -1,    -1,   141,   142,    -1,    -1,   146,    33,
      43,    45,   143,   115,    46,    -1,    -1,   146,    33,    43,
     144,   116,    -1,     5,    48,     3,    48,     5,    -1,     3,
      48,     5,    -1,     5,    48,     3,    -1,     3,    -1,    20,
      -1,   145,    -1,    14,   145,    -1,    13,     3,    -1,    -1,
      16,    39,   147,   148,    40,    -1,     5,    -1,   148,    38,
       5,    -1,     1,    -1,    12,   150,    -1,    -1,   150,   151,
      -1,     5,    33,    43,     5,    -1,     5,    33,    43,     5,
      33,     5,    -1,     5,    33,    43,    36,     5,    37,    -1,
       5,    33,    43,     5,    36,     5,    37,    -1,     5,    33,
      43,     5,    33,     5,    36,     5,    37,    -1,     4,    -1,
       5,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   162,   162,   163,   166,   167,   170,   171,   172,   173,
     174,   175,   176,   177,   178,   186,   188,   190,   194,   194,
     198,   206,   217,   219,   226,   235,   237,   239,   243,   243,
     247,   250,   254,   258,   262,   272,   276,   278,   281,   284,
     287,   290,   293,   303,   313,   323,   348,   356,   359,   369,
     399,   401,   403,   407,   407,   412,   411,   416,   415,   421,
     421,   424,   425,   426,   434,   435,   441,   442,   453,   454,
     461,   480,   481,   485,   486,   500,   502,   504,   506,   508,
     514,   518,   520,   525,   526,   524,   531,   529,   537,   535,
     547,   549,   546,   559,   560,   561,   562,   563,   564,   565,
     566,   567,   568,   569,   579,   581,   586,   588,   590,   592,
     597,   599,   604,   606,   608,   610,   612,   614,   616,   618,
     624,   623,   633,   634,   636,   636,   643,   644,   649,   653,
     657,   658,   660,   660,   663,   663,   666,   666,   669,   669,
     676,   676,   679,   679,   685,   685,   688,   688,   694,   694,
     700,   701,   705,   708,   710,   719,   718,   722,   726,   726,
     729,   729,   735,   736,   741,   740,   745,   744,   749,   748,
     756,   755,   763,   767,   768,   773,   772,   777,   787,   788,
     792,   793,   797,   798,   802,   806,   807,   807,   815,   814,
     820,   819,   827,   828,   833,   833,   837,   837,   843,   845,
     847,   849,   854,   855,   856,   857,   858,   858,   864,   866,
     868,   878,   882,   883,   887,   889,   891,   893,   895,   900,
     901
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
  "MUTABOR_TOKEN_ELSE", "MUTABOR_TOKEN_PARAMETER", "MUTABOR_TOKEN_ANCHOR",
  "MUTABOR_TOKEN_DISTANCE", "MUTABOR_TOKEN_ENDOFFILE",
  "MUTABOR_TOKEN_ERROR", "MUTABOR_TOKEN_SPACES", "MUTABOR_TOKEN_COMMENT",
  "MUTABOR_TOKEN_COMMENT_START", "MUTABOR_TOKEN_COMMENT_END",
  "MUTABOR_TOKEN_OTHER", "'='", "':'", "'-'", "'+'", "'/'", "'['", "']'",
  "','", "'('", "')'", "'@'", "'<'", "'>'", "'*'", "'{'", "'}'", "'.'",
  "'~'", "$accept", "start", "blocks", "block", "intervalldeklaration",
  "intervalldekl1", "intervalldekl2_1", "$@1", "intervalldekl2",
  "tondeklaration", "tondekl1", "tondekl2_1", "$@2", "tondekl2",
  "KOMPLEX_TON_LIST", "KOMPLEX_TON_LIST_2", "KOMPLEX_TON_1",
  "KOMPLEX_TON_START", "tonsystemdeklaration", "tonsystemdekl1",
  "tonsystemdekl2_1", "$@3", "tonsystemdekl2", "$@4", "$@5", "tonliste",
  "ton_element", "parameter_list", "nonempty_parameter_list", "parameter",
  "argument_list", "nonempty_argument_list", "argument_list_element",
  "umstimmungdeklaration", "retuning_definitions", "retuning_definition",
  "$@6", "$@7", "$@8", "$@9", "$@10", "$@11", "retuning_term",
  "umstimmungs_dekl_taste_abs", "umstimmungs_dekl_taste_rel",
  "umstimmungs_dekl_breite_abs", "umstimmungs_dekl_breite_rel",
  "umstimmungs_dekl_tonhoehe_veraendert", "$@12",
  "nonempty_umstimm_expression_list", "$@13", "umstimm_expression_list",
  "umstimm_expression", "nonempty_umstimm_expression", "$@14", "$@15",
  "$@16", "$@17", "umstimmungs_dekl_wiederholung_abs", "$@18", "$@19",
  "umstimmungs_dekl_wiederholung_rel", "$@20", "$@21",
  "umstimmungs_dekl_umstimmungs_bund", "$@22", "aktions_liste", "aktion",
  "$@23", "umstimmungs_dekl_umstimmungs_case", "$@24", "$@25",
  "umstimmungs_case_liste", "umstimmungs_case_element", "$@26", "$@27",
  "$@28", "umstimmungs_dekl_midi_out", "$@29", "harmoniedeklaration",
  "harmonie_dekl_1", "harmonie_dekl_2", "$@30", "bezugs_taste",
  "tasten_liste", "taste", "logikdeklaration", "logik_dekl_1", "$@31",
  "logik_dekl_2", "$@32", "$@33", "anweisungs_liste", "anweisung", "$@34",
  "$@35", "harmoniebezeichner", "ausloeser", "$@36", "integersequenz",
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
     285,    61,    58,    45,    43,    47,    91,    93,    44,    40,
      41,    64,    60,    62,    42,   123,   125,    46,   126
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    49,    50,    50,    51,    51,    52,    52,    52,    52,
      52,    52,    52,    52,    52,    53,    54,    54,    56,    55,
      57,    57,    57,    57,    57,    58,    59,    59,    61,    60,
      62,    62,    62,    62,    62,    63,    64,    64,    65,    65,
      65,    65,    65,    65,    65,    65,    66,    66,    66,    66,
      67,    68,    68,    70,    69,    72,    71,    73,    71,    74,
      74,    75,    75,    75,    76,    76,    77,    77,    78,    78,
      78,    79,    79,    80,    80,    81,    81,    81,    81,    81,
      82,    83,    83,    85,    86,    84,    87,    84,    88,    84,
      89,    90,    84,    91,    91,    91,    91,    91,    91,    91,
      91,    91,    91,    91,    92,    92,    93,    93,    93,    93,
      94,    94,    95,    95,    95,    95,    95,    95,    95,    95,
      97,    96,    98,    98,    99,    98,   100,   100,   101,   101,
     102,   102,   103,   102,   104,   102,   105,   102,   106,   102,
     108,   107,   109,   107,   111,   110,   112,   110,   114,   113,
     115,   115,   116,   116,   116,   117,   116,   116,   119,   118,
     120,   118,   121,   121,   123,   122,   124,   122,   125,   122,
     127,   126,   128,   129,   129,   131,   130,   130,   132,   132,
     133,   133,   134,   134,   135,   136,   137,   136,   139,   138,
     140,   138,   141,   141,   143,   142,   144,   142,   145,   145,
     145,   145,   146,   146,   146,   146,   147,   146,   148,   148,
     148,   149,   150,   150,   151,   151,   151,   151,   151,   152,
     152
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     1,     1,     2,     0,     1,     1,     1,
       1,     1,     1,     1,     2,     2,     0,     2,     0,     2,
       5,     5,     3,     3,     2,     2,     0,     2,     0,     2,
       3,     5,     3,     5,     3,     2,     0,     2,     2,     2,
       3,     3,     4,     4,     5,     5,     1,     2,     3,     4,
       2,     0,     2,     0,     2,     0,     8,     0,     9,     1,
       3,     1,     0,     1,     0,     1,     1,     3,     1,     1,
       1,     0,     1,     1,     3,     1,     1,     2,     1,     1,
       2,     0,     2,     0,     0,     5,     0,     7,     0,     7,
       0,     0,     6,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     3,     3,     5,     5,     5,     5,
       7,     7,     9,     9,     9,     9,     9,     9,     9,     9,
       0,     4,     1,     3,     0,     3,     1,     3,     0,     1,
       1,     1,     0,     4,     0,     4,     0,     4,     0,     4,
       0,     4,     0,     5,     0,     6,     0,     6,     0,     4,
       1,     3,     1,     4,     5,     0,     5,     1,     0,     5,
       0,     5,     1,     2,     0,     5,     0,     6,     0,     5,
       0,     5,     2,     0,     2,     0,     7,     3,     0,     2,
       1,     3,     1,     2,     2,     0,     0,     3,     0,     7,
       0,     8,     0,     2,     0,     7,     0,     5,     5,     3,
       3,     1,     1,     1,     2,     2,     0,     5,     1,     3,
       1,     2,     0,     2,     4,     6,     6,     7,     9,     1,
       1
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,    16,    26,    51,    81,   173,   185,   212,     0,
       0,     4,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    25,    50,    83,    80,    81,   172,   184,   211,     1,
       5,    17,     0,    27,     0,    52,     0,    64,     0,     0,
      82,     0,   174,     0,     0,   213,     0,    19,     0,    29,
       0,    54,    68,    70,    69,     0,    65,    66,    84,     0,
       0,     0,   187,     0,    24,     0,     0,     0,     0,     0,
       0,     0,    91,   177,   175,   201,     0,     0,     0,     0,
     202,   203,     0,     0,    23,    46,   219,   220,     0,    22,
      36,     0,    34,    32,    30,     0,    88,    86,    67,   103,
       0,     0,     0,   120,     0,   148,    85,    93,    94,    95,
      96,    97,    98,    99,   100,   101,   102,     0,     0,     0,
       0,   205,   204,   206,     0,   214,     0,     0,    35,    47,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   160,
       0,   158,   170,   140,     0,     0,     0,     0,     0,    92,
     182,     0,     0,   180,   199,   200,     0,     0,   188,     0,
       0,     0,    48,     0,     0,    37,    21,    20,     0,    31,
       0,    33,    63,    61,     0,    59,    89,    87,   105,     0,
     104,     0,     0,     0,     0,     0,     0,   130,   124,   131,
       0,   122,     0,     0,     0,     0,   152,     0,   157,     0,
     150,   183,     0,   178,     0,   210,   208,     0,   190,   192,
     215,     0,   216,    39,     0,     0,    38,     0,     0,    49,
      55,     0,     0,     0,     0,     0,   162,     0,     0,   146,
     144,   141,     0,     0,     0,     0,   136,   132,   128,   138,
     134,   121,   128,     0,     0,     0,     0,    71,   155,     0,
     149,   181,     0,   176,   198,     0,   207,   192,     0,     0,
     217,     0,    41,     0,     0,    40,     0,     0,     0,    60,
       0,     0,     0,   161,   163,   159,   171,     0,     0,   143,
       0,     0,     0,     0,     0,     0,     0,     0,   125,   126,
     129,     0,     0,   123,   109,   108,   107,   106,    75,    76,
      79,    78,     0,     0,    72,    73,     0,   151,   179,   209,
       0,   189,   193,     0,     0,    43,     0,    42,     0,    56,
       0,   164,   168,     0,   147,   145,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   137,   133,   128,   139,
     135,    77,     0,   153,     0,     0,   191,     0,   218,    45,
      44,    58,     0,     0,   166,   111,   110,     0,     0,     0,
       0,     0,     0,     0,     0,   127,   154,    74,   156,   196,
     165,   169,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   194,     0,   167,   115,   114,   113,   112,   119,   118,
     117,   116,     0,   197,     0,   195
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     9,    10,    11,    12,    20,    31,    32,    47,    13,
      21,    33,    34,    49,    89,   128,   165,    90,    14,    22,
      35,    36,    51,   267,   268,   174,   175,    55,    56,    57,
     303,   304,   305,    15,    24,    25,    38,    71,   137,   136,
      39,   117,   106,   107,   108,   109,   110,   111,   145,   190,
     238,   288,   289,   290,   287,   292,   286,   291,   112,   184,
     185,   113,   278,   277,   114,   148,   199,   200,   306,   115,
     181,   179,   225,   226,   352,   372,   353,   116,   182,    16,
      26,    42,   118,   253,   152,   153,    17,    27,    43,    62,
     209,   257,   258,   312,   392,   382,    81,   313,   156,   207,
      18,    28,    45,   170
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -341
static const yytype_int16 yypact[] =
{
     171,   184,  -341,  -341,  -341,    44,  -341,  -341,  -341,   123,
     199,  -341,  -341,  -341,  -341,  -341,  -341,  -341,  -341,  -341,
     132,   145,   148,    15,  -341,    44,   151,   155,    16,  -341,
    -341,  -341,   162,  -341,   166,  -341,   173,    94,   156,   196,
    -341,   172,  -341,   227,   180,  -341,    59,  -341,   209,  -341,
     220,  -341,  -341,  -341,  -341,     8,  -341,   216,  -341,   221,
       6,   154,  -341,   206,  -341,    33,   211,   245,   224,   225,
      94,     5,  -341,  -341,  -341,   213,   217,   250,   161,   223,
    -341,  -341,   226,    39,  -341,  -341,  -341,  -341,   228,  -341,
    -341,    76,  -341,   201,  -341,   230,  -341,  -341,  -341,  -341,
     -25,    38,   229,    43,   203,  -341,  -341,  -341,  -341,  -341,
    -341,  -341,  -341,  -341,  -341,  -341,  -341,     5,    13,   253,
     256,  -341,  -341,  -341,    25,    88,   255,   260,   205,  -341,
     228,   228,   228,    91,    91,    32,     5,     5,   232,  -341,
     233,  -341,  -341,    -2,   231,    21,   170,   183,    89,  -341,
    -341,   259,    81,  -341,  -341,   234,   137,   235,  -341,   262,
     267,   237,  -341,    99,   109,  -341,  -341,  -341,   272,  -341,
      14,  -341,  -341,  -341,   204,  -341,  -341,  -341,  -341,    95,
    -341,    95,   137,   210,    91,   243,    22,   212,  -341,   214,
     240,   241,   242,   244,   247,   248,   246,   249,  -341,    87,
    -341,  -341,    13,   239,   276,  -341,  -341,   164,  -341,  -341,
     251,   252,  -341,  -341,   228,    37,  -341,   228,    42,  -341,
     257,    32,   258,   261,   287,     9,  -341,    10,   179,  -341,
    -341,  -341,    91,   254,   263,    97,  -341,  -341,    23,  -341,
    -341,  -341,    23,   264,   265,   266,   268,   117,  -341,    89,
    -341,  -341,   288,  -341,  -341,   290,  -341,  -341,    68,   291,
    -341,   295,  -341,   228,   296,  -341,   228,    91,   271,  -341,
     269,   270,   274,  -341,  -341,  -341,  -341,    91,    91,  -341,
     273,   275,   215,   218,   219,   222,    91,    91,   277,  -341,
    -341,    91,    91,   277,  -341,  -341,  -341,  -341,  -341,  -341,
    -341,  -341,   303,    18,  -341,   279,   137,  -341,  -341,  -341,
      73,  -341,  -341,   278,   282,  -341,   297,  -341,   306,  -341,
      91,  -341,  -341,   280,  -341,  -341,   283,   284,   281,   285,
     286,   289,   292,   293,   294,   298,  -341,  -341,    23,  -341,
    -341,  -341,   299,  -341,   117,   188,  -341,   300,  -341,  -341,
    -341,  -341,    89,    89,  -341,  -341,  -341,   301,   302,   304,
     305,   307,   308,   309,   310,  -341,  -341,  -341,  -341,   311,
     316,   316,    89,   312,   318,   320,   321,   322,   323,   324,
     325,  -341,    89,   316,  -341,  -341,  -341,  -341,  -341,  -341,
    -341,  -341,    89,  -341,   107,  -341
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -341,  -341,  -341,   108,  -341,  -341,  -341,  -341,  -341,  -341,
    -341,  -341,  -341,  -341,  -131,  -341,  -341,  -341,  -341,  -341,
    -341,  -341,  -341,  -341,  -341,  -341,    93,  -341,   313,  -341,
    -341,   -34,  -341,  -341,   315,  -341,  -341,  -341,  -341,  -341,
    -341,  -341,    26,  -341,  -341,  -341,  -341,  -341,  -341,  -341,
    -341,    80,   -13,   181,  -341,  -341,  -341,  -341,  -341,  -341,
    -341,  -341,  -341,  -341,  -341,  -341,  -340,  -245,  -341,  -341,
    -341,  -341,   146,     4,  -341,  -341,  -341,  -341,  -341,  -341,
    -341,  -341,  -341,  -341,  -341,   128,  -341,  -341,  -341,  -341,
    -341,  -341,    74,  -341,  -341,  -341,   314,   317,  -341,  -177,
    -341,  -341,  -341,   -65
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -187
static const yytype_int16 yytable[] =
{
      91,    94,   169,   171,   307,   228,    99,    73,   100,    68,
     101,   138,   370,   371,   222,   222,   -90,   129,   150,   342,
     139,    44,   102,   127,   187,   233,   187,   234,   157,   223,
     223,  -142,   383,   172,    84,   173,    85,    86,    87,   183,
     262,   103,   224,   224,   125,   265,   104,    23,    69,   132,
     105,    74,   394,   231,    37,   273,   275,   151,   343,   188,
      64,   158,   189,   235,   189,   166,   167,   168,    88,   -62,
     -62,    75,   263,    76,   140,   126,    75,   266,    76,   129,
     143,    77,    78,   141,    79,   144,    77,    78,    80,    79,
      65,   130,   196,    80,    85,    86,    87,    52,   215,   218,
     222,   279,   213,    86,    87,   311,   197,   198,   131,    19,
     346,   132,   216,    86,    87,   223,    53,    54,    30,   202,
     298,   159,   299,    29,   160,   249,    88,   203,   224,   345,
     282,   283,   284,   250,   214,   -18,   319,   393,   205,   300,
     301,   285,   206,   149,   217,   249,   324,   325,   -28,   261,
     302,   -53,   264,   395,    41,   336,   337,    75,  -186,    76,
     339,   340,   176,   177,    75,    46,    76,    77,    78,    48,
      79,    -2,     1,   192,    80,   193,    50,     2,     3,     4,
       5,     6,     7,     8,    -6,     1,   194,    58,   195,   351,
       2,     3,     4,     5,     6,     7,     8,    59,   316,    -3,
       1,   318,   255,    60,   256,     2,     3,     4,     5,     6,
       7,     8,    92,    63,    93,    86,    87,   255,   328,   276,
     329,   330,   332,   331,   333,   334,   255,   335,   368,   274,
      61,   274,    86,    87,   133,   134,   146,   147,   163,   164,
      66,   220,   221,   229,   230,   236,   237,   239,   240,    83,
      95,    67,    72,   121,    70,    96,    97,   124,   154,   155,
     161,   119,   123,   162,   201,   120,   135,   210,   142,   178,
     180,   208,   211,   186,   212,   219,   232,   241,   243,   242,
     244,   254,   204,   245,   246,   247,   252,   259,   248,   260,
     -57,   270,   272,   308,   271,   309,   314,   280,   315,   317,
     349,   294,   295,   296,   320,   297,   281,   323,   341,   350,
     367,   347,   321,   322,   269,   338,   326,   344,   327,   348,
     355,   356,   293,   354,   357,   365,   191,   227,   358,   359,
     251,   310,   360,     0,     0,   361,   362,   363,     0,   366,
      40,   364,     0,   369,   373,   374,     0,   375,   376,   384,
     377,   378,   379,   380,   249,   385,   381,   386,   387,   388,
     389,   390,   391,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    82,     0,
       0,     0,     0,    98,     0,     0,     0,     0,     0,     0,
       0,     0,   122
};

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-341)))

#define yytable_value_is_error(Yytable_value) \
  YYID (0)

static const yytype_int16 yycheck[] =
{
      65,    66,   133,   134,   249,   182,     1,     1,     3,     1,
       5,    36,   352,   353,     5,     5,     1,     3,     5,     1,
      45,     5,    17,    88,     3,     3,     3,     5,     3,    20,
      20,    33,   372,     1,     1,     3,     3,     4,     5,    41,
       3,    36,    33,    33,     5,     3,    41,     3,    40,    35,
      45,    45,   392,   184,    39,    46,    46,    44,    40,    38,
       1,    36,    41,    41,    41,   130,   131,   132,    35,    37,
      38,     3,    35,     5,    36,    36,     3,    35,     5,     3,
      37,    13,    14,    45,    16,    42,    13,    14,    20,    16,
      31,    15,     3,    20,     3,     4,     5,     3,   163,   164,
       5,   232,     3,     4,     5,    37,    17,    18,    32,     1,
      37,    35,     3,     4,     5,    20,    22,    23,    10,    38,
       3,    33,     5,     0,    36,    38,    35,    46,    33,   306,
      33,    34,    35,    46,    35,     3,   267,   382,     1,    22,
      23,    44,     5,   117,    35,    38,   277,   278,     3,   214,
      33,     3,   217,    46,     3,   286,   287,     3,     3,     5,
     291,   292,   136,   137,     3,     3,     5,    13,    14,     3,
      16,     0,     1,     3,    20,     5,     3,     6,     7,     8,
       9,    10,    11,    12,     0,     1,     3,    31,     5,   320,
       6,     7,     8,     9,    10,    11,    12,     1,   263,     0,
       1,   266,    38,    31,    40,     6,     7,     8,     9,    10,
      11,    12,     1,    33,     3,     4,     5,    38,     3,    40,
       5,     3,     3,     5,     5,     3,    38,     5,    40,   225,
       3,   227,     4,     5,    33,    34,    33,    34,    33,    34,
      31,    37,    38,    33,    34,    33,    34,    33,    34,    43,
       5,    31,    31,     3,    38,    31,    31,    31,     5,     3,
       5,    48,    39,     3,     5,    48,    36,     5,    39,    37,
      37,    36,     5,    42,    37,     3,    33,    37,    36,    38,
      36,     5,    48,    36,    36,    39,    47,    36,    39,    37,
      33,    33,     5,     5,    33,     5,     5,    43,     3,     3,
       3,    37,    37,    37,    33,    37,    43,    33,     5,     3,
     344,    33,    43,    43,   221,    38,    43,    38,    43,    37,
      37,    37,   242,    43,    43,   338,   145,   181,    43,    43,
     202,   257,    43,    -1,    -1,    43,    43,    43,    -1,    40,
      25,    43,    -1,    43,    43,    43,    -1,    43,    43,    37,
      43,    43,    43,    43,    38,    37,    45,    37,    37,    37,
      37,    37,    37,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    61,    -1,
      -1,    -1,    -1,    70,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    78
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     1,     6,     7,     8,     9,    10,    11,    12,    50,
      51,    52,    53,    58,    67,    82,   128,   135,   149,    52,
      54,    59,    68,     3,    83,    84,   129,   136,   150,     0,
      52,    55,    56,    60,    61,    69,    70,    39,    85,    89,
      83,     3,   130,   137,     5,   151,     3,    57,     3,    62,
       3,    71,     3,    22,    23,    76,    77,    78,    31,     1,
      31,     3,   138,    33,     1,    31,    31,    31,     1,    40,
      38,    86,    31,     1,    45,     3,     5,    13,    14,    16,
      20,   145,   146,    43,     1,     3,     4,     5,    35,    63,
      66,   152,     1,     3,   152,     5,    31,    31,    77,     1,
       3,     5,    17,    36,    41,    45,    91,    92,    93,    94,
      95,    96,   107,   110,   113,   118,   126,    90,   131,    48,
      48,     3,   145,    39,    31,     5,    36,   152,    64,     3,
      15,    32,    35,    33,    34,    36,    88,    87,    36,    45,
      36,    45,    39,    37,    42,    97,    33,    34,   114,    91,
       5,    44,   133,   134,     5,     3,   147,     3,    36,    33,
      36,     5,     3,    33,    34,    65,   152,   152,   152,    63,
     152,    63,     1,     3,    74,    75,    91,    91,    37,   120,
      37,   119,   127,    41,   108,   109,    42,     3,    38,    41,
      98,   102,     3,     5,     3,     5,     3,    17,    18,   115,
     116,     5,    38,    46,    48,     1,     5,   148,    36,   139,
       5,     5,    37,     3,    35,   152,     3,    35,   152,     3,
      37,    38,     5,    20,    33,   121,   122,   121,   148,    33,
      34,    63,    33,     3,     5,    41,    33,    34,    99,    33,
      34,    37,    38,    36,    36,    36,    36,    39,    39,    38,
      46,   134,    47,   132,     5,    38,    40,   140,   141,    36,
      37,   152,     3,    35,   152,     3,    35,    72,    73,    75,
      33,    33,     5,    46,   122,    46,    40,   112,   111,    63,
      43,    43,    33,    34,    35,    44,   105,   103,   100,   101,
     102,   106,   104,   100,    37,    37,    37,    37,     3,     5,
      22,    23,    33,    79,    80,    81,   117,   116,     5,     5,
     141,    37,   142,   146,     5,     3,   152,     3,   152,    63,
      33,    43,    43,    33,    63,    63,    43,    43,     3,     5,
       3,     5,     3,     5,     3,     5,    63,    63,    38,    63,
      63,     5,     1,    40,    38,   148,    37,    33,    37,     3,
       3,    63,   123,   125,    43,    37,    37,    43,    43,    43,
      43,    43,    43,    43,    43,   101,    40,    80,    40,    43,
     115,   115,   124,    43,    43,    43,    43,    43,    43,    43,
      43,    45,   144,   115,    37,    37,    37,    37,    37,    37,
      37,    37,   143,   116,   115,    46
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
        case 14:
/* Line 1787 of yacc.c  */
#line 178 "../../../mutabor-git/src/kernel/mut.yy"
    {  mutabor_error_message(box,
		compiler_error,
		_("Syntax error in line %d."),
		FEHLERZEILE); 
		}
    break;

  case 18:
/* Line 1787 of yacc.c  */
#line 194 "../../../mutabor-git/src/kernel/mut.yy"
    { init_komplex_ton_list (box); }
    break;

  case 20:
/* Line 1787 of yacc.c  */
#line 199 "../../../mutabor-git/src/kernel/mut.yy"
    { if ( fabs((yyvsp[(5) - (5)].f_value)) > 0.001 )
				    get_new_intervall (box, (yyvsp[(1) - (5)].identifier), (yyvsp[(3) - (5)].f_value) / (yyvsp[(5) - (5)].f_value));
                      else
			      mutabor_error_message (box,compiler_error,
					   _("Bad interval value in %s"),
					   ((yyvsp[(1) - (5)].identifier)) ); }
    break;

  case 21:
/* Line 1787 of yacc.c  */
#line 207 "../../../mutabor-git/src/kernel/mut.yy"
    { if ( fabs ((yyvsp[(3) - (5)].f_value)) > 0.001 )
				    get_new_intervall (box, (yyvsp[(1) - (5)].identifier), pow ((yyvsp[(5) - (5)].f_value), 1 / (yyvsp[(3) - (5)].f_value)));
                      else
			      mutabor_error_message (box,compiler_error,
						     _("Bad interval value in %s"),
						     ((yyvsp[(1) - (5)].identifier))); }
    break;

  case 22:
/* Line 1787 of yacc.c  */
#line 218 "../../../mutabor-git/src/kernel/mut.yy"
    { get_new_intervall_komplex (box,(yyvsp[(1) - (3)].identifier)); }
    break;

  case 23:
/* Line 1787 of yacc.c  */
#line 219 "../../../mutabor-git/src/kernel/mut.yy"
    { 
		mutabor_error_message(box,
				      compiler_error,
				      _("Bad interval declaration of intervall %s in line %d."),
				      ((yyvsp[(1) - (3)].identifier)),
				      FEHLERZEILE); 
	  }
    break;

  case 24:
/* Line 1787 of yacc.c  */
#line 226 "../../../mutabor-git/src/kernel/mut.yy"
    { 
		mutabor_error_message(box,
				      compiler_error,
				      _("Wrong character. Expecting %s in line %d."),
				      mutT("="),FEHLERZEILE); 
	  }
    break;

  case 28:
/* Line 1787 of yacc.c  */
#line 243 "../../../mutabor-git/src/kernel/mut.yy"
    { init_komplex_ton_list (box); }
    break;

  case 30:
/* Line 1787 of yacc.c  */
#line 248 "../../../mutabor-git/src/kernel/mut.yy"
    { get_new_ton_absolut (box, (yyvsp[(1) - (3)].identifier), (yyvsp[(3) - (3)].f_value)); }
    break;

  case 31:
/* Line 1787 of yacc.c  */
#line 252 "../../../mutabor-git/src/kernel/mut.yy"
    { get_new_ton_komplex_negative (box, (yyvsp[(1) - (5)].identifier), (yyvsp[(3) - (5)].identifier)); }
    break;

  case 32:
/* Line 1787 of yacc.c  */
#line 256 "../../../mutabor-git/src/kernel/mut.yy"
    { get_new_ton_komplex_positive (box, (yyvsp[(1) - (3)].identifier), (yyvsp[(3) - (3)].identifier)); }
    break;

  case 33:
/* Line 1787 of yacc.c  */
#line 260 "../../../mutabor-git/src/kernel/mut.yy"
    { get_new_ton_komplex_positive (box, (yyvsp[(1) - (5)].identifier), (yyvsp[(3) - (5)].identifier)); }
    break;

  case 34:
/* Line 1787 of yacc.c  */
#line 262 "../../../mutabor-git/src/kernel/mut.yy"
    { 
	      mutabor_error_message(box,
				    compiler_error,
				    _("Bad tone declaration of tone %s in line %d."),
				    ((yyvsp[(1) - (3)].identifier)),
				    FEHLERZEILE); 
	}
    break;

  case 38:
/* Line 1787 of yacc.c  */
#line 282 "../../../mutabor-git/src/kernel/mut.yy"
    { get_new_faktor_anteil ( box, (double) 1, (yyvsp[(2) - (2)].identifier)); }
    break;

  case 39:
/* Line 1787 of yacc.c  */
#line 285 "../../../mutabor-git/src/kernel/mut.yy"
    { get_new_faktor_anteil ( box,  (double) -1, (yyvsp[(2) - (2)].identifier)); }
    break;

  case 40:
/* Line 1787 of yacc.c  */
#line 288 "../../../mutabor-git/src/kernel/mut.yy"
    { get_new_faktor_anteil (box, (yyvsp[(2) - (3)].f_value), (yyvsp[(3) - (3)].identifier)); }
    break;

  case 41:
/* Line 1787 of yacc.c  */
#line 291 "../../../mutabor-git/src/kernel/mut.yy"
    { get_new_faktor_anteil (box, -((yyvsp[(2) - (3)].f_value)), (yyvsp[(3) - (3)].identifier)); }
    break;

  case 42:
/* Line 1787 of yacc.c  */
#line 294 "../../../mutabor-git/src/kernel/mut.yy"
    { if ( fabs((yyvsp[(3) - (4)].f_value)) > 0.001 )
				   get_new_faktor_anteil (box, (double) 1 / ((yyvsp[(3) - (4)].f_value)), (yyvsp[(4) - (4)].identifier));
			   else
				   mutabor_error_message(box,
							 compiler_error,
							 _("Division by (nearly) 0 in line %d."),
							 FEHLERZEILE);  
		   }
    break;

  case 43:
/* Line 1787 of yacc.c  */
#line 304 "../../../mutabor-git/src/kernel/mut.yy"
    { if ( fabs((yyvsp[(3) - (4)].f_value)) > 0.001 )
				   get_new_faktor_anteil (box, (double) -1 / ((yyvsp[(3) - (4)].f_value)), (yyvsp[(4) - (4)].identifier));
                     else
				   mutabor_error_message(box,
							 compiler_error,
							 _("Division by (nearly) 0 in line %d."),
							 FEHLERZEILE);  
		   }
    break;

  case 44:
/* Line 1787 of yacc.c  */
#line 314 "../../../mutabor-git/src/kernel/mut.yy"
    { if ( fabs((yyvsp[(4) - (5)].f_value)) > 0.001 )
				   get_new_faktor_anteil (box, ((yyvsp[(2) - (5)].f_value)) / ((yyvsp[(4) - (5)].f_value)), (yyvsp[(5) - (5)].identifier));
                     else
			     mutabor_error_message(box,
						   compiler_error,
						   _("Division by (nearly) 0 in line %d."),
						   FEHLERZEILE);  
		   }
    break;

  case 45:
/* Line 1787 of yacc.c  */
#line 324 "../../../mutabor-git/src/kernel/mut.yy"
    { if ( fabs((yyvsp[(4) - (5)].f_value)) > 0.001 )
				   get_new_faktor_anteil (box, -((yyvsp[(2) - (5)].f_value)) / ((yyvsp[(4) - (5)].f_value)), (yyvsp[(5) - (5)].identifier));
                     else
			     mutabor_error_message(box,
						   compiler_error,
						   _("Division by (nearly) 0 in line %d."),
						   FEHLERZEILE);  
		   }
    break;

  case 46:
/* Line 1787 of yacc.c  */
#line 349 "../../../mutabor-git/src/kernel/mut.yy"
    { get_new_faktor_anteil (box, (double) 1.0 , (yyvsp[(1) - (1)].identifier)); }
    break;

  case 47:
/* Line 1787 of yacc.c  */
#line 357 "../../../mutabor-git/src/kernel/mut.yy"
    { get_new_faktor_anteil (box, (yyvsp[(1) - (2)].f_value), (yyvsp[(2) - (2)].identifier)); }
    break;

  case 48:
/* Line 1787 of yacc.c  */
#line 360 "../../../mutabor-git/src/kernel/mut.yy"
    { if ( fabs((yyvsp[(2) - (3)].f_value)) > 0.001 )
				   get_new_faktor_anteil (box, (double) 1 / ((yyvsp[(2) - (3)].f_value)), (yyvsp[(3) - (3)].identifier));
                     else
			     mutabor_error_message(box,
						   compiler_error,
						   _("Division by (nearly) 0 in line %d."),
						   FEHLERZEILE);  
		   }
    break;

  case 49:
/* Line 1787 of yacc.c  */
#line 370 "../../../mutabor-git/src/kernel/mut.yy"
    { if ( fabs((yyvsp[(3) - (4)].f_value)) > 0.001 )
				   get_new_faktor_anteil (box, ((yyvsp[(1) - (4)].f_value)) / ((yyvsp[(3) - (4)].f_value)), (yyvsp[(4) - (4)].identifier));
                     else
			     mutabor_error_message(box,
						   compiler_error,
						   _("Division by (nearly) 0 in line %d."),
						   FEHLERZEILE);  
		   }
    break;

  case 53:
/* Line 1787 of yacc.c  */
#line 407 "../../../mutabor-git/src/kernel/mut.yy"
    { init_ton_liste (box); }
    break;

  case 55:
/* Line 1787 of yacc.c  */
#line 412 "../../../mutabor-git/src/kernel/mut.yy"
    { init_komplex_ton_list (box); }
    break;

  case 56:
/* Line 1787 of yacc.c  */
#line 414 "../../../mutabor-git/src/kernel/mut.yy"
    { get_new_tonsystem (box, (yyvsp[(1) - (8)].identifier), (yyvsp[(3) - (8)].integer)); }
    break;

  case 57:
/* Line 1787 of yacc.c  */
#line 416 "../../../mutabor-git/src/kernel/mut.yy"
    { init_komplex_ton_list (box); }
    break;

  case 58:
/* Line 1787 of yacc.c  */
#line 418 "../../../mutabor-git/src/kernel/mut.yy"
    { get_new_tonsystem_negative (box, (yyvsp[(1) - (9)].identifier), (yyvsp[(3) - (9)].integer)); }
    break;

  case 61:
/* Line 1787 of yacc.c  */
#line 424 "../../../mutabor-git/src/kernel/mut.yy"
    { get_new_ton_in_tonsystem (box, (yyvsp[(1) - (1)].identifier)); }
    break;

  case 62:
/* Line 1787 of yacc.c  */
#line 425 "../../../mutabor-git/src/kernel/mut.yy"
    { get_new_ton_in_tonsystem (box, NULL); }
    break;

  case 63:
/* Line 1787 of yacc.c  */
#line 426 "../../../mutabor-git/src/kernel/mut.yy"
    {     mutabor_error_message(box,
		compiler_error,
		_("Bad tonesystem declaration in line %d."),		      
		FEHLERZEILE);
		}
    break;

  case 64:
/* Line 1787 of yacc.c  */
#line 434 "../../../mutabor-git/src/kernel/mut.yy"
    { (yyval.parameters) = NULL; }
    break;

  case 65:
/* Line 1787 of yacc.c  */
#line 435 "../../../mutabor-git/src/kernel/mut.yy"
    { (yyval.parameters) = (yyvsp[(1) - (1)].parameters); 
                    enumerate_parameters(box,(yyval.parameters));
		}
    break;

  case 67:
/* Line 1787 of yacc.c  */
#line 443 "../../../mutabor-git/src/kernel/mut.yy"
    {
		    if ((yyvsp[(1) - (3)].parameters) != NULL) {
			(yyval.parameters) = (yyvsp[(1) - (3)].parameters);
		        (yyval.parameters)->next = (yyvsp[(3) - (3)].parameters);
   		    } else {(yyval.parameters) = (yyvsp[(3) - (3)].parameters);}
		}
    break;

  case 68:
/* Line 1787 of yacc.c  */
#line 453 "../../../mutabor-git/src/kernel/mut.yy"
    { (yyval.parameters) = get_new_name_in_parameterlist (box, (yyvsp[(1) - (1)].identifier)); }
    break;

  case 69:
/* Line 1787 of yacc.c  */
#line 454 "../../../mutabor-git/src/kernel/mut.yy"
    { 
		    (yyval.parameters) = NULL;
		    mutabor_error_message(box,
					  compiler_warning,
		                          _("Arguments named “DISTANCE” or “ABSTAND” have a fixed meaning. Using them as parameters as in line %d is not supported. Expect undexpected behaviour."),
		                          FEHLERZEILE);
		}
    break;

  case 70:
/* Line 1787 of yacc.c  */
#line 461 "../../../mutabor-git/src/kernel/mut.yy"
    { (yyval.parameters) = NULL;
		    mutabor_error_message(box,
					  compiler_warning,
		_("Arguments named “DISTANCE” or “ABSTAND” have a fixed meaning. Using them as parameters as in line %d is not supported. Expect undexpected behaviour."),
		FEHLERZEILE);
		}
    break;

  case 71:
/* Line 1787 of yacc.c  */
#line 480 "../../../mutabor-git/src/kernel/mut.yy"
    { (yyval.arguments) = NULL; }
    break;

  case 72:
/* Line 1787 of yacc.c  */
#line 481 "../../../mutabor-git/src/kernel/mut.yy"
    { (yyval.arguments) = (yyvsp[(1) - (1)].arguments); }
    break;

  case 73:
/* Line 1787 of yacc.c  */
#line 485 "../../../mutabor-git/src/kernel/mut.yy"
    { (yyval.arguments) = (yyvsp[(1) - (1)].arguments); }
    break;

  case 74:
/* Line 1787 of yacc.c  */
#line 487 "../../../mutabor-git/src/kernel/mut.yy"
    { (yyval.arguments) = (yyvsp[(1) - (3)].arguments); (yyvsp[(1) - (3)].arguments)->next = (yyvsp[(3) - (3)].arguments);}
    break;

  case 75:
/* Line 1787 of yacc.c  */
#line 501 "../../../mutabor-git/src/kernel/mut.yy"
    { (yyval.arguments) = get_new_name_in_argument_list (box, (yyvsp[(1) - (1)].identifier)) ;  }
    break;

  case 76:
/* Line 1787 of yacc.c  */
#line 503 "../../../mutabor-git/src/kernel/mut.yy"
    { (yyval.arguments) = get_new_number_in_argument_list (box, (yyvsp[(1) - (1)].integer)) ;  }
    break;

  case 77:
/* Line 1787 of yacc.c  */
#line 505 "../../../mutabor-git/src/kernel/mut.yy"
    { (yyval.arguments) = get_new_number_in_argument_list (box, -((yyvsp[(2) - (2)].integer))); }
    break;

  case 78:
/* Line 1787 of yacc.c  */
#line 507 "../../../mutabor-git/src/kernel/mut.yy"
    { (yyval.arguments) = get_new_distance_in_argument_list (box); }
    break;

  case 79:
/* Line 1787 of yacc.c  */
#line 509 "../../../mutabor-git/src/kernel/mut.yy"
    { (yyval.arguments) = get_new_anchor_in_argument_list (box); }
    break;

  case 83:
/* Line 1787 of yacc.c  */
#line 525 "../../../mutabor-git/src/kernel/mut.yy"
    { init_umstimmung (box, (yyvsp[(1) - (1)].identifier)); }
    break;

  case 84:
/* Line 1787 of yacc.c  */
#line 526 "../../../mutabor-git/src/kernel/mut.yy"
    { eintrage_parameterliste_in_umstimmung (box, NULL); }
    break;

  case 85:
/* Line 1787 of yacc.c  */
#line 528 "../../../mutabor-git/src/kernel/mut.yy"
    { get_new_umstimmung (box); }
    break;

  case 86:
/* Line 1787 of yacc.c  */
#line 531 "../../../mutabor-git/src/kernel/mut.yy"
    { init_umstimmung (box,(yyvsp[(1) - (5)].identifier)); 
		eintrage_parameterliste_in_umstimmung (box, (yyvsp[(3) - (5)].parameters)); }
    break;

  case 87:
/* Line 1787 of yacc.c  */
#line 534 "../../../mutabor-git/src/kernel/mut.yy"
    { get_new_umstimmung (box); }
    break;

  case 88:
/* Line 1787 of yacc.c  */
#line 537 "../../../mutabor-git/src/kernel/mut.yy"
    { 
		    init_umstimmung (box,(yyvsp[(1) - (5)].identifier));
		    eintrage_parameterliste_in_umstimmung (box, (yyvsp[(3) - (5)].parameters));
		mutabor_error_message(box,
		compiler_error,
		_("Invalid parameter list in retuning %s line %d"),
		(yyvsp[(1) - (5)].identifier), FEHLERZEILE); }
    break;

  case 89:
/* Line 1787 of yacc.c  */
#line 545 "../../../mutabor-git/src/kernel/mut.yy"
    { get_new_umstimmung (box); }
    break;

  case 90:
/* Line 1787 of yacc.c  */
#line 547 "../../../mutabor-git/src/kernel/mut.yy"
    { init_umstimmung (box,(yyvsp[(1) - (1)].identifier)); }
    break;

  case 91:
/* Line 1787 of yacc.c  */
#line 549 "../../../mutabor-git/src/kernel/mut.yy"
    { eintrage_parameterliste_in_umstimmung (box, NULL);
		mutabor_error_message(box,
		compiler_error,
		_("Error while reading %s line %d"),
		(yyvsp[(1) - (4)].identifier), FEHLERZEILE); }
    break;

  case 92:
/* Line 1787 of yacc.c  */
#line 555 "../../../mutabor-git/src/kernel/mut.yy"
    { get_new_umstimmung (box); }
    break;

  case 93:
/* Line 1787 of yacc.c  */
#line 559 "../../../mutabor-git/src/kernel/mut.yy"
    {}
    break;

  case 94:
/* Line 1787 of yacc.c  */
#line 560 "../../../mutabor-git/src/kernel/mut.yy"
    {}
    break;

  case 95:
/* Line 1787 of yacc.c  */
#line 561 "../../../mutabor-git/src/kernel/mut.yy"
    {}
    break;

  case 96:
/* Line 1787 of yacc.c  */
#line 562 "../../../mutabor-git/src/kernel/mut.yy"
    {}
    break;

  case 97:
/* Line 1787 of yacc.c  */
#line 563 "../../../mutabor-git/src/kernel/mut.yy"
    {}
    break;

  case 98:
/* Line 1787 of yacc.c  */
#line 564 "../../../mutabor-git/src/kernel/mut.yy"
    {}
    break;

  case 99:
/* Line 1787 of yacc.c  */
#line 565 "../../../mutabor-git/src/kernel/mut.yy"
    {}
    break;

  case 100:
/* Line 1787 of yacc.c  */
#line 566 "../../../mutabor-git/src/kernel/mut.yy"
    {}
    break;

  case 101:
/* Line 1787 of yacc.c  */
#line 567 "../../../mutabor-git/src/kernel/mut.yy"
    {}
    break;

  case 102:
/* Line 1787 of yacc.c  */
#line 568 "../../../mutabor-git/src/kernel/mut.yy"
    {}
    break;

  case 103:
/* Line 1787 of yacc.c  */
#line 569 "../../../mutabor-git/src/kernel/mut.yy"
    {
		mutabor_error_message(box,
				      compiler_error,
				      _("Bad retuning in line %d."),
				      FEHLERZEILE);
	  }
    break;

  case 104:
/* Line 1787 of yacc.c  */
#line 580 "../../../mutabor-git/src/kernel/mut.yy"
    { get_umstimmung_taste_abs (box, mutabor_argument_integer, (yyvsp[(1) - (3)].integer), NULL); }
    break;

  case 105:
/* Line 1787 of yacc.c  */
#line 582 "../../../mutabor-git/src/kernel/mut.yy"
    { get_umstimmung_taste_abs (box, mutabor_argument_parameter, 0.0, (yyvsp[(1) - (3)].identifier)); }
    break;

  case 106:
/* Line 1787 of yacc.c  */
#line 587 "../../../mutabor-git/src/kernel/mut.yy"
    { get_umstimmung_taste_rel (box, mutabor_argument_integer, (yyvsp[(3) - (5)].integer), NULL, '+'); }
    break;

  case 107:
/* Line 1787 of yacc.c  */
#line 589 "../../../mutabor-git/src/kernel/mut.yy"
    { get_umstimmung_taste_rel (box, mutabor_argument_parameter, 0.0, (yyvsp[(3) - (5)].identifier), '+'); }
    break;

  case 108:
/* Line 1787 of yacc.c  */
#line 591 "../../../mutabor-git/src/kernel/mut.yy"
    { get_umstimmung_taste_rel (box, mutabor_argument_integer, (yyvsp[(3) - (5)].integer), NULL, '-'); }
    break;

  case 109:
/* Line 1787 of yacc.c  */
#line 593 "../../../mutabor-git/src/kernel/mut.yy"
    { get_umstimmung_taste_rel (box, mutabor_argument_parameter, 0.0, (yyvsp[(3) - (5)].identifier), '-'); }
    break;

  case 110:
/* Line 1787 of yacc.c  */
#line 598 "../../../mutabor-git/src/kernel/mut.yy"
    { get_umstimmung_breite_abs (box, mutabor_argument_integer, (yyvsp[(4) - (7)].integer), NULL); }
    break;

  case 111:
/* Line 1787 of yacc.c  */
#line 600 "../../../mutabor-git/src/kernel/mut.yy"
    { get_umstimmung_breite_abs (box, mutabor_argument_parameter, 0.0, (yyvsp[(4) - (7)].identifier)); }
    break;

  case 112:
/* Line 1787 of yacc.c  */
#line 605 "../../../mutabor-git/src/kernel/mut.yy"
    { get_umstimmung_breite_rel (box, mutabor_argument_integer, (yyvsp[(6) - (9)].integer), NULL, '+'); }
    break;

  case 113:
/* Line 1787 of yacc.c  */
#line 607 "../../../mutabor-git/src/kernel/mut.yy"
    { get_umstimmung_breite_rel (box, mutabor_argument_parameter, 0.0, (yyvsp[(6) - (9)].identifier), '+'); }
    break;

  case 114:
/* Line 1787 of yacc.c  */
#line 609 "../../../mutabor-git/src/kernel/mut.yy"
    { get_umstimmung_breite_rel (box, mutabor_argument_integer, (yyvsp[(6) - (9)].integer), NULL, '-'); }
    break;

  case 115:
/* Line 1787 of yacc.c  */
#line 611 "../../../mutabor-git/src/kernel/mut.yy"
    { get_umstimmung_breite_rel (box, mutabor_argument_parameter, 0.0, (yyvsp[(6) - (9)].identifier), '-'); }
    break;

  case 116:
/* Line 1787 of yacc.c  */
#line 613 "../../../mutabor-git/src/kernel/mut.yy"
    { get_umstimmung_breite_rel (box, mutabor_argument_integer, (yyvsp[(6) - (9)].integer), NULL, '*'); }
    break;

  case 117:
/* Line 1787 of yacc.c  */
#line 615 "../../../mutabor-git/src/kernel/mut.yy"
    { get_umstimmung_breite_rel (box, mutabor_argument_parameter, 0.0, (yyvsp[(6) - (9)].identifier), '*'); }
    break;

  case 118:
/* Line 1787 of yacc.c  */
#line 617 "../../../mutabor-git/src/kernel/mut.yy"
    { get_umstimmung_breite_rel (box, mutabor_argument_integer, (yyvsp[(6) - (9)].integer), NULL, '/'); }
    break;

  case 119:
/* Line 1787 of yacc.c  */
#line 619 "../../../mutabor-git/src/kernel/mut.yy"
    { get_umstimmung_breite_rel (box, mutabor_argument_parameter, 0.0, (yyvsp[(6) - (9)].identifier), '/'); }
    break;

  case 120:
/* Line 1787 of yacc.c  */
#line 624 "../../../mutabor-git/src/kernel/mut.yy"
    { init_umstimm_expression_list (box); }
    break;

  case 121:
/* Line 1787 of yacc.c  */
#line 626 "../../../mutabor-git/src/kernel/mut.yy"
    { get_umstimmung_tonhoehe_veraendert (box); }
    break;

  case 122:
/* Line 1787 of yacc.c  */
#line 633 "../../../mutabor-git/src/kernel/mut.yy"
    {}
    break;

  case 123:
/* Line 1787 of yacc.c  */
#line 634 "../../../mutabor-git/src/kernel/mut.yy"
    {}
    break;

  case 124:
/* Line 1787 of yacc.c  */
#line 636 "../../../mutabor-git/src/kernel/mut.yy"
    { init_komplex_ton_list(box);
		  get_new_umstimm_expression (box,NULL);
                   }
    break;

  case 125:
/* Line 1787 of yacc.c  */
#line 639 "../../../mutabor-git/src/kernel/mut.yy"
    {}
    break;

  case 126:
/* Line 1787 of yacc.c  */
#line 643 "../../../mutabor-git/src/kernel/mut.yy"
    {}
    break;

  case 127:
/* Line 1787 of yacc.c  */
#line 644 "../../../mutabor-git/src/kernel/mut.yy"
    {}
    break;

  case 128:
/* Line 1787 of yacc.c  */
#line 649 "../../../mutabor-git/src/kernel/mut.yy"
    { init_komplex_ton_list(box);
		  get_new_umstimm_expression (box, NULL);
                   }
    break;

  case 130:
/* Line 1787 of yacc.c  */
#line 657 "../../../mutabor-git/src/kernel/mut.yy"
    { get_new_umstimm_expression (box,(yyvsp[(1) - (1)].identifier)); }
    break;

  case 131:
/* Line 1787 of yacc.c  */
#line 658 "../../../mutabor-git/src/kernel/mut.yy"
    { get_new_umstimm_expression (box, "@"); }
    break;

  case 132:
/* Line 1787 of yacc.c  */
#line 660 "../../../mutabor-git/src/kernel/mut.yy"
    { init_komplex_ton_list (box); }
    break;

  case 133:
/* Line 1787 of yacc.c  */
#line 662 "../../../mutabor-git/src/kernel/mut.yy"
    { get_new_umstimm_expression_positive (box, (yyvsp[(1) - (4)].identifier)); }
    break;

  case 134:
/* Line 1787 of yacc.c  */
#line 663 "../../../mutabor-git/src/kernel/mut.yy"
    { init_komplex_ton_list (box); }
    break;

  case 135:
/* Line 1787 of yacc.c  */
#line 665 "../../../mutabor-git/src/kernel/mut.yy"
    { get_new_umstimm_expression_positive (box, "@" ); }
    break;

  case 136:
/* Line 1787 of yacc.c  */
#line 666 "../../../mutabor-git/src/kernel/mut.yy"
    { init_komplex_ton_list (box); }
    break;

  case 137:
/* Line 1787 of yacc.c  */
#line 668 "../../../mutabor-git/src/kernel/mut.yy"
    { get_new_umstimm_expression_negative (box,(yyvsp[(1) - (4)].identifier)); }
    break;

  case 138:
/* Line 1787 of yacc.c  */
#line 669 "../../../mutabor-git/src/kernel/mut.yy"
    { init_komplex_ton_list (box); }
    break;

  case 139:
/* Line 1787 of yacc.c  */
#line 671 "../../../mutabor-git/src/kernel/mut.yy"
    { get_new_umstimm_expression_negative (box, "@" ); }
    break;

  case 140:
/* Line 1787 of yacc.c  */
#line 676 "../../../mutabor-git/src/kernel/mut.yy"
    { init_komplex_ton_list (box); }
    break;

  case 141:
/* Line 1787 of yacc.c  */
#line 678 "../../../mutabor-git/src/kernel/mut.yy"
    { get_umstimmung_wiederholung_abs (box); }
    break;

  case 142:
/* Line 1787 of yacc.c  */
#line 679 "../../../mutabor-git/src/kernel/mut.yy"
    { init_komplex_ton_list (box); }
    break;

  case 143:
/* Line 1787 of yacc.c  */
#line 681 "../../../mutabor-git/src/kernel/mut.yy"
    { get_umstimmung_wiederholung_abs_negative (box); }
    break;

  case 144:
/* Line 1787 of yacc.c  */
#line 685 "../../../mutabor-git/src/kernel/mut.yy"
    { init_komplex_ton_list (box); }
    break;

  case 145:
/* Line 1787 of yacc.c  */
#line 687 "../../../mutabor-git/src/kernel/mut.yy"
    { get_umstimmung_wiederholung_rel_positive (box); }
    break;

  case 146:
/* Line 1787 of yacc.c  */
#line 688 "../../../mutabor-git/src/kernel/mut.yy"
    { init_komplex_ton_list (box); }
    break;

  case 147:
/* Line 1787 of yacc.c  */
#line 690 "../../../mutabor-git/src/kernel/mut.yy"
    { get_umstimmung_wiederholung_rel_negative (box); }
    break;

  case 148:
/* Line 1787 of yacc.c  */
#line 694 "../../../mutabor-git/src/kernel/mut.yy"
    { init_aktions_liste (box); }
    break;

  case 149:
/* Line 1787 of yacc.c  */
#line 696 "../../../mutabor-git/src/kernel/mut.yy"
    { get_umstimmung_umstimmungs_bund (box); }
    break;

  case 150:
/* Line 1787 of yacc.c  */
#line 700 "../../../mutabor-git/src/kernel/mut.yy"
    {}
    break;

  case 151:
/* Line 1787 of yacc.c  */
#line 701 "../../../mutabor-git/src/kernel/mut.yy"
    {}
    break;

  case 152:
/* Line 1787 of yacc.c  */
#line 705 "../../../mutabor-git/src/kernel/mut.yy"
    { 
		  get_new_aktion_aufruf_element (box,(yyvsp[(1) - (1)].identifier),NULL); 
	  }
    break;

  case 153:
/* Line 1787 of yacc.c  */
#line 709 "../../../mutabor-git/src/kernel/mut.yy"
    { get_new_aktion_aufruf_element (box,(yyvsp[(1) - (4)].identifier), (yyvsp[(3) - (4)].arguments)); }
    break;

  case 154:
/* Line 1787 of yacc.c  */
#line 711 "../../../mutabor-git/src/kernel/mut.yy"
    { get_new_aktion_aufruf_element (box,(yyvsp[(1) - (5)].identifier), (yyvsp[(3) - (5)].arguments));
			    mutabor_error_message(box,
						 compiler_error,
						 _("Invalid argument list for call to %s in line %d"),
						 (yyvsp[(1) - (5)].identifier),
						 FEHLERZEILE);
		    }
    break;

  case 155:
/* Line 1787 of yacc.c  */
#line 719 "../../../mutabor-git/src/kernel/mut.yy"
    { init_integersequenz (box);}
    break;

  case 156:
/* Line 1787 of yacc.c  */
#line 721 "../../../mutabor-git/src/kernel/mut.yy"
    { get_new_aktion_midi_out_element (box); }
    break;

  case 157:
/* Line 1787 of yacc.c  */
#line 722 "../../../mutabor-git/src/kernel/mut.yy"
    { get_new_aktion_harmony_analysis(box); }
    break;

  case 158:
/* Line 1787 of yacc.c  */
#line 726 "../../../mutabor-git/src/kernel/mut.yy"
    { init_umstimmungs_case_liste (box); }
    break;

  case 159:
/* Line 1787 of yacc.c  */
#line 728 "../../../mutabor-git/src/kernel/mut.yy"
    { get_umstimmung_umstimm_case_zahl (box,(yyvsp[(1) - (5)].integer)); }
    break;

  case 160:
/* Line 1787 of yacc.c  */
#line 729 "../../../mutabor-git/src/kernel/mut.yy"
    { init_umstimmungs_case_liste (box); }
    break;

  case 161:
/* Line 1787 of yacc.c  */
#line 731 "../../../mutabor-git/src/kernel/mut.yy"
    { get_umstimmung_umstimm_case_parameter (box,(yyvsp[(1) - (5)].identifier)); }
    break;

  case 162:
/* Line 1787 of yacc.c  */
#line 735 "../../../mutabor-git/src/kernel/mut.yy"
    {}
    break;

  case 163:
/* Line 1787 of yacc.c  */
#line 736 "../../../mutabor-git/src/kernel/mut.yy"
    {}
    break;

  case 164:
/* Line 1787 of yacc.c  */
#line 741 "../../../mutabor-git/src/kernel/mut.yy"
    { init_aktions_liste (box); }
    break;

  case 165:
/* Line 1787 of yacc.c  */
#line 743 "../../../mutabor-git/src/kernel/mut.yy"
    { get_umstimmungs_case_zahl_element (box,(yyvsp[(1) - (5)].integer)); }
    break;

  case 166:
/* Line 1787 of yacc.c  */
#line 745 "../../../mutabor-git/src/kernel/mut.yy"
    { init_aktions_liste (box); }
    break;

  case 167:
/* Line 1787 of yacc.c  */
#line 747 "../../../mutabor-git/src/kernel/mut.yy"
    { get_umstimmungs_case_zahl_element (box,-((yyvsp[(2) - (6)].integer))); }
    break;

  case 168:
/* Line 1787 of yacc.c  */
#line 749 "../../../mutabor-git/src/kernel/mut.yy"
    { init_aktions_liste (box); }
    break;

  case 169:
/* Line 1787 of yacc.c  */
#line 751 "../../../mutabor-git/src/kernel/mut.yy"
    { get_umstimmungs_case_default_element (box); }
    break;

  case 170:
/* Line 1787 of yacc.c  */
#line 756 "../../../mutabor-git/src/kernel/mut.yy"
    { init_integersequenz (box);}
    break;

  case 171:
/* Line 1787 of yacc.c  */
#line 758 "../../../mutabor-git/src/kernel/mut.yy"
    { get_umstimmung_midi_out (box); }
    break;

  case 172:
/* Line 1787 of yacc.c  */
#line 763 "../../../mutabor-git/src/kernel/mut.yy"
    {}
    break;

  case 173:
/* Line 1787 of yacc.c  */
#line 767 "../../../mutabor-git/src/kernel/mut.yy"
    {}
    break;

  case 174:
/* Line 1787 of yacc.c  */
#line 768 "../../../mutabor-git/src/kernel/mut.yy"
    {}
    break;

  case 175:
/* Line 1787 of yacc.c  */
#line 773 "../../../mutabor-git/src/kernel/mut.yy"
    { init_tastenliste (box); }
    break;

  case 176:
/* Line 1787 of yacc.c  */
#line 775 "../../../mutabor-git/src/kernel/mut.yy"
    { get_new_harmonie (box, (yyvsp[(1) - (7)].identifier), (yyvsp[(7) - (7)].integer)); }
    break;

  case 177:
/* Line 1787 of yacc.c  */
#line 777 "../../../mutabor-git/src/kernel/mut.yy"
    { 
		mutabor_error_message(box,
				      compiler_error,
				      _("Bad pattern declaration “%s” at line %d"),
				      ((yyvsp[(1) - (3)].identifier)),
				      FEHLERZEILE); 
	  }
    break;

  case 178:
/* Line 1787 of yacc.c  */
#line 787 "../../../mutabor-git/src/kernel/mut.yy"
    { (yyval.integer) = -1; }
    break;

  case 179:
/* Line 1787 of yacc.c  */
#line 788 "../../../mutabor-git/src/kernel/mut.yy"
    { (yyval.integer) = (yyvsp[(2) - (2)].integer); }
    break;

  case 180:
/* Line 1787 of yacc.c  */
#line 792 "../../../mutabor-git/src/kernel/mut.yy"
    {}
    break;

  case 181:
/* Line 1787 of yacc.c  */
#line 793 "../../../mutabor-git/src/kernel/mut.yy"
    {}
    break;

  case 182:
/* Line 1787 of yacc.c  */
#line 797 "../../../mutabor-git/src/kernel/mut.yy"
    { get_new_taste (box, (yyvsp[(1) - (1)].integer), '+'); }
    break;

  case 183:
/* Line 1787 of yacc.c  */
#line 798 "../../../mutabor-git/src/kernel/mut.yy"
    { get_new_taste (box, (yyvsp[(2) - (2)].integer), '*'); }
    break;

  case 184:
/* Line 1787 of yacc.c  */
#line 802 "../../../mutabor-git/src/kernel/mut.yy"
    {}
    break;

  case 185:
/* Line 1787 of yacc.c  */
#line 806 "../../../mutabor-git/src/kernel/mut.yy"
    {}
    break;

  case 186:
/* Line 1787 of yacc.c  */
#line 807 "../../../mutabor-git/src/kernel/mut.yy"
    { init_ausloeser (box);
                         /* f〉 die Anfangsausloesung der Logik */
                       }
    break;

  case 187:
/* Line 1787 of yacc.c  */
#line 810 "../../../mutabor-git/src/kernel/mut.yy"
    {}
    break;

  case 188:
/* Line 1787 of yacc.c  */
#line 815 "../../../mutabor-git/src/kernel/mut.yy"
    { get_new_logik (box, (yyvsp[(1) - (4)].identifier), NULL);
                init_anweisungs_liste (box); }
    break;

  case 189:
/* Line 1787 of yacc.c  */
#line 818 "../../../mutabor-git/src/kernel/mut.yy"
    { vervollstaendige_logik (box); }
    break;

  case 190:
/* Line 1787 of yacc.c  */
#line 820 "../../../mutabor-git/src/kernel/mut.yy"
    { get_new_logik (box, (yyvsp[(1) - (5)].identifier), (yyvsp[(4) - (5)].identifier));
                init_anweisungs_liste (box); }
    break;

  case 191:
/* Line 1787 of yacc.c  */
#line 823 "../../../mutabor-git/src/kernel/mut.yy"
    { vervollstaendige_logik (box); }
    break;

  case 192:
/* Line 1787 of yacc.c  */
#line 827 "../../../mutabor-git/src/kernel/mut.yy"
    {}
    break;

  case 193:
/* Line 1787 of yacc.c  */
#line 828 "../../../mutabor-git/src/kernel/mut.yy"
    {}
    break;

  case 194:
/* Line 1787 of yacc.c  */
#line 833 "../../../mutabor-git/src/kernel/mut.yy"
    { init_aktions_liste (box); }
    break;

  case 195:
/* Line 1787 of yacc.c  */
#line 835 "../../../mutabor-git/src/kernel/mut.yy"
    { get_new_anweisung (box); }
    break;

  case 196:
/* Line 1787 of yacc.c  */
#line 837 "../../../mutabor-git/src/kernel/mut.yy"
    { init_aktions_liste (box); }
    break;

  case 197:
/* Line 1787 of yacc.c  */
#line 839 "../../../mutabor-git/src/kernel/mut.yy"
    { get_new_anweisung (box); }
    break;

  case 198:
/* Line 1787 of yacc.c  */
#line 844 "../../../mutabor-git/src/kernel/mut.yy"
    { get_harmoniebezeichner (box, (yyvsp[(1) - (5)].integer), (yyvsp[(3) - (5)].identifier),  (yyvsp[(5) - (5)].integer)); }
    break;

  case 199:
/* Line 1787 of yacc.c  */
#line 846 "../../../mutabor-git/src/kernel/mut.yy"
    { get_harmoniebezeichner (box, MUTABOR_NO_KEY, (yyvsp[(1) - (3)].identifier),  (yyvsp[(3) - (3)].integer)); }
    break;

  case 200:
/* Line 1787 of yacc.c  */
#line 848 "../../../mutabor-git/src/kernel/mut.yy"
    { get_harmoniebezeichner (box, (yyvsp[(1) - (3)].integer), (yyvsp[(3) - (3)].identifier), MUTABOR_NO_KEY); }
    break;

  case 201:
/* Line 1787 of yacc.c  */
#line 850 "../../../mutabor-git/src/kernel/mut.yy"
    { get_harmoniebezeichner (box,  MUTABOR_NO_KEY, (yyvsp[(1) - (1)].identifier), MUTABOR_NO_KEY); }
    break;

  case 202:
/* Line 1787 of yacc.c  */
#line 854 "../../../mutabor-git/src/kernel/mut.yy"
    { get_ausloeser_default (box); }
    break;

  case 203:
/* Line 1787 of yacc.c  */
#line 855 "../../../mutabor-git/src/kernel/mut.yy"
    { get_ausloeser_harmonie (box); }
    break;

  case 204:
/* Line 1787 of yacc.c  */
#line 856 "../../../mutabor-git/src/kernel/mut.yy"
    { get_ausloeser_harmonie_form (box); }
    break;

  case 205:
/* Line 1787 of yacc.c  */
#line 857 "../../../mutabor-git/src/kernel/mut.yy"
    { get_ausloeser_taste (box,(yyvsp[(2) - (2)].identifier)); }
    break;

  case 206:
/* Line 1787 of yacc.c  */
#line 858 "../../../mutabor-git/src/kernel/mut.yy"
    { init_integersequenz (box); }
    break;

  case 207:
/* Line 1787 of yacc.c  */
#line 860 "../../../mutabor-git/src/kernel/mut.yy"
    { get_ausloeser_midi_in (box); }
    break;

  case 208:
/* Line 1787 of yacc.c  */
#line 865 "../../../mutabor-git/src/kernel/mut.yy"
    { get_new_integer_in_integersequenz (box,(yyvsp[(1) - (1)].integer));}
    break;

  case 209:
/* Line 1787 of yacc.c  */
#line 867 "../../../mutabor-git/src/kernel/mut.yy"
    { get_new_integer_in_integersequenz (box,(yyvsp[(3) - (3)].integer));}
    break;

  case 210:
/* Line 1787 of yacc.c  */
#line 868 "../../../mutabor-git/src/kernel/mut.yy"
    { 
		mutabor_error_message(box,
				      compiler_error,
				      _("Bad MIDI list in line %d"),  
				      FEHLERZEILE );
	  }
    break;

  case 211:
/* Line 1787 of yacc.c  */
#line 878 "../../../mutabor-git/src/kernel/mut.yy"
    {}
    break;

  case 212:
/* Line 1787 of yacc.c  */
#line 882 "../../../mutabor-git/src/kernel/mut.yy"
    {}
    break;

  case 213:
/* Line 1787 of yacc.c  */
#line 883 "../../../mutabor-git/src/kernel/mut.yy"
    {}
    break;

  case 214:
/* Line 1787 of yacc.c  */
#line 888 "../../../mutabor-git/src/kernel/mut.yy"
    { get_instrument_dekl (box, (yyvsp[(1) - (4)].integer), (yyvsp[(4) - (4)].integer), (yyvsp[(4) - (4)].integer), 0, & box->file->list_of_instrumente); }
    break;

  case 215:
/* Line 1787 of yacc.c  */
#line 890 "../../../mutabor-git/src/kernel/mut.yy"
    { get_instrument_dekl (box, (yyvsp[(1) - (6)].integer), (yyvsp[(4) - (6)].integer), (yyvsp[(6) - (6)].integer), 0, & box->file->list_of_instrumente); }
    break;

  case 216:
/* Line 1787 of yacc.c  */
#line 892 "../../../mutabor-git/src/kernel/mut.yy"
    { get_instrument_dekl (box, (yyvsp[(1) - (6)].integer), 0, 0, (yyvsp[(5) - (6)].integer), & box->file->list_of_instrumente); }
    break;

  case 217:
/* Line 1787 of yacc.c  */
#line 894 "../../../mutabor-git/src/kernel/mut.yy"
    { get_instrument_dekl (box, (yyvsp[(1) - (7)].integer), (yyvsp[(4) - (7)].integer), (yyvsp[(4) - (7)].integer), (yyvsp[(6) - (7)].integer), & box->file->list_of_instrumente); }
    break;

  case 218:
/* Line 1787 of yacc.c  */
#line 896 "../../../mutabor-git/src/kernel/mut.yy"
    { get_instrument_dekl (box, (yyvsp[(1) - (9)].integer), (yyvsp[(4) - (9)].integer), (yyvsp[(6) - (9)].integer), (yyvsp[(8) - (9)].integer), & box->file->list_of_instrumente); }
    break;

  case 219:
/* Line 1787 of yacc.c  */
#line 900 "../../../mutabor-git/src/kernel/mut.yy"
    { (yyval.f_value) = (yyvsp[(1) - (1)].f_value) ; }
    break;

  case 220:
/* Line 1787 of yacc.c  */
#line 901 "../../../mutabor-git/src/kernel/mut.yy"
    { (yyval.f_value) = (double) (yyvsp[(1) - (1)].integer) ; }
    break;


/* Line 1787 of yacc.c  */
#line 3259 "../../../mutabor-git/src/kernel/mut.cc"
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
#line 905 "../../../mutabor-git/src/kernel/mut.yy"

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

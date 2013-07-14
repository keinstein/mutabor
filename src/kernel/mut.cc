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
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
/* Line 371 of yacc.c  */
#line 35 "../../../mutabor-git/src/kernel/mut.yy"


/* BEGIN MUT_TAB.C */

/* MUTABOR / Version 2.1 */

//#pragma warn -cln
//#pragma warn -aus
//#pragma warn -sig
//#pragma warn -par


#include <ctype.h>
#include <limits.h>
#include "src/kernel/Global.h"
#include "src/kernel/GrafKern.h"
#include "src/kernel/Hilfs.h"

#define MAX_IDENTIFIER_LEN 80

#define FEHLERZEILE yylloc.first_line+1

#ifdef alloca
#undef alloca
#define alloca make_an_error ---
#endif
#define YYMALLOC xmalloc
#define YYFREE(X) do { /* empty */; } while (YYID (0))
#define YYMAXLIMIT (HEAP_PORTION_SYNTAX / sizeof(YYLTYPE) - 1)
                   /* wegen fehlendem alloca in PUREC */


/* Line 371 of yacc.c  */
#line 101 "../../../mutabor-git/src/kernel/mut.cc"

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
# define YYERROR_VERBOSE 0
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
     MUTABOR_TOKEN_ROOT = 262,
     MUTABOR_TOKEN_TONE = 263,
     MUTABOR_TOKEN_TONESYSTEM = 264,
     MUTABOR_TOKEN_RETUNING = 265,
     MUTABOR_TOKEN_HARMONY = 266,
     MUTABOR_TOKEN_LOGIC = 267,
     MUTABOR_TOKEN_FORM = 268,
     MUTABOR_TOKEN_MIDICHANNEL = 269,
     MUTABOR_TOKEN_KEY = 270,
     MUTABOR_TOKEN_MIDI_IN = 271,
     MUTABOR_TOKEN_MIDI_OUT = 272,
     MUTABOR_TOKEN_ELSE = 273,
     MUTABOR_TOKEN_SPACES = 274,
     MUTABOR_TOKEN_COMMENT = 275,
     MUTABOR_TOKEN_PARAMETER = 276,
     MUTABOR_TOKEN_OTHER = 277,
     MUTABOR_TOKEN_ERROR = 278,
     MUTABOR_TOKEN_ENDOFFILE = 279
   };
#endif
/* Tokens.  */
#define MUTABOR_TOKEN_IDENTIFIER 258
#define MUTABOR_TOKEN_F_NUMBER 259
#define MUTABOR_TOKEN_INTEGER 260
#define MUTABOR_TOKEN_INTERVAL 261
#define MUTABOR_TOKEN_ROOT 262
#define MUTABOR_TOKEN_TONE 263
#define MUTABOR_TOKEN_TONESYSTEM 264
#define MUTABOR_TOKEN_RETUNING 265
#define MUTABOR_TOKEN_HARMONY 266
#define MUTABOR_TOKEN_LOGIC 267
#define MUTABOR_TOKEN_FORM 268
#define MUTABOR_TOKEN_MIDICHANNEL 269
#define MUTABOR_TOKEN_KEY 270
#define MUTABOR_TOKEN_MIDI_IN 271
#define MUTABOR_TOKEN_MIDI_OUT 272
#define MUTABOR_TOKEN_ELSE 273
#define MUTABOR_TOKEN_SPACES 274
#define MUTABOR_TOKEN_COMMENT 275
#define MUTABOR_TOKEN_PARAMETER 276
#define MUTABOR_TOKEN_OTHER 277
#define MUTABOR_TOKEN_ERROR 278
#define MUTABOR_TOKEN_ENDOFFILE 279



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{
/* Line 387 of yacc.c  */
#line 68 "../../../mutabor-git/src/kernel/mut.yy"

    double      f_value;        /* fr Gleitkommazahlen */
    int         integer;        /* Fr integers */
    char        *identifier;    /* Fr Namen */


/* Line 387 of yacc.c  */
#line 199 "../../../mutabor-git/src/kernel/mut.cc"
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

extern YYSTYPE yylval;
extern YYLTYPE yylloc;
#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */

#endif /* !YY_YY__MUTABOR_GIT_SRC_KERNEL_MUT_HH_INCLUDED  */

/* Copy the second part of user declarations.  */

/* Line 390 of yacc.c  */
#line 240 "../../../mutabor-git/src/kernel/mut.cc"

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
#define YYLAST   343

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  43
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  98
/* YYNRULES -- Number of rules.  */
#define YYNRULES  204
/* YYNRULES -- Number of states.  */
#define YYNSTATES  376

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   279

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      33,    34,    38,    28,    32,    27,    41,    29,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    26,     2,
      36,    25,    37,     2,    35,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    30,     2,    31,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    39,     2,    40,    42,     2,     2,     2,
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
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24
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
     500,   501,   507,   508,   514,   515,   521,   523,   526,   527,
     533,   534,   541,   542,   548,   549,   555,   558,   559,   562,
     563,   571,   575,   576,   579,   581,   585,   587,   590,   593,
     594,   595,   599,   600,   608,   609,   618,   619,   622,   623,
     631,   632,   638,   644,   648,   652,   654,   656,   658,   661,
     664,   665,   671,   673,   677,   679,   682,   683,   686,   691,
     698,   705,   713,   723,   725
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
      44,     0,    -1,    -1,    44,    45,    -1,    44,    50,    -1,
      44,    59,    -1,    44,    71,    -1,    44,   116,    -1,    44,
     123,    -1,    44,   137,    -1,    44,     1,    -1,     6,    46,
      -1,    -1,    46,    47,    -1,    -1,    48,    49,    -1,     3,
      25,   140,    26,   140,    -1,     3,    25,   140,     7,   140,
      -1,     3,    25,    55,    -1,     3,    25,     1,    -1,     3,
       1,    -1,     8,    51,    -1,    -1,    51,    52,    -1,    -1,
      53,    54,    -1,     3,    25,   140,    -1,     3,    25,     3,
      27,    55,    -1,     3,    25,     3,    -1,     3,    25,     3,
      28,    55,    -1,     3,    25,     1,    -1,    58,    56,    -1,
      -1,    56,    57,    -1,    28,     3,    -1,    27,     3,    -1,
      28,   140,     3,    -1,    27,   140,     3,    -1,    28,    29,
     140,     3,    -1,    27,    29,   140,     3,    -1,    28,   140,
      29,   140,     3,    -1,    27,   140,    29,   140,     3,    -1,
       3,    -1,   140,     3,    -1,    29,   140,     3,    -1,   140,
      29,   140,     3,    -1,     9,    60,    -1,    -1,    60,    61,
      -1,    -1,    62,    63,    -1,    -1,     3,    25,     5,    30,
      66,    31,    64,    55,    -1,    -1,     3,    25,     5,    30,
      66,    31,    65,    27,    55,    -1,    67,    -1,    66,    32,
      67,    -1,     3,    -1,    -1,     1,    -1,     3,    -1,    68,
      32,     3,    -1,     1,    -1,    70,    -1,    69,    32,    70,
      -1,     1,    -1,     3,    -1,     5,    -1,    27,     5,    -1,
      10,    72,    -1,    -1,    72,    73,    -1,    -1,    -1,     3,
      74,    25,    75,    78,    -1,    -1,    -1,     3,    76,    33,
      68,    34,    25,    77,    78,    -1,    79,    -1,    80,    -1,
      81,    -1,    82,    -1,    83,    -1,    94,    -1,    97,    -1,
     100,    -1,   106,    -1,   114,    -1,     1,    -1,     5,    30,
      31,    -1,     3,    30,    31,    -1,    35,    28,     5,    30,
      31,    -1,    35,    28,     3,    30,    31,    -1,    35,    27,
       5,    30,    31,    -1,    35,    27,     3,    30,    31,    -1,
      30,    36,    36,     5,    37,    37,    31,    -1,    30,    36,
      36,     3,    37,    37,    31,    -1,    30,    36,    36,    35,
      28,     5,    37,    37,    31,    -1,    30,    36,    36,    35,
      28,     3,    37,    37,    31,    -1,    30,    36,    36,    35,
      27,     5,    37,    37,    31,    -1,    30,    36,    36,    35,
      27,     3,    37,    37,    31,    -1,    30,    36,    36,    35,
      38,     5,    37,    37,    31,    -1,    30,    36,    36,    35,
      38,     3,    37,    37,    31,    -1,    30,    36,    36,    35,
      29,     5,    37,    37,    31,    -1,    30,    36,    36,    35,
      29,     3,    37,    37,    31,    -1,    -1,    30,    84,    85,
      31,    -1,    89,    -1,    89,    32,    87,    -1,    -1,    32,
      86,    87,    -1,    88,    -1,    87,    32,    88,    -1,    -1,
      89,    -1,     3,    -1,    35,    -1,    -1,     3,    28,    90,
      55,    -1,    -1,    35,    28,    91,    55,    -1,    -1,     3,
      27,    92,    55,    -1,    -1,    35,    27,    93,    55,    -1,
      -1,    30,    31,    95,    55,    -1,    -1,    30,    31,    96,
      27,    55,    -1,    -1,    30,    31,    35,    28,    98,    55,
      -1,    -1,    30,    31,    35,    27,    99,    55,    -1,    -1,
      39,   101,   102,    40,    -1,   103,    -1,   102,    32,   103,
      -1,     3,    -1,    -1,     3,    33,   104,    69,    34,    -1,
      -1,    17,    33,   105,   136,    34,    -1,    -1,     5,    39,
     107,   109,    40,    -1,    -1,     3,    39,   108,   109,    40,
      -1,   110,    -1,   109,   110,    -1,    -1,     5,    27,    37,
     111,   102,    -1,    -1,    27,     5,    27,    37,   112,   102,
      -1,    -1,    18,    27,    37,   113,   102,    -1,    -1,    17,
      33,   115,   136,    34,    -1,    11,   117,    -1,    -1,   117,
     118,    -1,    -1,     3,    25,    39,   119,   121,    40,   120,
      -1,     3,    25,     1,    -1,    -1,    41,     5,    -1,   122,
      -1,   121,    32,   122,    -1,     5,    -1,    38,     5,    -1,
      12,   124,    -1,    -1,    -1,   124,   125,   126,    -1,    -1,
       3,   134,    25,    30,   127,   129,    31,    -1,    -1,     3,
     134,    25,     3,    30,   128,   129,    31,    -1,    -1,   129,
     130,    -1,    -1,   134,    27,    37,    39,   131,   102,    40,
      -1,    -1,   134,    27,    37,   132,   103,    -1,     5,    42,
       3,    42,     5,    -1,     3,    42,     5,    -1,     5,    42,
       3,    -1,     3,    -1,    18,    -1,   133,    -1,    13,   133,
      -1,    15,     3,    -1,    -1,    16,    33,   135,   136,    34,
      -1,     5,    -1,   136,    32,     5,    -1,     1,    -1,    14,
     138,    -1,    -1,   138,   139,    -1,     5,    27,    37,     5,
      -1,     5,    27,    37,     5,    27,     5,    -1,     5,    27,
      37,    30,     5,    31,    -1,     5,    27,    37,     5,    30,
       5,    31,    -1,     5,    27,    37,     5,    27,     5,    30,
       5,    31,    -1,     4,    -1,     5,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   105,   105,   106,   107,   108,   109,   110,   111,   112,
     113,   117,   119,   121,   125,   125,   129,   135,   144,   146,
     147,   151,   153,   155,   159,   159,   163,   166,   170,   174,
     178,   182,   186,   188,   191,   194,   197,   200,   203,   209,
     215,   221,   242,   250,   253,   259,   285,   287,   289,   293,
     293,   298,   297,   302,   301,   307,   307,   310,   311,   312,
     316,   317,   319,   324,   325,   326,   331,   332,   333,   339,
     341,   343,   348,   350,   347,   355,   358,   354,   364,   365,
     366,   367,   368,   369,   370,   371,   372,   373,   374,   379,
     381,   386,   388,   390,   392,   397,   399,   404,   406,   408,
     410,   412,   414,   416,   418,   424,   423,   433,   434,   436,
     436,   443,   444,   449,   453,   457,   458,   460,   460,   463,
     463,   466,   466,   469,   469,   476,   476,   479,   479,   485,
     485,   488,   488,   494,   494,   500,   501,   505,   507,   507,
     511,   510,   517,   517,   520,   520,   526,   527,   532,   531,
     536,   535,   540,   539,   547,   546,   554,   558,   559,   564,
     563,   568,   572,   573,   577,   578,   582,   583,   587,   591,
     592,   592,   600,   599,   605,   604,   612,   613,   618,   618,
     622,   622,   628,   630,   632,   634,   639,   640,   641,   642,
     643,   643,   649,   651,   653,   658,   662,   663,   667,   669,
     671,   673,   675,   680,   681
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "MUTABOR_TOKEN_IDENTIFIER",
  "MUTABOR_TOKEN_F_NUMBER", "MUTABOR_TOKEN_INTEGER",
  "MUTABOR_TOKEN_INTERVAL", "MUTABOR_TOKEN_ROOT", "MUTABOR_TOKEN_TONE",
  "MUTABOR_TOKEN_TONESYSTEM", "MUTABOR_TOKEN_RETUNING",
  "MUTABOR_TOKEN_HARMONY", "MUTABOR_TOKEN_LOGIC", "MUTABOR_TOKEN_FORM",
  "MUTABOR_TOKEN_MIDICHANNEL", "MUTABOR_TOKEN_KEY",
  "MUTABOR_TOKEN_MIDI_IN", "MUTABOR_TOKEN_MIDI_OUT", "MUTABOR_TOKEN_ELSE",
  "MUTABOR_TOKEN_SPACES", "MUTABOR_TOKEN_COMMENT",
  "MUTABOR_TOKEN_PARAMETER", "MUTABOR_TOKEN_OTHER", "MUTABOR_TOKEN_ERROR",
  "MUTABOR_TOKEN_ENDOFFILE", "'='", "':'", "'-'", "'+'", "'/'", "'['",
  "']'", "','", "'('", "')'", "'@'", "'<'", "'>'", "'*'", "'{'", "'}'",
  "'.'", "'~'", "$accept", "start", "intervalldeklaration",
  "intervalldekl1", "intervalldekl2_1", "$@1", "intervalldekl2",
  "tondeklaration", "tondekl1", "tondekl2_1", "$@2", "tondekl2",
  "KOMPLEX_TON_LIST", "KOMPLEX_TON_LIST_2", "KOMPLEX_TON_1",
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
     275,   276,   277,   278,   279,    61,    58,    45,    43,    47,
      91,    93,    44,    40,    41,    64,    60,    62,    42,   123,
     125,    46,   126
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    43,    44,    44,    44,    44,    44,    44,    44,    44,
      44,    45,    46,    46,    48,    47,    49,    49,    49,    49,
      49,    50,    51,    51,    53,    52,    54,    54,    54,    54,
      54,    55,    56,    56,    57,    57,    57,    57,    57,    57,
      57,    57,    58,    58,    58,    58,    59,    60,    60,    62,
      61,    64,    63,    65,    63,    66,    66,    67,    67,    67,
      68,    68,    68,    69,    69,    69,    70,    70,    70,    71,
      72,    72,    74,    75,    73,    76,    77,    73,    78,    78,
      78,    78,    78,    78,    78,    78,    78,    78,    78,    79,
      79,    80,    80,    80,    80,    81,    81,    82,    82,    82,
      82,    82,    82,    82,    82,    84,    83,    85,    85,    86,
      85,    87,    87,    88,    88,    89,    89,    90,    89,    91,
      89,    92,    89,    93,    89,    95,    94,    96,    94,    98,
      97,    99,    97,   101,   100,   102,   102,   103,   104,   103,
     105,   103,   107,   106,   108,   106,   109,   109,   111,   110,
     112,   110,   113,   110,   115,   114,   116,   117,   117,   119,
     118,   118,   120,   120,   121,   121,   122,   122,   123,   124,
     125,   124,   127,   126,   128,   126,   129,   129,   131,   130,
     132,   130,   133,   133,   133,   133,   134,   134,   134,   134,
     135,   134,   136,   136,   136,   137,   138,   138,   139,   139,
     139,   139,   139,   140,   140
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
       0,     5,     0,     5,     0,     5,     1,     2,     0,     5,
       0,     6,     0,     5,     0,     5,     2,     0,     2,     0,
       7,     3,     0,     2,     1,     3,     1,     2,     2,     0,
       0,     3,     0,     7,     0,     8,     0,     2,     0,     7,
       0,     5,     5,     3,     3,     1,     1,     1,     2,     2,
       0,     5,     1,     3,     1,     2,     0,     2,     4,     6,
       6,     7,     9,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,     0,     1,    10,    12,    22,    47,    70,   157,   169,
     196,     3,     4,     5,     6,     7,     8,     9,    11,    21,
      46,    69,   156,   168,   195,    13,     0,    23,     0,    48,
       0,    72,    71,     0,   158,     0,     0,   197,     0,    15,
       0,    25,     0,    50,     0,     0,     0,     0,   171,     0,
      20,     0,     0,     0,    73,     0,   161,   159,   185,     0,
       0,     0,     0,   186,   187,     0,     0,    19,    42,   203,
     204,     0,    18,    32,     0,    30,    28,    26,     0,     0,
      62,    60,     0,     0,     0,     0,   188,   189,   190,     0,
     198,     0,     0,    31,    43,     0,     0,     0,     0,     0,
       0,    88,     0,     0,     0,   105,     0,   133,    74,    78,
      79,    80,    81,    82,    83,    84,    85,    86,    87,     0,
       0,   166,     0,     0,   164,   183,   184,     0,     0,   172,
       0,     0,     0,    44,     0,     0,    33,    17,    16,     0,
      27,     0,    29,    59,    57,     0,    55,     0,   144,     0,
     142,   154,   125,     0,     0,     0,     0,     0,    61,    76,
     167,     0,   162,     0,   194,   192,     0,   174,   176,   199,
       0,   200,    35,     0,     0,    34,     0,     0,    45,    51,
       0,    90,     0,    89,     0,     0,     0,     0,     0,     0,
     115,   109,   116,     0,   107,     0,     0,     0,     0,   137,
       0,     0,   135,     0,   165,     0,   160,   182,     0,   191,
     176,     0,     0,   201,     0,    37,     0,     0,    36,     0,
       0,     0,    56,     0,     0,     0,     0,   146,     0,     0,
     131,   129,   126,     0,     0,     0,     0,   121,   117,   113,
     123,   119,   106,   113,     0,     0,     0,     0,   138,   140,
       0,   134,    77,   163,   193,     0,   173,   177,     0,     0,
      39,     0,    38,     0,    52,     0,     0,     0,     0,   145,
     147,   143,   155,     0,     0,   128,     0,     0,     0,     0,
       0,     0,     0,     0,   110,   111,   114,     0,     0,   108,
      94,    93,    92,    91,     0,     0,   136,   175,     0,   202,
      41,    40,    54,   148,   152,     0,   132,   130,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   122,   118,
     113,   124,   120,    65,    66,    67,     0,     0,    63,     0,
     180,     0,     0,   150,    96,    95,     0,     0,     0,     0,
       0,     0,     0,     0,   112,    68,     0,   139,   141,   178,
       0,   149,   153,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    64,     0,   181,   151,   100,    99,    98,    97,
     104,   103,   102,   101,     0,   179
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,    11,    18,    25,    26,    39,    12,    19,    27,
      28,    41,    72,    93,   136,    73,    13,    20,    29,    30,
      43,   220,   221,   145,   146,    82,   327,   328,    14,    21,
      32,    44,    79,    45,   203,   108,   109,   110,   111,   112,
     113,   154,   193,   239,   284,   285,   286,   283,   288,   282,
     287,   114,   187,   188,   115,   274,   273,   116,   157,   201,
     202,   294,   295,   117,   184,   182,   226,   227,   331,   353,
     332,   118,   185,    15,    22,    34,    83,   206,   123,   124,
      16,    23,    35,    48,   168,   210,   211,   257,   363,   350,
      64,   258,   127,   166,    17,    24,    37,   141
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -321
static const yytype_int16 yypact[] =
{
    -321,   143,  -321,  -321,  -321,  -321,  -321,  -321,  -321,  -321,
    -321,  -321,  -321,  -321,  -321,  -321,  -321,  -321,    38,    70,
      80,   100,   111,   115,   116,  -321,   135,  -321,   145,  -321,
     170,   187,  -321,   153,  -321,   216,   194,  -321,    30,  -321,
     162,  -321,   197,  -321,   198,   191,     6,   124,  -321,   195,
    -321,    66,   176,   220,  -321,    33,  -321,  -321,   185,   199,
     131,   223,   200,  -321,  -321,   203,    83,  -321,  -321,  -321,
    -321,   155,  -321,  -321,    56,  -321,   180,  -321,   201,     5,
    -321,  -321,   132,     4,   224,   227,  -321,  -321,  -321,    16,
      89,   229,   232,   182,  -321,   155,   155,   155,    88,    88,
      29,  -321,   -13,   102,   204,    84,   184,  -321,  -321,  -321,
    -321,  -321,  -321,  -321,  -321,  -321,  -321,  -321,  -321,   233,
     213,  -321,   234,   -19,  -321,  -321,   202,    13,   210,  -321,
     237,   238,   214,  -321,    94,    97,  -321,  -321,  -321,   243,
    -321,    36,  -321,  -321,  -321,   151,  -321,   217,  -321,   218,
    -321,  -321,   123,   211,    21,   160,   169,    93,  -321,  -321,
    -321,     4,   209,   246,  -321,  -321,   154,  -321,  -321,   222,
     225,  -321,  -321,   155,    51,  -321,   155,    55,  -321,   226,
      29,  -321,   106,  -321,   106,    13,   186,    88,   228,    22,
     188,  -321,   190,   230,   231,   235,   236,   239,   240,   221,
     241,   129,  -321,     5,  -321,   252,  -321,  -321,   253,  -321,
    -321,    59,   254,  -321,   257,  -321,   155,   259,  -321,   155,
      88,   244,  -321,   245,   248,   262,    10,  -321,    11,   159,
    -321,  -321,  -321,    88,   242,   247,   118,  -321,  -321,    17,
    -321,  -321,  -321,    17,   249,   250,   251,   255,  -321,  -321,
      93,  -321,  -321,  -321,  -321,    63,  -321,  -321,   256,   258,
    -321,   261,  -321,   265,  -321,    88,   260,   263,   264,  -321,
    -321,  -321,  -321,    88,    88,  -321,   266,   267,   189,   192,
     193,   196,    88,    88,   269,  -321,  -321,    88,    88,   269,
    -321,  -321,  -321,  -321,   103,    13,  -321,  -321,   268,  -321,
    -321,  -321,  -321,  -321,  -321,   270,  -321,  -321,   271,   275,
     272,   273,   274,   276,   277,   278,   279,   280,  -321,  -321,
      17,  -321,  -321,  -321,  -321,  -321,   282,   168,  -321,   171,
     281,    93,    93,  -321,  -321,  -321,   284,   285,   286,   287,
     288,   289,   290,   291,  -321,  -321,   104,  -321,  -321,  -321,
      93,   297,   297,    93,   299,   300,   301,   302,   303,   304,
     305,   306,  -321,    93,  -321,   297,  -321,  -321,  -321,  -321,
    -321,  -321,  -321,  -321,   130,  -321
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -321,  -321,  -321,  -321,  -321,  -321,  -321,  -321,  -321,  -321,
    -321,  -321,   -98,  -321,  -321,  -321,  -321,  -321,  -321,  -321,
    -321,  -321,  -321,  -321,    96,  -321,  -321,   -73,  -321,  -321,
    -321,  -321,  -321,  -321,  -321,    74,  -321,  -321,  -321,  -321,
    -321,  -321,  -321,  -321,    35,   -35,   134,  -321,  -321,  -321,
    -321,  -321,  -321,  -321,  -321,  -321,  -321,  -321,  -321,  -320,
    -245,  -321,  -321,  -321,  -321,  -321,   108,   -22,  -321,  -321,
    -321,  -321,  -321,  -321,  -321,  -321,  -321,  -321,  -321,   133,
    -321,  -321,  -321,  -321,  -321,  -321,    85,  -321,  -321,  -321,
     283,   292,  -321,  -183,  -321,  -321,  -321,   -48
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -171
static const yytype_int16 yytable[] =
{
     140,   142,   229,    74,    77,   296,   101,    56,   102,   121,
     103,   351,   352,   161,   164,   223,   223,   147,   165,   128,
     190,   162,   104,    92,   190,   234,   148,   235,   224,   224,
     143,    50,   144,   365,    80,   105,    81,   225,   225,    94,
     106,   -14,   122,   374,   107,    57,   129,   137,   138,   139,
     269,   271,   192,   191,   215,    51,   192,   236,   218,    94,
     -58,   -58,    58,    95,    59,    97,    58,    67,    59,    68,
      69,    70,    60,   -24,    61,    62,    60,    63,    61,    62,
     216,    63,    96,   -49,   219,    97,   174,   177,    90,   232,
     256,    68,    69,    70,   297,    71,   199,   172,    69,    70,
     175,    69,    70,    31,   323,   364,   324,   324,   325,   325,
     200,   223,   329,    91,    33,   152,   130,    71,  -170,   131,
     153,    36,   264,   173,   224,   214,   176,    58,   217,    59,
     326,   326,   149,   225,    58,   275,    59,    60,    38,    61,
      62,   150,    63,     2,     3,   278,   279,   280,    40,     4,
    -127,     5,     6,     7,     8,     9,   281,    10,   186,    69,
      70,   250,   250,   195,   119,   196,   120,   302,   261,   251,
     375,   263,   197,    42,   198,   306,   307,    75,    46,    76,
      69,    70,   179,   180,   318,   319,   208,    52,   209,   321,
     322,   208,   310,   272,   311,   312,   314,   313,   315,   316,
     346,   317,   347,   208,   270,   348,   270,    98,    99,   134,
     135,   155,   156,   230,   231,   237,   238,   240,   241,    47,
     -75,    49,    53,    54,    55,    78,    87,    84,    89,   125,
     126,   100,    66,    88,   132,   133,   158,   151,   159,   160,
     167,    85,   169,   170,   163,   171,   178,   189,   181,   183,
     205,   207,   212,   -53,   248,   233,   213,   253,   254,   259,
     260,   242,   262,   243,   300,   244,   245,   268,   301,   246,
     247,   265,   266,   362,   249,   267,   222,   252,   289,   276,
     290,   291,   292,   298,   277,   344,   293,   345,   194,   299,
       0,   305,   228,     0,   204,   255,     0,   303,     0,     0,
     304,   320,   334,   308,   309,   330,   335,   333,     0,   336,
     337,   338,     0,   339,   340,   341,   342,   343,     0,     0,
     349,   354,   355,   356,   357,   358,   359,   360,   361,   250,
     366,   367,   368,   369,   370,   371,   372,   373,     0,    65,
       0,     0,     0,    86
};

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-321)))

#define yytable_value_is_error(Yytable_value) \
  YYID (0)

static const yytype_int16 yycheck[] =
{
      98,    99,   185,    51,    52,   250,     1,     1,     3,     5,
       5,   331,   332,    32,     1,     5,     5,    30,     5,     3,
       3,    40,    17,    71,     3,     3,    39,     5,    18,    18,
       1,     1,     3,   353,     1,    30,     3,    27,    27,     3,
      35,     3,    38,   363,    39,    39,    30,    95,    96,    97,
      40,    40,    35,    32,     3,    25,    35,    35,     3,     3,
      31,    32,     3,     7,     5,    29,     3,     1,     5,     3,
       4,     5,    13,     3,    15,    16,    13,    18,    15,    16,
      29,    18,    26,     3,    29,    29,   134,   135,     5,   187,
      31,     3,     4,     5,    31,    29,     3,     3,     4,     5,
       3,     4,     5,     3,     1,   350,     3,     3,     5,     5,
      17,     5,   295,    30,     3,    31,    27,    29,     3,    30,
      36,     5,   220,    29,    18,   173,    29,     3,   176,     5,
      27,    27,    30,    27,     3,   233,     5,    13,     3,    15,
      16,    39,    18,     0,     1,    27,    28,    29,     3,     6,
      27,     8,     9,    10,    11,    12,    38,    14,    35,     4,
       5,    32,    32,     3,    32,     5,    34,   265,   216,    40,
      40,   219,     3,     3,     5,   273,   274,     1,    25,     3,
       4,     5,    31,    32,   282,   283,    32,    25,    34,   287,
     288,    32,     3,    34,     5,     3,     3,     5,     5,     3,
      32,     5,    34,    32,   226,    34,   228,    27,    28,    27,
      28,    27,    28,    27,    28,    27,    28,    27,    28,     3,
      33,    27,    25,    25,    33,     5,     3,    42,    25,     5,
       3,    30,    37,    33,     5,     3,     3,    33,    25,     5,
      30,    42,     5,     5,    42,    31,     3,    36,    31,    31,
      41,     5,    30,    27,    33,    27,    31,     5,     5,     5,
       3,    31,     3,    32,     3,    30,    30,     5,     3,    30,
      30,    27,    27,   346,    33,    27,   180,   203,   243,    37,
      31,    31,    31,    27,    37,   320,    31,     5,   154,    31,
      -1,    27,   184,    -1,   161,   210,    -1,    37,    -1,    -1,
      37,    32,    31,    37,    37,    37,    31,    37,    -1,    37,
      37,    37,    -1,    37,    37,    37,    37,    37,    -1,    -1,
      39,    37,    37,    37,    37,    37,    37,    37,    37,    32,
      31,    31,    31,    31,    31,    31,    31,    31,    -1,    47,
      -1,    -1,    -1,    60
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    44,     0,     1,     6,     8,     9,    10,    11,    12,
      14,    45,    50,    59,    71,   116,   123,   137,    46,    51,
      60,    72,   117,   124,   138,    47,    48,    52,    53,    61,
      62,     3,    73,     3,   118,   125,     5,   139,     3,    49,
       3,    54,     3,    63,    74,    76,    25,     3,   126,    27,
       1,    25,    25,    25,    25,    33,     1,    39,     3,     5,
      13,    15,    16,    18,   133,   134,    37,     1,     3,     4,
       5,    29,    55,    58,   140,     1,     3,   140,     5,    75,
       1,     3,    68,   119,    42,    42,   133,     3,    33,    25,
       5,    30,   140,    56,     3,     7,    26,    29,    27,    28,
      30,     1,     3,     5,    17,    30,    35,    39,    78,    79,
      80,    81,    82,    83,    94,    97,   100,   106,   114,    32,
      34,     5,    38,   121,   122,     5,     3,   135,     3,    30,
      27,    30,     5,     3,    27,    28,    57,   140,   140,   140,
      55,   140,    55,     1,     3,    66,    67,    30,    39,    30,
      39,    33,    31,    36,    84,    27,    28,   101,     3,    25,
       5,    32,    40,    42,     1,     5,   136,    30,   127,     5,
       5,    31,     3,    29,   140,     3,    29,   140,     3,    31,
      32,    31,   108,    31,   107,   115,    35,    95,    96,    36,
       3,    32,    35,    85,    89,     3,     5,     3,     5,     3,
      17,   102,   103,    77,   122,    41,   120,     5,    32,    34,
     128,   129,    30,    31,   140,     3,    29,   140,     3,    29,
      64,    65,    67,     5,    18,    27,   109,   110,   109,   136,
      27,    28,    55,    27,     3,     5,    35,    27,    28,    86,
      27,    28,    31,    32,    30,    30,    30,    30,    33,    33,
      32,    40,    78,     5,     5,   129,    31,   130,   134,     5,
       3,   140,     3,   140,    55,    27,    27,    27,     5,    40,
     110,    40,    34,    99,    98,    55,    37,    37,    27,    28,
      29,    38,    92,    90,    87,    88,    89,    93,    91,    87,
      31,    31,    31,    31,   104,   105,   103,    31,    27,    31,
       3,     3,    55,    37,    37,    27,    55,    55,    37,    37,
       3,     5,     3,     5,     3,     5,     3,     5,    55,    55,
      32,    55,    55,     1,     3,     5,    27,    69,    70,   136,
      37,   111,   113,    37,    31,    31,    37,    37,    37,    37,
      37,    37,    37,    37,    88,     5,    32,    34,    34,    39,
     132,   102,   102,   112,    37,    37,    37,    37,    37,    37,
      37,    37,    70,   131,   103,   102,    31,    31,    31,    31,
      31,    31,    31,    31,   102,    40
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
      yyerror (YY_("syntax error: cannot back up")); \
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
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
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
		  Type, Value, Location); \
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
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    YYLTYPE const * const yylocationp;
#endif
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
  YYUSE (yylocationp);
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
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep, yylocationp)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    YYLTYPE const * const yylocationp;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  YY_LOCATION_PRINT (yyoutput, *yylocationp);
  YYFPRINTF (yyoutput, ": ");
  yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp);
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
yy_reduce_print (YYSTYPE *yyvsp, YYLTYPE *yylsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yylsp, yyrule)
    YYSTYPE *yyvsp;
    YYLTYPE *yylsp;
    int yyrule;
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
		       , &(yylsp[(yyi + 1) - (yynrhs)])		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, yylsp, Rule); \
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
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
#else
static void
yydestruct (yymsg, yytype, yyvaluep, yylocationp)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
    YYLTYPE *yylocationp;
#endif
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YYUSE (yytype);
}




/* The lookahead symbol.  */
int yychar;


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
YYLTYPE yylloc
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;


/* Number of syntax errors so far.  */
int yynerrs;


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
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
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
#line 113 "../../../mutabor-git/src/kernel/mut.yy"
    {  fatal_error(1,FEHLERZEILE); }
    break;

  case 14:
/* Line 1787 of yacc.c  */
#line 125 "../../../mutabor-git/src/kernel/mut.yy"
    { init_komplex_ton_list (); }
    break;

  case 16:
/* Line 1787 of yacc.c  */
#line 130 "../../../mutabor-git/src/kernel/mut.yy"
    { if ( fabs((yyvsp[(5) - (5)].f_value)) > 0.001 )
                         get_new_intervall ((yyvsp[(1) - (5)].identifier), (yyvsp[(3) - (5)].f_value) / (yyvsp[(5) - (5)].f_value));
                      else
			fatal_error (46, mutC_STR((yyvsp[(1) - (5)].identifier)) ); }
    break;

  case 17:
/* Line 1787 of yacc.c  */
#line 136 "../../../mutabor-git/src/kernel/mut.yy"
    { if ( fabs ((yyvsp[(3) - (5)].f_value)) > 0.001 )
                          get_new_intervall ((yyvsp[(1) - (5)].identifier), pow ((yyvsp[(5) - (5)].f_value), 1 / (yyvsp[(3) - (5)].f_value)));
                      else
			fatal_error (46, mutC_STR((yyvsp[(1) - (5)].identifier))); }
    break;

  case 18:
/* Line 1787 of yacc.c  */
#line 145 "../../../mutabor-git/src/kernel/mut.yy"
    { get_new_intervall_komplex ((yyvsp[(1) - (3)].identifier)); }
    break;

  case 19:
/* Line 1787 of yacc.c  */
#line 146 "../../../mutabor-git/src/kernel/mut.yy"
    { fatal_error(71, mutC_STR((yyvsp[(1) - (3)].identifier))); }
    break;

  case 20:
/* Line 1787 of yacc.c  */
#line 147 "../../../mutabor-git/src/kernel/mut.yy"
    { fatal_error(70,mutT("="),FEHLERZEILE); }
    break;

  case 24:
/* Line 1787 of yacc.c  */
#line 159 "../../../mutabor-git/src/kernel/mut.yy"
    { init_komplex_ton_list (); }
    break;

  case 26:
/* Line 1787 of yacc.c  */
#line 164 "../../../mutabor-git/src/kernel/mut.yy"
    { get_new_ton_absolut ((yyvsp[(1) - (3)].identifier), (yyvsp[(3) - (3)].f_value)); }
    break;

  case 27:
/* Line 1787 of yacc.c  */
#line 168 "../../../mutabor-git/src/kernel/mut.yy"
    { get_new_ton_komplex_negative ((yyvsp[(1) - (5)].identifier), (yyvsp[(3) - (5)].identifier)); }
    break;

  case 28:
/* Line 1787 of yacc.c  */
#line 172 "../../../mutabor-git/src/kernel/mut.yy"
    { get_new_ton_komplex_positive ((yyvsp[(1) - (3)].identifier), (yyvsp[(3) - (3)].identifier)); }
    break;

  case 29:
/* Line 1787 of yacc.c  */
#line 176 "../../../mutabor-git/src/kernel/mut.yy"
    { get_new_ton_komplex_positive ((yyvsp[(1) - (5)].identifier), (yyvsp[(3) - (5)].identifier)); }
    break;

  case 30:
/* Line 1787 of yacc.c  */
#line 178 "../../../mutabor-git/src/kernel/mut.yy"
    { fatal_error( 72, mutC_STR((yyvsp[(1) - (3)].identifier)) ); }
    break;

  case 34:
/* Line 1787 of yacc.c  */
#line 192 "../../../mutabor-git/src/kernel/mut.yy"
    { get_new_faktor_anteil ( (double) 1, (yyvsp[(2) - (2)].identifier)); }
    break;

  case 35:
/* Line 1787 of yacc.c  */
#line 195 "../../../mutabor-git/src/kernel/mut.yy"
    { get_new_faktor_anteil ( (double) -1, (yyvsp[(2) - (2)].identifier)); }
    break;

  case 36:
/* Line 1787 of yacc.c  */
#line 198 "../../../mutabor-git/src/kernel/mut.yy"
    { get_new_faktor_anteil ( (yyvsp[(2) - (3)].f_value), (yyvsp[(3) - (3)].identifier)); }
    break;

  case 37:
/* Line 1787 of yacc.c  */
#line 201 "../../../mutabor-git/src/kernel/mut.yy"
    { get_new_faktor_anteil ( -((yyvsp[(2) - (3)].f_value)), (yyvsp[(3) - (3)].identifier)); }
    break;

  case 38:
/* Line 1787 of yacc.c  */
#line 204 "../../../mutabor-git/src/kernel/mut.yy"
    { if ( fabs((yyvsp[(3) - (4)].f_value)) > 0.001 )
                       get_new_faktor_anteil ( (double) 1 / ((yyvsp[(3) - (4)].f_value)), (yyvsp[(4) - (4)].identifier));
                     else
                       fatal_error(53, FEHLERZEILE);  }
    break;

  case 39:
/* Line 1787 of yacc.c  */
#line 210 "../../../mutabor-git/src/kernel/mut.yy"
    { if ( fabs((yyvsp[(3) - (4)].f_value)) > 0.001 )
                       get_new_faktor_anteil ( (double) -1 / ((yyvsp[(3) - (4)].f_value)), (yyvsp[(4) - (4)].identifier));
                     else
                       fatal_error(53, FEHLERZEILE);  }
    break;

  case 40:
/* Line 1787 of yacc.c  */
#line 216 "../../../mutabor-git/src/kernel/mut.yy"
    { if ( fabs((yyvsp[(4) - (5)].f_value)) > 0.001 )
                       get_new_faktor_anteil ( ((yyvsp[(2) - (5)].f_value)) / ((yyvsp[(4) - (5)].f_value)), (yyvsp[(5) - (5)].identifier));
                     else
                       fatal_error(53, FEHLERZEILE);  }
    break;

  case 41:
/* Line 1787 of yacc.c  */
#line 222 "../../../mutabor-git/src/kernel/mut.yy"
    { if ( fabs((yyvsp[(4) - (5)].f_value)) > 0.001 )
                       get_new_faktor_anteil ( -((yyvsp[(2) - (5)].f_value)) / ((yyvsp[(4) - (5)].f_value)), (yyvsp[(5) - (5)].identifier));
                     else
                       fatal_error(53, FEHLERZEILE);  }
    break;

  case 42:
/* Line 1787 of yacc.c  */
#line 243 "../../../mutabor-git/src/kernel/mut.yy"
    { get_new_faktor_anteil ( (double) 1.0 , (yyvsp[(1) - (1)].identifier)); }
    break;

  case 43:
/* Line 1787 of yacc.c  */
#line 251 "../../../mutabor-git/src/kernel/mut.yy"
    { get_new_faktor_anteil ( (yyvsp[(1) - (2)].f_value), (yyvsp[(2) - (2)].identifier)); }
    break;

  case 44:
/* Line 1787 of yacc.c  */
#line 254 "../../../mutabor-git/src/kernel/mut.yy"
    { if ( fabs((yyvsp[(2) - (3)].f_value)) > 0.001 )
                       get_new_faktor_anteil ( (double) 1 / ((yyvsp[(2) - (3)].f_value)), (yyvsp[(3) - (3)].identifier));
                     else
                       fatal_error(53, FEHLERZEILE);  }
    break;

  case 45:
/* Line 1787 of yacc.c  */
#line 260 "../../../mutabor-git/src/kernel/mut.yy"
    { if ( fabs((yyvsp[(3) - (4)].f_value)) > 0.001 )
                       get_new_faktor_anteil ( ((yyvsp[(1) - (4)].f_value)) / ((yyvsp[(3) - (4)].f_value)), (yyvsp[(4) - (4)].identifier));
                     else
                       fatal_error(53, FEHLERZEILE);  }
    break;

  case 49:
/* Line 1787 of yacc.c  */
#line 293 "../../../mutabor-git/src/kernel/mut.yy"
    { init_ton_liste (); }
    break;

  case 51:
/* Line 1787 of yacc.c  */
#line 298 "../../../mutabor-git/src/kernel/mut.yy"
    { init_komplex_ton_list (); }
    break;

  case 52:
/* Line 1787 of yacc.c  */
#line 300 "../../../mutabor-git/src/kernel/mut.yy"
    { get_new_tonsystem ((yyvsp[(1) - (8)].identifier), (yyvsp[(3) - (8)].integer)); }
    break;

  case 53:
/* Line 1787 of yacc.c  */
#line 302 "../../../mutabor-git/src/kernel/mut.yy"
    { init_komplex_ton_list (); }
    break;

  case 54:
/* Line 1787 of yacc.c  */
#line 304 "../../../mutabor-git/src/kernel/mut.yy"
    { get_new_tonsystem_negative ((yyvsp[(1) - (9)].identifier), (yyvsp[(3) - (9)].integer)); }
    break;

  case 57:
/* Line 1787 of yacc.c  */
#line 310 "../../../mutabor-git/src/kernel/mut.yy"
    { get_new_ton_in_tonsystem ((yyvsp[(1) - (1)].identifier)); }
    break;

  case 58:
/* Line 1787 of yacc.c  */
#line 311 "../../../mutabor-git/src/kernel/mut.yy"
    { get_new_ton_in_tonsystem (NULL); }
    break;

  case 59:
/* Line 1787 of yacc.c  */
#line 312 "../../../mutabor-git/src/kernel/mut.yy"
    { fatal_error(73,FEHLERZEILE); }
    break;

  case 60:
/* Line 1787 of yacc.c  */
#line 316 "../../../mutabor-git/src/kernel/mut.yy"
    { get_new_name_in_parameterlist ((yyvsp[(1) - (1)].identifier)); }
    break;

  case 61:
/* Line 1787 of yacc.c  */
#line 318 "../../../mutabor-git/src/kernel/mut.yy"
    { get_new_name_in_parameterlist ((yyvsp[(3) - (3)].identifier)); }
    break;

  case 62:
/* Line 1787 of yacc.c  */
#line 319 "../../../mutabor-git/src/kernel/mut.yy"
    { fatal_error(74,FEHLERZEILE); }
    break;

  case 63:
/* Line 1787 of yacc.c  */
#line 324 "../../../mutabor-git/src/kernel/mut.yy"
    {}
    break;

  case 64:
/* Line 1787 of yacc.c  */
#line 325 "../../../mutabor-git/src/kernel/mut.yy"
    {}
    break;

  case 65:
/* Line 1787 of yacc.c  */
#line 326 "../../../mutabor-git/src/kernel/mut.yy"
    { fatal_error(74,FEHLERZEILE); }
    break;

  case 66:
/* Line 1787 of yacc.c  */
#line 331 "../../../mutabor-git/src/kernel/mut.yy"
    { get_new_name_in_argument_list ((yyvsp[(1) - (1)].identifier)) ;  }
    break;

  case 67:
/* Line 1787 of yacc.c  */
#line 332 "../../../mutabor-git/src/kernel/mut.yy"
    { get_new_number_in_argument_list ((yyvsp[(1) - (1)].integer)) ;  }
    break;

  case 68:
/* Line 1787 of yacc.c  */
#line 333 "../../../mutabor-git/src/kernel/mut.yy"
    { get_new_number_in_argument_list (-((yyvsp[(2) - (2)].integer))); }
    break;

  case 72:
/* Line 1787 of yacc.c  */
#line 348 "../../../mutabor-git/src/kernel/mut.yy"
    { init_umstimmung ((yyvsp[(1) - (1)].identifier));
                      init_parameter_liste (); }
    break;

  case 73:
/* Line 1787 of yacc.c  */
#line 350 "../../../mutabor-git/src/kernel/mut.yy"
    { eintrage_parameterliste_in_umstimmung (); }
    break;

  case 74:
/* Line 1787 of yacc.c  */
#line 352 "../../../mutabor-git/src/kernel/mut.yy"
    { get_new_umstimmung (); }
    break;

  case 75:
/* Line 1787 of yacc.c  */
#line 355 "../../../mutabor-git/src/kernel/mut.yy"
    { init_umstimmung ((yyvsp[(1) - (1)].identifier));
                      init_parameter_liste (); }
    break;

  case 76:
/* Line 1787 of yacc.c  */
#line 358 "../../../mutabor-git/src/kernel/mut.yy"
    { eintrage_parameterliste_in_umstimmung (); }
    break;

  case 77:
/* Line 1787 of yacc.c  */
#line 360 "../../../mutabor-git/src/kernel/mut.yy"
    { get_new_umstimmung (); }
    break;

  case 78:
/* Line 1787 of yacc.c  */
#line 364 "../../../mutabor-git/src/kernel/mut.yy"
    {}
    break;

  case 79:
/* Line 1787 of yacc.c  */
#line 365 "../../../mutabor-git/src/kernel/mut.yy"
    {}
    break;

  case 80:
/* Line 1787 of yacc.c  */
#line 366 "../../../mutabor-git/src/kernel/mut.yy"
    {}
    break;

  case 81:
/* Line 1787 of yacc.c  */
#line 367 "../../../mutabor-git/src/kernel/mut.yy"
    {}
    break;

  case 82:
/* Line 1787 of yacc.c  */
#line 368 "../../../mutabor-git/src/kernel/mut.yy"
    {}
    break;

  case 83:
/* Line 1787 of yacc.c  */
#line 369 "../../../mutabor-git/src/kernel/mut.yy"
    {}
    break;

  case 84:
/* Line 1787 of yacc.c  */
#line 370 "../../../mutabor-git/src/kernel/mut.yy"
    {}
    break;

  case 85:
/* Line 1787 of yacc.c  */
#line 371 "../../../mutabor-git/src/kernel/mut.yy"
    {}
    break;

  case 86:
/* Line 1787 of yacc.c  */
#line 372 "../../../mutabor-git/src/kernel/mut.yy"
    {}
    break;

  case 87:
/* Line 1787 of yacc.c  */
#line 373 "../../../mutabor-git/src/kernel/mut.yy"
    {}
    break;

  case 88:
/* Line 1787 of yacc.c  */
#line 374 "../../../mutabor-git/src/kernel/mut.yy"
    {fatal_error(75,FEHLERZEILE);}
    break;

  case 89:
/* Line 1787 of yacc.c  */
#line 380 "../../../mutabor-git/src/kernel/mut.yy"
    { get_umstimmung_taste_abs (zahl, (yyvsp[(1) - (3)].integer), NULL); }
    break;

  case 90:
/* Line 1787 of yacc.c  */
#line 382 "../../../mutabor-git/src/kernel/mut.yy"
    { get_umstimmung_taste_abs (parameter, 0.0, (yyvsp[(1) - (3)].identifier)); }
    break;

  case 91:
/* Line 1787 of yacc.c  */
#line 387 "../../../mutabor-git/src/kernel/mut.yy"
    { get_umstimmung_taste_rel (zahl, (yyvsp[(3) - (5)].integer), NULL, '+'); }
    break;

  case 92:
/* Line 1787 of yacc.c  */
#line 389 "../../../mutabor-git/src/kernel/mut.yy"
    { get_umstimmung_taste_rel (parameter, 0.0, (yyvsp[(3) - (5)].identifier), '+'); }
    break;

  case 93:
/* Line 1787 of yacc.c  */
#line 391 "../../../mutabor-git/src/kernel/mut.yy"
    { get_umstimmung_taste_rel (zahl, (yyvsp[(3) - (5)].integer), NULL, '-'); }
    break;

  case 94:
/* Line 1787 of yacc.c  */
#line 393 "../../../mutabor-git/src/kernel/mut.yy"
    { get_umstimmung_taste_rel (parameter, 0.0, (yyvsp[(3) - (5)].identifier), '-'); }
    break;

  case 95:
/* Line 1787 of yacc.c  */
#line 398 "../../../mutabor-git/src/kernel/mut.yy"
    { get_umstimmung_breite_abs (zahl, (yyvsp[(4) - (7)].integer), NULL); }
    break;

  case 96:
/* Line 1787 of yacc.c  */
#line 400 "../../../mutabor-git/src/kernel/mut.yy"
    { get_umstimmung_breite_abs (parameter, 0.0, (yyvsp[(4) - (7)].identifier)); }
    break;

  case 97:
/* Line 1787 of yacc.c  */
#line 405 "../../../mutabor-git/src/kernel/mut.yy"
    { get_umstimmung_breite_rel (zahl, (yyvsp[(6) - (9)].integer), NULL, '+'); }
    break;

  case 98:
/* Line 1787 of yacc.c  */
#line 407 "../../../mutabor-git/src/kernel/mut.yy"
    { get_umstimmung_breite_rel (parameter, 0.0, (yyvsp[(6) - (9)].identifier), '+'); }
    break;

  case 99:
/* Line 1787 of yacc.c  */
#line 409 "../../../mutabor-git/src/kernel/mut.yy"
    { get_umstimmung_breite_rel (zahl, (yyvsp[(6) - (9)].integer), NULL, '-'); }
    break;

  case 100:
/* Line 1787 of yacc.c  */
#line 411 "../../../mutabor-git/src/kernel/mut.yy"
    { get_umstimmung_breite_rel (parameter, 0.0, (yyvsp[(6) - (9)].identifier), '-'); }
    break;

  case 101:
/* Line 1787 of yacc.c  */
#line 413 "../../../mutabor-git/src/kernel/mut.yy"
    { get_umstimmung_breite_rel (zahl, (yyvsp[(6) - (9)].integer), NULL, '*'); }
    break;

  case 102:
/* Line 1787 of yacc.c  */
#line 415 "../../../mutabor-git/src/kernel/mut.yy"
    { get_umstimmung_breite_rel (parameter, 0.0, (yyvsp[(6) - (9)].identifier), '*'); }
    break;

  case 103:
/* Line 1787 of yacc.c  */
#line 417 "../../../mutabor-git/src/kernel/mut.yy"
    { get_umstimmung_breite_rel (zahl, (yyvsp[(6) - (9)].integer), NULL, '/'); }
    break;

  case 104:
/* Line 1787 of yacc.c  */
#line 419 "../../../mutabor-git/src/kernel/mut.yy"
    { get_umstimmung_breite_rel (parameter, 0.0, (yyvsp[(6) - (9)].identifier), '/'); }
    break;

  case 105:
/* Line 1787 of yacc.c  */
#line 424 "../../../mutabor-git/src/kernel/mut.yy"
    { init_umstimm_expression_list (); }
    break;

  case 106:
/* Line 1787 of yacc.c  */
#line 426 "../../../mutabor-git/src/kernel/mut.yy"
    { get_umstimmung_tonhoehe_veraendert (); }
    break;

  case 107:
/* Line 1787 of yacc.c  */
#line 433 "../../../mutabor-git/src/kernel/mut.yy"
    {}
    break;

  case 108:
/* Line 1787 of yacc.c  */
#line 434 "../../../mutabor-git/src/kernel/mut.yy"
    {}
    break;

  case 109:
/* Line 1787 of yacc.c  */
#line 436 "../../../mutabor-git/src/kernel/mut.yy"
    { init_komplex_ton_list();
                     get_new_umstimm_expression (NULL);
                   }
    break;

  case 110:
/* Line 1787 of yacc.c  */
#line 439 "../../../mutabor-git/src/kernel/mut.yy"
    {}
    break;

  case 111:
/* Line 1787 of yacc.c  */
#line 443 "../../../mutabor-git/src/kernel/mut.yy"
    {}
    break;

  case 112:
/* Line 1787 of yacc.c  */
#line 444 "../../../mutabor-git/src/kernel/mut.yy"
    {}
    break;

  case 113:
/* Line 1787 of yacc.c  */
#line 449 "../../../mutabor-git/src/kernel/mut.yy"
    { init_komplex_ton_list();
                     get_new_umstimm_expression (NULL);
                   }
    break;

  case 115:
/* Line 1787 of yacc.c  */
#line 457 "../../../mutabor-git/src/kernel/mut.yy"
    { get_new_umstimm_expression ((yyvsp[(1) - (1)].identifier)); }
    break;

  case 116:
/* Line 1787 of yacc.c  */
#line 458 "../../../mutabor-git/src/kernel/mut.yy"
    { get_new_umstimm_expression ("@"); }
    break;

  case 117:
/* Line 1787 of yacc.c  */
#line 460 "../../../mutabor-git/src/kernel/mut.yy"
    { init_komplex_ton_list (); }
    break;

  case 118:
/* Line 1787 of yacc.c  */
#line 462 "../../../mutabor-git/src/kernel/mut.yy"
    { get_new_umstimm_expression_positive ((yyvsp[(1) - (4)].identifier)); }
    break;

  case 119:
/* Line 1787 of yacc.c  */
#line 463 "../../../mutabor-git/src/kernel/mut.yy"
    { init_komplex_ton_list (); }
    break;

  case 120:
/* Line 1787 of yacc.c  */
#line 465 "../../../mutabor-git/src/kernel/mut.yy"
    { get_new_umstimm_expression_positive ( "@" ); }
    break;

  case 121:
/* Line 1787 of yacc.c  */
#line 466 "../../../mutabor-git/src/kernel/mut.yy"
    { init_komplex_ton_list (); }
    break;

  case 122:
/* Line 1787 of yacc.c  */
#line 468 "../../../mutabor-git/src/kernel/mut.yy"
    { get_new_umstimm_expression_negative ((yyvsp[(1) - (4)].identifier)); }
    break;

  case 123:
/* Line 1787 of yacc.c  */
#line 469 "../../../mutabor-git/src/kernel/mut.yy"
    { init_komplex_ton_list (); }
    break;

  case 124:
/* Line 1787 of yacc.c  */
#line 471 "../../../mutabor-git/src/kernel/mut.yy"
    { get_new_umstimm_expression_negative ( "@" ); }
    break;

  case 125:
/* Line 1787 of yacc.c  */
#line 476 "../../../mutabor-git/src/kernel/mut.yy"
    { init_komplex_ton_list (); }
    break;

  case 126:
/* Line 1787 of yacc.c  */
#line 478 "../../../mutabor-git/src/kernel/mut.yy"
    { get_umstimmung_wiederholung_abs (); }
    break;

  case 127:
/* Line 1787 of yacc.c  */
#line 479 "../../../mutabor-git/src/kernel/mut.yy"
    { init_komplex_ton_list (); }
    break;

  case 128:
/* Line 1787 of yacc.c  */
#line 481 "../../../mutabor-git/src/kernel/mut.yy"
    { get_umstimmung_wiederholung_abs_negative (); }
    break;

  case 129:
/* Line 1787 of yacc.c  */
#line 485 "../../../mutabor-git/src/kernel/mut.yy"
    { init_komplex_ton_list (); }
    break;

  case 130:
/* Line 1787 of yacc.c  */
#line 487 "../../../mutabor-git/src/kernel/mut.yy"
    { get_umstimmung_wiederholung_rel_positive (); }
    break;

  case 131:
/* Line 1787 of yacc.c  */
#line 488 "../../../mutabor-git/src/kernel/mut.yy"
    { init_komplex_ton_list (); }
    break;

  case 132:
/* Line 1787 of yacc.c  */
#line 490 "../../../mutabor-git/src/kernel/mut.yy"
    { get_umstimmung_wiederholung_rel_negative (); }
    break;

  case 133:
/* Line 1787 of yacc.c  */
#line 494 "../../../mutabor-git/src/kernel/mut.yy"
    { init_aktions_liste (); }
    break;

  case 134:
/* Line 1787 of yacc.c  */
#line 496 "../../../mutabor-git/src/kernel/mut.yy"
    { get_umstimmung_umstimmungs_bund (); }
    break;

  case 135:
/* Line 1787 of yacc.c  */
#line 500 "../../../mutabor-git/src/kernel/mut.yy"
    {}
    break;

  case 136:
/* Line 1787 of yacc.c  */
#line 501 "../../../mutabor-git/src/kernel/mut.yy"
    {}
    break;

  case 137:
/* Line 1787 of yacc.c  */
#line 505 "../../../mutabor-git/src/kernel/mut.yy"
    { init_argument_liste (); 
                       get_new_aktion_aufruf_element ((yyvsp[(1) - (1)].identifier)); }
    break;

  case 138:
/* Line 1787 of yacc.c  */
#line 507 "../../../mutabor-git/src/kernel/mut.yy"
    { init_argument_liste (); }
    break;

  case 139:
/* Line 1787 of yacc.c  */
#line 509 "../../../mutabor-git/src/kernel/mut.yy"
    { get_new_aktion_aufruf_element ((yyvsp[(1) - (5)].identifier)); }
    break;

  case 140:
/* Line 1787 of yacc.c  */
#line 511 "../../../mutabor-git/src/kernel/mut.yy"
    { init_integersequenz ();}
    break;

  case 141:
/* Line 1787 of yacc.c  */
#line 513 "../../../mutabor-git/src/kernel/mut.yy"
    { get_new_aktion_midi_out_element (); }
    break;

  case 142:
/* Line 1787 of yacc.c  */
#line 517 "../../../mutabor-git/src/kernel/mut.yy"
    { init_umstimmungs_case_liste (); }
    break;

  case 143:
/* Line 1787 of yacc.c  */
#line 519 "../../../mutabor-git/src/kernel/mut.yy"
    { get_umstimmung_umstimm_case_zahl ((yyvsp[(1) - (5)].integer)); }
    break;

  case 144:
/* Line 1787 of yacc.c  */
#line 520 "../../../mutabor-git/src/kernel/mut.yy"
    { init_umstimmungs_case_liste (); }
    break;

  case 145:
/* Line 1787 of yacc.c  */
#line 522 "../../../mutabor-git/src/kernel/mut.yy"
    { get_umstimmung_umstimm_case_parameter ((yyvsp[(1) - (5)].identifier)); }
    break;

  case 146:
/* Line 1787 of yacc.c  */
#line 526 "../../../mutabor-git/src/kernel/mut.yy"
    {}
    break;

  case 147:
/* Line 1787 of yacc.c  */
#line 527 "../../../mutabor-git/src/kernel/mut.yy"
    {}
    break;

  case 148:
/* Line 1787 of yacc.c  */
#line 532 "../../../mutabor-git/src/kernel/mut.yy"
    { init_aktions_liste (); }
    break;

  case 149:
/* Line 1787 of yacc.c  */
#line 534 "../../../mutabor-git/src/kernel/mut.yy"
    { get_umstimmungs_case_zahl_element ((yyvsp[(1) - (5)].integer)); }
    break;

  case 150:
/* Line 1787 of yacc.c  */
#line 536 "../../../mutabor-git/src/kernel/mut.yy"
    { init_aktions_liste (); }
    break;

  case 151:
/* Line 1787 of yacc.c  */
#line 538 "../../../mutabor-git/src/kernel/mut.yy"
    { get_umstimmungs_case_zahl_element (-((yyvsp[(2) - (6)].integer))); }
    break;

  case 152:
/* Line 1787 of yacc.c  */
#line 540 "../../../mutabor-git/src/kernel/mut.yy"
    { init_aktions_liste (); }
    break;

  case 153:
/* Line 1787 of yacc.c  */
#line 542 "../../../mutabor-git/src/kernel/mut.yy"
    { get_umstimmungs_case_default_element (); }
    break;

  case 154:
/* Line 1787 of yacc.c  */
#line 547 "../../../mutabor-git/src/kernel/mut.yy"
    { init_integersequenz ();}
    break;

  case 155:
/* Line 1787 of yacc.c  */
#line 549 "../../../mutabor-git/src/kernel/mut.yy"
    { get_umstimmung_midi_out (); }
    break;

  case 156:
/* Line 1787 of yacc.c  */
#line 554 "../../../mutabor-git/src/kernel/mut.yy"
    {}
    break;

  case 157:
/* Line 1787 of yacc.c  */
#line 558 "../../../mutabor-git/src/kernel/mut.yy"
    {}
    break;

  case 158:
/* Line 1787 of yacc.c  */
#line 559 "../../../mutabor-git/src/kernel/mut.yy"
    {}
    break;

  case 159:
/* Line 1787 of yacc.c  */
#line 564 "../../../mutabor-git/src/kernel/mut.yy"
    { init_tastenliste (); }
    break;

  case 160:
/* Line 1787 of yacc.c  */
#line 566 "../../../mutabor-git/src/kernel/mut.yy"
    { get_new_harmonie ((yyvsp[(1) - (7)].identifier), (yyvsp[(7) - (7)].integer)); }
    break;

  case 161:
/* Line 1787 of yacc.c  */
#line 568 "../../../mutabor-git/src/kernel/mut.yy"
    { fatal_error(76, mutC_STR((yyvsp[(1) - (3)].identifier))); }
    break;

  case 162:
/* Line 1787 of yacc.c  */
#line 572 "../../../mutabor-git/src/kernel/mut.yy"
    { (yyval.integer) = -1; }
    break;

  case 163:
/* Line 1787 of yacc.c  */
#line 573 "../../../mutabor-git/src/kernel/mut.yy"
    { (yyval.integer) = (yyvsp[(2) - (2)].integer); }
    break;

  case 164:
/* Line 1787 of yacc.c  */
#line 577 "../../../mutabor-git/src/kernel/mut.yy"
    {}
    break;

  case 165:
/* Line 1787 of yacc.c  */
#line 578 "../../../mutabor-git/src/kernel/mut.yy"
    {}
    break;

  case 166:
/* Line 1787 of yacc.c  */
#line 582 "../../../mutabor-git/src/kernel/mut.yy"
    { get_new_taste ( (yyvsp[(1) - (1)].integer), '+'); }
    break;

  case 167:
/* Line 1787 of yacc.c  */
#line 583 "../../../mutabor-git/src/kernel/mut.yy"
    { get_new_taste ( (yyvsp[(2) - (2)].integer), '*'); }
    break;

  case 168:
/* Line 1787 of yacc.c  */
#line 587 "../../../mutabor-git/src/kernel/mut.yy"
    {}
    break;

  case 169:
/* Line 1787 of yacc.c  */
#line 591 "../../../mutabor-git/src/kernel/mut.yy"
    {}
    break;

  case 170:
/* Line 1787 of yacc.c  */
#line 592 "../../../mutabor-git/src/kernel/mut.yy"
    { init_ausloeser ();
                         /* fr die Anfangsausloesung der Logik */
                       }
    break;

  case 171:
/* Line 1787 of yacc.c  */
#line 595 "../../../mutabor-git/src/kernel/mut.yy"
    {}
    break;

  case 172:
/* Line 1787 of yacc.c  */
#line 600 "../../../mutabor-git/src/kernel/mut.yy"
    { get_new_logik ((yyvsp[(1) - (4)].identifier), NULL);
                init_anweisungs_liste (); }
    break;

  case 173:
/* Line 1787 of yacc.c  */
#line 603 "../../../mutabor-git/src/kernel/mut.yy"
    { vervollstaendige_logik (); }
    break;

  case 174:
/* Line 1787 of yacc.c  */
#line 605 "../../../mutabor-git/src/kernel/mut.yy"
    { get_new_logik ((yyvsp[(1) - (5)].identifier), (yyvsp[(4) - (5)].identifier));
                init_anweisungs_liste (); }
    break;

  case 175:
/* Line 1787 of yacc.c  */
#line 608 "../../../mutabor-git/src/kernel/mut.yy"
    { vervollstaendige_logik (); }
    break;

  case 176:
/* Line 1787 of yacc.c  */
#line 612 "../../../mutabor-git/src/kernel/mut.yy"
    {}
    break;

  case 177:
/* Line 1787 of yacc.c  */
#line 613 "../../../mutabor-git/src/kernel/mut.yy"
    {}
    break;

  case 178:
/* Line 1787 of yacc.c  */
#line 618 "../../../mutabor-git/src/kernel/mut.yy"
    { init_aktions_liste (); }
    break;

  case 179:
/* Line 1787 of yacc.c  */
#line 620 "../../../mutabor-git/src/kernel/mut.yy"
    { get_new_anweisung (); }
    break;

  case 180:
/* Line 1787 of yacc.c  */
#line 622 "../../../mutabor-git/src/kernel/mut.yy"
    { init_aktions_liste (); }
    break;

  case 181:
/* Line 1787 of yacc.c  */
#line 624 "../../../mutabor-git/src/kernel/mut.yy"
    { get_new_anweisung (); }
    break;

  case 182:
/* Line 1787 of yacc.c  */
#line 629 "../../../mutabor-git/src/kernel/mut.yy"
    { get_harmoniebezeichner (  (yyvsp[(1) - (5)].integer), (yyvsp[(3) - (5)].identifier),  (yyvsp[(5) - (5)].integer)); }
    break;

  case 183:
/* Line 1787 of yacc.c  */
#line 631 "../../../mutabor-git/src/kernel/mut.yy"
    { get_harmoniebezeichner (-1, (yyvsp[(1) - (3)].identifier),  (yyvsp[(3) - (3)].integer)); }
    break;

  case 184:
/* Line 1787 of yacc.c  */
#line 633 "../../../mutabor-git/src/kernel/mut.yy"
    { get_harmoniebezeichner (  (yyvsp[(1) - (3)].integer), (yyvsp[(3) - (3)].identifier), -1); }
    break;

  case 185:
/* Line 1787 of yacc.c  */
#line 635 "../../../mutabor-git/src/kernel/mut.yy"
    { get_harmoniebezeichner (-1, (yyvsp[(1) - (1)].identifier), -1); }
    break;

  case 186:
/* Line 1787 of yacc.c  */
#line 639 "../../../mutabor-git/src/kernel/mut.yy"
    { get_ausloeser_default (); }
    break;

  case 187:
/* Line 1787 of yacc.c  */
#line 640 "../../../mutabor-git/src/kernel/mut.yy"
    { get_ausloeser_harmonie (); }
    break;

  case 188:
/* Line 1787 of yacc.c  */
#line 641 "../../../mutabor-git/src/kernel/mut.yy"
    { get_ausloeser_harmonie_form (); }
    break;

  case 189:
/* Line 1787 of yacc.c  */
#line 642 "../../../mutabor-git/src/kernel/mut.yy"
    { get_ausloeser_taste ((yyvsp[(2) - (2)].identifier)); }
    break;

  case 190:
/* Line 1787 of yacc.c  */
#line 643 "../../../mutabor-git/src/kernel/mut.yy"
    { init_integersequenz (); }
    break;

  case 191:
/* Line 1787 of yacc.c  */
#line 645 "../../../mutabor-git/src/kernel/mut.yy"
    { get_ausloeser_midi_in (); }
    break;

  case 192:
/* Line 1787 of yacc.c  */
#line 650 "../../../mutabor-git/src/kernel/mut.yy"
    { get_new_integer_in_integersequenz ((yyvsp[(1) - (1)].integer));}
    break;

  case 193:
/* Line 1787 of yacc.c  */
#line 652 "../../../mutabor-git/src/kernel/mut.yy"
    { get_new_integer_in_integersequenz ((yyvsp[(3) - (3)].integer));}
    break;

  case 194:
/* Line 1787 of yacc.c  */
#line 653 "../../../mutabor-git/src/kernel/mut.yy"
    { fatal_error( 77, FEHLERZEILE ); }
    break;

  case 195:
/* Line 1787 of yacc.c  */
#line 658 "../../../mutabor-git/src/kernel/mut.yy"
    {}
    break;

  case 196:
/* Line 1787 of yacc.c  */
#line 662 "../../../mutabor-git/src/kernel/mut.yy"
    {}
    break;

  case 197:
/* Line 1787 of yacc.c  */
#line 663 "../../../mutabor-git/src/kernel/mut.yy"
    {}
    break;

  case 198:
/* Line 1787 of yacc.c  */
#line 668 "../../../mutabor-git/src/kernel/mut.yy"
    { get_instrument_dekl ((yyvsp[(1) - (4)].integer), (yyvsp[(4) - (4)].integer), (yyvsp[(4) - (4)].integer), 0, & list_of_instrumente); }
    break;

  case 199:
/* Line 1787 of yacc.c  */
#line 670 "../../../mutabor-git/src/kernel/mut.yy"
    { get_instrument_dekl ((yyvsp[(1) - (6)].integer), (yyvsp[(4) - (6)].integer), (yyvsp[(6) - (6)].integer), 0, & list_of_instrumente); }
    break;

  case 200:
/* Line 1787 of yacc.c  */
#line 672 "../../../mutabor-git/src/kernel/mut.yy"
    { get_instrument_dekl ((yyvsp[(1) - (6)].integer), 0, 0, (yyvsp[(5) - (6)].integer), & list_of_instrumente); }
    break;

  case 201:
/* Line 1787 of yacc.c  */
#line 674 "../../../mutabor-git/src/kernel/mut.yy"
    { get_instrument_dekl ((yyvsp[(1) - (7)].integer), (yyvsp[(4) - (7)].integer), (yyvsp[(4) - (7)].integer), (yyvsp[(6) - (7)].integer), & list_of_instrumente); }
    break;

  case 202:
/* Line 1787 of yacc.c  */
#line 676 "../../../mutabor-git/src/kernel/mut.yy"
    { get_instrument_dekl ((yyvsp[(1) - (9)].integer), (yyvsp[(4) - (9)].integer), (yyvsp[(6) - (9)].integer), (yyvsp[(8) - (9)].integer), & list_of_instrumente); }
    break;

  case 203:
/* Line 1787 of yacc.c  */
#line 680 "../../../mutabor-git/src/kernel/mut.yy"
    { (yyval.f_value) = (yyvsp[(1) - (1)].f_value) ; }
    break;

  case 204:
/* Line 1787 of yacc.c  */
#line 681 "../../../mutabor-git/src/kernel/mut.yy"
    { (yyval.f_value) = (double) (yyvsp[(1) - (1)].integer) ; }
    break;


/* Line 1787 of yacc.c  */
#line 2993 "../../../mutabor-git/src/kernel/mut.cc"
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
        yyerror (yymsgp);
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
		      yytoken, &yylval, &yylloc);
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
		  yystos[yystate], yyvsp, yylsp);
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
  yyerror (YY_("memory exhausted"));
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
                  yytoken, &yylval, &yylloc);
    }
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp, yylsp);
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
#line 685 "../../../mutabor-git/src/kernel/mut.yy"

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

int yylex(void) 
{
    int c;

start_lex:

    /* Ignore whitespace, get first nonwhitespace character */
    while ( anzahl_eingelesene_zeichen ++,

            isspace(c = toupper( intern_fgetc(quelldatei) ))) {
	DEBUGLOG2(other,_T("char %x"),c);

      if (c == '\n') {
	DEBUGLOG2(other,_T("New line"));
	if (!(yylloc.first_line ++ % LINE_DRAW_QUANTUM)) 
	  show_line_number(yylloc.first_line);
      }
    }
    
    if (c == '"') {
       while (anzahl_eingelesene_zeichen ++,
       
              (c=intern_fgetc(quelldatei)) != '"' && c != EOF )
                    if (c == '\n') yylloc.first_line ++;
        
       goto start_lex;
    }

    if (c == EOF) {
      show_line_number(yylloc.first_line);
        return 0;
    }

        
    /* char starts a number => parse the number. */
    if (isdigit(c)) {

#if 1
        double zahl = 0.0;
        while (isdigit(c)) {
            zahl *= 10;
            zahl += ( c - '0' );
            anzahl_eingelesene_zeichen ++;
            c = intern_fgetc (quelldatei);
        }
        if (c == '.') {    /* dann nachkommastellen */
            double faktor = 1.0;
            while (anzahl_eingelesene_zeichen ++,
                   isdigit (c = intern_fgetc (quelldatei))) {
                faktor /= 10;
                zahl += faktor * ( c - '0' );
            }
            intern_ungetc (c, quelldatei);
            anzahl_eingelesene_zeichen --;
            yylval.f_value = zahl;
            return MUTABOR_TOKEN_F_NUMBER;
        }
        else {
            intern_ungetc (c, quelldatei);
            anzahl_eingelesene_zeichen --;
            
            if (zahl > INT_MAX) {
                yylval.f_value = zahl;
                return MUTABOR_TOKEN_F_NUMBER;
            }
            else {
                yylval.integer = (int)zahl;
                return MUTABOR_TOKEN_INTEGER;
            }
        }
#else

        intern_ungetc (c, quelldatei);
        anzahl_eingelesene_zeichen --;
        fscanf (quelldatei, "%lf", &yylval.f_value);

#endif

/*
 printf("f_number:%lf:\n", yylval.f_value); 
*/
      
    }
    
    /* # starts a HEX-number => parse the number. */
    if (c == '#') {
        unsigned int help;
        if (fscanf (quelldatei, "%x", &help) == 0) {
            fatal_error (78, yylloc.first_line + 1);
            exit (1);
        }
        yylval.integer = help;

/* printf("f_number:%lf:\n", yylval.f_value); */

        return MUTABOR_TOKEN_INTEGER;
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
            c = toupper(intern_fgetc (quelldatei));
        } while (c != EOF                && 
                 i < MAX_IDENTIFIER_LEN  && 
                 (isalnum (c) || (c == '_') || (c == '\'') ) );
        
        intern_ungetc (c, quelldatei);
        symbuffer[i] = '\0';
#else
        int i = 0;
        int max_identifier_len = 10;
        char *symbuffer = (char*) xmalloc ((size_t) max_identifier_len);

        do {
            if (c == '\'') c = 'i';

            if ( i + 1 == max_identifier_len ) {
                char * help = (char*) xrealloc (symbuffer, (size_t) (max_identifier_len += 10));
                memmove (help, symbuffer, (size_t) max_identifier_len);
                symbuffer = help;
            }

            symbuffer[i++] = c;
	    DEBUGLOG2(other,_T("character #%d = %x"),i,c);
	    c = intern_fgetc(quelldatei);
	    DEBUGLOG2(other,_T("character #%d = %x"),i,c);
            c = toupper(c);
	    DEBUGLOG2(other,_T("character #%d = %x"),i,c);
            anzahl_eingelesene_zeichen ++;

        } while ((c != EOF) && 
                 (isalnum (c) || (c == '_') || (c == '\'') ) );
        
        intern_ungetc (c, quelldatei);
        anzahl_eingelesene_zeichen --;
        symbuffer[i] = '\0';

#endif

/* printf("symbuffer:%s:\n", symbuffer); */
        
        for (i=0; reserved_words[i].word; i++) {
            if ( ! strcmp (symbuffer, reserved_words[i].word)) {
                xfree (symbuffer);
                return reserved_words[i].token;
            }
        }
        
        yylval.identifier = symbuffer;
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

    fatal_error(2,c,yylloc.first_line + 1);
    
    return 0;  /* um Compilerwarnungen zu vermeiden */

    
} /* yylex */

void init_yylex (void)
{
    yylloc.first_line = 0;
    anzahl_eingelesene_zeichen = 0;
}

void yyerror(const char *s) {

/* ignore it ! */

} /* yyerror */



/* END MUT_TAB.C */

/* 
 * \}
 */

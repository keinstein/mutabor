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
     MUTABOR_TOKEN_CALLS = 278,
     MUTABOR_TOKEN_ERROR = 279,
     MUTABOR_TOKEN_ENDOFFILE = 280
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
#define MUTABOR_TOKEN_CALLS 278
#define MUTABOR_TOKEN_ERROR 279
#define MUTABOR_TOKEN_ENDOFFILE 280



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{
/* Line 387 of yacc.c  */
#line 68 "../../../mutabor-git/src/kernel/mut.yy"

    double      f_value;        /* fr Gleitkommazahlen */
    int         integer;        /* Fr integers */
    char        *identifier;    /* Fr Namen */


/* Line 387 of yacc.c  */
#line 201 "../../../mutabor-git/src/kernel/mut.cc"
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
#line 242 "../../../mutabor-git/src/kernel/mut.cc"

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
#define YYNTOKENS  44
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  98
/* YYNRULES -- Number of rules.  */
#define YYNRULES  204
/* YYNRULES -- Number of states.  */
#define YYNSTATES  376

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   280

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      34,    35,    39,    29,    33,    28,    42,    30,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    27,     2,
      37,    26,    38,     2,    36,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    31,     2,    32,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    40,     2,    41,    43,     2,     2,     2,
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
      25
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
      45,     0,    -1,    -1,    45,    46,    -1,    45,    51,    -1,
      45,    60,    -1,    45,    72,    -1,    45,   117,    -1,    45,
     124,    -1,    45,   138,    -1,    45,     1,    -1,     6,    47,
      -1,    -1,    47,    48,    -1,    -1,    49,    50,    -1,     3,
      26,   141,    27,   141,    -1,     3,    26,   141,     7,   141,
      -1,     3,    26,    56,    -1,     3,    26,     1,    -1,     3,
       1,    -1,     8,    52,    -1,    -1,    52,    53,    -1,    -1,
      54,    55,    -1,     3,    26,   141,    -1,     3,    26,     3,
      28,    56,    -1,     3,    26,     3,    -1,     3,    26,     3,
      29,    56,    -1,     3,    26,     1,    -1,    59,    57,    -1,
      -1,    57,    58,    -1,    29,     3,    -1,    28,     3,    -1,
      29,   141,     3,    -1,    28,   141,     3,    -1,    29,    30,
     141,     3,    -1,    28,    30,   141,     3,    -1,    29,   141,
      30,   141,     3,    -1,    28,   141,    30,   141,     3,    -1,
       3,    -1,   141,     3,    -1,    30,   141,     3,    -1,   141,
      30,   141,     3,    -1,     9,    61,    -1,    -1,    61,    62,
      -1,    -1,    63,    64,    -1,    -1,     3,    26,     5,    31,
      67,    32,    65,    56,    -1,    -1,     3,    26,     5,    31,
      67,    32,    66,    28,    56,    -1,    68,    -1,    67,    33,
      68,    -1,     3,    -1,    -1,     1,    -1,     3,    -1,    69,
      33,     3,    -1,     1,    -1,    71,    -1,    70,    33,    71,
      -1,     1,    -1,     3,    -1,     5,    -1,    28,     5,    -1,
      10,    73,    -1,    -1,    73,    74,    -1,    -1,    -1,     3,
      75,    26,    76,    79,    -1,    -1,    -1,     3,    77,    34,
      69,    35,    26,    78,    79,    -1,    80,    -1,    81,    -1,
      82,    -1,    83,    -1,    84,    -1,    95,    -1,    98,    -1,
     101,    -1,   107,    -1,   115,    -1,     1,    -1,     5,    31,
      32,    -1,     3,    31,    32,    -1,    36,    29,     5,    31,
      32,    -1,    36,    29,     3,    31,    32,    -1,    36,    28,
       5,    31,    32,    -1,    36,    28,     3,    31,    32,    -1,
      31,    37,    37,     5,    38,    38,    32,    -1,    31,    37,
      37,     3,    38,    38,    32,    -1,    31,    37,    37,    36,
      29,     5,    38,    38,    32,    -1,    31,    37,    37,    36,
      29,     3,    38,    38,    32,    -1,    31,    37,    37,    36,
      28,     5,    38,    38,    32,    -1,    31,    37,    37,    36,
      28,     3,    38,    38,    32,    -1,    31,    37,    37,    36,
      39,     5,    38,    38,    32,    -1,    31,    37,    37,    36,
      39,     3,    38,    38,    32,    -1,    31,    37,    37,    36,
      30,     5,    38,    38,    32,    -1,    31,    37,    37,    36,
      30,     3,    38,    38,    32,    -1,    -1,    31,    85,    86,
      32,    -1,    90,    -1,    90,    33,    88,    -1,    -1,    33,
      87,    88,    -1,    89,    -1,    88,    33,    89,    -1,    -1,
      90,    -1,     3,    -1,    36,    -1,    -1,     3,    29,    91,
      56,    -1,    -1,    36,    29,    92,    56,    -1,    -1,     3,
      28,    93,    56,    -1,    -1,    36,    28,    94,    56,    -1,
      -1,    31,    32,    96,    56,    -1,    -1,    31,    32,    97,
      28,    56,    -1,    -1,    31,    32,    36,    29,    99,    56,
      -1,    -1,    31,    32,    36,    28,   100,    56,    -1,    -1,
      40,   102,   103,    41,    -1,   104,    -1,   103,    33,   104,
      -1,     3,    -1,    -1,     3,    34,   105,    70,    35,    -1,
      -1,    17,    34,   106,   137,    35,    -1,    -1,     5,    40,
     108,   110,    41,    -1,    -1,     3,    40,   109,   110,    41,
      -1,   111,    -1,   110,   111,    -1,    -1,     5,    28,    38,
     112,   103,    -1,    -1,    28,     5,    28,    38,   113,   103,
      -1,    -1,    18,    28,    38,   114,   103,    -1,    -1,    17,
      34,   116,   137,    35,    -1,    11,   118,    -1,    -1,   118,
     119,    -1,    -1,     3,    26,    40,   120,   122,    41,   121,
      -1,     3,    26,     1,    -1,    -1,    42,     5,    -1,   123,
      -1,   122,    33,   123,    -1,     5,    -1,    39,     5,    -1,
      12,   125,    -1,    -1,    -1,   125,   126,   127,    -1,    -1,
       3,   135,    26,    31,   128,   130,    32,    -1,    -1,     3,
     135,    26,     3,    31,   129,   130,    32,    -1,    -1,   130,
     131,    -1,    -1,   135,    28,    38,    40,   132,   103,    41,
      -1,    -1,   135,    28,    38,   133,   104,    -1,     5,    43,
       3,    43,     5,    -1,     3,    43,     5,    -1,     5,    43,
       3,    -1,     3,    -1,    18,    -1,   134,    -1,    13,   134,
      -1,    15,     3,    -1,    -1,    16,    34,   136,   137,    35,
      -1,     5,    -1,   137,    33,     5,    -1,     1,    -1,    14,
     139,    -1,    -1,   139,   140,    -1,     5,    28,    38,     5,
      -1,     5,    28,    38,     5,    28,     5,    -1,     5,    28,
      38,    31,     5,    32,    -1,     5,    28,    38,     5,    31,
       5,    32,    -1,     5,    28,    38,     5,    28,     5,    31,
       5,    32,    -1,     4,    -1,     5,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   106,   106,   107,   108,   109,   110,   111,   112,   113,
     114,   118,   120,   122,   126,   126,   130,   136,   145,   147,
     148,   152,   154,   156,   160,   160,   164,   167,   171,   175,
     179,   183,   187,   189,   192,   195,   198,   201,   204,   210,
     216,   222,   243,   251,   254,   260,   286,   288,   290,   294,
     294,   299,   298,   303,   302,   308,   308,   311,   312,   313,
     317,   318,   320,   325,   326,   327,   332,   333,   334,   340,
     342,   344,   349,   351,   348,   356,   359,   355,   365,   366,
     367,   368,   369,   370,   371,   372,   373,   374,   375,   380,
     382,   387,   389,   391,   393,   398,   400,   405,   407,   409,
     411,   413,   415,   417,   419,   425,   424,   434,   435,   437,
     437,   444,   445,   450,   454,   458,   459,   461,   461,   464,
     464,   467,   467,   470,   470,   477,   477,   480,   480,   486,
     486,   489,   489,   495,   495,   501,   502,   506,   508,   508,
     512,   511,   518,   518,   521,   521,   527,   528,   533,   532,
     537,   536,   541,   540,   548,   547,   555,   559,   560,   565,
     564,   569,   573,   574,   578,   579,   583,   584,   588,   592,
     593,   593,   601,   600,   606,   605,   613,   614,   619,   619,
     623,   623,   629,   631,   633,   635,   640,   641,   642,   643,
     644,   644,   650,   652,   654,   659,   663,   664,   668,   670,
     672,   674,   676,   681,   682
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
  "MUTABOR_TOKEN_PARAMETER", "MUTABOR_TOKEN_OTHER", "MUTABOR_TOKEN_CALLS",
  "MUTABOR_TOKEN_ERROR", "MUTABOR_TOKEN_ENDOFFILE", "'='", "':'", "'-'",
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
     275,   276,   277,   278,   279,   280,    61,    58,    45,    43,
      47,    91,    93,    44,    40,    41,    64,    60,    62,    42,
     123,   125,    46,   126
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    44,    45,    45,    45,    45,    45,    45,    45,    45,
      45,    46,    47,    47,    49,    48,    50,    50,    50,    50,
      50,    51,    52,    52,    54,    53,    55,    55,    55,    55,
      55,    56,    57,    57,    58,    58,    58,    58,    58,    58,
      58,    58,    59,    59,    59,    59,    60,    61,    61,    63,
      62,    65,    64,    66,    64,    67,    67,    68,    68,    68,
      69,    69,    69,    70,    70,    70,    71,    71,    71,    72,
      73,    73,    75,    76,    74,    77,    78,    74,    79,    79,
      79,    79,    79,    79,    79,    79,    79,    79,    79,    80,
      80,    81,    81,    81,    81,    82,    82,    83,    83,    83,
      83,    83,    83,    83,    83,    85,    84,    86,    86,    87,
      86,    88,    88,    89,    89,    90,    90,    91,    90,    92,
      90,    93,    90,    94,    90,    96,    95,    97,    95,    99,
      98,   100,    98,   102,   101,   103,   103,   104,   105,   104,
     106,   104,   108,   107,   109,   107,   110,   110,   112,   111,
     113,   111,   114,   111,   116,   115,   117,   118,   118,   120,
     119,   119,   121,   121,   122,   122,   123,   123,   124,   125,
     126,   125,   128,   127,   129,   127,   130,   130,   132,   131,
     133,   131,   134,   134,   134,   134,   135,   135,   135,   135,
     136,   135,   137,   137,   137,   138,   139,   139,   140,   140,
     140,   140,   140,   141,   141
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
#define YYPACT_NINF -299
static const yytype_int16 yypact[] =
{
    -299,   138,  -299,  -299,  -299,  -299,  -299,  -299,  -299,  -299,
    -299,  -299,  -299,  -299,  -299,  -299,  -299,  -299,    15,    70,
      85,   114,   117,   126,   146,  -299,   154,  -299,   159,  -299,
     166,   148,  -299,   174,  -299,   184,   179,  -299,    69,  -299,
     187,  -299,   195,  -299,   198,   186,     6,   127,  -299,   191,
    -299,    77,   155,   220,  -299,   160,  -299,  -299,   185,   197,
     167,   223,   199,  -299,  -299,   201,    11,  -299,  -299,  -299,
    -299,   161,  -299,  -299,    76,  -299,   145,  -299,   200,     5,
    -299,  -299,   144,     4,   225,   229,  -299,  -299,  -299,    22,
     106,   230,   231,   181,  -299,   161,   161,   161,    89,    89,
      28,  -299,   -14,    -1,   202,    78,   183,  -299,  -299,  -299,
    -299,  -299,  -299,  -299,  -299,  -299,  -299,  -299,  -299,   234,
     212,  -299,   236,   -21,  -299,  -299,   203,   113,   208,  -299,
     237,   238,   213,  -299,    93,    96,  -299,  -299,  -299,   241,
    -299,    29,  -299,  -299,  -299,   182,  -299,   215,  -299,   216,
    -299,  -299,    48,   214,    21,   175,   178,    18,  -299,  -299,
    -299,     4,   207,   245,  -299,  -299,   153,  -299,  -299,   221,
     222,  -299,  -299,   161,    37,  -299,   161,    60,  -299,   227,
      28,  -299,   103,  -299,   103,   113,   188,    89,   228,     8,
     190,  -299,   194,   226,   224,   232,   233,   235,   239,   219,
     240,    83,  -299,     5,  -299,   254,  -299,  -299,   255,  -299,
    -299,    53,   256,  -299,   259,  -299,   161,   262,  -299,   161,
      89,   243,  -299,   244,   247,   263,     9,  -299,    10,   158,
    -299,  -299,  -299,    89,   242,   246,   125,  -299,  -299,    16,
    -299,  -299,  -299,    16,   249,   250,   251,   253,  -299,  -299,
      18,  -299,  -299,  -299,  -299,    59,  -299,  -299,   248,   257,
    -299,   264,  -299,   266,  -299,    89,   252,   258,   260,  -299,
    -299,  -299,  -299,    89,    89,  -299,   261,   265,   189,   192,
     193,   196,    89,    89,   267,  -299,  -299,    89,    89,   267,
    -299,  -299,  -299,  -299,   108,   113,  -299,  -299,   268,  -299,
    -299,  -299,  -299,  -299,  -299,   269,  -299,  -299,   270,   272,
     271,   273,   274,   275,   276,   277,   278,   279,  -299,  -299,
      16,  -299,  -299,  -299,  -299,  -299,   281,   169,  -299,   170,
     280,    18,    18,  -299,  -299,  -299,   283,   284,   285,   286,
     287,   288,   289,   290,  -299,  -299,    99,  -299,  -299,  -299,
      18,   296,   296,    18,   298,   299,   300,   301,   302,   303,
     304,   305,  -299,    18,  -299,   296,  -299,  -299,  -299,  -299,
    -299,  -299,  -299,  -299,   100,  -299
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -299,  -299,  -299,  -299,  -299,  -299,  -299,  -299,  -299,  -299,
    -299,  -299,   -98,  -299,  -299,  -299,  -299,  -299,  -299,  -299,
    -299,  -299,  -299,  -299,    97,  -299,  -299,   -73,  -299,  -299,
    -299,  -299,  -299,  -299,  -299,    75,  -299,  -299,  -299,  -299,
    -299,  -299,  -299,  -299,    36,   -33,   137,  -299,  -299,  -299,
    -299,  -299,  -299,  -299,  -299,  -299,  -299,  -299,  -299,  -298,
    -245,  -299,  -299,  -299,  -299,  -299,   109,   -20,  -299,  -299,
    -299,  -299,  -299,  -299,  -299,  -299,  -299,  -299,  -299,   131,
    -299,  -299,  -299,  -299,  -299,  -299,    84,  -299,  -299,  -299,
     282,   291,  -299,  -183,  -299,  -299,  -299,   -48
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -171
static const yytype_int16 yytable[] =
{
     140,   142,   229,    74,    77,   296,   101,    56,   102,   121,
     103,   234,   161,   235,   223,   223,    90,   147,   -14,   190,
     162,   199,   104,    92,   190,   128,   148,   224,   224,   143,
     149,   144,    94,   351,   352,   200,   105,   225,   225,   150,
     215,   106,    91,   122,   236,   107,    57,   137,   138,   139,
     269,   271,   192,   129,   191,   365,    58,   192,    59,    97,
     -58,   -58,    58,   218,    59,   374,    60,   216,    61,    62,
      50,    63,    60,   -24,    61,    62,  -127,    63,    67,    94,
      68,    69,    70,    95,   186,   256,   174,   177,   -49,   232,
     219,   297,    68,    69,    70,    51,   172,    69,    70,   175,
      69,    70,   324,    96,   325,   364,    97,    71,   223,   323,
     152,   324,   329,   325,   164,   153,   250,    31,   165,    71,
      33,   224,   264,   173,   251,   214,   176,   326,   217,  -170,
      58,   225,    59,   250,   130,   275,   326,   131,     2,     3,
      60,   375,    61,    62,     4,    63,     5,     6,     7,     8,
       9,    36,    10,   278,   279,   280,    75,    38,    76,    69,
      70,    80,    40,    81,   281,    69,    70,   302,   261,    42,
      58,   263,    59,    98,    99,   306,   307,   119,   195,   120,
     196,   197,   -75,   198,   318,   319,   208,    47,   209,   321,
     322,   208,   310,   272,   311,   312,   314,   313,   315,   316,
      46,   317,   346,   208,   347,   348,   270,    49,   270,   134,
     135,   155,   156,    52,   179,   180,   230,   231,   237,   238,
      55,    53,   240,   241,    54,    78,    87,    89,    84,    66,
     125,   100,   126,    88,   133,   132,   151,   158,   159,   167,
      85,   160,   169,   170,   178,   171,   163,   181,   183,   205,
     207,   189,   212,   248,   213,   -53,   233,   243,   242,   253,
     254,   259,   260,   244,   245,   262,   246,   300,   268,   301,
     247,   265,   266,   362,   249,   267,   298,   222,   252,   289,
     276,   290,   291,   292,   277,   293,   345,   344,   305,   299,
     303,   194,   204,   228,   255,     0,   304,     0,     0,   308,
     320,     0,   334,   309,   335,     0,   330,   333,     0,   336,
       0,   337,   338,   339,   340,   341,   342,   343,     0,     0,
     349,   354,   355,   356,   357,   358,   359,   360,   361,   250,
     366,   367,   368,   369,   370,   371,   372,   373,    65,     0,
       0,     0,    86
};

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-299)))

#define yytable_value_is_error(Yytable_value) \
  YYID (0)

static const yytype_int16 yycheck[] =
{
      98,    99,   185,    51,    52,   250,     1,     1,     3,     5,
       5,     3,    33,     5,     5,     5,     5,    31,     3,     3,
      41,     3,    17,    71,     3,     3,    40,    18,    18,     1,
      31,     3,     3,   331,   332,    17,    31,    28,    28,    40,
       3,    36,    31,    39,    36,    40,    40,    95,    96,    97,
      41,    41,    36,    31,    33,   353,     3,    36,     5,    30,
      32,    33,     3,     3,     5,   363,    13,    30,    15,    16,
       1,    18,    13,     3,    15,    16,    28,    18,     1,     3,
       3,     4,     5,     7,    36,    32,   134,   135,     3,   187,
      30,    32,     3,     4,     5,    26,     3,     4,     5,     3,
       4,     5,     3,    27,     5,   350,    30,    30,     5,     1,
      32,     3,   295,     5,     1,    37,    33,     3,     5,    30,
       3,    18,   220,    30,    41,   173,    30,    28,   176,     3,
       3,    28,     5,    33,    28,   233,    28,    31,     0,     1,
      13,    41,    15,    16,     6,    18,     8,     9,    10,    11,
      12,     5,    14,    28,    29,    30,     1,     3,     3,     4,
       5,     1,     3,     3,    39,     4,     5,   265,   216,     3,
       3,   219,     5,    28,    29,   273,   274,    33,     3,    35,
       5,     3,    34,     5,   282,   283,    33,     3,    35,   287,
     288,    33,     3,    35,     5,     3,     3,     5,     5,     3,
      26,     5,    33,    33,    35,    35,   226,    28,   228,    28,
      29,    28,    29,    26,    32,    33,    28,    29,    28,    29,
      34,    26,    28,    29,    26,     5,     3,    26,    43,    38,
       5,    31,     3,    34,     3,     5,    34,     3,    26,    31,
      43,     5,     5,     5,     3,    32,    43,    32,    32,    42,
       5,    37,    31,    34,    32,    28,    28,    33,    32,     5,
       5,     5,     3,    31,    31,     3,    31,     3,     5,     3,
      31,    28,    28,   346,    34,    28,    28,   180,   203,   243,
      38,    32,    32,    32,    38,    32,     5,   320,    28,    32,
      38,   154,   161,   184,   210,    -1,    38,    -1,    -1,    38,
      33,    -1,    32,    38,    32,    -1,    38,    38,    -1,    38,
      -1,    38,    38,    38,    38,    38,    38,    38,    -1,    -1,
      40,    38,    38,    38,    38,    38,    38,    38,    38,    33,
      32,    32,    32,    32,    32,    32,    32,    32,    47,    -1,
      -1,    -1,    60
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    45,     0,     1,     6,     8,     9,    10,    11,    12,
      14,    46,    51,    60,    72,   117,   124,   138,    47,    52,
      61,    73,   118,   125,   139,    48,    49,    53,    54,    62,
      63,     3,    74,     3,   119,   126,     5,   140,     3,    50,
       3,    55,     3,    64,    75,    77,    26,     3,   127,    28,
       1,    26,    26,    26,    26,    34,     1,    40,     3,     5,
      13,    15,    16,    18,   134,   135,    38,     1,     3,     4,
       5,    30,    56,    59,   141,     1,     3,   141,     5,    76,
       1,     3,    69,   120,    43,    43,   134,     3,    34,    26,
       5,    31,   141,    57,     3,     7,    27,    30,    28,    29,
      31,     1,     3,     5,    17,    31,    36,    40,    79,    80,
      81,    82,    83,    84,    95,    98,   101,   107,   115,    33,
      35,     5,    39,   122,   123,     5,     3,   136,     3,    31,
      28,    31,     5,     3,    28,    29,    58,   141,   141,   141,
      56,   141,    56,     1,     3,    67,    68,    31,    40,    31,
      40,    34,    32,    37,    85,    28,    29,   102,     3,    26,
       5,    33,    41,    43,     1,     5,   137,    31,   128,     5,
       5,    32,     3,    30,   141,     3,    30,   141,     3,    32,
      33,    32,   109,    32,   108,   116,    36,    96,    97,    37,
       3,    33,    36,    86,    90,     3,     5,     3,     5,     3,
      17,   103,   104,    78,   123,    42,   121,     5,    33,    35,
     129,   130,    31,    32,   141,     3,    30,   141,     3,    30,
      65,    66,    68,     5,    18,    28,   110,   111,   110,   137,
      28,    29,    56,    28,     3,     5,    36,    28,    29,    87,
      28,    29,    32,    33,    31,    31,    31,    31,    34,    34,
      33,    41,    79,     5,     5,   130,    32,   131,   135,     5,
       3,   141,     3,   141,    56,    28,    28,    28,     5,    41,
     111,    41,    35,   100,    99,    56,    38,    38,    28,    29,
      30,    39,    93,    91,    88,    89,    90,    94,    92,    88,
      32,    32,    32,    32,   105,   106,   104,    32,    28,    32,
       3,     3,    56,    38,    38,    28,    56,    56,    38,    38,
       3,     5,     3,     5,     3,     5,     3,     5,    56,    56,
      33,    56,    56,     1,     3,     5,    28,    70,    71,   137,
      38,   112,   114,    38,    32,    32,    38,    38,    38,    38,
      38,    38,    38,    38,    89,     5,    33,    35,    35,    40,
     133,   103,   103,   113,    38,    38,    38,    38,    38,    38,
      38,    38,    71,   132,   104,   103,    32,    32,    32,    32,
      32,    32,    32,    32,   103,    41
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
#line 114 "../../../mutabor-git/src/kernel/mut.yy"
    {  fatal_error(1,FEHLERZEILE); }
    break;

  case 14:
/* Line 1787 of yacc.c  */
#line 126 "../../../mutabor-git/src/kernel/mut.yy"
    { init_komplex_ton_list (); }
    break;

  case 16:
/* Line 1787 of yacc.c  */
#line 131 "../../../mutabor-git/src/kernel/mut.yy"
    { if ( fabs((yyvsp[(5) - (5)].f_value)) > 0.001 )
                         get_new_intervall ((yyvsp[(1) - (5)].identifier), (yyvsp[(3) - (5)].f_value) / (yyvsp[(5) - (5)].f_value));
                      else
			fatal_error (46, mutC_STR((yyvsp[(1) - (5)].identifier)) ); }
    break;

  case 17:
/* Line 1787 of yacc.c  */
#line 137 "../../../mutabor-git/src/kernel/mut.yy"
    { if ( fabs ((yyvsp[(3) - (5)].f_value)) > 0.001 )
                          get_new_intervall ((yyvsp[(1) - (5)].identifier), pow ((yyvsp[(5) - (5)].f_value), 1 / (yyvsp[(3) - (5)].f_value)));
                      else
			fatal_error (46, mutC_STR((yyvsp[(1) - (5)].identifier))); }
    break;

  case 18:
/* Line 1787 of yacc.c  */
#line 146 "../../../mutabor-git/src/kernel/mut.yy"
    { get_new_intervall_komplex ((yyvsp[(1) - (3)].identifier)); }
    break;

  case 19:
/* Line 1787 of yacc.c  */
#line 147 "../../../mutabor-git/src/kernel/mut.yy"
    { fatal_error(71, mutC_STR((yyvsp[(1) - (3)].identifier))); }
    break;

  case 20:
/* Line 1787 of yacc.c  */
#line 148 "../../../mutabor-git/src/kernel/mut.yy"
    { fatal_error(70,mutT("="),FEHLERZEILE); }
    break;

  case 24:
/* Line 1787 of yacc.c  */
#line 160 "../../../mutabor-git/src/kernel/mut.yy"
    { init_komplex_ton_list (); }
    break;

  case 26:
/* Line 1787 of yacc.c  */
#line 165 "../../../mutabor-git/src/kernel/mut.yy"
    { get_new_ton_absolut ((yyvsp[(1) - (3)].identifier), (yyvsp[(3) - (3)].f_value)); }
    break;

  case 27:
/* Line 1787 of yacc.c  */
#line 169 "../../../mutabor-git/src/kernel/mut.yy"
    { get_new_ton_komplex_negative ((yyvsp[(1) - (5)].identifier), (yyvsp[(3) - (5)].identifier)); }
    break;

  case 28:
/* Line 1787 of yacc.c  */
#line 173 "../../../mutabor-git/src/kernel/mut.yy"
    { get_new_ton_komplex_positive ((yyvsp[(1) - (3)].identifier), (yyvsp[(3) - (3)].identifier)); }
    break;

  case 29:
/* Line 1787 of yacc.c  */
#line 177 "../../../mutabor-git/src/kernel/mut.yy"
    { get_new_ton_komplex_positive ((yyvsp[(1) - (5)].identifier), (yyvsp[(3) - (5)].identifier)); }
    break;

  case 30:
/* Line 1787 of yacc.c  */
#line 179 "../../../mutabor-git/src/kernel/mut.yy"
    { fatal_error( 72, mutC_STR((yyvsp[(1) - (3)].identifier)) ); }
    break;

  case 34:
/* Line 1787 of yacc.c  */
#line 193 "../../../mutabor-git/src/kernel/mut.yy"
    { get_new_faktor_anteil ( (double) 1, (yyvsp[(2) - (2)].identifier)); }
    break;

  case 35:
/* Line 1787 of yacc.c  */
#line 196 "../../../mutabor-git/src/kernel/mut.yy"
    { get_new_faktor_anteil ( (double) -1, (yyvsp[(2) - (2)].identifier)); }
    break;

  case 36:
/* Line 1787 of yacc.c  */
#line 199 "../../../mutabor-git/src/kernel/mut.yy"
    { get_new_faktor_anteil ( (yyvsp[(2) - (3)].f_value), (yyvsp[(3) - (3)].identifier)); }
    break;

  case 37:
/* Line 1787 of yacc.c  */
#line 202 "../../../mutabor-git/src/kernel/mut.yy"
    { get_new_faktor_anteil ( -((yyvsp[(2) - (3)].f_value)), (yyvsp[(3) - (3)].identifier)); }
    break;

  case 38:
/* Line 1787 of yacc.c  */
#line 205 "../../../mutabor-git/src/kernel/mut.yy"
    { if ( fabs((yyvsp[(3) - (4)].f_value)) > 0.001 )
                       get_new_faktor_anteil ( (double) 1 / ((yyvsp[(3) - (4)].f_value)), (yyvsp[(4) - (4)].identifier));
                     else
                       fatal_error(53, FEHLERZEILE);  }
    break;

  case 39:
/* Line 1787 of yacc.c  */
#line 211 "../../../mutabor-git/src/kernel/mut.yy"
    { if ( fabs((yyvsp[(3) - (4)].f_value)) > 0.001 )
                       get_new_faktor_anteil ( (double) -1 / ((yyvsp[(3) - (4)].f_value)), (yyvsp[(4) - (4)].identifier));
                     else
                       fatal_error(53, FEHLERZEILE);  }
    break;

  case 40:
/* Line 1787 of yacc.c  */
#line 217 "../../../mutabor-git/src/kernel/mut.yy"
    { if ( fabs((yyvsp[(4) - (5)].f_value)) > 0.001 )
                       get_new_faktor_anteil ( ((yyvsp[(2) - (5)].f_value)) / ((yyvsp[(4) - (5)].f_value)), (yyvsp[(5) - (5)].identifier));
                     else
                       fatal_error(53, FEHLERZEILE);  }
    break;

  case 41:
/* Line 1787 of yacc.c  */
#line 223 "../../../mutabor-git/src/kernel/mut.yy"
    { if ( fabs((yyvsp[(4) - (5)].f_value)) > 0.001 )
                       get_new_faktor_anteil ( -((yyvsp[(2) - (5)].f_value)) / ((yyvsp[(4) - (5)].f_value)), (yyvsp[(5) - (5)].identifier));
                     else
                       fatal_error(53, FEHLERZEILE);  }
    break;

  case 42:
/* Line 1787 of yacc.c  */
#line 244 "../../../mutabor-git/src/kernel/mut.yy"
    { get_new_faktor_anteil ( (double) 1.0 , (yyvsp[(1) - (1)].identifier)); }
    break;

  case 43:
/* Line 1787 of yacc.c  */
#line 252 "../../../mutabor-git/src/kernel/mut.yy"
    { get_new_faktor_anteil ( (yyvsp[(1) - (2)].f_value), (yyvsp[(2) - (2)].identifier)); }
    break;

  case 44:
/* Line 1787 of yacc.c  */
#line 255 "../../../mutabor-git/src/kernel/mut.yy"
    { if ( fabs((yyvsp[(2) - (3)].f_value)) > 0.001 )
                       get_new_faktor_anteil ( (double) 1 / ((yyvsp[(2) - (3)].f_value)), (yyvsp[(3) - (3)].identifier));
                     else
                       fatal_error(53, FEHLERZEILE);  }
    break;

  case 45:
/* Line 1787 of yacc.c  */
#line 261 "../../../mutabor-git/src/kernel/mut.yy"
    { if ( fabs((yyvsp[(3) - (4)].f_value)) > 0.001 )
                       get_new_faktor_anteil ( ((yyvsp[(1) - (4)].f_value)) / ((yyvsp[(3) - (4)].f_value)), (yyvsp[(4) - (4)].identifier));
                     else
                       fatal_error(53, FEHLERZEILE);  }
    break;

  case 49:
/* Line 1787 of yacc.c  */
#line 294 "../../../mutabor-git/src/kernel/mut.yy"
    { init_ton_liste (); }
    break;

  case 51:
/* Line 1787 of yacc.c  */
#line 299 "../../../mutabor-git/src/kernel/mut.yy"
    { init_komplex_ton_list (); }
    break;

  case 52:
/* Line 1787 of yacc.c  */
#line 301 "../../../mutabor-git/src/kernel/mut.yy"
    { get_new_tonsystem ((yyvsp[(1) - (8)].identifier), (yyvsp[(3) - (8)].integer)); }
    break;

  case 53:
/* Line 1787 of yacc.c  */
#line 303 "../../../mutabor-git/src/kernel/mut.yy"
    { init_komplex_ton_list (); }
    break;

  case 54:
/* Line 1787 of yacc.c  */
#line 305 "../../../mutabor-git/src/kernel/mut.yy"
    { get_new_tonsystem_negative ((yyvsp[(1) - (9)].identifier), (yyvsp[(3) - (9)].integer)); }
    break;

  case 57:
/* Line 1787 of yacc.c  */
#line 311 "../../../mutabor-git/src/kernel/mut.yy"
    { get_new_ton_in_tonsystem ((yyvsp[(1) - (1)].identifier)); }
    break;

  case 58:
/* Line 1787 of yacc.c  */
#line 312 "../../../mutabor-git/src/kernel/mut.yy"
    { get_new_ton_in_tonsystem (NULL); }
    break;

  case 59:
/* Line 1787 of yacc.c  */
#line 313 "../../../mutabor-git/src/kernel/mut.yy"
    { fatal_error(73,FEHLERZEILE); }
    break;

  case 60:
/* Line 1787 of yacc.c  */
#line 317 "../../../mutabor-git/src/kernel/mut.yy"
    { get_new_name_in_parameterlist ((yyvsp[(1) - (1)].identifier)); }
    break;

  case 61:
/* Line 1787 of yacc.c  */
#line 319 "../../../mutabor-git/src/kernel/mut.yy"
    { get_new_name_in_parameterlist ((yyvsp[(3) - (3)].identifier)); }
    break;

  case 62:
/* Line 1787 of yacc.c  */
#line 320 "../../../mutabor-git/src/kernel/mut.yy"
    { fatal_error(74,FEHLERZEILE); }
    break;

  case 63:
/* Line 1787 of yacc.c  */
#line 325 "../../../mutabor-git/src/kernel/mut.yy"
    {}
    break;

  case 64:
/* Line 1787 of yacc.c  */
#line 326 "../../../mutabor-git/src/kernel/mut.yy"
    {}
    break;

  case 65:
/* Line 1787 of yacc.c  */
#line 327 "../../../mutabor-git/src/kernel/mut.yy"
    { fatal_error(74,FEHLERZEILE); }
    break;

  case 66:
/* Line 1787 of yacc.c  */
#line 332 "../../../mutabor-git/src/kernel/mut.yy"
    { get_new_name_in_argument_list ((yyvsp[(1) - (1)].identifier)) ;  }
    break;

  case 67:
/* Line 1787 of yacc.c  */
#line 333 "../../../mutabor-git/src/kernel/mut.yy"
    { get_new_number_in_argument_list ((yyvsp[(1) - (1)].integer)) ;  }
    break;

  case 68:
/* Line 1787 of yacc.c  */
#line 334 "../../../mutabor-git/src/kernel/mut.yy"
    { get_new_number_in_argument_list (-((yyvsp[(2) - (2)].integer))); }
    break;

  case 72:
/* Line 1787 of yacc.c  */
#line 349 "../../../mutabor-git/src/kernel/mut.yy"
    { init_umstimmung ((yyvsp[(1) - (1)].identifier));
                      init_parameter_liste (); }
    break;

  case 73:
/* Line 1787 of yacc.c  */
#line 351 "../../../mutabor-git/src/kernel/mut.yy"
    { eintrage_parameterliste_in_umstimmung (); }
    break;

  case 74:
/* Line 1787 of yacc.c  */
#line 353 "../../../mutabor-git/src/kernel/mut.yy"
    { get_new_umstimmung (); }
    break;

  case 75:
/* Line 1787 of yacc.c  */
#line 356 "../../../mutabor-git/src/kernel/mut.yy"
    { init_umstimmung ((yyvsp[(1) - (1)].identifier));
                      init_parameter_liste (); }
    break;

  case 76:
/* Line 1787 of yacc.c  */
#line 359 "../../../mutabor-git/src/kernel/mut.yy"
    { eintrage_parameterliste_in_umstimmung (); }
    break;

  case 77:
/* Line 1787 of yacc.c  */
#line 361 "../../../mutabor-git/src/kernel/mut.yy"
    { get_new_umstimmung (); }
    break;

  case 78:
/* Line 1787 of yacc.c  */
#line 365 "../../../mutabor-git/src/kernel/mut.yy"
    {}
    break;

  case 79:
/* Line 1787 of yacc.c  */
#line 366 "../../../mutabor-git/src/kernel/mut.yy"
    {}
    break;

  case 80:
/* Line 1787 of yacc.c  */
#line 367 "../../../mutabor-git/src/kernel/mut.yy"
    {}
    break;

  case 81:
/* Line 1787 of yacc.c  */
#line 368 "../../../mutabor-git/src/kernel/mut.yy"
    {}
    break;

  case 82:
/* Line 1787 of yacc.c  */
#line 369 "../../../mutabor-git/src/kernel/mut.yy"
    {}
    break;

  case 83:
/* Line 1787 of yacc.c  */
#line 370 "../../../mutabor-git/src/kernel/mut.yy"
    {}
    break;

  case 84:
/* Line 1787 of yacc.c  */
#line 371 "../../../mutabor-git/src/kernel/mut.yy"
    {}
    break;

  case 85:
/* Line 1787 of yacc.c  */
#line 372 "../../../mutabor-git/src/kernel/mut.yy"
    {}
    break;

  case 86:
/* Line 1787 of yacc.c  */
#line 373 "../../../mutabor-git/src/kernel/mut.yy"
    {}
    break;

  case 87:
/* Line 1787 of yacc.c  */
#line 374 "../../../mutabor-git/src/kernel/mut.yy"
    {}
    break;

  case 88:
/* Line 1787 of yacc.c  */
#line 375 "../../../mutabor-git/src/kernel/mut.yy"
    {fatal_error(75,FEHLERZEILE);}
    break;

  case 89:
/* Line 1787 of yacc.c  */
#line 381 "../../../mutabor-git/src/kernel/mut.yy"
    { get_umstimmung_taste_abs (zahl, (yyvsp[(1) - (3)].integer), NULL); }
    break;

  case 90:
/* Line 1787 of yacc.c  */
#line 383 "../../../mutabor-git/src/kernel/mut.yy"
    { get_umstimmung_taste_abs (parameter, 0.0, (yyvsp[(1) - (3)].identifier)); }
    break;

  case 91:
/* Line 1787 of yacc.c  */
#line 388 "../../../mutabor-git/src/kernel/mut.yy"
    { get_umstimmung_taste_rel (zahl, (yyvsp[(3) - (5)].integer), NULL, '+'); }
    break;

  case 92:
/* Line 1787 of yacc.c  */
#line 390 "../../../mutabor-git/src/kernel/mut.yy"
    { get_umstimmung_taste_rel (parameter, 0.0, (yyvsp[(3) - (5)].identifier), '+'); }
    break;

  case 93:
/* Line 1787 of yacc.c  */
#line 392 "../../../mutabor-git/src/kernel/mut.yy"
    { get_umstimmung_taste_rel (zahl, (yyvsp[(3) - (5)].integer), NULL, '-'); }
    break;

  case 94:
/* Line 1787 of yacc.c  */
#line 394 "../../../mutabor-git/src/kernel/mut.yy"
    { get_umstimmung_taste_rel (parameter, 0.0, (yyvsp[(3) - (5)].identifier), '-'); }
    break;

  case 95:
/* Line 1787 of yacc.c  */
#line 399 "../../../mutabor-git/src/kernel/mut.yy"
    { get_umstimmung_breite_abs (zahl, (yyvsp[(4) - (7)].integer), NULL); }
    break;

  case 96:
/* Line 1787 of yacc.c  */
#line 401 "../../../mutabor-git/src/kernel/mut.yy"
    { get_umstimmung_breite_abs (parameter, 0.0, (yyvsp[(4) - (7)].identifier)); }
    break;

  case 97:
/* Line 1787 of yacc.c  */
#line 406 "../../../mutabor-git/src/kernel/mut.yy"
    { get_umstimmung_breite_rel (zahl, (yyvsp[(6) - (9)].integer), NULL, '+'); }
    break;

  case 98:
/* Line 1787 of yacc.c  */
#line 408 "../../../mutabor-git/src/kernel/mut.yy"
    { get_umstimmung_breite_rel (parameter, 0.0, (yyvsp[(6) - (9)].identifier), '+'); }
    break;

  case 99:
/* Line 1787 of yacc.c  */
#line 410 "../../../mutabor-git/src/kernel/mut.yy"
    { get_umstimmung_breite_rel (zahl, (yyvsp[(6) - (9)].integer), NULL, '-'); }
    break;

  case 100:
/* Line 1787 of yacc.c  */
#line 412 "../../../mutabor-git/src/kernel/mut.yy"
    { get_umstimmung_breite_rel (parameter, 0.0, (yyvsp[(6) - (9)].identifier), '-'); }
    break;

  case 101:
/* Line 1787 of yacc.c  */
#line 414 "../../../mutabor-git/src/kernel/mut.yy"
    { get_umstimmung_breite_rel (zahl, (yyvsp[(6) - (9)].integer), NULL, '*'); }
    break;

  case 102:
/* Line 1787 of yacc.c  */
#line 416 "../../../mutabor-git/src/kernel/mut.yy"
    { get_umstimmung_breite_rel (parameter, 0.0, (yyvsp[(6) - (9)].identifier), '*'); }
    break;

  case 103:
/* Line 1787 of yacc.c  */
#line 418 "../../../mutabor-git/src/kernel/mut.yy"
    { get_umstimmung_breite_rel (zahl, (yyvsp[(6) - (9)].integer), NULL, '/'); }
    break;

  case 104:
/* Line 1787 of yacc.c  */
#line 420 "../../../mutabor-git/src/kernel/mut.yy"
    { get_umstimmung_breite_rel (parameter, 0.0, (yyvsp[(6) - (9)].identifier), '/'); }
    break;

  case 105:
/* Line 1787 of yacc.c  */
#line 425 "../../../mutabor-git/src/kernel/mut.yy"
    { init_umstimm_expression_list (); }
    break;

  case 106:
/* Line 1787 of yacc.c  */
#line 427 "../../../mutabor-git/src/kernel/mut.yy"
    { get_umstimmung_tonhoehe_veraendert (); }
    break;

  case 107:
/* Line 1787 of yacc.c  */
#line 434 "../../../mutabor-git/src/kernel/mut.yy"
    {}
    break;

  case 108:
/* Line 1787 of yacc.c  */
#line 435 "../../../mutabor-git/src/kernel/mut.yy"
    {}
    break;

  case 109:
/* Line 1787 of yacc.c  */
#line 437 "../../../mutabor-git/src/kernel/mut.yy"
    { init_komplex_ton_list();
                     get_new_umstimm_expression (NULL);
                   }
    break;

  case 110:
/* Line 1787 of yacc.c  */
#line 440 "../../../mutabor-git/src/kernel/mut.yy"
    {}
    break;

  case 111:
/* Line 1787 of yacc.c  */
#line 444 "../../../mutabor-git/src/kernel/mut.yy"
    {}
    break;

  case 112:
/* Line 1787 of yacc.c  */
#line 445 "../../../mutabor-git/src/kernel/mut.yy"
    {}
    break;

  case 113:
/* Line 1787 of yacc.c  */
#line 450 "../../../mutabor-git/src/kernel/mut.yy"
    { init_komplex_ton_list();
                     get_new_umstimm_expression (NULL);
                   }
    break;

  case 115:
/* Line 1787 of yacc.c  */
#line 458 "../../../mutabor-git/src/kernel/mut.yy"
    { get_new_umstimm_expression ((yyvsp[(1) - (1)].identifier)); }
    break;

  case 116:
/* Line 1787 of yacc.c  */
#line 459 "../../../mutabor-git/src/kernel/mut.yy"
    { get_new_umstimm_expression ("@"); }
    break;

  case 117:
/* Line 1787 of yacc.c  */
#line 461 "../../../mutabor-git/src/kernel/mut.yy"
    { init_komplex_ton_list (); }
    break;

  case 118:
/* Line 1787 of yacc.c  */
#line 463 "../../../mutabor-git/src/kernel/mut.yy"
    { get_new_umstimm_expression_positive ((yyvsp[(1) - (4)].identifier)); }
    break;

  case 119:
/* Line 1787 of yacc.c  */
#line 464 "../../../mutabor-git/src/kernel/mut.yy"
    { init_komplex_ton_list (); }
    break;

  case 120:
/* Line 1787 of yacc.c  */
#line 466 "../../../mutabor-git/src/kernel/mut.yy"
    { get_new_umstimm_expression_positive ( "@" ); }
    break;

  case 121:
/* Line 1787 of yacc.c  */
#line 467 "../../../mutabor-git/src/kernel/mut.yy"
    { init_komplex_ton_list (); }
    break;

  case 122:
/* Line 1787 of yacc.c  */
#line 469 "../../../mutabor-git/src/kernel/mut.yy"
    { get_new_umstimm_expression_negative ((yyvsp[(1) - (4)].identifier)); }
    break;

  case 123:
/* Line 1787 of yacc.c  */
#line 470 "../../../mutabor-git/src/kernel/mut.yy"
    { init_komplex_ton_list (); }
    break;

  case 124:
/* Line 1787 of yacc.c  */
#line 472 "../../../mutabor-git/src/kernel/mut.yy"
    { get_new_umstimm_expression_negative ( "@" ); }
    break;

  case 125:
/* Line 1787 of yacc.c  */
#line 477 "../../../mutabor-git/src/kernel/mut.yy"
    { init_komplex_ton_list (); }
    break;

  case 126:
/* Line 1787 of yacc.c  */
#line 479 "../../../mutabor-git/src/kernel/mut.yy"
    { get_umstimmung_wiederholung_abs (); }
    break;

  case 127:
/* Line 1787 of yacc.c  */
#line 480 "../../../mutabor-git/src/kernel/mut.yy"
    { init_komplex_ton_list (); }
    break;

  case 128:
/* Line 1787 of yacc.c  */
#line 482 "../../../mutabor-git/src/kernel/mut.yy"
    { get_umstimmung_wiederholung_abs_negative (); }
    break;

  case 129:
/* Line 1787 of yacc.c  */
#line 486 "../../../mutabor-git/src/kernel/mut.yy"
    { init_komplex_ton_list (); }
    break;

  case 130:
/* Line 1787 of yacc.c  */
#line 488 "../../../mutabor-git/src/kernel/mut.yy"
    { get_umstimmung_wiederholung_rel_positive (); }
    break;

  case 131:
/* Line 1787 of yacc.c  */
#line 489 "../../../mutabor-git/src/kernel/mut.yy"
    { init_komplex_ton_list (); }
    break;

  case 132:
/* Line 1787 of yacc.c  */
#line 491 "../../../mutabor-git/src/kernel/mut.yy"
    { get_umstimmung_wiederholung_rel_negative (); }
    break;

  case 133:
/* Line 1787 of yacc.c  */
#line 495 "../../../mutabor-git/src/kernel/mut.yy"
    { init_aktions_liste (); }
    break;

  case 134:
/* Line 1787 of yacc.c  */
#line 497 "../../../mutabor-git/src/kernel/mut.yy"
    { get_umstimmung_umstimmungs_bund (); }
    break;

  case 135:
/* Line 1787 of yacc.c  */
#line 501 "../../../mutabor-git/src/kernel/mut.yy"
    {}
    break;

  case 136:
/* Line 1787 of yacc.c  */
#line 502 "../../../mutabor-git/src/kernel/mut.yy"
    {}
    break;

  case 137:
/* Line 1787 of yacc.c  */
#line 506 "../../../mutabor-git/src/kernel/mut.yy"
    { init_argument_liste (); 
                       get_new_aktion_aufruf_element ((yyvsp[(1) - (1)].identifier)); }
    break;

  case 138:
/* Line 1787 of yacc.c  */
#line 508 "../../../mutabor-git/src/kernel/mut.yy"
    { init_argument_liste (); }
    break;

  case 139:
/* Line 1787 of yacc.c  */
#line 510 "../../../mutabor-git/src/kernel/mut.yy"
    { get_new_aktion_aufruf_element ((yyvsp[(1) - (5)].identifier)); }
    break;

  case 140:
/* Line 1787 of yacc.c  */
#line 512 "../../../mutabor-git/src/kernel/mut.yy"
    { init_integersequenz ();}
    break;

  case 141:
/* Line 1787 of yacc.c  */
#line 514 "../../../mutabor-git/src/kernel/mut.yy"
    { get_new_aktion_midi_out_element (); }
    break;

  case 142:
/* Line 1787 of yacc.c  */
#line 518 "../../../mutabor-git/src/kernel/mut.yy"
    { init_umstimmungs_case_liste (); }
    break;

  case 143:
/* Line 1787 of yacc.c  */
#line 520 "../../../mutabor-git/src/kernel/mut.yy"
    { get_umstimmung_umstimm_case_zahl ((yyvsp[(1) - (5)].integer)); }
    break;

  case 144:
/* Line 1787 of yacc.c  */
#line 521 "../../../mutabor-git/src/kernel/mut.yy"
    { init_umstimmungs_case_liste (); }
    break;

  case 145:
/* Line 1787 of yacc.c  */
#line 523 "../../../mutabor-git/src/kernel/mut.yy"
    { get_umstimmung_umstimm_case_parameter ((yyvsp[(1) - (5)].identifier)); }
    break;

  case 146:
/* Line 1787 of yacc.c  */
#line 527 "../../../mutabor-git/src/kernel/mut.yy"
    {}
    break;

  case 147:
/* Line 1787 of yacc.c  */
#line 528 "../../../mutabor-git/src/kernel/mut.yy"
    {}
    break;

  case 148:
/* Line 1787 of yacc.c  */
#line 533 "../../../mutabor-git/src/kernel/mut.yy"
    { init_aktions_liste (); }
    break;

  case 149:
/* Line 1787 of yacc.c  */
#line 535 "../../../mutabor-git/src/kernel/mut.yy"
    { get_umstimmungs_case_zahl_element ((yyvsp[(1) - (5)].integer)); }
    break;

  case 150:
/* Line 1787 of yacc.c  */
#line 537 "../../../mutabor-git/src/kernel/mut.yy"
    { init_aktions_liste (); }
    break;

  case 151:
/* Line 1787 of yacc.c  */
#line 539 "../../../mutabor-git/src/kernel/mut.yy"
    { get_umstimmungs_case_zahl_element (-((yyvsp[(2) - (6)].integer))); }
    break;

  case 152:
/* Line 1787 of yacc.c  */
#line 541 "../../../mutabor-git/src/kernel/mut.yy"
    { init_aktions_liste (); }
    break;

  case 153:
/* Line 1787 of yacc.c  */
#line 543 "../../../mutabor-git/src/kernel/mut.yy"
    { get_umstimmungs_case_default_element (); }
    break;

  case 154:
/* Line 1787 of yacc.c  */
#line 548 "../../../mutabor-git/src/kernel/mut.yy"
    { init_integersequenz ();}
    break;

  case 155:
/* Line 1787 of yacc.c  */
#line 550 "../../../mutabor-git/src/kernel/mut.yy"
    { get_umstimmung_midi_out (); }
    break;

  case 156:
/* Line 1787 of yacc.c  */
#line 555 "../../../mutabor-git/src/kernel/mut.yy"
    {}
    break;

  case 157:
/* Line 1787 of yacc.c  */
#line 559 "../../../mutabor-git/src/kernel/mut.yy"
    {}
    break;

  case 158:
/* Line 1787 of yacc.c  */
#line 560 "../../../mutabor-git/src/kernel/mut.yy"
    {}
    break;

  case 159:
/* Line 1787 of yacc.c  */
#line 565 "../../../mutabor-git/src/kernel/mut.yy"
    { init_tastenliste (); }
    break;

  case 160:
/* Line 1787 of yacc.c  */
#line 567 "../../../mutabor-git/src/kernel/mut.yy"
    { get_new_harmonie ((yyvsp[(1) - (7)].identifier), (yyvsp[(7) - (7)].integer)); }
    break;

  case 161:
/* Line 1787 of yacc.c  */
#line 569 "../../../mutabor-git/src/kernel/mut.yy"
    { fatal_error(76, mutC_STR((yyvsp[(1) - (3)].identifier))); }
    break;

  case 162:
/* Line 1787 of yacc.c  */
#line 573 "../../../mutabor-git/src/kernel/mut.yy"
    { (yyval.integer) = -1; }
    break;

  case 163:
/* Line 1787 of yacc.c  */
#line 574 "../../../mutabor-git/src/kernel/mut.yy"
    { (yyval.integer) = (yyvsp[(2) - (2)].integer); }
    break;

  case 164:
/* Line 1787 of yacc.c  */
#line 578 "../../../mutabor-git/src/kernel/mut.yy"
    {}
    break;

  case 165:
/* Line 1787 of yacc.c  */
#line 579 "../../../mutabor-git/src/kernel/mut.yy"
    {}
    break;

  case 166:
/* Line 1787 of yacc.c  */
#line 583 "../../../mutabor-git/src/kernel/mut.yy"
    { get_new_taste ( (yyvsp[(1) - (1)].integer), '+'); }
    break;

  case 167:
/* Line 1787 of yacc.c  */
#line 584 "../../../mutabor-git/src/kernel/mut.yy"
    { get_new_taste ( (yyvsp[(2) - (2)].integer), '*'); }
    break;

  case 168:
/* Line 1787 of yacc.c  */
#line 588 "../../../mutabor-git/src/kernel/mut.yy"
    {}
    break;

  case 169:
/* Line 1787 of yacc.c  */
#line 592 "../../../mutabor-git/src/kernel/mut.yy"
    {}
    break;

  case 170:
/* Line 1787 of yacc.c  */
#line 593 "../../../mutabor-git/src/kernel/mut.yy"
    { init_ausloeser ();
                         /* fr die Anfangsausloesung der Logik */
                       }
    break;

  case 171:
/* Line 1787 of yacc.c  */
#line 596 "../../../mutabor-git/src/kernel/mut.yy"
    {}
    break;

  case 172:
/* Line 1787 of yacc.c  */
#line 601 "../../../mutabor-git/src/kernel/mut.yy"
    { get_new_logik ((yyvsp[(1) - (4)].identifier), NULL);
                init_anweisungs_liste (); }
    break;

  case 173:
/* Line 1787 of yacc.c  */
#line 604 "../../../mutabor-git/src/kernel/mut.yy"
    { vervollstaendige_logik (); }
    break;

  case 174:
/* Line 1787 of yacc.c  */
#line 606 "../../../mutabor-git/src/kernel/mut.yy"
    { get_new_logik ((yyvsp[(1) - (5)].identifier), (yyvsp[(4) - (5)].identifier));
                init_anweisungs_liste (); }
    break;

  case 175:
/* Line 1787 of yacc.c  */
#line 609 "../../../mutabor-git/src/kernel/mut.yy"
    { vervollstaendige_logik (); }
    break;

  case 176:
/* Line 1787 of yacc.c  */
#line 613 "../../../mutabor-git/src/kernel/mut.yy"
    {}
    break;

  case 177:
/* Line 1787 of yacc.c  */
#line 614 "../../../mutabor-git/src/kernel/mut.yy"
    {}
    break;

  case 178:
/* Line 1787 of yacc.c  */
#line 619 "../../../mutabor-git/src/kernel/mut.yy"
    { init_aktions_liste (); }
    break;

  case 179:
/* Line 1787 of yacc.c  */
#line 621 "../../../mutabor-git/src/kernel/mut.yy"
    { get_new_anweisung (); }
    break;

  case 180:
/* Line 1787 of yacc.c  */
#line 623 "../../../mutabor-git/src/kernel/mut.yy"
    { init_aktions_liste (); }
    break;

  case 181:
/* Line 1787 of yacc.c  */
#line 625 "../../../mutabor-git/src/kernel/mut.yy"
    { get_new_anweisung (); }
    break;

  case 182:
/* Line 1787 of yacc.c  */
#line 630 "../../../mutabor-git/src/kernel/mut.yy"
    { get_harmoniebezeichner (  (yyvsp[(1) - (5)].integer), (yyvsp[(3) - (5)].identifier),  (yyvsp[(5) - (5)].integer)); }
    break;

  case 183:
/* Line 1787 of yacc.c  */
#line 632 "../../../mutabor-git/src/kernel/mut.yy"
    { get_harmoniebezeichner (-1, (yyvsp[(1) - (3)].identifier),  (yyvsp[(3) - (3)].integer)); }
    break;

  case 184:
/* Line 1787 of yacc.c  */
#line 634 "../../../mutabor-git/src/kernel/mut.yy"
    { get_harmoniebezeichner (  (yyvsp[(1) - (3)].integer), (yyvsp[(3) - (3)].identifier), -1); }
    break;

  case 185:
/* Line 1787 of yacc.c  */
#line 636 "../../../mutabor-git/src/kernel/mut.yy"
    { get_harmoniebezeichner (-1, (yyvsp[(1) - (1)].identifier), -1); }
    break;

  case 186:
/* Line 1787 of yacc.c  */
#line 640 "../../../mutabor-git/src/kernel/mut.yy"
    { get_ausloeser_default (); }
    break;

  case 187:
/* Line 1787 of yacc.c  */
#line 641 "../../../mutabor-git/src/kernel/mut.yy"
    { get_ausloeser_harmonie (); }
    break;

  case 188:
/* Line 1787 of yacc.c  */
#line 642 "../../../mutabor-git/src/kernel/mut.yy"
    { get_ausloeser_harmonie_form (); }
    break;

  case 189:
/* Line 1787 of yacc.c  */
#line 643 "../../../mutabor-git/src/kernel/mut.yy"
    { get_ausloeser_taste ((yyvsp[(2) - (2)].identifier)); }
    break;

  case 190:
/* Line 1787 of yacc.c  */
#line 644 "../../../mutabor-git/src/kernel/mut.yy"
    { init_integersequenz (); }
    break;

  case 191:
/* Line 1787 of yacc.c  */
#line 646 "../../../mutabor-git/src/kernel/mut.yy"
    { get_ausloeser_midi_in (); }
    break;

  case 192:
/* Line 1787 of yacc.c  */
#line 651 "../../../mutabor-git/src/kernel/mut.yy"
    { get_new_integer_in_integersequenz ((yyvsp[(1) - (1)].integer));}
    break;

  case 193:
/* Line 1787 of yacc.c  */
#line 653 "../../../mutabor-git/src/kernel/mut.yy"
    { get_new_integer_in_integersequenz ((yyvsp[(3) - (3)].integer));}
    break;

  case 194:
/* Line 1787 of yacc.c  */
#line 654 "../../../mutabor-git/src/kernel/mut.yy"
    { fatal_error( 77, FEHLERZEILE ); }
    break;

  case 195:
/* Line 1787 of yacc.c  */
#line 659 "../../../mutabor-git/src/kernel/mut.yy"
    {}
    break;

  case 196:
/* Line 1787 of yacc.c  */
#line 663 "../../../mutabor-git/src/kernel/mut.yy"
    {}
    break;

  case 197:
/* Line 1787 of yacc.c  */
#line 664 "../../../mutabor-git/src/kernel/mut.yy"
    {}
    break;

  case 198:
/* Line 1787 of yacc.c  */
#line 669 "../../../mutabor-git/src/kernel/mut.yy"
    { get_instrument_dekl ((yyvsp[(1) - (4)].integer), (yyvsp[(4) - (4)].integer), (yyvsp[(4) - (4)].integer), 0, & list_of_instrumente); }
    break;

  case 199:
/* Line 1787 of yacc.c  */
#line 671 "../../../mutabor-git/src/kernel/mut.yy"
    { get_instrument_dekl ((yyvsp[(1) - (6)].integer), (yyvsp[(4) - (6)].integer), (yyvsp[(6) - (6)].integer), 0, & list_of_instrumente); }
    break;

  case 200:
/* Line 1787 of yacc.c  */
#line 673 "../../../mutabor-git/src/kernel/mut.yy"
    { get_instrument_dekl ((yyvsp[(1) - (6)].integer), 0, 0, (yyvsp[(5) - (6)].integer), & list_of_instrumente); }
    break;

  case 201:
/* Line 1787 of yacc.c  */
#line 675 "../../../mutabor-git/src/kernel/mut.yy"
    { get_instrument_dekl ((yyvsp[(1) - (7)].integer), (yyvsp[(4) - (7)].integer), (yyvsp[(4) - (7)].integer), (yyvsp[(6) - (7)].integer), & list_of_instrumente); }
    break;

  case 202:
/* Line 1787 of yacc.c  */
#line 677 "../../../mutabor-git/src/kernel/mut.yy"
    { get_instrument_dekl ((yyvsp[(1) - (9)].integer), (yyvsp[(4) - (9)].integer), (yyvsp[(6) - (9)].integer), (yyvsp[(8) - (9)].integer), & list_of_instrumente); }
    break;

  case 203:
/* Line 1787 of yacc.c  */
#line 681 "../../../mutabor-git/src/kernel/mut.yy"
    { (yyval.f_value) = (yyvsp[(1) - (1)].f_value) ; }
    break;

  case 204:
/* Line 1787 of yacc.c  */
#line 682 "../../../mutabor-git/src/kernel/mut.yy"
    { (yyval.f_value) = (double) (yyvsp[(1) - (1)].integer) ; }
    break;


/* Line 1787 of yacc.c  */
#line 2996 "../../../mutabor-git/src/kernel/mut.cc"
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
#line 686 "../../../mutabor-git/src/kernel/mut.yy"

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

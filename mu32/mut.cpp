
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.
   
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
#define YYBISON_VERSION "2.4.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 1



/* Copy the first part of user declarations.  */

/* Line 189 of yacc.c  */
#line 34 "../mu32/mut.y"


/* BEGIN MUT_TAB.C */

/* MUTABOR / Version 2.1 */

//#pragma warn -cln
//#pragma warn -aus
//#pragma warn -sig
//#pragma warn -par


#include <ctype.h>
#include <limits.h>
#include "Global.h"
#include "GrafKern.h"
#include "Hilfs.h"

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



/* Line 189 of yacc.c  */
#line 107 "y.tab.c"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     IDENTIFIER = 258,
     F_NUMBER = 259,
     INTEGER = 260,
     INTERVALL = 261,
     WURZEL = 262,
     TON = 263,
     TONSYSTEM = 264,
     UMSTIMMUNG = 265,
     HARMONIE = 266,
     LOGIK = 267,
     FORM = 268,
     INSTRUMENT = 269,
     TASTE = 270,
     MIDI_IN = 271,
     MIDI_OUT = 272,
     ANSONSTEN = 273
   };
#endif
/* Tokens.  */
#define IDENTIFIER 258
#define F_NUMBER 259
#define INTEGER 260
#define INTERVALL 261
#define WURZEL 262
#define TON 263
#define TONSYSTEM 264
#define UMSTIMMUNG 265
#define HARMONIE 266
#define LOGIK 267
#define FORM 268
#define INSTRUMENT 269
#define TASTE 270
#define MIDI_IN 271
#define MIDI_OUT 272
#define ANSONSTEN 273




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 214 of yacc.c  */
#line 67 "../mu32/mut.y"

    double      f_value;        /* fÅr Gleitkommazahlen */
    int         integer;        /* FÅr integers */
    char        *identifier;    /* FÅr Namen */



/* Line 214 of yacc.c  */
#line 187 "y.tab.c"
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


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 212 "y.tab.c"

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
# if YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
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
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
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
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
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

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

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

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  2
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   348

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  37
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  98
/* YYNRULES -- Number of rules.  */
#define YYNRULES  204
/* YYNRULES -- Number of states.  */
#define YYNSTATES  376

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   273

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      27,    28,    32,    22,    26,    21,    35,    23,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    20,     2,
      30,    19,    31,     2,    29,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    24,     2,    25,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    33,     2,    34,    36,     2,     2,     2,
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
      15,    16,    17,    18
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
      38,     0,    -1,    -1,    38,    39,    -1,    38,    44,    -1,
      38,    53,    -1,    38,    65,    -1,    38,   110,    -1,    38,
     117,    -1,    38,   131,    -1,    38,     1,    -1,     6,    40,
      -1,    -1,    40,    41,    -1,    -1,    42,    43,    -1,     3,
      19,   134,    20,   134,    -1,     3,    19,   134,     7,   134,
      -1,     3,    19,    49,    -1,     3,    19,     1,    -1,     3,
       1,    -1,     8,    45,    -1,    -1,    45,    46,    -1,    -1,
      47,    48,    -1,     3,    19,   134,    -1,     3,    19,     3,
      21,    49,    -1,     3,    19,     3,    -1,     3,    19,     3,
      22,    49,    -1,     3,    19,     1,    -1,    52,    50,    -1,
      -1,    50,    51,    -1,    22,     3,    -1,    21,     3,    -1,
      22,   134,     3,    -1,    21,   134,     3,    -1,    22,    23,
     134,     3,    -1,    21,    23,   134,     3,    -1,    22,   134,
      23,   134,     3,    -1,    21,   134,    23,   134,     3,    -1,
       3,    -1,   134,     3,    -1,    23,   134,     3,    -1,   134,
      23,   134,     3,    -1,     9,    54,    -1,    -1,    54,    55,
      -1,    -1,    56,    57,    -1,    -1,     3,    19,     5,    24,
      60,    25,    58,    49,    -1,    -1,     3,    19,     5,    24,
      60,    25,    59,    21,    49,    -1,    61,    -1,    60,    26,
      61,    -1,     3,    -1,    -1,     1,    -1,     3,    -1,    62,
      26,     3,    -1,     1,    -1,    64,    -1,    63,    26,    64,
      -1,     1,    -1,     3,    -1,     5,    -1,    21,     5,    -1,
      10,    66,    -1,    -1,    66,    67,    -1,    -1,    -1,     3,
      68,    19,    69,    72,    -1,    -1,    -1,     3,    70,    27,
      62,    28,    19,    71,    72,    -1,    73,    -1,    74,    -1,
      75,    -1,    76,    -1,    77,    -1,    88,    -1,    91,    -1,
      94,    -1,   100,    -1,   108,    -1,     1,    -1,     5,    24,
      25,    -1,     3,    24,    25,    -1,    29,    22,     5,    24,
      25,    -1,    29,    22,     3,    24,    25,    -1,    29,    21,
       5,    24,    25,    -1,    29,    21,     3,    24,    25,    -1,
      24,    30,    30,     5,    31,    31,    25,    -1,    24,    30,
      30,     3,    31,    31,    25,    -1,    24,    30,    30,    29,
      22,     5,    31,    31,    25,    -1,    24,    30,    30,    29,
      22,     3,    31,    31,    25,    -1,    24,    30,    30,    29,
      21,     5,    31,    31,    25,    -1,    24,    30,    30,    29,
      21,     3,    31,    31,    25,    -1,    24,    30,    30,    29,
      32,     5,    31,    31,    25,    -1,    24,    30,    30,    29,
      32,     3,    31,    31,    25,    -1,    24,    30,    30,    29,
      23,     5,    31,    31,    25,    -1,    24,    30,    30,    29,
      23,     3,    31,    31,    25,    -1,    -1,    24,    78,    79,
      25,    -1,    83,    -1,    83,    26,    81,    -1,    -1,    26,
      80,    81,    -1,    82,    -1,    81,    26,    82,    -1,    -1,
      83,    -1,     3,    -1,    29,    -1,    -1,     3,    22,    84,
      49,    -1,    -1,    29,    22,    85,    49,    -1,    -1,     3,
      21,    86,    49,    -1,    -1,    29,    21,    87,    49,    -1,
      -1,    24,    25,    89,    49,    -1,    -1,    24,    25,    90,
      21,    49,    -1,    -1,    24,    25,    29,    22,    92,    49,
      -1,    -1,    24,    25,    29,    21,    93,    49,    -1,    -1,
      33,    95,    96,    34,    -1,    97,    -1,    96,    26,    97,
      -1,     3,    -1,    -1,     3,    27,    98,    63,    28,    -1,
      -1,    17,    27,    99,   130,    28,    -1,    -1,     5,    33,
     101,   103,    34,    -1,    -1,     3,    33,   102,   103,    34,
      -1,   104,    -1,   103,   104,    -1,    -1,     5,    21,    31,
     105,    96,    -1,    -1,    21,     5,    21,    31,   106,    96,
      -1,    -1,    18,    21,    31,   107,    96,    -1,    -1,    17,
      27,   109,   130,    28,    -1,    11,   111,    -1,    -1,   111,
     112,    -1,    -1,     3,    19,    33,   113,   115,    34,   114,
      -1,     3,    19,     1,    -1,    -1,    35,     5,    -1,   116,
      -1,   115,    26,   116,    -1,     5,    -1,    32,     5,    -1,
      12,   118,    -1,    -1,    -1,   118,   119,   120,    -1,    -1,
       3,   128,    19,    24,   121,   123,    25,    -1,    -1,     3,
     128,    19,     3,    24,   122,   123,    25,    -1,    -1,   123,
     124,    -1,    -1,   128,    21,    31,    33,   125,    96,    34,
      -1,    -1,   128,    21,    31,   126,    97,    -1,     5,    36,
       3,    36,     5,    -1,     3,    36,     5,    -1,     5,    36,
       3,    -1,     3,    -1,    18,    -1,   127,    -1,    13,   127,
      -1,    15,     3,    -1,    -1,    16,    27,   129,   130,    28,
      -1,     5,    -1,   130,    26,     5,    -1,     1,    -1,    14,
     132,    -1,    -1,   132,   133,    -1,     5,    21,    31,     5,
      -1,     5,    21,    31,     5,    21,     5,    -1,     5,    21,
      31,    24,     5,    25,    -1,     5,    21,    31,     5,    24,
       5,    25,    -1,     5,    21,    31,     5,    21,     5,    24,
       5,    25,    -1,     4,    -1,     5,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    98,    98,    99,   100,   101,   102,   103,   104,   105,
     106,   110,   112,   114,   118,   118,   122,   128,   137,   139,
     140,   144,   146,   148,   152,   152,   156,   159,   163,   167,
     171,   175,   179,   181,   184,   187,   190,   193,   196,   202,
     208,   214,   235,   243,   246,   252,   278,   280,   282,   286,
     286,   291,   290,   295,   294,   300,   300,   303,   304,   305,
     309,   310,   312,   317,   318,   319,   324,   325,   326,   332,
     334,   336,   341,   343,   340,   348,   351,   347,   357,   358,
     359,   360,   361,   362,   363,   364,   365,   366,   367,   372,
     374,   379,   381,   383,   385,   390,   392,   397,   399,   401,
     403,   405,   407,   409,   411,   417,   416,   426,   427,   429,
     429,   436,   437,   442,   446,   450,   451,   453,   453,   456,
     456,   459,   459,   462,   462,   469,   469,   472,   472,   478,
     478,   481,   481,   487,   487,   493,   494,   498,   500,   500,
     504,   503,   510,   510,   513,   513,   519,   520,   525,   524,
     529,   528,   533,   532,   540,   539,   547,   551,   552,   557,
     556,   561,   565,   566,   570,   571,   575,   576,   580,   584,
     585,   585,   593,   592,   598,   597,   605,   606,   611,   611,
     615,   615,   621,   623,   625,   627,   632,   633,   634,   635,
     636,   636,   642,   644,   646,   651,   655,   656,   660,   662,
     664,   666,   668,   673,   674
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "IDENTIFIER", "F_NUMBER", "INTEGER",
  "INTERVALL", "WURZEL", "TON", "TONSYSTEM", "UMSTIMMUNG", "HARMONIE",
  "LOGIK", "FORM", "INSTRUMENT", "TASTE", "MIDI_IN", "MIDI_OUT",
  "ANSONSTEN", "'='", "':'", "'-'", "'+'", "'/'", "'['", "']'", "','",
  "'('", "')'", "'@'", "'<'", "'>'", "'*'", "'{'", "'}'", "'.'", "'~'",
  "$accept", "start", "intervalldeklaration", "intervalldekl1",
  "intervalldekl2_1", "$@1", "intervalldekl2", "tondeklaration",
  "tondekl1", "tondekl2_1", "$@2", "tondekl2", "KOMPLEX_TON_LIST",
  "KOMPLEX_TON_LIST_2", "KOMPLEX_TON_1", "KOMPLEX_TON_START",
  "tonsystemdeklaration", "tonsystemdekl1", "tonsystemdekl2_1", "$@3",
  "tonsystemdekl2", "$@4", "$@5", "tonliste", "ton_element",
  "parameter_liste", "argument_liste", "argument_listenelement",
  "umstimmungdeklaration", "umstimmungs_dekl_1", "umstimmungs_dekl_2",
  "$@6", "$@7", "$@8", "$@9", "umstimmungs_dekl_3",
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
  "GLEITKOMMA_ZAHL", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,    61,
      58,    45,    43,    47,    91,    93,    44,    40,    41,    64,
      60,    62,    42,   123,   125,    46,   126
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    37,    38,    38,    38,    38,    38,    38,    38,    38,
      38,    39,    40,    40,    42,    41,    43,    43,    43,    43,
      43,    44,    45,    45,    47,    46,    48,    48,    48,    48,
      48,    49,    50,    50,    51,    51,    51,    51,    51,    51,
      51,    51,    52,    52,    52,    52,    53,    54,    54,    56,
      55,    58,    57,    59,    57,    60,    60,    61,    61,    61,
      62,    62,    62,    63,    63,    63,    64,    64,    64,    65,
      66,    66,    68,    69,    67,    70,    71,    67,    72,    72,
      72,    72,    72,    72,    72,    72,    72,    72,    72,    73,
      73,    74,    74,    74,    74,    75,    75,    76,    76,    76,
      76,    76,    76,    76,    76,    78,    77,    79,    79,    80,
      79,    81,    81,    82,    82,    83,    83,    84,    83,    85,
      83,    86,    83,    87,    83,    89,    88,    90,    88,    92,
      91,    93,    91,    95,    94,    96,    96,    97,    98,    97,
      99,    97,   101,   100,   102,   100,   103,   103,   105,   104,
     106,   104,   107,   104,   109,   108,   110,   111,   111,   113,
     112,   112,   114,   114,   115,   115,   116,   116,   117,   118,
     119,   118,   121,   120,   122,   120,   123,   123,   125,   124,
     126,   124,   127,   127,   127,   127,   128,   128,   128,   128,
     129,   128,   130,   130,   130,   131,   132,   132,   133,   133,
     133,   133,   133,   134,   134
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

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
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
    -321,   138,  -321,  -321,  -321,  -321,  -321,  -321,  -321,  -321,
    -321,  -321,  -321,  -321,  -321,  -321,  -321,  -321,    13,    95,
     111,   133,   163,   166,   177,  -321,   197,  -321,   201,  -321,
     206,   160,  -321,   191,  -321,   216,   199,  -321,    66,  -321,
     202,  -321,   203,  -321,   204,   200,     6,   127,  -321,   193,
    -321,    72,   115,   220,  -321,    56,  -321,  -321,   195,   205,
     153,   223,   207,  -321,  -321,   209,    83,  -321,  -321,  -321,
    -321,   198,  -321,  -321,    76,  -321,   184,  -321,   208,     5,
    -321,  -321,   134,     4,   224,   227,  -321,  -321,  -321,    11,
     113,   228,   232,   186,  -321,   198,   198,   198,    77,    77,
      29,  -321,    -7,    37,   210,   -12,   190,  -321,  -321,  -321,
    -321,  -321,  -321,  -321,  -321,  -321,  -321,  -321,  -321,   233,
     219,  -321,   234,    89,  -321,  -321,   211,    92,   218,  -321,
     235,   238,   221,  -321,    87,    98,  -321,  -321,  -321,   241,
    -321,    18,  -321,  -321,  -321,   148,  -321,   225,  -321,   226,
    -321,  -321,   112,   215,    16,   158,   167,   114,  -321,  -321,
    -321,     4,   213,   244,  -321,  -321,   151,  -321,  -321,   229,
     230,  -321,  -321,   198,    61,  -321,   198,    71,  -321,   231,
      29,  -321,   108,  -321,   108,    92,   192,    77,   236,    22,
     194,  -321,   196,   237,   239,   240,   242,   243,   245,   246,
     247,   125,  -321,     5,  -321,   249,  -321,  -321,   251,  -321,
    -321,    47,   253,  -321,   256,  -321,   198,   257,  -321,   198,
      77,   250,  -321,   254,   255,   258,    10,  -321,    19,   152,
    -321,  -321,  -321,    77,   248,   252,   132,  -321,  -321,    17,
    -321,  -321,  -321,    17,   259,   260,   261,   262,  -321,  -321,
     114,  -321,  -321,  -321,  -321,    53,  -321,  -321,   267,   264,
    -321,   265,  -321,   269,  -321,    77,   263,   266,   270,  -321,
    -321,  -321,  -321,    77,    77,  -321,   268,   271,   178,   183,
     188,   189,    77,    77,   272,  -321,  -321,    77,    77,   272,
    -321,  -321,  -321,  -321,   103,    92,  -321,  -321,   273,  -321,
    -321,  -321,  -321,  -321,  -321,   274,  -321,  -321,   275,   276,
     277,   278,   279,   280,   281,   282,   283,   284,  -321,  -321,
      17,  -321,  -321,  -321,  -321,  -321,   285,   169,  -321,   170,
     286,   114,   114,  -321,  -321,  -321,   287,   289,   290,   291,
     292,   293,   294,   295,  -321,  -321,   106,  -321,  -321,  -321,
     114,   301,   301,   114,   303,   304,   305,   306,   307,   308,
     309,   310,  -321,   114,  -321,   301,  -321,  -321,  -321,  -321,
    -321,  -321,  -321,  -321,   131,  -321
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -321,  -321,  -321,  -321,  -321,  -321,  -321,  -321,  -321,  -321,
    -321,  -321,   -98,  -321,  -321,  -321,  -321,  -321,  -321,  -321,
    -321,  -321,  -321,  -321,    81,  -321,  -321,   -76,  -321,  -321,
    -321,  -321,  -321,  -321,  -321,    74,  -321,  -321,  -321,  -321,
    -321,  -321,  -321,  -321,    35,   -40,   128,  -321,  -321,  -321,
    -321,  -321,  -321,  -321,  -321,  -321,  -321,  -321,  -321,  -320,
    -245,  -321,  -321,  -321,  -321,  -321,    97,   -27,  -321,  -321,
    -321,  -321,  -321,  -321,  -321,  -321,  -321,  -321,  -321,   135,
    -321,  -321,  -321,  -321,  -321,  -321,    82,  -321,  -321,  -321,
     288,   296,  -321,  -183,  -321,  -321,  -321,   -48
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -171
static const yytype_int16 yytable[] =
{
     140,   142,   229,    74,    77,   296,   101,    56,   102,   121,
     103,   351,   352,   152,   128,   223,   -14,   147,   153,   190,
     190,    94,   104,    92,   223,   234,   148,   235,   224,   105,
     143,   225,   144,   365,   106,   129,   122,   224,   107,    57,
     225,    97,   191,   374,   269,   192,   192,   137,   138,   139,
      58,   236,    59,   271,   -58,   -58,    58,    80,    59,    81,
      60,   149,    61,    62,   215,    63,    60,    50,    61,    62,
     150,    63,   256,    67,   218,    68,    69,    70,   297,    94,
      68,    69,    70,    95,   216,    51,   174,   177,    90,   232,
     172,    69,    70,   164,   219,    71,    96,   165,   -24,    97,
      71,   175,    69,    70,   323,   364,   324,    91,   325,   324,
     173,   325,   329,   223,   -49,   161,    75,   199,    76,    69,
      70,   176,   264,   162,   326,   214,   224,   326,   217,   225,
      58,   200,    59,  -127,   130,   275,    31,   131,     2,     3,
      60,   186,    61,    62,     4,    63,     5,     6,     7,     8,
       9,   250,    10,   278,   279,   280,    58,   250,    59,   251,
     119,   195,   120,   196,   281,   375,    33,   302,   261,  -170,
     197,   263,   198,   179,   180,   306,   307,   208,   208,   209,
     272,   310,    36,   311,   318,   319,   312,   -75,   313,   321,
     322,   314,   316,   315,   317,   346,   208,   347,   348,   270,
      38,   270,    69,    70,    40,    98,    99,   134,   135,    42,
      46,   155,   156,   230,   231,   237,   238,   240,   241,    47,
      49,    52,    53,    54,    66,    78,    87,    55,    89,   125,
     126,    84,   100,   132,    88,   133,   158,   151,   159,   160,
     169,    85,   167,   170,   178,   189,   171,   163,   205,   207,
     181,   183,   -53,   212,   253,   213,   254,   233,   259,   260,
     262,   222,   242,   268,   244,   243,   245,   246,   300,   247,
     362,   265,   301,   248,   249,   266,   267,   252,   289,   276,
     344,   228,   194,   277,   290,   291,   292,   293,   298,   299,
     345,   305,   255,     0,   303,     0,   204,   304,   320,   308,
     334,   335,   309,     0,   330,   333,     0,     0,   336,   337,
     338,   339,   340,   341,   342,   343,     0,     0,   354,   349,
     355,   356,   357,   358,   359,   360,   361,   250,   366,   367,
     368,   369,   370,   371,   372,   373,     0,     0,     0,     0,
       0,     0,     0,    65,     0,     0,     0,     0,    86
};

static const yytype_int16 yycheck[] =
{
      98,    99,   185,    51,    52,   250,     1,     1,     3,     5,
       5,   331,   332,    25,     3,     5,     3,    24,    30,     3,
       3,     3,    17,    71,     5,     3,    33,     5,    18,    24,
       1,    21,     3,   353,    29,    24,    32,    18,    33,    33,
      21,    23,    26,   363,    34,    29,    29,    95,    96,    97,
       3,    29,     5,    34,    25,    26,     3,     1,     5,     3,
      13,    24,    15,    16,     3,    18,    13,     1,    15,    16,
      33,    18,    25,     1,     3,     3,     4,     5,    25,     3,
       3,     4,     5,     7,    23,    19,   134,   135,     5,   187,
       3,     4,     5,     1,    23,    23,    20,     5,     3,    23,
      23,     3,     4,     5,     1,   350,     3,    24,     5,     3,
      23,     5,   295,     5,     3,    26,     1,     3,     3,     4,
       5,    23,   220,    34,    21,   173,    18,    21,   176,    21,
       3,    17,     5,    21,    21,   233,     3,    24,     0,     1,
      13,    29,    15,    16,     6,    18,     8,     9,    10,    11,
      12,    26,    14,    21,    22,    23,     3,    26,     5,    34,
      26,     3,    28,     5,    32,    34,     3,   265,   216,     3,
       3,   219,     5,    25,    26,   273,   274,    26,    26,    28,
      28,     3,     5,     5,   282,   283,     3,    27,     5,   287,
     288,     3,     3,     5,     5,    26,    26,    28,    28,   226,
       3,   228,     4,     5,     3,    21,    22,    21,    22,     3,
      19,    21,    22,    21,    22,    21,    22,    21,    22,     3,
      21,    19,    19,    19,    31,     5,     3,    27,    19,     5,
       3,    36,    24,     5,    27,     3,     3,    27,    19,     5,
       5,    36,    24,     5,     3,    30,    25,    36,    35,     5,
      25,    25,    21,    24,     5,    25,     5,    21,     5,     3,
       3,   180,    25,     5,    24,    26,    24,    24,     3,    24,
     346,    21,     3,    27,    27,    21,    21,   203,   243,    31,
     320,   184,   154,    31,    25,    25,    25,    25,    21,    25,
       5,    21,   210,    -1,    31,    -1,   161,    31,    26,    31,
      25,    25,    31,    -1,    31,    31,    -1,    -1,    31,    31,
      31,    31,    31,    31,    31,    31,    -1,    -1,    31,    33,
      31,    31,    31,    31,    31,    31,    31,    26,    25,    25,
      25,    25,    25,    25,    25,    25,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    47,    -1,    -1,    -1,    -1,    60
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    38,     0,     1,     6,     8,     9,    10,    11,    12,
      14,    39,    44,    53,    65,   110,   117,   131,    40,    45,
      54,    66,   111,   118,   132,    41,    42,    46,    47,    55,
      56,     3,    67,     3,   112,   119,     5,   133,     3,    43,
       3,    48,     3,    57,    68,    70,    19,     3,   120,    21,
       1,    19,    19,    19,    19,    27,     1,    33,     3,     5,
      13,    15,    16,    18,   127,   128,    31,     1,     3,     4,
       5,    23,    49,    52,   134,     1,     3,   134,     5,    69,
       1,     3,    62,   113,    36,    36,   127,     3,    27,    19,
       5,    24,   134,    50,     3,     7,    20,    23,    21,    22,
      24,     1,     3,     5,    17,    24,    29,    33,    72,    73,
      74,    75,    76,    77,    88,    91,    94,   100,   108,    26,
      28,     5,    32,   115,   116,     5,     3,   129,     3,    24,
      21,    24,     5,     3,    21,    22,    51,   134,   134,   134,
      49,   134,    49,     1,     3,    60,    61,    24,    33,    24,
      33,    27,    25,    30,    78,    21,    22,    95,     3,    19,
       5,    26,    34,    36,     1,     5,   130,    24,   121,     5,
       5,    25,     3,    23,   134,     3,    23,   134,     3,    25,
      26,    25,   102,    25,   101,   109,    29,    89,    90,    30,
       3,    26,    29,    79,    83,     3,     5,     3,     5,     3,
      17,    96,    97,    71,   116,    35,   114,     5,    26,    28,
     122,   123,    24,    25,   134,     3,    23,   134,     3,    23,
      58,    59,    61,     5,    18,    21,   103,   104,   103,   130,
      21,    22,    49,    21,     3,     5,    29,    21,    22,    80,
      21,    22,    25,    26,    24,    24,    24,    24,    27,    27,
      26,    34,    72,     5,     5,   123,    25,   124,   128,     5,
       3,   134,     3,   134,    49,    21,    21,    21,     5,    34,
     104,    34,    28,    93,    92,    49,    31,    31,    21,    22,
      23,    32,    86,    84,    81,    82,    83,    87,    85,    81,
      25,    25,    25,    25,    98,    99,    97,    25,    21,    25,
       3,     3,    49,    31,    31,    21,    49,    49,    31,    31,
       3,     5,     3,     5,     3,     5,     3,     5,    49,    49,
      26,    49,    49,     1,     3,     5,    21,    63,    64,   130,
      31,   105,   107,    31,    25,    25,    31,    31,    31,    31,
      31,    31,    31,    31,    82,     5,    26,    28,    28,    33,
     126,    96,    96,   106,    31,    31,    31,    31,    31,    31,
      31,    31,    64,   125,    97,    96,    25,    25,    25,    25,
      25,    25,    25,    25,    96,    34
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
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
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
  if (!yyvaluep)
    return;
  YYUSE (yylocationp);
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
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

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
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

  switch (yytype)
    {

      default:
	break;
    }
}

/* Prevent warnings from -Wmissing-prototypes.  */
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


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Location data for the lookahead symbol.  */
YYLTYPE yylloc;

/* Number of syntax errors so far.  */
int yynerrs;



/*-------------------------.
| yyparse or yypush_parse.  |
`-------------------------*/

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

       Refer to the stacks thru separate pointers, to allow yyoverflow
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
    YYLTYPE yyerror_range[2];

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken;
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

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yyls = yylsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  yyssp = yyss;
  yyvsp = yyvs;
  yylsp = yyls;

#if YYLTYPE_IS_TRIVIAL
  /* Initialize the default location before parsing starts.  */
  yylloc.first_line   = yylloc.last_line   = 1;
  yylloc.first_column = yylloc.last_column = 1;
#endif

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
  if (yyn == YYPACT_NINF)
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
      if (yyn == 0 || yyn == YYTABLE_NINF)
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
  *++yyvsp = yylval;
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

/* Line 1455 of yacc.c  */
#line 106 "../mu32/mut.y"
    {  fatal_error(1,FEHLERZEILE); }
    break;

  case 14:

/* Line 1455 of yacc.c  */
#line 118 "../mu32/mut.y"
    { init_komplex_ton_list (); }
    break;

  case 16:

/* Line 1455 of yacc.c  */
#line 123 "../mu32/mut.y"
    { if ( fabs((yyvsp[(5) - (5)].f_value)) > 0.001 )
                         get_new_intervall ((yyvsp[(1) - (5)].identifier), (yyvsp[(3) - (5)].f_value) / (yyvsp[(5) - (5)].f_value));
                      else
			fatal_error (46, mutC_STR((yyvsp[(1) - (5)].identifier)) ); }
    break;

  case 17:

/* Line 1455 of yacc.c  */
#line 129 "../mu32/mut.y"
    { if ( fabs ((yyvsp[(3) - (5)].f_value)) > 0.001 )
                          get_new_intervall ((yyvsp[(1) - (5)].identifier), pow ((yyvsp[(5) - (5)].f_value), 1 / (yyvsp[(3) - (5)].f_value)));
                      else
			fatal_error (46, mutC_STR((yyvsp[(1) - (5)].identifier))); }
    break;

  case 18:

/* Line 1455 of yacc.c  */
#line 138 "../mu32/mut.y"
    { get_new_intervall_komplex ((yyvsp[(1) - (3)].identifier)); }
    break;

  case 19:

/* Line 1455 of yacc.c  */
#line 139 "../mu32/mut.y"
    { fatal_error(71, mutC_STR((yyvsp[(1) - (3)].identifier))); }
    break;

  case 20:

/* Line 1455 of yacc.c  */
#line 140 "../mu32/mut.y"
    { fatal_error(70,mutT("'='"),FEHLERZEILE); }
    break;

  case 24:

/* Line 1455 of yacc.c  */
#line 152 "../mu32/mut.y"
    { init_komplex_ton_list (); }
    break;

  case 26:

/* Line 1455 of yacc.c  */
#line 157 "../mu32/mut.y"
    { get_new_ton_absolut ((yyvsp[(1) - (3)].identifier), (yyvsp[(3) - (3)].f_value)); }
    break;

  case 27:

/* Line 1455 of yacc.c  */
#line 161 "../mu32/mut.y"
    { get_new_ton_komplex_negative ((yyvsp[(1) - (5)].identifier), (yyvsp[(3) - (5)].identifier)); }
    break;

  case 28:

/* Line 1455 of yacc.c  */
#line 165 "../mu32/mut.y"
    { get_new_ton_komplex_positive ((yyvsp[(1) - (3)].identifier), (yyvsp[(3) - (3)].identifier)); }
    break;

  case 29:

/* Line 1455 of yacc.c  */
#line 169 "../mu32/mut.y"
    { get_new_ton_komplex_positive ((yyvsp[(1) - (5)].identifier), (yyvsp[(3) - (5)].identifier)); }
    break;

  case 30:

/* Line 1455 of yacc.c  */
#line 171 "../mu32/mut.y"
    { fatal_error( 72, mutC_STR((yyvsp[(1) - (3)].identifier)) ); }
    break;

  case 34:

/* Line 1455 of yacc.c  */
#line 185 "../mu32/mut.y"
    { get_new_faktor_anteil ( (double) 1, (yyvsp[(2) - (2)].identifier)); }
    break;

  case 35:

/* Line 1455 of yacc.c  */
#line 188 "../mu32/mut.y"
    { get_new_faktor_anteil ( (double) -1, (yyvsp[(2) - (2)].identifier)); }
    break;

  case 36:

/* Line 1455 of yacc.c  */
#line 191 "../mu32/mut.y"
    { get_new_faktor_anteil ( (yyvsp[(2) - (3)].f_value), (yyvsp[(3) - (3)].identifier)); }
    break;

  case 37:

/* Line 1455 of yacc.c  */
#line 194 "../mu32/mut.y"
    { get_new_faktor_anteil ( -((yyvsp[(2) - (3)].f_value)), (yyvsp[(3) - (3)].identifier)); }
    break;

  case 38:

/* Line 1455 of yacc.c  */
#line 197 "../mu32/mut.y"
    { if ( fabs((yyvsp[(3) - (4)].f_value)) > 0.001 )
                       get_new_faktor_anteil ( (double) 1 / ((yyvsp[(3) - (4)].f_value)), (yyvsp[(4) - (4)].identifier));
                     else
                       fatal_error(53, FEHLERZEILE);  }
    break;

  case 39:

/* Line 1455 of yacc.c  */
#line 203 "../mu32/mut.y"
    { if ( fabs((yyvsp[(3) - (4)].f_value)) > 0.001 )
                       get_new_faktor_anteil ( (double) -1 / ((yyvsp[(3) - (4)].f_value)), (yyvsp[(4) - (4)].identifier));
                     else
                       fatal_error(53, FEHLERZEILE);  }
    break;

  case 40:

/* Line 1455 of yacc.c  */
#line 209 "../mu32/mut.y"
    { if ( fabs((yyvsp[(4) - (5)].f_value)) > 0.001 )
                       get_new_faktor_anteil ( ((yyvsp[(2) - (5)].f_value)) / ((yyvsp[(4) - (5)].f_value)), (yyvsp[(5) - (5)].identifier));
                     else
                       fatal_error(53, FEHLERZEILE);  }
    break;

  case 41:

/* Line 1455 of yacc.c  */
#line 215 "../mu32/mut.y"
    { if ( fabs((yyvsp[(4) - (5)].f_value)) > 0.001 )
                       get_new_faktor_anteil ( -((yyvsp[(2) - (5)].f_value)) / ((yyvsp[(4) - (5)].f_value)), (yyvsp[(5) - (5)].identifier));
                     else
                       fatal_error(53, FEHLERZEILE);  }
    break;

  case 42:

/* Line 1455 of yacc.c  */
#line 236 "../mu32/mut.y"
    { get_new_faktor_anteil ( (double) 1.0 , (yyvsp[(1) - (1)].identifier)); }
    break;

  case 43:

/* Line 1455 of yacc.c  */
#line 244 "../mu32/mut.y"
    { get_new_faktor_anteil ( (yyvsp[(1) - (2)].f_value), (yyvsp[(2) - (2)].identifier)); }
    break;

  case 44:

/* Line 1455 of yacc.c  */
#line 247 "../mu32/mut.y"
    { if ( fabs((yyvsp[(2) - (3)].f_value)) > 0.001 )
                       get_new_faktor_anteil ( (double) 1 / ((yyvsp[(2) - (3)].f_value)), (yyvsp[(3) - (3)].identifier));
                     else
                       fatal_error(53, FEHLERZEILE);  }
    break;

  case 45:

/* Line 1455 of yacc.c  */
#line 253 "../mu32/mut.y"
    { if ( fabs((yyvsp[(3) - (4)].f_value)) > 0.001 )
                       get_new_faktor_anteil ( ((yyvsp[(1) - (4)].f_value)) / ((yyvsp[(3) - (4)].f_value)), (yyvsp[(4) - (4)].identifier));
                     else
                       fatal_error(53, FEHLERZEILE);  }
    break;

  case 49:

/* Line 1455 of yacc.c  */
#line 286 "../mu32/mut.y"
    { init_ton_liste (); }
    break;

  case 51:

/* Line 1455 of yacc.c  */
#line 291 "../mu32/mut.y"
    { init_komplex_ton_list (); }
    break;

  case 52:

/* Line 1455 of yacc.c  */
#line 293 "../mu32/mut.y"
    { get_new_tonsystem ((yyvsp[(1) - (8)].identifier), (yyvsp[(3) - (8)].integer)); }
    break;

  case 53:

/* Line 1455 of yacc.c  */
#line 295 "../mu32/mut.y"
    { init_komplex_ton_list (); }
    break;

  case 54:

/* Line 1455 of yacc.c  */
#line 297 "../mu32/mut.y"
    { get_new_tonsystem_negative ((yyvsp[(1) - (9)].identifier), (yyvsp[(3) - (9)].integer)); }
    break;

  case 57:

/* Line 1455 of yacc.c  */
#line 303 "../mu32/mut.y"
    { get_new_ton_in_tonsystem ((yyvsp[(1) - (1)].identifier)); }
    break;

  case 58:

/* Line 1455 of yacc.c  */
#line 304 "../mu32/mut.y"
    { get_new_ton_in_tonsystem (NULL); }
    break;

  case 59:

/* Line 1455 of yacc.c  */
#line 305 "../mu32/mut.y"
    { fatal_error(73,FEHLERZEILE); }
    break;

  case 60:

/* Line 1455 of yacc.c  */
#line 309 "../mu32/mut.y"
    { get_new_name_in_parameterlist ((yyvsp[(1) - (1)].identifier)); }
    break;

  case 61:

/* Line 1455 of yacc.c  */
#line 311 "../mu32/mut.y"
    { get_new_name_in_parameterlist ((yyvsp[(3) - (3)].identifier)); }
    break;

  case 62:

/* Line 1455 of yacc.c  */
#line 312 "../mu32/mut.y"
    { fatal_error(74,FEHLERZEILE); }
    break;

  case 63:

/* Line 1455 of yacc.c  */
#line 317 "../mu32/mut.y"
    {}
    break;

  case 64:

/* Line 1455 of yacc.c  */
#line 318 "../mu32/mut.y"
    {}
    break;

  case 65:

/* Line 1455 of yacc.c  */
#line 319 "../mu32/mut.y"
    { fatal_error(74,FEHLERZEILE); }
    break;

  case 66:

/* Line 1455 of yacc.c  */
#line 324 "../mu32/mut.y"
    { get_new_name_in_argument_list ((yyvsp[(1) - (1)].identifier)) ;  }
    break;

  case 67:

/* Line 1455 of yacc.c  */
#line 325 "../mu32/mut.y"
    { get_new_number_in_argument_list ((yyvsp[(1) - (1)].integer)) ;  }
    break;

  case 68:

/* Line 1455 of yacc.c  */
#line 326 "../mu32/mut.y"
    { get_new_number_in_argument_list (-((yyvsp[(2) - (2)].integer))); }
    break;

  case 72:

/* Line 1455 of yacc.c  */
#line 341 "../mu32/mut.y"
    { init_umstimmung ((yyvsp[(1) - (1)].identifier));
                      init_parameter_liste (); }
    break;

  case 73:

/* Line 1455 of yacc.c  */
#line 343 "../mu32/mut.y"
    { eintrage_parameterliste_in_umstimmung (); }
    break;

  case 74:

/* Line 1455 of yacc.c  */
#line 345 "../mu32/mut.y"
    { get_new_umstimmung (); }
    break;

  case 75:

/* Line 1455 of yacc.c  */
#line 348 "../mu32/mut.y"
    { init_umstimmung ((yyvsp[(1) - (1)].identifier));
                      init_parameter_liste (); }
    break;

  case 76:

/* Line 1455 of yacc.c  */
#line 351 "../mu32/mut.y"
    { eintrage_parameterliste_in_umstimmung (); }
    break;

  case 77:

/* Line 1455 of yacc.c  */
#line 353 "../mu32/mut.y"
    { get_new_umstimmung (); }
    break;

  case 78:

/* Line 1455 of yacc.c  */
#line 357 "../mu32/mut.y"
    {}
    break;

  case 79:

/* Line 1455 of yacc.c  */
#line 358 "../mu32/mut.y"
    {}
    break;

  case 80:

/* Line 1455 of yacc.c  */
#line 359 "../mu32/mut.y"
    {}
    break;

  case 81:

/* Line 1455 of yacc.c  */
#line 360 "../mu32/mut.y"
    {}
    break;

  case 82:

/* Line 1455 of yacc.c  */
#line 361 "../mu32/mut.y"
    {}
    break;

  case 83:

/* Line 1455 of yacc.c  */
#line 362 "../mu32/mut.y"
    {}
    break;

  case 84:

/* Line 1455 of yacc.c  */
#line 363 "../mu32/mut.y"
    {}
    break;

  case 85:

/* Line 1455 of yacc.c  */
#line 364 "../mu32/mut.y"
    {}
    break;

  case 86:

/* Line 1455 of yacc.c  */
#line 365 "../mu32/mut.y"
    {}
    break;

  case 87:

/* Line 1455 of yacc.c  */
#line 366 "../mu32/mut.y"
    {}
    break;

  case 88:

/* Line 1455 of yacc.c  */
#line 367 "../mu32/mut.y"
    {fatal_error(75,FEHLERZEILE);}
    break;

  case 89:

/* Line 1455 of yacc.c  */
#line 373 "../mu32/mut.y"
    { get_umstimmung_taste_abs (zahl, (yyvsp[(1) - (3)].integer), NULL); }
    break;

  case 90:

/* Line 1455 of yacc.c  */
#line 375 "../mu32/mut.y"
    { get_umstimmung_taste_abs (parameter, 0.0, (yyvsp[(1) - (3)].identifier)); }
    break;

  case 91:

/* Line 1455 of yacc.c  */
#line 380 "../mu32/mut.y"
    { get_umstimmung_taste_rel (zahl, (yyvsp[(3) - (5)].integer), NULL, '+'); }
    break;

  case 92:

/* Line 1455 of yacc.c  */
#line 382 "../mu32/mut.y"
    { get_umstimmung_taste_rel (parameter, 0.0, (yyvsp[(3) - (5)].identifier), '+'); }
    break;

  case 93:

/* Line 1455 of yacc.c  */
#line 384 "../mu32/mut.y"
    { get_umstimmung_taste_rel (zahl, (yyvsp[(3) - (5)].integer), NULL, '-'); }
    break;

  case 94:

/* Line 1455 of yacc.c  */
#line 386 "../mu32/mut.y"
    { get_umstimmung_taste_rel (parameter, 0.0, (yyvsp[(3) - (5)].identifier), '-'); }
    break;

  case 95:

/* Line 1455 of yacc.c  */
#line 391 "../mu32/mut.y"
    { get_umstimmung_breite_abs (zahl, (yyvsp[(4) - (7)].integer), NULL); }
    break;

  case 96:

/* Line 1455 of yacc.c  */
#line 393 "../mu32/mut.y"
    { get_umstimmung_breite_abs (parameter, 0.0, (yyvsp[(4) - (7)].identifier)); }
    break;

  case 97:

/* Line 1455 of yacc.c  */
#line 398 "../mu32/mut.y"
    { get_umstimmung_breite_rel (zahl, (yyvsp[(6) - (9)].integer), NULL, '+'); }
    break;

  case 98:

/* Line 1455 of yacc.c  */
#line 400 "../mu32/mut.y"
    { get_umstimmung_breite_rel (parameter, 0.0, (yyvsp[(6) - (9)].identifier), '+'); }
    break;

  case 99:

/* Line 1455 of yacc.c  */
#line 402 "../mu32/mut.y"
    { get_umstimmung_breite_rel (zahl, (yyvsp[(6) - (9)].integer), NULL, '-'); }
    break;

  case 100:

/* Line 1455 of yacc.c  */
#line 404 "../mu32/mut.y"
    { get_umstimmung_breite_rel (parameter, 0.0, (yyvsp[(6) - (9)].identifier), '-'); }
    break;

  case 101:

/* Line 1455 of yacc.c  */
#line 406 "../mu32/mut.y"
    { get_umstimmung_breite_rel (zahl, (yyvsp[(6) - (9)].integer), NULL, '*'); }
    break;

  case 102:

/* Line 1455 of yacc.c  */
#line 408 "../mu32/mut.y"
    { get_umstimmung_breite_rel (parameter, 0.0, (yyvsp[(6) - (9)].identifier), '*'); }
    break;

  case 103:

/* Line 1455 of yacc.c  */
#line 410 "../mu32/mut.y"
    { get_umstimmung_breite_rel (zahl, (yyvsp[(6) - (9)].integer), NULL, '/'); }
    break;

  case 104:

/* Line 1455 of yacc.c  */
#line 412 "../mu32/mut.y"
    { get_umstimmung_breite_rel (parameter, 0.0, (yyvsp[(6) - (9)].identifier), '/'); }
    break;

  case 105:

/* Line 1455 of yacc.c  */
#line 417 "../mu32/mut.y"
    { init_umstimm_expression_list (); }
    break;

  case 106:

/* Line 1455 of yacc.c  */
#line 419 "../mu32/mut.y"
    { get_umstimmung_tonhoehe_veraendert (); }
    break;

  case 107:

/* Line 1455 of yacc.c  */
#line 426 "../mu32/mut.y"
    {}
    break;

  case 108:

/* Line 1455 of yacc.c  */
#line 427 "../mu32/mut.y"
    {}
    break;

  case 109:

/* Line 1455 of yacc.c  */
#line 429 "../mu32/mut.y"
    { init_komplex_ton_list();
                     get_new_umstimm_expression (NULL);
                   }
    break;

  case 110:

/* Line 1455 of yacc.c  */
#line 432 "../mu32/mut.y"
    {}
    break;

  case 111:

/* Line 1455 of yacc.c  */
#line 436 "../mu32/mut.y"
    {}
    break;

  case 112:

/* Line 1455 of yacc.c  */
#line 437 "../mu32/mut.y"
    {}
    break;

  case 113:

/* Line 1455 of yacc.c  */
#line 442 "../mu32/mut.y"
    { init_komplex_ton_list();
                     get_new_umstimm_expression (NULL);
                   }
    break;

  case 115:

/* Line 1455 of yacc.c  */
#line 450 "../mu32/mut.y"
    { get_new_umstimm_expression ((yyvsp[(1) - (1)].identifier)); }
    break;

  case 116:

/* Line 1455 of yacc.c  */
#line 451 "../mu32/mut.y"
    { get_new_umstimm_expression ("@"); }
    break;

  case 117:

/* Line 1455 of yacc.c  */
#line 453 "../mu32/mut.y"
    { init_komplex_ton_list (); }
    break;

  case 118:

/* Line 1455 of yacc.c  */
#line 455 "../mu32/mut.y"
    { get_new_umstimm_expression_positive ((yyvsp[(1) - (4)].identifier)); }
    break;

  case 119:

/* Line 1455 of yacc.c  */
#line 456 "../mu32/mut.y"
    { init_komplex_ton_list (); }
    break;

  case 120:

/* Line 1455 of yacc.c  */
#line 458 "../mu32/mut.y"
    { get_new_umstimm_expression_positive ( "@" ); }
    break;

  case 121:

/* Line 1455 of yacc.c  */
#line 459 "../mu32/mut.y"
    { init_komplex_ton_list (); }
    break;

  case 122:

/* Line 1455 of yacc.c  */
#line 461 "../mu32/mut.y"
    { get_new_umstimm_expression_negative ((yyvsp[(1) - (4)].identifier)); }
    break;

  case 123:

/* Line 1455 of yacc.c  */
#line 462 "../mu32/mut.y"
    { init_komplex_ton_list (); }
    break;

  case 124:

/* Line 1455 of yacc.c  */
#line 464 "../mu32/mut.y"
    { get_new_umstimm_expression_negative ( "@" ); }
    break;

  case 125:

/* Line 1455 of yacc.c  */
#line 469 "../mu32/mut.y"
    { init_komplex_ton_list (); }
    break;

  case 126:

/* Line 1455 of yacc.c  */
#line 471 "../mu32/mut.y"
    { get_umstimmung_wiederholung_abs (); }
    break;

  case 127:

/* Line 1455 of yacc.c  */
#line 472 "../mu32/mut.y"
    { init_komplex_ton_list (); }
    break;

  case 128:

/* Line 1455 of yacc.c  */
#line 474 "../mu32/mut.y"
    { get_umstimmung_wiederholung_abs_negative (); }
    break;

  case 129:

/* Line 1455 of yacc.c  */
#line 478 "../mu32/mut.y"
    { init_komplex_ton_list (); }
    break;

  case 130:

/* Line 1455 of yacc.c  */
#line 480 "../mu32/mut.y"
    { get_umstimmung_wiederholung_rel_positive (); }
    break;

  case 131:

/* Line 1455 of yacc.c  */
#line 481 "../mu32/mut.y"
    { init_komplex_ton_list (); }
    break;

  case 132:

/* Line 1455 of yacc.c  */
#line 483 "../mu32/mut.y"
    { get_umstimmung_wiederholung_rel_negative (); }
    break;

  case 133:

/* Line 1455 of yacc.c  */
#line 487 "../mu32/mut.y"
    { init_aktions_liste (); }
    break;

  case 134:

/* Line 1455 of yacc.c  */
#line 489 "../mu32/mut.y"
    { get_umstimmung_umstimmungs_bund (); }
    break;

  case 135:

/* Line 1455 of yacc.c  */
#line 493 "../mu32/mut.y"
    {}
    break;

  case 136:

/* Line 1455 of yacc.c  */
#line 494 "../mu32/mut.y"
    {}
    break;

  case 137:

/* Line 1455 of yacc.c  */
#line 498 "../mu32/mut.y"
    { init_argument_liste (); 
                       get_new_aktion_aufruf_element ((yyvsp[(1) - (1)].identifier)); }
    break;

  case 138:

/* Line 1455 of yacc.c  */
#line 500 "../mu32/mut.y"
    { init_argument_liste (); }
    break;

  case 139:

/* Line 1455 of yacc.c  */
#line 502 "../mu32/mut.y"
    { get_new_aktion_aufruf_element ((yyvsp[(1) - (5)].identifier)); }
    break;

  case 140:

/* Line 1455 of yacc.c  */
#line 504 "../mu32/mut.y"
    { init_integersequenz ();}
    break;

  case 141:

/* Line 1455 of yacc.c  */
#line 506 "../mu32/mut.y"
    { get_new_aktion_midi_out_element (); }
    break;

  case 142:

/* Line 1455 of yacc.c  */
#line 510 "../mu32/mut.y"
    { init_umstimmungs_case_liste (); }
    break;

  case 143:

/* Line 1455 of yacc.c  */
#line 512 "../mu32/mut.y"
    { get_umstimmung_umstimm_case_zahl ((yyvsp[(1) - (5)].integer)); }
    break;

  case 144:

/* Line 1455 of yacc.c  */
#line 513 "../mu32/mut.y"
    { init_umstimmungs_case_liste (); }
    break;

  case 145:

/* Line 1455 of yacc.c  */
#line 515 "../mu32/mut.y"
    { get_umstimmung_umstimm_case_parameter ((yyvsp[(1) - (5)].identifier)); }
    break;

  case 146:

/* Line 1455 of yacc.c  */
#line 519 "../mu32/mut.y"
    {}
    break;

  case 147:

/* Line 1455 of yacc.c  */
#line 520 "../mu32/mut.y"
    {}
    break;

  case 148:

/* Line 1455 of yacc.c  */
#line 525 "../mu32/mut.y"
    { init_aktions_liste (); }
    break;

  case 149:

/* Line 1455 of yacc.c  */
#line 527 "../mu32/mut.y"
    { get_umstimmungs_case_zahl_element ((yyvsp[(1) - (5)].integer)); }
    break;

  case 150:

/* Line 1455 of yacc.c  */
#line 529 "../mu32/mut.y"
    { init_aktions_liste (); }
    break;

  case 151:

/* Line 1455 of yacc.c  */
#line 531 "../mu32/mut.y"
    { get_umstimmungs_case_zahl_element (-((yyvsp[(2) - (6)].integer))); }
    break;

  case 152:

/* Line 1455 of yacc.c  */
#line 533 "../mu32/mut.y"
    { init_aktions_liste (); }
    break;

  case 153:

/* Line 1455 of yacc.c  */
#line 535 "../mu32/mut.y"
    { get_umstimmungs_case_default_element (); }
    break;

  case 154:

/* Line 1455 of yacc.c  */
#line 540 "../mu32/mut.y"
    { init_integersequenz ();}
    break;

  case 155:

/* Line 1455 of yacc.c  */
#line 542 "../mu32/mut.y"
    { get_umstimmung_midi_out (); }
    break;

  case 156:

/* Line 1455 of yacc.c  */
#line 547 "../mu32/mut.y"
    {}
    break;

  case 157:

/* Line 1455 of yacc.c  */
#line 551 "../mu32/mut.y"
    {}
    break;

  case 158:

/* Line 1455 of yacc.c  */
#line 552 "../mu32/mut.y"
    {}
    break;

  case 159:

/* Line 1455 of yacc.c  */
#line 557 "../mu32/mut.y"
    { init_tastenliste (); }
    break;

  case 160:

/* Line 1455 of yacc.c  */
#line 559 "../mu32/mut.y"
    { get_new_harmonie ((yyvsp[(1) - (7)].identifier), (yyvsp[(7) - (7)].integer)); }
    break;

  case 161:

/* Line 1455 of yacc.c  */
#line 561 "../mu32/mut.y"
    { fatal_error(76, mutC_STR((yyvsp[(1) - (3)].identifier))); }
    break;

  case 162:

/* Line 1455 of yacc.c  */
#line 565 "../mu32/mut.y"
    { (yyval.integer) = -1; }
    break;

  case 163:

/* Line 1455 of yacc.c  */
#line 566 "../mu32/mut.y"
    { (yyval.integer) = (yyvsp[(2) - (2)].integer); }
    break;

  case 164:

/* Line 1455 of yacc.c  */
#line 570 "../mu32/mut.y"
    {}
    break;

  case 165:

/* Line 1455 of yacc.c  */
#line 571 "../mu32/mut.y"
    {}
    break;

  case 166:

/* Line 1455 of yacc.c  */
#line 575 "../mu32/mut.y"
    { get_new_taste ( (yyvsp[(1) - (1)].integer), '+'); }
    break;

  case 167:

/* Line 1455 of yacc.c  */
#line 576 "../mu32/mut.y"
    { get_new_taste ( (yyvsp[(2) - (2)].integer), '*'); }
    break;

  case 168:

/* Line 1455 of yacc.c  */
#line 580 "../mu32/mut.y"
    {}
    break;

  case 169:

/* Line 1455 of yacc.c  */
#line 584 "../mu32/mut.y"
    {}
    break;

  case 170:

/* Line 1455 of yacc.c  */
#line 585 "../mu32/mut.y"
    { init_ausloeser ();
                         /* fÅr die Anfangsausloesung der Logik */
                       }
    break;

  case 171:

/* Line 1455 of yacc.c  */
#line 588 "../mu32/mut.y"
    {}
    break;

  case 172:

/* Line 1455 of yacc.c  */
#line 593 "../mu32/mut.y"
    { get_new_logik ((yyvsp[(1) - (4)].identifier), NULL);
                init_anweisungs_liste (); }
    break;

  case 173:

/* Line 1455 of yacc.c  */
#line 596 "../mu32/mut.y"
    { vervollstaendige_logik (); }
    break;

  case 174:

/* Line 1455 of yacc.c  */
#line 598 "../mu32/mut.y"
    { get_new_logik ((yyvsp[(1) - (5)].identifier), (yyvsp[(4) - (5)].identifier));
                init_anweisungs_liste (); }
    break;

  case 175:

/* Line 1455 of yacc.c  */
#line 601 "../mu32/mut.y"
    { vervollstaendige_logik (); }
    break;

  case 176:

/* Line 1455 of yacc.c  */
#line 605 "../mu32/mut.y"
    {}
    break;

  case 177:

/* Line 1455 of yacc.c  */
#line 606 "../mu32/mut.y"
    {}
    break;

  case 178:

/* Line 1455 of yacc.c  */
#line 611 "../mu32/mut.y"
    { init_aktions_liste (); }
    break;

  case 179:

/* Line 1455 of yacc.c  */
#line 613 "../mu32/mut.y"
    { get_new_anweisung (); }
    break;

  case 180:

/* Line 1455 of yacc.c  */
#line 615 "../mu32/mut.y"
    { init_aktions_liste (); }
    break;

  case 181:

/* Line 1455 of yacc.c  */
#line 617 "../mu32/mut.y"
    { get_new_anweisung (); }
    break;

  case 182:

/* Line 1455 of yacc.c  */
#line 622 "../mu32/mut.y"
    { get_harmoniebezeichner (  (yyvsp[(1) - (5)].integer), (yyvsp[(3) - (5)].identifier),  (yyvsp[(5) - (5)].integer)); }
    break;

  case 183:

/* Line 1455 of yacc.c  */
#line 624 "../mu32/mut.y"
    { get_harmoniebezeichner (-1, (yyvsp[(1) - (3)].identifier),  (yyvsp[(3) - (3)].integer)); }
    break;

  case 184:

/* Line 1455 of yacc.c  */
#line 626 "../mu32/mut.y"
    { get_harmoniebezeichner (  (yyvsp[(1) - (3)].integer), (yyvsp[(3) - (3)].identifier), -1); }
    break;

  case 185:

/* Line 1455 of yacc.c  */
#line 628 "../mu32/mut.y"
    { get_harmoniebezeichner (-1, (yyvsp[(1) - (1)].identifier), -1); }
    break;

  case 186:

/* Line 1455 of yacc.c  */
#line 632 "../mu32/mut.y"
    { get_ausloeser_default (); }
    break;

  case 187:

/* Line 1455 of yacc.c  */
#line 633 "../mu32/mut.y"
    { get_ausloeser_harmonie (); }
    break;

  case 188:

/* Line 1455 of yacc.c  */
#line 634 "../mu32/mut.y"
    { get_ausloeser_harmonie_form (); }
    break;

  case 189:

/* Line 1455 of yacc.c  */
#line 635 "../mu32/mut.y"
    { get_ausloeser_taste ((yyvsp[(2) - (2)].identifier)); }
    break;

  case 190:

/* Line 1455 of yacc.c  */
#line 636 "../mu32/mut.y"
    { init_integersequenz (); }
    break;

  case 191:

/* Line 1455 of yacc.c  */
#line 638 "../mu32/mut.y"
    { get_ausloeser_midi_in (); }
    break;

  case 192:

/* Line 1455 of yacc.c  */
#line 643 "../mu32/mut.y"
    { get_new_integer_in_integersequenz ((yyvsp[(1) - (1)].integer));}
    break;

  case 193:

/* Line 1455 of yacc.c  */
#line 645 "../mu32/mut.y"
    { get_new_integer_in_integersequenz ((yyvsp[(3) - (3)].integer));}
    break;

  case 194:

/* Line 1455 of yacc.c  */
#line 646 "../mu32/mut.y"
    { fatal_error( 77, FEHLERZEILE ); }
    break;

  case 195:

/* Line 1455 of yacc.c  */
#line 651 "../mu32/mut.y"
    {}
    break;

  case 196:

/* Line 1455 of yacc.c  */
#line 655 "../mu32/mut.y"
    {}
    break;

  case 197:

/* Line 1455 of yacc.c  */
#line 656 "../mu32/mut.y"
    {}
    break;

  case 198:

/* Line 1455 of yacc.c  */
#line 661 "../mu32/mut.y"
    { get_instrument_dekl ((yyvsp[(1) - (4)].integer), (yyvsp[(4) - (4)].integer), (yyvsp[(4) - (4)].integer), 0, & list_of_instrumente); }
    break;

  case 199:

/* Line 1455 of yacc.c  */
#line 663 "../mu32/mut.y"
    { get_instrument_dekl ((yyvsp[(1) - (6)].integer), (yyvsp[(4) - (6)].integer), (yyvsp[(6) - (6)].integer), 0, & list_of_instrumente); }
    break;

  case 200:

/* Line 1455 of yacc.c  */
#line 665 "../mu32/mut.y"
    { get_instrument_dekl ((yyvsp[(1) - (6)].integer), 0, 0, (yyvsp[(5) - (6)].integer), & list_of_instrumente); }
    break;

  case 201:

/* Line 1455 of yacc.c  */
#line 667 "../mu32/mut.y"
    { get_instrument_dekl ((yyvsp[(1) - (7)].integer), (yyvsp[(4) - (7)].integer), (yyvsp[(4) - (7)].integer), (yyvsp[(6) - (7)].integer), & list_of_instrumente); }
    break;

  case 202:

/* Line 1455 of yacc.c  */
#line 669 "../mu32/mut.y"
    { get_instrument_dekl ((yyvsp[(1) - (9)].integer), (yyvsp[(4) - (9)].integer), (yyvsp[(6) - (9)].integer), (yyvsp[(8) - (9)].integer), & list_of_instrumente); }
    break;

  case 203:

/* Line 1455 of yacc.c  */
#line 673 "../mu32/mut.y"
    { (yyval.f_value) = (yyvsp[(1) - (1)].f_value) ; }
    break;

  case 204:

/* Line 1455 of yacc.c  */
#line 674 "../mu32/mut.y"
    { (yyval.f_value) = (double) (yyvsp[(1) - (1)].integer) ; }
    break;



/* Line 1455 of yacc.c  */
#line 3062 "y.tab.c"
      default: break;
    }
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
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }

  yyerror_range[0] = yylloc;

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

  yyerror_range[0] = yylsp[1-yylen];
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
      if (yyn != YYPACT_NINF)
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

      yyerror_range[0] = *yylsp;
      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp, yylsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  *++yyvsp = yylval;

  yyerror_range[1] = yylloc;
  /* Using YYLLOC is tempting, but would change the location of
     the lookahead.  YYLOC is available though.  */
  YYLLOC_DEFAULT (yyloc, (yyerror_range - 1), 2);
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

#if !defined(yyoverflow) || YYERROR_VERBOSE
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
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval, &yylloc);
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



/* Line 1675 of yacc.c  */
#line 678 "../mu32/mut.y"

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
            return F_NUMBER;
        }
        else {
            intern_ungetc (c, quelldatei);
            anzahl_eingelesene_zeichen --;
            
            if (zahl > INT_MAX) {
                yylval.f_value = zahl;
                return F_NUMBER;
            }
            else {
                yylval.integer = (int)zahl;
                return INTEGER;
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
        int help;
        if (fscanf (quelldatei, "%x", &help) == 0) {
            fatal_error (78, yylloc.first_line + 1);
            exit (1);
        }
        yylval.integer = help;

/* printf("f_number:%lf:\n", yylval.f_value); */

        return INTEGER;
    }
    
    /* Test auf reserved word oder einen Identifier */
    if (isalpha (c) || (c == '_') || (c == '\'') ) {

static struct { 
    const char *word;
    int token;
} reserved_words [] = {
/* German keywords : */
{ "INTERVALL"  , INTERVALL  },
{ "WURZEL"     , WURZEL     },
{ "TON"        , TON        },
{ "TONSYSTEM"  , TONSYSTEM  },
{ "UMSTIMMUNG" , UMSTIMMUNG },
{ "HARMONIE"   , HARMONIE   },
{ "LOGIK"      , LOGIK      },
{ "FORM"       , FORM       },
{ "MIDIKANAL"  , INSTRUMENT },
{ "TASTE"      , TASTE      },
{ "MIDIIN"     , MIDI_IN    },
{ "MIDIOUT"    , MIDI_OUT   },
{ "ANSONSTEN"  , ANSONSTEN  },
/* English keywords : */
{ "INTERVAL"   , INTERVALL  },
{ "ROOT"       , WURZEL     },
{ "TONE"       , TON        },
{ "TONESYSTEM" , TONSYSTEM  },
{ "RETUNING"   , UMSTIMMUNG },
{ "PATTERN"    , HARMONIE   },
{ "LOGIC"      , LOGIK      },
{ "SHIFTED"    , FORM       },
{ "MIDICHANNEL", INSTRUMENT },
{ "KEY"        , TASTE      },
{ "ELSE"       , ANSONSTEN  },
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
        return IDENTIFIER;
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


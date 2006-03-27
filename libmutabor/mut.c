/* A Bison parser, made by GNU Bison 1.875d.  */

/* Skeleton parser for Yacc-like parsing with Bison,
   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004 Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place - Suite 330,
   Boston, MA 02111-1307, USA.  */

/* As a special exception, when this file is copied by Bison into a
   Bison output file, you may use that output file without restriction.
   This special exception was added by the Free Software Foundation
   in version 1.24 of Bison.  */

/* Written by Richard Stallman by simplifying the original so called
   ``semantic'' parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 1

/* Using locations.  */
#define YYLSP_NEEDED 1

/* If NAME_PREFIX is specified substitute the variables and functions
   names.  */
#define yyparse mutabor_parser_parse
#define yylex   mutabor_parser_lex
#define yyerror mutabor_parser_error
#define yylval  mutabor_parser_lval
#define yychar  mutabor_parser_char
#define yydebug mutabor_parser_debug
#define yynerrs mutabor_parser_nerrs
#define yylloc mutabor_parser_lloc

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     IDENTIFIER = 258,
     F_NUMBER = 259,
     INTEGER = 260,
     UNREACHED = 261,
     INTERVALL = 262,
     INTERVALLOBJ = 263,
     WURZEL = 264,
     TON = 265,
     TONOBJ = 266,
     TONSYSTEM = 267,
     UMSTIMMUNG = 268,
     HARMONIE = 269,
     LOGIK = 270,
     FORM = 271,
     INSTRUMENT = 272,
     TASTE = 273,
     MIDI_IN = 274,
     MIDI_OUT = 275,
     ANSONSTEN = 276
   };
#endif
#define IDENTIFIER 258
#define F_NUMBER 259
#define INTEGER 260
#define UNREACHED 261
#define INTERVALL 262
#define INTERVALLOBJ 263
#define WURZEL 264
#define TON 265
#define TONOBJ 266
#define TONSYSTEM 267
#define UMSTIMMUNG 268
#define HARMONIE 269
#define LOGIK 270
#define FORM 271
#define INSTRUMENT 272
#define TASTE 273
#define MIDI_IN 274
#define MIDI_OUT 275
#define ANSONSTEN 276




/* Copy the first part of user declarations.  */
#line 36 "../../libmutabor/mut.y"


/* BEGIN MUT_TAB.C */

/* MUTABOR / Version 2.1 */

#ifdef __BORLANDC__
#pragma warn -cln
#pragma warn -aus
#pragma warn -sig
#pragma warn -par
#endif

#ifdef HAVE_CONFIG_H
#include "config.h"
  /* Relevante Variablen für diese Datei:
   * HAVE_MEMMOVE 
   * HAVE_POW
   * HAVE_LIMITS_H
   * const
   * size_t
   */
#endif

#include <ctype.h>
#  ifdef HAVE_LIMITS_H
#include <limits.h>
#endif
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

/* #include "mutabor/heap.h" */
#include "mutabor/bad_decl.h"
#include "mutabor/mut_tab.h"
#include "mutabor/intervalDiff.h"
#include "mutabor/intervalPlaceholder.h"
#include "mutabor/intervalStretch.h"
#include "mutabor/intervalInv.h"
#include "mutabor/tonsystem.h"
#include "mutabor/argument.h"
#include "mutabor/parameter.h"
#include "mutabor/umstimmung.h"
#include "mutabor/taste.h"
#include "mutabor/harmonie.h"
#include "mutabor/logik.h"
#include "mutabor/anweisung.h"
#include "mutabor/instrument.h"
#include "mutabor/parser.h"
#include "mutabor/errors.h"
#include "mutabor/mutfile.h"

  /*  
#undef yylloc
#undef yylval
#undef yylloc
#undef yylval
#define yylloc  mutabor_parser_lloc
#define yylval  mutabor_parser_lval
  */

#define YYLEX_PARAM self->scanner
#define FEHLERZEILE yylloc.first_line
  /*
#define MAX_IDENTIFIER_LEN 80


#define alloca xmalloc
#define YYMAXLIMIT (HEAP_PORTION_SYNTAX / sizeof(YYLTYPE) - 1)
                   / wegen fehlendem alloca in PUREC /

*/




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

#if ! defined (YYSTYPE) && ! defined (YYSTYPE_IS_DECLARED)
#line 113 "../../libmutabor/mut.y"
typedef union YYSTYPE {
	double      f_value;        /* for floating point numbers */
	int         integer;        /* for integers */
	char        *identifier;    /* for names */
	void        *object;        /* for data objects */
} YYSTYPE;
/* Line 191 of yacc.c.  */
#line 211 "../../libmutabor/mut.c"
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

#if ! defined (YYLTYPE) && ! defined (YYLTYPE_IS_DECLARED)
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
#line 121 "../../libmutabor/mut.y"

/* #include "mutlex.h" */
#define self ((MUT_CLASS(mutfile)*)_self)
void yyerror(YYLTYPE * locp, void * _self, char const *s);



/* Line 214 of yacc.c.  */
#line 241 "../../libmutabor/mut.c"

#if ! defined (yyoverflow) || YYERROR_VERBOSE

# ifndef YYFREE
#  define YYFREE free
# endif
# ifndef YYMALLOC
#  define YYMALLOC malloc
# endif

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   define YYSTACK_ALLOC alloca
#  endif
# else
#  if defined (alloca) || defined (_ALLOCA_H)
#   define YYSTACK_ALLOC alloca
#  else
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning. */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
# else
#  if defined (__STDC__) || defined (__cplusplus)
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   define YYSIZE_T size_t
#  endif
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
# endif
#endif /* ! defined (yyoverflow) || YYERROR_VERBOSE */


#if (! defined (yyoverflow) \
     && (! defined (__cplusplus) \
	 || (defined (YYLTYPE_IS_TRIVIAL) && YYLTYPE_IS_TRIVIAL \
             && defined (YYSTYPE_IS_TRIVIAL) && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  short int yyss;
  YYSTYPE yyvs;
    YYLTYPE yyls;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (short int) + sizeof (YYSTYPE) + sizeof (YYLTYPE))	\
      + 2 * YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined (__GNUC__) && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  register YYSIZE_T yyi;		\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (0)
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (0)

#endif

#if defined (__STDC__) || defined (__cplusplus)
   typedef signed char yysigned_char;
#else
   typedef short int yysigned_char;
#endif

/* YYFINAL -- State number of the termination state. */
#define YYFINAL  2
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   88

/* YYNTOKENS -- Number of terminals. */
#define YYNTOKENS  36
/* YYNNTS -- Number of nonterminals. */
#define YYNNTS  20
/* YYNRULES -- Number of rules. */
#define YYNRULES  47
/* YYNRULES -- Number of states. */
#define YYNSTATES  79

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   276

#define YYTRANSLATE(YYX) 						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const unsigned char yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      28,    29,    35,    24,    23,    25,     2,    26,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    27,     2,
      33,    22,    34,     2,    32,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    30,     2,    31,     2,     2,     2,     2,     2,     2,
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
      15,    16,    17,    18,    19,    20,    21
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const unsigned char yyprhs[] =
{
       0,     0,     3,     4,     7,    10,    13,    15,    18,    20,
      23,    27,    31,    35,    40,    44,    48,    51,    54,    56,
      58,    62,    68,    72,    76,    78,    80,    83,    85,    88,
      92,    96,   100,   102,   104,   106,   108,   111,   113,   116,
     118,   126,   128,   132,   134,   135,   137,   139
};

/* YYRHS -- A `-1'-separated list of the rules' RHS. */
static const yysigned_char yyrhs[] =
{
      37,     0,    -1,    -1,    37,    38,    -1,    37,    44,    -1,
      37,    49,    -1,     7,    -1,     7,    39,    -1,    40,    -1,
      39,    40,    -1,     3,    22,    41,    -1,    41,    24,    41,
      -1,    41,    25,    41,    -1,    55,    26,    55,    42,    -1,
      26,    55,    42,    -1,    42,    26,    55,    -1,    55,    42,
      -1,    25,    42,    -1,    42,    -1,    43,    -1,    28,    41,
      29,    -1,    28,    48,    23,    48,    29,    -1,    55,    27,
      55,    -1,    55,     9,    55,    -1,     3,    -1,    10,    -1,
      10,    45,    -1,    46,    -1,    45,    46,    -1,     3,    22,
      47,    -1,    48,    24,    41,    -1,    48,    25,    41,    -1,
      48,    -1,    55,    -1,     3,    -1,    12,    -1,    12,    50,
      -1,    51,    -1,    50,    51,    -1,    52,    -1,     3,    22,
       5,    30,    53,    31,    41,    -1,    54,    -1,    53,    23,
      54,    -1,     3,    -1,    -1,     1,    -1,     4,    -1,     5,
      -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const unsigned short int yyrline[] =
{
       0,   171,   171,   172,   173,   174,   183,   184,   187,   188,
     192,   218,   224,   230,   237,   244,   251,   257,   263,   271,
     272,   273,   282,   289,   295,   330,   331,   334,   335,   339,
     365,   377,   383,   391,   396,   543,   544,   547,   548,   552,
     556,   564,   564,   567,   568,   569,  1039,  1040
};
#endif

#if YYDEBUG || YYERROR_VERBOSE
/* YYTNME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals. */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "IDENTIFIER", "F_NUMBER", "INTEGER",
  "UNREACHED", "INTERVALL", "INTERVALLOBJ", "WURZEL", "TON", "TONOBJ",
  "TONSYSTEM", "UMSTIMMUNG", "HARMONIE", "LOGIK", "FORM", "INSTRUMENT",
  "TASTE", "MIDI_IN", "MIDI_OUT", "ANSONSTEN", "'='", "','", "'+'", "'-'",
  "'/'", "':'", "'('", "')'", "'['", "']'", "'@'", "'<'", "'>'", "'*'",
  "$accept", "start", "intervalldeklaration", "intervalldekl1",
  "intervalldekl2_1", "intervalsum", "intervalldekl2", "intervalldekl3",
  "tondeklaration", "tondekl1", "tondekl2_1", "tonsum", "tondekl3",
  "tonsystemdeklaration", "tonsystemdekl1", "tonsystemdekl2_1",
  "tonsystemdekl2", "tonliste", "ton_element", "GLEITKOMMA_ZAHL", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const unsigned short int yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,    61,    44,    43,    45,    47,    58,    40,    41,
      91,    93,    64,    60,    62,    42
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const unsigned char yyr1[] =
{
       0,    36,    37,    37,    37,    37,    38,    38,    39,    39,
      40,    41,    41,    41,    41,    41,    41,    41,    41,    42,
      42,    42,    43,    43,    43,    44,    44,    45,    45,    46,
      47,    47,    47,    48,    48,    49,    49,    50,    50,    51,
      52,    53,    53,    54,    54,    54,    55,    55
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const unsigned char yyr2[] =
{
       0,     2,     0,     2,     2,     2,     1,     2,     1,     2,
       3,     3,     3,     4,     3,     3,     2,     2,     1,     1,
       3,     5,     3,     3,     1,     1,     2,     1,     2,     3,
       3,     3,     1,     1,     1,     1,     2,     1,     2,     1,
       7,     1,     3,     1,     0,     1,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const unsigned char yydefact[] =
{
       2,     0,     1,     6,    25,    35,     3,     4,     5,     0,
       7,     8,     0,    26,    27,     0,    36,    37,    39,     0,
       9,     0,    28,     0,    38,    24,    46,    47,     0,     0,
       0,    10,    18,    19,     0,    34,    29,    32,    33,     0,
      17,     0,     0,    24,     0,     0,    33,     0,     0,     0,
       0,     0,     0,    16,     0,     0,     0,    14,    20,     0,
      11,    12,    15,    23,     0,    22,    30,    31,    45,    43,
       0,    41,     0,    13,     0,     0,    21,    42,    40
};

/* YYDEFGOTO[NTERM-NUM]. */
static const yysigned_char yydefgoto[] =
{
      -1,     1,     6,    10,    11,    31,    32,    33,     7,    13,
      14,    36,    37,     8,    16,    17,    18,    70,    71,    34
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -31
static const yysigned_char yypact[] =
{
     -31,    67,   -31,     0,     9,    13,   -31,   -31,   -31,    -1,
       0,   -31,    18,     9,   -31,    34,    13,   -31,   -31,    43,
     -31,    59,   -31,    29,   -31,   -31,   -31,   -31,    50,     2,
      47,     3,    32,   -31,    33,   -31,   -31,    56,   -31,    46,
     -31,    -7,    50,    60,    41,    61,    33,    43,    43,     2,
       2,     2,     2,   -31,    43,    43,    12,   -31,   -31,    59,
     -31,   -31,   -31,   -31,    50,   -31,     3,     3,   -31,   -31,
      26,   -31,    53,   -31,    12,    43,   -31,   -31,     3
};

/* YYPGOTO[NTERM-NUM].  */
static const yysigned_char yypgoto[] =
{
     -31,   -31,   -31,   -31,    75,   -30,   -23,   -31,   -31,   -31,
      73,   -31,   -26,   -31,   -31,    71,   -31,   -31,    14,   -20
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -45
static const yysigned_char yytable[] =
{
      44,    38,    50,     9,    45,    40,    26,    27,    41,    42,
      46,    53,    12,    68,    41,    69,    15,    60,    61,    57,
      52,    19,    41,    53,    66,    67,    41,    47,    48,    62,
      63,    64,    65,    72,    39,   -44,    25,    26,    27,    38,
      21,    73,    50,   -44,    41,    78,    25,    26,    27,    74,
      43,    26,    27,    25,    26,    27,    23,    75,    49,    51,
      52,    30,    35,    26,    27,    47,    48,     2,    28,    29,
      58,    30,    28,    29,     3,    30,    56,     4,    30,     5,
      54,    55,    76,   -34,    59,    20,    22,    24,    77
};

static const unsigned char yycheck[] =
{
      30,    21,     9,     3,    30,    28,     4,     5,    28,    29,
      30,    34,     3,     1,    34,     3,     3,    47,    48,    42,
      27,    22,    42,    46,    54,    55,    46,    24,    25,    49,
      50,    51,    52,    59,     5,    23,     3,     4,     5,    59,
      22,    64,     9,    31,    64,    75,     3,     4,     5,    23,
       3,     4,     5,     3,     4,     5,    22,    31,    26,    26,
      27,    28,     3,     4,     5,    24,    25,     0,    25,    26,
      29,    28,    25,    26,     7,    28,    30,    10,    28,    12,
      24,    25,    29,    23,    23,    10,    13,    16,    74
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const unsigned char yystos[] =
{
       0,    37,     0,     7,    10,    12,    38,    44,    49,     3,
      39,    40,     3,    45,    46,     3,    50,    51,    52,    22,
      40,    22,    46,    22,    51,     3,     4,     5,    25,    26,
      28,    41,    42,    43,    55,     3,    47,    48,    55,     5,
      42,    55,    55,     3,    41,    48,    55,    24,    25,    26,
       9,    26,    27,    42,    24,    25,    30,    42,    29,    23,
      41,    41,    55,    55,    55,    55,    41,    41,     1,     3,
      53,    54,    48,    42,    23,    31,    29,    54,    41
};

#if ! defined (YYSIZE_T) && defined (__SIZE_TYPE__)
# define YYSIZE_T __SIZE_TYPE__
#endif
#if ! defined (YYSIZE_T) && defined (size_t)
# define YYSIZE_T size_t
#endif
#if ! defined (YYSIZE_T)
# if defined (__STDC__) || defined (__cplusplus)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# endif
#endif
#if ! defined (YYSIZE_T)
# define YYSIZE_T unsigned int
#endif

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
      YYPOPSTACK;						\
      goto yybackup;						\
    }								\
  else								\
    { 								\
      yyerror (&yylloc, _self, "syntax error: cannot back up");\
      YYERROR;							\
    }								\
while (0)

#define YYTERROR	1
#define YYERRCODE	256

/* YYLLOC_DEFAULT -- Compute the default location (before the actions
   are run).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)		\
   ((Current).first_line   = (Rhs)[1].first_line,	\
    (Current).first_column = (Rhs)[1].first_column,	\
    (Current).last_line    = (Rhs)[N].last_line,	\
    (Current).last_column  = (Rhs)[N].last_column)
#endif

/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (&yylval, &yylloc, YYLEX_PARAM)
#else
# define YYLEX yylex (&yylval, &yylloc)
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
} while (0)

# define YYDSYMPRINT(Args)			\
do {						\
  if (yydebug)					\
    yysymprint Args;				\
} while (0)

# define YYDSYMPRINTF(Title, Token, Value, Location)		\
do {								\
  if (yydebug)							\
    {								\
      YYFPRINTF (stderr, "%s ", Title);				\
      yysymprint (stderr, 					\
                  Token, Value, Location);	\
      YYFPRINTF (stderr, "\n");					\
    }								\
} while (0)

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yy_stack_print (short int *bottom, short int *top)
#else
static void
yy_stack_print (bottom, top)
    short int *bottom;
    short int *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (/* Nothing. */; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yy_reduce_print (int yyrule)
#else
static void
yy_reduce_print (yyrule)
    int yyrule;
#endif
{
  int yyi;
  unsigned int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %u), ",
             yyrule - 1, yylno);
  /* Print the symbols being reduced, and their result.  */
  for (yyi = yyprhs[yyrule]; 0 <= yyrhs[yyi]; yyi++)
    YYFPRINTF (stderr, "%s ", yytname [yyrhs[yyi]]);
  YYFPRINTF (stderr, "-> %s\n", yytname [yyr1[yyrule]]);
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (Rule);		\
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YYDSYMPRINT(Args)
# define YYDSYMPRINTF(Title, Token, Value, Location)
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
   SIZE_MAX < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#if defined (YYMAXDEPTH) && YYMAXDEPTH == 0
# undef YYMAXDEPTH
#endif

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined (__GLIBC__) && defined (_STRING_H)
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
#   if defined (__STDC__) || defined (__cplusplus)
yystrlen (const char *yystr)
#   else
yystrlen (yystr)
     const char *yystr;
#   endif
{
  register const char *yys = yystr;

  while (*yys++ != '\0')
    continue;

  return yys - yystr - 1;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined (__GLIBC__) && defined (_STRING_H) && defined (_GNU_SOURCE)
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
#   if defined (__STDC__) || defined (__cplusplus)
yystpcpy (char *yydest, const char *yysrc)
#   else
yystpcpy (yydest, yysrc)
     char *yydest;
     const char *yysrc;
#   endif
{
  register char *yyd = yydest;
  register const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

#endif /* !YYERROR_VERBOSE */



#if YYDEBUG
/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yysymprint (FILE *yyoutput, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
#else
static void
yysymprint (yyoutput, yytype, yyvaluep, yylocationp)
    FILE *yyoutput;
    int yytype;
    YYSTYPE *yyvaluep;
    YYLTYPE *yylocationp;
#endif
{
  /* Pacify ``unused variable'' warnings.  */
  (void) yyvaluep;
  (void) yylocationp;

  if (yytype < YYNTOKENS)
    {
      YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
# ifdef YYPRINT
      YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
    }
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  switch (yytype)
    {
      default:
        break;
    }
  YYFPRINTF (yyoutput, ")");
}

#endif /* ! YYDEBUG */
/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yydestruct (int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
#else
static void
yydestruct (yytype, yyvaluep, yylocationp)
    int yytype;
    YYSTYPE *yyvaluep;
    YYLTYPE *yylocationp;
#endif
{
  /* Pacify ``unused variable'' warnings.  */
  (void) yyvaluep;
  (void) yylocationp;

  switch (yytype)
    {
      case 3: /* IDENTIFIER */
#line 153 "../../libmutabor/mut.y"
        { free(yyvaluep->identifier); };
#line 896 "../../libmutabor/mut.c"
        break;

      default:
        break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */

#ifdef YYPARSE_PARAM
# if defined (__STDC__) || defined (__cplusplus)
int yyparse (void *YYPARSE_PARAM);
# else
int yyparse ();
# endif
#else /* ! YYPARSE_PARAM */
#if defined (__STDC__) || defined (__cplusplus)
int yyparse (void * _self);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */






/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
# if defined (__STDC__) || defined (__cplusplus)
int yyparse (void *YYPARSE_PARAM)
# else
int yyparse (YYPARSE_PARAM)
  void *YYPARSE_PARAM;
# endif
#else /* ! YYPARSE_PARAM */
#if defined (__STDC__) || defined (__cplusplus)
int
yyparse (void * _self)
#else
int
yyparse (_self)
    void * _self;
#endif
#endif
{
  /* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;
/* Location data for the lookahead symbol.  */
YYLTYPE yylloc;

  register int yystate;
  register int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  short int yyssa[YYINITDEPTH];
  short int *yyss = yyssa;
  register short int *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  register YYSTYPE *yyvsp;

  /* The location stack.  */
  YYLTYPE yylsa[YYINITDEPTH];
  YYLTYPE *yyls = yylsa;
  YYLTYPE *yylsp;
  YYLTYPE *yylerrsp;

#define YYPOPSTACK   (yyvsp--, yyssp--, yylsp--)

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

  /* When reducing, the number of symbols on the RHS of the reduced
     rule.  */
  int yylen;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss;
  yyvsp = yyvs;
  yylsp = yyls;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed. so pushing a state here evens the stacks.
     */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack. Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	short int *yyss1 = yyss;
	YYLTYPE *yyls1 = yyls;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow ("parser stack overflow",
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
      goto yyoverflowlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyoverflowlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	short int *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyoverflowlab;
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);
	YYSTACK_RELOCATE (yyls);
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

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

/* Do appropriate processing given the current state.  */
/* Read a lookahead token if we need one and don't already have one.  */
/* yyresume: */

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
      YYDSYMPRINTF ("Next token is", yytoken, &yylval, &yylloc);
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

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Shift the lookahead token.  */
  YYDPRINTF ((stderr, "Shifting token %s, ", yytname[yytoken]));

  /* Discard the token being shifted unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  *++yyvsp = yylval;
  *++yylsp = yylloc;

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  yystate = yyn;
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

  /* Default location. */
  YYLLOC_DEFAULT (yyloc, yylsp - yylen, yylen);
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 171 "../../libmutabor/mut.y"
    { yylloc.last_line=1; yylloc.last_column=0; }
    break;

  case 10:
#line 192 "../../libmutabor/mut.y"
    {		   
		   if (yyvsp[0].object) { 
			   char * c;
			   if ((c=MUTABOR_CLASS_FUNCTION(identifier,get_name)(yyvsp[0].object))) {
			     if (strcmp(c,yyvsp[-2].identifier)) {
			       MUT_CLASS(intervalPlaceholder)* alias;
			       alias=MUT_NEW(intervalPlaceholder);
			       MUTABOR_CLASS_FUNCTION(mutfile,insert_interval)(_self,alias);
			       MUTABOR_CLASS_FUNCTION(intervalPlaceholder,setreplacement)
				                                               (alias,yyvsp[0].object);
			       MUTABOR_CLASS_FUNCTION(identifier,set_name)(alias,yyvsp[-2].identifier);
			       MUTABOR_CLASS_FUNCTION(idlist,sortbyname)(self->intervals,1);
			     }  else {
				     if (c!=yyvsp[-2].identifier) free(yyvsp[-2].identifier);
			     }
			   } else { 
				   if (MUTABOR_CLASS_FUNCTION(mutfile,check_interval)
				       (_self,yyvsp[0].object,yyvsp[-2].identifier)) {
					   fatal_error(MUTABOR_ERROR_DOUBLE_INTERVAL,yyvsp[-2].identifier);
					   free(yyvsp[-2].identifier);
				   }
			   }
		   } else free(yyvsp[-2].identifier);
	   }
    break;

  case 11:
#line 218 "../../libmutabor/mut.y"
    {
		    yyval.object=MUT_NEW(intervalSum);
		    MUTABOR_CLASS_FUNCTION(mutfile,insert_interval)(_self,yyval.object);
		    MUTABOR_CLASS_FUNCTION(intervalSum,setleft)(yyval.object,yyvsp[-2].object);
		    MUTABOR_CLASS_FUNCTION(intervalSum,setright)(yyval.object,yyvsp[0].object);
           }
    break;

  case 12:
#line 224 "../../libmutabor/mut.y"
    {
		    yyval.object=MUT_NEW(intervalDiff);
		    MUTABOR_CLASS_FUNCTION(mutfile,insert_interval)(_self,yyval.object);
		    MUTABOR_CLASS_FUNCTION(intervalDiff,setleft)(yyval.object,yyvsp[-2].object);
		    MUTABOR_CLASS_FUNCTION(intervalDiff,setright)(yyval.object,yyvsp[0].object);
           }
    break;

  case 13:
#line 230 "../../libmutabor/mut.y"
    {
		   yyval.object=MUT_NEW(intervalStretch);
		   MUTABOR_CLASS_FUNCTION(mutfile,insert_interval)(_self,yyval.object);
		   MUTABOR_CLASS_FUNCTION(intervalStretch,setstretch)
			   (yyval.object,MUTABOR_FLOAT_DIVIDE(yyvsp[-3].f_value,yyvsp[-1].f_value));
		   MUTABOR_CLASS_FUNCTION(intervalStretch,setright)(yyval.object,yyvsp[0].object);
	   }
    break;

  case 14:
#line 237 "../../libmutabor/mut.y"
    {
		   yyval.object=MUT_NEW(intervalStretch);
		   MUTABOR_CLASS_FUNCTION(mutfile,insert_interval)(_self,yyval.object);
		   MUTABOR_CLASS_FUNCTION(intervalStretch,setstretch)
			   (yyval.object,MUTABOR_FLOAT_DIVIDE(1,yyvsp[-1].f_value));
		   MUTABOR_CLASS_FUNCTION(intervalStretch,setright)(yyval.object,yyvsp[0].object);
	   }
    break;

  case 15:
#line 244 "../../libmutabor/mut.y"
    {
		   yyval.object=MUT_NEW(intervalStretch);
		   MUTABOR_CLASS_FUNCTION(mutfile,insert_interval)(_self,yyval.object);
		   MUTABOR_CLASS_FUNCTION(intervalStretch,setstretch)
			   (yyval.object,MUTABOR_FLOAT_DIVIDE(1,yyvsp[0].f_value));
		   MUTABOR_CLASS_FUNCTION(intervalStretch,setright)(yyval.object,yyvsp[-2].object);
	   }
    break;

  case 16:
#line 251 "../../libmutabor/mut.y"
    {
		   yyval.object=MUT_NEW(intervalStretch);
		   MUTABOR_CLASS_FUNCTION(mutfile,insert_interval)(_self,yyval.object);
		   MUTABOR_CLASS_FUNCTION(intervalStretch,setstretch)(yyval.object,yyvsp[-1].f_value);
		   MUTABOR_CLASS_FUNCTION(intervalStretch,setright)(yyval.object,yyvsp[0].object);
	   }
    break;

  case 17:
#line 257 "../../libmutabor/mut.y"
    {
		   yyval.object=MUT_NEW(intervalInv);
		   MUTABOR_CLASS_FUNCTION(mutfile,insert_interval)(_self,yyval.object);
		   MUTABOR_CLASS_FUNCTION(intervalInv,setright)
			   (yyval.object,yyvsp[0].object);
	   }
    break;

  case 20:
#line 272 "../../libmutabor/mut.y"
    { yyval.object=yyvsp[-1].object; }
    break;

  case 21:
#line 273 "../../libmutabor/mut.y"
    {
		    yyval.object=MUT_NEW(intervalDiff);
		    MUTABOR_CLASS_FUNCTION(mutfile,insert_interval)(_self,yyval.object);
		    MUTABOR_CLASS_FUNCTION(intervalSum,setleft)(yyval.object,yyvsp[-3].object);
		    MUTABOR_CLASS_FUNCTION(intervalSum,setright)(yyval.object,yyvsp[-1].object);
           }
    break;

  case 22:
#line 282 "../../libmutabor/mut.y"
    {	    
			    yyval.object=MUT_NEW(interval);
			    MUTABOR_CLASS_FUNCTION(mutfile,insert_interval)(_self,yyval.object);
			    MUTABOR_CLASS_FUNCTION(interval,set_factor)
				    (yyval.object,MUTABOR_FLOAT_DIVIDE(yyvsp[-2].f_value,yyvsp[0].f_value));
		    }
    break;

  case 23:
#line 289 "../../libmutabor/mut.y"
    {
			    yyval.object=MUT_NEW(interval);
			    MUTABOR_CLASS_FUNCTION(mutfile,insert_interval)(_self,yyval.object);
			    MUTABOR_CLASS_FUNCTION(interval,set_factor)
				    (yyval.object,MUTABOR_FLOAT_POW(yyvsp[0].f_value,MUTABOR_FLOAT_DIVIDE(1,yyvsp[-2].f_value)));
	            }
    break;

  case 24:
#line 295 "../../libmutabor/mut.y"
    {
		   yyval.object=MUTABOR_CLASS_FUNCTION(mutfile,get_interval)(_self,yyvsp[0].identifier);
		   free(yyvsp[0].identifier);
	   }
    break;

  case 29:
#line 339 "../../libmutabor/mut.y"
    {		   
		   if (yyvsp[0].object) { 
			   char * c;
			   if ((c=MUTABOR_CLASS_FUNCTION(identifier,get_name)(yyvsp[0].object))) {
			     if (strcmp(c,yyvsp[-2].identifier)) {
			       MUT_CLASS(intervalPlaceholder)* alias;
			       alias=MUT_NEW(intervalPlaceholder);
			       MUTABOR_CLASS_FUNCTION(mutfile,insert_interval)(_self,alias);
			       MUTABOR_CLASS_FUNCTION(intervalPlaceholder,setreplacement)
				                                               (alias,yyvsp[0].object);
			       MUTABOR_CLASS_FUNCTION(identifier,set_name)(alias,yyvsp[-2].identifier);
			       MUTABOR_CLASS_FUNCTION(idlist,sortbyname)(self->intervals,1);
			     }  else {
					if (c!=yyvsp[-2].identifier) free(yyvsp[-2].identifier);
			     }
			   } else { 
				   if (MUTABOR_CLASS_FUNCTION(mutfile,check_interval)
				       (_self,yyvsp[0].object,yyvsp[-2].identifier)) {
					   fatal_error(MUTABOR_ERROR_DOUBLE_INTERVAL,yyvsp[-2].identifier);
					   free(yyvsp[-2].identifier);
				   }
			   }
		   } else free(yyvsp[-2].identifier);
	   }
    break;

  case 30:
#line 365 "../../libmutabor/mut.y"
    {
		    yyval.object=MUT_NEW(intervalSum);
		    MUTABOR_CLASS_FUNCTION(mutfile,insert_interval)(_self,yyval.object);
		    MUTABOR_CLASS_FUNCTION(intervalSum,setleft)(yyval.object,yyvsp[-2].object);
		    MUTABOR_CLASS_FUNCTION(intervalSum,setright)(yyval.object,yyvsp[0].object);
           }
    break;

  case 31:
#line 377 "../../libmutabor/mut.y"
    {
		    yyval.object=MUT_NEW(intervalDiff);
		    MUTABOR_CLASS_FUNCTION(mutfile,insert_interval)(_self,yyval.object);
		    MUTABOR_CLASS_FUNCTION(intervalSum,setleft)(yyval.object,yyvsp[-2].object);
		    MUTABOR_CLASS_FUNCTION(intervalSum,setright)(yyval.object,yyvsp[0].object);
           }
    break;

  case 32:
#line 383 "../../libmutabor/mut.y"
    { yyval.object=yyvsp[0].object; }
    break;

  case 33:
#line 391 "../../libmutabor/mut.y"
    {
			    yyval.object=MUT_NEW(interval);
			    MUTABOR_CLASS_FUNCTION(mutfile,insert_interval)(_self,yyval.object);
			    MUTABOR_CLASS_FUNCTION(interval,set_factor)(yyval.object,yyvsp[0].f_value);
           }
    break;

  case 34:
#line 396 "../../libmutabor/mut.y"
    {
	           printf("tondekl3");
		   yyval.object=MUTABOR_CLASS_FUNCTION(mutfile,get_interval)(_self,yyvsp[0].identifier);
		   free(yyvsp[0].identifier);
	   }
    break;

  case 45:
#line 569 "../../libmutabor/mut.y"
    { fatal_error(73,FEHLERZEILE); }
    break;

  case 46:
#line 1039 "../../libmutabor/mut.y"
    { yyval.f_value = yyvsp[0].f_value; }
    break;

  case 47:
#line 1040 "../../libmutabor/mut.y"
    { yyval.f_value = (double) yyvsp[0].integer; }
    break;


    }

/* Line 1010 of yacc.c.  */
#line 1445 "../../libmutabor/mut.c"

  yyvsp -= yylen;
  yyssp -= yylen;
  yylsp -= yylen;

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
#if YYERROR_VERBOSE
      yyn = yypact[yystate];

      if (YYPACT_NINF < yyn && yyn < YYLAST)
	{
	  YYSIZE_T yysize = 0;
	  int yytype = YYTRANSLATE (yychar);
	  const char* yyprefix;
	  char *yymsg;
	  int yyx;

	  /* Start YYX at -YYN if negative to avoid negative indexes in
	     YYCHECK.  */
	  int yyxbegin = yyn < 0 ? -yyn : 0;

	  /* Stay within bounds of both yycheck and yytname.  */
	  int yychecklim = YYLAST - yyn;
	  int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
	  int yycount = 0;

	  yyprefix = ", expecting ";
	  for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	    if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	      {
		yysize += yystrlen (yyprefix) + yystrlen (yytname [yyx]);
		yycount += 1;
		if (yycount == 5)
		  {
		    yysize = 0;
		    break;
		  }
	      }
	  yysize += (sizeof ("syntax error, unexpected ")
		     + yystrlen (yytname[yytype]));
	  yymsg = (char *) YYSTACK_ALLOC (yysize);
	  if (yymsg != 0)
	    {
	      char *yyp = yystpcpy (yymsg, "syntax error, unexpected ");
	      yyp = yystpcpy (yyp, yytname[yytype]);

	      if (yycount < 5)
		{
		  yyprefix = ", expecting ";
		  for (yyx = yyxbegin; yyx < yyxend; ++yyx)
		    if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
		      {
			yyp = yystpcpy (yyp, yyprefix);
			yyp = yystpcpy (yyp, yytname[yyx]);
			yyprefix = " or ";
		      }
		}
	      yyerror (&yylloc, _self, yymsg);
	      YYSTACK_FREE (yymsg);
	    }
	  else
	    yyerror (&yylloc, _self, "syntax error; also virtual memory exhausted");
	}
      else
#endif /* YYERROR_VERBOSE */
	yyerror (&yylloc, _self, "syntax error");
    }

  yylerrsp = yylsp;

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* If at end of input, pop the error token,
	     then the rest of the stack, then return failure.  */
	  if (yychar == YYEOF)
	     for (;;)
	       {
		 YYPOPSTACK;
		 if (yyssp == yyss)
		   YYABORT;
		 YYDSYMPRINTF ("Error: popping", yystos[*yyssp], yyvsp, yylsp);
		 yydestruct (yystos[*yyssp], yyvsp, yylsp);
	       }
        }
      else
	{
	  YYDSYMPRINTF ("Error: discarding", yytoken, &yylval, &yylloc);
	  yydestruct (yytoken, &yylval, &yylloc);
	  yychar = YYEMPTY;
	  *++yylerrsp = yylloc;
	}
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

#ifdef __GNUC__
  /* Pacify GCC when the user code never invokes YYERROR and the label
     yyerrorlab therefore never appears in user code.  */
  if (0)
     goto yyerrorlab;
#endif

  yyvsp -= yylen;
  yyssp -= yylen;
  yystate = *yyssp;
  yylerrsp = yylsp;
  *++yylerrsp = yyloc;
  yylsp -= yylen;
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

      YYDSYMPRINTF ("Error: popping", yystos[*yyssp], yyvsp, yylsp);
      yydestruct (yystos[yystate], yyvsp, yylsp);
      YYPOPSTACK;
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  YYDPRINTF ((stderr, "Shifting error token, "));

  *++yyvsp = yylval;
  YYLLOC_DEFAULT (yyloc, yylsp, yylerrsp - yylsp);
  *++yylsp = yyloc;

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

#ifndef yyoverflow
/*----------------------------------------------.
| yyoverflowlab -- parser overflow comes here.  |
`----------------------------------------------*/
yyoverflowlab:
  yyerror (&yylloc, _self, "parser stack overflow");
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  return yyresult;
}


#line 1043 "../../libmutabor/mut.y"
        
void yyerror(YYLTYPE * locp, void * _self, char const *s) {
  fprintf(stderr,"\n%s at line %d col %d\n",s,locp->first_line,locp->first_column);
  /*
  return 1;
  */
/* ignore it ! */
  
} /* yyerror */

/* END MUT_TAB.C */


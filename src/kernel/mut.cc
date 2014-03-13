/* A Bison parser, made by GNU Bison 3.0.2.  */

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
#define YYBISON_VERSION "3.0.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 1

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 38 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:339  */


/* BEGIN MUT_TAB.C */

/* MUTABOR / Version 2.1 */

//#pragma warn -cln
//#pragma warn -aus
//#pragma warn -sig
//#pragma warn -par


#include <ctype.h>
#include <limits.h>
#include <errno.h>
#include <stdio.h>
#include "src/kernel/box.h"
#include "src/kernel/Global.h"
#include "src/kernel/Parser.h"
#include "src/kernel/Hilfs.h"
#include "src/kernel/Execute.h"
#ifdef SRC_WXINTL_LIBINTL
#define dgettext(domain,string) wxwidgets_sgettext(string)
#endif

#ifdef _
#undef _
#endif
#define _ _mut

#ifdef DEBUG
#define YYDEBUG 1
#endif

#ifdef __cplusplus
	namespace mutabor {
		namespace hidden {
			extern "C" {
#endif

#define MAX_IDENTIFIER_LEN 80

#define FEHLERZEILE yylloc.first_line

#ifdef alloca
#undef alloca
#define alloca make_an_error ---
#endif
#define YYERROR_VERBOSE 1
#define YYMALLOC(size) xmalloc(box,size)
#define YYFREE(X) do { /* empty */; } while (0)
#define YYMAXLIMIT (HEAP_PORTION_SYNTAX / sizeof(YYLTYPE) - 1)
                   /* wegen fehlendem alloca in PUREC */

#line 121 "src/kernel/mut.cc" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
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
#ifndef YY_YY_SRC_KERNEL_MUT_HH_INCLUDED
# define YY_YY_SRC_KERNEL_MUT_HH_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
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

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE YYSTYPE;
union YYSTYPE
{
#line 93 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:355  */

			double      f_value;        /* floating point numbers */
			int         integer;        /* integers */
			char        *identifier;    /* names/identifiers */
			struct argument_list * arguments;  /* argument list */
			struct parameter_list * parameters; /* parameter list */

#line 229 "src/kernel/mut.cc" /* yacc.c:355  */
};
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif



int yyparse (mutabor_box_type * box);

#endif /* !YY_YY_SRC_KERNEL_MUT_HH_INCLUDED  */

/* Copy the second part of user declarations.  */
#line 156 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:358  */

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

#line 271 "src/kernel/mut.cc" /* yacc.c:358  */

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
#else
typedef signed char yytype_int8;
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
# elif ! defined YYSIZE_T
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

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
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
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

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
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  29
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   324

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  49
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  102
/* YYNRULES -- Number of rules.  */
#define YYNRULES  209
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  348

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   285

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
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
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   174,   174,   175,   176,   185,   186,   190,   191,   195,
     196,   199,   200,   202,   203,   206,   207,   208,   209,   210,
     211,   212,   217,   219,   221,   225,   235,   244,   247,   254,
     267,   269,   271,   275,   278,   283,   290,   295,   305,   309,
     311,   314,   317,   320,   323,   326,   336,   346,   356,   381,
     390,   394,   405,   436,   438,   440,   444,   449,   448,   453,
     452,   458,   458,   461,   462,   463,   471,   472,   478,   479,
     490,   493,   500,   520,   521,   527,   530,   546,   548,   550,
     552,   554,   560,   564,   566,   570,   570,   581,   580,   591,
     590,   604,   604,   618,   619,   620,   621,   622,   623,   624,
     625,   626,   627,   628,   638,   643,   648,   653,   659,   658,
     668,   669,   671,   671,   678,   679,   684,   688,   692,   693,
     695,   695,   698,   698,   701,   701,   704,   704,   711,   711,
     714,   714,   720,   720,   723,   723,   729,   729,   735,   736,
     740,   743,   745,   754,   753,   757,   761,   761,   767,   768,
     773,   772,   777,   776,   781,   780,   788,   787,   795,   799,
     800,   805,   804,   809,   817,   825,   829,   830,   834,   835,
     839,   840,   844,   848,   849,   849,   857,   856,   863,   866,
     862,   873,   874,   879,   879,   883,   883,   889,   893,   897,
     901,   908,   909,   910,   911,   912,   912,   918,   920,   922,
     932,   936,   937,   941,   943,   945,   947,   949,   954,   955
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
  "intervalldeklaration", "intervalldekl1", "intervalldekl2",
  "tondeklaration", "tondekl1", "tondekl2", "KOMPLEX_TON_LIST",
  "KOMPLEX_TON_LIST_2", "KOMPLEX_TON_1", "KOMPLEX_TON_START",
  "tonsystemdeklaration", "tonsystemdekl1", "tonsystemdekl2_1",
  "tonsystemdekl2", "$@1", "$@2", "tonliste", "ton_element",
  "parameter_list", "nonempty_parameter_list", "parameter",
  "argument_list", "nonempty_argument_list", "argument_list_element",
  "umstimmungdeklaration", "retuning_definitions", "retuning_definition",
  "$@3", "$@4", "$@5", "$@6", "retuning_term",
  "umstimmungs_dekl_taste_abs", "umstimmungs_dekl_taste_rel",
  "umstimmungs_dekl_breite_abs", "umstimmungs_dekl_breite_rel",
  "umstimmungs_dekl_tonhoehe_veraendert", "$@7",
  "nonempty_umstimm_expression_list", "$@8", "umstimm_expression_list",
  "umstimm_expression", "nonempty_umstimm_expression", "$@9", "$@10",
  "$@11", "$@12", "umstimmungs_dekl_wiederholung_abs", "$@13", "$@14",
  "umstimmungs_dekl_wiederholung_rel", "$@15", "$@16",
  "umstimmungs_dekl_umstimmungs_bund", "$@17", "aktions_liste", "aktion",
  "$@18", "umstimmungs_dekl_umstimmungs_case", "$@19",
  "umstimmungs_case_liste", "umstimmungs_case_element", "$@20", "$@21",
  "$@22", "umstimmungs_dekl_midi_out", "$@23", "harmoniedeklaration",
  "harmonie_dekl_1", "harmonie_dekl_2", "$@24", "bezugs_taste",
  "tasten_liste", "taste", "logikdeklaration", "logik_dekl_1", "$@25",
  "logik_dekl_2", "$@26", "$@27", "$@28", "anweisungs_liste", "anweisung",
  "$@29", "$@30", "harmoniebezeichner", "ausloeser", "$@31",
  "integersequenz", "instrumentdeklaration", "instrument_dekl_1",
  "instrument_dekl_2", "GLEITKOMMA_ZAHL", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,    43,    45,    42,    47,    60,    62,    61,    58,    91,
      93,    44,    40,    41,    64,   123,   125,    46,   126
};
# endif

#define YYPACT_NINF -189

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-189)))

#define YYTABLE_NINF -175

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     203,   210,  -189,  -189,  -189,    47,  -189,  -189,  -189,    77,
     210,  -189,  -189,  -189,  -189,  -189,  -189,  -189,  -189,   210,
     103,   119,   132,    22,  -189,    47,   184,   135,    75,  -189,
    -189,    35,  -189,   -11,  -189,   133,   230,  -189,   152,  -189,
     141,  -189,  -189,   199,  -189,   234,   206,  -189,  -189,   114,
     168,  -189,   201,  -189,     8,  -189,  -189,  -189,    13,  -189,
     204,     9,   162,  -189,   205,  -189,  -189,  -189,  -189,   197,
    -189,  -189,    82,  -189,   175,  -189,    26,     8,  -189,  -189,
    -189,   207,  -189,  -189,   237,    61,   192,  -189,    55,  -189,
    -189,  -189,  -189,  -189,  -189,  -189,  -189,  -189,  -189,  -189,
     209,   211,   141,  -189,    74,   191,   195,   241,    32,   208,
    -189,  -189,   214,     7,   244,   194,  -189,   197,   197,   197,
     122,   122,  -189,  -189,   187,  -189,  -189,  -189,  -189,   217,
     -16,    16,    21,  -189,  -189,   118,   163,   213,  -189,  -189,
    -189,  -189,   212,    50,   249,   252,  -189,  -189,  -189,   218,
       2,   251,  -189,   125,   128,  -189,  -189,   256,  -189,  -189,
      15,  -189,   228,    26,   144,  -189,   198,   122,   229,   166,
     226,   200,  -189,   202,   223,   224,   225,   227,   231,  -189,
      57,  -189,  -189,   104,     8,     8,  -189,  -189,   261,    93,
    -189,  -189,   219,   144,  -189,   163,   263,   265,   232,  -189,
     197,    40,  -189,   197,    58,  -189,   122,   239,  -189,  -189,
    -189,    71,  -189,  -189,  -189,   122,  -189,  -189,  -189,  -189,
     118,   238,   235,  -189,  -189,    19,  -189,  -189,  -189,    19,
     236,   118,  -189,   163,  -189,   245,   246,   274,    12,  -189,
    -189,  -189,  -189,    50,   233,   276,   136,  -189,   243,   247,
     248,  -189,   280,  -189,   197,   281,  -189,   197,  -189,   122,
     282,  -189,   122,   122,  -189,   226,  -189,  -189,   122,   122,
     250,  -189,  -189,   122,   122,   250,  -189,    14,  -189,   253,
     144,  -189,   254,   257,   260,  -189,  -189,  -189,   284,  -189,
    -189,  -189,    68,  -189,   290,  -189,  -189,   293,  -189,   294,
    -189,  -189,  -189,  -189,   258,  -189,  -189,    19,  -189,  -189,
     242,  -189,   118,   145,  -189,  -189,   264,  -189,  -189,  -189,
     267,  -189,   262,  -189,  -189,  -189,  -189,  -189,  -189,  -189,
     163,   163,  -189,   268,    73,  -189,   266,   266,   163,   269,
    -189,   266,  -189,   163,   163,  -189,    96,  -189
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,    23,    31,    54,    83,   159,   173,   201,     0,
       3,    13,    15,    16,    17,    18,    19,    20,    21,     4,
      22,    30,    53,     0,    82,    83,     0,   172,   200,     1,
      14,     0,    24,     0,    32,     0,     0,    55,     0,    85,
      66,    84,   165,     0,   160,     0,     0,   202,    29,     0,
       0,    56,     0,    91,     0,    70,    72,    71,     0,    67,
      68,     0,     0,   175,     0,    28,    49,   208,   209,     0,
      27,    39,     0,    37,    35,    33,     0,     0,   103,    77,
      78,     0,    81,    80,     0,   108,     0,   136,     0,    86,
      93,    94,    95,    96,    97,    98,    99,   100,   101,   102,
       0,     0,     0,   164,     0,   190,     0,     0,     0,     0,
     191,   192,     0,     0,     0,    38,    50,     0,     0,     0,
       0,     0,    65,    63,     0,    61,    92,   156,    79,     0,
     128,     0,     0,     5,     6,     0,     0,     0,   146,    89,
      87,    69,     0,     0,     0,     0,   194,   193,   195,   178,
     203,     0,    51,     0,     0,    40,    26,     0,    25,    36,
       0,    34,    57,     0,     0,    11,     0,     0,     0,     0,
       0,   118,   112,   119,     0,   110,     0,   140,     0,   145,
       0,   138,   104,     0,     0,     0,   163,   170,     0,     0,
     168,   188,   189,     0,   176,     0,     0,     0,     0,    41,
       0,     0,    42,     0,     0,    52,     0,     0,    62,   199,
     197,     0,   132,   134,   129,     0,     7,     8,     9,    10,
       0,     0,     0,   120,   124,   116,   122,   126,   109,   116,
       0,    73,   143,     0,   137,     0,     0,     0,     0,   148,
      90,    88,   171,     0,   166,     0,     0,   181,     0,   204,
       0,   205,     0,    43,     0,     0,    44,     0,    58,     0,
       0,   157,     0,     0,   131,     0,    12,   106,     0,     0,
     113,   114,   117,     0,     0,   111,   105,     0,    74,    75,
       0,   139,     0,     0,     0,   147,   149,   169,     0,   162,
     187,   196,     0,   179,     0,   206,    45,     0,    46,     0,
      60,   198,   133,   135,     0,   121,   125,   116,   123,   127,
       0,   141,     0,     0,   150,   154,     0,   167,   177,   182,
       0,   181,     0,    47,    48,   107,   115,   142,    76,   144,
       0,     0,   152,     0,     0,   207,   151,   155,     0,   185,
     180,   153,   183,     0,     0,   186,     0,   184
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -189,  -189,   134,  -189,  -189,  -189,    36,   304,    23,  -189,
    -189,  -189,  -189,  -189,  -189,  -116,  -189,  -189,  -189,  -189,
    -189,  -189,  -189,  -189,  -189,  -189,   143,  -189,   215,  -189,
    -189,    -4,  -129,  -189,   285,  -189,  -189,  -189,  -189,  -189,
     -74,  -189,  -189,  -189,  -189,  -189,  -189,  -189,  -189,    80,
       4,   180,  -189,  -189,  -189,  -189,  -189,  -189,  -189,  -189,
    -189,  -189,  -189,  -189,  -170,  -188,  -189,  -189,  -189,  -189,
      78,  -189,  -189,  -189,  -189,  -189,  -189,  -189,  -189,  -189,
    -189,  -189,    70,  -189,  -189,  -189,  -189,  -189,  -189,  -189,
      -6,  -189,  -189,  -189,   216,   259,  -189,  -185,  -189,  -189,
    -189,   -49
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     9,   135,   219,   220,   131,   222,    10,    11,    12,
      20,    32,    13,    21,    34,    70,   115,   155,    71,    14,
      22,    36,    37,   206,   207,   124,   125,    58,    59,    60,
     277,   278,    88,    15,    24,    25,    54,   185,   184,    77,
      89,    90,    91,    92,    93,    94,   132,   174,   225,   270,
     271,   272,   268,   273,   269,   274,    95,   167,   168,    96,
     262,   263,    97,   136,   180,   181,   280,    98,   183,   238,
     239,   330,   338,   331,    99,   164,    16,    26,    44,   143,
     289,   189,   190,    17,    27,    45,    63,   247,   195,   321,
     292,   319,   344,   343,   111,   320,   193,   211,    18,    28,
      47,   160
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      72,    75,   170,   126,   159,   161,   176,   248,   246,    78,
     103,    79,   150,    80,   100,   310,  -130,   235,   116,    79,
     114,    80,   171,    38,   171,    81,    50,   122,   166,   123,
      82,    83,   236,    30,   196,   105,    48,   106,    82,    83,
      84,   197,    30,   253,   237,   281,   151,    85,    84,   118,
      23,   214,    86,    87,   104,   187,   101,   311,   285,    39,
     169,   256,   172,   173,    40,   173,   -64,   -64,   156,   157,
     158,   105,    49,   106,   254,   142,   105,    29,   106,  -161,
      46,   107,   108,   188,   109,   116,   107,   108,   110,   109,
     258,   265,   257,   110,   137,   313,   129,   117,   233,   264,
     138,   130,   279,   234,   201,   204,    31,  -161,   318,   235,
     240,   241,   260,   340,   261,    65,   118,    66,    67,    68,
     119,    79,    33,    80,   236,    66,    67,    68,   199,    67,
      68,   202,    67,    68,   243,    35,   237,   233,  -174,   244,
      82,    83,   347,   300,    55,   209,   302,   303,    69,   210,
      84,   252,   305,   306,   255,   345,    69,   308,   309,   200,
     336,   337,   203,    56,    57,   105,   177,   106,   341,    73,
      51,    74,    67,    68,   346,   107,   108,   260,   109,   291,
     178,   179,   110,   279,  -158,    42,   260,    43,   329,    53,
    -158,  -158,  -158,  -158,  -158,  -158,  -158,   133,   134,   216,
     217,    67,    68,    -2,     1,   297,   120,   121,   299,     2,
       3,     4,     5,     6,     7,     8,     2,     3,     4,     5,
       6,     7,     8,   133,   134,   153,   154,   162,   163,   212,
     213,   223,   224,   226,   227,    52,    61,    62,    64,   144,
      76,   113,   128,   145,   146,   102,   139,   152,   140,   127,
     148,   149,   165,   182,   191,   192,   198,   194,   186,   205,
     -59,   215,   221,   228,   230,   229,   242,   245,   249,   231,
     250,   259,   251,   232,   266,   267,   276,   282,   283,   284,
     288,   290,   293,   296,   298,   327,   294,   301,   295,   317,
     314,   307,   316,   315,   312,   322,   323,   324,   325,   333,
     332,   304,   335,   218,   339,    19,   208,   233,   328,   275,
      41,   326,   175,   287,   342,   334,   286,   141,     0,     0,
       0,   112,     0,     0,   147
};

static const yytype_int16 yycheck[] =
{
      49,    50,   131,    77,   120,   121,   135,   195,   193,     1,
       1,     3,     5,     5,     1,     1,    32,     5,     3,     3,
      69,     5,     3,     1,     3,    17,    37,     1,    44,     3,
      22,    23,    20,    10,    32,     3,     1,     5,    22,    23,
      32,    39,    19,     3,    32,   233,    39,    39,    32,    34,
       3,   167,    44,    45,    45,     5,    43,    43,    46,    37,
      44,     3,    41,    44,    42,    44,    40,    41,   117,   118,
     119,     3,    37,     5,    34,     1,     3,     0,     5,     5,
       5,    13,    14,    33,    16,     3,    13,    14,    20,    16,
     206,   220,    34,    20,    39,   280,    35,    15,    41,   215,
      45,    40,   231,    46,   153,   154,     3,    33,    40,     5,
     184,   185,    41,    40,    43,     1,    34,     3,     4,     5,
      38,     3,     3,     5,    20,     3,     4,     5,     3,     4,
       5,     3,     4,     5,    41,     3,    32,    41,     3,    46,
      22,    23,    46,   259,     3,     1,   262,   263,    34,     5,
      32,   200,   268,   269,   203,   343,    34,   273,   274,    34,
     330,   331,    34,    22,    23,     3,     3,     5,   338,     1,
      37,     3,     4,     5,   344,    13,    14,    41,    16,    43,
      17,    18,    20,   312,     0,     1,    41,     3,    43,    37,
       6,     7,     8,     9,    10,    11,    12,    31,    32,    33,
      34,     4,     5,     0,     1,   254,    31,    32,   257,     6,
       7,     8,     9,    10,    11,    12,     6,     7,     8,     9,
      10,    11,    12,    31,    32,    31,    32,    40,    41,    31,
      32,    31,    32,    31,    32,     5,    37,     3,    32,    48,
      39,    36,     5,    48,     3,    41,    37,     3,    37,    42,
      42,    37,    35,    40,     5,     3,     5,    39,    46,     3,
      32,    32,    36,    40,    39,    41,     5,    48,     5,    42,
       5,    32,    40,    42,    36,    40,    40,    32,    32,     5,
      47,     5,    39,     3,     3,    43,    39,     5,    40,     5,
      36,    41,    32,    36,    41,     5,     3,     3,    40,    32,
      36,   265,    40,   169,    36,     1,   163,    41,   312,   229,
      25,   307,   132,   243,    45,   321,   238,   102,    -1,    -1,
      -1,    62,    -1,    -1,   108
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     1,     6,     7,     8,     9,    10,    11,    12,    50,
      56,    57,    58,    61,    68,    82,   125,   132,   147,    56,
      59,    62,    69,     3,    83,    84,   126,   133,   148,     0,
      57,     3,    60,     3,    63,     3,    70,    71,     1,    37,
      42,    83,     1,     3,   127,   134,     5,   149,     1,    37,
      37,    37,     5,    37,    85,     3,    22,    23,    76,    77,
      78,    37,     3,   135,    32,     1,     3,     4,     5,    34,
      64,    67,   150,     1,     3,   150,    39,    88,     1,     3,
       5,    17,    22,    23,    32,    39,    44,    45,    81,    89,
      90,    91,    92,    93,    94,   105,   108,   111,   116,   123,
       1,    43,    41,     1,    45,     3,     5,    13,    14,    16,
      20,   143,   144,    36,   150,    65,     3,    15,    34,    38,
      31,    32,     1,     3,    74,    75,    89,    42,     5,    35,
      40,    54,    95,    31,    32,    51,   112,    39,    45,    37,
      37,    77,     1,   128,    48,    48,     3,   143,    42,    37,
       5,    39,     3,    31,    32,    66,   150,   150,   150,    64,
     150,    64,    40,    41,   124,    35,    44,   106,   107,    44,
      81,     3,    41,    44,    96,   100,    81,     3,    17,    18,
     113,   114,    40,   117,    87,    86,    46,     5,    33,   130,
     131,     5,     3,   145,    39,   137,    32,    39,     5,     3,
      34,   150,     3,    34,   150,     3,    72,    73,    75,     1,
       5,   146,    31,    32,    64,    32,    33,    34,    51,    52,
      53,    36,    55,    31,    32,    97,    31,    32,    40,    41,
      39,    42,    42,    41,    46,     5,    20,    32,   118,   119,
      89,    89,     5,    41,    46,    48,   146,   136,   114,     5,
       5,    40,   150,     3,    34,   150,     3,    34,    64,    32,
      41,    43,   109,   110,    64,    81,    36,    40,   101,   103,
      98,    99,   100,   102,   104,    98,    40,    79,    80,    81,
     115,   114,    32,    32,     5,    46,   119,   131,    47,   129,
       5,    43,   139,    39,    39,    40,     3,   150,     3,   150,
      64,     5,    64,    64,    55,    64,    64,    41,    64,    64,
       1,    43,    41,   146,    36,    36,    32,     5,    40,   140,
     144,   138,     5,     3,     3,    40,    99,    43,    80,    43,
     120,   122,    36,    32,   139,    40,   113,   113,   121,    36,
      40,   113,    45,   142,   141,   114,   113,    46
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    49,    50,    50,    50,    51,    51,    52,    52,    53,
      53,    54,    55,    56,    56,    57,    57,    57,    57,    57,
      57,    57,    58,    59,    59,    60,    60,    60,    60,    60,
      61,    62,    62,    63,    63,    63,    63,    63,    64,    65,
      65,    66,    66,    66,    66,    66,    66,    66,    66,    67,
      67,    67,    67,    68,    69,    69,    70,    72,    71,    73,
      71,    74,    74,    75,    75,    75,    76,    76,    77,    77,
      78,    78,    78,    79,    79,    80,    80,    81,    81,    81,
      81,    81,    82,    83,    83,    85,    84,    86,    84,    87,
      84,    88,    84,    89,    89,    89,    89,    89,    89,    89,
      89,    89,    89,    89,    90,    91,    92,    93,    95,    94,
      96,    96,    97,    96,    98,    98,    99,    99,   100,   100,
     101,   100,   102,   100,   103,   100,   104,   100,   106,   105,
     107,   105,   109,   108,   110,   108,   112,   111,   113,   113,
     114,   114,   114,   115,   114,   114,   117,   116,   118,   118,
     120,   119,   121,   119,   122,   119,   124,   123,   125,   126,
     126,   128,   127,   127,   127,   127,   129,   129,   130,   130,
     131,   131,   132,   133,   134,   133,   136,   135,   137,   138,
     135,   139,   139,   141,   140,   142,   140,   143,   143,   143,
     143,   144,   144,   144,   144,   145,   144,   146,   146,   146,
     147,   148,   148,   149,   149,   149,   149,   149,   150,   150
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     1,     2,     1,     1,     1,     1,     1,
       1,     2,     2,     1,     2,     1,     1,     1,     1,     1,
       1,     1,     2,     0,     2,     5,     5,     3,     3,     2,
       2,     0,     2,     3,     5,     3,     5,     3,     2,     0,
       2,     2,     2,     3,     3,     4,     4,     5,     5,     1,
       2,     3,     4,     2,     0,     2,     2,     0,     7,     0,
       8,     1,     3,     1,     0,     1,     0,     1,     1,     3,
       1,     1,     1,     0,     1,     1,     3,     1,     1,     2,
       1,     1,     2,     0,     2,     0,     4,     0,     7,     0,
       7,     0,     5,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     3,     5,     5,     7,     0,     4,
       1,     3,     0,     3,     1,     3,     0,     1,     1,     1,
       0,     4,     0,     4,     0,     4,     0,     4,     0,     4,
       0,     5,     0,     6,     0,     6,     0,     4,     1,     3,
       1,     4,     5,     0,     5,     1,     0,     5,     1,     2,
       0,     5,     0,     6,     0,     5,     0,     5,     2,     0,
       2,     0,     7,     5,     3,     1,     0,     2,     1,     3,
       1,     2,     2,     0,     0,     3,     0,     7,     0,     0,
       9,     0,     2,     0,     7,     0,     5,     5,     3,     3,
       1,     1,     1,     2,     2,     0,     5,     1,     3,     1,
       2,     0,     2,     4,     6,     6,     7,     9,     1,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


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
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (N)                                                            \
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
    while (0)
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


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


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static unsigned
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  unsigned res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += YYFPRINTF (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += YYFPRINTF (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += YYFPRINTF (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += YYFPRINTF (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += YYFPRINTF (yyo, "-%d", end_col);
    }
  return res;
 }

#  define YY_LOCATION_PRINT(File, Loc)          \
  yy_location_print_ (File, &(Loc))

# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value, Location, box); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, mutabor_box_type * box)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  YYUSE (yylocationp);
  YYUSE (box);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, mutabor_box_type * box)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  YY_LOCATION_PRINT (yyoutput, *yylocationp);
  YYFPRINTF (yyoutput, ": ");
  yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp, box);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
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
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp, int yyrule, mutabor_box_type * box)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                       , &(yylsp[(yyi + 1) - (yynrhs)])                       , box);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule, box); \
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
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
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
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
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
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
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

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp, mutabor_box_type * box)
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);
  YYUSE (box);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/*----------.
| yyparse.  |
`----------*/

int
yyparse (mutabor_box_type * box)
{
/* The lookahead symbol.  */
int yychar;


/* The semantic value of the lookahead symbol.  */
/* Default value used for initialization, for pacifying older GCCs
   or non-GCC compilers.  */
YY_INITIAL_VALUE (static YYSTYPE yyval_default;)
YYSTYPE yylval YY_INITIAL_VALUE (= yyval_default);

/* Location data for the lookahead symbol.  */
static YYLTYPE yyloc_default
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
YYLTYPE yylloc = yyloc_default;

    /* Number of syntax errors so far.  */
    int yynerrs;

    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.
       'yyls': related to locations.

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
      yychar = yylex (&yylval, &yylloc, box);
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
     '$$ = $1'.

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
#line 176 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    {  
			mutabor_error_message(box,
		                              compiler_error,
		                              _("Syntax error in line %d."),
		                              FEHLERZEILE);
		}
#line 1736 "src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 5:
#line 185 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { (yyval.integer) = '+' ; }
#line 1742 "src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 6:
#line 186 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { (yyval.integer) = '-' ; }
#line 1748 "src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 7:
#line 190 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { (yyval.integer) = '*' ; }
#line 1754 "src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 8:
#line 191 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { (yyval.integer) = '/' ; }
#line 1760 "src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 9:
#line 195 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { (yyval.integer) = (yyvsp[0].integer); }
#line 1766 "src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 10:
#line 196 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { (yyval.integer) = (yyvsp[0].integer); }
#line 1772 "src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 25:
#line 227 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { if ( fabs((yyvsp[0].f_value)) > 0.001 )
				    get_new_intervall (box, (yyvsp[-4].identifier), (yyvsp[-2].f_value) / (yyvsp[0].f_value));
                      else
			      mutabor_error_message (box,compiler_error,
					   _("Bad interval value in %s"),
					   ((yyvsp[-4].identifier)) );
		}
#line 1784 "src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 26:
#line 237 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { if ( fabs ((yyvsp[-2].f_value)) > 0.001 )
				    get_new_intervall (box, (yyvsp[-4].identifier), pow ((yyvsp[0].f_value), 1 / (yyvsp[-2].f_value)));
                      else
			      mutabor_error_message (box,compiler_error,
						     _("Bad interval value in %s"),
						     ((yyvsp[-4].identifier)));
		}
#line 1796 "src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 27:
#line 246 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { get_new_intervall_komplex (box,(yyvsp[-2].identifier)); }
#line 1802 "src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 28:
#line 247 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    {
		  mutabor_error_message(box,
		                        compiler_error,
		_("Bad interval declaration of intervall %s in line %d."),
		((yyvsp[-2].identifier)),
		FEHLERZEILE);
		}
#line 1814 "src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 29:
#line 254 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    {
		mutabor_error_message(box,
				      compiler_error,
				      _("Wrong character. Expecting %s in line %d."),
				      mutT("="),FEHLERZEILE);
	  }
#line 1825 "src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 33:
#line 276 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { get_new_ton_absolut (box, (yyvsp[-2].identifier), (yyvsp[0].f_value)); }
#line 1831 "src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 34:
#line 281 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { get_new_ton_komplex_negative (box, (yyvsp[-4].identifier), (yyvsp[-2].identifier)); }
#line 1837 "src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 35:
#line 285 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    {
		init_komplex_ton_list (box);
		get_new_ton_komplex_positive (box, (yyvsp[-2].identifier), (yyvsp[0].identifier)); 
	}
#line 1846 "src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 36:
#line 293 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { get_new_ton_komplex_positive (box, (yyvsp[-4].identifier), (yyvsp[-2].identifier)); }
#line 1852 "src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 37:
#line 295 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    {
		  mutabor_error_message(box,
		compiler_error,
		_("Bad tone declaration of tone %s in line %d."),
		((yyvsp[-2].identifier)),
		FEHLERZEILE);
		}
#line 1864 "src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 41:
#line 315 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { get_new_faktor_anteil ( box, (double) 1, (yyvsp[0].identifier)); }
#line 1870 "src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 42:
#line 318 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { get_new_faktor_anteil ( box,  (double) -1, (yyvsp[0].identifier)); }
#line 1876 "src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 43:
#line 321 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { get_new_faktor_anteil (box, (yyvsp[-1].f_value), (yyvsp[0].identifier)); }
#line 1882 "src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 44:
#line 324 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { get_new_faktor_anteil (box, -((yyvsp[-1].f_value)), (yyvsp[0].identifier)); }
#line 1888 "src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 45:
#line 327 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { if ( fabs((yyvsp[-1].f_value)) > 0.001 )
				   get_new_faktor_anteil (box, (double) 1 / ((yyvsp[-1].f_value)), (yyvsp[0].identifier));
			   else
				   mutabor_error_message(box,
							 compiler_error,
							 _("Division by (nearly) 0 in line %d."),
							 FEHLERZEILE);
		   }
#line 1901 "src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 46:
#line 337 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { if ( fabs((yyvsp[-1].f_value)) > 0.001 )
				   get_new_faktor_anteil (box, (double) -1 / ((yyvsp[-1].f_value)), (yyvsp[0].identifier));
                     else
				   mutabor_error_message(box,
							 compiler_error,
							 _("Division by (nearly) 0 in line %d."),
							 FEHLERZEILE);
		   }
#line 1914 "src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 47:
#line 347 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { if ( fabs((yyvsp[-1].f_value)) > 0.001 )
				   get_new_faktor_anteil (box, ((yyvsp[-3].f_value)) / ((yyvsp[-1].f_value)), (yyvsp[0].identifier));
                     else
			     mutabor_error_message(box,
						   compiler_error,
						   _("Division by (nearly) 0 in line %d."),
						   FEHLERZEILE);
		   }
#line 1927 "src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 48:
#line 357 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { if ( fabs((yyvsp[-1].f_value)) > 0.001 )
				   get_new_faktor_anteil (box, -((yyvsp[-3].f_value)) / ((yyvsp[-1].f_value)), (yyvsp[0].identifier));
                     else
			     mutabor_error_message(box,
						   compiler_error,
						   _("Division by (nearly) 0 in line %d."),
						   FEHLERZEILE);
		   }
#line 1940 "src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 49:
#line 382 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { init_komplex_ton_list (box); 
		get_new_faktor_anteil (box, (double) 1.0 , (yyvsp[0].identifier)); }
#line 1947 "src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 50:
#line 391 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { init_komplex_ton_list (box); 
		get_new_faktor_anteil (box, (yyvsp[-1].f_value), (yyvsp[0].identifier)); }
#line 1954 "src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 51:
#line 395 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { init_komplex_ton_list (box); 
		if ( fabs((yyvsp[-1].f_value)) > 0.001 )
				   get_new_faktor_anteil (box, (double) 1 / ((yyvsp[-1].f_value)), (yyvsp[0].identifier));
                     else
			     mutabor_error_message(box,
						   compiler_error,
						   _("Division by (nearly) 0 in line %d."),
						   FEHLERZEILE);
		   }
#line 1968 "src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 52:
#line 406 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { init_komplex_ton_list (box); 
		if ( fabs((yyvsp[-1].f_value)) > 0.001 )
				   get_new_faktor_anteil (box, ((yyvsp[-3].f_value)) / ((yyvsp[-1].f_value)), (yyvsp[0].identifier));
                     else
			     mutabor_error_message(box,
						   compiler_error,
						   _("Division by (nearly) 0 in line %d."),
						   FEHLERZEILE);
		   }
#line 1982 "src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 56:
#line 445 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { init_ton_liste (box); 
		(yyval.identifier) = (yyvsp[-1].identifier);
		}
#line 1990 "src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 57:
#line 449 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { init_komplex_ton_list (box); }
#line 1996 "src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 58:
#line 451 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { get_new_tonsystem (box, (yyvsp[-6].identifier), (yyvsp[-5].integer)); }
#line 2002 "src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 59:
#line 453 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { init_komplex_ton_list (box); }
#line 2008 "src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 60:
#line 455 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { get_new_tonsystem_negative (box, (yyvsp[-7].identifier), (yyvsp[-6].integer)); }
#line 2014 "src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 63:
#line 461 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { get_new_ton_in_tonsystem (box, (yyvsp[0].identifier)); }
#line 2020 "src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 64:
#line 462 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { get_new_ton_in_tonsystem (box, NULL); }
#line 2026 "src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 65:
#line 463 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    {     mutabor_error_message(box,
		compiler_error,
		_("Bad tonesystem declaration in line %d."),
		FEHLERZEILE);
		}
#line 2036 "src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 66:
#line 471 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { (yyval.parameters) = NULL; }
#line 2042 "src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 67:
#line 472 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { (yyval.parameters) = (yyvsp[0].parameters);
                    enumerate_parameters(box,(yyval.parameters));
		}
#line 2050 "src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 69:
#line 480 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    {
		    if ((yyvsp[-2].parameters) != NULL) {
			(yyval.parameters) = (yyvsp[-2].parameters);
		        (yyval.parameters)->next = (yyvsp[0].parameters);
   		    } else {(yyval.parameters) = (yyvsp[0].parameters);}
		}
#line 2061 "src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 70:
#line 490 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    {
			(yyval.parameters) = get_new_name_in_parameterlist (box, (yyvsp[0].identifier));
		}
#line 2069 "src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 71:
#line 493 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    {
		    (yyval.parameters) = NULL;
		    mutabor_error_message(box,
					  compiler_warning,
		                          _("Arguments named “DISTANCE” or “ABSTAND” have a fixed meaning. Using them as parameters as in line %d is not supported. Expect undexpected behaviour."),
		                          FEHLERZEILE);
		}
#line 2081 "src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 72:
#line 500 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    {
			(yyval.parameters) = NULL;
		        mutabor_error_message(box,
					  compiler_warning,
		                          _("Arguments named “DISTANCE” or “ABSTAND” have a fixed meaning. Using them as parameters as in line %d is not supported. Expect undexpected behaviour."),
 		                          FEHLERZEILE);
		}
#line 2093 "src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 73:
#line 520 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { (yyval.arguments) = NULL; }
#line 2099 "src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 74:
#line 521 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    {
			(yyval.arguments) = (yyvsp[0].arguments);
		}
#line 2107 "src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 75:
#line 527 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    {
			(yyval.arguments) = (yyvsp[0].arguments);
		}
#line 2115 "src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 76:
#line 530 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    {
			(yyval.arguments) = (yyvsp[-2].arguments);
		        (yyvsp[-2].arguments)->next = (yyvsp[0].arguments);
		}
#line 2124 "src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 77:
#line 547 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { (yyval.arguments) = get_new_name_in_argument_list (box, (yyvsp[0].identifier)) ;  }
#line 2130 "src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 78:
#line 549 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { (yyval.arguments) = get_new_number_in_argument_list (box, (yyvsp[0].integer)) ;  }
#line 2136 "src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 79:
#line 551 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { (yyval.arguments) = get_new_number_in_argument_list (box, -((yyvsp[0].integer))); }
#line 2142 "src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 80:
#line 553 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { (yyval.arguments) = get_new_distance_in_argument_list (box); }
#line 2148 "src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 81:
#line 555 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { (yyval.arguments) = get_new_anchor_in_argument_list (box); }
#line 2154 "src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 85:
#line 570 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    {
			init_umstimmung (box, (yyvsp[-1].identifier));
		eintrage_parameterliste_in_umstimmung (box,
                                                       box->file->tmp_umstimmung,
 		                                       NULL);
		}
#line 2165 "src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 86:
#line 576 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    {
			get_new_umstimmung (box);
		}
#line 2173 "src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 87:
#line 581 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    {
			init_umstimmung (box,(yyvsp[-4].identifier));
		        eintrage_parameterliste_in_umstimmung (box,
                                                       box->file->tmp_umstimmung,
 		                                       (yyvsp[-2].parameters));
		}
#line 2184 "src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 88:
#line 586 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    {
			get_new_umstimmung (box);
		}
#line 2192 "src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 89:
#line 591 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    {
			init_umstimmung (box,(yyvsp[-4].identifier));
		        eintrage_parameterliste_in_umstimmung (box,
                                                       box->file->tmp_umstimmung,
 		                                       (yyvsp[-2].parameters));
		        mutabor_error_message(box,
		                              compiler_error,
		                              _("Invalid parameter list in retuning %s line %d"),
		                              (yyvsp[-4].identifier), FEHLERZEILE);
		}
#line 2207 "src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 90:
#line 600 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    {
			get_new_umstimmung (box);
		}
#line 2215 "src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 91:
#line 604 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    {
			init_umstimmung (box,(yyvsp[-2].identifier));
		        eintrage_parameterliste_in_umstimmung (box,
                                                       box->file->tmp_umstimmung,
 		                                       NULL);
		        mutabor_error_message(box,
		                              compiler_error,
		                              _("Error while reading %s line %d"),
                               		      (yyvsp[-2].identifier), FEHLERZEILE);
		}
#line 2230 "src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 92:
#line 614 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { get_new_umstimmung (box); }
#line 2236 "src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 93:
#line 618 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    {}
#line 2242 "src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 94:
#line 619 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    {}
#line 2248 "src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 95:
#line 620 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    {}
#line 2254 "src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 96:
#line 621 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    {}
#line 2260 "src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 97:
#line 622 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    {}
#line 2266 "src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 98:
#line 623 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    {}
#line 2272 "src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 99:
#line 624 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    {}
#line 2278 "src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 100:
#line 625 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    {}
#line 2284 "src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 101:
#line 626 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    {}
#line 2290 "src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 102:
#line 627 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    {}
#line 2296 "src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 103:
#line 628 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    {
		mutabor_error_message(box,
				      compiler_error,
				      _("Bad retuning in line %d."),
				      FEHLERZEILE);
	  }
#line 2307 "src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 104:
#line 639 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { get_umstimmung_taste_abs (box, (yyvsp[-2].arguments)); }
#line 2313 "src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 105:
#line 644 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { get_umstimmung_taste_rel (box, (yyvsp[-2].arguments), (yyvsp[-3].integer)); }
#line 2319 "src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 106:
#line 649 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { get_umstimmung_breite_abs (box, (yyvsp[-2].arguments)); }
#line 2325 "src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 107:
#line 654 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { get_umstimmung_breite_rel (box, (yyvsp[-2].arguments), (yyvsp[-3].integer)); }
#line 2331 "src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 108:
#line 659 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { init_umstimm_expression_list (box); }
#line 2337 "src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 109:
#line 661 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { get_umstimmung_tonhoehe_veraendert (box); }
#line 2343 "src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 110:
#line 668 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    {}
#line 2349 "src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 111:
#line 669 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    {}
#line 2355 "src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 112:
#line 671 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { init_komplex_ton_list(box);
		  get_new_umstimm_expression (box,NULL);
                   }
#line 2363 "src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 113:
#line 674 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    {}
#line 2369 "src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 114:
#line 678 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    {}
#line 2375 "src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 115:
#line 679 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    {}
#line 2381 "src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 116:
#line 684 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { init_komplex_ton_list(box);
		  get_new_umstimm_expression (box, NULL);
                   }
#line 2389 "src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 118:
#line 692 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { get_new_umstimm_expression (box,(yyvsp[0].identifier)); }
#line 2395 "src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 119:
#line 693 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { get_new_umstimm_expression (box, "@"); }
#line 2401 "src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 120:
#line 695 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { init_komplex_ton_list (box); }
#line 2407 "src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 121:
#line 697 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { get_new_umstimm_expression_positive (box, (yyvsp[-3].identifier)); }
#line 2413 "src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 122:
#line 698 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { init_komplex_ton_list (box); }
#line 2419 "src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 123:
#line 700 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { get_new_umstimm_expression_positive (box, "@" ); }
#line 2425 "src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 124:
#line 701 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { init_komplex_ton_list (box); }
#line 2431 "src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 125:
#line 703 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { get_new_umstimm_expression_negative (box,(yyvsp[-3].identifier)); }
#line 2437 "src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 126:
#line 704 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { init_komplex_ton_list (box); }
#line 2443 "src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 127:
#line 706 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { get_new_umstimm_expression_negative (box, "@" ); }
#line 2449 "src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 128:
#line 711 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { init_komplex_ton_list (box); }
#line 2455 "src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 129:
#line 713 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { get_umstimmung_wiederholung_abs (box); }
#line 2461 "src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 130:
#line 714 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { init_komplex_ton_list (box); }
#line 2467 "src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 131:
#line 716 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { get_umstimmung_wiederholung_abs_negative (box); }
#line 2473 "src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 132:
#line 720 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { init_komplex_ton_list (box); }
#line 2479 "src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 133:
#line 722 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { get_umstimmung_wiederholung_rel_positive (box); }
#line 2485 "src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 134:
#line 723 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { init_komplex_ton_list (box); }
#line 2491 "src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 135:
#line 725 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { get_umstimmung_wiederholung_rel_negative (box); }
#line 2497 "src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 136:
#line 729 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { init_aktions_liste (box); }
#line 2503 "src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 137:
#line 731 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { get_umstimmung_umstimmungs_bund (box); }
#line 2509 "src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 138:
#line 735 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    {}
#line 2515 "src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 139:
#line 736 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    {}
#line 2521 "src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 140:
#line 740 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    {
		  get_new_aktion_aufruf_element (box,(yyvsp[0].identifier),NULL);
	  }
#line 2529 "src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 141:
#line 744 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { get_new_aktion_aufruf_element (box,(yyvsp[-3].identifier), (yyvsp[-1].arguments)); }
#line 2535 "src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 142:
#line 746 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { get_new_aktion_aufruf_element (box,(yyvsp[-4].identifier), (yyvsp[-2].arguments));
			    mutabor_error_message(box,
						 compiler_error,
						 _("Invalid argument list for call to %s in line %d"),
						 (yyvsp[-4].identifier),
						 FEHLERZEILE);
		    }
#line 2547 "src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 143:
#line 754 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { init_integersequenz (box);}
#line 2553 "src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 144:
#line 756 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { get_new_aktion_midi_out_element (box); }
#line 2559 "src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 145:
#line 757 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { get_new_aktion_harmony_analysis(box); }
#line 2565 "src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 146:
#line 761 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { init_umstimmungs_case_liste (box); }
#line 2571 "src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 147:
#line 763 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { get_umstimmung_umstimm_case (box,(yyvsp[-4].arguments)); }
#line 2577 "src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 148:
#line 767 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    {}
#line 2583 "src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 149:
#line 768 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    {}
#line 2589 "src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 150:
#line 773 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { init_aktions_liste (box); }
#line 2595 "src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 151:
#line 775 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { get_umstimmungs_case_zahl_element (box,(yyvsp[-4].integer)); }
#line 2601 "src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 152:
#line 777 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { init_aktions_liste (box); }
#line 2607 "src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 153:
#line 779 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { get_umstimmungs_case_zahl_element (box,-((yyvsp[-4].integer))); }
#line 2613 "src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 154:
#line 781 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { init_aktions_liste (box); }
#line 2619 "src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 155:
#line 783 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { get_umstimmungs_case_default_element (box); }
#line 2625 "src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 156:
#line 788 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { init_integersequenz (box);}
#line 2631 "src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 157:
#line 790 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { get_umstimmung_midi_out (box); }
#line 2637 "src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 158:
#line 795 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    {}
#line 2643 "src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 159:
#line 799 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    {}
#line 2649 "src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 160:
#line 800 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    {}
#line 2655 "src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 161:
#line 805 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { init_tastenliste (box); }
#line 2661 "src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 162:
#line 807 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { get_new_harmonie (box, (yyvsp[-6].identifier), (yyvsp[0].integer)); }
#line 2667 "src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 163:
#line 809 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    {
		mutabor_error_message(box,
		compiler_error,
		_("There is an error in the chroma list in harmony “%s” at line %d."),
		((yyvsp[-4].identifier)),
		FEHLERZEILE);
                yyclearin;
	  }
#line 2680 "src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 164:
#line 817 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    {
		  mutabor_error_message(box,
		                        compiler_error,
					_("The chroma list must be enclosed in braces '{' '}' in harmony “%s” at line %d."),
					((yyvsp[-2].identifier)),
		                        FEHLERZEILE);
                yyclearin;
          }
#line 2693 "src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 166:
#line 829 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { (yyval.integer) = -1; }
#line 2699 "src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 167:
#line 830 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { (yyval.integer) = (yyvsp[0].integer); }
#line 2705 "src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 168:
#line 834 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    {}
#line 2711 "src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 169:
#line 835 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    {}
#line 2717 "src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 170:
#line 839 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { get_new_taste (box, (yyvsp[0].integer), '+'); }
#line 2723 "src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 171:
#line 840 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { get_new_taste (box, (yyvsp[0].integer), '*'); }
#line 2729 "src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 172:
#line 844 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    {}
#line 2735 "src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 173:
#line 848 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    {}
#line 2741 "src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 174:
#line 849 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { init_ausloeser (box);
                         /* f〉 die Anfangsausloesung der Logik */
                       }
#line 2749 "src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 175:
#line 852 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    {}
#line 2755 "src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 176:
#line 857 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { init_aktions_liste (box);
		get_new_logik (box, (yyvsp[-3].identifier));
                init_anweisungs_liste (box); }
#line 2763 "src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 177:
#line 861 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { vervollstaendige_logik (box); }
#line 2769 "src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 178:
#line 863 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { init_aktions_liste (box); }
#line 2775 "src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 179:
#line 866 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { get_new_logik (box, (yyvsp[-5].identifier));
                init_anweisungs_liste (box); }
#line 2782 "src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 180:
#line 869 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { vervollstaendige_logik (box); }
#line 2788 "src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 181:
#line 873 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    {}
#line 2794 "src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 182:
#line 874 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    {}
#line 2800 "src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 183:
#line 879 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { init_aktions_liste (box); }
#line 2806 "src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 184:
#line 881 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { get_new_anweisung (box); }
#line 2812 "src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 185:
#line 883 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { init_aktions_liste (box); }
#line 2818 "src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 186:
#line 885 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { get_new_anweisung (box); }
#line 2824 "src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 187:
#line 890 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { get_harmoniebezeichner (box,
                                  mutabor_harmony_bothkey,
				  (yyvsp[-4].integer), (yyvsp[-2].identifier),  (yyvsp[0].integer)); }
#line 2832 "src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 188:
#line 894 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { get_harmoniebezeichner (box,
                                  mutabor_harmony_postkey,
				  0, (yyvsp[-2].identifier),  (yyvsp[0].integer)); }
#line 2840 "src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 189:
#line 898 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { get_harmoniebezeichner (box,
				  mutabor_harmony_prekey,
				  (yyvsp[-2].integer), (yyvsp[0].identifier), 0); }
#line 2848 "src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 190:
#line 902 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { get_harmoniebezeichner (box,
				  mutabor_harmony_nokey,
				  0, (yyvsp[0].identifier), 0); }
#line 2856 "src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 191:
#line 908 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { get_ausloeser_default (box); }
#line 2862 "src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 192:
#line 909 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { get_ausloeser_harmonie (box); }
#line 2868 "src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 193:
#line 910 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { get_ausloeser_harmonie_form (box); }
#line 2874 "src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 194:
#line 911 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { get_ausloeser_taste (box,(yyvsp[0].identifier)); }
#line 2880 "src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 195:
#line 912 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { init_integersequenz (box); }
#line 2886 "src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 196:
#line 914 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { get_ausloeser_midi_in (box); }
#line 2892 "src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 197:
#line 919 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { get_new_integer_in_integersequenz (box,(yyvsp[0].integer));}
#line 2898 "src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 198:
#line 921 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { get_new_integer_in_integersequenz (box,(yyvsp[0].integer));}
#line 2904 "src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 199:
#line 922 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    {
		mutabor_error_message(box,
				      compiler_error,
				      _("Bad MIDI list in line %d"),
				      FEHLERZEILE );
	  }
#line 2915 "src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 200:
#line 932 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    {}
#line 2921 "src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 201:
#line 936 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    {}
#line 2927 "src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 202:
#line 937 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    {}
#line 2933 "src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 203:
#line 942 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { get_instrument_dekl (box, (yyvsp[-3].integer), (yyvsp[0].integer), (yyvsp[0].integer), 0, & box->file->list_of_instrumente); }
#line 2939 "src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 204:
#line 944 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { get_instrument_dekl (box, (yyvsp[-5].integer), (yyvsp[-2].integer), (yyvsp[0].integer), 0, & box->file->list_of_instrumente); }
#line 2945 "src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 205:
#line 946 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { get_instrument_dekl (box, (yyvsp[-5].integer), 0, 0, (yyvsp[-1].integer), & box->file->list_of_instrumente); }
#line 2951 "src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 206:
#line 948 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { get_instrument_dekl (box, (yyvsp[-6].integer), (yyvsp[-3].integer), (yyvsp[-3].integer), (yyvsp[-1].integer), & box->file->list_of_instrumente); }
#line 2957 "src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 207:
#line 950 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { get_instrument_dekl (box, (yyvsp[-8].integer), (yyvsp[-5].integer), (yyvsp[-3].integer), (yyvsp[-1].integer), & box->file->list_of_instrumente); }
#line 2963 "src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 208:
#line 954 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { (yyval.f_value) = (yyvsp[0].f_value) ; }
#line 2969 "src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 209:
#line 955 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { (yyval.f_value) = (double) (yyvsp[0].integer) ; }
#line 2975 "src/kernel/mut.cc" /* yacc.c:1646  */
    break;


#line 2979 "src/kernel/mut.cc" /* yacc.c:1646  */
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

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

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
  /* Do not reclaim the symbols of the rule whose action triggered
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
  return yyresult;
}
#line 959 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1906  */

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
{ "HARMONY"    , MUTABOR_TOKEN_HARMONY   },
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

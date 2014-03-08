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
#define YYFREE(X) do { /* empty */; } while (0)
#define YYMAXLIMIT (HEAP_PORTION_SYNTAX / sizeof(YYLTYPE) - 1)
                   /* wegen fehlendem alloca in PUREC */

#line 116 "../../../mutabor-git/src/kernel/mut.cc" /* yacc.c:339  */

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
#ifndef YY_YY__MUTABOR_GIT_SRC_KERNEL_MUT_HH_INCLUDED
# define YY_YY__MUTABOR_GIT_SRC_KERNEL_MUT_HH_INCLUDED
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
#line 88 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:355  */

			double      f_value;        /* floating point numbers */
			int         integer;        /* integers */
			char        *identifier;    /* names/identifiers */
			struct argument_list * arguments;  /* argument list */
			struct parameter_list * parameters; /* parameter list */

#line 224 "../../../mutabor-git/src/kernel/mut.cc" /* yacc.c:355  */
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

#endif /* !YY_YY__MUTABOR_GIT_SRC_KERNEL_MUT_HH_INCLUDED  */

/* Copy the second part of user declarations.  */
#line 150 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:358  */

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

#line 266 "../../../mutabor-git/src/kernel/mut.cc" /* yacc.c:358  */

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
#define YYLAST   332

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  49
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  106
/* YYNRULES -- Number of rules.  */
#define YYNRULES  212
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  349

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
       0,   168,   168,   169,   173,   174,   178,   179,   183,   184,
     187,   188,   190,   191,   194,   195,   196,   197,   198,   199,
     200,   201,   202,   210,   212,   214,   218,   218,   222,   230,
     241,   243,   250,   259,   261,   263,   267,   267,   271,   274,
     278,   282,   286,   296,   300,   302,   305,   308,   311,   314,
     317,   327,   337,   347,   372,   380,   383,   393,   423,   425,
     427,   431,   431,   436,   435,   440,   439,   445,   445,   448,
     449,   450,   458,   459,   465,   466,   477,   480,   487,   507,
     508,   514,   517,   533,   535,   537,   539,   541,   547,   551,
     553,   557,   557,   568,   567,   578,   577,   591,   591,   605,
     606,   607,   608,   609,   610,   611,   612,   613,   614,   615,
     625,   630,   635,   640,   646,   645,   655,   656,   658,   658,
     665,   666,   671,   675,   679,   680,   682,   682,   685,   685,
     688,   688,   691,   691,   698,   698,   701,   701,   707,   707,
     710,   710,   716,   716,   722,   723,   727,   730,   732,   741,
     740,   744,   748,   748,   754,   755,   760,   759,   764,   763,
     768,   767,   775,   774,   782,   786,   787,   792,   791,   796,
     806,   807,   811,   812,   816,   817,   821,   825,   826,   826,
     834,   833,   839,   838,   846,   847,   852,   852,   856,   856,
     862,   866,   870,   874,   881,   882,   883,   884,   885,   885,
     891,   893,   895,   905,   909,   910,   914,   916,   918,   920,
     922,   927,   928
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
  "GLEITKOMMA_ZAHL", YY_NULLPTR
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

#define YYPACT_NINF -220

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-220)))

#define YYTABLE_NINF -179

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
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

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
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

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
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

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
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
#line 173 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { (yyval.integer) = '+' ; }
#line 1731 "../../../mutabor-git/src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 5:
#line 174 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { (yyval.integer) = '-' ; }
#line 1737 "../../../mutabor-git/src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 6:
#line 178 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { (yyval.integer) = '*' ; }
#line 1743 "../../../mutabor-git/src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 7:
#line 179 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { (yyval.integer) = '/' ; }
#line 1749 "../../../mutabor-git/src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 8:
#line 183 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { (yyval.integer) = (yyvsp[0].integer); }
#line 1755 "../../../mutabor-git/src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 9:
#line 184 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { (yyval.integer) = (yyvsp[0].integer); }
#line 1761 "../../../mutabor-git/src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 22:
#line 202 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    {  mutabor_error_message(box,
		compiler_error,
		_("Syntax error in line %d."),
		FEHLERZEILE);
		}
#line 1771 "../../../mutabor-git/src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 26:
#line 218 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { init_komplex_ton_list (box); }
#line 1777 "../../../mutabor-git/src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 28:
#line 223 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { if ( fabs((yyvsp[0].f_value)) > 0.001 )
				    get_new_intervall (box, (yyvsp[-4].identifier), (yyvsp[-2].f_value) / (yyvsp[0].f_value));
                      else
			      mutabor_error_message (box,compiler_error,
					   _("Bad interval value in %s"),
					   ((yyvsp[-4].identifier)) ); }
#line 1788 "../../../mutabor-git/src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 29:
#line 231 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { if ( fabs ((yyvsp[-2].f_value)) > 0.001 )
				    get_new_intervall (box, (yyvsp[-4].identifier), pow ((yyvsp[0].f_value), 1 / (yyvsp[-2].f_value)));
                      else
			      mutabor_error_message (box,compiler_error,
						     _("Bad interval value in %s"),
						     ((yyvsp[-4].identifier))); }
#line 1799 "../../../mutabor-git/src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 30:
#line 242 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { get_new_intervall_komplex (box,(yyvsp[-2].identifier)); }
#line 1805 "../../../mutabor-git/src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 31:
#line 243 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    {
		  mutabor_error_message(box,
		                        compiler_error,
		                        _("Bad interval declaration of intervall %s in line %d."),
				        ((yyvsp[-2].identifier)),
				        FEHLERZEILE);
		}
#line 1817 "../../../mutabor-git/src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 32:
#line 250 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    {
		mutabor_error_message(box,
				      compiler_error,
				      _("Wrong character. Expecting %s in line %d."),
				      mutT("="),FEHLERZEILE);
	  }
#line 1828 "../../../mutabor-git/src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 36:
#line 267 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { init_komplex_ton_list (box); }
#line 1834 "../../../mutabor-git/src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 38:
#line 272 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { get_new_ton_absolut (box, (yyvsp[-2].identifier), (yyvsp[0].f_value)); }
#line 1840 "../../../mutabor-git/src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 39:
#line 276 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { get_new_ton_komplex_negative (box, (yyvsp[-4].identifier), (yyvsp[-2].identifier)); }
#line 1846 "../../../mutabor-git/src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 40:
#line 280 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { get_new_ton_komplex_positive (box, (yyvsp[-2].identifier), (yyvsp[0].identifier)); }
#line 1852 "../../../mutabor-git/src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 41:
#line 284 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { get_new_ton_komplex_positive (box, (yyvsp[-4].identifier), (yyvsp[-2].identifier)); }
#line 1858 "../../../mutabor-git/src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 42:
#line 286 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    {
	      mutabor_error_message(box,
				    compiler_error,
				    _("Bad tone declaration of tone %s in line %d."),
				    ((yyvsp[-2].identifier)),
				    FEHLERZEILE);
	}
#line 1870 "../../../mutabor-git/src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 46:
#line 306 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { get_new_faktor_anteil ( box, (double) 1, (yyvsp[0].identifier)); }
#line 1876 "../../../mutabor-git/src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 47:
#line 309 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { get_new_faktor_anteil ( box,  (double) -1, (yyvsp[0].identifier)); }
#line 1882 "../../../mutabor-git/src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 48:
#line 312 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { get_new_faktor_anteil (box, (yyvsp[-1].f_value), (yyvsp[0].identifier)); }
#line 1888 "../../../mutabor-git/src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 49:
#line 315 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { get_new_faktor_anteil (box, -((yyvsp[-1].f_value)), (yyvsp[0].identifier)); }
#line 1894 "../../../mutabor-git/src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 50:
#line 318 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { if ( fabs((yyvsp[-1].f_value)) > 0.001 )
				   get_new_faktor_anteil (box, (double) 1 / ((yyvsp[-1].f_value)), (yyvsp[0].identifier));
			   else
				   mutabor_error_message(box,
							 compiler_error,
							 _("Division by (nearly) 0 in line %d."),
							 FEHLERZEILE);
		   }
#line 1907 "../../../mutabor-git/src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 51:
#line 328 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { if ( fabs((yyvsp[-1].f_value)) > 0.001 )
				   get_new_faktor_anteil (box, (double) -1 / ((yyvsp[-1].f_value)), (yyvsp[0].identifier));
                     else
				   mutabor_error_message(box,
							 compiler_error,
							 _("Division by (nearly) 0 in line %d."),
							 FEHLERZEILE);
		   }
#line 1920 "../../../mutabor-git/src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 52:
#line 338 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { if ( fabs((yyvsp[-1].f_value)) > 0.001 )
				   get_new_faktor_anteil (box, ((yyvsp[-3].f_value)) / ((yyvsp[-1].f_value)), (yyvsp[0].identifier));
                     else
			     mutabor_error_message(box,
						   compiler_error,
						   _("Division by (nearly) 0 in line %d."),
						   FEHLERZEILE);
		   }
#line 1933 "../../../mutabor-git/src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 53:
#line 348 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { if ( fabs((yyvsp[-1].f_value)) > 0.001 )
				   get_new_faktor_anteil (box, -((yyvsp[-3].f_value)) / ((yyvsp[-1].f_value)), (yyvsp[0].identifier));
                     else
			     mutabor_error_message(box,
						   compiler_error,
						   _("Division by (nearly) 0 in line %d."),
						   FEHLERZEILE);
		   }
#line 1946 "../../../mutabor-git/src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 54:
#line 373 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { get_new_faktor_anteil (box, (double) 1.0 , (yyvsp[0].identifier)); }
#line 1952 "../../../mutabor-git/src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 55:
#line 381 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { get_new_faktor_anteil (box, (yyvsp[-1].f_value), (yyvsp[0].identifier)); }
#line 1958 "../../../mutabor-git/src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 56:
#line 384 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { if ( fabs((yyvsp[-1].f_value)) > 0.001 )
				   get_new_faktor_anteil (box, (double) 1 / ((yyvsp[-1].f_value)), (yyvsp[0].identifier));
                     else
			     mutabor_error_message(box,
						   compiler_error,
						   _("Division by (nearly) 0 in line %d."),
						   FEHLERZEILE);
		   }
#line 1971 "../../../mutabor-git/src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 57:
#line 394 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { if ( fabs((yyvsp[-1].f_value)) > 0.001 )
				   get_new_faktor_anteil (box, ((yyvsp[-3].f_value)) / ((yyvsp[-1].f_value)), (yyvsp[0].identifier));
                     else
			     mutabor_error_message(box,
						   compiler_error,
						   _("Division by (nearly) 0 in line %d."),
						   FEHLERZEILE);
		   }
#line 1984 "../../../mutabor-git/src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 61:
#line 431 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { init_ton_liste (box); }
#line 1990 "../../../mutabor-git/src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 63:
#line 436 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { init_komplex_ton_list (box); }
#line 1996 "../../../mutabor-git/src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 64:
#line 438 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { get_new_tonsystem (box, (yyvsp[-7].identifier), (yyvsp[-5].integer)); }
#line 2002 "../../../mutabor-git/src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 65:
#line 440 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { init_komplex_ton_list (box); }
#line 2008 "../../../mutabor-git/src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 66:
#line 442 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { get_new_tonsystem_negative (box, (yyvsp[-8].identifier), (yyvsp[-6].integer)); }
#line 2014 "../../../mutabor-git/src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 69:
#line 448 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { get_new_ton_in_tonsystem (box, (yyvsp[0].identifier)); }
#line 2020 "../../../mutabor-git/src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 70:
#line 449 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { get_new_ton_in_tonsystem (box, NULL); }
#line 2026 "../../../mutabor-git/src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 71:
#line 450 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    {     mutabor_error_message(box,
		compiler_error,
		_("Bad tonesystem declaration in line %d."),
		FEHLERZEILE);
		}
#line 2036 "../../../mutabor-git/src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 72:
#line 458 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { (yyval.parameters) = NULL; }
#line 2042 "../../../mutabor-git/src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 73:
#line 459 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { (yyval.parameters) = (yyvsp[0].parameters);
                    enumerate_parameters(box,(yyval.parameters));
		}
#line 2050 "../../../mutabor-git/src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 75:
#line 467 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    {
		    if ((yyvsp[-2].parameters) != NULL) {
			(yyval.parameters) = (yyvsp[-2].parameters);
		        (yyval.parameters)->next = (yyvsp[0].parameters);
   		    } else {(yyval.parameters) = (yyvsp[0].parameters);}
		}
#line 2061 "../../../mutabor-git/src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 76:
#line 477 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    {
			(yyval.parameters) = get_new_name_in_parameterlist (box, (yyvsp[0].identifier));
		}
#line 2069 "../../../mutabor-git/src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 77:
#line 480 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    {
		    (yyval.parameters) = NULL;
		    mutabor_error_message(box,
					  compiler_warning,
		                          _("Arguments named “DISTANCE” or “ABSTAND” have a fixed meaning. Using them as parameters as in line %d is not supported. Expect undexpected behaviour."),
		                          FEHLERZEILE);
		}
#line 2081 "../../../mutabor-git/src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 78:
#line 487 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    {
			(yyval.parameters) = NULL;
		        mutabor_error_message(box,
					  compiler_warning,
		                          _("Arguments named “DISTANCE” or “ABSTAND” have a fixed meaning. Using them as parameters as in line %d is not supported. Expect undexpected behaviour."),
 		                          FEHLERZEILE);
		}
#line 2093 "../../../mutabor-git/src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 79:
#line 507 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { (yyval.arguments) = NULL; }
#line 2099 "../../../mutabor-git/src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 80:
#line 508 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    {
			(yyval.arguments) = (yyvsp[0].arguments);
		}
#line 2107 "../../../mutabor-git/src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 81:
#line 514 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    {
			(yyval.arguments) = (yyvsp[0].arguments);
		}
#line 2115 "../../../mutabor-git/src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 82:
#line 517 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    {
			(yyval.arguments) = (yyvsp[-2].arguments);
		        (yyvsp[-2].arguments)->next = (yyvsp[0].arguments);
		}
#line 2124 "../../../mutabor-git/src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 83:
#line 534 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { (yyval.arguments) = get_new_name_in_argument_list (box, (yyvsp[0].identifier)) ;  }
#line 2130 "../../../mutabor-git/src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 84:
#line 536 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { (yyval.arguments) = get_new_number_in_argument_list (box, (yyvsp[0].integer)) ;  }
#line 2136 "../../../mutabor-git/src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 85:
#line 538 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { (yyval.arguments) = get_new_number_in_argument_list (box, -((yyvsp[0].integer))); }
#line 2142 "../../../mutabor-git/src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 86:
#line 540 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { (yyval.arguments) = get_new_distance_in_argument_list (box); }
#line 2148 "../../../mutabor-git/src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 87:
#line 542 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { (yyval.arguments) = get_new_anchor_in_argument_list (box); }
#line 2154 "../../../mutabor-git/src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 91:
#line 557 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    {
			init_umstimmung (box, (yyvsp[-1].identifier));
		eintrage_parameterliste_in_umstimmung (box,
                                                       box->file->tmp_umstimmung,
 		                                       NULL);
		}
#line 2165 "../../../mutabor-git/src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 92:
#line 563 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    {
			get_new_umstimmung (box);
		}
#line 2173 "../../../mutabor-git/src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 93:
#line 568 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    {
			init_umstimmung (box,(yyvsp[-4].identifier));
		        eintrage_parameterliste_in_umstimmung (box,
                                                       box->file->tmp_umstimmung,
 		                                       (yyvsp[-2].parameters));
		}
#line 2184 "../../../mutabor-git/src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 94:
#line 573 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    {
			get_new_umstimmung (box);
		}
#line 2192 "../../../mutabor-git/src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 95:
#line 578 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
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
#line 2207 "../../../mutabor-git/src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 96:
#line 587 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    {
			get_new_umstimmung (box);
		}
#line 2215 "../../../mutabor-git/src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 97:
#line 591 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
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
#line 2230 "../../../mutabor-git/src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 98:
#line 601 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { get_new_umstimmung (box); }
#line 2236 "../../../mutabor-git/src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 99:
#line 605 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    {}
#line 2242 "../../../mutabor-git/src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 100:
#line 606 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    {}
#line 2248 "../../../mutabor-git/src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 101:
#line 607 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    {}
#line 2254 "../../../mutabor-git/src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 102:
#line 608 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    {}
#line 2260 "../../../mutabor-git/src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 103:
#line 609 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    {}
#line 2266 "../../../mutabor-git/src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 104:
#line 610 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    {}
#line 2272 "../../../mutabor-git/src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 105:
#line 611 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    {}
#line 2278 "../../../mutabor-git/src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 106:
#line 612 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    {}
#line 2284 "../../../mutabor-git/src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 107:
#line 613 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    {}
#line 2290 "../../../mutabor-git/src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 108:
#line 614 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    {}
#line 2296 "../../../mutabor-git/src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 109:
#line 615 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    {
		mutabor_error_message(box,
				      compiler_error,
				      _("Bad retuning in line %d."),
				      FEHLERZEILE);
	  }
#line 2307 "../../../mutabor-git/src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 110:
#line 626 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { get_umstimmung_taste_abs (box, (yyvsp[-2].arguments)); }
#line 2313 "../../../mutabor-git/src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 111:
#line 631 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { get_umstimmung_taste_rel (box, (yyvsp[-2].arguments), (yyvsp[-3].integer)); }
#line 2319 "../../../mutabor-git/src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 112:
#line 636 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { get_umstimmung_breite_abs (box, (yyvsp[-2].arguments)); }
#line 2325 "../../../mutabor-git/src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 113:
#line 641 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { get_umstimmung_breite_rel (box, (yyvsp[-2].arguments), (yyvsp[-3].integer)); }
#line 2331 "../../../mutabor-git/src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 114:
#line 646 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { init_umstimm_expression_list (box); }
#line 2337 "../../../mutabor-git/src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 115:
#line 648 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { get_umstimmung_tonhoehe_veraendert (box); }
#line 2343 "../../../mutabor-git/src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 116:
#line 655 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    {}
#line 2349 "../../../mutabor-git/src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 117:
#line 656 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    {}
#line 2355 "../../../mutabor-git/src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 118:
#line 658 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { init_komplex_ton_list(box);
		  get_new_umstimm_expression (box,NULL);
                   }
#line 2363 "../../../mutabor-git/src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 119:
#line 661 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    {}
#line 2369 "../../../mutabor-git/src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 120:
#line 665 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    {}
#line 2375 "../../../mutabor-git/src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 121:
#line 666 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    {}
#line 2381 "../../../mutabor-git/src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 122:
#line 671 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { init_komplex_ton_list(box);
		  get_new_umstimm_expression (box, NULL);
                   }
#line 2389 "../../../mutabor-git/src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 124:
#line 679 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { get_new_umstimm_expression (box,(yyvsp[0].identifier)); }
#line 2395 "../../../mutabor-git/src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 125:
#line 680 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { get_new_umstimm_expression (box, "@"); }
#line 2401 "../../../mutabor-git/src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 126:
#line 682 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { init_komplex_ton_list (box); }
#line 2407 "../../../mutabor-git/src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 127:
#line 684 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { get_new_umstimm_expression_positive (box, (yyvsp[-3].identifier)); }
#line 2413 "../../../mutabor-git/src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 128:
#line 685 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { init_komplex_ton_list (box); }
#line 2419 "../../../mutabor-git/src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 129:
#line 687 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { get_new_umstimm_expression_positive (box, "@" ); }
#line 2425 "../../../mutabor-git/src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 130:
#line 688 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { init_komplex_ton_list (box); }
#line 2431 "../../../mutabor-git/src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 131:
#line 690 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { get_new_umstimm_expression_negative (box,(yyvsp[-3].identifier)); }
#line 2437 "../../../mutabor-git/src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 132:
#line 691 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { init_komplex_ton_list (box); }
#line 2443 "../../../mutabor-git/src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 133:
#line 693 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { get_new_umstimm_expression_negative (box, "@" ); }
#line 2449 "../../../mutabor-git/src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 134:
#line 698 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { init_komplex_ton_list (box); }
#line 2455 "../../../mutabor-git/src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 135:
#line 700 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { get_umstimmung_wiederholung_abs (box); }
#line 2461 "../../../mutabor-git/src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 136:
#line 701 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { init_komplex_ton_list (box); }
#line 2467 "../../../mutabor-git/src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 137:
#line 703 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { get_umstimmung_wiederholung_abs_negative (box); }
#line 2473 "../../../mutabor-git/src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 138:
#line 707 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { init_komplex_ton_list (box); }
#line 2479 "../../../mutabor-git/src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 139:
#line 709 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { get_umstimmung_wiederholung_rel_positive (box); }
#line 2485 "../../../mutabor-git/src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 140:
#line 710 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { init_komplex_ton_list (box); }
#line 2491 "../../../mutabor-git/src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 141:
#line 712 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { get_umstimmung_wiederholung_rel_negative (box); }
#line 2497 "../../../mutabor-git/src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 142:
#line 716 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { init_aktions_liste (box); }
#line 2503 "../../../mutabor-git/src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 143:
#line 718 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { get_umstimmung_umstimmungs_bund (box); }
#line 2509 "../../../mutabor-git/src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 144:
#line 722 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    {}
#line 2515 "../../../mutabor-git/src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 145:
#line 723 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    {}
#line 2521 "../../../mutabor-git/src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 146:
#line 727 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    {
		  get_new_aktion_aufruf_element (box,(yyvsp[0].identifier),NULL);
	  }
#line 2529 "../../../mutabor-git/src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 147:
#line 731 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { get_new_aktion_aufruf_element (box,(yyvsp[-3].identifier), (yyvsp[-1].arguments)); }
#line 2535 "../../../mutabor-git/src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 148:
#line 733 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { get_new_aktion_aufruf_element (box,(yyvsp[-4].identifier), (yyvsp[-2].arguments));
			    mutabor_error_message(box,
						 compiler_error,
						 _("Invalid argument list for call to %s in line %d"),
						 (yyvsp[-4].identifier),
						 FEHLERZEILE);
		    }
#line 2547 "../../../mutabor-git/src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 149:
#line 741 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { init_integersequenz (box);}
#line 2553 "../../../mutabor-git/src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 150:
#line 743 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { get_new_aktion_midi_out_element (box); }
#line 2559 "../../../mutabor-git/src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 151:
#line 744 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { get_new_aktion_harmony_analysis(box); }
#line 2565 "../../../mutabor-git/src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 152:
#line 748 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { init_umstimmungs_case_liste (box); }
#line 2571 "../../../mutabor-git/src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 153:
#line 750 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { get_umstimmung_umstimm_case (box,(yyvsp[-4].arguments)); }
#line 2577 "../../../mutabor-git/src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 154:
#line 754 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    {}
#line 2583 "../../../mutabor-git/src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 155:
#line 755 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    {}
#line 2589 "../../../mutabor-git/src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 156:
#line 760 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { init_aktions_liste (box); }
#line 2595 "../../../mutabor-git/src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 157:
#line 762 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { get_umstimmungs_case_zahl_element (box,(yyvsp[-4].integer)); }
#line 2601 "../../../mutabor-git/src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 158:
#line 764 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { init_aktions_liste (box); }
#line 2607 "../../../mutabor-git/src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 159:
#line 766 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { get_umstimmungs_case_zahl_element (box,-((yyvsp[-4].integer))); }
#line 2613 "../../../mutabor-git/src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 160:
#line 768 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { init_aktions_liste (box); }
#line 2619 "../../../mutabor-git/src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 161:
#line 770 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { get_umstimmungs_case_default_element (box); }
#line 2625 "../../../mutabor-git/src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 162:
#line 775 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { init_integersequenz (box);}
#line 2631 "../../../mutabor-git/src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 163:
#line 777 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { get_umstimmung_midi_out (box); }
#line 2637 "../../../mutabor-git/src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 164:
#line 782 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    {}
#line 2643 "../../../mutabor-git/src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 165:
#line 786 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    {}
#line 2649 "../../../mutabor-git/src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 166:
#line 787 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    {}
#line 2655 "../../../mutabor-git/src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 167:
#line 792 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { init_tastenliste (box); }
#line 2661 "../../../mutabor-git/src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 168:
#line 794 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { get_new_harmonie (box, (yyvsp[-6].identifier), (yyvsp[0].integer)); }
#line 2667 "../../../mutabor-git/src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 169:
#line 796 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    {
		mutabor_error_message(box,
				      compiler_error,
				      _("Bad pattern declaration “%s” at line %d"),
				      ((yyvsp[-2].identifier)),
				      FEHLERZEILE);
	  }
#line 2679 "../../../mutabor-git/src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 170:
#line 806 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { (yyval.integer) = -1; }
#line 2685 "../../../mutabor-git/src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 171:
#line 807 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { (yyval.integer) = (yyvsp[0].integer); }
#line 2691 "../../../mutabor-git/src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 172:
#line 811 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    {}
#line 2697 "../../../mutabor-git/src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 173:
#line 812 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    {}
#line 2703 "../../../mutabor-git/src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 174:
#line 816 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { get_new_taste (box, (yyvsp[0].integer), '+'); }
#line 2709 "../../../mutabor-git/src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 175:
#line 817 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { get_new_taste (box, (yyvsp[0].integer), '*'); }
#line 2715 "../../../mutabor-git/src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 176:
#line 821 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    {}
#line 2721 "../../../mutabor-git/src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 177:
#line 825 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    {}
#line 2727 "../../../mutabor-git/src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 178:
#line 826 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { init_ausloeser (box);
                         /* f〉 die Anfangsausloesung der Logik */
                       }
#line 2735 "../../../mutabor-git/src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 179:
#line 829 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    {}
#line 2741 "../../../mutabor-git/src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 180:
#line 834 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { get_new_logik (box, (yyvsp[-3].identifier), NULL);
                init_anweisungs_liste (box); }
#line 2748 "../../../mutabor-git/src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 181:
#line 837 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { vervollstaendige_logik (box); }
#line 2754 "../../../mutabor-git/src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 182:
#line 839 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { get_new_logik (box, (yyvsp[-4].identifier), (yyvsp[-1].identifier));
                init_anweisungs_liste (box); }
#line 2761 "../../../mutabor-git/src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 183:
#line 842 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { vervollstaendige_logik (box); }
#line 2767 "../../../mutabor-git/src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 184:
#line 846 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    {}
#line 2773 "../../../mutabor-git/src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 185:
#line 847 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    {}
#line 2779 "../../../mutabor-git/src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 186:
#line 852 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { init_aktions_liste (box); }
#line 2785 "../../../mutabor-git/src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 187:
#line 854 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { get_new_anweisung (box); }
#line 2791 "../../../mutabor-git/src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 188:
#line 856 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { init_aktions_liste (box); }
#line 2797 "../../../mutabor-git/src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 189:
#line 858 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { get_new_anweisung (box); }
#line 2803 "../../../mutabor-git/src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 190:
#line 863 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { get_harmoniebezeichner (box,
                                  mutabor_harmony_bothkey,
				  (yyvsp[-4].integer), (yyvsp[-2].identifier),  (yyvsp[0].integer)); }
#line 2811 "../../../mutabor-git/src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 191:
#line 867 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { get_harmoniebezeichner (box,
                                  mutabor_harmony_postkey,
				  0, (yyvsp[-2].identifier),  (yyvsp[0].integer)); }
#line 2819 "../../../mutabor-git/src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 192:
#line 871 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { get_harmoniebezeichner (box,
				  mutabor_harmony_prekey,
				  (yyvsp[-2].integer), (yyvsp[0].identifier), 0); }
#line 2827 "../../../mutabor-git/src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 193:
#line 875 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { get_harmoniebezeichner (box,
				  mutabor_harmony_nokey,
				  0, (yyvsp[0].identifier), 0); }
#line 2835 "../../../mutabor-git/src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 194:
#line 881 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { get_ausloeser_default (box); }
#line 2841 "../../../mutabor-git/src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 195:
#line 882 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { get_ausloeser_harmonie (box); }
#line 2847 "../../../mutabor-git/src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 196:
#line 883 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { get_ausloeser_harmonie_form (box); }
#line 2853 "../../../mutabor-git/src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 197:
#line 884 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { get_ausloeser_taste (box,(yyvsp[0].identifier)); }
#line 2859 "../../../mutabor-git/src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 198:
#line 885 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { init_integersequenz (box); }
#line 2865 "../../../mutabor-git/src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 199:
#line 887 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { get_ausloeser_midi_in (box); }
#line 2871 "../../../mutabor-git/src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 200:
#line 892 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { get_new_integer_in_integersequenz (box,(yyvsp[0].integer));}
#line 2877 "../../../mutabor-git/src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 201:
#line 894 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { get_new_integer_in_integersequenz (box,(yyvsp[0].integer));}
#line 2883 "../../../mutabor-git/src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 202:
#line 895 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    {
		mutabor_error_message(box,
				      compiler_error,
				      _("Bad MIDI list in line %d"),
				      FEHLERZEILE );
	  }
#line 2894 "../../../mutabor-git/src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 203:
#line 905 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    {}
#line 2900 "../../../mutabor-git/src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 204:
#line 909 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    {}
#line 2906 "../../../mutabor-git/src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 205:
#line 910 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    {}
#line 2912 "../../../mutabor-git/src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 206:
#line 915 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { get_instrument_dekl (box, (yyvsp[-3].integer), (yyvsp[0].integer), (yyvsp[0].integer), 0, & box->file->list_of_instrumente); }
#line 2918 "../../../mutabor-git/src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 207:
#line 917 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { get_instrument_dekl (box, (yyvsp[-5].integer), (yyvsp[-2].integer), (yyvsp[0].integer), 0, & box->file->list_of_instrumente); }
#line 2924 "../../../mutabor-git/src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 208:
#line 919 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { get_instrument_dekl (box, (yyvsp[-5].integer), 0, 0, (yyvsp[-1].integer), & box->file->list_of_instrumente); }
#line 2930 "../../../mutabor-git/src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 209:
#line 921 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { get_instrument_dekl (box, (yyvsp[-6].integer), (yyvsp[-3].integer), (yyvsp[-3].integer), (yyvsp[-1].integer), & box->file->list_of_instrumente); }
#line 2936 "../../../mutabor-git/src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 210:
#line 923 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { get_instrument_dekl (box, (yyvsp[-8].integer), (yyvsp[-5].integer), (yyvsp[-3].integer), (yyvsp[-1].integer), & box->file->list_of_instrumente); }
#line 2942 "../../../mutabor-git/src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 211:
#line 927 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { (yyval.f_value) = (yyvsp[0].f_value) ; }
#line 2948 "../../../mutabor-git/src/kernel/mut.cc" /* yacc.c:1646  */
    break;

  case 212:
#line 928 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1646  */
    { (yyval.f_value) = (double) (yyvsp[0].integer) ; }
#line 2954 "../../../mutabor-git/src/kernel/mut.cc" /* yacc.c:1646  */
    break;


#line 2958 "../../../mutabor-git/src/kernel/mut.cc" /* yacc.c:1646  */
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
#line 932 "../../../mutabor-git/src/kernel/mut.yy" /* yacc.c:1906  */

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

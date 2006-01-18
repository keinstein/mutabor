
/*  A Bison parser, made from mut.y  */

#define	IDENTIFIER	258
#define	F_NUMBER	259
#define	INTEGER	260
#define	INTERVALL	261
#define	WURZEL	262
#define	TON	263
#define	TONSYSTEM	264
#define	UMSTIMMUNG	265
#define	HARMONIE	266
#define	LOGIK	267
#define	FORM	268
#define	INSTRUMENT	269
#define	TASTE	270
#define	MIDI_IN	271
#define	MIDI_OUT	272
#define	ANSONSTEN	273

#line 3 "mut.y"


/* BEGIN MUT_TAB.C */

/* MUTABOR / Version 2.1 */

#pragma warn -cln
#pragma warn -aus
#pragma warn -sig
#pragma warn -par

#include <ctype.h>
#include <limits.h>
#include "Global.h"
#include "GrafKern.h"
#include "Hilfs.h"

#define MAX_IDENTIFIER_LEN 80

#define FEHLERZEILE yylloc.first_line+1

#define alloca xmalloc
#define YYMAXLIMIT (HEAP_PORTION_SYNTAX / sizeof(YYLTYPE) - 1)
                   /* wegen fehlendem alloca in PUREC */


#line 30 "mut.y"
typedef union {
    double      f_value;        /* fÅr Gleitkommazahlen */
    int         integer;        /* FÅr integers */
    char        *identifier;    /* FÅr Namen */
} YYSTYPE;

#ifndef YYLTYPE
typedef
  struct yyltype
    {
      int timestamp;
      int first_line;
      int first_column;
      int last_line;
      int last_column;
      char *text;
   }
  yyltype;

#define YYLTYPE yyltype
#endif

#include <stdio.h>

#ifndef __STDC__
#define const
#endif



#define	YYFINAL		376
#define	YYFLAG		-32768
#define	YYNTBASE	37

#define YYTRANSLATE(x) ((unsigned)(x) <= 273 ? yytranslate[x] : 134)

static const char yytranslate[] = {     0,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,    27,
    28,    32,    22,    26,    21,    35,    23,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,    20,     2,    30,
    19,    31,     2,    29,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
    24,     2,    25,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,    33,     2,    34,    36,     2,     2,     2,     2,
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
     2,     2,     2,     2,     2,     1,     2,     3,     4,     5,
     6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
    16,    17,    18
};

static const short yyrline[] = {     0,
    61,    62,    63,    64,    65,    66,    67,    68,    69,    72,
    75,    77,    80,    82,    84,    91,   100,   102,   103,   106,
   109,   111,   114,   116,   118,   122,   126,   130,   134,   137,
   142,   144,   146,   150,   153,   156,   159,   165,   171,   177,
   197,   206,   209,   215,   240,   243,   245,   248,   250,   252,
   256,   257,   259,   263,   263,   265,   267,   268,   271,   273,
   275,   279,   281,   282,   285,   288,   289,   294,   297,   299,
   302,   306,   308,   309,   313,   316,   319,   321,   322,   323,
   324,   325,   326,   327,   328,   329,   330,   334,   337,   341,
   344,   346,   348,   352,   355,   359,   362,   364,   366,   368,
   370,   372,   374,   378,   381,   388,   390,   392,   395,   398,
   400,   403,   408,   412,   414,   416,   418,   419,   421,   422,
   424,   425,   427,   431,   434,   435,   436,   440,   443,   444,
   446,   449,   451,   455,   457,   460,   463,   464,   466,   468,
   472,   474,   476,   477,   481,   483,   486,   490,   491,   494,
   495,   498,   501,   504,   509,   513,   515,   518,   521,   524,
   527,   529,   532,   534,   537,   539,   542,   546,   548,   551,
   554,   558,   560,   563,   567,   569,   573,   575,   577,   580,
   583,   586,   588,   590,   594,   596,   597,   598,   599,   600,
   604,   607,   609,   613,   617,   619,   622,   625,   627,   629,
   631,   635,   637
};

static const char * const yytname[] = {     0,
"error","$illegal.","IDENTIFIER","F_NUMBER","INTEGER","INTERVALL","WURZEL","TON","TONSYSTEM","UMSTIMMUNG",
"HARMONIE","LOGIK","FORM","INSTRUMENT","TASTE","MIDI_IN","MIDI_OUT","ANSONSTEN","'='","':'",
"'-'","'+'","'/'","'['","']'","','","'('","')'","'@'","'<'",
"'>'","'*'","'{'","'}'","'.'","'~'","start"
};

static const short yyr1[] = {     0,
    37,    37,    37,    37,    37,    37,    37,    37,    37,    38,
    39,    39,    41,    40,    42,    42,    42,    42,    42,    43,
    44,    44,    46,    45,    47,    47,    47,    47,    47,    48,
    49,    49,    50,    50,    50,    50,    50,    50,    50,    50,
    51,    51,    51,    51,    52,    53,    53,    55,    54,    57,
    56,    58,    56,    59,    59,    60,    60,    60,    61,    61,
    61,    62,    62,    62,    63,    63,    63,    64,    65,    65,
    67,    68,    66,    69,    70,    66,    71,    71,    71,    71,
    71,    71,    71,    71,    71,    71,    71,    72,    72,    73,
    73,    73,    73,    74,    74,    75,    75,    75,    75,    75,
    75,    75,    75,    77,    76,    78,    78,    79,    78,    80,
    80,    81,    81,    82,    82,    83,    82,    84,    82,    85,
    82,    86,    82,    88,    87,    89,    87,    91,    90,    92,
    90,    94,    93,    95,    95,    96,    97,    96,    98,    96,
   100,    99,   101,    99,   102,   102,   104,   103,   105,   103,
   106,   103,   108,   107,   109,   110,   110,   112,   111,   111,
   113,   113,   114,   114,   115,   115,   116,   117,   118,   117,
   120,   119,   121,   119,   122,   122,   124,   123,   125,   123,
   126,   126,   126,   126,   127,   127,   127,   127,   128,   127,
   129,   129,   129,   130,   131,   131,   132,   132,   132,   132,
   132,   133,   133
};

static const short yyr2[] = {     0,
     0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     0,     2,     0,     2,     5,     5,     3,     3,     2,     2,
     0,     2,     0,     2,     3,     5,     3,     5,     3,     2,
     0,     2,     2,     2,     3,     3,     4,     4,     5,     5,
     1,     2,     3,     4,     2,     0,     2,     0,     2,     0,
     8,     0,     9,     1,     3,     1,     0,     1,     1,     3,
     1,     1,     3,     1,     1,     1,     2,     2,     0,     2,
     0,     0,     5,     0,     0,     8,     1,     1,     1,     1,
     1,     1,     1,     1,     1,     1,     1,     3,     3,     5,
     5,     5,     5,     7,     7,     9,     9,     9,     9,     9,
     9,     9,     9,     0,     4,     1,     3,     0,     3,     1,
     3,     0,     1,     1,     1,     0,     4,     0,     4,     0,
     4,     0,     4,     0,     4,     0,     5,     0,     6,     0,
     6,     0,     4,     1,     3,     1,     0,     5,     0,     5,
     0,     5,     0,     5,     1,     2,     0,     5,     0,     6,
     0,     5,     0,     5,     2,     0,     2,     0,     7,     3,
     0,     2,     1,     3,     1,     2,     2,     0,     0,     3,
     0,     7,     0,     8,     0,     2,     0,     7,     0,     5,
     5,     3,     3,     1,     1,     1,     2,     2,     0,     5,
     1,     3,     1,     2,     0,     2,     4,     6,     6,     7,
     9,     1,     1
};

static const short yydefact[] = {     1,
     0,     9,    11,    21,    46,    69,   156,   168,   195,     2,
     3,     4,     5,     6,     7,     8,    10,    20,    45,    68,
   155,   167,   194,    12,     0,    22,     0,    47,     0,    71,
    70,     0,   157,     0,     0,   196,     0,    14,     0,    24,
     0,    49,     0,     0,     0,     0,   170,     0,    19,     0,
     0,     0,    72,     0,   160,   158,   184,     0,     0,     0,
     0,   185,   186,     0,     0,    18,    41,   202,   203,     0,
    17,    31,     0,    29,    27,    25,     0,     0,    61,    59,
     0,     0,     0,     0,   187,   188,   189,     0,   197,     0,
     0,    30,    42,     0,     0,     0,     0,     0,     0,    87,
     0,     0,     0,   104,     0,   132,    73,    77,    78,    79,
    80,    81,    82,    83,    84,    85,    86,     0,     0,   165,
     0,     0,   163,   182,   183,     0,     0,   171,     0,     0,
     0,    43,     0,     0,    32,    16,    15,     0,    26,     0,
    28,    58,    56,     0,    54,     0,   143,     0,   141,   153,
   124,     0,     0,     0,     0,     0,    60,    75,   166,     0,
   161,     0,   193,   191,     0,   173,   175,   198,     0,   199,
    34,     0,     0,    33,     0,     0,    44,    50,     0,    89,
     0,    88,     0,     0,     0,     0,     0,     0,   114,   108,
   115,     0,   106,     0,     0,     0,     0,   136,     0,     0,
   134,     0,   164,     0,   159,   181,     0,   190,   175,     0,
     0,   200,     0,    36,     0,     0,    35,     0,     0,     0,
    55,     0,     0,     0,     0,   145,     0,     0,   130,   128,
   125,     0,     0,     0,     0,   120,   116,   112,   122,   118,
   105,   112,     0,     0,     0,     0,   137,   139,     0,   133,
    76,   162,   192,     0,   172,   176,     0,     0,    38,     0,
    37,     0,    51,     0,     0,     0,     0,   144,   146,   142,
   154,     0,     0,   127,     0,     0,     0,     0,     0,     0,
     0,     0,   109,   110,   113,     0,     0,   107,    93,    92,
    91,    90,     0,     0,   135,   174,     0,   201,    40,    39,
    53,   147,   151,     0,   131,   129,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,   121,   117,   112,   123,
   119,    64,    65,    66,     0,     0,    62,     0,   179,     0,
     0,   149,    95,    94,     0,     0,     0,     0,     0,     0,
     0,     0,   111,    67,     0,   138,   140,   177,     0,   148,
   152,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    63,     0,   180,   150,    99,    98,    97,    96,   103,   102,
   101,   100,     0,   178,     0,     0
};

static const short yydefgoto[] = {     1,
    10,    17,    24,    25,    38,    11,    18,    26,    27,    40,
    71,    92,   135,    72,    12,    19,    28,    29,    42,   219,
   220,   144,   145,    81,   326,   327,    13,    20,    31,    43,
    78,    44,   202,   107,   108,   109,   110,   111,   112,   153,
   192,   238,   283,   284,   285,   282,   287,   281,   286,   113,
   186,   187,   114,   273,   272,   115,   156,   200,   201,   293,
   294,   116,   183,   181,   225,   226,   330,   352,   331,   117,
   184,    14,    21,    33,    82,   205,   122,   123,    15,    22,
    34,    47,   167,   209,   210,   256,   362,   349,    63,   257,
   126,   165,    16,    23,    36,   140
};

static const short yypact[] = {-32768,
   138,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,    13,    95,   111,   133,
   163,   166,   177,-32768,   197,-32768,   201,-32768,   206,   160,
-32768,   191,-32768,   216,   199,-32768,    66,-32768,   202,-32768,
   203,-32768,   204,   200,     6,   127,-32768,   193,-32768,    72,
   115,   220,-32768,    56,-32768,-32768,   195,   205,   153,   223,
   207,-32768,-32768,   209,    83,-32768,-32768,-32768,-32768,   198,
-32768,-32768,    76,-32768,   184,-32768,   208,     5,-32768,-32768,
   134,     4,   224,   227,-32768,-32768,-32768,    11,   113,   228,
   232,   186,-32768,   198,   198,   198,    77,    77,    29,-32768,
    -7,    37,   210,   -12,   190,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,   233,   219,-32768,
   234,    89,-32768,-32768,   211,    92,   218,-32768,   235,   238,
   221,-32768,    87,    98,-32768,-32768,-32768,   241,-32768,    18,
-32768,-32768,-32768,   148,-32768,   225,-32768,   226,-32768,-32768,
   112,   215,    16,   158,   167,   114,-32768,-32768,-32768,     4,
   213,   244,-32768,-32768,   151,-32768,-32768,   229,   230,-32768,
-32768,   198,    61,-32768,   198,    71,-32768,   231,    29,-32768,
   108,-32768,   108,    92,   192,    77,   236,    22,   194,-32768,
   196,   237,   239,   240,   242,   243,   245,   246,   247,   125,
-32768,     5,-32768,   249,-32768,-32768,   251,-32768,-32768,    47,
   253,-32768,   256,-32768,   198,   257,-32768,   198,    77,   250,
-32768,   254,   255,   258,    10,-32768,    19,   152,-32768,-32768,
-32768,    77,   248,   252,   132,-32768,-32768,    17,-32768,-32768,
-32768,    17,   259,   260,   261,   262,-32768,-32768,   114,-32768,
-32768,-32768,-32768,    53,-32768,-32768,   267,   264,-32768,   265,
-32768,   269,-32768,    77,   263,   266,   270,-32768,-32768,-32768,
-32768,    77,    77,-32768,   268,   271,   178,   183,   188,   189,
    77,    77,   272,-32768,-32768,    77,    77,   272,-32768,-32768,
-32768,-32768,   103,    92,-32768,-32768,   273,-32768,-32768,-32768,
-32768,-32768,-32768,   274,-32768,-32768,   275,   276,   277,   278,
   279,   280,   281,   282,   283,   284,-32768,-32768,    17,-32768,
-32768,-32768,-32768,-32768,   285,   169,-32768,   170,   286,   114,
   114,-32768,-32768,-32768,   287,   289,   290,   291,   292,   293,
   294,   295,-32768,-32768,   106,-32768,-32768,-32768,   114,   301,
   301,   114,   303,   304,   305,   306,   307,   308,   309,   310,
-32768,   114,-32768,   301,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,   131,-32768,   296,-32768
};

static const short yypgoto[] = {-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
   -97,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,    82,-32768,-32768,   -75,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,    75,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,    36,   -39,   128,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,  -319,  -244,-32768,
-32768,-32768,-32768,-32768,    99,   -26,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,   135,-32768,-32768,
-32768,-32768,-32768,-32768,    84,-32768,-32768,-32768,   288,   297,
-32768,  -182,-32768,-32768,-32768,   -47
};


#define	YYLAST		347


static const short yytable[] = {   139,
   141,   228,    73,    76,   295,   100,    55,   101,   120,   102,
   350,   351,   151,   127,   222,   -13,   146,   152,   189,   189,
    93,   103,    91,   222,   233,   147,   234,   223,   104,   142,
   224,   143,   364,   105,   128,   121,   223,   106,    56,   224,
    96,   190,   373,   268,   191,   191,   136,   137,   138,    57,
   235,    58,   270,   -57,   -57,    57,    79,    58,    80,    59,
   148,    60,    61,   214,    62,    59,    49,    60,    61,   149,
    62,   255,    66,   217,    67,    68,    69,   296,    93,    67,
    68,    69,    94,   215,    50,   173,   176,    89,   231,   171,
    68,    69,   163,   218,    70,    95,   164,   -23,    96,    70,
   174,    68,    69,   322,   363,   323,    90,   324,   323,   172,
   324,   328,   222,   -48,   160,    74,   198,    75,    68,    69,
   175,   263,   161,   325,   213,   223,   325,   216,   224,    57,
   199,    58,  -126,   129,   274,    30,   130,   375,     2,    59,
   185,    60,    61,     3,    62,     4,     5,     6,     7,     8,
   249,     9,   277,   278,   279,    57,   249,    58,   250,   118,
   194,   119,   195,   280,   374,    32,   301,   260,  -169,   196,
   262,   197,   178,   179,   305,   306,   207,   207,   208,   271,
   309,    35,   310,   317,   318,   311,   -74,   312,   320,   321,
   313,   315,   314,   316,   345,   207,   346,   347,   269,    37,
   269,    68,    69,    39,    97,    98,   133,   134,    41,    45,
   154,   155,   229,   230,   236,   237,   239,   240,    46,    48,
    51,    52,    53,    65,    77,    86,    54,    88,   124,   125,
    83,    99,   131,    87,   132,   157,   150,   158,   159,   168,
    84,   166,   169,   177,   188,   170,   162,   204,   206,   180,
   182,   -52,   211,   252,   212,   253,   232,   258,   259,   261,
   221,   241,   267,   243,   242,   244,   245,   299,   246,   361,
   264,   300,   247,   248,   265,   266,   251,   288,   275,   343,
   193,   227,   276,   289,   290,   291,   292,   297,   298,   344,
   304,     0,   254,   302,   203,   376,   303,   319,   307,   333,
   334,   308,     0,   329,   332,     0,     0,   335,   336,   337,
   338,   339,   340,   341,   342,     0,     0,   353,   348,   354,
   355,   356,   357,   358,   359,   360,   249,   365,   366,   367,
   368,   369,   370,   371,   372,     0,     0,     0,     0,     0,
     0,     0,    64,     0,     0,     0,    85
};

static const short yycheck[] = {    97,
    98,   184,    50,    51,   249,     1,     1,     3,     5,     5,
   330,   331,    25,     3,     5,     3,    24,    30,     3,     3,
     3,    17,    70,     5,     3,    33,     5,    18,    24,     1,
    21,     3,   352,    29,    24,    32,    18,    33,    33,    21,
    23,    26,   362,    34,    29,    29,    94,    95,    96,     3,
    29,     5,    34,    25,    26,     3,     1,     5,     3,    13,
    24,    15,    16,     3,    18,    13,     1,    15,    16,    33,
    18,    25,     1,     3,     3,     4,     5,    25,     3,     3,
     4,     5,     7,    23,    19,   133,   134,     5,   186,     3,
     4,     5,     1,    23,    23,    20,     5,     3,    23,    23,
     3,     4,     5,     1,   349,     3,    24,     5,     3,    23,
     5,   294,     5,     3,    26,     1,     3,     3,     4,     5,
    23,   219,    34,    21,   172,    18,    21,   175,    21,     3,
    17,     5,    21,    21,   232,     3,    24,     0,     1,    13,
    29,    15,    16,     6,    18,     8,     9,    10,    11,    12,
    26,    14,    21,    22,    23,     3,    26,     5,    34,    26,
     3,    28,     5,    32,    34,     3,   264,   215,     3,     3,
   218,     5,    25,    26,   272,   273,    26,    26,    28,    28,
     3,     5,     5,   281,   282,     3,    27,     5,   286,   287,
     3,     3,     5,     5,    26,    26,    28,    28,   225,     3,
   227,     4,     5,     3,    21,    22,    21,    22,     3,    19,
    21,    22,    21,    22,    21,    22,    21,    22,     3,    21,
    19,    19,    19,    31,     5,     3,    27,    19,     5,     3,
    36,    24,     5,    27,     3,     3,    27,    19,     5,     5,
    36,    24,     5,     3,    30,    25,    36,    35,     5,    25,
    25,    21,    24,     5,    25,     5,    21,     5,     3,     3,
   179,    25,     5,    24,    26,    24,    24,     3,    24,   345,
    21,     3,    27,    27,    21,    21,   202,   242,    31,   319,
   153,   183,    31,    25,    25,    25,    25,    21,    25,     5,
    21,    -1,   209,    31,   160,     0,    31,    26,    31,    25,
    25,    31,    -1,    31,    31,    -1,    -1,    31,    31,    31,
    31,    31,    31,    31,    31,    -1,    -1,    31,    33,    31,
    31,    31,    31,    31,    31,    31,    26,    25,    25,    25,
    25,    25,    25,    25,    25,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    46,    -1,    -1,    -1,    59
};
#define YYPURE 1

/* -*-C-*-  Note some compilers choke on comments on `#line' lines.  */
#line 3 "bison.simple"

/* Skeleton output parser for bison,
   Copyright (C) 1984 Bob Corbett and Richard Stallman

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 1, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.  */


#if (!defined (__STDC__) && defined (sparc)) || defined (__sparc__)
#include <alloca.h>
#endif

/* This is the parser code that is written into each bison parser
  when the %semantic_parser declaration is not specified in the grammar.
  It was written by Richard Stallman by simplifying the hairy parser
  used when %semantic_parser is specified.  */

/* Note: there must be only one dollar sign in this file.
   It is replaced by the list of actions, each action
   as one case of the switch.  */

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		-2
#define YYEOF		0
#define YYFAIL		goto yyerrlab;
#define YYACCEPT	return(0)
#define YYABORT 	return(1)
#define YYERROR		goto yyerrlab

#define YYTERROR	1
#define YYERRCODE	256

#ifndef YYIMPURE
#define YYLEX		yylex()
#endif

#ifndef YYPURE
#define YYLEX		yylex(&yylval, &yylloc)
#endif

/* If nonreentrant, generate the variables here */

#ifndef YYIMPURE

int	yychar;			/*  the lookahead symbol		*/
YYSTYPE	yylval;			/*  the semantic value of the		*/
				/*  lookahead symbol			*/

YYLTYPE yylloc;			/*  location data for the lookahead	*/
				/*  symbol				*/

int yynerrs;			/*  number of parse errors so far       */
#endif  /* YYIMPURE */

#if YYDEBUG != 0
int yydebug;			/*  nonzero means print parse trace	*/
/* Since this is uninitialized, it does not stop multiple parsers
   from coexisting.  */
#endif

/*  YYMAXDEPTH indicates the initial size of the parser's stacks	*/

#ifndef	YYMAXDEPTH
#define YYMAXDEPTH 200
#endif

/*  YYMAXLIMIT is the maximum size the stacks can grow to
    (effective only if the built-in stack extension method is used).  */

#ifndef YYMAXLIMIT
#define YYMAXLIMIT 10000
#endif


#line 90 "bison.simple"
int
yyparse()
{
  register int yystate;
  register int yyn;
  register short *yyssp;
  register YYSTYPE *yyvsp;
  YYLTYPE *yylsp;
  int yyerrstatus;	/*  number of tokens to shift before error messages enabled */
  int yychar1;		/*  lookahead token as an internal (translated) token number */

  short	yyssa[YYMAXDEPTH];	/*  the state stack			*/
  YYSTYPE yyvsa[YYMAXDEPTH];	/*  the semantic value stack		*/
  YYLTYPE yylsa[YYMAXDEPTH];	/*  the location stack			*/

  short *yyss = yyssa;		/*  refer to the stacks thru separate pointers */
  YYSTYPE *yyvs = yyvsa;	/*  to allow yyoverflow to reallocate them elsewhere */
  YYLTYPE *yyls = yylsa;

  int yymaxdepth = YYMAXDEPTH;

#ifndef YYPURE
  int yychar;
  YYSTYPE yylval;
  YYLTYPE yylloc;
  int yynerrs;
#endif

  YYSTYPE yyval;		/*  the variable used to return		*/
				/*  semantic values from the action	*/
				/*  routines				*/

  int yylen;

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Starting parse\n");
#endif

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.  */

  yyssp = yyss - 1;
  yyvsp = yyvs;
  yylsp = yyls;

/* Push a new state, which is found in  yystate  .  */
/* In all cases, when you get here, the value and location stacks
   have just been pushed. so pushing a state here evens the stacks.  */
yynewstate:

  *++yyssp = yystate;

  if (yyssp >= yyss + yymaxdepth - 1)
    {
      /* Give user a chance to reallocate the stack */
      /* Use copies of these so that the &'s don't force the real ones into memory. */
      YYSTYPE *yyvs1 = yyvs;
      YYLTYPE *yyls1 = yyls;
      short *yyss1 = yyss;

      /* Get the current used size of the three stacks, in elements.  */
      int size = yyssp - yyss + 1;

#ifdef yyoverflow
      /* Each stack pointer address is followed by the size of
	 the data in use in that stack, in bytes.  */
      yyoverflow("parser stack overflow",
		 &yyss1, size * sizeof (*yyssp),
		 &yyvs1, size * sizeof (*yyvsp),
		 &yyls1, size * sizeof (*yylsp),
		 &yymaxdepth);

      yyss = yyss1; yyvs = yyvs1; yyls = yyls1;
#else /* no yyoverflow */
      /* Extend the stack our own way.  */
      if (yymaxdepth >= YYMAXLIMIT)
	yyerror("parser stack overflow");
      yymaxdepth *= 2;
      if (yymaxdepth > YYMAXLIMIT)
	yymaxdepth = YYMAXLIMIT;
      yyss = (short *) alloca (yymaxdepth * sizeof (*yyssp));
      bcopy ((char *)yyss1, (char *)yyss, size * sizeof (*yyssp));
      yyvs = (YYSTYPE *) alloca (yymaxdepth * sizeof (*yyvsp));
      bcopy ((char *)yyvs1, (char *)yyvs, size * sizeof (*yyvsp));
#ifdef YYLSP_NEEDED
      yyls = (YYLTYPE *) alloca (yymaxdepth * sizeof (*yylsp));
      bcopy ((char *)yyls1, (char *)yyls, size * sizeof (*yylsp));
#endif
#endif /* no yyoverflow */

      yyssp = yyss + size - 1;
      yyvsp = yyvs + size - 1;
#ifdef YYLSP_NEEDED
      yylsp = yyls + size - 1;
#endif

#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Stack size increased to %d\n", yymaxdepth);
#endif

      if (yyssp >= yyss + yymaxdepth - 1)
	YYABORT;
    }

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Entering state %d\n", yystate);
#endif

/* Do appropriate processing given the current state.  */
/* Read a lookahead token if we need one and don't already have one.  */
yyresume:

  /* First try to decide what to do without reference to lookahead token.  */

  yyn = yypact[yystate];
  if (yyn == YYFLAG)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* yychar is either YYEMPTY or YYEOF
     or a valid token in external form.  */

  if (yychar == YYEMPTY)
    {
#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Reading a token: ");
#endif
      yychar = YYLEX;
    }

  /* Convert token to internal form (in yychar1) for indexing tables with */

  if (yychar <= 0)		/* This means end of input. */
    {
      yychar1 = 0;
      yychar = YYEOF;		/* Don't call YYLEX any more */

#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Now at end of input.\n");
#endif
    }
  else
    {
      yychar1 = YYTRANSLATE(yychar);

#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Next token is %d (%s)\n", yychar, yytname[yychar1]);
#endif
    }

  yyn += yychar1;
  if (yyn < 0 || yyn > YYLAST || yycheck[yyn] != yychar1)
    goto yydefault;

  yyn = yytable[yyn];

  /* yyn is what to do for this token type in this state.
     Negative => reduce, -yyn is rule number.
     Positive => shift, yyn is new state.
       New state is final state => don't bother to shift,
       just return success.
     0, or most negative number => error.  */

  if (yyn < 0)
    {
      if (yyn == YYFLAG)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }
  else if (yyn == 0)
    goto yyerrlab;

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Shift the lookahead token.  */

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Shifting token %d (%s), ", yychar, yytname[yychar1]);
#endif

  /* Discard the token being shifted unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  *++yyvsp = yylval;
#ifdef YYLSP_NEEDED
  *++yylsp = yylloc;
#endif

  /* count tokens shifted since error; after three, turn off error status.  */
  if (yyerrstatus) yyerrstatus--;

  yystate = yyn;
  goto yynewstate;

/* Do the default action for the current state.  */
yydefault:

  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;

/* Do a reduction.  yyn is the number of a rule to reduce with.  */
yyreduce:
  yylen = yyr2[yyn];
  yyval = yyvsp[1-yylen]; /* implement default value of the action */

#if YYDEBUG != 0
  if (yydebug)
    {
      if (yylen == 1)
	fprintf (stderr, "Reducing 1 value via line %d, ",
		 yyrline[yyn]);
      else
	fprintf (stderr, "Reducing %d values via line %d, ",
		 yylen, yyrline[yyn]);
    }
#endif


  switch (yyn) {

case 9:
#line 69 "mut.y"
{ fatal_error(1,FEHLERZEILE); ;
    break;}
case 13:
#line 81 "mut.y"
{ init_komplex_ton_list (); ;
    break;}
case 15:
#line 86 "mut.y"
{ if ( fabs(yyvsp[0].f_value) > 0.001 )
                         get_new_intervall (yyvsp[-4].identifier, yyvsp[-2].f_value / yyvsp[0].f_value);
                      else
                         fatal_error (46, yyvsp[-4].identifier ); ;
    break;}
case 16:
#line 92 "mut.y"
{ if ( fabs (yyvsp[-2].f_value) > 0.001 )
                          get_new_intervall (yyvsp[-4].identifier, pow (yyvsp[0].f_value, 1 / yyvsp[-2].f_value));
                      else
                         fatal_error (46, yyvsp[-4].identifier); ;
    break;}
case 17:
#line 101 "mut.y"
{ get_new_intervall_komplex (yyvsp[-2].identifier); ;
    break;}
case 18:
#line 102 "mut.y"
{ fatal_error(71,yyvsp[-2].identifier); ;
    break;}
case 19:
#line 103 "mut.y"
{ fatal_error(70,"'='",FEHLERZEILE); ;
    break;}
case 23:
#line 115 "mut.y"
{ init_komplex_ton_list (); ;
    break;}
case 25:
#line 120 "mut.y"
{ get_new_ton_absolut (yyvsp[-2].identifier, yyvsp[0].f_value); ;
    break;}
case 26:
#line 124 "mut.y"
{ get_new_ton_komplex_negative (yyvsp[-4].identifier, yyvsp[-2].identifier); ;
    break;}
case 27:
#line 128 "mut.y"
{ get_new_ton_komplex_positive (yyvsp[-2].identifier, yyvsp[0].identifier); ;
    break;}
case 28:
#line 132 "mut.y"
{ get_new_ton_komplex_positive (yyvsp[-4].identifier, yyvsp[-2].identifier); ;
    break;}
case 29:
#line 134 "mut.y"
{ fatal_error( 72, yyvsp[-2].identifier ); ;
    break;}
case 33:
#line 148 "mut.y"
{ get_new_faktor_anteil ( (double) 1, yyvsp[0].identifier); ;
    break;}
case 34:
#line 151 "mut.y"
{ get_new_faktor_anteil ( (double) -1, yyvsp[0].identifier); ;
    break;}
case 35:
#line 154 "mut.y"
{ get_new_faktor_anteil ( yyvsp[-1].f_value, yyvsp[0].identifier); ;
    break;}
case 36:
#line 157 "mut.y"
{ get_new_faktor_anteil ( -(yyvsp[-1].f_value), yyvsp[0].identifier); ;
    break;}
case 37:
#line 160 "mut.y"
{ if ( fabs(yyvsp[-1].f_value) > 0.001 )
                       get_new_faktor_anteil ( (double) 1 / (yyvsp[-1].f_value), yyvsp[0].identifier);
                     else
                       fatal_error(53, FEHLERZEILE);  ;
    break;}
case 38:
#line 166 "mut.y"
{ if ( fabs(yyvsp[-1].f_value) > 0.001 )
                       get_new_faktor_anteil ( (double) -1 / (yyvsp[-1].f_value), yyvsp[0].identifier);
                     else
                       fatal_error(53, FEHLERZEILE);  ;
    break;}
case 39:
#line 172 "mut.y"
{ if ( fabs(yyvsp[-1].f_value) > 0.001 )
                       get_new_faktor_anteil ( (yyvsp[-3].f_value) / (yyvsp[-1].f_value), yyvsp[0].identifier);
                     else
                       fatal_error(53, FEHLERZEILE);  ;
    break;}
case 40:
#line 178 "mut.y"
{ if ( fabs(yyvsp[-1].f_value) > 0.001 )
                       get_new_faktor_anteil ( -(yyvsp[-3].f_value) / (yyvsp[-1].f_value), yyvsp[0].identifier);
                     else
                       fatal_error(53, FEHLERZEILE);  ;
    break;}
case 41:
#line 199 "mut.y"
{ get_new_faktor_anteil ( (double) 1.0 , yyvsp[0].identifier); ;
    break;}
case 42:
#line 207 "mut.y"
{ get_new_faktor_anteil ( yyvsp[-1].f_value, yyvsp[0].identifier); ;
    break;}
case 43:
#line 210 "mut.y"
{ if ( fabs(yyvsp[-1].f_value) > 0.001 )
                       get_new_faktor_anteil ( (double) 1 / (yyvsp[-1].f_value), yyvsp[0].identifier);
                     else
                       fatal_error(53, FEHLERZEILE);  ;
    break;}
case 44:
#line 216 "mut.y"
{ if ( fabs(yyvsp[-1].f_value) > 0.001 )
                       get_new_faktor_anteil ( (yyvsp[-3].f_value) / (yyvsp[-1].f_value), yyvsp[0].identifier);
                     else
                       fatal_error(53, FEHLERZEILE);  ;
    break;}
case 48:
#line 249 "mut.y"
{ init_ton_liste (); ;
    break;}
case 50:
#line 254 "mut.y"
{ init_komplex_ton_list (); ;
    break;}
case 51:
#line 256 "mut.y"
{ get_new_tonsystem (yyvsp[-7].identifier, yyvsp[-5].integer); ;
    break;}
case 52:
#line 258 "mut.y"
{ init_komplex_ton_list (); ;
    break;}
case 53:
#line 260 "mut.y"
{ get_new_tonsystem_negative (yyvsp[-8].identifier, yyvsp[-6].integer); ;
    break;}
case 56:
#line 266 "mut.y"
{ get_new_ton_in_tonsystem (yyvsp[0].identifier); ;
    break;}
case 57:
#line 267 "mut.y"
{ get_new_ton_in_tonsystem (NULL); ;
    break;}
case 58:
#line 268 "mut.y"
{ fatal_error(73,FEHLERZEILE); ;
    break;}
case 59:
#line 272 "mut.y"
{ get_new_name_in_parameterlist (yyvsp[0].identifier) ;
    break;}
case 60:
#line 274 "mut.y"
{ get_new_name_in_parameterlist (yyvsp[0].identifier) ;
    break;}
case 61:
#line 275 "mut.y"
{ fatal_error(74,FEHLERZEILE); ;
    break;}
case 62:
#line 280 "mut.y"
{;
    break;}
case 63:
#line 281 "mut.y"
{;
    break;}
case 64:
#line 282 "mut.y"
{ fatal_error(74,FEHLERZEILE); ;
    break;}
case 65:
#line 287 "mut.y"
{ get_new_name_in_argument_list (yyvsp[0].identifier)   ;
    break;}
case 66:
#line 288 "mut.y"
{ get_new_number_in_argument_list (yyvsp[0].integer) ;
    break;}
case 67:
#line 289 "mut.y"
{ get_new_number_in_argument_list (-(yyvsp[0].integer)) ;
    break;}
case 71:
#line 304 "mut.y"
{ init_umstimmung (yyvsp[0].identifier);
                      init_parameter_liste (); ;
    break;}
case 72:
#line 306 "mut.y"
{ eintrage_parameterliste_in_umstimmung (); ;
    break;}
case 73:
#line 308 "mut.y"
{ get_new_umstimmung (); ;
    break;}
case 74:
#line 311 "mut.y"
{ init_umstimmung (yyvsp[0].identifier);
                      init_parameter_liste (); ;
    break;}
case 75:
#line 314 "mut.y"
{ eintrage_parameterliste_in_umstimmung (); ;
    break;}
case 76:
#line 316 "mut.y"
{ get_new_umstimmung (); ;
    break;}
case 77:
#line 320 "mut.y"
{;
    break;}
case 78:
#line 321 "mut.y"
{;
    break;}
case 79:
#line 322 "mut.y"
{;
    break;}
case 80:
#line 323 "mut.y"
{;
    break;}
case 81:
#line 324 "mut.y"
{;
    break;}
case 82:
#line 325 "mut.y"
{;
    break;}
case 83:
#line 326 "mut.y"
{;
    break;}
case 84:
#line 327 "mut.y"
{;
    break;}
case 85:
#line 328 "mut.y"
{;
    break;}
case 86:
#line 329 "mut.y"
{;
    break;}
case 87:
#line 330 "mut.y"
{fatal_error(75,FEHLERZEILE);;
    break;}
case 88:
#line 336 "mut.y"
{ get_umstimmung_taste_abs (zahl, yyvsp[-2].integer, NULL); ;
    break;}
case 89:
#line 338 "mut.y"
{ get_umstimmung_taste_abs (parameter, 0.0, yyvsp[-2].identifier); ;
    break;}
case 90:
#line 343 "mut.y"
{ get_umstimmung_taste_rel (zahl, yyvsp[-2].integer, NULL, '+'); ;
    break;}
case 91:
#line 345 "mut.y"
{ get_umstimmung_taste_rel (parameter, 0.0, yyvsp[-2].identifier, '+'); ;
    break;}
case 92:
#line 347 "mut.y"
{ get_umstimmung_taste_rel (zahl, yyvsp[-2].integer, NULL, '-'); ;
    break;}
case 93:
#line 349 "mut.y"
{ get_umstimmung_taste_rel (parameter, 0.0, yyvsp[-2].identifier, '-'); ;
    break;}
case 94:
#line 354 "mut.y"
{ get_umstimmung_breite_abs (zahl, yyvsp[-3].integer, NULL); ;
    break;}
case 95:
#line 356 "mut.y"
{ get_umstimmung_breite_abs (parameter, 0.0, yyvsp[-3].identifier); ;
    break;}
case 96:
#line 361 "mut.y"
{ get_umstimmung_breite_rel (zahl, yyvsp[-3].integer, NULL, '+'); ;
    break;}
case 97:
#line 363 "mut.y"
{ get_umstimmung_breite_rel (parameter, 0.0, yyvsp[-3].identifier, '+'); ;
    break;}
case 98:
#line 365 "mut.y"
{ get_umstimmung_breite_rel (zahl, yyvsp[-3].integer, NULL, '-'); ;
    break;}
case 99:
#line 367 "mut.y"
{ get_umstimmung_breite_rel (parameter, 0.0, yyvsp[-3].identifier, '-'); ;
    break;}
case 100:
#line 369 "mut.y"
{ get_umstimmung_breite_rel (zahl, yyvsp[-3].integer, NULL, '*'); ;
    break;}
case 101:
#line 371 "mut.y"
{ get_umstimmung_breite_rel (parameter, 0.0, yyvsp[-3].identifier, '*'); ;
    break;}
case 102:
#line 373 "mut.y"
{ get_umstimmung_breite_rel (zahl, yyvsp[-3].integer, NULL, '/'); ;
    break;}
case 103:
#line 375 "mut.y"
{ get_umstimmung_breite_rel (parameter, 0.0, yyvsp[-3].identifier, '/'); ;
    break;}
case 104:
#line 380 "mut.y"
{ init_umstimm_expression_list (); ;
    break;}
case 105:
#line 382 "mut.y"
{ get_umstimmung_tonhoehe_veraendert (); ;
    break;}
case 106:
#line 389 "mut.y"
{;
    break;}
case 107:
#line 390 "mut.y"
{;
    break;}
case 108:
#line 392 "mut.y"
{ init_komplex_ton_list();
                     get_new_umstimm_expression (NULL);
                   ;
    break;}
case 109:
#line 395 "mut.y"
{;
    break;}
case 110:
#line 399 "mut.y"
{;
    break;}
case 111:
#line 400 "mut.y"
{;
    break;}
case 112:
#line 405 "mut.y"
{ init_komplex_ton_list();
                     get_new_umstimm_expression (NULL);
                   ;
    break;}
case 114:
#line 413 "mut.y"
{ get_new_umstimm_expression (yyvsp[0].identifier); ;
    break;}
case 115:
#line 414 "mut.y"
{ get_new_umstimm_expression ("@"); ;
    break;}
case 116:
#line 416 "mut.y"
{ init_komplex_ton_list (); ;
    break;}
case 117:
#line 418 "mut.y"
{ get_new_umstimm_expression_positive (yyvsp[-3].identifier); ;
    break;}
case 118:
#line 419 "mut.y"
{ init_komplex_ton_list (); ;
    break;}
case 119:
#line 421 "mut.y"
{ get_new_umstimm_expression_positive ( "@" ); ;
    break;}
case 120:
#line 422 "mut.y"
{ init_komplex_ton_list (); ;
    break;}
case 121:
#line 424 "mut.y"
{ get_new_umstimm_expression_negative (yyvsp[-3].identifier); ;
    break;}
case 122:
#line 425 "mut.y"
{ init_komplex_ton_list (); ;
    break;}
case 123:
#line 427 "mut.y"
{ get_new_umstimm_expression_negative ( "@" ); ;
    break;}
case 124:
#line 432 "mut.y"
{ init_komplex_ton_list (); ;
    break;}
case 125:
#line 434 "mut.y"
{ get_umstimmung_wiederholung_abs (); ;
    break;}
case 126:
#line 435 "mut.y"
{ init_komplex_ton_list (); ;
    break;}
case 127:
#line 437 "mut.y"
{ get_umstimmung_wiederholung_abs_negative (); ;
    break;}
case 128:
#line 441 "mut.y"
{ init_komplex_ton_list (); ;
    break;}
case 129:
#line 443 "mut.y"
{ get_umstimmung_wiederholung_rel_positive (); ;
    break;}
case 130:
#line 444 "mut.y"
{ init_komplex_ton_list (); ;
    break;}
case 131:
#line 446 "mut.y"
{ get_umstimmung_wiederholung_rel_negative (); ;
    break;}
case 132:
#line 450 "mut.y"
{ init_aktions_liste (); ;
    break;}
case 133:
#line 452 "mut.y"
{ get_umstimmung_umstimmungs_bund (); ;
    break;}
case 134:
#line 456 "mut.y"
{;
    break;}
case 135:
#line 457 "mut.y"
{;
    break;}
case 136:
#line 461 "mut.y"
{ init_argument_liste ();
                       get_new_aktion_aufruf_element (yyvsp[0].identifier); ;
    break;}
case 137:
#line 463 "mut.y"
{ init_argument_liste (); ;
    break;}
case 138:
#line 465 "mut.y"
{ get_new_aktion_aufruf_element (yyvsp[-4].identifier); ;
    break;}
case 139:
#line 467 "mut.y"
{ init_integersequenz ();;
    break;}
case 140:
#line 469 "mut.y"
{ get_new_aktion_midi_out_element (); ;
    break;}
case 141:
#line 473 "mut.y"
{ init_umstimmungs_case_liste (); ;
    break;}
case 142:
#line 475 "mut.y"
{ get_umstimmung_umstimm_case_zahl (yyvsp[-4].integer); ;
    break;}
case 143:
#line 476 "mut.y"
{ init_umstimmungs_case_liste (); ;
    break;}
case 144:
#line 478 "mut.y"
{ get_umstimmung_umstimm_case_parameter (yyvsp[-4].identifier); ;
    break;}
case 145:
#line 482 "mut.y"
{;
    break;}
case 146:
#line 483 "mut.y"
{;
    break;}
case 147:
#line 488 "mut.y"
{ init_aktions_liste (); ;
    break;}
case 148:
#line 490 "mut.y"
{ get_umstimmungs_case_zahl_element (yyvsp[-4].integer); ;
    break;}
case 149:
#line 492 "mut.y"
{ init_aktions_liste (); ;
    break;}
case 150:
#line 494 "mut.y"
{ get_umstimmungs_case_zahl_element (-(yyvsp[-4].integer)); ;
    break;}
case 151:
#line 496 "mut.y"
{ init_aktions_liste (); ;
    break;}
case 152:
#line 498 "mut.y"
{ get_umstimmungs_case_default_element (); ;
    break;}
case 153:
#line 503 "mut.y"
{ init_integersequenz ();;
    break;}
case 154:
#line 505 "mut.y"
{ get_umstimmung_midi_out (); ;
    break;}
case 155:
#line 510 "mut.y"
{;
    break;}
case 156:
#line 514 "mut.y"
{;
    break;}
case 157:
#line 515 "mut.y"
{;
    break;}
case 158:
#line 520 "mut.y"
{ init_tastenliste (); ;
    break;}
case 159:
#line 522 "mut.y"
{ get_new_harmonie (yyvsp[-6].identifier, yyvsp[0].integer); ;
    break;}
case 160:
#line 524 "mut.y"
{ fatal_error(76,yyvsp[-2].identifier); ;
    break;}
case 161:
#line 528 "mut.y"
{ yyval.integer = -1; ;
    break;}
case 162:
#line 529 "mut.y"
{ yyval.integer = yyvsp[0].integer; ;
    break;}
case 163:
#line 533 "mut.y"
{;
    break;}
case 164:
#line 534 "mut.y"
{;
    break;}
case 165:
#line 538 "mut.y"
{ get_new_taste ( yyvsp[0].integer, '+'); ;
    break;}
case 166:
#line 539 "mut.y"
{ get_new_taste ( yyvsp[0].integer, '*'); ;
    break;}
case 167:
#line 543 "mut.y"
{;
    break;}
case 168:
#line 547 "mut.y"
{;
    break;}
case 169:
#line 548 "mut.y"
{ init_ausloeser ();
                         /* fÅr die Anfangsausloesung der Logik */
                       ;
    break;}
case 170:
#line 551 "mut.y"
{;
    break;}
case 171:
#line 556 "mut.y"
{ get_new_logik (yyvsp[-3].identifier, NULL);
                init_anweisungs_liste (); ;
    break;}
case 172:
#line 559 "mut.y"
{ vervollstaendige_logik (); ;
    break;}
case 173:
#line 561 "mut.y"
{ get_new_logik (yyvsp[-4].identifier, yyvsp[-1].identifier);
                init_anweisungs_liste (); ;
    break;}
case 174:
#line 564 "mut.y"
{ vervollstaendige_logik (); ;
    break;}
case 175:
#line 568 "mut.y"
{;
    break;}
case 176:
#line 569 "mut.y"
{;
    break;}
case 177:
#line 574 "mut.y"
{ init_aktions_liste (); ;
    break;}
case 178:
#line 576 "mut.y"
{ get_new_anweisung (); ;
    break;}
case 179:
#line 578 "mut.y"
{ init_aktions_liste (); ;
    break;}
case 180:
#line 580 "mut.y"
{ get_new_anweisung (); ;
    break;}
case 181:
#line 585 "mut.y"
{ get_harmoniebezeichner (  yyvsp[-4].integer, yyvsp[-2].identifier,  yyvsp[0].integer); ;
    break;}
case 182:
#line 587 "mut.y"
{ get_harmoniebezeichner (-1, yyvsp[-2].identifier,  yyvsp[0].integer); ;
    break;}
case 183:
#line 589 "mut.y"
{ get_harmoniebezeichner (  yyvsp[-2].integer, yyvsp[0].identifier, -1); ;
    break;}
case 184:
#line 591 "mut.y"
{ get_harmoniebezeichner (-1, yyvsp[0].identifier, -1); ;
    break;}
case 185:
#line 595 "mut.y"
{ get_ausloeser_default (); ;
    break;}
case 186:
#line 596 "mut.y"
{ get_ausloeser_harmonie (); ;
    break;}
case 187:
#line 597 "mut.y"
{ get_ausloeser_harmonie_form (); ;
    break;}
case 188:
#line 598 "mut.y"
{ get_ausloeser_taste (yyvsp[0].identifier); ;
    break;}
case 189:
#line 599 "mut.y"
{ init_integersequenz (); ;
    break;}
case 190:
#line 601 "mut.y"
{ get_ausloeser_midi_in (); ;
    break;}
case 191:
#line 606 "mut.y"
{ get_new_integer_in_integersequenz (yyvsp[0].integer);;
    break;}
case 192:
#line 608 "mut.y"
{ get_new_integer_in_integersequenz (yyvsp[0].integer);;
    break;}
case 193:
#line 609 "mut.y"
{ fatal_error( 77, FEHLERZEILE ); ;
    break;}
case 194:
#line 614 "mut.y"
{;
    break;}
case 195:
#line 618 "mut.y"
{;
    break;}
case 196:
#line 619 "mut.y"
{;
    break;}
case 197:
#line 624 "mut.y"
{ get_instrument_dekl (yyvsp[-3].integer, yyvsp[0].integer, yyvsp[0].integer, 0, & list_of_instrumente); ;
    break;}
case 198:
#line 626 "mut.y"
{ get_instrument_dekl (yyvsp[-5].integer, yyvsp[-2].integer, yyvsp[0].integer, 0, & list_of_instrumente); ;
    break;}
case 199:
#line 628 "mut.y"
{ get_instrument_dekl (yyvsp[-5].integer, 0, 0, yyvsp[-1].integer, & list_of_instrumente); ;
    break;}
case 200:
#line 630 "mut.y"
{ get_instrument_dekl (yyvsp[-6].integer, yyvsp[-3].integer, yyvsp[-3].integer, yyvsp[-1].integer, & list_of_instrumente); ;
    break;}
case 201:
#line 632 "mut.y"
{ get_instrument_dekl (yyvsp[-8].integer, yyvsp[-5].integer, yyvsp[-3].integer, yyvsp[-1].integer, & list_of_instrumente); ;
    break;}
case 202:
#line 636 "mut.y"
{ yyval.f_value = yyvsp[0].f_value ;
    break;}
case 203:
#line 637 "mut.y"
{ yyval.f_value = (double) yyvsp[0].integer ;
    break;}
}
   /* the action file gets copied in in place of this dollarsign */
#line 327 "bison.simple"

  yyvsp -= yylen;
  yyssp -= yylen;
#ifdef YYLSP_NEEDED
  yylsp -= yylen;
#endif

#if YYDEBUG != 0
  if (yydebug)
    {
      short *ssp1 = yyss - 1;
      fprintf (stderr, "state stack now");
      while (ssp1 != yyssp)
	fprintf (stderr, " %d", *++ssp1);
      fprintf (stderr, "\n");
    }
#endif

  *++yyvsp = yyval;

#ifdef YYLSP_NEEDED
  yylsp++;
  if (yylen == 0)
    {
      yylsp->first_line = yylloc.first_line;
      yylsp->first_column = yylloc.first_column;
      yylsp->last_line = (yylsp-1)->last_line;
      yylsp->last_column = (yylsp-1)->last_column;
      yylsp->text = 0;
    }
  else
    {
      yylsp->last_line = (yylsp+yylen-1)->last_line;
      yylsp->last_column = (yylsp+yylen-1)->last_column;
    }
#endif

  /* Now "shift" the result of the reduction.
     Determine what state that goes to,
     based on the state we popped back to
     and the rule number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTBASE] + *yyssp;
  if (yystate >= 0 && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTBASE];

  goto yynewstate;

yyerrlab:   /* here on detecting error */

  if (! yyerrstatus)
    /* If not already recovering from an error, report this error.  */
    {
      ++yynerrs;
      yyerror("parse error");
    }

  if (yyerrstatus == 3)
    {
      /* if just tried and failed to reuse lookahead token after an error, discard it.  */

      /* return failure if at end of input */
      if (yychar == YYEOF)
	YYABORT;

#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Discarding token %d (%s).\n", yychar, yytname[yychar1]);
#endif

      yychar = YYEMPTY;
    }

  /* Else will try to reuse lookahead token
     after shifting the error token.  */

  yyerrstatus = 3;		/* Each real token shifted decrements this */

  goto yyerrhandle;

yyerrdefault:  /* current state does not do anything special for the error token. */

#if 0
  /* This is wrong; only states that explicitly want error tokens
     should shift them.  */
  yyn = yydefact[yystate];  /* If its default is to accept any token, ok.  Otherwise pop it.*/
  if (yyn) goto yydefault;
#endif

yyerrpop:   /* pop the current state because it cannot handle the error token */

  if (yyssp == yyss) YYABORT;
  yyvsp--;
  yystate = *--yyssp;
#ifdef YYLSP_NEEDED
  yylsp--;
#endif

#if YYDEBUG != 0
  if (yydebug)
    {
      short *ssp1 = yyss - 1;
      fprintf (stderr, "Error: state stack now");
      while (ssp1 != yyssp)
	fprintf (stderr, " %d", *++ssp1);
      fprintf (stderr, "\n");
    }
#endif

yyerrhandle:

  yyn = yypact[yystate];
  if (yyn == YYFLAG)
    goto yyerrdefault;

  yyn += YYTERROR;
  if (yyn < 0 || yyn > YYLAST || yycheck[yyn] != YYTERROR)
    goto yyerrdefault;

  yyn = yytable[yyn];
  if (yyn < 0)
    {
      if (yyn == YYFLAG)
	goto yyerrpop;
      yyn = -yyn;
      goto yyreduce;
    }
  else if (yyn == 0)
    goto yyerrpop;

  if (yyn == YYFINAL)
    YYACCEPT;

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Shifting error token, ");
#endif

  *++yyvsp = yylval;
#ifdef YYLSP_NEEDED
  *++yylsp = yylloc;
#endif

  yystate = yyn;
  goto yynewstate;
}
#line 641 "mut.y"


int yylex(void)
{
    int c;

start_lex:

    /* Ignore whitespace, get first nonwhitespace character */
    while ( anzahl_eingelesene_zeichen ++,

            isspace(c = toupper( intern_fgetc(quelldatei) ))
		    /* == ' '
          || c == '\t'
          || c == '\n'*/)  {

       if (c == '\n')
#ifdef ACS_VERSION
        if (!(yylloc.first_line ++ % LINE_DRAW_QUANTUM))
           show_line_number(yylloc.first_line);
#else
         yylloc.first_line ++;
#endif
       }

    if (c == '"') {
       while (anzahl_eingelesene_zeichen ++,

              (c=intern_fgetc(quelldatei)) != '"' && c != EOF )
                    if (c == '\n') yylloc.first_line ++;

       goto start_lex;
    }

    if (c == EOF)
        return 0;


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
    char *word;
    int token;
} reserved_words [] = {
/* Deutsche SchlÅsselworte : */
{ "INTERVALL"  , INTERVALL  },
{ "WURZEL"     , WURZEL     },
{ "TON"        , TON        },
{ "TONSYSTEM"  , TONSYSTEM  },
{ "UMSTIMMUNG" , UMSTIMMUNG },
{ "HARMONIE"   , HARMONIE   },
{ "LOGIK"      , LOGIK      },
{ "FORM"       , FORM       },
{ "MIDIKANAL" , INSTRUMENT },
{ "TASTE"      , TASTE      },
{ "MIDIIN"     , MIDI_IN    },
{ "MIDIOUT"    , MIDI_OUT   },
{ "ANSONSTEN"  , ANSONSTEN  },
/* Englische SchlÅsselworte : */
{ "INTERVAL"  , INTERVALL  },
{ "ROOT"     , WURZEL     },
{ "TONE"        , TON        },
{ "TONESYSTEM"  , TONSYSTEM  },
{ "RETUNING" , UMSTIMMUNG },
{ "PATTERN"   , HARMONIE   },
{ "LOGIC"      , LOGIK      },
{ "SHIFTED"       , FORM       },
{ "MIDICHANNEL" , INSTRUMENT },
{ "KEY"      , TASTE      },
{ "ELSE"  , ANSONSTEN  },
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
            c = toupper(intern_fgetc (quelldatei));
            anzahl_eingelesene_zeichen ++;

        } while (c != EOF                &&
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

void yyerror(char *s) {

/* ignore it ! */

} /* yyerror */



/* END MUT_TAB.C */

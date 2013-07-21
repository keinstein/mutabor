/* A Bison parser, made by GNU Bison 2.7.12-4996.  */

/* Bison interface for Yacc-like parsers in C
   
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

#ifndef YY_YY_SRC_KERNEL_MUT_HH_INCLUDED
# define YY_YY_SRC_KERNEL_MUT_HH_INCLUDED
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
     MUTABOR_TOKEN_COMMENT_START = 276,
     MUTABOR_TOKEN_COMMENT_END = 277,
     MUTABOR_TOKEN_PARAMETER = 278,
     MUTABOR_TOKEN_OTHER = 279,
     MUTABOR_TOKEN_CALLS = 280,
     MUTABOR_TOKEN_ERROR = 281,
     MUTABOR_TOKEN_ENDOFFILE = 282
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
#define MUTABOR_TOKEN_COMMENT_START 276
#define MUTABOR_TOKEN_COMMENT_END 277
#define MUTABOR_TOKEN_PARAMETER 278
#define MUTABOR_TOKEN_OTHER 279
#define MUTABOR_TOKEN_CALLS 280
#define MUTABOR_TOKEN_ERROR 281
#define MUTABOR_TOKEN_ENDOFFILE 282



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{
/* Line 2053 of yacc.c  */
#line 68 "../../../mutabor-git/src/kernel/mut.yy"

    double      f_value;        /* fÅr Gleitkommazahlen */
    int         integer;        /* FÅr integers */
    char        *identifier;    /* FÅr Namen */


/* Line 2053 of yacc.c  */
#line 118 "src/kernel/mut.hh"
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

#endif /* !YY_YY_SRC_KERNEL_MUT_HH_INCLUDED  */

/* A Bison parser, made by GNU Bison 2.5.  */

/* Bison interface for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2011 Free Software Foundation, Inc.
   
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

/* Line 2068 of yacc.c  */
#line 70 "mut.yy"

    double      f_value;        /* f�r Gleitkommazahlen */
    int         integer;        /* F�r integers */
    char        *identifier;    /* F�r Namen */



/* Line 2068 of yacc.c  */
#line 94 "src/kernel/mut.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;

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

extern YYLTYPE yylloc;

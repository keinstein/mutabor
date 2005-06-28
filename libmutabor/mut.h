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




#if ! defined (YYSTYPE) && ! defined (YYSTYPE_IS_DECLARED)
#line 51 "mut.y"
typedef union YYSTYPE {
    double      f_value;        /* fÅr Gleitkommazahlen */
    int         integer;        /* FÅr integers */
    char        *identifier;    /* FÅr Namen */
} YYSTYPE;
/* Line 1285 of yacc.c.  */
#line 79 "y.tab.h"
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE mutabor_parser_lval;

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

extern YYLTYPE mutabor_parser_lloc;



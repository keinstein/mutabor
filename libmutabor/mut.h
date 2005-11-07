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




#if ! defined (YYSTYPE) && ! defined (YYSTYPE_IS_DECLARED)
#line 112 "mut.y"
typedef union YYSTYPE {
	double      f_value;        /* for floating point numbers */
	int         integer;        /* for integers */
	char        *identifier;    /* for names */
	void        *object;        /* for data objects */
} YYSTYPE;
/* Line 1285 of yacc.c.  */
#line 86 "mut.h"
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






%{/* -*- C++ -*- */
%}
%option   noyywrap nounput batch debug noinput
%option   8bit
%option   warn
%option   verbose
%option yyclass="scale_lexer"
%option yylineno
%option prefix="scale_lexer_"

blank [ \t]
number [+-]?[ \t]*[[:digit:]]+

%{
MUTABOR_NAMESPACE_END(scala_parser)
MUTABOR_NAMESPACE_END(mutabor)

# include "src/kernel/parsers/scala/scale_lexer.h"
# include "src/kernel/parsers/scala/scale_parser.hh"
# include "src/kernel/parsers/scala/scala-inlines.h"
MUTABOR_NAMESPACE(mutabor)
MUTABOR_NAMESPACE(scala_parser)
// Work around an incompatibility in flex (at least versions
// 2.5.31 through 2.5.33): it generates code that does
// not conform to C89.  See Debian bug 333231
// <http://bugs.debian.org/cgi-bin/bugreport.cgi?bug=333231>.
# undef yywrap
# define yywrap() 1

//extern "C" inline int dummyisatty (int fd) { return isatty(fd); }
//#define isatty dummyisatty
/*
#define BUMP \
  yylloc->first_line = yylloc->last_line; \
  yylloc->first_column = yylloc->last_column; \
  yylloc->last_column = yycolumn; \
  yylloc->last_line = yylineno;
*/
//define BUMP
#undef  YY_DECL
# define YY_DECL					\
	scale_lexer::symbol_type scale_lexer::get_token ()

  // Code run each time a pattern is matched.
  # define YY_USER_ACTION  loc.columns (yyleng);
%}
%top {
# include "src/kernel/Defs.h"
# include <cerrno>
# include <climits>
# include <cstdlib>
# include <string>
# include <iostream>
# include <errno.h>
# include <cstdio>
# include <cstring>
# include <unistd.h>
# include <algorithm>
/* the header file defines yyFlexLexer in order move everything to the right name space.
   But yyFlexLexer will be defined by Flex as soon as possible. So we must undefine it, here. */
#undef yyFlexLexer
#if defined (__STDC_VERSION__) && __STDC_VERSION__ >= 199901L

/* C99 says to define __STDC_LIMIT_MACROS before including stdint.h,
 * if you want the limit (max/min) macros for int types.
 */
#ifndef __STDC_LIMIT_MACROS
#define __STDC_LIMIT_MACROS 1
#endif

#include <inttypes.h>
#endif
MUTABOR_NAMESPACE(mutabor)
MUTABOR_NAMESPACE(scala_parser)
}
%x string
%x sclname
%x integer
%x interval
%x key
%x garbage
%%
%{
	if (start_token) {
		scale_parser::token_type t = start_token;
		start_token = scale_parser::token::SCALA_TOKEN_END;
		return scale_parser::symbol_type(t,loc);
	}
	/*
	switch (start_mode) {
	case top_mode:BEGIN(INITIAL); break;
	case in_string:BEGIN(string); break;
	case in_interval:BEGIN(interval); break;
	case in_garbage:BEGIN(garbage); break;
	case in_integer:BEGIN(integer); break;
	}
	std::cerr << "start_mode: " << start_mode << std::endl;
	*/
	DEBUGLOG(sclparser,
		 "yy_start: %d",
		 (int)yy_start);
	// Code run each time yylex is called.
	loc.step ();
	loc.begin.filename = loc.end.filename = &file;

	DEBUGLOG(sclparser,
		 "location: %s:%d.%d-",
		 loc.begin.filename->c_str(),
		 loc.begin.line,
		 loc.begin.column);
	DEBUGLOG(sclparser,
		 "          %s:%d.%d",
		 loc.end.filename->c_str(),
		 loc.end.line,
		 loc.end.column);
%}

<*>\n                 {
	loc.lines();
	return scale_parser::symbol_type((scale_parser::token_type)(yytext[0]),loc);
}
<garbage>.*                        return scale_parser::make_GARBAGE(yytext,loc);
<string>[^\n]*                     return scale_parser::make_STRING(yytext,loc);
<interval,integer,key>{number}?{blank}*"."{number}?    return scale_parser::make_F_NUMBER(yytext,loc);
<interval,integer,key>{number}          return scale_parser::make_INTEGER(yytext,loc);
<interval,integer,key>[!/]             {
	return scale_parser::symbol_type((scale_parser::token_type)(yytext[0]),loc);
 }
<key>[Xx]                               {
	return scale_parser::symbol_type((scale_parser::token_type)(yytext[0]),loc);
 }
<interval,integer>[^ \t\n/!.]{-}[[:digit:]][^\n]* {
	return scale_parser::make_STRING(yytext,loc);
				}
<key>[^x \t\n/!.]{-}[[:digit:]][^\n]* {
	return scale_parser::make_STRING(yytext,loc);
				}

<INITIAL,interval,integer>"!"      {
	return scale_parser::symbol_type((scale_parser::token_type)(yytext[0]),loc);
}
<INITIAL,interval,integer>{blank}+   {
	return scale_parser::make_SPACE(yytext,loc);
 }
[^!\n][^\n]*                       return scale_parser::make_STRING(yytext,loc);
<*><<EOF>>                         return scale_parser::make_END(loc);
%%
int scale_lexer::LexerInput( char* buf, int max_size ) {
	if (!buffer)
		return yyFlexLexer::LexerInput(buf, max_size);
	if (buflen <= position || max_size <= 0) return 0;
	size_t  size = std::min((size_t)max_size, buflen - position);
	std::memcpy(buf,buffer+position,size);
	position += size;
	return size;
}
int scale_lexer::yy_start_mode[] =
	{ INITIAL, string, sclname, integer, interval, key, garbage };
}
 }
/** \} */
/*
 ********************************************************************
 * Header file for scala lexer
 *
 * Copyright:   (c) 2016 Tobias Schlemmer <keinstein@users.sf.net>
 * \author  Tobias Schlemmer
 * \license GPL
 *
 *    This program is free software; you can redistribute it and/or modify
 *    it under the terms of the GNU General Public License as published by
 *    the Free Software Foundation; either version 2 of the License, or
 *    (at your option) any later version.
 *
 *    This program is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License for more details.
 *
 *    You should have received a copy of the GNU General Public License
 *    along with this program; if not, write to the Free Software
 *    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 *
 ********************************************************************
 * \addtogroup Parser
 * \{
 ********************************************************************/
/* available groups: GUI, Parser, route, kernel, debug, docview, config, GUIroute */

/** \file                             -*- bison -*-
 ********************************************************************
 * Scala parser gerneator file
 *
 * Copyright:   (c) 2016 Toblas Schlemmer
 * \author   Toblas Schlemmer <keinstein@users.sf.net>
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
/* Muta */
%skeleton "lalr1.cc"
%require "3.0.2"
%defines
%define parser_class_name {scale_parser}
%define api.namespace {mutabor::scala_parser}
%define api.token.constructor
%define api.value.type variant
%define parse.assert

%code requires
{
#include <string>
#include <cerrno>
#include "src/kernel/parsers/scala/scala.h"
namespace mutabor {
	namespace scala_parser {
			class scale_lexer;
        }
}
}
%param { scale_lexer & lexer }
%param { interval_pattern & result }
%locations
%initial-action
{
	// intial location
	@$.begin.filename = @$.end.filename = &lexer.get_filename();
};
%define parse.trace
%define parse.error verbose
%code
{
#include "src/kernel/Defs.h"
#include "src/kernel/parsers/scala/scale_lexer.h"

#ifdef _
#undef _
#endif
#define _ _mut

// fix the interface to the scanner
#ifdef yylex
#undef yylex
#endif
#define yylex(x,y) lexer.get_token()

#if 0
#ifdef DEBUG
#define YYDEBUG 1
#endif
#endif
}
%define api.token.prefix {SCALA_TOKEN_}


/* %define api.token.prefix MUTABOR_TOKEN_ */
/* data types */
/*
        scl_data ".scl data"
        scl_data1 ".scl interval list"
        scl_data2 ".scl interval list (processed)"
        sclfile  ".scl file content"
        scl_data_start ".scl data header"
        scl_data_start1 ".scl data header (processed)"
*/
%token
	END 0        "end of file"
	INTERVAL_END "end of interval list"
        NEWLINE      "\\n"
	COMMENT_SIGN  "!"
        SLASH         "/"
	TAB           "->|"
	BLANK         "' '"
;
%token <std::string>  STRING     "comment line"
%token <std::string>  F_NUMBER   "floating point number"
%token <std::string>  INTEGER    "integer number"
%type  <std::string>  comment    "comment"
%type  <std::string>  comment1   "single comment line"
%type  <int32_t>      integer    "integer"
%type  <double>       float      "double"
%type  <std::string>  single_space "single space"
%type  <std::string>  space      "whitespace"
%type  <std::string>  string     "character string with newline"
%type  <std::string>  string_element  "one of several tokens that can be in a string"
%type  <std::string>  string1    "character string"
%type  <scala_parser::interval> interval "interval"
%type  <scala_parser::interval> interval1 "bare interval"
%type  <scala_parser::interval> interval2 "bare interval with description"
%type  <scala_parser::interval> interval3 "interval with leading space and description"
%printer { yyoutput << $$; } <*>

%% /* Grammar rules and actions */
%start sclfile;

sclfile : scl_data INTERVAL_END
		{ YYACCEPT; }
;
scl_data:	scl_data1
	|	comment scl_data1 { std::swap(result.comment1,$1); }
	;

scl_data_start:	string '\n' integer { result = interval_pattern($1,$3); }
	|	string NEWLINE integer { result = interval_pattern($1,$3); }
	|	string '\n' comment integer { result = interval_pattern($1,$4); std::swap(result.comment2,$3); }
	|	string NEWLINE comment integer { result = interval_pattern($1,$4); std::swap(result.comment2,$3); }
	;

scl_data_start1:
		scl_data_start string_end
	|	scl_data_start string string_end { std::swap(result.count_comment,$2); }
	;
scl_data_start2:
		scl_data_start1 { if (!result.count) { YYACCEPT; }
		result.intervals.reserve(result.count); }
	;
scl_data1:	scl_data_start2
	|	scl_data2 { if (result.count == result.intervals.size()) { YYACCEPT; } }
	;

scl_data2:	scl_data1 interval { result.intervals.push_back($2); }
	;

comment:	comment1
	|	comment comment1 { $$ = $1 + "\n" + $2; }
	;
comment1:	'!' string '\n' { $$ = $2; }
	|	COMMENT_SIGN string '\n' { $$ = $2; }
	|	'!' string NEWLINE { $$ = $2; }
	|	COMMENT_SIGN string NEWLINE { $$ = $2; }
		;

interval:       interval3
	|	comment interval3 { $$ = $2; std::swap($$.comment,$1); }
		;
interval3:	interval2
	|	space interval2 { $$ = $2; }
	;
interval2:	interval1 string_end
	|	interval1 string string_end { $$ = $1; std::swap($$.description,$2); }
		;
interval1:      integer { $$ = scala_parser::interval($1); }
	| 	integer '/' integer { $$ = scala_parser::interval($1,$3); }
	| 	integer SLASH integer { $$ = scala_parser::interval($1,$3); }
	|	float { $$ = scala_parser::interval($1); }
		;

string_element:		STRING
	|	F_NUMBER
	|	INTEGER
	|	space
	|	SLASH { $$ = "/"; }
	|	COMMENT_SIGN { $$ = "!"; }
	|	'/' { $$ = "/"; }
	|	'!' { $$ = "!"; }
		;

string1:	string_element
	|	string1 string_element { $$ = $1 + $2; }
		;

string_end:	'\n'
	|	NEWLINE
	|	END
		;
string: string1 string_end { $$ = $1; }
		;
integer: 	INTEGER {
		errno = 0;
		long n = strtol ($1.c_str(), NULL, 10);
		if (! (0x80000000l+n >= 0 && n <= 0x7fFFffFFl && errno != ERANGE))
		lexer.error (@1, "integer is out of range");
		$$ = n;
		}
	|	space integer { $$ = $2; }
		;

float: 		F_NUMBER {
		errno = 0;
		double value = strtod($1.c_str(), NULL);
		if (! (errno != ERANGE))
		lexer.error (@1, "float is out of range");
		$$ = value;
		}
	|	space float { $$ = $2; }
		;

single_space: ' ' { $$ = " "; }
	|	BLANK { $$ = " "; }
	|	'\t' { $$ = "\t"; }
	|	TAB { $$ = "\t"; }
		;

space: single_space
	|	space single_space { $$ = $1 + $2; }
		;


%%
/// \		todo check whether this function is necessary for any system but windows

       /*
 void
yy::calcxx_parser::error (const location_type& l,
                          const std::string& m)
{
  driver.error (l, m);
}
       */

/*
 * \}
 */

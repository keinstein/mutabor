/** \file               -*- C++ -*-
********************************************************************
* Header file for scala lexer.
*
* Copyright:   (c) 2013 Tobias Schlemmer
* \author  Tobias Schlemmer <keinstein@users.sourceforge.net>
* \version $Version$
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
// availlable groups: GUI, route, kernel, muwx, debug, docview, config, docview

/* we guard a little bit complicated to ensure the references are set right
 */

#if (!defined(SRC_KERNEL_MUTLEX_H) && !defined(PRECOMPILE))	\
	|| (!defined(SRC_KERNEL_MUTLEX_H_PRECOMPILED))
#ifndef PRECOMPILE
#define SRC_KERNEL_MUTLEX_H
#endif

// ---------------------------------------------------------------------------
// headers
// ---------------------------------------------------------------------------

#include "src/kernel/Defs.h"
#ifdef LEXER_NAMESPACE
#undef LEXER_NAMESPACE
#endif
#define LEXER_NAMESPACE namespace mutabor { namespace scala_parser {
#include "src/kernel/parsers/scala/scale_parser.hh"

#ifndef SRC_KERNEL_MUTLEX_H_PRECOMPILED
#define SRC_KERNEL_MUTLEX_H_PRECOMPILED

// system headers which do seldom change
#include <cstring>
#include <cstdarg>

namespace mutabor {
	namespace scala_parser {

#if ! defined(yyFlexLexerOnce)
#ifndef yyFlexLexer
#define yyFlexLexer scale_lexer_FlexLexer
#endif
#ifdef HAVE_FLEXLEXER_H
#include <FlexLexer.h>
#else
#include "FlexLexer.h"
#endif
#endif


		class scale_lexer: public yyFlexLexer {
		public:
			enum start_mode {
				top_mode=0,
				in_string,
				in_sclname,
				in_integer,
				in_interval,
				in_key,
				in_garbage
			};
			typedef scale_parser::symbol_type symbol_type;
			scale_lexer(const char * string,
				    const char * f,
				    size_t len):
				yyFlexLexer(),
				handler(NULL),
				file(f),
				buffer(strdup(string)),
				buflen(len),
				position(0),
				report_parameters(true),
				start_token(scale_parser::token::SCALA_TOKEN_END)
				//			  yylval(new mutabor::hidden::YYSTYPE)
			{}
			~scale_lexer() {
				// delete yylval;
				if (buffer)
					free(buffer);
			}


			error_handler * get_error_handler() const {
				return handler;
			}
			void set_error_handler(error_handler * h) {
				handler = h;
			}

			scale_parser::token_type get_start_token() const {
				return start_token;
			}

			void set_start_token(scale_parser::token_type  t) {
				start_token = t;
			}

			void set_string(const char * string,
					const char * f,
					size_t len) {
				file = f;
				if (buffer) free(buffer);
				buffer = strdup(string);
				buflen = len;
				position = 0;
				yyrestart(yyin);
			}

			void error (const location & loc,
				    const char * message,
				    ...) {
				char * formatted;
				va_list args;
				bool allocated = true;
				va_start(args,message);
				if (vasprintf(&formatted,message,args) == -1) {
					allocated = false;
					formatted = (char *)_mut("Error in Error: Could not allocate buffer for error message.");
					if (!formatted) {
						formatted =
							(char *) "Error in Error: Could not allocate buffer for error message.";
					}
				}
				va_end(args);
				if (handler)
					handler->error(loc,formatted);
				else
					std::cerr << loc
						  << std::endl
						  << "Error: "
						  << formatted << std::endl;
				if (allocated)
					free(formatted);
			}
			std::string & get_filename() {return file;}
			symbol_type get_token();
			void free_identifier() { /* free(yylval->identifier); yylval->identifier = NULL; */ }
			void push_state(start_mode mode) {
				DEBUGLOG(sclparser,"pushing mode: %d/%d (%d) ->",
					 mode,
					 yy_start_mode[mode],
					 ((yy_start_stack_ptr>0)?yy_top_state():-1));
				yy_push_state(yy_start_mode[mode]);
#ifdef DEBUG
				/* in debug mode we do a double push, as the current start state is
				   usually not on the stack. With teh additional push we can verify
				   the correct push/pop pairs later during pop */
				yy_push_state(yy_start_mode[mode]);
#endif
				DEBUGLOG(sclparser,"pushing mode: %d/%d (%d).",
					 mode,
					 yy_start_mode[mode],
					 ((yy_start_stack_ptr>0)?yy_top_state():-1));
			}
			void pop_state(start_mode mode) {
				mutUnused(mode);
				DEBUGLOG(sclparser,
					 "popping mode1: (%d) %d ->",
					 yy_start_mode[mode],
					 yy_top_state());
				yy_pop_state();
#ifdef DEBUG
				DEBUGLOG(sclparser,
					 "popping mode2: (%d) %d ->",
					 yy_start_mode[mode],
					 yy_top_state());
				yy_pop_state();
#endif
				DEBUGLOG(sclparser,
					 "popping mode3: (%d) %d.",
					 yy_start_mode[mode],
					 ((yy_start_stack_ptr>0)?yy_top_state():-1));

			}
		protected:
			static int yy_start_mode[];
			error_handler * handler;
			std::string file;
			char * buffer;
			size_t buflen;
			size_t position;
			bool report_parameters;
			// The location of the current token.
			location loc;
			scale_parser::token_type start_token;

			virtual int LexerInput( char* buf, int max_size );
		};
	}
}

#endif // precompiled
#endif // header loaded


	///\}

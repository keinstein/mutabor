/** \file               -*- C++ -*-
********************************************************************
* Header file for scala lexer.
*
* Copyright:   (c) 2013 Tobias Schlemmer
* \author  Tobias Schlemmer <keinstein@users.berlios.de>
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
			typedef scale_parser::symbol_type symbol_type;
			scale_lexer(const char * string,
				    const char * f,
				    size_t len):
				yyFlexLexer(),
				file(f),
				buffer(strdup(string)),
				buflen(len),
				position(0),
				report_parameters(true)
				//			  yylval(new mutabor::hidden::YYSTYPE)
			{}
			~scale_lexer() {
				// delete yylval;
				free(buffer);
			}

			void error (const location & loc,
				    const char * message) {
				std::cerr << loc << std::endl << message << std::endl;
			}
			std::string & get_filename() {return file;}
			symbol_type get_token();
			void free_identifier() { /* free(yylval->identifier); yylval->identifier = NULL; */ }
		protected:
			std::string file;
			char * buffer;
			size_t buflen;
			size_t position;
			bool report_parameters;
			// The location of the current token.
			location loc;

			virtual int LexerInput( char* buf, int max_size );
		};
	}
}

#endif // precompiled
#endif // header loaded


	///\}

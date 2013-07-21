/** \file               -*- C++ -*-
********************************************************************
* Header file for the mutabor lexer class.
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
* \addtogroup kernel
* \{
********************************************************************/
// availlable groups: GUI, route, kernel, muwx, debug, docview, config, docview

/* we guard a little bit complicated to ensure the references are set right
 */

#if (!defined(HEADERFILENAME) && !defined(PRECOMPILE))	\
	|| (!defined(HEADERFILENAME_PRECOMPILED))
#ifndef PRECOMPILE
#define HEADERFILENAME
#endif

// ---------------------------------------------------------------------------
// headers
// ---------------------------------------------------------------------------

#include "src/kernel/Defs.h"
#include "src/kernel/mut.hh"

#ifndef HEADERFILENAME_PRECOMPILED
#define HEADERFILENAME_PRECOMPILED

// system headers which do seldom change
 
#if ! defined(yyFlexLexerOnce)
#ifndef yyFlexLexer
#define yyFlexLexer mutabor_lexer_FlexLexer
#endif
#ifdef HAVE_FLEXLEXER_H
#include <FlexLexer.h>
#else
#include "FlexLexer.h"
#endif
#endif


#undef  YY_DECL
#define YY_DECL int  mutabor::mutabor_lexer::yylex()

/// not for headers
#ifdef __BORLANDC__
#pragma hdrstop
#endif


namespace mutabor {
	class mutabor_lexer: public mutabor_lexer_FlexLexer {
	public:
		mutabor_lexer(const char * string, 
			      size_t len):yyFlexLexer(),
					  buffer(string),
					  buflen(len),
					  position(0),
					  report_parameters(true),
					  yylval(new YYSTYPE) {}
		~mutabor_lexer() { delete yylval; }
		
		int yylex();
		void free_identifier() { free(yylval->identifier); yylval->identifier = NULL; }
	protected:
		virtual int LexerInput( char* buf, int max_size ) {
			int size = std::min(max_size, (int)(buflen - position));
			memcpy(buf,buffer,size);
			position += size;
			return std::max(size,0);
		}
		const char * buffer;
		size_t buflen;
		size_t position;
		bool report_parameters;
		YYSTYPE * yylval;
	};
}


#endif // precompiled
#endif // header loaded


///\}

/** \file               -*- C++ -*-
 ********************************************************************
 * Data structures for the scala file parser and generator.
 *
 * Copyright:   (c) 2013 Tobias Schlemmer
 * \author  Tobias Schlemmer <keinstein@users.berlios.de>
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

/* we guard a little bit complicated to ensure the references are set right
 */

/* ---------------------------------------------------------------------------
 * headers
 * --------------------------------------------------------------------------- */

#include "src/kernel/Defs.h"
#include <cstdarg>
#include "src/kernel/parsers/scala/scala.h"
#include "src/kernel/parsers/scala/scale_lexer.h"
#include "src/kernel/parsers/scala/scale_parser.hh"

/* system headers which do seldom change */

/** not for headers */
#ifdef __BORLANDC__
    #pragma hdrstop
#endif



namespace mutabor {
	namespace scala_parser {
		parser::~parser() {
			delete bison_parser;
			bison_parser = NULL;
			delete lexer;
			lexer = NULL;
		}

		void parser::parse(const std::string & s) {
			if (!lexer) {
				lexer = new scale_lexer(s.c_str(),"direct input",s.length());
				lexer ->set_debug(7);
			}
			if (!bison_parser) {
				bison_parser = new scale_parser(*lexer,intervals);
				bison_parser->set_debug_level(7);
			}
			bison_parser -> parse();
		}

		void parser::error(const char *  format, ...) {
			char * formatted;
			va_list args;
			bool allocated = true;
			va_start(args,format);
			if (vasprintf(const_cast<char **>(&formatted),format,args) == -1) {
				allocated = false;
				formatted = const_cast<char *>(_mut("Error in Error: Could not allocate buffer for error message."));
				if (!formatted) {
					formatted = 
						const_cast<char *>("Error in Error: Could not allocate buffer for error message.");
				}
			}
			va_end(args);
			std::cerr << _mut("Error parsing scala document: ")
				  << formatted << std::endl;
			if (allocated)
				free(formatted);
		}

	}
}

/** \} */

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
#include <cmath>
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

		void parser::parse(const std::string & s,
				   const std::string & filename) {
			if (!lexer) {
				lexer = new scale_lexer(s.c_str(),
							filename.c_str(),
							s.length());
#ifdef DEBUG
				if (isDebugFlag(sclparser))
					lexer -> set_debug(7);
#endif
				lexer -> set_error_handler(handler);
			}
			if (!bison_parser) {
				bison_parser = new scale_parser(*lexer,intervals);
#ifdef DEBUG
				if (isDebugFlag(sclparser))
					bison_parser->set_debug_level(7);
#endif
			}
			bison_parser -> parse();
		}

		void parser::error(const location & loc, const char *  message) {
			std::cerr << loc
				  << std::endl
				  << message << std::endl;
		}

		std::ostream & parser::write_mutabor(std::ostream & o, const mutabor_writer_options & w) {
			o << "\" converted from scala to -*- MUTABOR -*- \"" << std::endl;
			o << "\"       " << intervals.comment1 << std::endl;
			o << " Name:  " << intervals.name << std::endl;
			o << "        " << intervals.comment2 << std::endl;
			o << " Tones: " << intervals.count << " " << intervals.count_comment  << "\"" << std::endl;
			o << std::endl;
			o << _mut("TONESYSTEM") << std::endl;
			o << "\t" << w.prefix << "T" << " = 60 [ " << w.prefix << "0";

			for (size_t i = 1; i < intervals.intervals.size() ; i++) {
				o << ", " << w.prefix << i;
			}
			o << " ] " << w.prefix << intervals.intervals.size() << std::endl;
			o << std::endl;
			o << _mut("INTERVAL") << std::endl;
			o << "\t" << w.prefix << _mut("OCTAVE") << " = 2:1" << std::endl;
			o << "\t" << w.prefix << _mut("CENT") << " = "
			  << w.prefix << "OCTAVE / 1200" << std::endl;
			o << "\t" << w.prefix << "0 = 1:1" << std::endl;
			for (size_t i = 0 ; i < intervals.intervals.size() ; i++) {
				interval &interv = intervals.intervals[i];
				o << "\"" << interv.comment << "\"" << std::endl;
				o << "\t" << w.prefix << i+1 << " = " ;
				switch (interv.type) {
				case interval::cent_value:
					o << interv.data.cents << " " << w.prefix << "CENT";
					break;
				case interval::ratio:
					o << interv.data.f.numerator << ":" << interv.data.f.denominator;
					break;
				case interval::cent_ratio:
					{
						double cents =  interv.data.df.numerator/interv.data.df.denominator;
						cents = 1200 * log2(cents);
						o << cents << " " << w.prefix << "CENT";
					}
				}
				o << " \"" << interv.description << "\"" << std::endl;
			}
			o << _mut("TONE") << std::endl;
			o << "\t" << w.prefix << "0 = 440" << std::endl;
			for (size_t i = 1 ; i < intervals.intervals.size() ; i++) {
				o << "\t" << w.prefix << i << " = "
				  << w.prefix << "0 + " << w.prefix << i << std::endl;
			}
			o << _mut("LOGIC") << std::endl;
			o << "\t" << w.prefix << " KEY " << w.prefix[0]
			  << " = " << w.prefix << "T []" << std::endl;
			return o;
		}
	}
}

/** \} */

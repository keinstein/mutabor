/** \file               -*- C++ -*-
 ********************************************************************
 * Data structures for the scala file parser and generator.
 *
 * Copyright:   (c) 2013 Tobias Schlemmer
 * \author  Tobias Schlemmer <keinstein@users.sourceforge.net>
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
#include <sstream>
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
			else lexer->set_string(s.c_str(),
					       filename.c_str(),
					       s.length());
			if (!bison_parser) {
				bison_parser = new scale_parser(*lexer,intervals,keys);
#ifdef DEBUG
				if (isDebugFlag(sclparser))
					bison_parser->set_debug_level(7);
#endif
			}
			if (lexer && bison_parser) {
				lexer -> set_start_token(scale_parser::token::SCALA_TOKEN_SCL_START);
				bison_parser -> parse();
			}
		}

		void parser::load_keymap(const std::string & s,
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
			else lexer->set_string(s.c_str(),
					       filename.c_str(),
					       s.length());
			if (!bison_parser) {
				bison_parser = new scale_parser(*lexer,intervals,keys);
#ifdef DEBUG
				if (isDebugFlag(sclparser))
					bison_parser->set_debug_level(7);
#endif
			}

			if (lexer && bison_parser) {
				lexer -> set_start_token(scale_parser::token::SCALA_TOKEN_KBM_START);
				bison_parser -> parse();
			}
		}

		void parser::error(const location & loc, const char *  message) {
			std::cerr << loc
				  << std::endl
				  << message << std::endl;
		}

		template<class T>
		std::ostream & scala_value<T>::print_mutabor(std::ostream & o,
							  const std::string & name,
							  bool in_comment) const {
			std::string quote = in_comment?"":"\"";
			if (!comment.empty())
				o << quote << comment << quote << std::endl;
			o << name << value;
			if (!description.empty())
				o << " " << quote << description << quote;
			o << std::endl;
			return o;
		}

		std::ostream & interval::print_mutabor_interval (std::ostream & o,
								 int i,
								 const mutabor_writer_options & w) const {
			if (!(comment.empty()))
				o << "\"" << comment << "\"" << std::endl;
			o << "\t" << w.prefix << i+1 << " = " ;
			switch (type) {
			case interval::cent_value:
				o << data.cents << " " << w.prefix << _mut("CENT");
				break;
			case interval::ratio:
				o << data.f.numerator << ":" << data.f.denominator;
				break;
			case interval::cent_ratio:
				{
					double cents =  data.df.numerator/data.df.denominator;
					cents = 1200 * log2(cents);
					o << cents << " " << w.prefix << _mut("CENT");
				}
			}
			if (!description.empty())
				o << " \"" << description << "\"";
			o << std::endl;
			return o;
		}

		std::ostream & interval_pattern::print_mutabor (std::ostream & o,
								const mutabor_writer_options & w) const {
			if (!(comment1.empty()))
				o << "\"       " << comment1 << std::endl;
			o << " Name:  " << name << std::endl;
			if (!(comment2.empty()))
				o << "        " << comment2 << std::endl;
			o << " Intervals: " << count << " " << count_comment  << "\"" << std::endl;
			o << std::endl;
			o << _mut("INTERVAL") << std::endl;
			o << "\t" << w.prefix << _mut("OCTAVE") << " = 2:1" << std::endl;
			o << "\t" << w.prefix << _mut("CENT") << " = "
			  << w.prefix << _mut("OCTAVE") << " / 1200" << std::endl;
			o << "\t" << w.prefix << "0 = 1:1" << std::endl;
			for (size_t i = 0 ; i < intervals.size() ; i++) {
				intervals[i].print_mutabor_interval(o,i,w);
			}
			if (!(garbage.empty())) {
				o << "\"" << garbage << "\"";
			}
			return o;
		}

		std::ostream & key::print_mutabor_tone (std::ostream & o,
							int i,
							const mutabor_writer_options & w) const
		{
			if (type == empty)
				return o;

			std::ostringstream s;
			s << "\t" << w.tone_prefix << i
			  << " = " << w.tone_prefix << _mut("_anchor")
			  << " + " << w.prefix;
			return print_mutabor(o,
					     s.str(),
					     false);
 		}
		std::ostream & keymap::print_mutabor (std::ostream & o,
						      const mutabor_writer_options & w) const {
			
			o << "\"" << std::endl;
			count.print_mutabor(o, " Tonesystem size: ", true);
			first_key.print_mutabor(o, " First key: ", true);
			last_key.print_mutabor(o, " Last key: ", true);
			o << " Note: The key range must be configured using the route system. " << std::endl;
			reference.print_mutabor(o, " Reference key: ",true);
			o << "\"" << std::endl;
			
			o << std::endl;
			repetition_interval.print_mutabor(o,
							  "\t" + w.prefix +
							  _mut("_repetition") + " = "
							  + w.prefix,
							  true);

			o << std::endl << std::endl;
			o << _mut("TONE") << std::endl;
			reference_frequency.print_mutabor(o,
							  "\t" + w.tone_prefix + _mut("_reference") + " = ",
							  true);
			int distance = anchor.value - reference.value;
			std::cerr << "Distance: " << anchor.value
				  << " - " << reference.value
				  << " = " << distance << std::endl;
			int divisor = std::max(count.value,1);
			int octaves =  distance / divisor;
			int offset = octaves*divisor - distance ;
			if (offset < 0) {
				offset += divisor;
				octaves += 1;
			}
			
			o << "\t" << w.tone_prefix << _mut("_anchor") << " = "
			  << w.tone_prefix << _mut("_reference");
			if (octaves)
				o << ((octaves < 0) ? " - ":" + ")
				  << std::abs(octaves) << " " << w.prefix << _mut("_repetition");
			
			if ((size_t)(offset) < keys.size() &&
				 keys[offset].type != key::empty)
				o << " - "  << w.prefix
				  << keys[offset].value;
			else 
				o <<" \" "
				  << " - "  << w.prefix << "_" << offset
				  << " \"" ;
			o << std::endl;

			for (size_t i = 0 ; i < keys.size() ; i++) {
				keys[i].print_mutabor_tone(o,i,w);
			}

			o << std::endl << std::endl;
			
			o << _mut("TONESYSTEM") << std::endl;
			o << "\t" << w.tonesystem_name << " = ";
			anchor.print_mutabor(o,"", false)
				<< "\t\t[ ";
			if (keys.empty() || keys[0].type != key::empty)
				o << w.tone_prefix << "0";

			for (size_t i = 1; i < keys.size() ; i++) {
				o << ", ";
				if (keys[i].type != key::empty)
					o << w.tone_prefix << i;
			}
			o << " ] " << std::endl
			  << "\t\t  " <<  w.prefix << _mut("_repetition") << std::endl;
			o << std::endl << std::endl;
			
			o << _mut("LOGIC") << std::endl;
			o << "\t" << w.logic_name << " " << _mut("KEY") << " " << w.logic_name[0]
			  << " = " << w.tonesystem_name << " []" << std::endl;
			if (!garbage.empty()) {
				o << "\"" << garbage << "\"";
			}
			return o;
		}		

		std::ostream & parser::write_mutabor(std::ostream & o,
						     const mutabor_writer_options & w) {
			o << "\" converted from scala to -*- MUTABOR -*- \"" << std::endl;
			intervals.print_mutabor(o,w) << std::endl;
			keys.print_mutabor(o,w) << std::endl;
			return o;
		}
	}
}

/** \} */

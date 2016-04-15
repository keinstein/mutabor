/** \file               -*- C++ -*-
 ********************************************************************
 * Internal data structures for the scala parseer.
 *
 * Copyright:   (c) 2016 Tobias Schlemmer
 * \author  Tobias Schlemmer <keinstein@users.sf.net>
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

#if (!defined(HEADERFILENAME) && !defined(PRECOMPILE)) \
	|| (!defined(HEADERFILENAME_PRECOMPILED))
#ifndef PRECOMPILE
#define HEADERFILENAME
#endif

/* ---------------------------------------------------------------------------
 * headers
 * --------------------------------------------------------------------------- */

#include "src/kernel/Defs.h"

#ifndef HEADERFILENAME_PRECOMPILED
#define HEADERFILENAME_PRECOMPILED

/* system headers which do seldom change */
#include <vector>

namespace mutabor {
	namespace scala_parser {
		class scala_lexer;

		struct interval {
			enum interval_type {
				cent_value,
				ratio
			} type;
			union {
				struct {
					int32_t numerator;
					int32_t denominator;
				} f;
				double cents;
			} data;
			std::string comment; // comments before the interval
			std::string description; // text following in the same line
			interval ():type(ratio){
				data.f.numerator = 1;
				data.f.denominator = 1;
			}
			interval (double c):type(cent_value) {
				data.cents = c;
			}
			interval (int32_t i):type(ratio) {
				data.f.numerator = i;
				data.f.denominator = 1;
			}
			interval (int32_t n, int32_t d):type(ratio) {
				data.f.numerator = n;
				data.f.denominator = d;
			}
		};
		inline std::ostream & operator<< (std::ostream & o, const interval & i) {
			switch (i.type) {
			case interval::cent_value:
				o << i.data.cents;
				break;
			case interval::ratio:
				o << i.data.f.numerator
				  << "/"
				  << i.data.f.denominator;
			default:
				o << "<unknown interval>";
			}
			return o;
		}
		typedef typename std::vector<interval> interval_list;
		struct interval_pattern {
			std::string comment1;
			std::string name;
			std::string comment2;
			size_t count;
			std::string count_comment;
			interval_list intervals;
			std::string garbage;
			interval_pattern(const std::string & n,
					 size_t c):name(n),count(c) {}
		};

		class parser {
		public:
			parser (const std::string & s) {
				parse(s);
			}

			void parse (const std::string & s) {

			}

			void error(const char *  format, ...) {}
		protected:
			scala_parser::scala_lexer * lexer;

		};
	}
}

#endif /* precompiled */
#endif /* header loaded */


/** \} */

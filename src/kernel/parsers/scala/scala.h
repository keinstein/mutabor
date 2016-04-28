/** \file               -*- C++ -*-
 ********************************************************************
 * Data structures for the scala file parser and generator.
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
#include <iostream>

namespace mutabor {
	namespace scala_parser {
		class scale_lexer;
		class scale_parser;
		class location;
		struct interval {
			enum interval_type {
				cent_value,
				ratio,
				cent_ratio
			} type;
			union {
				struct {
					int32_t numerator;
					int32_t denominator;
				} f;
				struct {
					int32_t numerator;
					double denominator;
				} df;
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
			interval (int32_t n, double d):type(cent_ratio) {
				data.df.numerator = n;
				data.df.denominator = d;
			}
			std::ostream & print (std::ostream & o) const {
				if (!comment.empty())
					o << "!" << comment << std::endl;
				switch (type) {
				case interval::cent_value:
					o << data.cents;
					break;
				case interval::ratio:
					o << data.f.numerator
					  << "/"
					  << data.f.denominator;
					break;
				case interval::cent_ratio:
					o << data.df.numerator
					  << "/"
					  << data.df.denominator;
					break;
				default:
					o << "<unknown interval>";
				}
				o << description;
				return o;
			}
			bool operator == (const interval & o) const {
				bool retval = type == o.type;
				if (!retval) return false;
				switch (type) {
				case cent_value: retval = data.cents == o.data.cents;
					break;
				case ratio:
					retval = data.f.denominator == o.data.f.denominator
						&& data.f.numerator == o.data.f.numerator;
					break;
				case cent_ratio:
					retval = data.df.denominator == o.data.df.denominator
						&& data.df.numerator == o.data.df.numerator;
					break;
				default:
					return false;
				}
				retval = retval && comment == o.comment && description == o.description;
				return retval;
			}
		};
		inline std::ostream & operator<< (std::ostream & o, const interval & i) {		return i.print(o);
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
			interval_pattern() {}
			interval_pattern(const std::string & n,
					 size_t c):name(n),count(c) {}
			bool operator == (const interval_pattern & o) const {
				return name == o.name &&
					count == o.count &&
					intervals == o.intervals &&
					comment1 == o.comment1 &&
					comment2 == o.comment2 &&
					count_comment==o.count_comment &&
					garbage == o.garbage;
			}
			std::ostream & print (std::ostream & o) const {
				o << "!" << comment1 << std::endl
				  << name << std::endl
				  << "!" << comment2 << std::endl
				  << count << count_comment << std::endl;
				for (interval_list::const_iterator i = intervals.begin();
				     i != intervals.end();
				     ++i) {
					o << *i << std::endl;
				}
				return o << garbage;
			}
		};

		inline std::ostream & operator << (std::ostream & o, const interval_pattern & i) {
			return (i.print(o)) << std::endl;
		}


		struct error_handler {
			virtual ~error_handler() {}
			virtual void error(const location & loc,
					   const char * message) = 0;
		};

		class parser: public error_handler {
		public:
			struct mutabor_writer_options {
				std::string prefix;
			};
			parser (const std::string & s,
				const std::string & f): handler(this),
							intervals(),
							lexer(NULL),
							bison_parser(NULL)
			{
				parse(s,f);
			}
			virtual ~parser();

			void parse (const std::string & s,
				    const std::string & filename);

			error_handler * get_error_handler() const;
			void set_error_handler(error_handler * h);

			virtual void error(const location &loc, const char *  message);

			const interval_pattern & get_intervals () { return intervals; }


			std::ostream & write_mutabor(std::ostream & o, const mutabor_writer_options & w);
		protected:
			error_handler * handler;
			interval_pattern intervals;
			scale_lexer * lexer;
			scale_parser * bison_parser;
		};
	}
}

#endif /* precompiled */
#endif /* header loaded */


/** \} */

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

#if (!defined(SRC_PARSERS_SCALA_SCALA_INLINES_H) && !defined(PRECOMPILE))	\
	|| (!defined(SRC_PARSERS_SCALA_SCALA_INLINES_H_PRECOMPILED))
#ifndef PRECOMPILE
#define SRC_PARSERS_SCALA_SCALA_INLINES_H
#endif

/* ---------------------------------------------------------------------------
 * headers
 * --------------------------------------------------------------------------- */

#include "src/kernel/parsers/scala/scala.h"
#include "src/kernel/parsers/scala/scale_lexer.h"

#ifndef SRC_PARSERS_SCALA_SCALA_INLINES_H_PRECOMPILED
#define SRC_PARSERS_SCALA_SCALA_INLINES_H_PRECOMPILED

/* system headers which do seldom change */
#include <vector>
#include <iostream>

namespace mutabor {
	namespace scala_parser {
		template<class T>
		inline scala_value<T> & scala_value<T>::swap(scala_value<T> & o) {
			std::swap(comment,o.comment);
			std::swap(value,o.value);
			std::swap(description,o.description);
		}
		template<class T>
		inline std::ostream & scala_value<T>::print(std::ostream & o) const
		{
			if (!comment.empty())
				o << "!" << comment << std::endl;
			o << std::showpoint << value << description;
			return o;

		}
		template<class T>
		inline std::ostream & operator << (std::ostream & o,
					    const scala_value<T> & v)
		{
			return v.print(o);
		}


		inline std::ostream & interval::print (std::ostream & o) const {
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
		inline bool interval::operator == (const interval & o) const {
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

		inline std::ostream & operator<< (std::ostream & o,
						  const interval & i) {
			return i.print(o);
		}

		inline std::ostream & interval_pattern::print (std::ostream & o) const {
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

		inline std::ostream & operator << (std::ostream & o,
						   const interval_pattern & i) {
			return (i.print(o)) << std::endl;
		}


		inline std::ostream & key::print (std::ostream & o) const {
			if (!comment.empty())
				o << "!" << comment << std::endl;
			switch (type) {
			case key::empty:
				o << "x";
				break;
			case key::numeric:
				o << value;
				break;
			default:
				o << "<unknown key>";
			}
			o << description;
			return o;
		}

		inline std::ostream & operator<< (std::ostream & o,
						  const key & k) {
			return k.print(o);
		}

#ifdef DEBUG
		inline bool keymap::compare(const keymap & o) const {
			bool retval = (count == o.count);
			DEBUGLOG(sclparser,"count : %s", (retval ? "ok" : "fail"));
			mutASSERT(retval);
			retval = retval &&  (first_key == o.first_key);
			DEBUGLOG(sclparser,"first_key : %s", (retval ? "ok" : "fail"));
			mutASSERT(retval);
			retval = retval &&  (last_key == o.last_key);
			DEBUGLOG(sclparser,"last_key : %s", (retval ? "ok" : "fail"));
			mutASSERT(retval);
			retval = retval &&  (reference == o.reference);
			DEBUGLOG(sclparser,"reference : %s", (retval ? "ok" : "fail"));
			mutASSERT(retval);
			retval = retval &&  (anchor == o.anchor);
			DEBUGLOG(sclparser,"anchor : %s", (retval ? "ok" : "fail"));
			mutASSERT(retval);
			retval = retval &&  (reference_frequency == o.reference_frequency);
			DEBUGLOG(sclparser,"reference_frequency : %s", (retval ? "ok" : "fail"));
			mutASSERT(retval);
			retval = retval &&  (repetition_interval == o.repetition_interval);
			DEBUGLOG(sclparser,"repetition_interval : %s", (retval ? "ok" : "fail"));
			mutASSERT(retval);
			retval = retval &&  (keys == o.keys);
			DEBUGLOG(sclparser,"keys : %s", (retval ? "ok" : "fail"));
			mutASSERT(retval);
			retval = retval &&  (garbage == o.garbage);
			DEBUGLOG(sclparser,"garbage : %s", (retval ? "ok" : "fail"));
			mutASSERT(retval);
			return retval;
		}
#endif

		inline std::ostream & keymap::print (std::ostream & o) const {
			o << count << std::endl
			  << first_key << std::endl
			  << last_key << std::endl;
			o << anchor << std::endl;
			o << reference << std::endl;
			o << reference_frequency << std::endl;
			o << repetition_interval << std::endl;
			for (key_list::const_iterator i = keys.begin();
			     i != keys.end();
			     ++i) {
				o << *i << std::endl;
			}
			return o << garbage;
		}

		inline std::ostream & operator << (std::ostream & o,
						   const keymap & k) {
			return (k.print(o)) << std::endl;
		}

		inline bool key::operator == (const key & o) const {
			if (type != o.type) return false;
			switch (type) {
			case numeric: return value == o.value;
			case empty: return true;
			default: return false;
			}
		}

		inline error_handler * parser::get_error_handler() const {
			error_handler * retval = NULL;
			if (lexer)
				retval =  lexer->get_error_handler();
			return retval? retval:handler;
		}
		inline void parser::set_error_handler(error_handler * h) {
			handler = h;
			if (lexer) lexer->set_error_handler(h);
		}


	}
}

#endif /* precompiled */
#endif /* header loaded */


/** \} */

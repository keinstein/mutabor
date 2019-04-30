/** \file
 ********************************************************************
 * Common definitions
 *
 * Copyright:   (c) 2008-2011 TU Dresden
 *              changes after 2011-11 (c) by the authors
 * \author  Tobias Schlemmer <keinstein@users.sourceforge.net>
 * \version $Revision: 1.24 $
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
/* prevent double inclusion */

#ifndef	MU32_DEFS_H
#define MU32_DEFS_H

#ifdef HAVE_CONFIG_H
#include "config.h"
#else
#define MUTWIN
/*#define MUTMIDI */
#endif

/* don't confuse auto indentation with namespaces
   workaround for inflexible Flex */
#ifdef __cplusplus
#define MUTABOR_NAMESPACE(X) namespace X {
#define MUTABOR_NAMESPACE_END(X) }
#define MUTABOR_EXTERN_C extern "C" {
#define MUTABOR_EXTERN_C_END }
#else
#define MUTABOR_NAMESPACE(X)
#define MUTABOR_NAMESPACE_END(X)
#define MUTABOR_EXTERN_C
#define MUTABOR_EXTERN_C_END
#endif

#ifndef _GNU_SOURCE
#define _GNU_SOURCE 1
#endif


#include "interface_deps.h"

#ifdef __cplusplus

#include <cstddef>
using std::size_t;

#else

#include <stddef.h>
#include <stdbool.h>

#endif


/* the following code has been found at
   http://gustedt.wordpress.com/2010/06/08/detect-empty-macro-arguments/
*/
#define _ARG16(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, ...) _15
#define HAS_COMMA(...) _ARG16(__VA_ARGS__, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0,0)
#define _TRIGGER_PARENTHESIS_(...) ,

#define ISEMPTY(...)                                                    \
_ISEMPTY(                                                               \
          /* test if there is just one argument, eventually an empty    \
             one */                                                     \
          HAS_COMMA(__VA_ARGS__),                                       \
          /* test if _TRIGGER_PARENTHESIS_ together with the argument   \
             adds a comma */                                            \
          HAS_COMMA(_TRIGGER_PARENTHESIS_ __VA_ARGS__),                 \
          /* test if the argument together with a parenthesis           \
             adds a comma */                                            \
          HAS_COMMA(__VA_ARGS__ (/*empty*/)),                           \
          /* test if placing it between _TRIGGER_PARENTHESIS_ and the   \
             parenthesis adds a comma */                                \
          HAS_COMMA(_TRIGGER_PARENTHESIS_ __VA_ARGS__ (/*empty*/))      \
          )

#define PASTE5(_0, _1, _2, _3, _4) _0 ## _1 ## _2 ## _3 ## _4
#define _ISEMPTY(_0, _1, _2, _3) HAS_COMMA(PASTE5(_IS_EMPTY_CASE_, _0, _1, _2, _3))
#define _IS_EMPTY_CASE_0001 ,

/* end of cited code */

#define mutint64 int_fast64_t
#define mutUnused(expr) do { (void)(expr); } while (0)
#define mutUNUSED(expr)
#ifdef __cplusplus
#define FALLTHROUGH mutfallthrough
#else
#define FALLTHROUGH mutCfallthrough
#endif

#include "src/kernel/debug.h"

#ifdef __cplusplus
namespace mutabor {
	template<class T>
		class idtype {
	public:
		typedef T referenceing_type;
	idtype():id(idpool++) {}
		size_t operator ()() const { return id; }
		operator size_t () const { return id; }
		operator int () const { return (int) id; }
	protected:
		const size_t id;
		static size_t idpool;
	};
	template <class T>
		inline std::string str(T obj) { return obj; }
}


#endif

#define _mutN(x) x
#define _mut wxwidgets_gettext
#define _dmut wxwidgets_dgettext
#define _nmut wxwidgets_ngettext
#define _dnmut wxwidgets_dngettext
#define bindtextdomain wxwidgets_bindtextdomain
#define textdomain wxwidgets_textdomain
#include "src/kernel/error.h"





#endif /* MU32_DEFS_H */




/** \} */

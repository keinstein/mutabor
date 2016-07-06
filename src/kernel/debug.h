/** \file               -*- C++ -*-
 ********************************************************************
 * Debug routines for mutabor
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
 * \addtogroup debug
 * \{
 ********************************************************************/
/* available groups: GUI, Parser, route, kernel, debug, docview, config, GUIroute */

/* we guard a little bit complicated to ensure the references are set right
 */

#if (!defined(SRC_KERNEL_DEBUG) && !defined(PRECOMPILE)) \
	|| (!defined(SRC_KERNEL_DEBUG_PRECOMPILED))
#ifndef PRECOMPILE
#define SRC_KERNEL_DEBUG
#endif

/* ---------------------------------------------------------------------------
 * headers
 * --------------------------------------------------------------------------- */

#include "src/kernel/Defs.h"
#include "src/wxintl/libintl.h"

#ifndef SRC_KERNEL_DEBUG_PRECOMPILED
#define SRC_KERNEL_DEBUG_PRECOMPILED

/* system headers which do seldom change */


#ifdef __cplusplus
#include <string>
#include <cstdio>
#ifdef __clang__
/* the following line is a workaround for using boost and clang together.
 *  It avoids the following error messages:
 *  In file included from ../../../../../mutabor-git/src/wxintl/libintl.cpp:34:
 *  In file included from ../../../../../mutabor-git/src/wxintl/libintl.h:43:
 * In file included from ../../../../../mutabor-git/src/kernel/Defs.h:86:
 * In file included from ../../../../../mutabor-git/src/kernel/debug.h:56:
 * In file included from /usr/include/boost/format.hpp:19:
 * In file included from /usr/include/boost/detail/workaround.hpp:41:
 * In file included from /usr/include/boost/config.hpp:57:
 * In file included from /usr/include/boost/config/platform/linux.hpp:15:
 * /usr/bin/../lib/gcc/x86_64-linux-gnu/5.2.1/../../../../include/c++/5.2.1/cstdlib:153:11: error: no member named 'realloc' in the
 *       global namespace
 *   using ::realloc;
 *         ~~^
 */
extern "C" {
#include <stdlib.h>
}
//#include <cstdlib>
#define _GLIBCXX_CSTDLIB 1
namespace std {
	using ::free;
	using ::rand;
}
#endif
using std::fflush;
#include "boost/format.hpp"
#else
#include <stdio.h>
#endif

#include <stdint.h>

#ifdef __LINUX__
#include <backtrace.h>
#endif

#ifdef DEBUG

#ifdef __cplusplus
namespace mutabor {
	extern "C" {
#endif

struct mutabor_debug_flagtype {
#       define DEBUGFLAG(flag,description) bool flag:1;
#       include "debugFlags.h"
#       undef DEBUGFLAG
};

extern struct mutabor_debug_flagtype mutabor_debug_flags;

#ifdef __cplusplus
struct debugFlags {

	debugFlags();

	struct nogetflag {
		bool operator()() const { return false; }
	};
	struct nosetflag {
		void operator()(bool) {
		}
	};

#       define DEBUGFLAG(flag,description)				\
	struct get ## flag {						\
		bool operator()() const { return mutabor_debug_flags.flag; } \
	};								\
	struct set ## flag {						\
		void operator()(bool value=true) const {		\
			mutabor_debug_flags.flag = value;		\
		}							\
	};
#       include "debugFlags.h"
#       undef DEBUGFLAG
};

extern debugFlags debugFlagInitialiser;
class Mutex;
extern Mutex debugmutex;
#endif


#ifdef __cplusplus
	}
}
extern "C" {
#endif

/* its easier that these are outside the namespace.
   this prevents us from defining namespacing macros */
void mutabor_debug_lock();
void mutabor_debug_unlock();

#ifdef __cplusplus
#ifdef __GNUC__
#include <cxxabi.h>
	inline std::string DEMANGLE(const std::string & x) {
		int status;
		char * dem = abi::__cxa_demangle(x.c_str(), 0, 0, &status);
		std::string retval;
		switch (status) {
		case 0: /* success */
			if (dem) {
				retval = dem;
				free(dem);
			}
			break;
		case -1: /* Memory allocation failiure */
		case -2: /* not a valid C++ name */
		case -3: /* invalid argument */
			retval = x;
			break;
		}
		return retval;
	}
#define DEMANGLED(x) (DEMANGLE(x).c_str())
#else
#define DEMANGLED(x) (x)
#endif
#else
#define DEMANGLED(x) (x)
#endif

#ifdef __cplusplus
#define GET_ARG_16(a0,a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,...) a15
#define COUNT_ARGS(...) GET_ARG_16(__VA_ARGS__,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1,0)
#define PASTE3(_1,_2,_3) _1 ## _2 ## _3
#define PASTE3a(_1,_2,_3) PASTE3(_1,_2,_3)
#define PASTE2(_1,_2) _1 ## _2
#define PASTE2a(_1,_2) PASTE2(_1,_2)
#define SELECT_MACRO2(_NAME,...) PASTE2a(_NAME, COUNT_ARGS(__VA_ARGS__))
#define SELECT_MACRO(_NAME,...) PASTE2a(_NAME, ISEMPTY(__VA_ARGS__))

#define isDebugFlag(level) (::mutabor::mutabor_debug_flags.level)
#define DEBUGLOGBASEINT(level,strlevel, type, ...)			\
	DEBUGLOGBASEINT2(level,strlevel,type,"%s",			\
			 SELECT_MACRO2(DEBUGLOGBASEINT_,__VA_ARGS__)(__VA_ARGS__))


#define DEBUGLOGBASEINT_1(msgstr) msgstr
#define DEBUGLOGBASEINT_2a(msgstr,arg) boost::str(boost::format(msgstr) % arg).c_str()
#define DEBUGLOGBASEINT_2(msgstr,arg) boost::str(boost::format(msgstr) % (arg)).c_str()
#define DEBUGLOGBASEINT_3(msgstr,_1,_2) DEBUGLOGBASEINT_2a(msgstr, (_1) % (_2))
#define DEBUGLOGBASEINT_4(msgstr,_1,_2,_3) DEBUGLOGBASEINT_2a(msgstr, (_1) % (_2) % (_3))
#define DEBUGLOGBASEINT_5(msgstr,_1,_2,_3,_4) DEBUGLOGBASEINT_2a(msgstr, (_1) % (_2) % (_3) % (_4))
#define DEBUGLOGBASEINT_6(msgstr,_1,_2,_3,_4,_5)			\
	DEBUGLOGBASEINT_2a(msgstr,(_1) % (_2) % (_3) % (_4) % (_5))
#define DEBUGLOGBASEINT_7(msgstr,_1,_2,_3,_4,_5,_6)		      \
	DEBUGLOGBASEINT_2a(msgstr,(_1) % (_2) % (_3) % (_4) % (_5) % (_6))
#define DEBUGLOGBASEINT_8(msgstr,_1,_2,_3,_4,_5,_6,_7)			\
	DEBUGLOGBASEINT_2a(msgstr,(_1) % (_2) % (_3) % (_4) % (_5) % (_6) % (_7))
#define DEBUGLOGBASEINT_9(msgstr,_1,_2,_3,_4,_5,_6,_7,_8)		\
	DEBUGLOGBASEINT_2a(msgstr,(_1) % (_2) % (_3) % (_4) % (_5) % (_6) % (_7) % (_8))
#define DEBUGLOGBASEINT_10(msgstr,_1,_2,_3,_4,_5,_6,_7,_8,_9)		\
	DEBUGLOGBASEINT_2a(msgstr, (_1) % (_2) % (_3) % (_4) % (_5)	\
			  % (_6) % (_7) % ( _8) % (_9))
#define DEBUGLOGBASEINT_11(msgstr,_1,_2,_3,_4,_5,_6,_7,_8,_9,_10)	\
	DEBUGLOGBASEINT_2a(msgstr, (_1) % (_2) % (_3) % (_4) % (_5)	\
			   % (_6) % (_7) % ( _8) % (_9) % (_10))
#define DEBUGLOGBASEINT_12(msgstr,_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11)	\
	DEBUGLOGBASEINT_2a(msgstr, (_1) % (_2) % (_3) % (_4) % (_5)	\
			   % (_6) % (_7) % ( _8) % (_9) % (_10) % (_11))
#define DEBUGLOGBASEINT_13(msgstr,_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12) \
	DEBUGLOGBASEINT_2a(msgstr, (_1) % (_2) % (_3) % (_4) % (_5)	\
			   % (_6) % (_7) % ( _8) % (_9) % (_10) % (_11) % (_12))


#define WATCHEDPTR(T,f,P) watchedPtr<T,debugFlags::get##f,P>
#define DEFWATCHEDPTR /* template <class T,class flag, class P> \
			 const flag watchedPtr<T,flag,P>::myflag;
		      */

#else
#define isDebugFlag(level) (mutabor_debug_flags.level)
# define DEBUGLOGBASEINT(...) DEBUGLOGBASEINT2(__VA_ARGS__)
#endif

# define DEBUGLOGBASEINT2(level,strlevel, type, ...)			\
	do {								\
		if (level) {						\
		    mutabor_debug_lock();				\
		    fprintf(stderr, "%s:%d:%s::%s ",			\
			    __FILE__,					\
                            __LINE__,					\
			    DEMANGLED(type),				\
			    __FUNCTION__);				\
		    fprintf(stderr, __VA_ARGS__);			\
		    fprintf(stderr, " (%s)\n", strlevel);		\
		    fflush(stderr);					\
		    mutabor_debug_unlock();				\
		}							\
	} while (false)



#define STUBBASE(stubtype,classtype)					\
	do {								\
			mutabor_debug_lock();				\
			fprintf(stderr, "%s:%d:%s::%s: %s",		\
				__FILE__,				\
				__LINE__,				\
				classtype,				\
				__FUNCTION__,				\
				stubtype);				\
			fflush(stderr);					\
			mutabor_debug_unlock();				\
	} while (false)


#define mutRefCast(type,value) dynamic_cast<type &>(value)
#define mutPtrCast(type,value) (mutASSERT(dynamic_cast<type *>(value)), dynamic_cast<type *>(value))
#define mutPtrDynCast mutPtrCast

#else /* no DEBUG */

#define STUBBASE(stubtype,classtype)					\
	do {								\
			fprintf(stderr, "%s:%d:%s::%s: %s",		\
				__FILE__,				\
				__LINE__,				\
				classtype,				\
				__FUNCTION__,				\
				stubtype);				\
			fflush(stderr);					\
	} while (false)

#define isDebugFlag(level) false
# define DEBUGLOGBASEINT(...) do {} while (0)
# define PRINTSIZER(X) do {} while (0)

#define mutRefCast(type,value) static_cast<type &>(value)
#define mutPtrCast(type,value) static_cast<type *>(value)
#define mutPtrDynCast(type,value) dynamic_cast<type *>(value)

#define WATCHEDPTR(T,f,P) watchedPtr<T,nogetflag,P>
#define DEFWATCHEDPTR

#endif /* DEBUG */


#define DEBUGLOGBASE(level,type,...) DEBUGLOGBASEINT(isDebugFlag(level),#level,type,__VA_ARGS__)
#define DEBUGLOG(level,...) DEBUGLOGBASE(level, typeid(*this).name(),__VA_ARGS__)
#define DEBUGLOG2(level,...) DEBUGLOGBASE(level, "",__VA_ARGS__)
#define DEBUGLOGTYPE(level, type,...) DEBUGLOGBASE(level, typeid(type).name(), __VA_ARGS__)
#define DEBUGLOGTYPEINT(level, strlevel,type,...) DEBUGLOGBASEINT(level, strlevel, typeid(type).name(), __VA_ARGS__)

#define TRACE DEBUGLOGBASE(trace,"",".")
#define TRACEC DEBUGLOG(trace,".")
#define TRACET(type) DEBUGLOGTYPE(trace,type,".")


#define STUB STUBBASE("stub.", "")
#define STUBCT(type) STUBBASE("stub.",((const char *) (typeid(type).name())))
#define STUBC STUBCT(*this)

#define UNREACHABLE STUBBASE("unreachable code","")
#define UNREACHABLECT(type) STUBBASE("unreachable code",((const char *) (typeid(type).name())))
#define UNREACHABLEC UNREACHABLECT(*this)

#define ABSTRACT_FUNCTION STUBBASE("unreachable function","")
#define ABSTRACT_FUNCTIONCT(type) STUBBASE("unreachable function",((const char *) (typeid(type).name())))
#define ABSTRACT_FUNCTIONC ABSTRACT_FUNCTIONCT(*this)



#ifdef __cplusplus
#ifdef DEBUG
}
#endif
struct nogetflag {
		bool operator()() const { return false; }
};

template <class T,class flag, class P>
class watchedPtr {
private:
	typedef T datatype;
	typedef T* dataptr;
	typedef P parenttype;
	datatype * data;
#ifdef DEBUG
/*	static const flag myflag; */
	parenttype * parent;
	std::string name;
#endif
public:
	watchedPtr(parenttype * p, const std::string & varname = "watchedPtr", datatype * d = NULL)
	{
#ifdef DEBUG
		parent = p;
		name = varname;
#endif
		DEBUGLOGTYPEINT(flag()(),"???",parenttype,"nothing");
		(*this) = d;
	}

	watchedPtr<T,flag,P> &operator= (datatype * d)
	{
		DEBUGLOGTYPEINT(flag()(),"???",parenttype,
				"Setting %s in %p from %p to %p",
				name,(void*)parent,(void*)data,d);
		data = d;
		return *this;
	}


	operator dataptr () const
	{
		return data;
	}

#if 0
	datatype & operator -> ()
	{
		return *data;
	}

	const datatype & operator -> () const
	{
		return *data;
	}
#endif
};


#ifdef DEBUG
extern "C" {
void debug_destroy_class(void * ptr, std::string file, int l);
void debug_destruct_class(void * ptr);
void debug_print_pointers();
bool debug_is_all_deleted();
void print_stacktrace (bool flag);
}
class mutabor_backtrace: public std::vector<uintptr_t> {
public:
	typedef std::vector<uintptr_t> base;
	mutabor_backtrace(int omit_count = 0);
	~mutabor_backtrace();
	void set_print (bool p = true) { print = p; }
	static void set_global_print(bool p = true) { global_print = p; }
	static bool get_global_print() { return global_print; }
protected:
	bool print;
	static bool global_print;
	static struct backtrace_state * state;
};
#else
extern "C" {
inline void debug_destroy_class(void * ptr, std::string file, int l) {}
inline void debug_destruct_class(void * ptr) {}
inline void debug_print_pointers() {}
inline bool debug_is_all_deleted() { return true; }
inline void print_stacktrace (bool flag){}
}

class mutabor_backtrace {
public:
	typedef mutabor_backtrace base;
	mutabor_backtrace(int omit_count = 0) {}
	void set_print (bool p = true) {  }
	static void set_global_print(bool p = true) {  }
};

#endif
#define debug_destroy_class(ptr) debug_destroy_class(ptr,__FILE__,__LINE__)


#endif


#ifdef MUTABOR_TEST
extern const char * srcdir;
extern const char * top_srcdir;
extern const char * top_builddir;

std::string StreamToHex(std::istream & buf);
#endif

#endif /* precompiled */
#endif /* header loaded */


/** \} */

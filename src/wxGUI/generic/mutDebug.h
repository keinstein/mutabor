/** \file 
 ********************************************************************
 * Main debugging functions
 *
 * Copyright:   (c) 2008 TU Dresden
 * \author  Tobias Schlemmer <keinstein@users.berlios.de>
 * \license GPL
 *
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
 * \defgroup debug Debugging functions 
 *
 * This group contains the functions that are used to help debugging
 * of Mutabor. Despite the core is written in C these functions are
 * written in C++ but can easily replaced by C.
 * 
 * \{
 ********************************************************************/
/*
 *  mutDebug.h
 *  Mutabor
 *
 *  Created by Tobias Schlemmer on 25.03.10.
 *  Copyright 2010 TU Dresden. All rights reserved.
 *
 */

#ifndef __MUTDEBUGFLAGS__
#define __MUTDEBUGFLAGS__

#ifdef DEBUG


#include <bitset>
#include <iostream>
#include <cstdio>
#include "wx/cmdline.h"
#include "wx/string.h"
#include "wx/debug.h"
#pragma GCC diagnostic ignored "-Wvariadic-macros"

#ifdef WX
#include "wx/thread.h"
typedef wxMutex debugMutex;
typedef wxMutexLocker debugScopedLock;
#endif

void MutInitConsole();

struct debugFlags {
	struct flagtype {

		flagtype();

#       define DEBUGFLAG(flag,description) bool flag:1;
#       include "mutDebugFlags.h"
#       undef DEBUGFLAG
	};

	struct nogetflag {
		bool operator()() const { return false; }
	};
	struct nosetflag {
		void operator()(bool) {
		}
	};

#       define DEBUGFLAG(flag,description)			\
	struct get ## flag {					\
		bool operator()() const { return flags.flag; }	\
	};							\
	struct set ## flag {					\
		void operator()(bool value=true) const {	\
			flags.flag = value;			\
		}						\
	};
#       include "mutDebugFlags.h"
#       undef DEBUGFLAG
	
	static flagtype flags;


	static void InitCommandLine(wxCmdLineParser&  parser);
	static void ProcessCommandLine(wxCmdLineParser&  parser);
};

extern debugMutex debugmutex;

#define isDebugFlag(level) (debugFlags::flags.level)
# define DEBUGLOGBASEINT(level,strlevel, type,...)			\
	do {								\
		if (level) {						\
			debugScopedLock lock(debugmutex);		\
			if (!std::clog.good()) MutInitConsole();	\
			wxASSERT(std::clog.good());			\
			std::clog << __FILE__ << ":" << __LINE__	\
				  << ": " << ((const char *) type)	\
				  << "::" << __WXFUNCTION__ << ": ";	\
			std::clog << (const char *)(wxString::Format( __VA_ARGS__ ).ToUTF8()) \
				  << " (" << strlevel << ")"	\
				  << std::endl;				\
			std::clog.flush();				\
		}							\
	} while (false)
#define DEBUGLOGBASE(level,type,...) DEBUGLOGBASEINT(debugFlags::flags.level,#level,type,__VA_ARGS__)
#define mutRefCast(type,value) dynamic_cast<type &>(value)
#define mutPtrCast(type,value) (wxASSERT(dynamic_cast<type *>(value)), dynamic_cast<type *>(value))
#define mutPtrDynCast mutPtrCast
#else

struct nogetflag {
		bool operator()() const { return false; }
};

#define isDebugFlag(level) false
# define DEBUGLOGBASEINT(...) do {} while (0)
# define DEBUGLOGBASE(...) do {} while (0)
# define PRINTSIZER(X) do {} while (0)

#define mutRefCast(type,value) static_cast<type &>(value)
#define mutPtrCast(type,value) static_cast<type *>(value)
#define mutPtrDynCast(type,value) dynamic_cast<type *>(value)

#endif

#define DEBUGLOG(level,...) DEBUGLOGBASE(level, typeid(*this).name(),__VA_ARGS__)
#define DEBUGLOG2(level,...) DEBUGLOGBASE(level, _T(""),__VA_ARGS__)
#define DEBUGLOGTYPE(level, type,...) DEBUGLOGBASE(level, typeid(type).name(), __VA_ARGS__)
#define DEBUGLOGTYPEINT(level, strlevel,type,...) DEBUGLOGBASEINT(level, strlevel, typeid(type).name(), __VA_ARGS__)
#define TRACE DEBUGLOGBASE(trace,_T(""),_T("."))
#define TRACEC DEBUGLOG(trace,_T("."))
#define TRACET(type) DEBUGLOGTYPE(trace,type,_T("."))

template <class T,class flag, class P>
class watchedPtr {
private:
	typedef T datatype;
	typedef T* dataptr;
	typedef P parenttype;
	datatype * data;
#ifdef DEBUG
//	static const flag myflag;
	parenttype * parent;
	wxString name;
#endif
public:
	watchedPtr(parenttype * p, const wxString & varname = _T("watchedPtr"), datatype * d = NULL)
	{
#ifdef DEBUG
		parent = p;
		name = varname;
#endif
		(*this) = d;
	}
	
	watchedPtr<T,flag,P> &operator= (datatype * d)
	{
		DEBUGLOGTYPEINT(flag()(),"???",parenttype,
				_T("Setting %s in %p from %p to %p"),
				name.c_str(),(void*)parent,(void*)data,d);
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

//template <class T,class flag, class P>
//        const flag watchedPtr<T,flag,P>::myflag;

#define WATCHEDPTR(T,f,P) watchedPtr<T,debugFlags::get##f,P>
#define DEFWATCHEDPTR /* template <class T,class flag, class P> \
			 const flag watchedPtr<T,flag,P>::myflag;
		      */
#else
#define WATCHEDPTR(T,f,P) watchedPtr<T,nogetflag,P>
#define DEFWATCHEDPTR
#endif


#ifdef DEBUG
void debug_destroy_class(void * ptr, std::string file, int l);
void debug_destruct_class(void * ptr);
void debug_print_pointers();
bool debug_is_all_deleted();
void print_stacktrace ();
#else 
inline void debug_destroy_class(void * ptr, std::string file, int l) {}
inline void debug_destruct_class(void * ptr) {}
inline void debug_print_pointers() {}
inline bool debug_is_all_deleted() { return true; }
inline void print_stacktrace (){}
#endif
#define debug_destroy_class(ptr) debug_destroy_class(ptr,__FILE__,__LINE__)

void mutAssertFailure(const wxChar *file,
		      int line,
		      const wxChar *func,
		      const wxChar *cond,
		      const wxChar *msg);

#ifdef MUTABOR_TEST
extern const wxChar * srcdir;
extern const wxChar * top_srcdir;
extern const wxChar * top_builddir;

wxString StreamToHex(wxStreamBuffer * buf);
#endif

#endif

///\}

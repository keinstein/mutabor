/** \file 
 ********************************************************************
 * Description
 *
 * $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/mywx/mutDebug.h,v 1.9 2011/10/04 20:09:16 keinstein Exp $
 * Copyright:   (c) 2008 TU Dresden
 * \author  Tobias Schlemmer <keinstein@users.berlios.de>
 * \date 
 * $Date: 2011/10/04 20:09:16 $
 * \version $Revision: 1.9 $
 * \license GPL
 *
 * $Log: mutDebug.h,v $
 * Revision 1.9  2011/10/04 20:09:16  keinstein
 * Clean up focus handling a little bit.
 * Change perimeter point handling a little bit. Need at least one night to
 * get overthought.
 *
 * Revision 1.8  2011-10-04 17:16:14  keinstein
 * make program compile on Mac (wx 2.9) and fix some memory corruption
 *
 * Revision 1.7  2011-10-03 20:03:27  keinstein
 * add missing struct nogetflag
 *
 * Revision 1.6  2011-10-02 16:58:42  keinstein
 * * generate Class debug information when compile in debug mode
 * * InputDeviceClass::Destroy() prevented RouteClass::Destroy() from clearing references -- fixed.
 * * Reenable confirmation dialog when closing document while the logic is active
 * * Change debug flag management to be more debugger friendly
 * * implement automatic route/device deletion check
 * * new debug flag --debug-trace
 * * generate lots of tracing output
 *
 * Revision 1.5  2011-08-21 16:52:05  keinstein
 * Integrate a more sophisticated editor menu based on the stc sample
 *
 * Revision 1.4  2011-02-20 22:35:59  keinstein
 * updated license information; some file headers have to be revised, though
 *
 *
 *
 ********************************************************************
 * \addtogroup debug
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
		void operator()(bool value=true) {
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



#define isDebugFlag(level) (debugFlags::flags.level)
# define DEBUGLOGBASEINT(level,type, ...)				\
	do {								\
		wxASSERT(std::cerr.good());				\
		if (level) {						\
			std::fprintf(stderr,"[Debug] ");		\
			wxASSERT(std::clog.good());			\
			std::clog << __FILE__ << ":" << __LINE__	\
				  << ": " << ((const char *) type)	\
				  << "::" << __WXFUNCTION__ << ": ";	\
			std::clog.flush();				\
			std::clog << (const char *)((wxString::Format(__VA_ARGS__)).ToUTF8()) << std::endl; \
			std::clog.flush();				\
			if (std::clog.eof()) {				\
				std::clog.clear();			\
				std::clog << "Error: std::clog.eof()";	\
				abort();				\
			}						\
			if (std::clog.fail()) {				\
				std::clog.clear();			\
				std::clog << "Error: std::clog.fail()";	\
				abort();				\
			}						\
			if (std::clog.bad()) {				\
				std::clog.clear();			\
				std::clog << "Error: std::clog.eof()";	\
				abort();				\
			}						\
			if (!std::clog.good()) {			\
				std::clog.clear();			\
				std::clog << "Error: std::clog.eof()";	\
				abort();				\
			}						\
									\
		}							\
	} while (false)
#define DEBUGLOGBASE(level,...) DEBUGLOGBASEINT(debugFlags::flags.level,__VA_ARGS__)
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

#define DEBUGLOG(level, ...) DEBUGLOGBASE(level, typeid(*this).name(),__VA_ARGS__)
#define DEBUGLOG2(level, ...) DEBUGLOGBASE(level, _T(""),__VA_ARGS__)
#define DEBUGLOGTYPE(level, type, ...) DEBUGLOGBASE(level, typeid(type).name(), __VA_ARGS__)
#define DEBUGLOGTYPEINT(level, type, ...) DEBUGLOGBASEINT(level, typeid(type).name(), __VA_ARGS__)
#define TRACE DEBUGLOGBASE(trace,_T(""),_T(""))
#define TRACEC DEBUGLOG(trace,_T(""))
#define TRACET(type) DEBUGLOGTYPE(trace,type,_T(""))

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
		DEBUGLOGTYPEINT(flag()(),parenttype,_T("Setting %s in %p from %p to %p"),name.c_str(),parent,data,d);
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
void debug_destroy_class(void * ptr);
void debug_destruct_class(void * ptr);
void debug_print_pointers();
bool debug_is_all_deleted();
#else 
inline void debug_destroy_class(void * ptr) {}
inline void debug_destruct_class(void * ptr) {}
inline void debug_print_pointers() {}
inline bool debug_is_all_deleted() { return true; }
#endif

#endif

///\}

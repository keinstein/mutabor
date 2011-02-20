/** \file 
 ********************************************************************
 * Description
 *
 * $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/mywx/mutDebug.h,v 1.4 2011/02/20 22:35:59 keinstein Exp $
 * Copyright:   (c) 2008 TU Dresden
 * \author  Tobias Schlemmer <keinstein@users.berlios.de>
 * \date 
 * $Date: 2011/02/20 22:35:59 $
 * \version $Revision: 1.4 $
 * \license GPL
 *
 * $Log: mutDebug.h,v $
 * Revision 1.4  2011/02/20 22:35:59  keinstein
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
#include "wx/cmdline.h"

#define DEBUGFLAG(flag,description) flag,

struct debugFlags {
	enum {
#include "mutDebugFlags.h"
		debugFlagCount
	};
	typedef std::bitset<debugFlagCount> debugFlagSet;
	static debugFlagSet flags;
	static void InitCommandLine(wxCmdLineParser&  parser);
	static void ProcessCommandLine(wxCmdLineParser&  parser);
};
#undef DEBUGFLAG

#define isDebugFlag(level) (debugFlags::flags[debugFlags::level])
# define DEBUGLOGBASEINT(level,type, ...) \
        if (debugFlags::flags[level]) { \
                 std::cerr << __FILE__ << ":" << __LINE__ << ": " \
                           << ((const char *) type) << "::" << __WXFUNCTION__ << ": "	\
                           << (const char *)((wxString::Format(__VA_ARGS__)).ToUTF8()) << std::endl; \
	}
#define DEBUGLOGBASE(level,...) DEBUGLOGBASEINT(debugFlags::level,__VA_ARGS__)
#define mutRefCast(type,value) dynamic_cast<type &>(value)
#define mutPtrCast(type,value) (wxASSERT(dynamic_cast<type *>(value)), dynamic_cast<type *>(value))
#define mutPtrDynCast mutPtrCast
#define WATCHEDPTR(T,f,P) watchedPtr<T,debugFlags::f,P>
#define DEFWATCHEDPTR \
        template <class T,int flag, class P> \
        const int watchedPtr<T,flag,P>::myflag = flag;
#else

#define isDebugFlag(level) false
# define DEBUGLOGBASEINT(...) do {} while (0)
# define DEBUGLOGBASE(...) do {} while (0)
# define PRINTSIZER(X) do {} while (0)

#define mutRefCast(type,value) static_cast<type &>(value)
#define mutPtrCast(type,value) static_cast<type *>(value)
#define mutPtrDynCast(type,value) dynamic_cast<type *>(value)

#define WATCHEDPTR(T,f,P) watchedPtr<T,-1,P>
#define DEFWATCHEDPTR
#endif

#define DEBUGLOG(level, ...) DEBUGLOGBASE(level, typeid(*this).name(),__VA_ARGS__)
#define DEBUGLOG2(level, ...) DEBUGLOGBASE(level, _T(""),__VA_ARGS__)
#define DEBUGLOGTYPE(level, type, ...) DEBUGLOGBASE(level, typeid(type).name(), __VA_ARGS__)
#define DEBUGLOGTYPEINT(level, type, ...) DEBUGLOGBASEINT(level, typeid(type).name(), __VA_ARGS__)

template <class T,int flag, class P>
class watchedPtr {
private:
	typedef T datatype;
	typedef T* dataptr;
	typedef P parenttype;
	datatype * data;
#ifdef DEBUG
	static const int myflag;
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
		DEBUGLOGTYPEINT(myflag,parenttype,_T("Setting %s in %p from %p to %p"),name.c_str(),parent,data,d);
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

DEFWATCHEDPTR



#endif

///\}

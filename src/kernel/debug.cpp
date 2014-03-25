/** \file               -*- C++ -*-
********************************************************************
* Debugging routines
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
* \addtogroup debug
* \{
********************************************************************/
/* available groups: GUI, Parser, route, kernel, debug, docview, config, GUIroute */

/* we guard a little bit complicated to ensure the references are set right
 */

#if (!defined(HEADERFILENAME) && !defined(PRECOMPILE))		      \
	|| (!defined(HEADERFILENAME_PRECOMPILED))
#ifndef PRECOMPILE
#define HEADERFILENAME
#endif

/* ---------------------------------------------------------------------------
 * headers
 * --------------------------------------------------------------------------- */

#include "src/kernel/Defs.h"
#include "src/kernel/routing/thread.h"
/** \todo move thread.h into src/kernel */


#ifndef HEADERFILENAME_PRECOMPILED
#define HEADERFILENAME_PRECOMPILED

/* system headers which do seldom change */
#ifdef DEBUG
#include <list>
#include <cstring>
#include <sstream>
#include <iomanip>
#include <cstdio>
#if __LINUX__
#include "backtrace.h"
#endif
#endif



#ifdef DEBUG
bool mutabor_backtrace::global_print = false;

namespace mutabor {
	extern "C" {

		struct mutabor_debug_flagtype mutabor_debug_flags;
		debugFlags debugFlagInitialiser;

		mutabor::debugFlags::debugFlags()
		{
#define DEBUGFLAG(flag,description)					\
			mutabor::mutabor_debug_flags.flag = false;
#include "src/kernel/debugFlags.h"
#undef DEBUGFLAG
			mutabor::mutabor_debug_flags.always = true;
			// manual overrides for debug purposes
			//	flags.smartptr = true;
		}

		static Mutex debugmutex;
	}
}

extern "C" {
	void mutabor_debug_lock() {
		mutabor::debugmutex.Lock();
	}
	void mutabor_debug_unlock() {
		mutabor::debugmutex.Unlock();
	}


	struct ptrlist_item {
		void * ptr;
		std::string file;
		int line;
		ptrlist_item(void * p, std::string &f, int l):ptr(p),
							      file(f),
							      line(l) {}
		bool operator == (void * p) const { return ptr == p ; }
		bool operator < (void * p) const { return ptr < p ; }
	};

	typedef std::list<ptrlist_item> ptrlist;
	static ptrlist debug_save_pointers;

#undef debug_destroy_class
	void debug_destroy_class(void * ptr, std::string file, int l)
	{
		mutASSERT(std::find(debug_save_pointers.begin(),
				    debug_save_pointers.end(),
				    ptr)
			  == debug_save_pointers.end());
		debug_save_pointers.push_back(ptrlist_item(ptr,file,l));
	}

	void debug_destruct_class(void * ptr)
	{
		ptrlist::iterator i = std::find(debug_save_pointers.begin(),
						debug_save_pointers.end(),
						ptr);
		mutASSERT(i!=debug_save_pointers.end());
		if (i != debug_save_pointers.end())
			debug_save_pointers.erase (i);
	}
	void debug_print_pointers()
	{
		for (ptrlist::iterator i = debug_save_pointers.begin();
		     i != debug_save_pointers.end();
		     i++) {
			fprintf(stderr, "\n%s:%d:\nUndeleted pointer: %p",
				i->file.c_str(),
				i->line,
				i->ptr);
		}
		fprintf(stderr,"\n");
	}
	bool debug_is_all_deleted()
	{
		return debug_save_pointers.empty();
	}


	static void
	mutabor_backtrace_error_callback (void *data, const char *msg, int errnum)
	{
		fprintf (stderr, "backtrace: %s: (%d) %s\n",
			 msg,
			 errnum,
			 errnum>0?std::strerror (errnum):"");
	}


	static int mutabor_backtrace_print_callback (void *data,
						     uintptr_t pc,
						     const char *filename,
						     int lineno,
						     const char *function)
	{
		fprintf (stderr, "%s:%d:\n\t0x%lx: %s \n",
			 filename == NULL ? "???" : filename,
			 lineno,
			 (unsigned long) pc,
			 function == NULL ? "???" : function);
		return 0;
	}
	int mutabor_backtrace_simple_print_callback (void *data,
						     uintptr_t pc)
	{
		fprintf (stderr, "%lx \n",
			 (unsigned long) pc);
		return 0;
	}



	void print_stacktrace (bool flag) {
		if (!flag) return;
#if __LINUX__
		backtrace_state * state = backtrace_create_state(NULL,
								 false,
								 &mutabor_backtrace_error_callback,
								 NULL);
#if 1
		fprintf(stderr,"Stack trace:");
		backtrace_full (state,
				1,
				mutabor_backtrace_print_callback,
				mutabor_backtrace_error_callback,
				NULL);
#else
		backtrace_simple(state,
				 1,
				 mutabor_backtrace_simple_print_callback,
				 mutabor_backtrace_error_callback,
				 NULL);
#endif

		//	backtrace_print(state,0,stderr);
		//	__asan_backtrace_free (state);
#endif
#if 0
		int j, nptrs;
		const int size = 100;
		void *buffer[size];
		char **strings;

		nptrs = backtrace(buffer, size);
		fprintf(stderr,"backtrace() returned %d addresses\n", nptrs);

		/* The call backtrace_symbols_fd(buffer, nptrs, STDOUT_FILENO)
		   would produce similar output to the following: */

		strings = backtrace_symbols_fd(stderr, buffer, nptrs);
		// in case we implement our own backtrace function
		if (strings == NULL) {
			perror("backtrace_symbols");
			return;
		}

		for (j = 0; j < nptrs; j++)
			printf("%s\n", strings[j]);

		free(strings);
#endif
	}



	static int mutabor_save_backtrace_callback (void *data,
						    uintptr_t pc)
	{
		mutabor_backtrace * obj
			= reinterpret_cast<mutabor_backtrace *> (data);
		if (obj)
			obj->push_back(pc);
		return 0;
	}


#endif


	void MutInitConsole()
	{
#if __WXMSW__
		// taken from http://www.halcyon.com/~ast/dload/guicon.htm
		static const WORD MAX_CONSOLE_LINES = 500;

		int hConHandle;
		long lStdHandle;
		CONSOLE_SCREEN_BUFFER_INFO coninfo;
		FILE *fp;

		// allocate a console for this app
		AllocConsole();

		// set the screen buffer to be big enough to let us scroll text
		GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE),
					   &coninfo);
		coninfo.dwSize.Y = MAX_CONSOLE_LINES;
		SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE),
					   coninfo.dwSize);

		// redirect unbuffered STDOUT to the console
		lStdHandle = (long)GetStdHandle(STD_OUTPUT_HANDLE);
		hConHandle = _open_osfhandle(lStdHandle, _O_TEXT);
		fp = _fdopen( hConHandle, "w" );
		*stdout = *fp;
		setvbuf( stdout, NULL, _IONBF, 0 );

		// redirect unbuffered STDIN to the console
		lStdHandle = (long)GetStdHandle(STD_INPUT_HANDLE);
		hConHandle = _open_osfhandle(lStdHandle, _O_TEXT);

		fp = _fdopen( hConHandle, "r" );
		*stdin = *fp;
		setvbuf( stdin, NULL, _IONBF, 0 );

		// redirect unbuffered STDERR to the console
		lStdHandle = (long)GetStdHandle(STD_ERROR_HANDLE);
		hConHandle = _open_osfhandle(lStdHandle, _O_TEXT);
		fp = _fdopen( hConHandle, "w" );
		*stderr = *fp;
		setvbuf( stderr, NULL, _IONBF, 0 );

		// make cout, wcout, cin, wcin, wcerr, cerr, wclog and clog
		// point to console as well
		std::ios::sync_with_stdio();
#endif
	}


	// execute as early as possible
	class consoleinit {
	public:
		consoleinit() {
			MutInitConsole();
		}
	} g_consoleinit;


}

#ifdef DEBUG

struct backtrace_state * mutabor_backtrace::state =
	backtrace_create_state(NULL,
			       true,
			       &mutabor_backtrace_error_callback,
			       NULL);

mutabor_backtrace::mutabor_backtrace(int omit_count):base(0),
						     print(false)
{
	reserve(10);

	backtrace_simple(state,
			 omit_count + 1,
			 mutabor_save_backtrace_callback,
			 mutabor_backtrace_error_callback,
			 reinterpret_cast<void *>(this));
}

mutabor_backtrace::~mutabor_backtrace() {
	if (!(print && global_print))
		return;

	fprintf(stderr,"Stack trace:");
	for (base::iterator i = begin();
	     i!= end(); ++i) {
		backtrace_pcinfo (state,
				  *i,
				  mutabor_backtrace_print_callback,
				  mutabor_backtrace_error_callback,
				  NULL);
	}
}

#endif



#endif /* precompiled */
#endif /* header loaded */

std::string StreamToHex(std::istream & buf)
{
	std::ostringstream retval;
	if (buf.bad())
		return "";

	buf.seekg(0);

	int tmpchar = buf.get();
	for (size_t i = 1 ; !buf.eof() ; i++) {
		retval << "  "
		       << std::hex << std::setfill('0')
		       << std::setw (2) << tmpchar
		       << " ";

		if (32 <= tmpchar && tmpchar < 127)
			retval << (char)tmpchar;
		else
			retval << "·";

		tmpchar = buf.get();
		if (buf.fail()) break;

		if (!(i % 16)) {
			retval << "\n";
		}
		else if (!(i % 8)) {
			retval << "  ";
		}
	}
	retval << "\n";
	return retval.str();
}

/** \} */

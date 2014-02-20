/** \file
 ********************************************************************
 * Some functions and classes to help to debug Mutabor
 *
 * Copyright:   (c) 2010,2011 TU Dresden
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
 ********************************************************************
 * \addtogroup debug
 * \{
 ********************************************************************/
/*
 *  mutDebug.cpp
 *  Mutabor
 *
 *  Created by Tobias Schlemmer on 25.03.10.
 *  Copyright 2010 TU Dresden. All rights reserved.
 *
 */

#include "src/kernel/Defs.h"
#include "src/wxGUI/MutApp.h"
#include "wx/apptrait.h"
#include "wx/log.h"
#ifdef DEBUG
#ifdef MUTABOR_CPPUNIT
#include "cppunit/extensions/HelperMacros.h"
#include "cppunit/Portability.h"
#include "cppunit/Asserter.h"
#include "cppunit/Message.h"
#include "cppunit/SourceLine.h"
#endif
#include "mutDebug.h"
#include <list>
#if __WXMSW__
#include <iostream>
#include <fstream>
#include <conio.h>
#include <stdio.h>
#endif
#if __LINUX__
#include <backtrace.h>
#endif

#include "src/kernel/routing/Route-inlines.h"

debugFlags::flagtype debugFlags::flags;


debugFlags::flagtype::flagtype()
{
#define DEBUGFLAG(flag,description)				      \
	flags.flag = false;
#include "mutDebugFlags.h"
#undef DEBUGFLAG
	flags.always = true;
	// manual overrides for debug purposes
	//	flags.smartptr = true;
}


void debugFlags::InitCommandLine(wxCmdLineParser&  parser)
{
#if wxCHECK_VERSION(2,9,0)
#  ifdef N_
#    undef N_
#  endif
#  define N_(text) text
#  define DEBUGFLAG(flag,description)					\
        { wxCMD_LINE_SWITCH, "", ("debug-"#flag), (description) },
#else
#  define DEBUGFLAG(flag,description)					\
	{ wxCMD_LINE_SWITCH, wxEmptyString, _T("debug-"#flag), description },
#endif
	static const wxCmdLineEntryDesc cmdLineDesc[] =
		{
#include "mutDebugFlags.h"
			{ wxCMD_LINE_NONE }
		};
#undef DEBUGFLAG
	parser.SetDesc(cmdLineDesc);
}

void debugFlags::ProcessCommandLine(wxCmdLineParser&  parser)
{
#define DEBUGFLAG(flag,description)					\
	debugFlags::flags.flag = parser.Found(_T("debug-"#flag));
#include "mutDebugFlags.h"
#undef DEBUGFLAG
	debugFlags::flags.always = true;
}

debugMutex debugmutex;

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
		 errnum>0?strerror (errnum):"");
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


bool mutabor_backtrace::global_print = false;

static int mutabor_save_backtrace_callback (void *data,
					    uintptr_t pc)
{
	mutabor_backtrace * obj
		= reinterpret_cast<mutabor_backtrace *> (data);
	if (obj)
		obj->push_back(pc);
	return 0;
}

mutabor_backtrace::mutabor_backtrace(int omit_count):base(0),
						     print(false)
{
	reserve(10);

	state = backtrace_create_state(NULL,
				       false,
				       &mutabor_backtrace_error_callback,
				       reinterpret_cast<void *>(this));
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

#ifndef MUTABOR_CPPUNIT
static bool DoShowAssertDialog(const wxString& msg)
{
	// under MSW we can show the dialog even in the console mode
#if defined(__WXMSW__) && !defined(__WXMICROWIN__)
	wxString msgDlg(msg);

	// this message is intentionally not translated -- it is for
	// developpers only
	msgDlg += wxT("\nDo you want to stop the program?\n")
		wxT("You can also choose [Cancel] to suppress ")
		wxT("further warnings.");

	switch ( ::MessageBox(NULL, msgDlg, _T("wxWidgets Debug Alert"),
			      MB_YESNOCANCEL | MB_ICONSTOP ) )
		{
		case IDYES:
			wxTrap();
			break;

		case IDCANCEL:
			// stop the asserts
			return true;

			//case IDNO: nothing to do
		}
#else // !__WXMSW__
	wxFprintf(stderr, wxT("%s\n"), msg.c_str());
	fflush(stderr);

	// TODO: ask the user to enter "Y" or "N" on the console?
	wxTrap();
#endif // __WXMSW__/!__WXMSW__

	// continue with the asserts
	return false;
}
#endif


void mutAssertFailure(const wxChar *file,
		      int line,
		      const wxChar *func,
		      const wxChar *cond,
		      const wxChar *msg)
{
#ifdef MUTABOR_CPPUNIT
	{
		CPPUNIT_NS::Message mesg( "assertion failed",
					  std::string(wxString::Format(_T("%s:%d:%s\nFunction: %s; Expression: %s"),
								       file,
								       line,
								       (msg?msg:_T("")),
								       func,
								       cond).ToUTF8()));

		wxString filename(file);
		CPPUNIT_NS::Asserter::fail(mesg,
					   CPPUNIT_NS::SourceLine(std::string(filename.ToUTF8()), line )
					   );
	}

#else
	if (!std::clog.good()) MutInitConsole();
	wxString s = wxString::Format(_("%s:%d: An assert failed in %s().\nCondition: %s\nMessage:%s\nDo you want to call the default assert handler?"),
				      file,line,func,cond,msg);
	std::clog << (const char *) s.ToUTF8() << std::endl;


	// use wxWidgets ShowAssertDialog function (it's static so we repeat its code, here.

	{
		// this variable can be set to true to suppress "assert failure" messages
		static bool s_bNoAsserts = false;

		wxString message;
 		message.reserve(2048);

		// here, we change format to the gcc form
		message.Printf(wxT("%s:%d: assert \"%s\" failed"), file, line, cond);

		// add the function name, if any
		if ( func && *func )
			message << _T(" in ") << func << _T("()");

		// and the message itself
		if ( msg )
			{
				message << _T(": ") << msg;
			}
		else // no message given
			{
				message << _T('.');
			}

#if wxUSE_THREADS
		// if we are not in the main thread, output the assert directly and trap
		// since dialogs cannot be displayed
		if ( !wxThread::IsMain() )
			{
				message += wxT(" [in child thread]");

#if defined(__WXMSW__) && !defined(__WXMICROWIN__)
				message << wxT("\r\n");
				OutputDebugString(message );
#else
				// send to stderr
				wxFprintf(stderr, wxT("%s\n"), message.c_str());
				fflush(stderr);
#endif
				// He-e-e-e-elp!! we're asserting in a child thread
				wxTrap();
			}
		else
#endif // wxUSE_THREADS

			if ( !s_bNoAsserts )
				{
					// send it to the normal log destination
					wxLogDebug(_T("%s"), message.c_str());

#ifdef __WXDEBUG__
					if ( wxGetApp().GetTraits() )
						{
							// delegate showing assert dialog (if possible) to that class
							s_bNoAsserts = wxGetApp().GetTraits()->ShowAssertDialog(message);
						}
					else // no traits object
#endif
						{
							// fall back to the function of last resort
							s_bNoAsserts = DoShowAssertDialog(message);
						}
				}
	}
#endif
}

#ifdef MUTABOR_TEST
mutString StreamToHex(mutStreamBuffer * buf)
{
	mutString retval;
	if (!buf)
		return retval;
	if (buf->Seek(0,wxFromStart) == wxInvalidOffset)
		return retval;

	size_t max = buf->GetDataLeft();
	retval.Alloc(6*max);
	unsigned char * start = (unsigned char *)buf->GetBufferStart();
	unsigned char * end = start + max;
	wxChar tmpchar;
	wxString clearstring;
	clearstring.Alloc(9);

	for (unsigned char * i = start; i < end ; i++ ) {
		if ((i-start) && !((i-start)%16)){
#if 0 
			retval += _T("   ") + clearstring + _T("\n");
			clearstring = _T("");
			clearstring.Alloc(9);
#else
			retval += _T("\n");
#endif
		}
		else if ((i-start) && !((i-start)%8)) {
			retval += _T("  ");
#if 0
			clearstring += _T(" ");
#endif
		}
		retval += wxString::Format(_T("  %02x "),*i);
		tmpchar = *i;
#if 0
		if (32 <= tmpchar && tmpchar < 127)
			clearstring += tmpchar;
		else
			clearstring += _T("·");
#else
		if (32 <= tmpchar && tmpchar < 127)
			retval += tmpchar;
		else
			retval += _T("·");
#endif
	}
#if 0
	for (size_t j = 15-((end-start+15) % 16); j ; j--) {
		retval += _T("   ");
	}
	//	retval += wxString :: Format(_T("  %d/%d  "),(end-start), (end-start)%16);
	if ((end-start+15)%16 < 8 )
		retval += _T(" ");

	retval += _T("   ") + clearstring + _T("\n");
#else
	retval +=_T("\n");
#endif
	return retval;
}
#endif


///\}

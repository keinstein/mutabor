/** \file
 ********************************************************************
 * Some functions and classes to help to debug Mutabor
 *
 * Copyright:   (c) 2010,2011 TU Dresden
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

#include "mutDebug.h"
#include <list>
#if __WXMSW__
#include <iostream>
#include <fstream>
#include <conio.h>
#include <stdio.h>
#endif

#include "src/kernel/routing/Route-inlines.h"

#ifdef DEBUG
void InitDebugCommandLine(wxCmdLineParser&  parser)
{
#if wxCHECK_VERSION(2,9,0)
#  ifdef N_
#    undef N_
#  endif
#  define N_(text) text
#  define DEBUGFLAG(flag,description)					\
        { wxCMD_LINE_SWITCH, "", ("debug-"#flag), (description),	\
	  wxCMD_LINE_VAL_NONE, wxCMD_LINE_PARAM_MULTIPLE },
#else
#  define DEBUGFLAG(flag,description)					\
	{ wxCMD_LINE_SWITCH, wxEmptyString, _T("debug-"#flag), description },
#endif
	static const wxCmdLineEntryDesc cmdLineDesc[] =	{
#include "src/kernel/debugFlags.h"
#if wxCHECK_VERSION(2,9,0)
		{ wxCMD_LINE_NONE, "", "", "", wxCMD_LINE_VAL_NONE, 0 }
#else
		{ wxCMD_LINE_NONE, wxEmptyString, wxEmptyString, wxEmptyString }
#endif
	};
#undef DEBUGFLAG
	parser.SetDesc(cmdLineDesc);
}

void ProcessDebugCommandLine(wxCmdLineParser&  parser)
{
#define DEBUGFLAG(flag,description)					\
	mutabor::mutabor_debug_flags.flag = parser.Found(_T("debug-"#flag));
#include "src/kernel/debugFlags.h"
#undef DEBUGFLAG
	mutabor::mutabor_debug_flags.always = true;
}
#endif



#define EXTERNC extern "C" {
#define EXTERNCEND }

EXTERNC

// Functions returning default options are declared weak in the tools' runtime
// libraries. To make the linker pick the strong replacements for those
// functions from this module, we explicitly force its inclusion by passing
// -Wl,-u_sanitizer_options_link_helper
void _sanitizer_options_link_helper() { }
#define NO_SANITIZE							\
	__attribute__((no_sanitize_address,				\
		       no_sanitize_memory,				\
		       no_sanitize_thread,				\
		       no_sanitize_undefined,				\
		       visibility("default"),				\
		       used))

// Default options for AddressSanitizer in various configurations:
//   malloc_context_size=5 - limit the size of stack traces collected by ASan
//     for each malloc/free by 5 frames. These stack traces tend to accumulate
//     very fast in applications using JIT (v8 in Chrome's case), see
//     https://code.google.com/p/address-sanitizer/issues/detail?id=177
//   symbolize=1 - enable in-process symbolization.
//   legacy_pthread_cond=1 - run in the libpthread 2.2.5 compatibility mode to
//     work around libGL.so using the obsolete API, see
//     http://crbug.com/341805. This may break if pthread_cond_t objects are
//     accessed by both instrumented and non-instrumented binaries (e.g. if
//     they reside in shared memory). This option is going to be deprecated in
//     upstream AddressSanitizer and must not be used anywhere except the
//     official builds.
//   check_printf=1 - check the memory accesses to printf (and other formatted
//     output routines) arguments.
//   use_sigaltstack=1 - handle signals on an alternate signal stack. Useful
//     for stack overflow detection.
//   strip_path_prefix=/../../ - prefixes up to and including this
//     substring will be stripped from source file paths in symbolized reports
//   fast_unwind_on_fatal=1 - use the fast (frame-pointer-based) stack unwinder
//     to print error reports. V8 doesn't generate debug info for the JIT code,
//     so the slow unwinder may not work properly.
//   detect_stack_use_after_return=1 - use fake stack to delay the reuse of
//     stack allocations and detect stack-use-after-return errors.
const char * mutASANoptions =
	"legacy_pthread_cond=1 "
	"malloc_context_size=5 "
	"symbolize=1 "
	"check_printf=1 "
	"use_sigaltstack=1 "
	"detect_leaks=1 "
	"strip_path_prefix=/../../ "
	"fast_unwind_on_fatal=1 "
	"detect_stack_use_after_return=1 "
	"detect_odr_violation=1 "
	"allow_user_segv_handler=1 "
	"fast_unwind_on_malloc=0 "
	"report_globals=1 "
	"print_full_thread_history=1";

NO_SANITIZE const char *__asan_default_options() {
  return mutASANoptions;
}

const char * mutASANsuppressions = "";
NO_SANITIZE const char *__asan_default_suppressions() {
	return mutASANsuppressions;
}

// Default options for ThreadSanitizer in various configurations:
//   detect_deadlocks=1 - enable deadlock (lock inversion) detection.
//   second_deadlock_stack=1 - more verbose deadlock reports.
//   report_signal_unsafe=0 - do not report async-signal-unsafe functions
//     called from signal handlers.
//   report_thread_leaks=0 - do not report unjoined threads at the end of
//     the program execution.
//   print_suppressions=1 - print the list of matched suppressions.
//   history_size=7 - make the history buffer proportional to 2^7 (the maximum
//     value) to keep more stack traces.
//   strip_path_prefix=/../../ - prefixes up to and including this
//     substring will be stripped from source file paths in symbolized reports.
const char * mutTSANoptions =
    "detect_deadlocks=1 second_deadlock_stack=1 report_signal_unsafe=0 "
    "report_thread_leaks=0 print_suppressions=1 history_size=7 "
    "strict_memcmp=0 strip_path_prefix=../../ ";
NO_SANITIZE const char *__tsan_default_options() {
	return mutTSANoptions;
}

const char * mutTSANsuppressions = "";
NO_SANITIZE const char *__tsan_default_suppressions() {
	return mutTSANsuppressions;
}

// Default options for MemorySanitizer:
//   intercept_memcmp=0 - do not detect uninitialized memory in memcmp() calls.
//     Pending cleanup, see http://crbug.com/523428
//   strip_path_prefix=/../../ - prefixes up to and including this
//     substring will be stripped from source file paths in symbolized reports.
const char * mutMSANoptions =
    "intercept_memcmp=1 strip_path_prefix=../../ ";
NO_SANITIZE const char *__msan_default_options() {
	return mutMSANoptions;
}

// Default options for LeakSanitizer:
//   print_suppressions=1 - print the list of matched suppressions.
//   strip_path_prefix=/../../ - prefixes up to and including this
//     substring will be stripped from source file paths in symbolized reports.
const char * mutLSANoptions =
    "print_suppressions=1 strip_path_prefix=../../ ";
NO_SANITIZE const char *__lsan_default_options() {
	return mutLSANoptions;
}
const char * mutLSANsuppressions =
	// fontconfig is used by wxWidgets, so we don't
	// want to debug it. This prevents TSAN from
	// reporting the caches from fontconfig
	"leak:libfontconfig\n"
	"leak:wxInitializer\n"
	"leak:g_slice_alloc\n"
	"leak:libX11.so\n"
	"leak:libglib-2.0.so\n";
NO_SANITIZE const char *__lsan_default_suppressions() {
	return mutLSANsuppressions;
}

// Default options for UndefinedBehaviorSanitizer:
//   print_stacktrace=1 - print the stacktrace when UBSan reports an error.
const char * mutUBoptions =
    "print_stacktrace=1 strip_path_prefix=../../ ";
NO_SANITIZE const char* __ubsan_default_options() {
  return mutUBoptions;
}

EXTERNCEND

///\}

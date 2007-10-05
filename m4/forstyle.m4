# forstyle.m4 serial 1 (mutabor)
dnl Copyright (C) 2008 Tobias Schlemmer.
dnl This file is free software; the Free Software Foundation
dnl gives unlimited permission to copy and/or distribute it,
dnl with or without modifications, as long as this notice is preserved.

dnl From Tobias Schlemmer.
dnl Test the scoping of variables defined in for loops.
dnl Prerequisite: AC_PROG_CXX

AC_DEFUN([CXX_FOR_SCOPING],
[
  AC_CACHE_CHECK([for ISO C++ for loop variable scoping], cxx_iso_for_loop_scope,
    [AC_LANG_PUSH(C++)
	AC_COMPILE_IFELSE(AC_LANG_PROGRAM([],[
		for (int i = 1; i < 3; i++);
		for (int i = 1; i < 4; i++);
	]), cxx_iso_for_loop_scope=yes, cxx_iso_for_loop_scope=no)
	AC_LANG_POP(C++)
	])
  if test $cxx_iso_for_loop_scope = yes; then
    AC_DEFINE(CXX_ISO_FOR_LOOP_SCOPE, 1, [Define if your C++ compiler accepts ISO for loop soping.])
  fi
])

# longlong.m4 serial 14
dnl Copyright (C) 1999-2007, 2009-2010 Free Software Foundation, Inc.
dnl This file is free software; the Free Software Foundation
dnl gives unlimited permission to copy and/or distribute it,
dnl with or without modifications, as long as this notice is preserved.

dnl From Paul Eggert.

# Define HAVE_LONG_LONG_INT if 'long long int' works.
# This fixes a bug in Autoconf 2.61, but can be removed once we
# assume 2.62 everywhere.

# Note: If the type 'long long int' exists but is only 32 bits large
# (as on some very old compilers), HAVE_LONG_LONG_INT will not be
# defined. In this case you can treat 'long long int' like 'long int'.

AC_DEFUN([AC_FUNCTION_VECTOR_DATA],
[
  AC_CACHE_CHECK([for vector::data], [ac_cv_function_vector_data],
    [
       AC_LANG_PUSH(C++)
       AC_COMPILE_IFELSE(
       [_AC_FUNCTION_VECTOR_DATA_SNIPPET],
          [ac_cv_function_vector_data=yes],
          [ac_cv_function_vector_data=no])
       AC_LANG_POP
    ])
       
  if test "$ac_cv_function_vector_data" = no ; then :
    AC_DEFINE([DEFINE_VECTOR_DATA], [1],
      [Define to 1 if the system does not support vector<...>::data().])
  fi
])

# Expands to a C program that can be used to test for vector<int>::data()
AC_DEFUN([_AC_FUNCTION_VECTOR_DATA_SNIPPET],
[
  AC_LANG_PROGRAM(
	[[#include <vector>
	]],
    [[std::vector<int> vec(1,0);
      int * ptr = vec.data();
      return *ptr;]])
])

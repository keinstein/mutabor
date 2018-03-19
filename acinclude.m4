AC_DEFUN([AX_CFLAGS_WARN_ALL_ANSI],[dnl
AS_VAR_PUSHDEF([FLAGS],[CFLAGS])dnl
AS_VAR_PUSHDEF([VAR],[ac_cv_cflags_warn_all_ansi])dnl
AC_CACHE_CHECK([m4_ifval($1,$1,FLAGS) for maximum ansi warnings],
VAR,[VAR="no, unknown"
 AC_LANG_SAVE
 AC_LANG(C)
 ac_save_[]FLAGS="$[]FLAGS"
# IRIX C compiler:
#      -use_readonly_const is the default for IRIX C,
#       puts them into .rodata, but they are copied later.
#       need to be "-G0 -rdatashared" for strictmode but
#       I am not sure what effect that has really.         - guidod
for ac_arg dnl
in "-pedantic  % -Wall -ansi -pedantic"       dnl   GCC
   "-xstrconst % -v -Xc"                      dnl Solaris C
   "-std1      % -verbose -w0 -warnprotos -std1" dnl Digital Unix
   " % -qlanglvl=ansi -qsrcmsg -qinfo=all:noppt:noppc:noobs:nocnd" dnl AIX
   " % -ansi -ansiE -fullwarn"                dnl IRIX
   "+ESlit     % +w1 -Aa"                     dnl HP-UX C
   "-Xc        % -pvctl[,]fullmsg -Xc"        dnl NEC SX-5 (Super-UX 10)
   "-h conform % -h msglevel 2 -h conform"    dnl Cray C (Unicos)
   #
do FLAGS="$ac_save_[]FLAGS "`echo $ac_arg | sed -e 's,%%.*,,' -e 's,%,,'`
   AC_TRY_COMPILE([],[return 0;],
   [VAR=`echo $ac_arg | sed -e 's,.*% *,,'` ; break])
done
 FLAGS="$ac_save_[]FLAGS"
 AC_LANG_RESTORE
])
case ".$VAR" in
     .ok|.ok,*) m4_ifvaln($3,$3) ;;
   .|.no|.no,*) m4_ifvaln($4,$4,[m4_ifval($2,[
        AC_RUN_LOG([: m4_ifval($1,$1,FLAGS)="$m4_ifval($1,$1,FLAGS) $2"])
                      m4_ifval($1,$1,FLAGS)="$m4_ifval($1,$1,FLAGS) $2"])]) ;;
   *) m4_ifvaln($3,$3,[
   if echo " $[]m4_ifval($1,$1,FLAGS) " | grep " $VAR " 2>&1 >/dev/null
   then AC_RUN_LOG([: m4_ifval($1,$1,FLAGS) does contain $VAR])
   else AC_RUN_LOG([: m4_ifval($1,$1,FLAGS)="$m4_ifval($1,$1,FLAGS) $VAR"])
                      m4_ifval($1,$1,FLAGS)="$m4_ifval($1,$1,FLAGS) $VAR"
   fi ]) ;;
esac
AS_VAR_POPDEF([VAR])dnl
AS_VAR_POPDEF([FLAGS])dnl
])

dnl the only difference - the LANG selection... and the default FLAGS

AC_DEFUN([AX_CXXFLAGS_WARN_ALL_ANSI],[dnl
AS_VAR_PUSHDEF([FLAGS],[CXXFLAGS])dnl
AS_VAR_PUSHDEF([VAR],[ac_cv_cxxflags_warn_all_ansi])dnl
AC_CACHE_CHECK([m4_ifval($1,$1,FLAGS) for maximum ansi warnings],
VAR,[VAR="no, unknown"
 AC_LANG_SAVE
 AC_LANG(C++)
 ac_save_[]FLAGS="$[]FLAGS"
# IRIX C compiler:
#      -use_readonly_const is the default for IRIX C,
#       puts them into .rodata, but they are copied later.
#       need to be "-G0 -rdatashared" for strictmode but
#       I am not sure what effect that has really.         - guidod
for ac_arg dnl
in "-pedantic  % -Wall -ansi -pedantic"       dnl   GCC
   "-xstrconst % -v -Xc"                      dnl Solaris C
   "-std1      % -verbose -w0 -warnprotos -std1" dnl Digital Unix
   " % -qlanglvl=ansi -qsrcmsg -qinfo=all:noppt:noppc:noobs:nocnd" dnl AIX
   " % -ansi -ansiE -fullwarn"                dnl IRIX
   "+ESlit     % +w1 -Aa"                     dnl HP-UX C
   "-Xc        % -pvctl[,]fullmsg -Xc"        dnl NEC SX-5 (Super-UX 10)
   "-h conform % -h msglevel 2 -h conform"    dnl Cray C (Unicos)
   #
do FLAGS="$ac_save_[]FLAGS "`echo $ac_arg | sed -e 's,%%.*,,' -e 's,%,,'`
   AC_TRY_COMPILE([],[return 0;],
   [VAR=`echo $ac_arg | sed -e 's,.*% *,,'` ; break])
done
 FLAGS="$ac_save_[]FLAGS"
 AC_LANG_RESTORE
])
case ".$VAR" in
     .ok|.ok,*) m4_ifvaln($3,$3) ;;
   .|.no|.no,*) m4_ifvaln($4,$4,[m4_ifval($2,[
        AC_RUN_LOG([: m4_ifval($1,$1,FLAGS)="$m4_ifval($1,$1,FLAGS) $2"])
                      m4_ifval($1,$1,FLAGS)="$m4_ifval($1,$1,FLAGS) $2"])]) ;;
   *) m4_ifvaln($3,$3,[
   if echo " $[]m4_ifval($1,$1,FLAGS) " | grep " $VAR " 2>&1 >/dev/null
   then AC_RUN_LOG([: m4_ifval($1,$1,FLAGS) does contain $VAR])
   else AC_RUN_LOG([: m4_ifval($1,$1,FLAGS)="$m4_ifval($1,$1,FLAGS) $VAR"])
                      m4_ifval($1,$1,FLAGS)="$m4_ifval($1,$1,FLAGS) $VAR"
   fi ]) ;;
esac
AS_VAR_POPDEF([VAR])dnl
AS_VAR_POPDEF([FLAGS])dnl
])


m4_define([_AC_COMPILER_PCHEXT_REJECT],[_AC_COMPILER_EXEEXT_REJECT | *.h ])
m4_define([AX_COMPILER_PCH_C_],
[
  rm -f conftest{.h,}{,.pch,.gch}
  cat >conftest.h <<_ACEOF
#define pchtest 1
_ACEOF
  AS_IF([AC_TRY_COMMAND($CC -c $CFLAGS $CPPFLAGS conftest.h >&AS_MESSAGE_LOG_FD)],[
    rm -f conftest.h
    AC_LANG_CONFTEST([AC_LANG_PROGRAM([
#include "conftest.h"
],[])])
    rm -f conftest.o conftest.obj
    AS_IF([AC_TRY_EVAL(ac_compile)],
    [ac_cv_c_header_precompile="yes"
      for ac_file in ` ( ls conftest.h.gch conftest.h.* ; ls conftest.* )` ; do
        case $ac_file in
          _AC_COMPILER_PCHEXT_REJECT ) ;;
          *) ac_c_pchext=[`expr "$ac_file" : '[^.]*\.\(.*\)'`]
             break;;
        esac
      done
      ac_cv_c_pchext=${ac_cv_c_pchext=$ac_c_pchext}
    ],[
	ac_cv_c_header_precompile="no"
	_AC_MSG_LOG_CONFTEST
    ])
  ],[
	_AC_MSG_LOG_CONFTEST
	ac_cv_c_header_precompile="no"
  ])
])# AX_COMPILER_PCH_C_

# AX_COMPILER_PCH_C
# -------------------
# Check the compiled header extension used by the compiler: typically `.h.gch' or
# `.pch'.  If this is called, some other behavior will change,
# determined by ac_objext.
m4_define([AX_COMPILER_PCH_C],
[
  AC_LANG_PUSH(C)
  AC_CACHE_CHECK([for precompiled C header files], ac_cv_c_header_precompile,
	[AX_COMPILER_PCH_C_])

  if test "$ac_cv_c_header_precompile" = "yes"; then
    AC_CACHE_CHECK([for precompiled C header file extension], ac_cv_c_pchext,
	[AX_COMPILER_PCH_C_])
  fi

  AM_CONDITIONAL(COND_PRECOMP_C,test "$ac_cv_c_header_precompile"="yes")
  rm -f conftest.$ac_ext conftest.$ac_objext conftest.$ac_cv_c_pchext
  AC_SUBST([PCHEXT_C], [$ac_cv_c_pchext])dnl
  ac_c_pchext=$PCHEXT_C
  AC_LANG_POP(C)
])# AX_COMPILER_PCH(C)




m4_define([AX_COMPILER_PCH_CXX_],
[
  rm -f conftesth{.h,}{,.pch,.gch}
  cat >conftesth.h <<_ACEOF
#define pchtest 1
_ACEOF
  AS_IF([AC_TRY_COMMAND($CXX -c $CXXFLAGS -xc++-header $CPPFLAGS -Winvalid-pch conftesth.h >&AS_MESSAGE_LOG_FD)],[
    rm -f conftesth.h
    AC_LANG_CONFTEST([AC_LANG_PROGRAM([
#ifdef pchtest
#else
#error Test
#endif
],[])])
    rm -f conftest.o conftest.obj
    ls conftest*
    AS_IF([AC_TRY_COMMAND($CXX -c $CXXFLAGS $CPPFLAGS -Winvalid-pch --include conftesth.h conftest.$ac_ext)],
    [ac_cv_cxx_header_precompile="yes"
		ls conftest*
      for ac_file in ` ( ls conftesth.h.gch conftesth.h.* ; ls conftesth.* )` ; do
        case $ac_file in
          _AC_COMPILER_PCHEXT_REJECT ) ;;
          *) ac_cxx_pchext=[`expr "$ac_file" : '[^.]*\.\(.*\)'`]
             break;;
        esac
      done
      ac_cv_cxx_pchext=${ac_cv_cxx_pchext=$ac_cxx_pchext}
    ],[
	ac_cv_cxx_header_precompile="no"
        _AC_MSG_LOG_CONFTEST
    ])
  ],[
	ac_cv_cxx_header_precompile="no"
	_AC_MSG_LOG_CONFTEST
  ])
])# AX_COMPILER_PCH_CXX_

# AX_COMPILER_PCH_CXX
# -------------------
# Check the compiled header extension used by the c++ compiler: typically `.h.gch' or
# `.pch'.  If this is called, some other behavior will change,
# determined by ac_objext.
m4_define([AX_COMPILER_PCH_CXX],
[
  AC_LANG_PUSH(C++)
  AC_CACHE_CHECK([for precompiled C++ header files], ac_cv_cxx_header_precompile,
	[AX_COMPILER_PCH_CXX_])

  if test "$ac_cv_cxx_header_precompile" = "yes"; then
    AC_CACHE_CHECK([for precompiled C++ header file extension], ac_cv_cxx_pchext,
	[AX_COMPILER_PCH_CXX_])
  fi

  AM_CONDITIONAL(COND_PRECOMP_CXX,test "$ac_cv_cxx_header_precompile" = "yes")
  rm -f conftest.$ac_ext conftest.$ac_objext conftest.$ac_cv_cxx_pchext
  AC_SUBST([PCHEXT_CXX], [$ac_cv_cxx_pchext])dnl
  ac_cxx_pchext=$PCHEXT_CXX
  AC_LANG_POP(C++)
])# AX_COMPILER_PCH(CXX)


# AC_CECK_LIB_HEADER(LIBRARY,FUNCTION,HEADER
#              [ACTION-IF-FOUND], [ACTION-IF-NOT-FOUND],
#              [OTHER-LIBRARIES])
# ------------------------------------------------------
#
# Use a cache variable name containing both the library and function name,
# because the test really is for library $1 defining function $2, not
# just for library $1.  Separate tests with the same $1 and different $2s
# may have different results.
#
# Note that using directly AS_VAR_PUSHDEF([ac_Lib], [ac_cv_lib_$1_$2])
# is asking for troubles, since AC_CHECK_LIB($lib, fun) would give
# ac_cv_lib_$lib_fun, which is definitely not what was meant.  Hence
# the AS_LITERAL_IF indirection.
#
# FIXME: This macro is extremely suspicious.  It DEFINEs unconditionally,
# whatever the FUNCTION, in addition to not being a *S macro.  Note
# that the cache does depend upon the function we are looking for.
#
# It is on purpose we used `ac_check_lib_save_LIBS' and not just
# `ac_save_LIBS': there are many macros which don't want to see `LIBS'
# changed but still want to use AC_CHECK_LIB, so they save `LIBS'.
# And ``ac_save_LIBS' is too tempting a name, so let's leave them some
# freedom.
AC_DEFUN([AC_CHECK_LIB_HEADER],
[m4_ifval([$4], , [AH_CHECK_LIB([winmm])])dnl
AC_CACHE_CHECK([for $2 in -l$1], [ac_cv_lib_$1_$2],
[ac_check_lib_save_LIBS="$LIBS"
LIBS="-l$1 $6 $LIBS"
AC_LINK_IFELSE([AC_LANG_PROGRAM([
$3
],[[void * x= &$2;]])],
	       [ac_cv_lib_$1_$2=yes],
	       [ac_cv_lib_$1_$2=no])
LIBS=$ac_check_lib_save_LIBS])
AS_IF([test "${ac_cv_lib_$1_$2}" = yes],
      [m4_default([$4], [AC_DEFINE_UNQUOTED(AS_TR_CPP(HAVE_LIB$1),1,[Define to 1 if you have winsock2.dll])
  LIBS="-l$1 $LIBS"
])],
      [$5])dnl
dnl AS_VAR_POPDEF([ac_Lib])dnl
])# AC_CHECK_LIB


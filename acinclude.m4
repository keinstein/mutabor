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
  rm -f conftest{.h,}{,.pch,.gch}
  cat >conftest.h <<_ACEOF
#define pchtest 1
_ACEOF
  AS_IF([AC_TRY_COMMAND($CXX -c $CXXFLAGS $CPPFLAGS -Winvalid-pch conftest.h >&AS_MESSAGE_LOG_FD)],[
    rm -f conftest.h
    AC_LANG_CONFTEST([AC_LANG_PROGRAM([],[])])
    rm -f conftest.o conftest.obj
    ls conftest.*
    AS_IF([AC_TRY_COMMAND($CXX -c $CXXFLAGS $CPPFLAGS -Winvalid-pch -include conftest.h conftest.cc)],
    [ac_cv_cxx_header_precompile="yes"
      for ac_file in ` ( ls conftest.h.gch conftest.h.* ; ls conftest.* )` ; do
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

  AM_CONDITIONAL(COND_PRECOMP_CXX,test "$ac_cv_cxx_header_precompile"="yes")
  rm -f conftest.$ac_ext conftest.$ac_objext conftest.$ac_cv_cxx_pchext
  AC_SUBST([PCHEXT_CXX], [$ac_cv_cxx_pchext])dnl
  ac_cxx_pchext=$PCHEXT_CXX
  AC_LANG_POP(C++)
])# AX_COMPILER_PCH(CXX)


dnl
dnl Get the cflags and libraries from the wx-config script
dnl
AC_DEFUN([AM_PATH_WXCONFIG],
[
  dnl do we have wx-config name: it can be wx-config or wxd-config or ...
  if test x${WX_CONFIG_NAME+set} != xset ; then
     WX_CONFIG_NAME=wx-config
  fi

  if test "x$wx_config_name" != x ; then
     WX_CONFIG_NAME="$wx_config_name"
  fi

  dnl deal with optional prefixes
  if test x$wx_config_exec_prefix != x ; then
     wx_config_args="$wx_config_args --exec-prefix=$wx_config_exec_prefix"
     WX_LOOKUP_PATH="$wx_config_exec_prefix/bin"
  fi
  if test x$wx_config_prefix != x ; then
     wx_config_args="$wx_config_args --prefix=$wx_config_prefix"
     WX_LOOKUP_PATH="$WX_LOOKUP_PATH:$wx_config_prefix/bin"
  fi
  if test "$cross_compiling" = "yes" || test "$host_alias" ; then
     wx_config_args="$wx_config_args --host=$host_alias"
  fi

  dnl don't search the PATH if WX_CONFIG_NAME is absolute filename
  if test -x "$WX_CONFIG_NAME" ; then
     AC_MSG_CHECKING(for wx-config)
     WX_CONFIG_PATH="$WX_CONFIG_NAME"
     AC_MSG_RESULT($WX_CONFIG_PATH)
  else
     AC_PATH_PROG(WX_CONFIG_PATH, $WX_CONFIG_NAME, no, "$WX_LOOKUP_PATH:$PATH")
  fi

  if test "$WX_CONFIG_PATH" != "no" ; then
    WX_VERSION=""

    min_wx_version=ifelse([$1], ,2.2.1,$1)
    if test -z "$5" ; then
      AC_MSG_CHECKING([for wxWidgets version >= $min_wx_version])
    else
      AC_MSG_CHECKING([for wxWidgets version >= $min_wx_version ($5)])
    fi

    WX_CONFIG_WITH_ARGS="$WX_CONFIG_PATH $wx_config_args $5 $4"

    WX_VERSION=`$WX_CONFIG_WITH_ARGS --version 2>/dev/null`
    wx_config_major_version=`echo $WX_VERSION | \
           sed 's/\([[0-9]]*\).\([[0-9]]*\).\([[0-9]]*\)/\1/'`
    wx_config_minor_version=`echo $WX_VERSION | \
           sed 's/\([[0-9]]*\).\([[0-9]]*\).\([[0-9]]*\)/\2/'`
    wx_config_micro_version=`echo $WX_VERSION | \
           sed 's/\([[0-9]]*\).\([[0-9]]*\).\([[0-9]]*\)/\3/'`

    wx_requested_major_version=`echo $min_wx_version | \
           sed 's/\([[0-9]]*\).\([[0-9]]*\).\([[0-9]]*\)/\1/'`
    wx_requested_minor_version=`echo $min_wx_version | \
           sed 's/\([[0-9]]*\).\([[0-9]]*\).\([[0-9]]*\)/\2/'`
    wx_requested_micro_version=`echo $min_wx_version | \
           sed 's/\([[0-9]]*\).\([[0-9]]*\).\([[0-9]]*\)/\3/'`

    _WX_PRIVATE_CHECK_VERSION([$wx_requested_major_version],
                              [$wx_requested_minor_version],
                              [$wx_requested_micro_version])

    if test -n "$wx_ver_ok"; then

      AC_MSG_RESULT(yes (version $WX_VERSION))
      WX_LIBS=`$WX_CONFIG_WITH_ARGS --libs`

      dnl is this even still appropriate?  --static is a real option now
      dnl and WX_CONFIG_WITH_ARGS is likely to contain it if that is
      dnl what the user actually wants, making this redundant at best.
      dnl For now keep it in case anyone actually used it in the past.
      AC_MSG_CHECKING([for wxWidgets static library])
      WX_LIBS_STATIC=`$WX_CONFIG_WITH_ARGS --static --libs 2>/dev/null`
      if test "x$WX_LIBS_STATIC" = "x"; then
        AC_MSG_RESULT(no)
      else
        AC_MSG_RESULT(yes)
      fi

      dnl starting with version 2.2.6 wx-config has --cppflags argument
      wx_has_cppflags=""
      if test $wx_config_major_version -gt 2; then
        wx_has_cppflags=yes
      else
        if test $wx_config_major_version -eq 2; then
           if test $wx_config_minor_version -gt 2; then
              wx_has_cppflags=yes
           else
              if test $wx_config_minor_version -eq 2; then
                 if test $wx_config_micro_version -ge 6; then
                    wx_has_cppflags=yes
                 fi
              fi
           fi
        fi
      fi

      if test "x$wx_has_cppflags" = x ; then
         dnl no choice but to define all flags like CFLAGS
         WX_CFLAGS=`$WX_CONFIG_WITH_ARGS --cflags`
         WX_CPPFLAGS=$WX_CFLAGS
         WX_CXXFLAGS=$WX_CFLAGS

         WX_CFLAGS_ONLY=$WX_CFLAGS
         WX_CXXFLAGS_ONLY=$WX_CFLAGS
      else
         dnl we have CPPFLAGS included in CFLAGS included in CXXFLAGS
         WX_CPPFLAGS=`$WX_CONFIG_WITH_ARGS --cppflags`
         WX_CXXFLAGS=`$WX_CONFIG_WITH_ARGS --cxxflags`
         WX_CFLAGS=`$WX_CONFIG_WITH_ARGS --cflags`

         WX_CFLAGS_ONLY=`echo $WX_CFLAGS | sed "s@^$WX_CPPFLAGS *@@"`
         WX_CXXFLAGS_ONLY=`echo $WX_CXXFLAGS | sed "s@^$WX_CFLAGS *@@"`
      fi

      ifelse([$2], , :, [$2])

    else

       if test "x$WX_VERSION" = x; then
          dnl no wx-config at all
          AC_MSG_RESULT(no)
       else
          AC_MSG_RESULT(no (version $WX_VERSION is not new enough))
       fi

       WX_CFLAGS=""
       WX_CPPFLAGS=""
       WX_CXXFLAGS=""
       WX_LIBS=""
       WX_LIBS_STATIC=""
       ifelse([$3], , :, [$3])

    fi
  else

    WX_CFLAGS=""
    WX_CPPFLAGS=""
    WX_CXXFLAGS=""
    WX_LIBS=""
    WX_LIBS_STATIC=""
    ifelse([$3], , :, [$3])

  fi

  AC_SUBST(WX_CPPFLAGS)
  AC_SUBST(WX_CFLAGS)
  AC_SUBST(WX_CXXFLAGS)
  AC_SUBST(WX_CFLAGS_ONLY)
  AC_SUBST(WX_CXXFLAGS_ONLY)
  AC_SUBST(WX_LIBS)
  AC_SUBST(WX_LIBS_STATIC)
  AC_SUBST(WX_VERSION)
])

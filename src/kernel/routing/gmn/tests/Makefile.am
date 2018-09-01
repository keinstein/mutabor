#include $(top_srcdir)/common-rules.mk
#include $(top_srcdir)/common-linklibs.mk

DEBUGPATHS +=  \
	%D%/debugPaths.cpp

CLEANFILES += %D%/playgmn1.gmn \
	%D%/*.class

EXTRA_DIST += %D%/gmn1_source.gmn

check_PROGRAMS += \
	%D%/playgmn1 \
	%D%/gmnopenfail1

check_SCRIPTS += \
	%D%/playgmn1.gmn

TESTS += \
	%D%/playgmn1$(EXEEXT) \
	%D%/gmnopenfail1$(EXEEXT)

%C%_playgmn1_CPPFLAGS = $(CPPFLAGS) \
	-DSRCDIR="\"$(srcdir)/%D%/\"" \
	$(WXINTLCXXFLAGS)
%C%_playgmn1_SOURCES = \
	%D%/playgmn1.cpp

nodist_%C%_playgmn1_SOURCES = \
	%D%/debugPaths.cpp

%C%_playgmn1_LDADD = \
	libmutaborrouting.a \
	libmutabordebugnogui.a \
	src/kernel/libmutaborkernel.a \
	lib/rtmidi/librtmidi@rtmidi_suffix@.la \
	src/wxintl/libboostintl.a \
	$(LDADD) \
	$(AM_LDFLAGS) \
	$(BOOST_LDFLAGS) \
	$(BOOST_FILESYSTEM_LIB) \
	$(BOOST_THREAD_LIB) \
	$(BOOST_CHRONO_LIB) \
	$(BOOST_LOCALE_LIB) \
	$(BOOST_SYSTEM_LIB)

%C%_gmnopenfail1_LDADD = \
	libmutaborrouting.a \
	libmutabordebugnogui.a \
	src/kernel/libmutaborkernel.a \
	lib/rtmidi/librtmidi@rtmidi_suffix@.la \
	src/wxintl/libboostintl.a \
	$(LDADD) \
	$(AM_LDFLAGS) \
	$(BOOST_LDFLAGS) \
	$(BOOST_FILESYSTEM_LIB) \
	$(BOOST_THREAD_LIB) \
	$(BOOST_CHRONO_LIB) \
	$(BOOST_LOCALE_LIB) \
	$(BOOST_SYSTEM_LIB)

%C%_gmnopenfail1_SOURCES = \
	%D%/gmnopenfail1.cpp

%C%_gmnopenfail1_CXXFLAGS = \
	$(AM_CXXFLAGS) \
	$(WXINTLCXXFLAGS)


nodist_%C%_gmnopenfail1_SOURCES = \
	%D%/debugPaths.cpp


%D%/playgmn1.gmn: %D%/gmn1_source.gmn
	cp `(if test -f '$<' ; then  echo '$<' ; else echo '$(top_srcdir)/$<' ; fi )` $@


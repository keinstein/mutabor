#include $(top_srcdir)/common-rules.mk
#include $(top_srcdir)/common-linklibs.mk

DEBUGPATHS +=  \
	%D%/debugPaths.cpp

CLEANFILES += %D%/*.class


TESTS += \
	%D%/wxlinktest$(EXEEXT) \
	%D%/wxlinktest2$(EXEEXT)

check_PROGRAMS += \
	%D%/wxlinktest \
	%D%/wxlinktest2

EXTRA_DIST += \
	$(srcdir)/%D%/12tet.scl

check_MIDISOURCES += \
	%D%/runmut.txt

%C%_wxlinktest_SOURCES = \
	%D%/wxlinktest.cpp

%C%_wxlinktest_CXXFLAGS = \
	$(AM_CXXFLAGS) \
	$(WXINTLCXXFLAGS)

%C%_wxlinktest_LDADD= \
	libmutabordebugtest.a \
	libmutaborgui.a \
	libmutaborrouting.a \
	src/kernel/libmutaborkernel.a \
	libmutaborscala.a \
	src/wxintl/libwxintl.la \
	$(SANITIZER_LIBS) \
	$(LDADD) \
	$(AM_LDFLAGS) \
	$(BOOST_LDFLAGS) \
	$(BOOST_FILESYSTEM_LDFLAGS) \
	$(BOOST_SYSTEM_LDFLAGS) \
	$(BOOST_FILESYSTEM_LIB) \
	$(BOOST_SYSTEM_LIB) \
	$(WX_LIBS)

%C%_wxlinktest2_SOURCES = %D%/wxlinktest2.cpp

nodist_%C%_wxlinktest2_SOURCES = \
	%D%/debugPaths.cpp

%C%_wxlinktest2_CXXFLAGS = \
	$(AM_CXXFLAGS) \
	$(WXINTLCXXFLAGS)

%C%_wxlinktest2_LDADD= \
	libmutabordebugtest.a \
	libmutaborgui.a \
	libmutaborrouting.a \
	src/kernel/libmutaborkernel.a \
	libmutaborscala.a \
	lib/rtmidi/librtmidi@rtmidi_suffix@.la \
	src/wxintl/libwxintl.la \
	$(SANITIZER_LIBS) \
	$(LDADD) \
	$(AM_LDFLAGS) \
	$(BOOST_LDFLAGS) \
	$(BOOST_FILESYSTEM_LDFLAGS) \
	$(BOOST_SYSTEM_LDFLAGS) \
	$(BOOST_FILESYSTEM_LIB) \
	$(BOOST_THREAD_LIB) \
	$(BOOST_CHRONO_LIB) \
	$(BOOST_SYSTEM_LIB) \
	$(WX_LIBS)

if HAVE_CPPUNIT
TESTS += \
	%D%/cppunitlinktest$(EXEEXT)

check_PROGRAMS += %D%/cppunitlinktest

%C%_cppunitlinktest_CXXFLAGS = \
	$(AM_CXXFLAGS) \
	$(CPPUNIT_CFLAGS) \
	$(WXINTLCXXFLAGS)

%C%_cppunitlinktest_SOURCES = \
	%D%/cppunitlinktest.cpp

nodist_%C%_cppunitlinktest_SOURCES = \
	%D%/debugPaths.cpp

%C%_cppunitlinktest_LDADD = \
	libmutabordebugcppunit.a \
	libmutaborgui.a \
	src/kernel/libmutaborkernel.a \
	libmutaborrouting.a \
	libmutaborscala.a \
	lib/rtmidi/librtmidi@rtmidi_suffix@.la \
	src/wxintl/libwxintl.la \
	$(SANITIZER_LIBS) \
	$(LDADD) \
	$(AM_LDFLAGS) \
	$(CPPUNIT_LIBS) \
	$(BOOST_LDFLAGS) \
	$(BOOST_FILESYSTEM_LDFLAGS) \
	$(BOOST_SYSTEM_LDFLAGS) \
	$(BOOST_FILESYSTEM_LIB) \
	$(BOOST_SYSTEM_LIB)

endif



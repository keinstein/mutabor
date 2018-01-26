#include $(top_srcdir)/common-rules.mk
#include $(top_srcdir)/common-linklibs.mk

CLEANFILES += %D%/*.class

DEBUGPATHS +=  \
	%D%/debugPaths.cpp

check_PROGRAMS += %D%/timer1

TESTS += %D%/timer1$(EXEEXT)

%C%_timer1_SOURCES = \
	%D%/timer1.cpp

nodist_%C%_timer1_SOURCES = \
	%D%/debugPaths.cpp

%C%_timer1_CXXFLAGS = \
	$(AM_CXXFLGAS) \
	$(WXINTLCXXFLAGS)

%C%_timer1_LDADD= \
	libmutabordebugtest.a \
	libmutaborgui.a \
	libmutaborrouting.a \
	src/kernel/libmutaborkernel.a \
	libmutaborscala.a \
	lib/rtmidi/librtmidi@rtmidi_suffix@.la \
	src/wxintl/libwxintl.la \
	$(RTMIDITESTLDFLAGS) \
	$(LDADD) \
	$(AM_LDFLAGS) \
	$(BOOST_LDFLAGS) \
	$(BOOST_FILESYSTEM_LIB) \
	$(BOOST_SYSTEM_LIB)

if HAVE_CPPUNIT
TESTS += \
	%D%/testcppunit$(EXEEXT)

check_PROGRAMS += %D%/testcppunit

%C%_testcppunit_CXXFLAGS = \
	$(AM_CXXFLAGS) \
	$(CPPUNIT_CFLAGS) \
	$(WXINTLCXXFLAGS)

%C%_testcppunit_SOURCES = \
	%D%/main.cpp \
	%D%/timing.h \
	%D%/RouteTest.h \
	%D%/RouteTest.cpp \
	%D%/BoxTest.h \
	%D%/BoxTest.cpp \
	%D%/CommonFileDeviceTest.h \
	%D%/CommonFileDeviceTest.cpp

nodist_%C%_testcppunit_SOURCES = \
	%D%/debugPaths.cpp

%C%_testcppunit_LDADD = \
	libmutabormaincppunit.a \
	libmutabordebugcppunit.a \
	libmutaborgui.a \
	libmutaborrouting.a \
	src/kernel/libmutaborkernel.a \
	libmutaborscala.a \
	lib/rtmidi/librtmidi@rtmidi_suffix@.la \
	src/wxintl/libwxintl.la \
	$(LDADD) \
	$(AM_LDFLAGS) \
	$(CPPUNIT_LIBS) \
	$(BOOST_LDFLAGS) \
	$(BOOST_FILESYSTEM_LIB) \
	$(BOOST_SYSTEM_LIB)
endif




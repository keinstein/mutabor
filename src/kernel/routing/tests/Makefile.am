#include $(top_srcdir)/common-rules.mk
#include $(top_srcdir)/common-linklibs.mk

CLEANFILES += %D%/*.class

DEBUGPATHS +=  \
	%D%/debugPaths.cpp

check_PROGRAMS += \
	%D%/timer1 \
	%D%/test_thread

TESTS += \
	%D%/timer1$(EXEEXT) \
	%D%/test_thread$(EXEEXT)

%C%_timer1_SOURCES = \
	%D%/timer1.cpp

nodist_%C%_timer1_SOURCES = \
	%D%/debugPaths.cpp

%C%_timer1_CXXFLAGS = \
	$(AM_CXXFLGAS) \
	$(WXINTLCXXFLAGS)

%C%_timer1_LDADD = \
	libmutaborrouting.a \
	src/kernel/libmutaborkernel.a \
	libmutaborscala.a \
	lib/rtmidi/librtmidi@rtmidi_suffix@.la \
	libmutabordebugnogui.a \
	src/wxintl/libboostintl.a \
	$(RTMIDITESTLDFLAGS) \
	$(LDADD) \
	$(AM_LDFLAGS) \
	$(BOOST_LDFLAGS) \
	$(BOOST_FILESYSTEM_LIB) \
	$(BOOST_CHRONO_LIB) \
	$(BOOST_THREAD_LIB) \
	$(BOOST_LOCALE_LIB) \
	$(BOOST_SYSTEM_LIB)

%C%_test_thread_SOURCES = \
	%D%/test_thread.cpp

nodist_%C%_test_thread_SOURCES = \
	%D%/debugPaths.cpp

%C%_test_thread_CXXFLAGS = \
	$(AM_CXXFLGAS) \
	$(WXINTLCXXFLAGS)

%C%_test_thread_LDADD = \
	$(LDADD) \
	$(AM_LDFLAGS) \
	$(BOOST_LDFLAGS) \
	$(BOOST_FILESYSTEM_LIB) \
	$(BOOST_CHRONO_LIB) \
	$(BOOST_THREAD_LIB) \
	$(BOOST_LOCALE_LIB) \
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
	libmutabordebugcppunit.a \
	libmutaborrouting.a \
	src/kernel/libmutaborkernel.a \
	libmutaborscala.a \
	lib/rtmidi/librtmidi@rtmidi_suffix@.la \
	src/wxintl/libboostintl.a \
	$(LDADD) \
	$(AM_LDFLAGS) \
	$(CPPUNIT_LIBS) \
	$(BOOST_LDFLAGS) \
	$(BOOST_FILESYSTEM_LIB) \
	$(BOOST_CHRONO_LIB) \
	$(BOOST_THREAD_LIB) \
	$(BOOST_SYSTEM_LIB)
endif




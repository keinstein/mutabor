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
	lib/rtmidi/librtmidi-ts.la \
	src/wxintl/libwxintl.a \
	$(LDADD) \
	$(AM_LDFLAGS) \
	$(BOOST_FILESYSTEM_LDFLAGS) \
	$(BOOST_SYSTEM_LDFLAGS) \
	$(BOOST_FILESYSTEM_LIBS) \
	$(BOOST_SYSTEM_LIBS)

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
	lib/rtmidi/librtmidi-ts.la \
	src/wxintl/libwxintl.a \
	$(LDADD) \
	$(AM_LDFLAGS) \
	$(CPPUNIT_LIBS) \
	$(BOOST_FILESYSTEM_LDFLAGS) \
	$(BOOST_SYSTEM_LDFLAGS) \
	$(BOOST_FILESYSTEM_LIBS) \
	$(BOOST_SYSTEM_LIBS)
endif



if COPYDLLS
check-am: check-dll

check-dll: all-am
	$(MAKE) $(AM_MAKEFLAGS) $(check_PROGRAMS)
	$(MAKE) $(AM_MAKEFLAGS)	linkchecks

linkchecks:
	for d in `echo $(TESTS)| tr ' ' '\n' | grep -i -e '$(EXEEXT)$$'` ; \
	do \
		ls -l "$$d" ; \
		$(MAKE) $(AM_MAKEFLAGS) DLLLINKFILE="$$d" DLLEXEDIR="." installdll ; \
		test -f ".libs/$$d" && \
			$(MAKE) $(AM_MAKEFLAGS) DLLLINKFILE=".libs/$$d" DLLEXEDIR="." installdll ; \
	done
endif


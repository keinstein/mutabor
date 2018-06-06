#include $(top_srcdir)/common-rules.mk
#include $(top_srcdir)/common-linklibs.mk

DEBUGPATHS +=  \
	%D%/debugPaths.cpp

EXTRA_DIST += \
	%D%/all.mut

CLEANFILES += \
	%D%/*.class


if HAVE_CPPUNIT
TESTS += \
	%D%/testcppunit$(EXEEXT)

check_PROGRAMS += %D%/testcppunit

%C%_testcppunit_CXXFLAGS = $(AM_CXXFLAGS) $(CPPUNIT_CFLAGS)

%C%_testcppunit_SOURCES = \
	%D%/main.cpp \
	%D%/boxTest.h \
	%D%/boxTest.cpp


nodist_%C%_testcppunit_SOURCES = \
	%D%/debugPaths.cpp

%C%_testcppunit_LDADD = \
	src/kernel/libmutaborkernel.a \
	libmutabordebugcppunit.a \
	libmutaborrouting.a \
	libmutaborscala.a \
	src/wxintl/libboostintl.a \
	lib/rtmidi/librtmidi@rtmidi_suffix@.la \
	$(LDADD) \
	$(AM_LDFLAGS) \
	$(CPPUNIT_LIBS) \
	$(BOOST_FILESYSTEM_LDFLAGS) \
	$(BOOST_SYSTEM_LDFLAGS) \
	$(BOOST_FILESYSTEM_LIB) \
	$(BOOST_LOCALE_LIB) \
	$(BOOST_SYSTEM_LIB)

endif





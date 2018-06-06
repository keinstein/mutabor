#include $(top_srcdir)/common-rules.mk
#include $(top_srcdir)/common-linklibs.mk

#TESTS =
#check_PROGRAMS = 
DEBUGPATHS +=  \
	%D%/debugPaths.cpp

CLEANFILES += \
	texidlist.tex \
	%D%/*.class

if HAVE_CPPUNIT
TESTS += \
	%D%/testcppunit$(EXEEXT)

check_PROGRAMS += %D%/testcppunit

%C%_testcppunit_CXXFLAGS = $(AM_CXXFLAGS) $(CPPUNIT_CFLAGS)

%C%_testcppunit_SOURCES = \
	%D%/main.cpp \
	%D%/MkIDlist.h

nodist_%C%_testcppunit_SOURCES = \
	%D%/debugPaths.cpp

%C%_testcppunit_LDADD = \
	libmutaborwxcppunit.a \
	src/kernel/libmutaborkernel.a \
	lib/rtmidi/librtmidi@rtmidi_suffix@.la \
	src/wxintl/libwxintl.la \
	libmutabordebug.a \
	$(CPPUNIT_LIBS) \
	$(LDADD) \
	$(AM_LDFLAGS) \
	$(WX_LIBS) \
	$(BOOST_LDFLAGS) \
	$(BOOST_FILESYSTEM_LDFLAGS) \
	$(BOOST_FILESYSTEM_LIB) \
	$(BOOST_SYSTEM_LDFLAGS) \
	$(BOOST_THREAD_LIB) \
	$(BOOST_CHRONO_LIB) \
	$(BOOST_SYSTEM_LIB)
endif


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
	libmutabormaincppunit.a \
	src/kernel/libmutaborkernel.a \
	src/wxintl/libwxintl.a \
	$(LDADD) \
	$(AM_LDFLAGS) \
	$(CPPUNIT_LIBS) \
	$(BOOST_FILESYSTEM_LDFLAGS) \
	$(BOOST_SYSTEM_LDFLAGS) \
	$(BOOST_FILESYSTEM_LIBS) \
	$(BOOST_SYSTEM_LIBS)
endif


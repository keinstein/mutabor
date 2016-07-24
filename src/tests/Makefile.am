#include $(top_srcdir)/common-rules.mk
#include $(top_srcdir)/common-linklibs.mk

CLEANFILES += %D%/*.class


TESTS += \
	%D%/wxlinktest$(EXEEXT) \
	%D%/wxlinktest2$(EXEEXT)

check_PROGRAMS += \
	%D%/wxlinktest \
	%D%/wxlinktest2

%C%_wxlinktest_SOURCES = \
	%D%/wxlinktest.cpp

%C%_wxlinktest_LDADD= \
	libmutabordebugtest.a \
	libmutaborgui.a \
	libmutaborrouting.a \
	src/kernel/libmutaborkernel.a \
	libmutaborscala.a \
	librtmidi.a \
	src/wxintl/libwxintl.a \
	$(LDADD) \
	$(AM_LDFLAGS) \
	$(BOOST_FILESYSTEM_LDFLAGS) \
	$(BOOST_SYSTEM_LDFLAGS) \
	$(BOOST_FILESYSTEM_LIBS) \
	$(BOOST_SYSTEM_LIBS)

%C%_wxlinktest2_SOURCES = %D%/wxlinktest2.cpp

DEBUGPATHS += \
	%D%/debugPaths.cpp

nodist_%C%_wxlinktest2_SOURCES = \
	%D%/debugPaths.cpp

%C%_wxlinktest2_LDADD= \
	libmutabordebugtest.a \
	libmutaborgui.a \
	libmutaborrouting.a \
	src/kernel/libmutaborkernel.a \
	libmutaborscala.a \
	librtmidi.a \
	src/wxintl/libwxintl.a \
	$(LDADD) \
	$(AM_LDFLAGS) \
	$(BOOST_FILESYSTEM_LDFLAGS) \
	$(BOOST_SYSTEM_LDFLAGS) \
	$(BOOST_FILESYSTEM_LIBS) \
	$(BOOST_SYSTEM_LIBS)

if HAVE_CPPUNIT
TESTS += \
	%D%/cppunitlinktest$(EXEEXT)

check_PROGRAMS += %D%/cppunitlinktest

%C%_cppunitlinktest_CXXFLAGS = $(AM_CXXFLAGS) $(CPPUNIT_CFLAGS)

%C%_cppunitlinktest_SOURCES = \
	%D%/cppunitlinktest.cpp

nodist_%C%_cppunitlinktest_SOURCES = \
	%D%/debugPaths.cpp

%C%_cppunitlinktest_LDADD = \
	libmutabormaincppunit.a \
	libmutabordebugcppunit.a \
	libmutaborgui.a \
	src/kernel/libmutaborkernel.a \
	libmutaborrouting.a \
	libmutaborscala.a \
	librtmidi.a \
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


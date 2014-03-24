include $(top_srcdir)/common-rules.mk
include $(top_srcdir)/common-linklibs.mk

TESTS = wxlinktest$(EXEEXT) wxlinktest2$(EXEEXT)

check_PROGRAMS = wxlinktest wxlinktest2

wxlinktest_SOURCES = wxlinktest.cpp

wxlinktest_LDADD= \
	$(top_builddir)/libmutabordebugtest.a \
	$(top_builddir)/libmutaborgui.a \
	$(top_builddir)/libmutaborrouting.a \
	$(top_builddir)/libmutaborkernel.a \
	$(top_builddir)/librtmidi.a \
	$(top_builddir)/src/wxintl/libwxintl.a \
	$(LDADD) \
	$(AM_LDFLAGS) \
	$(BOOST_FILESYSTEM_LDFLAGS) \
	$(BOOST_SYSTEM_LDFLAGS) \
	$(BOOST_FILESYSTEM_LIBS) \
	$(BOOST_SYSTEM_LIBS)

wxlinktest2_SOURCES = wxlinktest2.cpp

nodist_wxlinktest2_SOURCES = \
	debugPaths.cpp

wxlinktest2_LDADD= \
	$(top_builddir)/libmutabordebugtest.a \
	$(top_builddir)/libmutaborgui.a \
	$(top_builddir)/libmutaborrouting.a \
	$(top_builddir)/libmutaborkernel.a \
	$(top_builddir)/librtmidi.a \
	$(top_builddir)/src/wxintl/libwxintl.a \
	$(LDADD) \
	$(AM_LDFLAGS) \
	$(BOOST_FILESYSTEM_LDFLAGS) \
	$(BOOST_SYSTEM_LDFLAGS) \
	$(BOOST_FILESYSTEM_LIBS) \
	$(BOOST_SYSTEM_LIBS)

if HAVE_CPPUNIT
TESTS += \
	cppunitlinktest$(EXEEXT)

check_PROGRAMS += cppunitlinktest

cppunitlinktest_CXXFLAGS = $(AM_CXXFLAGS) $(CPPUNIT_CFLAGS)

cppunitlinktest_SOURCES = \
	cppunitlinktest.cpp

nodist_cppunitlinktest_SOURCES = \
	debugPaths.cpp

cppunitlinktest_LDADD = \
	$(top_builddir)/libmutabormaincppunit.a \
	$(top_builddir)/libmutabordebugcppunit.a \
	$(top_builddir)/libmutaborgui.a \
	$(top_builddir)/libmutaborkernel.a \
	$(top_builddir)/libmutaborrouting.a \
	$(top_builddir)/librtmidi.a \
	$(top_builddir)/src/wxintl/libwxintl.a \
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


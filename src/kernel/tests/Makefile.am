include $(top_srcdir)/common-rules.mk
include $(top_srcdir)/common-linklibs.mk


EXTRA_DIST = \
	all.mut


if HAVE_CPPUNIT
TESTS = \
	testcppunit$(EXEEXT)

check_PROGRAMS = testcppunit

testcppunit_CXXFLAGS = $(AM_CXXFLAGS) $(CPPUNIT_CFLAGS)

testcppunit_SOURCES = \
	main.cpp \
	boxTest.h \
	boxTest.cpp

nodist_testcppunit_SOURCES = \
	debugPaths.cpp

testcppunit_LDADD = \
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


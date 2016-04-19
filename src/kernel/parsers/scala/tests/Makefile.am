include $(top_srcdir)/common-rules.mk
include $(top_srcdir)/common-linklibs.mk

EXTRA_DIST = 
#	all.mut

TESTS = \
	test_empty$(EXEEXT) \
	test_empty_comments$(EXEEXT) \
	test_intervals1$(EXEEXT)


check_PROGRAMS = \
	test_empty \
	test_empty_comments \
	test_intervals1

nodist_test_empty_SOURCES = \
	debugPaths.cpp

test_empty_SOURCES = \
	test_empty.cpp

test_empty_LDADD = \
	$(top_builddir)/libmutaborscala.a \
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

nodist_test_empty_comments_SOURCES = \
	debugPaths.cpp

test_empty_comments_SOURCES = \
	test_empty_comments.cpp

test_empty_comments_LDADD = \
	$(top_builddir)/libmutaborscala.a \
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

nodist_test_intervals1_SOURCES = \
	debugPaths.cpp

test_intervals1_SOURCES = \
	test_intervals1.cpp

test_intervals1_LDADD = \
	$(top_builddir)/libmutaborscala.a \
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


# if HAVE_CPPUNIT
# TESTS = 
# #	testcppunit$(EXEEXT)
# 
# 
# #testcppunit
# 
# testcppunit_CXXFLAGS = $(AM_CXXFLAGS) $(CPPUNIT_CFLAGS)
# 
# testcppunit_SOURCES = \
# 	main.cpp \
# 	boxTest.h \
# 	boxTest.cpp
# 
# nodist_testcppunit_SOURCES = \
# 	debugPaths.cpp
# 
# testcppunit_LDADD = \
# 	$(top_builddir)/libmutabormaincppunit.a \
# 	$(top_builddir)/libmutabordebugcppunit.a \
# 	$(top_builddir)/libmutaborgui.a \
# 	$(top_builddir)/libmutaborkernel.a \
# 	$(top_builddir)/libmutaborrouting.a \
# 	$(top_builddir)/librtmidi.a \
# 	$(top_builddir)/src/wxintl/libwxintl.a \
# 	$(LDADD) \
# 	$(AM_LDFLAGS) \
# 	$(CPPUNIT_LIBS) \
# 	$(BOOST_FILESYSTEM_LDFLAGS) \
# 	$(BOOST_SYSTEM_LDFLAGS) \
# 	$(BOOST_FILESYSTEM_LIBS) \
# 	$(BOOST_SYSTEM_LIBS)
# 
# endif




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


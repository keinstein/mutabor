include $(top_srcdir)/common-rules.mk
include $(top_srcdir)/common-linklibs.mk

CLEANFILES += \
	playmidi1.mid \
	test_output.mid \
	test_output2.mid

AM_CPPFLAGS += -DSRCDIR="\"$(srcdir)\""
check_PROGRAMS = \
	playmidi1 \
	midiopenfail1

EXTRA_DIST = \
	midi1_source.mid \
	midi1_source.txt \
	bug019010.mid \
	bug019010.txt \
	controller.txt \
	controller.mid \
	bank_select.txt \
	bank_select.mid

check_SCRIPTS = playmidi1.mid

TESTS = \
	playmidi1$(EXEEXT) \
	midiopenfail1$(EXEEXT)

playmidi1_SOURCES = \
	playmidi1.cpp

nodist_playmidi1_SOURCES = \
	debugPaths.cpp

playmidi1_LDADD = \
	$(top_builddir)/libmutabordebugtest.a \
	$(top_builddir)/libmutaborgui.a \
	$(top_builddir)/libmutaborrouting.a \
	$(top_builddir)/libmutaborkernel.a \
	$(top_builddir)/librtmidi.a \
	$(top_builddir)/src/wxintl/libwxintl.a \
	$(LDADD) \
	$(AM_LDFLAGS)

midiopenfail1_LDADD = \
	$(top_builddir)/libmutabordebugtest.a \
	$(top_builddir)/libmutaborgui.a \
	$(top_builddir)/libmutaborrouting.a \
	$(top_builddir)/libmutaborkernel.a \
	$(top_builddir)/librtmidi.a \
	$(top_builddir)/src/wxintl/libwxintl.a \
	$(LDADD) \
	$(AM_LDFLAGS)

midiopenfail1_SOURCES = \
	midiopenfail1.cpp

nodist_midiopenfail1_SOURCES = \
	debugPaths.cpp


if HAVE_CPPUNIT
check_SCRIPTS += \
	$(srcdir)/all_controller_off.mid

TESTS += \
	testcppunit$(EXEEXT)

check_PROGRAMS += testcppunit

testcppunit_CXXFLAGS =  $(CPPUNIT_CFLAGS) $(AM_CXXFLAGS)

testcppunit_SOURCES = \
	main.cpp \
	DevMidFTest.h \
	DevMidFTest.cpp \
	midicmnTest.h \
	midicmnTest.cpp

nodist_testcppunit_SOURCES = \
	debugPaths.cpp

testcppunit_LDADD = \
	$(top_builddir)/libmutabormaincppunit.a \
	$(top_builddir)/src/wxintl/libwxintl.a \
	$(CPPUNIT_LIBS) \
	$(LDADD) \
	$(AM_LDFLAGS)
endif


playmidi1.mid: midi1_source.mid
	cp `(if test -f '$<' ; then  echo '$<' ; else echo '$(top_srcdir)/$<' ; fi )` $@


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

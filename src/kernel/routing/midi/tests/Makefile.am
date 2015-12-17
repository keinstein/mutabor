include $(top_srcdir)/common-rules.mk
include $(top_srcdir)/common-linklibs.mk

CLEANFILES += \
	playmidi1.mid \
	test_output.mid \
	test_output2.mid

AM_CPPFLAGS += -DSRCDIR="\"$(srcdir)\""
check_PROGRAMS = \
	playmidi1 \
	midiopenfail1 \
	genmidirnd \
	genmidilinear

EXTRA_DIST = \
	midi1_source.mid \
	midi1_source.txt \
	bug019010.mid \
	bug019010.txt \
	controller.txt \
	controller.mid \
	bank_select.txt \
	bank_select.mid \
	all_controller_off.txt \
	all_controller_off.mid \
	rpn_nrpn.txt \
	rpn_nrpn.mid \
	controller.txt \
	controller.mid \
	midiin.txt \
	midiin.mid \
	midiin.mut \
	aftertouch.txt \
	aftertouch.mid \
	sysex.txt \
	sysex.mid


check_SCRIPTS = playmidi1.mid

TESTS = \
	playmidi1$(EXEEXT) \
	midiopenfail1$(EXEEXT) \
	genmidirnd$(EXEEXT) \
	genmidilinear$(EXEEXT)

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
	$(AM_LDFLAGS) \
	$(BOOST_FILESYSTEM_LDFLAGS) \
	$(BOOST_SYSTEM_LDFLAGS) \
	$(BOOST_FILESYSTEM_LIBS) \
	$(BOOST_SYSTEM_LIBS)

midiopenfail1_LDADD = \
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

midiopenfail1_SOURCES = \
	midiopenfail1.cpp

nodist_midiopenfail1_SOURCES = \
	debugPaths.cpp

genmidirnd_SOURCES = \
	genmidirnd.cpp

nodist_genmidirnd_SOURCES = \
	debugPaths.cpp

genmidirnd_LDADD = \
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


genmidilinear_SOURCES = \
	genmidilinear.cpp

nodist_genmidilinear_SOURCES = \
	debugPaths.cpp

genmidilinear_LDADD = \
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
check_SCRIPTS += \
	$(srcdir)/midi1_source.mid \
	$(srcdir)/bug019010.mid \
	$(srcdir)/bank_select.mid \
	$(srcdir)/all_controller_off.mid \
	$(srcdir)/rpn_nrpn.mid \
	$(srcdir)/controller.mid \
	$(srcdir)/midiin.mid \
	$(srcdir)/aftertouch.mid \
	$(srcdir)/sysex.mid

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
	$(AM_LDFLAGS) \
	$(BOOST_FILESYSTEM_LDFLAGS) \
	$(BOOST_SYSTEM_LDFLAGS) \
	$(BOOST_FILESYSTEM_LIBS) \
	$(BOOST_SYSTEM_LIBS)
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

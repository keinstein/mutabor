include $(top_srcdir)/common-rules.mk
include $(top_srcdir)/common-linklibs.mk

CLEANFILES += \
	playmidi1.mid \
	test_output.mid

AM_CPPFLAGS += -DSRCDIR="\"$(srcdir)\""
check_PROGRAMS = \
	playmidi1 \
	midiopenfail1

EXTRA_DIST = midi1_source.mid

check_SCRIPTS = playmidi1.mid

TESTS = \
	playmidi1$(EXEEXT) \
	midiopenfail1$(EXEEXT)

playmidi1_SOURCES = \
	playmidi1.cpp

playmidi1_LDADD = \
	$(top_builddir)/libmutaborrouting.a \
	$(top_builddir)/libmutaborkernel.a \
	$(top_builddir)/libmutabordebug.a \
	$(top_builddir)/librtmidi.a \
	$(LDADD) \
	$(AM_LDFLAGS)

midiopenfail1_LDADD = \
	$(top_builddir)/libmutaborrouting.a \
	$(top_builddir)/libmutaborkernel.a \
	$(top_builddir)/libmutabordebug.a \
	$(top_builddir)/librtmidi.a \
	$(LDADD) \
	$(AM_LDFLAGS)

midiopenfail1_SOURCES = \
	midiopenfail1.cpp


if HAVE_CPPUNIT
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

testcppunit_LDADD = \
	$(top_builddir)/libmutaborrouting.a \
	$(top_builddir)/libmutaborkernel.a \
	$(top_builddir)/libmutabordebug.a \
	$(top_builddir)/librtmidi.a \
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

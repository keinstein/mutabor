#include $(top_srcdir)/common-rules.mk
#include $(top_srcdir)/common-linklibs.mk
DEBUGPATHS +=  \
	%D%/debugPaths.cpp

CLEANFILES += \
	%D%/playmidi1.mid \
	%D%/test_output.mid \
	%D%/test_output2.mid

check_PROGRAMS += \
	%D%/playmidi1 \
	%D%/midiopenfail1 \
	%D%/genmidirnd \
	%D%/genmidilinear

EXTRA_DIST += \
	%D%/midi1_source.mid \
	%D%/midi1_source.txt \
	%D%/bug019010.mid \
	%D%/bug019010.txt \
	%D%/controller.txt \
	%D%/controller.mid \
	%D%/bank_select.txt \
	%D%/bank_select.mid \
	%D%/all_controller_off.txt \
	%D%/all_controller_off.mid \
	%D%/rpn_nrpn.txt \
	%D%/rpn_nrpn.mid \
	%D%/controller.txt \
	%D%/controller.mid \
	%D%/midiin.txt \
	%D%/midiin.mid \
	%D%/midiin.mut \
	%D%/aftertouch.txt \
	%D%/aftertouch.mid \
	%D%/sysex.txt \
	%D%/sysex.mid


check_SCRIPTS += %D%/playmidi1.mid

TESTS += \
	%D%/playmidi1$(EXEEXT) \
	%D%/midiopenfail1$(EXEEXT) \
	%D%/genmidirnd$(EXEEXT) \
	%D%/genmidilinear$(EXEEXT)

%C%_playmidi1_CPPFLAGS = $(CPPFLAGS) \
	-DSRCDIR="\"$(srcdir)/%D%/\""
%C%_playmidi1_SOURCES = \
	%D%/playmidi1.cpp

nodist_%C%_playmidi1_SOURCES = \
	%D%/debugPaths.cpp

%C%_playmidi1_LDADD = \
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

%C%_midiopenfail1_LDADD = \
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

%C%_midiopenfail1_SOURCES = \
	%D%/midiopenfail1.cpp

nodist_%C%_midiopenfail1_SOURCES = \
	%D%/debugPaths.cpp

%C%_genmidirnd_SOURCES = \
	%D%/genmidirnd.cpp

nodist_%C%_genmidirnd_SOURCES = \
	%D%/debugPaths.cpp

%C%_genmidirnd_LDADD = \
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


%C%_genmidilinear_SOURCES = \
	%D%/genmidilinear.cpp

nodist_%C%_genmidilinear_SOURCES = \
	%D%/debugPaths.cpp

%C%_genmidilinear_LDADD = \
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
check_SCRIPTS += \
	$(srcdir)/%D%/midi1_source.mid \
	$(srcdir)/%D%/bug019010.mid \
	$(srcdir)/%D%/bank_select.mid \
	$(srcdir)/%D%/all_controller_off.mid \
	$(srcdir)/%D%/rpn_nrpn.mid \
	$(srcdir)/%D%/controller.mid \
	$(srcdir)/%D%/midiin.mid \
	$(srcdir)/%D%/aftertouch.mid \
	$(srcdir)/%D%/sysex.mid

TESTS += \
	%D%/testcppunit$(EXEEXT)

check_PROGRAMS += %D%/testcppunit

%C%_testcppunit_CPPFLAGS = $(CPPFLAGS) \
	-DSRCDIR="\"$(srcdir)/%D%/\""
%C%_testcppunit_CXXFLAGS = \
	$(CPPUNIT_CFLAGS) \
	$(AM_CXXFLAGS)


%C%_testcppunit_SOURCES = \
	%D%/main.cpp \
	%D%/DevMidFTest.h \
	%D%/DevMidFTest.cpp \
	%D%/midicmnTest.h \
	%D%/midicmnTest.cpp

nodist_%C%_testcppunit_SOURCES = \
	%D%/debugPaths.cpp

%C%_testcppunit_LDADD = \
	libmutabormaincppunit.a \
	src/kernel/libmutaborkernel.a \
	src/wxintl/libwxintl.a \
	$(CPPUNIT_LIBS) \
	$(LDADD) \
	$(AM_LDFLAGS) \
	$(BOOST_FILESYSTEM_LDFLAGS) \
	$(BOOST_SYSTEM_LDFLAGS) \
	$(BOOST_FILESYSTEM_LIBS) \
	$(BOOST_SYSTEM_LIBS)
endif


%D%/playmidi1.mid: %D%/midi1_source.mid
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

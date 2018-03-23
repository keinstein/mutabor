#include $(top_srcdir)/common-rules.mk
#include $(top_srcdir)/common-linklibs.mk

EXTRA_DIST += \
	$(srcdir)/%D%/lsan_suppressions.txt

CLEANFILES += \
	%D%/*.class \
	test_rnd.mid \
	test_output.mid \
	test_linear.mid \
	test_output2.mid

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
	%D%/midiin.mut

check_SCRIPTS += \
	%D%/midiin.mut

check_MIDIFILES += $(srcdir)/%D%/playmidi1.mid
check_MIDISOURCES += \
	$(srcdir)/%D%/midi1_source.txt \
	$(srcdir)/%D%/bug019010.txt \
	$(srcdir)/%D%/controller.txt \
	$(srcdir)/%D%/bank_select.txt \
	$(srcdir)/%D%/all_controller_off.txt \
	$(srcdir)/%D%/rpn_nrpn.txt \
	$(srcdir)/%D%/controller.txt \
	$(srcdir)/%D%/midiin.txt \
	$(srcdir)/%D%/aftertouch.txt \
	$(srcdir)/%D%/sysex.txt

TESTS += \
	%D%/playmidi1$(EXEEXT) \
	%D%/midiopenfail1$(EXEEXT) \
	%D%/genmidirnd$(EXEEXT) \
	%D%/genmidilinear$(EXEEXT)

%C%_playmidi1_CPPFLAGS = $(CPPFLAGS) \
	-DSRCDIR="\"$(srcdir)/%D%/\"" \
	$(WXINTLCXXFLAGS)

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
	lib/rtmidi/librtmidi@rtmidi_suffix@.la \
	src/wxintl/libwxintl.la \
	$(LDADD) \
	$(AM_LDFLAGS) \
	$(BOOST_LDFLAGS) \
	$(BOOST_FILESYSTEM_LDFLAGS) \
	$(BOOST_SYSTEM_LDFLAGS) \
	$(BOOST_FILESYSTEM_LIB) \
	$(BOOST_SYSTEM_LIB)

%C%_midiopenfail1_LDADD = \
	libmutabordebugtest.a \
	libmutaborgui.a \
	libmutaborrouting.a \
	src/kernel/libmutaborkernel.a \
	libmutaborscala.a \
	lib/rtmidi/librtmidi@rtmidi_suffix@.la \
	src/wxintl/libwxintl.la \
	$(LDADD) \
	$(AM_LDFLAGS) \
	$(BOOST_LDFLAGS) \
	$(BOOST_FILESYSTEM_LDFLAGS) \
	$(BOOST_SYSTEM_LDFLAGS) \
	$(BOOST_FILESYSTEM_LIB) \
	$(BOOST_SYSTEM_LIB)

%C%_midiopenfail1_CXXFLAGS = \
	$(WXINTLCXXFLAGS)

%C%_midiopenfail1_SOURCES = \
	%D%/midiopenfail1.cpp

nodist_%C%_midiopenfail1_SOURCES = \
	%D%/debugPaths.cpp

%C%_genmidirnd_CXXFLAGS = \
	$(WXINTLCXXFLAGS)

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
	lib/rtmidi/librtmidi@rtmidi_suffix@.la \
	src/wxintl/libwxintl.la \
	$(LDADD) \
	$(AM_LDFLAGS) \
	$(BOOST_LDFLAGS) \
	$(BOOST_FILESYSTEM_LDFLAGS) \
	$(BOOST_SYSTEM_LDFLAGS) \
	$(BOOST_FILESYSTEM_LIB) \
	$(BOOST_SYSTEM_LIB)


%C%_genmidilinear_SOURCES = \
	%D%/genmidilinear.cpp

%C%_genmidilinear_CXXFLAGS = \
	$(WXINTLCXXFLAGS)

nodist_%C%_genmidilinear_SOURCES = \
	%D%/debugPaths.cpp

%C%_genmidilinear_LDADD = \
	libmutabordebugtest.a \
	libmutaborgui.a \
	libmutaborrouting.a \
	src/kernel/libmutaborkernel.a \
	libmutaborscala.a \
	lib/rtmidi/librtmidi@rtmidi_suffix@.la \
	src/wxintl/libwxintl.la \
	$(LDADD) \
	$(AM_LDFLAGS) \
	$(BOOST_LDFLAGS) \
	$(BOOST_FILESYSTEM_LDFLAGS) \
	$(BOOST_SYSTEM_LDFLAGS) \
	$(BOOST_FILESYSTEM_LIB) \
	$(BOOST_SYSTEM_LIB)


BUILT_SOURCES += \
	%D%/asan_options.cpp
CLEANFILES += \
	%D%/asan_options.cpp


%D%/asan_options.cpp: Makefile
	echo '#ifdef __cplusplus' > "$@.tmp"
	echo 'extern "C"' >> "$@.tmp"
	echo '#endif' >> "$@.tmp"
	echo '__attribute__((no_sanitize_address))' >> "$@.tmp"
	echo 'const char *__asan_default_options() {' >> "$@.tmp"
	echo '  return "fast_unwind_on_malloc=0:report_globals=1:print_full_thread_history=1:suppressions=$(srcdir)/%D%/lsan_suppressions.txt";' >> "$@.tmp"
	echo '}' >> "$@.tmp"
	cmp $@ $@.tmp && rm -f $@.tmp || ( mv "$@.tmp" "$@" ; echo "created $@")


if HAVE_CPPUNIT
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
	src/wxintl/libwxintl.la \
	lib/rtmidi/librtmidi@rtmidi_suffix@.la \
	$(CPPUNIT_LIBS) \
	$(LDADD) \
	$(AM_LDFLAGS) \
	$(BOOST_LDFLAGS) \
	$(BOOST_FILESYSTEM_LDFLAGS) \
	$(BOOST_SYSTEM_LDFLAGS) \
	$(BOOST_FILESYSTEM_LIB) \
	$(BOOST_SYSTEM_LIB)
endif


$(srcdir)/%D%/playmidi1.mid: $(srcdir)/%D%/midi1_source.mid
	cp `(if test -f '$<' ; then  echo '$<' ; else echo '$(srcdir)/$<' ; fi )` $@


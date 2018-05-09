#include $(top_srcdir)/common-rules.mk
#include $(top_srcdir)/common-linklibs.mk

#TESTS =
#check_PROGRAMS =

DEBUGPATHS += \
	%D%/debugPaths.cpp


if HAVE_CPPUNIT
TESTS += \
	%D%/testcppunit$(EXEEXT)

check_PROGRAMS += %D%/testcppunit

%C%_testcppunit_CXXFLAGS = $(AM_CXXFLAGS) $(CPPUNIT_CFLAGS)

%C%_testcppunit_SOURCES = \
	%D%/main.cpp \
	%D%/GUIRouteTest.h \
	%D%/GUIRouteTest.cpp
#	%D%/asan_options.cpp


nodist_%C%_testcppunit_SOURCES = \
	%D%/debugPaths.cpp

%C%_testcppunit_LDADD = \
	libmutabormaincppunit.a \
	src/kernel/libmutaborkernel.a \
	lib/rtmidi/librtmidi@rtmidi_suffix@.la \
	src/wxintl/libwxintl.la \
	libmutabordebug.a \
	$(LDADD) \
	$(AM_LDFLAGS) \
	$(WX_LIBS) \
	$(CPPUNIT_LIBS) \
	$(BOOST_FILESYSTEM_LDFLAGS) \
	$(BOOST_SYSTEM_LDFLAGS) \
	$(BOOST_FILESYSTEM_LIB) \
	$(BOOST_THREAD_LIB) \
	$(BOOST_CHRONO_LIB) \
	$(BOOST_SYSTEM_LIB)
endif

EXTRA_DIST += \
	$(srcdir)/%D%/lsan_suppressions.txt

BUILT_SOURCES += \
	%D%/asan_options.cpp
CLEANFILES += \
	%D%/asan_options.cpp \
	%D%/*.class

%D%/asan_options.cpp: Makefile
	echo '#ifdef __cplusplus' > "$@.tmp"
	echo 'extern "C"' >> "$@.tmp"
	echo '#endif' >> "$@.tmp"
	echo '__attribute__((no_sanitize_address))' >> "$@.tmp"
	echo 'const char *__asan_default_options() {' >> "$@.tmp"
	echo '  return "fast_unwind_on_malloc=0:report_globals=1:print_full_thread_history=1:suppressions=$(srcdir)/%D%/lsan_suppressions.txt";' >> "$@.tmp" ;
	echo '}' >> "$@.tmp" ; \
	cmp $@ $@.tmp && rm -f $@.tmp || ( mv "$@.tmp" "$@" ; echo "created $@")


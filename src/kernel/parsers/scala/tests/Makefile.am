include $(top_srcdir)/common-rules.mk
include $(top_srcdir)/common-linklibs.mk

BUILT_SOURCES +=  \
	debugPaths.cpp

EXTRA_DIST = 
#	all.mut

TEST_EXTENSIONS = .scl

SCL_LOG_COMPILER = ./run_scl2mut.sh

SCLTESTS = \
	allowed001.scl \
	allowed002.scl \
	allowed003.scl \
	allowed004.scl \
	allowed005.scl \
	allowed006.scl \
	allowed007.scl \
	allowed008.scl \
	allowed009.scl

TESTS = \
	test_empty$(EXEEXT) \
	test_empty_comments$(EXEEXT) \
	test_intervals1$(EXEEXT) \
	$(SCLTESTS)







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

$(SCLTESTS:.scl=.log): ./run_scl2mut.sh

./run_scl2mut.sh: $(top_builddir)/scl2mut Makefile
	@echo '#!/bin/sh' > $@
	@echo 'file="$$1"' >> $@
	@echo 'basefile=`basename "$$file"`' >> $@
	@echo 'ls "$(top_builddir)/scl2mut" "$$file" "$${basefile%.scl}.mut2"' >> $@
	@echo '"$(top_builddir)/scl2mut" "$$file" "$${basefile%.scl}.mut2" || exit 1' >> $@
	@echo 'diff "$${file%.scl}.mut" "$${basefile%.scl}.mut2" || exit 2' >> $@
	@echo 'exit 0' >> $@
	@chmod u+x $@

.PHONY: $(top_builddir)/scl2mut

$(top_builddir)/scl2mut:
	$(MAKE) -C $(top_builddir) scl2mut


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


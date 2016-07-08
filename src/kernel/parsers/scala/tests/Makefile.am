#include $(top_srcdir)/common-rules.mk
#include $(top_srcdir)/common-linklibs.mk

BUILT_SOURCES +=  \
	debugPaths.cpp

EXTRA_DIST +=
#	all.mut

# .nscl is a .scl file that should be rejected
TEST_EXTENSIONS += .scl .nscl .kbm


SCL_LOG_COMPILER = ./run_scl2mut.sh
NSCL_LOG_COMPILER = ./run_nscl2mut.sh
KBM_LOG_COMPILER = ./run_kbm2mut.sh

SCLTESTS = \
	%D%/allowed001.scl \
	%D%/allowed002.scl \
	%D%/allowed003.scl \
	%D%/allowed004.scl \
	%D%/allowed005.scl \
	%D%/allowed006.scl \
	%D%/allowed007.scl \
	%D%/allowed008.scl \
	%D%/allowed009.scl

NSCLTESTS = \
	%D%/not_allowed001.nscl \
	%D%/not_allowed002.nscl \
	%D%/not_allowed003.nscl \
	%D%/not_allowed004.nscl

KBMTESTS = \
	%D%/allowed001_kbm.kbm \
	%D%/allowed002_kbm.kbm \
	%D%/allowed003_kbm.kbm \
	%D%/allowed004_kbm.kbm \
	%D%/allowed005_kbm.kbm \
	%D%/allowed006_kbm.kbm \
	%D%/allowed007_kbm.kbm \
	%D%/allowed008_kbm.kbm

TESTS += \
	%D%/test_empty$(EXEEXT) \
	%D%/test_empty_comments$(EXEEXT) \
	%D%/test_intervals1$(EXEEXT) \
	%D%/test_keymaps$(EXEEXT) \
	$(SCLTESTS) \
	$(NSCLTESTS) \
	$(KBMTESTS)







check_PROGRAMS += \
	%D%/test_empty \
	%D%/test_empty_comments \
	%D%/test_intervals1 \
	%D%/test_keymaps

nodist_%C%_test_empty_SOURCES = \
	debugPaths.cpp

%C%_test_empty_SOURCES = \
	%D%/test_empty.cpp

%C%_test_empty_LDADD = \
	libmutaborscala.a \
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

nodist_%C%_test_empty_comments_SOURCES = \
	debugPaths.cpp

%C%_test_empty_comments_SOURCES = \
	%D%/test_empty_comments.cpp

%C%_test_empty_comments_LDADD = \
	libmutaborscala.a \
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

nodist_%C%_test_intervals1_SOURCES = \
	debugPaths.cpp

%C%_test_intervals1_SOURCES = \
	%D%/test_intervals1.cpp

%C%_test_intervals1_LDADD = \
	libmutaborscala.a \
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

nodist_%C%_test_keymaps_SOURCES = \
	debugPaths.cpp

%C%_test_keymaps_SOURCES = \
	%D%/test_keymaps.cpp

%C%_test_keymaps_LDADD = \
	libmutaborscala.a \
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
# 	libmutabormaincppunit.a \
# 	libmutabordebugcppunit.a \
# 	libmutaborgui.a \
# 	src/kernel/libmutaborkernel.a \
# 	libmutaborrouting.a \
# 	librtmidi.a \
# 	src/wxintl/libwxintl.a \
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
$(NSCLTESTS:.nscl=.log): ./run_nscl2mut.sh
$(KBMTESTS:.kbm=.log): ./run_kbm2mut.sh

./run_scl2mut.sh: scl2mut$(EXEEXT) Makefile
	@echo '#!/bin/sh' > $@
	@echo 'file="$$1"' >> $@
	@echo 'basefile=`basename "$$file"`' >> $@
	@echo 'LC_ALL=C' >> $@
	@echo 'export LC_ALL' >> $@
	@echo '"./scl2mut" "$$file" "$${basefile%.scl}.mut2" || exit 1' >> $@
	@echo 'diff -u "$${file%.scl}.mut" "$${basefile%.scl}.mut2" || exit 2' >> $@
	@echo 'exit 0' >> $@
	@chmod u+x $@

./run_nscl2mut.sh: scl2mut$(EXEEXT) Makefile
	@echo '#!/bin/sh' > $@
	@echo 'file="$$1"' >> $@
	@echo 'basefile=`basename "$$file"`' >> $@
	@echo 'LC_ALL=C' >> $@
	@echo 'export LC_ALL' >> $@
	@echo '"./scl2mut" "$$file" "$${basefile%.scl}.mut2" 2>&1 | tee $${basefile%.nscl}.log2 || exit 1' >> $@
	@echo 'echo "starting grep..."' >> $@
	@echo 'grep -Pzo -f $${file%.nscl}.err $${basefile%.nscl}.log2 || exit 2' >> $@
	@echo 'exit 0' >> $@
	@chmod u+x $@

./run_kbm2mut.sh: scl2mut$(EXEEXT) Makefile
	@echo '#!/bin/sh' > $@
	@echo 'file="$$1"' >> $@
	@echo 'dir="`dirname $$file`"' >> $@
	@echo 'basefile=`basename "$$file"`' >> $@
	@echo 'LC_ALL=C' >> $@
	@echo 'export LC_ALL' >> $@
	@echo './scl2mut --debug-sclparser -k $$file "$$dir/12tet.scl" "$${basefile%.kbm}.mut2" || exit 1' >> $@
	@echo 'diff -u $${file%.kbm}.mut $${basefile%.kbm}.mut2 || exit 2' >> $@
	@echo 'exit 0' >> $@
	@chmod u+x $@



#.PHONY: scl2mut

#scl2mut:
#	$(MAKE) $(AM_MAKEFLAGS) -C $(top_builddir) scl2mut


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


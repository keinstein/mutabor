#include $(top_srcdir)/common-rules.mk
#include $(top_srcdir)/common-linklibs.mk

CLEANFILES += %D%/*.class

DEBUGPATHS +=  \
	%D%/debugPaths.cpp

#	all.mut



check_SCLFILES += \
	%D%/allowed001.scl \
	%D%/allowed002.scl \
	%D%/allowed003.scl \
	%D%/allowed004.scl \
	%D%/allowed005.scl \
	%D%/allowed006.scl \
	%D%/allowed007.scl \
	%D%/allowed008.scl \
	%D%/allowed009.scl

check_NSCLFILES += \
	%D%/not_allowed001.nscl \
	%D%/not_allowed002.nscl \
	%D%/not_allowed003.nscl \
	%D%/not_allowed004.nscl

check_KBMFILES += \
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
	%D%/test_keymaps$(EXEEXT)


check_PROGRAMS += \
	%D%/test_empty \
	%D%/test_empty_comments \
	%D%/test_intervals1 \
	%D%/test_keymaps

nodist_%C%_test_empty_SOURCES = \
	%D%/debugPaths.cpp


%C%_test_empty_SOURCES = \
	%D%/test_empty.cpp

%C%_test_empty_LDADD = \
	libmutaborscala.a \
	libmutaborrouting.a \
	libmutabordebugnogui.a \
	src/kernel/libmutaborkernel.a \
	lib/rtmidi/librtmidi@rtmidi_suffix@.la \
	src/wxintl/libboostintl.a \
	$(LDADD) \
	$(AM_LDFLAGS) \
	$(BOOST_LDFLAGS) \
	$(BOOST_FILESYSTEM_LIB) \
	$(BOOST_LOCALE_LIB) \
	$(BOOST_SYSTEM_LIB)

nodist_%C%_test_empty_comments_SOURCES = \
	%D%/debugPaths.cpp

%C%_test_empty_comments_SOURCES = \
	%D%/test_empty_comments.cpp

%C%_test_empty_comments_LDADD = \
	libmutaborscala.a \
	libmutaborrouting.a \
	libmutabordebugnogui.a \
	src/kernel/libmutaborkernel.a \
	lib/rtmidi/librtmidi@rtmidi_suffix@.la \
	src/wxintl/libboostintl.a \
	$(LDADD) \
	$(AM_LDFLAGS) \
	$(BOOST_LDFLAGS) \
	$(BOOST_FILESYSTEM_LIB) \
	$(BOOST_LOCALE_LIB) \
	$(BOOST_SYSTEM_LIB)

nodist_%C%_test_intervals1_SOURCES = \
	%D%/debugPaths.cpp

%C%_test_intervals1_SOURCES = \
	%D%/test_intervals1.cpp

%C%_test_intervals1_LDADD = \
	libmutaborscala.a \
	libmutaborrouting.a \
	libmutabordebugnogui.a \
	src/kernel/libmutaborkernel.a \
	lib/rtmidi/librtmidi@rtmidi_suffix@.la \
	src/wxintl/libboostintl.a \
	$(LDADD) \
	$(AM_LDFLAGS) \
	$(BOOST_LDFLAGS) \
	$(BOOST_FILESYSTEM_LIB) \
	$(BOOST_LOCALE_LIB) \
	$(BOOST_SYSTEM_LIB)

nodist_%C%_test_keymaps_SOURCES = \
	%D%/debugPaths.cpp

%C%_test_keymaps_SOURCES = \
	%D%/test_keymaps.cpp

%C%_test_keymaps_LDADD = \
	libmutaborscala.a \
	libmutaborrouting.a \
	libmutabordebugnogui.a \
	src/kernel/libmutaborkernel.a \
	lib/rtmidi/librtmidi@rtmidi_suffix@.la \
	src/wxintl/libboostintl.a \
	$(LDADD) \
	$(AM_LDFLAGS) \
	$(BOOST_LDFLAGS) \
	$(BOOST_FILESYSTEM_LIB) \
	$(BOOST_LOCALE_LIB) \
	$(BOOST_SYSTEM_LIB)


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
# 	lib/rtmidi/librtmidi@rtmidi_suffix@.la \
# 	debugPaths.cpp
#
# testcppunit_LDADD = \
# 	libmutabormaincppunit.a \
# 	libmutabordebugcppunit.a \
# 	libmutaborgui.a \
# 	src/kernel/libmutaborkernel.a \
# 	libmutaborrouting.a \
# 	src/wxintl/libwxintl.la \
# 	$(LDADD) \
# 	$(AM_LDFLAGS) \
# 	$(CPPUNIT_LIBS) \
# 	$(BOOST_LDFLAGS) \
# 	$(BOOST_FILESYSTEM_LIB) \
# 	$(BOOST_SYSTEM_LIB)
#
# endif

# 
# %D%/run_scl2mut.sh: scl2mut$(EXEEXT) Makefile
# 	@echo '#!/bin/sh' > $@
# 	@echo 'file="$$1"' >> $@
# 	@echo 'basefile=`basename "$$file"`' >> $@
# 	@echo "outputdir='%D%/'" >> $@
# 	@echo 'LC_ALL=C' >> $@
# 	@echo 'export LC_ALL' >> $@
# 	@echo '"./scl2mut$(EXEEXT)" "$$file" "$$outputdir$${basefile%.scl}.mut2" || exit 1' >> $@
# 	echo 'sed "s/\$$//" "$$outputdir$${basefile%.scl}.mut2" | diff -u "$${file%.scl}.mut" - || exit 2' >> $@
# 	@echo 'exit 0' >> $@
# 	@chmod u+x $@
# 
# %D%/run_nscl2mut.sh: scl2mut$(EXEEXT) Makefile
# 	@echo '#!/bin/sh' > $@
# 	@echo 'file="$$1"' >> $@
# 	@echo 'basefile=`basename "$$file"`' >> $@
# 	@echo "outputdir='%D%/'" >> $@
# 	@echo 'LC_ALL=C' >> $@
# 	@echo 'export LC_ALL' >> $@
# 	@echo '"./scl2mut$(EXEEXT)" "$$file" "$$outputdir$${basefile%.scl}.mut2" 2>&1 | tee $$outputdir$${basefile%.nscl}.log2 || exit 1' >> $@
# 	@echo 'echo "starting grep..."' >> $@
# 	@echo 'grep -Eo -f $${file%.nscl}.err $$outputdir$${basefile%.nscl}.log2 || exit 2' >> $@
# 	@echo 'exit 0' >> $@
# 	@chmod u+x $@
# 
# %D%/run_kbm2mut.sh: scl2mut$(EXEEXT) Makefile
# 	@echo '#!/bin/sh' > $@
# 	@echo 'file="$$1"' >> $@
# 	@echo 'dir="`dirname $$file`"' >> $@
# 	@echo 'basefile=`basename "$$file"`' >> $@
# 	@echo "outputdir='%D%/'" >> $@
# 	@echo 'LC_ALL=C' >> $@
# 	@echo 'export LC_ALL' >> $@
# 	@echo './scl2mut$(EXEEXT) -k $$file "$$dir/12tet.scl" "$$outputdir$${basefile%.kbm}.mut2" || exit 1' >> $@
# 	@echo 'sed "s/\$$//" "$$outputdir$${basefile%.kbm}.mut2" | diff -u "$${file%.kbm}.mut" - || exit 2' >> $@
# 	@echo 'exit 0' >> $@
# 	@chmod u+x $@
# 


#.PHONY: scl2mut

#scl2mut:
#	$(MAKE) $(AM_MAKEFLAGS) -C $(top_builddir) scl2mut


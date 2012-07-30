include $(top_srcdir)/common-rules.mk
include $(top_srcdir)/common-linklibs.mk

check_PROGRAMS=timer1

TESTS=timer1$(EXEEXT)

timer1_SOURCES=timer1.cpp
timer1_LDADD=$(top_builddir)/libmutaborrouting.a $(top_builddir)/libmutaborkernel.a $(top_builddir)/libmutabordebug.a $(LDADD) $(AM_LDFLAGS)

if COPYDLLS
check-am: check-dll

check-dll: all-am
	$(MAKE) $(AM_MAKEFLAGS) $(check_PROGRAMS)
	$(MAKE) $(AM_MAKEFLAGS)	linkchecks

linkchecks:
	for d in `echo $(TESTS)| tr ' ' '\n' | grep -i -e '$(EXEEXT)$$'` ; \
	do \
		ls -l "$$d" ; \
		$(MAKE) $(AM_MAKEFLAGS) DLLLINKFILE=".libs/$$d" DLLEXEDIR="." installdll ; \
	done
endif

include $(top_srcdir)/common-rules.mk
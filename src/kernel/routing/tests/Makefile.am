buildincludedir=$(top_builddir)
AM_CPPFLAGS = -I$(buildincludedir)  \
	-I$(top_srcdir)/includes \
	-I$(top_srcdir) \
	@NETINET_INC@ \
	-I $(top_builddir)/intl \
	$(WX_CPPFLAGS) \
	-DPREFIX='"$(prefix)"'
AM_LDFLAGS = $(ALSA_LIBS) $(WX_LIBS)
AM_CFLAGS = $(ALSA_CFLAGS)  $(WX_CFLAGS)
AM_CXXFLAGS = $(AM_CFLAGS)
AM_CXX = $(MAKE) $(AM_MAKEFLAGS) mutabor-precompile && $(CXX)

check_PROGRAMS=timer1

TESTS=timer1$(EXEEXT)

timer1_SOURCES=timer1.cpp

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
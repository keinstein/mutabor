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
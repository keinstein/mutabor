#include $(top_srcdir)/common-rules.mk
#include $(top_srcdir)/common-linklibs.mk

DEBUGPATHS +=  \
	%D%/debugPaths.cpp

CLEANFILES += %D%/playgmn1.gmn \
	%D%/*.class

EXTRA_DIST += %D%/gmn1_source.gmn

check_PROGRAMS += \
	%D%/playgmn1 \
	%D%/gmnopenfail1

check_SCRIPTS = %D%/playgmn1.gmn

TESTS += \
	%D%/playgmn1$(EXEEXT) \
	%D%/gmnopenfail1$(EXEEXT)

%C%_playgmn1_CPPFLAGS = $(CPPFLAGS) \
	-DSRCDIR="\"$(srcdir)/%D%/\""
%C%_playgmn1_SOURCES = \
	%D%/playgmn1.cpp

nodist_%C%_playgmn1_SOURCES = \
	%D%/debugPaths.cpp

%C%_playgmn1_LDADD = \
	libmutabormaintest.a \
	src/wxintl/libwxintl.a \
	$(LDADD) \
	$(AM_LDFLAGS) \
	$(BOOST_FILESYSTEM_LDFLAGS) \
	$(BOOST_SYSTEM_LDFLAGS) \
	$(BOOST_FILESYSTEM_LIBS) \
	$(BOOST_SYSTEM_LIBS) \
	$(RTMIDITESTLDFLAGS)

%C%_gmnopenfail1_LDADD = \
	libmutabormaintest.a \
	src/wxintl/libwxintl.a \
	$(LDADD) \
	$(AM_LDFLAGS) \
	$(BOOST_FILESYSTEM_LDFLAGS) \
	$(BOOST_SYSTEM_LDFLAGS) \
	$(BOOST_FILESYSTEM_LIBS) \
	$(BOOST_SYSTEM_LIBS) \
	$(RTMIDITESTLDFLAGS)

%C%_gmnopenfail1_SOURCES = \
	%D%/gmnopenfail1.cpp

nodist_%C%_gmnopenfail1_SOURCES = \
	%D%/debugPaths.cpp


%D%/playgmn1.gmn: %D%/gmn1_source.gmn
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

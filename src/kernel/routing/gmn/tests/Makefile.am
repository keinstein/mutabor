include $(top_srcdir)/common-rules.mk
include $(top_srcdir)/common-linklibs.mk

CLEANFILES += playgmn1.gmn

AM_CPPFLAGS += -DSRCDIR="\"$(srcdir)\""
EXTRA_DIST = gmn1_source.gmn

check_PROGRAMS = \
	playgmn1 \
	gmnopenfail1

check_SCRIPTS = playgmn1.gmn

TESTS = \
	playgmn1$(EXEEXT) \
	gmnopenfail1$(EXEEXT)

playgmn1_SOURCES = \
	debugPaths.cpp \
	playgmn1.cpp

playgmn1_LDADD = \
	$(top_builddir)/libmutabormaintest.a \
	$(LDADD) \
	$(AM_LDFLAGS)

gmnopenfail1_LDADD = \
	$(top_builddir)/libmutabormaintest.a \
	$(LDADD) \
	$(AM_LDFLAGS)

gmnopenfail1_SOURCES = \
	debugPaths.cpp \
	gmnopenfail1.cpp


playgmn1.gmn: gmn1_source.gmn
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

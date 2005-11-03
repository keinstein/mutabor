SUBDIRS = . tests
INCLUDES = -I../includes
AUTOMAKE_OPTIONS=foreign
AM_YFLAGS = -d -v --report=itemset

ACLOCAL_AMFLAGS = -I m4

BUILT_SOURCES=mutlex.h mut.h

lib_LTLIBRARIES = libmutabor.la
libmutabor_la_CFLAGS = -Wall
libmutabor_la_includedir = $(pkgincludedir)
libmutabor_la_include_HEADERS = ../includes/mutabor/object.h \
			../includes/mutabor/identifier.h \
			../includes/mutabor/intervalSum.h \
			../includes/mutabor/idlist.h \
			../includes/mutabor/ptrlist.h \
			../includes/mutabor/intervalPlaceholder.h \
			../includes/mutabor/intervalStretch.h \
			../includes/mutabor/intervalInv.h \
			../includes/mutabor/mutfile.h \
			../includes/mutabor/heap.h ../includes/mutabor/interval.h \
			../includes/mutabor/aktion.h ../includes/mutabor/anweisung.h \
			../includes/mutabor/argument.h ../includes/mutabor/ausloeser.h \
			../includes/mutabor/bad_decl.h ../includes/mutabor/case_liste.h \
			../includes/mutabor/global.h ../includes/mutabor/harmonie.h \
			../includes/mutabor/instrument.h ../includes/mutabor/logik.h \
			../includes/mutabor/midicalc.h ../includes/mutabor/mut_tab.h \
			../includes/mutabor/parameter.h ../includes/mutabor/parser.h \
			../includes/mutabor/tabgen.h ../includes/mutabor/taste.h \
			../includes/mutabor/ton.h ../includes/mutabor/tonsystem.h \
			../includes/mutabor/umstimmung.h 

libmutabor_la_SOURCES = object.c identifier.c \
			intervalSum.c intervalDiff.c \
			idlist.c intervalPlaceholder.c \
			intervalStretch.c intervalInv.c mutfile.c \
			ptrlist.c \
			mut.y mutlex.h mut.h \
			aktion.c anweisung.c argument.c ausloeser.c \
			case_liste.c harmonie.c heap.c instrument.c interval.c logik.c \
			midicalc.c parameter.c taste.c ton.c tonsystem.c umstimmung.c \
			errors.c mutlex.l interpreter.c 
#			parser.c

libmutabor_la_LDFLAGS = -version-info 0:0:0

SUFFIXES = .h

.l.h:
	$(LEXCOMPILE) `test -f $< || echo '$(srcdir)/'`$<
	sed '/^#/ s|$(LEX_OUTPUT_ROOT)\.c|$*.c|' $(LEX_OUTPUT_ROOT).c >$*.c
	rm -f $(LEX_OUTPUT_ROOT).c

.y.h:
	$(YACCCOMPILE) `test -f '$<' || echo '$(srcdir)/'`$<
	if test -f y.tab.h; then \
	  to=`echo "$*_H" | sed \
                -e 'y/abcdefghijklmnopqrstuvwxyz/ABCDEFGHIJKLMNOPQRSTUVWXYZ/' \
                -e 's/[^ABCDEFGHIJKLMNOPQRSTUVWXYZ]/_/g'`; \
	  sed "/^#/ s/Y_TAB_H/$$to/g" y.tab.h >$*.ht; \
	  rm -f y.tab.h; \
	  if cmp -s $*.ht $*.h; then \
	    rm -f $*.ht ;\
	  else \
	    mv $*.ht $*.h; \
	  fi; \
	fi
	if test -f y.output; then \
	  mv y.output $*.output; \
	fi
	sed '/^#/ s|y\.tab\.c|$@|' y.tab.c >$@t && mv $@t $@
	rm -f y.tab.c

mutlex.h: mutlex.l
mut.h: mut.y

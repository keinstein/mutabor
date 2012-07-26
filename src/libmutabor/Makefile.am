SUBDIRS = . tests
buildincludedir=$(top_builddir)/includes
INCLUDES = -I$(buildincludedir) -I$(top_srcdir)/includes \
	-I$(top_builddir)/$(INTLDIR) -I$(top_srcdir)/$(INTLDIR) \
	@NETINET_INC@ -I$(top_srcdir)/libasprintf -I$(top_srcdir)/missfunc
AUTOMAKE_OPTIONS=foreign
AM_YFLAGS = -d -v --report=itemset

ACLOCAL_AMFLAGS = -I m4

BUILT_SOURCES=$(srcdir)/mutlex.h $(srcdir)/mut.h

lib_LTLIBRARIES = libmutabor.la
libmutabor_la_CFLAGS = -Wall
libmutabor_la_includedir = $(pkgincludedir)
libmutabor_la_include_HEADERS = $(buildincludedir)/mutabor/object.h \
			$(buildincludedir)/mutabor/identifier.h \
			$(buildincludedir)/mutabor/intervalSum.h \
			$(buildincludedir)/mutabor/idlist.h \
			$(buildincludedir)/mutabor/ptrlist.h \
			$(buildincludedir)/mutabor/intervalPlaceholder.h \
			$(buildincludedir)/mutabor/intervalStretch.h \
			$(buildincludedir)/mutabor/intervalInv.h \
			$(buildincludedir)/mutabor/mutfile.h \
			$(buildincludedir)/mutabor/interval.h \
			$(top_srcdir)/includes/mutabor/heap.h \
			$(top_srcdir)/includes/mutabor/aktion.h \
			$(top_srcdir)/includes/mutabor/anweisung.h \
			$(top_srcdir)/includes/mutabor/argument.h \
			$(top_srcdir)/includes/mutabor/ausloeser.h \
			$(top_srcdir)/includes/mutabor/bad_decl.h \
			$(top_srcdir)/includes/mutabor/case_liste.h \
			$(top_srcdir)/includes/mutabor/global.h \
			$(top_srcdir)/includes/mutabor/harmonie.h \
			$(top_srcdir)/includes/mutabor/instrument.h \
			$(top_srcdir)/includes/mutabor/interpreter.h \
			$(top_srcdir)/includes/mutabor/logik.h \
			$(top_srcdir)/includes/mutabor/midicalc.h \
			$(top_srcdir)/includes/mutabor/mut_tab.h \
			$(top_srcdir)/includes/mutabor/parameter.h \
			$(top_srcdir)/includes/mutabor/parser.h \
			$(top_srcdir)/includes/mutabor/tabgen.h \
			$(top_srcdir)/includes/mutabor/taste.h \
			$(top_srcdir)/includes/mutabor/ton.h \
			$(top_srcdir)/includes/mutabor/tonsystem.h \
			$(top_srcdir)/includes/mutabor/umstimmung.h \
			$(top_srcdir)/includes/mutabor/errors.h 

libmutabor_la_SOURCES = object.c identifier.c \
			intervalSum.c intervalDiff.c \
			idlist.c intervalPlaceholder.c \
			intervalStretch.c intervalInv.c mutfile.c \
			ptrlist.c \
			mut.y $(srcdir)/mutlex.h $(srcdir)/mut.h \
			aktion.c anweisung.c argument.c ausloeser.c \
			case_liste.c harmonie.c heap.c instrument.c interval.c logik.c \
			midicalc.c parameter.c taste.c ton.c tonsystem.c umstimmung.c \
			errors.c mutlex.l interpreter.c \
			$(buildincludedir)/mutabor/object.hh \
			$(buildincludedir)/mutabor/identifier.hh \
			$(buildincludedir)/mutabor/intervalSum.hh \
			$(buildincludedir)/mutabor/idlist.hh \
			$(buildincludedir)/mutabor/ptrlist.hh \
			$(buildincludedir)/mutabor/intervalPlaceholder.hh \
			$(buildincludedir)/mutabor/intervalStretch.hh \
			$(buildincludedir)/mutabor/intervalInv.hh \
			$(buildincludedir)/mutabor/mutfile.hh \
			$(buildincludedir)/mutabor/interval.hh \
			$(top_srcdir)/libasprintf/lib-asprintf.c
#			parser.c

libmutabor_la_LDFLAGS = -version-info 0:0:0 @LTLIBINTL@ \
	$(top_builddir)/missfunc/libmissfunc.a

SUFFIXES = .h

.l.h:
	$(LEXCOMPILE) $<
	cfilename=`echo $@|sed 's/\.h$$/.c/;t'` && \
		sed '/^#/ s|$(LEX_OUTPUT_ROOT)\.c|$$cfilename|' \
		$(LEX_OUTPUT_ROOT).c >$$cfilename
	mv `sed 's,%option[ 	]\+header-file="\(.*\)".*,\1,;t;d' $<` $@
	mv `sed 's,%option[ 	]\+tables-file="\(.*\)".*,\1,;t;d' $<` $(srcdir)
.l.c:
	$(LEXCOMPILE) $<
	sed '/^#/ s|$(LEX_OUTPUT_ROOT)\.c|$@|' $(LEX_OUTPUT_ROOT).c >$@
	mv `sed 's,%option[ 	]\+header-file="\(.*\)".*,\1,;t;d' $<` $(srcdir)
	mv `sed 's,%option[ 	]\+tables-file="\(.*\)".*,\1,;t;d' $<` $(srcdir)


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


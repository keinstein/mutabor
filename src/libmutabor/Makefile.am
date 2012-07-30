SUBDIRS = tests
include $(top_srcdir)/common-rules.mk
override buildincludedir=$(top_builddir)/includes

BUILT_SOURCES += $(srcdir)/mutlex.h $(srcdir)/mut.h

lib_LTLIBRARIES = libmutabor.la
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
	$(top_builddir)/src/lib/missfunc/libmissfunc.a

mutlex.h $(srcdir)/mutlex.h: mutlex.l
$(srcdir)/mutlex.c: mutlex.l
	rm $(srcdir)/mutlex.h
	$(MAKE) $(AM_MAKEFLAGS) mutlex.h
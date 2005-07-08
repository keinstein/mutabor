INCLUDES = -I../includes
AUTOMAKE_OPTIONS=foreign
AM_YFLAGS = -d

ACLOCAL_AMFLAGS = -I m4

lib_LTLIBRARIES = libmutabor.la
libmutabor_la_CFLAGS = -Wall --ansi
libmutabor_la_SOURCES = ../includes/mutabor/heap.h ../includes/mutabor/interval.h \
			../includes/mutabor/aktion.h ../includes/mutabor/anweisung.h \
			../includes/mutabor/argument.h ../includes/mutabor/ausloeser.h \
			../includes/mutabor/bad_decl.h ../includes/mutaborcase_liste.h \
			../includes/mutabor/global.h ../includes/mutabor/harmonie.h \
			../includes/mutabor/instrument.h ../includes/mutabor/logik.h \
			../includes/mutabor/midicalc.h ../includes/mutabor/mut_tab.h \
			../includes/mutabor/parameter.h ../includes/mutabor/parser.h \
			../includes/mutabor/tabgen.h ../includes/mutabor/taste.h \
			../includes/mutabor/ton.h ../includes/mutabor/tonsystem.h \
			../includes/mutabor/umstimmung.h \
			mut.y \
			aktion.c anweisung.c argument.c ausloeser.c \
			case_liste.c harmonie.c heap.c instrument.c interval.c logik.c \
			midicalc.c parameter.c parser.c taste.c ton.c tonsystem.c umstimmung.c
libmutabor_la_LDFLAGS = -version-info 0:0:0

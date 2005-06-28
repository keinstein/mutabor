INCLUDES = -I../includes
AUTOMAKE_OPTIONS=foreign
AM_YFLAGS = -d

ACLOCAL_AMFLAGS = -I m4

lib_LTLIBRARIES = libmutabor.la
libmutabor_la_CFLAGS = -Wall --ansi
libmutabor_la_SOURCES = heap.c interval.c ../includes/mutabor/heap.h ../includes/mutabor/interval.h mut.y
libmutabor_la_LDFLAGS = -version-info 0:0:0

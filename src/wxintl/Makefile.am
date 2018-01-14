SUBDIRS += %D%/tests
CLEANFILES += %D%/*.class

noinst_LTLIBRARIES += %D%/libwxintl.la
#noinst_%C%_libwxintl_la_noinst_HEADERS = %D%/libintl.h
#BUILT_SOURCES = $(top_builddir)/intl/libintl.h
%C%_libwxintl_la_SOURCES = \
	%D%/libintl.cpp \
	%D%/libintl.h

all: all-wxintl@USE_INCLUDED_LIBWXINTL@
all-wxintlyes: %D%/libwxintl.la
all-wxintlno: all-wxintlno-@BUILD_INCLUDED_LIBWXINTL@
all-wxintlno-yes: %D%/libwxintl.la
all-wxintlno-no:

mac:

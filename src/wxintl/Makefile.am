SUBDIRS += %D%/tests

noinst_LIBRARIES += %D%/libwxintl.a
libwxintl_a_HEADRES = %D%/libintl.h
#BUILT_SOURCES = $(top_builddir)/intl/libintl.h
%C%_libwxintl_a_SOURCES = \
	%D%/libintl.cpp \
	%D%/libintl.h

all: all-wxintl@USE_INCLUDED_LIBWXINTL@
all-wxintlyes: %D%/libwxintl.a
all-wxintlno: all-wxintlno-@BUILD_INCLUDED_LIBWXINTL@
all-wxintlno-yes: %D%/libwxintl.a
all-wxintlno-no:

mac:

include %D%/tests/Makefile.am

CLEANFILES += %D%/*.class

WXBUILDDEPENDS_yes = %D%/libwxintl.la
WXBUILDDEPENDS_no =
WXBUILDDEPENDS = $(WXBUILDDEPENDS_@BUILD_INCLUDED_LIBWXINTL@)


noinst_LTLIBRARIES += \
	%D%/libwxintl.la
noinst_LIBRARIES += \
	%D%/libboostintl.a
#noinst_%C%_libwxintl_la_noinst_HEADERS = %D%/libintl.h
#BUILT_SOURCES = $(top_builddir)/intl/libintl.h
%C%_libwxintl_la_SOURCES = \
	%D%/libintl.cpp \
	%D%/libintl.h

%C%_libboostintl_a_SOURCES = \
	%D%/libintl_boost.cpp \
	%D%/libintl.h

all: all-wxintl@USE_INCLUDED_LIBWXINTL@
all-wxintlyes: %D%/libwxintl.la
all-wxintlno: all-wxintlno-@BUILD_INCLUDED_LIBWXINTL@
all-wxintlno-yes: %D%/libwxintl.la
all-wxintlno-no:

mac:

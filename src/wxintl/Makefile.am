SUBDIRS=tests
include $(top_srcdir)/common-rules.mk

noinst_LIBRARIES = libwxintl.a
libwxintl_a_HEADRES = libintl.h
#BUILT_SOURCES = $(top_builddir)/intl/libintl.h
libwxintl_a_SOURCES = libintl.cpp

all: all-@USE_INCLUDED_LIBWXINTL@
all-yes: $(BUILT_SOURCES) all-am #libintl.h charset.alias ref-add.sed ref-del.sed
all-no: all-no-@BUILD_INCLUDED_LIBWXINTL@
all-no-yes: libwxintl.a
all-no-no:

mac:

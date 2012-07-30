SUBDIRS=tests
include $(top_srcdir)/common-rules.mk



noinst_LTLIBRARIES = libintl.la
libintl_la_HEADRES = libintl.h
#BUILT_SOURCES = $(top_builddir)/intl/libintl.h
libintl_la_SOURCES = gettext.c

DEFS = -DLOCALEDIR=\"$(localedir)\" -DLOCALE_ALIAS_PATH=\"$(aliaspath)\" \
-DLIBDIR=\"$(libdir)\" -DIN_LIBINTL \
-DENABLE_RELOCATABLE=1 -DIN_LIBRARY -DINSTALLDIR=\"$(libdir)\" -DNO_XMALLOC \
-Dset_relocation_prefix=libintl_set_relocation_prefix \
-Drelocate=libintl_relocate \
-DDEPENDS_ON_LIBICONV=1 @DEFS@

all: all-@USE_INCLUDED_LIBWXINTL@
all-yes: $(BUILT_SOURCES) all-am #libintl.h charset.alias ref-add.sed ref-del.sed
all-no: all-no-@BUILD_INCLUDED_LIBWXINTL@
all-no-yes: #libgnuintl.$la
all-no-no:

mac:

MAKE_MUTABOR_LIBRARY=$(MAKE) $(AM_MAKEFLAGS) -C "$(top_builddir)" "`basename '$<'`" || exit 1

mutaborlibraries = \
	$(top_builddir)/src/wxintl/libwxintl.la \
	$(top_builddir)/libmutabormaintest.a \
	$(top_builddir)/libmutabormaincppunit.a \
	$(top_builddir)/libmutaborgui.a \
	$(top_builddir)/libmutaborrouting.a \
	$(top_builddir)/libmutaborkernel.a \
	$(top_builddir)/libmutaborscala.a \
	$(top_builddir)/libmutabordebug.a \
	$(top_builddir)/libmutabordebugcppunit.a \
	$(top_builddir)/libmutabordebugtest.a \
	$(top_builddir)/librtmidi.a



.PHONY: $(mutaborlibraries)

$(mutaborlibraries):
	$(MAKE) $(AM_MAKEFLAGS) -C "$(top_builddir)" "`basename '$@' `"

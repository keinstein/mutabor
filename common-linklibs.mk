mutaborlibraries = \
	$(top_builddir)/libmutaborgui.a \
	$(top_builddir)/libmutaborrouting.a \
	$(top_builddir)/libmutaborkernel.a \
	$(top_builddir)/libmutabordebug.a \
	$(top_builddir)/libmutabordebugcppunit.a \
	$(top_builddir)/libmutabordebugtest.a \
	$(top_builddir)/librtmidi.a



.PHONY: mkmutaborlibraries

$(mutaborlibraries):mkmutaborlibraries

mkmutaborlibraries:
	for d in $(mutaborlibraries) ; \
	do \
		lib="`basename "$$d"`" ; \
		echo "$$lib" ; \
		$(MAKE) $(AM_MAKEFLAGS) -C "$(top_builddir)" "$$lib" || exit 1 ; \
	done
mutaborlibraries = $(top_builddir)/libmutaborrouting.a $(top_builddir)/libmutaborkernel.a $(top_builddir)/libmutabordebug.a

$(mutaborlibraries):
	$(MAKE) $(AM_MAKEFLAGS) -C "$(top_builddir)" "`basename '$@'`"
SUBDIRS = de

mac: mac-recursive

mac-recursive:
	for dir in $(SUBDIRS); do \
		(cd "$$dir" && $(MAKE) $(AM_MAKEFLAGS) mac) \
	done
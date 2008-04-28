SUBDIRS = localized
#RECURSIVE_TARGETS += mac-recursive
bin_PROGRAMS = fixhhp htmldecode

htmldecode_SOURCES = htmldecode.cpp

fixhhp_SOURCES = fixhhp.cpp

html: htmldecode fixhhp html-recursive

mac: mac-recursive

mac-recursive:
	for dir in $(SUBDIRS); do \
		(cd "$$dir" && $(MAKE) $(AM_MAKEFLAGS) mac) \
	done
SUBDIRS = localized
#RECURSIVE_TARGETS += mac-recursive
bin_PROGRAMS = fixhhp htmldecode
EXTRA_DIST = \
	addbookm.png \
	back.png \
	delbookm.png \
	dir_up.png \
	down.png \
	emlines.sty \
	fixhhp.cpp \
	forward.png \
	helptoolbar.png \
	htmbook.png \
	htmfoldr.png \
	htmldecode.cpp \
	htmoptns.png \
	htmpage.png \
	htmsidep.png \
	keystroke.4ht \
	Makefile.am \
	Makefile.cmn \
	Makefile.in \
	mkhtml \
	mutabor.cfg \
	preamble.tex \
	print.png \
	toparent.png \
	up.png \
	wxdin.ist \
	xr-hyper.4ht

htmldecode_SOURCES = htmldecode.cpp

fixhhp_SOURCES = fixhhp.cpp

html: html-recursive
html-recursive: htmldecode fixhhp 

mac: mac-recursive

mac-recursive:
	for dir in $(SUBDIRS); do \
		(cd "$$dir" && $(MAKE) $(AM_MAKEFLAGS) mac) \
	done

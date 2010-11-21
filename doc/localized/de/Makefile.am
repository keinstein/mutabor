TEXSOURCES = $(srcdir)/Handbuch.tex \
	$(srcdir)/Referenz.tex \
	$(srcdir)/Bedienung.tex
ZIPFILE = Hilfe.zip
rel_docdir = ../..

DOCLOCALE = de

pkgdata_DATA =$(ZIPFILE)

TEX_DEPS = \
	abhaeng.pic \
	anker1.pic \
	anker2.pic \
	ft.pic \
	netz.pic \
	pt.pic \
	syn1.pic \
	syn10.pic \
	syn11.pic \
	syn12.pic \
	syn13.pic \
	syn14.pic \
	syn15.pic \
	syn16.pic \
	syn17.pic \
	syn18.pic \
	syn19.pic \
	syn2.pic \
	syn20.pic \
	syn21.pic \
	syn22.pic \
	syn23.pic \
	syn24.pic \
	syn25.pic \
	syn26.pic \
	syn27.pic \
	syn28.pic \
	syn3.pic \
	syn4.pic \
	syn5.pic \
	syn6.pic \
	syn7.pic \
	syn8.pic \
	syn9.pic

EXTRA_DIST = $(TEXSOURCES) \
	$(ZIPFILE) \
	$(TEX_DEPS)

include $(top_srcdir)/doc/Makefile.cmn

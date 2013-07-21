TOOLBARICONS = \
	document-new \
	document-open \
	document-save \
	document-save-as \
	document-print \
	ActivateMutabor \
	StopMutabor \
	Panic \
	edit-copy \
	edit-cut \
	edit-paste \
	edit-undo \
	edit-redo \
	RouteLoad \
	RouteSave \
	InDevPlay \
	InDevStop \
	InDevPause \
	help-browser

SVGTOOLBARICONS = $(shell for d in $(TOOLBARICONS); \
	do echo "$(top_srcdir)/Images/Icons/svg/$$d.svg"; done)

PNGTOOLBARICONS = $(shell for d in $(TOOLBARICONS); \
	do echo "$(top_srcdir)/Images/Icons/png/$(XSIZE)x$(YSIZE)/$$d.png"; done)

pkgdatadir = $(datadir)/@PACKAGE@/$(XSIZE)x$(YSIZE)
dist_pkgdata_DATA = $(PNGTOOLBARICONS)

CLEANFILES =

if COND_INKSCAPE
CLEANFILES += Makefile.dep

define DEPFILERULE
<<EOF
$(top_srcdir)/Images/Icons/png/$(XSIZE)x$(YSIZE)/$$d.png: $(top_srcdir)/Images/Icons/svg/$$d.svg
	\$$(INKSCAPE) -e \"\$$@\" -w $(XSIZE) -h $(YSIZE) \"\$$<\" 
EOF
endef
all-local: icons
icons: $(ICONS)

Makefile.dep:
	echo '# -*- Makefile -*-' > "$@"
	for d in $(TOOLBARICONS); \
	do \
		echo -e "@DST@: @SRC@\n\t\$$(INKSCAPE) -e \"\$$@\" -w $(XSIZE) -h $(YSIZE) \"\$$<\"" | \
		sed \
-e 's&@DST@&$$(top_srcdir)/Images/Icons/png/$(XSIZE)x$(YSIZE)/'"$$d.png"'&g' \
-e 's&@SRC@&$$(top_srcdir)/Images/Icons/svg/'"$$d.svg"'&g' \
		  >> "$@" ; \
	done
#< $(top_srcdir)/Images/depfilerule.prototype

-include Makefile.dep

else
icons:
endif
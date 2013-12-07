ICONDIR = $(top_srcdir)/Images/Icons
SVGICONDIR = $(ICONDIR)/svg
PNGICONDIR = $(ICONDIR)/png
PNGSIZEICONDIR = $(PNGICONDIR)/$(XSIZE)x$(YSIZE)

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
	go-up \
	go-down \
	RouteLoad \
	RouteSave \
	InDevPlay \
	InDevStop \
	InDevPause \
	InDevRecord \
	help-browser

STATUSBARICONS = \
	InDevPlay \
	InDevStop \
	InDevPause \
	InDevRecord \
	ToolbarLogicActive

#SVGTOOLBARICONS = $(shell for d in $(TOOLBARICONS); \
#	do echo "$$d" | \
#		sed -e 's,^,$(SVGICONDIR)/, ; s,$,.svg,'; \
#	done | sort | uniq)

UNIQUEICONS = $(shell  for d in $(ICONS); \
	do echo "$$d"; done | sort | uniq )

PNGICONS = $(shell for d in $(UNIQUEICONS); \
	do echo "$(PNGSIZEICONDIR)/$$d.png"; done)



icondatadir = $(pkgdatadir)/$(XSIZE)x$(YSIZE)
# iconbaselist is copied from Automake generated variable am__base_list
iconbaselist = \
  sed '$$!N;$$!N;$$!N;$$!N;$$!N;$$!N;$$!N;s/\n/ /g' | \
  sed '$$!N;$$!N;$$!N;$$!N;s/\n/ /g'
# iconuninstallfromdir comes from am__uninstall_files_from_dir
iconuninstallfromdir = { \
  test -z "$$files" \
    || { test ! -d "$$dir" && test ! -f "$$dir" && test ! -r "$$dir"; } \
    || { echo " ( cd '$$dir' && rm -f" $$files ")"; \
         $(am__cd) "$$dir" && rm -f $$files; }; \
  }

CLEANFILES =

if COND_INKSCAPE
CLEANFILES += Makefile.dep

all-local: icons
install-data-am: install-icons
unintall-data-am: uninstall-icons
icons: $(ICONDATA)

Makefile.dep: Makefile
	echo '# -*- Makefile -*-' > "$@"
	for d in $(UNIQUEICONS); \
	do \
		echo -e "@DST@: @SRC@\n\t\$$(INKSCAPE) -e \"\$$@\" -w $(XSIZE) -h $(YSIZE) \"\$$<\"" | \
		sed \
-e 's&@DST@&$(PNGSIZEICONDIR)/'"$$d.png"'&g' \
-e 's&@SRC@&$(SVGICONDIR)/'"$$d.svg"'&g' \
		  >> "$@" ; \
	done
#< $(top_srcdir)/Images/depfilerule.prototype

install-icons: icons
	@$(NORMAL_INSTALL)
	@list='$(ICONDATA)'; test -n "$(icondatadir)" || list=; \
	if test -n "$$list"; then \
	  echo " $(MKDIR_P) '$(DESTDIR)$(icondatadir)'"; \
	  $(MKDIR_P) "$(DESTDIR)$(icondatadir)" || exit 1; \
	fi; \
	for p in $$list; do \
	  if test -f "$$p"; then d=; else d="$(srcdir)/"; fi; \
	  echo "$$d$$p"; \
	done | $(iconbaselist) | \
	while read files; do \
	  echo " $(INSTALL_DATA) $$files '$(DESTDIR)$(icondatadir)'"; \
	  $(INSTALL_DATA) $$files "$(DESTDIR)$(icondatadir)" || exit $$?; \
	done

uninstall-icons:
	@$(NORMAL_UNINSTALL)
	@list='$(ICONDATA)'; test -n "$(icondatadir)" || list=; \
	files=`for p in $$list; do echo $$p; done | sed -e 's|^.*/||'`; \
	dir='$(DESTDIR)$(icondatadir)'; $(iconuninstallfromdir)


-include Makefile.dep

else
icons:
endif

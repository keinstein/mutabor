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

SVGTOOLBARICONS = $(shell for d in $(TOOLBARICONS); \
	do echo "$(top_srcdir)/Images/Icons/svg/$$d.svg"; done)

PNGTOOLBARICONS = $(shell for d in $(TOOLBARICONS); \
	do echo "$(top_srcdir)/Images/Icons/png/$(XSIZE)x$(YSIZE)/$$d.png"; done)

icondatadir = $(pkgdatadir)/$(XSIZE)x$(YSIZE)
ICONDATA = $(PNGTOOLBARICONS)
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
icons: $(ICONS)

Makefile.dep: Makefile
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

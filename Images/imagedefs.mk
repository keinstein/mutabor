ICONDIR = $(top_srcdir)/Images/Icons
SVGICONDIR = $(ICONDIR)/svg
PNGICONDIR = $(ICONDIR)/png
PNGSIZEICONDIR = $(PNGICONDIR)/$(XSIZE)x$(YSIZE)

TOOLBARICONS = \
	document-new.svg \
	document-open.svg \
	document-save.svg \
	document-save-as.svg \
	document-print.svg \
	ActivateMutabor.svg \
	StopMutabor.svg \
	Panic.svg \
	edit-copy.svg \
	edit-cut.svg \
	edit-paste.svg \
	edit-undo.svg \
	edit-redo.svg \
	go-up.svg \
	go-down.svg \
	RouteLoad.svg \
	RouteSave.svg \
	InDevPlay.svg \
	InDevStop.svg \
	InDevPause.svg \
	InDevRecord.svg \
	help-browser.svg

STATUSBARICONS = \
	InDevPlay.svg \
	InDevStop.svg \
	InDevPause.svg \
	InDevRecord.svg \
	ToolbarLogicActive.svg

#SVGTOOLBARICONS = $(shell for d in $(TOOLBARICONS); \
#	do echo "$$d" | \
#		sed -e 's,^,$(SVGICONDIR)/, ; s,$,.svg,'; \
#	done | sort | uniq)

PNGICONS = $(ICONS:.svg=.png)



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


all-local: icons
install-data-local: install-icons
unintall-data-local: uninstall-icons
#icons: $(ICONDATA)

if COND_INKSCAPE
CLEANFILES += Makefile.dep
Makefile.dep: Makefile
	echo $(PNGICONS)
	echo $(ICONDATA)
	echo '# -*- Makefile -*-' > "$@"
	for d in `echo $(PNGICONS:.png=)|tr ' ' '\n' |sort -u`; \
	do \
		( echo -e "icons: $(PNGSIZEICONDIR)/@DST@" ; \
		echo -e "$(PNGSIZEICONDIR)/@DST@: $@" ; \
		echo -e "$(PNGSIZEICONDIR)/@DST@: $(SVGICONDIR)/@SRC@\n\t\$$(INKSCAPE) -e \"\$$@\" -w $(XSIZE) -h $(YSIZE) \"\$$<\"" ) | \
		sed \
-e 's&@DST@&'"$$d.png"'&g' \
-e 's&@DSTDIR@&$(PNGSIZEICONDIR)&g' \
-e 's&@SRC@&'"$$d.svg"'&g' \
		  >> "$@" ; \
	done
#< $(top_srcdir)/Images/depfilerule.prototype
else
icons:
endif

install-icons: icons
	echo $(NORMAL_INSTALL)
	@list=`echo $(ICONDATA)|tr ' ' '\n'|sort -u`; test -n "$(icondatadir)" || list=; \
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


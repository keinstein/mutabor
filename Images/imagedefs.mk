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


all-local: icons
install-data-local: install-icons
# there is no uninstall-data-local target in Automake
uninstall-local: uninstall-icons
#icons: $(ICONDATA)

EXTRA_DIST = $(PNGSIZEICONDIR)/Makefile.inkscape
if COND_INKSCAPE
$(PNGSIZEICONDIR)/Makefile.inkscape: $(PNGSIZEICONDIR)/Makefile.in
	@echo PNG icons: $(PNGICONS)
	@echo icon data: $(ICONDATA)
	@echo "$(PNGSIZEICONDIR)"
	@echo "making file $@"
	@echo '# -*- Makefile -*-' > "Makefile.tmp"
	@for d in `echo $(PNGICONS:.png=)|tr ' ' '\n' |sort -u`; \
	do \
		( echo -e "icons: @DST@" ; \
		echo -e "#@DST@: Makefile.inkscape" ; \
		echo -e "@DST@: ../../svg/@SRC@\n\t\$$(INKSCAPE) -e \"\$$@\" -w $(XSIZE) -h $(YSIZE) \"\$$<\"" ) | \
		sed \
-e 's&@DST@&'"$$d.png"'&g' \
-e 's&@DSTDIR@&$(PNGSIZEICONDIR)&g' \
-e 's&@SRC@&'"$$d.svg"'&g' \
		  >> "Makefile.tmp" ; \
	done
	cmp "Makefile.tmp" "$@" >/dev/null || cp "Makefile.tmp" "$@"
#< $(top_srcdir)/Images/depfilerule.prototype

icons: $(PNGSIZEICONDIR)/Makefile.inkscape
	$(MAKE) $(AM_MAKEFLAGS) -C  $(PNGSIZEICONDIR) -f Makefile.inkscape icons
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
	cd '$(DESTDIR)$(icondatadir)' && rm -rf $(PNGICONS)




ACLOCAL_AMFLAGS = -I m4 --install
distdir = $(PACKAGE_TARNAME)-$(VERSION)
SUBDIRS = missfunc po wxintl includes . doc intl# libmutabor .
DIST_SUBDIRS = $(SUBDIRS)
AM_CPPFLAGS = -I $(srcdir)/mu32 \
	-I $(srcdir)/mu32/routing \
	-I $(srcdir)/mu32/routing/midi \
	-I $(srcdir)/mu32/routing/gmn \
	-I $(srcdir)/muwx -I $(srcdir)/rtmidi \
	-I $(srcdir)/muwx/Routing \
	-I $(srcdir)/mywx -I $(top_builddir)/intl -I $(top_srcdir)/intl \
	-I $(top_srcdir)/xrc -I $(top_srcdir)/libs/includes \
	@NETINET_INC@
SUFFIXES = .$(PCHEXT_CXX) .rc .res

BUILT_SOURCES = $(top_srcdir)/xrc/wxresource.h
if COND_PRECOMP_CXX
BUILT_SOURCES += mutabor-cxxprecompiled.$(PCHEXT_CXX)
endif

RCCOMPILE = $(RC) $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(CPPFLAGS) $(RCFLAGS)
CVS = cvs
INDENT = astyle --style=linux --indent=tab=8
EXTRA_DIST = config.rpath \
	m4/ChangeLog  \
	debian/changelog \
	debian/compat \
	debian/control \
	debian/copyright \
	debian/dirs \
	debian/docs \
	debian/libmutabor-dev.install \
	debian/libmutabor.install \
	debian/mutabor-doc.docs \
	debian/mutabor-doc.install \
	debian/mutabor.install \
	debian/README.Debian \
	debian/rules \
	debian/source \
	debian/menu \
	libasprintf \
	muwx/Icon \
	muwx/bitmaps \
	$(top_srcdir)/mu32/mut.y \
	xrc/wxresource.cpp \
	xrc/wxresource.h \
	xrc/reslocale.cpp

dist_pkgdata_DATA = xrc/Mutabor.xrc Images/about.png \
	Icons/png/NewInputDevice.png \
	Icons/png/InputDevice.png \
	Icons/png/NewOutputDevice.png \
	Icons/png/OutputDevice.png \
	Icons/png/MidiFile.png \
	Icons/png/GuidoFile.png \
	Icons/png/ActiveChannel.png \
	Icons/png/PassiveChannel.png \
	Icons/png/TuningBox.png
#RECURSIVE_TARGETS += mac-recursive
BUILT_SOURCES += $(top_srcdir)/mu32/mut.cpp $(top_srcdir)/mu32/mut.h \
	$(top_srcdir)/xrc/wxresource.h
bin_PROGRAMS = mutabor
mutabor_INDENTS = \
		mu32/Defs.h \
		mu32/routing/gmn/DevGIS.cpp \
		mu32/routing/gmn/DevGIS.h \
		mu32/routing/gmn/GIS_Head.cpp \
		mu32/routing/gmn/GIS_Head.h \
		mu32/routing/gmn/GIS.cpp \
		mu32/routing/gmn/GIS.h \
		mu32/routing/gmn/GSP_Err.cpp \
		mu32/routing/gmn/GSP_File.cpp \
		mu32/routing/gmn/GSP_File.h \
		mu32/routing/gmn/GSP.cpp \
		mu32/routing/gmn/GSP.h \
		mu32/routing/midi/DevMidF.cpp \
		mu32/routing/midi/DevMidF.h \
		mu32/routing/midi/DevMidi.cpp \
		mu32/routing/midi/DevMidi.h \
		mu32/routing/Device.cpp \
		mu32/routing/Device.h \
		mu32/routing/Route.cpp \
		mu32/routing/Route.h \
		mu32/routing/RouteCompat.cpp \
		mu32/routing/RouteCompat.h \
		mu32/Errors.cpp \
		mu32/Errors.h \
		mu32/Execute.cpp \
		mu32/Execute.h \
		mu32/Frac.cpp \
		mu32/Frac.h \
		mu32/Global.h \
		mu32/GrafKern.cpp \
		mu32/GrafKern.h \
		mu32/Hilfs.cpp \
		mu32/Hilfs.h \
		mu32/Interpre.h \
		mu32/Interval.cpp \
		mu32/Interval.h \
		mu32/MidiKern.h \
		mu32/Parser.cpp \
		mu32/Runtime.cpp \
		mu32/Runtime.h \
		mu32/TabGen.cpp \
		mu32/treestorage.h \
		muwx/Routing/BoxChannelShape.cpp \
		muwx/Routing/BoxChannelShape.h \
		muwx/Routing/BoxDlg.cpp \
		muwx/Routing/BoxDlg.h \
		muwx/Routing/BoxIconShape.cpp \
		muwx/Routing/BoxIconShape.h \
		muwx/Routing/BoxShape.cpp \
		muwx/Routing/BoxShape.h \
		muwx/Routing/DebugRoute.cpp \
		muwx/Routing/DebugRoute.h \
		muwx/Routing/DeviceShape.cpp \
		muwx/Routing/DeviceShape.h \
		muwx/Routing/InputDevDlg.cpp \
		muwx/Routing/InputDevDlg.h \
		muwx/Routing/InputDeviceShape.cpp \
		muwx/Routing/InputDeviceShape.h \
		muwx/Routing/InputGuidoFileDeviceShape.cpp \
		muwx/Routing/InputGuidoFileDeviceShape.h \
		muwx/Routing/InputMidiDeviceShape.cpp \
		muwx/Routing/InputMidiDeviceShape.h \
		muwx/Routing/InputMidiFileDeviceShape.cpp \
		muwx/Routing/InputMidiFileDeviceShape.h \
		muwx/Routing/NewBoxShape.cpp \
		muwx/Routing/NewBoxShape.h \
		muwx/Routing/NewInputDeviceShape.cpp \
		muwx/Routing/NewInputDeviceShape.h \
		muwx/Routing/NewOutputDeviceShape.cpp \
		muwx/Routing/NewOutputDeviceShape.h \
		muwx/Routing/OutputDevDlg.cpp \
		muwx/Routing/OutputDevDlg.h \
		muwx/Routing/OutputDeviceShape.cpp \
		muwx/Routing/OutputDeviceShape.h \
		muwx/Routing/OutputGuidoFileDeviceShape.cpp \
		muwx/Routing/OutputGuidoFileDeviceShape.h \
		muwx/Routing/OutputMidiDeviceShape.cpp \
		muwx/Routing/OutputMidiDeviceShape.h \
		muwx/Routing/OutputMidiFileDeviceShape.cpp \
		muwx/Routing/OutputMidiFileDeviceShape.h \
		muwx/Routing/RouteIcons.cpp \
		muwx/Routing/RouteIcons.h \
		muwx/Action.cpp \
		muwx/Action.h \
		muwx/CompDlg.cpp \
		muwx/CompDlg.h \
		muwx/configtree.cpp \
		muwx/configtree.h \
		muwx/IconShape.cpp \
		muwx/IconShape.h \
		muwx/Mutabor.rh \
		muwx/MutApp.cpp \
		muwx/MutApp.h \
		muwx/MutChild.cpp \
		muwx/MutChild.h \
		muwx/MutConfDlg.h \
		muwx/MutEditFile.cpp \
		muwx/MutEditFile.h \
		muwx/MutFrame.cpp \
		muwx/MutFrame.h \
		muwx/MutIcon.cpp \
		muwx/MutIcon.h \
		muwx/MutLogicWnd.cpp \
		muwx/MutLogicWnd.h \
		muwx/MutRouteWnd.cpp  \
		muwx/MutRouteWnd.h \
		muwx/MutTextBox.cpp \
		muwx/MutTextBox.h \
		muwx/Panel.cpp \
		muwx/Panel.h \
		muwx/resourceload.h \
		mywx/mhArray.h \
		mywx/mhDefs.h \
		mywx/muconvauto.cpp \
		mywx/muconvauto.h \
		mywx/mutDebug.h \
		mywx/mutDebug.cpp \
		mywx/mxDefs.cpp \
		mywx/valNum.cpp \
		mywx/valNum.h \
		mywx/valRadio.cpp \
		mywx/valRadio.h \
		rtmidi/RtError.h \
		rtmidi/RtMidi.cpp \
		rtmidi/RtMidi.h \
		$(top_srcdir)/xrc/wxresource.h


#		muwx/InputFilterDlg.cpp \
#		muwx/InputFilterDlg.h \
#		muwx/OutputFilterDlg.cpp \
#		muwx/OutputFilterDlg.h \
#

CLEANFILES = \
	mutabor-cxxprecompiled.$(PCHEXT_CXX) \
	mutabor-cxxprecompiled.h \
	mutabor-cxxprecompiled.stamp \
	Mutabor.xrc

if COND_WINRC
mutabor_INDENTS += muwx/Mutabor.rc
endif

INDENTS = $(mutabor_INDENTS)

mutabor_SOURCES = $(mutabor_INDENTS) \
		  $(top_srcdir)/mu32/mut.cpp \
		  $(top_srcdir)/mu32/mut.h \
		  mywx/mutDebugFlags.h 

if COND_PRECOMP_CXX
mutabor_SOURCES += mutabor-cxxprecompiled.$(PCHEXT_CXX)
endif


#		mywx/myContextHelpButton.h \
#		mywx/myContextHelpButton.cpp \
#
mutabordir=$(datadir)/mutabor

AM_LDFLAGS = $(ALSA_LIBS) $(WX_LIBS) -lexpat
AM_CFLAGS = $(ALSA_CFLAGS)  $(WX_CFLAGS)
AM_CXXFLAGS = $(AM_CFLAGS)
AM_CXX = $(MAKE) $(AM_MAKEFLAGS) mutabor-precompile && $(CXX)
AM_CPPFLAGS += $(WX_CPPFLAGS) -DPREFIX='"$(prefix)"'

mutabor_CXXLD=$(CXX)

if COND_PRECOMP_C
mutabor_CFLAGS = -include mutabor-precompiled.h -fpch-deps
endif

if COND_PRECOMP_CXX
mutabor_CXXFLAGS = -include mutabor-cxxprecompiled.h -fpch-deps
endif

mutabor_SHORTNAME = mutabor

if COND_WINRC
mutabor_DEPENDENCIES = $(mutabor_SHORTNAME)-Mutabor.$(OBJEXT)
endif

mutabor_LDADD = $(LDADD)
if COND_WINRC
mutabor_LDADD += $(mutabor_SHORTNAME)-Mutabor.$(OBJEXT)
endif
mutabor_DATA = Images/about.png Mutabor.xrc

if AMDEP
@am__include@ @am__quote@./$(DEPDIR)/mutabor-cxxprecompiled.Po@am__quote@
endif

.PHONY: cvs_dist cvs_distcheck mutabor-cxxprecompiled mac mac-recursive

if COND_WINRC
.rc.$(OBJEXT):
	$(RCCOMPILE) $< $@
endif

.h.$(PCHEXT_CXX):
if am__fastdepCXX
	if $(CXXCOMPILE) $(mutabor_CPPFLAGS) $(mutabor_CallFLAGS) -MT $@ \
		-MD -MP -MF "$(DEPDIR)/$*.Tpo" -o $@ \
		-c `test -f '$<' || echo '$(srcdir)/'`$<; \
	then mv -f "$(DEPDIR)/$*.Tpo" "$(DEPDIR)/$*.Po"; \
	else rm -f "$(DEPDIR)/$*.Tpo"; exit 1; fi 
else
if AMDEP
	source='$<' object='$@' libtool=no @AMDEPBACKSLASH@
	DEPDIR=$(DEPDIR) $(CXXDEPMODE) $(depcomp) @AMDEPBACKSLASH@
endif
	$(CXXCOMPILE) $(mutabor_CPPFLAGS) $(mutabor_CallFLAGS) \
		 -c  `test -f '$<' || echo '$(srcdir)/'`$<
endif

cvs_dist: Makefile
	touch cvsdist
	chmod -R u+w  cvsdist
	rm -rf cvsdist
	mkdir cvsdist
	cd cvsdist && \
	$(CVS) -d `cat ../CVS/Root` export -r HEAD `cat ../CVS/Repository` && \
	cd `cat ../CVS/Repository` && \
	./configure && \
	$(MAKE) dist

cvs_distcheck: Makefile
	touch cvsdist
	chmod -R u+w  cvsdist
	rm -rf cvsdist
	tag=`sed -e s/^T// <$(top_srcdir)/CVS/Tag` ; \
	repo=`cat $(top_srcdir)/CVS/Repository` ; \
	mkdir -p cvsdist cvsdistm ; \
	CVSROOT=`cat $(top_srcdir)/CVS/Root` \
	$(CVS) export -r "$$tag" -d "cvsdistm" "$$repo" && \
	mv cvsdistm "cvsdist/$$repo" && \
	cd "cvsdist/$$repo" && \
	autoreconf -i && \
	./configure && \
	$(MAKE)  distcheck


mutabor-cxxprecompiled.stamp:mutabor-cxxprecompiled.$(PCHEXT_CXX)
	if test \! -f mutabor-cxxprecompiled.stamp ; then touch mutabor-cxxprecompiled.stamp ; fi


if COND_PRECOMP_CXX
$(mutabor_OBJECTS):mutabor-cxxprecompiled.stamp

mutabor-cxxprecompiled.h: Makefile
	@echo 'creating $<'
	@echo '#define PRECOMPILE 1' >$@
	@echo '#include "Defs.h"' >>$@
	@for datei in $(mutabor_INDENTS) ; \
	do  \
		echo $$datei | $(EGREP) '\.h$$' && \
		echo '#include "'"$$datei"'"' >>$@ ; \
	done ; true
	@echo '#undef PRECOMPILE' >>$@

endif

if COND_WINRC
$(mutabor_SHORTNAME)-Mutabor.$(OBJEXT):$(srcdir)/muwx/Mutabor.rc
	$(RCCOMPILE) $(srcdir)/muwx/Mutabor.rc $@
endif

Mutabor.xrc: $(top_srcdir)/xrc/Mutabor.xrc
	cp $< $@
#	sed -e 's/_amp;/\&amp;/g' <$(top_srcdir)/xrc/Mutabor.xrc >Mutabor.xrc

Mutabor.app:all Mutabor.xrc mutabor update-gmo
	$(MKDIR_P) Mutabor.app/Contents/MacOS
	$(MKDIR_P) Mutabor.app/Contents/Resources
	cp mutabor Mutabor.app/Contents/MacOS
	cp osdep/macosx/Info.plist Mutabor.app/Contents
	cp $(top_srcdir)/muwx/Icon/Mutabor.icns Mutabor.app/Contents/Resources/Mutabor.icns
	echo -n APPL???? >Mutabor.app/Contents/PkgInfo
	for datei in $(top_srcdir)/po/*.gmo ; \
	do \
		shortname=`basename "$$datei" | sed -e 's/\.gmo$$//'` ; \
		mkdir -p Mutabor.app/Contents/Resources/$$shortname.lproj ; \
		cp "$$datei" Mutabor.app/Contents/Resources/$$shortname.lproj/mutabor.mo ; \
	done
	for d in $(dist_pkgdata_DATA) ; do \
		cp $(top_srcdir)/$$d Mutabor.app/Contents/Resources ; \
	done
	ls "$(WX_LOCALE_DIRS)"/*/LC_MESSAGES/wxstd.mo | \
	while read file ; do \
		lang=`echo $$file | sed -e 's,.*/\([^/]*\)/LC_MESSAGES/wxstd.mo,\1,g'` ; echo $$lang ;\
		mkdir -p Mutabor.app/Contents/Resources/$$lang.lproj ; \
		cp $$file Mutabor.app/Contents/Resources/$$lang.lproj ; \
	done

$(top_srcdir)/xrc/wxresource.h : $(top_srcdir)/xrc/Mutabor.xrc
	(cd $(top_srcdir)/xrc; \
	wxrc -c -e -o wxresource.cpp Mutabor.xrc)

reslocale.cpp: $(top_srcdir)/xrc/reslocale.cpp $(top_srcdir)/xrc/Mutabor.xrc
$(top_srcdir)/xrc/reslocale.cpp : $(top_srcdir)/xrc/Mutabor.xrc
	(cd $(top_srcdir)/xrc; \
	wxrc -g -o reslocale.cpp Mutabor.xrc)


SUFFIXES += .h

.l.h:
	$(LEXCOMPILE) $<
	cfilename=`echo $@|sed 's/\.h$$/.c/;t'` && \
		sed '/^#/ s|$(LEX_OUTPUT_ROOT)\.c|$$cfilename|' \
		$(LEX_OUTPUT_ROOT).c >$$cfilename
	mv `sed 's,%option[ 	]\+header-file="\(.*\)".*,\1,;t;d' $<` $@
	mv `sed 's,%option[ 	]\+tables-file="\(.*\)".*,\1,;t;d' $<` $(srcdir)
.l.c:
	$(LEXCOMPILE) $<
	sed '/^#/ s|$(LEX_OUTPUT_ROOT)\.c|$@|' $(LEX_OUTPUT_ROOT).c >$@
	mv `sed 's,%option[ 	]\+header-file="\(.*\)".*,\1,;t;d' $<` $(srcdir)
	mv `sed 's,%option[ 	]\+tables-file="\(.*\)".*,\1,;t;d' $<` $(srcdir)

YACCCOMPILE = $(YACC) $(YFLAGS) $(AM_YFLAGS)

.y.cpp: 
	rm -f $*.h
	$(MAKE) $@

.y.h:
	$(YACCCOMPILE) `test -f '$<' || echo '$(srcdir)/'`$<
	if test -f y.tab.h; then \
	  to=`echo "$*_H" | sed \
		-e 'y/abcdefghijklmnopqrstuvwxyz/ABCDEFGHIJKLMNOPQRSTUVWXYZ/' \
		-e 's/[^ABCDEFGHIJKLMNOPQRSTUVWXYZ]/_/g'`; \
	  sed "/^#/ s/Y_TAB_H/$$to/g" y.tab.h >$*.ht; \
	  rm -f y.tab.h; \
	  if cmp -s $*.ht $*.h; then \
	    rm -f $*.ht ;\
	  else \
	    mv $*.ht $*.h; \
	  fi; \
	fi
	if test -f y.output; then \
	  mv y.output $*.output; \
	fi
	sed '/^#/ s|y\.tab\.c|$@|' y.tab.c >$@t && mv $@t $@
	mv y.tab.c $*.cpp

mutlex.h: mutlex.l
$(top_srcdir)/mu32/mut.h: $(top_srcdir)/mu32/mut.y
$(top_srcdir)/mu32/mut.cpp: $(top_srcdir)/mu32/mut.h

mac: copymac
	(cd doc && $(MAKE) $(AM_MAKEFLAGS) mac)


copymac: Mutabor.app

dylibbundler: mac
	dylibbundler -b -x Mutabor.app/Contents/MacOS/mutabor \
		-cd -od -d Mutabor.app/Contents/libs 
pydmg: dylibbundler
	wget --no-check-certificate https://anon:@scm.wilcoxd.com:8081/svn/OpenSource/Scripts/sane_build_disk_image/sane_build_disk_image.py

dmg: dylibbundler
	mkdir -p dmg/Mutabor
	cp -r Mutabor.app dmg/Mutabor
	ln -s /Applications dmg/Mutabor
	hdiutil create -srcfolder dmg/Mutabor -volname "$(PACKAGE_STRING)" "$(PACKAGE_NAME)-$(PACKAGE_VERSION)"
	rm -r dmg/Mutabor


installwin: mutabor.exe
	mkdir -p Mutabor
	cp mutabor.exe Mutabor
	for datei in $(top_srcdir)/po/*.gmo ; \
	do \
		shortname=`basename "$$datei" | sed -e 's/\.gmo$$//'` ; \
		mkdir -p Mutabor/$$shortname/LC_MESSAGES ; \
		cp "$$datei" Mutabor/$$shortname/LC_MESSAGES/mutabor.mo ; \
	done
	for d in $(dist_pkgdata_DATA) ; do \
		cp $(top_srcdir)/$$d Mutabor ; \
	done
	test -z "$(WX_LOCALE_DIRS)" || ( ls "$(WX_LOCALE_DIRS)"/* | \
	while read file ; do \
		lang=`echo $$file | sed -e 's,.*/\([^/]*\)/LC_MESSAGES/wxstd.mo,\1,g'` ; echo $$lang ;\
		mkdir -p Mutabor/$$lang/LC_MESSAGES ; \
		cp $$file Mutabor/$$lang/LC_MESSAGES ; \
	done )
	WXLIBDIR=`$(WX_CONFIG_PATH) --exec-prefix`
	for d in `$(WX_CONFIG_PATH) --exec-prefix`/lib/wx*{msw,base}*.dll ; \
	do \
		cp $$d Mutabor ; \
	done

count:
	cd $(top_srcdir) ; sloccount $(SUBDIRS)

cvstagdate:
	cd $(top_srcdir); cvs tag `date '+date_%Y-%m-%d_%H%M'`


# mostly copied from distdir target of Makefile.in
indent:
	@srcdirstrip=`echo "$(srcdir)" | sed 's/[].[^$$\\*]/\\\\&/g'`; \
	topsrcdirstrip=`echo "$(top_srcdir)" | sed 's/[].[^$$\\*]/\\\\&/g'`; \
	list='$(INDENTS)'; \
	  dist_sources=`for file in $$list; do echo $$file; done | \
	  sed -e "s|^$$srcdirstrip/||;t" \
	      -e "s|^$$topsrcdirstrip/|$(top_builddir)/|;t"`; \
	for file in $$dist_sources ; do \
	  if test -f $$file || test -d $$file; then d=.; else d=$(srcdir); fi; \
	  if test -d $$d/$$file; then \
	    dir=`echo "/$$file" | sed -e 's,/[^/]*$$,,'`; \
	    if test -d $(srcdir)/$$file && test $$d != $(srcdir); then \
	      $(INDENT) $(srcdir)/$$file || exit 1; \
	    fi; \
	    $(INDENT) $$d/$$file || exit 1; \
	  else \
	    test -f $(distdir)/$$file \
	    || $(INDENT) $$d/$$file \
	    || exit 1; \
	  fi; \
	done

POTFILESchk:
	for d in $(mutabor_SOURCES); \
	do \
		echo $$d ;\
	done | grep -e '\(.cpp\|.h\)' >POTFILES.tmp
	diff -u $(top_srcdir)/po/POTFILES.in POTFILES.tmp 

update-po: reslocale.cpp
	make -C po update-po

update-gmo: update-po
	make -C po update-gmo

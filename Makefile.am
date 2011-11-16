ACLOCAL_AMFLAGS = -I m4 --install
MAKEFILE_DEPS = remove-podeps.stamp
DLLCOPYPATTERN = \(wx\|mingw\)
DLLSEARCHPATH = `$(WX_CONFIG_PATH) --exec-prefix`/lib /usr/lib /usr/share/doc/mingw32-runtime /mingw/lib /mingw/bin /bin /usr/bin
SUBDIRS = missfunc po wxintl includes . doc #intl# libmutabor .
#DIST_SUBDIRS = $(SUBDIRS)
AM_CPPFLAGS = -I$(srcdir)/mu32 \
	-I$(srcdir)/mu32/routing \
	-I$(srcdir)/mu32/routing/midi \
	-I$(srcdir)/mu32/routing/gmn \
	-I$(srcdir)/muwx -I$(srcdir)/rtmidi \
	-I$(srcdir)/muwx/Routing \
	-I$(srcdir)/mywx \
	-I$(top_srcdir)/xrc -I$(top_srcdir)/libs/includes \
	@NETINET_INC@ #$(top_builddir)/intl -I $(top_srcdir)/intl 
SUFFIXES = .$(PCHEXT_CXX) .rc .res

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
	xrc/reslocale.cpp \
	osdep/macosx/Application_Code.txt \
	osdep/macosx/background.png \
	osdep/macosx/background.svg \
	osdep/macosx/DS_Store \
	osdep/macosx/Info.plist.in \
	osdep/win/config.h \
	osdep/win/config.h.in \
	osdep/win/Mutabor.rc \
	osdep/win/Mutabor.sln \
	osdep/win/muwx.vcxproj \
	muwx/Mutabor.rc

# Please use Tango names for new files
# http://tango.freedesktop.org/Tango_Desktop_Project
dist_pkgdata_DATA = xrc/Mutabor.xrc Images/about.png \
	Icons/png/NewInputDevice.png \
	Icons/png/InputDevice.png \
	Icons/png/NewOutputDevice.png \
	Icons/png/OutputDevice.png \
	Icons/png/MidiFile.png \
	Icons/png/GuidoFile.png \
	Icons/png/ActiveChannel.png \
	Icons/png/PassiveChannel.png \
	Icons/png/TuningBox.png \
	Icons/png/document-new.png \
	Icons/png/document-open.png \
	Icons/png/document-save.png \
	Icons/png/document-save-as.png \
	Icons/png/document-print.png \
	Icons/png/ActivateMutabor.png \
	Icons/png/StopMutabor.png \
	Icons/png/Panic.png \
	Icons/png/edit-copy.png \
	Icons/png/edit-cut.png \
	Icons/png/edit-paste.png \
	Icons/png/edit-undo.png \
	Icons/png/edit-redo.png \
	Icons/png/RouteLoad.png \
	Icons/png/RouteSave.png \
	Icons/png/InDevPlay.png \
	Icons/png/InDevStop.png \
	Icons/png/InDevPause.png \
	Icons/png/help-browser.png
#RECURSIVE_TARGETS += mac-recursive
BUILT_SOURCES = \
	$(top_srcdir)/mu32/mut.cpp \
	$(top_srcdir)/mu32/mut.h \
	$(top_srcdir)/xrc/wxresource.h

if COND_PRECOMP_CXX
BUILT_SOURCES += mutabor-cxxprecompiled.$(PCHEXT_CXX)
nodist_mutabor_SOURCES = mutabor-cxxprecompiled.$(PCHEXT_CXX)
endif

bin_PROGRAMS = mutabor

INLINEHEADERS = \
		mu32/routing/Device-inlines.h \
		mu32/routing/Route-inlines.h \
		muwx/GUIBoxData-inlines.h \
		muwx/Routing/GUIRoute-inlines.h 


INDENTHEADERS = \
		mu32/Defs.h \
		mu32/routing/gmn/DevGIS.h \
		mu32/routing/gmn/GIS_Head.h \
		mu32/routing/gmn/GIS.h \
		mu32/routing/gmn/GSP_File.h \
		mu32/routing/gmn/GSP.h \
		mu32/routing/midi/DevMidF.h \
		mu32/routing/midi/DevMidi.h \
		mu32/routing/Device.h \
		mu32/routing/Route.h \
		mu32/routing/RouteCompat.h \
		mu32/box.h \
		mu32/Errors.h \
		mu32/Execute.h \
		mu32/Frac.h \
		mu32/Global.h \
		mu32/GrafKern.h \
		mu32/Hilfs.h \
		mu32/Interpre.h \
		mu32/Interval.h \
		mu32/MidiKern.h \
		mu32/Runtime.h \
		mu32/treestorage.h \
		muwx/Routing/BoxChannelShape.h \
		muwx/Routing/BoxDlg.h \
		muwx/Routing/BoxIconShape.h \
		muwx/Routing/BoxShape.h \
		muwx/Routing/DebugRoute.h \
		muwx/Routing/DeviceShape.h \
		muwx/Routing/GUIRoute.h \
		muwx/Routing/InputDevDlg.h \
		muwx/Routing/InputDeviceShape.h \
		muwx/Routing/InputGuidoFileDeviceShape.h \
		muwx/Routing/InputMidiDeviceShape.h \
		muwx/Routing/InputMidiFileDeviceShape.h \
		muwx/Routing/NewBoxShape.h \
		muwx/Routing/NewInputDeviceShape.h \
		muwx/Routing/NewOutputDeviceShape.h \
		muwx/Routing/OutputDevDlg.h \
		muwx/Routing/OutputDeviceShape.h \
		muwx/Routing/OutputGuidoFileDeviceShape.h \
		muwx/Routing/OutputMidiDeviceShape.h \
		muwx/Routing/OutputMidiFileDeviceShape.h \
		muwx/Routing/RouteIcons.h \
		muwx/Routing/RouteLists.h \
		muwx/Action.h \
		muwx/GUIBoxData.h \
		muwx/MutBitmaps.h \
		muwx/Mutabor.rh \
		muwx/CompDlg.h \
		muwx/configtree.h \
		muwx/IconShape.h \
		muwx/MutApp.h \
		muwx/MutChild.h \
		muwx/MutConfDlg.h \
		muwx/MutDocManager.h \
		muwx/MutDocument.h \
		muwx/MutEditFile.h \
		muwx/MutFrame.h \
		muwx/MutIcon.h \
		muwx/MutLogicWnd.h \
		muwx/MutRouteWnd.h \
		muwx/MutTextBox.h \
		muwx/MutView.h \
		muwx/Panel.h \
		muwx/resourceload.h \
		muwx/stclanguage.h \
		mywx/mhArray.h \
		mywx/mhDefs.h \
		mywx/muconvauto.h \
		mywx/mutDebug.h \
		mywx/valNum.h \
		mywx/valRadio.h \
		rtmidi/RtError.h \
		rtmidi/RtMidi.h

mutabor_INDENTS = \
		mu32/routing/gmn/DevGIS.cpp \
		mu32/routing/gmn/GIS_Head.cpp \
		mu32/routing/gmn/GIS.cpp \
		mu32/routing/gmn/GSP_Err.cpp \
		mu32/routing/gmn/GSP_File.cpp \
		mu32/routing/gmn/GSP.cpp \
		mu32/routing/midi/DevMidF.cpp \
		mu32/routing/midi/DevMidi.cpp \
		mu32/routing/Device.cpp \
		mu32/routing/Route.cpp \
		mu32/routing/RouteCompat.cpp \
		mu32/box.cpp \
		mu32/Errors.cpp \
		mu32/Execute.cpp \
		mu32/Frac.cpp \
		mu32/GrafKern.cpp \
		mu32/Hilfs.cpp \
		mu32/Interval.cpp \
		mu32/Parser.cpp \
		mu32/Runtime.cpp \
		mu32/TabGen.cpp \
		muwx/Routing/BoxChannelShape.cpp \
		muwx/Routing/BoxDlg.cpp \
		muwx/Routing/BoxIconShape.cpp \
		muwx/Routing/BoxShape.cpp \
		muwx/Routing/DebugRoute.cpp \
		muwx/Routing/DeviceShape.cpp \
		muwx/Routing/GUIRoute.cpp \
		muwx/Routing/InputDevDlg.cpp \
		muwx/Routing/InputDeviceShape.cpp \
		muwx/Routing/InputGuidoFileDeviceShape.cpp \
		muwx/Routing/InputMidiDeviceShape.cpp \
		muwx/Routing/InputMidiFileDeviceShape.cpp \
		muwx/Routing/NewBoxShape.cpp \
		muwx/Routing/NewInputDeviceShape.cpp \
		muwx/Routing/NewOutputDeviceShape.cpp \
		muwx/Routing/OutputDevDlg.cpp \
		muwx/Routing/OutputDeviceShape.cpp \
		muwx/Routing/OutputGuidoFileDeviceShape.cpp \
		muwx/Routing/OutputMidiDeviceShape.cpp \
		muwx/Routing/OutputMidiFileDeviceShape.cpp \
		muwx/Routing/RouteIcons.cpp \
		muwx/Action.cpp \
		muwx/GUIBoxData.cpp \
		muwx/MutBitmaps.cpp \
		muwx/CompDlg.cpp \
		muwx/configtree.cpp \
		muwx/IconShape.cpp \
		muwx/MutApp.cpp \
		muwx/MutChild.cpp \
		muwx/MutDocManager.cpp \
		muwx/MutDocument.cpp \
		muwx/MutEditFile.cpp \
		muwx/MutFrame.cpp \
		muwx/MutIcon.cpp \
		muwx/MutLogicWnd.cpp \
		muwx/MutRouteWnd.cpp  \
		muwx/MutTextBox.cpp \
		muwx/MutView.cpp \
		muwx/Panel.cpp \
		muwx/stclanguage.cpp \
		mywx/muconvauto.cpp \
		mywx/mutDebug.cpp \
		mywx/mxDefs.cpp \
		mywx/valNum.cpp \
		mywx/valRadio.cpp \
		rtmidi/RtMidi.cpp

#		muwx/InputFilterDlg.cpp \
#		muwx/InputFilterDlg.h \
#		muwx/OutputFilterDlg.cpp \
#		muwx/OutputFilterDlg.h \
#

CLEANFILES = \
	mutabor-cxxprecompiled.$(PCHEXT_CXX) \
	mutabor-cxxprecompiled.h \
	mutabor-cxxprecompiled.stamp \
	Mutabor.xrc \
	$(mutabor_SHORTNAME)-Mutabor-winrc.$(OBJEXT)

INDENTS = $(mutabor_INDENTS) $(INDENTHEADERS) $(INLINEHEADERS)

noinst_HEADERS =  mu32/mut.h \
		  mywx/mutDebugFlags.h \
		  $(INDENTHEADERS) \
		  $(INLINEHEADERS)

mutabor_COMPILESOURCES = $(mutabor_INDENTS) \
			  mu32/mut.cpp

mutabor_SOURCES = $(mutabor_COMPILESOURCES)
if COND_WINRC
mutabor_COMPILESOURCES += muwx/Mutabor.rc
endif

#		mywx/myContextHelpButton.h \
#		mywx/myContextHelpButton.cpp \
#
mutabordir=$(datadir)/mutabor

AM_LDFLAGS = $(ALSA_LIBS) $(WX_LIBS)
AM_CFLAGS = $(ALSA_CFLAGS)  $(WX_CFLAGS)
AM_CXXFLAGS = $(AM_CFLAGS)
AM_CXX = $(MAKE) $(AM_MAKEFLAGS) mutabor-precompile && $(CXX)
AM_CPPFLAGS += $(WX_CPPFLAGS) -DPREFIX='"$(prefix)"'

mutabor_CXXLD=$(CXX)

if COND_PRECOMP_C
mutabor_CFLAGS = -include mutabor-precompiled.h # -fpch-deps
endif

if COND_PRECOMP_CXX
mutabor_CXXFLAGS = -include mutabor-cxxprecompiled.h # -fpch-deps
endif

mutabor_SHORTNAME = mutabor

mutabor_LDADD = $(LDADD)
if COND_WINRC
BUILT_SOURCES +=  $(mutabor_SHORTNAME)-Mutabor-winrc.$(OBJEXT)
mutabor_LDADD += $(mutabor_SHORTNAME)-Mutabor-winrc.$(OBJEXT)
mutabor.$(EXEEXT):$(mutabor_SHORTNAME)-Mutabor-winrc.$(OBJEXT)
$(mutabor_SHORTNAME)-Mutabor-winrc.$(OBJEXT):$(srcdir)/muwx/Mutabor.rc
	$(RCCOMPILE) $< $@
else
$(mutabor_SHORTNAME)-Mutabor-winrc.$(OBJEXT):$(srcdir)/muwx/Mutabor.rc
endif

if COND_PRECOMP_CXX
if AMDEP
@am__include@ @am__quote@./$(DEPDIR)/mutabor-cxxprecompiled.Po@am__quote@
endif
endif

.PHONY: cvs_dist cvs_distcheck \
	mutabor-cxxprecompiled mutabor-cxxprecompiled.h.shuffle \
	mac mac-recursive \
	fixdependencies

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


if COND_PRECOMP_CXX

#./$(DEPDIR)/mutabor-cxxprecompiled.Po:fixdependencies.stamp

podeps.stamp:
	touch $@


Makefile:remove-podeps.stamp $(srcdir)/Makefile.in $(top_builddir)/config.status
        @case '$?' in \
          *config.status*) \
            echo ' $(SHELL) ./config.status'; \
            $(SHELL) ./config.status;; \
          *) \
            echo ' cd $(top_builddir) && $(SHELL) ./config.status $@ $(am__depfiles_maybe)'; \
            cd $(top_builddir) && $(SHELL) ./config.status $@ $(am__depfiles_maybe);; \
        esac;
remove-podeps.stamp:$(srcdir)/Makefile.in $(top_builddir)/config.status
	rm -f podeps.stamp
	touch $@

./$(DEPDIR)/podeps.dep:$(mutabor_COMPILESOURCES) podeps.stamp
	$(MKDIR_P) `dirname $@`
	echo >$@
	for obj in $(mutabor_OBJECTS) ; do \
		base=`basename "$$obj"` ; \
		dir=`dirname "$$obj"` ; \
		pofilebase=`echo "$$base" | sed 's/\.$(OBJEXT)\$$/.Po/g'` ; \
		pofile="$$dir/\$$(DEPDIR)/$$pofilebase" ; \
		echo >>$@ ; \
		echo >>$@ ; \
		echo "$$pofile: $$pofile.stamp" >>$@ ; \
		echo "$$pofile.stamp:" >>$@ ; \
		echo "	-$(SED) -i 's/ mutabor-cxxprecompiled\.[a-zA-Z0-9]* / /g' $$pofile" >>$@ ; \
		echo '	touch $$@' >>$@ ; \
		echo >>$@ ; \
		echo "$$obj:$$pofile.stamp-remove" >>$@ ; \
		echo "$$pofile.stamp-remove:" >>$@ ; \
		echo "	rm -f '$$pofile.stamp'" >>$@ ; \
		echo '	touch $$@' >>$@ ; \
	done
@am__include@ @am__quote@./$(DEPDIR)/podeps.dep@am__quote@

endif


muwx/resourceload.h:$(top_srcdir)/xrc/wxresource.h

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
	cvstag="check_`echo $(PACKAGE_VERSION)| sed -e 's/[$,.:; 	@]/_/g'`" ; \
	(cd $(top_srcdir) && cvs tag -F "$$cvstag" ) ; \
	test -f $(top_srcdir)/CVS/Tag && tag=" -r `sed -e s/^T// <$(top_srcdir)/CVS/Tag`" || tag=" -r $$cvstag" ; \
	repo=`cat $(top_srcdir)/CVS/Repository` ; \
	mkdir -p cvsdist cvsdistm ; \
	CVSROOT=`cat $(top_srcdir)/CVS/Root` ; \
	export CVSROOT ; \
	if test "" = "$$tag"  ; then \
	  $(CVS) export -d "cvsdistm" "$$repo" ; \
	else \
	  echo $(CVS) export $$tag -d "cvsdistm" "$$repo" ; \
	  $(CVS) export $$tag -d "cvsdistm" "$$repo" ; \
	fi && \
	mv cvsdistm "cvsdist/$$repo" && \
	cd "cvsdist/$$repo" && \
	autoreconf -i && \
	./configure && \
	$(MAKE)  distcheck


mutabor-cxxprecompiled.stamp:mutabor-cxxprecompiled.$(PCHEXT_CXX)
	if test \! -f mutabor-cxxprecompiled.stamp ; then touch mutabor-cxxprecompiled.stamp ; fi
	touch -d '2001-01-01 00:00:00' mutabor-cxxprecompiled.$(PCHEXT_CXX)
	touch -d '2002-01-01 00:00:00' $@

mutabor-cxxprecompiled:mutabor-cxxprecompiled.stamp


if COND_PRECOMP_CXX
$(mutabor_OBJECTS):mutabor-cxxprecompiled.stamp


mutabor-cxxprecompiled.sorted: Makefile
	@echo 'creating $@'
	@for datei in $(INDENTHEADERS) ; \
	do  \
		echo $$datei | $(EGREP) '\.h$$' >/dev/null && \
		echo '#include "'"$$datei"'"' >>$@.tmp ; \
	done ; true
	@if cmp -s $@.tmp $@ ; then \
		rm -f $@.tmp ;\
        else \
		mv $@.tmp $@; \
        fi 

mutabor-cxxprecompiled.h:mutabor-cxxprecompiled.h.shuffle

mutabor-cxxprecompiled.h.shuffle: mutabor-cxxprecompiled.sorted
	$(MAKE) mutabor-cxxprecompiled.sorted
	@echo 'Shuffling mutabor-cxxprecompiled.h ...'
	echo '#define PRECOMPILE 1' >mutabor-cxxprecompiled.h
	echo '#include "Defs.h"' >> mutabor-cxxprecompiled.h
	$(SHUFFLE) <$< >> mutabor-cxxprecompiled.h
	echo '#undef PRECOMPILE' >> mutabor-cxxprecompiled.h
	touch -d '2000-01-01 00:00:00' mutabor-cxxprecompiled.h
	rm -f mutabor-cxxprecompiled.$(PCHEXT_CXX)
endif

if COND_WINRC
$(mutabor_SHORTNAME)-Mutabor.$(OBJEXT):$(top_srcdir)/muwx/Mutabor.rc
	$(RCCOMPILE) $(srcdir)/muwx/Mutabor.rc $@
endif

Mutabor.xrc: $(top_srcdir)/xrc/Mutabor.xrc
	cp $< $@
#	sed -e 's/_amp;/\&amp;/g' <$(top_srcdir)/xrc/Mutabor.xrc >Mutabor.xrc

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
	$(MAKE) $*.h

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
mu32/mut.cpp mu32/mut.h: $(top_srcdir)/mu32/mut.h
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
	mkdir -p dmg/Mutabor/.background
	cp -r Mutabor.app dmg/Mutabor
	cp $(top_srcdir)/osdep/macosx/DS_Store dmg/Mutabor/.DS_Store
	cp $(top_srcdir)/osdep/macosx/background.png dmg/Mutabor/.background
	cp $(top_srcdir)/muwx/Icon/Mutabor.icns dmg/Mutabor/.VolumeIcon.icns 
	ln -s /Applications dmg/Mutabor
	rm -f "$(PACKAGE_NAME)-$(PACKAGE_VERSION).dmg"
	hdiutil create -srcfolder dmg/Mutabor -volname "$(PACKAGE_NAME)" "$(PACKAGE_NAME)-$(PACKAGE_VERSION)"
	rm -r dmg/Mutabor


Mutabor.appold:all Mutabor.xrc mutabor update-gmo
	$(MKDIR_P) Mutabor.app/Contents/MacOS
	$(MKDIR_P) Mutabor.app/Contents/Resources
	cp mutabor Mutabor.app/Contents/MacOS
	cp osdep/macosx/Info.plist Mutabor.app/Contents
	cp $(top_srcdir)/muwx/Icon/Mutabor.icns Mutabor.app/Contents/Resources/Mutabor.icns
	echo -n APPLMUTA >Mutabor.app/Contents/PkgInfo
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

Mutabor.app:all Mutabor.xrc mutabor update-gmo
	$(MAKE) "prefix=`pwd`/Mutabor.app/Contents" 'bindir=$$(prefix)/MacOS' 'datarootdir=$$(prefix)/Resources' 'libdir=$$(prefix)' \
		'libexecdir=$$(prefix)/libs' 'localedir=$$(prefix)/locales' 'pkgdatadir=$$(prefix)/Resources' install installwxlocale
	ls Mutabor.app/Contents/locales/*/LC_MESSAGES/*.mo | \
	while read file ; do \
		lang=`echo $$file | sed -e 's,.*/\([^/]*\)/LC_MESSAGES/.*\.mo,\1,g'` ; echo $$lang ;\
		mkdir -p Mutabor.app/Contents/Resources/$$lang.lproj ; \
		mv $$file Mutabor.app/Contents/Resources/$$lang.lproj ; \
	done
	rm -rf Mutabor.app/Contents/locales
	cp osdep/macosx/Info.plist Mutabor.app/Contents
	cp $(top_srcdir)/muwx/Icon/Mutabor.icns Mutabor.app/Contents/Resources/Mutabor.icns
	echo -n APPLMUTA >Mutabor.app/Contents/PkgInfo

installwinold: mutabor.exe
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
	WXLIBDIR=`$(WX_CONFIG_PATH) --exec-prefix`
	for d in `$(WX_CONFIG_PATH) --exec-prefix`/lib/wx*{msw,base}*.dll ; \
	do \
		cp $$d Mutabor ; \
	done

installdll:
	@echo 'solving references for $(DLLLINKFILE)'
	DLLSEARCHPATH="$(DLLSEARCHPATH)" ; \
	for d in `LANG=C $(OBJDUMP) -p  Mutabor/$(DLLLINKFILE) |sed '/^\s*DLL Name:.*\(wx\|mingw\|gcc\|stdc++\)/ { s/^\s*DLL Name:\s*//; p } ; d '` ; \
	do \
		echo -n checking "$$d" ; \
		if [ ! -f Mutabor/$$d ] ; then \
			echo -n search ; \
			f=`( find $$DLLSEARCHPATH -name "$$d" ; \
			find $$DLLSEARCHPATH -name "$$d.*")|head -n 1` ; \
			echo -n install "$$f" ; \
			test -f "$$f" && $(INSTALL_PROGRAM_ENV) $(INSTALL_DATA) "$$f" "`pwd`/Mutabor" ; \
			case "$$f" in \
			*.gz)  GZIP=$(GZIP_ENV) gzip -dc Mutabor/`basename "$$f"` >Mutabor/"$$d" ;; \
			esac ; \
			echo -n check "$$d" ; \
			$(MAKE) DLLLINKFILE="$$d" installdll ; \
		fi ; \
		echo done ;\
	done

installwxlocale:
	test -z "$(WX_LOCALE_DIRS)" || ( ls "$(WX_LOCALE_DIRS)"/*/LC_MESSAGES/wxstd.mo | \
	while read file ; do \
		lang=`echo $$file | sed -e 's,.*/\([^/]*\)/LC_MESSAGES/wxstd.mo,\1,g'` ; echo $$lang ;\
		mkdir -p $(localedir)/$$lang/LC_MESSAGES ; \
		cp $$file $(localedir)/$$lang/LC_MESSAGES ; \
	done )

installwin:
	rm -f Mutabor/mutabor.exe
	$(MAKE) "prefix=`pwd`/Mutabor" \
		'bindir=$$(prefix)' \
		'datarootdir=$$(prefix)' \
		'libdir=$$(prefix)' \
		'libexecdir=$$(prefix)' \
		'localedir=$$(prefix)' \
		'pkgdatadir=$$(prefix)' \
		'mutabordir=$$(prefix)' \
		install installwxlocale
	$(MAKE) DLLLINKFILE="mutabor.exe" installdll

installwinbackup:
	WXLIBDIR=`$(WX_CONFIG_PATH) --exec-prefix`/lib ;\
	for d in `LANG=C $(OBJDUMP) -p  Mutabor/mutabor.exe |sed '/^\s*DLL Name:.*\(wx\|mingw\)/ { s/^\s*DLL Name:\s*//; p } ; d '` ; \
	do \
		f=`( find "$$WXLIBDIR" /lib /usr/lib /usr/share/doc/mingw32-runtime -name "$$d" ; \
		find "$$WXLIBDIR" /lib /usr/lib /usr/share/doc/mingw32-runtime -name "$$d.*")|head -n 1` ; \
		test -f "$$f" && $(INSTALL_PROGRAM_ENV) $(INSTALL_DATA) "$$f" "`pwd`/Mutabor" ; \
		case "$$f" in \
		*.gz)  GZIP=$(GZIP_ENV) gzip -dc Mutabor/`basename "$$f"` >Mutabor/"$$d" ;; \
		esac ; \
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

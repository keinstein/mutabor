ACLOCAL_AMFLAGS = -I m4 --install
MAKEFILE_DEPS = remove-podeps.stamp
DLLCOPYPATTERN = \(wx\|mingw\)
SUBDIRS = po lib src . doc #intl# libmutabor .
#DIST_SUBDIRS = $(SUBDIRS)
AM_CPPFLAGS = -I$(top_srcdir)/lib/rtmidi @NETINET_INC@ #$(top_builddir)/intl -I $(top_srcdir)/intl 
SUFFIXES = .$(PCHEXT_CXX) .rc .res

RCCOMPILE = $(RC) $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(CPPFLAGS) $(RCFLAGS)
CVS = cvs
GIT = git
REPOSITORY = http://git.berlios.de/mutabor
REPOSITORY_PATH = .
INDENT = astyle --style=linux --indent=tab=8
EXTRA_DIST = config.rpath \
	m4/ChangeLog  \
	debian \
	lib/libasprintf \
	Images \
	$(top_srcdir)/src/kernel/mut.y \
	src/xrc/wxresource.cpp \
	src/xrc/wxresource.h \
	src/xrc/reslocale.cpp \
	osdep/macosx/Application_Code.txt \
	osdep/macosx/background.png \
	osdep/macosx/background.svg \
	osdep/macosx/DS_Store \
	osdep/macosx/Info.plist.in \
	osdep/win/config.h \
	osdep/win/config.h.in \
	osdep/win/Mutabor.rc \
	osdep/win/Mutabor.nsi \
	osdep/win/Mutabor.nsi.in \
	osdep/win/Mutabor.sln \
	osdep/win/muwx.vcxproj \
	src/wxGUI/Mutabor.rc \
	Examples/english/cdur.mut \
	Examples/english/cohen.mut \
	Examples/english/demo.mut \
	Examples/english/demos.mut \
	Examples/english/extern.mut \
	Examples/english/instr.mut \
	Examples/english/midi.mut \
	Examples/english/nix.mut \
	Examples/german/Cdur.mut \
	Examples/german/Cohen.mut \
	Examples/german/Demo.mut \
	Examples/german/Demos.mut \
	Examples/german/Demo-utf8.mut \
	Examples/german/Extern.mut \
	Examples/german/Instr.mut \
	Examples/german/Midi.mut \
	Examples/german/Nix.mut

# Please use Tango names for new files
# http://tango.freedesktop.org/Tango_Desktop_Project
dist_pkgdata_DATA = src/xrc/Mutabor.xrc \
	Images/about.png \
	Images/about.xpm \
	Images/Icons/png/NewInputDevice.png \
	Images/Icons/png/InputDevice.png \
	Images/Icons/png/NewOutputDevice.png \
	Images/Icons/png/OutputDevice.png \
	Images/Icons/png/MidiFile.png \
	Images/Icons/png/GuidoFile.png \
	Images/Icons/png/ActiveChannel.png \
	Images/Icons/png/PassiveChannel.png \
	Images/Icons/png/TuningBox.png \
	Images/Icons/png/document-new.png \
	Images/Icons/png/document-open.png \
	Images/Icons/png/document-save.png \
	Images/Icons/png/document-save-as.png \
	Images/Icons/png/document-print.png \
	Images/Icons/png/ActivateMutabor.png \
	Images/Icons/png/StopMutabor.png \
	Images/Icons/png/Panic.png \
	Images/Icons/png/edit-copy.png \
	Images/Icons/png/edit-cut.png \
	Images/Icons/png/edit-paste.png \
	Images/Icons/png/edit-undo.png \
	Images/Icons/png/edit-redo.png \
	Images/Icons/png/RouteLoad.png \
	Images/Icons/png/RouteSave.png \
	Images/Icons/png/InDevPlay.png \
	Images/Icons/png/InDevStop.png \
	Images/Icons/png/InDevPause.png \
	Images/Icons/png/help-browser.png
#RECURSIVE_TARGETS += mac-recursive
BUILT_SOURCES = \
	$(top_srcdir)/src/kernel/mut.cpp \
	$(top_srcdir)/src/kernel/mut.h \
	$(top_srcdir)/src/xrc/wxresource.h \
	$(top_srcdir)/osdep/win/Mutabor.nsi

if COND_PRECOMP_CXX
BUILT_SOURCES += mutabor-cxxprecompiled.$(PCHEXT_CXX)
nodist_mutabor_SOURCES = mutabor-cxxprecompiled.$(PCHEXT_CXX)
endif

bin_PROGRAMS = mutabor

INLINEHEADERS = \
		src/kernel/routing/CommonFileDevice-inlines.h \
		src/kernel/routing/Device-inlines.h \
		src/kernel/routing/Route-inlines.h \
		src/wxGUI/GUIBoxData-inlines.h \
		src/wxGUI/Routing/GUIRoute-inlines.h 


INDENTHEADERS = \
		src/kernel/Defs.h \
		src/kernel/routing/gmn/DevGIS.h \
		src/kernel/routing/gmn/GIS_Head.h \
		src/kernel/routing/gmn/GIS.h \
		src/kernel/routing/gmn/GSP_File.h \
		src/kernel/routing/gmn/GSP.h \
		src/kernel/routing/midi/DevMidF.h \
		src/kernel/routing/midi/DevMidi.h \
		src/kernel/routing/CommonFileDevice.h \
		src/kernel/routing/Device.h \
		src/kernel/routing/Route.h \
		src/kernel/routing/RouteCompat.h \
		src/kernel/box.h \
		src/kernel/Errors.h \
		src/kernel/Execute.h \
		src/kernel/Frac.h \
		src/kernel/Global.h \
		src/kernel/GrafKern.h \
		src/kernel/Hilfs.h \
		src/kernel/Interpre.h \
		src/kernel/Interval.h \
		src/kernel/MidiKern.h \
		src/kernel/Runtime.h \
		src/kernel/treestorage.h \
		src/wxGUI/Routing/BoxChannelShape.h \
		src/wxGUI/Routing/BoxDlg.h \
		src/wxGUI/Routing/BoxIconShape.h \
		src/wxGUI/Routing/BoxShape.h \
		src/wxGUI/Routing/DebugRoute.h \
		src/wxGUI/Routing/DeviceShape.h \
		src/wxGUI/Routing/GUIRoute.h \
		src/wxGUI/Routing/InputDevDlg.h \
		src/wxGUI/Routing/InputDeviceShape.h \
		src/wxGUI/Routing/InputGuidoFileDeviceShape.h \
		src/wxGUI/Routing/InputMidiDeviceShape.h \
		src/wxGUI/Routing/InputMidiFileDeviceShape.h \
		src/wxGUI/Routing/NewBoxShape.h \
		src/wxGUI/Routing/NewInputDeviceShape.h \
		src/wxGUI/Routing/NewOutputDeviceShape.h \
		src/wxGUI/Routing/OutputDevDlg.h \
		src/wxGUI/Routing/OutputDeviceShape.h \
		src/wxGUI/Routing/OutputGuidoFileDeviceShape.h \
		src/wxGUI/Routing/OutputMidiDeviceShape.h \
		src/wxGUI/Routing/OutputMidiFileDeviceShape.h \
		src/wxGUI/Routing/RouteIcons.h \
		src/wxGUI/Routing/RouteLists.h \
		src/wxGUI/Action.h \
		src/wxGUI/GUIBoxData.h \
		src/wxGUI/MutBitmaps.h \
		src/wxGUI/Mutabor.rh \
		src/wxGUI/CompDlg.h \
		src/wxGUI/configtree.h \
		src/wxGUI/IconShape.h \
		src/wxGUI/MutApp.h \
		src/wxGUI/MutChild.h \
		src/wxGUI/MutConfDlg.h \
		src/wxGUI/MutDocManager.h \
		src/wxGUI/MutDocument.h \
		src/wxGUI/MutEditFile.h \
		src/wxGUI/MutFrame.h \
		src/wxGUI/MutIcon.h \
		src/wxGUI/MutLogicWnd.h \
		src/wxGUI/MutRouteWnd.h \
		src/wxGUI/MutTextBox.h \
		src/wxGUI/MutView.h \
		src/wxGUI/Panel.h \
		src/wxGUI/resourceload.h \
		src/wxGUI/stclanguage.h \
		src/wxGUI/generic/mhArray.h \
		src/wxGUI/generic/mhDefs.h \
		src/wxGUI/generic/muconvauto.h \
		src/wxGUI/generic/mutDebug.h \
		src/wxGUI/generic/valNum.h \
		src/wxGUI/generic/valRadio.h \
		lib/rtmidi/RtError.h \
		lib/rtmidi/RtMidi.h

mutabor_INDENTS = \
		src/kernel/routing/gmn/DevGIS.cpp \
		src/kernel/routing/gmn/GIS_Head.cpp \
		src/kernel/routing/gmn/GIS.cpp \
		src/kernel/routing/gmn/GSP_Err.cpp \
		src/kernel/routing/gmn/GSP_File.cpp \
		src/kernel/routing/gmn/GSP.cpp \
		src/kernel/routing/midi/DevMidF.cpp \
		src/kernel/routing/midi/DevMidi.cpp \
		src/kernel/routing/CommonFileDevice.cpp \
		src/kernel/routing/Device.cpp \
		src/kernel/routing/Route.cpp \
		src/kernel/routing/RouteCompat.cpp \
		src/kernel/box.cpp \
		src/kernel/Errors.cpp \
		src/kernel/Execute.cpp \
		src/kernel/Frac.cpp \
		src/kernel/GrafKern.cpp \
		src/kernel/Hilfs.cpp \
		src/kernel/Interval.cpp \
		src/kernel/Parser.cpp \
		src/kernel/Runtime.cpp \
		src/kernel/TabGen.cpp \
		src/wxGUI/Routing/BoxChannelShape.cpp \
		src/wxGUI/Routing/BoxDlg.cpp \
		src/wxGUI/Routing/BoxIconShape.cpp \
		src/wxGUI/Routing/BoxShape.cpp \
		src/wxGUI/Routing/DebugRoute.cpp \
		src/wxGUI/Routing/DeviceShape.cpp \
		src/wxGUI/Routing/GUIRoute.cpp \
		src/wxGUI/Routing/InputDevDlg.cpp \
		src/wxGUI/Routing/InputDeviceShape.cpp \
		src/wxGUI/Routing/InputGuidoFileDeviceShape.cpp \
		src/wxGUI/Routing/InputMidiDeviceShape.cpp \
		src/wxGUI/Routing/InputMidiFileDeviceShape.cpp \
		src/wxGUI/Routing/NewBoxShape.cpp \
		src/wxGUI/Routing/NewInputDeviceShape.cpp \
		src/wxGUI/Routing/NewOutputDeviceShape.cpp \
		src/wxGUI/Routing/OutputDevDlg.cpp \
		src/wxGUI/Routing/OutputDeviceShape.cpp \
		src/wxGUI/Routing/OutputGuidoFileDeviceShape.cpp \
		src/wxGUI/Routing/OutputMidiDeviceShape.cpp \
		src/wxGUI/Routing/OutputMidiFileDeviceShape.cpp \
		src/wxGUI/Routing/RouteIcons.cpp \
		src/wxGUI/Action.cpp \
		src/wxGUI/GUIBoxData.cpp \
		src/wxGUI/MutBitmaps.cpp \
		src/wxGUI/CompDlg.cpp \
		src/wxGUI/configtree.cpp \
		src/wxGUI/IconShape.cpp \
		src/wxGUI/MutApp.cpp \
		src/wxGUI/MutChild.cpp \
		src/wxGUI/MutDocManager.cpp \
		src/wxGUI/MutDocument.cpp \
		src/wxGUI/MutEditFile.cpp \
		src/wxGUI/MutFrame.cpp \
		src/wxGUI/MutIcon.cpp \
		src/wxGUI/MutLogicWnd.cpp \
		src/wxGUI/MutRouteWnd.cpp  \
		src/wxGUI/MutTextBox.cpp \
		src/wxGUI/MutView.cpp \
		src/wxGUI/Panel.cpp \
		src/wxGUI/stclanguage.cpp \
		src/wxGUI/generic/muconvauto.cpp \
		src/wxGUI/generic/mutDebug.cpp \
		src/wxGUI/generic/mxDefs.cpp \
		src/wxGUI/generic/valNum.cpp \
		src/wxGUI/generic/valRadio.cpp \
		lib/rtmidi/RtMidi.cpp

#		src/wxGUI/InputFilterDlg.cpp \
#		src/wxGUI/InputFilterDlg.h \
#		src/wxGUI/OutputFilterDlg.cpp \
#		src/wxGUI/OutputFilterDlg.h \
#

CLEANFILES = \
	mutabor-cxxprecompiled.$(PCHEXT_CXX) \
	mutabor-cxxprecompiled.h \
	mutabor-cxxprecompiled.stamp \
	Mutabor.xrc \
	$(mutabor_SHORTNAME)-Mutabor-winrc.$(OBJEXT)

INDENTS = $(mutabor_INDENTS) $(INDENTHEADERS) $(INLINEHEADERS)

noinst_HEADERS =  src/kernel/mut.h \
		  src/wxGUI/generic/mutDebugFlags.h \
		  $(INDENTHEADERS) \
		  $(INLINEHEADERS)

mutabor_COMPILESOURCES = $(mutabor_INDENTS) \
			  src/kernel/mut.cpp

mutabor_SOURCES = $(mutabor_COMPILESOURCES)
if COND_WINRC
mutabor_COMPILESOURCES += src/wxGUI/Mutabor.rc
endif

#		src/wxGUI/generic/myContextHelpButton.h \
#		src/wxGUI/generic/myContextHelpButton.cpp \
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
$(mutabor_SHORTNAME)-Mutabor-winrc.$(OBJEXT):$(srcdir)/src/wxGUI/Mutabor.rc
	$(RCCOMPILE) $< $@
else
$(mutabor_SHORTNAME)-Mutabor-winrc.$(OBJEXT):$(srcdir)/src/wxGUI/Mutabor.rc
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


src/wxGUI/resourceload.h:$(top_srcdir)/src/xrc/wxresource.h

cvs_dist: Makefile
	touch cvsdist
	chmod -R u+w  cvsdist
	rm -rf cvsdist
	mkdir cvsdist
	cd cvsdist && \
	$(GIT) clone $(REPOSITORY) && \
	cd $(REPOSITORY_PATH) && \
	autoreconf -i && \
	./configure && \
	$(MAKE) dist

cvs_distcheck: Makefile
	touch cvsdist
	chmod -R u+w  cvsdist
	rm -rf cvsdist
	cvstag="check_`echo $(PACKAGE_VERSION)| sed -e 's/[$,.:; 	@]/_/g'`" ; \
	(cd $(top_srcdir) && $(GIT) tag -f "$$cvstag" ) ; \
	test -f $(top_srcdir)/CVS/Tag && tag=" -r `sed -e s/^T// <$(top_srcdir)/CVS/Tag`" || tag=" -r $$cvstag" ; \
	repo=mutabor ; \
	$(GIT) clone "$(REPOSITORY)" "cvsdist/$$repo" ; \
	if test "" = "$$tag"  ; then \
	  $(GIT) checkout master ; \
	else \
	  $(GIT) checkout "$$tag" ; \
	fi && \
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
$(mutabor_SHORTNAME)-Mutabor.$(OBJEXT):$(top_srcdir)/src/wxGUI/Mutabor.rc
	$(RCCOMPILE) $(srcdir)/src/wxGUI/Mutabor.rc $@
endif

Mutabor.xrc: $(top_srcdir)/src/xrc/Mutabor.xrc
	cp $< $@
#	sed -e 's/_amp;/\&amp;/g' <$(top_srcdir)/src/xrc/Mutabor.xrc >Mutabor.xrc

$(top_srcdir)/src/xrc/wxresource.h : $(top_srcdir)/src/xrc/Mutabor.xrc
	(cd $(top_srcdir)/src/xrc; \
	wxrc -c -e -o wxresource.cpp Mutabor.xrc)

reslocale.cpp: $(top_srcdir)/src/xrc/reslocale.cpp $(top_srcdir)/src/xrc/Mutabor.xrc
$(top_srcdir)/src/xrc/reslocale.cpp : $(top_srcdir)/src/xrc/Mutabor.xrc
	(cd $(top_srcdir)/src/xrc; \
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
src/kernel/mut.cpp src/kernel/mut.h: $(top_srcdir)/src/kernel/mut.h
$(top_srcdir)/src/kernel/mut.h: $(top_srcdir)/src/kernel/mut.y
$(top_srcdir)/src/kernel/mut.cpp: $(top_srcdir)/src/kernel/mut.h
if MAINTAINER_MODE
$(top_srcdir)/osdep/win/Mutabor.nsi: $(top_srcdir)/osdep/win/Mutabor.nsi.in \
	$(top_builddir)/config.status
	cd $(top_builddir) ; ./config.status osdep/win/Mutabor.nsi
	cp $(top_builddir)/osdep/win/Mutabor.nsi $@
endif

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
	cp $(top_srcdir)/src/wxGUI/Icon/Mutabor.icns dmg/Mutabor/.VolumeIcon.icns 
	ln -s /Applications dmg/Mutabor
	rm -f "$(PACKAGE_NAME)-$(PACKAGE_VERSION).dmg"
	hdiutil create -srcfolder dmg/Mutabor -volname "$(PACKAGE_NAME)" "$(PACKAGE_NAME)-$(PACKAGE_VERSION)"
	rm -r dmg/Mutabor


Mutabor.appold:all Mutabor.xrc mutabor update-gmo
	$(MKDIR_P) Mutabor.app/Contents/MacOS
	$(MKDIR_P) Mutabor.app/Contents/Resources
	cp mutabor Mutabor.app/Contents/MacOS
	cp osdep/macosx/Info.plist Mutabor.app/Contents
	cp $(top_srcdir)/src/wxGUI/Icon/Mutabor.icns Mutabor.app/Contents/Resources/Mutabor.icns
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
	cp $(top_srcdir)/src/wxGUI/Icon/Mutabor.icns Mutabor.app/Contents/Resources/Mutabor.icns
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
	@DLLSEARCHPATH="$(DLLSEARCHPATH)" ; \
	for d in `LANG=C $(OBJDUMP) -p  Mutabor/$(DLLLINKFILE) |sed '/^\s*DLL Name:.*\(wx\|mingw\|gcc\|stdc++\)/ { s/^\s*DLL Name:\s*//; p } ; d '` ; \
	do \
		echo -n checking "$$d" ; \
		if [ ! -f Mutabor/$$d ] ; then \
			echo -n search ; \
			f=`( find $$DLLSEARCHPATH -name "$$d" || \
			find $$DLLSEARCHPATH -name "$$d.*")|head -n 1` ; \
			echo -n install " $$f " ; \
			test -f "$$f" && $(INSTALL_PROGRAM_ENV) $(INSTALL_DATA) "$$f" "`pwd`/Mutabor" ; \
			case "$$f" in \
			*.gz)  GZIP=$(GZIP_ENV) gzip -dc Mutabor/`basename "$$f"` >Mutabor/"$$d" ;; \
			esac ; \
			echo -n check " $$d " ; \
			$(MAKE) DLLLINKFILE="$$d" installdll ; \
		fi ; \
		echo " done." ;\
	done

installwxlocale:
	test -z "$(WX_LOCALE_DIRS)" || { for dir in  $(WX_LOCALE_DIRS) ; \
	do \
		ls "$$dir"/*/LC_MESSAGES/wxstd.mo | \
		while read file ; do \
			lang=`echo $$file | sed -e 's,.*/\([^/]*\)/LC_MESSAGES/wxstd.mo,\1,g'` ; echo $$lang ;\
			mkdir -p $(localedir)/$$lang/LC_MESSAGES ; \
			cp $$file $(localedir)/$$lang/LC_MESSAGES ; \
		done ; \
	done }

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
	for d in GPL-2 LGPL-2.1 ; do \
		cp $(top_srcdir)/$$d Mutabor/$$d.txt ; \
	done

nsis: installwin
	rm -f mutabor-files.nsh
	rm -f mutabor-dirs.nsh
	rm -f mutabor-uninst-files.nsh
	cd Mutabor && \
	ls --file-type | grep -v / |  while read d ; \
	do \
		echo "file  \"Mutabor\\$$d\"" >>../mutabor-files.nsh ; \
		echo "delete \"\$$INSTDIR\\$$d\"" >>../mutabor-uninst-files.nsh  ; \
	done ; \
	ls  --file-type | grep / |  sed 's,/,\\\\,g' | while read d ; \
	do \
		echo "section \"-default dir $$d\"" >> ../mutabor-dirs.nsh ;  \
		echo "setOutPath \"\$$INSTDIR\\$$d\"" >> ../mutabor-dirs.nsh ; \
		echo "file /r \"Mutabor\\$$d*.*\"" >> ../mutabor-dirs.nsh ; \
		echo "sectionEnd" >> ../mutabor-dirs.nsh ; \
		echo "RMDir /r \"\$$INSTDIR\\$$d\"" >>../mutabor-uninst-files.nsh ; \
	done
	cp osdep/win/Mutabor.nsi .
	makensis Mutabor.nsi


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
	cd $(top_srcdir); $(GIT) tag `date '+date_%Y-%m-%d_%H%M'`


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

dch:
	dch -v "$(PACKAGE_VERSION)"

debuild: dch
	debuild

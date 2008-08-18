ACLOCAL_AMFLAGS = -I m4
distdir = $(PACKAGE_TARNAME)-$(VERSION)
SUBDIRS = missfunc intl po wxintl includes . doc # libmutabor .
INCLUDES = -I $(srcdir)/mu32  -I $(srcdir)/muwx -I $(srcdir)/rtmidi \
	-I $(srcdir)/mywx -I $(top_builddir)/intl -I $(top_srcdir)/intl \
	-I $(top_srcdir)/xrc \
	@NETINET_INC@
SUFFIXES = .$(PCHEXT_CXX) .rc .res
BUILT_SOURCES = $(top_srcdir)/xrc/wxresource.h
BUILT_SOURCES += @COND_PRECOMP_CXX_TRUE@mutabor-cxxprecompiled.$(PCHEXT_CXX)
RCCOMPILE = $(RC) $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(CPPFLAGS) $(RCFLAGS)
CVS = cvs
EXTRA_DIST = config.rpath mkinstalldirs m4/ChangeLog  debian/changelog debian/compat debian/control debian/copyright \
debian/dirs debian/docs debian/libmutabor-dev.install \
debian/libmutabor.install debian/mutabor-doc.docs debian/mutabor-doc.install \
debian/mutabor.install debian/README.Debian debian/rules \
 libasprintf
dist_pkgdata_DATA = xrc/Mutabor.xrc Images/about.png
#RECURSIVE_TARGETS += mac-recursive
BUILT_SOURCES += $(top_srcdir)/mu32/mut.cpp $(top_srcdir)/mu32/mut.h
bin_PROGRAMS = mutabor
mutabor_SOURCES = mu32/Hilfs.cpp mywx/mxDefs.cpp \
		mu32/Interval.cpp \
		$(top_srcdir)/mu32/mut.cpp $(top_srcdir)/mu32/mut.h \
		mu32/Parser.cpp mu32/Runtime.cpp \
		mu32/TabGen.cpp rtmidi/RtMidi.cpp muwx/MutApp.cpp muwx/MutChild.cpp \
		muwx/MutEditFile.cpp muwx/MutFrame.cpp \
		muwx/OutputDevDlg.cpp \
		muwx/MutLogicWnd.cpp \
		muwx/MutRouteWnd.cpp  \
		muwx/MutTextBox.cpp \
		muwx/CompDlg.cpp muwx/Action.cpp \
		muwx/InputDevDlg.cpp mu32/DevGIS.cpp mu32/Device.cpp mu32/DevMidF.cpp \
		mu32/DevMidi.cpp mu32/EDevice.cpp mu32/Errors.cpp mu32/Execute.cpp \
		mu32/Frac.cpp mu32/GrafKern.cpp mywx/valNum.cpp mu32/GIS_Head.cpp mu32/GIS.cpp \
		mu32/GSP_Err.cpp mu32/GSP_File.cpp mu32/GSP.cpp muwx/InputFilterDlg.cpp \
		muwx/BoxDlg.cpp muwx/OutputFilterDlg.cpp mywx/valRadio.cpp \
		mu32/Hilfs.h mywx/mhDefs.h mu32/Defs.h mu32/Interpre.h \
		mu32/Interval.h mu32/Runtime.h mu32/Global.h \
		rtmidi/RtMidi.h muwx/MutApp.h muwx/MutChild.h \
		muwx/MutEditFile.h muwx/MutFrame.h muwx/MutLogicWnd.h \
		muwx/OutputDevDlg.h muwx/Mutabor.rh \
		muwx/MutRouteWnd.h muwx/MutTextBox.h muwx/CompDlg.h muwx/Action.h \
		muwx/InputDevDlg.h mu32/DevGIS.h mu32/Device.h mu32/DevMidF.h \
		mu32/DevMidi.h mu32/EDevice.h mu32/Execute.h \
		mu32/Frac.h mu32/GrafKern.h mywx/valNum.h mu32/GIS_Head.h mu32/GIS.h \
		mu32/GSP_File.h mu32/GSP.h muwx/InputFilterDlg.h \
		muwx/BoxDlg.h muwx/OutputFilterDlg.h mywx/valRadio.h \
		mywx/mhArray.h rtmidi/RtError.h mu32/MidiKern.h \
		muwx/Mutabor.rc \
		mywx/myContextHelpButton.h \
		mywx/myContextHelpButton.cpp \
		mywx/muconvauto.cpp mywx/muconvauto.h \
		$(top_srcdir)/xrc/wxresource.h \
		muwx/Icon muwx/bitmaps @COND_PRECOMP_CXX_TRUE@mutabor-cxxprecompiled.$(PCHEXT_CXX)

#
mutabordir=$(datadir)/mutabor

mutabor_LDFLAGS = $(LDFLAGS) $(ALSA_LIBS) $(WX_LIBS)
mutabor_CallFLAGS = $(ALSA_CFLAGS)  $(WX_CFLAGS)
mutabor_CFLAGS = $(mutabor_CallFLAGS)
mutabor_CXXFLAGS = $(mutabor_CallFLAGS)
mutabor_CXX = $(MAKE) $(AM_MAKEFLAGS) mutabor-precompile && $(CXX)
mutabor_CPPFLAGS = $(WX_CPPFLAGS) 
mutabor_CFLAGS += @COND_PRECOMP_C_TRUE@-include mutabor-precompiled.h
mutabor_CXXFLAGS += @COND_PRECOMP_CXX_TRUE@-include mutabor-cxxprecompiled.h
mutabor_SHORTNAME = mutabor
mutabor_DEPENDENCIES = @COND_WINRC_TRUE@$(mutabor_SHORTNAME)-Mutabor.$(OBJEXT)
mutabor_LDADD = $(LDADD) @COND_WINRC_TRUE@ $(mutabor_SHORTNAME)-Mutabor.$(OBJEXT)
mutabor_DATA = Images/about.png Mutabor.xrc

@AMDEP_TRUE@@am__include@ @am__quote@./$(DEPDIR)/mutabor-cxxprecompiled.Po@am__quote@

.PHONY: cvs_dist cvs_distcheck mutabor-cxxprecompiled mac mac-recursive

@COND_WINRC_TRUE@.rc.$(OBJEXT):
@COND_WINRC_TRUE@	 $(RCCOMPILE) $< $@

.h.$(PCHEXT_CXX):
@am__fastdepCXX_TRUE@	if $(CXXCOMPILE) $(mutabor_CPPFLAGS) $(mutabor_CallFLAGS) -MT $@ -MD -MP -MF "$(DEPDIR)/$*.Tpo" -o $@ -c `test -f '$<' || echo '$(srcdir)/'`$<; \
@am__fastdepCXX_TRUE@	then mv -f "$(DEPDIR)/$*.Tpo" "$(DEPDIR)/$*.Po"; else rm -f "$(DEPDIR)/$*.Tpo"; exit 1; fi 
@AMDEP_TRUE@@am__fastdepCXX_FALSE@	source='$<' object='$@' libtool=no @AMDEPBACKSLASH@
@AMDEP_TRUE@@am__fastdepCXX_FALSE@	DEPDIR=$(DEPDIR) $(CXXDEPMODE) $(depcomp) @AMDEPBACKSLASH@
@am__fastdepCXX_FALSE@	$(CXX) $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(mutabor_CPPFLAGS) $(CPPFLAGS) $(mutabor_CallFLAGS) $(CXXFLAGS) -c  `test -f '$<' || echo '$(srcdir)/'`$<

cvs_dist: Makefile
	chmod -R u+w  cvsdist
	rm -rf cvsdist
	mkdir cvsdist
	cd cvsdist && \
	$(CVS) -d `cat ../CVS/Root` export -r HEAD `cat ../CVS/Repository` && \
	cd `cat ../CVS/Repository` && \
	./configure && \
	$(MAKE) dist

cvs_distcheck: Makefile
	chmod -R u+w  cvsdist
	rm -rf cvsdist
	mkdir cvsdist
	cd cvsdist && \
	$(CVS) -d `cat ../CVS/Root` export -r HEAD `cat ../CVS/Repository` && \
	cd `cat ../CVS/Repository` && \
	./configure && \
	$(MAKE)  distcheck

@COND_PRECOMP_CXX_TRUE@$(mutabor_OBJECTS):mutabor-cxxprecompiled.stamp

mutabor-cxxprecompiled.stamp:mutabor-cxxprecompiled.$(PCHEXT_CXX)
	if test \! -f mutabor-cxxprecompiled.stamp ; then touch mutabor-cxxprecompiled.stamp ; fi


mutabor-cxxprecompiled.h:
@COND_PRECOMP_CXX_TRUE@	echo '#define PRECOMPILE 1' >$@
@COND_PRECOMP_CXX_TRUE@	echo '#ifdef HAVE_CONFIG_H' >>$@
@COND_PRECOMP_CXX_TRUE@	echo '#include "config.h"' >>$@
@COND_PRECOMP_CXX_TRUE@	echo '#endif' >>$@
@COND_PRECOMP_CXX_TRUE@	for datei in $(mutabor_SOURCES) ; \
@COND_PRECOMP_CXX_TRUE@	do  \
@COND_PRECOMP_CXX_TRUE@		echo -n $$datei | $(EGREP) '\.r?h$$' && echo '#include "'"$$datei"'"' >>$@ ; \
@COND_PRECOMP_CXX_TRUE@ done ; true
@COND_PRECOMP_CXX_TRUE@	echo '#undef PRECOMPILE' >>$@


@COND_WINRC_TRUE@$(mutabor_SHORTNAME)-Mutabor.$(OBJEXT):$(srcdir)/muwx/Mutabor.rc
@COND_WINRC_TRUE@	 $(RCCOMPILE) $(srcdir)/muwx/Mutabor.rc $@

Mutabor.xrc: $(top_srcdir)/xrc/Mutabor.xrc
	cp $< $@
#	sed -e 's/_amp;/\&amp;/g' <$(top_srcdir)/xrc/Mutabor.xrc >Mutabor.xrc

Mutabor.app:all Mutabor.xrc mutabor
	mkdir -p Mutabor.app/Contents/MacOS
	mkdir -p Mutabor.app/Contents/Resources
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
	cp $(top_srcdir)/Images/about.png Mutabor.xrc Mutabor.app/Contents/Resources
	ls "$(WX_LOCALE_DIRS)"/*/LC_MESSAGES/wxstd.mo | \
	while read file ; do \
		lang=`echo $$file | sed -e 's,.*/\([^/]*\)/LC_MESSAGES/wxstd.mo,\1,g'` ; echo $$lang ;\
		mkdir -p Mutabor.app/Contents/Resources/$$lang.lproj ; \
		cp $$file Mutabor.app/Contents/Resources/$$lang.lproj ; \
	done

$(top_srcdir)/xrc/wxresource.h : $(top_srcdir)/xrc/Mutabor.xrc
	(cd $(top_srcdir)/xrc; \
	wxrc -c -e -o wxresource.cpp Mutabor.xrc)

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

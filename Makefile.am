distdir = $(PACKAGE_TARNAME)-$(VERSION)
SUBDIRS = includes libmutabor .
INCLUDES = -I $(srcdir)/mu32  -I $(srcdir)/muwx -I $(srcdir)/rtmidi -I $(srcdir)/mywx
SUFFIXES = .$(PCHEXT_CXX)
BUILT_SOURCES = @COND_PRECOMP_CXX_TRUE@mutabor-cxxprecompiled.$(PCHEXT_CXX)
CVS = cvs
EXTRA_DIST = debian/changelog debian/compat debian/control debian/copyright \
debian/dirs debian/docs debian/libmutabor-dev.install \
debian/libmutabor.install debian/mutabor-doc.docs debian/mutabor-doc.install \
debian/mutabor.install debian/README.Debian debian/rules
bin_PROGRAMS = mutabor
mutabor_SOURCES = mu32/Hilfs.cpp mywx/mxDefs.cpp \
		mu32/Interval.cpp mu32/Mut_Tab.cpp mu32/Parser.cpp mu32/Runtime.cpp \
		mu32/TabGen.cpp rtmidi/RtMidi.cpp muwx/MutApp.cpp muwx/MutChild.cpp \
		muwx/MutEditFile.cpp muwx/MutFrame.cpp muwx/MutLogicWnd.cpp \
		muwx/OutputDevDlg.cpp \
		muwx/MutRouteWnd.cpp muwx/MutTextBox.cpp muwx/CompDlg.cpp muwx/Action.cpp \
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
		muwx/Icon muwx/bitmaps @COND_PRECOMP_CXX_TRUE@mutabor-cxxprecompiled.$(PCHEXT_CXX)
mutabor_LDFLAGS = $(ALSA_LIBS) $(WX_LIBS)
mutabor_CallFLAGS = $(ALSA_CFLAGS)  $(WX_CFLAGS)
mutabor_CFLAGS = $(mutabor_CallFLAGS)
mutabor_CXXFLAGS = $(mutabor_CallFLAGS)
mutabor_CXX = $(MAKE) $(AM_MAKEFLAGS) mutabor-precompile && $(CXX)
mutabor_CPPFLAGS = $(WX_CPPFLAGS) 
mutabor_CFLAGS += @COND_PRECOMP_C_TRUE@-include mutabor-precompiled.h
mutabor_CXXFLAGS += @COND_PRECOMP_CXX_TRUE@-include mutabor-cxxprecompiled.h

@AMDEP_TRUE@@am__include@ @am__quote@./$(DEPDIR)/mutabor-cxxprecompiled.Po@am__quote@

.PHONY: cvs_dist cvs_distcheck mutabor-cxxprecompiled

.h.$(PCHEXT_CXX):
@am__fastdepCXX_TRUE@	if $(CXXCOMPILE) $(mutabor_CPPFLAGS) $(mutabor_CallFLAGS) -MT $@ -MD -MP -MF "$(DEPDIR)/$*.Tpo" -o $@ -c `test -f '$<' || echo '$(srcdir)/'`$<; \
@am__fastdepCXX_TRUE@	then mv -f "$(DEPDIR)/$*.Tpo" "$(DEPDIR)/$*.Po"; else rm -f "$(DEPDIR)/$*.Tpo"; exit 1; fi 
@AMDEP_TRUE@@am__fastdepCXX_FALSE@	source='$<' object='$@' libtool=no @AMDEPBACKSLASH@
@AMDEP_TRUE@@am__fastdepCXX_FALSE@	DEPDIR=$(DEPDIR) $(CXXDEPMODE) $(depcomp) @AMDEPBACKSLASH@
@am__fastdepCXX_FALSE@	$(CXX) $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(mutabor_CPPFLAGS) $(CPPFLAGS) $(mutabor_CallFLAGS) $(CXXFLAGS) -c  `test -f '$<' || echo '$(srcdir)/'`$<

.cpp.o:
@am__fastdepCXX_TRUE@	if $(CXXCOMPILE) -MT $@ -MD -MP -MF "$(DEPDIR)/$*.Tpo" -c -o $@ $<; \
@am__fastdepCXX_TRUE@	then mv -f "$(DEPDIR)/$*.Tpo" "$(DEPDIR)/$*.Po"; else rm -f "$(DEPDIR)/$*.Tpo"; exit 1; fi
@AMDEP_TRUE@@am__fastdepCXX_FALSE@	source='$<' object='$@' libtool=no @AMDEPBACKSLASH@
@AMDEP_TRUE@@am__fastdepCXX_FALSE@	DEPDIR=$(DEPDIR) $(CXXDEPMODE) $(depcomp) @AMDEPBACKSLASH@
@am__fastdepCXX_FALSE@	$(CXXCOMPILE) -c -o $@ $<

.cpp.obj:
#@COND_PRECOMP_C_TRUE@	$(MAKE) $(AM_MAKEFLAGS) mutabor-cxxprecompiled.$(PCHEXT_CXX)
@am__fastdepCXX_TRUE@	if $(CXXCOMPILE) -MT $@ -MD -MP -MF "$(DEPDIR)/$*.Tpo" -c -o $@ `$(CYGPATH_W) '$<'`; \
@am__fastdepCXX_TRUE@	then mv -f "$(DEPDIR)/$*.Tpo" "$(DEPDIR)/$*.Po"; else rm -f "$(DEPDIR)/$*.Tpo"; exit 1; fi
@AMDEP_TRUE@@am__fastdepCXX_FALSE@	source='$<' object='$@' libtool=no @AMDEPBACKSLASH@
@AMDEP_TRUE@@am__fastdepCXX_FALSE@	DEPDIR=$(DEPDIR) $(CXXDEPMODE) $(depcomp) @AMDEPBACKSLASH@
@am__fastdepCXX_FALSE@	$(CXXCOMPILE) -c -o $@ `$(CYGPATH_W) '$<'`

.cpp.lo:
#@COND_PRECOMP_C_TRUE@	$(MAKE) $(AM_MAKEFLAGS) mutabor-cxxprecompiled.$(PCHEXT_CXX)
@am__fastdepCXX_TRUE@	if $(LTCXXCOMPILE) -MT $@ -MD -MP -MF "$(DEPDIR)/$*.Tpo" -c -o $@ $<; \
@am__fastdepCXX_TRUE@	then mv -f "$(DEPDIR)/$*.Tpo" "$(DEPDIR)/$*.Plo"; else rm -f "$(DEPDIR)/$*.Tpo"; exit 1; fi
@AMDEP_TRUE@@am__fastdepCXX_FALSE@	source='$<' object='$@' libtool=yes @AMDEPBACKSLASH@
@AMDEP_TRUE@@am__fastdepCXX_FALSE@	DEPDIR=$(DEPDIR) $(CXXDEPMODE) $(depcomp) @AMDEPBACKSLASH@
@am__fastdepCXX_FALSE@	$(LTCXXCOMPILE) -c -o $@ $<

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

#@COND_PRECOMP_CXX_TRUE@  $(mutabor_OBJECTS) mutabor-cxxprecompile: mutabor-cxxprecompile

mutabor-cxxprecompiled.h:
@COND_PRECOMP_CXX_TRUE@	echo '#define PRECOMPILE 1' >$@
@COND_PRECOMP_CXX_TRUE@	echo '#ifdef HAVE_CONFIG_H' >>$@
@COND_PRECOMP_CXX_TRUE@	echo '#include "config.h"' >>$@
@COND_PRECOMP_CXX_TRUE@	echo '#endif' >>$@
@COND_PRECOMP_CXX_TRUE@	ls $(mutabor_SOURCES) | \
@COND_PRECOMP_CXX_TRUE@		sed '/\.r\?h$$/ ! d ; s/^\(.*\)$$/#include "\1"/' >>$@
@COND_PRECOMP_CXX_TRUE@	echo '#undef PRECOMPILE' >>$@


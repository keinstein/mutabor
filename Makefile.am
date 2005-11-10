distdir = $(PACKAGE_TARNAME)-$(VERSION)
SUBDIRS = includes libmutabor .
INCLUDES = -I $(srcdir)/mu32  -I $(srcdir)/muwx -I $(srcdir)/rtmidi -I $(srcdir)/mywx
CVS = cvs
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
		mu32/Hilfs.h mywx/mxDefs.h \
		mu32/Interval.h mu32/Mut_Tab.h mu32/Parser.h mu32/Runtime.h \
		mu32/TabGen.h rtmidi/RtMidi.h muwx/MutApp.h muwx/MutChild.h \
		muwx/MutEditFile.h muwx/MutFrame.h muwx/MutLogicWnd.h \
		muwx/OutputDevDlg.h \
		muwx/MutRouteWnd.h muwx/MutTextBox.h muwx/CompDlg.h muwx/Action.h \
		muwx/InputDevDlg.h mu32/DevGIS.h mu32/Device.h mu32/DevMidF.h \
		mu32/DevMidi.h mu32/EDevice.h mu32/Errors.h mu32/Execute.h \
		mu32/Frac.h mu32/GrafKern.h mywx/valNum.h mu32/GIS_Head.h mu32/GIS.h \
		mu32/GSP_Err.h mu32/GSP_File.h mu32/GSP.h muwx/InputFilterDlg.h \
		muwx/BoxDlg.h muwx/OutputFilterDlg.h mywx/valRadio.h 
mutabor_LDFLAGS = $(ALSA_LIBS) $(WX_LIBS)
mutabor_CFLAGS = $(ALSA_CFLAGS) $(WX_CFLAGS)
mutabor_CXXFLAGS = $(ALSA_CFLAGS) $(WX_CXXFLAGS)
mutabor_CPPFLAGS = $(WX_CPPFLAGS)

.PHONY: cvs_dist cvs_distcheck

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
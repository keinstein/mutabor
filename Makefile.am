SUBDIRS=includes libmutabor .
INCLUDES = -I $(srcdir)/mu32  -I $(srcdir)/muwx -I $(srcdir)/rtmidi -I $(srcdir)/mywx
bin_PROGRAMS = mutabor

mutabor_SOURCES = mu32/Hilfs.cpp \
		mu32/Interval.cpp mu32/Mut_Tab.cpp mu32/Parser.cpp mu32/Runtime.cpp \
		mu32/TabGen.cpp rtmidi/RtMidi.cpp muwx/MutApp.cpp muwx/MutChild.cpp \
		muwx/MutEditFile.cpp muwx/MutFrame.cpp muwx/MutLogicWnd.cpp \
		muwx/OutputDevDlg.cpp \
		muwx/MutRouteWnd.cpp muwx/MutTextBox.cpp muwx/CompDlg.cpp muwx/Action.cpp \
		muwx/InputDevDlg.cpp mu32/DevGIS.cpp mu32/Device.cpp mu32/DevMidF.cpp \
		mu32/DevMidi.cpp mu32/EDevice.cpp mu32/Errors.cpp mu32/Execute.cpp \
		mu32/Frac.cpp mu32/GrafKern.cpp mywx/valNum.cpp mu32/GIS_Head.cpp mu32/GIS.cpp \
		mu32/GSP_Err.cpp mu32/GSP_File.cpp mu32/GSP.cpp
mutabor_LDFLAGS = $(ALSA_LIBS) $(WX_LIBS)
mutabor_CFLAGS = $(ALSA_CFLAGS) $(WX_CFLAGS)
mutabor_CXXFLAGS = $(ALSA_CFLAGS) $(WX_CXXFLAGS)
mutabor_CPPFLAGS = $(WX_CPPFLAGS)
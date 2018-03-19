ACLOCAL_AMFLAGS = -I m4 -I lib/rtmidi/m4 --install
#AUTOMAKE_OPTIONS = dejagnu
# intl must be before any source directories

SUBDIRS = po lib . doc  #libmutabor . #intl
#DIST_SUBDIRS = $(SUBDIRS)
precompCOMPILESOURCES=$(mutabor_COMPILESOURCES)

RCCOMPILE = $(RC) $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(CPPFLAGS) $(RCFLAGS)
CVS = cvs
GIT = git
REPOSITORY = http://git.berlios.de/mutabor
REPOSITORY_PATH = .
AM_LFLAGS = --c++
AM_CFLAGS =
DLLPROGRAMS = $(TESTS) $(noinst_PROGRAMS) $(bin_PROGRAMS)
#-o lex.yy.c

noinst_LIBRARIES =
noinst_LTLIBRARIES =
lib_LTLIBRARIES =
check_LIBRARIES =

bin_PROGRAMS =
noinst_PROGRAMS =
check_PROGRAMS =

CLEANFILES =

EXTRA_DIST =
TEST_EXTENSIONS =
TESTS =
NOCOMPSOURCES =

dist_pkgdata_DATA =

EXTRA_RTMIDITESTLDFLAGS = \
	$(WXINTLLDFLAGS) \
	$(WXINTLLDADD)
EXTRA_RTMIDITESTCXXFLAGS = \
	$(AM_CXXFLAGS) \
	$(WXINTLCXXFLAGS) \
	"-DLOCALEDIR=\"$(LOCALEDIR)\""

RTMIDICONFIGRPATH =


include common-rules.mk
include %D%/src/Makefile.am
include %D%/Images/Makefile.am
include %D%/lib/rtmidi/Makefile.library
include %D%/tools/midi2text/Makefile.am


lib_rtmidi_librtmidi@rtmidi_suffix@_la_CXXFLAGS += \
	$(WXINTLCXXFLAGS) \
	"-DLOCALEDIR=\"$(LOCALEDIR)\""
lib_rtmidi_librtmidi@rtmidi_suffix@_la_LDFLAGS  += \
	$(WXINTLLDFLAGS) \
	$(WXINTLLDADD)




lib/rtmidi/librtmidi@rtmidi_suffix@.a:lib/rtmidi/librtmidi@rtmidi_suffix.la
lib_rtmidi_librtmidi@rtmidi_suffix@_la_DEPENDENCIES  = $(WXBUILDDEPENDS)

NOCOMPSOURCES += \
	src/xrc/wxresource.cpp \
	src/xrc/wxresource.h \
	src/xrc/reslocale.cpp


BUILT_SOURCES += $(NOCOMPSOURCES)


EXTRA_DIST += config.rpath \
	README.md \
	m4/ChangeLog  \
	debian \
	lib/libasprintf \
	Images \
	src/kernel/parsers/scala/scale_parser.yy \
	src/kernel/parsers/scala/scale_lexer.ll \
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
	Examples/english/tutorial.mut \
	Examples/german/Cdur.mut \
	Examples/german/Cohen.mut \
	Examples/german/Demo.mut \
	Examples/german/Demos.mut \
	Examples/german/Demo-utf8.mut \
	Examples/german/Extern.mut \
	Examples/german/Instr.mut \
	Examples/german/Midi.mut \
	Examples/german/Nix.mut \
	lib/includes/flex/FlexLexer.h \
	$(NOCOMPSOURCES)

# Please use Tango names for new files
# http://tango.freedesktop.org/Tango_Desktop_Project
dist_pkgdata_DATA += src/xrc/Mutabor.xrc \
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
	Images/Icons/png/help-browser.png \
	Images/Icons/png/ToolbarLogicActive.png
#RECURSIVE_TARGETS += mac-recursive


bin_PROGRAMS += mutabor scl2mut
noinst_LIBRARIES += \
	libmutaborgui.a \
	libmutaborrouting.a \
	libmutaborscala.a \
	libmutabordebug.a  #libmutaborGUIrouting.a libmutaborGUI.a
check_LIBRARIES += \
	libmutabordebugtest.a \
	libmutabormaintest.a

if HAVE_CPPUNIT
check_LIBRARIES += \
	libmutabordebugcppunit.a \
	libmutabormaincppunit.a
endif

#-------------------------------------------------------------
# libmutaborgui.a
#-------------------------------------------------------------

libmutaborgui_a_INLINEHEADERS = \
		src/wxGUI/GUIBoxData-inlines.h \
		src/wxGUI/Routing/GUIRoute-inlines.h


 libmutaborgui_a_INDENTHEADERS = \
		src/wxGUI/Routing/BoxChannelShape.h \
		src/wxGUI/Routing/BoxDlg.h \
		src/wxGUI/Routing/BoxIconShape.h \
		src/wxGUI/Routing/BoxShape.h \
		src/wxGUI/Routing/DebugRoute.h \
		src/wxGUI/Routing/DeviceShape.h \
		src/wxGUI/Routing/GUIRoute.h \
		src/wxGUI/Routing/InputDevDlg.h \
		src/wxGUI/Routing/InputGuidoFileDeviceShape.h \
		src/wxGUI/Routing/InputMidiDeviceShape.h \
		src/wxGUI/Routing/InputMidiFileDeviceShape.h \
		src/wxGUI/Routing/NewBoxShape.h \
		src/wxGUI/Routing/NewInputDeviceShape.h \
		src/wxGUI/Routing/NewOutputDeviceShape.h \
		src/wxGUI/Routing/OutputDevDlg.h \
		src/wxGUI/Routing/OutputGuidoFileDeviceShape.h \
		src/wxGUI/Routing/OutputMidiDeviceShape.h \
		src/wxGUI/Routing/OutputMidiFileDeviceShape.h \
		src/wxGUI/Routing/RouteIcons.h \
		src/wxGUI/Routing/RouteLists.h \
		src/wxGUI/ScalaGUI.h \
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
		src/wxGUI/StatusBar.h \
		src/wxGUI/resourceload.h \
		src/wxGUI/stclanguage.h \
		src/wxGUI/xmltree.h \
		src/wxGUI/generic/mhArray.h \
		src/wxGUI/generic/mhDefs.h \
		src/wxGUI/generic/muconvauto.h \
		src/wxGUI/generic/valNum.h \
		src/wxGUI/generic/valRadio.h

libmutaborgui_a_INDENTS = \
		src/wxGUI/Routing/BoxChannelShape.cpp \
		src/wxGUI/Routing/BoxDlg.cpp \
		src/wxGUI/Routing/BoxIconShape.cpp \
		src/wxGUI/Routing/BoxShape.cpp \
		src/wxGUI/Routing/DebugRoute.cpp \
		src/wxGUI/Routing/DeviceShape.cpp \
		src/wxGUI/Routing/GUIRoute.cpp \
		src/wxGUI/Routing/InputDevDlg.cpp \
		src/wxGUI/Routing/InputGuidoFileDeviceShape.cpp \
		src/wxGUI/Routing/InputMidiDeviceShape.cpp \
		src/wxGUI/Routing/InputMidiFileDeviceShape.cpp \
		src/wxGUI/Routing/NewBoxShape.cpp \
		src/wxGUI/Routing/NewInputDeviceShape.cpp \
		src/wxGUI/Routing/NewOutputDeviceShape.cpp \
		src/wxGUI/Routing/OutputDevDlg.cpp \
		src/wxGUI/Routing/OutputGuidoFileDeviceShape.cpp \
		src/wxGUI/Routing/OutputMidiDeviceShape.cpp \
		src/wxGUI/Routing/OutputMidiFileDeviceShape.cpp \
		src/wxGUI/Routing/RouteIcons.cpp \
		src/wxGUI/GUIBoxData.cpp \
		src/wxGUI/MutBitmaps.cpp \
		src/wxGUI/CompDlg.cpp \
		src/wxGUI/configtree.cpp \
		src/wxGUI/IconShape.cpp \
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
		src/wxGUI/StatusBar.cpp \
		src/wxGUI/stclanguage.cpp \
		src/wxGUI/xmltree.cpp \
		src/wxGUI/generic/muconvauto.cpp \
		src/wxGUI/generic/mxDefs.cpp \
		src/wxGUI/generic/valNum.cpp \
		src/wxGUI/generic/valRadio.cpp

noinst_HEADERS += $(libmutaborgui_a_INLINEHEADERS) $(libmutaborgui_a_INDENTHEADERS)

libmutaborgui_a_POTSOURCES = $(libmutaborgui_a_INLINEHEADERS) $(libmutaborgui_a_INDENTHEADERS) $(libmutaborgui_a_INDENTS)

libmutaborgui_a_SOURCES = $(libmutaborgui_a_INDENTS)

libmutaborgui_a_CXXFLAGS = $(WXINTLCXXFLAGS) $(AM_CXXFLAGS) $(BOOST_CPPFLAGS)


#-------------------------------------------------------------
# libmutaborrouting.a
#-------------------------------------------------------------

libmutaborrouting_a_INLINEHEADERS = \
		src/kernel/routing/CommonFileDevice-inlines.h \
		src/kernel/routing/Device-inlines.h \
		src/kernel/routing/Route-inlines.h \
		src/kernel/routing/Box-inlines.h


libmutaborrouting_a_INDENTHEADERS = \
		src/kernel/boost-interface.h \
		src/kernel/routing/gmn/DevGIS.h \
		src/kernel/routing/gmn/GIS_Head.h \
		src/kernel/routing/gmn/GIS.h \
		src/kernel/routing/gmn/GSP_File.h \
		src/kernel/routing/gmn/GSP.h \
		src/kernel/routing/midi/DevMidF.h \
		src/kernel/routing/midi/DevMidi.h \
		src/kernel/routing/midi/midicmn.h \
		src/kernel/routing/midi/midicmn-inlines.h \
		src/kernel/routing/midi/midicmn.cpp \
		src/kernel/routing/CommonFileDevice.h \
		src/kernel/routing/Device.h \
		src/kernel/routing/Route.h \
		src/kernel/routing/Box.h \
		src/kernel/routing/box_support.h \
		src/kernel/routing/event.h \
		src/kernel/routing/RouteCompat.h \
		src/kernel/routing/timing.h \
		src/kernel/routing/thread.h \
		src/kernel/routing/watchdog.h

libmutaborrouting_a_INDENTS = \
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
		src/kernel/routing/Box.cpp \
		src/kernel/routing/RouteCompat.cpp \
		src/kernel/routing/timing.cpp

noinst_HEADERS += $(libmutaborrouting_a_INLINEHEADERS) $(libmutaborrouting_a_INDENTHEADERS)

libmutaborrouting_a_POTSOURCES = $(libmutaborrouting_a_INLINEHEADERS) $(libmutaborrouting_a_INDENTHEADERS) $(libmutaborrouting_a_INDENTS)

libmutaborrouting_a_SOURCES = $(libmutaborrouting_a_INDENTS)

libmutaborrouting_a_CXXFLAGS = $(WXINTLCXXFLAGS) $(AM_CXXFLAGS) $(BOOST_CPPFLAGS)

#-------------------------------------------------------------
# libmutaborscala.a
#-------------------------------------------------------------

libmutaborscala_a_INLINEHEADERS = \
		src/kernel/parsers/scala/scale_parser.cc \
		src/kernel/parsers/scala/scale_parser.hh \
		src/kernel/parsers/scala/position.hh \
		src/kernel/parsers/scala/location.hh \
		src/kernel/parsers/scala/stack.hh \
		src/kernel/parsers/scala/scale_lexer.cc \
		src/kernel/parsers/scala/scala-inlines.h

EXTRA_DIST += $(libmutaborscala_a_INLINEHEADERS)

libmutaborscala_a_INDENTHEADERS = \
		src/kernel/parsers/scala/scala.h \
		src/kernel/parsers/scala/scale_lexer.h


libmutaborscala_a_INDENTS = \
		src/kernel/parsers/scala/scala.cpp

noinst_HEADERS += $(libmutaborscala_a_INLINEHEADERS) $(libmutaborscala_a_INDENTHEADERS)

libmutaborscala_a_POTSOURCES = $(libmutaborscala_a_INLINEHEADERS) $(libmutaborscala_a_INDENTHEADERS) $(libmutaborscala_a_INDENTS)

libmutaborscala_a_SOURCES = $(libmutaborscala_a_INDENTS) \
			$(libmutaborscala_a_INDENTHEADERS) \
			src/kernel/parsers/scala/scale_parser.yy \
			src/kernel/parsers/scala/scale_lexer.ll


#-------------------------------------------------------------
# libmutabordebug.a
#-------------------------------------------------------------

libmutabordebug_a_INLINEHEADERS = \
		src/kernel/debugFlags.h
libmutabordebug_a_INDENTHEADERS = \
		src/wxGUI/generic/mutDebug.h
libmutabordebug_a_INDENTS = \
		src/wxGUI/interface_deps_wxWidgets.cpp \
		src/wxGUI/generic/mutDebug.cpp

noinst_HEADERS += $(libmutabordebug_a_INLINEHEADERS) $(libmutabordebug_a_INDENTHEADERS)

libmutabordebug_a_POTSOURCES = \
	$(libmutabordebug_a_INLINEHEADERS) \
	$(libmutabordebug_a_INDENTHEADERS) \
	$(libmutabordebug_a_INDENTS) \
	src/wxGUI/TestInitializer.h

libmutabordebug_a_SOURCES = $(libmutabordebug_a_INDENTS)
libmutabordebug_a_CXXFLAGS = $(WXINTLCXXFLAGS) $(AM_CXXFLAGS) $(BOOST_CPPFLAGS)


if HAVE_CPPUNIT
#-------------------------------------------------------------
# libmutabordebugcppunit.a
#-------------------------------------------------------------
libmutabordebugcppunit_a_INLINEHEADERS = \
		$(libmutabordebug_a_INLINEHEADERS)
libmutabordebugcppunit_a_INDENTHEADERS = \
		$(libmutabordebug_a_INDENTHEADERS)
libmutabordebugcppunit_a_INDENTS = \
		$(libmutabordebug_a_INDENTS)

# no noinst_HEADERS or POTSOURCES needed as we are using common files declared elsewhere

libmutabordebugcppunit_a_SOURCES = $(libmutabordebugcppunit_a_INDENTS)
libmutabordebugcppunit_a_CXXFLAGS = $(WXINTLCXXFLAGS) $(AM_CXXFLAGS) $(CPPUNIT_CFLAGS) -DMUTABOR_TEST  $(BOOST_CPPFLAGS)

#-------------------------------------------------------------
# libmutabordebugcppunit.a
#-------------------------------------------------------------

libmutabormaincppunit_a_INLINEHEADERS =
libmutabormaincppunit_a_INDENTHEADERS = \
		src/wxGUI/MutApp.h \
		src/wxGUI/TestInitializer.h
libmutabormaincppunit_a_INDENTS = \
		src/kernel/interface_deps_cppunit.cpp \
		src/wxGUI/MutApp.cpp \
		src/wxGUI/TestInitializer.cpp

# no noinst_HEADERS or POTSOURCES needed as we are using common files declared elsewhere

libmutabormaincppunit_a_SOURCES = $(libmutabormaincppunit_a_INDENTS)
libmutabormaincppunit_a_CXXFLAGS = $(WXINTLCXXFLAGS) $(AM_CXXFLAGS) $(CPPUNIT_CFLAGS) -DMUTABOR_TEST \
					"-DSRCDIR=\"$(srcdir)\""  $(BOOST_CPPFLAGS)
libmutabormaincppunit_a_LIBADD = $(libmutaborgui_a_OBJECTS) \
				$(libmutaborrouting_a_OBJECTS) \
				$(src_kernel_libmutaborkernel_a_OBJECTS) \
				$(libmutaborscala_a_OBJECTS) \
				$(libmutabordebugcppunit_a_OBJECTS) \
				lib/rtmidi/librtmidi@rtmidi_suffix@.la

libmutabormaincppunit_a_DEPENDENCIES = $(libmutabormaincppunit_a_LIBADD)

noinst_HEADERS += $(libmutabormaincppunit_a_INDENTHEADERS)
endif

#-------------------------------------------------------------
# libmutabordebugtest.a
#-------------------------------------------------------------

libmutabordebugtest_a_INLINEHEADERS = \
		$(libmutabordebug_a_INLINEHEADERS)
libmutabordebugtest_a_INDENTHEADERS = \
		$(libmutabordebug_a_INDENTHEADERS) \
		src/wxGUI/MutApp.h \
		src/wxGUI/TestInitializer.h

libmutabordebugtest_a_INDENTS = \
		$(libmutabordebug_a_INDENTS) \
		src/kernel/interface_deps_generic.cpp \
		src/wxGUI/MutApp.cpp \
		src/wxGUI/TestInitializer.cpp


# no noinst_HEADERS or POTSOURCES needed as we are using common files declared elsewhere

libmutabordebugtest_a_SOURCES = $(libmutabordebugtest_a_INDENTS)
libmutabordebugtest_a_CXXFLAGS = $(WXINTLCXXFLAGS) $(AM_CXXFLAGS) -DMUTABOR_TEST  $(BOOST_CPPFLAGS)


#-------------------------------------------------------------
# libmutabormaintest.a
#-------------------------------------------------------------

libmutabormaintest_a_INLINEHEADERS =
libmutabormaintest_a_INDENTHEADERS = \
		src/wxGUI/MutApp.h \
		src/wxGUI/TestInitializer.h
libmutabormaintest_a_INDENTS = \
		src/kernel/interface_deps_generic.cpp \
		src/wxGUI/MutApp.cpp \
		src/wxGUI/TestInitializer.cpp

# no noinst_HEADERS or POTSOURCES needed as we are using common files declared elsewhere

libmutabormaintest_a_SOURCES = $(libmutabormaintest_a_INDENTS)
libmutabormaintest_a_CXXFLAGS = $(WXINTLCXXFLAGS) $(AM_CXXFLAGS) $(TEST_CFLAGS) -DMUTABOR_TEST $(BOOST_CPPFLAGS)
libmutabormaintest_a_LIBADD = $(libmutaborgui_a_OBJECTS) \
				$(libmutaborrouting_a_OBJECTS) \
				$(src_kernel_libmutaborkernel_a_OBJECTS) \
				$(libmutaborscala_a_OBJECTS) \
				$(libmutabordebugtest_a_OBJECTS) \
				lib/rtmidi/librtmidi@rtmidi_suffix@.la

libmutabormaintest_a_DEPENDENCIES = $(libmutabormaintest_a_LIBADD)

#-------------------------------------------------------------
# librtmidi@rtmidi_suffix@.la
#-------------------------------------------------------------

CLEANFILES += lib/rtmidi/*.class

rtmidi_INLINEHEADERS = \
	lib/rtmidi/RtMidi.h

rtmidi_INDENTHEADERS =
rtmidi_INDENTS = $(lib_rtmdidi_librtmidi@rtmidi_suffix@_la_SOURCES)

noinst_HEADERS += $(rtmidi_INLINEHEADERS)

librtmidi@rtmidi_suffix@_la_POTSOURCES = $(lib_rtmidi_librtmidi@rtmidi_suffix@_la_SOURCES)

#-------------------------------------------------------------
# Other files
#-------------------------------------------------------------

INLINEHEADERS = \
		$(libmutaborrouting_a_INLINEHEADERS) \
		$(src_kernel_libmutaborkernel_a_INLINEHEADERS) \
		$(libmutaborscala_a_INLINEHEADERS) \
		$(libmutabordebug_a_INLINEHEADERS) \
		$(librtmidi@rtmidi_suffix@_la_INLINEHEADERS) \
		$(libmutaborgui_a_INLINEHEADERS)

INDENTHEADERS = \
		$(libmutaborrouting_a_INDENTHEADERS) \
		$(src_kernel_libmutaborkernel_a_INDENTHEADERS) \
		$(libmutaborscala_a_INDENTHEADERS) \
		$(libmutabordebug_a_INDENTHEADERS) \
		$(libmutaborgui_a_INDENTHEADERS)

mutabor_INDENTS = \
		src/wxGUI/MutApp.cpp

#		src/wxGUI/InputFilterDlg.cpp \
#		src/wxGUI/InputFilterDlg.h \
#		src/wxGUI/OutputFilterDlg.cpp \
#		src/wxGUI/OutputFilterDlg.h \
#

INDENTSOURCES = \
	$(mutabor_INDENTS) \
	$(libmutaborrouting_a_INDENTS) \
	$(src_kernel_libmutaborkernel_a_INDENTS) \
	$(libmutaborscala_a_INDENTS) \
	$(librtmidi@rtmidi_suffix@_la_INDENTS) \
	$(libmutabordebug_a_INDENTS) \
	$(libmutaborgui_a_INDENTS)



mutabor_COMPILESOURCES = $(mutabor_INDENTS)

mutabor_SOURCES = $(mutabor_COMPILESOURCES)

POTSOURCES += $(INDENTSOURCES) \
	$(noinst_HEADERS) \
	$(mutabor_COMPILESOURCES) \
	$(scl2mut_POTSOURCES) \
	$(NOCOMPSOURCES) \
	$(libmutaborrouting_a_POTSOURCES) \
	$(libmutaborscala_a_POTSOURCES) \
	$(librtmidi@rtmidi_suffix@_la_POTSOURCES) \
	$(libmutabordebug_a_POTSOURCES) \
	$(libmutaborgui_a_POTSOURCES)

if COND_WINRC
mutabor_COMPILESOURCES += src/wxGUI/Mutabor.rc
endif

mutabor_CXXFLAGS=$(WXINTLCXXFLAGS) $(AM_CXXFLAGS) $(BOOST_CPPFLAGS)
mutabor_CXXLD=$(CXX)
mutabor_SHORTNAME = mutabor
mutabor_LDADD = \
	libmutaborgui.a \
	libmutaborrouting.a \
	src/kernel/libmutaborkernel.a \
	libmutaborscala.a \
	libmutabordebug.a \
	lib/rtmidi/librtmidi@rtmidi_suffix@.la \
	$(WXINTLLDADD) \
	$(LDADD) \
	$(AM_LDFLAGS) \
	$(BOOST_LDFLAGS) \
	$(BOOST_FILESYSTEM_LIB) \
	$(BOOST_SYSTEM_LIB)

if COND_WINRC
CLEANFILES +=  $(mutabor_SHORTNAME)-Mutabor-winrc.$(OBJEXT)
BUILT_SOURCES +=  $(mutabor_SHORTNAME)-Mutabor-winrc.$(OBJEXT)
mutabor_LDADD += $(mutabor_SHORTNAME)-Mutabor-winrc.$(OBJEXT)
mutabor.$(EXEEXT):$(mutabor_SHORTNAME)-Mutabor-winrc.$(OBJEXT)
$(mutabor_SHORTNAME)-Mutabor-winrc.$(OBJEXT):$(srcdir)/src/wxGUI/Mutabor.rc
	$(RCCOMPILE) $< $@
else
$(mutabor_SHORTNAME)-Mutabor-winrc.$(OBJEXT):$(srcdir)/src/wxGUI/Mutabor.rc
endif

scl2mut_SOURCES = \
	src/gmut/scl2mut.cpp \
	src/wxintl/libintl_boost.cpp

scl2mut_POTSOURCES = $(scl2mut_SOURCES)

scl2mut_LDADD = \
	libmutaborscala.a \
	$(BOOST_LDFLAGS) \
	$(BOOST_PROGRAM_OPTIONS_LIB) \
	$(BOOST_LOCALE_LIB) \
	$(BOOST_FILESYSTEM_LIB) \
	$(BOOST_SYSTEM_LIB)

if COND_PRECOMP_C
#AM_CFLAGS += -include mutabor-precompiled.h # -fpch-deps
endif

if COND_PRECOMP_CXX
AM_CXXFLAGS += -include mutabor-cxxprecompiled.h # -fpch-deps
BUILT_SOURCES += mutabor-cxxprecompiled.$(PCHEXT_CXX)
nodist_mutabor_SOURCES = mutabor-cxxprecompiled.$(PCHEXT_CXX)

if AMDEP
@am__include@ @am__quote@./$(DEPDIR)/mutabor-cxxprecompiled.Po@am__quote@
endif
endif



.PHONY: cvs_dist cvs_distcheck \
	fixdependencies generated_headers


src/wxGUI/resourceload.h:$(top_srcdir)/src/xrc/wxresource.h

cvs_dist: Makefile.am
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

cvs_distcheck: Makefile.am
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



#if COND_WINRC
#$(mutabor_SHORTNAME)-Mutabor.$(OBJEXT):$(top_srcdir)/src/wxGUI/Mutabor.rc
#	$(RCCOMPILE) $< $@
#endif






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
	cp $(top_srcdir)/Images/Icons/icns/Mutabor.icns dmg/Mutabor/.VolumeIcon.icns
	ln -s /Applications dmg/Mutabor
	cp -r $(top_srcdir)/Examples dmg/Mutabor
	rm -f "$(PACKAGE_NAME)-$(PACKAGE_VERSION).dmg"
	hdiutil create -srcfolder dmg/Mutabor -volname "$(PACKAGE_NAME)" "$(PACKAGE_NAME)-$(PACKAGE_VERSION)"
	rm -r dmg/Mutabor


Mutabor.appold:all Mutabor.xrc mutabor update-gmo
	$(MKDIR_P) Mutabor.app/Contents/MacOS
	$(MKDIR_P) Mutabor.app/Contents/Resources
	cp mutabor Mutabor.app/Contents/MacOS
	cp osdep/macosx/Info.plist Mutabor.app/Contents
	cp $(top_srcdir)/Images/Icons/icns/Mutabor.icns Mutabor.app/Contents/Resources/Mutabor.icns
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
	$(MAKE) "prefix=`pwd`/Mutabor.app/Contents" \
		'bindir=$$(prefix)/MacOS' \
		'datarootdir=$$(prefix)/Resources' \
		'libdir=$$(prefix)' \
		'libexecdir=$$(prefix)/libs' \
		'localedir=$$(prefix)/locales' \
		'pkgdatadir=$$(prefix)/Resources' \
		'mutabordir=$$(prefix)' \
		install installwxlocale
	ls Mutabor.app/Contents/locales/*/LC_MESSAGES/*.mo | \
	while read file ; do \
		lang=`echo $$file | sed -e 's,.*/\([^/]*\)/LC_MESSAGES/.*\.mo,\1,g'` ; echo $$lang ;\
		mkdir -p Mutabor.app/Contents/Resources/$$lang.lproj ; \
		mv $$file Mutabor.app/Contents/Resources/$$lang.lproj ; \
	done
	rm -rf Mutabor.app/Contents/locales
	cp osdep/macosx/Info.plist Mutabor.app/Contents
	cp $(top_srcdir)/Images/Icons/icns/Mutabor.icns Mutabor.app/Contents/Resources/Mutabor.icns
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

wx_locale_pattern=$(localedir)/$$lang/LC_MESSAGES/wxstd.mo
if WX_INPLACE
installwxlocale:
	echo inplace
	test -z "$(WX_LOCALE_DIRS)" || { for dir in  $(WX_LOCALE_DIRS) ; \
	do \
		(cd "$$dir" && make allmo) ; \
		ls "$$dir"/*.mo | \
		while read file ; do \
			echo \|$$file\| ; \
			lang=`echo $$file | sed -e 's,^\(.*/\)\([^/]*\)\.mo$$,\2,g'` ; echo $$lang ;\
			mkdir -p "`dirname $(wx_locale_pattern)`" ; \
			cp $$file "$(wx_locale_pattern)" ; \
		done ; \
	done }
else
installwxlocale:
	echo installed
	test -z "$(WX_LOCALE_DIRS)" || { for dir in  $(WX_LOCALE_DIRS) ; \
	do \
		ls "$$dir"/*/LC_MESSAGES/wxstd.mo | \
		while read file ; do \
			lang=`echo $$file | sed -e 's,.*/\([^/]*\)/LC_MESSAGES/wxstd.mo,\1,g'` ; echo $$lang ;\
			mkdir -p "`dirname $(wx_locale_pattern)`" ; \
			cp $$file "$(wx_locale_pattern)" ; \
		done ; \
	done }
endif

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
	for d in mutabor.exe scl2mut.exe ; \
	do \
		$(MAKE) DLLLINKFILE="$$d" DLLEXEDIR="`pwd`/Mutabor" installdll ; \
	done
	for d in Mutabor/*.exe Mutabor/*.dll ; \
	do \
		$(STRIP) --only-keep-debug "$$d" -o "$$d.dbg" ; \
		$(STRIP) --strip-debug "$$d" ; \
		echo 'not running $(STRIP) --add-gnu-debuglink='"$$d.dbg" "$$d" ; \
	done
	for d in GPL-2 LGPL-2.1 ChangeLog; do \
		cp $(top_srcdir)/$$d Mutabor/$$d.txt ; \
	done
	cp -r $(top_srcdir)/Examples Mutabor


#-------------------------------------------------------------------------------------
# Certain fixed files
#-------------------------------------------------------------------------------------


if COPYDLLS
check-am: check-dll

check-dll: all-am
	$(MAKE) $(AM_MAKEFLAGS) $(check_PROGRAMS)
	$(MAKE) $(AM_MAKEFLAGS)	linkchecks

linkchecks:
	for d in `echo $(DLLPROGRAMS)| tr ' ' '\n' | grep -i -e '$(EXEEXT)$$'` ; \
	do \
		ls -l "$$d" ; \
		file=`basename "$$d"` ; \
		dir=`dirname "$$d"` ; \
		$(MAKE) $(AM_MAKEFLAGS) DLLLINKFILE="$$file" DLLEXEDIR="$$dir" installdll ; \
		test -f "$$dir/.libs/$$file" && \
			$(MAKE) $(AM_MAKEFLAGS) DLLLINKFILE="$$file" DLLEXEDIR="$$dir/.libs" installdll ; \
	done
endif


if MAINTAINER_MODE
Mutabor.nsi: $(top_srcdir)/osdep/win/Mutabor.nsi
$(top_srcdir)/osdep/win/Mutabor.nsi: $(top_srcdir)/osdep/win/Mutabor.nsi.in \
	$(top_builddir)/config.status
	cd $(top_builddir) ; ./config.status osdep/win/Mutabor.nsi
	test -f "$@" && cmp -s $(top_builddir)/osdep/win/Mutabor.nsi "$@" || cp $(top_builddir)/osdep/win/Mutabor.nsi "$@"
endif



nsis: installwin $(top_srcdir)/osdep/win/Mutabor.nsi
	rm -f mutabor-files.nsh
	rm -f mutabor-dirs.nsh
	rm -f mutabor-uninst-files.nsh
	cd Mutabor && \
	ls --file-type | grep -v /\\\|\\\.a$$\\\|\\\.la$$\\\|\\\.dbg$$ |  while read d ; \
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
	zip $(PACKAGE)-$(VERSION)-$(host_cpu)-dbgsym.zip Mutabor/*.dbg


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

# POTFLILES.tmp is added in common-rules.mk
CLEANFILES += POTFILES.tmp2

potfilechk-local: POTFILES.tmp $(top_srcdir)/po/POTFILES.in
	sed -e 's,#.*$$,, ; /^$$/ d' $(top_srcdir)/po/POTFILES.in | LC_ALL=C sort -u >POTFILES.tmp2
	diff -u POTFILES.tmp2 POTFILES.tmp

update-po: src/xrc/reslocale.cpp src/kernel/mut.cc
	make -C po update-po

update-gmo: update-po
	make -C po update-gmo

dch:
	dch -v "$(PACKAGE_VERSION)"

debuild: dch
	debuild


check-local: potfilechk

if VPATH_BUILD
generated_headers: $(TSBUILTSOURCES)
	for d in $(TSBUILTSOURCES) ; \
	do \
		cmp "$$d" "$(top_srcdir)/$$d" || cp "$$d" "$(top_srcdir)/$$d" ; \
	done
else
generated_headers:
endif




# all-local:
# 	for file in src/kernel/mut{.cc,.hh,lex.cc} ; \
# 	do if test -f "$$file" ; \
# 		then \
# 			cmp "$$file" "$(top_srcdir)/$$file" || \
# 			cp "$$file" "$(top_srcdir)/$$file" ; \
# 		fi \
# 	done

doxygen: Doxyfile
	builddir=`pwd` ; \
	cd $(top_srcdir) ; \
	doxygen "$$builddir/Doxyfile"

cppcheck:
	cd '$(top_srcdir)' ; \
	INCLUDES=`echo "$(CXXCOMPILE)" | \
		sed -e 's/ -I */ -I/' | \
		tr ' ' '\n' | \
		grep -e '$(top_srcdir)' | \
		sed -e '/-I/ {s/-I/-I /; p } ; d'` ; \
	echo $$INCLUDES ; \
	cfiles=`echo $(POTSOURCES) | tr ' ' '\n' | grep -ve '\\.h$$'` ; \
	echo "$$cfiles" ; \
	hfiles=`echo $(POTSOURCES) | tr ' ' '\n' | grep -e '\\.h$$'` ; \
	echo "$$hfiles" ; \
	cppcheck -v --enable=all --force $$INCLUDES -I. $$cfiles $$hfiles -j8

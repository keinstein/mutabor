/** \file MutApp.cpp
 ********************************************************************
 * Mutabor Application.
 *
 * $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/muwx/MutApp.cpp,v 1.54 2011/11/02 14:31:58 keinstein Exp $
 * Copyright:   (c) 2005,2006,2007 TU Dresden
 * \author Rüdiger Krauße <krausze@mail.berlios.de>
 * Tobias Schlemmer <keinstein@users.berlios.de>
 * \date 2005/08/12
 * $Date: 2011/11/02 14:31:58 $
 * \version $Revision: 1.54 $
 * \license GPL
 *
 * $Log: MutApp.cpp,v $
 * Revision 1.54  2011/11/02 14:31:58  keinstein
 * fix some errors crashing Mutabor on Windows
 *
 * Revision 1.53  2011-10-04 17:16:13  keinstein
 * make program compile on Mac (wx 2.9) and fix some memory corruption
 *
 * Revision 1.52  2011-10-02 16:58:41  keinstein
 * * generate Class debug information when compile in debug mode
 * * InputDeviceClass::Destroy() prevented RouteClass::Destroy() from clearing references -- fixed.
 * * Reenable confirmation dialog when closing document while the logic is active
 * * Change debug flag management to be more debugger friendly
 * * implement automatic route/device deletion check
 * * new debug flag --debug-trace
 * * generate lots of tracing output
 *
 * Revision 1.51  2011-09-30 09:10:24  keinstein
 * Further improvements in the routing system.
 *
 * Revision 1.50  2011-09-29 05:26:59  keinstein
 * debug intrusive_ptr
 * fix storage and retrieving of input/output devices in treestorage
 * save maximum border size in icons
 * Apply the calculated offset in IconShape (box and box channels still missing)
 * Fix debug saving and restoring route information/route window on activation
 * Add wxWANTS_CHARS to MutEditWindow
 *
 * Revision 1.49  2011-09-27 20:13:23  keinstein
 * * Reworked route editing backend
 * * rewireing is done by RouteClass/GUIRoute now
 * * other classes forward most requests to this pair
 * * many bugfixes
 * * Version change: We are reaching beta phase now
 *
 * Revision 1.48  2011-09-07 15:58:56  keinstein
 * fix compilation on MinGW
 *
 * Revision 1.47  2011-09-05 11:30:07  keinstein
 * Some code cleanups moving some global box arrays into class mutaborGUI::BoxData
 * Restore perspective on logic start
 *
 * Revision 1.46  2011-09-04 15:35:08  keinstein
 * disable print preview on OS X and when using libgnomeprint as they proviede their own means
 *
 * Revision 1.45  2011-09-04 12:02:08  keinstein
 * require wxWidgets 2.8.5 configure.in
 *
 * Revision 1.44  2011-08-31 20:18:16  keinstein
 * some work on printing the editor file
 *
 * Revision 1.43  2011-08-28 20:09:10  keinstein
 * several impovements for opening and saving files
 *
 * Revision 1.42  2011-08-28 14:38:23  keinstein
 * Some menu impovements
 *
 * Revision 1.41  2011-08-27 17:44:44  keinstein
 * Implemented Search and Search/Replace
 *
 * Revision 1.40  2011-08-24 21:19:36  keinstein
 * first run with 2.9.2+
 *
 * Revision 1.39  2011-08-21 16:52:04  keinstein
 * Integrate a more sophisticated editor menu based on the stc sample
 *
 * Revision 1.38  2011-08-20 17:50:39  keinstein
 * use  wxSTC for the editor windows
 *
 * Revision 1.37  2011-08-16 20:20:03  keinstein
 * Fix compiling on Mac OS X 10.5
 *
 * Revision 1.36  2011-08-16 07:13:54  keinstein
 * added Creator code to .app meta data
 *
 * Revision 1.35  2011-08-14 19:12:53  keinstein
 * raise frame after “opening” an already open file
 *
 * Revision 1.34  2011-08-11 19:00:48  keinstein
 * get Document/View running.
 * Needs further testing (possible segfaults).
 *
 * Revision 1.33  2011-08-06 11:36:16  keinstein
 * allow multiple open documents
 *
 * Revision 1.32  2011-08-06 09:21:23  keinstein
 * activated and debugged document manager
 *
 * Revision 1.31  2011-07-31 21:32:21  keinstein
 * Slightly improved window positioning
 * Suppress route window, when a Window is opened from the command line
 *
 * Revision 1.30  2011-07-31 20:16:04  keinstein
 * Implemented opening files from command line using Document/View framework
 *
 * Revision 1.29  2011-07-31 12:40:41  keinstein
 * Added classes and functions for Document/View support
 *
 * Revision 1.28  2011-07-30 21:36:46  keinstein
 * allow file open from command line
 *
 * Revision 1.27  2011-02-20 22:35:57  keinstein
 * updated license information; some file headers have to be revised, though
 *
 * Revision 1.26  2011-01-09 16:26:37  keinstein
 * make building in wine environment using unix shell
 *
 * Revision 1.25  2010-12-11 02:10:09  keinstein
 * make 2.9.1 build but Mutabor crashes still at runtime in an infinite recursion :-(
 *
 * Revision 1.24  2010-12-10 09:28:23  keinstein
 * add menu item to help menu, which calls exit(0).
 *
 * Revision 1.23  2010-11-21 13:15:47  keinstein
 * merged experimental_tobias
 *
 * Revision 1.21.2.11  2010-11-19 10:06:32  keinstein
 * remove MutFrame OnIdle
 *
 * Revision 1.21.2.10  2010-11-14 22:29:53  keinstein
 * Remvoed EDevice.cpp and EDevice.h from the sources list
 * They still reside in the source tree, since they have been used for Midi/GMN
 * file playing. That funcitonality has been disabled so far.
 * After reimplementation the files can be removed.
 *
 * Revision 1.21.2.9  2010-09-30 16:26:26  keinstein
 * remove global variables routewindow and frame
 * move route loading and route saving into MutRouteWnd
 * implement MutRouteWnd::InitShapes.
 * Destroy Route children before loading new route configuration (still some crashes)
 *
 * Revision 1.21.2.8  2010-09-15 17:58:01  keinstein
 * old configuration can be loaded again.
 *
 * Revision 1.21.2.7  2010-08-10 15:54:29  keinstein
 * new, direct route configuration on init
 *
 * Revision 1.21.2.6  2010/03/30 08:38:26  keinstein
 * added rudimentary command line support
 * changed debug system to allow selection of messages via command line
 * further enhancements to the route dialogs
 *
 * Revision 1.21.2.5  2010/02/15 12:08:20  keinstein
 * intermediate update for backup progress
 *
 * Revision 1.21.2.4  2010/01/14 18:14:20  keinstein
 * fix usage of installation prefix
 * MutInputDeviceShape/MutOutputDeviceShape:
 *     use GetType for type checking in OnChoiceSelected
 *     make InitalizeDialog const
 * MutNewOutputDeviceShape: add InitializeDialog and ReplaceSelfBy
 *
 * Revision 1.21.2.3  2010/01/14 15:43:44  keinstein
 * trying to get mutabor work on local install
 *
 * Revision 1.21.2.2  2009/11/16 20:07:10  keinstein
 * make “make distcheck” happy
 *
 * Revision 1.21.2.1  2009/08/10 11:23:12  keinstein
 * merged from wrong tree
 *
 * Revision 1.22  2009/08/10 11:15:46  keinstein
 * some steps towards new route window
 *
 * Revision 1.21  2008/10/10 08:25:42  keinstein
 * Call OGLInitialize if OGL is used
 *
 * Revision 1.20  2008/10/09 15:14:02  keinstein
 * make compile on mingw
 *
 * Revision 1.19  2008/08/18 15:08:42  keinstein
 * Exit Main loop if no window is open
 *
 * Revision 1.18  2008/08/05 07:04:47  keinstein
 * CmQuit Use DeletePendingObjects to delete frames
 *
 * Revision 1.17  2008/08/01 16:22:13  keinstein
 * OnExit: uninit MIDI
 * CmQuit: try to fix endless loop on Linux
 *
 * Revision 1.16  2008/07/22 07:57:06  keinstein
 * solved some valgrind issues
 *
 * Revision 1.15  2008/07/21 09:08:44  keinstein
 * some reformatting of white space and debug logging
 * Changed window deletion on Quit.
 * Changed window Variables to one per Box and type
 *
 * Revision 1.14  2008/06/30 08:27:10  keinstein
 * New Variable: routewindow
 * OnInit(): Register Ids from Mutabor.rh
 * Implement Loading and Saving routes
 * MustOpenFrame(): New function.
 * On window open: use MustOpenFrame() to determine if new frame must be created
 * CmRoutes(): Implement correct window opening.
 * CmQuit(): Reimplemented Frame deletion to prevent crashes and endless loops on quitting
 *
 * Revision 1.13  2008/06/02 16:11:00  keinstein
 * Don't include Mutabor.rh, since it is included with headers.
 * Implement Help for config dialog
 * MutApp::CmAbout(): Remove newlines from People list.
 * Implement CM_EXECUTE
 * MutApp::CmFileOpen(), MutApp::CmFileNew(): Open new windows only when really necessary
 *
 * Revision 1.12  2008/04/28 08:19:58  keinstein
 * Use one single file Help.zip for online help.
 * MutApp::ShowHelp: Implement the other Help commands.
 * MutApp::CmQuit: remove unused variable frame
 * 	silence a warning about paren scoping
 * MutApp::MakeHelpMenu: Add missing menu items.
 *
 * Revision 1.11  2008/03/11 10:37:34  keinstein
 * Holyday edition
 * put CM_xxx in an enum
 * use wx constants
 * document mutframe
 * some white space formattings
 * make route saving more system specific
 * many other fixes
 *
 *
 * \addtogroup muwx
 * \{
 ********************************************************************/


// ---------------------------------------------------------------------------
// headers
// ---------------------------------------------------------------------------

#include "mu32/Defs.h"
#include "wx/image.h"
#include "wx/stdpaths.h"
#include "wx/filename.h"
#include "wx/imagpng.h"
#include "wx/xrc/xmlres.h"
#include "wx/xrc/xh_all.h"
#include "wx/fs_zip.h"
#include "wx/cshelp.h"
#include "wx/aboutdlg.h"
#include "wx/generic/aboutdlgg.h"
#include "wx/cmdline.h"
#include "wx/file.h"
#include "wx/event.h"


#if !defined(__WXMSW__)
#include "Icon/Mutabor.xpm"
#endif

//#include "Mutabor.rh"
#include "muwx/MutApp.h"
#include "muwx/MutFrame.h"
#include "muwx/MutDocument.h"
#include "muwx/MutView.h"
#include "mu32/routing/midi/DevMidi.h"
#include "muwx/MutConfDlg.h"
#include "muwx/resourceload.h"
#include "muwx/Action.h"
#include "muwx/stclanguage.h"
#include "muwx/MutDocManager.h"
#include "muwx/Routing/GUIRoute.h"
#include "muwx/configtree.h"
#include "mu32/box.h"
#include "muwx/Routing/DebugRoute.h"

#ifdef __WXMAC__
#include <ApplicationServices/ApplicationServices.h>
#endif

#ifdef __BORLANDC__
#pragma hdrstop
#endif

using namespace mutabor;
using namespace mutaborGUI;


IMPLEMENT_APP(MutApp)

namespace mutaborGUI {

	wxHtmlHelpController * HelpController = (wxHtmlHelpController *) NULL;
#if wxUSE_PRINTING_ARCHITECTURE

//! global print data, to remember settings during the session
	wxPrintData *g_printData = (wxPrintData*) NULL;
	wxPageSetupData *g_pageSetupData = (wxPageSetupData*) NULL;

#endif // wxUSE_PRINTING_ARCHITECTURE
// ===========================================================================
// implementation
// ===========================================================================

// ---------------------------------------------------------------------------
// MutApp
// ---------------------------------------------------------------------------


#define OPENMENU				\
	{ wxMenu * menu = new wxMenu;

#define CLOSEMENU(name)				\
	menuBar->Append(menu, name); }

#define MENUITEM(name, id, help)		\
	menu->Append(id, name, help)

#define MENUCHECKITEM(name, id, help)		\
	menu->AppendCheckItem(id, name, help)

#define MENUITEM_ADD(name, id, help, add)	\
	menu->Append(id, name, help, add)

#define MENUITEM_SEPARATOR			\
	menu->AppendSeparator()

	BEGIN_EVENT_TABLE(MutApp, wxApp)
	EVT_MENU(CM_SETUP,                     MutApp::CmSetup)
	EVT_MENU(wxID_OPEN,                    MutApp::PassEventToDocManagerCMD)
	EVT_MENU(wxID_CLOSE,                   MutApp::PassEventToDocManagerCMD)
	EVT_MENU(wxID_CLOSE_ALL,               MutApp::PassEventToDocManagerCMD)
	EVT_MENU(wxID_REVERT,                  MutApp::PassEventToDocManagerCMD)
	EVT_MENU(wxID_NEW,                     MutApp::PassEventToDocManagerCMD)
	EVT_MENU(wxID_SAVE,                    MutApp::PassEventToDocManagerCMD)
	EVT_MENU(wxID_SAVEAS,                  MutApp::PassEventToDocManagerCMD)
	EVT_MENU(wxID_UNDO,                    MutApp::PassEventToDocManagerCMD)
	EVT_MENU(wxID_REDO,                    MutApp::PassEventToDocManagerCMD)
	EVT_MENU(CM_EXECUTE,                   MutApp::PassEventToDocManagerCMD)

	EVT_UPDATE_UI(wxID_OPEN,               MutApp::PassEventToDocManagerUPD)
	EVT_UPDATE_UI(wxID_CLOSE,              MutApp::PassEventToDocManagerUPD)
	EVT_UPDATE_UI(wxID_CLOSE_ALL,          MutApp::PassEventToDocManagerUPD)
	EVT_UPDATE_UI(wxID_REVERT,             MutApp::PassEventToDocManagerUPD)
	EVT_UPDATE_UI(wxID_NEW,                MutApp::PassEventToDocManagerUPD)
	EVT_UPDATE_UI(wxID_SAVE,               MutApp::PassEventToDocManagerUPD)
	EVT_UPDATE_UI(wxID_SAVEAS,             MutApp::PassEventToDocManagerUPD)
	EVT_UPDATE_UI(wxID_UNDO,               MutApp::PassEventToDocManagerUPD)
	EVT_UPDATE_UI(wxID_REDO,               MutApp::PassEventToDocManagerUPD)

#if wxUSE_PRINTING_ARCHITECTURE
	EVT_MENU (wxID_PRINT_SETUP,            MutApp::OnPrintSetup)
	EVT_MENU(wxID_PRINT,                   MutApp::PassEventToDocManagerCMD)
	EVT_MENU(wxID_PREVIEW,                 MutApp::PassEventToDocManagerCMD)

	EVT_UPDATE_UI(wxID_PRINT,              MutApp::PassEventToDocManagerUPD)
	EVT_UPDATE_UI(wxID_PREVIEW,            MutApp::PassEventToDocManagerUPD)
#endif
	EVT_MENU_RANGE(wxID_FILE1, wxID_FILE9, MutApp::OnMRUFile)	
	EVT_MENU(CM_ROUTES,                    MutApp::CmRoutes)
	EVT_MENU(CM_ROUTELOAD,                 MutApp::CmRouteLoad)
	EVT_MENU(CM_ROUTESAVE,                 MutApp::CmRouteSave)
	EVT_MENU(CM_ROUTESAVEAS,               MutApp::CmRouteSaveAs)
	EVT_MENU(CM_HELP,                      MutApp::CmHelp)
	EVT_MENU(CM_HELPHANDBOOK,              MutApp::CmHelp)
	EVT_MENU(CM_HELPREFERENCE,             MutApp::CmHelp)
	EVT_MENU(CM_HELPINDEX,                 MutApp::CmHelp)
	EVT_MENU(CM_HELPSEARCH,                MutApp::CmHelp)
	EVT_MENU(CM_HELPONHELP,                MutApp::CmHelp)
	EVT_MENU(CM_ABOUT,                     MutApp::CmAbout) 
	EVT_MENU(CM_EXIT,                      MutApp::CmQuit)
#ifdef DEBUG
	EVT_MENU(cmCallExitId,                 MutApp::CmCallExit)
#endif
	END_EVENT_TABLE()

	// Initialise this in OnInit, not statically
	bool MutApp::OnInit()
	{
		/* Short form for
		   for (int i = MUT_FIRST; i < MUT_LAST; i++) 
		   wxRegisterId(i);
		*/
		wxRegisterId(MUT_LAST);

		SetAppName(_T(PACKAGE));
		SetClassName(_T(PACKAGE_NAME));

#ifdef DEBUG
		std::cerr << "Starting Mutabor..." << std::endl;
#endif
        
		wxStandardPaths& sp = (wxStandardPaths &) wxStandardPaths::Get();

#ifdef __LINUX__
		sp.SetInstallPrefix(_T(PREFIX));
#endif

		quitting = false;

		// initialize the languages
		m_locale.Init(wxLANGUAGE_DEFAULT);

		// TODO: Check this!
		// normally this wouldn't be necessary as the catalog files would be found
		// in the default locations, but under Windows then the program is not
		// installed the catalogs are in the parent directory (because the binary
		// is in a subdirectory of samples/internat) where we wouldn't find them by
		// default
		wxLocale::AddCatalogLookupPathPrefix(_T("."));
		wxLocale::AddCatalogLookupPathPrefix(wxT(".."));

		// Initialize the catalogs we'll be using
		m_locale.AddCatalog(wxT("mutabor"));
		m_locale.AddCatalog(wxT("wxstd"));
#ifdef __LINUX__
		{
			wxLogNull noLog;
			m_locale.AddCatalog(_T("fileutils"));
		}
#endif


#ifdef DEBUG
		std::cout << (muT(__FUNCTION__).ToUTF8()) << std::endl;
		std::cout << (muT(typeid(m_locale).name()).ToUTF8()) << std::endl;
		std::cout << "ConfigDir:        "

			  << (const char *)(sp.GetConfigDir().ToUTF8()) << std::endl
			  << "DataDir:          "
			  << (const char *)(sp.GetDataDir().ToUTF8()) << std::endl
			  << "DocumentsDir:     "
			  << (const char *)(sp.GetDocumentsDir().ToUTF8()) << std::endl
			  << "ExecutablePath:   "
			  << (const char *)(sp.GetExecutablePath().ToUTF8()) << std::endl

#if defined(__UNIX__) && !defined(__WXMAC__)
			  << "InstallPrefix:    " << (const char *)(sp.GetInstallPrefix().ToUTF8())
			  << std::endl
#endif
			  << "LocalDataDir:     " << (const char *)(sp.GetLocalDataDir().ToUTF8())
			  << std::endl
			  << "PluginsDir:       " << (const char *)(sp.GetPluginsDir().ToUTF8())
			  << std::endl
			  << "ResourcesDir:     " << (const char *)(sp.GetResourcesDir().ToUTF8())
			  << std::endl
			  << "TempDir:          " << (const char *)(sp.GetTempDir().ToUTF8())
			  << std::endl
			  << "UserConfigDir:    " << (const char *)(sp.GetUserConfigDir().ToUTF8())
			  << std::endl
			  << "UserDataDir:      " << (const char *)(sp.GetUserDataDir().ToUTF8())
			  << std::endl
			  << "UserLocalDataDir: " << (const char *)(sp.GetUserLocalDataDir().ToUTF8())
			  << std::endl;

		std::cout
			<< "LocalizedResourcesDir(Can): "
			<< (const char *)(sp.GetLocalizedResourcesDir(m_locale.GetCanonicalName(),
								      sp.ResourceCat_None).ToUTF8())
			<< std::endl
			<< "LocalizedResourcesDir(Can,Messages): "
			<< (const char *)(sp.GetLocalizedResourcesDir(m_locale.GetCanonicalName(),
								      sp.ResourceCat_Messages).ToUTF8())
			<< std::endl
			<< "LocalizedResourcesDir(): "
			<< (const char *)(sp.GetLocalizedResourcesDir(m_locale.GetName(),
								      sp.ResourceCat_None).ToUTF8())
			<< std::endl
			<< "LocalizedResourcesDir(Messages): "
			<< (const char *)(sp.GetLocalizedResourcesDir(m_locale.GetName(),
								      sp.ResourceCat_Messages).ToUTF8())
			<< std::endl;

#endif

		// init global objects
		// -------------------

		g_printData = new wxPrintData;

		// You could set an initial paper size here
#if 0
		g_printData->SetPaperId(wxPAPER_LETTER); // for Americans
		g_printData->SetPaperId(wxPAPER_A4);    // for everyone else
#endif

		g_pageSetupData = new wxPageSetupDialogData;

		// copy over initial paper size from print record
		(*g_pageSetupData) = *g_printData;

		// Set some initial page margins in mm.
		g_pageSetupData->SetMarginTopLeft(wxPoint(15, 15));
		g_pageSetupData->SetMarginBottomRight(wxPoint(15, 15));

		// We are using .png files for some extra bitmaps.
		wxImageHandler * pnghandler = new wxPNGHandler;
		wxImage::AddHandler(pnghandler);
		wxImage::AddHandler(new wxGIFHandler);
	
		wxFileSystem::AddHandler(new wxZipFSHandler);

		wxXmlResource::Get()->InitAllHandlers();
		wxString resfilename = GetResourceName(_T("Mutabor.xrc"));
		wxXmlResource::Get()->Load(resfilename);

		wxHelpControllerHelpProvider* provider = new wxHelpControllerHelpProvider;
		wxHelpProvider::Set(provider);
		HelpController = new wxHtmlHelpController();
		provider->SetHelpController(HelpController);

		// we want to name the help files according to the lanuage.
		if (!HelpController->Initialize(GetResourceName(_("Help.zip"))))
			std::cerr << "Warning: could not initialize Help system: "
				  << (const char *)(wxString(_("Help.zip")).ToUTF8())
				  << std::endl;


		if (!(document_manager=new MutDocManager()))
			return false;
		//  restrict to having <= 1 doc open at any time
//	document_manager->SetMaxDocsOpen(5);
		//  establish a doc template for the doc,view pair
		new wxDocTemplate(document_manager, 
				  _("Mutabor logic file"), 
				  wxT("*.mut"), 
				  wxT("") /*dir*/, 
				  wxT("mut"), 
				  wxT("mutabor_logic_document"), 
				  wxT("mutabor_logic_view"), 
				  CLASSINFO(mutaborGUI::MutDocument), 
				  CLASSINFO(mutaborGUI::MutView) );
#if defined(__WXMAC__) && defined(__WXCARBON__) 
		wxFileName::MacRegisterDefaultTypeAndCreator( wxT("mut") , 'MUTA' , 'MUTA' ) ;
#endif

#if defined(__WXMAC__)
		// || defined(__WXCOCOA__)
		// Make a common menubar

		wxApp::SetExitOnFrameDelete(false);
		wxApp::s_macAboutMenuItemId = CM_ABOUT;
		wxApp::s_macPreferencesMenuItemId = CM_SETUP;
		wxApp::s_macExitMenuItemId = CM_EXIT;
		wxApp::s_macHelpMenuTitleName = _("&Help");
		wxMenuBar *menuBar = new wxMenuBar;
		MakeFileMenu(menuBar,ProgramMenu);
		MakeViewMenu(menuBar,ProgramMenu);
		MakeHelpMenu(menuBar);
		wxMenuBar::MacSetCommonMenuBar(menuBar);
	
#endif

		// RestoreState needs initialized MIDI
		initialize_boxes();
		MidiInit();
		InitGUIRouteFactories();

		RestoreState();

		// Command line files must be opened after the file history has been read
		// This call parses the command line
		if (!wxApp::OnInit()) return false;

		
		if (!GetTopWindow()) {
			MutFrame * frame = CreateMainFrame(RouteMenu);
			frame->RestoreState();
			wxCommandEvent event(CM_ROUTES);
			frame->CmRoutes(event);
			frame->Show(true);
		}

#if wxUSE_PRINTING_ARCHITECTURE
		// initialize print data and setup
		g_printData = new wxPrintData;
		g_pageSetupData = new wxPageSetupDialogData;
#endif // wxUSE_PRINTING_ARCHITECTURE


		return true;
	}

	void MutApp::OnInitCmdLine(wxCmdLineParser&  parser) {
		const wxCmdLineEntryDesc cmdLineDesc[] = {
			{ wxCMD_LINE_PARAM,  NULL, NULL, _("logic file"), 
			  wxCMD_LINE_VAL_STRING, wxCMD_LINE_PARAM_MULTIPLE|wxCMD_LINE_PARAM_OPTIONAL },
			{ wxCMD_LINE_NONE }
		};

		wxApp::OnInitCmdLine(parser);
		parser.SetDesc(cmdLineDesc);

#ifdef DEBUG
		debugFlags::InitCommandLine(parser);
#endif

	
	}

	bool MutApp::OnCmdLineParsed(wxCmdLineParser&  parser) {
		if (!wxApp::OnCmdLineParsed(parser)) return false;
#ifdef DEBUG
		debugFlags::ProcessCommandLine(parser);
#endif
		wxString str;
		int count = parser.GetParamCount();
		for (int i = 0; i<count;i++)
		{
			// we have a document to open
			str = parser.GetParam(i);
			printf("cmd line param: %ls\n", WXSTRINGCAST(str));
			// this will probably see if the file exists, and has the right extension

//		MutFrame * frame = CreateMainFrame(EditorMenu);
//		frame->OpenFile(str);

			if (document_manager)
				document_manager->CreateDocument(str, wxDOC_SILENT);
		}

		DEBUGLOG (other, _T("Command line parsed."));
		return true;
	}

// Extend event processing to search the view's event table
	bool MutApp::ProcessEvent(wxEvent& event)
	{
		bool retval =  wxApp::ProcessEvent(event);
#ifdef DEBUG
		if (!retval) {
			DEBUGLOG(eventqueue,
				 _T("Undhandled event %p, id=%d, type=%d"),
				 static_cast<void *>(&event),
				 (int)(event.GetId()),
				 (int)(event.GetEventType())
				);
		}
#endif
		return retval;
	}

	void MutApp::PassEventToDocManagerCMD(wxCommandEvent& event)
	{
		DEBUGLOG(eventqueue,_T("Command %p, id=%d, type=%d"),
			 static_cast<void *>(&event),
			 event.GetId(),
			 (int)event.GetEventType()
			);
		if (!(document_manager->ProcessEvent(event))) 
			event.Skip();
	}
	void MutApp::PassEventToDocManagerUPD(wxUpdateUIEvent& event)
	{
		DEBUGLOG(eventqueue,_T("UpdateUI: %p, id=%d, type=%d"),
			 static_cast<void *>(&event),
			 event.GetId(),
			 (int)event.GetEventType()
			);
		if (!(document_manager->ProcessEvent(event)))
			event.Skip();
	}

	void MutApp::OnMRUFile(wxCommandEvent& event)
	{
		int n = event.GetId() - wxID_FILE1;  // the index in MRU list
		wxString filename(document_manager->GetHistoryFile(n));
		if ( !filename.empty() )
		{
			// verify that the file exists before doing anything else
			if ( wxFile::Exists(filename) )
			{
				// try to open it
				if (!document_manager->CreateDocument(filename, wxDOC_SILENT))
				{
					// remove the file from the MRU list. The user should already be notified.
					document_manager->RemoveFileFromHistory(n);

					wxLogError(_("The file '%s' couldn't be opened.\nIt has been removed from the most recently used files list."),
						   filename.c_str());
				} else {
					wxView * v = document_manager->GetCurrentView();
					if (v) {
						wxWindow * w = v->GetFrame();
						if (w) {
							w->Raise();
						}
					}
				}
			}
			else
			{
				// remove the bogus filename from the MRU list and notify the user
				// about it
				document_manager->RemoveFileFromHistory(n);

				wxLogError(_("The file '%s' doesn't exist and couldn't be opened.\nIt has been removed from the most recently used files list."),
					   filename.c_str());
			}
		}
	}



	BEGIN_EVENT_TABLE(MutConfigDialog, ConfigDlg)
	EVT_BUTTON(::wxID_HELP, MutConfigDialog::CmHelp)
	END_EVENT_TABLE()

	void MutApp::CmSetup (wxCommandEvent& event)
	{
		mutUnused(event);
		MutConfigDialog * config;
		config = new MutConfigDialog((wxFrame *) NULL);

		if (config) {
			//we don't need the return value as we are using validators
			//int value = 
			config->ShowModal();
			config->Destroy();
		}
	}

	void MutApp::CmAbout (wxCommandEvent& event)
	{
		mutUnused(event);
		/*
		  (void)wxMessageBox(wxString::Format(_("%s\nAuthors: \n%s\nUsage: %s"),
		  mumT(PACKAGE_STRING),
		  _T("Ruediger Krausze <krausze@mail.berlios.de>\n")
		  _T("Tobias Schlemmer <keinstein@mail.berlios.de>\n"),
		  mumT(PACKAGE)),
		  wxString::Format(_("About %s"),mumT(PACKAGE_NAME)));
		*/
		/*	AppAbout * about;
			about = new AppAbout((wxFrame *) NULL);
			about->Destroy();

		*/
		// setup path
		wxStandardPathsBase &path = wxStandardPaths::Get();
		wxAboutDialogInfo info;
		info.SetCopyright(_("(c) 2005-2011 TU Dresden"));
		info.SetVersion(_T(PACKAGE_VERSION));
		info.SetWebSite(_T("http://www.math.tu-dresden.de/~mutabor/"));
		info.SetIcon(wxIcon(wxFileName(path.GetResourcesDir(),
					       _T("about"),
					       _T("png")).GetFullPath(),
				    wxBITMAP_TYPE_PNG));
		info.SetDescription(_("An application to implement different tuning logics.\n Both fixed, adaptive and mutable tunings are supported."));
		info.AddArtist(_("Rudolf Wille (mathematical foundation)"));
		info.AddArtist(_("Tobias Schlemmer (new icon/splash)"));
		info.AddDeveloper(_("Bernhard Ganter"));
		info.AddDeveloper(_("Volker Abel"));
		info.AddDeveloper(_("Peter Reiss"));
		info.AddDeveloper(_("Ruediger Krausze <krausze@mail.berlios.de>"));
		info.AddDeveloper(_("Tobias Schlemmer <keinstein@mail.berlios.de>"));
		info.AddDocWriter(_("Volker Abel"));
		info.AddDocWriter(_("Peter Reiss"));
		info.AddDocWriter(_("Ruediger Krausze <krausze@mail.berlios.de>"));
		info.AddDocWriter(_("Tobias Schlemmer <keinstein@mail.berlios.de>"));
		info.AddTranslator(_("English: Tobias Schlemmer"));

		wxGenericAboutBox(info);
	}


	AppAbout::AppAbout (wxWindow *parent, long style)
		: wxDialog (parent, -1, wxEmptyString,
		            wxDefaultPosition, wxDefaultSize,
		            wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER)
	{
		mutUnused(style);
		// setup path
		wxStandardPathsBase &path = wxStandardPaths::Get();


		// sets the application icon
		SetTitle (_("About ..."));

		// about info
		wxGridSizer *aboutinfo = new wxFlexGridSizer (2, 5, 5);
		aboutinfo->Add (new wxStaticText(this, -1, _("Version: ")));
		aboutinfo->Add (new wxStaticText(this, -1, _T(PACKAGE_VERSION)));
		aboutinfo->Add (new wxStaticText(this, -1, _("Written by: ")));
		aboutinfo->Add (new wxStaticText(this, -1, _("Bernhard Ganter\n"
							     "Volker Abel\n"
							     "Peter Reiss\n"
							     "Ruediger Krausze <krausze@mail.berlios.de>\n"
							     "Tobias Schlemmer <keinstein@mail.berlios.de>")));
		aboutinfo->Add (new wxStaticText(this, -1, _("Mathematical\nmodelling:")));
		aboutinfo->Add (new wxStaticText(this, -1, _("Rudolf Wille")));
		aboutinfo->Add (new wxStaticText(this, -1, _("Licence type: ")));
		aboutinfo->Add (new wxStaticText(this, -1, _("GPL")));
		aboutinfo->Add (new wxStaticText(this, -1, _("wxWidgets: ")));
		aboutinfo->Add (new wxStaticText(this, -1, wxVERSION_STRING));
		aboutinfo->Add (new wxStaticText(this, -1, _("Copyright: ")));
		aboutinfo->Add (new wxStaticText(this, -1, _("(c) 2007 TU Dresden, Institut fuer Algebra")));

		// about title/info
		wxBoxSizer *abouttext = new wxBoxSizer (wxVERTICAL);
//    wxStaticText *appname = new wxStaticText (this, -1, g_appname);
		wxStaticText * appname = new wxStaticText (this, -1, mumT(PACKAGE_NAME));
		appname->SetFont (wxFont (10, wxDEFAULT, wxNORMAL, wxBOLD));
		abouttext->Add (appname, 0, wxALIGN_LEFT);
		abouttext->Add (0, 10);
		abouttext->Add (aboutinfo, 1, wxEXPAND);

		// about icontitle//info
		wxBoxSizer *aboutpane = new wxBoxSizer (wxHORIZONTAL);
//    wxBitmap bitmap = wxBitmap(wxICON (mutabor));
		wxBitmap bitmap = wxBitmap(wxFileName(path.GetResourcesDir(),_T("about"),_T("png")).GetFullPath(),
					   wxBITMAP_TYPE_PNG);
		aboutpane->Add (new wxStaticBitmap (this, -1, bitmap),
				0, wxALIGN_LEFT);
		aboutpane->Add (10, 0);
		aboutpane->Add (abouttext, 1, wxEXPAND);

		// about complete
		wxBoxSizer *totalpane = new wxBoxSizer (wxVERTICAL);
		totalpane->Add (aboutpane, 0, wxEXPAND | wxALL, 10);
		totalpane->Add (new wxStaticText(this, -1, _("Mutabor tuning")),
				0, wxALIGN_CENTER | wxLEFT | wxRIGHT, 10);
		totalpane->Add (0, 6);
//    myHyperLink *website = new myHyperLink (this, -1, APP_WEBSITE);
//    wxString url = APP_WEBSITE;
//    url.Append ("/indexedit.html");
//    website->SetURL (url);
//    totalpane->Add (website, 0, wxALIGN_CENTER);
//	totalpane->Add (new wxStaticLine(this, -1), 0, wxEXPAND | wxALL, 10);
		wxButton *okButton = new wxButton (this, wxID_OK, _("OK"));
		okButton->SetDefault();
		totalpane->Add (okButton, 0, wxALIGN_CENTER | wxLEFT | wxRIGHT | wxBOTTOM, 10);

		SetSizerAndFit (totalpane);

		ShowModal();
	}



	MutFrame* MutApp::CreateMainFrame(MenuType type, wxWindowID id)
	{
		MutFrame* frame = new MutFrame((wxFrame *)NULL, wxID_ANY, _T("Mutabor"),
					       wxDefaultPosition, wxDefaultSize, //wxSize(500, 400),
					       wxDEFAULT_FRAME_STYLE | wxHSCROLL | wxVSCROLL);
		return InitMainFrame(type,frame);
	}


	// Give it an icon
	MutFrame* MutApp::InitMainFrame(MenuType type, MutFrame * frame) 
	{
#ifdef __WXMSW__
		frame->SetIcon(wxIcon(_T("mutabor_icn")));
#else
		frame->SetIcon(wxIcon( mutabor_xpm ));
#endif

		// Make a menubar

		wxMenuBar *menuBar = new wxMenuBar;
		frame->SetFileMenu(MakeFileMenu(menuBar, type));
		MakeEditMenu(menuBar, type);
		MakeViewMenu(menuBar, type);
		MakeLogicMenu(menuBar);
		MakeRoutesMenu(menuBar);
		MakeSequencerMenu(menuBar);
		MakeHelpMenu(menuBar);

		// Associate the menu bar with the frame
		frame->SetMenuBar(menuBar);

#if wxUSE_STATUSBAR
		frame->CreateStatusBar();
#endif // wxUSE_STATUSBAR

		return frame;
	}

	void MutApp::CmFileNew (wxCommandEvent& event)
	{
		STUBC;
		return;
# if 0
#ifdef DEBUG
		printf("MutApp::CmFileNew\n");
#endif
		MutFrame * frame = dynamic_cast<MutFrame*>(GetTopWindow());

		if (MustOpenFrame(frame))
			frame = CreateMainFrame(EditorMenu);

#ifdef DEBUG
		printf("MutApp::CmFileNew: created main frame\n");

#endif
		frame->CmFileNew(event);
		frame->Show();

#ifdef DEBUG
		printf("MutApp::CmFileNew: file new: done.\n");

#endif
		event.Skip(false);
#endif
	}


	void MutApp::CmFileOpen (wxCommandEvent& event)
	{

		STUBC;
		return;
#if 0
		wxWindow * topwindow=GetTopWindow();

		event.Skip(false);

		wxString path = FileNameDialog(topwindow);

		MutFrame * frame = dynamic_cast<MutFrame*>(topwindow);

		if ( !path )
			return;

		if (MustOpenFrame(frame)) 
			frame = CreateMainFrame(EditorMenu);

		frame->OpenFile(path);

		DEBUGLOG(other,_T("%d == %d?"),(int)CM_EXECUTE,event.GetId());

		switch (event.GetId()) {

		case CM_EXECUTE:
			wxCommandEvent e(wxEVT_COMMAND_MENU_SELECTED,CM_ACTIVATE);

			wxPostEvent(frame,e);

			break;
		}
		frame->Show();
#endif
	}

// print event handlers
	void MutApp::OnPrintSetup (wxCommandEvent &WXUNUSED(event)) {
#if wxUSE_PRINTING_ARCHITECTURE
		(*g_pageSetupData) = * g_printData;
		wxPageSetupDialog pageSetupDialog(GetTopWindow(), g_pageSetupData);
		pageSetupDialog.ShowModal();
		(*g_printData) = pageSetupDialog.GetPageSetupData().GetPrintData();
		(*g_pageSetupData) = pageSetupDialog.GetPageSetupData();
#endif // wxUSE_PRINTING_ARCHITECTURE
	}

	void MutApp::CmRoutes (wxCommandEvent& event)
	{
		DEBUGLOG(other,_T("window %p is casted %p"),
			 wxWindow::FindWindowById(WK_ROUTE),
			 dynamic_cast <MutFrame *>(wxWindow::FindWindowById(WK_ROUTE)));

		MutFrame * frame = 
			dynamic_cast<MutFrame*>(wxWindow::FindWindowById(WK_ROUTE));

		if (!frame) {
			frame = dynamic_cast<MutFrame*>(GetTopWindow());

			if (MustOpenFrame(frame))
				frame = CreateMainFrame(RouteMenu);
		}

		frame->CmRoutes(event);

		frame->Show(true);
		event.Skip(false);
	}

	void MutApp::CmHelp (wxCommandEvent& event)
	{
		ShowHelp(event.GetId());
		event.Skip();
	}

	void MutApp::ShowHelp(int commandId)
	{
		switch (commandId) {

		case CM_HELPINDEX:
			HelpController->DisplayContents();

			break;

		case CM_HELP:
			HelpController->Display(_("help.html"));

			break;

		case CM_SETUP:
			HelpController->Display(_("The setup dialog"));

			break;

		case CM_HELPHANDBOOK:
			HelpController->Display(_("manual.html"));

			break;

		case CM_HELPREFERENCE:
			HelpController->Display(_("reference.html"));

			break;

		case CM_HELPONHELP:
			HelpController->Display(_("Help window"));

			break;

		case CM_HELPCOMMON:
			HelpController->DisplayContents();

			break;

		case CM_HELPSEARCH: {
			wxString key = wxGetTextFromUser(_("Search for?"),
							 _("Search help for keyword"),
							 wxEmptyString,
							 GetTopWindow());

			if (! key.IsEmpty())
				HelpController->KeywordSearch(key);
		}

			break;
		}
	}

	void MutApp::CmQuit (wxCommandEvent& event)
	{
		DEBUGLOG (other, _T(""));

		SetExitOnFrameDelete(true);
		//		Exit();

		if (quitting) return;

		quitting = true;
		event.Skip(false);


		wxWindow * window;
		SetTopWindow(NULL);

		//	if (frames.empty()) {
		if ((window = GetTopWindow()) == NULL) {
			DEBUGLOG (other, _T("No Frames."));
			quitting = false;
			ExitMainLoop();
			return;
		}

		// first check whether docmanager allows quitting
		if (!document_manager->Clear(false))
		{
			quitting = false;
			return;
		}


		DEBUGLOG (other, _T("Starting Loop"));

/*	while (Pending())
	Dispatch();


	DEBUGLOG (other, _T("Dispatched all events"));

	wxIdleMode imode = wxIdleEvent::GetMode();
	wxIdleEvent::SetMode(wxIDLE_PROCESS_ALL);
*/

		for (wxWindowList::iterator i = wxTopLevelWindows.begin();
		     i!= wxTopLevelWindows.end();
		     i++) {
			if (!window->Close()) {
//			wxIdleEvent::SetMode(imode);
				quitting = false;
				return;
			}
                
		}
#if 0
		while ((window = GetTopWindow())) {
			DEBUGLOG (other, _("Closing window of class %s"), 
				  muT(typeid(*(window)).name()).c_str());

			if (!window->Close()) {
				wxIdleEvent::SetMode(imode);
				quitting = false;
				return;
			}

			DEBUGLOG (other, _T("Closed window"));

			// empty queue and process idle event to delete the frame

/*		while (Pending())
		Dispatch();
*/
			//   wxIdleEvent idle;
			//ProcessEvent(idle);
			//while(Pending())
			//  Dispatch();
//		DeletePendingObjects();

			DEBUGLOG (other, _T("Dispatched all events"));
		}
#endif

		DEBUGLOG (other, _T("finished loop"));
	}



	wxString MutApp::GetResourceName(const wxString & file)
	{
		const wxLocale * m_locale = wxGetLocale();
		wxStandardPathsBase & sp = wxStandardPaths::Get();
		wxString localename = m_locale->GetCanonicalName();
		wxFileName rcname(sp.GetLocalizedResourcesDir(localename),file);
		DEBUGLOGTYPE(other,MutApp,_T("Trying do load resources...\n%s\n%s"),rcname.GetFullPath().c_str(),sp.GetResourcesDir().c_str());
		if (!rcname.IsFileReadable()) {
			rcname.SetPath(sp.GetLocalizedResourcesDir(localename.BeforeFirst(_T('_'))));
			DEBUGLOGTYPE(other,MutApp,_T("Trying %s"),rcname.GetFullPath().c_str());
			if (!rcname.IsFileReadable()) {
				rcname.SetPath(sp.GetResourcesDir());
				DEBUGLOGTYPE(other,MutApp,_T("Trying %s"),rcname.GetFullPath().c_str());
			}
		}
		localename = rcname.GetFullPath();
		return localename;
	}

	wxMenu * MutApp::MakeFileMenu(wxMenuBar * menuBar, MenuType type)
	{
		wxMenu * menu = new wxMenu;
		MENUITEM(_("&New\tCtrl+N"), CM_FILENEW,
			 _("Create a new logic file."));
		MENUITEM(_("&Open...\tCtrl+O"), CM_FILEOPEN,
			 _("Open a logic file in editor window"));

		if (type == EditorMenu || type == RouteMenu) {
			menu->Append (wxID_SAVE);
			menu->Append (wxID_SAVEAS);
			menu->Append (wxID_CLOSE);
		}

		MENUITEM_SEPARATOR;

		MENUITEM(_("&Execute\tCtrl+F9"), CM_EXECUTE,
			 _("Load a logic file an immediately activate it"));

#if (defined(__WXMAC__) || defined(__WXCOCOA__))
		if (type == EditorMenu)
#endif
			MENUITEM_SEPARATOR;

		if (type == EditorMenu) {
			menu->Append (CM_PROPERTIES,
				      _("Proper&ties ...\tCtrl+I"),
				      _("Get some information about the currently edited file"));
		} 
		menu->Append (wxID_PREFERENCES);


		if (type == EditorMenu) {
			menu->AppendSeparator();
#if 0
			menu->Append (wxID_PRINT_SETUP,_("Print setup..."),
				      _("Configure how the pages will be printed"));
#endif
#if !defined(__WXMAC__) && !defined(__WXOSX__)	\
	&& !defined(wxUSE_LIBGNOMEPRINT)
			menu->Append (wxID_PREVIEW);
#endif
			menu->Append (wxID_PRINT);
		}



#if !(defined(__WXMAC__) || defined(__WXCOCOA__))
		MENUITEM_SEPARATOR;
#endif
		menu->Append(wxID_EXIT);
		DEBUGLOG(docview,_T("Adding file history menu"));
		document_manager->FileHistoryUseMenu(menu);
		document_manager->GetFileHistory()->AddFilesToMenu(menu);

#if !(defined(__WXMAC__) || defined(__WXCOCOA__))
		menuBar->Append(menu, _("&File"));
#else
		menuBar->Append(menu, getContextLocal(_("@MAC|&File")));
#endif
		return menu;
	}

	void MutApp::MakeEditMenu(wxMenuBar * menuBar, MenuType type)
	{
		if (type != EditorMenu) return;

		wxMenu * menu = new wxMenu;
		menu->Append (wxID_UNDO);
		menu->Append (wxID_REDO);
		menu->AppendSeparator();
		menu->Append (wxID_CUT);
		menu->Append (wxID_COPY);
		menu->Append (wxID_PASTE);
		menu->Append (wxID_CLEAR);
		menu->AppendSeparator();
		menu->Append (wxID_SELECTALL);
		menu->Append (CM_SELECTLINE, 
			      _("Select &line\tCtrl+Shift+L"),
			      _("Select the complete line at cursor position"));
		menu->AppendSeparator();
		menu->Append (wxID_FIND);
		menu->Append (CM_FINDNEXT, 
			      _("Find &next\tCtrl+G"),
			      _("Continue last search"));
		menu->Append (wxID_REPLACE);
		menu->Append (CM_REPLACENEXT,
			      _("Replace &again\tShift+F4"),
			      _("Go on with replacement"));
		menu->AppendSeparator();
		menu->Append (CM_BRACEMATCH, 
			      _("&Match brace\tCtrl+M"),
			      _("Find matching brace and select all contained characters"));
		menu->Append (CM_GOTO, 
			      _("&Goto Line...\tCtrl+L"),
			      _("Jump to a specific line"));
		menu->AppendSeparator();
		menu->Append (wxID_INDENT);
		menu->Append (wxID_UNINDENT);

		wxMenu *menuOptions = new wxMenu;
		menuOptions->AppendCheckItem (CM_OVERTYPE, 
					      _("&Overwrite mode\tIns"),
					      _("Replace the caracters at the caret position by the ones you type in"));
		menuOptions->AppendCheckItem (CM_WRAPMODEON, 
					      _("&Wrap mode\tCtrl+U"),
					      _("Automatic line breaking while inserting text"));
		menuOptions->AppendCheckItem (CM_READONLY,
					      _("&Readonly mode"),
					      _("Disallow changing the document"));

		// change case submenu
		wxMenu *menuChangeCase = new wxMenu;
		menuChangeCase->Append (CM_CHANGEUPPER, 
					_("&Upper case"),
					_("Change the current selection to upper case"));
		menuChangeCase->Append (CM_CHANGELOWER, 
					_("&Lower case"),
					_("Change the current selection to lower case"));

		// convert EOL submenu
		wxMenu *menuConvertEOL = new wxMenu;
		menuConvertEOL->Append (CM_CONVERTCR, 
					_("CR (&Linux/MAC OS X)"),
					_("Change line endings to carrage return only (Unix style)"));
		menuConvertEOL->Append (CM_CONVERTCRLF,
					_("CR+LF (&Windows)"),
					_("Change line endigs to carrage return + line feed (DOS/Windows style)"));
		menuConvertEOL->Append (CM_CONVERTLF,
					_("LF (&Macintosh)"),
					_("Change line endings to line feed only (old Macintosh style)"));

		menu->Append (wxID_ANY, _("Edit options ..."), menuOptions);
		menu->Append (CM_CHANGECASE, _("Change &case to ..."), menuChangeCase);
		menu->Append (CM_CONVERTEOL, 
			      _("Convert line &endings to ..."), 
			      menuConvertEOL);

		menuBar->Append(menu, _("&Edit"));
	}

	
	void MutApp::MakeLogicMenu(wxMenuBar * menuBar)
	{
		wxMenu * menu = new wxMenu;
		MENUITEM(_("&Compile\tAlt+F9"), CM_COMPILE, _("Load the actual file into the Mutabor Kernel."));
		MENUITEM(_("&Activate\tF9"), CM_ACTIVATE, _("Activate the Mutabor Kernel."));
		MENUITEM(_("&Stop\tF8"), CM_STOP, _("Stop the Mutabor Kernel."));
		MENUITEM_SEPARATOR;
		MENUITEM(_("&Panic\tF12"), CM_PANIC, _("Send \"all notes off\" signal to on all MIDI Channels."));
		menuBar->Append(menu, _("&Logic"));
	}

	void MutApp::MakeRoutesMenu(wxMenuBar * menuBar)
	{
		wxMenu * menu = new wxMenu;
		MENUITEM(_("&Load routes"), CM_ROUTELOAD,
			 _("Load the current route configuration from a file"));
		MENUITEM(_("&Save routes"), CM_ROUTESAVE,
			 _("Save current route configuration to a file."));
		MENUITEM(_("Save routes &as"), CM_ROUTESAVEAS,
			 _("Save current route configuration to a file with a new name."));
		menuBar->Append(menu, _("&Routes"));
	}

	void MutApp::MakeViewMenu(wxMenuBar * menuBar, MenuType type)
	{
	

		wxMenu * menu = new wxMenu;
		if (type == EditorMenu) {
			// hilight submenu
			wxMenu *menuHilight = new wxMenu;
			int Nr;
			for (Nr = 0; Nr < ::g_LanguagePrefsSize; Nr++) {
				menuHilight->Append (CM_HILIGHTFIRST + Nr,
						     ::g_LanguagePrefs [Nr].name);
			}

			// charset submenu
			wxMenu *menuCharset = new wxMenu;
			menuCharset->Append (CM_CHARSETANSI, _("&ANSI (Windows)"));
			menuCharset->Append (CM_CHARSETMAC, _("&MAC (Macintosh)"));

			menu->Append (CM_HILIGHTLANG, 
				      _("&Hilight language..."), 
				      menuHilight);
			menu->AppendSeparator();
			menu->AppendCheckItem (CM_FOLDTOGGLE, 
					       _("&Toggle current fold\tCtrl+T"));
			menu->AppendSeparator();
			menu->AppendCheckItem (CM_DISPLAYEOL, _("Show line &endings"));
			menu->AppendCheckItem (CM_INDENTGUIDE, _("Show &indent guides"));
			menu->AppendCheckItem (CM_LINENUMBER, _("Show line &numbers"));
			menu->AppendCheckItem (CM_LONGLINEON, _("Show &long line marker"));
			menu->AppendCheckItem (CM_WHITESPACE, _("Show white&space"));
			menu->AppendSeparator();
			menu->Append (CM_USECHARSET, _("Use &code page of..."), menuCharset);
			menu->AppendSeparator();
		}
	
		/*	MENUCHECKITEM(_("&Status bar"), IDW_STATUSBAR,
			_("Toggle status bar on/off"));
			MENUCHECKITEM(_("&Toolbar"), IDW_TOOLBAR,
			_("Toggle tool bar on/off"));
			MENUITEM_SEPARATOR;
		*/
		if (type != ProgramMenu) {
			if (type != EditorMenu) {
				MENUITEM_SEPARATOR;
			}
			MENUCHECKITEM(_("Current ke&ys\tF5"), CM_TOGGLEKEY,
				      _("Show current keys window"));
			MENUCHECKITEM(_("&Tone system\tF6"), CM_TOGGLETS,
				      _("Show tone system window"));
			MENUCHECKITEM(_("&Actions\tF7"), CM_TOGGLEACT,
				      _("Show current actions window"));
		}
		MENUCHECKITEM(_("&Routes\tF11"), CM_ROUTES,
			      _("Open route configuration window"));

		if (type != ProgramMenu) {
			/*	  MENUITEM_SEPARATOR;
				  MENUCHECKITEM(_("&One window mode"), CM_OWM,
				  _("Toggle logic satus window: one each or one common"));
				  MENUCHECKITEM(_("One &common action window"), CM_CAW,
				  _("Toggle action window mode: one each or one common"));
			*/
			MENUITEM_SEPARATOR;
			menu->Append(CM_SELECTBOX,_("Select &Box"), new wxMenu(),
				     _("Select current Box"));
		}

		menuBar->Append(menu, _("&View"));
	}

	void MutApp::MakeSequencerMenu(wxMenuBar * menuBar)
	{
		wxMenu * menu = new wxMenu;
		MENUITEM(_("&Play"), CM_INDEVPLAY,
			 _("Start playing the music from input file devices"));
		MENUITEM(_("St&op"), CM_INDEVSTOP,
			 _("Stop playing the music from input file devices"));
		MENUITEM(_("P&ause"), CM_INDEVPAUSE,
			 _("Pause plaing the music from input file devices"));
		menuBar->Append(menu, _("&Sequencer"));
	}


	void MutApp::MakeHelpMenu(wxMenuBar * menuBar)

	{
		wxMenu * menu = new wxMenu;
		MENUITEM(_("Online &Help\tF1"), CM_HELP,
			 _("Open the help Window"));
		MENUITEM(_("&Manual"), CM_HELPHANDBOOK,
			 _("Open the manual"));
		MENUITEM(_("Language &reference"), CM_HELPREFERENCE,
			 _("Open the Mutabor language reference"));
		MENUITEM_SEPARATOR;
		MENUITEM(_("&Index"), CM_HELPINDEX,
			 _("Open the help index"));
		MENUITEM(_("&Search"), CM_HELPSEARCH,
			 _("Search the help system for a specific keyword"));
		MENUITEM_SEPARATOR;
		MENUITEM(_("Help &on help"), CM_HELPONHELP,
			 _("Show Help about the help system"));

#if !(defined(__WXMAC__) || defined(__WXCOCOA__))
		MENUITEM_SEPARATOR;
#endif

		MENUITEM(_("&About"), CM_ABOUT,
			 _("Show information about the program"));
#ifdef DEBUG
		MENUITEM_SEPARATOR;
		MENUITEM(_("Stop"), cmCallExitId,
			 _("Stop the current program"));
#endif
		menuBar->Append(menu, _("&Help"));
	}

	int MutApp::OnExit()
	{
		SaveState();

		AktionTraceReset();

		TRACEC;
		InputDeviceClass::ClearDeviceList();
		TRACEC;
		OutputDeviceClass::ClearDeviceList();
		TRACEC;
		RouteClass::ClearRouteList();
		TRACEC;

		MidiUninit();

		delete document_manager;
#if defined(__WXMAC__)
		wxMenuBar::MacSetCommonMenuBar(NULL);
#endif
		delete HelpController;
		wxXmlResource::Get()->ClearHandlers();

		debug_print_pointers();
		wxASSERT(debug_is_all_deleted());

		return wxApp::OnExit();
	}

#ifdef __WXMAC__

	void MutApp::MacOpenFile(const wxString &fileName)
	{
		///\todo use the some as the command line functions
		STUBC;
		return;
		//  wxApp::MacOpenFile(fileName);

		DEBUGLOG (other, _T("Filename: %s"),fileName.c_str());

		MutFrame * frame = dynamic_cast<MutFrame*>(GetTopWindow());

		if ( !fileName )
			return;

		if (MustOpenFrame(frame))
			frame = CreateMainFrame(EditorMenu);

		frame->OpenFile(fileName);
		frame->Show();
	}

#endif

	void MutApp::SaveState()
	{
		/* \todo save Parameters of all open windows */
		wxConfigBase *config = wxConfig::Get();
		if (!config) {
			wxLogError(_("Could not get configuration storage"));
			return;
		}

		wxString oldpath = config->GetPath();

		config->SetPath(_T("/Settings"));
		config->Write(_T("Tone system"), asTS);
		config->Write(_T("Save editor"), SaveEditor);
		config->Write(_T("Color bars"), UseColorBars);

		config->SetPath(_T("Box settings"));
		BoxData::SaveAll(config);
		config->SetPath(_T(".."));

		config->SetPath(_T("DocManager"));
		document_manager->FileHistorySave(*config);
		config->SetPath(_T(".."));

		SaveRoutes(config);
		config->SetPath(oldpath);
	}

	void MutApp::RestoreState()

	{
		/* \todo restore Windows of last session. */
		wxConfigBase *config = wxConfig::Get();
		if (!config) {
			wxLogError(_("Could not get configuration storage"));
			return;
		}


		// up to Version 2.9.3 the file history does not cleanup menus
		if (document_manager) {
			int max = document_manager->GetHistoryFilesCount();
			wxFileHistory * h = document_manager->GetFileHistory();
			if (h)
				for (int i = max-1; i >= 0; i--) 
					h -> RemoveFileFromHistory(i);
		}

		wxString oldpath = config->GetPath();

		config->SetPath(_T("/Settings"));
		config->Read(_T("ToneSystem"), &asTS, true);
		config->Read(_T("SaveEditor"), &SaveEditor, true);
		config->Read(_T("ColorBars"), &UseColorBars, true);

		config->SetPath(_T("Box settings"));
		BoxData::LoadAll(config);
		config->SetPath(_T(".."));

		config->SetPath(_T("DocManager"));
		document_manager->FileHistoryLoad(*config);
		config->SetPath(_T(".."));

		MutRouteWnd * routewnd=NULL;
		MutFrame * frame = 
			dynamic_cast<MutFrame*>(wxWindow::FindWindowById(WK_ROUTE));
		if (frame) {
			wxWindowList & list = frame->GetChildren();
			for (wxWindowList::iterator i = list.begin();i!= list.end();i++) {
				routewnd = dynamic_cast<MutRouteWnd *> (*i);
				if (routewnd) break;
			}
		}
/*		if (routewnd) {
			routewnd->ClearDevices();
		}
*/	
		// emty lists
		TRACE;
		InputDeviceClass::ClearDeviceList();
		TRACE;
		OutputDeviceClass::ClearDeviceList();
		TRACE;
		RouteClass::ClearRouteList();
		TRACE;

		DebugCheckRoutes();

		LoadRoutes(config);

		DebugCheckRoutes();

		if (routewnd) {
			routewnd->InitDevices();
			routewnd->Layout();
			routewnd->FitInside();
			routewnd->Refresh();
			routewnd->Update();

			DebugCheckRoutes();
		}

		config->SetPath(oldpath);
	}

}

///\}

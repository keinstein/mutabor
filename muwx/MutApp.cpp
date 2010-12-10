/** \file MutApp.cpp
 ********************************************************************
 * Mutabor Application.
 *
 * $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/muwx/MutApp.cpp,v 1.24 2010/12/10 09:28:23 keinstein Exp $
 * Copyright:   (c) 2005,2006,2007 TU Dresden
 * \author Rüdiger Krauße <krausze@mail.berlios.de>
 * Tobias Schlemmer <keinstein@users.berlios.de>
 * \date 2005/08/12
 * $Date: 2010/12/10 09:28:23 $
 * \version $Revision: 1.24 $
 * \license wxWindows license
 *
 * $Log: MutApp.cpp,v $
 * Revision 1.24  2010/12/10 09:28:23  keinstein
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

// For compilers that support precompilation, includes "wx/wx.h".
#include "Defs.h"
#include "wx/wxprec.h"
#include "wx/xrc/xmlres.h"
#include "wx/xrc/xh_all.h"
#include "wx/fs_zip.h"
#include "wx/cshelp.h"
#include "wx/aboutdlg.h"
#include "wx/generic/aboutdlgg.h"


#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
//    #include "wx/mdi.h"
#include "wx/stdpaths.h"
#include "wx/filename.h"
#include "wx/imagpng.h"
#endif

//#include "wx/toolbar.h"

#if !defined(__WXMSW__)
#include "Icon/Mutabor.xpm"
#endif

//#include "Mutabor.rh"
#include "MutApp.h"
#include "MutFrame.h"
#include "DevMidi.h"
#include "MutConfDlg.h"
#include "resourceload.h"
#include "Action.h"

#ifdef __WXMAC__
#include <ApplicationServices/ApplicationServices.h>
#endif

wxHtmlHelpController * HelpController = (wxHtmlHelpController *) NULL;

IMPLEMENT_APP(MutApp)

// ===========================================================================
// implementation
// ===========================================================================

// ---------------------------------------------------------------------------
// MutApp
// ---------------------------------------------------------------------------


#define OPENMENU \
  { wxMenu * menu = new wxMenu;

#define CLOSEMENU(name) \
  menuBar->Append(menu, name); }

#define MENUITEM(name, id, help) \
	menu->Append(id, name, help)

#define MENUCHECKITEM(name, id, help) \
	menu->AppendCheckItem(id, name, help)

#define MENUITEM_ADD(name, id, help, add) \
	menu->Append(id, name, help, add)

#define MENUITEM_SEPARATOR \
    menu->AppendSeparator()

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
	std::cout << muT(__FUNCTION__).ToUTF8() << std::endl;
	std::cout << muT(typeid(m_locale).name()).ToUTF8() << std::endl;
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

	if (!wxApp::OnInit()) return false;
	
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
		<< (const char *)(wxString(_("Help.zip")).ToUTF8()) << std::endl;


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


	MutFrame * frame = CreateMainFrame(EditorMenu);
	MidiInit();
	RestoreState();
	((MutFrame*)frame)->RestoreState();
	wxCommandEvent event(CM_ROUTES);
	((MutFrame*)frame)->CmRoutes(event);

	return true;
}

void MutApp::OnInitCmdLine(wxCmdLineParser&  parser) {
	wxApp::OnInitCmdLine(parser);
#ifdef DEBUG
	debugFlags::InitCommandLine(parser);
#endif
}

bool MutApp::OnCmdLineParsed(wxCmdLineParser&  parser) {
	if (!wxApp::OnCmdLineParsed(parser)) return false;
#ifdef DEBUG
	debugFlags::ProcessCommandLine(parser);
#endif
	DEBUGLOG (other, _T("Command line parsed."));
	return true;
}

BEGIN_EVENT_TABLE(MutConfigDialog, ConfigDlg)
	EVT_BUTTON(::wxID_HELP, MutConfigDialog::CmHelp)
END_EVENT_TABLE()

void MutApp::CmSetup (wxCommandEvent& event)
{

	MutConfigDialog * config;
	config = new MutConfigDialog((wxFrame *) NULL);

	int value = config->ShowModal();

	config->Destroy();

	event.Skip();
}

void MutApp::CmAbout (wxCommandEvent& event)
{

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
	info.SetCopyright(_("(c) 2005-2008 TU Dresden"));
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
	//  info.AddTranslator(_("English: N.N."));

	wxGenericAboutBox(info);
	//  event.Skip(false);
}


AppAbout::AppAbout (wxWindow *parent, long style)
		: wxDialog (parent, -1, wxEmptyString,
		            wxDefaultPosition, wxDefaultSize,
		            wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER)
{

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


BEGIN_EVENT_TABLE(MutApp, wxApp)
	EVT_MENU(CM_SETUP, MutApp::CmSetup)
	EVT_MENU(CM_FILENEW, MutApp::CmFileNew)
	EVT_MENU(CM_FILEOPEN, MutApp::CmFileOpen)
	EVT_MENU(CM_EXECUTE, MutApp::CmFileOpen)
	/*    EVT_MENU(CM_FILESAVE, MutFrame::EventPassOn)
	    EVT_MENU(CM_DOACTIVATE, MutFrame::CmDoActivate)
	    EVT_MENU(CM_STOP, MutFrame::CmStop)
		EVT_UPDATE_UI(CM_ACTIVATE, MutFrame::CeActivate)
		EVT_UPDATE_UI(CM_STOP, MutFrame::CeStop)

	*/	EVT_MENU(CM_ROUTES, MutApp::CmRoutes)
	EVT_MENU(CM_ROUTELOAD, MutApp::CmRouteLoad)
	EVT_MENU(CM_ROUTESAVE, MutApp::CmRouteSave)
	EVT_MENU(CM_ROUTESAVEAS, MutApp::CmRouteSaveAs)
	/*
		EVT_MENU(CM_TOGGLEKEY, MutFrame::CmToggleKey)
		EVT_MENU(CM_TOGGLETS, MutFrame::CmToggleTS)
		EVT_MENU(CM_TOGGLEACT, MutFrame::CmToggleAct)
		EVT_MENU(CM_OWM, MutFrame::CmToggleOWM)
		EVT_MENU(CM_CAW, MutFrame::CmToggleCAW)
		EVT_UPDATE_UI(CM_TOGGLEKEY, MutFrame::CeToggleKey)
		EVT_UPDATE_UI(CM_TOGGLETS, MutFrame::CeToggleTS)
		EVT_UPDATE_UI(CM_TOGGLEACT, MutFrame::CeToggleAct)
		EVT_UPDATE_UI(CM_OWM, MutFrame::CeToggleOWM)
		EVT_UPDATE_UI(CM_CAW, MutFrame::CeToggleCAW)

		EVT_MENU(CM_INDEVSTOP, MutFrame::CmInDevStop)
		EVT_MENU(CM_INDEVPLAY, MutFrame::CmInDevPlay)
		EVT_MENU(CM_INDEVPAUSE, MutFrame::CmInDevPause)
		EVT_UPDATE_UI(CM_INDEVSTOP, MutFrame::CeInDevStop)
		EVT_UPDATE_UI(CM_INDEVPLAY, MutFrame::CeInDevPlay)
		EVT_UPDATE_UI(CM_INDEVPAUSE, MutFrame::CeInDevPause)

	*/

	EVT_MENU(CM_HELP, MutApp::CmHelp)
	EVT_MENU(CM_HELPHANDBOOK, MutApp::CmHelp)
	EVT_MENU(CM_HELPREFERENCE, MutApp::CmHelp)
	EVT_MENU(CM_HELPINDEX, MutApp::CmHelp)
	EVT_MENU(CM_HELPSEARCH, MutApp::CmHelp)
	EVT_MENU(CM_HELPONHELP, MutApp::CmHelp)
	EVT_MENU(CM_ABOUT, MutApp::CmAbout)
	//    EVT_MENU(MDI_NEW_WINDOW, MutFrame::OnNewWindow)
	EVT_MENU(CM_EXIT, MutApp::CmQuit)
	EVT_MENU(cmCallExitId, MutApp::CmCallExit)


	/*    EVT_CLOSE(MutFrame::OnClose)
	    EVT_MENU(CM_UPDATEUI, MutFrame::UpdateUI)
		EVT_IDLE(MutFrame::OnIdle)
        */
	//    EVT_SIZE(MutFrame::OnSize)
END_EVENT_TABLE()

MutFrame* MutApp::CreateMainFrame(MenuType type, wxWindowID id)
{
	MutFrame* frame = new MutFrame((wxFrame *)NULL, wxID_ANY, _T("Mutabor"),
	                               wxDefaultPosition, wxDefaultSize, //wxSize(500, 400),
	                               wxDEFAULT_FRAME_STYLE | wxHSCROLL | wxVSCROLL);
#ifdef __WXMSW__
#if 0
	// Experimental: change the window menu
	wxMenu* windowMenu = new wxMenu;
	windowMenu->Append(5000, _T("My menu item!"));
	frame->SetWindowMenu(windowMenu);
#endif
#endif

	// Give it an icon
#ifdef __WXMSW__
	frame->SetIcon(wxIcon(_T("mutabor_icn")));
#else
	frame->SetIcon(wxIcon( mutabor_xpm ));
#endif

	// Make a menubar

	wxMenuBar *menuBar = new wxMenuBar;
	MakeFileMenu(menuBar, type);
	MakeLogicMenu(menuBar);
	MakeRoutesMenu(menuBar);
	MakeViewMenu(menuBar, type);
	MakeSequencerMenu(menuBar);
	MakeHelpMenu(menuBar);

	// Associate the menu bar with the frame
	frame->SetMenuBar(menuBar);

#if wxUSE_STATUSBAR
	frame->CreateStatusBar();
#endif // wxUSE_STATUSBAR

	frame->Show(true);

	RegisterFrame(frame);

	return frame;
}

void MutApp::CmFileNew (wxCommandEvent& event)
{
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

#ifdef DEBUG
	printf("MutApp::CmFileNew: file new: done.\n");

#endif
	event.Skip(false);
}


void MutApp::CmFileOpen (wxCommandEvent& event)
{
	wxWindow * topwindow=GetTopWindow();

	event.Skip(false);

	wxString path = FileNameDialog(topwindow);

	MutFrame * frame = dynamic_cast<MutFrame*>(topwindow);

	if ( !path )
		return;

	if (MustOpenFrame(frame))
		frame = CreateMainFrame(EditorMenu);

	frame->OpenFile(path);

#ifdef DEBUG
	std::cerr << "MutApp:CmFileOpen " << CM_EXECUTE << " == "
	<< event.GetId() << "?" << std::endl;

#endif

	switch (event.GetId()) {

	case CM_EXECUTE:
		wxCommandEvent e(wxEVT_COMMAND_MENU_SELECTED,CM_ACTIVATE);

		frame->ProcessEvent(e);

		break;
	}

}

void MutApp::CmRoutes (wxCommandEvent& event)
{

	wxWindow * topwindow=GetTopWindow();

#ifdef DEBUG
	std::cerr << "MutApp::CmRoutes: window "
	<< wxWindow::FindWindowById(WK_ROUTE)
	<< " casted "
	<< dynamic_cast <MutFrame *>(wxWindow::FindWindowById(WK_ROUTE))
	<< std::endl;
#endif

	MutFrame * frame = dynamic_cast<MutFrame*>(wxWindow::FindWindowById(WK_ROUTE));

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

	FrameHash::iterator it;

	DEBUGLOG (other, _T("Starting Loop"));

	while (Pending())
		Dispatch();

	DEBUGLOG (other, _T("Dispatched all events"));

	wxIdleMode imode = wxIdleEvent::GetMode();

	wxIdleEvent::SetMode(wxIDLE_PROCESS_ALL);

	while ((window = GetTopWindow())) {
#ifdef DEBUG
		DEBUGLOG (other, _("Closing window of class %s"), muT(typeid(*(window)).name()).c_str());
#endif

		if (!window->Close()) {
			wxIdleEvent::SetMode(imode);
			quitting = false;
			return;
		}

		DEBUGLOG (other, _T("Closed window"));

		// empty queue and process idle event to delete the frame

		while (Pending())
			Dispatch();

		//   wxIdleEvent idle;
		//ProcessEvent(idle);
		//while(Pending())
		//  Dispatch();
		DeletePendingObjects();

		DEBUGLOG (other, _T("Dispatched all events"));
	}


	DEBUGLOG (other, _T("finished loop"));
}



void MutApp::RegisterFrame (wxFrame * f)
{
	frames[f] = f;
}

void MutApp::UnregisterFrame (wxFrame * f)
{
	frames.erase(f);
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

void MutApp::MakeHelpMenu(wxMenuBar * menuBar)

{
	OPENMENU;
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
	CLOSEMENU(_("&Help"));
}

void MutApp::MakeSequencerMenu(wxMenuBar * menuBar)
{
	OPENMENU;
	MENUITEM(_("&Play"), CM_INDEVPLAY,
	         _("Start playing the music from input file devices"));
	MENUITEM(_("St&op"), CM_INDEVSTOP,
	         _("Stop playing the music from input file devices"));
	MENUITEM(_("P&ause"), CM_INDEVPAUSE,
	         _("Pause plaing the music from input file devices"));
	CLOSEMENU(_("&Sequencer"));
}

void MutApp::MakeViewMenu(wxMenuBar * menuBar, MenuType type)
{
	OPENMENU;
	/*	MENUCHECKITEM(_("&Status bar"), IDW_STATUSBAR,
	   _("Toggle status bar on/off"));
	MENUCHECKITEM(_("&Toolbar"), IDW_TOOLBAR,
	   _("Toggle tool bar on/off"));
	MENUITEM_SEPARATOR;
	*/
	MENUCHECKITEM(_("&Routes\tF11"), CM_ROUTES,
	              _("Open route configuration window"));

	if (type != ProgramMenu) {
		MENUITEM_SEPARATOR;
		MENUCHECKITEM(_("Current ke&ys\tF5"), CM_TOGGLEKEY,
		              _("Show current keys window"));
		MENUCHECKITEM(_("&Tone system\tF6"), CM_TOGGLETS,
		              _("Show tone system window"));
		MENUCHECKITEM(_("&Actions\tF7"), CM_TOGGLEACT,
		              _("Show current actions window"));
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

	CLOSEMENU(_("&View"));
}

void MutApp::MakeRoutesMenu(wxMenuBar * menuBar)
{
	OPENMENU;
	MENUITEM(_("&Load routes"), CM_ROUTELOAD,
	         _("Load the current route configuration from a file"));
	MENUITEM(_("&Save routes"), CM_ROUTESAVE,
	         _("Save current route configuration to a file."));
	MENUITEM(_("Save routes &as"), CM_ROUTESAVEAS,
	         _("Save current route configuration to a file with a new name."));
	CLOSEMENU(_("&Routes"));
}

void MutApp::MakeLogicMenu(wxMenuBar * menuBar)
{
	OPENMENU;
	MENUITEM(_("&Compile\tAlt+F9"), CM_COMPILE, _("Load the actual file into the Mutabor Kernel."));
	MENUITEM(_("&Activate\tF9"), CM_ACTIVATE, _("Activate the Mutabor Kernel."));
	MENUITEM(_("&Stop\tF8"), CM_STOP, _("Stop the Mutabor Kernel."));
	MENUITEM_SEPARATOR;
	MENUITEM(_("&Panic\tF12"), CM_PANIC, _("Send \"all notes off\" signal to on all MIDI Channels."));
	CLOSEMENU(_("&Logic"));
}

void MutApp::MakeFileMenu(wxMenuBar * menuBar, MenuType type)
{
	OPENMENU;
	MENUITEM(_("&New\tCtrl+N"), CM_FILENEW,
	         _("Create a new logic file."));
	MENUITEM(_("&Open...\tCtrl+O"), CM_FILEOPEN,
	         _("Open a logic file in editor window"));

	if (type == EditorMenu || type == RouteMenu) {
		MENUITEM(_("&Save\tCtrl+S"), CM_FILESAVE,
		         _("Save the current file."));
		MENUITEM(_("Save &As...\tShift+Ctrl+S"), CM_FILESAVEAS,
		         _("Save the current file with a new file name"));
	}

	MENUITEM_SEPARATOR;

	MENUITEM(_("&Execute\tCtrl+F9"), CM_EXECUTE,
	         _("Load a logic file an immediately activate it"));

#if !(defined(__WXMAC__) || defined(__WXCOCOA__))
	MENUITEM_SEPARATOR;
#endif

	MENUITEM(_("&Preferences"), CM_SETUP, _("Edit program settings"));

#if !(defined(__WXMAC__) || defined(__WXCOCOA__))
	MENUITEM_SEPARATOR;
	MENUITEM(_("E&xit"), CM_EXIT, _("Quit Mutabor"));
	CLOSEMENU(_("&File"));
#else
	MENUITEM(_T("E&xit"), CM_EXIT, _("Quit Mutabor"));
	CLOSEMENU(getContextLocal(_("@MAC|&File")));
#endif
}

int MutApp::OnExit()
{
	SaveState();
	AktionTraceReset();
	MidiUninit();
#if defined(__WXMAC__)
	wxMenuBar::MacSetCommonMenuBar(NULL);
#endif
	delete HelpController;
	wxXmlResource::Get()->ClearHandlers();
	return wxApp::OnExit();
}

#ifdef __WXMAC__

void MutApp::MacOpenFile(const wxString &fileName)
{
	//  wxApp::MacOpenFile(fileName);

	DEBUGLOG (other, _T("Filename: %s"),fileName.c_str());

	MutFrame * frame = dynamic_cast<MutFrame*>(GetTopWindow());

	if ( !fileName )
		return;

	if (MustOpenFrame(frame))
		frame = CreateMainFrame(EditorMenu);

	frame->OpenFile(fileName);
}

#endif

void MutApp::SaveState()
{
	/* \todo save Parameters of all open windows */
	wxConfigBase *config = wxConfig::Get();

	wxString oldpath = config->GetPath();

	config->SetPath(_T("/Settings"));
	config->Write(_T("Tone system"), asTS);
	config->Write(_T("Save editor"), SaveEditor);
	config->Write(_T("Color bars"), UseColorBars);

	config->SetPath(_T("Box settings"));

	for (size_t box = 0 ; box < MAX_BOX ; box++) {
		config->SetPath(wxString::Format(_T("%d"),box));
		config->Write(_T("KeyWindow"), TextBoxWanted[box][WK_KEY]);
		config->Write(_T("ToneSystemWindow"), TextBoxWanted[box][WK_TS]);
		config->Write(_T("ActionsWindow"), TextBoxWanted[box][WK_ACT]);
		config->SetPath(_T(".."));
	}

	config->SetPath(_T(".."));

	SaveRoutes(config);
	config->SetPath(oldpath);
}

void MutApp::RestoreState()

{
	/* \todo restore Windows of last session. */
	wxConfigBase *config = wxConfig::Get();

	wxString oldpath = config->GetPath();

	config->SetPath(_T("/Settings"));
	config->Read(_T("ToneSystem"), &asTS, true);
	config->Read(_T("SaveEditor"), &SaveEditor, true);
	config->Read(_T("ColorBars"), &UseColorBars, true);

	config->SetPath(_T("Box settings"));

	for (size_t box = 0 ; box < MAX_BOX ; box++) {
		config->SetPath(wxString::Format(_T("%d"),box));
		config->Read(_T("KeyWindow"), &TextBoxWanted[box][WK_KEY], false);
		config->Read(_T("ToneSystemWindow"), &TextBoxWanted[box][WK_TS], false);
		config->Read(_T("ActionsWindow"), &TextBoxWanted[box][WK_ACT], false);
		config->SetPath(_T(".."));
	}

	config->SetPath(_T(".."));

	LoadRoutes(config);
	config->SetPath(oldpath);
}

///\}

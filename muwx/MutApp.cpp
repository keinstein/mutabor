/** \file MutApp.cpp
 ********************************************************************
 * Mutabor Application.
 *
 * $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/muwx/MutApp.cpp,v 1.11 2008/03/11 10:37:34 keinstein Exp $
 * Copyright:   (c) 2005,2006,2007 TU Dresden
 * \author Rüdiger Krauße <krausze@mail.berlios.de>
 * Tobias Schlemmer <keinstein@users.berlios.de>
 * \date 2005/08/12
 * $Date: 2008/03/11 10:37:34 $
 * \version $Revision: 1.11 $
 * \license wxWindows license
 *
 * $Log: MutApp.cpp,v $
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
#include <wx/wxprec.h>
#include <wx/xrc/xmlres.h>
#include <wx/xrc/xh_all.h>
#include <wx/fs_zip.h>
#include <wx/cshelp.h>
#include <wx/aboutdlg.h>
#include <wx/generic/aboutdlgg.h>


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

#include "Mutabor.rh"
#include "MutApp.h"
#include "MutFrame.h"
#include "DevMidi.h"
#include "MutConfDlg.h"
#include "EDevice.h"

MutFrame *frame = (MutFrame *) NULL;
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
  SetAppName(_T(PACKAGE));
  SetClassName(_T(PACKAGE_NAME));
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

  wxStandardPaths & sp = (wxStandardPaths &) (wxStandardPaths::Get());

#ifdef DEBUG
  std::cout << "ConfigDir:        "
	    << sp.GetConfigDir().ToUTF8() << std::endl
	    << "DataDir:          " 
	    << sp.GetDataDir().ToUTF8() << std::endl
	    << "DocumentsDir:     "
	    << sp.GetDocumentsDir().ToUTF8() << std::endl
	    << "ExecutablePath:   " 
	    << sp.GetExecutablePath().ToUTF8() << std::endl
    
#if defined(__UNIX__) && !defined(__WXMAC__)
	    << "InstallPrefix:    " << sp.GetInstallPrefix().ToUTF8() 
	    << std::endl
#endif
	    << "LocalDataDir:     " << sp.GetLocalDataDir().ToUTF8() 
	    << std::endl
	    << "PluginsDir:       " << sp.GetPluginsDir().ToUTF8() 
	    << std::endl
	    << "ResourcesDir:     " << sp.GetResourcesDir().ToUTF8() 
	    << std::endl
	    << "TempDir:          " << sp.GetTempDir().ToUTF8() 
	    << std::endl
	    << "UserConfigDir:    " << sp.GetUserConfigDir().ToUTF8() 
	    << std::endl
	    << "UserDataDir:      " << sp.GetUserDataDir().ToUTF8() 
	    << std::endl
	    << "UserLocalDataDir: " << sp.GetUserLocalDataDir().ToUTF8() 
	    << std::endl;
    
  std::cout 
            << "LocalizedResourcesDir(Can): " 
	    << sp.GetLocalizedResourcesDir(m_locale.GetCanonicalName(), 
					   sp.ResourceCat_None).ToUTF8()
	    << std::endl
            << "LocalizedResourcesDir(Can,Messages): " 
	    << sp.GetLocalizedResourcesDir(m_locale.GetCanonicalName(),
					   sp.ResourceCat_Messages).ToUTF8()
	    << std::endl
            << "LocalizedResourcesDir(): " 
	    << sp.GetLocalizedResourcesDir(m_locale.GetName(), 
					   sp.ResourceCat_None).ToUTF8()
	    << std::endl
            << "LocalizedResourcesDir(Messages): " 
	    << sp.GetLocalizedResourcesDir(m_locale.GetName(),
					   sp.ResourceCat_Messages).ToUTF8()
	    << std::endl;
#endif 
 
  // We are using .png files for some extra bitmaps.
  wxImageHandler * pnghandler = new wxPNGHandler;
  wxImage::AddHandler(pnghandler);
  wxImage::AddHandler(new wxGIFHandler);

  wxFileSystem::AddHandler(new wxZipFSHandler);

  wxXmlResource::Get()->InitAllHandlers();
  wxXmlResource::Get()->Load(GetResourceName(_T("Mutabor.xrc")));

  wxHelpControllerHelpProvider* provider = new wxHelpControllerHelpProvider;
  wxHelpProvider::Set(provider);

  HelpController = new wxHtmlHelpController();

  provider->SetHelpController(HelpController);

  // we want to name the help files according to the lanuage.
  if (!HelpController->Initialize(GetResourceName(_("manual.zip")))) 
    std::cerr << "Warning: could not initialize Help system: " 
	      << wxString(_("manual.zip")).ToUTF8() << std::endl;
  //  HelpController->AddBook(_("manual.zip"));
  //  HelpController->DisplayIndex();

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


  frame = CreateMainFrame(EditorMenu);
  MidiInit();
  RestoreState();
  ((MutFrame*)frame)->RestoreState();
  

  return true;
}


void MutApp::CmSetup (wxCommandEvent& event)
{

	MutConfigDialog * config;
	config = new MutConfigDialog((wxFrame *) NULL);
	int value = config->ShowModal();
	std::cout << "MutApp::CmSetup: not implemented. Got value " 
		  << value << std::endl;
//	if 
	config->Destroy();
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
  info.AddArtist(_("Rudolf Wille (mathematical foundation)\n"));
  info.AddArtist(_("Tobias Schlemmer (new icon/splash)"));
  info.AddDeveloper(_("Bernhard Ganter\n"));
  info.AddDeveloper(_("Volker Abel\n"));
  info.AddDeveloper(_("Peter Reiss\n"));
  info.AddDeveloper(_("Ruediger Krausze <krausze@mail.berlios.de>\n"));
  info.AddDeveloper(_("Tobias Schlemmer <keinstein@mail.berlios.de>"));
  info.AddDocWriter(_("Volker Abel\n"));
  info.AddDocWriter(_("Peter Reiss\n"));
  info.AddDocWriter(_("Ruediger Krausze <krausze@mail.berlios.de>\n"));
  info.AddDocWriter(_("Tobias Schlemmer <keinstein@mail.berlios.de>"));
  //  info.AddTranslator(_("English: N.N."));
  
  wxGenericAboutBox(info);
}


AppAbout::AppAbout (wxWindow *parent, long style)
        : wxDialog (parent, -1, wxEmptyString,
                    wxDefaultPosition, wxDefaultSize,
                    wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER) {
					
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
/*    EVT_MENU(CM_FILESAVE, MutFrame::EventPassOn)
    EVT_MENU(CM_DOACTIVATE, MutFrame::CmDoActivate)
    EVT_MENU(CM_STOP, MutFrame::CmStop)
	EVT_UPDATE_UI(CM_ACTIVATE, MutFrame::CeActivate)
	EVT_UPDATE_UI(CM_STOP, MutFrame::CeStop)
    
*/	EVT_MENU(CM_ROUTES, MutApp::CmRoutes)
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

*/	EVT_MENU(CM_ABOUT, MutApp::CmAbout)
EVT_MENU(CM_HELPINDEX, MutApp::CmHelp)
EVT_MENU(CM_HELPHANDBOOK, MutApp::CmHelp)
EVT_MENU(CM_HELPONHELP, MutApp::CmHelp)
//    EVT_MENU(MDI_NEW_WINDOW, MutFrame::OnNewWindow)
    EVT_MENU(CM_EXIT, MutApp::CmQuit)

/*    EVT_CLOSE(MutFrame::OnClose)
    EVT_MENU(CM_UPDATEUI, MutFrame::UpdateUI)
*/	EVT_IDLE(MutFrame::OnIdle) 
//    EVT_SIZE(MutFrame::OnSize)
END_EVENT_TABLE()

MutFrame* MutApp::CreateMainFrame(MenuType type, wxWindowID id) {
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

void MutApp::CmFileNew (wxCommandEvent& event) {
#ifdef DEBUG
	printf("MutApp::CmFileNew\n");
#endif

	frame = CreateMainFrame(EditorMenu);
	frame->CmFileNew(event);
}


void MutApp::CmFileOpen (wxCommandEvent& event) {
	frame = CreateMainFrame(EditorMenu);
	frame->CmFileOpen(event);
}

void MutApp::CmRoutes (wxCommandEvent& event) {
	frame = new MutFrame((wxFrame *) NULL,WK_ROUTE, wxString().Format(_("%s -- Routes"),_(PACKAGE_NAME)),
		wxDefaultPosition,wxDefaultSize,wxDEFAULT_FRAME_STYLE | wxHSCROLL | wxVSCROLL);
	RegisterFrame(frame);
	frame->CmRoutes(event);
	frame->Show(true);
}

void MutApp::CmHelp (wxCommandEvent& event) {
  ShowHelp(event.GetId());
}

void MutApp::ShowHelp(int commandId) {
  switch (commandId) {
  case CM_HELPINDEX:
    HelpController->DisplayContents();
    break;
  case CM_HELPHANDBOOK:
  case CM_HELPONHELP:
  case CM_HELPCOMMON:
    HelpController->DisplayContents();
    break;
  case CM_HELPSEARCH:
    {
      wxString key = wxGetTextFromUser(_("Search for?"),
				       _("Search help for keyword"),
				       wxEmptyString,
				       GetTopWindow());
      if(! key.IsEmpty())
	HelpController->KeywordSearch(key);
    }
    break;
  }
}

void MutApp::CmQuit (wxCommandEvent& event) {
#ifdef DEBUG
	printf("MutApp::CmQuit\n");
#endif

	SetExitOnFrameDelete(true);
	//		Exit();

	quitting = true;


	wxWindow * window;
	//	if (frames.empty()) {
	if ((window = GetTopWindow()) == NULL) {
#ifdef DEBUG
		printf("MutApp::CmQuit: No Frames.\n");
#endif
		quitting = false;
		event.Skip(true);
		return;
	}

	
	wxFrame * frame;
	FrameHash::iterator it;

	while (window = GetTopWindow()) {
	  if (!window->Close()) return;
	  while (Pending()) Dispatch();
	}

#ifdef DEBUG
	printf("MutApp::CmQuit: Starting Loop\n");
#endif



	/*

    for( it = frames.begin(); !frames.empty(); it = frames.begin() )
    {
        frame	= it->second;
		
#ifdef DEBUG
		printf("MutApp::CmQuit: Trying to delete Frame %x/%x\n",frame,frame);
#endif

		if (frame) {
			if (!frame -> Close()) {
				// the frame vetoed.
				event.Skip();
				quitting = false;
				return;
			}
		}
    }
	*/
}



void MutApp::RegisterFrame (wxFrame * f) {
	frames[f] = f;
}

void MutApp::UnregisterFrame (wxFrame * f) {
	frames.erase(f);
}

wxString MutApp::GetResourceName(const wxString & file){
  const wxLocale * m_locale = wxGetLocale();
  wxStandardPathsBase & sp = wxStandardPaths::Get();
  wxString localename = m_locale->GetCanonicalName();
  wxFileName rcname(sp.GetLocalizedResourcesDir(localename),file);

#ifdef DEBUG
  std::cerr << "Trying do load resources..." << std::endl
	    << "Trying " << rcname.GetFullPath().ToUTF8() << std::endl
	    << (sp.GetResourcesDir().ToUTF8()) << std::endl;
#endif

  if (!rcname.IsFileReadable()) {
    rcname.SetPath(sp.GetLocalizedResourcesDir(localename.BeforeFirst(_T('_'))));
#ifdef DEBUG
    std::cerr << "Trying " << rcname.GetFullPath().ToUTF8() << std::endl;
#endif

    if (!rcname.IsFileReadable()){
      rcname.SetPath(sp.GetResourcesDir());
#ifdef DEBUG
      std::cerr << "Trying " << rcname.GetFullPath().ToUTF8() << std::endl;
#endif
    }

  }
  return rcname.GetFullPath(); 
}

void MutApp::MakeHelpMenu(wxMenuBar * menuBar) {
  OPENMENU;
  MENUITEM(_("&Index"), CM_HELPINDEX,
	   _("Open the help index"));
  MENUITEM(_("&Handbook"), CM_HELPHANDBOOK,
	   _("Open the Handbook"));
  MENUITEM(_("&Help on help"), CM_HELPONHELP,
	   _("Show Help about the help system"));

#if !(defined(__WXMAC__) || defined(__WXCOCOA__))
  MENUITEM_SEPARATOR;
#endif

  MENUITEM(_("&About"), CM_ABOUT,
	   _("Show information about the program"));
  CLOSEMENU(_("&Help"));
}

void MutApp::MakeSequencerMenu(wxMenuBar * menuBar) {
  OPENMENU;
  MENUITEM(_("&Play"), CM_INDEVPLAY,
	   _("Start playing the music from input file devices"));
  MENUITEM(_("St&op"), CM_INDEVSTOP,
	   _("Stop playing the music from input file devices"));
  MENUITEM(_("P&ause"), CM_INDEVPAUSE,
	   _("Pause plaing the music from input file devices"));
  CLOSEMENU(_("&Sequencer"));
}

void MutApp::MakeViewMenu(wxMenuBar * menuBar, MenuType type) {
  	OPENMENU;
	MENUCHECKITEM(_("&Status bar"), IDW_STATUSBAR,
	   _("Toggle status bar on/off"));
	MENUCHECKITEM(_("&Toolbar"), IDW_TOOLBAR,
	   _("Toggle tool bar on/off"));
	MENUITEM_SEPARATOR;
	MENUITEM(_("&Routes\tF11"), CM_ROUTES,
	   _("Open route configuration window"));

	if (type != ProgramMenu) {
	  MENUITEM_SEPARATOR;
	  MENUCHECKITEM(_("Current ke&ys\tF5"), CM_TOGGLEKEY,
			_("Show current keys window"));
	  MENUCHECKITEM(_("&Tone system\tF6"), CM_TOGGLETS,
			_("Show tone system window"));
	  MENUCHECKITEM(_("&Actions\tF7"), CM_TOGGLEACT,
			_("Show current actions window"));
	  MENUITEM_SEPARATOR;
	  MENUCHECKITEM(_("&One window mode"), CM_OWM,
			_("Toggle logic satus window: one each or one common"));
	  MENUCHECKITEM(_("One &common action window"), CM_CAW,
			_("Toggle action window mode: one each or one common"));
	  MENUITEM_SEPARATOR;
	  MENUITEM(_("Select &Box"), CM_SELECTBOX,
		   _("Select current Box"));
	}

	CLOSEMENU(_("&View"));
}

void MutApp::MakeRoutesMenu(wxMenuBar * menuBar) {
  OPENMENU;
  MENUITEM(_("&Load routes"), CM_ROUTELOAD,
	   _("Load the current route configuration from a file")); 
  MENUITEM(_("&Save routes"), CM_ROUTESAVE, 
	   _("Save current route configuration to a file."));
  MENUITEM(_("Save routes &as"), CM_ROUTESAVEAS, 
	   _("Save current route configuration to a file with a new name."));
  CLOSEMENU(_("&Routes"));
}

void MutApp::MakeLogicMenu(wxMenuBar * menuBar) {
	OPENMENU;
	MENUITEM(_("&Compile\tAlt+F9"), CM_COMPILE, _("Load the actual file into the Mutabor Kernel."));
	MENUITEM(_("&Activate\tF9"), CM_ACTIVATE, _("Activate the Mutabor Kernel."));
	MENUITEM(_("&Stop\tF8"), CM_STOP, _("Stop the Mutabor Kernel."));
	MENUITEM_SEPARATOR;
	MENUITEM(_("&Panic\tF12"), CM_PANIC, _("Send \"all notes off\" signal to on all MIDI Channels."));
	CLOSEMENU(_("&Logic"));
}

void MutApp::MakeFileMenu(wxMenuBar * menuBar, MenuType type) {
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

int MutApp::OnExit() {
  SaveState();
  return wxApp::OnExit();
}

void MutApp::SaveState()
{
  /* \todo save Parameters of all open windows */
  wxConfigBase *config = wxConfig::Get();

  wxString oldpath = config->GetPath();
 
  config->SetPath(_T("/Settings"));
  config->Write(_T("Tone system"), asTS);
  config->Write(_T("Save editor"), SaveEditor);
  config->Write(_T("Color bars"), UseColorBars);

  config->Write(_T("KeyWindow"), TextBoxWanted[WK_KEY]);
  config->Write(_T("ToneSystemWindow"), TextBoxWanted[WK_TS]);
  config->Write(_T("ActionsWindow"), TextBoxWanted[WK_ACT]);

  WriteRoutes(config);
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
    
  config->Read(_T("KeyWindow"), &TextBoxWanted[WK_KEY], false);
  config->Read(_T("ToneSystemWindow"), &TextBoxWanted[WK_TS], false);
  config->Read(_T("ActionsWindow"), &TextBoxWanted[WK_ACT], false);

  ScanRoutes(config);
  config->SetPath(oldpath);
}

///\}

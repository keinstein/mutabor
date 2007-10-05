/////////////////////////////////////////////////////////////////////////////
// Name:        MutApp.cpp
// Purpose:     Mutabor Application
// Author:      R. Krauﬂe
// Modified by:
// Created:     12.08.05
// Copyright:   (c) R. Krauﬂe
// Licence:     wxWindows license
/////////////////////////////////////////////////////////////////////////////

// ---------------------------------------------------------------------------
// headers
// ---------------------------------------------------------------------------

// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
    #pragma hdrstop
#endif

#ifndef WX_PRECOMP
    #include "wx/wx.h"
//    #include "wx/mdi.h"
#endif

//#include "wx/toolbar.h"

#if !defined(__WXMSW__)
    #include "Icon/Mutabor.xpm"
#endif

#include "Mutabor.rh"
#include "MutApp.h"
#include "MutFrame.h"
#include "DevMidi.h"

MutFrame *frame = (MutFrame *) NULL;

IMPLEMENT_APP(MutApp)

// ===========================================================================
// implementation
// ===========================================================================

// ---------------------------------------------------------------------------
// MutApp
// ---------------------------------------------------------------------------


#define OPENMENU \
	menu = new wxMenu;

#define CLOSEMENU(name) \
	menuBar->Append(menu, name);

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
  // initialize the languages
      long lng = wxLANGUAGE_DEFAULT;

    if ( argc == 2 )
    {
        // the parameter must be the lang index
        wxString tmp(argv[1]);
        tmp.ToLong(&lng);
    }

    static const wxLanguage langIds[] =
    {
        wxLANGUAGE_DEFAULT,
	//        wxLANGUAGE_FRENCH,
        wxLANGUAGE_GERMAN,
	//        wxLANGUAGE_RUSSIAN,
	//        wxLANGUAGE_BULGARIAN,
	//        wxLANGUAGE_CZECH,
	//        wxLANGUAGE_POLISH,
	//        wxLANGUAGE_SWEDISH,
#if wxUSE_UNICODE
	//        wxLANGUAGE_JAPANESE,
	//        wxLANGUAGE_GEORGIAN,
#endif
        wxLANGUAGE_ENGLISH,
        wxLANGUAGE_ENGLISH_US
    };

    if ( lng == -1 )
    {
        // note that it makes no sense to translate these strings, they are
        // shown before we set the locale anyhow
        const wxString langNames[] =
        {
            _T("System default"),
	    //            _T("French"),
            _T("German"),
	    //            _T("Russian"),
	    //            _T("Bulgarian"),
	    //            _T("Czech"),
	    //            _T("Polish"),
	    //            _T("Swedish"),
#if wxUSE_UNICODE
	    //            _T("Japanese"),
	    //            _T("Georgian"),
#endif
            _T("English"),
            _T("English (U.S.)")
        };

        // the arrays should be in sync
        wxCOMPILE_TIME_ASSERT( WXSIZEOF(langNames) == WXSIZEOF(langIds),
                               LangArraysMismatch );

        lng = wxGetSingleChoiceIndex
              (
                _T("Please choose language:"),
                _T("Language"),
                WXSIZEOF(langNames),
                langNames
              );
    }

    if ( lng != -1 )
        m_locale.Init(langIds[lng]);

    // normally this wouldn't be necessary as the catalog files would be found
    // in the default locations, but under Windows then the program is not
    // installed the catalogs are in the parent directory (because the binary
    // is in a subdirectory of samples/internat) where we wouldn't find them by
    // default
    wxLocale::AddCatalogLookupPathPrefix(wxT("."));
    wxLocale::AddCatalogLookupPathPrefix(wxT(".."));

    // Initialize the catalogs we'll be using
    m_locale.AddCatalog(wxT("mutabor"));

    // this catalog is installed in standard location on Linux systems and
    // shows that you may make use of the standard message catalogs as well
    //
    // if it's not installed on your system, it is just silently ignored
#ifdef __LINUX__
    {
        wxLogNull noLog;
        m_locale.AddCatalog(_T("fileutils"));
    }
#endif

/* TODO: Implement common behaviour for Mac OS   
  wxMenuBar *menubar = new wxMenuBar;
  // add open, new, etc options to your menubar.

*/
#if defined(__WXMAC__)
// || defined(__WXCOCOA__)
    // Make a common menubar

    wxApp::SetExitOnFrameDelete(false);

	wxApp::s_macAboutMenuItemId = CM_ABOUT;
	wxApp::s_macPreferencesMenuItemId = CM_SETUP;
	wxApp::s_macExitMenuItemId = CM_EXIT;
	wxApp::s_macHelpMenuTitleName = _("&Help");

    wxMenuBar *menuBar = new wxMenuBar;
	wxMenu *menu;
	OPENMENU;
	MENUITEM(_("&New\tCtrl-N"), CM_FILENEW, _("Create a new child window"));
	MENUITEM(_("&Open...\tCtrl+O"), CM_FILEOPEN, wxT(""));
	MENUITEM_SEPARATOR;
	MENUITEM(_("&Execute\tCtrl-F9"), CM_EXECUTE, wxT(""));
	MENUITEM_SEPARATOR;
	MENUITEM(_("&Preferences"), CM_SETUP, wxT(""));
	MENUITEM(_T("E&xit"), CM_EXIT, _("Quit the program"));
	CLOSEMENU(_("&File"));

	OPENMENU;
	MENUITEM(_("&Load routes"), CM_ROUTELOAD, wxT("")); 
	CLOSEMENU(_("&Routes"));

	OPENMENU;
	MENUITEM(_("&Routes\tF11"), CM_ROUTES, wxT(""));
	CLOSEMENU(_("&View"));

	OPENMENU;
	MENUITEM(_("&Index"), CM_HELPINDEX, wxT(""));
	MENUITEM(_("&Handbook"), CM_HELPHANDBOOK, wxT(""));
	MENUITEM(_("&Help on help"), CM_HELPONHELP, wxT(""));
	MENUITEM_SEPARATOR;
	MENUITEM(_("&About"), CM_ABOUT, wxT(""));
	CLOSEMENU(_("&Help"));
	
	wxMenuBar::MacSetCommonMenuBar(menuBar);
#endif


    frame = CreateMainFrame();
    SetTopWindow(frame);

	((MutFrame*)frame)->RestoreState();

	MidiInit();

    return true;
}


void MutApp::OnAbout (wxCommandEvent& event)
{
  (void)wxMessageBox(wxString::Format(_("%s\nAuthors: \n%s\nUsage: %s"),
				      mumT(PACKAGE_STRING),
				      _T("Ruediger Krausze <krausze@mail.berlios.de>\n")
				      _T("Tobias Schlemmer <keinstein@mail.berlios.de>\n"),
				      mumT(PACKAGE)),
		     wxString::Format(_("About %s"),mumT(PACKAGE_NAME)));
}


BEGIN_EVENT_TABLE(MutApp, wxApp)
/*    EVT_MENU(CM_FILENEW, MutFrame::CmFileNew)
    EVT_MENU(CM_FILEOPEN, MutFrame::CmFileOpen)
    EVT_MENU(CM_FILESAVE, MutFrame::EventPassOn)
    EVT_MENU(CM_DOACTIVATE, MutFrame::CmDoActivate)
    EVT_MENU(CM_STOP, MutFrame::CmStop)
	EVT_UPDATE_UI(CM_ACTIVATE, MutFrame::CeActivate)
	EVT_UPDATE_UI(CM_STOP, MutFrame::CeStop)
    
	EVT_MENU(CM_ROUTES, MutFrame::CmRoutes)

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

*/	EVT_MENU(CM_ABOUT, MutApp::OnAbout)
//    EVT_MENU(MDI_NEW_WINDOW, MutFrame::OnNewWindow)
/*    EVT_MENU(CM_EXIT, MutFrame::OnQuit)

    EVT_CLOSE(MutFrame::OnClose)
    EVT_MENU(CM_UPDATEUI, MutFrame::UpdateUI)
*/	EVT_IDLE(MutFrame::OnIdle) 
//    EVT_SIZE(MutFrame::OnSize)
END_EVENT_TABLE()

MutFrame* MutApp::CreateMainFrame() {
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
	wxMenu *menu;
	OPENMENU;
	MENUITEM(_("&New\tCtrl-N"), CM_FILENEW, _("Create a new child window"));
	MENUITEM(_("&Open...\tCtrl+O"), CM_FILEOPEN, wxT(""));
	MENUITEM(_("&Save\tCtrl+S"), CM_FILESAVE, wxT(""));
	MENUITEM(_("Save &As...\tShift+Ctrl+S"), CM_FILESAVEAS, wxT(""));
	MENUITEM_SEPARATOR;
	MENUITEM(_("&Execute\tCtrl-F9"), CM_EXECUTE, wxT(""));
	MENUITEM_SEPARATOR;
	MENUITEM(_("&Preferences"), CM_SETUP, wxT(""));
#if !(defined(__WXMAC__) || defined(__WXCOCOA__))
	MENUITEM_SEPARATOR;
	MENUITEM(_("E&xit"), CM_EXIT, _("Quit the program"));
#else
	MENUITEM(_T("E&xit"), CM_EXIT, _("Quit the program"));
#endif
	CLOSEMENU(_("&File"));

	OPENMENU;
	MENUITEM(_("&Compile\tAlt-F9"), CM_COMPILE, wxT(""));
	MENUITEM(_("&Activate\tF9"), CM_ACTIVATE, wxT(""));
	MENUITEM(_("&Stop\tF8"), CM_STOP, wxT(""));
	MENUITEM_SEPARATOR;
	MENUITEM(_("&Panic\tF12"), CM_PANIC, wxT(""));
	CLOSEMENU(_("&Logic"));

	OPENMENU;
	MENUITEM(_("&Load routes"), CM_ROUTELOAD, wxT("")); 
	MENUITEM(_("&Save routes"), CM_ROUTESAVE, wxT(""));
	MENUITEM(_("Save routes &as"), CM_ROUTESAVEAS, wxT(""));
	CLOSEMENU(_("&Routes"));

	OPENMENU;
	MENUCHECKITEM(_("&Status bar"), IDW_STATUSBAR, wxT(""));
	MENUCHECKITEM(_("&Toolbar"), IDW_TOOLBAR, wxT(""));
	MENUITEM_SEPARATOR;
	MENUITEM(_("&Routes\tF11"), CM_ROUTES, wxT(""));
	MENUITEM_SEPARATOR;
	MENUCHECKITEM(_("Current ke&ys\tF5"), CM_TOGGLEKEY, wxT(""));
	MENUCHECKITEM(_("&Tone system\tF6"), CM_TOGGLETS, wxT(""));
	MENUCHECKITEM(_("&Actions\tF7"), CM_TOGGLEACT, wxT(""));
	MENUITEM_SEPARATOR;
	MENUCHECKITEM(_("&One window mode"), CM_OWM, wxT(""));
	MENUCHECKITEM(_("One &common action window"), CM_CAW, wxT(""));
	MENUITEM_SEPARATOR;
	MENUITEM(_("Select &Box"), CM_SELECTBOX, wxT(""));
	CLOSEMENU(_("&View"));

	OPENMENU;
	MENUITEM(_("&Play"), CM_INDEVPLAY, wxT(""));
	MENUITEM(_("St&op"), CM_INDEVSTOP, wxT(""));
	MENUITEM(_("P&ause"), CM_INDEVPAUSE, wxT(""));
	CLOSEMENU(_("&Sequencer"));

	OPENMENU;
	MENUITEM(_("&Index"), CM_HELPINDEX, wxT(""));
	MENUITEM(_("&Handbook"), CM_HELPHANDBOOK, wxT(""));
	MENUITEM(_("&Help on help"), CM_HELPONHELP, wxT(""));
	MENUITEM_SEPARATOR;
	MENUITEM(_("&About"), CM_ABOUT, wxT(""));
	CLOSEMENU(_("&Help"));

    // Associate the menu bar with the frame
    frame->SetMenuBar(menuBar);

#if wxUSE_STATUSBAR
    frame->CreateStatusBar();
#endif // wxUSE_STATUSBAR

    frame->Show(true);
	
	return frame;
}
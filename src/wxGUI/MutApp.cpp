/** \file MutApp.cpp
 ********************************************************************
 * Mutabor Application.
 *
 * Copyright:   (c) 2005,2006,2007-2011 TU Dresden
 * Changes: (c) 2012-2013 Tobias Schlemmer
 * \author Rüdiger Krauße <krausze@mail.berlios.de>
 * Tobias Schlemmer <keinstein@users.sourceforge.net>
 * \license GPL
 *
 *    This program is free software; you can redistribute it and/or modify
 *    it under the terms of the GNU General Public License as published by
 *    the Free Software Foundation; either version 2 of the License, or
 *    (at your option) any later version.
 *
 *    This program is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License for more details.
 *
 *    You should have received a copy of the GNU General Public License
 *    along with this program; if not, write to the Free Software
 *    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * \addtogroup GUI
 * \{
 ********************************************************************/


// ---------------------------------------------------------------------------
// headers
// ---------------------------------------------------------------------------

#include "src/kernel/Defs.h"
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
#include "wx/strconv.h"
#include "wx/aui/framemanager.h"

#if !defined(__WXMSW__)
#include "Images/Icons/xpm/Mutabor.xpm"
#endif

//#include "Mutabor.rh"
//#include "src/kernel/GrafKern.h"
#include <boost/exception/diagnostic_information.hpp>
#include "src/wxGUI/MutApp.h"
#include "src/wxGUI/MutFrame.h"
#include "src/wxGUI/MutDocument.h"
#include "src/wxGUI/MutView.h"
#include "src/kernel/routing/midi/DevMidi.h"
#include "src/kernel/routing/Route-inlines.h"
#include "src/wxGUI/MutConfDlg.h"
#include "src/wxGUI/resourceload.h"
#include "src/wxGUI/stclanguage.h"
#include "src/wxGUI/MutDocManager.h"
#include "src/wxGUI/Routing/GUIRoute.h"
#include "src/wxGUI/configtree.h"
#include "src/wxGUI/Routing/DebugRoute.h"
#include "src/wxGUI/generic/mutDebug.h"

#ifdef __WXMAC__
#include <ApplicationServices/ApplicationServices.h>
#endif

#ifdef __BORLANDC__
#pragma hdrstop
#endif

using namespace mutabor;
using namespace mutaborGUI;


#ifdef MUTABOR_TEST
IMPLEMENT_APP_NO_MAIN(MutApp)
#else
IMPLEMENT_APP(MutApp)
#endif

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

#if wxUSE_PRINTING_ARCHITECTURE
	EVT_MENU (wxID_PRINT_SETUP,            MutApp::OnPrintSetup)
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
	EVT_MENU(CM_PRINT_ERROR,               MutApp::CmPrintError)
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

		wxStandardPaths& sp = (wxStandardPaths &) wxStandardPaths::Get();

#ifdef __LINUX__
		sp.SetInstallPrefix(_T(PREFIX));
#endif
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
#ifdef __WXMSW__
		wxLocale::AddCatalogLookupPathPrefix(_T("."));
//		wxLocale::AddCatalogLookupPathPrefix(wxT(".."));
#endif

		// Initialize the catalogs we'll be using
		m_locale.AddCatalog(wxT("mutabor"));
		m_locale.AddCatalog(wxT("wxstd"));
#ifdef __LINUX__
		{
//			wxLogNull noLog;
			m_locale.AddCatalog(_T("fileutils"));
		}
#endif


#ifdef DEBUG
		std::cout << (__FUNCTION__) << std::endl;
		std::cout << (typeid(m_locale).name())
			  << std::endl;
		std::cout << "ConfigDir:        "

			  << (const char *)(sp.GetConfigDir().ToUTF8()) << std::endl;
		std::cout
			  << "DataDir:          "
			  << (const char *)(sp.GetDataDir().ToUTF8()) << std::endl;
		std::cout
			  << "DocumentsDir:     "
			  << (const char *)(sp.GetDocumentsDir().ToUTF8()) << std::endl;
		std::cout
			  << "ExecutablePath:   "
			  << (const char *)(sp.GetExecutablePath().ToUTF8()) << std::endl;

#if defined(__UNIX__) && !defined(__WXMAC__)
		std::cout
			  << "InstallPrefix:    " << (const char *)(sp.GetInstallPrefix().ToUTF8())
			  << std::endl;
#endif
		std::cout
			  << "LocalDataDir:     " << (const char *)(sp.GetLocalDataDir().ToUTF8())
			  << std::endl;
		std::cout
			  << "PluginsDir:       " << (const char *)(sp.GetPluginsDir().ToUTF8())
			  << std::endl;
		std::cout
			  << "ResourcesDir:     " << (const char *)(sp.GetResourcesDir().ToUTF8())
			  << std::endl;
		std::cout
			  << "TempDir:          " << (const char *)(sp.GetTempDir().ToUTF8())
			  << std::endl;
		std::cout
			  << "UserConfigDir:    " << (const char *)(sp.GetUserConfigDir().ToUTF8())
			  << std::endl;
		std::cout
			  << "UserDataDir:      " << (const char *)(sp.GetUserDataDir().ToUTF8())
			  << std::endl;
		std::cout
			  << "UserLocalDataDir: " << (const char *)(sp.GetUserLocalDataDir().ToUTF8())
			  << std::endl;

		std::cout
			<< "LocalizedResourcesDir(Can): "
			<< (const char *)(sp.GetLocalizedResourcesDir(m_locale.GetCanonicalName(),
								      sp.ResourceCat_None).ToUTF8())
			<< std::endl;
		std::cout
			<< "LocalizedResourcesDir(Can,Messages): "
			<< (const char *)(sp.GetLocalizedResourcesDir(m_locale.GetCanonicalName(),
								      sp.ResourceCat_Messages).ToUTF8())
			<< std::endl;
		std::cout
			<< "LocalizedResourcesDir(): "
			<< (const char *)(sp.GetLocalizedResourcesDir(m_locale.GetName(),
								      sp.ResourceCat_None).ToUTF8())
			<< std::endl;
		std::cout
			<< "LocalizedResourcesDir(Messages): "
			<< (const char *)(sp.GetLocalizedResourcesDir(m_locale.GetName(),
								      sp.ResourceCat_Messages).ToUTF8())
			<< std::endl;

#endif
		// tell the mutabor kernel that we are using a GUI
		//		has_gui = 1;



		// init global wx objects
		// -------------------


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


		// initialize Mutabor before the doc manager
		mutabor::initialize_box_data();

		if (!(document_manager=new MutDocManager())) {
			return false;
		}
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
		document_manager->ConnectToApp(this);
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
		initialize_box_data();
		MidiInit();
		initMutIconShapes();
		InitGUIRouteFactories();
		//		InitGUIBoxFactories();

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
#endif // wxUSE_PRINTING_ARCHITECTURE

		return true;
	}

	void MutApp::OnInitCmdLine(wxCmdLineParser&  parser) {
		const wxCmdLineEntryDesc cmdLineDesc[] = {
			{ wxCMD_LINE_PARAM,  NULL, NULL, _("logic file"),
			  wxCMD_LINE_VAL_STRING, wxCMD_LINE_PARAM_MULTIPLE|wxCMD_LINE_PARAM_OPTIONAL },
			{ wxCMD_LINE_NONE, "", "", "", wxCMD_LINE_VAL_NONE, 0 }
		};

		wxApp::OnInitCmdLine(parser);
		parser.SetDesc(cmdLineDesc);

#ifdef DEBUG
		InitDebugCommandLine(parser);
#endif


	}

	bool MutApp::OnCmdLineParsed(wxCmdLineParser&  parser) {
		if (!wxApp::OnCmdLineParsed(parser)) return false;
#ifdef DEBUG
		ProcessDebugCommandLine(parser);
#endif
		wxString str;
		int count = parser.GetParamCount();
		for (int i = 0; i<count;i++)
		{
			// we have a document to open
			str = parser.GetParam(i);
			DEBUGLOG (always, "cmd line param: %s\n" , WXSTRINGCAST(str));
			// this will probably see if the file exists, and has the right extension

//		MutFrame * frame = CreateMainFrame(EditorMenu);
//		frame->OpenFile(str);

			if (document_manager)
				document_manager->CreateDocument(str, wxDOC_SILENT);
		}

		DEBUGLOG (other, "Command line parsed." );
		return true;
	}

	void MutApp::OnUnhandledException() {
		try {
			throw;
		} catch (std::exception e) {
			std::cerr << "Unhandled exception: " << e.what() << std::endl <<
				boost::current_exception_diagnostic_information();
		} catch(...) {
			std::cerr << "Unhandled exception!" << std::endl <<
				boost::current_exception_diagnostic_information();
		}
#ifdef DEBUG
		abort();
#endif
	}
	bool MutApp::OnExceptionInMainLoop() {
		try {
			throw;
		} catch (std::exception e) {
			std::cerr << "Unhandled exception: " << e.what() << std::endl <<
				boost::current_exception_diagnostic_information();
		} catch(...) {
			std::cerr << "Unhandled exception!" << std::endl <<
				boost::current_exception_diagnostic_information();
		}
#ifdef DEBUG
		abort();
#endif
		return true; // continue
	}
	void MutApp::OnFatalException() {
		try {
			throw;
		} catch (std::exception e) {
			std::cerr << "Unhandled exception: " << e.what() << std::endl <<
				boost::current_exception_diagnostic_information();
		} catch(...) {
			std::cerr << "Unhandled exception!" << std::endl <<
				boost::current_exception_diagnostic_information();
		}
#ifdef DEBUG
		abort();
#endif
	}

#ifdef DEBUG
	void MutApp::OnAssertFailure(const wxChar *file,
				    int line,
				    const wxChar *func,
				    const wxChar *cond,
				    const wxChar *msg)
	{
		mutabor_assert_fail(wxConvUTF8.cWX2MB(file),
				    line,
				    wxConvUTF8.cWX2MB(func),
				    wxConvUTF8.cWX2MB(cond),
				    wxConvUTF8.cWX2MB(msg));
	}
#endif



// Extend event processing to search the view's event table
	bool MutApp::ProcessEvent(wxEvent& event)
	{
		bool retval =  wxApp::ProcessEvent(event);
#ifdef DEBUG
		if (!retval) {
			DEBUGLOG(eventqueue,
				 ("Unhandled event %p, id=%d, type=%d"),
				 static_cast<void *>(&event),
				 (int)(event.GetId()),
				 (int)(event.GetEventType())
				);
		}
#endif
		return retval;
	}
#if 0
	// may be removed
	void MutApp::PassEventToDocManagerCMD(wxCommandEvent& event)
	{
		DEBUGLOG (eventqueue, "Command %p, id=%d, type=%d" ,
			 static_cast<void *>(&event),
			 event.GetId(),
			 (int)event.GetEventType()
			);
		if (!(document_manager->ProcessEvent(event)))
			event.Skip();
	}
	void MutApp::PassEventToDocManagerUPD(wxUpdateUIEvent& event)
	{
		DEBUGLOG (eventqueue, "UpdateUI: %p, id=%d, type=%d" ,
			 static_cast<void *>(&event),
			 event.GetId(),
			 (int)event.GetEventType()
			);
		if (!(document_manager->ProcessEvent(event)))
			event.Skip();
	}
#endif
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
		  ("Ruediger Krausze <krausze@mail.berlios.de>\n")
		  ("Tobias Schlemmer <keinstein@mail.berlios.de>\n"),
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
		info.AddDeveloper(_("Ruediger Krausze"));
		info.AddDeveloper(_("Tobias Schlemmer <keinstein@users.sf.net>"));
		info.AddDocWriter(_("Volker Abel"));
		info.AddDocWriter(_("Peter Reiss"));
		info.AddDocWriter(_("Ruediger Krausze"));
		info.AddDocWriter(_("Tobias Schlemmer <keinstein@users.sf.net>"));
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
		mutUnused(id);
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
		MakeRoutesMenu(menuBar, type);
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
		mutUnused(event);
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
		mutUnused(event);

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

		DEBUGLOG (other, "%d == %d?" ,(int)CM_EXECUTE,event.GetId());

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
		DEBUGLOG (other, "window %p is casted %p" ,
			 (void*)wxWindow::FindWindowById(WK_ROUTE),
			 (void*)dynamic_cast <MutFrame *>(wxWindow::FindWindowById(WK_ROUTE)));

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

	/// Show an error message from somewhere in the program
	void CmError(wxCommandEvent& event) {
		mutabor::error_type type = (mutabor::error_type) event.GetInt();
		wxString heading;
		int style;
		switch (type) {
		case mutabor::warning:
		case mutabor::compiler_warning:
		case mutabor::runtime_warning:
			style = wxICON_WARNING;
			break;
		case mutabor::error:
		case mutabor::internal_error:
		case mutabor::compiler_error:
		case mutabor::runtime_error:
		default:
			style = wxICON_ERROR;
			break;
		}
#if wxCHECK_VERSION(2,9,0)
		heading = to_string(type);
#else
		heading = wxString::FromUTF8(to_string(type));
#endif
		wxMessageBox(event.GetString(),heading,wxOK | style);
	}


	void MutApp::CmQuit (wxCommandEvent& event)
	{
		TRACE;

		SetExitOnFrameDelete(true);
		//		Exit();

		if (quitting) return;

		quitting = true;
		event.Skip(false);


		wxWindow * window;
		SetTopWindow(NULL);

		//	if (frames.empty()) {
		if ((window = GetTopWindow()) == NULL) {
			DEBUGLOG (other, "No Frames." );
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


		DEBUGLOG (other, "Starting Loop" );

/*	while (Pending())
	Dispatch();


	DEBUGLOG (other, "Dispatched all events" );

	wxIdleMode imode = wxIdleEvent::GetMode();
	wxIdleEvent::SetMode(wxIDLE_PROCESS_ALL);
*/

		Yield();

		/* make a copy of the top level window list as the
		   list may change or not, this depends on actions, we
		   don't have control over */
		wxWindowList frames = wxTopLevelWindows;

		for (wxWindowList::iterator i = frames.begin();
		     i!= frames.end();
		     i++) {
			wxWindow * window = *i;
			DEBUGLOG(aui,"Closing window with id %d\n",
				 window->GetId());
			if (wxTopLevelWindows.Find(window) == NULL)
				continue;
			{
				// On Windows we get an SEGV when we delete panes directly without detaching.
				// So we have two choices: find the panes and detach them or delete their
				// managed frame instead, leaving the cleaning to wxAuiManager.
				// We choose the latter.
				wxAuiManager * manager = wxAuiManager::GetManager(window);
				if (manager != NULL) {
					DEBUGLOG(aui,"Not deleting window %d with title %s.",
						 window->GetId(),
						 (dynamic_cast<wxTopLevelWindow *>(window)?
						  dynamic_cast<wxTopLevelWindow *>(window)->GetTitle().ToUTF8():
						  "<not a toplevel window>"));
					window = manager->GetManagedWindow();
					if (!window)
						continue;
				}
			}
			if (! window->Close()) {
//			wxIdleEvent::SetMode(imode);
				quitting = false;
				return;
			}
			Yield();
		}

		DEBUGLOG (other, "finished loop" );
	}


	void MutApp::CmPrintError (wxCommandEvent& event) {
		PrintError(event.GetInt(),event.GetString());
	}

	void MutApp::PrintError(int type, const wxString & s, wxWindow * parent) {
#if wxCHECK_VERSION(2,9,0)
		wxString head(mutabor::to_string((mutabor::error_type)type));
#else
		wxString head=wxString::FromUTF8(mutabor::to_string((mutabor::error_type)type));
#endif
		int style = wxOK | wxCENTRE;
		switch (type) {
	case mutabor::compiler_warning:
	case mutabor::runtime_warning:
	case mutabor::warning:
		style |= wxICON_EXCLAMATION;
		break;
	case mutabor::error:
	case mutabor::internal_error:
	case mutabor::compiler_error:
	case mutabor::runtime_error:
		style |= wxICON_ERROR;
		break;
	default:
		style |= wxICON_INFORMATION;
	}
		wxMessageDialog * dialog  = new wxMessageDialog (parent?parent:GetTopWindow(), s, head, style);
		dialog->ShowModal();
		dialog->Destroy();

	}


	wxString MutApp::GetResourceName(const wxString & file)
	{
#ifdef MUTABOR_TEST
		wxFileName rcname(file);
		wxString dir = rcname.GetPath();
		wxChar sep = rcname.GetPathSeparator();
		if (dir.empty())
			rcname.SetPath(wxString::FromUTF8(srcdir));
		else
			rcname.SetPath(wxString::FromUTF8(srcdir) + sep + dir);
		if (rcname.IsFileReadable()) {
			return rcname.GetFullPath();
		}
		if (dir.empty())
			rcname.SetPath(wxString::FromUTF8(top_srcdir));
		else
			rcname.SetPath(wxString::FromUTF8(top_srcdir) + sep + dir);
		if (rcname.IsFileReadable()) {
			return rcname.GetFullPath();
		}
		rcname.SetPath(wxString::FromUTF8(top_srcdir) + _T("/Images/Icons/png/"));
		if (dir.empty())
			rcname.SetPath(wxString::FromUTF8(top_srcdir) + _T("/Images/Icons/png/"));
		else
			rcname.SetPath(wxString::FromUTF8(top_srcdir) + _T("/Images/Icons/png/") + dir);
		if (rcname.IsFileReadable()) {
			return rcname.GetFullPath();
		}
		std::cout << (const char *)rcname.GetFullPath().ToUTF8() << std::endl;
		return file;

#else

		const wxLocale * m_locale = wxGetLocale();
		wxStandardPathsBase & sp = wxStandardPaths::Get();
		wxString localename = m_locale->GetCanonicalName();
		wxFileName relativename(file);
		wxFileName rcname(relativename);
		rcname.MakeAbsolute(sp.GetLocalizedResourcesDir(localename));
		DEBUGLOGTYPE(other,MutApp,("Trying do load resources...\n%s\n%s"),rcname.GetFullPath().c_str(),sp.GetResourcesDir().c_str());
		if (!rcname.IsFileReadable()) {
			rcname = relativename;
			rcname.MakeAbsolute(sp.GetLocalizedResourcesDir(localename.BeforeFirst(_T('_'))));
			DEBUGLOGTYPE(other,MutApp,("Trying %s"),rcname.GetFullPath().c_str());
			if (!rcname.IsFileReadable()) {
				rcname = relativename;
				rcname.MakeAbsolute(sp.GetResourcesDir());
				DEBUGLOGTYPE(other,MutApp,("Trying %s"),rcname.GetFullPath().c_str());
			}
		}
		localename = rcname.GetFullPath();
		return localename;
#endif
	}

	wxMenu * MutApp::MakeFileMenu(wxMenuBar * menuBar, MenuType type)
	{
		wxMenu * menu = new wxMenu;
		menu->Append( CM_FILENEW, _("&New\tCtrl+N"),
			      _("Create a new logic file."));
		menu->Append( CM_FILEOPEN, _("&Open...\tCtrl+O"),
			      _("Open a logic file in editor window"));

		if (type == EditorMenu || type == RouteMenu) {
			menu->Append (wxID_SAVE);
			menu->Append (wxID_SAVEAS);
			menu->Append (wxID_CLOSE);
		}

		menu->AppendSeparator();
		menu->Append( CM_IMPORT_SCALA,
			     _("&Import from Scala"),
			     _("Import a tuning logic from a Scala file and its keymap"));
		menu->Append( CM_EXPORT_SCALA,
			     _("E&xport to Scala"),
			     _("Export the currently active logic to a Scala file with keymap"));

		menu->AppendSeparator();

		menu->Append( CM_EXECUTE, _("&Execute\tCtrl+F9"),
			      _("Load a logic file an immediately activate it"));

#if (defined(__WXMAC__) || defined(__WXCOCOA__))
		if (type == EditorMenu)
#endif
			menu->AppendSeparator();

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
		menu->AppendSeparator();
#endif
		menu->Append(wxID_EXIT);
		DEBUGLOG (docview, "Adding file history menu" );
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
		menu->Append( CM_COMPILE, _("&Compile\tAlt+F9"),  _("Load the actual file into the Mutabor Kernel."));
		menu->Append( CM_ACTIVATE, _("&Activate\tF9"),  _("Activate the Mutabor Kernel."));
		menu->Append( CM_STOP, _("&Stop\tF8"),  _("Stop the Mutabor Kernel."));
		menu->AppendSeparator();
		menu->Append( CM_PANIC, _("&Panic\tF12"),  _("Send \"all notes off\" signal to on all MIDI Channels."));
		menuBar->Append(menu, _("&Logic"));
	}

	void MutApp::MakeRoutesMenu(wxMenuBar * menuBar, MenuType type)
	{
		wxMenu * menu = new wxMenu;
		if (type == RouteMenu) {
			menu->Append( CM_MOVE_UP, _("&Move icon up\tShift+Up"),
				      _("Moves the device or box upwards in the window."));
			menu->Append( CM_MOVE_DOWN, _("&Move icon down\tShift+Down"),
				      _("Moves the device or box downwards in the window."));
			menu->AppendSeparator();
		}
		menu->Append( CM_ROUTELOAD, _("&Load routes"),
			      _("Load the current route configuration from a file"));
		menu->Append( CM_ROUTESAVE, _("&Save routes"),
			      _("Save current route configuration to a file."));
		menu->Append( CM_ROUTESAVEAS, _("Save routes &as"),
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
			menuCharset->Append (CM_CHARSETUTF8, _("&UTF-8 (International)"));
			menuCharset->Append (CM_CHARSETUTF8, _("Uni&code (same as UTF-8)"));

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

		/*	menu->AppendCheckItem( IDW_STATUSBAR, _("&Status bar"),
			_("Toggle status bar on/off"));
			menu->AppendCheckItem( IDW_TOOLBAR, _("&Toolbar"),
			_("Toggle tool bar on/off"));
			menu->AppendSeparator();
		*/
		if (type != ProgramMenu) {
			if (type != EditorMenu) {
				menu->AppendSeparator();
			}
			menu->AppendCheckItem( CM_TOGGLEKEY, _("Current ke&ys\tF5"),
					       _("Show current keys window"));
			menu->AppendCheckItem( CM_TOGGLETS, _("&Tone system\tF6"),
					       _("Show tone system window"));
			menu->AppendCheckItem( CM_TOGGLEACT, _("&Actions\tF7"),
					       _("Show current actions window"));
		}
		menu->AppendCheckItem( CM_ROUTES, _("&Routes\tF11"),
				       _("Open route configuration window"));

		if (type != ProgramMenu) {
			/*	  menu->AppendSeparator();
				  menu->AppendCheckItem( CM_OWM, _("&One window mode"),
				  _("Toggle logic satus window: one each or one common"));
				  menu->AppendCheckItem( CM_CAW, _("One &common action window"),
				  _("Toggle action window mode: one each or one common"));
			*/
			menu->AppendSeparator();
			menu->Append(CM_SELECTBOX,_("Select &Box"), new wxMenu(),
				     _("Select current Box"));
		}

		menuBar->Append(menu, _("&View"));
	}

	void MutApp::MakeSequencerMenu(wxMenuBar * menuBar)
	{
		wxMenu * menu = new wxMenu;
		menu->Append( CM_INDEVPLAY, _("&Play"),
			      _("Start playing the music from input file devices"));
		menu->Append( CM_INDEVSTOP, _("St&op"),
			      _("Stop playing the music from input file devices"));
		menu->Append( CM_INDEVPAUSE, _("P&ause"),
			      _("Pause plaing the music from input file devices"));
		menuBar->Append(menu, _("&Sequencer"));
	}


	void MutApp::MakeHelpMenu(wxMenuBar * menuBar)

	{
		wxMenu * menu = new wxMenu;
		menu->Append( CM_HELP, _("Online &Help\tF1"),
			      _("Open the help Window"));
		menu->Append( CM_HELPHANDBOOK, _("&Manual"),
			      _("Open the manual"));
		menu->Append( CM_HELPREFERENCE, _("Language &reference"),
			      _("Open the Mutabor language reference"));
		menu->AppendSeparator();
		menu->Append( CM_HELPINDEX, _("&Index"),
			      _("Open the help index"));
		menu->Append( CM_HELPSEARCH, _("&Search"),
			      _("Search the help system for a specific keyword"));
		menu->AppendSeparator();
		menu->Append( CM_HELPONHELP, _("Help &on help"),
			      _("Show Help about the help system"));

#if !(defined(__WXMAC__) || defined(__WXCOCOA__))
		menu->AppendSeparator();
#endif

		menu->Append( CM_ABOUT, _("&About"),
			      _("Show information about the program"));
#ifdef DEBUG
		menu->AppendSeparator();
		menu->Append( cmCallExitId, _("Stop"),
			      _("Stop the current program"));
#endif
		menuBar->Append(menu, _("&Help"));
	}

	int MutApp::OnExit()
	{
		SaveState();

//		AktionTraceReset();

		TRACEC;
		InputDeviceClass::ClearDeviceList();
		TRACEC;
		OutputDeviceClass::ClearDeviceList();
		TRACEC;
		BoxClass::ClearBoxList();
		TRACEC;
		RouteClass::ClearRouteList();
		TRACEC;

		MidiUninit();

		if (g_pageSetupData)
			delete g_pageSetupData;
		g_pageSetupData = NULL;

		if (g_printData)
			delete g_printData;
		g_printData = NULL;

		document_manager->DisconnectFromApp(this);
		if (document_manager)
			delete document_manager;
		document_manager = NULL;
#if defined(__WXMAC__)
		wxMenuBar::MacSetCommonMenuBar(NULL);
#endif
		if (HelpController)
			delete HelpController;
		HelpController = NULL;
		wxXmlResource::Get()->ClearHandlers();

		mutabor_backtrace::set_global_print();
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

		DEBUGLOG (other, "Filename: %s" ,fileName.c_str());

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
		RouteClass::ClearRouteList();
		TRACE;
		InputDeviceClass::ClearDeviceList();
		TRACE;
		BoxClass::ClearBoxList();
		TRACE;
		OutputDeviceClass::ClearDeviceList();
		TRACE;

		DebugCheckRoutes();

		LoadRoutes(config);


		if (routewnd) {
			routewnd->InitDevices();
			routewnd->Layout();
			routewnd->FitInside();
			routewnd->Refresh();
//			routewnd->Update();

		}
		DebugCheckRoutes();

		config->SetPath(oldpath);
	}

}

///\}

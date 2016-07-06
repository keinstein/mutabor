/** \file               -*- C++ -*-
 ********************************************************************
 * Document/View framework document manager
 *
 * Copyright:   (c) 2011 TU Dresden
 * \author  Tobias Schlemmer <keinstein@users.berlios.de>
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
 *
 *
 ********************************************************************
 * \deftogroup docview Document/View framework
 * \{
 ********************************************************************/
// availlable groups: GUI, route, kernel, src/wxGUI, debug

// ---------------------------------------------------------------------------
// headers
// ---------------------------------------------------------------------------

#include "src/kernel/Defs.h"
#include "src/wxGUI/MutDocManager.h"
#include "src/wxGUI/MutView.h"
#include "src/wxGUI/MutDocument.h"
#include "src/wxGUI/MutEditFile.h"
#include "src/wxGUI/MutApp.h"
#include "src/wxGUI/ScalaGUI.h"
#include "src/kernel/routing/Route-inlines.h"

#include "wx/file.h"
#include "wx/convauto.h"
#include <sstream>
#ifdef __BORLANDC__
#pragma hdrstop
#endif


using mutaborGUI::MutDocManager;

BEGIN_EVENT_TABLE(MutDocManager, wxDocManager)
EVT_MENU(CM_EXECUTE, MutDocManager::CmExecuteLogic)
EVT_MENU(CM_IMPORT_SCALA, MutDocManager::CmImportScala)
END_EVENT_TABLE()

namespace mutaborGUI {

#if 0
	bool MutDocManager::TryParent(wxEvent& event)
	{
		mutUnused(event);
		TRACEC;
		// if we must pass some events to the Application,
		// they must be handled here somehow replacing false
#if 0
		// Implementation in Event.cpp:
		if ( wxTheApp && false )
			{
				// Special case: don't pass wxEVT_IDLE to wxApp, since it'll always
				// swallow it. wxEVT_IDLE is sent explicitly to wxApp so it will be
				// processed appropriately via SearchEventTable.
				if ( event.GetEventType() != wxEVT_IDLE )
					{
						if ( wxTheApp->ProcessEvent(event) )
							return true;
					}
			}
#endif

		return true;
	}
#endif

        // Extend event processing to search the view's event table
	bool MutDocManager::ProcessEvent(wxEvent& event)
	{
		if (!wxEvtHandler::ProcessEvent(event))
			{
				wxView* view = GetCurrentView();
				DEBUGLOG (eventqueue, "View: %p" ,
					  (void*)(dynamic_cast<MutView *>(view)));
				if (view && view->ProcessEvent(event))
					return true;
				else return false;
			}
		return true;
	}


	// Make a frame title (override this to do something different)
        // If docName is empty, a document is not currently active.
	wxString MutDocManager::MakeFrameTitle(wxDocument* doc)
	{
		wxString appName = wxTheApp->GetAppName();
		wxString title;
		if (!doc)
			title = appName;
		else
			{
				wxString docName;
#if wxCHECK_VERSION(2,9,0)
				docName = doc->GetUserReadableName();
#else
				doc->GetPrintableName(docName);
#endif
				title = docName + wxString(_(" - ")) + _T(PACKAGE_NAME);
			}
		return title;
	}

	void MutDocManager::CmExecuteLogic(wxCommandEvent& event)
	{
		mutUnused(event);
		wxDocument * doc = CreateDocument( wxEmptyString, 0);
		if ( !doc )
			{
				OnOpenFileFailure();
				return;
			}

		/** \todo correct command processing */

		mutASSERT(dynamic_cast<MutDocument *>(doc));
		wxView * view = doc->GetFirstView();
		if (!view) {
			UNREACHABLEC;
			return;
		}
		wxWindow * f = view->GetFrame();
		if (!f) {
			UNREACHABLEC;
			return;
		}
		mutASSERT(dynamic_cast<MutFrame *>(f));
		wxCommandEvent ev(wxEVT_COMMAND_MENU_SELECTED,
				  CM_ACTIVATE);
		f->GetEventHandler()->ProcessEvent(ev);
	}

	void MutDocManager::CmImportScala(wxCommandEvent & event) {
		ImportScala(NULL);
	}

	void MutDocManager::ImportScala(MutEditFile * editor) {
		ScalaImportDialog * dialog = new ScalaImportDialog(editor);
		if (!dialog) return;
		mutabor::scala_parser::mutabor_writer_options options;
		wxFileName ScalaFile, KeymapFile;
		for (;;) {
			if (dialog -> ShowModal() == wxID_CANCEL) {
				dialog -> Destroy();
				return;
			}
			ScalaFile = dialog -> GetScalaFile();
			if (ScalaFile.IsFileReadable())
				break;
		}
		dialog -> GetData(options);
		KeymapFile = dialog -> GetKeymapFile();
		dialog -> Destroy();
		wxFile scala(ScalaFile.GetFullPath());
		if (!scala.IsOpened())
			return;

		wxString scalaText;
		wxConvAuto autoConverter(wxFONTENCODING_ISO8859_15);
		if (!scala.ReadAll(&scalaText, autoConverter) ) {
			wxGetApp().PrintError(mutabor::error,
					      _("Could not load the scala file contents into memory."),
					      editor);
			return;
		}
		mutabor::scala_parser::parser scparser(std::string(scalaText.ToUTF8()),
						       std::string(ScalaFile.GetFullName().ToUTF8()));
		scalaText.Clear();

		if (!KeymapFile.IsFileReadable())
			scparser.make_keymap();
		else {
			wxFile kfile(KeymapFile.GetFullPath());
			if (!kfile.IsOpened() ||
			    !kfile.ReadAll(&scalaText, autoConverter))
				scparser.make_keymap();
			else {
				scparser.load_keymap(std::string(scalaText.ToUTF8()),
						     std::string(KeymapFile.GetFullName().ToUTF8()));
			}
		}

		if (!editor) {
			wxDocument * doc = CreateNewDocument();
			if (!doc) return;
			MutView * view = dynamic_cast<MutView *>(doc -> GetFirstView());
			if (!view) {
				CloseDocument(doc,true);
				return;
			}
			editor = view -> GetTextsw();
			if (!editor) {
				CloseDocument(doc,true);
				return;
			}
#if 0
			editor->InitializePrefs(editor->DeterminePrefs(_T(".mut")));
#endif
		}

		std::ostringstream s;
		scparser.write_mutabor(s, options);
		editor->AddText(wxString::FromUTF8(s.str().c_str()));
	}

	class MutDocManagerEventConnector {
	public:
		MutDocManagerEventConnector(wxEvtHandler * h):handler(h) {}
		MutDocManagerEventConnector & operator () (int id,
			     wxEventType eventType,
			     wxObjectEventFunction function,
			     wxObject* userData = NULL,
			     wxEvtHandler* eventSink = NULL) {
			handler -> Connect(id, eventType, function, userData, eventSink);
			return *this;
		}
	protected:
		wxEvtHandler * handler;
	};
	class MutDocManagerEventDisconnector {
	public:
		MutDocManagerEventDisconnector(wxEvtHandler * h):handler(h) {}
		MutDocManagerEventDisconnector & operator () (int id,
			     wxEventType eventType,
			     wxObjectEventFunction function,
			     wxObject* userData = NULL,
			     wxEvtHandler* eventSink = NULL) {
			handler -> Disconnect(id, eventType, function, userData, eventSink);
			return * this;
		}
	protected:
		wxEvtHandler * handler;
	};

	template<class C>
	inline void MutDocManager::doConnect(C & Connect) {
		// original handlers
		Connect(wxID_OPEN,
			wxEVT_COMMAND_MENU_SELECTED,
			wxCommandEventHandler( wxDocManager::OnFileOpen ),
			NULL,
			this);
		Connect(wxID_CLOSE,
			wxEVT_COMMAND_MENU_SELECTED,
			wxCommandEventHandler( wxDocManager::OnFileClose ),
			NULL,
			this);
		Connect(wxID_CLOSE_ALL,
			wxEVT_COMMAND_MENU_SELECTED,
			wxCommandEventHandler( wxDocManager::OnFileCloseAll ),
			NULL,
			this);
		Connect(wxID_REVERT,
			wxEVT_COMMAND_MENU_SELECTED,
			wxCommandEventHandler( wxDocManager::OnFileRevert ),
			NULL,
			this);
		Connect(wxID_NEW,
			wxEVT_COMMAND_MENU_SELECTED,
			wxCommandEventHandler( wxDocManager::OnFileNew ),
			NULL,
			this);
		Connect(wxID_SAVE,
			wxEVT_COMMAND_MENU_SELECTED,
			wxCommandEventHandler( wxDocManager::OnFileSave ),
			NULL,
			this);
		Connect(wxID_SAVEAS,
			wxEVT_COMMAND_MENU_SELECTED,
			wxCommandEventHandler( wxDocManager::OnFileSaveAs ),
			NULL,
			this);
		Connect(wxID_UNDO,
			wxEVT_COMMAND_MENU_SELECTED,
			wxCommandEventHandler( wxDocManager::OnUndo ),
			NULL,
			this);
		Connect(wxID_REDO,
			wxEVT_COMMAND_MENU_SELECTED,
			wxCommandEventHandler( wxDocManager::OnRedo ),
			NULL,
			this);

		Connect(wxID_OPEN,
			wxEVT_UPDATE_UI,
			wxUpdateUIEventHandler( wxDocManager::OnUpdateFileOpen ),
			NULL,
			this);
#if wxCHECK_VERSION(2,9,0)
		Connect(wxID_CLOSE,
			wxEVT_UPDATE_UI,
			wxUpdateUIEventHandler( wxDocManager::OnUpdateDisableIfNoDoc ),
			NULL,
			this);
		Connect(wxID_CLOSE_ALL,
			wxEVT_UPDATE_UI,
			wxUpdateUIEventHandler( wxDocManager::OnUpdateDisableIfNoDoc ),
			NULL,
			this);
#else
		Connect(wxID_CLOSE,
			wxEVT_UPDATE_UI,
			wxUpdateUIEventHandler( wxDocManager::OnUpdateFileClose ),
			NULL,
			this);
		Connect(wxID_CLOSE_ALL,
			wxEVT_UPDATE_UI,
			wxUpdateUIEventHandler( wxDocManager::OnUpdateFileClose ),
			NULL,
			this);
#endif
		Connect(wxID_REVERT,
			wxEVT_UPDATE_UI,
			wxUpdateUIEventHandler( wxDocManager::OnUpdateFileRevert ),
			NULL,
			this);
		Connect(wxID_NEW,
			wxEVT_UPDATE_UI,
			wxUpdateUIEventHandler( wxDocManager::OnUpdateFileNew ),
			NULL,
			this);
		Connect(wxID_SAVE,
			wxEVT_UPDATE_UI,
			wxUpdateUIEventHandler( wxDocManager::OnUpdateFileSave ),
			NULL,
			this);
		Connect(wxID_SAVEAS,
			wxEVT_UPDATE_UI,
			wxUpdateUIEventHandler( wxDocManager::OnUpdateFileSaveAs ),
			NULL,
			this);
		Connect(wxID_UNDO,
			wxEVT_UPDATE_UI,
			wxUpdateUIEventHandler( wxDocManager::OnUpdateUndo ),
			NULL,
			this);
		Connect(wxID_REDO,
			wxEVT_UPDATE_UI,
			wxUpdateUIEventHandler( wxDocManager::OnUpdateRedo ),
			NULL,
			this);

#if wxUSE_PRINTING_ARCHITECTURE
		Connect(wxID_PRINT,
			wxEVT_COMMAND_MENU_SELECTED,
			wxCommandEventHandler( wxDocManager::OnPrint ),
			NULL,
			this);
		Connect(wxID_PREVIEW,
			wxEVT_COMMAND_MENU_SELECTED,
			wxCommandEventHandler( wxDocManager::OnPreview ),
			NULL,
			this);

#if wxCHECK_VERSION(2,9,0)
		Connect(wxID_PRINT,
			wxEVT_UPDATE_UI,
			wxUpdateUIEventHandler( wxDocManager::OnUpdateDisableIfNoDoc ),
			NULL,
			this);
		Connect(wxID_PREVIEW,
			wxEVT_UPDATE_UI,
			wxUpdateUIEventHandler( wxDocManager::OnUpdateDisableIfNoDoc ),
			NULL,
			this);
#else
		Connect(wxID_PRINT,
			wxEVT_UPDATE_UI,
			wxUpdateUIEventHandler( wxDocManager::OnUpdatePrint ),
			NULL,
			this);
		Connect(wxID_PREVIEW,
			wxEVT_UPDATE_UI,
			wxUpdateUIEventHandler( wxDocManager::OnUpdatePreview ),
			NULL,
			this);
#endif
#endif


		// our own handlers
		Connect(CM_EXECUTE,
			wxEVT_COMMAND_MENU_SELECTED,
			wxCommandEventHandler(MutDocManager::CmExecuteLogic),
			NULL,
			this);

		Connect(CM_IMPORT_SCALA,
			wxEVT_COMMAND_MENU_SELECTED,
			wxCommandEventHandler(MutDocManager::CmImportScala),
			NULL,
			this);
	}

	void MutDocManager::ConnectToApp(wxEvtHandler * handler) {
		MutDocManagerEventConnector Connect(handler);
		doConnect(Connect);
	}

	void MutDocManager::DisconnectFromApp(wxEvtHandler * handler) {
		MutDocManagerEventDisconnector Disconnect(handler);
		doConnect(Disconnect);
	}


}
///\}

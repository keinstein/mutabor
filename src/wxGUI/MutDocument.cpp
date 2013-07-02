/** \file 
********************************************************************
* Document/View Document class for Mutabor source files.
*
* $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/src/wxGUI/MutDocument.cpp,v 1.13 2011/11/02 14:31:58 keinstein Exp $
* Copyright:   (c) 2011 TU Dresden
* \author  Tobias Schlemmer <keinstein@users.berlios.de>
* \date 
* $Date: 2011/11/02 14:31:58 $
* \version $Revision: 1.13 $
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
* \addtogroup docview
* \{
********************************************************************/
// availlable groups: GUI, route, kernel, src/wxGUI, debug

// ---------------------------------------------------------------------------
// headers
// ---------------------------------------------------------------------------

#include "src/kernel/Defs.h"

#include "src/wxGUI/MutDocument.h"
#include "src/wxGUI/MutView.h"
#include "src/wxGUI/MutApp.h"
#include <wx/debug.h>
#include "src/kernel/routing/Route-inlines.h"

#include <cstdio>
#include <iostream>

#ifdef __BORLANDC__
#pragma hdrstop
#endif

using mutaborGUI::MutCommandProcessor;
using mutaborGUI::MutDocument;
IMPLEMENT_DYNAMIC_CLASS(MutCommandProcessor, wxCommandProcessor)
IMPLEMENT_DYNAMIC_CLASS(MutDocument, wxDocument)

BEGIN_EVENT_TABLE(MutDocument, wxDocument)
//	EVT_MENU(ID_NewViewFrame, MutDocument::CmdNewView)
//	EVT_UPDATE_UI(ID_NewViewFrame, MutDocument::OnNewViewUpdateUI)
//	EVT_MENU(ID_UpdateAllViews, MutDocument::CmdUpdateAllViews)
END_EVENT_TABLE()

namespace mutaborGUI {
	MutCommandProcessor::MutCommandProcessor(MutDocument * doc,int maxCommands):
		wxCommandProcessor(maxCommands)
	{
		m_undoAccelerator = wxT("\tCtrl+Z");
		m_redoAccelerator = wxT("\tShift+Ctrl+Z");
		document = doc;
	}

	MutCommandProcessor::~MutCommandProcessor()
	{
	}


	bool MutCommandProcessor::DoCommand(wxCommand& cmd)
	{
		DEBUGLOG(editor,_T("doing Command: %s"),
			 (const wxChar*)cmd.GetName().c_str());
		return cmd.Do();
	}

	bool MutCommandProcessor::UndoCommand(wxCommand& cmd)
	{
		DEBUGLOG(editor,_T("undoing Command: %s"),
			 (const wxChar*)cmd.GetName().c_str());
		return cmd.Undo();
	}

// Pass a command to the processor. The processor calls Do();
// if successful, is appended to the command history unless
// storeIt is false.
	bool MutCommandProcessor::Submit(wxCommand *command, bool storeIt)
	{

		DEBUGLOG(editor,_T("Submitted command (storeIt = %d): %s"),
			 storeIt,
			 (command?(const wxChar*)command->GetName().c_str():_T(""))
			);
		return wxCommandProcessor::Submit(command,false);
	}

	void MutCommandProcessor::Store(wxCommand *command)
	{
		DEBUGLOG(editor,_T("storing command: %s"),
			 (command?(const wxChar*)command->GetName().c_str():_T(""))
			);
		wxCommandProcessor::Store(command);
	}

	bool MutCommandProcessor::Undo()
	{
		DEBUGLOG(editor,_T("."));
		STUBC;
		return wxCommandProcessor::Undo();
	}

	bool MutCommandProcessor::Redo()
	{
		DEBUGLOG(editor,_T("."));
		STUBC;
		return wxCommandProcessor::Redo();
	}

	bool MutCommandProcessor::CanUndo() const
	{
		DEBUGLOG(editor,_T("Can undo?"));
		STUBC;
		return true;
	}

	bool MutCommandProcessor::CanRedo() const
	{
		DEBUGLOG(editor,_T("Can redo?"));
		STUBC;
		return true;
	}

	void MutCommandProcessor::Initialize()
	{
		DEBUGLOG(editor,_T("."));
		wxCommandProcessor::Initialize();
	}

	void MutCommandProcessor::SetMenuStrings()
	{
		DEBUGLOG(editor,_T("."));
		wxCommandProcessor::SetMenuStrings();
	}

	void MutCommandProcessor::ClearCommands()
	{
		DEBUGLOG(editor,_T("."));
		wxCommandProcessor::ClearCommands();
	}



	MutDocument::MutDocument():wxDocument()
	{


	}

	MutDocument::~MutDocument()
	{

	}

	wxCommandProcessor* MutDocument::OnCreateCommandProcessor()
	{
		return NULL;
	}


	bool MutDocument::DoSaveDocument(const wxString& filename)
	{
		MutView *view = (MutView *)GetFirstView();

		if (!view->GetTextsw()->SaveFile(filename))
			return false;

		SetTitle(GetDocumentManager()->MakeFrameTitle(this));
		SetFilename(filename,true);

		return true;
	}

	bool MutDocument::DoOpenDocument(const wxString& filename)
	{
		MutView *view = (MutView *)GetFirstView();
		mutASSERT(view);
		if (!view->GetTextsw()->LoadFile(filename))
			return false;
		DEBUGLOG(docview,_T("New title: ")+GetDocumentManager()->MakeFrameTitle(this));
		SetTitle(GetDocumentManager()->MakeFrameTitle(this));
		SetFilename(filename,true);
		return true;
	}

	bool MutDocument::OnNewDocument() 
	{
		if (!wxDocument::OnNewDocument()) 
			return false;
		DEBUGLOG(docview,_T("New title: ")+GetDocumentManager()->MakeFrameTitle(this));
		
		
		MutView *view = (MutView *)GetFirstView();
		if (view) {
			MutFrame * frame = view -> GetMutFrame();
			if (frame)
				frame -> SetTitle(GetDocumentManager()->MakeFrameTitle(this));
		} 
		return true;
	}

	bool MutDocument::CheckLogic() {
		if (!LogicOn) return true;
		MutFrame * frame = MutFrame::GetActiveWindow();
		if (frame && frame->GetDocument() == this) {
			DEBUGLOG (other, _T("We are the active window."));

			wxString msg;
			msg.Printf(_("This logic is currently active. On closing it will be deactivated. Really close this window?"));

			if ( wxMessageBox(msg, _("Please confirm closing."),
					  wxICON_QUESTION | wxYES_NO) != wxYES ) {
				return false;
			}
			frame -> DoStop();
		}

		return true;
	}

	bool MutDocument::OnSaveModified() {
		if (!CheckLogic()) return false;
		else return wxDocument::OnSaveModified();
	}

#if wxUSE_STD_IOSTREAM

	wxSTD ostream& MutDocument::SaveObject(wxSTD ostream& stream)
	{
		printf("cmydoc::saveobject\n");
		stream << 5;
		stream << 'j';
		return stream;
	}

	wxSTD istream& MutDocument::LoadObject(wxSTD istream& stream)
	{
		DEBUGLOG(docview,_T("."));
		bool bOK(false);
		int nA(0);
		char ch(0);

		stream >> nA;
		stream >> ch;

		if(stream.good())
		{
			DEBUGLOG(docview,_T("num is %d and char is %c"), nA, ch);
			bOK = true;
		}

		if(bOK == false)
		{
			DEBUGLOG(docview,_T("load error"));
			// tell the framework to abort the load procedure
			stream.clear(std::ios_base::badbit);
		}
		return stream;
	}

#else

	wxOutputStream& MutDocument::SaveObject(wxOutputStream& stream)
	{
		printf("mydoc::saveobject()\n");
		return stream;
	}

	wxInputStream& MutDocument::LoadObject(wxInputStream& stream)
	{
		printf("mydoc::loadobject()\n");
		return stream;
	}

#endif

	bool MutDocument::OnCreate(const wxString& path, long flags)
	{

		// you should call the one in the superclass
		return wxDocument::OnCreate(path, flags);
	}

	bool MutDocument::IsModified(void) const
	{
		MutView *view = (MutView *)GetFirstView();
		if (view && view -> GetTextsw())
		{
			return (wxDocument::IsModified() || view->GetTextsw()->IsModified());
		}
		else
			return wxDocument::IsModified();
	}

	void MutDocument::Modify(bool mod)
	{
		MutView *view = (MutView *)GetFirstView();

		wxDocument::Modify(mod);

		if (!mod && view && view->GetTextsw())
			view->GetTextsw()->SetSavePoint();
	}

	void MutDocument::CmdNewView(wxCommandEvent& event)
	{
		mutUnused(event);
		//wxMessageBox(wxT("doc newview 1"), _T("dialog"), wxOK | wxICON_INFORMATION, NULL);

		//  we manually create a view, and register it with the document.
		// the view needs to create a window for itself, which 
		//  it can do in OnCreate
		MutView* pview = new MutView();
		bool bKeep = pview->OnCreate(NULL, 0);
		if(bKeep)
		{
			AddView(pview);
			// we could set the title of the view's frame
			// AddView() does not set the document in the view, so we do that now
			pview->SetDocument(this);
		}
		else
		{
			// kill the view and its window. Hopefully nothing else.
			pview->Close(TRUE);
			// I don't think the Close function works
			wxFAIL;
		}	

		// wxMessageBox(wxT("doc newview 2"), _T("dialog"), wxOK | wxICON_INFORMATION, NULL);


	}

	void MutDocument::CmdUpdateAllViews(wxCommandEvent& event)
	{
		mutUnused(event);
		UpdateAllViews();
	}

	void MutDocument::OnNewViewUpdateUI(wxUpdateUIEvent& event)
	{
		event.Enable(true);
		// printf("MutDocument::OnNewViewUpdateUI\n");
	}


	bool MutDocument::TryParent(wxEvent& event)
	{
		mutUnused(event);
		DEBUGLOG(eventqueue,_T("."));
		// if we must pass some events to the Application, 
		// they must be handled here somehow replacing false
		return false;
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
		return false;
#endif

	}

	
}


///\}

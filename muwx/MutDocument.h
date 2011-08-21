/** \file  -*- C++ -*-
 ********************************************************************
 * Document/View Document class for Mutabor source files.
 *
 * $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/muwx/MutDocument.h,v 1.6 2011/08/21 16:52:05 keinstein Exp $
 * Copyright:   (c) 2011 TU Dresden
 * \author  Tobias Schlemmer <keinstein@users.berlios.de>
 * \date 
 * $Date: 2011/08/21 16:52:05 $
 * \version $Revision: 1.6 $
 * \license GPL
 *
 * $Log: MutDocument.h,v $
 * Revision 1.6  2011/08/21 16:52:05  keinstein
 * Integrate a more sophisticated editor menu based on the stc sample
 *
 * Revision 1.5  2011-08-16 20:20:03  keinstein
 * Fix compiling on Mac OS X 10.5
 *
 * Revision 1.4  2011-08-11 19:00:48  keinstein
 * get Document/View running.
 * Needs further testing (possible segfaults).
 *
 * Revision 1.3  2011-08-06 09:20:16  keinstein
 * documentation fixes
 *
 * Revision 1.2  2011-07-31 20:16:04  keinstein
 * Implemented opening files from command line using Document/View framework
 *
 * Revision 1.1  2011-07-31 12:40:42  keinstein
 * Added classes and functions for Document/View support
 *
 *
 *
 ********************************************************************
 * \addtogroup docview
 * \{
 ********************************************************************/

// ---------------------------------------------------------------------------
// headers
// ---------------------------------------------------------------------------

#ifndef MUTABOR_MUT_DOCUMENT_H
#define MUTABOR_MUT_DOCUMENT_H

// For compilers that support precompilation, includes "wx/wx.h".
#include "Defs.h"
#include <wx/wxprec.h>

#ifdef __BORLANDC__
    #pragma hdrstop
#endif

#include <wx/wx.h>
#include <wx/docview.h>
#include "wx/cmdproc.h"

namespace mutaborGUI {

	class MutDocument;
	/// Command processor for wxStyledTextControl
	/** This class proviedes a command forwarder for wxStyledTextControl.
	    Since Scintalla uses its internal document/view framework 
	    it is overkill to implement a doubling. The best would be if 
	    wxSTC exposes the model to wxWidgets thus that it can be used easily.
	*/
	class MutCommandProcessor:wxCommandProcessor {
	public:
		// if max number of commands is -1, it is unlimited
		MutCommandProcessor(MutDocument * doc = NULL, int maxCommands = -1);
		virtual ~MutCommandProcessor();

		// Pass a command to the processor. The processor calls Do(); if
		// successful, is appended to the command history unless storeIt is false.
		virtual bool Submit(wxCommand *command, bool storeIt = true);

		// just store the command without executing it
		virtual void Store(wxCommand *command);

		virtual bool Undo();
		virtual bool Redo();
		virtual bool CanUndo() const;
		virtual bool CanRedo() const;

		// Initialises the current command and menu strings.
		virtual void Initialize();

		// Sets the Undo/Redo menu strings for the current menu.
		virtual void SetMenuStrings();

		virtual void ClearCommands();

		// Has the current project been changed?
		virtual bool IsDirty() const
		{
			return m_currentCommand && (m_lastSavedCommand != m_currentCommand);
		}


	protected:
		// for further flexibility, command processor doesn't call wxCommand::Do()
		// and Undo() directly but uses these functions which can be overridden in
		// the derived class
		virtual bool DoCommand(wxCommand& cmd);
		virtual bool UndoCommand(wxCommand& cmd);

		MutDocument * document;

	private:
		DECLARE_DYNAMIC_CLASS(MutCommandProcessor)
		DECLARE_NO_COPY_CLASS(MutCommandProcessor)
        };


	class MutDocument : public wxDocument
	{
		DECLARE_DYNAMIC_CLASS(MutDocument)
			public:
		MutDocument();
		virtual ~MutDocument();

		virtual wxCommandProcessor* OnCreateCommandProcessor();

		bool DoSaveDocument(const wxString& filename);

		bool DoOpenDocument(const wxString& filename);
		virtual bool OnNewDocument();

		virtual bool IsModified(void) const;
		virtual void Modify(bool mod);


		// save and load methods go here (backup for eventual usage)
#if wxUSE_STD_IOSTREAM
		virtual wxSTD ostream& SaveObject(wxSTD ostream& stream);
		virtual wxSTD istream& LoadObject(wxSTD istream& stream);
#else
		virtual wxOutputStream& SaveObject(wxOutputStream& stream);
		virtual wxInputStream& LoadObject(wxInputStream& stream);
#endif

		virtual bool OnCreate(const wxString& path, long flags);
		// event handlers go here
		void CmdNewView(wxCommandEvent& event);
		void OnNewViewUpdateUI(wxUpdateUIEvent& event);
		void CmdUpdateAllViews(wxCommandEvent& event);
	protected:
		/// Pass certain events to the Application.
		/** MutView::ProcessEvent is called indirectly from MutApp event 
		    handlers. This leads to endless loops. To prevent these loops, 
		    we must be very careful, which kind of events get passed back.
	    
		    Probably no events should be propagated.
		*/
		bool TryParent(wxEvent& event);		

	private:
		DECLARE_EVENT_TABLE()
			
        };

}

#endif

///\}

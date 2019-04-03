/** \file  -*- C++ -*-
 ********************************************************************
 * Document/View Document class for Mutabor source files.
 *
 * Copyright:   (c) 2011 TU Dresden
 * \author  Tobias Schlemmer <keinstein@users.sourceforge.net>
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
 ********************************************************************
 * \addtogroup docview
 * \{
 ********************************************************************/

// ---------------------------------------------------------------------------
// headers
// ---------------------------------------------------------------------------

#if (!defined(MUWX_MUTDOCUMENT_H) && !defined(PRECOMPILE)) \
	|| (!defined(MUWX_MUTDOCUMENT_H_PRECOMPILED))
#ifndef PRECOMPILE
#define MUWX_MUTDOCUMENT_H
#endif

// ---------------------------------------------------------------------------
// headers
// ---------------------------------------------------------------------------

#include "src/kernel/Defs.h"

#ifndef MUWX_MUTDOCUMENT_H_PRECOMPILED
#define MUWX_MUTDOCUMENT_H_PRECOMPILED

#include "wx/docview.h"
#include "wx/cmdproc.h"

MUTABOR_NAMESPACE(mutaborGUI)

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

		bool CheckLogic();
		virtual bool OnSaveModified();

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
		void CmImportScala(wxCommandEvent & event);
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

MUTABOR_NAMESPACE_END(mutaborGUI)

#endif
#endif

///\}

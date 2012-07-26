/** \file  -*- C++ -*-
 ***********************************************************************
 * Input device selection dialog.
 *
 * $Id: InputDevDlg.h,v 1.6 2011/11/02 14:32:00 keinstein Exp $
 * \author R. Krauße <krausze@users.berlios.de>
 * \date Created: 2005/12/10 14:22:47
 * $Date: 2011/11/02 14:32:00 $
 * \version $Revision: 1.6 $
 * \license: GPL
 * Copyright:   (c) R. Krauße, TU Dresden
 *
 * $Log: InputDevDlg.h,v $
 * Revision 1.6  2011/11/02 14:32:00  keinstein
 * fix some errors crashing Mutabor on Windows
 *
 * Revision 1.5  2011-09-30 18:07:05  keinstein
 * * make compile on windows
 * * s/wxASSERT/mutASSERT/g to get assert handler completely removed
 * * add ax_boost_base for boost detection
 *
 * Revision 1.4  2011-09-27 20:13:24  keinstein
 * * Reworked route editing backend
 * * rewireing is done by RouteClass/GUIRoute now
 * * other classes forward most requests to this pair
 * * many bugfixes
 * * Version change: We are reaching beta phase now
 *
 * Revision 1.3  2011-02-20 22:35:58  keinstein
 * updated license information; some file headers have to be revised, though
 *
 * Revision 1.2  2010-11-21 13:15:48  keinstein
 * merged experimental_tobias
 *
 * Revision 1.1.2.4  2010-06-15 14:30:14  keinstein
 * allow deleting of input devices in route window
 * several bug fixes
 * rudimentary box deletion support
 *
 * Revision 1.1.2.3  2010/03/30 08:38:27  keinstein
 * added rudimentary command line support
 * changed debug system to allow selection of messages via command line
 * further enhancements to the route dialogs
 *
 * Revision 1.1.2.2  2010/02/15 12:08:21  keinstein
 * intermediate update for backup progress
 *
 * Revision 1.1.2.1  2009/11/30 15:46:46  keinstein
 * moved InputDevDlg.h InputDevDlg.cpp OutputDevDlg.h OutputDevDlg.cpp into subdirectory Routing.
 *
 * Revision 1.6.2.2  2009/11/03 15:07:07  keinstein
 * Compile on Ubuntu 9.10
 * remove several interface and implementation pragmas
 * fixed some file names for case insensitive filesystems
 *
 * Revision 1.6.2.1  2009/08/10 11:23:12  keinstein
 * merged from wrong tree
 *
 * Revision 1.7  2009/08/10 11:15:46  keinstein
 * some steps towards new route window
 *
 * Revision 1.6  2008/08/18 15:06:35  keinstein
 * Changed Input dev dialog to wxResources
 *
 * Revision 1.5  2008/01/25 09:08:58  keinstein
 * charset conversion
 *
 * Revision 1.4  2006/01/18 15:34:57  keinstein
 * Doxygen header
 *
 * ID definition conflict solved
 *
 *
 ********************************************************************
 * \addtogroup route
 * \{
 ********************************************************************/

/* we guard a little bit complicated to ensure the references are set right
 */

#if (!defined(MUWX_ROUTING_INPUTDEVDLG_H) && !defined(PRECOMPILE)) \
	|| (!defined(MUWX_ROUTING_INPUTDEVDLG_H_PRECOMPILED))
#ifndef PRECOMPILE
#define MUWX_ROUTING_INPUTDEVDLG_H
#endif

// ---------------------------------------------------------------------------
// headers
// ---------------------------------------------------------------------------

#include "src/kernel/Defs.h"
#include "src/wxGUI/resourceload.h"
#include "src/kernel/routing/Device.h"

#ifndef MUWX_ROUTING_INPUTDEVDLG_H_PRECOMPILED
#define MUWX_ROUTING_INPUTDEVDLG_H_PRECOMPILED

// system headers which do seldom change

#include "wx/xrc/xmlres.h"
#include "wx/html/htmlwin.h"
#include "wx/statline.h"
#include "wx/filepicker.h"
#include "wx/valgen.h"
#include "wx/valtext.h"

namespace mutaborGUI {


#if 0
/*!
 * Control identifiers
 */

#define ID_INPDIALOG 10010
#define SYMBOL_INPUTDEVDLG_STYLE wxCAPTION|wxRESIZE_BORDER|wxSYSTEM_MENU|wxCLOSE_BOX
#define SYMBOL_INPUTDEVDLG_TITLE _("Input Device")
#define SYMBOL_INPUTDEVDLG_IDNAME ID_INPDIALOG
#define SYMBOL_INPUTDEVDLG_SIZE wxSize(400, 300)
#define SYMBOL_INPUTDEVDLG_POSITION wxDefaultPosition
#define ID_CHOICE 10011
#define ID_CHOICE1 10012
#define ID_TEXTCTRL 10013
#define ID_BUTTON 10014
#define ID_TEXTCTRL1 10015
#define ID_BUTTON1 10016

#endif

	class InputDevDlg: public InputDevDlgBase
	{
		DECLARE_DYNAMIC_CLASS( InputDevDlg )
		DECLARE_EVENT_TABLE()

		protected:
		wxSizer *Container,* TypeBox, *PortBox, *MidiFileBox, *GuidoFileBox;

		struct TypeData:wxClientData
		{
			mutabor::DevType nr;
			TypeData(mutabor::DevType i):wxClientData()
				{
					nr=i;
				}

			bool operator == (mutabor::DevType i)
				{
					if (this)
						return i == nr;
					else return false;
				}

			operator mutabor::DevType()
				{
					if (this) return nr;
					else return mutabor::DTNotSet;
				}
		};

		int FindType (mutabor::DevType t);

	public:
		/// Constructors
		InputDevDlg( wxWindow* parent = NULL);

		/// wxEVT_COMMAND_CHOICE_SELECTED event handler for ID_CHOICE
		void OnChoiceSelected( wxCommandEvent& event );

		/// wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_BUTTON
		void OnRemoveClick( wxCommandEvent& event );

		void OnFileChanged ( wxFileDirPickerEvent & event );

		void UpdateLayout(mutabor::DevType type);

		int GetMidiDevice() const
			{
				return PortChoice->GetSelection() ;
			}

		void SetMidiDevice(int value)

			{
				DEBUGLOG(other, _T("%d"),value);
				PortChoice->SetSelection (value) ;
				Update();
			}

		wxString GetMidiFile() const
			{
				return MidiFilePicker->GetPath() ;
			}

		void SetMidiFile(wxString value)

			{
				DEBUGLOG(other, value);
				MidiFilePicker->SetPath(value);
				Update();
				DEBUGLOG(other, _T("done"));
			}

		wxString GetGUIDOFile() const
			{
				return GuidoFilePicker->GetPath() ;
			}

		void SetGUIDOFile(wxString value)

			{
				DEBUGLOG(other, value);
				GuidoFilePicker->SetPath(value);
				Update();
			}

		mutabor::DevType GetType() const
			{
				int Type = DeviceChoice->GetSelection();
				if (Type == wxNOT_FOUND) return mutabor::DTNotSet;

				mutASSERT (dynamic_cast<TypeData *>(DeviceChoice->GetClientObject(Type)));
				TypeData * obj = (TypeData *)DeviceChoice->GetClientObject(Type);

				if (obj) return  *obj;
				else return mutabor::DTNotSet;
			}

		void SetType(mutabor::DevType value)

			{
				DEBUGLOG(other, _T("%d"),value);
				UpdateLayout(value);
				Update();
			}

		wxString GetPortString(int i)
			{
				return PortChoice->GetString (i);
			}

		void AppendPortChoice (const wxString &s)
			{
				PortChoice->Append (s);
			}
	
		void DisableRemove (bool disable=true) 
			{
				wxID_REMOVE->Show(!disable);
				wxID_REMOVE->Enable(!disable);
			}

		/// Retrieves bitmap resources
		wxBitmap GetBitmapResource (const wxString& name );

		/// Retrieves icon resources
		wxIcon GetIconResource (const wxString& name );

		/// Should we show tooltips?
		static bool ShowToolTips ();

	};
}
#endif
// _INPUTDEVDLG_H_PRECOMPILED
#endif
// _INPUTDEVDLG_H_


///\}

/** \file               -*- C++ -*-
 ***********************************************************************
 * Input device selection dialog.
 *
 * \author R. Krauße <krausze@users.berlios.de>
 *   T. Schlemmer <keinstein@users.berlios.de>
 * \date Created: 2005/12/10 14:22:47
 * $Date: 2011/09/30 18:07:04 $
 * \license: GPL
 * Copyright:   (c) R. Krauße, TU Dresden
 *
 *
 * \addtogroup route
 * \{
 ********************************************************************/

#if (!defined(MUWX_INPUTDEVDLG_H) && !defined(PRECOMPILE)) \
	|| (!defined(MUWX_INPUTDEVDLG_H_PRECOMPILED))
#ifndef PRECOMPILE
#define MUWX_INPUTDEVDLG_H
#endif

// our dedendencies
#include "Defs.h"
#include "wxresource.h"
#include "Device.h"

#if defined(__GNUG__) && !defined(__APPLE__)
#pragma interface "InputDevDlg.cpp"
#endif


#ifndef MUWX_INPUTDEVDLG_H_PRECOMPILED
#define MUWX_INPUTDEVDLG_H_PRECOMPILED
/*!
 * system includes
 */

////@begin includes
#include "wx/xrc/xmlres.h"
#include "wx/html/htmlwin.h"
#include "wx/statline.h"
#include "wx/filepicker.h"
#include "wx/valgen.h"
#include "wx/valtext.h"
////@end includes


#if 0
/*!
 * Forward declarations
 */

////@begin forward declarations

class wxBoxSizer;
////@end forward declarations

/*!
 * Control identifiers
 */

////@begin control identifiers
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
////@end control identifiers

/*!
 * Compatibility
 */

#ifndef wxCLOSE_BOX
#define wxCLOSE_BOX 0x1000
#endif
#ifndef wxFIXED_MINSIZE
#define wxFIXED_MINSIZE 0
#endif

/*!
 * InputDevDlg class declaration
 */

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
		DEBUGLOG(other,_T("%d"),value);
		PortChoice->SetSelection (value) ;
		Update();
	}

	wxString GetMidiFile() const
	{
		return MidiFilePicker->GetPath() ;
	}

	void SetMidiFile(wxString value)

	{
		DEBUGLOG(other,value);
		MidiFilePicker->SetPath(value);
		Update();
		DEBUGLOG(other,_T("done"));
	}

	wxString GetGUIDOFile() const
	{
		return GuidoFilePicker->GetPath() ;
	}

	void SetGUIDOFile(wxString value)

	{
		DEBUGLOG(other,_T("%s"),(const wxChar*)value);
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
		DEBUGLOG(other,_T("%d"),value);
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

	/// Retrieves bitmap resources
	wxBitmap GetBitmapResource (const wxString& name );

	/// Retrieves icon resources
	wxIcon GetIconResource (const wxString& name );

	/// Should we show tooltips?
	static bool ShowToolTips ();

};

#endif // precompiled
#endif
// _INPUTDEVDLG_H_


///\}

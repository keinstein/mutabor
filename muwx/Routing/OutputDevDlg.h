/** \file
 ***********************************************************************
 * Input device selection dialog.
 *
 * $Id: OutputDevDlg.h,v 1.2 2010/11/21 13:15:49 keinstein Exp $
 * \author R. Krauße <krausze@users.berlios.de>
 * \date Created: 2005/12/10 14:22:47
 * $Date: 2010/11/21 13:15:49 $
 * \version $Revision: 1.2 $
 * \license: GPL
 * Copyright:   (c) R. Krauße, TU Dresden
 *
 * $Log: OutputDevDlg.h,v $
 * Revision 1.2  2010/11/21 13:15:49  keinstein
 * merged experimental_tobias
 *
 * Revision 1.1.2.5  2010-06-22 15:05:45  keinstein
 * debugging segfault in route check after replacement of MutOutputDevice
 *
 * Revision 1.1.2.4  2010/03/30 08:38:27  keinstein
 * added rudimentary command line support
 * changed debug system to allow selection of messages via command line
 * further enhancements to the route dialogs
 *
 * Revision 1.1.2.3  2010/02/15 12:08:21  keinstein
 * intermediate update for backup progress
 *
 * Revision 1.1.2.2  2010/01/14 09:34:24  keinstein
 * Checkin searching for a bug
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
 */

#ifndef _OUTPUTDEVDLG_H_
#define _OUTPUTDEVDLG_H_


/*!
 * Includes
 */

#include "Defs.h"
#include "wx/xrc/xmlres.h"
#include "wx/html/htmlwin.h"
#include "wx/statline.h"
#include "wx/filepicker.h"
#include "resourceload.h"
#include "Device.h"
#include "wx/valgen.h"
#include "wx/valtext.h"


class OutputDevDlg: public OutputDevDlgBase
{
	DECLARE_DYNAMIC_CLASS( OutputDevDlg )
	DECLARE_EVENT_TABLE()

protected:
	wxSizer *Container,* TypeBox, *PortBox, *MidiFileBox, *GuidoFileBox;

struct TypeData:wxClientData
	{
		DevType nr;
		TypeData(DevType i):wxClientData()
		{
			nr=i;
		}

		bool operator == (DevType i)
		{
			if (this)
				return i == nr;
			else return false;
		}

		operator DevType()
		{
			if (this) return nr;
			else return DTNotSet;
		}
	};

	int FindType (DevType t);

public:
	/// Constructors
	OutputDevDlg( wxWindow* parent = NULL);

	/// wxEVT_COMMAND_CHOICE_SELECTED event handler for ID_CHOICE
	void OnChoiceSelected( wxCommandEvent& event );

	/// wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_BUTTON
	void OnRemoveClick( wxCommandEvent& event );

        void OnFileChanged ( wxFileDirPickerEvent & event );

	void UpdateLayout(DevType type);

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
		InvalidateBestSize();
		SetInitialSize(wxDefaultSize);
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

	DevType GetType() const
	{
                int Type = DeviceChoice->GetSelection();
		if (Type == wxNOT_FOUND) return DTNotSet;

                wxASSERT (dynamic_cast<TypeData *>(DeviceChoice->GetClientObject(Type)));
		TypeData * obj = (TypeData *)DeviceChoice->GetClientObject(Type);

		if (obj) return  *obj;
		else return DTNotSet;
	}

	void SetType(DevType value)

	{
		DEBUGLOG(other, _T("%d"),value);
		UpdateLayout(value);
		Update();
	}

        long GetMidiBendingRange() {
                return MidiBendingRange->GetValue();
        }

        void SetMidiBendingRange (long i) {
                MidiBendingRange->SetValue (i);
        }

        long GetMidiFileBendingRange() {
                return MidiFileBendingRange->GetValue();
        }

        void SetMidiFileBendingRange (long i) {
                MidiFileBendingRange->SetValue (i);
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

#endif
// _OUTPUTDEVDLG_H_


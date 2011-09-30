/** \file   -*- C++ -*-
 ***********************************************************************
 * Input device selection dialog.
 *
 * $Id: OutputDevDlg.h,v 1.4 2011/09/30 18:07:06 keinstein Exp $
 * \author R. Krauße <krausze@users.berlios.de>
 * \date Created: 2005/12/10 14:22:47
 * $Date: 2011/09/30 18:07:06 $
 * \version $Revision: 1.4 $
 * \license: GPL
 * Copyright:   (c) R. Krauße, TU Dresden
 *
 * $Log: OutputDevDlg.h,v $
 * Revision 1.4  2011/09/30 18:07:06  keinstein
 * * make compile on windows
 * * s/wxASSERT/mutASSERT/g to get assert handler completely removed
 * * add ax_boost_base for boost detection
 *
 * Revision 1.3  2011-09-27 20:13:25  keinstein
 * * Reworked route editing backend
 * * rewireing is done by RouteClass/GUIRoute now
 * * other classes forward most requests to this pair
 * * many bugfixes
 * * Version change: We are reaching beta phase now
 *
 * Revision 1.2  2010-11-21 13:15:49  keinstein
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

/* we guard a little bit complicated to ensure the references are set right
 */

#if (!defined(MUWX_ROUTING_OUTPUTDEVDLG_H) && !defined(PRECOMPILE)) \
	|| (!defined(MUWX_ROUTING_OUTPUTDEVDLG_H_PRECOMPILED))
#ifndef PRECOMPILE
#define MUWX_ROUTING_OUTPUTDEVDLG_H
#endif

// ---------------------------------------------------------------------------
// headers
// ---------------------------------------------------------------------------

#include "Defs.h"
#include "resourceload.h"
#include "Device.h"

#ifndef MUWX_ROUTING_OUTPUTDEVDLG_H_PRECOMPILED
#define MUWX_ROUTING_OUTPUTDEVDLG_H_PRECOMPILED

// system headers which do seldom change

/*!
 * Includes
 */

#include "wx/xrc/xmlres.h"
#include "wx/html/htmlwin.h"
#include "wx/statline.h"
#include "wx/filepicker.h"
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
	OutputDevDlg( wxWindow* parent = NULL);

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
// _OUTPUTDEVDLG_H_PRECOMPILED
#endif
// _OUTPUTDEVDLG_H_


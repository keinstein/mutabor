/** \file 
 ********************************************************************
 * Input device dialog
 *
 * Copyright:   (c) 2005 TU Dresden
 * \author   R. Krauße,
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
 *
 *
 ********************************************************************
 * \addtogroup GUIroute
 * \{
 ********************************************************************/

#include "src/kernel/Defs.h"

#include "src/kernel/routing/Route-inlines.h"
#include "src/wxGUI/Routing/InputDevDlg.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif


using namespace mutabor;

namespace mutaborGUI {

/*!
 * InputDevDlg type definition
 */

	IMPLEMENT_DYNAMIC_CLASS( InputDevDlg, InputDevDlgBase )

	BEGIN_EVENT_TABLE( InputDevDlg, InputDevDlgBase )
	EVT_CHOICE( XRCID("DeviceChoice"), InputDevDlg::OnChoiceSelected )
        EVT_BUTTON( ::wxID_REMOVE, InputDevDlg::OnRemoveClick )
        EVT_FILEPICKER_CHANGED(XRCID ("MidiFilePicker"), 
                               InputDevDlg::OnFileChanged)
        EVT_FILEPICKER_CHANGED(XRCID ("GuidoFilePicker"), 
                               InputDevDlg::OnFileChanged)
	END_EVENT_TABLE()

	/*!
	 * InputDevDlg constructors
	 */
	/* \todo: find out, how we can reuse a file Picker for different file types */

	InputDevDlg::InputDevDlg( wxWindow* parent):InputDevDlgBase(parent)
	{
		DeviceChoice->Clear();
		DeviceChoice->Append(_("MIDI Device"),
				     static_cast<wxClientData *>(new TypeData(DTMidiPort)));
		DeviceChoice->Append(_("MIDI file"),new TypeData(DTMidiFile));
		DeviceChoice->Append(_("GUIDO file"),new TypeData(DTGis));

		TypeBox = DeviceChoice->GetContainingSizer();
		PortBox = PortChoice->GetContainingSizer();
		MidiFileBox = MidiFilePicker->GetContainingSizer();
		DEBUGLOG (other, ("MidiFilePicker Growable: %d"), MidiFilePicker->IsPickerCtrlGrowable());
		if (MidiFilePicker->HasTextCtrl()) {
			DEBUGLOG (other, ("MidiFileTextCtrl Growable: %d"), 
				  MidiFilePicker->IsTextCtrlGrowable());
			MidiFilePicker->SetTextCtrlGrowable(true);
			DEBUGLOG (other, ("MidiFileTextCtrl Growable: %d"), 
				  MidiFilePicker->IsTextCtrlGrowable());
		}
		GuidoFileBox = GuidoFilePicker->GetContainingSizer();

//	GetSizer()->Fit(this);
//	GetSizer()->SetSizeHints(this);
//	Centre();
	}

/*!
 * Should we show tooltips?
 */

	bool InputDevDlg::ShowToolTips()
	{
		return TRUE;
	}

/*!
 * Get bitmap resources
 */

	wxBitmap InputDevDlg::GetBitmapResource( const wxString& name )
	{
		mutUnused(name);
		// Bitmap retrieval
		return wxNullBitmap;
	}

/*!
 * Get icon resources
 */

	wxIcon InputDevDlg::GetIconResource( const wxString& name )
	{
		mutUnused(name);
		// Icon retrieval
		return wxNullIcon;
	}

/*!
 * wxEVT_COMMAND_CHOICE_SELECTED event handler for ID_CHOICE
 */

	void InputDevDlg::OnChoiceSelected( wxCommandEvent& event )
	{
		UpdateLayout(GetType());
		event.Skip();
	}

	void InputDevDlg::UpdateLayout(DevType type)
	{
		if (type == DTNotSet) {
			if (FindType (type) == wxNOT_FOUND)
				DeviceChoice->Insert (_ ("Choose device type"),
						      0,
						      new TypeData (type));
		} else {
			int notset = FindType (DTNotSet);
			if (notset != wxNOT_FOUND) {
				DeviceChoice->Delete (notset);
			}

			if (type == DTUnknown) {
				if (FindType (type) == wxNOT_FOUND)
					DeviceChoice->Insert (_ ("Unknown device type"),
							      0,
							      new TypeData (type));
			}
		}
		int Type = FindType (type);
		DeviceChoice -> SetSelection (Type);

		DEBUGLOG (other, "%d" ,type);
		wxSizer * sizer = GetSizer();

		DEBUGLOG (other, "%d" ,DTMidiPort);
		sizer->Show(PortBox, type == DTMidiPort, true);
		DEBUGLOG (other, "%d" ,DTMidiFile);
		sizer->Show(MidiFileBox, (type == DTMidiFile), true);
		DEBUGLOG (other, "%d" ,DTGis);
		sizer->Show(GuidoFileBox, (type == DTGis) , true);

		// We need Layout here, since otherwise the input boxex are not
		// shown in certain circumstances
		Layout();
		GetSizer()->SetSizeHints(this);
		Fit();
	}


/*!
 * wxEVT_COMMAND_BUTTON_CLICKED event handler for wxID_REMOVE
 */

	void InputDevDlg::OnRemoveClick( wxCommandEvent& event )
	{
		mutUnused(event);
		EndModal(::wxID_REMOVE);
	}

	void InputDevDlg::OnFileChanged ( wxFileDirPickerEvent & event ) 
	{
		DEBUGLOG (other, ("Path changed: %s"),event.GetPath().c_str());
		GetSizer()->SetSizeHints(this);
		Fit();
	}


	int InputDevDlg::FindType (DevType t)
	{
		TypeData * Data;
		for (unsigned int i = 0; i < DeviceChoice->GetCount(); i++) {
			DEBUGLOG (other, ("Choice #%d of %d"),i, DeviceChoice->GetCount());
			Data = (TypeData *)DeviceChoice->GetClientObject(i);
			if (Data) {
				if (*Data == t) return i;
			}
		}
		return wxNOT_FOUND;
	}

}
///\}

// -*-C++ -*-
/** \file
********************************************************************
* MIDI input device shape for route window.
*
* \author Rüdiger Krauße <krausze@mail.berlios.de>,
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
*\addtogroup GUIroute
*\{
********************************************************************/

#include "src/kernel/Defs.h"

#include "src/kernel/routing/Route-inlines.h"
#include "src/wxGUI/Routing/OutputDevDlg.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

using namespace mutabor;

/*!
 * OutputDevDlg type definition
 */

IMPLEMENT_DYNAMIC_CLASS( mutaborGUI::OutputDevDlg, OutputDevDlgBase )

namespace mutaborGUI {

	BEGIN_EVENT_TABLE( OutputDevDlg, OutputDevDlgBase )
	EVT_CHOICE( XRCID("DeviceChoice"), OutputDevDlg::OnChoiceSelected )
	EVT_BUTTON( ::wxID_REMOVE, OutputDevDlg::OnRemoveClick )
        EVT_FILEPICKER_CHANGED(XRCID ("MidiFilePicker"), 
                               OutputDevDlg::OnFileChanged)
        EVT_FILEPICKER_CHANGED(XRCID ("GuidoFilePicker"), 
                               OutputDevDlg::OnFileChanged)
	END_EVENT_TABLE()

	/*!
	 * OutputDevDlg constructors
	 */
	/* \todo: find out, how we can reuse a file Picker for different file types */

	OutputDevDlg::OutputDevDlg( wxWindow* parent):OutputDevDlgBase(parent)
	{
		DeviceChoice->Clear();
		DeviceChoice->Append(_("MIDI Device"), new TypeData(DTMidiPort));
		DeviceChoice->Append(_("MIDI file"),   new TypeData(DTMidiFile));
		DeviceChoice->Append(_("GUIDO file"),  new TypeData(DTGis));

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

	bool OutputDevDlg::ShowToolTips()
	{
		return TRUE;
	}

/*!
 * Get bitmap resources
 */

	wxBitmap OutputDevDlg::GetBitmapResource( const wxString& name )
	{
		mutUnused(name);
		return wxNullBitmap;
	}

/*!
 * Get icon resources
 */

	wxIcon OutputDevDlg::GetIconResource( const wxString& name )
	{
		mutUnused(name);
		return wxNullIcon;
	}

/*!
 * wxEVT_COMMAND_CHOICE_SELECTED event handler for ID_CHOICE
 */

	void OutputDevDlg::OnChoiceSelected( wxCommandEvent& event )
	{
		DevType data = GetType();
		UpdateLayout(data);
		event.Skip();
	}

	void OutputDevDlg::UpdateLayout(DevType type)
	{
		DEBUGLOG (other, "type: %d" ,type);
		if (type == DTNotSet) {
			DEBUGLOG (other, "Type not set" );
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

		DEBUGLOG (other, "found Number %d (wxNOT_FOUND=%d)" ,type,wxNOT_FOUND);
		wxSizer * sizer = GetSizer();

		DEBUGLOG (other, "DTMidiPort=%d" ,DTMidiPort);
		sizer->Show(PortBox, type == DTMidiPort, true);
		DEBUGLOG (other, "DTMidiFile=%d" ,DTMidiFile);
		sizer->Show(MidiFileBox, (type == DTMidiFile), true);
		DEBUGLOG (other, "DTGis=%d" ,DTGis);
		sizer->Show(GuidoFileBox, (type == DTGis) , true);

		// We need Layout here, since otherwise the output boxex are not
		// shown in certain circumstances
		//CenterOnScreen();
		Layout();
		GetSizer()->SetSizeHints(this);
		Fit();
	}


/*!
 * wxEVT_COMMAND_BUTTON_CLICKED event handler for wxID_REMOVE
 */

	void OutputDevDlg::OnRemoveClick( wxCommandEvent& event )
	{
		mutUnused(event);
		EndModal(::wxID_REMOVE);
	}

	void OutputDevDlg::OnFileChanged ( wxFileDirPickerEvent & event ) 
	{
		mutUnused(event);
		DEBUGLOG (other, ("Path changed: %s"),event.GetPath().c_str());
		SetSize(wxDefaultSize);
		Layout();
		Fit();
	}


	int OutputDevDlg::FindType (DevType t)
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

/** \file 
 ********************************************************************
 * Input device dialog
 *
 * $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/muwx/Routing/InputDevDlg.cpp,v 1.6 2011/11/02 14:32:00 keinstein Exp $
 * Copyright:   (c) 2005 TU Dresden
 * \author   R. Krauße,
 * Tobias Schlemmer <keinstein@users.berlios.de>
 * \date 2005-10-12 14:22:47
 * $Date: 2011/11/02 14:32:00 $
 * \version $Revision: 1.6 $
 * \license GPL
 *
 * $Log: InputDevDlg.cpp,v $
 * Revision 1.6  2011/11/02 14:32:00  keinstein
 * fix some errors crashing Mutabor on Windows
 *
 * Revision 1.5  2011-09-27 20:13:24  keinstein
 * * Reworked route editing backend
 * * rewireing is done by RouteClass/GUIRoute now
 * * other classes forward most requests to this pair
 * * many bugfixes
 * * Version change: We are reaching beta phase now
 *
 * Revision 1.4  2011-02-20 22:35:58  keinstein
 * updated license information; some file headers have to be revised, though
 *
 *
 *
 ********************************************************************
 * \addtogroup templates
 * \{
 ********************************************************************/

#include "mu32/Defs.h"

#include "muwx/Routing/InputDevDlg.h"

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
		DeviceChoice->Append(_("MIDI Device"),new TypeData(DTMidiPort));
		DeviceChoice->Append(_("MIDI file"),new TypeData(DTMidiFile));
		DeviceChoice->Append(_("GUIDO file"),new TypeData(DTGis));

		TypeBox = DeviceChoice->GetContainingSizer();
		PortBox = PortChoice->GetContainingSizer();
		MidiFileBox = MidiFilePicker->GetContainingSizer();
		DEBUGLOG (other,_T ("MidiFilePicker Growable: %d"), MidiFilePicker->IsPickerCtrlGrowable());
		if (MidiFilePicker->HasTextCtrl()) {
			DEBUGLOG (other,_T ("MidiFileTextCtrl Growable: %d"), 
				  MidiFilePicker->IsTextCtrlGrowable());
			MidiFilePicker->SetTextCtrlGrowable(true);
			DEBUGLOG (other,_T ("MidiFileTextCtrl Growable: %d"), 
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

		DEBUGLOG (other, _T("%d"),type);
		wxSizer * sizer = GetSizer();

		DEBUGLOG (other, _T("%d"),DTMidiPort);
		sizer->Show(PortBox, type == DTMidiPort, true);
		DEBUGLOG (other, _T("%d"),DTMidiFile);
		sizer->Show(MidiFileBox, (type == DTMidiFile), true);
		DEBUGLOG (other, _T("%d"),DTGis);
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
		DEBUGLOG (other,_T ("Path changed: %s"),event.GetPath().c_str());
		GetSizer()->SetSizeHints(this);
		Fit();
	}


	int InputDevDlg::FindType (DevType t)
	{
		TypeData * Data;
		for (unsigned int i = 0; i < DeviceChoice->GetCount(); i++) {
			DEBUGLOG (other,_T ("Choice #%d of %d"),i, DeviceChoice->GetCount());
			Data = (TypeData *)DeviceChoice->GetClientObject(i);
			if (Data) {
				if (*Data == t) return i;
			}
		}
		return wxNOT_FOUND;
	}

}
///\}

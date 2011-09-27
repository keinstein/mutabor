/** \file 
 ********************************************************************
 * Description
 *
 * $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/muwx/InputDevDlg.cpp,v 1.8 2011/09/27 20:13:22 keinstein Exp $
 * Copyright:   (c) 2005,2011 TU Dresden
 * \author R. Krauße
 * Tobias Schlemmer <keinstein@users.berlios.de>
 * \date 2005/10/12 14:22:47
 * $Date: 2011/09/27 20:13:22 $
 * \version $Revision: 1.8 $
 * \license GPL
 *
 * $Log: InputDevDlg.cpp,v $
 * Revision 1.8  2011/09/27 20:13:22  keinstein
 * * Reworked route editing backend
 * * rewireing is done by RouteClass/GUIRoute now
 * * other classes forward most requests to this pair
 * * many bugfixes
 * * Version change: We are reaching beta phase now
 *
 * Revision 1.7  2011-02-20 22:35:57  keinstein
 * updated license information; some file headers have to be revised, though
 *
 *
 * \addtogroup route
 * \{
 ********************************************************************/

#include "Defs.h"
#include "InputDevDlg.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif



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
        DEBUGLOG (_T ("MidiFilePicker Growable: %d"), MidiFilePicker->IsPickerCtrlGrowable());
        if (MidiFilePicker->HasTextCtrl()) {
                DEBUGLOG (_T ("MidiFileTextCtrl Growable: %d"), 
                          MidiFilePicker->IsTextCtrlGrowable());
                MidiFilePicker->SetTextCtrlGrowable(true);
                DEBUGLOG (_T ("MidiFileTextCtrl Growable: %d"), 
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
	// Bitmap retrieval
////@begin InputDevDlg bitmap retrieval
	return wxNullBitmap;
////@end InputDevDlg bitmap retrieval
}

/*!
 * Get icon resources
 */

wxIcon InputDevDlg::GetIconResource( const wxString& name )
{
	// Icon retrieval
////@begin InputDevDlg icon retrieval
	return wxNullIcon;
////@end InputDevDlg icon retrieval
}

/*!
 * wxEVT_COMMAND_CHOICE_SELECTED event handler for ID_CHOICE
 */

void InputDevDlg::OnChoiceSelected( wxCommandEvent& event )
{
	int i = DeviceChoice->GetSelection();
	TypeData * data =(TypeData *)DeviceChoice->GetClientObject(i);
	UpdateLayout(*data);
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

	DEBUGLOG(_T("%d"),type);
	wxSizer * sizer = GetSizer();

	DEBUGLOG(_T("%d"),DTMidiPort);
	sizer->Show(PortBox, type == DTMidiPort, true);
	DEBUGLOG(_T("%d"),DTMidiFile);
	sizer->Show(MidiFileBox, (type == DTMidiFile), true);
	DEBUGLOG(_T("%d"),DTGis);
	sizer->Show(GuidoFileBox, (type == DTGis) , true);

//	Layout();
//	GetSizer()->SetSizeHints(this);
	Fit();
}


/*!
 * wxEVT_COMMAND_BUTTON_CLICKED event handler for wxID_REMOVE
 */

void InputDevDlg::OnRemoveClick( wxCommandEvent& event )
{
	EndModal(::wxID_REMOVE);
}

void InputDevDlg::OnFileChanged ( wxFileDirPickerEvent & event ) 
{
        DEBUGLOG (_T ("Path changed: %s"),event.GetPath().c_str());
        Fit();
}


int InputDevDlg::FindType (DevType t)
{
        TypeData * Data;
	for (unsigned int i = 0; i < DeviceChoice->GetCount(); i++) {
                DEBUGLOG (_T ("Choice #%d of %d"),i, DeviceChoice->GetCount());
                Data = (TypeData *)DeviceChoice->GetClientObject(i);
                if (Data) {
                        if (*Data == t) return i;
                }
        }
	return wxNOT_FOUND;
}


///\}

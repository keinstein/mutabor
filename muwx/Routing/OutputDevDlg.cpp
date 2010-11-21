// -*-C++ -*-

/** \file
********************************************************************
* MIDI input device shape for route window.
*
* $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/muwx/Routing/OutputDevDlg.cpp,v 1.2 2010/11/21 13:15:49 keinstein Exp $
* \author Rüdiger Krauße <krausze@mail.berlios.de>,
* Tobias Schlemmer <keinstein@users.berlios.de>
* \date 2009/01/11
* $Date: 2010/11/21 13:15:49 $
* \version $Revision: 1.2 $
*
* $Log: OutputDevDlg.cpp,v $
* Revision 1.2  2010/11/21 13:15:49  keinstein
* merged experimental_tobias
*
* Revision 1.1.2.6  2010-03-30 08:38:27  keinstein
* added rudimentary command line support
* changed debug system to allow selection of messages via command line
* further enhancements to the route dialogs
*
* Revision 1.1.2.5  2010/02/15 12:08:21  keinstein
* intermediate update for backup progress
*
* Revision 1.1.2.4  2010/01/14 18:14:20  keinstein
* fix usage of installation prefix
* MutInputDeviceShape/MutOutputDeviceShape:
*     use GetType for type checking in OnChoiceSelected
*     make InitalizeDialog const
* MutNewOutputDeviceShape: add InitializeDialog and ReplaceSelfBy
*
* Revision 1.1.2.3  2010/01/14 09:34:24  keinstein
* Checkin searching for a bug
*
*
*
********************************************************************
*\addtogroup route
*\{
********************************************************************/

// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif




#include "OutputDevDlg.h"

/*!
 * OutputDevDlg type definition
 */

IMPLEMENT_DYNAMIC_CLASS( OutputDevDlg, OutputDevDlgBase )

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

bool OutputDevDlg::ShowToolTips()
{
	return TRUE;
}

/*!
 * Get bitmap resources
 */

wxBitmap OutputDevDlg::GetBitmapResource( const wxString& name )
{
	// Bitmap retrieval
////@begin OutputDevDlg bitmap retrieval
	return wxNullBitmap;
////@end OutputDevDlg bitmap retrieval
}

/*!
 * Get icon resources
 */

wxIcon OutputDevDlg::GetIconResource( const wxString& name )
{
	// Icon retrieval
////@begin OutputDevDlg icon retrieval
	return wxNullIcon;
////@end OutputDevDlg icon retrieval
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
	DEBUGLOG (other, _T("type: %d"),type);
        if (type == DTNotSet) {
		DEBUGLOG (other, _T("Type not set"));
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

	DEBUGLOG (other, _T("found Number %d (wxNOT_FOUND=%d)"),type,wxNOT_FOUND);
	wxSizer * sizer = GetSizer();

	DEBUGLOG (other, _T("DTMidiPort=%d"),DTMidiPort);
	sizer->Show(PortBox, type == DTMidiPort, true);
	DEBUGLOG (other, _T("DTMidiFile=%d"),DTMidiFile);
	sizer->Show(MidiFileBox, (type == DTMidiFile), true);
	DEBUGLOG (other, _T("DTGis=%d"),DTGis);
	sizer->Show(GuidoFileBox, (type == DTGis) , true);

        // We need Layout here, since otherwise the output boxex are not
        // shown in certain circumstances
	sizer->Layout();
	sizer->SetSizeHints(this);
	SetSize(-1, -1, 0, 0);
	//CenterOnScreen();
}


/*!
 * wxEVT_COMMAND_BUTTON_CLICKED event handler for wxID_REMOVE
 */

void OutputDevDlg::OnRemoveClick( wxCommandEvent& event )
{
	EndModal(::wxID_REMOVE);
}

void OutputDevDlg::OnFileChanged ( wxFileDirPickerEvent & event ) 
{
        DEBUGLOG (other,_T ("Path changed: %s"),event.GetPath().c_str());
	SetSize(wxDefaultSize);
	Layout();
        Fit();
}


int OutputDevDlg::FindType (DevType t)
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

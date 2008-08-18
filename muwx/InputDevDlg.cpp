/////////////////////////////////////////////////////////////////////////////
// Name:        InputDevDlg.cpp
// Purpose:     
// Author:      R. Krauße
// Modified by: 
// Created:     10/12/05 14:22:47
// RCS-ID:      
// Copyright:   (c) R. Krauße, TU Dresden
// Licence:     
/////////////////////////////////////////////////////////////////////////////

#if defined(__GNUG__) && !defined(__APPLE__)
#pragma implementation "InputDevDlg.h"
#endif

// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

////@begin includes
////@end includes

#include "InputDevDlg.h"

/*!
 * InputDevDlg type definition
 */

IMPLEMENT_DYNAMIC_CLASS( InputDevDlg, InputDevDlgBase )

BEGIN_EVENT_TABLE( InputDevDlg, InputDevDlgBase )
    EVT_CHOICE( XRCID("DeviceChoice"), InputDevDlg::OnChoiceSelected )
    EVT_BUTTON( ::wxID_REMOVE, InputDevDlg::OnRemoveClick )
END_EVENT_TABLE()

/*!
 * InputDevDlg constructors
 */
/* \todo: find out, how we can reuse a file Picker for different file types */

InputDevDlg::InputDevDlg( wxWindow* parent):InputDevDlgBase(parent),
  MidiDevice(0),
  Type(0),
  typeVal((int *)&Type),
  deviceVal(&MidiDevice)
{
  DeviceChoice->Clear();
  DeviceChoice->Append(_("MIDI Device"),new TypeData(DTMidiPort));
  DeviceChoice->Append(_("MIDI file"),new TypeData(DTMidiFile));
  DeviceChoice->Append(_("GUIDO file"),new TypeData(DTGis));
  

  //  DeviceChoice->SetID(ID_CHOICE);
  DeviceChoice->SetValidator(typeVal);
  PortChoice->SetValidator(deviceVal);
  // MidiFilePicker->SetValidator(midifileVal);
  // GuidoFilePicker->SetValidator(guidofileVal);

  TypeBox = DeviceChoice->GetContainingSizer();
  PortBox = PortChoice->GetContainingSizer();
  MidiFileBox = MidiFilePicker->GetContainingSizer();
  GuidoFileBox = GuidoFilePicker->GetContainingSizer();

  GetSizer()->Fit(this);
  GetSizer()->SetSizeHints(this);
  Centre();
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
  DEBUGLOG(_T("%d"),type);
  wxSizer * sizer = GetSizer();
  
  DEBUGLOG(_T("%d"),DTMidiPort);
  sizer->Show(PortBox, type == DTMidiPort, true);
  DEBUGLOG(_T("%d"),DTMidiFile);
  sizer->Show(MidiFileBox, (type == DTMidiFile), true);
  DEBUGLOG(_T("%d"),DTGis);
  sizer->Show(GuidoFileBox, (type == DTGis) , true);

  Layout();
  GetSizer()->SetSizeHints(this);
  Fit();
}


/*!
 * wxEVT_COMMAND_BUTTON_CLICKED event handler for wxID_REMOVE
 */

void InputDevDlg::OnRemoveClick( wxCommandEvent& event )
{
  EndModal(::wxID_REMOVE);
}

int InputDevDlg::FindType (DevType t) {
  for (unsigned int i = 0; i < DeviceChoice->GetCount(); i++) 
    if (*((TypeData *)DeviceChoice->GetClientObject(i)) == t) return i;
  return wxNOT_FOUND;
}

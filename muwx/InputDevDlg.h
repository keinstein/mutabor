/** \file
 ***********************************************************************
 * Input device selection dialog.
 *
 * $Id: InputDevDlg.h,v 1.6 2008/08/18 15:06:35 keinstein Exp $
 * \author R. Krauße <krausze@users.berlios.de>
 * \date Created: 2005/12/10 14:22:47
 * $Date: 2008/08/18 15:06:35 $
 * \version $Revision: 1.6 $
 * \license: GPL
 * Copyright:   (c) R. Krauße, TU Dresden
 *
 * $Log: InputDevDlg.h,v $
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

#ifndef _INPUTDEVDLG_H_
#define _INPUTDEVDLG_H_


#if defined(__GNUG__) && !defined(__APPLE__)
#pragma interface "InputDevDlg.cpp"
#endif

/*!
 * Includes
 */

////@begin includes
#include "Defs.h"
#include "wx/xrc/xmlres.h"
#include "wx/html/htmlwin.h"
#include "wx/statline.h"
#include "wx/filepicker.h"
#include "wxresource.h"
#include "Device.h"
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
#define SYMBOL_INPUTDEVDLG_TITLE _("Inut Device")
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
    int MidiDevice;
    unsigned int Type;

    wxSizer *Container,* TypeBox, *PortBox, *MidiFileBox, *GuidoFileBox;

    wxGenericValidator typeVal, deviceVal;

    struct TypeData:wxClientData {
      DevType nr;
      TypeData(DevType i):wxClientData()
      {
	nr=i;
      }

      bool operator == (DevType i) {
	if (this)
	  return i == nr;
	else return false;
      }

      operator DevType() { if (this) return nr; else return DTNotSet; }
    };

  int FindType (DevType t);
public:
    /// Constructors
    InputDevDlg( wxWindow* parent = NULL);

    /// wxEVT_COMMAND_CHOICE_SELECTED event handler for ID_CHOICE
    void OnChoiceSelected( wxCommandEvent& event );

    /// wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_BUTTON
    void OnRemoveClick( wxCommandEvent& event );

    void UpdateLayout(DevType type);

    int GetMidiDevice() const { return MidiDevice ; }
    void SetMidiDevice(int value) { 
      DEBUGLOG(_T("%d"),value);
      MidiDevice = value ;
      Update();
    }

  wxString GetMidiFile() const { return MidiFilePicker->GetPath() ; }
  void SetMidiFile(wxString value) { 
      DEBUGLOG(value);
      MidiFilePicker->SetPath(value);
      Update();
      DEBUGLOG(_T("done"));
    }

  wxString GetGUIDOFile() const { return GuidoFilePicker->GetPath() ; }
    void SetGUIDOFile(wxString value) { 
      DEBUGLOG(value);
      GuidoFilePicker->SetPath(value);
      Update();
    }

  DevType GetType() const {
    if (Type > DeviceChoice->GetCount()) return DTNotSet;
    TypeData * obj = (TypeData *)DeviceChoice->GetClientObject(Type);
    if (obj) return  *obj; else return DTNotSet; 
  }
  
    void SetType(DevType value) { 
      DEBUGLOG(_T("%d"),value);
      Type = FindType(value) ; 
      UpdateLayout(value);
      Update();
    }

    wxString GetPortString(int i) {
      return PortChoice->GetString (i);
    }
    void AppendPortChoice (const wxString &s) {
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
    // _INPUTDEVDLG_H_


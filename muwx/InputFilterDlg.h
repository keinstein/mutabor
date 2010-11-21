/** \file
 ********************************************************************
 * MIDI Input filter configuration dialog
 *
 * $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/muwx/Attic/InputFilterDlg.h,v 1.6 2010/11/21 13:15:47 keinstein Exp $
 * Copyright:   (c) 2005,2006,2007,2008 TU Dresden
 * \author R. Krauße
 * Tobias Schlemmer <keinstein@users.berlios.de>
 * \date 2005/10/21 18:28:56
 * $Date: 2010/11/21 13:15:47 $
 * \version $Revision: 1.6 $
 * \license GPL
 *
 * $Log: InputFilterDlg.h,v $
 * Revision 1.6  2010/11/21 13:15:47  keinstein
 * merged experimental_tobias
 *
 * Revision 1.4.2.4  2010-03-30 08:38:27  keinstein
 * added rudimentary command line support
 * changed debug system to allow selection of messages via command line
 * further enhancements to the route dialogs
 *
 * Revision 1.4.2.3  2010/02/15 12:08:20  keinstein
 * intermediate update for backup progress
 *
 * Revision 1.4.2.2  2009/11/03 15:07:07  keinstein
 * Compile on Ubuntu 9.10
 * remove several interface and implementation pragmas
 * fixed some file names for case insensitive filesystems
 *
 * Revision 1.4.2.1  2009/08/10 11:23:12  keinstein
 * merged from wrong tree
 *
 * Revision 1.5  2009/08/10 11:15:46  keinstein
 * some steps towards new route window
 *
 * Revision 1.4  2008/08/18 15:07:41  keinstein
 * Changed Input filter dialog to wxResources
 *
 * \addtogroup muwx
 * \{
 ********************************************************************/

#ifndef _INPUTFILTERDLG_H_
#define _INPUTFILTERDLG_H_

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


#if 0
/*!
 * Control identifiers
 */

////@begin control identifiers
#define ID_MYDIALOG1 10026
#define SYMBOL_INPUTFILTERDLG_STYLE wxCAPTION|wxRESIZE_BORDER|wxSYSTEM_MENU|wxCLOSE_BOX
#define SYMBOL_INPUTFILTERDLG_TITLE _("Input Filter")
#define SYMBOL_INPUTFILTERDLG_IDNAME ID_MYDIALOG1
#define SYMBOL_INPUTFILTERDLG_SIZE wxSize(400, 300)
#define SYMBOL_INPUTFILTERDLG_POSITION wxDefaultPosition
#define ID_RADIOBOX 10029
#define ID_TEXTCTRL6 10027
#define ID_TEXTCTRL7 10028
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

#endif

/*!
 * InputFilterDlg class declaration
 */

class InputFilterDlg: public InputFilterDlgBase
{
	int type;
	long from;
	long to;

	DECLARE_DYNAMIC_CLASS( InputFilterDlg )
	DECLARE_EVENT_TABLE()

public:
	/// Constructors
	InputFilterDlg( wxWindow* parent=NULL, DevType type = DTUnknown);

	/// wxEVT_COMMAND_RADIOBOX_SELECTED event handler for ID_RADIOBOX
	void OnRadioboxSelected( wxCommandEvent& event );
	void UpdateLayout(int type);

	void OnRemoveClick( wxCommandEvent& event );

	void SetDeviceType(DevType type);


	int GetType() const
	{
		DEBUGLOG(other, _T("%d"),type);
		return type ;
	}

	void SetType(int value)

	{
		DEBUGLOG(other, _T("%d"),value);
		type = value ;
		Update();
	}

	long GetFrom() const
	{
		DEBUGLOG(other, _T("%d"),from);
		return from ;
	}

	void SetFrom(long value)

	{
		DEBUGLOG(other, _T("%d"),value);
		from = value ;
		Update();
	}

	long GetTo() const
	{
		DEBUGLOG(other, _T("%d"),to);
		return to ;
	}

	void SetTo(long value)

	{
		DEBUGLOG(other, _T("%d"),value);
		to = value ;
		Update();
	}

	/// Retrieves bitmap resources

	wxBitmap GetBitmapResource( const wxString& name );

	/// Retrieves icon resources
	wxIcon GetIconResource( const wxString& name );

	/// Should we show tooltips?
	static bool ShowToolTips();
};

#endif
// _INPUTFILTERDLG_H_

///\}

/** \file 
 ********************************************************************
 * Description
 *
 * $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/muwx/Attic/BoxDlg.h,v 1.7 2011/09/05 11:30:07 keinstein Exp $
 * Copyright:   (c) 2008 TU Dresden
 * \author  Tobias Schlemmer <keinstein@users.berlios.de>
 * \date 2005/10/22 16:16:24
 * $Date: 2011/09/05 11:30:07 $
 * \version $Revision: 1.7 $
 * \license GPL
 *
 * $Log: BoxDlg.h,v $
 * Revision 1.7  2011/09/05 11:30:07  keinstein
 * Some code cleanups moving some global box arrays into class mutaborGUI::BoxData
 * Restore perspective on logic start
 *
 * Revision 1.6  2011-02-20 22:35:57  keinstein
 * updated license information; some file headers have to be revised, though
 *
 *
 * \addtogroup route
 * \{
 ********************************************************************/

#ifndef _BOXDLG_H_
#define _BOXDLG_H_

#if defined(__GNUG__) && !defined(__APPLE__)
#pragma interface "BoxDlg.cpp"
#endif

#include "wx/valgen.h"

#define ID_MYDIALOG3 10034
#define SYMBOL_BOXDLG_STYLE wxCAPTION|wxRESIZE_BORDER|wxSYSTEM_MENU|wxCLOSE_BOX
#define SYMBOL_BOXDLG_TITLE _("Mutabor-Box")
#define SYMBOL_BOXDLG_IDNAME ID_MYDIALOG3
#define SYMBOL_BOXDLG_SIZE wxSize(400, 300)
#define SYMBOL_BOXDLG_POSITION wxDefaultPosition
#define ID_RADIOBUTTON 10036
#define ID_TEXTCTRL10 10037
#define ID_RADIOBUTTON1 10038
#define ID_RADIOBUTTON2 10039
#define ID_RADIOBOX1 10035

#ifndef wxCLOSE_BOX
#define wxCLOSE_BOX 0x1000
#endif
#ifndef wxFIXED_MINSIZE
#define wxFIXED_MINSIZE 0
#endif

/*!
 * BoxDlg class declaration
 */

class BoxDlg: public wxDialog
{
	DECLARE_DYNAMIC_CLASS( BoxDlg )
	DECLARE_EVENT_TABLE()

public:
	/// Constructors
	BoxDlg( );

	BoxDlg( wxWindow* parent, 
                wxWindowID id = SYMBOL_BOXDLG_IDNAME, 
                const wxString& caption = SYMBOL_BOXDLG_TITLE, 
                const wxPoint& pos = SYMBOL_BOXDLG_POSITION, 
                const wxSize& size = SYMBOL_BOXDLG_SIZE, 
                long style = SYMBOL_BOXDLG_STYLE );

	/// Creation
	bool Create( wxWindow* parent, 
                     wxWindowID id = SYMBOL_BOXDLG_IDNAME, 
                     const wxString& caption = SYMBOL_BOXDLG_TITLE,
                     const wxPoint& pos = SYMBOL_BOXDLG_POSITION, 
                     const wxSize& size = SYMBOL_BOXDLG_SIZE, 
                     long style = SYMBOL_BOXDLG_STYLE );

	/// Creates the controls and sizers
	void CreateControls();


	/// wxEVT_COMMAND_RADIOBUTTON_SELECTED event handler for ID_RADIOBUTTON
	void UpdateEnable( wxCommandEvent& event );

	void UpdateLayout(int type);

	int GetBoxType() const
	{
		return Type ;
	}

	void SetBoxType(int value)

	{
		Type = value ;
	}

	long GetBoxNr() const
	{
		return BoxNr ;
	}

	void SetBoxNr(long value)
	{
		BoxNr = value ;
	}

	int GetMode() const
	{
		return Mode ;
	}

	void SetMode(int value)
	{
		Mode = value ;
	}

	/// Retrieves bitmap resources

	wxBitmap GetBitmapResource( const wxString& name );

	/// Retrieves icon resources
	wxIcon GetIconResource( const wxString& name );


	/// Should we show tooltips?
	static bool ShowToolTips();

	wxRadioButton* ctrlBox1;
	wxTextCtrl* ctrlBoxNr;
	wxRadioButton* ctrlBox2;
	wxRadioButton* ctrlBox3;
	wxRadioBox* ctrlMode;

	int Type;
	long BoxNr;
	int Mode;
};

#endif
// _BOXDLG_H_


///\}

/** \file 
 ********************************************************************
 * Mutabor Bitmaps. We save Bitmaps in global variables as they can be used in several contexts.
 * so their data can be shared if the underlying framework supports it.
 *
 * $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/src/wxGUI/MutBitmaps.cpp,v 1.4 2011/11/16 14:07:03 keinstein Exp $
 * Copyright:   (c) TU Dresden
 * \author 
 * Tobias Schlemmer <keinstein@users.berlios.de>
 * \date 2011/02/13
 * $Date: 2011/11/16 14:07:03 $
 * \version $Revision: 1.4 $
 * \license GPL
 *
 * $Log: MutBitmaps.cpp,v $
 * Revision 1.4  2011/11/16 14:07:03  keinstein
 * passed make distcheck on linux
 * addedd some osdep files to the archive
 *
 * Revision 1.3  2011-11-02 14:31:58  keinstein
 * fix some errors crashing Mutabor on Windows
 *
 * Revision 1.2  2011-09-27 20:13:23  keinstein
 * * Reworked route editing backend
 * * rewireing is done by RouteClass/GUIRoute now
 * * other classes forward most requests to this pair
 * * many bugfixes
 * * Version change: We are reaching beta phase now
 *
 * Revision 1.1  2011-02-16 07:01:33  keinstein
 * added files for global bitmap storage
 *
 *
 * \addtogroup src/wxGUI
 * \{
 ********************************************************************/

#include "MutBitmaps.h"
#include "MutApp.h"
#include "wx/msgdlg.h"
#include "src/kernel/routing/Route-inlines.h"
namespace mutaborGUI {


	bool MutToolBarBitmaps::initialized = false;
	wxBitmap MutToolBarBitmaps::EmptyBitmap;
	wxBitmap MutToolBarBitmaps::New;
	wxBitmap MutToolBarBitmaps::Open;
	wxBitmap MutToolBarBitmaps::Save;
	wxBitmap MutToolBarBitmaps::SaveAs;
	wxBitmap MutToolBarBitmaps::Print;
	wxBitmap MutToolBarBitmaps::LogicActivate;
	wxBitmap MutToolBarBitmaps::LogicStop;
	wxBitmap MutToolBarBitmaps::LogicPanic;
	wxBitmap MutToolBarBitmaps::Copy;
	wxBitmap MutToolBarBitmaps::Cut;
	wxBitmap MutToolBarBitmaps::Paste;
	wxBitmap MutToolBarBitmaps::Undo;
	wxBitmap MutToolBarBitmaps::Redo;
	wxBitmap MutToolBarBitmaps::RouteLoad;
	wxBitmap MutToolBarBitmaps::RouteSave;
	wxBitmap MutToolBarBitmaps::IndevsPlay;
	wxBitmap MutToolBarBitmaps::IndevsStop;
	wxBitmap MutToolBarBitmaps::IndevsPause;
	wxBitmap MutToolBarBitmaps::About;

	inline static void initMutBitmap(wxBitmap & bitmap,
					 const wxString & filename,
					 const wxBitmapType type)
	{
		if (!bitmap.IsOk())
			if(!bitmap.LoadFile(filename,type)) {
				wxMessageBox(wxString::Format(_("Error: The bitmap %s could not be found."),
					(const wxChar *)filename),
					_("Error"),
					wxOK | wxICON_ERROR);
				bitmap = MutToolBarBitmaps::EmptyBitmap;
			}
		mutASSERT(bitmap.IsOk());
	}

// Please use Tango names for new bitmap files
// http://tango.freedesktop.org/Tango_Desktop_Project

	bool MutToolBarBitmaps::Init() {
		if (initialized) return(true);
		EmptyBitmap.Create(16,16,-1);
		initMutBitmap(New,
			      wxGetApp().GetResourceName (_T ("document-new.png")),
			      wxBITMAP_TYPE_PNG);
		initMutBitmap(Open,
			      wxGetApp().GetResourceName (_T ("document-open.png")),
			      wxBITMAP_TYPE_PNG);
		initMutBitmap(Save,
			      wxGetApp().GetResourceName (_T ("document-save.png")),
			      wxBITMAP_TYPE_PNG);
		initMutBitmap(SaveAs,
			      wxGetApp().GetResourceName (_T ("document-save-as.png")),
			      wxBITMAP_TYPE_PNG);
		initMutBitmap(Print,
			      wxGetApp().GetResourceName (_T ("document-print.png")),
			      wxBITMAP_TYPE_PNG);
		initMutBitmap(LogicActivate,
			      wxGetApp().GetResourceName (_T ("ActivateMutabor.png")),
			      wxBITMAP_TYPE_PNG);
		initMutBitmap(LogicStop,
			      wxGetApp().GetResourceName (_T ("StopMutabor.png")),
			      wxBITMAP_TYPE_PNG);
		initMutBitmap(LogicPanic,
			      wxGetApp().GetResourceName (_T ("Panic.png")),
			      wxBITMAP_TYPE_PNG);
		initMutBitmap(Copy,
			      wxGetApp().GetResourceName (_T ("edit-copy.png")),
			      wxBITMAP_TYPE_PNG);
		initMutBitmap(Cut,
			      wxGetApp().GetResourceName (_T ("edit-cut.png")),
			      wxBITMAP_TYPE_PNG);
		initMutBitmap(Paste,
			      wxGetApp().GetResourceName (_T ("edit-paste.png")),
			      wxBITMAP_TYPE_PNG);
		initMutBitmap(Undo,
			      wxGetApp().GetResourceName (_T ("edit-undo.png")),
			      wxBITMAP_TYPE_PNG);
		initMutBitmap(Redo,
			      wxGetApp().GetResourceName (_T ("edit-redo.png")),
			      wxBITMAP_TYPE_PNG);
		initMutBitmap(RouteLoad,
			      wxGetApp().GetResourceName (_T ("RouteLoad.png")),
			      wxBITMAP_TYPE_PNG);
		initMutBitmap(RouteSave,
			      wxGetApp().GetResourceName (_T ("RouteSave.png")),
			      wxBITMAP_TYPE_PNG);
		initMutBitmap(IndevsPlay,
			      wxGetApp().GetResourceName (_T ("InDevPlay.png")),
			      wxBITMAP_TYPE_PNG);
		initMutBitmap(IndevsStop,
			      wxGetApp().GetResourceName (_T ("InDevStop.png")),
			      wxBITMAP_TYPE_PNG);
		initMutBitmap(IndevsPause,
			      wxGetApp().GetResourceName (_T ("InDevPause.png")),
			      wxBITMAP_TYPE_PNG);
		initMutBitmap(About,
			      wxGetApp().GetResourceName (_T ("help-browser.png")),
			      wxBITMAP_TYPE_PNG);
		initialized = true;
		return true;	
	}

	bool StatusBarBitmaps::initialized = false;
	wxBitmap StatusBarBitmaps::Play;
	wxBitmap StatusBarBitmaps::Stop;
	wxBitmap StatusBarBitmaps::Pause;
	wxBitmap StatusBarBitmaps::Active;

	bool StatusBarBitmaps::DoInit() {
		if (initialized) return(true);
		initMutBitmap(Play,
			      wxGetApp().GetResourceName (_T ("InDevPlay.png")),
			      wxBITMAP_TYPE_PNG);
		initMutBitmap(Stop,
			      wxGetApp().GetResourceName (_T ("InDevStop.png")),
			      wxBITMAP_TYPE_PNG);
		initMutBitmap(Pause,
			      wxGetApp().GetResourceName (_T ("InDevPause.png")),
			      wxBITMAP_TYPE_PNG);
		initMutBitmap(Active,
			      wxGetApp().GetResourceName (_T ("ToolbarLogicActive.png")),
			      wxBITMAP_TYPE_PNG);
		initialized = true;
		return true;	
	}

}

//\}

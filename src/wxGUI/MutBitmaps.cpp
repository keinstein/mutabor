/** \file 
 ********************************************************************
 * Mutabor Bitmaps. We save Bitmaps in global variables as they can be used in several contexts.
 * so their data can be shared if the underlying framework supports it.
 *
 * Copyright:   (c) TU Dresden
 * \author 
 * Tobias Schlemmer <keinstein@users.berlios.de>
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
 * \addtogroup GUI
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
	wxBitmap MutToolBarBitmaps::GoUp;
	wxBitmap MutToolBarBitmaps::GoDown;
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

/* Please use Tango names for new bitmap files
   http://tango.freedesktop.org/Tango_Desktop_Project
   cvs access:

   cvs -d:pserver:anoncvs@anoncvs.freedesktop.org:/cvs/tango login
   cvs -d:pserver:anoncvs@anoncvs.freedesktop.org:/cvs/tango co tango-icon-theme

   and naming tools

   cvs -d:pserver:anoncvs@anoncvs.freedesktop.org:/cvs/icon-theme login
   cvs -d:pserver:anoncvs@anoncvs.freedesktop.org:/cvs/icon-theme co icon-naming-utils

*/


	bool MutToolBarBitmaps::Init() {
		if (initialized) return(true);
		EmptyBitmap.Create(16,16,-1);
		initMutBitmap(New,
			      wxGetApp().GetResourceName (_T ("16x16/document-new.png")),
			      wxBITMAP_TYPE_PNG);
		initMutBitmap(Open,
			      wxGetApp().GetResourceName (_T ("16x16/document-open.png")),
			      wxBITMAP_TYPE_PNG);
		initMutBitmap(Save,
			      wxGetApp().GetResourceName (_T ("16x16/document-save.png")),
			      wxBITMAP_TYPE_PNG);
		initMutBitmap(SaveAs,
			      wxGetApp().GetResourceName (_T ("16x16/document-save-as.png")),
			      wxBITMAP_TYPE_PNG);
		initMutBitmap(Print,
			      wxGetApp().GetResourceName (_T ("16x16/document-print.png")),
			      wxBITMAP_TYPE_PNG);
		initMutBitmap(LogicActivate,
			      wxGetApp().GetResourceName (_T ("16x16/ActivateMutabor.png")),
			      wxBITMAP_TYPE_PNG);
		initMutBitmap(LogicStop,
			      wxGetApp().GetResourceName (_T ("16x16/StopMutabor.png")),
			      wxBITMAP_TYPE_PNG);
		initMutBitmap(LogicPanic,
			      wxGetApp().GetResourceName (_T ("16x16/Panic.png")),
			      wxBITMAP_TYPE_PNG);
		initMutBitmap(Copy,
			      wxGetApp().GetResourceName (_T ("16x16/edit-copy.png")),
			      wxBITMAP_TYPE_PNG);
		initMutBitmap(Cut,
			      wxGetApp().GetResourceName (_T ("16x16/edit-cut.png")),
			      wxBITMAP_TYPE_PNG);
		initMutBitmap(Paste,
			      wxGetApp().GetResourceName (_T ("16x16/edit-paste.png")),
			      wxBITMAP_TYPE_PNG);
		initMutBitmap(Undo,
			      wxGetApp().GetResourceName (_T ("16x16/edit-undo.png")),
			      wxBITMAP_TYPE_PNG);
		initMutBitmap(Redo,
			      wxGetApp().GetResourceName (_T ("16x16/edit-redo.png")),
			      wxBITMAP_TYPE_PNG);
		initMutBitmap(GoUp,
			      wxGetApp().GetResourceName (_T ("16x16/go-up.png")),
			      wxBITMAP_TYPE_PNG);
		initMutBitmap(GoDown,
			      wxGetApp().GetResourceName (_T ("16x16/go-down.png")),
			      wxBITMAP_TYPE_PNG);
		initMutBitmap(RouteLoad,
			      wxGetApp().GetResourceName (_T ("16x16/RouteLoad.png")),
			      wxBITMAP_TYPE_PNG);
		initMutBitmap(RouteSave,
			      wxGetApp().GetResourceName (_T ("16x16/RouteSave.png")),
			      wxBITMAP_TYPE_PNG);
		initMutBitmap(IndevsPlay,
			      wxGetApp().GetResourceName (_T ("16x16/InDevPlay.png")),
			      wxBITMAP_TYPE_PNG);
		initMutBitmap(IndevsStop,
			      wxGetApp().GetResourceName (_T ("16x16/InDevStop.png")),
			      wxBITMAP_TYPE_PNG);
		initMutBitmap(IndevsPause,
			      wxGetApp().GetResourceName (_T ("16x16/InDevPause.png")),
			      wxBITMAP_TYPE_PNG);
		initMutBitmap(About,
			      wxGetApp().GetResourceName (_T ("16x16/help-browser.png")),
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

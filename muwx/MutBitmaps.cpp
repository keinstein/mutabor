/** \file 
 ********************************************************************
 * Mutabor Bitmaps. We save Bitmaps in global variables as they can be used in several contexts.
 * so their data can be shared if the underlying framework supports it.
 *
 * $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/muwx/MutBitmaps.cpp,v 1.1 2011/02/16 07:01:33 keinstein Exp $
 * Copyright:   (c) TU Dresden
 * \author 
 * Tobias Schlemmer <keinstein@users.berlios.de>
 * \date 2011/02/13
 * $Date: 2011/02/16 07:01:33 $
 * \version $Revision: 1.1 $
 * \license GPL
 *
 * $Log: MutBitmaps.cpp,v $
 * Revision 1.1  2011/02/16 07:01:33  keinstein
 * added files for global bitmap storage
 *
 *
 * \addtogroup muwx
 * \{
 ********************************************************************/
#include "MutBitmaps.h"

bool MutToolBarBitmaps::initialized = false;
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
                if(!bitmap.LoadFile(filename,type))
                        bitmap = wxNullBitmap;
}

// Please use Tango names for new bitmap files
// http://tango.freedesktop.org/Tango_Desktop_Project

bool MutToolBarBitmaps::Init() {
	if (initialized) return(true);
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


//\}
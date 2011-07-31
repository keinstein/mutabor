/** \file 
 ********************************************************************
 * Document/View Document class for Mutabor source files.
 *
 * $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/muwx/MutDocument.cpp,v 1.3 2011/07/31 21:32:21 keinstein Exp $
 * Copyright:   (c) 2011 TU Dresden
 * \author  Tobias Schlemmer <keinstein@users.berlios.de>
 * \date 
 * $Date: 2011/07/31 21:32:21 $
 * \version $Revision: 1.3 $
 * \license GPL
 *
 * $Log: MutDocument.cpp,v $
 * Revision 1.3  2011/07/31 21:32:21  keinstein
 * Slightly improved window positioning
 * Suppress route window, when a Window is opened from the command line
 *
 * Revision 1.2  2011-07-31 20:16:04  keinstein
 * Implemented opening files from command line using Document/View framework
 *
 * Revision 1.1  2011-07-31 12:40:41  keinstein
 * Added classes and functions for Document/View support
 *
 *
 *
 ********************************************************************
 * \addtogroup templates
 * \{
 ********************************************************************/
// availlable groups: GUI, route, kernel, muwx, debug

// ---------------------------------------------------------------------------
// headers
// ---------------------------------------------------------------------------

// For compilers that support precompilation, includes "wx/wx.h".
#include "Defs.h"
#include <wx/wxprec.h>

#ifdef __BORLANDC__
    #pragma hdrstop
#endif

#include "MutDocument.h"
#include "MutView.h"
#include "MutApp.h"
#include <wx/debug.h>

#include <cstdio>
#include <iostream>

using mutaborGUI::MutDocument;
IMPLEMENT_DYNAMIC_CLASS(MutDocument, wxDocument)

BEGIN_EVENT_TABLE(MutDocument, wxDocument)
//	EVT_MENU(ID_NewViewFrame, MutDocument::CmdNewView)
//	EVT_UPDATE_UI(ID_NewViewFrame, MutDocument::OnNewViewUpdateUI)
//	EVT_MENU(ID_UpdateAllViews, MutDocument::CmdUpdateAllViews)
END_EVENT_TABLE()

namespace mutaborGUI {

MutDocument::MutDocument()
{


}

MutDocument::~MutDocument()
{

}

#if wxUSE_STD_IOSTREAM

bool MutDocument::DoSaveDocument(const wxString& filename)
{
    MutView *view = (MutView *)GetFirstView();

    if (!view->GetTextsw()->SaveFile(filename))
        return false;

    return true;
}

bool MutDocument::DoOpenDocument(const wxString& filename)
{
    MutView *view = (MutView *)GetFirstView();
    if (!view->GetTextsw()->LoadFile(filename))
        return false;
    if (view->GetFrame())
	    view->GetFrame()->SetTitle(filename);
    return true;
}

wxSTD ostream& MutDocument::SaveObject(wxSTD ostream& stream)
{
	printf("cmydoc::saveobject\n");
	stream << 5;
	stream << 'j';
	return stream;
}

wxSTD istream& MutDocument::LoadObject(wxSTD istream& stream)
{
	DEBUGLOG(docview,_T(""));
	bool bOK(false);
	int nA(0);
	char ch(0);

	stream >> nA;
	stream >> ch;

	if(stream.good())
	{
		DEBUGLOG(docview,_T("num is %d and char is %c"), nA, ch);
		bOK = true;
	}

	if(bOK == false)
	{
		DEBUGLOG(docview,_T("load error"));
		// tell the framework to abort the load procedure
		stream.clear(std::ios_base::badbit);
	}
	return stream;
}

#else

wxOutputStream& MutDocument::SaveObject(wxOutputStream& stream)
{
	printf("mydoc::saveobject()\n");
	return stream;
}

wxInputStream& MutDocument::LoadObject(wxInputStream& stream)
{
	printf("mydoc::loadobject()\n");
	return stream;
}

#endif

bool MutDocument::OnCreate(const wxString& path, long flags)
{

	// you should call the one in the superclass
	return wxDocument::OnCreate(path, flags);
}

void MutDocument::Modify(bool modify)
{
	// note this function calls wxView::OnChangeFilename() which, in some circumstances, is preferable
	// to using our own SetMainTitle().
	wxDocument::Modify(modify);
	// we may want to alter the caption of the mainframe, adding a * to the end
//	GetMainFrame()->SetMainTitle(true);
}


void MutDocument::CmdNewView(wxCommandEvent& event)
{
   printf("MutDocument::CmdNewView\n");
   //wxMessageBox(wxT("doc newview 1"), _T("dialog"), wxOK | wxICON_INFORMATION, NULL);

   //  we manually create a view, and register it with the document.
   // the view needs to create a window for itself, which 
   //  it can do in OnCreate
   MutView* pview = new MutView();
   bool bKeep = pview->OnCreate(NULL, 0);
   if(bKeep)
   {
        AddView(pview);
   		// we could set the title of the view's frame
   		// AddView() does not set the document in the view, so we do that now
   		pview->SetDocument(this);
   }
   else
   {
	// kill the view and its window. Hopefully nothing else.
	pview->Close(TRUE);
	// I don't think the Close function works
	wxFAIL;
   }	

   // wxMessageBox(wxT("doc newview 2"), _T("dialog"), wxOK | wxICON_INFORMATION, NULL);


}

void MutDocument::CmdUpdateAllViews(wxCommandEvent& event)
{
	UpdateAllViews();
}

void MutDocument::OnNewViewUpdateUI(wxUpdateUIEvent& event)
{
	event.Enable(true);
	// printf("MutDocument::OnNewViewUpdateUI\n");
}
	
}


///\}

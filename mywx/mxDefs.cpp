/** \file 
 ********************************************************************
 * Description
 *
 * $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/mywx/mxDefs.cpp,v 1.12 2011/09/27 20:13:26 keinstein Exp $
 * Copyright:   (c) 2008 TU Dresden
 * \author  R. Krauße, Tobias Schlemmer <keinstein@users.berlios.de>
 * \date 
 * $Date: 2011/09/27 20:13:26 $
 * \version $Revision: 1.12 $
 * \license GPL
 *
 * $Log: mxDefs.cpp,v $
 * Revision 1.12  2011/09/27 20:13:26  keinstein
 * * Reworked route editing backend
 * * rewireing is done by RouteClass/GUIRoute now
 * * other classes forward most requests to this pair
 * * many bugfixes
 * * Version change: We are reaching beta phase now
 *
 * Revision 1.11  2011-02-20 22:35:59  keinstein
 * updated license information; some file headers have to be revised, though
 *
 * Revision 1.2  2010-11-21 13:15:51  keinstein
 * merged experimental_tobias
 *
 * Revision 1.1.2.1  2010-01-11 10:12:59  keinstein
 * added some .cvsignore files
 *
 *
 ********************************************************************
 * \addtogroup templates
 * \{
 ********************************************************************/
#include "Defs.h"
#include "mhDefs.h"

#include "wx/filedlg.h"
#include "wx/log.h"
#include "wx/sizer.h"

#if defined(WX) && (wxUSE_UNICODE || wxUSE_WCHAR_T)
wxCSConv muCSConv(wxT("ISO-8859-1"));

#endif

wxString FileNameDialog(wxWindow * parent,
                        int Command,
                        wxString Filename)
{
#ifdef DEBUG
	std::cout << "FileNameDialog: " << Command << std::endl;
#endif

	static const wxString logic_sources(_("Mutabor tuning file (*.mut)|*.mut|Old Mutabor tuning file (*.mus)|*.mus|All files (*.*)|*.*"));

	static const wxString route_sources(_("Mutabor routing file (*.mur)|*.mur|All files (*.*)|*.*"));

	wxString title, filetypes,
	dir(wxEmptyString), name(wxEmptyString) , ext(wxEmptyString);

	int flags;

	switch (Command) {

	case CM_FILEOPEN:
		title = _("Which Mutabor file shall be loaded?");

		filetypes = logic_sources;

		flags = wxFD_CHANGE_DIR | wxFD_FILE_MUST_EXIST | wxFD_OPEN;

		break;

	case CM_EXECUTE:
		title = _("Which Mutabor file shall be executed?");

		filetypes = logic_sources;

		flags = wxFD_CHANGE_DIR | wxFD_FILE_MUST_EXIST | wxFD_OPEN;

		break;

	case CM_FILESAVEAS:
		title = _("Enter the new Mutabor file name, please!");

		filetypes = logic_sources;

		flags = wxFD_CHANGE_DIR | wxFD_OVERWRITE_PROMPT | wxFD_SAVE;

		break;

	case CM_ROUTELOAD:
		title = _("Which Mutabor route file shall be loaded?");

		filetypes = route_sources;

		flags = wxFD_CHANGE_DIR | wxFD_FILE_MUST_EXIST | wxFD_OPEN;

		break;

	case CM_ROUTESAVE:

	case CM_ROUTESAVEAS:
		title = _("Enter the new Mutabor route file name, please!");

		filetypes = route_sources;

		flags = wxFD_CHANGE_DIR | wxFD_OVERWRITE_PROMPT | wxFD_SAVE;

		break;

	default:
		wxLogError(_("Unexpected Command Id in FileNameDialog: %d"),Command);

		return wxString(_T(""));
	}

	if (!Filename.IsEmpty()) {
		wxFileName splitter(Filename);
		ext = splitter.GetExt();
		name = splitter.GetFullName();
		dir = splitter.GetPath();
	}

	wxFileDialog  * FileSelector = new wxFileDialog(parent, title, dir, name, filetypes,

#ifdef __WXCOCOA__
	                               0
#else
	                               flags
#endif
	                               //	,parent
	                                               );

	int cmd = FileSelector->ShowModal();

	wxString retval;
	retval = (cmd == wxID_OK) ? (FileSelector->GetPath()) : wxString(wxEmptyString);

	FileSelector->Destroy();

	return retval;
}

void PRINTWINDOW (wxWindow * window, const wxString & offset = _T ("")) 
{
        if (!window) DEBUGLOG2 (other,_T("NULL window."));
        
}

#ifdef DEBUG
void PRINTSIZER (wxSizer * sizer, const wxString & offset) 
{
        if (!sizer) DEBUGLOG2 (other,_T("NULL Pointer."));
        DEBUGLOGTYPE (other, *sizer, _T ("%sSizer: %p to Window %p"),
                      offset.c_str (),
                      sizer,sizer->GetContainingWindow ());
        wxSizerItemList &childs = sizer -> GetChildren ();
        for (wxSizerItemList::iterator i = childs.begin ();
             i!=childs.end (); i++) {
                wxSizerItem * item = *i;
                wxRect rect = item->GetRect ();
                if (item->IsSizer ()) {
                        DEBUGLOGTYPE (other, *sizer,
                                      _T ("%s%s sizer from (%d,%d) to (%d,%d):"),
                                      offset.c_str (),
                                      (item -> IsShown ()?
                                       _T ("shown"):_T ("hidden")),
                                      rect.x,rect.y, rect.x+rect.width,
                                      rect.y+rect.height);
                        PRINTSIZER (item->GetSizer (), offset + _T (" | "));
                } else if (item -> IsWindow ()) {
                        wxWindow * window = item->GetWindow ();
                        DEBUGLOGTYPE (other, *window, 
                                      _T ("%sWindow: %p with parent window %p (%s) from (%d,%d) to (%d,%d)"),
                                      offset.c_str (),
                                      window,window->GetParent (),
                                      (item -> IsShown ()?
                                       _T ("shown"):_T ("hidden")),
                                      rect.x,rect.y, rect.x+rect.width,
                                      rect.y+rect.height);
			if (window -> GetSizer()) 
				PRINTSIZER(window -> GetSizer(), offset + _T(" [] "));
                } else if (item -> IsSpacer ()) {
                        wxSize size = item->GetSpacer ();
                        DEBUGLOGTYPE (other, size,
                                      _T ("%sSpacer: %d x %d (%s) from (%d,%d) to (%d,%d)"),
                                      offset.c_str (),
                                      size.x,size.y,
                                      (item -> IsShown ()?
                                       _T ("shown"):_T ("hidden")),
                                      rect.x,rect.y, rect.x+rect.width,
                                      rect.y+rect.height);
                }
        }
}
#endif


///\}

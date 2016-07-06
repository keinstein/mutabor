/** \file 
 ********************************************************************
 * Uncategorized definitions.
 *
 * Copyright:   (c) 2008-2011 TU Dresden
 *              changes after 2011/11 (c) by the authors
 * \author  R. Krauße, Tobias Schlemmer <keinstein@users.sourceforge.net>
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
 *
 *
 ********************************************************************
 * \addtogroup GUI
 * \{
 ********************************************************************/
#include "src/kernel/Defs.h"
#include "src/wxGUI/generic/mhDefs.h"

#include "wx/filedlg.h"
#include "wx/log.h"
#include "wx/sizer.h"

#if defined(WX) && (wxUSE_UNICODE || wxUSE_WCHAR_T)
wxCSConv muCSConv(wxT("ISO-8859-1"));

#endif

MutFileDataType FileNameDialog(wxWindow * parent,
                        int Command,
                        wxString Filename)
{
	DEBUGLOG2(gui,("Command: %d"),Command);

	static const wxString logic_sources(_("Mutabor tuning file (*.mut)|*.mut|Old Mutabor tuning file (*.mus)|*.mus|All files (*.*)|*.*"));

	static const wxString route_sources(_("Mutabor routing file (*.murx)|*.murx|Old Mutabor routing file (*.mur)|*.mur|All files (*.*)|*.*"));

	wxString title, filetypes,
	dir(wxEmptyString), name(wxEmptyString) , ext(wxEmptyString);

	int flags;

	MutFileDataType retval;
	switch (Command) {

	case CM_FILEOPEN:
		title = _("Which Mutabor file shall be loaded?");
		filetypes = logic_sources;
		flags = wxFD_CHANGE_DIR | wxFD_FILE_MUST_EXIST | wxFD_OPEN;
		break;

	case mutaborGUI::CM_EXECUTE:
		title = _("Which Mutabor file shall be executed?");
		filetypes = logic_sources;
		flags = wxFD_CHANGE_DIR | wxFD_FILE_MUST_EXIST | wxFD_OPEN;
		break;

	case CM_FILESAVEAS:
		title = _("Enter the new Mutabor file name, please!");
		filetypes = logic_sources;
		flags = wxFD_CHANGE_DIR | wxFD_OVERWRITE_PROMPT | wxFD_SAVE;
		break;

	case mutaborGUI::CM_ROUTELOAD:
		title = _("Which Mutabor route file shall be loaded?");
		filetypes = route_sources;
		flags = wxFD_CHANGE_DIR | wxFD_FILE_MUST_EXIST | wxFD_OPEN;
		break;

	case mutaborGUI::CM_ROUTESAVE:
	case mutaborGUI::CM_ROUTESAVEAS:
		title = _("Enter the new Mutabor route file name, please!");
		filetypes = route_sources;
		flags = wxFD_CHANGE_DIR | wxFD_OVERWRITE_PROMPT | wxFD_SAVE;
		break;

	default:
		wxLogError(_("Unexpected Command Id in FileNameDialog: %d"),Command);
		retval.type = MutFileDataType::Unknown;
		return retval;
	}

	if (!Filename.IsEmpty()) {
		wxFileName splitter(Filename);
		ext = splitter.GetExt();
		name = splitter.GetFullName();
		dir = splitter.GetPath();
	}

	wxFileDialog  * FileSelector = new wxFileDialog(parent, title, dir, name, filetypes, flags);

	int cmd = FileSelector->ShowModal();

	if (cmd != wxID_OK) {
		retval.type  = MutFileDataType::Canceled;
		return retval;
	}
	retval.name = FileSelector->GetPath();
	switch (Command) {
	case CM_FILEOPEN:
	case mutaborGUI::CM_EXECUTE:
	case CM_FILESAVEAS:
			retval.type=MutFileDataType::LogicSource;
		break;
	case mutaborGUI::CM_ROUTELOAD:
	case mutaborGUI::CM_ROUTESAVE:
	case mutaborGUI::CM_ROUTESAVEAS:
		switch (FileSelector->GetFilterIndex()) {
		case 0: 
			retval.type = MutFileDataType::XMLRoute1;
			break;
		case 1: 
			retval.type = MutFileDataType::UTF8TextRoute;
			break;
		default:
			wxString ext = retval.name.GetExt().Upper();
			if (ext == _T("MUR")) {
				retval.type = MutFileDataType::UTF8TextRoute;
			} else if (ext == _T("MURX")) {
				retval.type = MutFileDataType::XMLRoute1;
			} else retval.type = MutFileDataType::Unknown;
		}
		break;

	default:
		wxLogError(_("Unexpected Command Id in FileNameDialog: %d"),Command);
		retval.type = MutFileDataType::Unknown;
		return retval;
	}

	FileSelector->Destroy();

	return retval;
}

void PRINTWINDOW (wxWindow * window, const wxString & offset = _T ("")) 
{
		mutUnused(offset);
        if (!window) DEBUGLOG2 (other, ("NULL window."));
        
}

#ifdef DEBUG
void PRINTSIZER (wxSizer * sizer, const wxString & offset) 
{
        if (!sizer) DEBUGLOG2 (other,("NULL Pointer."));
        DEBUGLOGTYPE (other, *sizer, ("%sSizer: %p to Window %p"),
                      offset.c_str (),
                      (void*)sizer,(void*)sizer->GetContainingWindow ());
        wxSizerItemList &childs = sizer -> GetChildren ();
        for (wxSizerItemList::iterator i = childs.begin ();
             i!=childs.end (); ++i) {
                wxSizerItem * item = *i;
                wxRect rect = item->GetRect ();
                if (item->IsSizer ()) {
                        DEBUGLOGTYPE (other, *sizer,
                                      ("%s%s sizer from (%d,%d) to (%d,%d):"),
                                      offset.c_str (),
                                      (item -> IsShown ()?
				       ("shown"): ("hidden")),
                                      rect.x,rect.y, rect.x+rect.width,
                                      rect.y+rect.height);
                        PRINTSIZER (item->GetSizer (), offset + _T (" | "));
                } else if (item -> IsWindow ()) {
                        wxWindow * window = item->GetWindow ();
                        DEBUGLOGTYPE (other, *window, 
                                      ("%sWindow: %p with parent window %p (%s) from (%d,%d) to (%d,%d)"),
                                      offset.c_str (),
                                      (void*)window,(void*)window->GetParent (),
                                      (item -> IsShown ()?
				       ("shown"): ("hidden")),
                                      rect.x,rect.y, rect.x+rect.width,
                                      rect.y+rect.height);
			if (window -> GetSizer()) 
				PRINTSIZER(window -> GetSizer(), offset + _T(" [] "));
                } else if (item -> IsSpacer ()) {
                        wxSize size = item->GetSpacer ();
                        DEBUGLOGTYPE (other, size,
                                      ("%sSpacer: %d x %d (%s) from (%d,%d) to (%d,%d)"),
                                      offset.c_str (),
                                      size.x,size.y,
                                      (item -> IsShown ()?
				       ("shown"): ("hidden")),
                                      rect.x,rect.y, rect.x+rect.width,
                                      rect.y+rect.height);
                }
        }
}
#endif


///\}

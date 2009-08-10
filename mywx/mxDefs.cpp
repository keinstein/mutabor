#include "Defs.h"
#include "mhDefs.h"

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
        if (!window) DEBUGLOG2 (_T("NULL window."));
        
}

void PRINTSIZER (wxSizer * sizer, const wxString & offset) 
{
        if (!sizer) DEBUGLOG2 (_T("NULL Pointer."));
        DEBUGLOGTYPE (*sizer, _T ("%sSizer: %p to Window %p"),
                      offset.c_str (),
                      sizer,sizer->GetContainingWindow ());
        wxSizerItemList &childs = sizer -> GetChildren ();
        for (wxSizerItemList::iterator i = childs.begin ();
             i!=childs.end (); i++) {
                wxSizerItem * item = *i;
                wxRect rect = item->GetRect ();
                if (item->IsSizer ()) {
                        DEBUGLOGTYPE (*sizer,
                                      _T ("%s%s sizer from (%d,%d) to (%d,%d):"),
                                      offset.c_str (),
                                      (item -> IsShown ()?
                                       _T ("shown"):_T ("hidden")),
                                      rect.x,rect.y, rect.x+rect.width,
                                      rect.y+rect.height);
                        PRINTSIZER (item->GetSizer (), offset + _T (" | "));
                } else if (item -> IsWindow ()) {
                        wxWindow * window = item->GetWindow ();
                        DEBUGLOGTYPE (*window, 
                                      _T ("%sWindow: %p with parent window %p (%s) from (%d,%d) to (%d,%d)"),
                                      offset.c_str (),
                                      window,window->GetParent (),
                                      (item -> IsShown ()?
                                       _T ("shown"):_T ("hidden")),
                                      rect.x,rect.y, rect.x+rect.width,
                                      rect.y+rect.height);
                } else if (item -> IsSpacer ()) {
                        wxSize size = item->GetSpacer ();
                        DEBUGLOGTYPE (size,
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

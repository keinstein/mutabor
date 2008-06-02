#include "Defs.h"
#include "mhDefs.h"

#if defined(WX) && (wxUSE_UNICODE)
wxCSConv muCSConv(wxT("ISO-8859-1"));

#endif

wxString FileNameDialog(wxWindow * parent, 
			int Command,
			wxString Filename)
{
  static const wxString logic_sources(_("Mutabor tuning file (*.mut)|*.mut|Old Mutabor tuning file (*.mus)|*.mus|All files (*.*)|*.*"));

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
  default:
    wxLogError(_("Unexpected Command Id in FileNameDialog: %d"),Command);
  }

  if (!Filename.IsEmpty()) {
    wxFileName splitter(Filename);
    ext = splitter.GetExt();
    name = splitter.GetFullName();
    dir = splitter.GetPath();
  }

  wxFileDialog  FileSelector(parent, title, dir, name, filetypes,
#ifdef __WXCOCOA__
		   0
#else
		   flags
#endif
			     //	,parent
		   );

  int cmd = FileSelector.ShowModal();
  
  if (cmd == wxID_OK) {
    return FileSelector.GetPath();
  } else {
    return wxEmptyString;
  }
}

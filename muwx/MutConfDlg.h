/** \file
 ***********************************************************************
 * Mutabor Configuration Dialog.
 *
 * $Id: MutConfDlg.h,v 1.2 2008/06/02 16:12:15 keinstein Exp $
 * \author Tobias Schlemmer <keinstein@users.berlios.de>
 * \date $Date: 2008/06/02 16:12:15 $
 * \version $Revision: 1.2 $
 *
 * $Log: MutConfDlg.h,v $
 * Revision 1.2  2008/06/02 16:12:15  keinstein
 * Implement Help
 *
 * Revision 1.1  2008/01/25 10:04:30  keinstein
 * New file.
 *
 *
 */

#ifndef MUT_CONF_DLG_H
#define MUT_CONF_DLG_H

#include "wx/statline.h"
#include "wx/filepicker.h"
#include "wx/html/htmlwin.h"
#include "wx/valgen.h"
#include "wxresource.h"
#include "MutFrame.h"

class MutConfigDialog : public ConfigDlg {
 public:
 MutConfigDialog(wxWindow * parent = NULL) : ConfigDlg(parent) {

    ToneSystem->SetValidator(wxGenericValidator((int *) &asTS));
    SaveEditor->SetValidator(wxGenericValidator(&::SaveEditor));
    ColorBars->SetValidator(wxGenericValidator(&UseColorBars));

#if 0
#ifndef __WXMSW__
    wxSizer * buttonSizer = this->wxID_OK->GetParent()->GetSizer();
      buttonSizer->Add(new wxContextHelpButton(this), 0, wxALIGN_CENTER|wxALL, 5);
#endif
#endif    

  }

  ~MutConfigDialog() {}

  void CmHelp(wxCommandEvent& event) {
    std::cerr << "MutConfigDialog::CmHelp" << std::endl;
    HelpController->Display(_("The setup dialog"));
    event.Skip();
  }
 private:
  DECLARE_EVENT_TABLE()
};

#endif /* MUT_CONF_DLG_H */

/** \file 
 ********************************************************************
 * Description
 *
 * $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/muwx/MutConfDlg.h,v 1.5 2011/02/20 22:35:57 keinstein Exp $
 * Copyright:   (c) 2008 TU Dresden
 * \author Tobias Schlemmer <keinstein@users.berlios.de>
 * \date $Date: 2011/02/20 22:35:57 $
 * \version $Revision: 1.5 $
 *
 * $Log: MutConfDlg.h,v $
 * Revision 1.5  2011/02/20 22:35:57  keinstein
 * updated license information; some file headers have to be revised, though
 *
 * Revision 1.4  2010-11-21 13:15:47  keinstein
 * merged experimental_tobias
 *
 * Revision 1.3.2.1  2010-02-15 12:08:21  keinstein
 * intermediate update for backup progress
 *
 * Revision 1.3  2008/10/09 15:14:02  keinstein
 * make compile on mingw
 *
 * Revision 1.2  2008/06/02 16:12:15  keinstein
 * Implement Help
 *
 * Revision 1.1  2008/01/25 10:04:30  keinstein
 * New file.
 *
 * \addtogroup muwx
 * \{
 ********************************************************************/

#ifndef MUT_CONF_DLG_H
#define MUT_CONF_DLG_H

#include "wx/statline.h"
#include "wx/filepicker.h"
#include "wx/html/htmlwin.h"
#include "wx/html/helpctrl.h"
#include "wx/valgen.h"
#include "resourceload.h"
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

///\}

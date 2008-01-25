/** \file
 ***********************************************************************
 * Mutabor Configuration Dialog.
 *
 * $Id: MutConfDlg.h,v 1.1 2008/01/25 10:04:30 keinstein Exp $
 * \author Tobias Schlemmer <keinstein@users.berlios.de>
 * \date $Date: 2008/01/25 10:04:30 $
 * \version $Revision: 1.1 $
 *
 * $Log: MutConfDlg.h,v $
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
  }
  ~MutConfigDialog() {}
};

#endif /* MUT_CONF_DLG_H */

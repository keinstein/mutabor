/** \file 
 ********************************************************************
 * Wrapper around wxcresource.h since wxrc doesn't prevent multiple 
 * inclusion
 *
 * $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/muwx/resourceload.h,v 1.4 2011/02/20 22:35:58 keinstein Exp $
 * Copyright:   (c) 2008 TU Dresden
 * \author  Tobias Schlemmer <keinstein@users.berlios.de>
 * \date 2008/08/05
 * $Date: 2011/02/20 22:35:58 $
 * \version $Revision: 1.4 $
 * \license GPL
 *
 * $Log: resourceload.h,v $
 * Revision 1.4  2011/02/20 22:35:58  keinstein
 * updated license information; some file headers have to be revised, though
 *
 * Revision 1.3  2011-01-28 20:59:45  keinstein
 * satisfy distcheck on Ubuntu 10.10
 *
 * Revision 1.2  2010-11-21 13:15:48  keinstein
 * merged experimental_tobias
 *
 * Revision 1.1.2.2  2010-02-15 12:08:21  keinstein
 * intermediate update for backup progress
 *
 * Revision 1.1.2.1  2010/01/14 10:13:51  keinstein
 * muwx/resourceload.h: new file to preload other header files for wxresource.h
 *
 * Revision 1.1.2.1  2010/01/11 10:12:59  keinstein
 * added some .cvsignore files
 *
 * \addtogroup muwx
 * \{
 ********************************************************************/

#ifndef MUWX_RESOURCELOAD_H
#define MUWX_RESOURCELOAD_H

// ---------------------------------------------------------------------------
// headers
// ---------------------------------------------------------------------------

// For compilers that support precompilation, includes "wx/wx.h".
#include "Defs.h"
#include "wx/wxprec.h"

#include "wx/spinctrl.h"
#include "wx/choicebk.h"

#include "../xrc/wxresource.h"


#endif
///\}

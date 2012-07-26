/** \file                   -*- C++ -*-
 ********************************************************************
 * Wrapper around wxcresource.h since wxrc doesn't prevent multiple 
 * inclusion
 *
 * $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/src/wxGUI/resourceload.h,v 1.6 2011/11/02 14:31:59 keinstein Exp $
 * Copyright:   (c) 2008 TU Dresden
 * \author  Tobias Schlemmer <keinstein@users.berlios.de>
 * \date 2008/08/05
 * $Date: 2011/11/02 14:31:59 $
 * \version $Revision: 1.6 $
 * \license GPL
 *
 * $Log: resourceload.h,v $
 * Revision 1.6  2011/11/02 14:31:59  keinstein
 * fix some errors crashing Mutabor on Windows
 *
 * Revision 1.5  2011-09-27 20:13:24  keinstein
 * * Reworked route editing backend
 * * rewireing is done by RouteClass/GUIRoute now
 * * other classes forward most requests to this pair
 * * many bugfixes
 * * Version change: We are reaching beta phase now
 *
 * Revision 1.4  2011-02-20 22:35:58  keinstein
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
 * src/wxGUI/resourceload.h: new file to preload other header files for wxresource.h
 *
 * Revision 1.1.2.1  2010/01/11 10:12:59  keinstein
 * added some .cvsignore files
 *
 * \addtogroup src/wxGUI
 * \{
 ********************************************************************/

#if (!defined(MUWX_RESOURCELOUAD_H) && !defined(PRECOMPILE)) \
	|| (!defined(MUWX_RESOURCELOUAD_H_PRECOMPILED))
#ifndef PRECOMPILE
#define MUWX_RESOURCELOUAD_H
#endif

// ---------------------------------------------------------------------------
// headers
// ---------------------------------------------------------------------------

#include "src/kernel/Defs.h"

#ifndef MUWX_RESOURCELOUAD_H_PRECOMPILED
#define MUWX_RESOURCELOUAD_H_PRECOMPILED

// ---------------------------------------------------------------------------
// headers
// ---------------------------------------------------------------------------

#include "wx/button.h"
#include "wx/checkbox.h"
#include "wx/choicebk.h"
#include "wx/dialog.h"
#include "wx/filepicker.h"
#include "wx/html/htmlwin.h"
#include "wx/radiobox.h"
#include "wx/radiobut.h"
#include "wx/spinctrl.h"
#include "wx/stattext.h"
#include "wx/textctrl.h"
#include "wx/window.h"
#include "wx/xrc/xmlres.h"


#include "src/xrc/wxresource.h"

#endif // precompiled
#endif
///\}

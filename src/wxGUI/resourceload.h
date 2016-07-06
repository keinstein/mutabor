/** \file                   -*- C++ -*-
 ********************************************************************
 * Wrapper around wxcresource.h since wxrc doesn't prevent multiple 
 * inclusion
 *
 * Copyright:   (c) 2008 TU Dresden
 * \author  Tobias Schlemmer <keinstein@users.sourceforge.net>
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
 * \addtogroup GUI
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
#include "wx/statline.h"
#include "wx/window.h"
#include "wx/xrc/xmlres.h"


#include "src/xrc/wxresource.h"

#endif // precompiled
#endif
///\}

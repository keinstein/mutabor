// -*- C++ -*-
/** \file
********************************************************************
* New box shape for route window.
*
* \author Rüdiger Krauße,
* Tobias Schlemmer <keinstein@users.sourceforge.net>
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
********************************************************************
*\addtogroup GUIroute
*\{
********************************************************************/

/* we guard a little bit complicated to ensure the references are set right
 */

#if (!defined(MUWX_ROUTING_NEWBOXSHAPE_H) && !defined(PRECOMPILE))	\
	|| (!defined(MUWX_ROUTING_NEWBOXSHAPE_H_PRECOMPILED))
#ifndef PRECOMPILE
#define MUWX_ROUTING_NEWBOXSHAPE_H
#endif

// ---------------------------------------------------------------------------
// headers
// ---------------------------------------------------------------------------

#include "src/kernel/Defs.h"
#include "src/wxGUI/MutIcon.h"
#include "src/wxGUI/Routing/BoxShape.h"
//#include "Device.h"


#ifndef MUWX_ROUTING_NEWBOXSHAPE_H_PRECOMPILED
#define MUWX_ROUTING_NEWBOXSHAPE_H_PRECOMPILED

// system headers which do seldom change

//#include <map>

//#include "wx/defs.h"
//#include "wx/icon.h"
//#include "wx/stattext.h"

MUTABOR_NAMESPACE(mutaborGUI)



class NewMutBoxShape:public MutBoxShape
{
	virtual MutIcon& GetMutIcon();

public:
	NewMutBoxShape(wxWindow * parent, wxWindowID wid):MutBoxShape()	{
		Create (parent, wid);
	}

	bool Create (wxWindow * parent, wxWindowID wid)	{ 
		if (!MutBoxShape::Create(parent, 
					 wid)) return false;
		m_icon->SetLabel(_("New Box"));
		m_icon->SetBackgroundStyle(wxBG_STYLE_SYSTEM);
		return true;
	}

	virtual ~NewMutBoxShape() {}
	
	virtual bool CanHandleType (int  type) { mutUnused(type); return false; }
	virtual bool replaceSelfBy (MutBoxShape  * newshape);
	virtual void InitializeDialog(BoxDlg * dlg) const;
	virtual bool readDialog (BoxDlg * box) 
	{ 
		mutUnused(box);
		UNREACHABLEC;
		return false; 
	}	
private:
	DECLARE_CLASS(NewMutBoxShape)
	DECLARE_NO_COPY_CLASS(NewMutBoxShape)
};

MUTABOR_NAMESPACE_END(mutaborGUI)

#endif				/* NEWBOXSHAPE_H_PRECMPILED */
#endif				/* NEWBOXSHAPE_H */
/**
 * \}
 */

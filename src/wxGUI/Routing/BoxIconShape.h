// -*- C++ -*-

/** \file
********************************************************************
* Box icon shape for route window.
*
* \author Rüdiger Krauße <krausze@mail.berlios.de>,
* Tobias Schlemmer <keinstein@users.berlios.de>
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
*\addtogroup route
*\{
********************************************************************/

#if (!defined(MUWX_ROUTING_BOXICONSHAPE_H) && !defined(PRECOMPILE))	\
	|| (!defined(MUWX_ROUTING_BOXICONSHAPE_H_PRECOMPILED))
#ifndef PRECOMPILE
#define MUWX_ROUTING_BOXICONSHAPE_H
#endif

// ---------------------------------------------------------------------------
// headers
// ---------------------------------------------------------------------------

#include "src/kernel/Defs.h"
#include "src/wxGUI/IconShape.h"
#include "src/wxGUI/Routing/RouteIcons.h"

#ifndef MUWX_ROUTING_BOXICONSHAPE_H_PRECOMPILED
#define MUWX_ROUTING_BOXICONSHAPE_H_PRECOMPILED

// system headers which do seldom change

//#include <map>

//#include "wx/defs.h"
//#include "wx/icon.h"
//#include "wx/stattext.h"

//#include "Device.h"

namespace mutaborGUI {
	class MutBoxIconShape:public MutIconShapeClass<MutPanel>
	{
	public:
		MutBoxIconShape():MutIconShapeClass<MutPanel>() {}
	
		MutBoxIconShape(wxWindow * parent, wxWindowID id = wxID_ANY):
			MutIconShapeClass<MutPanel>() 
			{
				Create (parent, id);
			}

		virtual ~MutBoxIconShape() {}
	
		bool Create (wxWindow * parent = NULL, wxWindowID id = wxID_ANY)
			{
				return MutIconShapeClass<MutPanel>::Create(parent, id);
			}

		virtual bool SetForegroundColour (const wxColour & colour) 
			{
				if (staticText)
					staticText->SetForegroundColour(colour);
				return MutIconShapeClass<MutPanel>::SetForegroundColour(colour);
			}

		/*  bool Create( wxWindow *parent,
		    wxWindowID id,
		    const wxString &label,
		    const wxPoint &pos = wxDefaultPosition,
		    const wxSize &size = wxDefaultSize,
		    long style = 0,
		    const wxString &name = wxStaticBoxNameStr );
		*/

		void GetBordersForSizer(int &borderTop, int &borderOther) const;
 
		virtual void OnDraw (wxDC & dc);
		virtual bool Layout();

		MutIcon & GetMutIcon () {
			mutASSERT(BoxBitmap.IsOk());
			return BoxBitmap;
		}



		// returning true from here ensures that we act as a container window for
		// our children
		//virtual bool IsStaticBox() const { return true; }
	
	private: 
	};

}
#endif				/* BOXICONSHAPE_H_PRECOMPILED */
#endif				/* BOXICONSHAPE_H */
/*
 * \}
 */

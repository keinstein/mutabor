// -*- C++ -*-
/** \file
 ********************************************************************
 * Guido/Salieri file input device class.
 *
 * \author Rüdiger Krauße <krausze@mail.berlios.de>,
 * Tobias Schlemmer <keinstein@users.berlios.de>
 * \license GPL
 *
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

#if (!defined(MUWX_ROUTING_INPUTGUIDOFILEDEVICESHAPE_H) && !defined(PRECOMPILE)) \
	|| (!defined(MUWX_ROUTING_INPUTGUIDOFILEDEVICESHAPE_H_PRECOMPILED))
#ifndef PRECOMPILE
#define MUWX_ROUTING_INPUTGUIDOFILEDEVICESHAPE_H
#endif

// ---------------------------------------------------------------------------
// headers
// ---------------------------------------------------------------------------

#include "src/kernel/Defs.h"
#include "src/wxGUI/MutIcon.h"
#include "src/wxGUI/Routing/RouteIcons.h"
#include "src/wxGUI/Routing/InputMidiDeviceShape.h"
//#include "Device.h"

#ifndef MUWX_ROUTING_INPUTGUIDOFILEDEVICESHAPE_H_PRECOMPILED
#define MUWX_ROUTING_INPUTGUIDOFILEDEVICESHAPE_H_PRECOMPILED

// system headers which do seldom change

//#include <map>

//#include "wx/defs.h"
//#include "wx/icon.h"
//#include "wx/stattext.h"


namespace mutaborGUI {

	class MutInputGuidoFileDeviceShape:public MutInputDeviceShape
	{
		friend class GUIGisFactory;
	protected:
		MutInputGuidoFileDeviceShape():MutInputDeviceShape() {}
		MutInputGuidoFileDeviceShape (wxWindow * parent,
					      wxWindowID id, 
					      mutabor::InputDevice & d):
			MutInputDeviceShape() {
			TRACEC;
			Create (parent,id,d);
		}
	public:
		bool Create (wxWindow * parent, 
			     wxWindowID id, 
			     mutabor::InputDevice & d)
			{
				TRACEC;
				return MutInputDeviceShape::Create(parent,id,d);
			}

		virtual MutIcon & GetMutIcon () 
			{
				TRACEC;
				return GuidoFileBitmap;
			}

		void SetLabel(const wxString & st ) {
			fileName = st;
			fileName.Normalize();
			MutInputDeviceShape::SetLabel (fileName.GetFullName());
		}

		virtual wxPanel * GetFilterPanel(wxWindow * parent, 
						      mutabor::Route & route) const;
		virtual void ReadFilterPanel(wxWindow * panel, 
						  mutabor::Route & route);
	
		/**
		 * The device notifies the shape about a state change.
		 *
		 * \param event wxCommandEvent containing the request
		 */
		void DoDeviceNotification (wxCommandEvent & event);
	protected: 
		virtual void InitializeDialog(InputDevDlg * in) const;
		virtual bool readDialog (InputDevDlg * in);
		virtual bool CanHandleType (mutabor::DevType  type) 
			{ return type == mutabor::DTGis; }

		wxFileName fileName;

	private:
		DECLARE_DYNAMIC_CLASS(MutInputGuidoFileDeviceShape)

	};
}
#endif				/* INPUTGUIDOFILEDEVICESHAPE_H_PRECOMPILED */
#endif				/* INPUTGUIDOFILEDEVICESHAPE_H */
/*
 * \}
 */

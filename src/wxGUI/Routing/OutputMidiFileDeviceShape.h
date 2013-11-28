// -*- C++ -*-
/** \file
 ********************************************************************
 * MIDI file input device shape.
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
 *
 ********************************************************************
 *\addtogroup GUIroute
 *\{
 ********************************************************************/

/* we guard a little bit complicated to ensure the references are set right
 */

#if (!defined(MUWX_ROUTING_OUTPUTMIDIFILEDEVICESHAPE_H) && !defined(PRECOMPILE)) \
	|| (!defined(MUWX_ROUTING_OUTPUTMIDIFILEDEVICESHAPE_H_PRECOMPILED))
#ifndef PRECOMPILE
#define MUWX_ROUTING_OUTPUTMIDIFILEDEVICESHAPE_H
#endif

// ---------------------------------------------------------------------------
// headers
// ---------------------------------------------------------------------------

#include "src/kernel/Defs.h"
#include "src/wxGUI/Routing/RouteIcons.h"
#include "src/wxGUI/Routing/DeviceShape.h"
//#include "Device.h"

#ifndef MUWX_ROUTING_OUTPUTMIDIFILEDEVICESHAPE_H_PRECOMPILED
#define MUWX_ROUTING_OUTPUTMIDIFILEDEVICESHAPE_H_PRECOMPILED

// system headers which do seldom change

//#include <map>

//#include "wx/defs.h"
//#include "wx/icon.h"
//#include "wx/stattext.h"

namespace mutaborGUI {

	class MutOutputMidiFileDeviceShape:public MutOutputDeviceShape
	{
		friend class GUIMidiFileFactory;
	protected:
		MutOutputMidiFileDeviceShape():MutOutputDeviceShape() {}
		MutOutputMidiFileDeviceShape (wxWindow * parent,
					      wxWindowID id, 
					      mutabor::OutputDevice d):
			MutOutputDeviceShape() 
			{
				Create (parent,id,d);
			}
	public:
		bool Create (wxWindow * parent, wxWindowID id, mutabor::OutputDevice d)
			{
				TRACEC;
				bool ret = MutOutputDeviceShape::Create(parent,id,d);
				TRACEC;
				return ret;
			}

		virtual MutIcon & GetMutIcon () 
			{
				TRACEC;
				return MidiFileBitmap;
			}

		void SetLabel(const wxString & st ) {
			fileName = st;
			fileName.Normalize();
			MutOutputDeviceShape::SetLabel (fileName.GetFullName());
		}

		virtual wxPanel * GetFilterPanel(wxWindow * parent, 
						       mutabor::Route & route) const;
		virtual void ReadFilterPanel(wxWindow * panel, 
						   mutabor::Route & route);

	protected: 
		virtual void InitializeDialog(OutputDevDlg * out) const;
		virtual bool readDialog (OutputDevDlg * out);
		virtual bool CanHandleType (mutabor::DevType  type) { 
			return type == mutabor::DTMidiFile;
		}

		wxFileName fileName;

	private:
		DECLARE_DYNAMIC_CLASS(MutOutputMidiFileDeviceShape)

	};
}
#endif				/* OutputMidiFileDeviceShape_H_PRECOMPILED */
#endif				/* OutputMidiFileDeviceShape_H */
/*
 * \}
 */

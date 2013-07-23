// -*- C++ -*-
/** \file
 ********************************************************************
 * Box shape for route window.
 *
 * Copyright: (c) 2011 TU Dresden
 *            (c) Tobias Schlemmer (changes after 2011-11-01)
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
 *\addtogroup route
 *\{
 ********************************************************************/

/* we guard a little bit complicated to ensure the references are set right
 */

#if (!defined(MUWX_ROUTING_BOXSHAPE_H) && !defined(PRECOMPILE)) \
	|| (!defined(MUWX_ROUTING_BOXSHAPE_H_PRECOMPILED))
#ifndef PRECOMPILE
#define MUWX_ROUTING_BOXSHAPE_H
#endif

// ---------------------------------------------------------------------------
// headers
// ---------------------------------------------------------------------------

#include "src/kernel/Defs.h"
#include "src/wxGUI/GUIBoxData.h"
#include "src/wxGUI/Routing/GUIRoute.h"
#include "src/wxGUI/Routing/BoxChannelShape.h"
#include "src/wxGUI/Routing/BoxIconShape.h"
#include "src/kernel/routing/Device.h"

#ifndef MUWX_ROUTING_BOXSHAPE_H_PRECOMPILED
#define MUWX_ROUTING_BOXSHAPE_H_PRECOMPILED

// system headers which do seldom change
// we must break some recursion
//#include <map>

//#include "wx/defs.h"
//#include "wx/icon.h"
//#include "wx/stattext.h"

#include "wx/colour.h"
#include "wx/sizer.h"

namespace mutaborGUI {
	class BoxDlg;
	class MutBoxChannelShape;
//	class MutOutputDeviceShape;
	class RoutePanel;

	const wxColour & BoxColour(int nr);
	const wxColour & BoxTextColour(int nr);
	void initBoxColours();

	class MutBoxShape:public MutBoxIconShape
	{
	protected:
		MutBoxIconShape * m_icon;
		wxSizer * channels;
		static wxSizerFlags sizerFlags;
		int boxId;
		static int maxBoxId;
	
	public:
		MutBoxShape():MutBoxIconShape(),m_icon(NULL),channels(NULL),
			      boxId(NoBox) {}

#if defined(_MSC_VER)
#pragma warning(push) // Save warning settings.
#pragma warning(disable : 4100) // Disable unreferenced formal parameter warnings
#endif
		MutBoxShape(wxStaticBox * box, int orient):
			MutBoxIconShape(),m_icon(NULL),channels(NULL)
			{
				STUBC;
			}

		MutBoxShape(wxWindow * parent,wxWindowID wid, int Id = NoBox):
			MutBoxIconShape(),m_icon(NULL),channels(NULL)
			{
				Create(parent,wid,Id);
			}
  
		virtual ~MutBoxShape()
			{ 
//		delete channels; 
			}
	
		bool Create(wxWindow * parent,wxWindowID wid, int Id = NoBox);

		static void SetSizerFlags (wxSizerFlags flags) {sizerFlags = flags; }
		static const wxSizerFlags & GetSizerFlags() { return sizerFlags; }

		virtual void DoLeftDblClick();

#if 0
		virtual void Focus() {
			SetFocusIgnoringChildren();
			UpdateBorder(wxBORDER_SUNKEN);
		}
#endif
		virtual void GotFocus() ;

		virtual bool SetBackgroundColour(const wxColour& colour);
		/// Get a double click and prepare for execution of the command
		/** Since programs might produce segmentation faults
		    when the object is deleted during processing of mouse
		    events, we send us a new event using the event queue.
		*/
		void LeftDblClickEvent (wxMouseEvent & event) { 
			wxCommandEvent command(wxEVT_COMMAND_MENU_SELECTED,
					       CM_LEFT_DOUBLE_CLICK); 
			wxPostEvent(this,command); 
		}
		/// Process a double click
		/** Since programs might produce segmentation faults
		    when the object is deleted during processing of mouse
		    events, we send us a new event using the event queue.
		*/
		void CmLeftDblClick (wxCommandEvent& event) {
			mutUnused(event);
			DoLeftDblClick(); 
		}


		void CmMoveIcon(wxCommandEvent & event);
		void OnKeyDown (wxKeyEvent & event);

		BoxDlg * ShowBoxDialog() const;
		virtual void InitializeDialog(BoxDlg * dlg) const;

		
		virtual MutBoxChannelShape * AddChannel(mutabor::Route & route);
		virtual MutBoxChannelShape * AddChannel(RoutePanel * panel);

		virtual MutBoxChannelShape * Add(MutBoxChannelShape * channel);
		virtual bool Remove(MutBoxChannelShape * shape);
	
		virtual bool HasChannel(const mutabor::Route & route);

		virtual void AddPossibleOutput(MutOutputDeviceShape * device);
	

//	virtual void SetLabel(const wxString &s);

//	virtual void RecalcSizes();
//	virtual wxSize CalcMin();

		//  override to hide/show the static box as well
//	virtual void ShowItems (bool show);

		virtual void Add(BoxData * box);
		virtual bool Remove(BoxData * box);
		
		void Attatch(BoxData * box) {
			box->Attatch(this);
		}
		bool Detatch(BoxData * box) {
			return box->Detatch(this);
		}
		bool Delete(BoxData * box) {
			return box->Delete(this);
		}

		virtual void DrawLines(wxDC & dc, const wxRect & screenpos);
  
		virtual bool Detach( wxWindow *window );
		virtual bool Detach( wxSizer *sizer ) 
			{
				if (channels) 
					return channels -> Detach(sizer); 
				else 
					return false;
			}
		virtual bool Detach( int index ) 
			{ 
				if (channels) 
					return channels -> Detach(index);
				else 
					return false;
			}
		virtual bool replaceSelfBy (MutBoxShape  * newshape);
		virtual bool DetachBox ();
	
		virtual bool readDialog (BoxDlg * box);
		virtual bool CanHandleType (int  type) { return true; }
		int GetBoxId() const { return boxId; }

		wxSizer * GetChannels() const { return channels; }
	private:
		void SetBoxId(int Id, bool layout=true);
		DECLARE_CLASS(MutBoxShape)
		DECLARE_EVENT_TABLE()
	};

	typedef std::list <MutBoxShape *> MutBoxShapeList;

}

#if defined(_MSC_VER)
#pragma warning(pop) // Restore warnings to previous state.
#endif 

#endif				/* BOXSHAPE_H_PRECOMPILED */
#endif				/* BOXSHAPE_H */
/*
 * \}
 */

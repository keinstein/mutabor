// -*- C++ -*-
/** \file
 ********************************************************************
 * Box shape for route window.
 *
 * Copyright: (c) 2011 TU Dresden
 *            (c) Tobias Schlemmer (changes after 2011-11-01)
 *
 * \author Rüdiger Krauße <krausze@mail.berlios.de>,
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
 *
 ********************************************************************
 *\addtogroup GUIroute
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

	class MutBoxShape:public MutBoxIconShape
	{
	public:
		MutBoxShape():MutBoxIconShape(),m_icon(NULL),channels(NULL),
			      box() {}

#if defined(_MSC_VER)
#pragma warning(push) // Save warning settings.
#pragma warning(disable : 4100) // Disable unreferenced formal parameter warnings
#endif


		MutBoxShape(wxWindow * parent,wxWindowID wid, mutabor::Box & b):
			MutBoxIconShape(),m_icon(NULL),channels(NULL),box(NULL) {
			Create(parent,wid,b);
		}

		virtual ~MutBoxShape();

		bool Create(wxWindow * parent, wxWindowID wid) {
			m_icon = this;
			return MutBoxIconShape::Create(parent,wid);
		}
		bool Create(wxWindow * parent,wxWindowID wid, mutabor::Box & b);

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

		/**
		 * Move the box in the box list and update the GUI
		 * according to the new order. This function provides the
		 * event handler that is called from the GUI.
		 *
		 * \param event wxCommandEvent containing the request
		 */
		void CmMoveIcon (wxCommandEvent & event);


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


		void OnKeyDown (wxKeyEvent & event);

		BoxDlg * ShowBoxDialog() const;
		virtual void InitializeDialog(BoxDlg * dlg) const;


		//		virtual MutBoxChannelShape * AddChannel(mutabor::Route & route);
		virtual MutBoxChannelShape * AddChannel(RoutePanel * panel);

		/// add a box
		virtual void Add(mutabor::Box & b) {
			TRACEC;
			if (box || !b)
				UNREACHABLEC;
			else
				SetBox(b, true);
			TRACEC;
		};

		/// replace a box
		virtual bool Replace(mutabor::Box oldbox,
				     mutabor::Box newbox) {
			/* we are using no references here, as we might get deleted
			   otherwise */
			TRACEC;
			if (box != oldbox) {
				UNREACHABLEC;
				return false;
			} else
				SetBox(newbox);
			TRACEC;
			return true;
		}

		/// remove a box
		virtual bool Remove(mutabor::Box b) {
			TRACEC;
			if (box != b) {
				UNREACHABLEC;
				return false;
			} else {
				SetBox();
			}

			TRACEC;
			return true;
		}


		virtual MutBoxChannelShape * Add(MutBoxChannelShape * channel);
		virtual bool Remove(MutBoxChannelShape * shape);

		virtual bool HasChannel(const mutabor::Route & route);

		virtual void AddPossibleOutput(MutOutputDeviceShape * device);


//	virtual void SetLabel(const wxString &s);

//	virtual void RecalcSizes();
//	virtual wxSize CalcMin();

		//  override to hide/show the static box as well
//	virtual void ShowItems (bool show);


		virtual void DrawLines(wxGraphicsContext & dc,
				       wxWindow * paintingWindow/*,
								  const wxPoint & origin*/);

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
		virtual bool DeleteBox ();

		virtual bool readDialog (BoxDlg * boxdlg);
		virtual bool CanHandleType (int  type) { return true; }
		mutabor::Box GetBox() const { return box; }

		wxSizer * GetChannels() const { return channels; }

		/**
		 * Updates the Display of the Box shape after a change
		 * of the box that must be honoured by this shape.
		 *
		 */
		void BoxChanged();
	protected:
		MutBoxIconShape * m_icon;
		wxSizer * channels;
		mutabor::Box box;
		static wxSizerFlags sizerFlags;

		/**
		 * Move the box in the box list and update the GUI
		 * according to the new order.
		 *
		 * \param count number of entries the device should be moved
		 *              up. Negative values indicate downwards direction.
		 */
		virtual void MoveBox(int count) {
				box->MoveInList(count);
		}


	private:
		void SetBox(bool nullify = true) {
			if (nullify)
				box.reset();
			SetLabel(_("No Box / Though mode"));
			SetBackgroundStyle(wxBG_STYLE_SYSTEM);
		}
		void SetBox(mutabor::Box & b, bool layout=true);
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

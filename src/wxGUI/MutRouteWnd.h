/** \file    -*- C++ -*-
 ********************************************************************
 * Routing window
 *
 * Copyright:   (c) 2005 TU Dresden
 * \author R. Krauße
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
 ********************************************************************
 * \addtogroup GUIroute
 * \{
 ********************************************************************/

#if (!defined(MUWX_MUTROUTEWND_H) && !defined(PRECOMPILE)) \
	|| (!defined(MUWX_MUTROUTEWND_H_PRECOMPILED))
#ifndef PRECOMPILE
#define MUWX_MUTROUTEWND_H
#endif

// ---------------------------------------------------------------------------
// headers
// ---------------------------------------------------------------------------

#include "src/kernel/Defs.h"
#include "src/wxGUI/Routing/RouteLists.h"
#include "src/wxGUI/generic/muconvauto.h"
#include "src/wxGUI/Routing/DeviceShape.h"
#include "src/wxGUI/Routing/BoxShape.h"

#ifndef MUWX_MUTROUTEWND_H_PRECOMPILED
#define MUWX_MUTROUTEWND_H_PRECOMPILED

#include "wx/scrolwin.h"
//#include "EDevice.h"

namespace mutaborGUI {

/* 
#define xz 5 // Zwischenräume
#define yz 5
*/

// RouteWin ----------------------------------------------------------
// Fenster, das die Routen enthält

	class MutRouteWnd : public wxScrolledWindow
	{

	public:
		/** Constructor for MutRouteWnd class.
		 * This constructor sets up the Routing window. It loads
		 * Icons, initializes sizers and creates the shapes of
		 * the different routing elements (e.g., devices and
		 * boxes).
		 * 
		 * \param parent parent Window as used in wxWidgets.
		 * \param pos positions of the window (if unset use
		 *           application default) 
		 * \param size size of the window
		 *           (if unset use the application default).
		 */
		MutRouteWnd(wxWindow *parent = NULL, 
			    const wxPoint& pos = wxDefaultPosition, 
			    const wxSize& size = wxDefaultSize);

		/*    void RePaint();
		      int FocusPos[2];
		      private:
		      wxString FileName;
		      int nTags;*/

	private:
		/*
		/// horizontal spacing between the sizers components.
		int spacex;
		/// space spacing between the sizers components.
		int spacey;
		wxIcon * DevIcon[4];
		wxBitmap *ConIcon[4];
		wxIcon * PlopIcon[4];
		*/
		wxSizer * InputSizer;
		wxSizer * OutputSizer;
		wxSizer * BoxSizer;
		MutInputDeviceShapeList InputDevices;
		MutOutputDeviceShapeList OutputDevices;
		MutBoxShapeList Boxes;
	
#if 0
		struct MurFileDataType
		{
			wxFileName name;
			enum { 
				TextRoute,
				UTF8TextRoute,
				XMLRoute1
			} type;
		};
#endif
	
		static MutFileDataType MurFileData;
	
	
	
		void createInputDevices(wxSizerFlags flags);
		void createBoxes(wxSizerFlags flags);
		void createRoutes(wxSizerFlags flags);
		void createOutputDevices(wxSizerFlags flags);
	public:
		/// interactive route loading
		/**
		 * This function opens a file open dialog in order to load a route configuration from disk storage.
		 * \argument event (wxCommandEvent) event to be processed
		 */
		static void CmRouteLoad(wxCommandEvent& event);
	
		/// save routes to disk.
		/**
		 * This function saves the current routing conifiguriton into a file on disk storage.
		 * \argument event (wxCommandEvent) event to be processed
		 */
		static void CmRouteSave(wxCommandEvent& event);
	
		/// save routes with a new file name
		/**
		 * This function opens a file save dialog in order to save a route configuration to disk storage.
		 * \argument event (wxCommandEvent) event to be processed
		 */
		static void CmRouteSaveAs(wxCommandEvent& event);
	
	
		/// fills the window with the corresponding shapes.
		/**
		 * This function is used to initialize the window with the current
		 * routing information. It creates the shapes for devices, routes and new objects.
		 */
		void InitShapes();
		void InitDevices();
		void ClearDevices();
	
		/// Adds an input device shape
		/**
		   \param device (MutInputDeviceShape *) device to be added
		   \param flags (wxSizerFlages &) Sizer flags, which shall be applied
		*/
		bool AddInputDevice(MutInputDeviceShape * device, const wxSizerFlags & flags) {
			mutASSERT(InputSizer);
			InputSizer -> Add(device,flags);
			Layout();
			FitInside();
			SetVirtualSize(wxDefaultSize);
			return true;
		}

		/// Clears all input device shapes
		void ClearInputDevices();
	
		/// Adds an output device shape
		/**
		   \param device (MutInputDeviceShape *) device to be added
		   \param flags (wxSizerFlages &) Sizer flags, which shall be applied
		*/
		bool AddOutputDevice(MutOutputDeviceShape * device, const wxSizerFlags & flags) {
			mutASSERT(OutputSizer);
			OutputSizer -> Add(device, flags);
			Layout();
			FitInside();
			SetVirtualSize(wxDefaultSize);
			return true;
		}
		/// Clears all output device shapes
		void ClearOutputDevices();
	
		/// Adds a box shape
		/**
		   \param box (MutInputDeviceShape *) box to be added
		   \param flags (wxSizerFlages &) Sizer flags, which shall be applied
		*/
		bool AddBox(MutBoxShape * box, const wxSizerFlags & flags) {
			mutASSERT(BoxSizer);
			BoxSizer -> Add(box,flags);
#if 0
			box->Fit();
			box->Layout();
//			GetSizer()->SetItemMinSize(box,-1,-1);
//			GetSizer()->RecalcSizes();
//			Layout();
			Fit();
			Layout();
			FitInside();
			Refresh();
//			SetVirtualSize(GetBestVirtualSize());
#endif
			Boxes.push_back(box);
//			InvalidateRect(GetClientRect);
			return true;
		}

		bool AddRoute(MutBoxChannelShape * channel, const wxSizerFlags & flags) {
			mutASSERT(BoxSizer);
			mutabor::Route r = channel->GetRoute();
			mutabor::Box b = r->GetBox();
			MutBoxShape * boxshape = ToGUIBase(b)->GetShape(this);
			boxshape->Add(channel);
			return true;
		}

		/// Clears all box shapes
		void ClearBoxes();
	
		wxSizer * GetInputDevices() const 
			{
				return InputSizer;
			}
	
		wxSizer * GetBoxes() const 
			{
				return BoxSizer;
			}
	
		wxSizer * GetOutputDevices() const 
			{
				return OutputSizer;
			}
	
		// calls layout for layout constraints and sizers
		void OnSize(wxSizeEvent& event);
		virtual void FitInside();
		void OnPaint(wxPaintEvent & event);
		virtual void OnDraw(wxDC& dc);
		void OnMoveShape(wxCommandEvent& event);
		
		template<class T>
		wxSizer * GetShapeSizer ();

		template<class T>
		wxSizer * GetShapeSizer (T * shape) {
			return GetShapeSizer<T>();
		}
		
		template<class T> 
		void MoveShape(T * shape, int newpos) {
			return MoveShape(shape, newpos, GetShapeSizer<T>());
		}


	public:
	  //		WX_DECLARE_CONTROL_CONTAINER();
	protected:
		/** 
		 * Rally move shape. This function should not be called from outside the 
		 * class. It's here, because C++ does not allow partial specialisation
		 * of functions.
		 * 
		 * \param shape   Shape to be moved.
		 * \param newpos  New position where the shape shall be dropped.
		 * \param sizer   Sizer that is responsible for the dropped window
		 */
		void MoveShape(wxWindow * shape, int newpos, wxSizer * sizer);


	private:
		DECLARE_DYNAMIC_CLASS_NO_COPY(MutRouteWnd)
		DECLARE_EVENT_TABLE()
	};


	template<> 
	inline wxSizer * MutRouteWnd::GetShapeSizer<MutInputDeviceShape> () {
		return InputSizer;
	}

	template<> 
	inline wxSizer * MutRouteWnd::GetShapeSizer<MutOutputDeviceShape> () {
		return OutputSizer;
	}

	template<> 
	inline wxSizer * MutRouteWnd::GetShapeSizer<MutBoxShape> () {
		return BoxSizer;
	}


	extern bool LogicOn;
}
#endif // precompiled
#endif // header loaded

///\}

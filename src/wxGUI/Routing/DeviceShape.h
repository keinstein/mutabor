// -*- C++ -*-
/** \file
 ********************************************************************
 * Device shape base class for route window.
 *
 * $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/src/wxGUI/Routing/DeviceShape.h,v 1.8 2011/11/02 14:32:00 keinstein Exp $
 * \author Rüdiger Krauße <krausze@mail.berlios.de>,
 * Tobias Schlemmer <keinstein@users.berlios.de>
 * \date 1998
 * $Date: 2011/11/02 14:32:00 $
 * \version $Revision: 1.8 $
 * \license GPL
 *
 *
 *
 ********************************************************************
 *\addtogroup route
 *\{
 ********************************************************************/

#if (!defined(MUWX_ROUTING_DEVICESHAPE_H) && !defined(PRECOMPILE)) \
	|| (!defined(MUWX_ROUTING_DEVICESHAPE_H_PRECOMPILED))
#ifndef PRECOMPILE
#define MUWX_ROUTING_DEVICESHAPE_H
#endif

// ---------------------------------------------------------------------------
// headers
// ---------------------------------------------------------------------------

#include "src/kernel/Defs.h"
#include "src/wxGUI/IconShape.h"
#include "src/kernel/routing/Route.h"
#include "src/wxGUI/Routing/RouteLists.h"
//#include "Device.h"

#ifndef MUWX_ROUTING_DEVICESHAPE_H_PRECOMPILED
#define MUWX_ROUTING_DEVICESHAPE_H_PRECOMPILED

// system headers which do seldom change

#include <map>
//#include "wx/defs.h"
//#include "wx/ogl/ogl.h"
//#include "wx/icon.h"
//#include "wx/stattext.h"


namespace mutaborGUI {

	class InputDevDlg;

	class MutDeviceShape:public MutIconShape
	{
	protected:
		//	wxFileName filename;
		class strptrless {
		public:
			bool operator () (wxString * a, wxString * b) {
				if (a == b) return true;
				if (a == NULL) return true;
				if (b == NULL) return false;
				return (*a <= *b);
			}
		};

		MutBoxChannelShapeList routes;
	public:

		typedef std::map<wxString *, MutDeviceShape *, strptrless> 
		stringmaptype;
		typedef stringmaptype::iterator stringmapiterator;
  
	protected:
		MutDeviceShape():MutIconShape() 
			{
			}
		MutDeviceShape (wxWindow * parent, wxWindowID id, 
				const wxString & name = wxEmptyString):
			MutIconShape()
			{
				Create(parent, id, name);
			}
	public:
		virtual ~MutDeviceShape() {}
 
		bool Create (wxWindow * parent, wxWindowID id, 
			     const wxString & name = wxEmptyString)
			{


				DEBUGLOG(other, _T(""));
				DEBUGLOG(other, _T("Name %s"),name.c_str());
				bool state = MutIconShape::Create (parent,id);
				if (state) SetLabel(name);
				return state;
			}
		const MutBoxChannelShapeList & GetChannels() const {
			return routes;
		}
	
		/// add a route
		virtual void Add(MutBoxChannelShape *  route);
		/// replace a route
		virtual bool Replace(MutBoxChannelShape * oldroute,
				     MutBoxChannelShape * newroute);
		/// remove a route
		virtual bool Remove(MutBoxChannelShape * route);
		/// Move routes to another device 
		virtual bool MoveRoutes (MutDeviceShape * newclass);

		virtual bool Recompute();
//		virtual mutabor::Route getRoutes() = 0;
		virtual void DoLeftDblClick() = 0;


#if defined(_MSC_VER)
#pragma warning(push) // Save warning settings.
#pragma warning(disable : 4100) // Disable unreferenced formal parameter warnings
#endif

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
			DoLeftDblClick(); 
		}

#if defined(_MSC_VER)
#pragma warning(pop) // Restore warnings to previous state.
#endif 

		void OnKeyDown (wxKeyEvent & event);

#if 0
	protected:
		void RemoveFromStringMap(stringmaptype & sm) {
			std::pair<stringmapiterator,stringmapiterator> 
				bounds = sm.equal_range(&m_label);
			for (stringmapiterator it = bounds.first; 
			     it != bounds.second; ++it) {
				if ((*it).second == this) {
					stringmapiterator it1 = it;
					it++;
					sm.erase(it1);
				}
			}
		}

		void InsertSelfToStringMap(stringmaptype & sm) {
			sm.insert(std::make_pair(&m_label,this)); 
		}
#endif
	private:
		DECLARE_DYNAMIC_CLASS(MutIconShape)
		DECLARE_EVENT_TABLE()
	};

}
#endif				/* DEVICESHAPE_H_PRECOMPILED */
#endif				/* DEVICESHAPE_H */
/*
 * \}
 */

// -*- C++ -*-
/** \file
 ********************************************************************
 * Device shape base class for route window.
 *
 * $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/muwx/Routing/DeviceShape.h,v 1.5 2011/09/27 20:13:24 keinstein Exp $
 * \author Rüdiger Krauße <krausze@mail.berlios.de>,
 * Tobias Schlemmer <keinstein@users.berlios.de>
 * \date 1998
 * $Date: 2011/09/27 20:13:24 $
 * \version $Revision: 1.5 $
 * \license GPL
 *
 * $Log: DeviceShape.h,v $
 * Revision 1.5  2011/09/27 20:13:24  keinstein
 * * Reworked route editing backend
 * * rewireing is done by RouteClass/GUIRoute now
 * * other classes forward most requests to this pair
 * * many bugfixes
 * * Version change: We are reaching beta phase now
 *
 * Revision 1.4  2011-02-20 22:35:58  keinstein
 * updated license information; some file headers have to be revised, though
 *
 * Revision 1.3  2010-12-13 00:27:53  keinstein
 * compiles in linux as well as in mingw
 *
 * Revision 1.2  2010-11-21 13:15:48  keinstein
 * merged experimental_tobias
 *
 * Revision 1.1.2.5  2010-03-30 08:38:27  keinstein
 * added rudimentary command line support
 * changed debug system to allow selection of messages via command line
 * further enhancements to the route dialogs
 *
 * Revision 1.1.2.4  2010/02/15 12:08:21  keinstein
 * intermediate update for backup progress
 *
 * Revision 1.1.2.3  2010/01/14 09:34:24  keinstein
 * Checkin searching for a bug
 *
 * Revision 1.1.2.2  2010/01/11 12:51:52  keinstein
 * fix some problems due to splitting MutRouteShapes.{cpp,h}
 *
 * Revision 1.1.2.1  2009/11/30 12:08:57  keinstein
 * split MutRouteShapes into several files into directory Routing
 *
 * MutRouteShapes.h,v
 * Revision 1.1.2.2  2009/11/03 12:39:31  keinstein
 * input device dialog: Allow to edit input devices
 * fix a bug on Mac OS X, that prevented Mutabor from starting if no MIDI device is availlable
 *
 * Revision 1.1.2.1  2009/08/10 11:23:12  keinstein
 * merged from wrong tree
 *
 * Revision 1.2  2009/08/10 11:15:47  keinstein
 * some steps towards new route window
 *
 * Revision 1.1  2008/11/03 15:31:54  keinstein
 * Added to the system
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

#include "Defs.h"
#include "IconShape.h"
#include "Route.h"
#include "RouteLists.h"
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
		const MutBoxChannelShapeList & GetChannels() {
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
		DECLARE_DYNAMIC_CLASS(MutIconShape);
		DECLARE_EVENT_TABLE();
	};

}
#endif				/* DEVICESHAPE_H_PRECOMPILED */
#endif				/* DEVICESHAPE_H */
/*
 * \}
 */

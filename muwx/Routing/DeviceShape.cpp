// -*-C++ -*-
/** \file
 ********************************************************************
 * Device shape base class for route window.
 *
 * $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/muwx/Routing/DeviceShape.cpp,v 1.6 2011/10/03 17:42:41 keinstein Exp $
 * \author Rüdiger Krauße <krausze@mail.berlios.de>,
 * Tobias Schlemmer <keinstein@users.berlios.de>
 * \date 2009/11/23
 * $Date: 2011/10/03 17:42:41 $
 * \version $Revision: 1.6 $
 * \license GPL
 *
 * $Log: DeviceShape.cpp,v $
 * Revision 1.6  2011/10/03 17:42:41  keinstein
 * Open the configuration dialog on key press in the route window
 * Accept entering nothing in the input/output device dialog
 *
 * Revision 1.5  2011-09-30 18:07:05  keinstein
 * * make compile on windows
 * * s/wxASSERT/mutASSERT/g to get assert handler completely removed
 * * add ax_boost_base for boost detection
 *
 * Revision 1.4  2011-09-27 20:13:24  keinstein
 * * Reworked route editing backend
 * * rewireing is done by RouteClass/GUIRoute now
 * * other classes forward most requests to this pair
 * * many bugfixes
 * * Version change: We are reaching beta phase now
 *
 * Revision 1.3  2011-02-20 22:35:58  keinstein
 * updated license information; some file headers have to be revised, though
 *
 * Revision 1.2  2010-11-21 13:15:48  keinstein
 * merged experimental_tobias
 *
 * Revision 1.1.2.3  2010-03-30 08:40:15  keinstein
 * added rudimentary command line support
 * changed debug system to allow selection of messages via command line
 * further enhancements to the route dialogs
 *
 * Revision 1.1.2.2  2010/02/15 12:08:21  keinstein
 * intermediate update for backup progress
 *
 * Revision 1.1.2.1  2009/11/30 12:08:57  keinstein
 * split MutRouteShapes into several files into directory Routing
 *
 * MutRouteShapes.cpp,v $
 * Revision 1.1.2.3  2009/11/03 15:07:07  keinstein
 * Compile on Ubuntu 9.10
 * remove several interface and implementation pragmas
 * fixed some file names for case insensitive filesystems
 *
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
#include "Defs.h"
#include "DeviceShape.h"
#include <algorithm>
//#include "MutApp.h"
//#include "MutIcon.h"
//#include "MutRouteWnd.h"
//#include "InputDevDlg.h"
//#include "Device.h"

namespace mutaborGUI {
	IMPLEMENT_ABSTRACT_CLASS(MutDeviceShape, MutIconShape)
	
	BEGIN_EVENT_TABLE(MutDeviceShape, MutIconShape)
	EVT_KEY_DOWN(MutDeviceShape::OnKeyDown)
	EVT_LEFT_DCLICK(MutDeviceShape::LeftDblClickEvent)
	EVT_MENU(CM_LEFT_DOUBLE_CLICK,MutDeviceShape::CmLeftDblClick)
	END_EVENT_TABLE()

	void MutDeviceShape::OnKeyDown (wxKeyEvent & event) {
		if (event.HasModifiers()) {
			event.Skip();
			return;
		}

                /* Other inspirations:
		   case WXK_DELETE:
		   // cursor keys
		   */
		switch (event.GetKeyCode()) {
		case WXK_NUMPAD_ENTER:
		case WXK_RETURN:
		case WXK_SPACE:
		case WXK_NUMPAD_SPACE:
		case WXK_NUMPAD_ADD:
		case WXK_ADD:
		case WXK_WINDOWS_MENU:
		case WXK_MENU:
		{
			wxCommandEvent command(wxEVT_COMMAND_MENU_SELECTED,
					       CM_LEFT_DOUBLE_CLICK); 
			wxPostEvent(this,command); 
			return;
		}
		default:
			event.Skip();
		}
	}


	

	void MutDeviceShape::Add(MutBoxChannelShape *  route) 
	{
#ifdef DEBUG
		MutBoxChannelShapeList::iterator pos = 
			std::find(routes.begin(),routes.end(),route);
		mutASSERT(pos == routes.end());
#endif 
		routes.push_back(route);
		Update();
	}

	bool MutDeviceShape::Replace(MutBoxChannelShape * oldroute,
					  MutBoxChannelShape * newroute)
	{
		bool retval = Remove(oldroute);
		Add(newroute);
		Recompute();
		return retval;
	}
	bool MutDeviceShape::Remove(MutBoxChannelShape * route)
	{
		MutBoxChannelShapeList::iterator pos = 
			std::find(routes.begin(),routes.end(),route);
		if (pos == routes.end()) {
			UNREACHABLEC;
			return false;
		} else { 
			routes.erase(pos);
		}
		Recompute();
		return true;
	}
	bool MutDeviceShape::MoveRoutes (MutDeviceShape * newclass) 
	{
		routes.swap(newclass->routes);
		Recompute();
		return true;
	}

	bool MutDeviceShape::Recompute() 
	{
		SetIcon(GetMutIcon());
		//  SetLabel (filename.GetFullName());
		return GetIcon().IsOk();
	}
}



/*
 * \}
 */

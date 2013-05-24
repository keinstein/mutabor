// -*-C++ -*-
/** \file
 ********************************************************************
 * Device shape base class for route window.
 *
 * \author Rüdiger Krauße <krausze@mail.berlios.de>,
 * Tobias Schlemmer <keinstein@users.berlios.de>
 * \date 2009/11/23
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
#include "src/kernel/Defs.h"
#include "src/wxGUI/Routing/DeviceShape.h"
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
		ClearPerimeterPoints();
		Update();
	}

	bool MutDeviceShape::Replace(MutBoxChannelShape * oldroute,
				     MutBoxChannelShape * newroute)
	{
#ifdef DEBUG
		MutBoxChannelShapeList::iterator pos = 
			std::find(routes.begin(),routes.end(),oldroute);
		mutASSERT(pos != routes.end());
#endif
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
		ClearPerimeterPoints();
		SetIcon(GetMutIcon());
		//  SetLabel (filename.GetFullName());
		return GetIcon().IsOk();
	}
}



/*
 * \}
 */

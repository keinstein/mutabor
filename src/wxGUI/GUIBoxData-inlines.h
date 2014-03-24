/** \file               -*- C++ -*-
********************************************************************
* GUI Box data. Inline functions that must not be defined at class declaration time
*
* Copyright:   (c) 2011 TU Dresden
*              Changes after 2011-11 (c) Tobias Schlemmmer
* \author  Tobias Schlemmer <keinstein@users.berlios.de>
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
* \addtogroup GUI
* \{
********************************************************************/

#if (!defined(MUWX_GUIBOXDATA_INLINES_H) && !defined(PRECOMPILE))	\
	|| (!defined(MUWX_GUIBOXDATA_INLINES_H_PRECOMPILED))
#ifndef PRECOMPILE
#define MUWX_GUIBOXDATA_INLINES_H
#endif

// ---------------------------------------------------------------------------
// headers
// ---------------------------------------------------------------------------

#include "src/kernel/Defs.h"
#include "src/wxGUI/Routing/RouteLists.h"
#include "src/wxGUI/GUIBoxData.h"
#include "src/wxGUI/Routing/BoxShape.h"

#ifndef MUWX_GUIBOXDATA_INLINES_H_PRECOMPILED
#define MUWX_GUIBOXDATA_INLINES_H_PRECOMPILED

// ---------------------------------------------------------------------------
// headers
// ---------------------------------------------------------------------------


namespace mutaborGUI {

	inline void connect(mutabor::Box & box, MutBoxShape * shape) {
		BoxData * guibox = ToGUIBase(box);
 		TRACE;
		DEBUGLOG2(routing,("Connecting %p"),(void*)shape);
		if (!shape || !guibox) {
			UNREACHABLE;
			return;
		}
		if (shape->GetBox()) {
			UNREACHABLE;
			return;
		}

		guibox->Add(shape);
		shape->Add(box);

		wxWindow * parent = shape->GetParent();
		TRACE;
		const mutabor::routeListType & routes = box -> GetRoutes();
		for (mutabor::routeListType::const_iterator 
			     route = routes.begin();
		     route != routes.end(); route++) {
			mutabor::Route & r = const_cast<mutabor::Route & >(*route);
			TRACE;
			MutBoxChannelShape * channel =
				ToGUIBase(r)->GetShape(parent);
			if (channel) {
				DEBUGLOG2(always,("Strange... a route without box shape should not have a box channel shape"));
				UNREACHABLE;
				shape->Add(channel);
				TRACE;
				channel->Add(shape);
				TRACE;
			}
			
		}

	}

	inline bool disconnect(mutabor::Box & box, MutBoxShape * shape) 
	{
		BoxData * guibox = ToGUIBase(box);
 		TRACE;
		DEBUGLOG2(routing,("Connecting %p"),(void*)shape);
		if (!shape || !guibox) {
			UNREACHABLE;
			return false;
		}
		if (shape->GetBox() != box) {
			UNREACHABLE;
			return false;
		}

#if 0

		wxWindow * parent = shape->GetParent();
		TRACE;
		const mutabor::routeListType & routes = box -> GetRoutes();
		for (mutabor::routeListType::const_iterator 
			     route = routes.begin();
		     route != routes.end(); route++) {
			mutabor::Route & r = const_cast<mutabor::Route & >(*route);
			TRACE;
			MutBoxChannelShape * channel =
				ToGUIBase(r)->GetShape(parent);
			/* clients are removed automatically and routes are removed in the destructor */
			if (channel) {
				// #warning this seems odd: check it
				// after Mutabor is running again. at
				// least each channel should be
				// disconnected from its route
				shape->Remove(channel);
				TRACE;
				channel->Remove(shape);
				TRACE;
			} else {
				UNREACHABLE;
			}
			
		}
#endif

		guibox->Remove(shape);
		shape->Remove(box);

		return true;

#if 0
//-----------------------------
 		TRACE;
		DEBUGLOG2(routing,_T("Disconnecting %p"),(void*)shape);
		if (!shape) {
			UNREACHABLE;
			return false;
		}
		bool retval = true; 
		const MutBoxChannelShapeList & channels = 
			shape->GetChannels();
		DEBUGLOG2(routing,_T("%d channels"), (int)channels.size());
		MutBoxChannelShapeList::const_iterator i;
		while ( (i = channels.begin()) != channels.end()) {
			MutBoxChannelShape * channel = 
				const_cast<MutBoxChannelShape *>(*i);
			DEBUGLOG2(routing,_T("Disconnecting %p from %p"),
				  (void*)shape,(void*)channel);
			TRACE;
			retval = retval && shape -> Remove(channel);
			TRACE;
			retval = retval && channel -> Remove(shape);
		}

		DEBUGLOG2(routing,_T("Disconnecting %p from %p"),(void*)shape,(void*)dev);
 		TRACE;
		if (retval) 
			retval = dev->Remove(shape);
 		TRACE;

		// note: the shape keeps a smartptr to dev. So this
		// should be callde after the other Remove.
		if (retval)
			retval = shape->Remove(dev->GetDevice());
 		TRACE;
		if (!retval) 
			UNREACHABLE;
		return retval;
#endif
	}

	inline const MutBoxShape * BoxData::GetShape(wxWindow * parent) const {
		for (MutBoxShapeList::const_iterator shape = shapes.begin();
		     shape != shapes.end(); shape++) {
			if ((*shape)->GetParent() == parent) 
				return *shape;
		}
		return NULL;
	}

	inline MutBoxShape * BoxData::GetShape(wxWindow * parent) {
		for (MutBoxShapeList::const_iterator shape = shapes.begin();
		     shape != shapes.end(); shape++) {
			if ((*shape)->GetParent() == parent) 
				return *shape;
		}
		return NULL;
	}

	inline void BoxData::MoveToInList(int newpos) {
		for (MutBoxShapeList::iterator i = shapes.begin();
		     i != shapes.end();
		     i++) {
			wxWindow * win = (*i)->GetParent();
			MutRouteWnd * display = NULL;
			while (win && !(display = dynamic_cast<MutRouteWnd *>(win)))
				win = win->GetParent();
			if (display)
				display -> MoveShape(*i,newpos);
		}
	}

	inline int BoxData::MoveInList(int count) {
		int newpos = basetype::MoveInList(count);
		MoveToInList(newpos);
		return newpos;
	}

	inline void BoxData::Add(MutBoxShape * shape) {
		if (shape) {
			shapes.push_back(shape);
		} else {
			UNREACHABLEC;
		}
	}
	inline bool BoxData::Remove(MutBoxShape * shape) {
		bool ok = false;
		if (shape) {
			MutBoxShapeList::iterator pos = 
				std::find(shapes.begin(),shapes.end(),shape);
			ok = (pos != shapes.end()); 
			mutASSERT(ok);
			if (ok)
				shapes.erase(pos);
		} else {
			UNREACHABLEC;
			ok = false;
		}
		return ok;
	}
#if 0

	inline void BoxData::Attatch(MutBoxShape * shape) {
		if (!shape) {
			UNREACHABLEC;
			return;
		}
		Add(shape);
		shape->Add(this);
	}
	inline bool BoxData::Detatch(MutBoxShape * shape) {
		if (!shape) {
			UNREACHABLEC;
			return false;
		}
		bool retval = Remove(shape);
		if (retval)
			retval = retval && shape->Remove(this);
		return retval;
	}
	inline bool BoxData::Delete(MutBoxShape * shape) {
		if (!shape) {
			UNREACHABLEC;
			return false;
		}
		bool retval = Detatch(shape);
		if (retval) 
			shape -> Destroy();
	}
#endif
}
#endif // MUWX_GUIBOXDATA_INLINES_H_PRECOMPILED
#endif // MUWX_GUIBOXDATA_INLINES_H
///\}

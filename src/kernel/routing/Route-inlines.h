/** \file               -*- C++ -*-
 ********************************************************************
 * Inline functions from Route.h
 *
 * $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/src/kernel/routing/Route-inlines.h,v 1.4 2011/11/02 14:31:57 keinstein Exp $
 * Copyright:   (c) 2011 TU Dresden
 * \author  Tobias Schlemmer <keinstein@users.berlios.de>
 * \date 
 * $Date: 2011/11/02 14:31:57 $
 * \version $Revision: 1.4 $
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
 * \addtogroup templates
 * \{
 ********************************************************************/
// availlable groups: GUI, route, kernel, src/wxGUI, debug, docview

/* we guard a little bit complicated to ensure the references are set right
 */

#if (!defined(MU32_ROUTING_ROUTE_INLINES_H) && !defined(PRECOMPILE)) \
	|| (!defined(MU32_ROUTING_ROUTE_INLINES_H_PRECOMPILED))
#ifndef PRECOMPILE
#define MU32_ROUTING_ROUTE_INLINES_H
#endif

// ---------------------------------------------------------------------------
// headers
// ---------------------------------------------------------------------------

#include "src/kernel/Defs.h"
#include "src/kernel/routing/Route.h"

#ifndef MU32_ROUTING_ROUTE_INLINES_H_PRECOMPILED
#define MU32_ROUTING_ROUTE_INLINES_H_PRECOMPILED

// system headers which do seldom change
#include "Device.h"


namespace mutabor {



	inline void connect(Route & r, OutputDevice & out) {
		r->Add(out);
		out->Add(r);
	}


	inline void connect(Route & r, InputDevice & in) {
		r->Add(in);
		in->Add(r);
	}

	inline void connect(Route & r, int boxid) {
		r->Add(boxid);
	}

	inline void connect(OutputDevice & out, Route & r) { connect(r,out); }
	inline void connect(InputDevice & in, Route & r) { connect(r,in); }
	inline void connect(int boxid, Route & r) { connect(boxid,r); }

	inline bool disconnect(Route & r, OutputDevice & out) {
		bool retval = out->Remove(r);
		if (retval) 
			if (!(retval = r->Remove(out))) {
				out->Add(r);
			}
		return retval;
	}

	inline bool disconnect(Route & r, InputDevice & in) {
		bool retval = in->Remove(r);
		if (retval) {
			if (!(retval = r->Remove(in))) {
				in -> Add(r);
			}
		}
		return retval;
	}

	inline bool disconnect(Route & r, int boxid) {
		return r->Remove(boxid);
	}

	inline bool disconnect(OutputDevice & out, Route & r) { return disconnect(r,out); }
	inline bool disconnect(InputDevice & in, Route & r) { return disconnect(r,in); }
	inline bool disconnect(int boxid, Route & r) { return disconnect(boxid,r); }

	inline bool reconnect(Route & r, OutputDevice & oldout, OutputDevice & newout) {
		bool retval = oldout->Remove(r);
		if (retval) {
			retval = r->Replace(oldout,newout);
		}
		if (retval) {
			newout->Add(r);
		} else {
			mutASSERT(false);
			r->Remove(newout);
			// Check that oldout is correcty disconnected
			
		}
		return retval;
	}

	inline bool reconnect(Route & r, InputDevice & oldin, InputDevice & newin) {
		bool retval = r->Replace(oldin,newin);
		if (retval) {
			retval = retval && oldin->Remove(r);
		}
		if (retval) {
			newin->Add(r);
		} else {
			mutASSERT(false);
			// Check that oldin is correcty disconnected
			r->Remove(newin);
			
		}
		return retval;
	}
	
	inline bool reconnect(Route & r, int oldboxid, int newboxid) {
			return r->Replace(oldboxid,newboxid);
	}

	inline bool reconnect(OutputDevice & out, Route & oldroute, Route & newroute) {
		DEBUGLOG2(smartptr,_T("out: %p, oldroute: %p, newroute: %p"),
			  (void *)(out.get()),(void *)(oldroute.get()),(void *)(newroute.get()));

		bool ok = oldroute->Remove(out);
		if (ok) 
			ok = out->Replace(oldroute,newroute);
		if (ok) {
			newroute->Add(out);
		}
		DEBUGLOG2(smartptr,_T("out: %p, oldroute: %p, newroute: %p"),
			  (void *)(out.get()),(void*)(oldroute.get()),(void *)(newroute.get()));
		return ok;
	}

	inline bool reconnect(InputDevice & in, Route & oldroute, Route & newroute) {
		DEBUGLOG2(smartptr,_T("in: %p, oldroute: %p, newroute: %p"),
			  (void *)(in.get()),(void *)(oldroute.get()),(void *)(newroute.get()));

		bool ok = oldroute->Remove(in);
		if (ok) 
			ok = in->Replace(oldroute,newroute);
		if (ok) {
			newroute->Add(in);
		}
		DEBUGLOG2(smartptr,_T("in: %p, oldroute: %p, newroute: %p"),
			  (void *)(in.get()),(void *)(oldroute.get()),(void *)(newroute.get()));
		return ok;
	}

	template <class I, class O>
	inline void TRouteClass<I,O>::Create(InputDevice & in,
					OutputDevice & out,
					RouteType type,
					int iFrom,
					int iTo,
					int box,
					bool active,
					int oFrom,
					int oTo,
					bool oNoDrum)
	{
		DEBUGLOG(smartptr,_T("Route %p (%d)"),
			 (void*)this, 
			 (int)intrusive_ptr_get_refcount(this));
		DEBUGLOG(smartptr,_T("input device %p (%d)"),
			 (void*)in.get(),
			 (int)intrusive_ptr_get_refcount(in.get()));
		DEBUGLOG(smartptr,_T("output device %p (%d)"),
			 (void*)out.get(),
			 (int)intrusive_ptr_get_refcount(out.get()));
		Route self(this);
		if (in) 
			connect(self,in);
		else 
			In = NULL;
		if (out)
			connect(self,out);
		else 
			Out = NULL;
		Type = type;
		IFrom = iFrom;
		ITo = iTo;
		Box = box;
		Active = active;
		OFrom = oFrom;
		OTo = oTo;
		ONoDrum = oNoDrum;
		Id = NextRouteId();
	}

	template <class I, class O>
	inline void TRouteClass<I,O>::Destroy() 
	{
		Route self(this);
		debug_destroy_class(this);
		RemoveFromRouteList(this);
		if (In) disconnect(self,In);
		if (Out) disconnect(self,Out);
	}


	inline Route RouteFactory::Create(InputDevice & in,
					  OutputDevice & out,
					  RouteType type,
					  int iFrom,
					  int iTo,
					  int box,
					  bool active,
					  int oFrom,
					  int oTo,
					  bool oNoDrum) {

		DEBUGLOGTYPE(smartptr,RouteFactory,_T("input device %p (%d)"),
			     (void *)in.get(),
			     (int)intrusive_ptr_get_refcount(in.get()));

		DEBUGLOGTYPE(smartptr,RouteFactory,_T("output device %p (%d)"),
			     (void *)out.get(),
			     (int)intrusive_ptr_get_refcount(out.get()));

		if (factory) {
			RouteClass * r = factory->DoCreate(in,
							   out,
							   type,
							   iFrom,
							   iTo,
							   box,
							   active,
							   oFrom,
							   oTo,
							   oNoDrum);
			DEBUGLOGTYPE(smartptr,
				     RouteFactory,
				     _T("Shipping %p from factory"),
				     (void *)r);

			return r;
		} else {

			throw RouteFactoryNotSet();

//			UNREACHABLECT(RouteFactory);
			return NULL;
		}
			
	}

	inline ScopedRoute::~ScopedRoute()
	{ 
		if (get())
			get()->Destroy();
	}

}


#endif // precompiled
#endif // header loaded


///\}

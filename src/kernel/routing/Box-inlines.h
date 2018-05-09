/** \file               -*- C++ -*-
********************************************************************
* Inline routitnes for the device class
*
* Copyright:   (c) 2013 Tobias Schlemmer
* \author  Tobias Schlemmer <keinstein@users.sourceforge.net>
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
* \addtogroup route
* \{
********************************************************************/
/* we guard a little bit complicated to ensure the references are set right
 */

#if (!defined(ROUTING_BOX_INLINES) && !defined(PRECOMPILE))	      \
	|| (!defined(ROUTING_BOX_INLINES_PRECOMPILED))
#ifndef PRECOMPILE
#define ROUTING_BOX_INLINES
#endif

// ---------------------------------------------------------------------------
// headers
// ---------------------------------------------------------------------------

#include "src/kernel/Defs.h"
#include "src/kernel/routing/Box.h"
#include "src/kernel/Interpre.h"
#include "src/kernel/routing/Route-inlines.h"

#ifndef ROUTING_BOX_INLINES_PRECOMPILED
#define ROUTING_BOX_INLINES_PRECOMPILED

// system headers which do seldom change

MUTABOR_NAMESPACE(mutabor)

inline void BoxClass::Destroy()  {
	TRACEC;
	Box self(this);
	TRACEC;
	if (IsOpen()) Close();
	mutASSERT(!loopguard);

	DisconnectFromAll();

	TRACEC;
	debug_destroy_class(this);
	RemoveFromBoxList(this);
	TRACEC;
}

inline void BoxClass::DisconnectFromAll()  {
	Route route (NULL);
	Box self(this);

	routeListType::iterator R;
	while ( (R = routes.begin()) != routes.end() ) {
		TRACEC;
		route = (*R);
		TRACEC;
		disconnect(route,self);
		TRACEC;
	}
	route.reset();
}
	
inline bool is_key_trigger(struct any_trigger & trigger) {
	return trigger.type == any_trigger::key;
}
inline bool is_harmony_trigger(struct any_trigger & trigger) {
	return trigger.type == any_trigger::key;
}
inline bool is_midi_trigger(struct any_trigger & trigger) {
	return trigger.type == any_trigger::key;
}
inline keyboard_action * get_key_trigger(struct any_trigger & trigger) {
	return trigger.u.key_trigger;
}
inline harmony_action * get_harmony_trigger(struct any_trigger & trigger) {
	return trigger.u.harmony_trigger;
}
inline midi_action * get_midi_trigger(struct any_trigger & trigger) {
	return trigger.u.midi_trigger;
}

MUTABOR_NAMESPACE_END(mutabor)

#endif // precompiled
#endif // header loaded


///\}

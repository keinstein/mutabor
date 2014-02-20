/** \file               -*- C++ -*-
 ********************************************************************
 * A mutabor event class.
 *
 * Copyright:   (c) 2013 Tobias Schlemmer
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
 * \addtogroup route
 * \{
 ********************************************************************/

/* we guard a little bit complicated to ensure the references are set right
 */

#if (!defined(SRC_KERNEL_ROUTING_EVENT_H) && !defined(PRECOMPILE)) \
	|| (!defined(SRC_KERNEL_ROUTING_EVENT_H_PRECOMPILED))
#ifndef PRECOMPILE
#define SRC_KERNEL_ROUTING_EVENT_H
#endif

// ---------------------------------------------------------------------------
// headers
// ---------------------------------------------------------------------------

#include "src/kernel/Defs.h"
#include "src/kernel/routing/Device.h"

#ifndef SRC_KERNEL_ROUTING_EVENT_H_PRECOMPILED
#define SRC_KERNEL_ROUTING_EVENT_H_PRECOMPILED

#include <limits>

// system headers which do seldom change

namespace mutabor {
	namespace hidden {
		extern "C" {
			struct mutabor_event_type {
				int type;          //< uses midi::... constants
				size_t route_channel;
				int input_channel;
				size_t unique_id;
				union {
					struct {
						int note;
						int pressure;
					} aftertouch;

				};
			};
		}
	}
	using hidden::mutabor_event_type;

	class event_class: protected hidden::mutabor_event_type {
	public:
		event_class() { type = midi::UNKNOWN_EVENT; }
		virtual ~event_class() {}
		virtual int get_type() { return type; }

		virtual void set_box(Box & b) {
			box = b;
		}

		virtual void set_route(Route & r) {
			route_channel = r->get_session_id();
		}

		size_t get_unique_id() {
			return unique_id;
		}

		size_t get_route_channel() {
			return route_channel;
		}
	protected:
		REFPTR_INTERFACE;
		Box box;
	};

	class key_pressure_event: public event_class {
	public:
		key_pressure_event(int channel,
				   size_t id,
				   int n,
				   int p) {
			type = midi::KEY_PRESSURE;
			input_channel = channel;
			route_channel = std::numeric_limits<size_t>::max();
			unique_id = id;
			aftertouch.note = n;
			aftertouch.pressure = p;
		}

		int get_note() { return aftertouch.note; }
		int get_pressure() { return aftertouch.pressure; }

	};

	inline event_class * create_event(const std::vector<unsigned char> * code,
				   size_t unique_id) {
		mutASSERT(code);
		unsigned char midiStatus = code -> at(0) & 0xF0;
		switch (midiStatus) {
		case midi::KEY_PRESSURE:
			return new key_pressure_event(code->at(0) & 0x0f,
						      unique_id,
						      code->at(1),
						      code->at(2));

		default:
			return new event_class;
		}
	}

	typedef boost::intrusive_ptr<event_class> event;

}


#endif // precompiled
#endif // header loaded


///\}

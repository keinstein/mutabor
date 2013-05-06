/** \file               -*- C++ -*-
 ********************************************************************
 * Timing classes: Timer and timing parameters.
 *
 * Copyright:   (c) 2013 Tobias Schlemmer
 * \author  Tobias Schlemmer <keinstein@users.berlios.de>
 * \date 
 * $Date: 2011/09/27 20:13:26 $
 * \version $Version$
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

#if (!defined(ROUTING_TIMINGPARAMS) && !defined(PRECOMPILE)) \
	|| (!defined(ROUTING_TIMINGPARAMS_PRECOMPILED))
#ifndef PRECOMPILE
#define ROUTING_TIMINGPARAMS
#endif

// ---------------------------------------------------------------------------
// headers
// ---------------------------------------------------------------------------

#include "src/kernel/Defs.h"
#include "src/kernel/MidiKern.h"

#ifndef ROUTING_TIMINGPARAMS_PRECOMPILED
#define ROUTING_TIMINGPARAMS_PRECOMPILED

// system headers which do seldom change
#include <limits>
#include <exception>
#include "wx/stopwatch.h"

#define MUTABOR_NO_DELTA (std::numeric_limits<mutint64>::max()) //2147483647  // long max-Zahl

namespace mutabor {

	class timing_params {
	public:
		timing_params (): 
			is_fixed_ticks(true),
			fps(0),
			quarter_duration(wxLL(500000)),
			quarter_divisions(1000) {
		}

		timing_params (const timing_params & o): 
			is_fixed_ticks(o.is_fixed_ticks),
			fps(o.fps),
			quarter_duration(o.quarter_duration),
			quarter_divisions(o.quarter_divisions) {
		}
		
		void reset () {
			is_fixed_ticks = true;
			fps = 0;
			quarter_duration = 500000;
			quarter_divisions = 1000;
		}

		void set_duration(mutint64 d) { 
			quarter_duration = d;
		}
		mutint64 get_duration() { return quarter_duration; }

/*
		void set_ticks(mutint64 t) {
			quarter_divisions = t;
		}
*/
		mutint64 get_ticks() { return quarter_divisions; }
		
		mutint64 get_time(mutint64 d) {
			return is_fixed_ticks?
				(d * 1000000 + (quarter_divisions + 1)/2)/quarter_divisions:
				(d * quarter_duration + (quarter_divisions + 1)/2)/quarter_divisions;
		}

		mutint64 get_delta(mutint64 time) {
			return is_fixed_ticks?
				(time * quarter_divisions + 500000) / 1000000:
				(time * quarter_divisions + (quarter_duration+1)/2) / quarter_duration;
		}

		std::pair<uint8_t,uint8_t> get_MIDI_tick_signature();
		void set_MIDI_tick_signature(uint8_t fps, uint8_t count);

		static mutint64 update_duration(mutint64 duration,
						const timing_params oldd,
						const timing_params newd) {
			if ((oldd.is_fixed_ticks && newd.is_fixed_ticks) || duration == MUTABOR_NO_DELTA) return duration;
			mutint64 old_quarter = oldd.is_fixed_ticks ? 1000000 : oldd.quarter_duration;
			mutint64 new_quarter = newd.is_fixed_ticks ? 1000000 : newd.quarter_duration;
			mutint64 delta_quarter = new_quarter - old_quarter;
			if (delta_quarter > 0) {
				duration = (duration * new_quarter)/old_quarter;
			}
			if (oldd.quarter_divisions != newd.quarter_divisions) {
				duration = (duration * newd.quarter_divisions)/oldd.quarter_divisions;
			}
			if (delta_quarter < 0) {
				duration = (duration * new_quarter)/old_quarter;
			}
			return duration;
		}
	protected:
		bool is_fixed_ticks;       //< indicates whether we are in MIDI time code and ignore quarter_duration
		int fps;                   //< fps rate
		mutint64 quarter_duration; //< duration of quarter notes in μs
		mutint64 quarter_divisions; //< divisions of quarter notes
 	};



	class CurrentTimer: public wxStopWatch
	{
	public:
		CurrentTimer(mutint64 t = 0):wxStopWatch() {
			Start(t/1000);
			is_realtime = false;
		}
	
		virtual ~CurrentTimer() {}
		
		void UseRealtime(bool flag) { 
			if (flag == is_realtime) return;
			is_realtime = flag;
			
			if (is_realtime) {
				Start(time/1000);
			} else {
				time = Time()*1000;
			}
		}

		bool isRealtime() { return is_realtime; }

		void Set(mutint64 t = 0) {
			if (is_realtime) {
				Start(t/1000);
			} else {
				time = t;
			}
		}

		void Stop() {}
		
		mutint64 Get() { return is_realtime?(mutint64)Time()*1000:time; }
		
		CurrentTimer& operator = (mutint64 t) {
			Set(t);
			return * this;
		}

		CurrentTimer& operator += (mutint64 t) {
			mutASSERT(is_realtime);
			time += t;
		}


	protected:
		mutint64 time;
		bool is_realtime;
		timing_params timing;

	private:
		// should not be used (if defined)
		virtual void  Notify() {
			STUBC;
		}
		
		using wxStopWatch::Time;

		operator unsigned int () {
			return Get()/1000;
		}
	
		operator mutint64 () {
			return Get();
		}
	};

	extern CurrentTimer CurrentTime;

}
#endif // precompiled
#endif // header loaded


///\}

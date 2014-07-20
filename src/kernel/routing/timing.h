/** \file               -*- C++ -*-
 ********************************************************************
 * Timing classes: Timer and timing parameters.
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
#include <stdexcept>
#include <boost/throw_exception.hpp>
#if _XOPEN_SOURCE >= 600 || _POSIX_C_SOURCE >= 200112L
#include <time.h>
#include <errno.h>
//#elseif __WXMSW__
#else
#include "wx/stopwatch.h"
#include "thread.h"
#endif

#define MUTABOR_NO_DELTA (std::numeric_limits<mutint64>::max()) //2147483647  // long max-Zahl

namespace mutabor {

	/**
	 * A class for managing time calculations.
	 *
	 * This class provides a common API for time calculation. It
	 * allows to store timing parameters and provides functions
	 * for the correct transformation between the different time
	 * formats.
	 */

	class timing_params {
	public:
		/**
		 * Default Constructor. 
		 * The default constructor sets
		 * the timing parametes as follows: Fixed step
		 * durations on a 1ms grid at 120 bpm.
		 *
		 */
		timing_params ():
			is_fixed_ticks(true),
			fps(0),
			quarter_duration(500000),
			quarter_divisions(1000) {
		}

		/**
		 * Copy constructor.
		 *
		 * \param o the timing params that should be copied.
		 */
		timing_params (const timing_params & o):
			is_fixed_ticks(o.is_fixed_ticks),
			fps(o.fps),
			quarter_duration(o.quarter_duration),
			quarter_divisions(o.quarter_divisions) {
		}
	
		/**
		 * Reset the parameters to the default values.
		 * Fixed step durations on a 1ms grid at 120 bpm.
		 *
		 */
		void reset () {
			is_fixed_ticks = true;
			fps = 0;
			quarter_duration = 500000;
			quarter_divisions = 1000;
		}


		/**
		 * Set the quarter duration parameter.
		 *
		 * \param d duration of a quarter note in microseconds.
		 */
		void set_quarter_duration(mutint64 d) {
			if (d <= 0)
				BOOST_THROW_EXCEPTION(std::range_error("duration must be positive"));
			quarter_duration = d;
		}

		/**
		 * Get the quarter duration.
		 *
		 *
		 * \return quarter duration in microseconds.
		 */
		mutint64 get_quarter_duration() { return quarter_duration; }

/*
		void set_ticks(mutint64 t) {
			quarter_divisions = t;
		}
*/

		/**
		 * Get the number of ticks per time interval.
		 *
		 *
		 * \return in fixed time mode return the ticks per
		 * second otherwise the number of divisions of a
		 * quarter note.
		 */
		mutint64 get_ticks() { return quarter_divisions; }
	
		/** Translates a given number of MIDI quarter ticks into microseconds.
		 * Rounding is done according to the formula given in the midi standard:
		 * time = ticks * (quarter_duration / ticks per quarter)
		 *
		 * \param d time in quarter divisions
		 *
		 * \return time in microseconds.
		 */
		mutint64 get_time_midi(mutint64 d) {
			return is_fixed_ticks?
				d * (1000000/quarter_divisions):
				d * (quarter_duration/quarter_divisions);
		}

		/** Translates a given number of quarter ticks into microseconds using more exact rounding.
		 * Rounding is done according to the following formula (in integer arithmetic):
		 * time = round ((ticks * (quarter_duration )) / ticks per quarter)
		 *
		 * \param d time in quarter divisions
		 *
		 * \return time in microseconds.
		 */
		mutint64 get_time_exact(mutint64 d) {
			return is_fixed_ticks?
				((d * 1000000 + (quarter_divisions+1)/2)/quarter_divisions):
				(d * quarter_duration + (quarter_divisions + 1)/2)/quarter_divisions;
		}

		/** Translates a given time in microseconds into the corresponding number of MIDI.
		 * Rounding is done to meet the formula given in the midi standard:
		 * time = ticks * (quarter_duration / ticks per quarter)
		 *
		 * \param time time in microseconds.
		 *
		 * \return time in quarter divisions
		 */
		mutint64 get_delta_midi(mutint64 time) {
			mutint64 factor = is_fixed_ticks?
				1000000/quarter_divisions:
				quarter_duration/quarter_divisions;
			

			// The calculation should round for 25 fps 40 subframes correctly microseconds to milliseconds
			// if in daubt: round up as time calculation rounds down.
			return (2 * time + factor + 1) / (2 * factor);
		}

		/** Translates a given time in microseconds into number of quarter ticks using more exact rounding.
		 * Rounding is done to meet following formula (in integer arithmetic):
		 * time = round ((ticks * (quarter_duration )) / ticks per quarter)
		 *
		 * \param time time in microseconds.
		 *
		 * \return  time in quarter divisions
		 */
		mutint64 get_delta_exact(mutint64 time) {
			return is_fixed_ticks?
				(time * quarter_divisions + 500000) / 1000000:
				(time * quarter_divisions + (quarter_duration+1)/2) / quarter_duration;
		}


		/**
		 * Calculate the two bytes indicating the ticks per
		 * divisions field in a MIDI file
		 *
		 * The return value can be read as -fps and ticks per
		 * frame in fixed timing mode and as a 15 bit number
		 * in quarter relative timeing mode.
		 *
		 *
		 * \return pair of bytes that can be directly copied
		 * into the Standard MIDI File header.
		 */
		std::pair<uint8_t,uint8_t> get_MIDI_tick_signature();

		/**
		 * Calculate timing mode and timing parameters
		 * from the corresponding bytes in the MIDI file header.
		 *
		 * \param fps first byte of the signature denating MSB or negative frame rate.
		 * \param count second byte of the signature denoting LSB or ticks per frame.
		 */
		void set_MIDI_tick_signature(uint8_t fps, uint8_t count);

		/**
		 * Update the a duration when the parameters change.
		 *
		 * In Type 1 MIDI files the first track contains
		 * timing parameters for all tracks. This function can
		 * be used to update time stamps that are stored in
		 * microseconds.
		 *
		 * \note This function assumes that the change should
		 * take after an offset of 0 μs. Thus, offsets must be
		 * honoured in the calling code.
		 *
		 * \param duration  time to be recalculated
		 * \param oldd  old timing object.
		 * \param newd  now timing object.
		 *
		 * \return recalculated duration according to the two passed timing objects.
		 */	
		static mutint64 update_duration_midi(mutint64 duration,
						const timing_params & oldd,
						const timing_params & newd) {
			if ((oldd.is_fixed_ticks && newd.is_fixed_ticks) || duration == MUTABOR_NO_DELTA) return duration;
			mutint64 old_quarter = oldd.is_fixed_ticks ? 1000000 : oldd.quarter_duration;
			mutint64 new_quarter = newd.is_fixed_ticks ? 1000000 : newd.quarter_duration;
			mutint64 old_factor = old_quarter/oldd.quarter_divisions;
			mutint64 new_factor = new_quarter/newd.quarter_divisions;
		
			return ((duration + (old_factor+1)/2) / old_factor) * new_factor;
		}

		/**
		 * Update the a duration when the parameters change.
		 *
		 * In Type 1 MIDI files the first track contains
		 * timing parameters for all tracks. This function can
		 * be used to update time stamps that are stored in
		 * microseconds.
		 *
		 * This version tries to be more exact than the MIDI
		 * standard. For decoding standard MIDI files
		 * update_duration_midi is recommended.
		 *
		 * \note This function assumes that the change should
		 * take after an offset of 0 μs. Thus, offsets must be
		 * honoured in the calling code.
		 *
		 * \param duration  time to be recalculated
		 * \param oldd  old timing object.
		 * \param newd  now timing object.
		 *
		 * \return recalculated duration according to the two passed timing objects.
		 */	
		static mutint64 update_duration_exact(mutint64 duration,
						const timing_params & oldd,
						const timing_params & newd) {
			if ((oldd.is_fixed_ticks && newd.is_fixed_ticks) || duration == MUTABOR_NO_DELTA) return duration;
			mutint64 old_quarter = oldd.is_fixed_ticks ? 1000000 : oldd.quarter_duration;
			mutint64 new_quarter = newd.is_fixed_ticks ? 1000000 : newd.quarter_duration;
			mutint64 delta_quarter = new_quarter - old_quarter;
			if (delta_quarter > 0) {
				duration = (duration * new_quarter)/old_quarter;
			}
			if (oldd.quarter_divisions != newd.quarter_divisions) {
				duration = (duration * oldd.quarter_divisions)/newd.quarter_divisions;
			}
			if (delta_quarter < 0) {
				duration = (duration * new_quarter)/old_quarter;
			}
			return duration;

		}
	
		operator std::string() const;
	protected:
		bool is_fixed_ticks;       //< indicates whether we are in MIDI time code and ignore quarter_duration
		int fps;                   //< fps rate
		mutint64 quarter_duration; //< duration of quarter notes in μs
		mutint64 quarter_divisions; //< divisions of quarter notes
 	};

	inline std::string str(const timing_params & t) { return t; }

#if _XOPEN_SOURCE >= 600 || _POSIX_C_SOURCE >= 200112L
	class CurrentTimerBase {
	public:
		CurrentTimerBase():running(false) {
		}

		void Sleep(mutint64 time) {
			struct timespec data,remain = {0,0};
#ifdef DEBUG
			if (isDebugFlag(timer)) {
				clock_getres(CLOCK_MONOTONIC, &data);
				DEBUGLOGTYPE(timer,
					     CurrentTimerBase,
					     ("Timer resolution: %d s %ld ns"),
					     (int)data.tv_sec,
					     data.tv_nsec);
			}
#endif
			data.tv_sec = time/1000000;
			mutint64 tmp = time % 1000000;
			if (tmp < 0) tmp+= 1000000;
			data.tv_nsec = (long)(tmp *1000);
			DEBUGLOGTYPE(timer,
				     CurrentTimerBase,
				     ("sleeping time: %d s, %ld ns"),
				     (int)data.tv_sec,
				     data.tv_nsec);
			int status = clock_nanosleep(CLOCK_MONOTONIC,0,&data,&remain);
			DEBUGLOGTYPE(timer,
				     CurrentTimerBase,
				     ("Remaining time: %d s, %ld ns"),
				     (int)remain.tv_sec,
				     remain.tv_nsec);
			mutASSERT(status != EINTR);
			mutASSERT(status != EINVAL);
			mutASSERT(status != EFAULT);
			mutASSERT(!status);
		}

	protected:
		struct timespec start, resolution;
		bool running;
	

		void Start(mutint64 t = 0) {
			clock_getres(CLOCK_MONOTONIC,&resolution);
			clock_gettime(CLOCK_MONOTONIC,&start);
			start.tv_sec -= t/(1000*1000);
			start.tv_nsec -= (t % (1000*1000))*1000;
			if (start.tv_nsec < 0) {
				start.tv_sec -= 1;
				start.tv_nsec += 1000*1000*1000;
			} else if (start.tv_nsec > 1000*1000*1000) {
				start.tv_nsec -= 1000*1000*1000;
				start.tv_sec += 1;
			}
			DEBUGLOGTYPE(timer,
				     CurrentTimerBase,
				     ("Starting time: %d s, %ld ns"),
				     (int)start.tv_sec,
				     start.tv_nsec);
			running=true;
		}

		mutint64 Time() {
			struct timespec tmp;
			mutASSERT(running);
			if (!running)
				return 0;
			clock_gettime(CLOCK_MONOTONIC,&tmp);
			tmp.tv_sec -= start.tv_sec;
			tmp.tv_nsec -= start.tv_nsec;
			DEBUGLOGTYPE(timer,
				     CurrentTimerBase,
				     ("Elapsed time: %d s, %ld ns; = %ld μs"),
				     (int)tmp.tv_sec,
				     tmp.tv_nsec,
				     tmp.tv_sec *1000*1000 + tmp.tv_nsec/1000);
			return tmp.tv_sec *1000*1000 + tmp.tv_nsec/1000;
		}
	
	};

#else
	class CurrentTimerBase:protected wxStopWatch {
	public:
		static void Sleep(mutint64 time) {
			DEBUGLOGTYPE(timer,
				     CurrentTimerBase,
				     ("wxSleeping: %lu ms"),
				     (unsigned long) time/1000);
			Thread::Sleep((unsigned long)time/1000);
		}
	protected:
		struct timespec start, resolution;
	

		void Start(mutint64 t = 0) {
			wxStopWatch::Start(t/1000);
		}

		mutint64 Time() {
			return 1000*(mutint64)wxStopWatch::Time();
		}
	
	};

#endif

	/**
	 * A class for handling global timing issues. This class
	 * provides support for central timing. In realtime mode it
	 * works as central timer and in batch mode it works as global
	 * time variable.
	 *
	 * The time resolution is system dependent, but should not be
	 * worse than 1 ms in real time mode and 1μs in batch mode.
	 */
	class CurrentTimer: public CurrentTimerBase
	{
	public:

		/**
		 * Constructor starting the time at a given parameter.
		 *
		 * \param t start time
		 */
		CurrentTimer(mutint64 t = 0):CurrentTimerBase() {
			Start(t);
			is_realtime = true;
		}

		/**
		 * Destructor.
		 */
		virtual ~CurrentTimer() {}
	
		/**
		 * Switch between realtime and batch mode.
		 *
		 * \param flag indicating real time mode: true for realtime and false for batch mode.
		 */
		void UseRealtime(bool flag) {
			if (flag == is_realtime) return;
			is_realtime = flag;
		
			if (is_realtime) {
				Start(time);
			} else {
				time = Time();
			}
		}

		/**
		 * Return the mode of the timer.
		 *
		 * \retval true realtime mode
		 * \retval false batch mode
		 */
		bool isRealtime() { return is_realtime; }

		/**
		 * Set the current time.
		 *
		 * \param t time in μs.
		 */
		void Set(mutint64 t = 0) {
			if (is_realtime) {
				Start(t);
			} else {
				time = t;
			}
		}

		/**
		 * Return the current time in μs.
		 *
		 *
		 * \return Time in μs.
		 */
		mutint64 Get() { return is_realtime?Time():time; }

		/**
		 * Dummy function for stopping the timer.
		 *
		 * Currently this function does nothing. It is called
		 * from the global Stop function to support APIs that
		 * need to stop the global timer.
		 */
		void Stop() {}

		/**
		 * Assign a time value.
		 *
		 * \param t time in μs.
		 *
		 * \return reference to self.
		 */
		CurrentTimer& operator = (mutint64 t) {
			Set(t);
			return * this;
		}

		/**
		 * Increment a time value in batch mode.
		 *
		 * \param t time to add to the current time.
		 *
		 * \return reference to self.
		 */
		CurrentTimer& operator += (mutint64 t) {
			mutASSERT(!is_realtime);
			time += t;
			return * this;
		}


	protected:
		mutint64 time; //< Time value for batch mode
		bool is_realtime; //< flag indicating whether we are in batch mode.

	};

	extern CurrentTimer CurrentTime;

}
#endif // precompiled
#endif // header loaded


///\}

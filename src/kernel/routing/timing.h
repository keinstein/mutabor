/** \file               -*- C++ -*-
 ********************************************************************
 * Timing classes: Timer and timing parameters.
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
#include <limits>
#include <boost/throw_exception.hpp>
#include <boost/chrono.hpp>

#if _XOPEN_SOURCE >= 600 || _POSIX_C_SOURCE >= 200112L
#include <time.h>
#include <errno.h>
//#elseif __WXMSW__
#else
#include "wx/stopwatch.h"
#endif
#include "thread.h"

namespace mutabor {

	typedef boost::chrono::high_resolution_clock clocktype;
	using boost::chrono::microseconds;
	//	using boost::chrono::milliseconds;

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

		typedef microseconds::rep ticktype;
		class miditicks {
		public:
			class no_delta {
			public:
				static constexpr ticktype count() {
					return std::numeric_limits<ticktype>::max();
				}
			};

			constexpr miditicks(const ticktype & t,
					    timing_params & p):ticks(t),
				params(p) {}

			miditicks(const microseconds & ms,
				  timing_params & p,
				  bool midi = false):ticks(),
				params(p)
			{
				if (ms == microseconds::max()) {
					ticks = std::numeric_limits<ticktype>::max();
					return;
				}
				if (midi) {
					ticktype factor = p.is_fixed_ticks?
						1000000/p.quarter_divisions:
						p.quarter_duration.count()/p.quarter_divisions;
					// The calculation should
					// round for 25 fps 40
					// subframes correctly
					// microseconds to
					// milliseconds if in daubt:
					// round up as time
					// calculation rounds down.
					ticks = (2 * ms.count() + factor + 1) / (2 * factor);
				} else {
					ticks = p.is_fixed_ticks?
						(ms.count() * p.quarter_divisions + 500000) / 1000000:
						(ms.count() * p.quarter_divisions + (p.quarter_duration.count()+1)/2)
						/ p.quarter_duration.count();
				}

			}

			constexpr ticktype count() const { return ticks; }

			constexpr ticktype count_in_range(ticktype from, ticktype to) {
				if (ticks <= from) return from;
				if (to < ticks) return to;
				return ticks;
			}

			constexpr microseconds mus () const {
				return
					microseconds(params.is_fixed_ticks?
						     ((ticks * 1000000 + (params.quarter_divisions+1)/2)
						      /params.quarter_divisions):
						     (ticks * params.quarter_duration.count() +
						      (params.quarter_divisions + 1)/2)
						     /params.quarter_divisions);
			}

			constexpr microseconds midi_mus () const {
				return
					microseconds(params. is_fixed_ticks?
					    ticks * (1000000/params.quarter_divisions):
					    ticks * (params.quarter_duration.count()/params.quarter_divisions));
			}


			miditicks & set_zero() {
				ticks = 0;
				return *this;
			}

			miditicks & operator = (const miditicks & o) {
				if (&params != &(o.params)) {
					BOOST_THROW_EXCEPTION(std::invalid_argument(_mutN("Trying to assign a miditicks object with different timing parameters")));
				}
				ticks = o.ticks;
				return *this;
			}

			constexpr bool is_in_range(ticktype from, ticktype to) const {
				return from <= ticks && ticks < to;
			}

			miditicks & operator = (const no_delta & o) {
				ticks = o.count();
				return *this;

			}

			constexpr bool operator == (const no_delta & o) const {
				return ticks == o.count();
			}

			constexpr bool operator == (const miditicks & o) const {
				if (&params != &(o.params)) {
					return false;
				}
				return (ticks == o.ticks);
			}

			bool operator != (const no_delta & o) const {
				return ticks != o.count();
			}

			bool operator != (const miditicks & o) const {
				if (&params != &(o.params)) {
					return true;
				}
				return (ticks != o.ticks);
			}

			std::ostream & write(std::ostream & o) const {
				o << "ticks: " << ticks << "(" << (std::string)(params) << ")";
				return o;
			}
		protected:
			ticktype ticks;
			timing_params & params;
		};

			/**
		 * Default Constructor.
		 * The default constructor sets
		 * the timing parametes as follows: Fixed step
		 * durations on a 1ms grid at 120 bpm.
		 *
		 */
		constexpr timing_params ():
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
		constexpr timing_params (const timing_params & o):
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
			quarter_duration = microseconds(500000);
			quarter_divisions = 1000;
		}


		/**
		 * Set the quarter duration parameter.
		 *
		 * \param d duration of a quarter note in microseconds.
		 */
		void set_quarter_duration(const microseconds & d) {
			if (d <= microseconds(0))
				BOOST_THROW_EXCEPTION(std::range_error("duration must be positive"));
			quarter_duration = d;
		}

		/**
		 * Get the quarter duration.
		 *
		 *
		 * \return quarter duration in microseconds.
		 */
		constexpr microseconds get_quarter_duration() const { return quarter_duration; }

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
		constexpr ticktype get_ticks() { return quarter_divisions; }

#if 0

		/** Translates a given number of MIDI quarter ticks into microseconds.
		 * Rounding is done according to the formula given in the midi standard:
		 * time = ticks * (quarter_duration / ticks per quarter)
		 *
		 * \param d time in quarter divisions
		 *
		 * \return time in microseconds.
		 */
		constexpr microseconds get_time_midi(miditicks d) const {
			return d.midi_mus();
		}

		/** Translates a given number of quarter ticks into microseconds using more exact rounding.
		 * Rounding is done according to the following formula (in integer arithmetic):
		 * time = round ((ticks * (quarter_duration )) / ticks per quarter)
		 *
		 * \param d time in quarter divisions
		 *
		 * \return time in microseconds.
		 */
		constexpr microseconds get_time_exact(miditicks d) const {
			return d.mus();
		}

		/** Translates a given time in microseconds into the corresponding number of MIDI.
		 * Rounding is done to meet the formula given in the midi standard:
		 * time = ticks * (quarter_duration / ticks per quarter)
		 *
		 * \param time time in microseconds.
		 *
		 * \return time in quarter divisions
		 */
		constexpr miditicks get_delta_midi(microseconds time) {
#if 0
			ticktype factor = is_fixed_ticks?
				1000000/quarter_divisions:
				quarter_duration.count()/quarter_divisions;


			// The calculation should round for 25 fps 40 subframes correctly microseconds to milliseconds
			// if in daubt: round up as time calculation rounds down.
			return (2 * time.count() + factor + 1) / (2 * factor);
#else
			return miditicks(time, *this, true);
#endif
		}

		/** Translates a given time in microseconds into number of quarter ticks using more exact rounding.
		 * Rounding is done to meet following formula (in integer arithmetic):
		 * time = round ((ticks * (quarter_duration )) / ticks per quarter)
		 *
		 * \param time time in microseconds.
		 *
		 * \return  time in quarter divisions
		 */
		constexpr miditicks get_delta_exact(microseconds time) {
#if 0
			return is_fixed_ticks?
				(time.count() * quarter_divisions + 500000) / 1000000:
				(time.count() * quarter_divisions + (quarter_duration.count()+1)/2)
				/ quarter_duration.count();
#else
			return miditicks(time, *this, false);
#endif
		}
#endif

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
		static microseconds update_duration_midi(microseconds duration,
							 const timing_params & oldd,
							 const timing_params & newd) {
			if ((oldd.is_fixed_ticks && newd.is_fixed_ticks)
			    || duration == microseconds::max()) return duration;
			ticktype old_quarter = oldd.is_fixed_ticks ? 1000000 : oldd.quarter_duration.count();
			ticktype new_quarter = newd.is_fixed_ticks ? 1000000 : newd.quarter_duration.count();
			ticktype old_factor = old_quarter/oldd.quarter_divisions;
			ticktype new_factor = new_quarter/newd.quarter_divisions;

			return microseconds(((duration.count() + (old_factor+1)/2) / old_factor) * new_factor);
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
		static microseconds update_duration_exact(microseconds duration,
							  const timing_params & oldd,
							  const timing_params & newd) {
			if ((oldd.is_fixed_ticks && newd.is_fixed_ticks)
			    || duration == microseconds::max()) return duration;
			ticktype old_quarter = oldd.is_fixed_ticks ? 1000000 : oldd.quarter_duration.count();
			ticktype new_quarter = newd.is_fixed_ticks ? 1000000 : newd.quarter_duration.count();
			ticktype delta_quarter = new_quarter - old_quarter;
			ticktype duration_count = duration.count();
			if (delta_quarter > 0) {
				duration_count = (duration_count * new_quarter)/old_quarter;
			}
			if (oldd.quarter_divisions != newd.quarter_divisions) {
				duration_count = (duration_count * oldd.quarter_divisions)/newd.quarter_divisions;
			}
			if (delta_quarter < 0) {
				duration_count = (duration_count * new_quarter)/old_quarter;
			}
			return microseconds(duration_count);

		}

		constexpr bool operator != (timing_params & o) {
			return  (this != &o) &&
				(is_fixed_ticks != o.is_fixed_ticks ||
				 fps != o.fps ||
				 quarter_duration != o.quarter_duration ||
				 quarter_divisions != o.quarter_divisions);

		}

		operator std::string() const;
	protected:
		bool is_fixed_ticks;       //< indicates whether we are in MIDI time code and ignore quarter_duration
		int fps;                   //< fps rate
		microseconds quarter_duration; //< duration of quarter notes in μs
		ticktype quarter_divisions; //< divisions of quarter notes
 	};

	inline std::string str(const timing_params & t) { return t; }

	inline std::ostream & operator << (std::ostream & o, const timing_params & t) {
		return o << str(t);
	}

	inline std::ostream & operator << (std::ostream & o, const timing_params::miditicks &m ) {
		return m.write(o);
	}

#if _XOPEN_SOURCE >= 600 || _POSIX_C_SOURCE >= 200112L
	class CurrentTimerBase: public boost::chrono::high_resolution_clock {
	public:
		typedef boost::chrono::high_resolution_clock base;
		typedef base::duration duration;
		typedef base::rep rep;
		typedef base::period period;
		typedef base::time_point time_point;

		CurrentTimerBase():running(false) {
		}
#if 0
		static void Sleep(mutint64 time) {
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
#ifdef DEBUG
			int status =
#endif
				clock_nanosleep(CLOCK_MONOTONIC,0,&data,&remain);
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
#endif
	protected:
		time_point start;
#if 0
		period resolution;
#endif
		bool running;

		void Start(const time_point & t) {
			start = t;
			running = true;
		}

		void Start(const duration & d) {
#if 0
			//clock_getres(CLOCK_MONOTONIC,&resolution);
#endif
			start = now() - d;
			DEBUGLOGTYPE(timer,
				     CurrentTimerBase,
				     ("Starting time: %s"),
				     boost::lexical_cast<std::string>(start).c_str());
			running=true;
		}

#if 0
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
#endif
		time_point Time() {
			if (!running)
				return time_point();
			return now();
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
		typedef CurrentTimerBase base;
		typedef base::duration duration;
		typedef base::rep rep;
		typedef base::period period;
		typedef base::time_point time_point;

		/**
		 * Constructor starting the time at a given parameter.
		 *
		 * \param t start time
		 */
		CurrentTimer(const duration & d = duration(0)):CurrentTimerBase() {
			Start(d);
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
				Start(duration(0));
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
		 * \param duration time in μs.
		 */
		void Set(const duration & d = duration(0)) {
			if (is_realtime) {
				Start(d);
			} else {
				time = time_point() + d;
			}
		}

		/**
		 * Set the current time.
		 *
		 * \param t time point.
		 */
		void Set(const time_point & t) {
			if (is_realtime) {
				Start(t);
			} else {
				time = t;
			}
		}

		/**
		 * Reset the current time to epoch.
		 */
		void Reset() {
			if (is_realtime)
				Start(duration(0));
			else {
				time = time_point();
			}
		}

		/**
		 * Return the current time in μs.
		 *
		 *
		 * \return Time in μs.
		 */
		time_point Get() { return is_realtime?Time():time; }

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
		CurrentTimer& operator = (const time_point & t) {
			Set(t);
			return * this;
		}

		/**
		 * Assign a time value.
		 *
		 * \param t time in μs.
		 *
		 * \return reference to self.
		 */
		CurrentTimer& operator = (const duration & d) {
			Set(d);
			return * this;
		}

		/**
		 * Increment a time value in batch mode.
		 *
		 * \param t time to add to the current time.
		 *
		 * \return reference to self.
		 */
		CurrentTimer& operator += (const duration & t) {
			mutASSERT(!is_realtime);
			time += t;
			return * this;
		}


		/**
		 * Sleep for a given time of microsecounds.
		 * The sleep can be interupted by a signal from another thread.
		 *
		 * \param time time to sleep
		 * \param condition the condition that can be used to wake the thread up
		 *
		 * \return a status information frem the thread.
		 */
		template<class T, class M>
		typename ThreadCondition<M>::status Sleep(boost::unique_lock<boost::mutex> & lock,
							  T & t,
							  ThreadCondition<M> & condition) {
			return condition.Sleep(lock,t);
		}

				/**
		 * Sleep for a given time of microsecounds.
		 * The sleep can be interupted by a signal from another thread.
		 *
		 * \param time time to sleep
		 * \param condition the condition that can be used to wake the thread up
		 *
		 * \return a status information frem the thread.
		 */
		template<class T, class S, class M>
		typename ThreadCondition<M>::status Sleep(T & time,
							   ThreadSignal<S,M> & signal) {
			if (time < boost::chrono::steady_clock::now())
				return ThreadCondition<M>::status::wakeup;
			else {
				boost::unique_lock<boost::mutex> lock(signal.get_mutex());
				return (typename ThreadCondition<M>::status)
					signal.get_condition().wait_until(lock, time);
			}
		}

		//using CurrentTimerBase::Sleep;
	protected:
		time_point time; //< Time value for batch mode
		bool is_realtime; //< flag indicating whether we are in batch mode.

	};

	extern CurrentTimer CurrentTime;

	inline CurrentTimer::duration operator - (const CurrentTimer::time_point & a,
						  const CurrentTimer::time_point & b) {
		return a.time_since_epoch() - b.time_since_epoch();
	}
}
#endif // precompiled
#endif // header loaded


///\}

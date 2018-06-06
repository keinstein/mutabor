/** \file               -*- C++ -*-
 ********************************************************************
 * Thread wrapper classses.
 *
 * We need some abstraction for the thread library. So we do not
 * depend on a special GUI library. In particular this file provides
 * some imitation of the wxThread class from wxWidgets 2.8 which has
 * been used as first thread implementation.
 *
 * wxThread binds to wxWidgets so we could not easily use the library
 * with different GUIs like Juce, e.g. for buildinge a VST plugin.
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
// availlable groups: GUI, route, kernel, muwx, debug, docview, config, docview

/* we guard a little bit complicated to ensure the references are set right
 */

#if (!defined(SRC_KERNEL_ROUTING_THREAD_H) && !defined(PRECOMPILE)) \
	|| (!defined(SRC_KERNEL_ROUTING_THREAD_H_PRECOMPILED))
#ifndef PRECOMPILE
#define SRC_KERNEL_ROUTING_THREAD_H
#endif

// ---------------------------------------------------------------------------
// headers
// ---------------------------------------------------------------------------

#include "src/kernel/Defs.h"
#include "boost/thread.hpp"
#include "boost/atomic.hpp"
#include "boost/lexical_cast.hpp"

#ifndef SRC_KERNEL_ROUTING_THREAD_H_PRECOMPILED
#define SRC_KERNEL_ROUTING_THREAD_H_PRECOMPILED

// system headers which do seldom change

#ifdef MUTABOR_WX_THREAD
#include "wx/thread.h"
namespace mutabor {
	// see CommonFileDevice for usage
	typedef wxThread      Thread;
	typedef wxThreadKind  ThreadKind;
	typedef wxMutexLocker ScopedLock;
	typedef wxMutexError  ThreadResult;
	typedef wxCondError   WaitResult;
#ifdef DEBUG
	class Mutex: public wxMutex {
	public:
		Mutex(wxMutexType mutexType = wxMUTEX_DEFAULT):wxMutex(mutexType) {}
		~Mutex() {}
		wxMutexError Lock() {
			if (debugmutex.m_internal == m_internal) return wxMutex::Lock();
			wxMutexError error = wxMutex::TryLock();
			if (error != wxMUTEX_NO_ERROR) {
				DEBUGLOG(thread,
					 ("Thread %s waiting for mutex %p."),
					 Thread::get_current_string_id().c_str(),
					 m_internal);
				error = wxMutex::Lock();
			}
			DEBUGLOG(thread,
				 ("Thread %s locking result for mutex %p (%s)."),
				 Thread::get_current_string_id().c_str(),
				 m_internal,
				 str_error(error));
			mutASSERT(error == wxMUTEX_NO_ERROR);
			return error;
		}

		wxMutexError Unlock() {
			wxMutexError error = wxMutex::Unlock();
			if (debugmutex.m_internal == m_internal) return error;
			DEBUGLOG(thread,
				 ("Thread %s unlocking mutex %p (%s)."),
				 Thread::get_current_string_id().c_str(),
				 m_internal,
				 str_error(error));
			mutASSERT(error == wxMUTEX_NO_ERROR);
			return error;
		}

		wxMutexError TryLock() {
			wxMutexError error = wxMutex::TryLock();
			if (debugmutex.m_internal == m_internal) return error;
			DEBUGLOG(thread,
				 ("Thread %s trying to lock mutex %p (%s)."),
				 Thread::get_current_string_id().c_str(),
				 m_internal,
				 str_error(error));
			mutASSERT(error == wxMUTEX_NO_ERROR || error == wxMUTEX_BUSY);
			return error;
		}

		wxMutexError LockTimeout(unsigned long ms) {
			wxMutexError error = wxMutex::LockTimeout(ms);
			if (debugmutex.m_internal == m_internal) return error;
			DEBUGLOG(thread,
				 ("Thread %s trying to lock mutex %p for %lu ms (%s)."),
				 Thread::get_current_string_id().c_str(),
				 m_internal,
				 ms,
				 str_error(error));
			mutASSERT(error == wxMUTEX_NO_ERROR || error == wxMUTEX_TIMEOUT);
			return error;
		}

		const char * str_error (wxMutexError error) {
			static const char * s[] = {
				"ok",
				"uninitialized mutex",
				"we already own this mutex",
				"another thread owns this mutex",
				"unlocking an unlocked mutex",
				"timeout",
				"other error"
			};
			if (error > 6 || error < 0) return "unknown error";
			else return s[error];
		}
	};
#else
	typedef wxMutex       Mutex;
#endif

	class ScopedUnlock {
	public:
		ScopedUnlock(Mutex & m):mutex(m) {
			mutex.Unlock();
		}
		~ScopedUnlock() {
			mutex.Lock();
		}
	protected:
		Mutex & mutex;
	};

	class ThreadCondition:public wxCondition {
	public:
		ThreadCondition(Mutex &m):wxCondition(m) {}
		WaitResult Sleep(mutint64 time)
		{
			return WaitTimeout(time/1000);
		}
	};

	template<bool dolock>
	class ScopedCondLock: public ScopedLock
	{
	public:
		ScopedCondLock(Mutex & m):ScopedLock(m) {}
		// nothing
	};

	template<>
	struct ScopedCondLock<false> {
		ScopedCondLock(const Mutex) {}
	};


	template<class T>
	class safe_integer {
	public:
		typedef T datatype;
		safe_integer(datatype d):data(d),mutex() {}
		safe_integer(const safe_integer & o):mutex() {
			ScopedLock l1(mutex), l2(o.mutex);
			data = o.data;
		}
		safe_integer(safe_integer & o):mutex() {
			ScopedLock l1(mutex), l2(o.mutex);
			data = o.data;
		}
		safe_integer(volatile safe_integer & o):mutex() {
			ScopedLock l1(mutex), l2(const_cast<safe_integer&>(o).mutex);
			data = o.data;
		}
		safe_integer & operator = (const safe_integer & other) {
			ScopedLock l1(mutex), l2(other.mutex);
			data = other.data;
			return *this;
		}
		safe_integer & operator |= (const safe_integer & other) {
			ScopedLock l1(mutex), l2(other.mutex);
			data |= other.data;
			return *this;
		}
		safe_integer & operator &= (const safe_integer & other) {
			ScopedLock l1(mutex), l2(other.mutex);
			data &= other.data;
			return *this;
		}

		safe_integer & operator = (const datatype & other) {
			ScopedLock l1(mutex);
			data = other;
			return *this;
		}
		safe_integer & operator |= (const datatype & other) {
			ScopedLock l1(mutex);
			data |= other;
			return *this;
		}
		safe_integer & operator &= (const datatype  & other) {
			ScopedLock l1(mutex);
			data &= other;
			return *this;
		}
		operator datatype () {
			ScopedLock l1(mutex);
			return data;
		}
		datatype get()  {
			ScopedLock l1(mutex);
			return data;
		}

	protected:
		volatile datatype data;
		Mutex mutex;
        };
}
#define MUTABOR_THREAD_OK wxMUTEX_NO_ERROR
#else
MUTABOR_NAMESPACE(mutabor)

enum  ThreadKind {};

template<class M=boost::mutex>
class ScopedLock: public boost::unique_lock<M> {
public:
	typedef boost::unique_lock<M> base;
	typedef M mutex_type;
	ScopedLock(mutex_type & m):base(m) {}
	~ScopedLock() {}
	constexpr operator base&() {
		return static_cast<base &>(*this);
	}
};
typedef int ThreadResult;
typedef int  WaitResult;

template <class M = boost::mutex> class Mutex;
#if DEBUG
extern Mutex<> debugmutex;
#endif

template <class M>
class Mutex: public M  {
public:
	typedef M base;
	Mutex():base() {}
	~Mutex() {}
	void Lock() {
#if DEBUG
		if (debugmutex.native_handle() == this->native_handle()) {
			this->lock();
			return;
		}
		debug_print_thread_mutex
			 ("Thread %s waiting for mutex %s.");
		if (!this->try_lock()) {
			debug_print_thread_mutex
				("Thread %s waiting for mutex %s.");
			this->lock();
		}
#else
		this->lock();
#endif
	}

	void Unlock() {
		this->unlock();
#if DEBUG
		if (debugmutex.native_handle() == this->native_handle()) return;
		debug_print_thread_mutex
			 ("Thread %s unlocked mutex %s.");
#endif
	}

	bool TryLock() {
		bool error = this->try_lock();
#if DEBUG
		if (debugmutex.native_handle() == this->native_handle()) return error;
		if (error)
			debug_print_thread_mutex
				("Thread %s trying to lock mutex %s. (ok)");
		else
			debug_print_thread_mutex
				("Thread %s trying to lock mutex %s. (fail)");
#endif
		return error;
	}
#if 0
	wxMutexError LockTimeout(unsigned long ms) {
		wxMutexError error = wxMutex::LockTimeout(ms);
		if (debugmutex.m_internal == m_internal) return error;
		DEBUGLOG(thread,
			 ("Thread %s trying to lock mutex %p for %lu ms (%s)."),
			 Thread::get_current_id().c_str(),
			 m_internal,
			 ms,
			 str_error(error));
		mutASSERT(error == wxMUTEX_NO_ERROR || error == wxMUTEX_TIMEOUT);
		return error;
	}

	const char * str_error (wxMutexError error) {
		static const char * s[] = {
			"ok",
			"uninitialized mutex",
			"we already own this mutex",
			"another thread owns this mutex",
			"unlocking an unlocked mutex",
			"timeout",
			"other error"
		};
		if (error > 6 || error < 0) return "unknown error";
		else return s[error];
	}
#endif
	std::string get_string_handle() {
		return boost::lexical_cast<std::string>(this->native_handle());
	}

#if DEBUG
	void debug_print_thread_mutex(const char * s);
#endif
};

template <class M = boost::mutex>
class ScopedUnlock {
public:
	ScopedUnlock(M & m):mutex(m) {
		mutex.Unlock();
	}
	~ScopedUnlock() {
		mutex.Lock();
	}
protected:
	M & mutex;
};


template <class M = boost::mutex>
class ThreadCondition:public boost::condition_variable {
public:

	typedef boost::condition_variable  base;

	enum class status  {
 		wakeup = (char) boost::cv_status::no_timeout,
		timeout = (char) boost::cv_status::timeout
	};
	ThreadCondition(Mutex<M> &m):base(),mutex(m) {}


	void Wait(boost::unique_lock<boost::mutex> & lock) {
		wait(lock);
	}

	void Broadcast() {
		notify_all();
	}

	template<class T>
	status Sleep(boost::unique_lock<boost::mutex> &lock,
		     const T & time)
	{
		if (time < boost::chrono::steady_clock::now())
			return status::wakeup;
		else
			return (status)wait_until(lock, time);
	}
protected:
	Mutex<M> & mutex;
};

template<bool dolock, class M = boost::mutex>
class ScopedCondLock: public ScopedLock<M>
{
public:
	typedef ScopedLock<M> base;
	ScopedCondLock(Mutex<M> & m):base(m) {}
	// nothing
};

template<class M>
struct ScopedCondLock<false, M> {
	ScopedCondLock(const Mutex<M>) {}
};


template<class T,class M = boost::mutex, class C = boost::condition_variable>
class ThreadSignal: public boost::atomic<T> {
public:
	typedef T data_type;
	typedef M mutex_type;
	typedef C condition_type;

	typedef boost::atomic<data_type> base;

	ThreadSignal():base(),
		       mutex(),
		       condition() {
	}

	ThreadSignal(data_type & d):base(d),
				    mutex(),
				    condition() {
	}

	ThreadSignal(data_type && d):base(d),
				     mutex(),
				     condition() {
	}

	~ThreadSignal() {
#if DEBUG
		if (!mutex.try_lock()) {
			assert(false);
		} else mutex.unlock();
#endif
	}

	void wait_for_data(const data_type & d) {
		ScopedLock<mutex_type> lock(mutex);
		while (*this != d)
			condition.wait(lock);
	}

	void wait(ScopedLock<mutex_type> & lock) {
		condition.wait(lock);
	}

	base &  wait_for_data_change(const data_type & d,
					  ScopedLock<mutex_type> & lock) {
		while (*this == d)
			condition.wait(lock);
		return static_cast<base &>(*this);
	}

	data_type &  wait_for_data_change(const data_type & d) {
		ScopedLock<mutex_type> lock(mutex);
		return wait_for_data_change(d, lock);
	}

	data_type & wait_for_data_change() {
		data_type d = static_cast<data_type &>(*this);
		return wait_for_data_change(d);
	}

	void notify_all () {
		condition.notify_all();
	}

	void notify_one() {
		condition.notify_one();
	}

	mutex_type & get_mutex() {
		return mutex;
	}

	condition_type & get_condition() {
		return condition;
	}
protected:
	mutex_type     mutex;
	condition_type condition;
};


// see CommonFileDevice for usage
class Thread {
public:
	enum thread_state {
		thread_initializing,
		thread_initialized,
		thread_running,
		thread_ending,
		thread_finished
	};

	class meeting_point {
	public:
		enum {
			locked_master=1,
			locked_slave=2,
			unlocked_first=4,
			unlocked_secound=8,
			locked_mask = locked_master | locked_slave,
			unlocked_mask = unlocked_first | unlocked_secound
		};
		meeting_point():sync_condition() {
			locked = 0;
		}

		void sync(int role,
			  boost::unique_lock<boost::mutex> & lock) {
			// We must ensure that subsequent syncronisation
			// points do not interfere with each other.
			while (locked & unlocked_mask) {
				sync_condition.wait(lock);
			}
			locked |= role;
			if ((locked & locked_mask) == locked_mask) {
				locked |= (unlocked_mask &  ~(int) unlocked_secound);
			} else {
				while (!(locked & unlocked_mask)) {
					sync_condition.wait(lock);
				}
				locked &= ~(int) unlocked_first;
			}
			locked &= ~role;
			sync_condition.notify_all();
		}

	protected:
		boost::condition_variable sync_condition;
		boost::atomic<int> locked;
	};

	Thread():command(thread_initializing),
		 state(thread_initializing),
		 sync_mutex(),
		 sync(),
		 thread(boost::ref(*this)) {
		{
			boost::unique_lock<boost::mutex> lock(sync_mutex);
			command = thread_initialized;
			sync.sync(meeting_point::locked_master,
				  lock);
		}
	}
	virtual ~Thread() {}

	void operator()() {
		{
			boost::unique_lock<boost::mutex> lock(sync_mutex);
			state = thread_initialized;
			sync.sync(meeting_point::locked_slave,
				  lock);
			sync.sync(meeting_point::locked_slave,
				  lock);
			state = thread_running;
		}
		exitcode = Entry();
		state = thread_ending;
		OnExit();
		state = thread_finished;
	}

	virtual int Entry() = 0;
	virtual void OnExit() {}


	bool IsDetached() {
		return !thread.joinable();
	}

	void Run() {
		boost::unique_lock<boost::mutex> lock(sync_mutex);
		command = thread_running;
		sync.sync(meeting_point::locked_master,
			  lock);
	}

	void interrupt() {
		thread.interrupt();
	}

	int Wait() {
		thread.join();
		return exitcode;
	}

	bool TestDestroy() {
		return boost::this_thread::interruption_requested() && boost::this_thread::interruption_enabled();
	}

	boost::thread::id get_id() {
		return thread.get_id();
	}

	static boost::thread::id get_current_id() {
		return boost::this_thread::get_id();
	}

	static std::string get_current_string_id() {
		return boost::lexical_cast<std::string>(boost::this_thread::get_id());
	}
protected:
	boost::atomic<thread_state> command;
	boost::atomic<thread_state> state;
	Mutex<> sync_mutex;
	meeting_point sync;
	boost::thread thread;
	int exitcode;
};


template<class T>
class safe_integer {
public:
	typedef T datatype;
	safe_integer(datatype d):data(d),mutex() {}
	safe_integer(const safe_integer & o):mutex() {
		ScopedLock<> l1(mutex), l2(o.mutex);
		data = o.data;
	}
	safe_integer(safe_integer & o):mutex() {
		ScopedLock<> l1(mutex), l2(o.mutex);
		data = o.data;
	}
	safe_integer(volatile safe_integer & o):mutex() {
		ScopedLock<> l1(mutex), l2(const_cast<safe_integer&>(o).mutex);
		data = o.data;
	}
	safe_integer & operator = (const safe_integer & other) {
		ScopedLock<> l1(mutex), l2(other.mutex);
		data = other.data;
		return *this;
	}
	safe_integer & operator |= (const safe_integer & other) {
		ScopedLock<> l1(mutex), l2(other.mutex);
		data |= other.data;
		return *this;
	}
	safe_integer & operator &= (const safe_integer & other) {
		ScopedLock<> l1(mutex), l2(other.mutex);
		data &= other.data;
		return *this;
	}

	safe_integer & operator = (const datatype & other) {
		ScopedLock<> l1(mutex);
		data = other;
		return *this;
	}
	safe_integer & operator |= (const datatype & other) {
		ScopedLock<> l1(mutex);
		data |= other;
		return *this;
	}
	safe_integer & operator &= (const datatype  & other) {
		ScopedLock<> l1(mutex);
		data &= other;
		return *this;
	}
	operator datatype () {
		ScopedLock<> l1(mutex);
		return data;
	}
	datatype get()  {
		ScopedLock<> l1(mutex);
		return data;
	}

protected:
	volatile datatype data;
	Mutex<> mutex;
};
MUTABOR_NAMESPACE_END(mutabor)
#endif


#endif // precompiled
#endif // header loaded


///\}

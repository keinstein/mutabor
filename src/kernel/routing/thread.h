/** \file               -*- C++ -*-
 ********************************************************************
 * Thread wrapper classses.
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

#ifndef SRC_KERNEL_ROUTING_THREAD_H_PRECOMPILED
#define SRC_KERNEL_ROUTING_THREAD_H_PRECOMPILED

// system headers which do seldom change

#ifdef WX
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
					 ("Thread %p waiting for mutex %p."),
					 Thread::This(),
					 m_internal);
				error = wxMutex::Lock();
			}
			DEBUGLOG(thread,
				 ("Thread %p locking result for mutex %p (%s)."),
				 Thread::This(),
				 m_internal,
				 str_error(error));
			mutASSERT(error == wxMUTEX_NO_ERROR);
			return error;
		}

		wxMutexError Unlock() {
			wxMutexError error = wxMutex::Unlock();
			if (debugmutex.m_internal == m_internal) return error;
			DEBUGLOG(thread,
				 ("Thread %p unlocking mutex %p (%s)."),
				 Thread::This(),
				 m_internal,
				 str_error(error));
			mutASSERT(error == wxMUTEX_NO_ERROR);
			return error;
		}

		wxMutexError TryLock() {
			wxMutexError error = wxMutex::TryLock();
			if (debugmutex.m_internal == m_internal) return error;
			DEBUGLOG(thread,
				 ("Thread %p trying to lock mutex %p (%s)."),
				 Thread::This(),
				 m_internal,
				 str_error(error));
			mutASSERT(error == wxMUTEX_NO_ERROR || error == wxMUTEX_BUSY);
			return error;
		}

		wxMutexError LockTimeout(unsigned long ms) {
			wxMutexError error = wxMutex::LockTimeout(ms);
			if (debugmutex.m_internal == m_internal) return error;
			DEBUGLOG(thread,
				 ("Thread %p trying to lock mutex %p for %lu ms (%s)."),
				 Thread::This(),
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
#endif


#endif // precompiled
#endif // header loaded


///\}

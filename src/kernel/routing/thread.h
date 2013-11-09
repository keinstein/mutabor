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
 * \addtogroup templates
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
	typedef wxMutex       Mutex;
	typedef wxMutexLocker ScopedLock;
	typedef wxMutexError  ThreadResult;
	typedef wxCondition   ThreadCondition;

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

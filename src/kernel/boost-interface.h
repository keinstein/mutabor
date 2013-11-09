/** \file 
 ********************************************************************
 * Interface to the boost library
 *
 * Copyright:   (c) 2008-2011 TU Dresden
 *              changes after 2011-11 (c) by the authors
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
 * \addtogroup kernel
 * \{
 ********************************************************************/
// prevent double inclusion

/* we guard a little bit complicated to ensure the references are set right
 */

#if (!defined(SRC_KERNEL_BOOST_INTERFACE_H) && !defined(PRECOMPILE)) \
	|| (!defined(SRC_KERNEL_BOOST_INTERFACE_H_PRECOMPILED))
#ifndef PRECOMPILE
#define SRC_KERNEL_BOOST_INTERFACE_H
#endif

// ---------------------------------------------------------------------------
// headers
// ---------------------------------------------------------------------------

#include "src/kernel/Defs.h"
#include "src/kernel/routing/thread.h"

#ifndef SRC_KERNEL_BOOST_INTERFACE_H_PRECOMPILED
#define SRC_KERNEL_BOOST_INTERFACE_H_PRECOMPILED

// system headers which do seldom change

#include "src/kernel/Defs.h"

template<bool locking=1>
class intrusive_ptr_refcount_type {
public:
	typedef mutabor::ScopedCondLock<locking> locker;
	intrusive_ptr_refcount_type():value(0) {}
	
	void lock () {
		if (locking)
			mutex.Lock();
	}

	void unlock () {
		if (locking)
			mutex.Unlock();
	}

	size_t operator ++() {
		locker lock(mutex);
		return ++value;
	}

	size_t operator ++(int) {
		locker lock(mutex);
		return value++;
	}

	size_t operator --() {
		locker lock(mutex);
		return --value;
	}

	size_t operator --(int) {
		locker lock(mutex);
		return value--;
	}

	operator size_t () const {
		locker lock(const_cast<intrusive_ptr_refcount_type *>(this)->mutex);
		return value;
	}
private:
        volatile size_t value;
	mutabor::Mutex mutex;

	template<class intrusive_ptr_T>
		friend void intrusive_ptr_add_ref(intrusive_ptr_T * obj);	
	template<class intrusive_ptr_T>
		friend void intrusive_ptr_release(intrusive_ptr_T * obj);
	template <class intrusive_ptr_T>
		friend size_t intrusive_ptr_get_refcount(intrusive_ptr_T * obj);
};			

template <class intrusive_ptr_T>
inline size_t intrusive_ptr_get_refcount(intrusive_ptr_T * obj)
{
	if (!obj) return 0;
	return obj->intrusive_ptr_refcount;
}

template <class intrusive_ptr_T>
inline void intrusive_ptr_add_ref(intrusive_ptr_T * obj)
{
	if (!obj) return;
	++(obj->intrusive_ptr_refcount);
	DEBUGLOGTYPE(smartptr,*obj,_T("Incrementing %p to %d"),
		     (void *)obj,(int)intrusive_ptr_get_refcount(obj));
}

template <class intrusive_ptr_T>
inline void intrusive_ptr_release(intrusive_ptr_T * obj)
{
	if (!obj) return;
	DEBUGLOGTYPE(smartptr,*obj,_T("Decrementing %p from %d"),
		     (void *)obj,(int)intrusive_ptr_get_refcount(obj));
	if (!(--(obj->intrusive_ptr_refcount))) delete obj;
}

							      
#define REFPTR_INTERFACE						\
	public:								\
	intrusive_ptr_refcount_type<true> intrusive_ptr_refcount

#define REFPTR_INTERFACE_NOLOCK						\
	public:								\
	intrusive_ptr_refcount_type<false> intrusive_ptr_refcount


#define CHECK_REFPTR_NULL(class_data)				\
	mutASSERT(intrusive_ptr_get_refcount(class_data) <= 1);


#endif /* SRC_KERNEL_BOOST_INTERFACE_H_PRECOMPILED */
#endif /* SRC_KERNEL_BOOST_INTERFACE_H */




///\}

// Local Variables:
// mode: c++
// End:

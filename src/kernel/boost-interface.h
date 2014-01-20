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
// boost/intrusive_ptr.hpp can be included only after the refcounting is defined

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
	// print_stacktrace(isDebugFlag(smartptr));
}

template <class intrusive_ptr_T>
inline void intrusive_ptr_release(intrusive_ptr_T * obj)
{
	if (!obj) return;
	DEBUGLOGTYPE(smartptr,*obj,_T("Decrementing %p from %d"),
		     (void *)obj,(int)intrusive_ptr_get_refcount(obj));
	//	print_stacktrace(isDebugFlag(smartptr));
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

#include "boost/intrusive_ptr.hpp"

#ifdef DEBUG
namespace boost {
	namespace mutabor {
		template<typename T>
		class intrusive_ptr:public ::boost::intrusive_ptr<T> {
		public:
			typedef T element_type;
			typedef intrusive_ptr<T> this_type;
			typedef ::boost::intrusive_ptr<T> base;

			intrusive_ptr() : base(),
					  backtrace(1)
			{
				DEBUGLOG(smartptr,_T("Creating %p (@ %p)"),
					 this,
					 (void *)backtrace.front());
			}

			intrusive_ptr( T * p, bool add_ref = true ):
				base(p,add_ref),
				backtrace(1)
			{
				DEBUGLOG(smartptr,_T("Creating %p (@ %p)"),
					 this,
					 (void *)backtrace.front());
				DEBUGLOG(smartptr,_T("New value %p -> %p"),this,this->get());
			}

#if !defined(BOOST_NO_MEMBER_TEMPLATES) || defined(BOOST_MSVC6_MEMBER_TEMPLATES)

			template<class U>
#if !defined( BOOST_SP_NO_SP_CONVERTIBLE )

			intrusive_ptr( intrusive_ptr<U> const & rhs,
				       typename boost::detail::sp_enable_if_convertible<U,T>::type t
				       = boost::detail::sp_empty() ):
				base(rhs,t),
				backtrace(1)
#else

				intrusive_ptr( intrusive_ptr<U> const & rhs ):
				base(rhs),
				backtrace(1)
#endif
			{
				DEBUGLOG(smartptr,_T("Creating %p (@ %p)"),
					 this,
					 (void *)backtrace.front());
				DEBUGLOG(smartptr,_T("New value %p -> %p"),
					 this,this->get());
			}

#endif

			intrusive_ptr(intrusive_ptr const & rhs):
				base(rhs ),
				backtrace(1)

			{
				DEBUGLOG(smartptr,_T("Creating %p (@ %p)"),
					 this,
					 (void *)backtrace.front());
				DEBUGLOG(smartptr,
					 _T("New value %p -> %p"),
					 this,this->get());
			}

			~intrusive_ptr() {
				void * ptr = NULL;
				DEBUGLOG(smartptr,
					 _T("Destroying %p -> %p (NULL=“%p”, @ %p)"),
					 this,
					 this->get(),
					 ptr,
					 (void *)backtrace.front());

				if ((*this))
					backtrace.set_print(false);
				// print_stacktrace(isDebugFlag(smartptr));
			}


			template<class U>
			intrusive_ptr & operator=(U const & rhs)
			{
				if (backtrace.get_global_print())
					backtrace.set_print();
				base::operator=(rhs);
				DEBUGLOG(smartptr,_T("New value %p -> %p"),
					 this,this->get());
				return *this;
			}

			// Move support

#if !defined( BOOST_NO_CXX11_RVALUE_REFERENCES )

			intrusive_ptr(intrusive_ptr && rhs) BOOST_NOEXCEPT :
			        base( rhs ),
				backtrace(1)

			{
				DEBUGLOG(smartptr,_T("Creating %p (@ %p)"),
					 this,
					 (void *)backtrace.front());
				DEBUGLOG(smartptr,_T("New value %p -> %p"),
					 this,this->get());
			}

#endif

			void reset() BOOST_NOEXCEPT
			{
				base::reset();
				DEBUGLOG(smartptr,_T("New value %p -> %p"),this,this->get());
			}

			void reset( T * rhs )
			{
				base::reset(rhs);
				DEBUGLOG(smartptr,_T("New value %p -> %p"),this,this->get());
			}

			T & operator*() const
			{
				return base::operator*();
			}

			T * operator->() const
			{
				return base::operator->();
			}

			operator bool() {
				return *static_cast<base *>(this);
			}

			void swap(intrusive_ptr & rhs) BOOST_NOEXCEPT
			{
				base::swap(rhs);
				DEBUGLOG(smartptr,_T("New value %p -> %p"),this,this->get());
				DEBUGLOG(smartptr,_T("New value %p -> %p"),&rhs,rhs.get());
			}

			void print_backtrace() {
				backtrace.set_print();
			}
		protected:
			mutabor_backtrace backtrace;


		};
	}
}
#define intrusive_ptr mutabor::intrusive_ptr
#endif

#endif /* SRC_KERNEL_BOOST_INTERFACE_H_PRECOMPILED */
#endif /* SRC_KERNEL_BOOST_INTERFACE_H */




///\}

// Local Variables:
// mode: c++
// End:

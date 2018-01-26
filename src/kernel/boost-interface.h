/** \file
 ********************************************************************
 * Interface to the boost library
 *
 * Copyright:   (c) 2008-2011 TU Dresden
 *              changes after 2011-11 (c) by the authors
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
//#include "src/kernel/routing/thread.h"
// boost/intrusive_ptr.hpp can be included only after the refcounting is defined

#ifndef SRC_KERNEL_BOOST_INTERFACE_H_PRECOMPILED
#define SRC_KERNEL_BOOST_INTERFACE_H_PRECOMPILED

// system headers which do seldom change

#include "src/kernel/Defs.h"
#include <boost/atomic.hpp>



/* Documentation from Boost.Atomic

#include <boost/intrusive_ptr.hpp>

class X {
public:
  typedef boost::intrusive_ptr<X> pointer;
  X() : refcount_(0) {}

private:
  mutable boost::atomic<int> refcount_;
  friend void intrusive_ptr_add_ref(const X * x)
  {
    x->refcount_.fetch_add(1, boost::memory_order_relaxed);
  }
  friend void intrusive_ptr_release(const X * x)
  {
    if (x->refcount_.fetch_sub(1, boost::memory_order_release) == 1) {
      boost::atomic_thread_fence(boost::memory_order_acquire);
      delete x;
    }
  }
};
*/

template<class T>
class atomic_refcount_type {
public:
	atomic_refcount_type():value(0) {}
	atomic_refcount_type(T init):value(init) {}

	T get()
	{
		return value;
	}

	T fetch_add(T number, boost::memory_order order)
	{
		return value.fetch_add(number,order);
	}

	T fetch_sub(T number, boost::memory_order order)
	{
		return value.fetch_sub(number,order);
	}
protected:
	boost::atomic<T> value;
};

template<class T>
class nonatomic_refcount_type {
public:
	nonatomic_refcount_type():value(0) {}
	nonatomic_refcount_type(T init):value(init) {}

	T get()
	{
		return value;
	}

	T fetch_add(T number, boost::memory_order order)
	{
		T retval = value;
		value += number;
		return retval;
	}

	T fetch_sub(T number, boost::memory_order order)
	{
		T retval = value;
		value -= number;
		return retval;
	}
protected:
	T value;
};

template <class intrusive_ptr_T>
inline void intrusive_ptr_atomic_fence(intrusive_ptr_T * mutUNUSED(obj)) {
	boost::atomic_thread_fence(boost::memory_order_acquire);
}

template <>
inline void intrusive_ptr_atomic_fence<nonatomic_refcount_type <int> >(nonatomic_refcount_type <int> * mutUNUSED(obj)) {}

template <class intrusive_ptr_T>
inline size_t intrusive_ptr_get_refcount(intrusive_ptr_T * obj)
{
	if (!obj) return 0;
	return obj->intrusive_ptr_refcount.get();
}

template <class intrusive_ptr_T>
inline void intrusive_ptr_add_ref(intrusive_ptr_T * obj)
{
	if (!obj) return;
	obj->intrusive_ptr_refcount.fetch_add(1,boost::memory_order_relaxed);
	DEBUGLOGTYPE(smartptr,*obj,("Incrementing %p to %d"),
		     (void *)obj,(int)intrusive_ptr_get_refcount(obj));
	// print_stacktrace(isDebugFlag(smartptr));
}

template <class intrusive_ptr_T>
inline void intrusive_ptr_release(intrusive_ptr_T * obj)
{
	if (!obj) return;
	DEBUGLOGTYPE(smartptr,*obj,("Decrementing %p from %d"),
		     (void *)obj,(int)intrusive_ptr_get_refcount(obj));
	//	print_stacktrace(isDebugFlag(smartptr));
	if (obj->intrusive_ptr_refcount.fetch_sub(1, boost::memory_order_release) == 1) {
		intrusive_ptr_atomic_fence(obj);
		delete obj;
	}
}


#define REFPTR_INTERFACE						\
	public:								\
	mutable atomic_refcount_type<int> intrusive_ptr_refcount

#define REFPTR_INTERFACE_NOLOCK						\
	public:								\
	intrusive_ptr_refcount_type<int> intrusive_ptr_refcount


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
				DEBUGLOG (smartptr, "Creating %p (@ %p)" ,
					 this,
					 (void *)backtrace.front());
			}

			intrusive_ptr( T * p, bool add_ref = true ):
				base(p,add_ref),
				backtrace(1)
			{
				DEBUGLOG (smartptr, "Creating %p (@ %p)" ,
					 this,
					 (void *)backtrace.front());
				DEBUGLOG (smartptr, "New value %p -> %p" ,this,this->get());
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
				DEBUGLOG (smartptr, "Creating %p (@ %p)" ,
					 this,
					 (void *)backtrace.front());
				DEBUGLOG (smartptr, "New value %p -> %p" ,
					 this,this->get());
			}

#endif

			intrusive_ptr(intrusive_ptr const & rhs):
				base(rhs ),
				backtrace(1)

			{
				DEBUGLOG (smartptr, "Creating %p (@ %p)" ,
					 this,
					 (void *)backtrace.front());
				DEBUGLOG(smartptr,
					 ("New value %p -> %p"),
					 this,this->get());
			}

			~intrusive_ptr() {
				void * ptr = NULL;
				DEBUGLOG(smartptr,
					 ("Destroying %p -> %p (NULL=“%p”, @ %p)"),
					 this,
					 this->get(),
					 ptr,
					 (void *)backtrace.front());

				if ((*this))
					backtrace.set_print(false);
				// print_stacktrace(isDebugFlag(smartptr));
			}


#if !defined(BOOST_NO_MEMBER_TEMPLATES) || defined(BOOST_MSVC6_MEMBER_TEMPLATES)
			template<class U>
			intrusive_ptr & operator=(intrusive_ptr<U> const & rhs)
			{
				if (backtrace.get_global_print())
					backtrace.set_print();
				base::operator=(rhs);
				DEBUGLOG (smartptr, "New value %p -> %p" ,
					 this,this->get());
				return *this;
			}
#endif

			intrusive_ptr & operator=(intrusive_ptr const & rhs)
			{
				if (backtrace.get_global_print())
					backtrace.set_print();
				base::operator=(static_cast<base const &>(rhs));
				DEBUGLOG (smartptr, "New value %p -> %p" ,
					 this,this->get());
				return *this;
			}

			intrusive_ptr & operator=(T * rhs)
			{
				if (backtrace.get_global_print())
					backtrace.set_print();
				base::operator=(rhs);
				DEBUGLOG (smartptr, "New value %p -> %p" ,
					 this,this->get());
				return *this;
			}




			// Move support

#if !defined( BOOST_NO_CXX11_RVALUE_REFERENCES )

			intrusive_ptr(intrusive_ptr && rhs) BOOST_NOEXCEPT :
			        base( rhs ),
				backtrace(1)

			{
				DEBUGLOG (smartptr, "Creating %p (@ %p)" ,
					 this,
					 (void *)backtrace.front());
				DEBUGLOG (smartptr, "New value %p -> %p" ,
					 this,this->get());
			}

#endif

			void reset() BOOST_NOEXCEPT
			{
				base::reset();
				DEBUGLOG (smartptr, "New value %p -> %p" ,this,this->get());
			}

			void reset( T * rhs )
			{
				base::reset(rhs);
				DEBUGLOG (smartptr, "New value %p -> %p" ,this,this->get());
			}

			T & operator*() const
			{
				return base::operator*();
			}

			T * operator->() const
			{
				return base::operator->();
			}

			explicit operator bool() const BOOST_SP_NOEXCEPT{
				return base::operator bool();
			}

			void swap(intrusive_ptr & rhs) BOOST_NOEXCEPT
			{
				base::swap(rhs);
				DEBUGLOG (smartptr, "New value %p -> %p" ,this,this->get());
				DEBUGLOG (smartptr, "New value %p -> %p" ,&rhs,rhs.get());
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

// -*- C++ -*-

/** \file
********************************************************************
* Copy on write container
*
* \author Tobias Schlemmer <keinstein@users.sourceforge.net>
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
*\addtogroup kernel
*\{
********************************************************************/

/* we guard a little bit complicated to ensure the references are set right
 */

#if (!defined(KERNEL_COW_CONTAINER_H) && !defined(PRECOMPILE))	\
	|| (!defined(KERNEL_COW_CONTAINER_H_PRECOMPILED))
#ifndef PRECOMPILE
#define KERNEL_COW_CONTAINER_H
#endif

// ---------------------------------------------------------------------------
// headers
// ---------------------------------------------------------------------------

#include "src/kernel/Defs.h"
#include "src/kernel/boost-interface.h"

#ifndef KERNEL_COW_CONTAINER_H_PRECOMPILED
#define KERNEL_COW_CONTAINER_H_PRECOMPILED

// system headers which do seldom change

namespace mutabor {
	template<class C>
	class cow_container {
	protected:
		struct container_t:public C {
			typedef C base;
			typedef class base::iterator iterator;
			typedef class base::const_iterator const_iterator;
			REFPTR_INTERFACE;

			container_t():C() {}
			container_t(const container_t & o):C(static_cast<const C&>(o)) {}
			container_t & operator = (const container_t & o) {
				*static_cast<C>(this) = static_cast<const C&>(o);
				return *this;
			}
		};
	public:
		typedef boost::intrusive_ptr<container_t> container_p;
		typedef C base_container;
		typedef cow_container<C> thistype;
		typedef typename base_container::value_type value_type;
		
		typedef typename container_t::reference reference;
		typedef typename container_t::const_reference const_reference;
		typedef typename container_t::pointer pointer;
		typedef typename container_t::const_pointer const_pointer;

		class const_iterator;
		class iterator:public container_t::iterator {
		public:
			typedef typename container_t::iterator base;
			iterator():base(),container() {}
			iterator(container_p & c, base  i):base(i),
							    container(c) {}

			iterator & operator = (const iterator & o) {
				*static_cast<base *>(this) = static_cast<const base &>(o);
				container = o.container;
				return *this;
			}

			reference operator*() const {
				return base::operator*();
			}

			pointer operator->() const {
				return base::operator->();
			}

			/* 
			iterator & operator = (iterator  o) {
				static_cast<base &>(*this) = static_cast<base &>(o);
				container = o.container;
				return *this;
			}
			*/
			friend class const_iterator;
		protected:
			container_p container;
		};
		class const_iterator:public container_t::const_iterator {
		public:
			typedef typename C::const_iterator base;
			const_iterator():base(),container() {}
			const_iterator(container_p & c, base i):base(i),
								  container(c) {}
			const_iterator(container_p & c,
				       typename container_t::iterator i):base(i),
									 container(c) {}
			const_iterator(const iterator & o):base(static_cast<const typename iterator::base &>(o)),
							   container(o.container) {}

			
			const_iterator & operator = (const iterator & o) {
				static_cast<base &>(*this) = static_cast<typename iterator::base &>(o);
				container = o.container;
				return *this;
			}

			const_iterator & operator = (const const_iterator & o) {
				static_cast<base &>(*this) = static_cast<base &>(o);
				container = o.container;
				return *this;
			}
			
			const_reference operator*() const {
				return base::operator*();
			}

			const_pointer operator->() const {
				return base::operator->();
			}
			/*
			const_iterator & operator = (const_iterator o) {
				static_cast<base &>(*this) = static_cast<base &>(o);
				container = o.container;
				return *this;
			}
			*/
		protected:
			container_p container;
		};
		
		cow_container():container(new container_t) {}
		cow_container(const thistype &o):container(o.container) {}
		cow_container(const C & o):container(new container_t(o)) {}
		
		void swap (base_container & c) {
			container = new container_t;
			container->swap(c);
		}
		const C & get_ref() {
			return *container;
		}

		thistype copy() {
			return thistype(*container);
		}

		thistype &copy_to(C & o) {
			o=*static_cast<C*>(container.get());
			return *this;
		}
		
		void duplicate() {
			container = copy();
		}

		void push_back(const value_type & e) {
			thistype tmp(copy());
			tmp.container->push_back(e);
			container.swap(tmp.container);
		}

		bool erase(const value_type & e) {
			bool found;
			thistype tmp = copy();
			typename base_container::iterator i = std::find(tmp.container->begin(),
									tmp.container->end(),
									e);
			if ((found=(i!=tmp.end())))
				tmp.container->erase(i);
			container.swap(tmp.container);
			return found;
		}

		iterator begin() {
			return iterator(container,container->begin());
		}
		const_iterator begin() const {
			return const_iterator(const_cast<thistype*>(this)->container,
					      container->begin());
		}
		iterator end() {
			return iterator(container,container->end());
		}
		const_iterator end() const {
			return const_iterator(const_cast<thistype*>(this)->container,
					      container->end());
		}

		size_t size() const {
			return container->size();
		}

		bool empty() const {
			return container->empty();
		}
		reference front() {
			return container->front();
		}
		const_reference front() const {
			return container->front();
		}
		reference back() {
			return container->back();
		}
		const_reference back() const {
			return container->back();
		}

	protected:
		container_p container;

		cow_container(const container_t & o):container(new container_t(o)) {}
	};
}


#endif /* precompiled */
#endif

/*
 * \}
 */

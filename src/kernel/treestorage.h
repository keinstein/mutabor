/** \file
 ***********************************************************************
 * abstract class for tree like storage
 *
 * \author T. Schlemmer <keinstein@users.berlios.de>
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

/* we guard a little bit complicated to ensure the references are set right
 */

#if (!defined(MU32_TREESTORAGE_H) && !defined(PRECOMPILE))	\
	|| (!defined(MU32_TREESTORAGE_H_PRECOMPILED))
#ifndef PRECOMPILE
#define MU32_TREESTORAGE_H
#endif

// ---------------------------------------------------------------------------
// headers
// ---------------------------------------------------------------------------

#include "Defs.h"

#ifndef MU32_TREESTORAGE_H_PRECOMPILED
#define MU32_TREESTORAGE_H_PRECOMPILED

// system headers which do seldom change

namespace mutabor {

/// Class tree_storage proviedes an interface for classes providing tree based storage.
/** This class is an abstract class.
 *  subclass it to provide some storage technology, which can be used for routing and other options.
 */
	class tree_storage 
	{
	public:
		/// default constructor.
		tree_storage()  {}
	
		/// virtual destructor
		virtual ~tree_storage() {}

		/// Reads a long integer value
		/**
		 * \argument key (mutStringRef) Name of the desired leaf in the tree
		 * \argument defval (long) default value, if the leaf is not availlable
		 * \retval data read or defval, if the leaf does not exist.
		 */
		virtual long Read(const mutStringRef key, long defval) = 0;
	
		/// Reads a double value
		/**
		 * \argument key (mutStringRef) Name of the desired leaf in the tree
		 * \argument defval (double) default value, if the leaf is not availlable
		 * \retval data read or defval, if the leaf does not exist.
		 */
		virtual double Read(const mutStringRef key, double defval) = 0;
	
		/// Reads an integer value
		/**
		 * \argument key (mutStringRef) Name of the desired leaf in the tree
		 * \argument defval (int) default value, if the leaf is not availlable
		 * \retval data read or defval, if the leaf does not exist.
		 */
		virtual int Read(const mutStringRef key, int defval) = 0;
	
		/// Reads a boolean value
		/**
		 * \argument key (mutStringRef) Name of the desired leaf in the tree
		 * \argument defval (bool) default value, if the leaf is not availlable
		 * \retval data read or defval, if the leaf does not exist.
		 */
		virtual bool Read(const mutStringRef key, bool defval) = 0;
	
		/// Reads a string value
		/**
		 * \argument key (mutStringRef) Name of the desired leaf in the tree
		 * \argument defval (mutStringRef) default value, if the leaf is not availlable
		 * \retval data read or defval, if the leaf does not exist.
		 */
		virtual mutString Read(const mutStringRef key, const mutStringRef defval) = 0;
		mutString Read(const mutStringRef key, const mutChar * defval)
		{ 
			return Read(key,mutString(defval));
		}

		mutString Read(const mutStringRef key, mutChar * defval)
		{ 
			return Read(key,mutString(defval));
		}
	
		/// Writes a long integer value
		/**
		 * \argument key (mutStringRef) Name of the desired leaf in the tree
		 * \argument value (long) value, to be written
		 */
		virtual void Write (const mutStringRef key, long value) = 0;
	
		/// Writes a double value
		/**
		 * \argument key (mutStringRef) Name of the desired leaf in the tree
		 * \argument value (double) value, to be written
		 */
		virtual void Write (const mutStringRef key, double value) = 0;
	
		/// Writes an integer value
		/**
		 * \argument key (mutStringRef) Name of the desired leaf in the tree
		 * \argument value (int) value, to be written
		 */
		virtual void Write (const mutStringRef key, int value) = 0;
	
		/// Writes a boolean value
		/**
		 * \argument key (mutStringRef) Name of the desired leaf in the tree
		 * \argument value (bool) value, to be written
		 */
		virtual void Write (const mutStringRef key, bool value) = 0;

		/// Writes a string value
		/**
		 * \argument key (mutStringRef) Name of the desired leaf in the tree
		 * \argument value (mutStringRef) value, to be written
		 */
		virtual void Write (const mutStringRef key, const mutStringRef value) = 0;
	
		/// Checks if the tree has a branch with the given name
		/** \argument subdir (mutStringRef) subdirectory to check for.
		 *  \return true if the current node has a leaf with the given 
		 *  name which is a node itself.
		 */
		virtual bool HasGroup(const mutStringRef) const = 0;

		/// Changes the current node downwards.
		/** this function can be used to navigate towards the leaves in the tree.
		 *  The argument can be considered like a subdirectory in a file system.
		 *  \argument subdir (mutStringRef) subdirectory to be written to.
		 */
		virtual void toLeaf(const mutStringRef subdir) = 0;

		/// Changes the current node downwards.
		/** this function can be used to navigate towards the leaves in the tree.
		 *  The argument can be considered as Items with a unique id.
		 *  if the id is negative, it will create a new item.
		 *  \argument subdir (mutStringRef) name of the entity to be written to.
		 *  \argument id (int) id of the current object
		 */
		virtual void toLeaf(const mutStringRef name, int id) = 0;
	
		/// Changes the current node downdwards to the first leaf of given type
		/** this function can be used to navigate towards the leaves in the tree.
		 *  The argument can be considered as Items with a unique id.
		 *  \argument subdir (mutStringRef) name of the entity to be read from.
		 *  \return (int) id of the selected item
		 *  \see toNextLeaf
		 */
		virtual int toFirstLeaf(const mutStringRef name) = 0;

		/// Changes the current node downdwards to the first leaf of given type
		/** this function can be used to navigate towards the leaves in the tree.
		 *  The argument can be considered as Items with a unique id.
		 *  \argument subdir (mutStringRef) name of the entity to be read from.
		 *  \argument id (mutStringRef) reference to a String where the id of the 
		 *       leaf will be stored
		 *  \return (int) id of the selected item
		 *  \see toNextLeaf
		 */
		virtual int toFirstLeaf(const mutStringRef name, mutStringRef id) = 0;

		/// Changes the current node downdwards to the next leaf of given type
		/** this function can be used to navigate towards the leaves in the tree.
		 *  The argument can be considered as Items with a unique id.
		 *  \argument subdir (mutStringRef) name of the entity to be read from.
		 *  \return (int) id of the selected item
		 *  \see toFirstLeaf
		 */
		virtual int toNextLeaf(const mutStringRef name) = 0;

		/// Changes the current node downdwards to the next leaf of given type
		/** this function can be used to navigate towards the leaves in the tree.
		 *  The argument can be considered as Items with a unique id.
		 *  \argument subdir (mutStringRef) name of the entity to be read from.
		 *  \argument id (mutStringRef) reference to a String where the id of the 
		 *       leaf will be stored
		 *  \return (int) id of the selected item
		 *  \see toFirstLeaf
		 */
		virtual int toNextLeaf(const mutStringRef name, mutStringRef id) = 0;
	
		/// This function jumps up in the tree (i.e. towards the root). 
		/** \argument count (int) number of nodes to go upward. Default: 1.
		 */
		virtual void toParent(unsigned int count = 1) = 0;

		/// Return a string representation of the position in the current tree.
		/** This function can be used to store the current position in the tree.
		 *  \retval mutString String representation of the current path. 
		 *  The concrete representation is implementation dependent and 
		 *  can vary for different tree types.
		 */
		virtual mutString GetPath() = 0;
	
		/// Set the current pointer in the tree.
		/** This function can be used to store the current position in the tree.
		 *  \argument path (mutString) String representation of the new path as returned by GetPath().
		 *  The concrete representation is implementation dependent and 
		 *  can vary for different tree types.
		 */	
		virtual void SetPath(const mutStringRef path) = 0;
	
		/// Delete an entry
		/** 
		 *  \argument entry path to the entry that shall be deleted
		 */
		virtual void DeleteEntry(const mutStringRef path) = 0;

		/// Delete an entire group with all childs
		/** 
		 *  \argument group path to the entry that shall be deleted
		 */
		virtual void DeleteGroup(const mutStringRef path) = 0;
	};

}
#endif //MUTABOR_TREESTORAGE_H_PRECOMPILED
#endif //MUTABOR_TREESTORAGE_H


///\}

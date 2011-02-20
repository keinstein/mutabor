/** \file
 ***********************************************************************
 * abstract class for tree like storage
 *
 * $Id: treestorage.h,v 1.3 2011/02/20 22:35:56 keinstein Exp $
 * \author T. Schlemmer <keinstein@users.berlios.de>
 * \date $Date: 2011/02/20 22:35:56 $
 * \version $Revision: 1.3 $
 * \license GPL
 *
 * $Log: treestorage.h,v $
 * Revision 1.3  2011/02/20 22:35:56  keinstein
 * updated license information; some file headers have to be revised, though
 *
 * Revision 1.2  2010-11-21 13:15:45  keinstein
 * merged experimental_tobias
 *
 * Revision 1.1.2.3  2010-09-29 15:06:40  keinstein
 * Reset config before saving routing information and fix two bugs concerned with the deletion of boxes
 *
 * Revision 1.1.2.2  2010-09-15 17:58:01  keinstein
 * old configuration can be loaded again.
 *
 * Revision 1.1.2.1  2010-08-10 16:33:37  keinstein
 * added simple wrapper for config and XML like files
 *
 *
 *
 *
 ********************************************************************
 * \addtogroup kernel
 * \{
 ********************************************************************/
 */
#ifndef MUTABOR_TREESTORAGE_H
#define MUTABOR_TREESTORAGE_H

#include "Defs.h"

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

#endif //MUTABOR_TREESTORAGE_H


///\}

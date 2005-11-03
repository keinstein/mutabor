/** \file
 ***********************************************************************
 * List of identifiers.
 *
 * $Id: ptrlist.h,v 1.1 2005/11/03 14:02:56 keinstein Exp $
 * \author Tobias Schlemmer <keinstein@users.berlios.de>
 * \date $Date: 2005/11/03 14:02:56 $
 * \version $Revision: 1.1 $
 *
 * $Log: ptrlist.h,v $
 * Revision 1.1  2005/11/03 14:02:56  keinstein
 * initial revision
 *
 */

#ifndef __MUTABOR_PTRLIST_H__
#define __MUTABOR_PTRLIST_H__

#include "object.h"

struct mutabor_avl_node_ptr;

struct mutabor_class_ptrlist {
    struct mutabor_class_object _; /**< Parent class */
    struct mutabor_avl_node_ptr * root; 
};

struct mutabor_virttable_ptrlist {
    size_t size;
    char * name;
    void ** parent;
    void * (*constructor)(void * _self); /**< Constructor for creating an object. */
    void * (*destructor)(void * _self); /**< Destructor for deleting an object. */
    int (*compare)(void * one, void * two); /**< Simple comparison. */
    char * (*tostring)(void * _self); /**< Stringify for data output. */
    int (*insert)(void * _self,const void * ptr); 
    void * (*find)(void const * _self, void const * ptr); 
};

extern const void * mutabor_object_ptrlist;


#endif /* __MUTABOR_PTRLIST_H__ */

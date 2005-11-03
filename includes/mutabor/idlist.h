/** \file
 ***********************************************************************
 * List of identifiers.
 *
 * $Id: idlist.h,v 1.1 2005/11/03 13:53:40 keinstein Exp $
 * \author Tobias Schlemmer <keinstein@users.berlios.de>
 * \date $Date: 2005/11/03 13:53:40 $
 * \version $Revision: 1.1 $
 *
 * $Log: idlist.h,v $
 * Revision 1.1  2005/11/03 13:53:40  keinstein
 * Identifier list class
 *
 */

#ifndef __MUTABOR_IDLIST_H__
#define __MUTABOR_IDLIST_H__

#include "identifier.h"

struct mutabor_class_idlist {
    struct mutabor_class_object _; /**< Parent class */
    size_t number; /**< Current number of entries */
    size_t arraysize; /**< Maximum number of entries */
    int status; /**< 1 sorted according name, 2 sorted according pointers */
    MUT_CLASS(identifier) ** array; /**< Entries of class */
};

struct mutabor_virttable_idlist {
    size_t size;
    char * name;
    void ** parent;
    void * (*constructor)(void * _self); /**< Constructor for creating an object. */
    void * (*destructor)(void * _self); /**< Destructor for deleting an object. */
    int (*compare)(void * one, void * two); /**< Simple comparison. */
    char * (*tostring)(void * _self); /**< Stringify for data output. */
    int (*insert)(void * _self,const void * identifier); 
    MUT_CLASS(identifier) * (*find)(void * _self,const char * name); 
};

extern const void * mutabor_object_idlist;

extern void mutabor_cls_idlist_sortbyname(void * _self, int force_bubble);
extern void mutabor_cls_idlist_sortbynumber(void * _self, int force_bubble);

#endif /* __MUTABOR_IDLIST_H__ */

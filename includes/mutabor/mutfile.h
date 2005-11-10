/** \file
 ***********************************************************************
 * Mutabor File class.
 *
 * $Id: mutfile.h,v 1.6 2008/10/10 08:45:28 keinstein Exp $
 * \author Tobias Schlemmer <keinstein@users.berlios.de>
 * \date $Date: 2008/10/10 08:45:28 $
 * \version $Revision: 1.6 $
 *
 * $Log: mutfile.h,v $
 * Revision 1.6  2008/10/10 08:45:28  keinstein
 * myContextHelpButton is still not needed
 *
 * Revision 1.2  2005/11/10 16:16:59  keinstein
 * working distcheck
 *
 * Revision 1.1  2005/11/03 14:01:48  keinstein
 * initial revision
 *
 */

#ifndef __MUTABOR_MUTFILE_H__
#define __MUTABOR_MUTFILE_H__

#include "mutabor/idlist.h"

struct mutabor_class_mutfile {
    struct mutabor_class_object _; /**< Parent class */
    MUT_CLASS(idlist) * intervals; 
    MUT_CLASS(idlist) * interval_placeholder; 
    char * filename; 
    FILE * descriptor; 
    void * scanner; 
};

struct mutabor_virttable_mutfile {
    size_t size;
    char * name;
    void ** parent;
    void * (*constructor)(void * _self); 
    void * (*destructor)(void * _self); 
    int (*compare)(void * one, void * two); /**< Simple comparison. */
    char * (*tostring)(void * _self); 
};

extern const void * mutabor_object_mutfile;

extern void * mutabor_cls_mutfile_insert_interval(void * _self,void * interval);
extern void * mutabor_cls_mutfile_get_interval(void * _self,char * name);
extern void * mutabor_cls_mutfile_check_interval(void * _self,void * _interval,char * name);
extern void * mutabor_cls_mutfile_sort_interval_names(void * _self, int force_bubble);
extern void * mutabor_cls_mutfile_sort_interval_pointers(void * _self, int force_bubble);
extern void * mutabor_cls_mutfile_sort_interval_pl_names(void * _self, int force_bubble);
extern void * mutabor_cls_mutfile_sort_interval_pl_pointers(void * _self, int force_bubble);

#endif /* __MUTABOR_MUTFILE_H__ */

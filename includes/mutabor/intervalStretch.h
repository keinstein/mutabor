/** \file
 ********************************************************************
 * Placeholder objects for not yet specified identifiers.
 *
 * $Id: intervalStretch.h,v 1.3 2005/11/10 16:16:59 keinstein Exp $
 * \author Tobias Schlemmer <keinstein@users.berlios.de>
 * \date $Date: 2005/11/10 16:16:59 $
 * \version $Revision: 1.3 $
 * 
 * $Log: intervalStretch.h,v $
 * Revision 1.3  2005/11/10 16:16:59  keinstein
 * working distcheck
 *
 * Revision 1.1  2005/11/03 14:00:01  keinstein
 * initial revision
 *
 ********************************************************************/

#ifndef __MUTABOR_STRETCH_H_INCLUDED
#define __MUTABOR_STRETCH_H_INCLUDED

#ifdef __cplusplus 
namespace mutabor {
  extern "C" {
#endif

#include "mutabor/interval.h"
#include "mutabor/bad_decl.h"

    /** Interval class. */

struct mutabor_class_intervalStretch {
    struct mutabor_class_interval _; /**< Parent class */
    MUTABOR_FLOAT stretch; 
    MUT_CLASS(interval) * right; 
};

struct mutabor_virttable_intervalStretch {
    size_t size;
    char * name;
    void ** parent;
    void * (*constructor)(void * _self); 
    void * (*destructor)(void * _self); /**< Destructor for deleting the class. */
    int (*compare)(void * one, void * two); 
    char * (*tostring)(void * _self); 
    void * (*check_cycle)(register void * _self, register void * _identifier,  register MUT_CLASS(ptrlist) * list); /**< checks, if _self depends somehow on _identifier. */
    void (*precalculate)(void * _self); /**< precalculate the dependencies */
};

extern const void * mutabor_object_intervalStretch;


#define mutabor_cls_intervalStretch_copy_name mutabor_cls_identifier_copy_name

#define mutabor_cls_intervalStretch_set_name mutabor_cls_identifier_set_name

#define mutabor_cls_intervalStretch_get_name mutabor_cls_identifier_get_name

#define mutabor_cls_intervalStretch_set_factor mutabor_cls_interval_set_factor
extern void mutabor_cls_intervalStretch_setright(void * _self, void * right);
extern void mutabor_cls_intervalStretch_setstretch(void * _self, MUTABOR_FLOAT stretch);


#ifdef __cplusplus
  }
}
#endif

#endif /* __MUTABOR_STRETCH_H_INCLUDED */

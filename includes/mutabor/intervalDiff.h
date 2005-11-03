/** \file
 ********************************************************************
 * Complex intervals (differences).
 *
 * $Id: intervalDiff.h,v 1.1 2005/11/03 13:55:25 keinstein Exp $
 * \author Tobias Schlemmer <keinstein@users.berlios.de>
 * \date $Date: 2005/11/03 13:55:25 $
 * \version $Revision: 1.1 $
 * 
 * $Log: intervalDiff.h,v $
 * Revision 1.1  2005/11/03 13:55:25  keinstein
 * Initial release
 *
 ********************************************************************/

#if ! defined (__MUTABOR_INTERVALDIFF_H_INCLUDED__)
#define __MUTABOR_INTERVALDIFF_H_INCLUDED__

#ifdef __cplusplus 
namespace mutabor {
  extern "C" {
#endif

#include "intervalSum.h"

    /** Difference of two intervals. */

struct mutabor_class_intervalDiff {
    struct mutabor_class_intervalSum _; /**< Parent class */
};

struct mutabor_virttable_intervalDiff {
    size_t size;
    char * name;
    void ** parent;
    void * (*constructor)(void * _self); 
    void * (*destructor)(void * _self); /**< Destructor for deleting the class. */
    int (*compare)(void * one, void * two); 
    char * (*tostring)(void * _self); 
    void (*precalculate)(void * _self); 
    void (*link_childs)(void * _self); /**< link pointers to childs */
};

extern const void * mutabor_object_intervalDiff;


#define mutabor_cls_intervalDiff_copy_name mutabor_cls_identifier_copy_name

#define mutabor_cls_intervalDiff_is_name mutabor_cls_identifier_is_name

#define mutabor_cls_intervalDiff_set_factor mutabor_cls_interval_set_factor

#define mutabor_cls_intervalDiff_setleft mutabor_cls_intervalSum_setleft

#define mutabor_cls_intervalDiff_setright mutabor_cls_intervalSum_setright


#ifdef __cplusplus
  }
}
#endif

#endif /* __MUTABOR_INTERVALDIFF_H_INCLUDED__ */

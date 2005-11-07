/** \file
 ********************************************************************
 * Complex intervals.
 *
 * $Id: intervalSum.h,v 1.2 2005/11/07 19:42:54 keinstein Exp $
 * \author Tobias Schlemmer <keinstein@users.berlios.de>
 * \date $Date: 2005/11/07 19:42:54 $
 * \version $Revision: 1.2 $
 * 
 * $Log: intervalSum.h,v $
 * Revision 1.2  2005/11/07 19:42:54  keinstein
 * Some additional changes
 *
 * Revision 1.1  2005/11/03 14:29:13  keinstein
 * initial revision
 *
 ********************************************************************/

#if ! defined (__MUTABOR_INTERVALSUM_H_INCLUDED__)
#define __MUTABOR_INTERVASUML_H_INCLUDED__

#ifdef __cplusplus 
namespace mutabor {
  extern "C" {
#endif

#include "interval.h"

    /** Interval class. */

/* %virtual int compare (void * one, void * two) */
struct mutabor_class_intervalSum {
    struct mutabor_class_interval _; /**< Parent class */
    MUT_CLASS(interval)* left; 
    MUT_CLASS(interval)* right; 
};

struct mutabor_virttable_intervalSum {
    size_t size;
    char * name;
    void ** parent;
    void * (*constructor)(void * _self); 
    void * (*destructor)(void * _self); /**< Destructor for deleting the class. */
    int (*compare)(void * one, void * two); 
    char * (*tostring)(void * _self); 
    void * (*check_cycle)(register void * _self, register void * _identifier,  register MUT_CLASS(ptrlist) * list); /**< checks, if _self depends somehow on _identifier. */
    void (*precalculate)(void * _self); 
};

extern const void * mutabor_object_intervalSum;


#define mutabor_cls_intervalSum_copy_name mutabor_cls_identifier_copy_name

#define mutabor_cls_intervalSum_set_name mutabor_cls_identifier_set_name

#define mutabor_cls_intervalSum_get_name mutabor_cls_identifier_get_name

#define mutabor_cls_intervalSum_set_factor mutabor_cls_interval_set_factor
extern void mutabor_cls_intervalSum_setleft(void * _self,void * _interval);
extern void mutabor_cls_intervalSum_setright(void * _self,void * _interval);


#ifdef __cplusplus
  }
}
#endif

#endif /* __MUTABOR_INTERVALSUM_H_INCLUDED__ */

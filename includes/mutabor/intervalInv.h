/** \file
 ********************************************************************
 * Inv objects for not yet specified identifiers.
 *
 * $Id: intervalInv.h,v 1.2 2005/11/07 19:42:54 keinstein Exp $
 * \author Tobias Schlemmer <keinstein@users.berlios.de>
 * \date $Date: 2005/11/07 19:42:54 $
 * \version $Revision: 1.2 $
 * 
 * $Log: intervalInv.h,v $
 * Revision 1.2  2005/11/07 19:42:54  keinstein
 * Some additional changes
 *
 * Revision 1.1  2005/11/03 13:56:24  keinstein
 * Initial revision
 *
 ********************************************************************/

#ifndef __MUTABOR_INTERVALINV_H_INCLUDED
#define __MUTABOR_INTERVALINV_H_INCLUDED

#ifdef __cplusplus 
namespace mutabor {
  extern "C" {
#endif

#include "intervalPlaceholder.h"
#include "bad_decl.h"

    /** Interval class. */

struct mutabor_class_intervalInv {
    struct mutabor_class_intervalPlaceholder _; /**< Parent class */
};

struct mutabor_virttable_intervalInv {
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

extern const void * mutabor_object_intervalInv;


#define mutabor_cls_intervalInv_copy_name mutabor_cls_identifier_copy_name

#define mutabor_cls_intervalInv_set_name mutabor_cls_identifier_set_name

#define mutabor_cls_intervalInv_get_name mutabor_cls_identifier_get_name

#define mutabor_cls_intervalInv_set_factor mutabor_cls_interval_set_factor

#define mutabor_cls_intervalInv_setreplacement mutabor_cls_intervalPlaceholder_setreplacement
extern void mutabor_cls_intervalInv_setright(void * _self, void * interval);


#ifdef __cplusplus
  }
}
#endif

#endif /* __MUTABOR_ITERVALINV_H_INCLUDED */

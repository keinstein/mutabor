/** \file
 ********************************************************************
 * Placeholder objects for not yet specified identifiers.
 *
 * $Id: intervalPlaceholder.h,v 1.6 2008/10/10 08:45:28 keinstein Exp $
 * \author Tobias Schlemmer <keinstein@users.sourceforge.net>
 * \date $Date: 2008/10/10 08:45:28 $
 * \version $Revision: 1.6 $
 * 
 * $Log: intervalPlaceholder.h,v $
 * Revision 1.6  2008/10/10 08:45:28  keinstein
 * myContextHelpButton is still not needed
 *
 * Revision 1.2  2005/11/10 16:16:59  keinstein
 * working distcheck
 *
 * Revision 1.1  2005/11/03 13:58:48  keinstein
 * initial revision
 *
 ********************************************************************/

#ifndef __MUTABOR_PLACEHOLDER_H_INCLUDED
#define __MUTABOR_PLACEHOLDER_H_INCLUDED

#ifdef __cplusplus 
namespace mutabor {
  extern "C" {
#endif

#include "mutabor/interval.h"
#include "mutabor/bad_decl.h"

    /** Interval class. */

struct mutabor_class_intervalPlaceholder {
    struct mutabor_class_interval _; /**< Parent class */
    MUT_CLASS(interval) * replacement; 
};

struct mutabor_virttable_intervalPlaceholder {
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

extern const void * mutabor_object_intervalPlaceholder;


#define mutabor_cls_intervalPlaceholder_copy_name mutabor_cls_identifier_copy_name

#define mutabor_cls_intervalPlaceholder_set_name mutabor_cls_identifier_set_name

#define mutabor_cls_intervalPlaceholder_get_name mutabor_cls_identifier_get_name

#define mutabor_cls_intervalPlaceholder_set_factor mutabor_cls_interval_set_factor
extern void mutabor_cls_intervalPlaceholder_setreplacement(void * _self, void * replacement);


#ifdef __cplusplus
  }
}
#endif

#endif /* __MUTABOR_PLACEHOLDER_H_INCLUDED */

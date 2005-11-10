/** \file
 ***********************************************************************
 * Identifier class
 *
 * $Id: identifier.h,v 1.5 2008/10/10 08:45:28 keinstein Exp $
 * \author Tobias Schlemmer <keinstein@users.berlios.de>
 * \date $Date: 2008/10/10 08:45:28 $
 * \version $Revision: 1.5 $
 *
 * $Log: identifier.h,v $
 * Revision 1.5  2008/10/10 08:45:28  keinstein
 * myContextHelpButton is still not needed
 *
 * Revision 1.2  2005/11/10 16:16:59  keinstein
 * working distcheck
 *
 * Revision 1.1  2005/11/03 13:52:56  keinstein
 * Identifier Class file
 *
 */

#ifndef __MUTABOR_IDENTIFIER_H__
#define __MUTABOR_IDENTIFIER_H__

#include "mutabor/object.h"

#ifdef OLD_MUTABOR_CLASSES
#define MUTABOR_CLASS_DEFINITIONS_identifier(class) \
  PARENT(class,object)\
  FIELD(class,char *,name)\
  OVERRIDE(class, void *, constructor, void * _self) \
  OVERRIDE(class, void *, destructor, void * _self) \
  OVERRIDE(class, int, compare, void * one, void * two) \
  OVERRIDE(class, char *, tostring,void * _self)\
  VIRTUAL(class,void,precalculate,void * _self)\
  VIRTUAL(class,void,link_childs,void * _self)

MUTABOR_DECLARE_CLASS(identifier);
#endif

MUT_CLASS(ptrlist);

struct mutabor_class_identifier {
    struct mutabor_class_object _; /**< Parent class */
    char * name; /**< Name of the identifier. */
};

struct mutabor_virttable_identifier {
    size_t size;
    char * name;
    void ** parent;
    void * (*constructor)(void * _self); /**< Constructor for initializing the class. */
    void * (*destructor)(void * _self); /**< Destructor for deleting the class. */
    int (*compare)(void * one, void * two); /**< compares two objects. */
    char * (*tostring)(void * _self); /**< Printing (mainly for debugging) */
    void * (*check_cycle)(register void * _self, register void * _identifier,  register MUT_CLASS(ptrlist) * list); /**< checks, if _self depends somehow on _identifier. */
    void (*precalculate)(void * _self); /**< precalculate the dependencies */
};

extern const void * mutabor_object_identifier;

extern void mutabor_cls_identifier_copy_name(void * _self,char * name);
extern void mutabor_cls_identifier_set_name(void * _self,char * name);
extern char * mutabor_cls_identifier_get_name(void * _self);

#endif /* __MUTABOR_IDENTIFIER_H__ */

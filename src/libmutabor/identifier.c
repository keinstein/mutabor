/** \file
 ***********************************************************************
 * Identifier class
 *
 * $Id: identifier.c,v 1.2 2006/03/27 16:58:42 keinstein Exp $
 * \author Tobias Schlemmer <keinstein@users.berlios.de>
 * \date $Date: 2006/03/27 16:58:42 $
 * \version $Revision: 1.2 $
 *
 * $Log: identifier.c,v $
 * Revision 1.2  2006/03/27 16:58:42  keinstein
 * added lab-asprintf.h to headers
 *
 * Revision 1.1  2005/11/03 14:06:05  keinstein
 * initial revision
 *
 */

#ifdef HAVE_CONFIG_H
#  include "config.h"
#endif
#ifdef HAVE_STRING_H
#  include <string.h>
#endif
#ifdef HAVE_STRINGS_H
#  include <strings.h>
#endif
#  include <stdio.h>
#include <assert.h>
#include "lib-asprintf.h"
#include "mutabor/bad_decl.h"
#include "mutabor/ptrlist.h"
#include "mutabor/identifier.h"
#include "mutabor/identifier.hh"

     /*
#define MUTABOR_CLASS_DEFINITIONS_identifier(class) \
  PARENT(class,object)\
  FIELD(class,char *,name)\
  OVERRIDE(class, void *, constructor, void * _self) \
  OVERRIDE(class, void *, destructor, void * _self) \
  OVERRIDE(class, int, compare, void * one, void * two) \
  OVERRIDE(class, char *, tostring,void * _self)\
  VIRTUAL(class,void,precalculate,void * _self)\
  VIRTUAL(class,void,link_childs,void * _self)
     */

/** Constructor for class object. Does nothing than error checking. */

void * MUTABOR_CLASS_FUNCTION(identifier,constructor)(void * _self){
  CHK_CLASS(_self,identifier);
  ((MUT_CLASS(identifier)*) _self)->name=NULL;
  return (_self);
}

/** Destructor for class object. Does nothing than error checking. */

void * MUTABOR_CLASS_FUNCTION(identifier, destructor)(void * _self) {
  CHK_CLASS(_self,identifier);
  free(((MUT_CLASS(identifier)*) _self)->name);
  return (_self);
}

/** Comparison between two objects. Simple comparison by pointers. */

int MUTABOR_CLASS_FUNCTION(identifier, compare)(void * _one, void * _two){
  MUT_CLASS(identifier) *one=_one,*two=_two;
  CHK_CLASS(_one,identifier);
  CHK_CLASS(_two,identifier);
  return strcmp(one->name,two->name);
}

/** Formats Class content as string. Intented exspecially for debugging. */

char * MUTABOR_CLASS_FUNCTION(identifier,tostring)(void * _self){
  MUT_VIRTTABLE(object) ** self=_self;
  char * data;
  CHK_CLASS(_self,identifier);
  if (asprintf(&data,"%s (%p): %s %p",
	       (*self)->name, 
	       (void *)*self,
	       ((MUT_CLASS(identifier)*) _self)->name,
	       _self)){
    return data;
  }
  else 
    return NULL;
}

void MUTABOR_CLASS_FUNCTION(identifier,precalculate)(void * _self) {
  CHK_CLASS(_self,identifier);
}

void MUTABOR_CLASS_FUNCTION(identifier,link_childs)(void * _self) {
  CHK_CLASS(_self,identifier);
}

#ifdef OLD_MUTABOR_CLASSES
/** Initialiszing of global class data for object. */
MUTABOR_INITIALIZE_CLASS(identifier)
#endif

void MUTABOR_CLASS_FUNCTION(identifier,copy_name)(void * _self,char * name){
  CHK_CLASS(_self,identifier);
  ((MUT_CLASS(identifier)*) _self)->name=strdup(name);
}

void MUTABOR_CLASS_FUNCTION(identifier,set_name)(void * _self,char * name){
  CHK_CLASS(_self,identifier);
  ((MUT_CLASS(identifier)*) _self)->name=name;
}

char * MUTABOR_CLASS_FUNCTION(identifier,get_name)(void * _self){
  CHK_CLASS(_self,identifier);
  return ((MUT_CLASS(identifier)*) _self)->name;
}


void * MUTABOR_CLASS_FUNCTION(identifier,check_cycle)
     (register void * _self, register void * _identifier, register MUT_CLASS(ptrlist) * list)
{
  return NULL;
}

/** \file
 ***********************************************************************
 * Common definitions for object oriented programming and base class
 * \c #object.
 *
 * $Id: object.c,v 1.2 2006/03/27 17:07:51 keinstein Exp $
 * \author Tobias Schlemmer <keinstein@users.berlios.de>
 * \date $Date: 2006/03/27 17:07:51 $
 * \version $Revision: 1.2 $
 *
 * $Log: object.c,v $
 * Revision 1.2  2006/03/27 17:07:51  keinstein
 * added lib-asprintf.h
 *
 * Revision 1.1  2005/11/03 14:58:11  keinstein
 * initial release
 *
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
  /* Relevante Variablen für diese Datei:
   * HAVE_MEMMOVE 
   * malloc
   * size_t
   */
#endif

#ifdef HAVE_STDLIB_H
#  include<stdlib.h>
#endif
#ifdef HAVE_STRING_H
#  include<string.h>
#elif HAVE_STRINGS_H
#  include<strings.h>
#endif
#  include <stdio.h>
#include<assert.h>
#include "lib-asprintf.h"
#include "mutabor/object.h"
#include "mutabor/object.hh"
#include "mutabor/bad_decl.h"

/** Constructor for class object. Does nothing than error checking. */

void * MUTABOR_CLASS_FUNCTION(object,constructor) (void * _self){
  CHK_CLASS(_self,object);
  return (_self);
}

/** Destructor for class object. Does nothing than error checking. */

void * MUTABOR_CLASS_FUNCTION(object,destructor)(void * _self) {
  CHK_CLASS(_self,object);
  return (_self);
}

/** Comparison between two objects. Simple comparison by pointers. */

int MUTABOR_CLASS_FUNCTION(object,compare)(void * one, void * two){
  CHK_CLASS(one,object);
  CHK_CLASS(two,object);
  return (one != two);
}

/** Formats Class content as string. Intented exspecially for debugging. */

char* MUTABOR_CLASS_FUNCTION(object,tostring)(void * _self){
  MUT_VIRTTABLE(object) ** self=_self;
  char * data;
  CHK_CLASS(_self,object);
  if (data) {
    if (asprintf(&data,"%s (%p): %p",
		 (*self)->name, 
		 (void *)*self,
		 _self)){
      return data;
    }
    else 
      return NULL;
  }
  else
    return NULL;
}

#ifdef OLD_MUTABOR_CLASSES
/** Initialiszing of global class data for object. */
MUTABOR_INITIALIZE_CLASS(object)
#endif

/** Creates a new object in Heap space. If the table of virtual
 *  functions is not initialized yet, it will be initialized.
 *  \param _type Pointer to the virtual table of the desired class. 
 * It plays the role of class name.
 */

void * mutabor_new(void * _type) {
  MUT_VIRTTABLE(object) * type=_type;
#ifdef OLD_MUTABOR_CLASSES
  assert(type->init_virttable);
  if (!type->parent) type->init_virttable();
#endif
  MUT_CLASS(object) * data;
  CHK_CLASS(&_type,object);
  data=(struct mutabor_class_object *) malloc(type->size);
  if (data) {
    data->virttable=_type;
    type->constructor(data);
  }
  return (data);
}

/** Deletes an object from the heap. 
 *  \param _object object to be deleted.
 */

void mutabor_delete(void * _object) {
  struct mutabor_class_object * object=_object;
  CHK_CLASS(_object,object);
  free(object->virttable->destructor(_object));
}

/** Checks, if a pointer is a subclass of a given class.
 * \param _self object to be checked
 * \param object pointer to the virtual table of the desired class.
 * \retval 0 if not an object of the desired class
 * \retval 1 if _self is an instance of \c object
 * \return The function does not return if it encounters 
 *         cyclic dependencies of objects (or what it takes as objects).
 *         In most cases of weired data structures it will (hopefully) 
 *         fail with a null pointer dereference or a segmentation fault.
 */

int mutabor_check_class(void * _self, void * object){
  if (!(_self && object && *(void **)object && *(void**)_self)) return 0;
  if (*(void **)_self == object) return 1;
  else if(*(void **)_self==*(MUT_VIRTCALL(object,_self,parent))) return 0;
  else return mutabor_check_class(MUT_VIRTCALL(object,_self,parent),object);
}

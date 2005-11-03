/** \file
 ***********************************************************************
 * Identifier class
 *
 * $Id: intervalStretch.c,v 1.1 2005/11/03 14:11:17 keinstein Exp $
 * \author Tobias Schlemmer <keinstein@users.berlios.de>
 * \date $Date: 2005/11/03 14:11:17 $
 * \version $Revision: 1.1 $
 *
 * $Log: intervalStretch.c,v $
 * Revision 1.1  2005/11/03 14:11:17  keinstein
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
#include "mutabor/ptrlist.h"
#include "mutabor/intervalStretch.h"
#include "mutabor/intervalStretch.hh"

/** Constructor for class object. Does nothing than error checking. */
void * MUTABOR_CLASS_FUNCTION(interval,constructor)(void * _self);
void * MUTABOR_CLASS_FUNCTION(intervalStretch,constructor)(void * _self){
  MUT_CLASS(intervalStretch)* self = _self;
  CHK_CLASS(_self,intervalStretch);
  MUTABOR_CLASS_FUNCTION(interval,constructor)(_self);
  self->right=NULL;
  self->stretch=1;
  return (_self);
}

/** Formats Class content as string. Intented exspecially for debugging. */

char * MUTABOR_CLASS_FUNCTION(intervalStretch,tostring)(void * _self){
  MUT_VIRTTABLE(object) ** self=_self;
  char * data;
  CHK_CLASS(_self,intervalStretch);
  if (asprintf(&data,"%s (%p): %s %p factor: %12.8g;\n\t%12.8g*%p",
	       (*self)->name, 
	       (void *)*self,
	       ((MUT_CLASS(identifier)*) _self)->name,
	       _self,
	       MUT_VALUE(interval,_self)->factor,
	       ((MUT_CLASS(intervalStretch)*) _self)->stretch,
	       (void *)(((MUT_CLASS(intervalStretch)*) _self)->right)
	       )){
    return data;
  }
  else 
    return NULL;
}

void MUTABOR_CLASS_FUNCTION(intervalStretch,setright) (void * _self, void * right) 
{
  CHK_CLASS(_self,intervalStretch);
  CHK_CLASS(right,identifier);
  MUT_VALUE(intervalStretch,_self)->right=right;
  MUT_VALUE(interval,_self)->factor=log(-1);
}

void MUTABOR_CLASS_FUNCTION(intervalStretch,setstretch)(void * _self, MUTABOR_FLOAT stretch)
{
  CHK_CLASS(_self,intervalStretch);
  MUT_VALUE(intervalStretch,_self)->stretch=stretch;
  MUT_VALUE(interval,_self)->factor=log(-1);
}

void MUTABOR_CLASS_FUNCTION(intervalStretch,precalculate)(void * _self)
{
  MUT_CLASS(intervalStretch) * self=_self;
  CHK_CLASS(_self,intervalStretch);
  if (self->right) {
      MUT_VIRTCALL(interval,self->right,precalculate)(self->right);
      MUT_VALUE(interval,_self)->factor=
	MUTABOR_FLOAT_POW(self->right->factor,self->stretch);
  } else MUT_VALUE(interval,_self)->factor=log(-1);
}

void * MUTABOR_CLASS_FUNCTION(identifier,check_cycle)
      (register void * _self, register void * _identifier, register MUT_CLASS(ptrlist) * list);
void * MUTABOR_CLASS_FUNCTION(intervalStretch,check_cycle)
     (register void * _self, register void * _identifier, register MUT_CLASS(ptrlist) * list)
{
	MUT_CLASS(intervalStretch) * self=_self;
	void *i;
	if ((i=MUTABOR_CLASS_FUNCTION(identifier,check_cycle)(_self,_identifier,list))) return i;
	if ( self->right == _identifier ) return self;
	if (MUT_VIRTCALL(ptrlist,list,find)(list,self->right)) return NULL;
	else {
		if ((i=MUT_VIRTCALL(identifier,self->right,check_cycle)
		     (self->right,_identifier,list))) return i;
		else MUT_VIRTCALL(ptrlist,list,insert)(list,self->right);
	}
}

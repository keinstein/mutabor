/** \file
 ***********************************************************************
 * Identifier class
 *
 * $Id: intervalPlaceholder.c,v 1.1 2005/11/03 14:10:35 keinstein Exp $
 * \author Tobias Schlemmer <keinstein@users.berlios.de>
 * \date $Date: 2005/11/03 14:10:35 $
 * \version $Revision: 1.1 $
 *
 * $Log: intervalPlaceholder.c,v $
 * Revision 1.1  2005/11/03 14:10:35  keinstein
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
#include "mutabor/intervalPlaceholder.h"
#include "mutabor/intervalPlaceholder.hh"

/** Constructor for class object. Does nothing than error checking. */
void * MUTABOR_CLASS_FUNCTION(interval,constructor)(void * _self);
void * MUTABOR_CLASS_FUNCTION(intervalPlaceholder,constructor)(void * _self){
  MUT_CLASS(intervalPlaceholder)* self = _self;
  CHK_CLASS(_self,intervalPlaceholder);
  MUTABOR_CLASS_FUNCTION(interval,constructor)(_self);
  self->replacement=NULL;
  return (_self);
}

/** Formats Class content as string. Intented exspecially for debugging. */

char * MUTABOR_CLASS_FUNCTION(intervalPlaceholder,tostring)(void * _self){
  MUT_VIRTTABLE(object) ** self=_self;
  char * data;
  CHK_CLASS(_self,intervalPlaceholder);
  if (asprintf(&data,"%s (%p): %s %p Factor: %g (%p)",
	       (*self)->name, 
	       (void *)*self,
	       ((MUT_CLASS(identifier)*) _self)->name,
	       _self,
	       MUT_VALUE(interval,_self)->factor,
	       (void *)(((MUT_CLASS(intervalPlaceholder)*) _self)->replacement)
	       )){
    return data;
  }
  else 
    return NULL;
}

void MUTABOR_CLASS_FUNCTION(intervalPlaceholder,setreplacement) (void * _self, void * replacement) 
{
  CHK_CLASS(_self,intervalPlaceholder);
  CHK_CLASS(replacement,interval);
  MUT_VALUE(intervalPlaceholder,_self)->replacement=replacement;
  MUT_VALUE(interval,_self)->factor=log(-1);
}

void MUTABOR_CLASS_FUNCTION(intervalPlaceholder,precalculate)(void * _self){
	MUT_CLASS(intervalPlaceholder) * self=_self;
	CHK_CLASS(_self,intervalPlaceholder);
	if (self->replacement) {
		MUT_VIRTCALL(interval,self->replacement,precalculate)(self->replacement);
		MUT_VALUE(interval,_self)->factor=self->replacement->factor;
	} else MUT_VALUE(interval,_self)->factor=log(-1);
}

void * MUTABOR_CLASS_FUNCTION(identifier,check_cycle)
      (register void * _self, register void * _identifier, register MUT_CLASS(ptrlist) * list);
void * MUTABOR_CLASS_FUNCTION(intervalPlaceholder,check_cycle)
     (register void * _self, register void * _identifier, register MUT_CLASS(ptrlist) * list)
{
	MUT_CLASS(intervalPlaceholder) * self=_self;
	void *i;
	if ((i=MUTABOR_CLASS_FUNCTION(identifier,check_cycle)(_self,_identifier,list))) return i;
	if (self->replacement==_identifier) return self;
	if (MUT_VIRTCALL(ptrlist,list,find)(list,self->replacement)) return NULL;
	else {
		if ((i=MUT_VIRTCALL(identifier,self->replacement,check_cycle)
		     (self->replacement,_identifier,list))) return i;
		else MUT_VIRTCALL(ptrlist,list,insert)(list,self->replacement);
	}
	return NULL;
}

/** \file
 ********************************************************************
 * complex intervals.
 *
 * $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/libmutabor/intervalSum.c,v 1.2 2006/03/27 17:01:22 keinstein Exp $
 * \author Tobias Schlemmer <keinstein@users.berlios.de>
 * \date $Date: 2006/03/27 17:01:22 $
 * \version $Revision: 1.2 $
 *
 * $Log: intervalSum.c,v $
 * Revision 1.2  2006/03/27 17:01:22  keinstein
 * added lab-asprintf.h to headers
 *
 * Revision 1.1  2005/11/03 14:12:02  keinstein
 * initial revision
 *
 ********************************************************************/
#ifdef HAVE_CONFIG_H
#include "config.h"
  /* Relevante Variablen für diese Datei:
   * HAVE_POW
   * size_t
   * HAVE_STRING_H
   */
#endif

#ifdef HAVE_STRING_H
#  include<string.h>
#endif

#include<math.h>
#include<assert.h>
#include "lib-asprintf.h"
#include "mutabor/ptrlist.h"
#include "mutabor/intervalSum.h"
#include "mutabor/intervalSum.hh"

void * MUTABOR_CLASS_FUNCTION(interval,constructor) (void * _self);
void * MUTABOR_CLASS_FUNCTION(intervalSum,constructor) (void * _self){
  register MUT_CLASS(intervalSum) * self;
  CHK_CLASS(_self,intervalSum);
  self = MUTABOR_CLASS_FUNCTION(interval,constructor)(_self);
  self->left=NULL;
  self->right=NULL;
  return self;
}

char * MUTABOR_CLASS_FUNCTION(intervalSum,tostring)(void * _self){
  register MUT_VIRTTABLE(object) ** self=_self;
  char * data;
  CHK_CLASS(_self,intervalSum);
  if (asprintf(&data,"%s (%p): %s (%p) factor: %12.8g;\n\t %12.8g (%p), %12.8g(%p)",
	       (*self)->name, 
	       (void *)*self,
	       ((MUT_CLASS(identifier)*) _self)->name,
	       _self,
	       MUT_VALUE(interval,_self)->factor,
	       MUT_VALUE(intervalSum,_self)->left?MUT_VALUE(intervalSum,_self)->left->factor:log(-1),
	       (void *)(MUT_VALUE(intervalSum,_self)->left),
 	       MUT_VALUE(intervalSum,_self)->right?MUT_VALUE(intervalSum,_self)->right->factor:log(-1),
	       (void *)(MUT_VALUE(intervalSum,_self)->right))){
    return data;
  }
  else 
    return NULL;
}

void MUTABOR_CLASS_FUNCTION(intervalSum,precalculate)(void * _self){
  CHK_CLASS(_self,intervalSum);
  if (isnan(MUT_VALUE(interval,_self)->factor)) {
    if (MUT_VALUE(intervalSum,_self)->left && MUT_VALUE(intervalSum,_self)->right) {
      MUT_VIRTCALL(interval,(MUT_VALUE(intervalSum,_self)->left),precalculate)
	(MUT_VALUE(intervalSum,_self)->left);
      MUT_VIRTCALL(interval,(MUT_VALUE(intervalSum,_self)->right),precalculate)
	(MUT_VALUE(intervalSum,_self)->right);
      MUT_VALUE(interval,_self)->factor=
	MUT_VALUE(intervalSum,_self)->left->factor 
	* MUT_VALUE(intervalSum,_self)->right->factor;
    } else MUT_VALUE(interval,_self)->factor=log(-1);
  }
}

void MUTABOR_CLASS_FUNCTION(intervalSum,setleft)(void * _self,void * _interval){
  CHK_CLASS(_self,intervalSum);
  MUT_VALUE(intervalSum,_self)->left=_interval;
  MUT_VALUE(interval,_self)->factor=log(-1);
}

void MUTABOR_CLASS_FUNCTION(intervalSum,setright)(void * _self,void * _interval){
  CHK_CLASS(_self,intervalSum);
  MUT_VALUE(intervalSum,_self)->right=_interval;
  MUT_VALUE(interval,_self)->factor=log(-1);
}

void * MUTABOR_CLASS_FUNCTION(identifier,check_cycle)
      (register void * _self, register void * _identifier, register MUT_CLASS(ptrlist) * list);
void * MUTABOR_CLASS_FUNCTION(intervalSum,check_cycle)
     (register void * _self, register void * _identifier, register MUT_CLASS(ptrlist) * list)
{
	MUT_CLASS(intervalSum) * self=_self;
	void *i;
	if ((i=MUTABOR_CLASS_FUNCTION(identifier,check_cycle)(_self,_identifier,list))) return i;
	if (self->left == _identifier || self->right == _identifier) return _self;
	if (self->left)
		if (!MUT_VIRTCALL(ptrlist,list,find)(list,self->left)) { 
			if ((i=MUT_VIRTCALL(identifier,self->left,check_cycle)
			     (self->left,_identifier,list))) return i;
			else MUT_VIRTCALL(ptrlist,list,insert)(list,self->left);
		}
	if (self->right)
		if (!MUT_VIRTCALL(ptrlist,list,find)(list,self->right)){
			if ((i=MUT_VIRTCALL(identifier,self->right,check_cycle)
			     (self->right,_identifier,list))) return i;
			else MUT_VIRTCALL(ptrlist,list,insert)(list,self->right);
		}
	return NULL;
}

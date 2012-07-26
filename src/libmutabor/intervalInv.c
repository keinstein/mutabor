/** \file
 ***********************************************************************
 * Identifier class
 *
 * $Id: intervalInv.c,v 1.1 2005/11/03 14:10:01 keinstein Exp $
 * \author Tobias Schlemmer <keinstein@users.berlios.de>
 * \date $Date: 2005/11/03 14:10:01 $
 * \version $Revision: 1.1 $
 *
 * $Log: intervalInv.c,v $
 * Revision 1.1  2005/11/03 14:10:01  keinstein
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
#include <math.h>
#include "mutabor/intervalInv.h"
#include "mutabor/intervalInv.hh"

void MUTABOR_CLASS_FUNCTION(intervalInv,setright) (void * _self, void * interval) 
{
  CHK_CLASS(_self,intervalInv);
  CHK_CLASS(interval,interval);
  MUT_VALUE(intervalPlaceholder,_self)->replacement=interval;
  MUT_VALUE(interval,_self)->factor=log(-1);
}

void MUTABOR_CLASS_FUNCTION(intervalInv,precalculate)(void * _self){
  CHK_CLASS(_self,intervalInv);
  if (MUT_VALUE(intervalPlaceholder,_self)->replacement) {
      MUT_VIRTCALL(interval,(MUT_VALUE(intervalPlaceholder,_self)->replacement),precalculate)
	(MUT_VALUE(intervalPlaceholder,_self)->replacement);
      MUT_VALUE(interval,_self)->factor=
	MUTABOR_FLOAT_DIVIDE(1,MUT_VALUE(intervalPlaceholder,_self)->replacement->factor);
  } else MUT_VALUE(interval,_self)->factor=log(-1);
}

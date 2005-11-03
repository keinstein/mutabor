/** \file
 ********************************************************************
 * complex intervals.
 *
 * $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/libmutabor/intervalDiff.c,v 1.1 2005/11/03 14:08:44 keinstein Exp $
 * \author Tobias Schlemmer <keinstein@users.berlios.de>
 * \date $Date: 2005/11/03 14:08:44 $
 * \version $Revision: 1.1 $
 *
 * $Log: intervalDiff.c,v $
 * Revision 1.1  2005/11/03 14:08:44  keinstein
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
#include "mutabor/intervalDiff.h"
#include "mutabor/intervalDiff.hh"

void MUTABOR_CLASS_FUNCTION(intervalDiff,precalculate)(void * _self){
  CHK_CLASS(_self,intervalDiff);
  if (isnan(MUT_VALUE(interval,_self)->factor)) {
    if (MUT_VALUE(intervalSum,_self)->left && MUT_VALUE(intervalSum,_self)->right) {
      MUT_VIRTCALL(interval,(MUT_VALUE(intervalSum,_self)->left),precalculate)
	(MUT_VALUE(intervalSum,_self)->left);
      MUT_VIRTCALL(interval,(MUT_VALUE(intervalSum,_self)->right),precalculate)
	(MUT_VALUE(intervalSum,_self)->right);
      MUT_VALUE(interval,_self)->factor=
	MUT_VALUE(intervalSum,_self)->left->factor 
	/ MUT_VALUE(intervalSum,_self)->right->factor;
    } else MUT_VALUE(interval,_self)->factor=log(-1);
  }
}

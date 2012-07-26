/** \file
 ********************************************************************
 * Alles zu Anweisungen.
 *
 * $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/includes/mutabor/anweisung.h,v 1.3 2006/03/27 16:53:05 keinstein Exp $
 * \author Tobias Schlemmer <keinstein_junior@gmx.net>
 * \date $Date: 2006/03/27 16:53:05 $
 * \version $Revision: 1.3 $
 * \log 
 * $Log: anweisung.h,v $
 * Revision 1.3  2006/03/27 16:53:05  keinstein
 * insert_in_lokale_liste moved from ausloeser to anweisung
 *
 * Revision 1.2  2005/07/08 14:48:35  keinstein
 * Neu:
 * 	Kopf (CVS)
 * 	get_last_anweisungs_liste
 *
 ********************************************************************/

#ifndef __ANWEISUNG_H_INCLUDED
#define __ANWEISUNG_H_INCLUDED

#include "mutabor/ausloeser.h"
#include "mutabor/aktion.h"

#ifdef __cplusplus
namespace mutabor {
  extern "C" {
#endif


    /** Anweisungen als einfach verkettete Liste. Anweisungen 
     *  enthalten einen Auslöser und eine Aktion.
     */
    struct anweisung {
      struct ausloeser * ausloeser;    /**< Auslösendes Ereignis */
      struct aktions_liste * aktion;   /**< Ausgelöste Aktion */
      struct anweisung * next;         /**< Nächste Anweisung */
    };
    
    struct anweisung * get_last_anweisungs_liste (void);
    void init_anweisungs_liste (void);
    void get_new_anweisung (void);
    void insert_in_lokale_liste (int instrument, struct anweisung * lauf,
				 char * name_der_logik);


#ifdef __cplusplus 
  } // extern "C"
} // namespace mutabor
#endif

#endif /* __ANWEISUNG_H_INCLUDED */

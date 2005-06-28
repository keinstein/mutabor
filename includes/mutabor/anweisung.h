/** \file
 ********************************************************************
 * Alles zu Anweisungen.
 *
 * \author Tobias Schlemmer <keinstein_junior@gmx.net>
 * \date 2005
 * \version 0.1
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
    
void init_anweisungs_liste (void);
void get_new_anweisung (void);


#ifdef __cplusplus 
  } // extern "C"
} // namespace mutabor
#endif

#endif /* __ANWEISUNG_H_INCLUDED */

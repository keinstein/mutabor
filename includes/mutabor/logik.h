/** \file
 ********************************************************************
 * Alles zu Logiken.
 *
 * \author Tobias Schlemmer <keinstein_junior@gmx.net>
 * \date 2005
 * \version 0.1
 ********************************************************************/

#ifndef __LOGIK_H_INCLUDED
#define __LOGIK_H_INCLUDED

#include "mutabor/ausloeser.h"
#include "mutabor/aktion.h"

#ifdef __cplusplus
namespace mutabor {
  extern "C" {
#endif


    /*********  Definition der Logiken als verkettete Liste ********/
    /** Logiken als einfach verkettete Liste. */
    struct logik {
      char * name; /**< Name der Logik */ 
      struct ausloeser * ausloeser; /**< Auslösendes Ereignis */
      char * einstimmungs_name;     /**< Name der Einstimmung */
      struct anweisung * anweisungsliste; /**< Liste der Einzel-Anweisungen */
      struct logik * next; /** nächste Logik */
    };

    void vervollstaendige_logik (void);
    void get_new_logik (char * name, char * einstimmung);
    int logik_list_laenge (struct logik *list);
    int get_logik_nummer (char * name, struct logik * liste);
    struct logik * get_logik (char * name, struct logik * liste);

    extern struct logik          *  list_of_logiken;

#ifdef __cplusplus 
  } // extern "C"
} // namespace mutabor
#endif

#endif /* __LOGIK_H_INCLUDED */

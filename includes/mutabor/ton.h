/** \file
 ********************************************************************
 * Alles zu Tönen.
 *
 * \author Tobias Schlemmer <keinstein_junior@gmx.net>
 * \date 2005
 * \version 0.1
 ********************************************************************/

#ifndef __TON_H_INCLUDED
#define __TON_H_INCLUDED

#include "mutabor/interval.h"

#ifdef __cplusplus
namespace mutabor {
  extern "C" {
#endif

    /** Töne können absolut oder als Folge von Intervallen relativ zu
	einem Grundton angegeben werden. */
    enum ton_typ {
      ton_absolut, /**< Absoluter Ton */
      ton_komplex /**< Intervallfolge */
    };

    /**
     * Ein Ton. Er kriegt einen Namen und je nach Typ einen Wert oder
     * einen Grundton und ein \c komplex_intervall.  Einfach
     * verkettete Liste.
     */

    struct ton {
      char * name; /**< Name des Tones */
      enum ton_typ ton_typ; /**< Typ des Tones (absolut oder Intervallfolge */
      union {
        struct {
	  double ton_wert; /**< Wert des absoluten Tones */
        } ton_absolut; /**< absoluter Ton */
        struct {
	  char * bezugston; /**< Ausgangston der Intervallfolge */
	  struct komplex_intervall * komplex_liste; /**< Intervallfolge */
        } ton_komplex; /**< Grundton+Intervallfolge */
      } u;
      struct ton * next; /** Nächste Ton */
    };

    void get_new_ton_absolut (char * name, double wert);
    void init_komplex_ton_list (void);
    void get_new_ton_komplex_positive (char *name, char *bezugston);
    void get_new_ton_komplex_negative (char *name, char *bezugston);
    
    void init_ton_liste (void);
    void get_new_ton_in_tonsystem (char *name);

    int ton_list_laenge (struct ton *list);
    
    struct ton * get_ton (char * name, struct ton * liste);

    extern struct ton            *  list_of_toene;

#ifdef __cplusplus 
  } // extern "C"
} // namespace mutabor
#endif

#endif /* __TON_H_INCLUDED */

/** \file
 ********************************************************************
 * Tasten usw.
 *
 * \author Tobias Schlemmer <keinstein_junior@gmx.net>
 * \date 2005
 * \version 0.1
 ********************************************************************/

#ifndef __TASTE_H_INCLUDED
#define __TASTE_H_INCLUDED

#ifdef __cplusplus
namespace mutabor {
  extern "C" {
#endif

    /** Einzelne Tasten als einfach verkettete Liste. */
    struct taste {
      int taste;           /**< Tastennummer (Schlüssel-C = 60) */
      char stern;          /**< TRUE oder FALSE, ob Stern deklariert ist.  */
      struct taste * next; /**< Nächste Taste */
    };

    void init_tastenliste (void);
    void get_new_taste (int taste, char stern);
    int enthalten_in_tastenliste (int taste, struct taste * lauf);
    
    struct taste * tmp_tastenliste;
#ifdef __cplusplus 
  } // extern "C"
} // namespace mutabor
#endif

#endif /* __TASTE_H_INCLUDED */

/** \file
 ********************************************************************
 * Alles zu Argumenten.
 *
 * $Id: argument.h,v 1.3 2005/11/03 14:24:30 keinstein Exp $
 * \author Tobias Schlemmer <keinstein@users.sourceforge.net>
 * \date $Date: 2005/11/03 14:24:30 $
 * \version $Revision: 1.3 $
 *
 * $Log: argument.h,v $
 * Revision 1.3  2005/11/03 14:24:30  keinstein
 * new Header
 * includes corrected
 * interpreter functions and data structures
 *
 ********************************************************************/

struct argument_liste;
#ifndef __ARGUMENT_H_INCLUDED
#define __ARGUMENT_H_INCLUDED

#include "mutabor/parameter.h"

#ifdef __cplusplus
namespace mutabor {
  extern "C" {
#endif

    /** Argumententypen: Zahl oder Zeichenkette. */
    enum argument_typ {zahl, parameter};

    /** Einzelnes Argument. */
    struct argument {
      enum argument_typ argument_typ ; /**< Typ Zahl oder Parameter? */
      union {
	struct {
	  int zahl; /**< Wert der Zahl */
	} zahl;     /**< Zahl */
	struct {
	  int parameter_nummer;   /**< Der soundsovielte,
				     der deklariert ist. */
	  char * parameter_name; /**< Parameter-Name */
	} parameter; /**< Parameter */
      } u; /**< Wert des Argumentes */
    };

    /**< Einfach verkettete Liste von Argumenten. */
    struct argument_liste {
      struct argument argument; /**< Aktuelles Argument */
      struct argument_liste * next; /**< Das nächste Argument in der Liste */
    };
    
    void drucke_argument (struct argument * z_or_p);

    void init_argument_liste (void);
    void get_new_name_in_argument_list (char * parameter);
    void get_new_number_in_argument_list (double parameter);

    int * get_wert_of_argument(
                 struct argument * argument,
                 struct interpreter_parameter_liste * aktuelle_parameter
                 );
    int argument_list_laenge (struct argument_liste *list);

    struct argument_liste * get_last_argument_liste (void);

#ifdef __cplusplus 
  } // extern "C"
} // namespace mutabor
#endif

#endif /* __ARGUMENT_H_INCLUDED */

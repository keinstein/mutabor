/** \file
 ********************************************************************
 * Alles zu Argumenten.
 *
 * \author Tobias Schlemmer <keinstein_junior@gmx.net>
 * \date 2005
 * \version 0.1
 ********************************************************************/

#ifndef __ARGUMENT_H_INCLUDED
#define __ARGUMENT_H_INCLUDED


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
    
    void init_argument_liste (void);
    void get_new_name_in_argument_list (char * parameter);
    void get_new_number_in_argument_list (double parameter);

#ifdef __cplusplus 
  } // extern "C"
} // namespace mutabor
#endif

#endif /* __ARGUMENT_H_INCLUDED */

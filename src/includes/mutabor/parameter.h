/** \file
 ********************************************************************
 * Alles zu Parametern.
 *
 * $Id: parameter.h,v 1.3 2005/11/03 14:35:54 keinstein Exp $
 * \author Tobias Schlemmer <keinstein_junior@gmx.net>
 * \date $Date: 2005/11/03 14:35:54 $
 * \version $Revision: 1.3 $
 * 
 * $Log: parameter.h,v $
 * Revision 1.3  2005/11/03 14:35:54  keinstein
 * new file header
 * includes corrected
 * interpreter data structures and functions
 *
 ********************************************************************/

struct interpreter_parameter_liste;
#ifndef __PARAMETER_H_INCLUDED
#define __PARAMETER_H_INCLUDED

#include "mutabor/argument.h"
#include "mutabor/bad_decl.h"

#ifdef __cplusplus
namespace mutabor {
  extern "C" {
#endif
    /** Einfach verkettete Liste mit Parameternamen */
    struct parameter_liste {
      char * name;                    /**< Name des Parameters */
      struct parameter_liste * next;  /**< Nächster Parameter */
    };

    /** Einfach verkettete Liste mit Parametern */
    struct interpreter_parameter_liste {
      int (* werte_feld) [MAX_BOX]; /**< Werte für jede Box */
      struct interpreter_parameter_liste * next; /**< Nächster Parameter */
    };

    /** Ganzzahliger Parametertyp */
    typedef int parameter_typ;

    void init_parameter_liste (void);
    void get_new_name_in_parameterlist (char * name);
    void get_new_number_in_parameterlist (double wert);

    int parameter_list_laenge (struct parameter_liste *list);

    int parameter_nummer (int aktueller_index, char * such_name, 
			  struct parameter_liste * knoten);
    struct parameter_liste * get_last_parameter_liste (void);
    struct interpreter_parameter_liste * gen_parameter_liste (
			struct argument_liste * liste,
			struct interpreter_parameter_liste * bezugs_liste);
    extern struct interpreter_parameter_liste * start_parameter_liste;
#ifdef __cplusplus 
  } // extern "C"
} // namespace mutabor
#endif

#endif /* __PARAMETER_H_INCLUDED */

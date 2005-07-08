/** \file
 ********************************************************************
 * Verzweigungsliste für Umstimmungen und ähnliches.
 *
 * $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/includes/mutabor/case_liste.h,v 1.2 2005/07/08 14:51:41 keinstein Exp $
 * \author Tobias Schlemmer <keinstein_junior@gmx.net>
 * \date $Date: 2005/07/08 14:51:41 $
 * \version $Revision: 1.2 $
 * \log 
 * $Log: case_liste.h,v $
 * Revision 1.2  2005/07/08 14:51:41  keinstein
 * Neu:
 * 	Kopf
 * 	case_label_enthalten_in_case_liste
 * 	Abhängig von aktion.h
 *
 ********************************************************************/

#ifndef __CASE_LISTE_H_INCLUDED
#define __CASE_LISTE_H_INCLUDED

#include "mutabor/aktion.h"

#ifdef __cplusplus
namespace mutabor {
  extern "C" {
#endif


    /** Verzweigungsliste für Umstimmungen */
    struct case_liste {
      int case_label; /**< Bezeichnug/Wert des Zweiges */
      char is_default; /**< !=0, wenn Standard-Zweig */
      struct aktions_liste * case_aktion; /**< auszulösende Aktion */
      struct case_liste * next; /**< Der nächste Zweig */
    };

    void init_umstimmungs_case_liste (void);
    void get_umstimmung_umstimm_case_zahl (int selector);
    void get_umstimmung_umstimm_case_parameter (char * selector);
    void init_umstimmungs_case_aktions_liste (void);
    void get_umstimmungs_case_zahl_element (int konstante); 
    void get_umstimmungs_case_default_element (void);
    void get_umstimmungs_case_aktions_element (char * aktion);
    int case_label_enthalten_in_case_liste (double case_label, struct case_liste * lauf);

#ifdef __cplusplus 
  } // extern "C"
} // namespace mutabor
#endif

#endif /* __CASE_LISTE_H_INCLUDED */

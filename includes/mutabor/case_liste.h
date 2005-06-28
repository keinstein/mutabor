/** \file
 ********************************************************************
 * Verzweigungsliste für Umstimmungen und ähnliches.
 *
 * \author Tobias Schlemmer <keinstein_junior@gmx.net>
 * \date 2005
 * \version 0.1
 ********************************************************************/

#ifndef __CASE_LISTE_H_INCLUDED
#define __CASE_LISTE_H_INCLUDED


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
    
#ifdef __cplusplus 
  } // extern "C"
} // namespace mutabor
#endif

#endif /* __CASE_LISTE_H_INCLUDED */

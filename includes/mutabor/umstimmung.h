/** \file
 ********************************************************************
 * Alles zu Umstimmungen. Umstimmungen werden als verkettete Liste
 * implementiert.
 *
 * \author Tobias Schlemmer <keinstein_junior@gmx.net>
 * \date 2005
 * \version 0.1
 ********************************************************************/

#ifndef __UMSTIMMUNG_H_INCLUDED
#define __UMSTIMMUNG_H_INCLUDED

struct umstimmung; 
#include "ton.h"
#include "case_liste.h"

#ifdef __cplusplus
namespace mutabor {
  extern "C" {
#endif

    /*********  Definition der Umstimmungen als verkettete Liste ********/
    
    /** Typ einer Umstimming. */
    enum umstimmung_typ {
      umstimmung_taste_abs, /**< eine Ankertaste absolut stimmen */
      umstimmung_taste_rel, /**< eine Ankertaste relativ stimmen */
      umstimmung_breite_abs, /**< verändern der Periodenlänge/breite (absolut) */
      umstimmung_breite_rel, /**< verändern der Periodenlänge/breite (relativ) */
      umstimmung_toene_veraendert, /**< Töne verändern */
      umstimmung_wiederholung_abs, /**< Wiederholung absolut*/
      umstimmung_wiederholung_rel, /**< Wiederholung relativ */
      umstimmung_umstimmungsbund,  /**< Mehrere Umstimmungsschritte */
      umstimmung_umstimmungs_case, /**< Bedingte Umstimmungen */
      umstimmung_midi_out          /**< Keine Umstimmung, MIDI-Ausgabe */
    };

    /** Definition der Umstimmungen als verkettete Liste.
     *
     */
    struct umstimmung {
      char *name; /**< Name der Umstimmung */
      struct parameter_liste * parameter_liste; /**< Liste der Parameter */
      enum umstimmung_typ umstimmung_typ; /**< Typ der Umstimmung */
      union {
        struct {
	  struct argument argument; /**< Argument einer absoluten Tasten-Umstimmung */
        } umstimmung_taste_abs; /**< Daten für absolute Tasten-Umstimmung */
        struct {
	  struct argument argument; /**< Argument einer relativen Tasten-Umstimmung */
	  char rechenzeichen;       /**< Vorzeichen für die Berechnugn */
        } umstimmung_taste_rel;     /**< Daten für relative Tasten-Umstimmung */
        struct {
	  struct argument argument; /**< Argument einer absoluten Breiten-Änderung */
        } umstimmung_breite_abs;    /**< Daten einer absoluten Breiten-Änderung */
        struct {                    
	  struct argument argument; /**< Argument einer relativen Breiten-Änderung */
	  char rechenzeichen;       /**< Vorzeichen für die Berechnung */
        } umstimmung_breite_rel;    /**< Daten einer relativen Breiten-Änderung */
        struct {
	  struct ton * tonliste;    /**< Neue Töne bei Tonveränderung */
        } umstimmung_toene_veraendert; /**< Daten einer Tonveränderung */
        struct {
	  struct komplex_intervall * komplex_liste;
        } umstimmung_wiederholung_abs;
        struct {
	  struct komplex_intervall * komplex_liste;
        } umstimmung_wiederholung_rel;
        struct {
	  struct aktions_liste * aktions_liste;
        } umstimmung_umstimmungsbund;
        struct {
	  struct argument argument;
	  struct case_liste * umstimmungs_case_liste;
        } umstimmung_umstimmungs_case;
        struct {
	  struct midiliste * out_liste;
        } umstimmung_midi_out;
      } u;
      struct umstimmung * next;
    };
    
    void init_umstimmung (char * name);
    void eintrage_parameterliste_in_umstimmung (void);
    void get_new_umstimmung (void);
    
    void get_umstimmung_taste_abs (
				   enum argument_typ argument, 
				   /* zahl_oder_parameter_typ zahl_oder_parameter, */
				   double zahl_wert, char * parameter);
    void get_umstimmung_taste_rel (
				   enum argument_typ argument,
				   double zahl_wert, char * parameter, char vorzeichen);
    void get_umstimmung_breite_abs (
				    enum argument_typ argument,
				    double zahl_wert, char * parameter);
    void get_umstimmung_breite_rel (
				    enum argument_typ argument,
				    double zahl_wert, char * parameter, char vorzeichen);
    void init_umstimm_expression_list (void);
    void get_umstimmung_tonhoehe_veraendert (void);
    void get_new_umstimm_expression (char * bezugston);
    void get_new_umstimm_expression_positive (char * bezugston);
    void get_new_umstimm_expression_negative (char * bezugston);
    void get_umstimmung_wiederholung_abs (void);
    void get_umstimmung_wiederholung_abs_negative (void);
    void get_umstimmung_wiederholung_rel_positive (void);
    void get_umstimmung_wiederholung_rel_negative (void);
    void get_umstimmung_umstimmungs_bund (void);
    void get_umstimmung_midi_out (void);
    int umstimmungs_list_laenge (struct umstimmung *list);
    struct umstimmung * get_umstimmung (char * name, struct umstimmung * liste);
    void check_umstimmungs_konsistenz(void);

    /** Wurzel der Umstimmungen */
    struct umstimmung     *  list_of_umstimmungen;
    struct umstimmung * tmp_umstimmung;
#ifdef __cplusplus 
  } // extern "C"
} // namespace mutabor
#endif

#endif /* __UMSTIMMUNG_H_INCLUDED */

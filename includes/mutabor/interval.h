/** \file
 ********************************************************************
 * Intervallberechnungen
 * \author R.Krauße
 * \date 1997
 * \version 2.win
 * 
 ********************************************************************/

#if ! defined (__INTERVAL_H_INCLUDED)
#define __INTERVAL_H_INCLUDED

#ifdef __cplusplus 
namespace mutabor {
  extern "C" {
#endif

/*********  Definition der Intervalle als verkettete Liste ********/

/** Intervalle können absolut oder über mehrere Sprünge angegeben werden. */
enum intervall_typ {intervall_absolut, intervall_komplex};

/** Folge von Intervallen, die zum Grundton addiert werden. */
struct komplex_intervall {
  double faktor; /**< exponent des Frequenzfaktors */
  char * name; /**< Name des Intervalles */
  struct komplex_intervall * next; /**< Liste der Einzel-Intervalle */
};

/** Definition der Intervalle als einfach verkettete Liste.
 * 
 */ 
struct intervall {
  char * name; /**< Name des Intervalls */
  enum intervall_typ intervall_typ; /**< Typ des Intervalles */
    union {
        struct {
	  double intervall_wert; /**< Wert eines absoluten Intervalles */
        } intervall_absolut; /**< Daten des absoluten Intervalles */
        struct {
	  struct komplex_intervall * komplex_liste; /**< Liste der Intervalle */
        } intervall_komplex; /**< Daten eines zusammengesetzten Intervalles */
    } u; /**< Daten des Intervalles */
  struct intervall *next; /**< Nächstes in der Liste */
};

void get_new_intervall (char * name, double wert);
void get_new_intervall_komplex (char * name);
double get_wert_komplex_intervall (struct komplex_intervall * intervall);
void get_new_faktor_anteil (double f, char *name);

struct intervall * get_intervall (char * name,
                                      struct intervall * liste);
int intervall_list_laenge (struct intervall *list);
void berechne_intervalle_absolut (struct intervall * list_of_intervalle);
void check_komplex_intervall (struct komplex_intervall * liste,
                              char * konstrukt_name);

extern struct intervall      *  list_of_intervalle;

#ifdef __cplusplus
  }
}
#endif

#endif

// ------------------------------------------------------------------
// Mutabor 2.win, 1997, R.Krauﬂe
// Intervallberechnungen
// ------------------------------------------------------------------

#if ! defined (__INTERVAL_H_INCLUDED)
#define __INTERVAL_H_INCLUDED

int intervall_list_laenge (struct intervall *list);

void berechne_intervalle_absolut (struct intervall * list_of_intervalle);

void check_komplex_intervall (struct komplex_intervall * liste,

                              const char * konstrukt_name);

#endif


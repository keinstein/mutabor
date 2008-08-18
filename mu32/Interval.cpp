// ------------------------------------------------------------------
// Mutabor 2.win, 1997, R.Krauße
// Intervallberechnungen
// ------------------------------------------------------------------

#include "Global.h"
#include "GrafKern.h"
#include "Interval.h"
#include "Hilfs.h"

static double get_intervall_wert (const char * name)
{
  struct intervall *lauf;

  for (lauf = list_of_intervalle; lauf; lauf = lauf -> next) {
      if ( ! strcmp (name, lauf->name)) {
          switch (lauf -> intervall_typ) {
          default: /* und */
          case intervall_komplex:
	    fatal_error (0, mutC_STR(__FILE__), __LINE__);
          break;
          case intervall_absolut:
              return lauf->u.intervall_absolut.intervall_wert ;
          /* break; */
          }
      }
  }

  fatal_error(26,mutC_STR(name)); /* Intrvall n.dekl. */
  return 0.0; /* to prevent warnings */
}


double get_wert_komplex_intervall (struct komplex_intervall * intervall)
{
    double ret = 1.0;

    for ( ; intervall ; intervall = intervall -> next ) {
        double help = get_intervall_wert (intervall -> name);
        if (help > 0)
            ret *= pow (help, intervall -> faktor);
        else {
	  fatal_error(46, mutC_STR(intervall -> name));
                    /* unzul. Intervallwert */
        }

    }

    return ret;
}



/**************************************************************

            Hier werden die Intervalle aufgel”st.
            Nach dem Parsing ist nur die Syntax-Struktur
            vorhanden, aber keine fertig ausgerechneten Intervalle.

            Es wird ein azyklischer Graph der Intervalle und ihrer
            UnterIntervalle gebildet, der dann nach den
            depth-first-search traversiert wird.
            Dabei bekommt jedes Intervall seinen AbsolutFaktor berechnet.

****************************************************************/

static int anzahl_intervalle;       /* so viele Intervalle wurden gelesen */

static struct intervall ** intervalle;    /* Feld von Intervallen zum schnelleren Zugriff
                                  als ueber Listen */

static char * visited;         /* Traversierungsmerker */

static char * matrix;          /* Adjazenzmatrix (auf sie darf nur ueber
                                  das folgende Makro zugegriffen werden !*/

#define adjazent(a,b) matrix [ (a) * anzahl_intervalle * sizeof (char) \
                             + (b) * sizeof (char)]

int intervall_list_laenge (struct intervall *list)
{ if (list) return 1 + intervall_list_laenge (list -> next);
  return 0;
}



static void belege_intervalle (struct intervall **intervalle, struct intervall * liste)
{
  while (liste) {
      *intervalle = liste;
      intervalle++;
      liste = liste->next;
  }
}

static int intervall_nummer (const char *name)
{ int i;

  for (i=0; i<anzahl_intervalle; i++)
      if ( ! strcmp (name, intervalle[i]->name)) return i;

  fatal_error(26,mutC_STR(name)); /* Ton n.dekl. */

  return 0; /* to prevent warnings */
}

static void test_zyklen (int startknoten)
{
    int i;
    for (i=0; i<anzahl_intervalle; i++) {
        if (adjazent (startknoten, i)) {
            if (visited [i]) {
	      fatal_error(67,mutC_STR(intervalle [startknoten]->name),
                               intervalle [i]->name);
            }
            visited [i] = 1;
            test_zyklen (i);
            visited [i] = 0;
        }
    }
}

static void berechne_intervall_endgueltig (int k)
{ int b;
  double help;

  switch (intervalle[k]->intervall_typ) {

    case intervall_absolut:         /* hier nichts zu tun */
      break;

    case intervall_komplex: {
        struct komplex_intervall * lauf;
        for (lauf = intervalle[k]->u.intervall_komplex.komplex_liste;
             lauf;
             lauf = lauf -> next) {
            b = intervall_nummer (lauf -> name);
            berechne_intervall_endgueltig (b);
        }

        help = get_wert_komplex_intervall (intervalle[k]->u.intervall_komplex.komplex_liste);

        intervalle[k]->intervall_typ = intervall_absolut;
        intervalle[k]->u.intervall_absolut.intervall_wert = help;
      }
      break;

    default:
      fatal_error(0,_("loop"));
  }
}

void berechne_intervalle_absolut (struct intervall * list_of_intervalle)
{
  int i,j,k;

  anzahl_intervalle = intervall_list_laenge (list_of_intervalle);
  intervalle = (intervall* *) xalloca (sizeof(struct intervall *) * anzahl_intervalle);
  visited = (char*) xalloca (sizeof(char) * anzahl_intervalle);
  matrix = (char*) xalloca (sizeof(char) * anzahl_intervalle * anzahl_intervalle);


/* Feld mit intervallen initialisieren (zum schnelleren Zugriff) */

  belege_intervalle (intervalle, list_of_intervalle);

/* Adjazenzmatrix initialisieren (Kein Intervall h„ngt vom anderen ab) */

  for (i=0; i<anzahl_intervalle; i++) {
      for (j=0; j<anzahl_intervalle; j++) {
          adjazent (i,j) = 0;
      }
  }

/* Adjazenzmatrix initialisieren (Abh„ngigkeiten eintragen) */

  for (i=0; i<anzahl_intervalle; i++) {
      if (intervalle[i]->intervall_typ == intervall_absolut)  /* alles ok */ ;
      else if (intervalle[i]->intervall_typ == intervall_komplex) {
          struct komplex_intervall * lauf;
          for (lauf = intervalle[i]->u.intervall_komplex.komplex_liste;
               lauf;
               lauf = lauf -> next) {
              adjazent (i, intervall_nummer (lauf -> name)) = 1;
          }
      }
      else {
	fatal_error(0,_("loop"));
      }
  }

#ifdef DEBUG_ANZEIGE_3
/* Adjazenzmatrix anzeigen */

  printf ("Matrix:\n");

  for (i=0; i<anzahl_intervalle; i++) {
      printf ("%s -> ", intervalle[i]->name);
      for (j=0; j<anzahl_intervalle; j++) {
          if (adjazent (i,j))
              printf ("%s  ", intervalle[j]->name);
      }
      printf ("\n");
  }
  printf ("\n");

#endif

/* auf Zyklenfreiheit Pruefen */

  for (k=0; k<anzahl_intervalle; k++)
      visited [k] = 0;

  for (k=0; k<anzahl_intervalle; k++) {
      visited [k] = 1;
      test_zyklen (k);
      visited [k] = 0;
  }

/* Toene endgueltig berechnen */

  for (k=0; k<anzahl_intervalle; k++)
      berechne_intervall_endgueltig (k);

#ifdef DEBUG_ANZEIGE_3
                        /* Adjazenzmatrix anzeigen */

  printf ("Matrix:\n");

  for (i=0; i<anzahl_intervalle; i++) {
      printf ("%s -> ", intervalle[i]->name);
      for (j=0; j<anzahl_intervalle; j++) {
          if (adjazent (i,j))
              printf ("%s  ", intervalle[j]->name);
      }
      printf ("\n");
  }
  printf ("\n");
#endif

  xde_alloca (intervalle);
  xde_alloca (visited);
  xde_alloca (matrix);

}

/*****************************************/

void check_komplex_intervall (struct komplex_intervall * liste,
                              const char * konstrukt_name)
{
    for ( ; liste ; liste = liste -> next ) {
        struct intervall * help = get_intervall (liste -> name, list_of_intervalle);
        if (help == NULL) {
	  fatal_error (32, mutC_STR(liste -> name), mutC_STR(konstrukt_name));
            return;
        }
        if (help -> intervall_typ != intervall_absolut) {
	  fatal_error (0, _T(__FILE__), __LINE__);
	  return;
        }
    }
}


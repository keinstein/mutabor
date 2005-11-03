/** \file
 ********************************************************************
 * Intervallberechnungen
 *
 * $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/libmutabor/interval.c,v 1.6 2005/11/03 14:49:57 keinstein Exp $
 * \author R.Krauße <krausze@users.berlios.de>
 * \date $Date: 2005/11/03 14:49:57 $
 * \version $Revision: 1.6 $
 *
 * \todo make this file thred-proof
 * \todo Portabilisierung von: pow
 ********************************************************************/
#ifdef HAVE_CONFIG_H
#include "config.h"
  /* Relevante Variablen für diese Datei:
   * HAVE_POW
   * size_t
   * HAVE_STRING_H
   */
#endif

#ifdef HAVE_STRING_H
#  include<string.h>
#endif

#include<math.h>
#include<assert.h>
#include "mutabor/interval.h"
#include "mutabor/interval.hh"
#include "mutabor/heap.h"
#include "mutabor/parser.h"
#include "mutabor/errors.h"

void * MUTABOR_CLASS_FUNCTION(identifier,constructor)(void * _self);
void * MUTABOR_CLASS_FUNCTION(interval,constructor)(void * _self) {
  MUT_CLASS(interval) *self;
  CHK_CLASS(_self,interval);
  self=MUTABOR_CLASS_FUNCTION(identifier,constructor)(_self);
  assert(self);
  self->factor=log(-1);
  return self;
}

/** Comparison between two objects. Simple comparison by pointers. */

int MUTABOR_CLASS_FUNCTION(interval,compare)(void * _one, void * _two){
  MUT_CLASS(interval) *one=_one,*two=_two;
  CHK_CLASS(_one,interval);
  CHK_CLASS(_two,interval);
  return MUTABOR_FLOAT_FACTOR_COMPARE(one->factor,two->factor);
}

/** Formats Class content as string. Intented exspecially for debugging. */

char * MUTABOR_CLASS_FUNCTION(interval,tostring)(void * _self){
  register MUT_VIRTTABLE(object) ** self=_self;
  char * data;
  CHK_CLASS(_self,interval);
  if (asprintf(&data,"%s (%p): %s (%p,%p) factor: %12.8g",
	       (*self)->name, 
	       (void *)*self,
	       ((MUT_CLASS(identifier)*) _self)->name,
	       _self,
	       (void *)(((MUT_CLASS(identifier)*) _self)->name),
	       MUT_VALUE(interval,_self)->factor)){
    return data;
  }
  else 
    return NULL;
}

void MUTABOR_CLASS_FUNCTION(interval,set_factor)(void * _self,MUTABOR_FLOAT value){
  CHK_CLASS(_self,interval);
  MUT_VALUE(interval,_self)->factor=value;
}


/** Wurzel der Intervallliste */
struct intervall      *  list_of_intervalle;

/** Sucht ein Intervall aus einer Intervallliste.
 * \param name Name des gesuchten Intervalles
 * \param liste Liste der Intervalle, in der das Intervall gesucht wird
 * \retval NULL, falls Intervall nicht in \a liste
 * \retval Intervall, sonst.
 */
struct intervall * get_intervall (char * name,
                                      struct intervall * liste)
{
    if (liste == NULL) return NULL;
    if ( ! strcmp (name, liste->name)) return liste;
    return get_intervall (name, liste->next);
}

/** Sucht den Wert eines absoluten Intervalles aus der globalen Intervallliste.
 * Falls das erste gefundene Intervall nicht absolut ist, wird 
 * ein fataler Fehler ausgegeben.
 * \param name Name des gesuchten Intervalles
 * \retval Frequenzverhältnis des Intervalles
 */
static double get_intervall_wert (char *name)
{
  struct intervall *lauf;
#if (DEBUG)
  if (mutabor_debug_level)
    fprintf(stderr,"Reading interval: %s",name);
#endif
  
  for (lauf = list_of_intervalle; lauf; lauf = lauf -> next) {
#if (DEBUG)
  if (mutabor_debug_level)
    fprintf(stderr,"Reading interval: %s (%s)\n",name,lauf->name);
#endif
      if ( ! strcmp (name, lauf->name)) {
          switch (lauf -> intervall_typ) {
          default: /* und */
          case intervall_komplex:
#if (DEBUG)
	    if (mutabor_debug_level)
	      fprintf(stderr,"\n");
#endif
              fatal_error (0, __FILE__, __LINE__);
          break;
          case intervall_absolut:
#if (DEBUG)
	    if (mutabor_debug_level)
	      fprintf(stderr,"%f\n",lauf->u.intervall_absolut.intervall_wert);
#endif
              return lauf->u.intervall_absolut.intervall_wert ;
          /* break; */
          }
      }
  }
  
#if (DEBUG)
	    if (mutabor_debug_level)
	      fprintf(stderr,"\n");
#endif
  fatal_error(MUTABOR_ERROR_UNDEFINED_INTERVAL,name); /* Intrvall n.dekl. */
  return 0.0; /* to prevent warnings */
}


/** Berechnet den Wert eines komplexen Intervalles aus der globalen Intervallliste.
 * Falls ein Intervallwert nicht positiv ist, wird 
 * ein fataler Fehler ausgegeben.
 * \param intervall
 * \retval Frequenzverhältnis des Intervalles
 */
double get_wert_komplex_intervall (struct komplex_intervall * intervall)
{
    double ret = 1.0;

#ifdef DEBUG
  if (mutabor_debug_level) 
    fprintf (stderr,"Get value of complex interval.\n");
#endif
    for ( ; intervall ; intervall = intervall -> next ) {
        double help;
#ifdef DEBUG
	if (mutabor_debug_level) 
	  fprintf (stderr,"    %s*%f\n",intervall->name,intervall->faktor);
#endif
	help = get_intervall_wert (intervall -> name);
        if (help > 0)
            ret *= pow (help, intervall -> faktor);
        else {
              fatal_error(MUTABOR_ERROR_INVALID_INTERVAL_VALUE,
			  intervall -> name); 
                    /* unzul. Intervallwert */
        }
          
    }

#ifdef DEBUG
	if (mutabor_debug_level) 
	  fprintf (stderr,"           %f",ret);
#endif
    return ret;
}

/** Berechnet den Intervall-Faktor eines komplexen Intervalles. 
 * Bei Inkonsistenzen wird ein fataler Fehler ausgegeben.
 * \param lauf Komplexes Intervall, das bei der Berechnung durchlaufen 
 *             werden soll.
 */
double get_komplex_faktor (struct komplex_intervall * lauf) {
    double ret = 1.0;
    for ( ; lauf ; lauf = lauf -> next ) {
        struct intervall * help = get_intervall (lauf->name, list_of_intervalle);
        if (help && help -> intervall_typ == intervall_absolut) {
            ret *= pow (help -> u.intervall_absolut.intervall_wert,
                        lauf->faktor);
        }
        else {
            fatal_error (0, __FILE__, __LINE__);
        }
        
    }
    return ret;
}


/**************************************************************

            Hier werden die Intervalle aufgelöst.
            Nach dem Parsing ist nur die Syntax-Struktur
            vorhanden, aber keine fertig ausgerechneten Intervalle.
            
            Es wird ein azyklischer Graph der Intervalle und ihrer
            UnterIntervalle gebildet, der dann nach den
            depth-first-search traversiert wird.
            Dabei bekommt jedes Intervall seinen AbsolutFaktor berechnet.
            
****************************************************************/

static int anzahl_intervalle;       /**< so viele Intervalle wurden gelesen */

static struct intervall ** intervalle;    /**< Feld von Intervallen zum schnelleren Zugriff
                                  als ueber Listen */

static char * visited;         /**< Traversierungsmerker */

static char * matrix;          /**< Adjazenzmatrix (auf sie darf nur ueber
                                  das folgende Makro zugegriffen werden !*/

/** Eintrag der Adjazenzmatrix \a matrix.
 *  \param a zeile der Matrix
 *  \param b Spalte der Matrix
 *  \retval Eintrag der Matrix
 */

#define adjazent(a,b) matrix [ (a) * anzahl_intervalle * sizeof (char) \
                             + (b) * sizeof (char)]
  

/** Zählt die Einträge eine Liste von Intervallen.
 * \param list Liste der Intervalle
 * \retval Länge der Intervall-Liste
 * \todo Zählen in iterativer Form
 */
int intervall_list_laenge (struct intervall *list)
{ if (list) return 1 + intervall_list_laenge (list -> next);
  return 0;
}



/** Belegt ein Feld von Zeigern auf Intervalle mit den Werten einer Intervallliste.
 * \param intervalle Feld, in das die Intervalle eingetragen werden.
 * \param liste Liste mit den Intervallen, die einsortiert werden sollen.
 * \todo Zählen in iterativer Form
 */
static void belege_intervalle (struct intervall **intervalle, struct intervall * liste)
{
  while (liste) {
      *intervalle = liste;
      intervalle++;
      liste = liste->next;
  }
}

/** Sucht die Nummer eines Intervalles im globalen Intervall-Feld.
 * Wird das Intervall nicht gefunden, wird ein fataler Fehler ausgelöst.
 * \param name Name des zu suchenden Intervalles.
 * \retval Laufende Nummer des Intervalls.
 */
static int intervall_nummer (char *name)
{ 
  int i;
#if (DEBUG)
  if (mutabor_debug_level)
    fprintf(stderr,"Suche Intervall: %s\n",name);
#endif
	 
  for (i=0; i<anzahl_intervalle; i++)
      if ( ! strcmp (name, intervalle[i]->name)) return i;
      
  fatal_error(26,name); /* Intervall nicht deklariert. */

  return 0; /* to prevent warnings */
}
 
/** Testet den Graphen der Intervalle auf Kreise.
 * \param startknoten Knoten, von dem an getestet werden soll.
 * \todo Komplexität n!(?) reduzieren
 */
static void test_zyklen (int startknoten)
{
    int i;
    for (i=0; i<anzahl_intervalle; i++) {
        if (adjazent (startknoten, i)) {
            if (visited [i]) {
                fatal_error(67,intervalle [startknoten]->name,
                               intervalle [i]->name);
            }
            visited [i] = 1;
            test_zyklen (i);
            visited [i] = 0;
        }
    }
}

/** Berechnet für alle Intervalle die endgültigen Werte.  Wird
 * ein nicht korrektes Intervall gefunden, wird ein fataler Fehler
 * ausgelöst.  
 * \param k Nummer des aktuell zu bearbeitenden Intervalles.
 */
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
      fatal_error(0,"schleife"); 
  }
}

/** Berechnet aus einer Intervall-Liste ein Intervall-Feld mit
 * absoluten Werten.  Dabei wird das Intervall-Feld aufgebaut, auf
 * Kreisbezüge getestet und abschließend werden zusammengesetzte
 * Intervalle zu absoluten Intervallen aufgelöst.
 * \param list_of_intervalle Liste der Intervalle, die bearbeitet werden sollen.
 * \return Fertige Intervalle in der Intervall-Liste \a list_of_intervalle.
 */ 

void berechne_intervalle_absolut (struct intervall * list_of_intervalle)
{ 
  int i,j,k;

  anzahl_intervalle = intervall_list_laenge (list_of_intervalle);
  intervalle = (struct intervall* *) xalloca (sizeof(struct intervall *) * anzahl_intervalle);
  visited = (char*) xalloca (sizeof(char) * anzahl_intervalle);
  matrix = (char*) xalloca (sizeof(char) * anzahl_intervalle * anzahl_intervalle);
  

/* Feld mit intervallen initialisieren (zum schnelleren Zugriff) */
#ifdef DEBUG
  if (mutabor_debug_level) 
    fprintf (stderr,"Belege Intervalle\n");
#endif

  belege_intervalle (intervalle, list_of_intervalle);
  
/* Adjazenzmatrix initialisieren (Kein Intervall hängt vom anderen ab) */

#ifdef DEBUG
  if (mutabor_debug_level) 
    fprintf (stderr,"Initialisiere Adjazenzmatrix (Nullen)\n");
#endif

  for (i=0; i<anzahl_intervalle; i++) {
      for (j=0; j<anzahl_intervalle; j++) {
          adjazent (i,j) = 0;
      }
  }
  
/* Adjazenzmatrix initialisieren (Abhängigkeiten eintragen) */

#ifdef DEBUG
  if (mutabor_debug_level) 
    fprintf (stderr,"Initialisiere Adjazenzmatrix (Abhängigkeiten)\n");
#endif

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
          fatal_error(0,"schleife");
      }
  }   

#ifdef DEBUG
  if (mutabor_debug_level) {
    /* Adjazenzmatrix anzeigen */

    fprintf (stderr,"Matrix:\n");
    
    for (i=0; i<anzahl_intervalle; i++) {
      fprintf (stderr,"%s -> ", intervalle[i]->name);
      for (j=0; j<anzahl_intervalle; j++) {
	if (adjazent (i,j))
	  fprintf (stderr,"%s  ", intervalle[j]->name);
      }
      fprintf (stderr,"\n");
    } 
    fprintf (stderr,"\n");
  }
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
      
#ifdef DEBUG
  if (mutabor_debug_level) {
    /* Adjazenzmatrix anzeigen */
    
    fprintf (stderr,"\nMatrix nach dem Zyklentest:\n");
    
    for (i=0; i<anzahl_intervalle; i++) {
      fprintf (stderr,"%s -> ", intervalle[i]->name);
      for (j=0; j<anzahl_intervalle; j++) {
	if (adjazent (i,j))
	  fprintf (stderr,"%s  ", intervalle[j]->name);
      }
      fprintf (stderr,"\n");
    }
    fprintf (stderr,"\n");
  }
#endif

  xde_alloca (intervalle);
  xde_alloca (visited);
  xde_alloca (matrix);

}

/*****************************************/

/** Sucht zusammengesetzte Intervalle in der globalen Intervallliste.
 * Ist ein Intervall nicht in der Intervallliste oder es wurde kein
 * absolutes Intervall zurückgegeben, wird ein fataler Fehler ausgelöst.
 *
 * \param liste Liste der zu suchenden Intervalle.
 * \param konstrukt_name Konstruktionsname für eventuelle Fehlermeldung.
 */
void check_komplex_intervall (struct komplex_intervall * liste,
                              char * konstrukt_name)
{
    for ( ; liste ; liste = liste -> next ) {
        struct intervall * help = get_intervall (liste -> name, list_of_intervalle);
        if (help == NULL) {
            fatal_error (32, liste -> name, konstrukt_name);
            return;
        }
        if (help -> intervall_typ != intervall_absolut) {
            fatal_error (0, __FILE__, __LINE__);
            return;
        }
    }
}

/* Einleseroutinen für komplex_intervalle  ****/

/** Liste komplexer Intervalle */
static struct komplex_intervall * the_komplex_liste; 


/** Setzt Liste komplexer Intervalle auf NULL.
 * \warning Die Liste wird nicht gelöscht. 
 *          Das muss gegebenenfalls vor der Initialiserung manuell erledigt werden.
 */
void init_komplex_ton_list (void)
{
    the_komplex_liste = NULL;
}

/** Fügt ein Intervall ans Ende von \a the_komplex_liste an. 
 * \param f Faktor des Intervalles.
 * \param name Bezeichnung des Intervalles, das angefügt werden soll 
 * \note Es wird immer die gesamte Liste durchsucht. Effektivität?
 */
void get_new_faktor_anteil (double f, char *name)
{
    struct komplex_intervall * * lauf;
#ifdef DEBUG
  if (mutabor_debug_level) 
    fprintf (stderr,"New complex interval factor %s*%f\n",name,f);
#endif

    for (lauf= & the_komplex_liste; * lauf; lauf= & (*lauf)->next) 
      /* nur ende der Liste finden */ ;

    (* lauf) = (struct komplex_intervall*) xmalloc ((size_t) sizeof (struct komplex_intervall));
    (* lauf) -> faktor = f;
    (* lauf) -> name   = name;
    (* lauf) -> next   = NULL;
    
#ifdef DEBUG
  if (mutabor_debug_level) 
    fprintf (stderr,"End complex interval factor %s*%f\n",name,f);
#endif
}

/** Gibt Wurzelelement von \a the_komplex_liste zurück */
struct komplex_intervall * get_last_komplex_intervall (void) 
{
    return the_komplex_liste;
}

#if 0

void get_new_relativ_anteil (double f, char *linke_grenze, char *rechte_grenze)
{
    struct komplex_anteil * * lauf;

    for (lauf= & komplex_liste; * lauf; lauf= & (*lauf)->next) 
      /* nur ende der Liste finden */ ;

    (* lauf) = xmalloc ((size_t) sizeof (struct komplex_anteil));
    (* lauf) -> komplex_typ                     = komplex_anteil_relativ;
    (* lauf) -> u.komplex_anteil_relativ.faktor        = f;
    (* lauf) -> u.komplex_anteil_relativ.linke_grenze  = linke_grenze;
    (* lauf) -> u.komplex_anteil_relativ.rechte_grenze = rechte_grenze;
	 (* lauf) -> next                                   = NULL;
    
}
#endif

/** Einleseroutine fuer die Intervalle 
 *  Es wird einfach eine Liste of Intervallen aufgebaut. Das übergebene 
 *  Intervall wird hinten angehängt. Taucht der Intervallname schon einmal auf, 
 *  wird ein fataler Fehler ausgegeben.
 *  \param name Name des Intervalles
 *  \param wert Wert des Intervalles (\f$\geq\f$ 0,001)
 *  \note Es wird immer die gesamte Liste durchsucht. Effektivität?
 */

void get_new_intervall (char *name, double wert)
{
    struct intervall * * lauf;
    for (lauf= & list_of_intervalle; * lauf; lauf= &(*lauf)->next) {
        if ( ! strcmp (name, (*lauf)->name)) {
            fatal_error(10,name); /* Intervallname doppelt */
        }
    }
    
    if (fabs (wert) < 0.001) 
        fatal_error (46, name);
    
    (* lauf) = (struct intervall*) xmalloc ((size_t) sizeof (struct intervall));
    (* lauf) -> name = name;
    (* lauf) -> intervall_typ = intervall_absolut;
    (* lauf) -> u.intervall_absolut.intervall_wert = wert;
    (* lauf) -> next = NULL;
    
}


/** Fügt ein komplexes Intervall ans Ende von \a #list_of_intervalle an. 
 *  Taucht der Intervallname schon einmal auf, 
 *  wird ein fataler Fehler ausgegeben.
 * \param name Bezeichnung des Intervalles, das angefügt werden soll 
 * \note Es wird immer die gesamte Liste durchsucht. Effektivität?
 */
void get_new_intervall_komplex (char *name)
{
    struct intervall * * lauf;
    for (lauf= & list_of_intervalle; * lauf; lauf= &(*lauf)->next) {
        if ( ! strcmp (name, (*lauf)->name)) {
            fatal_error(10,name); /* Intervallname doppelt */
        }
    }
    
    (* lauf) = (struct intervall*) xmalloc ((size_t) sizeof (struct intervall));
    (* lauf) -> name = name;
    (* lauf) -> intervall_typ = intervall_komplex;
    (* lauf) -> u.intervall_komplex.komplex_liste = 
                       get_last_komplex_intervall ();
    (* lauf) -> next = NULL;
    
}


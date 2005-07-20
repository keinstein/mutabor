/** \file
 ********************************************************************
 * Alles zu Tönen.
 *
 * $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/libmutabor/ton.c,v 1.3 2005/07/20 12:29:50 keinstein Exp $
 * \author Tobias Schlemmer <keinstein_junior@gmx.net>
 * \date $Date: 2005/07/20 12:29:50 $
 * \version $Revision: 1.3 $
 *  
 * $Log: ton.c,v $
 * Revision 1.3  2005/07/20 12:29:50  keinstein
 * Kopf korrigiert
 * config.h
 * Rudimentäre Debug-Ausgaben
 *
 * Revision 1.2  2005/07/19 15:15:27  keinstein
 * Using own Templates
 *
 * Revision 1.1  2005/07/08 14:44:20  keinstein
 * Neue Datei.
 * Aus parser.c herausgelöst.
 *
 ********************************************************************/
#ifdef HAVE_CONFIG_H
#  include "config.h"
/* für HAVE_STDDEF_H, size_t */
#endif
#ifdef HAVE_STDDEF_H
#  include <stddef.h>
#endif
#include <string.h>
#include <stdio.h>
#include "mutabor/ton.h"
#include "mutabor/heap.h"
#include "mutabor/interval.h"
#include "mutabor/errors.h"

/** Wurzel der Tonliste */
struct ton            *  list_of_toene;
struct ton            *  ton_ohne_namen; /**< Frequenz=0 */

void init_nullton( void ) {
   ton_ohne_namen=(struct ton*) xmalloc((size_t) sizeof(struct ton));
   ton_ohne_namen->name=NULL;
   ton_ohne_namen->ton_typ=ton_absolut;
   ton_ohne_namen->u.ton_absolut.ton_wert=0.0;
   ton_ohne_namen->next=NULL;
}

/** Zählen der Elemente einer einfach verketteten Tonliste.
 * \param list Liste der Töne
 * \return Anzahl der Elemente von \a list
 */
int ton_list_laenge (struct ton *list)
{ if (list) return 1 + ton_list_laenge (list -> next);
  return 0;
}

/** Sucht einen ton aus einer Tonliste.
 * \param name Name des gesuchten Tones
 * \param liste Liste der Töne, in der der Ton gesucht wird
 * \retval ton_ohne_namen, falls \a name == \a NULL
 * \retval NULL, falls Ton nicht in \a liste
 * \retval Ton, sonst.
 */
struct ton * get_ton (char * name, struct ton * liste)
{
    if (name==NULL) return(ton_ohne_namen);
    if (liste == NULL) return NULL;
    if ( ! strcmp (name, liste->name)) return liste;
    return get_ton (name, liste->next);
}


/** Gibt einen Ton auf der Standardausgabe aus.
 * \param lauf Ton
 */
void drucke_ton (struct ton * lauf)
{
          printf ("Name: %s, Typ: %s:\n",
                   lauf->name ? lauf->name : "(NULL)",
                   lauf->ton_typ == ton_absolut ? "absolut" :
                   lauf->ton_typ == ton_komplex ? "komplex" :
                                              "undefined" );

      if (lauf->name == NULL) return;

          switch (lauf->ton_typ) {
            case ton_absolut : 
                printf ("%lf\n", lauf->u.ton_absolut.ton_wert);
                break;
            case ton_komplex : {
                 struct komplex_intervall * help = lauf->u.ton_komplex.komplex_liste;
                 printf ("%s ", lauf->u.ton_komplex.bezugston);
                 while (help) {
                     printf ("Faktor: %lf %s ", 
                             help->faktor, 
                             help->name);
                     help = help->next;
                 }
                }
                break;
          }
          printf ("\n");
}

/********* Einleseroutinen fuer die Toene           *********/
/*         Es wird einfach eine Liste of Toenen aufgebaut  **/
/*         Je nach erkanntem Ton_Typ                       **/


/** Fügt einen absoluten Ton ans Ende von \a list_of_toene an. 
 *  Taucht der Tonname schon einmal auf, 
 *  wird ein fataler Fehler ausgegeben.
 * \param name Bezeichnung des Tones, das angefügt werden soll 
 * \param wert Wert des Tones, der angfügt werden soll
 * \note Es wird immer die gesamte Liste durchsucht. Effektivität?
 */
void get_new_ton_absolut (char *name, double wert)
{
    struct ton * * lauf;
    for (lauf= & list_of_toene; * lauf; lauf= & (*lauf)->next) {
        if ( ! strcmp (name, (* lauf)->name)) {
            fatal_error(11,name); /* Tonname doppelt */
        }
    }
    
    (* lauf) = (struct ton*) xmalloc ((size_t) sizeof (struct ton));
    (* lauf) -> name                   = name;
    (* lauf) -> ton_typ                = ton_absolut;
    (* lauf) -> u.ton_absolut.ton_wert = wert;
    (* lauf) -> next                   = NULL;
    
}


/** Fügt einen komplexen Ton ans Ende von \a list_of_toene an. Dabei
 *  wird mittels \c get_last_komplex_intervall() die letzte eingelesene
 *  Intevallliste verwendet. Taucht der Tonname schon einmal auf, 
 *  wird ein fataler Fehler ausgegeben.
 * \param name Bezeichnung des Tones, das angefügt werden soll 
 * \param bezugston Basiston, auf den sich die Intervallliste bezieht.
 * \note Es wird immer die gesamte Liste durchsucht. Effektivität?
 */
void get_new_ton_komplex_positive (char *name, char *bezugston)
{
    struct ton * * lauf;
    for (lauf= & list_of_toene; * lauf; lauf= & (*lauf)->next) {
        if ( ! strcmp (name, (*lauf)->name)) {
            fatal_error(11,name); /* Tonname doppelt */
        }
    }
    
    (* lauf) = (struct ton*) xmalloc ((size_t) sizeof (struct ton));
    (* lauf) -> name                        = name;
    (* lauf) -> ton_typ                     = ton_komplex;
    (* lauf) -> u.ton_komplex.bezugston     = bezugston;
    (* lauf) -> u.ton_komplex.komplex_liste = get_last_komplex_intervall ();
    (* lauf) -> next                        = NULL;
    
}

/** Fügt einen komplexen Ton ans Ende von \a list_of_toene an. Dabei
 *  wird mittels \c get_last_komplex_intervall() die letzte eingelesene
 *  Intevallliste verwendet. Diese wird jedoch zunächst einmal invertiert.
 *  Taucht der Tonname schon einmal auf, 
 *  wird ein fataler Fehler ausgegeben.
 * \param name Bezeichnung des Tones, das angefügt werden soll 
 * \param bezugston Basiston, auf den sich die Intervallliste bezieht.
 * \note Es wird immer die gesamte Liste durchsucht. Effektivität?
 */
void get_new_ton_komplex_negative (char *name, char *bezugston)
{
    struct ton * * lauf;
    for (lauf= & list_of_toene; * lauf; lauf= & (*lauf)->next) {
        if ( ! strcmp (name, (*lauf)->name)) {
            fatal_error(11,name); /* Tonname doppelt */
        }
    }
    
    (* lauf) = (struct ton*) xmalloc ((size_t) sizeof (struct ton));
    (* lauf) -> name                        = name;
    (* lauf) -> ton_typ                     = ton_komplex;
    (* lauf) -> u.ton_komplex.bezugston     = bezugston;

    {
        struct komplex_intervall * help = get_last_komplex_intervall ();
        if (help == NULL) {
            fatal_error (0, __FILE__, __LINE__);
        }
        help -> faktor *= -1.0 ;
        (* lauf) -> u.ton_komplex.komplex_liste = help;
    }

    (* lauf) -> next                        = NULL;
    
}

/**************************************************************

            Hier werden die Toene aufgel�st.
            Nach dem Parsing ist nur die Syntax-Struktur
            vorhanden, aber keine fertig ausgerechneten Toene.
            
            Es wird ein azyklischer Graph der Toene und ihrer
            Untertoene gebildet, der dann nach den
            depth-first-search traversiert wird.
            Dabei bekommt jeder Ton seine Absolutfrequenz berechnet.
            
****************************************************************/

static int anzahl_toene;       /**< So viele Toene wurden gelesen. */

static struct ton ** toene;    /**< Feld von Toenen zum schnelleren Zugriff
                                  als ueber Listen */

static char * visited;         /**< Traversierungsmerker */

static char * matrix;          /**< Adjazenzmatrix (auf sie darf nur ueber
                                  das folgende Makro zugegriffen werden !*/

/** Zugriff auf Adjazenzmatrix 
 * \param a Zeile der Matrix 
 * \param b Spalte der Matrix 
 */
#define adjazent(a,b) matrix [ (a) * anzahl_toene * sizeof (char) \
                             + (b) * sizeof (char)]
  

/** Erzeugt zu einer einfach verketteten Liste von Tönen ein Array mit Verweisen
 * auf die Einträge.
 * \param[in,out]  toene  Array für Töne
 * \param[in]      liste  Liste der Töne
 * \warning Das Array muss vor dem Funktionsaufruf genügend Platz für alle Töne der
 *          Liste bieten. In der Funktion selbst findet keinerlei Längenprüfung statt.
 */
static void belege_toene (struct ton **toene, struct ton * liste)
{
#ifdef DEBUG
  if (mutabor_debug_level) 
    fprintf (stderr,"Initializing tone array\n");
#endif
  while (liste) {
      *toene = liste;
      toene++;
      liste = liste->next;
  }
}

/** Sucht einen Ton in der globalen Tonliste.
 * \param name Name des zu suchenden Tones
 * Wird der Ton nicht gefunden, wird ein fataler Fehler ausgelöst.
 */
static int ton_nummer (char *name)
{ int i;

  for (i=0; i<anzahl_toene; i++)
      if ( ! strcmp (name, toene[i]->name)) return i;
      
  fatal_error(27,name); /* Ton n.dekl. */

  return 0; /* to prevent warnings */
}
  
/** Durchsucht die Adjazenzmatrix nach Kreisen. Wird ein Kreis gefunden, wird
 *  ein fataler Fehler ausgelöst
 * \param[in] startknoten Nummer des ersten Knoten, der getestet werden soll. 
 */
static void test_zyklen (int startknoten)
{
    int i;
    for (i=0; i<anzahl_toene; i++) {
        if (adjazent (startknoten, i)) {
            if (visited [i]) {
                fatal_error(65,toene [startknoten]->name,toene [i]->name);
            }
            visited [i] = 1;
            test_zyklen (i);
            visited [i] = 0;
        }
    }
}

/** Rechnet komplexe Töne in absolute um. Wird ein ungültiger Tontyp
 * gefunden, wird ein fataler Fehler ausgelöst.
 * \param[in] k Nummer des zu bearbeitenden Tones
 */
static void berechne_ton_endgueltig (int k)
{ int b;
  double help, help2;
  
#ifdef DEBUG
  if (mutabor_debug_level) 
    fprintf (stderr,"Calculate final tone values %d ",k);
#endif
  switch (toene[k]->ton_typ) {

    case ton_absolut:         /* hier nichts zu tun */
#ifdef DEBUG
  if (mutabor_debug_level) 
    fprintf (stderr,"Absolute tone %s: %f\n",toene[k]->name,toene[k]->u.ton_absolut.ton_wert);
#endif
      break;
      
    case ton_komplex:
#ifdef DEBUG
  if (mutabor_debug_level) 
    fprintf (stderr,"Complex tone %s:\n",toene[k]->name);
#endif
      b = ton_nummer (toene[k]->u.ton_komplex.bezugston);
      berechne_ton_endgueltig (b);
      
      help2 = get_wert_komplex_intervall (toene[k]->u.ton_komplex.komplex_liste);
      help = toene[b]->u.ton_absolut.ton_wert;
      
      toene[k]->ton_typ = ton_absolut;
      toene[k]->u.ton_absolut.ton_wert = help * help2;
#ifdef DEBUG
  if (mutabor_debug_level) 
    fprintf (stderr,"Complex tone %s: %f\n",toene[k]->name, toene[k]->u.ton_absolut.ton_wert);
#endif
      break;
      
    default:
      fatal_error(0,"schleife"); 
  }
}

/** Berechnet die absoluten Tonwerte für eine einfach verkettete Tonliste.
 * Dabei werden die globalen Variablen \c anzahl_toene, \c toene, \c visited
 * und die Adjazenzmatrix benutzt. Falls mit \c DEBUG_ANZEIGE 
 * compiliert, wird die Matrix nach der Aufstellung auf der Standardausgabe ausgegeben.
 * \param[in,out] list_of_toene
 */
void berechne_toene_absolut (struct ton *list_of_toene)
{ 
#ifdef DEBUG
  if (mutabor_debug_level) 
    fprintf (stderr,"Calculate abolute tone values\n");
#endif
  int i,j,k;

  anzahl_toene = ton_list_laenge (list_of_toene);
  toene = (struct ton* *) xalloca (sizeof(struct ton *) * anzahl_toene);
  visited = (char*) xalloca (sizeof(char) * anzahl_toene);
  matrix = (char*) xalloca (sizeof(char) * anzahl_toene * anzahl_toene);
  

/* Feld mit toenen initialisieren (zum schnelleren Zugriff) */

  belege_toene (toene, list_of_toene);
  
/* Adjazenzmatrix initialisieren (Kein Ton h�ngt vom anderen ab) */

#ifdef DEBUG
  if (mutabor_debug_level) 
    fprintf (stderr,"Initializing adjacency matrix\n");
#endif
  for (i=0; i<anzahl_toene; i++) {
      for (j=0; j<anzahl_toene; j++) {
          adjazent (i,j) = 0;
      }
  }
  
/* Adjazenzmatrix initialisieren (Abhängigkeiten eintragen) */

#ifdef DEBUG
  if (mutabor_debug_level) 
    fprintf (stderr,"Initializing tone entries\n");
#endif
  for (i=0; i<anzahl_toene; i++) {
      if (toene[i]->ton_typ == ton_absolut)  /* alles ok */ ;
      else if (toene[i]->ton_typ == ton_komplex) {
          adjazent (i, ton_nummer (toene[i]->u.ton_komplex.bezugston)) = 1;
      }
      else { 
          fatal_error(0,"schleife");
      }
  }

#ifdef DEBUG
  if (mutabor_debug_level) {
    /* Adjazenzmatrix anzeigen */
    
    fprintf (stderr,"Tone Matrix:\n");
  
    for (i=0; i<anzahl_toene; i++) {
      fprintf (stderr,"%s -> ", toene[i]->name);
      for (j=0; j<anzahl_toene; j++) {
	if (adjazent (i,j))
	  fprintf (stderr,"%s  ", toene[j]->name);
      }
      fprintf (stderr,"\n");
    } 
    fprintf (stderr,"\n");
  }
#endif
  
/* auf Zyklenfreiheit Pruefen */

  for (k=0; k<anzahl_toene; k++)
      visited [k] = 0;
      
  for (k=0; k<anzahl_toene; k++) {
      visited [k] = 1;
      test_zyklen (k);
      visited [k] = 0;
  }
  
/* Toene endgueltig berechnen */

  for (k=0; k<anzahl_toene; k++)
      berechne_ton_endgueltig (k);
      
#ifdef DEBUG_ANZEIGE
                        /* Adjazenzmatrix anzeigen */

  printf ("Matrix:\n");
  
  for (i=0; i<anzahl_toene; i++) {
      printf ("%s -> ", toene[i]->name);
      for (j=0; j<anzahl_toene; j++) {
          if (adjazent (i,j))
              printf ("%s  ", toene[j]->name);
      }
      printf ("\n");
  }
  printf ("\n");
#endif

  xde_alloca (toene);
  xde_alloca (visited);
  xde_alloca (matrix);

}


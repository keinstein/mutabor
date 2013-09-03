/** \file 
 ********************************************************************
 * Interval calculations
 *
 * Copyright:   (c) 2008 TU Dresden
 *              changes after 2011 (c) Tobias Schlemmer
 * \author  Tobias Schlemmer <keinstein@users.berlios.de>
 * \license GPL
 *
 *    This program is free software; you can redistribute it and/or modify
 *    it under the terms of the GNU General Public License as published by
 *    the Free Software Foundation; either version 2 of the License, or
 *    (at your option) any later version.
 *
 *    This program is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License for more details.
 *
 *    You should have received a copy of the GNU General Public License
 *    along with this program; if not, write to the Free Software
 *    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 *
 ********************************************************************
 * \addtogroup templates
 * \{
 ********************************************************************/

#include "box.h"
#include "Global.h"
#include "Runtime.h"
#include "Execute.h"
#include "Interval.h"
#include "Parser.h"
#include "Hilfs.h"

#ifdef _
#undef _
#endif
#define _ _mut


#ifdef __cplusplus
using namespace mutabor;
using namespace mutabor::hidden;
extern "C" {
#endif

static double get_intervall_wert (mutabor_box_type * box,
				  const char * name)
{

	struct intervall *lauf;

	for (lauf = box->file->list_of_intervalle; lauf; lauf = lauf -> next) {
		if ( ! strcasecmp (name, lauf->name)) {
			switch (lauf -> intervall_typ) {

			case intervall_komplex:
				return get_wert_komplex_intervall(box,
								  lauf->u.intervall_komplex.komplex_liste);
				break;

			case intervall_absolut:
				return lauf->u.intervall_absolut.intervall_wert ;
				break;
				
			default:
				mutabor_error_message(box,
						      true,
						      _("Undefined interval type %d for interval %s."),
						      lauf->intervall_typ,
						      (name));
				
				return 0.0;
			}
		}
	}

	mutabor_error_message(box,
			      true,
			      _("Undefined interval: %s"),
			      (name));

	return 0.0; /* to prevent warnings */
}


double get_wert_komplex_intervall (mutabor_box_type * box, struct komplex_intervall * intervall)

{
	double ret = 1.0;

	for ( ; intervall ; intervall = intervall -> next )
	{
		double help = get_intervall_wert (box, intervall -> name);

		if (help > 0)
			ret *= pow (help, intervall -> faktor);
		else {
			mutabor_error_message(box,
					      false,
					      _("Bad interval value in %s"),	    
					      (intervall -> name));
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

static int anzahl_intervalle;       /* so viele Intervalle wurden gelesen */

static struct intervall ** intervalle;    /* Feld von Intervallen zum schnelleren Zugriff

                                  als ueber Listen */

static char * visited;         /* Traversierungsmerker */

static char * matrix;          /* Adjazenzmatrix (auf sie darf nur ueber

                                  das folgende Makro zugegriffen werden !*/

#define adjazent(a,b) matrix [ (a) * anzahl_intervalle * sizeof (char) \
                             + (b) * sizeof (char)]

int intervall_list_laenge (struct intervall *list)
{
	if (list) return 1 + intervall_list_laenge (list -> next);

	return 0;
}



static void belege_intervalle (struct intervall **intervalle, struct intervall * liste)
{
	while (liste)
	{
		*intervalle = liste;
		intervalle++;
		liste = liste->next;
	}
}

static int intervall_nummer (mutabor_box_type * box, const char *name)
{
	int i;

	for (i=0; i<anzahl_intervalle; i++)
		if ( ! strcasecmp (name, intervalle[i]->name)) return i;

	mutabor_error_message(box,
			      false,
			      _("Undefined interval: %s"),
			      (name)); 

	return 0; /* to prevent warnings */
}

static void test_zyklen (mutabor_box_type * box, int startknoten)
{
	int i;

	for (i=0; i<anzahl_intervalle; i++) {
		if (adjazent (startknoten, i)) {
			if (visited [i]) {
				mutabor_error_message(box,
						      false,
				              _("Intervals %s and %s depend on each other"),
					      (intervalle [startknoten]->name),
					      intervalle [i]->name);
			}

			visited [i] = 1;

			test_zyklen (box, i);
			visited [i] = 0;
		}
	}
}

static void berechne_intervall_endgueltig (mutabor_box_type * box, int k)
{
	int b;
	double help;

	switch (intervalle[k]->intervall_typ) {

	case intervall_absolut:         /* hier nichts zu tun */
		break;

	case intervall_komplex: {

		struct komplex_intervall * lauf;

		for (lauf = intervalle[k]->u.intervall_komplex.komplex_liste;
		                lauf;
		                lauf = lauf -> next) {
			b = intervall_nummer (box, lauf -> name);
			berechne_intervall_endgueltig (box, b);
		}

		help = get_wert_komplex_intervall (box,
						   intervalle[k]->u.intervall_komplex.komplex_liste);

		intervalle[k]->intervall_typ = intervall_absolut;
		intervalle[k]->u.intervall_absolut.intervall_wert = help;
	}
		break;
		
	default:
		mutabor_error_message(box, 
				      false,
				      _("Unknown error in %s , line %d."),	     
				      _("loop"),
				      -1);
	}
}

void berechne_intervalle_absolut (mutabor_box_type * box, struct intervall * list_of_intervalle)

{
	int i,j,k;

	anzahl_intervalle = intervall_list_laenge (list_of_intervalle);

	intervalle = (intervall* *) xalloca (box, sizeof(struct intervall *) * anzahl_intervalle);
	visited = (char*) xalloca (box, sizeof(char) * anzahl_intervalle);
	matrix = (char*) xalloca (box, sizeof(char) * anzahl_intervalle * anzahl_intervalle);


	/* Feld mit intervallen initialisieren (zum schnelleren Zugriff) */

	belege_intervalle (intervalle, list_of_intervalle);

	/* Adjazenzmatrix initialisieren (Kein Intervall hängt vom anderen ab) */

	for (i=0; i<anzahl_intervalle; i++)
	{
		for (j=0; j<anzahl_intervalle; j++) {
			adjazent (i,j) = 0;
		}
	}

	/* Adjazenzmatrix initialisieren (Abhängigkeiten eintragen) */

	for (i=0; i<anzahl_intervalle; i++)
	{
		if (intervalle[i]->intervall_typ == intervall_absolut)  /* alles ok */ ;
		else if (intervalle[i]->intervall_typ == intervall_komplex) {

			struct komplex_intervall * lauf;

			for (lauf = intervalle[i]->u.intervall_komplex.komplex_liste;
			                lauf;
			                lauf = lauf -> next) {
				adjazent (i, intervall_nummer (box, lauf -> name)) = 1;
			}
		} else {
			mutabor_error_message(box,
					      false,
					      _("Undefined interval type %d for interval %s."),
					      intervalle[i]->intervall_typ,
					      (intervalle[i]->name));
		}
	}

#ifdef DEBUG_ANZEIGE_3
	/* Adjazenzmatrix anzeigen */

	printf ("Matrix:\n");

	for (i=0; i<anzahl_intervalle; i++)
	{
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

	for (k=0; k<anzahl_intervalle; k++)
	{
		visited [k] = 1;
		test_zyklen (box, k);
		visited [k] = 0;
	}

	/* Toene endgueltig berechnen */

	for (k=0; k<anzahl_intervalle; k++)
		berechne_intervall_endgueltig (box, k);

#ifdef DEBUG_ANZEIGE_3
	/* Adjazenzmatrix anzeigen */

	printf ("Matrix:\n");

	for (i=0; i<anzahl_intervalle; i++)
	{
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

void check_komplex_intervall (mutabor_box_type * box, 
			      struct komplex_intervall * liste,
                              const char * konstrukt_name)
{
	for ( ; liste ; liste = liste -> next )
	{

		struct intervall * help = get_intervall (liste -> name, box->file->list_of_intervalle);

		if (help == NULL) {
			mutabor_error_message(box,
					      false,
					      _("Undefined interval: %s (in %s)"),
					      (liste -> name), 
					      (konstrukt_name));
			return;
		}

		if (help -> intervall_typ != intervall_absolut) {
			mutabor_error_message(box,
					      false,
					      _("Undefined interval type %d for interval %s (%s:%d)."),
					      help->intervall_typ,
					      _T(__FILE__), 
					      __LINE__);
			return;
		}
	}
}


#ifdef __cplusplus
}
#endif
///\}

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
 * \addtogroup kernel
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

	mutASSERT(box);
	DEBUGLOG2(kernel_tabgen,"name = %s", name);

	for (lauf = box->file->list_of_intervalle; lauf; lauf = lauf -> next) {
		if ( ! strcasecmp (name, lauf->name)) {
			switch (lauf -> intervall_typ) {

			case intervall_komplex:
				return get_wert_komplex_intervall(box,
								  lauf->u.intervall_komplex.komplex_liste);

			case intervall_absolut:
				return lauf->u.intervall_absolut.intervall_wert ;

			default:
				mutabor_error_message(box,
						      compiler_error,
						      _("Undefined interval type %d for interval %s."),
						      lauf->intervall_typ,
						      (name));

				return 0.0;
			}
		}
	}

	mutabor_error_message(box,
			      compiler_error,
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
					      compiler_error,
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


#define adjacent(file,a,b) file->interval_matrix [ (a) * file->interval_count * sizeof (char) \
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
	size_t i;
	for (i=0; i<box->file->interval_count; i++)
		if ( ! strcasecmp (name, box->file->check_intervals[i]->name)) return i;

	mutabor_error_message(box,
			      compiler_error,
			      _("Undefined interval: %s"),
			      (name));

	return 0; /* to prevent warnings */
}

static void test_zyklen (mutabor_box_type * box, int startknoten)
{
	size_t i;
	for (i=0; i<box->file->interval_count; i++) {
		if (adjacent (box->file, startknoten, i)) {
			if (box->file->visited_intervals [i]) {
				mutabor_error_message(box,
						      compiler_error,
				              _("Intervals %s and %s depend on each other"),
					      (box->file->check_intervals [startknoten]->name),
					      box->file->check_intervals [i]->name);
				box->file->check_intervals [startknoten] -> intervall_typ = intervall_absolut;
				box->file->check_intervals [startknoten] -> u.intervall_absolut.intervall_wert = 1;
				return;
			}

			box->file->visited_intervals [i] = 1;

			test_zyklen (box, i);
			box->file->visited_intervals [i] = 0;
		}
	}
}

static void berechne_intervall_endgueltig (mutabor_box_type * box, int k)
{
	int b;
	double help;

	switch (box->file->check_intervals[k]->intervall_typ) {

	case intervall_absolut:         /* hier nichts zu tun */
		break;

	case intervall_komplex: {

		struct komplex_intervall * lauf;

		for (lauf = box->file->check_intervals[k]->u.intervall_komplex.komplex_liste;
		                lauf;
		                lauf = lauf -> next) {
			b = intervall_nummer (box, lauf -> name);
			berechne_intervall_endgueltig (box, b);
		}

		help = get_wert_komplex_intervall (box,
						   box->file->check_intervals[k]->u.intervall_komplex.komplex_liste);

		box->file->check_intervals[k]->intervall_typ = intervall_absolut;
		box->file->check_intervals[k]->u.intervall_absolut.intervall_wert = help;
	}
		break;

	default:
		mutabor_error_message(box,
				      internal_error,
				      _("Unknown error in %s, line %d."),
				      _("loop"),
				      -1);
	}
}

void berechne_intervalle_absolut (mutabor_box_type * box, struct intervall * list_of_intervalle)

{
	size_t i,j;

	box->file->interval_count = intervall_list_laenge (list_of_intervalle);

	box->file->check_intervals = (struct intervall* *) xalloca (box, sizeof(struct intervall *) * box->file->interval_count);
	box->file->visited_intervals = (char*) xalloca (box, sizeof(char) * box->file->interval_count);
	box->file->interval_matrix = (char*) xalloca (box, sizeof(char) * box->file->interval_count * box->file->interval_count);


	/* Feld mit intervallen initialisieren (zum schnelleren Zugriff) */

	belege_intervalle (box->file->check_intervals, list_of_intervalle);

	/* Adjazenzmatrix initialisieren (Kein Intervall hängt vom anderen ab) */

	for (i=0; i<box->file->interval_count; i++)
	{
		for (j=0; j<box->file->interval_count; j++) {
			adjacent (box->file, i,j) = 0;
		}
	}

	/* Adjazenzmatrix initialisieren (Abhängigkeiten eintragen) */

	for (i=0; i<box->file->interval_count; i++)
	{
		if (box->file->check_intervals[i]->intervall_typ == intervall_absolut)  /* alles ok */ ;
		else if (box->file->check_intervals[i]->intervall_typ == intervall_komplex) {

			struct komplex_intervall * lauf;

			for (lauf = box->file->check_intervals[i]->u.intervall_komplex.komplex_liste;
			                lauf;
			                lauf = lauf -> next) {
				adjacent (box->file, i, intervall_nummer (box, lauf -> name)) = 1;
			}
		} else {
			mutabor_error_message(box,
					      internal_error,
					      _("Undefined interval type %d for interval %s."),
					      box->file->check_intervals[i]->intervall_typ,
					      (box->file->check_intervals[i]->name));
		}
	}

#ifdef DEBUG_ANZEIGE_3
	/* Adjazenzmatrix anzeigen */

	printf ("Matrix:\n");

	for (i=0; i<box->file->interval_count; i++)
	{
		printf ("%s -> ", box->file->check_intervals[i]->name);

		for (j=0; j<box->file->interval_count; j++) {
			if (adjacent (box->file, i,j))
				printf ("%s  ", box->file->check_intervals[j]->name);
		}

		printf ("\n");
	}

	printf ("\n");

#endif
	/** \todo we should use Dykstra to reduce complexity */
	/* Test for cycles  */

	for (i=0; i<box->file->interval_count; i++)
		box->file->visited_intervals [i] = 0;

	for (i=0; i<box->file->interval_count; i++)
	{
		box->file->visited_intervals [i] = 1;
		test_zyklen (box, i);
		box->file->visited_intervals [i] = 0;
	}

	/* Toene endgueltig berechnen */

	for (i=0; i<box->file->interval_count; i++)
		berechne_intervall_endgueltig (box, i);

#ifdef DEBUG_ANZEIGE_3
	/* Adjazenzmatrix anzeigen */

	printf ("Matrix:\n");

	for (i=0; i<box->file->interval_count; i++)
	{
		printf ("%s -> ", box->file->check_intervals[i]->name);

		for (j=0; j<box->file->interval_count; j++) {
			if (adjacent (box->file, i,j))
				printf ("%s  ", box->file->check_intervals[j]->name);
		}

		printf ("\n");
	}

	printf ("\n");

#endif

	xde_alloca (box->file->check_intervals);
	xde_alloca (box->file->visited_intervals);
	xde_alloca (box->file->interval_matrix);

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
					      compiler_error,
					      _("Undefined interval: %s (in %s)"),
					      (liste -> name),
					      (konstrukt_name));
			return;
		}

		if (help -> intervall_typ != intervall_absolut) {
			mutabor_error_message(box,
					      internal_error,
					      _("Undefined interval type %d for interval %s (%s:%d)."),
					      help->intervall_typ,
					      (__FILE__),
					      __LINE__);
			return;
		}
	}
}


#ifdef __cplusplus
}
#endif
/** \} */

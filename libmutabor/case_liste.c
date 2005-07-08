/** \file
 ********************************************************************
 * Verzweigungsliste für Umstimmungen und ähnliches.
 *
 * $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/libmutabor/case_liste.c,v 1.1 2005/07/08 14:44:20 keinstein Exp $
 * \author Tobias Schlemmer <keinstein_junior@gmx.net>
 * \date $Date: 2005/07/08 14:44:20 $
 * \version $Revision: 1.1 $
 * $Log: case_liste.c,v $
 * Revision 1.1  2005/07/08 14:44:20  keinstein
 * Neue Datei.
 * Aus parser.c herausgelöst.
 *
 ********************************************************************/
/** \defgroup parser
 * Einleseroutine.
 * \{
 */


#include "mutabor/case_liste.h"
#include "mutabor/heap.h"
#include "mutabor/umstimmung.h"
#include "mutabor/parameter.h"

/***********************************
      case Umstimmungen:
***********************************/


static struct case_liste * tmp_umstimmungs_case_liste;


/** Fügt einen Fall ans Ende von \a tmp_umstimmungs_case_liste an. 
 * Der Aufruf erhält die letzte eingelesene Argumentliste.
 * \param konstante Bezeichnung der Konstante für Fall, der angefügt werden soll 
 * \note Es wird immer die gesamte Liste durchsucht. Effektivität?
 */
void get_umstimmungs_case_zahl_element (int konstante)
{
    struct case_liste * * lauf;
    for (lauf= & tmp_umstimmungs_case_liste; 
         * lauf; 
         lauf= (struct case_liste * *) &(*lauf)->next)
        /* Nur Ende der Liste finden */ ;
    
    (* lauf) = (struct case_liste*) xmalloc (sizeof (struct case_liste));
    (* lauf) -> case_label          = konstante;
    (* lauf) -> is_default          = 0;
    (* lauf) -> case_aktion         = get_last_aktions_liste (); 
    (* lauf) -> next                = NULL;
}

/** Fügt einen Standardfall ans Ende von \a tmp_umstimmungs_case_liste an. 
 * Der Aufruf erhält die letzte eingelesene Argumentliste.
 * \note Es wird immer die gesamte Liste durchsucht. Effektivität?
 * \todo Typkonvertierung von \c doube nach \c int prüfen.
 */
void get_umstimmungs_case_default_element (void)
{
    struct case_liste * * lauf;
    for (lauf= & tmp_umstimmungs_case_liste; 
         * lauf; 
         lauf= & (*lauf)->next)
        /* Nur Ende der Liste finden */ ;
    
    (* lauf) = (struct case_liste*) xmalloc (sizeof (struct case_liste));
    (* lauf) -> case_label          = (int)  -1000000.0; /* als dummy-wert */
    (* lauf) -> is_default          = 1;
    (* lauf) -> case_aktion         = get_last_aktions_liste (); 
    (* lauf) -> next                = NULL;
}


/** Setzt \c tmp_umstimmungs_case_liste auf \c NULL. 
 * \warning Die Liste wird nicht gelöscht. 
 *          Das muss gegebenenfalls vor der Initialiserung manuell erledigt werden.
 */
void init_umstimmungs_case_liste (void)
{
    tmp_umstimmungs_case_liste = NULL;
}

/** Baut \c tmp_umstimmung zu einer Zahlgesteuerten Case-Umstimmung aus.
 * Dabei wird die letzte eingelesene Umstimmungs-Case-Liste verwendet.
 * Falls darin ein unbekannter Parameter gefunden wird, wird ein fataler Fehler 
 * ausgelöst.
 * \param selector Wert für die Case-Anweisung
 */
void get_umstimmung_umstimm_case_zahl (int selector)
{
    tmp_umstimmung -> umstimmung_typ = umstimmung_umstimmungs_case;
    tmp_umstimmung -> u.umstimmung_umstimmungs_case
                       .argument
                       .argument_typ = zahl;
    tmp_umstimmung -> u.umstimmung_umstimmungs_case
                       .argument
                       .u.zahl.zahl = selector;
    tmp_umstimmung -> u.umstimmung_umstimmungs_case
                       .umstimmungs_case_liste = tmp_umstimmungs_case_liste;


/* check, ob die Parameter zulässig sind */

    {
      struct case_liste * case_lauf;
      for (case_lauf = tmp_umstimmung -> u.umstimmung_umstimmungs_case
                       .umstimmungs_case_liste ;
           case_lauf;
           case_lauf = case_lauf -> next) {
       
       struct aktions_liste * aktions_lauf;
       for (aktions_lauf = case_lauf -> case_aktion;
            aktions_lauf;
            aktions_lauf = aktions_lauf -> next) {
         
         if (aktions_lauf -> aktions_typ == aktion_aufruf) {   
	        struct argument_liste * argument_lauf;
	        for (argument_lauf = aktions_lauf -> u.aktion_aufruf.argument_liste;
	             argument_lauf;
	             argument_lauf = argument_lauf -> next ) {
	          if (argument_lauf -> argument.argument_typ == parameter) {
	            int i = parameter_nummer (0,
	                      argument_lauf->argument.u.parameter.parameter_name, 
            	                 tmp_umstimmung -> parameter_liste);
            	if (i == EOF ) {
	              fatal_error(31,argument_lauf->argument.u.parameter.parameter_name,
	                             tmp_umstimmung -> name); /* Parameter n.dekl. */
	            }
	            else {
	              argument_lauf->argument.u.parameter.parameter_nummer = i;
	            } /* if */
	          } /* if */
	        }  /* for argument_lauf */
	     } /* if (aktions_lauf ... */
       }  /* for aktions_lauf */
      }  /* for case_lauf */
    }


}


/** Baut \c tmp_umstimmung zu einer Parametergesteuerten Case-Umstimmung aus.
 * Dabei wird die letzte eingelesene Umstimmungs-Case-Liste verwendet.
 * Falls darin ein unbekannter Parameter gefunden wird, wird ein fataler Fehler 
 * ausgelöst. Dies geschieht auch, falls \a selector nicht definiert ist.
 * \param selector Parameter für die Case-Anweisung
 */
void get_umstimmung_umstimm_case_parameter (char * selector)
{
    tmp_umstimmung -> umstimmung_typ = umstimmung_umstimmungs_case;
    tmp_umstimmung -> u.umstimmung_umstimmungs_case
                       .argument
                       .argument_typ = parameter;
    tmp_umstimmung -> u.umstimmung_umstimmungs_case
                       .argument
                       .u.parameter.parameter_name = selector;
                       
/* und test, ob selector als Parameter deklariert ist. */

    {
       int i = parameter_nummer (0,selector, tmp_umstimmung -> parameter_liste);
       if (i == EOF ) {
          fatal_error(31,selector,tmp_umstimmung->name); /* Parameter n.dekl. */
       }
       else {
           tmp_umstimmung -> u.umstimmung_umstimmungs_case
                       .argument
                       .u.parameter.parameter_nummer = i;
       
       }
    }
                       
    tmp_umstimmung -> u.umstimmung_umstimmungs_case
                       .umstimmungs_case_liste = tmp_umstimmungs_case_liste;



/* check, ob die Parameter zulässig sind */

    {
      struct case_liste * case_lauf;
      for (case_lauf = tmp_umstimmung -> u.umstimmung_umstimmungs_case
                       .umstimmungs_case_liste ;
           case_lauf;
           case_lauf = case_lauf -> next) {
       
       struct aktions_liste * aktions_lauf;
       for (aktions_lauf = case_lauf -> case_aktion;
            aktions_lauf;
            aktions_lauf = aktions_lauf -> next) {
            
         if (aktions_lauf -> aktions_typ == aktion_aufruf) {
	        struct argument_liste * argument_lauf;
	        for (argument_lauf = aktions_lauf -> u.aktion_aufruf.argument_liste;
	             argument_lauf;
	             argument_lauf = argument_lauf -> next ) {
	          if (argument_lauf -> argument.argument_typ == parameter) {
	            int i = parameter_nummer (0,
	                        argument_lauf->argument.u.parameter.parameter_name, 
            	                 tmp_umstimmung -> parameter_liste);
            	if (i == EOF ) {
	              fatal_error(31,argument_lauf->argument.u.parameter.parameter_name,
	                             tmp_umstimmung -> name); /* Parameter n.dekl. */
	            }
	            else {
	              argument_lauf->argument.u.parameter.parameter_nummer = i;
	            } /* if */
	          } /* if */
	        }  /* for argument_lauf */
	     } /* if (aktions_lauf .. */
       }  /* for aktions_lauf */
      }  /* for case_lauf */
    }



}

#if 0

/** Liste für Case-Umstimmungen */
static struct aufruf_liste * tmp_umstimmungs_case_aufrufs_liste;


/** Setzt Case-Liste auf NULL.
 * \warning Die Argumentliste wird nicht gelöscht. 
 *          Das muss gegebenenfalls vor der Initialiserung manuell erledigt werden.
 */
void init_umstimmungs_case_aufrufs_liste (void)
{
    tmp_umstimmungs_case_aufrufs_liste = NULL;
}

/** Gibt die Wurzel von \a tmp_umstimmungs_case_aufrufs_liste zurück. */
static struct umstimmung * get_last_umstimmungs_case_aufrufs_liste (void)
{
    return tmp_umstimmungs_case_aufrufs_liste; 
}


/** Fügt eine Aufruf-Aktion ans Ende von \a tmp_umstimmungs_case_aufrufs_liste an. 
 * Der Aufruf erhält die letzte eingelesene Argumentliste.
 * Ist ein Parameter nicht definiert, wird ein fataler Fehler ausgegeben
 * \param aktion Bezeichnung der Aktion, die angefügt werden soll 
 * \note Es wird immer die gesamte Liste durchsucht. Effektivität?
 */
void get_umstimmungs_case_aufrufs_element (char * aktion)
{
    struct aufruf_liste * * lauf;
    for (lauf= & tmp_umstimmungs_case_aufrufs_liste; 
         * lauf; 
         lauf= & (*lauf)->next)
        /* Nur Ende der Liste finden */ ;
    
    (* lauf) = xmalloc (sizeof (struct aufruf_liste));
    (* lauf) -> name                = aktion;
    (* lauf) -> argument_liste      = get_last_argument_liste ();
    (* lauf) -> next                = NULL;

/* check, ob die Parameter zulässig sind */

    {
        struct argument_liste * params;
        for (params = (* lauf) -> argument_liste;
             params;
             params = params -> next ) {
          if (params -> argument.argument_typ == parameter) {
            if (parameter_nummer (0,params->argument.u.parameter.parameter_name, 
                 tmp_umstimmung -> parameter_liste)  == EOF ) {
              fatal_error(31,params->argument.u.parameter.parameter_name,
                             (*lauf)->name); /* Parameter n.dekl. */
            }
          }
        }
    }

}

#endif

/** Sucht ein Case-Label in einer entsprechenden Liste.
 * \param[in] case_label Zu suchendes Label
 * \param[in] lauf Liste, in der gesucht wird
 * \retval 1 Label wurde gefunden
 * \retval 0 Label wurde nicht gefunden
 */
int case_label_enthalten_in_case_liste (double case_label, struct case_liste * lauf)
{      if (lauf == NULL)
           return 0;
  else if ( ! lauf -> is_default  &&
               ( (int)(case_label) == (int)(lauf -> case_label) ) )
           return 1;
  else
           return case_label_enthalten_in_case_liste (case_label, lauf -> next);
}        

/** \} */

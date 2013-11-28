/** \file
 ********************************************************************
 * Everything about event triggers
 *
 * Copyright:   (c) 2011 TU Dresden
 * \author Tobias Schlemmer <keinstein@users.berlios.de>
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
 * \addtogroup Parser
 * \{
 ********************************************************************/
#ifdef HAVE_CONFIG_H
#  include "config.h"
#endif
#ifdef HAVE_STDDEF_H
#  include <stddef.h>
#endif
#include <string.h>
#include <stdio.h>
#include "mutabor/ausloeser.h"
#include "mutabor/heap.h"
#include "mutabor/harmonie.h"
#include "mutabor/taste.h"
#include "mutabor/logik.h"
#include "mutabor/anweisung.h"

/** Globaler Zwischenspeicher für auslösende Ereignisse */
static struct ausloeser * tmp_ausloeser;
/** Liste der globalen auslösenden Harmonieen. */
struct harmonie_ereignis *  first_harmonie[MAX_BOX];
/** Letztes Element der globalen auslösenden Harmonien. */
struct harmonie_ereignis ** last_global_harmonie[MAX_BOX];
/** Liste der lokalen auslösenden Harmonien. */
struct harmonie_ereignis ** first_lokal_harmonie;
/** Liste der globalen auslösenden Tastenereignissen. */
struct keyboard_ereignis *  first_keyboard[MAX_BOX];
/** Letztes Element der globalen auslösenden Tastenereignissen. */
struct keyboard_ereignis ** last_global_keyboard[MAX_BOX];
/** Liste der lokalen auslösenden Tastenereignissen. */
struct keyboard_ereignis ** first_lokal_keyboard;
/** Liste der globalen auslösenden MIDI-Ereignissen. */
struct midi_ereignis     *  first_midi[MAX_BOX];
/** Letztes Element der globalen auslösenden MIDI-Ereignissen. */
struct midi_ereignis     ** last_global_midi[MAX_BOX];
/** Liste der lokalen auslösenden MIDI-Ereignissen. */
struct midi_ereignis     ** first_lokal_midi;


/** Setzt Liste auslösender Ereignisse auf NULL.
 * \warning Die Liste wird nicht gelöscht. 
 *          Das muss gegebenenfalls vor der Initialiserung manuell erledigt werden.
 */
void init_ausloeser (void)
{
    tmp_ausloeser = NULL;
}

/** Gibt Wurzelelement von \a #tmp_ausloeser zurück */
struct ausloeser * get_last_ausloeser (void)
{
    return tmp_ausloeser;
}

/** Markiert \c #tmp_ausloeser als Standard-Auslöser */
void get_ausloeser_default (void)
{
    tmp_ausloeser = (struct ausloeser*) xmalloc (sizeof (struct ausloeser));
    tmp_ausloeser -> ausloeser_typ = ausloeser_default;
}

/** Deklariert \c #tmp_ausloeser als Harmonie-Auslöser und setzt die Werte aus 
 * dem Zwischenspeicher.
 */
void get_ausloeser_harmonie (void)
{
    tmp_ausloeser = (struct ausloeser*) xmalloc (sizeof (struct ausloeser));
    tmp_ausloeser -> ausloeser_typ = ausloeser_harmonie;
    tmp_ausloeser -> u.ausloeser_harmonie.vortaste  = tmp_vor_taste;
    tmp_ausloeser -> u.ausloeser_harmonie.name      = tmp_name;
    tmp_ausloeser -> u.ausloeser_harmonie.nachtaste = tmp_nach_taste;
}

/** Deklariert \c #tmp_ausloeser als Harmonie-Auslöser und setzt die Werte aus 
 * dem Zwischenspeicher.
 */
void get_ausloeser_harmonie_form (void)
{
    tmp_ausloeser = (struct ausloeser*) xmalloc (sizeof (struct ausloeser));
    tmp_ausloeser -> ausloeser_typ = ausloeser_harmonie_form;
    tmp_ausloeser -> u.ausloeser_harmonie_form.vortaste  = tmp_vor_taste;
    tmp_ausloeser -> u.ausloeser_harmonie_form.name      = tmp_name;
    tmp_ausloeser -> u.ausloeser_harmonie_form.nachtaste = tmp_nach_taste;
}

/** Deklariert \c tmp_ausloeser als Tasten-Auslöser.
 * Ist die Taste nicht definiert, wird ein fataler Fehler ausgelöst.
 * \param name Name der auslösenden Taste
 */
void get_ausloeser_taste (char * name)
{
    tmp_ausloeser = (struct ausloeser*) xmalloc (sizeof (struct ausloeser));
    tmp_ausloeser -> ausloeser_typ = ausloeser_taste;
    tmp_ausloeser -> u.ausloeser_taste.taste  = name;

    if (strlen (name) != 1) {
        fatal_error (52, name);
    }

}

/** Deklariert \c tmp_ausloeser als MIDI-Sequenz. Dafür wird die letzte 
 * eingelesene Ganzzahlen-Folge verwendet.
 */
void get_ausloeser_midi_in (void)
{
    tmp_ausloeser = (struct ausloeser*) xmalloc (sizeof (struct ausloeser));
    tmp_ausloeser -> ausloeser_typ = ausloeser_midi_in;
    tmp_ausloeser -> u.ausloeser_midi_in.midi_code  
                      = get_last_integersequenz ();
}


/** Gibt einen Auslöser auf der Standard-Ausgabe aus.
 * \param[in] this_ Auslöser.
 */
void print_ausloeser (struct ausloeser * this_)
{
  if (this_) {
    switch (this_->ausloeser_typ)
    {
    default: fatal_error (0, "print_ausloeser");
    case ausloeser_default:
         printf ("ANSONSTEN\n");
         break;
    case ausloeser_harmonie:
         printf ("Harmonie  Vor-Taste: %d"
                 " Harmonie-Name: %s"
                 " Nach-Taste: %d \n",
                 this_->u.ausloeser_harmonie.vortaste,
                 this_->u.ausloeser_harmonie.name,
                 this_->u.ausloeser_harmonie.nachtaste);
         break;
    case ausloeser_harmonie_form:
         printf ("Harmonie FORM  Vor-Taste: %d"
                 " Harmonie-Name: %s"
                 " Nach-Taste: %d \n",
                 this_->u.ausloeser_harmonie_form.vortaste,
                 this_->u.ausloeser_harmonie_form.name,
                 this_->u.ausloeser_harmonie_form.nachtaste);
         break;
    case ausloeser_taste:
         printf ("TASTE  %s\n",
                 this_->u.ausloeser_taste.taste);
         break;
    case ausloeser_midi_in:
         printf ("MIDI-IN: ");
         print_integersequenz (this_->u.ausloeser_midi_in.midi_code);
         break;
    }
  }
  else
     printf ("Kein Ausloeser\n");
}

/** Testet einen Auslöser auf Zulässigkeit. Wird eine nicht zulässige oder erreichbare
 * Konfiguration gefunden, wird je nach Situation ein fataler Fehler oder eine Compiler-Warnung
 * ausgelöst.
 * \param[in] ausloeser Auslöser, der geprüft werden soll
 * \param[in] name Name für Meldungen 
 */
void check_ausloeser (struct ausloeser * ausloeser, char * name) {

          struct harmonie * help_harmonie;
          
          if (ausloeser == NULL) return;
          
          if (ausloeser->ausloeser_typ == ausloeser_harmonie_form) {
              help_harmonie = get_harmonie (ausloeser->u.ausloeser_harmonie_form.name, list_of_harmonien);
              if (help_harmonie == NULL) {
                  fatal_error (30, 
                               ausloeser->u.ausloeser_harmonie_form.name,
                               name);
              }
              if (enthalten_in_tastenliste 
                    (ausloeser->u.ausloeser_harmonie_form.vortaste, 
                     help_harmonie->tastenliste) ||
                     ausloeser->u.ausloeser_harmonie_form.vortaste
                        == -1 ) {
                /* OK */
              }
              else {
                  compiler_warning (2, name);
/* Markierung setzen, fuer unmoeglichen Ausloeser */
                  ausloeser->u.ausloeser_harmonie_form.vortaste = -2;
              }
              if (enthalten_in_tastenliste 
                    (ausloeser->u.ausloeser_harmonie_form.nachtaste, 
                     help_harmonie->tastenliste) ||
                     ausloeser->u.ausloeser_harmonie_form.nachtaste
                          == -1 ) {
                /* OK */
              }
              else {
                  compiler_warning (2, name);
/* Markierung setzen, fuer unmoeglichen Ausloeser */
                  ausloeser->u.ausloeser_harmonie_form.vortaste = -2;
              }
          }

          
          if (ausloeser->ausloeser_typ == ausloeser_harmonie) {
              help_harmonie = get_harmonie (ausloeser->u.ausloeser_harmonie.name, list_of_harmonien);
              if (help_harmonie == NULL) {
                  fatal_error (30, 
                               ausloeser->u.ausloeser_harmonie.name,
                               name);
              }
              if (enthalten_in_tastenliste 
                       (ausloeser->u.ausloeser_harmonie.vortaste, 
                        help_harmonie->tastenliste) ||
                        ausloeser->u.ausloeser_harmonie.vortaste
                            == -1 ) {
                /* OK */
              }
              else {
                  compiler_warning (2, name);
/* Markierung setzen, fuer unmoeglichen Ausloeser */
                  ausloeser->u.ausloeser_harmonie.vortaste = -2;
              }
              if (enthalten_in_tastenliste 
                       (ausloeser->u.ausloeser_harmonie.nachtaste, 
                        help_harmonie->tastenliste) ||
                        ausloeser->u.ausloeser_harmonie.nachtaste
                            == -1 ) {
                /* OK */
              }
              else {
                  compiler_warning (2, name);
/* Markierung setzen, fuer unmoeglichen Ausloeser */
                  ausloeser->u.ausloeser_harmonie.vortaste = -2;
              }
          }

          if (ausloeser->ausloeser_typ == ausloeser_midi_in) {
              struct midiliste * midi_lauf 
                   = ausloeser->u.ausloeser_midi_in.midi_code;
              if (midi_lauf -> midi_code < 128 || 
                  midi_lauf -> midi_code > 255 ) {
                    fatal_error (50, name,"Statusbyte");
              }
              if (midi_lauf -> midi_code & 0x000F ) {
                    midi_lauf -> midi_code &= 0xFFF0;
                    compiler_warning(1,name);        
              }      
              midi_lauf = midi_lauf -> next;
              while (midi_lauf) {
                  if (midi_lauf -> midi_code < 0 ||
                      midi_lauf -> midi_code > 127 ) {
                      fatal_error (50, name,"Datenbyte");
                  }
                  else 
                      midi_lauf = midi_lauf -> next;
              }
          }

}

/** \}
 * \defgroup Interpreter
 * \{
 */

/** Fügt die auslösende Harmonien, Taste bzw. das Midiereignis der Logik in die 
 * entsprechenede globale Liste eines Instrumentes ein.
 * \param instrument Instrument, für das das Ereignis eingefügt werden soll.
 * \param lauf Logik, deren Auslöser eingefügt werden soll.
 */

void insert_in_globale_liste (int instrument, struct logik * lauf)
{
    struct harmonie_ereignis ** temp_harmonie;
    struct keyboard_ereignis ** temp_keyboard;
    struct midi_ereignis     ** temp_midi;

    if (lauf->ausloeser) {
        switch ((lauf->ausloeser)->ausloeser_typ) {
            case ausloeser_harmonie:
                if (lauf->ausloeser->u.ausloeser_harmonie.vortaste == -2)
            /* Dann unmöglicher Harmonieauslöser */
                    break;

                /* Neuen Eintrag erzeugen */
                for (temp_harmonie = & first_harmonie[instrument];
                     *temp_harmonie;
                     temp_harmonie = & (*temp_harmonie)->next)
                ;

                *temp_harmonie = (struct harmonie_ereignis*) xmalloc( (size_t)sizeof(struct harmonie_ereignis));
                (*temp_harmonie) -> pattern=expand_pattern ((lauf->ausloeser)->u.ausloeser_harmonie.name) ;
                (*temp_harmonie) -> ist_harmonieform=0;
                (*temp_harmonie) -> vortaste=(lauf->ausloeser)->u.ausloeser_harmonie.vortaste ;
                (*temp_harmonie) -> nachtaste=(lauf->ausloeser)->u.ausloeser_harmonie.nachtaste ;
                (*temp_harmonie) -> name=lauf->name;
                (*temp_harmonie) -> aktion=NULL;
                (*temp_harmonie) -> the_logik_to_expand=lauf;
                (*temp_harmonie) -> next=NULL;
            break;
            case ausloeser_harmonie_form:
                if (lauf->ausloeser->u.ausloeser_harmonie_form.vortaste == -2)
            /* Dann unmöglicher Harmonieauslöser */
                    break;
                /* Neuen Eintrag erzeugen */
                for (temp_harmonie = & first_harmonie[instrument];
                     *temp_harmonie;
                     temp_harmonie = & (*temp_harmonie)->next) 
                ;

                *temp_harmonie  = (struct harmonie_ereignis*) xmalloc((size_t)sizeof(struct harmonie_ereignis));
                (*temp_harmonie) -> pattern=expand_pattern ((lauf->ausloeser)->u.ausloeser_harmonie_form.name) ;
                (*temp_harmonie) -> ist_harmonieform=1;
                (*temp_harmonie) -> vortaste=(lauf->ausloeser)->u.ausloeser_harmonie_form.vortaste ;
                (*temp_harmonie) -> nachtaste=(lauf->ausloeser)->u.ausloeser_harmonie_form.nachtaste ;
                (*temp_harmonie) -> name=lauf->name;
                (*temp_harmonie) -> aktion=NULL;
                (*temp_harmonie) -> the_logik_to_expand=lauf;
                (*temp_harmonie) -> next=NULL;
            break;
            case ausloeser_taste:
                /* Neuen Eintrag erzeugen */
                for (temp_keyboard = & first_keyboard[instrument];
                     *temp_keyboard;
                     temp_keyboard = & (*temp_keyboard)->next)
                ;

                *temp_keyboard  = (struct keyboard_ereignis*) xmalloc((size_t)sizeof(struct keyboard_ereignis));
                (*temp_keyboard) -> taste= (*((lauf->ausloeser)->u.ausloeser_taste.taste)) ;
                (*temp_keyboard) -> name=lauf->name;
                (*temp_keyboard) -> aktion=NULL;
                (*temp_keyboard) -> the_logik_to_expand=lauf;
                (*temp_keyboard) -> next=NULL;
            break;
            case ausloeser_midi_in:
                /* Neuen Eintrag erzeugen */
                for (temp_midi = & first_midi[instrument];
                     *temp_midi;
                     temp_midi = & (*temp_midi)->next) 
                ;

                *temp_midi  = (struct midi_ereignis*) xmalloc((size_t)sizeof(struct midi_ereignis));
                /* Werte eintragen */
                   
                (*temp_midi) -> first_pos =
                (*temp_midi) -> scan_pos =
                        create_midi_scan_liste (lauf->ausloeser->u.ausloeser_midi_in.midi_code);
                (*temp_midi) -> name = lauf->name;
                (*temp_midi) -> aktion=NULL;
                (*temp_midi) -> the_logik_to_expand=lauf;
                (*temp_midi) -> next = NULL;
            break;
            default: fatal_error(0, __FILE__, __LINE__);
        }
    }
}

/** Liefert einen Zeiger auf den Nachfolge-Zeiger des letzten Elementes einer
 *  Harmonie-Ereignis-Liste.
 * \param lauf Zeiger auf die Wurzel einer einfach verketteten Liste von Harmonieereignissen.
 */
struct harmonie_ereignis ** 
        get_ende_harmonie (struct harmonie_ereignis ** lauf)
{
    if (*lauf == NULL) return lauf;
    return get_ende_harmonie (& (*lauf) -> next);
}

/** Liefert einen Zeiger auf den Nachfolge-Zeiger des letzten Elementes einer
 *  Tasten-Ereignis-Liste.
 * \param lauf Zeiger auf die Wurzel einer einfach verketteten Liste von Tastenereignissen.
 */
struct keyboard_ereignis **
        get_ende_keyboard (struct keyboard_ereignis ** lauf) 
{
    if (*lauf == NULL) return lauf;
    return get_ende_keyboard (& (*lauf) -> next);
}

/** Liefert einen Zeiger auf den Nachfolge-Zeiger des letzten Elementes einer
 *  MIDI-Ereignis-Liste.
 * \param lauf Zeiger auf die Wurzel einer einfach verketteten Liste von MIDI-Ereignissen.
 */
struct midi_ereignis **
        get_ende_midi (struct midi_ereignis ** lauf) 
{
    if (*lauf == NULL) return lauf;
    return get_ende_midi (& (*lauf) -> next);
}

/** Fügt die auslösende Harmonien, Taste bzw. das Midiereignis der Logik in die 
 * entsprechenede lokale Liste eines Instrumentes ein.
 * \param instrument Instrument, für das das Ereignis eingefügt werden soll.
 * \param lauf Anweisung, deren Auslöser eingefügt werden soll.
 * \param name_der_logik Name der Logik, zu der die Anweisung gehört.
 */
void insert_in_lokale_liste (int instrument, struct anweisung * lauf,
                             char * name_der_logik)
{
    struct harmonie_ereignis ** temp_harmonie;
    struct keyboard_ereignis ** temp_keyboard;
    struct midi_ereignis     ** temp_midi;

    if (lauf->ausloeser) {
        switch ((lauf->ausloeser)->ausloeser_typ) {
            case ausloeser_harmonie:
                if (lauf->ausloeser->u.ausloeser_harmonie.vortaste == -2)
            /* Dann unmöglicher Harmonieauslöser */
                    break;

                /* Neuen Eintrag erzeugen */
                for (temp_harmonie = & first_lokal_harmonie[instrument];
                     *temp_harmonie;
                     temp_harmonie = & (*temp_harmonie)->next)
                ;

                *temp_harmonie = (struct harmonie_ereignis*) xmalloc( (size_t)sizeof(struct harmonie_ereignis));
                (*temp_harmonie) -> pattern =expand_pattern ((lauf->ausloeser)->u.ausloeser_harmonie.name) ;
                (*temp_harmonie) -> ist_harmonieform=0;
                (*temp_harmonie) -> vortaste=(lauf->ausloeser)->u.ausloeser_harmonie.vortaste ;
                (*temp_harmonie) -> nachtaste=(lauf->ausloeser)->u.ausloeser_harmonie.nachtaste ;
                (*temp_harmonie) -> name=name_der_logik;
                (*temp_harmonie) -> aktion=
                         expand_aktions_liste (lauf->aktion, start_parameter_liste);
                (*temp_harmonie) -> next=NULL;
            break;
            case ausloeser_harmonie_form:
                if (lauf->ausloeser->u.ausloeser_harmonie_form.vortaste == -2)
            /* Dann unmöglicher Harmonieauslöser */
                    break;
                /* Neuen Eintrag erzeugen */
                for (temp_harmonie = & first_lokal_harmonie[instrument];
                     *temp_harmonie;
                     temp_harmonie = & (*temp_harmonie)->next) 
                ;

                *temp_harmonie  = (struct harmonie_ereignis*) xmalloc((size_t)sizeof(struct harmonie_ereignis));
                (*temp_harmonie) -> pattern=expand_pattern ((lauf->ausloeser)->u.ausloeser_harmonie_form.name) ;
                (*temp_harmonie) -> ist_harmonieform=1;
                (*temp_harmonie) -> vortaste=(lauf->ausloeser)->u.ausloeser_harmonie_form.vortaste ;
                (*temp_harmonie) -> nachtaste=(lauf->ausloeser)->u.ausloeser_harmonie_form.nachtaste ;
                (*temp_harmonie) -> name=name_der_logik;
                (*temp_harmonie) -> aktion=
                         expand_aktions_liste (lauf->aktion, start_parameter_liste);
                (*temp_harmonie) -> next=NULL;
            break;
            case ausloeser_default:
                /* Neuen Eintrag erzeugen */
                for (temp_harmonie = & first_lokal_harmonie[instrument];
                     *temp_harmonie;
                     temp_harmonie = & (*temp_harmonie)->next) 
                ;

                *temp_harmonie  = (struct harmonie_ereignis*) xmalloc((size_t)sizeof(struct harmonie_ereignis));
                (*temp_harmonie) -> pattern=NULL ;
                (*temp_harmonie) -> ist_harmonieform=2;
/* 2 als Wert für ANSONSTEN */

                (*temp_harmonie) -> vortaste=0 ;
                (*temp_harmonie) -> nachtaste=0 ;
                (*temp_harmonie) -> name=name_der_logik;
                (*temp_harmonie) -> aktion=
                         expand_aktions_liste (lauf->aktion, start_parameter_liste);
                (*temp_harmonie) -> next=NULL;
            break;
            case ausloeser_taste:
                /* Neuen Eintrag erzeugen */
                for (temp_keyboard = & first_lokal_keyboard[instrument];
                     *temp_keyboard;
                     temp_keyboard = & (*temp_keyboard)->next) 
                ;

                *temp_keyboard  = (struct keyboard_ereignis*) xmalloc((size_t)sizeof(struct keyboard_ereignis));
                (*temp_keyboard) -> taste= (*((lauf->ausloeser)->u.ausloeser_taste.taste)) ;
                (*temp_keyboard) -> name=name_der_logik;
                (*temp_keyboard) -> aktion=
                         expand_aktions_liste (lauf->aktion, start_parameter_liste);
                (*temp_keyboard) -> next=NULL;
            break;
            case ausloeser_midi_in:
                /* Neuen Eintrag erzeugen */
                for (temp_midi = & first_lokal_midi[instrument];
                     *temp_midi;
                     temp_midi = & (*temp_midi)->next)
                ;

                *temp_midi  = (struct midi_ereignis*) xmalloc((size_t)sizeof(struct midi_ereignis));
                /* Werte eintragen */

                (*temp_midi) -> first_pos =
                (*temp_midi) -> scan_pos =
                        create_midi_scan_liste (lauf->ausloeser->u.ausloeser_midi_in.midi_code);
                (*temp_midi) -> name=name_der_logik;
                (*temp_midi) -> aktion=
                         expand_aktions_liste (lauf->aktion, start_parameter_liste);
                (*temp_midi) -> next = NULL;
            break;
            default: fatal_error(0, __FILE__, __LINE__);
        }
    }
}


/** Expandiert die Auslösenden Ereignisse aller angesammeldten Logiken in die globale
 * Liste.
 */
void expandiere_in_globale_liste (void)
{
    struct harmonie_ereignis * lauf_harmonie [MAX_BOX];
    struct keyboard_ereignis * lauf_keyboard [MAX_BOX];
    struct midi_ereignis     * lauf_midi     [MAX_BOX];
    int i;
    
    for (i=0; i<MAX_BOX; i++) {
        lauf_harmonie[i] = first_harmonie[i];
        lauf_keyboard[i] = first_keyboard[i];
        lauf_midi    [i] = first_midi    [i];
    }
    
    while (lauf_harmonie[0]) {
        int j;

        lauf_harmonie[0] -> aktion =
            expandiere_logik (lauf_harmonie[0] -> the_logik_to_expand);
        
        for (j=1; j<MAX_BOX; j++) {
            lauf_harmonie[j] -> aktion = lauf_harmonie[0] -> aktion;
        }

        for (j=0; j<MAX_BOX; j++) {
            lauf_harmonie[j] = lauf_harmonie[j] -> next;
        }
    }

        

    while (lauf_keyboard[0]) {
        int j;

        lauf_keyboard[0] -> aktion = 
            expandiere_logik (lauf_keyboard[0] -> the_logik_to_expand);

        for (j=1; j<MAX_BOX; j++) {
            lauf_keyboard[j] -> aktion = lauf_keyboard[0] -> aktion;
        }

        for (j=0; j<MAX_BOX; j++) {
            lauf_keyboard[j] = lauf_keyboard[j] -> next;
        }
    }
    
    
    
    while (lauf_midi[0]) {
        int j;

        lauf_midi[0] -> aktion =
            expandiere_logik (lauf_midi[0] -> the_logik_to_expand);

        for (j=1; j<MAX_BOX; j++) {
            lauf_midi[j] -> aktion = lauf_midi[0] -> aktion;
        }

        for (j=0; j<MAX_BOX; j++) {
            lauf_midi[j] = lauf_midi[j] -> next;
        }
    }

}


/** \} */

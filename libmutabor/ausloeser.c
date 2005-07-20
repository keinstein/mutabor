/** \file
 ********************************************************************
 * Alles zu Ereignis-Auslösern
 *
 * $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/libmutabor/ausloeser.c,v 1.3 2005/07/20 09:49:55 keinstein Exp $
 * \author Tobias Schlemmer <keinstein_junior@gmx.net>
 * \date $Date: 2005/07/20 09:49:55 $
 * \version $Revision: 1.3 $
 *
 * $Log: ausloeser.c,v $
 * Revision 1.3  2005/07/20 09:49:55  keinstein
 * Includes für Doxygen verschönert
 * config.h genutzt
 * ein paar Links für Doxygen
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

/** Globaler Zwischenspeicher für auslösende Ereignisse */
static struct ausloeser * tmp_ausloeser;


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



/** \file
 ********************************************************************
 * Alles zu Instrumenten.
 *
 * $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/libmutabor/instrument.c,v 1.2 2005/07/19 15:15:27 keinstein Exp $
 * \author Tobias Schlemmer <keinstein_junior@gmx.net>
 * \date $Date: 2005/07/19 15:15:27 $
 * \version $Revision: 1.2 $
 *
 * $Log: instrument.c,v $
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
#include "mutabor/instrument.h"
#include "mutabor/bad_decl.h"
#include "mutabor/heap.h"

/******* Einlesen der Instrumente *******/
/** Einlesen der Instrumentdeklarationen.
 * Falls das Instrument schon vorhanden ist, wird eine Fehlermeldung ausgegeben.
 * \param[in]     midi_in          MIDI-Instrument
 * \param[in]     midi_von         kleinster MIDI-Kanal
 * \param[in]     midi_bis         größter MIDI-Kanal
 * \param[in]     midi_umleit      MIDI-Durchleitung
 * \param[in,out] list_to_insert  Instrumentenliste
 * \note Es wird immer die gesamte Liste durchsucht. Effektivität?
 */
void get_instrument_dekl (int midi_in, int midi_von, int midi_bis, int midi_umleit,
                          struct instrument ** list_to_insert)
{   int temp;

/**for (list_to_insert = & list_of_instrumente; */
      for (;
         * list_to_insert;
         list_to_insert = & (*list_to_insert)->next) {
        if ( midi_in == (*list_to_insert)->midi_in) {
            fatal_error(18,midi_in); /* MIDI-Instrument doppelt */
        }
    }

    if ( midi_von > midi_bis ) {
        temp=midi_von;       /* Vertauschen der Reihenfolge */
        midi_von=midi_bis;
        midi_bis=temp;

    }

    if ( (midi_in < 1) || (midi_in > 16) ) {
        fatal_error(45);
    }

    if ( midi_von && midi_bis )
    {
      if ( (midi_von < 1) || (midi_von > 16) )
        fatal_error(45);
      if ( (midi_bis < 1) || (midi_bis > 16) ) 
        fatal_error(45);
    }

    if ( (midi_umleit < 0) || (midi_umleit > 16) ) {
        fatal_error(45);
    }


    (* list_to_insert) = (struct instrument*) xmalloc (sizeof (struct instrument));
    (* list_to_insert) -> midi_in             = midi_in;
    (* list_to_insert) -> midi_von            = midi_von;
    (* list_to_insert) -> midi_bis            = midi_bis;
    (* list_to_insert) -> midi_umleit         = midi_umleit;
    (* list_to_insert) -> next                = NULL;

}



/** \file
 ***********************************************************************
 * Error descriptions for Mutabor.
 *
 * $Id: Errors.cpp,v 1.8 2010/11/21 13:15:44 keinstein Exp $
 * \author R. Krauße <krausze@users.berlios.de>
 * T. Schlemmer <keinstein@users.berlios.de>
 * \date $Date: 2010/11/21 13:15:44 $
 * \version $Revision: 1.8 $
 *
 * $Log: Errors.cpp,v $
 * Revision 1.8  2010/11/21 13:15:44  keinstein
 * merged experimental_tobias
 *
 * Revision 1.7.2.3  2010-05-07 11:40:27  keinstein
 * actual_settings
 *
 * Revision 1.7.2.2  2009/11/30 12:08:57  keinstein
 * split MutRouteShapes into several files into directory Routing
 *
 * Revision 1.7.2.1  2009/08/04 11:30:49  keinstein
 * removed mut.h
 *
 * Revision 1.7  2008/10/14 08:07:59  keinstein
 * added Errors.h and started to define Error symbols
 *
 * Revision 1.6  2008/08/18 14:59:41  keinstein
 * added License header
 * added const to string arrays
 * some reformatting
 *
 *
 */
#include "GrafKern.h"
#include "Errors.h"

#if defined(WX)
#else
#ifndef N_
#define N_(s) s
#endif
#endif

#if defined(GERMAN) && !defined(WX)

const mutChar * Error_text[] =
        {

                /* 0 */ "Undefinierter Fehler in %s   Zeile %d !", /* allgemeinster Fehler */

                /* Datei- und Systemfehler */
                /* 1 */ "Syntaktischer Fehler, nicht näher spezifiziert. (Zeile %d)" ,
                "Ungültiges Zeichen im Quelltext: asc=%d (Zeile %d)",
                "Kann Datei nicht öffnen: %s",
                "Speichermangel oder zu wenig Daten für Mutabor in Quelldatei.",
                "Kommentar am Dateiende nicht abgeschlossen.",
                " ",
                " ",
                " ",
                " ",

                /* Doppeldeklarationen */
                /* 10 */ "Der Intervallname %s wurde doppelt benutzt",
                "Der Tonname %s wurde doppelt benutzt",
                "Der Tonsystemname %s wurde doppelt benutzt",
                "Der Umstimmungsname %s wurde doppelt benutzt",
                "Der Harmoniename %s wurde doppelt benutzt",
                "Der Logikname %s wurde doppelt benutzt",
                "(unbenutzt)",
                "Der Parametername %s wurde doppelt benutzt",
                "Das MIDI-Instrument %d wurde doppelt benutzt",
                "Überlappungsfehler bei der MIDI-Zuordnung: Kanal %d wurde doppelt benutzt",
                "Mehr als ein ANSONSTEN-Auslöser in Logik %s",
                "Mehr als ein ANSONSTEN in Umstimmung %s",
                "Die Alternative %d ist doppelt in %s",
                " ",
                " ",

                /* Undefinierte Symbole */
                /* 25 */ "Unbekanntes Symbol: %s",
                "Unbekanntes Intervall: %s",
                "Unbekannter Ton: %s",
                "Unbekanntes Tonsystem: %s",
                "Unbekannte Umstimmung: %s",
                "Unbekannte Harmonie: %s (in Logik %s)",
                "Unbekannter Parametername: %s in %s",
                "Unbekanntes Intervall: %s (in %s)",
                "Unbekannter Ton: %s (in Tonsystem %s)",
                "Unbekannter Ton: %s (in Umstimmung %s)",
                /* 35 */ "(to be reused)",
                "Unbekannte Umstimmung: %s (in Umstimmung %s)",
                "Unbekannte Einstimmung: %s (in Logik %s)",
                "Unbekannte Aktion: %s (in Logik %s)",
                "Unbekannter Parameter: %s (in Aufruf %s von Logik %s)",
                " ",
                " ",
                " ",
                " ",
                " ",

                /* Bereichsüber- bzw. unterschreitungen */
                /* 45 */ "MIDI-Kanal ungültig (zulässig: 1 bis 16)",
                "Unzulässiger Wert von Intervall %s",
                "Taste %d liegt außerhalb des Wertebereichs 24..108 (in Tonsystem %s)",
                "In Umstimmung %s ist der Ton %s nicht komplex",
                "Unzulässiger Wert in %s", /* (allgemein) */
                "Unzulässiger MIDI-Code in Logik %s (erwarte %s)",
                "Logik %s darf nicht mit ANSONSTEN aufgerufen werden",
                "Als Taste eines Auslösers wurde kein einzelner Buchstabe angegeben TASTE %s",
                "Division durch (fast) 0 in Zeile %d",
                " ",
                " ",
                " ",
                " ",
                " ",
                " ",

                /* Parameterfehler */
                /* 60 */ "In Umstimmungsbund/case %s stimmen in Umstimmung %s die Parameter nicht",
                "In Logik %s stimmt die Parameter- anzahl von %s nicht",
                "In Logik %s ist die Einstimmung %s nicht parameterlos",
                "in Umstimmungsbund %s ist der Aufruf %s nicht parameterlos",
                "in Umstimmungs_case %s ist der Aufruf %s nicht parameterlos",

                /* Abhängigkeiten */
                /* 65 */ "Die Töne %s und %s hängen gegenseitig voneinander ab",
                "Die Umstimmungen/Logiken %s und %s hängen gegenseitig voneinander ab",
                "Die Intervalle %s und %s hängen gegenseitig voneinander ab",
                "Die MIDI-Kanäle hängen gegenseitig voneinander ab",
                " ",

                /* Syntaxfehler (vom BISON-Parser aufgerufen) */
                /* 70 */ "Falsches Zeichen! Erwarte %s (Zeile %d)",
                "Fehlerhafte Intervall- deklaration in Intervall %s.",
                "Fehlerhafte Tondeklaration von Ton %s.",
                "Fehlerhafte Tonsystem- deklaration. (Zeile %d)",
                "Ungültige Pameterliste in Zeile %d",
                "Ungültige Umstimmung in Zeile %d",
                "Ungültige Harmoniedekl. bei %s",
                "Fehlerhafte MIDI-Liste in Zeile %d",
                "Nach einem # folgt keine Hex-Ziffer (Zeile %d)",
                /* 79 */ "Deklaration erwartet. (Zeile %d)",
                "Zwei Punkte (.) in einer Zahl. (Zeile %d)",
                "Hier nur Integer statt Gleitkommazahl erlaubt (Zeile %d)",
                "Operand fehlt ? (Zeile %d)"

        };

const mutChar * Warning_text[] =
        {
                /*  0 */ "Undefinierte Compilerwarnung",
                "MIDI-Auslöser in Logik %s beginnt nicht mit Kanal 0-Statusbyte. "
                "Wert wurde korrigiert",
                "Unmöglicher Harmonieauslöser in Logik %s",
                "Mehrdeutiger Auslöser %s in Logik %s",
                "Auslöser ANSONSTEN ist nicht der letzte in Logik %s",
                /*  5 */ "Verschwendung bei der Kanalzuordnung",
                "Keine Datei angegeben, versuche test.mut",
                "Konfigurationsdatei fehlerhaft",
                "Echte Überschneidung bei der MIDI-Zuordnung: Kanäle %d und %d",
                "Fehler in GMN-Datei %s Position(%d, %d): %s"
        };

/* ====================================== ENGLISH ... ========= */

#else

const mutChar * Error_text[] =
        {

                /* 0 */ N_("Unknown error in %s , line %d !"), /* allgemeinster Fehler */

                /* Datei- und Systemfehler */
                /* 1 */ N_("Syntax error in line %d"),
                N_("Non-valid character: asc=%x (line %d)"),
                N_("Can't open file: %s"),
                N_("Not enough memory or too few data for mutabor in source file"),
                N_(" "),
                N_(" "),
                N_(" "),
                N_(" "),
                N_(" "),

                /* Doppeldeklarationen */
                /* 10 */ N_("The interval name %s was used twice"),
                N_("The tone name %s was used twice"),
                N_("The tonesystem name %s was used twice"),
                N_("The retuning name %s was used twice"),
                N_("The pattern name %s was used twice"),
                N_("The logic name %s was used twice"),
                N_("(unused)"),
                N_("The parameter name %s was used twice"),
                N_("The MIDI-Instrument %d was used twice"),
                N_("MIDI-Mapping: Channel %d was used twice"),
                N_("Logik %s contains more than one ELSE statement"),
                N_("Retuning %s contains more than one ELSE statement"),
                N_("The alternative %d is ued twice in %s"),
                N_(" "),
                N_(" "),

                /* Undefinierte Symbole */
                /* 25 */ N_("Undefined symbol: %s"),
                N_("Undefined interval: %s"),
                N_("Undefined tone: %s"),
                N_("Undefined tonesystem: %s"),
                N_("Undefined retuning: %s"),
                N_("Undefined pattern: %s (in logic %s)"),
                N_("Undefined parameter name: %s in %s"),
                N_("Undefined interval: %s (in %s)"),
                N_("Undefined tone: %s (in tone system %s)"),
                N_("Undefined tone: %s (in retuning %s)"),
                /* 35 */ N_("(to be reused)"),
                N_("Undefined retuning: %s (in retuning %s)"),
                N_("Undefined initial tuning: %s (in logic %s)"),
                N_("Undefined action: %s (in logic %s)"),
                N_("Undefined parameter: %s (in call %s from logic %s)"),
                N_(" "),
                N_(" "),
                N_(" "),
                N_(" "),
                N_(" "),

                /* Range violations */
                /* 45 */
                N_("Bad MIDI channel (valid: 1...16)"),
                N_("Bad interval value in %s"),
                N_("Bad key %d (valid: 36..96 (in tonesystem %s)"),
                N_("Not-complex tone in retuning %s ( %s )"),
                N_("Bad value in %s"), /* (allgemein) */
                N_("Bad MIDI-Code in logic %s (expecting %s )"),
                N_("Logic %s must not be called by ELSE"),
                N_("A Key needs to be a single character ( %s )"),
                N_("Division by (nearly) 0 in line %d"),
                N_(" "),
                N_(" "),
                N_(" "),
                N_(" "),
                N_(" "),
                N_(" "),

                /* Parameterfehler */
                /* 60 */ N_("In retuning %s and %s : Bad parameters"),
                N_("In logic %s : Bad number of parameters ( %s )"),
                N_("In logik %s : initial tuning %s mustn't have parameters"),
                N_("In collection %s : call to %s mustn't have parameters"),
                N_("In case %s : call to %s mustn't have parameters"),

                /* Dependencies */
                /* 65 */ N_("Tones %s and %s are dependent"),
                N_("Retunings/logics %s and %s are dependent"),
                N_("Intervals %s and %s are dependent"),
                N_("MIDI-channels are dependent"),
                N_(" "),

                /* Syntaxfehler (vom BISON-Parser aufgerufen) */
                /* 70 */ N_("Wrong character ! Expecting %s (line %d)"),
                N_("Bad interval declaration of intervall %s"),
                N_("Bad tone declaration of tone %s"),
                N_("Bad tonesystem declaration. (line %d)"),
                N_("Bad parameter list in call to %s in line %d"),
                N_("Bad retuning in line %d"),
                N_("bad pattern decl. at %s"),
                N_("Bad MIDI list in line %d"),
                N_("No hex number after # (line %d)"),
                N_(" ")

        };

const mutChar * Warning_text[] =
        {
                /*  0 */ N_("Undefined compiler warning"),
                N_("MIDI event in logic %s does not start with channel 0 status byte. Value corrected."),
                N_("Non existent harmony event in logic %s"),
                N_("Non well defined event %s in logic %s"),
                N_("Event ELSE is last in %s"),
                /*  5 */ N_("MIDI channels wasted in channel assotiation"),
                N_("No file given, trying test.mut"),
                N_("Invalid configuration file"),
                N_("Intersection of MIDI channels %d und %d"),
                N_("Error in GMN-File %s position(%d, %d): %s")
        };

#endif

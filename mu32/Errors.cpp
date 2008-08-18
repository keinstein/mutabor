/** \file
 ***********************************************************************
 * Error descriptions for Mutabor.
 *
 * $Id: Errors.cpp,v 1.6 2008/08/18 14:59:41 keinstein Exp $
 * \author R. Krau�e <krausze@users.berlios.de>
 * T. Schlemmer <keinstein@users.berlios.de>
 * \date $Date: 2008/08/18 14:59:41 $
 * \version $Revision: 1.6 $
 *
 * $Log: Errors.cpp,v $
 * Revision 1.6  2008/08/18 14:59:41  keinstein
 * added License header
 * added const to string arrays
 * some reformatting
 *
 *
 */
#include "GrafKern.h"

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
    /* 1 */ "Syntaktischer Fehler, nicht n�her spezifiziert. (Zeile %d)" ,
    "Ung�ltiges Zeichen im Quelltext: asc=%d (Zeile %d)",
    "Kann Datei nicht �ffnen: %s",
    "Speichermangel oder zu wenig Daten f�r Mutabor in Quelldatei.",
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
    "�berlappungsfehler bei der MIDI-Zuordnung: Kanal %d wurde doppelt benutzt",
    "Mehr als ein ANSONSTEN-Ausl�ser in Logik %s",
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

    /* Bereichs�ber- bzw. unterschreitungen */
    /* 45 */ "MIDI-Kanal ung�ltig (zul�ssig: 1 bis 16)",
    "Unzul�ssiger Wert von Intervall %s",
    "Taste %d liegt au�erhalb des Wertebereichs 24..108 (in Tonsystem %s)",
    "In Umstimmung %s ist der Ton %s nicht komplex",
    "Unzul�ssiger Wert in %s", /* (allgemein) */
    "Unzul�ssiger MIDI-Code in Logik %s (erwarte %s)",
    "Logik %s darf nicht mit ANSONSTEN aufgerufen werden",
    "Als Taste eines Ausl�sers wurde kein einzelner Buchstabe angegeben TASTE %s",
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

    /* Abh�ngigkeiten */
    /* 65 */ "Die T�ne %s und %s h�ngen gegenseitig voneinander ab",
    "Die Umstimmungen/Logiken %s und %s h�ngen gegenseitig voneinander ab",
    "Die Intervalle %s und %s h�ngen gegenseitig voneinander ab",
    "Die MIDI-Kan�le h�ngen gegenseitig voneinander ab",
    " ",

    /* Syntaxfehler (vom BISON-Parser aufgerufen) */
    /* 70 */ "Falsches Zeichen! Erwarte %s (Zeile %d)",
    "Fehlerhafte Intervall- deklaration in Intervall %s.",
    "Fehlerhafte Tondeklaration von Ton %s.",
    "Fehlerhafte Tonsystem- deklaration. (Zeile %d)",
    "Ung�ltige Pameterliste in Zeile %d",
    "Ung�ltige Umstimmung in Zeile %d",
    "Ung�ltige Harmoniedekl. bei %s",
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
    "MIDI-Ausl�ser in Logik %s beginnt nicht mit Kanal 0-Statusbyte. "
    "Wert wurde korrigiert",
    "Unm�glicher Harmonieausl�ser in Logik %s",
    "Mehrdeutiger Ausl�ser %s in Logik %s",
    "Ausl�ser ANSONSTEN ist nicht der letzte in Logik %s",
    /*  5 */ "Verschwendung bei der Kanalzuordnung",
    "Keine Datei angegeben, versuche test.mut",
    "Konfigurationsdatei fehlerhaft",
    "Echte �berschneidung bei der MIDI-Zuordnung: Kan�le %d und %d",
    "Fehler in GMN-Datei %s Position(%d, %d): %s"
  };

/* ====================================== ENGLISH ... ========= */

#else

const mutChar * Error_text[] =
  {

    /* 0 */ N_("Unknown error in %s , line %d !"), /* allgemeinster Fehler */

    /* Datei- und Systemfehler */
    /* 1 */ N_("Syntax error, not specified. (line %d)"),
    N_("Non-valid character: asc=%d (line %d)"),
    N_("Can't open file: %s"),
    N_("Not enough memory or to few datas for mutabor in source file"),
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

/** \file
 ********************************************************************
 * Fehlermeldungen des Mutabor-Parsers und -Compilers
 *
 * $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/libmutabor/errors.c,v 1.1 2005/11/03 14:04:04 keinstein Exp $
 * \author R.Krauße <krausze@users.berlios.de>
 * \date $Date: 2005/11/03 14:04:04 $
 * \version $Revision: 1.1 $
 *
 * $Log: errors.c,v $
 * Revision 1.1  2005/11/03 14:04:04  keinstein
 * initial revision
 *
 ********************************************************************/
#ifdef HAVE_CONFIG_H
#  include "config.h"
#endif
#include "mutabor/errors.h"

int mutabor_debug_level=0;

#define GERMAN
#ifdef GERMAN
char *Error_text[] =
{

/* 0 */ "Undefinierter Fehler in %s   Zeile %d !", /* allgemeinster Fehler */

/* Datei- und Systemfehler */
/* 1 */ "Syntaktischer Fehler, nicht näher spezifiziert. (Zeile %d, Spalte %d)" ,
		"Ungültiges Zeichen im Quelltext: asc=%x (Zeile %d)",
		"Kann Datei nicht öffnen: %s",
		"Speichermangel oder zu wenig Daten für Mutabor in Quelldatei.",
		"Kommentar am Dateiende nicht abgeschlossen.",
		"Dieser Punkt darf nicht aufgerufen werden (%f: %d)!\n"
                "Fehlerbericht bitte an : " PACKAGE_BUGREPORT,
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
         "Fehlerhafte Intervall- deklaration (Zeile %d)",
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

char * Warning_text[] =
{
/*  0 */ "Undefinierte Compilerwarnung",
         "MIDI-Auslöser in Logik %s beginnt nicht mit Kanal 0- Statusbyte. "
                 "Wert wurde korrigiert!",
         "Unmöglicher Harmonieauslöser in Logik %s",
         "Mehrdeutiger Auslöser %s in Logik %s",
         "Auslöser ANSONSTEN ist nicht der letzte in Logik %s",
/*  5 */ "Verschwendung bei der Kanalzuordnung",
			"Keine Datei angegeben, versuche TEST.MUS",
         "Konfigurationsdatei fehlerhaft",
         "Echte Überschneidung bei der MIDI-Zuordnung: Kanäle %d und %d",
       "Fehler in GMN-Datei %s Position(%d, %d): %s"
         };

/* ====================================== ENGLISH ... ========= */

#else

char *Error_text[] =
{

/* 0 */ "Unknown error in %s , line %d !", /* allgemeinster Fehler */

/* Datei- und Systemfehler */
/* 1 */ "Syntax error, not specified. (line %d)" ,
		"Non-valid character: asc=%d (line %d)",
		"Can't open file: %s",
		"Not enough memory or to few datas for mutabor in source file",
		" ",
		" ",
		" ",
		" ",
		" ",

/* Doppeldeklarationen */
/* 10 */ "The interval name %s was used twice",
         "The tone name %s was used twice",
			"The tonesystem name %s was used twice",
         "The retuning name %s was used twice",
         "The pattern name %s was used twice",
         "The logic name %s was used twice",
         "(unused)",
         "The parameter name %s was used twice",
         "The MIDI-Instrument %d was used twice",
         "MIDI-Mapping: Channel %d was used twice",
         "Logik %s contains more than one ELSE statement",
         "Retuning %s contains more than one ELSE statement",
         "The alternative %d is ued twice in %s",
			" ",
         " ",

/* Undefinierte Symbole */
/* 25 */ "Undefined symbol: %s",
         "Undefined interval: %s",
         "Undefined tone: %s",
         "Undefined tonesystem: %s",
         "Undefined retuning: %s",
         "Undefined pattern: %s (in logic %s)",
         "Undefined parameter name: %s in %s",
			"Undefined interval: %s (in %s)",
         "Undefined tone: %s (in tone system %s)",
         "Undefined tone: %s (in retuning %s)",
/* 35 */ "(to be reused)",
         "Undefined retuning: %s (in retuning %s)",
         "Undefined initial tuning: %s (in logic %s)",
         "Undefined action: %s (in logic %s)",
         "Undefined parameter: %s (in call %s from logic %s)",
         " ",
         " ",
         " ",
			" ",
         " ",
         
/* Bereichsüber- bzw. unterschreitungen */
/* 45 */ "Bad MIDI-Channel (valid: 1 .. 16)",
			"Bad interval value in %s",
         "Bad key %d (valid: 36..96 (in tonesystem %s)",
         "Not-complex tone in retuning %s ( %s )",
         "Bad value in %s", /* (allgemein) */
         "Bad MIDI-Code in logic %s (expecting %s )",
         "Logic %s must not be called by ELSE",
			"A Key needs to be a single character ( %s )",
         "Division by (nearly) 0 in line %d",
         " ",
         " ",
         " ",
			" ",
         " ",
         " ",
     
/* Parameterfehler */
/* 60 */ "In retuning %s and %s : Bad parameters",
			"In logic %s : Bad number of parameters ( %s )",
         "In logik %s : initial tuning %s mustn't have parameters",
         "In collection %s : call to %s mustn't have parameters",
         "In case %s : call to %s mustn't have parameters",

/* Abhängigkeiten */
/* 65 */ "Tones %s and %s are dependent",
         "Retunings/logics %s and %s are dependent",
         "Intervals %s and %s are dependent",
         "MIDI-channels are dependent",
         " ",

/* Syntaxfehler (vom BISON-Parser aufgerufen) */
/* 70 */ "Wrong character ! Expecting %s (line %d)",
         "Bad interval declaration of intervall %s",
         "Bad tone declaration of tone %s",
         "Bad tonesystem declaration. (line %d)",
         "Bad parameter list in call to %s in line %d",
         "Bad retuning in line %d",
         "bad pattern decl. at %s",
         "Bad MIDI list in line %d",
         "No hex number after # (line %d)",
			" ",

};

char * Warning_text[] =
{
/*  0 */ "Undefined compiler warning",
         "MIDI-Auslöser in Logik %s beginnt nicht mit Kanal 0- Statusbyte. "
                 "Wert wurde korrigiert!",
         "Unmöglicher Harmonieauslöser in Logik %s",
         "Mehrdeutiger Auslöser %s in Logik %s",
			"Auslöser ANSONSTEN ist nicht der letzte in Logik %s",
/*  5 */ "Verschwendung bei der Kanalzuordnung",
         "Keine Datei angegeben, versuche TEST.MUS",
         "Konfigurationsdatei fehlerhaft",
         "Überschneidung bei der MIDI-Zuordnung: Kanäle %d und %d",
       "Error in GMN-File %s position(%d, %d): %s"
};

#endif

#include "Global.h"

#ifdef GERMAN
char *Error_text[] =
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

char * Warning_text[] =
{
/*  0 */ "Undefinierte Compilerwarnung",
         "MIDI-Ausl�ser in Logik %s beginnt nicht mit Kanal 0- Statusbyte. "
                 "Wert wurde korrigiert!",
         "Unm�glicher Harmonieausl�ser in Logik %s",
         "Mehrdeutiger Ausl�ser %s in Logik %s",
         "Ausl�ser ANSONSTEN ist nicht der letzte in Logik %s",
/*  5 */ "Verschwendung bei der Kanalzuordnung",
			"Keine Datei angegeben, versuche TEST.MUS",
         "Konfigurationsdatei fehlerhaft",
         "Echte �berschneidung bei der MIDI-Zuordnung: Kan�le %d und %d",
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

/* Bereichs�ber- bzw. unterschreitungen */
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

/* Abh�ngigkeiten */
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
         "MIDI-Ausl�ser in Logik %s beginnt nicht mit Kanal 0- Statusbyte. "
                 "Wert wurde korrigiert!",
         "Unm�glicher Harmonieausl�ser in Logik %s",
         "Mehrdeutiger Ausl�ser %s in Logik %s",
			"Ausl�ser ANSONSTEN ist nicht der letzte in Logik %s",
/*  5 */ "Verschwendung bei der Kanalzuordnung",
         "Keine Datei angegeben, versuche TEST.MUS",
         "Konfigurationsdatei fehlerhaft",
         "�berschneidung bei der MIDI-Zuordnung: Kan�le %d und %d",
       "Error in GMN-File %s position(%d, %d): %s"
};

#endif
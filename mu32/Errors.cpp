

#if defined(WX)
  #include "wx/wx.h"
  #define STR wxString
#else
  #define _(s) s
  #define STR char*
#endif

#if defined(GERMAN) && !defined(WX) 
char *Error_text[] =
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

STR Error_text[] =
{

/* 0 */ _("Unknown error in %s , line %d !"), /* allgemeinster Fehler */

/* Datei- und Systemfehler */
/* 1 */ _("Syntax error, not specified. (line %d)"),
		_("Non-valid character: asc=%d (line %d)"),
		_("Can't open file: %s"),
		_("Not enough memory or to few datas for mutabor in source file"),
		_(" "),
		_(" "),
		_(" "),
		_(" "),
		_(" "),

/* Doppeldeklarationen */
/* 10 */ _("The interval name %s was used twice"),
		_("The tone name %s was used twice"),
		_("The tonesystem name %s was used twice"),
		_("The retuning name %s was used twice"),
		_("The pattern name %s was used twice"),
		_("The logic name %s was used twice"),
		_("(unused)"),
		_("The parameter name %s was used twice"),
		_("The MIDI-Instrument %d was used twice"),
		_("MIDI-Mapping: Channel %d was used twice"),
		_("Logik %s contains more than one ELSE statement"),
		_("Retuning %s contains more than one ELSE statement"),
		_("The alternative %d is ued twice in %s"),
		_(" "),
		_(" "),

/* Undefinierte Symbole */
/* 25 */ _("Undefined symbol: %s"),
		_("Undefined interval: %s"),
		_("Undefined tone: %s"),
		_("Undefined tonesystem: %s"),
		_("Undefined retuning: %s"),
		_("Undefined pattern: %s (in logic %s)"),
		_("Undefined parameter name: %s in %s"),
		_("Undefined interval: %s (in %s)"),
		_("Undefined tone: %s (in tone system %s)"),
		_("Undefined tone: %s (in retuning %s)"),
/* 35 */ _("(to be reused)"),
		_("Undefined retuning: %s (in retuning %s)"),
		_("Undefined initial tuning: %s (in logic %s)"),
		_("Undefined action: %s (in logic %s)"),
		_("Undefined parameter: %s (in call %s from logic %s)"),
		_(" "),
		_(" "),
		_(" "),
		_(" "),
		_(" "),

/* Bereichsüber- bzw. unterschreitungen */
/* 45 */ _("Bad MIDI-Channel (valid: 1 .. 16)"),
		_("Bad interval value in %s"),
		_("Bad key %d (valid: 36..96 (in tonesystem %s)"),
		_("Not-complex tone in retuning %s ( %s )"),
		_("Bad value in %s"), /* (allgemein) */
		_("Bad MIDI-Code in logic %s (expecting %s )"),
		_("Logic %s must not be called by ELSE"),
		_("A Key needs to be a single character ( %s )"),
		_("Division by (nearly) 0 in line %d"),
		_(" "),
		_(" "),
		_(" "),
		_(" "),
		_(" "),
		_(" "),

/* Parameterfehler */
/* 60 */ _("In retuning %s and %s : Bad parameters"),
		_("In logic %s : Bad number of parameters ( %s )"),
		_("In logik %s : initial tuning %s mustn't have parameters"),
		_("In collection %s : call to %s mustn't have parameters"),
		_("In case %s : call to %s mustn't have parameters"),

/* Abhängigkeiten */
/* 65 */ _("Tones %s and %s are dependent"),
		_("Retunings/logics %s and %s are dependent"),
		_("Intervals %s and %s are dependent"),
		_("MIDI-channels are dependent"),
		_(" "),

/* Syntaxfehler (vom BISON-Parser aufgerufen) */
/* 70 */ _("Wrong character ! Expecting %s (line %d)"),
		_("Bad interval declaration of intervall %s"),
		_("Bad tone declaration of tone %s"),
		_("Bad tonesystem declaration. (line %d)"),
		_("Bad parameter list in call to %s in line %d"),
		_("Bad retuning in line %d"),
		_("bad pattern decl. at %s"),
		_("Bad MIDI list in line %d"),
		_("No hex number after # (line %d)"),
		_(" ")

};

STR Warning_text[] =
{
/*  0 */ _("Undefined compiler warning"),
		_("MIDI-Auslöser in Logik %s beginnt nicht mit Kanal 0- Statusbyte. Wert wurde korrigiert!"),
		_("Unmoeglicher Harmonieausloeser in Logik %s"),
		_("Mehrdeutiger Ausloeser %s in Logik %s"),
		_("Auslöser ANSONSTEN ist nicht der letzte in Logik %s"),
/*  5 */ _("Verschwendung bei der Kanalzuordnung"),
		_("Keine Datei angegeben, versuche TEST.MUS"),
		_("Konfigurationsdatei fehlerhaft"),
		_("Überschneidung bei der MIDI-Zuordnung: Kanäle %d und %d"),
		_("Error in GMN-File %s position(%d, %d): %s")
};

#endif

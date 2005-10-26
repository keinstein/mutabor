// ##################################################################
// error messages of gsp (GMN Soft Parser)
// ##################################################################

char *GspErrorText[] =
{
  // 0: alles ok
  "OK",
  // 1-9: Klammerfehler
  /*  1 */ "Keine korrespondierende öffnende Klammer vorhanden.",
  /*  2 */ "Falsche schließende Klammer. '}' erwartet.",
  /*  3 */ "Falsche schließende Klammer. ']' erwartet.",
  /*  4 */ "Falsche schließende Klammer. ')' erwartet.",
  /*  5 */ "",
  /*  6 */ "",
  /*  7 */ "",
  /*  8 */ "",
  /*  9 */ "",
  // 10-19: Parameterfehler
  /* 10 */ "Parameter erwartet.",
  /* 11 */ "'>' oder ',' erwartet.",
  /* 12 */ "",
  /* 13 */ "",
  /* 14 */ "",
  /* 15 */ "",
  /* 16 */ "",
  /* 17 */ "",
  /* 18 */ "",
  /* 19 */ "",
  // 20-29: allgemeine Fehler
  /* 20 */ "Note, Tag oder öffnende Klammer erwartet.",
  /* 21 */ "Zähler für Notenlänge erwartet.",
  /* 22 */ "Nenner für Notenlänge erwartet.",
  /* 23 */ "Punktierung ohne Angabe der Notenlänge.",
  /* 24 */ "Unerwartetes Komma.",
  /* 25 */ "",
  /* 26 */ "",
  /* 27 */ "",
  /* 28 */ "",
  /* 29 */ "",
  // 30-39: Dateifehler
  /* 30 */ "Kann Datei nicht öffnen.",
  /* 31 */ "Fehler beim Schließen der Datei.",
  /* 32 */ "Fehler beim Lesen der Datei.",
  /* 33 */ "",
  /* 34 */ "",
  /* 35 */ "",
  /* 36 */ "",
  /* 37 */ "",
  /* 38 */ "",
  /* 39 */ "",
  // 40- 49: Strict-GMN-Fehler
  /* 40 */ "Datei muß mit '[' oder '{' beginnen.",
  /* 41 */ "Range ohne vorhergehendes Tag."

};

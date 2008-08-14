#include "Defs.h"
// ##################################################################
// error messages of gsp (GMN Soft Parser)
// ##################################################################

const mutChar *GspErrorText[] =
{
  // 0: alles ok
  N_("OK"),
  // 1-9: Klammerfehler
  /*  1 */ N_("No corresponding opening bracket."),
  /*  2 */ N_("Wrong closing bracket. '}' expected."),
  /*  3 */ N_("Wrong closing bracket. ']' expected."),
  /*  4 */ N_("Wrong closing bracket. ')' expected."),
  /*  5 */ N_(""),
  /*  6 */ N_(""),
  /*  7 */ N_(""),
  /*  8 */ N_(""),
  /*  9 */ N_(""),
  // 10-19: Parameterfehler
  /* 10 */ N_("Parameter expected."),
  /* 11 */ N_("'>' oder ',' erwartet."),
  /* 12 */ N_(""),
  /* 13 */ N_(""),
  /* 14 */ N_(""),
  /* 15 */ N_(""),
  /* 16 */ N_(""),
  /* 17 */ N_(""),
  /* 18 */ N_(""),
  /* 19 */ N_(""),
  // 20-29: allgemeine Fehler
  /* 20 */ N_("Note, tag or opening bracket expected."),
  /* 21 */ N_("Expected enumerator of note length."),
  /* 22 */ N_("Expected denominator of note length."),
  /* 23 */ N_("Dotted note, but no note length was given."),
  /* 24 */ N_("Unexpected comma."),
  /* 25 */ N_(""),
  /* 26 */ N_(""),
  /* 27 */ N_(""),
  /* 28 */ N_(""),
  /* 29 */ N_(""),
  // 30-39: Dateifehler
  /* 30 */ N_("Can't open file."),
  /* 31 */ N_("Error closing the file."),
  /* 32 */ N_("Error reading the file."),
  /* 33 */ N_(""),
  /* 34 */ N_(""),
  /* 35 */ N_(""),
  /* 36 */ N_(""),
  /* 37 */ N_(""),
  /* 38 */ N_(""),
  /* 39 */ N_(""),
  // 40- 49: Strict-GMN-Fehler
  /* 40 */ N_("The file must begin with '[' or '{'."),
  /* 41 */ N_("Range range without preceeding tag.")

};

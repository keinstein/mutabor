#include "Defs.h"
// ##################################################################
// error messages of gsp (GMN Soft Parser)
// ##################################################################

const mutTranslationChar *GspErrorText[] =
        {
                // 0: alles ok
                N_("OK"),
                // 1-9: Klammerfehler
                /*  1 */ N_("No corresponding opening bracket."),
                /*  2 */ N_("Wrong closing bracket. '}' expected."),
                /*  3 */ N_("Wrong closing bracket. ']' expected."),
                /*  4 */ N_("Wrong closing bracket. ')' expected."),
                /*  5 */ N_T(""),
                /*  6 */ N_T(""),
                /*  7 */ N_T(""),
                /*  8 */ N_T(""),
                /*  9 */ N_T(""),
                // 10-19: Parameterfehler
                /* 10 */ N_("Parameter expected."),
                /* 11 */ N_("'>' or ',' expected."),
                /* 12 */ N_T(""),
                /* 13 */ N_T(""),
                /* 14 */ N_T(""),
                /* 15 */ N_T(""),
                /* 16 */ N_T(""),
                /* 17 */ N_T(""),
                /* 18 */ N_T(""),
                /* 19 */ N_T(""),
                // 20-29: allgemeine Fehler
                /* 20 */ N_("Note, tag or opening bracket expected."),
                /* 21 */ N_("Expected enumerator of note length."),
                /* 22 */ N_("Expected denominator of note length."),
                /* 23 */ N_("Dotted note, but no note length was given."),
                /* 24 */ N_("Unexpected comma."),
                /* 25 */ N_T(""),
                /* 26 */ N_T(""),
                /* 27 */ N_T(""),
                /* 28 */ N_T(""),
                /* 29 */ N_T(""),
                // 30-39: Dateifehler
                /* 30 */ N_("Can't open file."),
                /* 31 */ N_("Error closing the file."),
                /* 32 */ N_("Error reading the file."),
                /* 33 */ N_T(""),
                /* 34 */ N_T(""),
                /* 35 */ N_T(""),
                /* 36 */ N_T(""),
                /* 37 */ N_T(""),
                /* 38 */ N_T(""),
                /* 39 */ N_T(""),
                // 40- 49: Strict-GMN-Fehler
                /* 40 */ N_("The file must begin with '[' or '{'."),
                /* 41 */ N_("Range without preceeding tag.")

        };

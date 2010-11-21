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
                /*  5 */ _T(""),
                /*  6 */ _T(""),
                /*  7 */ _T(""),
                /*  8 */ _T(""),
                /*  9 */ _T(""),
                // 10-19: Parameterfehler
                /* 10 */ N_("Parameter expected."),
                /* 11 */ N_("'>' or ',' expected."),
                /* 12 */ _T(""),
                /* 13 */ _T(""),
                /* 14 */ _T(""),
                /* 15 */ _T(""),
                /* 16 */ _T(""),
                /* 17 */ _T(""),
                /* 18 */ _T(""),
                /* 19 */ _T(""),
                // 20-29: allgemeine Fehler
                /* 20 */ N_("Note, tag or opening bracket expected."),
                /* 21 */ N_("Expected enumerator of note length."),
                /* 22 */ N_("Expected denominator of note length."),
                /* 23 */ N_("Dotted note, but no note length was given."),
                /* 24 */ N_("Unexpected comma."),
                /* 25 */ _T(""),
                /* 26 */ _T(""),
                /* 27 */ _T(""),
                /* 28 */ _T(""),
                /* 29 */ _T(""),
                // 30-39: Dateifehler
                /* 30 */ N_("Can't open file."),
                /* 31 */ N_("Error closing the file."),
                /* 32 */ N_("Error reading the file."),
                /* 33 */ _T(""),
                /* 34 */ _T(""),
                /* 35 */ _T(""),
                /* 36 */ _T(""),
                /* 37 */ _T(""),
                /* 38 */ _T(""),
                /* 39 */ _T(""),
                // 40- 49: Strict-GMN-Fehler
                /* 40 */ N_("The file must begin with '[' or '{'."),
                /* 41 */ N_("Range without preceeding tag.")

        };

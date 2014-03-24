/** \file
 ********************************************************************
 * Description
 *
 * $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/src/kernel/routing/gmn/GSP_Err.cpp,v 1.5 2011/11/02 14:31:57 keinstein Exp $
 * Copyright:   (c) 2008 TU Dresden
 * \author  Tobias Schlemmer <keinstein@users.berlios.de>
 * \date
 * $Date: 2011/11/02 14:31:57 $
 * \version $Revision: 1.5 $
 * \license GPL
 *
 * $Log: GSP_Err.cpp,v $
 * Revision 1.5  2011/11/02 14:31:57  keinstein
 * fix some errors crashing Mutabor on Windows
 *
 * Revision 1.4  2011-02-20 22:35:56  keinstein
 * updated license information; some file headers have to be revised, though
 *
 *
 *
 ********************************************************************
 * \addtogroup route
 * \{
 ********************************************************************/
// ##################################################################
// error messages of gsp (GMN Soft Parser)
// ##################################################################
#include "src/kernel/Defs.h"

const char *GspErrorText[] =
        {
                // 0: alles ok
                _mutN("OK"),
                // 1-9: Klammerfehler
                /*  1 */ _mutN("No corresponding opening bracket."),
                /*  2 */ _mutN("Wrong closing bracket. '}' expected."),
                /*  3 */ _mutN("Wrong closing bracket. ']' expected."),
                /*  4 */ _mutN("Wrong closing bracket. ')' expected."),
                /*  5 */ (""),
                /*  6 */ (""),
                /*  7 */ (""),
                /*  8 */ (""),
                /*  9 */ (""),
                // 10-19: Parameterfehler
                /* 10 */ _mutN("Parameter expected."),
                /* 11 */ _mutN("'>' or ',' expected."),
                /* 12 */ (""),
                /* 13 */ (""),
                /* 14 */ (""),
                /* 15 */ (""),
                /* 16 */ (""),
                /* 17 */ (""),
                /* 18 */ (""),
                /* 19 */ (""),
                // 20-29: allgemeine Fehler
                /* 20 */ _mutN("Note, tag or opening bracket expected."),
                /* 21 */ _mutN("Expected enumerator of note length."),
                /* 22 */ _mutN("Expected denominator of note length."),
                /* 23 */ _mutN("Dotted note, but no note length was given."),
                /* 24 */ _mutN("Unexpected comma."),
                /* 25 */ (""),
                /* 26 */ (""),
                /* 27 */ (""),
                /* 28 */ (""),
                /* 29 */ (""),
                // 30-39: Dateifehler
                /* 30 */ _mutN("Can't open file."),
                /* 31 */ _mutN("Error closing the file."),
                /* 32 */ _mutN("Error reading the file."),
                /* 33 */ (""),
                /* 34 */ (""),
                /* 35 */ (""),
                /* 36 */ (""),
                /* 37 */ (""),
                /* 38 */ (""),
                /* 39 */ (""),
                // 40- 49: Strict-GMN-Fehler
                /* 40 */ _mutN("The file must begin with '[' or '{'."),
                /* 41 */ _mutN("Range without preceeding tag.")

        };

///\}

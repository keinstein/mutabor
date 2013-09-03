/** \file
 ***********************************************************************
 * Error descriptions for Mutabor.
 *
 * $Id: Errors.h,v 1.5 2011/09/27 20:13:21 keinstein Exp $
 * \author R. Krauße <krausze@users.berlios.de>
 * T. Schlemmer <keinstein@users.berlios.de>
 * \date $Date: 2011/09/27 20:13:21 $
 * \version $Revision: 1.5 $
 * \license GPL
 *
 * $Log: Errors.h,v $
 * Revision 1.5  2011/09/27 20:13:21  keinstein
 * * Reworked route editing backend
 * * rewireing is done by RouteClass/GUIRoute now
 * * other classes forward most requests to this pair
 * * many bugfixes
 * * Version change: We are reaching beta phase now
 *
 * Revision 1.4  2011-02-20 22:35:55  keinstein
 * updated license information; some file headers have to be revised, though
 *
 * Revision 1.3  2010-12-11 02:10:08  keinstein
 * make 2.9.1 build but Mutabor crashes still at runtime in an infinite recursion :-(
 *
 * Revision 1.2  2010-11-21 13:15:44  keinstein
 * merged experimental_tobias
 *
 * Revision 1.1.2.2  2010-01-14 09:34:24  keinstein
 * Checkin searching for a bug
 *
 * Revision 1.1.2.1  2009/08/04 11:30:49  keinstein
 * removed mut.h
 *
 * Revision 1.1  2008/10/14 08:13:45  keinstein
 * provide symbolic error constants
 *
 * Revision 1.6  2008/08/18 14:59:41  keinstein
 * added License header
 * added const to string arrays
 * some reformatting
 *
 *
 ********************************************************************
 * \addtogroup kernel
 * \{
 ********************************************************************/

/* we guard a little bit complicated to ensure the references are set right
 */

#if (!defined(MU32_ERRORS_H) && !defined(PRECOMPILE)) \
	|| (!defined(MU32_ERRORS_H_PRECOMPILED))
#ifndef PRECOMPILE
#define MU32_ERRORS_H
#endif

// ---------------------------------------------------------------------------
// headers
// ---------------------------------------------------------------------------

#include "Defs.h"

#ifndef MU32_ERRORS_H_PRECOMPILED
#define MU32_ERRORS_H_PRECOMPILED

// system headers which do seldom change

extern const mutTranslationChar * Error_text[];

extern const mutTranslationChar * Warning_text[];

#define MUT_ERR_MALLOC_FAILED MUT_ERR_UNFINISHED_TRANSLATION

enum
{
        MUT_ERR_UNKNOWN=0,
        MUT_ERR_SYNTAX_ERROR,
        MUT_ERR_INVALID_CHAR,
        MUT_ERR_FILE_OPEN_FAILED,
        MUT_ERR_UNFINISHED_TRANSLATION, /* Memory exhausted or insufficient source file */
	MUT_ERROR_COUNT
};

/*
const char * Error_text[] =
  {

    / * 0 * / N_("Unknown error in %s , line %d !"), / * allgemeinster Fehler * /

    / * Datei- und Systemfehler * /
    / * 1 * / N_("Syntax error, not specified. (line %d)"),
    N_("Non-valid character: asc=%d (line %d)"),
    N_("Can't open file: %s"),
    N_("Not enough memory or too few data for mutabor in source file"),
    N_(" "),
    N_(" "),
    N_(" "),
    N_(" "),
    N_(" "),

    / * Doppeldeklarationen * /
    / * 10 * / N_("The interval name %s was used twice"),
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

    / * Undefinierte Symbole * /
    / * 25 * / N_("Undefined symbol: %s"),
    N_("Undefined interval: %s"),
    N_("Undefined tone: %s"),
    N_("Undefined tonesystem: %s"),
    N_("Undefined retuning: %s"),
    N_("Undefined pattern: %s (in logic %s)"),
    N_("Undefined parameter name: %s in %s"),
    N_("Undefined interval: %s (in %s)"),
    N_("Undefined tone: %s (in tone system %s)"),
    N_("Undefined tone: %s (in retuning %s)"),
    / * 35 * / N_("(to be reused)"),
    N_("Undefined retuning: %s (in retuning %s)"),
    N_("Undefined initial tuning: %s (in logic %s)"),
    N_("Undefined action: %s (in logic %s)"),
    N_("Undefined parameter: %s (in call %s from logic %s)"),
    N_(" "),
    N_(" "),
    N_(" "),
    N_(" "),
    N_(" "),

    / * Range violations * /
    / * 45 * /
    N_("Bad MIDI channel (valid: 1...16)"),
    N_("Bad interval value in %s"),
    N_("Bad key %d (valid: 36...96 (in tonesystem %s)"),
    N_("Not-complex tone in retuning %s ( %s )"),
    N_("Bad value in %s"), / * (allgemein) * /
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

    / * Parameterfehler * /
    / * 60 * / N_("In retuning %s and %s : Bad parameters"),
    N_("In logic %s : Bad number of parameters ( %s )"),
    N_("In logik %s : initial tuning %s mustn't have parameters"),
    N_("In collection %s : call to %s mustn't have parameters"),
    N_("In case %s : call to %s mustn't have parameters"),

    / * Dependencies * /
    / * 65 * / N_("Tones %s and %s are dependent"),
    N_("Retunings/logics %s and %s are dependent"),
    N_("Intervals %s and %s are dependent"),
    N_("MIDI-channels are dependent"),
    N_(" "),

    / * Syntaxfehler (vom BISON-Parser aufgerufen) * /
    / * 70 * / N_("Wrong character ! Expecting %s (line %d)"),
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

const char * Warning_text[] =
  {
    / *  0 * / N_("Undefined compiler warning"),
    N_("MIDI event in logic %s does not start with channel 0 status byte. Value corrected."),
    N_("Non existent harmony event in logic %s"),
    N_("Non well defined event %s in logic %s"),
    N_("Event ELSE is last in %s"),
    / *  5 * / N_("MIDI channels wasted in channel assotiation"),
    N_("No file given, trying test.mut"),
    N_("Invalid configuration file"),
    N_("Intersection of MIDI channels %d und %d"),
    N_("Error in GMN-File %s position(%d, %d): %s")
  };
*/
#endif //PRECOMPILED
#endif

///\}

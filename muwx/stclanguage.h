/** \file               -*- C++ -*-
 ********************************************************************
 * Language definitions for wxStyledTextControl (wxScintilla)
 *
 * $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/muwx/stclanguage.h,v 1.3 2011/09/27 20:13:24 keinstein Exp $
 * Copyright:   (c) 2011 TU Dresden
 * \author  Tobias Schlemmer <keinstein@users.berlios.de>
 * \date 
 * $Date: 2011/09/27 20:13:24 $
 * \version $Revision: 1.3 $
 * \license GPL
 *
 *    This program is free software; you can redistribute it and/or modify
 *    it under the terms of the GNU General Public License as published by
 *    the Free Software Foundation; either version 2 of the License, or
 *    (at your option) any later version.
 *
 *    This program is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License for more details.
 *
 *    You should have received a copy of the GNprU General Public License
 *    along with this program; if not, write to the Free Software
 *    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 *
 * $Log: stclanguage.h,v $
 * Revision 1.3  2011/09/27 20:13:24  keinstein
 * * Reworked route editing backend
 * * rewireing is done by RouteClass/GUIRoute now
 * * other classes forward most requests to this pair
 * * many bugfixes
 * * Version change: We are reaching beta phase now
 *
 * Revision 1.2  2011-08-21 16:52:05  keinstein
 * Integrate a more sophisticated editor menu based on the stc sample
 *
 * Revision 1.1  2011-08-20 18:15:36  keinstein
 * new files
 *
 *
 *
 ********************************************************************
 * \addtogroup muwx
 * \{
 ********************************************************************/
// availlable groups: GUI, route, kernel, muwx, debug, docview

#if (!defined(MUWX_STCLANGUAGE_H) && !defined(PRECOMPILE)) \
	|| (!defined(MUWX_STCLANGUAGE_H_PRECOMPILED))
#ifndef PRECOMPILE
#define MUWX_STCLANGUAGE_H
#endif

// ---------------------------------------------------------------------------
// headers
// ---------------------------------------------------------------------------

#include "Defs.h"

#ifndef MUWX_STCLANGUAGE_H_PRECOMPILED
#define MUWX_STCLANGUAGE_H_PRECOMPILED

// ---------------------------------------------------------------------------
// headers
// ---------------------------------------------------------------------------

//! wxWidgets/contrib headers
#include "wx/stc/stc.h"  // styled text control

//! application headers

namespace mutaborGUI {
//============================================================================
// declarations
//============================================================================

#define DEFAULT_LANGUAGE _("<default>")

#define PAGE_COMMON _("Common")
#define PAGE_LANGUAGES _("Languages")
#define PAGE_STYLE_TYPES _("Style types")

#define STYLE_TYPES_COUNT 32

//! general style types
#define MutSTC_TYPE_DEFAULT 0

#define MutSTC_TYPE_WORD1 1
#define MutSTC_TYPE_WORD2 2
#define MutSTC_TYPE_WORD3 3
#define MutSTC_TYPE_WORD4 4
#define MutSTC_TYPE_WORD5 5
#define MutSTC_TYPE_WORD6 6

#define MutSTC_TYPE_COMMENT 7
#define MutSTC_TYPE_COMMENT_DOC 8
#define MutSTC_TYPE_COMMENT_LINE 9
#define MutSTC_TYPE_COMMENT_SPECIAL 10

#define MutSTC_TYPE_CHARACTER 11
#define MutSTC_TYPE_CHARACTER_EOL 12
#define MutSTC_TYPE_STRING 13
#define MutSTC_TYPE_STRING_EOL 14

#define MutSTC_TYPE_DELIMITER 15

#define MutSTC_TYPE_PUNCTUATION 16

#define MutSTC_TYPE_OPERATOR 17

#define MutSTC_TYPE_BRACE 18

#define MutSTC_TYPE_COMMAND 19
#define MutSTC_TYPE_IDENTIFIER 20
#define MutSTC_TYPE_LABEL 21
#define MutSTC_TYPE_NUMBER 22
#define MutSTC_TYPE_PARAMETER 23
#define MutSTC_TYPE_REGEX 24
#define MutSTC_TYPE_UUID 25
#define MutSTC_TYPE_VALUE 26

#define MutSTC_TYPE_PREPROCESSOR 27
#define MutSTC_TYPE_SCRIPT 28

#define MutSTC_TYPE_ERROR 29

//----------------------------------------------------------------------------
//! style bits types
#define MutSTC_STYLE_BOLD 1
#define MutSTC_STYLE_ITALIC 2
#define MutSTC_STYLE_UNDERL 4
#define MutSTC_STYLE_HIDDEN 8

//----------------------------------------------------------------------------
//! general folding types
#define MutSTC_FOLD_COMMENT 1
#define MutSTC_FOLD_COMPACT 2
#define MutSTC_FOLD_PREPROC 4

#define MutSTC_FOLD_HTML 16
#define MutSTC_FOLD_HTMLPREP 32

#define MutSTC_FOLD_COMMENTPY 64
#define MutSTC_FOLD_QUOTESPY 128

//----------------------------------------------------------------------------
//! flags
#define MutSTC_FLAG_WRAPMODE 16

//----------------------------------------------------------------------------
//! Lexers
#define MutSTC_LEX_MUTABOR 900

//----------------------------------------------------------------------------
//! Lexer stats
#define MutSTC_MUTABOR_DEFAULT 0
#define MutSTC_MUTABOR_SECTION 1
#define MutSTC_MUTABOR_PARAMETER 2
#define MutSTC_MUTABOR_COMMENT 3
#define MutSTC_MUTABOR_IDENTIFIER 4
#define MutSTC_MUTABOR_DEFNAME 5
#define MutSTC_MUTABOR_OPERATOR 6
#define MutSTC_MUTABOR_PAREN 6
#define MutSTC_MUTABOR_BRACKET 7
#define MutSTC_MUTABOR_BRACE 8
#define MutSTC_MUTABOR_NUMBER 9

//----------------------------------------------------------------------------
// CommonInfo

	struct CommonInfo {
		// editor functionality prefs
		bool syntaxEnable;
		bool foldEnable;
		bool indentEnable;
		// display defaults prefs
		bool readOnlyInitial;
		bool overTypeInitial;
		bool wrapModeInitial;
		bool displayEOLEnable;
		bool indentGuideEnable;
		bool lineNumberEnable;
		bool longLineOnEnable;
		bool whiteSpaceEnable;
	};
	extern const CommonInfo g_CommonPrefs;

//----------------------------------------------------------------------------
// LanguageInfo

	struct LanguageInfo {
		const wxChar *name;
		const wxChar *filepattern;
		int lexer;
		struct {
			int type;
			const wxChar *words;
		} styles [STYLE_TYPES_COUNT];
		int folds;
	};

	extern const LanguageInfo g_LanguagePrefs[];
	extern const int g_LanguagePrefsSize;

//----------------------------------------------------------------------------
// StyleInfo
	struct StyleInfo {
		const wxChar *name;
		const wxChar *foreground;
		const wxChar *background;
		const wxChar *fontname;
		int fontsize;
		int fontstyle;
		int lettercase;
	};

	extern const StyleInfo g_StylePrefs[];
	extern const int g_StylePrefsSize;


}

#endif // precompiled
#endif // full header inclusion
///\}

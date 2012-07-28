/** \file               -*- C++ -*-
********************************************************************
* Test for file device timer
*
* $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/templates/template.cpp,v 1.5 2011/09/27 20:13:26 keinstein Exp $
* Copyright:   (c) 2012 TU Dresden
* \author  Tobias Schlemmer <keinstein@users.berlios.de>
* \date 
* $Date: 2011/09/27 20:13:26 $
* \version $Revision: 1.5 $
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
*    You should have received a copy of the GNU General Public License
*    along with this program; if not, write to the Free Software
*    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*
*
* $Log: template.cpp,v $
*
*
********************************************************************
* \addtogroup tests
* \{
********************************************************************/
// availlable groups: GUI, route, kernel, muwx, debug, docview


#include "src/kernel/Defs.h"



/// not for headers
#ifdef __BORLANDC__
#pragma hdrstop
#endif



// for all others, include the necessary headers (this file is usually all you
// need because it includes almost all "standard" wxWidgets headers)
#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include <wx/app.h>
#include <wx/cmdline.h>

// ============================================================================
// implementation
// ============================================================================

static const wxCmdLineEntryDesc cmdLineDesc[] =
{
	{ wxCMD_LINE_SWITCH, _T("h"), _T("help"), _T("show this help message"),
	  wxCMD_LINE_VAL_NONE, wxCMD_LINE_OPTION_HELP },
	{ wxCMD_LINE_SWITCH, _T("d"), _T("dummy"), _T("a dummy switch") },
// ... your other command line options here...

	{ wxCMD_LINE_NONE }
};

int main(int argc, char **argv)
{
	wxApp::CheckBuildOptions(WX_BUILD_OPTIONS_SIGNATURE, "program");

	wxInitializer initializer;
	if ( !initializer )
	{
		fprintf(stderr, "Failed to initialize the wxWidgets library, aborting.");
		return -1;
	}

	wxCmdLineParser parser(cmdLineDesc, argc, argv);
	switch ( parser.Parse() )
	{
	case -1:
		// help was given, terminating
		break;

	case 0:
		// everything is ok; proceed
		if (parser.Found(_T("d")))
		{
			wxPrintf(_T("Dummy switch was given...\n"));

			while (1)
			{
				wxChar input[128];
				wxPrintf(_T("Try to guess the magic number (type 'quit' to escape): "));
				if ( !wxFgets(input, WXSIZEOF(input), stdin) )
					break;

				// kill the last '\n'
				input[wxStrlen(input) - 1] = 0;

				if (wxStrcmp(input, _T("quit")) == 0)
					break;

				long val;
				if (!wxString(input).ToLong(&val))
				{
					wxPrintf(_T("Invalid number...\n"));
					continue;
				}

				if (val == 42)
					wxPrintf(_T("You guessed!\n"));
				else
					wxPrintf(_T("Bad luck!\n"));
			}
		}
		break;

	default:
		break;
	}

	if ( argc == 1 )
	{
		// If there were no command-line options supplied, emit a message
		// otherwise it's not obvious that the sample ran successfully
		wxPrintf(_T("Welcome to the wxWidgets 'console' sample!\n"));
		wxPrintf(_T("For more information, run it again with the --help option\n"));
	}

	// do something useful here

	return 0;
}
///\}

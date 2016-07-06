/** \file               -*- C++ -*-
 ********************************************************************
 * Description
 *
 * Copyright:   (c) 2012 Tobias Schlemmer
 * \author  Tobias Schlemmer <keinstein@users.sourceforge.net>
 * \date 
 * $Date: 2011/09/27 20:13:26 $
 * \version $Version$
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
 ********************************************************************
 * \addtogroup tests
 * \{
 ********************************************************************/
#ifndef __TESTS_GUIROUTETEST_H__
#define __TESTS_GUIROUTETEST_H__

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/portability/Stream.h>
#include "src/kernel/routing/Route.h"
#include "src/wxGUI/Mutabor.rh"
#include <iostream>
//#include "src/kernel/Runtime.h"

class MkIDlist : public CPPUNIT_NS::TestFixture 
{
	CPPUNIT_TEST_SUITE( MkIDlist );
	CPPUNIT_TEST( doMkIDlist );
	CPPUNIT_TEST_SUITE_END();

protected:
//	mutabor::Route route;

public:
	MkIDlist()
	{
	}

	virtual ~MkIDlist()
	{
	}

	int countTestCases () const
	{ 
		return 1; 
	}
  
	void setUp() {}
	void tearDown() {}


	void doMkIDlist() {
		std::ofstream stream("texidlist.tex");

#define printid(file,token)					      \
		file << "\\definewxid{" << #token << "}{" << token << "}" << std::endl
		printid(stream,CM_FILEOPEN);
		printid(stream,CM_FILECLOSE);
		printid(stream,CM_FILENEW);
		printid(stream,CM_FILESAVE);
		printid(stream,CM_FILESAVEAS);
		printid(stream,CM_FILEREVERT);
		printid(stream,CM_EXIT);

		printid(stream,CM_HELP);
		printid(stream,CM_HELPINDEX);
		printid(stream,CM_HELPSEARCH);
		printid(stream,CM_ABOUT);

#undef printid
#define printid(file,token)					      \
		file << "\\definewxid{" << #token << "}{" << mutaborGUI::token << "}" << std::endl
		printid(stream,MUT_FIRST);
		printid(stream,CM_EXECUTE);
		printid(stream,CM_SETUP);

		printid(stream,CM_COMPILE);
		printid(stream,CM_ACTIVATE);
		printid(stream,CM_STOP);
		printid(stream,CM_PANIC);

		printid(stream,CM_TOGGLEKEY);
		printid(stream,CM_TOGGLETS);
		printid(stream,CM_TOGGLEACT);
		printid(stream,CM_ROUTES);
		printid(stream,CM_OWM);
		printid(stream,CM_CAW);
		printid(stream,CM_SELECTBOX);

		printid(stream,CM_ROUTELOAD);
		printid(stream,CM_ROUTESAVE);
		printid(stream,CM_ROUTESAVEAS);

		printid(stream,CM_INDEVPLAY);
		printid(stream,CM_INDEVSTOP);
		printid(stream,CM_INDEVPAUSE);

		printid(stream,CM_HELPREFERENCE);
		printid(stream,CM_HELPHANDBOOK);
		printid(stream,CM_HELPONHELP);
		printid(stream,CM_HELPCOMMON);

		printid(stream,CM_BOX);

		printid(stream,CM_HELPCONTEXT);

		printid(stream,CM_COMPACT);
		printid(stream,CM_MUTTAG);
		printid(stream,CM_SBREFRESH);
		printid(stream,CM_GETLINE);
		printid(stream,CM_DOACTIVATE);
		printid(stream,CM_TASTE);
		printid(stream,CM_LEFT_DOUBLE_CLICK);
		printid(stream,CM_UPDATE);

		printid(stream,MDI_REFRESH);

		printid(stream,CM_UPDATEUI);
		printid(stream,CM_SETTITLE);
		printid(stream,CM_SELECT_BOXWINDOW);
		printid(stream,ID_CHOICE_DEVICE);
		
		printid(stream,CM_DELETE_CONTROL);
		printid(stream,cmCallExitId);

		printid(stream,CM_PROPERTIES);
		printid(stream,CM_INDENTINC);
		printid(stream,CM_INDENTRED);
		printid(stream,CM_FINDNEXT);
		printid(stream,CM_REPLACENEXT);
		printid(stream,CM_BRACEMATCH);
		printid(stream,CM_GOTO);
		printid(stream,CM_PAGEACTIVE);
		printid(stream,CM_DISPLAYEOL);
		printid(stream,CM_INDENTGUIDE);
		printid(stream,CM_LINENUMBER);
		printid(stream,CM_LONGLINEON);
		printid(stream,CM_WHITESPACE);
		printid(stream,CM_FOLDTOGGLE);
		printid(stream,CM_OVERTYPE);
		printid(stream,CM_READONLY);
		printid(stream,CM_WRAPMODEON);
		printid(stream,CM_CHANGECASE);
		printid(stream,CM_CHANGELOWER);
		printid(stream,CM_CHANGEUPPER);
		printid(stream,CM_HILIGHTLANG);
		printid(stream,CM_HILIGHTFIRST);
		printid(stream,CM_HILIGHTLAST);
		printid(stream,CM_CONVERTEOL);
		printid(stream,CM_CONVERTCR);
		printid(stream,CM_CONVERTCRLF);
		printid(stream,CM_CONVERTLF);
		printid(stream,CM_USECHARSET);
		printid(stream,CM_CHARSETANSI);
		printid(stream,CM_CHARSETMAC);
		printid(stream,CM_CHARSETUTF8);
		printid(stream,CM_PAGEPREV);
		printid(stream,CM_PAGENEXT);
		printid(stream,CM_SELECTLINE);
		printid(stream,CM_MOVE_UP);
		printid(stream,CM_MOVE_DOWN);

		// other IDs
		printid(stream,CM_STATUSBAR);
		printid(stream,CM_TITLEBAR);
		printid(stream,CM_ABOUTTIMER);
		printid(stream,CM_UPDATETIMER);

		// dialog find IDs
		printid(stream,CM_DLG_FIND_TEXT);

		// preferences IDs
		printid(stream,CM_PREFS_LANGUAGE);
		printid(stream,CM_PREFS_STYLETYPE);
		printid(stream,CM_PREFS_KEYWORDS);

		// last id 
		printid(stream,MUT_LAST);

		stream.close();
		mutASSERT(mutaborGUI::CM_PREFS_KEYWORDS == mutaborGUI::MUT_LAST - 1);
	}
};

#endif

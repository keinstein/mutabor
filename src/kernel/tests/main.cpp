/** \file
 ********************************************************************
 * cppunit main program
 *
 * Copyright:   (c) 2011 TU Dresden
 * \author Tobias Schlemmer <keinstein@users.sourceforge.net>
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
 * \defgroup tests Test suite
 * This group contains the test suite.
 * \{
 ********************************************************************/
#include "src/kernel/tests/boxTest.h"
#include "src/wxGUI/TestInitializer.h"
#include <iostream>
#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/TestResult.h>
#include <cppunit/BriefTestProgressListener.h>

// Skip the GUI related checks from DebugRoute.cpp
#if 1
#define no_wxGUI 1
#include "src/wxGUI/Routing/DebugRoute.cpp"
#undef no_wxGUI
#endif

int 
main(int argc, char** argv)
{
	mutwxInitializer initializer;
//	mutabor::InitDeviceFactories();

#ifdef _GLIBCXX_DEBUG
	std::clog << "In case of segmentation faults assure that cppunit is compiled using -D_GLIBCXX_DEBUG" << std::endl;
#endif

	CPPUNIT_NS::TextUi::TestRunner runner;
	
	CppUnit::BriefTestProgressListener listener; 
	runner.eventManager().addListener(&listener);

	runner.addTest( boxTest::suite() );
	
	bool wasSuccessful = runner.run();

	return wasSuccessful ? 0 : 1;
}

/// }

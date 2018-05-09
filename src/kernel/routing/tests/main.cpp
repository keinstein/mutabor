/** \file               -*- C++ -*-
 ********************************************************************
 * Description
 *
 * Copyright:   (c) 2012 Tobias Schlemmer
 * \author  Tobias Schlemmer <keinstein@users.sourceforge.net>
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
#include "src/kernel/Defs.h"
#include "src/kernel/routing/tests/CommonFileDeviceTest.h"
#include "src/kernel/routing/tests/RouteTest.h"
#include "src/kernel/routing/tests/BoxTest.h"
#include "src/kernel/routing/tests/timing.h"
#include "src/kernel/routing/Route-inlines.h"
#include "src/wxGUI/TestInitializer.h"
#include <iostream>
#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/TestResult.h>
#include <cppunit/BriefTestProgressListener.h>

// Skip the GUI related checks from DebugRoute.cpp
#define no_wxGUI 1
#include "src/wxGUI/Routing/DebugRoute.cpp"
#undef no_wxGUI


int 
main()
{
	//	mutwxInitializer initializer;

	mutabor::InitDeviceFactories();

#ifdef _GLIBCXX_DEBUG
	std::clog << "In case of segmentation faults assure that cppunit is compiled using -D_GLIBCXX_DEBUG" << std::endl;
#endif

	CPPUNIT_NS::TextUi::TestRunner runner;
	
	CppUnit::BriefTestProgressListener listener; 
	runner.eventManager().addListener(&listener);

	runner.addTest( TimingParamsTest::suite() );
	runner.addTest( BoxTest::suite() );
	runner.addTest( RouteTest::suite() );
	runner.addTest( CommonFileDeviceTest::suite() );
	
	bool wasSuccessful = runner.run();
#ifdef DEBUG
	std::clog << "Sucess: " << (wasSuccessful ? "Yes" : "No") << std::endl << std::flush;
#endif
	//CurrentTime.Sleep(1000);
	return wasSuccessful ? 0 : 1;
}


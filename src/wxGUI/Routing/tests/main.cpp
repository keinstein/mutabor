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
#include "src/wxGUI/Routing/tests/GUIRouteTest.h"
#include "src/wxGUI/Routing/RouteIcons.h"
#include "src/wxGUI/Routing/GUIRoute.h"
#include "src/kernel/routing/Route-inlines.h"
#include "src/wxGUI/TestInitializer.h"
#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/TestResult.h>
#include <cppunit/BriefTestProgressListener.h>

// Skip the GUI related checks from DebugRoute.cpp
//#define no_wxGUI 1
#include "src/wxGUI/Routing/DebugRoute.cpp"
//#undef no_wxGUI

extern "C"
const char * __lsan_default_suppressions();

int
main()
{
	std::cerr << "Using the following suppressions" << std::endl;
	std::cerr << __lsan_default_suppressions() << std::endl;
	std::cerr << "--------------------------------" << std::endl;

	mutwxInitializer initializer;

	// We are using .png files for some extra bitmaps.
	wxImageHandler * pnghandler = new wxPNGHandler;
	wxImage::AddHandler(pnghandler);
	wxImage::AddHandler(new wxGIFHandler);

	mutaborGUI::initMutIconShapes();
	try {
		mutaborGUI::InitGUIRouteFactories();
	} catch (const mutabor::RouteFactory::FactoryAlreadySet & e) {
		std::cerr << boost::current_exception_diagnostic_information();
		return 1;
	}




#ifdef _GLIBCXX_DEBUG
	std::clog << "In case of segmentation faults assure that cppunit is compiled using -D_GLIBCXX_DEBUG" << std::endl;
#endif

	CPPUNIT_NS::TextUi::TestRunner runner;

	CppUnit::BriefTestProgressListener listener;
	runner.eventManager().addListener(&listener);

	runner.addTest( GUIRouteTest::suite() );

	bool wasSuccessful = runner.run();

	return wasSuccessful ? 0 : 1;
}

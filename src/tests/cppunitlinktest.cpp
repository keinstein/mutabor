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
 * \addgroup tests Test suite
 * This group contains the test suite.
 * \{
 ********************************************************************/
#include <iostream>
#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/TestResult.h>
#include <cppunit/BriefTestProgressListener.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/portability/Stream.h>


class dummyTest : public CPPUNIT_NS::TestFixture 
{
	CPPUNIT_TEST_SUITE( dummyTest );
	CPPUNIT_TEST( hello );
	CPPUNIT_TEST_SUITE_END();

public:
	dummyTest() {}

	virtual ~dummyTest() {}

	int countTestCases () const
	{ 
		return 1; 
	}
  
	void setUp() {}
	void tearDown() {}


	void hello() {
		std::cout << "cppunitliktest is running." << std::endl;
	}

};


int 
main()
{
	/*
	wxApp::CheckBuildOptions(WX_BUILD_OPTIONS_SIGNATURE, "program");
	
	wxInitializer initializer;
	if ( !initializer )
	{
		fprintf(stderr, "Failed to initialize the wxWidgets library, aborting.");
		return -1;
	}
//	mutabor::InitDeviceFactories();
*/

#ifdef _GLIBCXX_DEBUG
	std::clog << "In case of segmentation faults assure that cppunit is compiled using -D_GLIBCXX_DEBUG" << std::endl;
#endif

	CPPUNIT_NS::TextUi::TestRunner runner;
	
	CppUnit::BriefTestProgressListener listener; 
	runner.eventManager().addListener(&listener);

	runner.addTest( dummyTest::suite() );
	
	bool wasSuccessful = runner.run();

	return wasSuccessful ? 0 : 1;
}

/// }

#include <iostream>

#include "src/kernel/routing/midi/tests/DevMidFTest.h"
#include "src/kernel/routing/midi/tests/midicmnTest.h"
#include "src/wxGUI/TestInitializer.h"
#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/TestResult.h>
#include <cppunit/BriefTestProgressListener.h>

// Skip the GUI related checks from DebugRoute.cpp
#define no_wxGUI 1
#include "src/wxGUI/Routing/DebugRoute.cpp"
#undef no_wxGUI

int 
main(int argc, char** argv)
{
	mutwxInitializer initializer;
	mutabor::InitDeviceFactories();

#ifdef _GLIBCXX_DEBUG
	std::clog << "In case of segmentation faults assure that cppuinit is compiled using -D_GLIBCXX_DEBUG" << std::endl;
#endif

	CPPUNIT_NS::TextUi::TestRunner runner;
	
	CppUnit::BriefTestProgressListener listener; 
	runner.eventManager().addListener(&listener);

	runner.addTest( CommonMidiOutputTest::suite() );

	/// Input tests use the output device for logging
	runner.addTest( CommonMidiInputTest::suite() );
	runner.addTest( InputMidiFileTest::suite() );
	// Output file tests use input devices
	runner.addTest( OutputMidiFileTest::suite() );
	
	bool wasSuccessful = runner.run();

	return wasSuccessful ? 0 : 1;
}

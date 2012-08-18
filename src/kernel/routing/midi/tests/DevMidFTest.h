#ifndef __DEVMIDFTEST_H__
#define __DEVMIDFTEST_H__

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/portability/Stream.h>
#include "src/kernel/routing/midi/DevMidF.h"
#include "src/kernel/Runtime.h"

template<class input> 
class InputMidiFileTest : public CPPUNIT_NS::TestFixture 
{
	CPPUNIT_TEST_SUITE( InputMidiFileTest );
	CPPUNIT_TEST( testOpenFail );
	CPPUNIT_TEST( testPlayMidi );
	CPPUNIT_TEST_SUITE_END();

protected:
	mutabor::InputDevice in;

public:
	InputMidiFileTest()
	{
	}

	virtual ~InputMidiFileTest()
	{
	}

	int countTestCases () const
	{ 
		return 1; 
	}
  
	void setUp() 
	{ 
// change DEBUGA to DEBUG in case you need the debug output
#ifdef DEBUGA
		debugFlags::flags.timer = true;
		debugFlags::flags.midifile = true;
#endif
		std::clog << "Running setUp()" << std::endl;
		RealTime = true;
		in = mutabor::DeviceFactory::CreateInput(mutabor::DTMidiFile);
	}
  
	void tearDown()
	{ 
#ifdef DEBUG
		debugFlags::flags.timer = false;
		debugFlags::flags.midifile = false;
#endif
		in = NULL;
	}
  
	void testOpenFail() 
	{ 	  
		CPPUNIT_ASSERT( in );
		in -> SetName(_T("+-*”„“"));
		CPPUNIT_ASSERT(!(in -> Open()));
	}

	void testPlayMidi() 
	{ 
		CPPUNIT_ASSERT( in );
		in -> SetName(_T("playmidi1.mid"));
		CPPUNIT_ASSERT((in -> Open()));
	
		in -> Play(wxTHREAD_JOINABLE);
		CPPUNIT_ASSERT(!in->WaitForDeviceFinish());
	}
};

#endif

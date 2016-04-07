/** \file               -*- C++ -*-
 ********************************************************************
 * Test midi file functions
 *
 * Copyright:   (c) 2012 Tobias Schlemmer
 * \author  Tobias Schlemmer <keinstein@users.berlios.de>
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
 * \addtogroup route
 * \{
 ********************************************************************/

/* we guard a little bit complicated to ensure the references are set right
 */

#if (!defined(DEVFMIDFTEST_H) && !defined(PRECOMPILE)) \
	|| (!defined(DEVFMIDFTEST_H_PRECOMPILED))
#ifndef PRECOMPILE
#define DEVFMIDFTEST_H
#endif

#include "src/kernel/Defs.h"


#ifndef DEVFMIDFTEST_H_PRECOMPILED
#define DEVFMIDFTEST_H_PRECOMPILED

// system headers which do seldom change

/// not for headers
#ifdef __BORLANDC__
    #pragma hdrstop
#endif


// ---------------------------------------------------------------------------
// headers
// ---------------------------------------------------------------------------


#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/portability/Stream.h>
#include "src/kernel/routing/midi/DevMidF.h"
#include "src/kernel/Runtime.h"

class InputMidiFileTest : public CPPUNIT_NS::TestFixture 
{
	CPPUNIT_TEST_SUITE( InputMidiFileTest );
	CPPUNIT_TEST( testOpenFail );
	CPPUNIT_TEST( testPlayMidi );
	CPPUNIT_TEST( testBatchPlay1 );
	CPPUNIT_TEST( testBug019010_2 );
	CPPUNIT_TEST( testBug019010 );
	CPPUNIT_TEST( testBankSelect );
	CPPUNIT_TEST( testAllControllerOff );
	CPPUNIT_TEST( testRpnNrpn );
	CPPUNIT_TEST( testControllerPlay );
	CPPUNIT_TEST( testBoxMidiIn );
	CPPUNIT_TEST( testAfterTouch );
	CPPUNIT_TEST( testSysEx );


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
#ifdef DEBUG
//		debugFlags::flags.timer = true;
//		debugFlags::flags.midifile = true;
//		isDebugFlag(smartptr) = true;
#endif
		mutabor_backtrace::set_global_print();
		CPPUNIT_ASSERT(mutabor::InputDeviceClass::GetDeviceList().empty());
		CPPUNIT_ASSERT(mutabor::OutputDeviceClass::GetDeviceList().empty());
		CPPUNIT_ASSERT(mutabor::RouteClass::GetRouteList().empty());
		CPPUNIT_ASSERT(mutabor::BoxClass::GetBoxList().empty());
		mutabor::CurrentTime.UseRealtime(true);
		in = mutabor::DeviceFactory::CreateInput(mutabor::DTMidiFile);
		CPPUNIT_ASSERT(in);
	}
  
	void tearDown()
	{ 
		if (in) {
			in -> Destroy();
			std::cout << std::endl << "Refcount : " << intrusive_ptr_get_refcount(in.get()) << std::endl;
		}
		in.reset();
		CPPUNIT_ASSERT(mutabor::InputDeviceClass::GetDeviceList().empty());
		CPPUNIT_ASSERT(mutabor::OutputDeviceClass::GetDeviceList().empty());
		CPPUNIT_ASSERT(mutabor::RouteClass::GetRouteList().empty());
#ifdef DEBUG
		isDebugFlag(timer) = false;
		isDebugFlag(midifile) = false;
		isDebugFlag(smartptr) = false;
#endif
	}
  
	void testOpenFail() 
	{ 	  
		CPPUNIT_ASSERT( in );
		in -> SetName(("+-*”„“"));
		CPPUNIT_ASSERT(!(in -> Open()));
	}

	void testPlayMidi() 
	{ 
		CPPUNIT_ASSERT( in );
		in -> SetName(SRCDIR "/midi1_source.mid");
		CPPUNIT_ASSERT((in -> Open()));
	
		in -> Play();
		CPPUNIT_ASSERT(!in->WaitForDeviceFinish());
	}

	void testBatchPlay1();
	void testBug019010_2();
	void testBug019010();
	void testBankSelect();
	void testAllControllerOff();
	void testRpnNrpn();
	void testControllerPlay();
	void testBoxMidiIn();
	void testAfterTouch();
	void testSysEx();

#if __WXMSW__
protected:
	void usleep(int waitTime) {
		__int64 time1 = 0, time2 = 0, freq = 0;

		QueryPerformanceCounter((LARGE_INTEGER *) &time1);
		QueryPerformanceFrequency((LARGE_INTEGER *)&freq);
		
		do {
			QueryPerformanceCounter((LARGE_INTEGER *) &time2);
		} while((time2-time1) < waitTime);
	}	

	void sleep(int waitTime) {
		usleep(waitTime * 1000);
	}
#endif
};


/*
class  midicmnOutputDevice:public mutabor::CommonMidiOutput<mutabor::DebugMidiOutputProvider,mutabor::OutputDeviceClass> {
public:
	typedef mutabor::CommonMidiOutput<mutabor::DebugMidiOutputProvider,mutabor::OutputDeviceClass> base;

	midicmnOutputDevice(int devId, 
			    wxString name, 
			    int id = -1, 
			    int bendingRange = 2):base(devId,name,id,bendingRange) {}
	~midicmnOutputDevice() {}
	mutabor::DebugMidiOutputProvider & getOut() { return Out; }

// fix pure virtual functions:
	void Save(tree_storage&) {}
	void Save(tree_storage&, const mutabor::RouteClass*) {}
	void Load(tree_storage&) {}
	void Load(tree_storage&, mutabor::RouteClass*) {}
	void AddTime(frac) {}
	int GetMaxChannel() const { return 15; }
	int GetMinChannel() const { return 0; }
	bool Check(std::string s) {
		bool retval = (s == (std::string)Out);
		Out.ClearData();
		return retval;
	}
};
*/

class OutputMidiFileTest : public CPPUNIT_NS::TestFixture 
{
	CPPUNIT_TEST_SUITE( OutputMidiFileTest );
	CPPUNIT_TEST( testNoteOnOff );
	CPPUNIT_TEST( testBatchPlay1 );
	CPPUNIT_TEST_SUITE_END();

public:

	OutputMidiFileTest()
	{
	}

	virtual ~OutputMidiFileTest()
	{
	}

	int countTestCases () const
	{ 
		abort();
		return 1; 
	}
  
	void setUp();
	void tearDown();

	bool CheckOut(std::string s, int line, const char * file);

	void testNoteOnOff();
	void testBatchPlay1();

protected:
	mutabor::OutputDevice guard;
	mutabor::OutputMidiFile * out;
	mutabor::Route  route;
       	mutabor::Box box;
	mutabor::ChannelData cd;
#if __WXMSW__
	void usleep(int waitTime) {
		__int64 time1 = 0, time2 = 0, freq = 0;

		QueryPerformanceCounter((LARGE_INTEGER *) &time1);
		QueryPerformanceFrequency((LARGE_INTEGER *)&freq);
		
		do {
			QueryPerformanceCounter((LARGE_INTEGER *) &time2);
		} while((time2-time1) < waitTime);
	}	

	void sleep(int waitTime) {
		usleep(waitTime * 1000);
	}
#endif
};

#endif // precompiled
#endif // header loaded
///\}


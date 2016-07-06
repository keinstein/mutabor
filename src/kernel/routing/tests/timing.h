/** \file               -*- C++ -*-
********************************************************************
* Test for file device timer
*
* $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/templates/template.cpp,v 1.5 2011/09/27 20:13:26 keinstein Exp $
* Copyright:   (c) 2012 TU Dresden
* \author  Tobias Schlemmer <keinstein@users.sourceforge.net>
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
#include "src/kernel/routing/timing.h"
#include <cstdlib>


class TimingParamsTest : public CPPUNIT_NS::TestFixture {
	CPPUNIT_TEST_SUITE( TimingParamsTest );
	CPPUNIT_TEST( testMIDITicks );
	CPPUNIT_TEST( testExactTicks );
	CPPUNIT_TEST_SUITE_END();
	
public:
	TimingParamsTest()
	{
	}

	virtual ~TimingParamsTest()
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
                // debugFlags::flags.timer = true;
		// debugFlags::flags.midifile = true;
#endif
	}

	void tearDown()
		{
		}

#if __WXMSW__
	void usleep(int waitTime) {
		__int64 time1 = 0, time2 = 0, freq = 0;

		QueryPerformanceCounter((LARGE_INTEGER *) &time1);
		QueryPerformanceFrequency((LARGE_INTEGER *)&freq);
		
		do {
			QueryPerformanceCounter((LARGE_INTEGER *) &time2);
		} while((time2-time1) < waitTime);
	}	
#endif
	
	void testMIDITicks() {
		std::pair <uint8_t,uint8_t> params;
		mutabor::timing_params timing;
		CPPUNIT_ASSERT(timing.get_ticks() == 1000);
		CPPUNIT_ASSERT(timing.get_quarter_duration() == 500*1000);
		params = timing.get_MIDI_tick_signature();
		CPPUNIT_ASSERT(params.first == 0xe7); // -25
		CPPUNIT_ASSERT(params.second == 40);
		CPPUNIT_ASSERT(timing.get_time_midi(1) == 1000);
		CPPUNIT_ASSERT(timing.get_delta_midi(1000) == 1);
		// check correct rounding for microseconds
		CPPUNIT_ASSERT(timing.get_delta_midi(499) == 0);
		CPPUNIT_ASSERT(timing.get_delta_midi(500) == 1);
		CPPUNIT_ASSERT(timing.get_delta_midi(1499) == 1);
		CPPUNIT_ASSERT(timing.get_delta_midi(1500) == 2);
		CPPUNIT_ASSERT(timing.get_delta_midi(2499) == 2);
		CPPUNIT_ASSERT(timing.get_delta_midi(2500) == 3);

		timing.set_MIDI_tick_signature(1,224);
		CPPUNIT_ASSERT(timing.get_ticks() == 480);
		CPPUNIT_ASSERT(timing.get_time_midi(1) == 1041);
		CPPUNIT_ASSERT(timing.get_delta_midi(960) == 1);
		CPPUNIT_ASSERT(timing.get_delta_midi(1399) == 1);
		CPPUNIT_ASSERT(timing.get_delta_midi(2400) == 2);
		params = timing.get_MIDI_tick_signature();
		CPPUNIT_ASSERT(params.first == 1);
		CPPUNIT_ASSERT(params.second == 224);

		timing.set_MIDI_tick_signature(0xe2,120);
		CPPUNIT_ASSERT(timing.get_ticks() == 3600);
		CPPUNIT_ASSERT(timing.get_time_midi(1) == 277);
		CPPUNIT_ASSERT(timing.get_delta_midi(555) == 2);
		CPPUNIT_ASSERT(timing.get_delta_midi(691) == 2);
		CPPUNIT_ASSERT(timing.get_delta_midi(692) == 3);
		CPPUNIT_ASSERT(timing.get_delta_midi(693) == 3);
		CPPUNIT_ASSERT(timing.get_delta_midi(694) == 3);
		CPPUNIT_ASSERT(timing.get_delta_midi(695) == 3);
		params = timing.get_MIDI_tick_signature();
		CPPUNIT_ASSERT(params.first == 0xe2);
		CPPUNIT_ASSERT(params.second == 120);
			       
		timing.set_MIDI_tick_signature(0xe8,100);
		CPPUNIT_ASSERT(timing.get_ticks() == 2400);
		CPPUNIT_ASSERT(timing.get_time_midi(1) == 416);
		CPPUNIT_ASSERT(timing.get_delta_midi(833) == 2);
		CPPUNIT_ASSERT(timing.get_delta_midi(1039) == 2);
		CPPUNIT_ASSERT(timing.get_delta_midi(1040) == 3);
		params = timing.get_MIDI_tick_signature();
		CPPUNIT_ASSERT(params.first == 0xe8);
		CPPUNIT_ASSERT(params.second == 100);

		// 29 is handled like 30
		timing.set_MIDI_tick_signature(0xe3,120);
		CPPUNIT_ASSERT(timing.get_ticks() == 3600);
		CPPUNIT_ASSERT(timing.get_time_midi(1) == 277);
		CPPUNIT_ASSERT(timing.get_delta_midi(555) == 2);
		CPPUNIT_ASSERT(timing.get_delta_midi(691) == 2);
		CPPUNIT_ASSERT(timing.get_delta_midi(692) == 3);
		params = timing.get_MIDI_tick_signature();
		CPPUNIT_ASSERT(params.first == 0xe2);
		CPPUNIT_ASSERT(params.second == 120);
			       
		timing.set_MIDI_tick_signature(0xe7,40);
		CPPUNIT_ASSERT(timing.get_ticks() == 1000);
		CPPUNIT_ASSERT(timing.get_quarter_duration() == 500*1000);
		params = timing.get_MIDI_tick_signature();
		CPPUNIT_ASSERT(params.first == 0xe7); // -25
		CPPUNIT_ASSERT(params.second == 40);
		CPPUNIT_ASSERT(timing.get_time_midi(1) == 1000);
		CPPUNIT_ASSERT(timing.get_delta_midi(1000) == 1);
		CPPUNIT_ASSERT(timing.get_delta_midi(4769600) == 4770);
		CPPUNIT_ASSERT(timing.get_delta_midi(3222960) == 3223);
		CPPUNIT_ASSERT(timing.get_delta_midi(148080) == 148);
		CPPUNIT_ASSERT(timing.get_delta_midi(14725074) == 14725);

	}
	void testExactTicks() {
		std::pair <uint8_t,uint8_t> params;
		mutabor::timing_params timing;
		CPPUNIT_ASSERT(timing.get_ticks() == 1000);
		CPPUNIT_ASSERT(timing.get_quarter_duration() == 500*1000);
		params = timing.get_MIDI_tick_signature();
		CPPUNIT_ASSERT(params.first == 0xe7); // -25
		CPPUNIT_ASSERT(params.second == 40);
		CPPUNIT_ASSERT(timing.get_time_exact(1) == 1000);
		CPPUNIT_ASSERT(timing.get_delta_exact(1000) == 1);

		timing.set_MIDI_tick_signature(1,224);
		CPPUNIT_ASSERT(timing.get_ticks() == 480);
		CPPUNIT_ASSERT(timing.get_time_exact(1) == 1042);
		CPPUNIT_ASSERT(timing.get_delta_exact(960) == 1);
		CPPUNIT_ASSERT(timing.get_delta_exact(1399) == 1);
		CPPUNIT_ASSERT(timing.get_delta_exact(2400) == 2);
		params = timing.get_MIDI_tick_signature();
		CPPUNIT_ASSERT(params.first == 1);
		CPPUNIT_ASSERT(params.second == 224);

		timing.set_MIDI_tick_signature(0xe2,120);
		std::cerr << "get = " << timing.get_ticks() << std::endl;
		CPPUNIT_ASSERT(timing.get_ticks() == 3600);
		CPPUNIT_ASSERT(timing.get_time_exact(1) == 278);
		CPPUNIT_ASSERT(timing.get_delta_exact(555) == 2);
		CPPUNIT_ASSERT(timing.get_delta_exact(694) == 2);
		CPPUNIT_ASSERT(timing.get_delta_exact(695) == 3);
		params = timing.get_MIDI_tick_signature();
		CPPUNIT_ASSERT(params.first == 0xe2);
		CPPUNIT_ASSERT(params.second == 120);
			       
		timing.set_MIDI_tick_signature(0xe8,100);
		CPPUNIT_ASSERT(timing.get_ticks() == 2400);
		CPPUNIT_ASSERT(timing.get_time_exact(1) == 417);
		CPPUNIT_ASSERT(timing.get_delta_exact(833) == 2);
		CPPUNIT_ASSERT(timing.get_delta_exact(1041) == 2);
		CPPUNIT_ASSERT(timing.get_delta_exact(1042) == 3);
		params = timing.get_MIDI_tick_signature();
		CPPUNIT_ASSERT(params.first == 0xe8);
		CPPUNIT_ASSERT(params.second == 100);

		// 29 is handled like 30
		timing.set_MIDI_tick_signature(0xe3,120);
		CPPUNIT_ASSERT(timing.get_ticks() == 3600);
		CPPUNIT_ASSERT(timing.get_time_exact(1) == 278);
		CPPUNIT_ASSERT(timing.get_delta_exact(555) == 2);
		CPPUNIT_ASSERT(timing.get_delta_exact(694) == 2);
		CPPUNIT_ASSERT(timing.get_delta_exact(695) == 3);
		params = timing.get_MIDI_tick_signature();
		CPPUNIT_ASSERT(params.first == 0xe2);
		CPPUNIT_ASSERT(params.second == 120);
			       
		timing.set_MIDI_tick_signature(0xe7,40);
		CPPUNIT_ASSERT(timing.get_ticks() == 1000);
		CPPUNIT_ASSERT(timing.get_quarter_duration() == 500*1000);
		params = timing.get_MIDI_tick_signature();
		CPPUNIT_ASSERT(params.first == 0xe7); // -25
		CPPUNIT_ASSERT(params.second == 40);
		CPPUNIT_ASSERT(timing.get_time_exact(1) == 1000);
		CPPUNIT_ASSERT(timing.get_delta_exact(1000) == 1);

	}
	
};
///\}

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
	typedef boost::chrono::milliseconds milliseconds;
	typedef boost::chrono::high_resolution_clock clocktype;
	typedef clocktype::time_point     time_point;
	typedef mutabor::timing_params::miditicks miditicks;
	typedef mutabor::microseconds microseconds;

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
		CPPUNIT_ASSERT(timing.get_quarter_duration() == milliseconds(500));
		params = timing.get_MIDI_tick_signature();
		CPPUNIT_ASSERT(params.first == 0xe7); // -25
		CPPUNIT_ASSERT(params.second == 40);
		CPPUNIT_ASSERT(miditicks(1,timing).midi_mus() == milliseconds(1));
		CPPUNIT_ASSERT(miditicks(microseconds(1000),timing,true).count() == 1);
		// check correct rounding for microseconds
		CPPUNIT_ASSERT(miditicks(microseconds(499),timing,true).count() == 0);
		CPPUNIT_ASSERT(miditicks(microseconds(500),timing,true).count() == 1);
		CPPUNIT_ASSERT(miditicks(microseconds(1499),timing,true).count() == 1);
		CPPUNIT_ASSERT(miditicks(microseconds(1500),timing,true).count() == 2);
		CPPUNIT_ASSERT(miditicks(microseconds(2499),timing,true).count() == 2);
		CPPUNIT_ASSERT(miditicks(microseconds(2500),timing,true).count() == 3);

		timing.set_MIDI_tick_signature(1,224);
		CPPUNIT_ASSERT(timing.get_ticks() == 480);
		CPPUNIT_ASSERT(miditicks(1,timing).midi_mus() == microseconds(1041));
		CPPUNIT_ASSERT(miditicks(microseconds(960),timing,true).count() == 1);
		CPPUNIT_ASSERT(miditicks(microseconds(1399),timing,true).count() == 1);
		CPPUNIT_ASSERT(miditicks(microseconds(2400),timing,true).count() == 2);
		params = timing.get_MIDI_tick_signature();
		CPPUNIT_ASSERT(params.first == 1);
		CPPUNIT_ASSERT(params.second == 224);

		timing.set_MIDI_tick_signature(0xe2,120);
		CPPUNIT_ASSERT(timing.get_ticks() == 3600);
		CPPUNIT_ASSERT(miditicks(1,timing).midi_mus() == microseconds(277));
		CPPUNIT_ASSERT(miditicks(microseconds(555),timing,true).count() == 2);
		CPPUNIT_ASSERT(miditicks(microseconds(691),timing,true).count() == 2);
		CPPUNIT_ASSERT(miditicks(microseconds(692),timing,true).count() == 3);
		CPPUNIT_ASSERT(miditicks(microseconds(693),timing,true).count() == 3);
		CPPUNIT_ASSERT(miditicks(microseconds(694),timing,true).count() == 3);
		CPPUNIT_ASSERT(miditicks(microseconds(695),timing,true).count() == 3);
		params = timing.get_MIDI_tick_signature();
		CPPUNIT_ASSERT(params.first == 0xe2);
		CPPUNIT_ASSERT(params.second == 120);

		timing.set_MIDI_tick_signature(0xe8,100);
		CPPUNIT_ASSERT(timing.get_ticks() == 2400);
		CPPUNIT_ASSERT(miditicks(1,timing).midi_mus() == microseconds(416));
		CPPUNIT_ASSERT(miditicks(microseconds(833),timing,true).count() == 2);
		CPPUNIT_ASSERT(miditicks(microseconds(1039),timing,true).count() == 2);
		CPPUNIT_ASSERT(miditicks(microseconds(1040),timing,true).count() == 3);
		params = timing.get_MIDI_tick_signature();
		CPPUNIT_ASSERT(params.first == 0xe8);
		CPPUNIT_ASSERT(params.second == 100);

		// 29 is handled like 30
		timing.set_MIDI_tick_signature(0xe3,120);
		CPPUNIT_ASSERT(timing.get_ticks() == 3600);
		CPPUNIT_ASSERT(miditicks(1,timing).midi_mus() == microseconds(277));
		CPPUNIT_ASSERT(miditicks(microseconds(555),timing,true).count() == 2);
		CPPUNIT_ASSERT(miditicks(microseconds(691),timing,true).count() == 2);
		CPPUNIT_ASSERT(miditicks(microseconds(692),timing,true).count() == 3);
		params = timing.get_MIDI_tick_signature();
		CPPUNIT_ASSERT(params.first == 0xe2);
		CPPUNIT_ASSERT(params.second == 120);

		timing.set_MIDI_tick_signature(0xe7,40);
		CPPUNIT_ASSERT(timing.get_ticks() == 1000);
		CPPUNIT_ASSERT(timing.get_quarter_duration() == milliseconds(500));
		params = timing.get_MIDI_tick_signature();
		CPPUNIT_ASSERT(params.first == 0xe7); // -25
		CPPUNIT_ASSERT(params.second == 40);
		CPPUNIT_ASSERT(miditicks(1,timing).midi_mus() == microseconds(1000));
		CPPUNIT_ASSERT(miditicks(microseconds(1000),timing,true).count() == 1);
		CPPUNIT_ASSERT(miditicks(microseconds(4769600),timing,true).count() == 4770);
		CPPUNIT_ASSERT(miditicks(microseconds(3222960),timing,true).count() == 3223);
		CPPUNIT_ASSERT(miditicks(microseconds(148080),timing,true).count() == 148);
		CPPUNIT_ASSERT(miditicks(microseconds(14725074),timing,true).count() == 14725);

	}
	void testExactTicks() {
		std::pair <uint8_t,uint8_t> params;
		mutabor::timing_params timing;
		CPPUNIT_ASSERT(timing.get_ticks() == 1000);
		CPPUNIT_ASSERT(timing.get_quarter_duration() == milliseconds(500));
		params = timing.get_MIDI_tick_signature();
		CPPUNIT_ASSERT(params.first == 0xe7); // -25
		CPPUNIT_ASSERT(params.second == 40);
		CPPUNIT_ASSERT(miditicks(1,timing).mus() == milliseconds(1));
		CPPUNIT_ASSERT(miditicks(microseconds(1000),timing,false).count() == 1);

		timing.set_MIDI_tick_signature(1,224);
		CPPUNIT_ASSERT(timing.get_ticks() == 480);
		CPPUNIT_ASSERT(miditicks(1,timing).mus() == microseconds(1042));
		CPPUNIT_ASSERT(miditicks(microseconds(960),timing,false).count() == 1);
		CPPUNIT_ASSERT(miditicks(microseconds(1399),timing,false).count() == 1);
		CPPUNIT_ASSERT(miditicks(microseconds(2400),timing,false).count() == 2);
		params = timing.get_MIDI_tick_signature();
		CPPUNIT_ASSERT(params.first == 1);
		CPPUNIT_ASSERT(params.second == 224);

		timing.set_MIDI_tick_signature(0xe2,120);
		std::cerr << "get = " << timing.get_ticks() << std::endl;
		CPPUNIT_ASSERT(timing.get_ticks() == 3600);
		CPPUNIT_ASSERT(miditicks(1,timing).mus() == microseconds(278));
		CPPUNIT_ASSERT(miditicks(microseconds(555),timing,false).count() == 2);
		CPPUNIT_ASSERT(miditicks(microseconds(694),timing,false).count() == 2);
		CPPUNIT_ASSERT(miditicks(microseconds(695),timing,false).count() == 3);
		params = timing.get_MIDI_tick_signature();
		CPPUNIT_ASSERT(params.first == 0xe2);
		CPPUNIT_ASSERT(params.second == 120);

		timing.set_MIDI_tick_signature(0xe8,100);
		CPPUNIT_ASSERT(timing.get_ticks() == 2400);
		CPPUNIT_ASSERT(miditicks(1,timing).mus() == microseconds(417));
		CPPUNIT_ASSERT(miditicks(microseconds(833),timing,false).count() == 2);
		CPPUNIT_ASSERT(miditicks(microseconds(1041),timing,false).count() == 2);
		CPPUNIT_ASSERT(miditicks(microseconds(1042),timing,false).count() == 3);
		params = timing.get_MIDI_tick_signature();
		CPPUNIT_ASSERT(params.first == 0xe8);
		CPPUNIT_ASSERT(params.second == 100);

		// 29 is handled like 30
		timing.set_MIDI_tick_signature(0xe3,120);
		CPPUNIT_ASSERT(timing.get_ticks() == 3600);
		CPPUNIT_ASSERT(miditicks(1,timing).mus() == microseconds(278));
		CPPUNIT_ASSERT(miditicks(microseconds(555),timing,false).count() == 2);
		CPPUNIT_ASSERT(miditicks(microseconds(694),timing,false).count() == 2);
		CPPUNIT_ASSERT(miditicks(microseconds(695),timing,false).count() == 3);
		params = timing.get_MIDI_tick_signature();
		CPPUNIT_ASSERT(params.first == 0xe2);
		CPPUNIT_ASSERT(params.second == 120);

		timing.set_MIDI_tick_signature(0xe7,40);
		CPPUNIT_ASSERT(timing.get_ticks() == 1000);
		CPPUNIT_ASSERT(timing.get_quarter_duration() == milliseconds(500));
		params = timing.get_MIDI_tick_signature();
		CPPUNIT_ASSERT(params.first == 0xe7); // -25
		CPPUNIT_ASSERT(params.second == 40);
		CPPUNIT_ASSERT(miditicks(1,timing).mus() == microseconds(1000));
		CPPUNIT_ASSERT(miditicks(microseconds(1000),timing,false).count() == 1);

	}

};
///\}

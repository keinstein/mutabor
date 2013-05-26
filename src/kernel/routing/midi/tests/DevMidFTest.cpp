/** \file               -*- C++ -*-
 ********************************************************************
 * Test Midi File functions
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
#include "src/kernel/Defs.h"
#include "src/kernel/Runtime.h"
#include "src/kernel/routing/midi/tests/DevMidFTest.h"
#include "src/kernel/routing/midi/tests/midicmnTest.h"
#include "src/kernel/routing/midi/midicmn-inlines.h"
#include "src/kernel/routing/Route-inlines.h"


void  InputMidiFileTest::testBatchPlay1() 
{
#ifdef DEBUG
	debugFlags::flags.timer = true;
	debugFlags::flags.midiio = true;
#endif

	mutabor::OutputDevice guard;
	midicmnOutputDevice * out;
	mutabor ::Route  route;
	mutabor_box_type * box;
	mutabor::ChannelData cd;

	initialize_boxes();
	GlobalReset();
	route = mutabor::RouteFactory::Create();
	connect(route,0);
	box = &mut_box[route->GetBox()];

	mutabor::CurrentTime.UseRealtime(true);
	out = new midicmnOutputDevice(3,_T("Test"));
	out->SetBendingRange(2);
	//out = new midicmnOutputDevice(3,_T("Test"));
	guard = out;

	connect(route,guard);
	route->SetOutputFrom (0);
	route->SetOutputTo (15);
	route->OutputAvoidDrumChannel (true);

	connect(route, in);

	CPPUNIT_ASSERT( in );
	in -> SetName(_T(SRCDIR) _T("/midi1_source.mid"));


	// First check: Input device provides the correct delta times

	GlobalReset();
	mutabor::CurrentTime.UseRealtime(false);
	mutabor::CurrentTime = 0;

	CPPUNIT_ASSERT((out -> Open()));
	CPPUNIT_ASSERT((in -> Open()));
	CPPUNIT_ASSERT(out->Check(_T("0 Opened...\n\
0   0: e0 00 40\n\
0   0: b0 7a 00\n\
0   0: b0 7d 00\n\
0   0: b0 7f 00\n\
0   0: b0 65 00\n\
0   0: b0 64 00\n\
0   0: b0 06 02\n\
0   0: b0 26 00\n\
0   1: e1 00 40\n\
0   1: b1 7a 00\n\
0   1: b1 7d 00\n\
0   1: b1 7f 00\n\
0   1: b1 65 00\n\
0   1: b1 64 00\n\
0   1: b1 06 02\n\
0   1: b1 26 00\n\
0   2: e2 00 40\n\
0   2: b2 7a 00\n\
0   2: b2 7d 00\n\
0   2: b2 7f 00\n\
0   2: b2 65 00\n\
0   2: b2 64 00\n\
0   2: b2 06 02\n\
0   2: b2 26 00\n\
0   3: e3 00 40\n\
0   3: b3 7a 00\n\
0   3: b3 7d 00\n\
0   3: b3 7f 00\n\
0   3: b3 65 00\n\
0   3: b3 64 00\n\
0   3: b3 06 02\n\
0   3: b3 26 00\n\
0   4: e4 00 40\n\
0   4: b4 7a 00\n\
0   4: b4 7d 00\n\
0   4: b4 7f 00\n\
0   4: b4 65 00\n\
0   4: b4 64 00\n\
0   4: b4 06 02\n\
0   4: b4 26 00\n\
0   5: e5 00 40\n\
0   5: b5 7a 00\n\
0   5: b5 7d 00\n\
0   5: b5 7f 00\n\
0   5: b5 65 00\n\
0   5: b5 64 00\n\
0   5: b5 06 02\n\
0   5: b5 26 00\n\
0   6: e6 00 40\n\
0   6: b6 7a 00\n\
0   6: b6 7d 00\n\
0   6: b6 7f 00\n\
0   6: b6 65 00\n\
0   6: b6 64 00\n\
0   6: b6 06 02\n\
0   6: b6 26 00\n\
0   7: e7 00 40\n\
0   7: b7 7a 00\n\
0   7: b7 7d 00\n\
0   7: b7 7f 00\n\
0   7: b7 65 00\n\
0   7: b7 64 00\n\
0   7: b7 06 02\n\
0   7: b7 26 00\n\
0   8: e8 00 40\n\
0   8: b8 7a 00\n\
0   8: b8 7d 00\n\
0   8: b8 7f 00\n\
0   8: b8 65 00\n\
0   8: b8 64 00\n\
0   8: b8 06 02\n\
0   8: b8 26 00\n\
0   9: e9 00 40\n\
0   9: b9 7a 00\n\
0   9: b9 7d 00\n\
0   9: b9 7f 00\n\
0   9: b9 65 00\n\
0   9: b9 64 00\n\
0   9: b9 06 02\n\
0   9: b9 26 00\n\
0  10: ea 00 40\n\
0  10: ba 7a 00\n\
0  10: ba 7d 00\n\
0  10: ba 7f 00\n\
0  10: ba 65 00\n\
0  10: ba 64 00\n\
0  10: ba 06 02\n\
0  10: ba 26 00\n\
0  11: eb 00 40\n\
0  11: bb 7a 00\n\
0  11: bb 7d 00\n\
0  11: bb 7f 00\n\
0  11: bb 65 00\n\
0  11: bb 64 00\n\
0  11: bb 06 02\n\
0  11: bb 26 00\n\
0  12: ec 00 40\n\
0  12: bc 7a 00\n\
0  12: bc 7d 00\n\
0  12: bc 7f 00\n\
0  12: bc 65 00\n\
0  12: bc 64 00\n\
0  12: bc 06 02\n\
0  12: bc 26 00\n\
0  13: ed 00 40\n\
0  13: bd 7a 00\n\
0  13: bd 7d 00\n\
0  13: bd 7f 00\n\
0  13: bd 65 00\n\
0  13: bd 64 00\n\
0  13: bd 06 02\n\
0  13: bd 26 00\n\
0  14: ee 00 40\n\
0  14: be 7a 00\n\
0  14: be 7d 00\n\
0  14: be 7f 00\n\
0  14: be 65 00\n\
0  14: be 64 00\n\
0  14: be 06 02\n\
0  14: be 26 00\n\
0  15: ef 00 40\n\
0  15: bf 7a 00\n\
0  15: bf 7d 00\n\
0  15: bf 7f 00\n\
0  15: bf 65 00\n\
0  15: bf 64 00\n\
0  15: bf 06 02\n\
0  15: bf 26 00\n"),__LINE__,_T(__FILE__)));
	
//	in -> Play(wxTHREAD_JOINABLE);
//	mutabor::InputDeviceClass::BatchPlay();
	in -> Play();
	mutint64 delta = in -> PrepareNextEvent();
	CPPUNIT_ASSERT(out->Check(_T("0   0: b0 7b 00\n\
0   1: b1 7b 00\n\
0   2: b2 7b 00\n\
0   3: b3 7b 00\n\
0   4: b4 7b 00\n\
0   5: b5 7b 00\n\
0   6: b6 7b 00\n\
0   7: b7 7b 00\n\
0   8: b8 7b 00\n\
0   9: b9 7b 00\n\
0  10: ba 7b 00\n\
0  11: bb 7b 00\n\
0  12: bc 7b 00\n\
0  13: bd 7b 00\n\
0  14: be 7b 00\n\
0  15: bf 7b 00\n\
0   0: c0 4f\n\
0   0: 90 3c 7f\n"),__LINE__,_T(__FILE__)));

	std::cout << delta << std::endl;
	CPPUNIT_ASSERT(delta == 49920);
	delta = in -> PrepareNextEvent();
	CPPUNIT_ASSERT(out->Check(_T("\
0   1: c1 4f\n\
0   1: 91 40 1f\n"),__LINE__,_T(__FILE__)));
	std::cout << delta << std::endl;
	CPPUNIT_ASSERT(delta == 49920);
	delta = in -> PrepareNextEvent();
	CPPUNIT_ASSERT(out->Check(_T("0   1: 81 40 40\n\
0   2: c2 4f\n\
0   2: 92 43 3f\n"),__LINE__,_T(__FILE__)));
	std::cout << delta << std::endl;
	CPPUNIT_ASSERT(delta == 49920);
	delta = in -> PrepareNextEvent();
	CPPUNIT_ASSERT(out->Check(_T("0   2: 82 43 40\n\
0   3: c3 4f\n\
0   3: 93 34 7f\n"),__LINE__,_T(__FILE__)));
	std::cout << delta << std::endl;
	CPPUNIT_ASSERT(delta == 49920);
	delta = in -> PrepareNextEvent();
	CPPUNIT_ASSERT(out->Check(_T("0   3: 83 34 40\n"),__LINE__,_T(__FILE__)));
	std::cout << delta << std::endl;
	CPPUNIT_ASSERT(delta == 49920);
	delta = in -> PrepareNextEvent();
	CPPUNIT_ASSERT(out->Check(_T("0   0: 80 3c 7f\n"),__LINE__,_T(__FILE__)));
	std::cout << delta << std::endl;
	CPPUNIT_ASSERT(delta == MUTABOR_NO_DELTA);

	in->Close();
	out->Close();
	CPPUNIT_ASSERT(out->Check(_T("0 ...closed.\n"),__LINE__,_T(__FILE__)));



	// Second check: Output device gets the correct delta times

	mutabor::CurrentTime = 0;

//	in -> Play(wxTHREAD_JOINABLE);
	mutabor::InputDeviceClass::BatchPlay();

	CPPUNIT_ASSERT(out->Check(_T("0 Opened...\n\
0   0: e0 00 40\n\
0   0: b0 7a 00\n\
0   0: b0 7d 00\n\
0   0: b0 7f 00\n\
0   0: b0 65 00\n\
0   0: b0 64 00\n\
0   0: b0 06 02\n\
0   0: b0 26 00\n\
0   1: e1 00 40\n\
0   1: b1 7a 00\n\
0   1: b1 7d 00\n\
0   1: b1 7f 00\n\
0   1: b1 65 00\n\
0   1: b1 64 00\n\
0   1: b1 06 02\n\
0   1: b1 26 00\n\
0   2: e2 00 40\n\
0   2: b2 7a 00\n\
0   2: b2 7d 00\n\
0   2: b2 7f 00\n\
0   2: b2 65 00\n\
0   2: b2 64 00\n\
0   2: b2 06 02\n\
0   2: b2 26 00\n\
0   3: e3 00 40\n\
0   3: b3 7a 00\n\
0   3: b3 7d 00\n\
0   3: b3 7f 00\n\
0   3: b3 65 00\n\
0   3: b3 64 00\n\
0   3: b3 06 02\n\
0   3: b3 26 00\n\
0   4: e4 00 40\n\
0   4: b4 7a 00\n\
0   4: b4 7d 00\n\
0   4: b4 7f 00\n\
0   4: b4 65 00\n\
0   4: b4 64 00\n\
0   4: b4 06 02\n\
0   4: b4 26 00\n\
0   5: e5 00 40\n\
0   5: b5 7a 00\n\
0   5: b5 7d 00\n\
0   5: b5 7f 00\n\
0   5: b5 65 00\n\
0   5: b5 64 00\n\
0   5: b5 06 02\n\
0   5: b5 26 00\n\
0   6: e6 00 40\n\
0   6: b6 7a 00\n\
0   6: b6 7d 00\n\
0   6: b6 7f 00\n\
0   6: b6 65 00\n\
0   6: b6 64 00\n\
0   6: b6 06 02\n\
0   6: b6 26 00\n\
0   7: e7 00 40\n\
0   7: b7 7a 00\n\
0   7: b7 7d 00\n\
0   7: b7 7f 00\n\
0   7: b7 65 00\n\
0   7: b7 64 00\n\
0   7: b7 06 02\n\
0   7: b7 26 00\n\
0   8: e8 00 40\n\
0   8: b8 7a 00\n\
0   8: b8 7d 00\n\
0   8: b8 7f 00\n\
0   8: b8 65 00\n\
0   8: b8 64 00\n\
0   8: b8 06 02\n\
0   8: b8 26 00\n\
0   9: e9 00 40\n\
0   9: b9 7a 00\n\
0   9: b9 7d 00\n\
0   9: b9 7f 00\n\
0   9: b9 65 00\n\
0   9: b9 64 00\n\
0   9: b9 06 02\n\
0   9: b9 26 00\n\
0  10: ea 00 40\n\
0  10: ba 7a 00\n\
0  10: ba 7d 00\n\
0  10: ba 7f 00\n\
0  10: ba 65 00\n\
0  10: ba 64 00\n\
0  10: ba 06 02\n\
0  10: ba 26 00\n\
0  11: eb 00 40\n\
0  11: bb 7a 00\n\
0  11: bb 7d 00\n\
0  11: bb 7f 00\n\
0  11: bb 65 00\n\
0  11: bb 64 00\n\
0  11: bb 06 02\n\
0  11: bb 26 00\n\
0  12: ec 00 40\n\
0  12: bc 7a 00\n\
0  12: bc 7d 00\n\
0  12: bc 7f 00\n\
0  12: bc 65 00\n\
0  12: bc 64 00\n\
0  12: bc 06 02\n\
0  12: bc 26 00\n\
0  13: ed 00 40\n\
0  13: bd 7a 00\n\
0  13: bd 7d 00\n\
0  13: bd 7f 00\n\
0  13: bd 65 00\n\
0  13: bd 64 00\n\
0  13: bd 06 02\n\
0  13: bd 26 00\n\
0  14: ee 00 40\n\
0  14: be 7a 00\n\
0  14: be 7d 00\n\
0  14: be 7f 00\n\
0  14: be 65 00\n\
0  14: be 64 00\n\
0  14: be 06 02\n\
0  14: be 26 00\n\
0  15: ef 00 40\n\
0  15: bf 7a 00\n\
0  15: bf 7d 00\n\
0  15: bf 7f 00\n\
0  15: bf 65 00\n\
0  15: bf 64 00\n\
0  15: bf 06 02\n\
0  15: bf 26 00\n\
0   0: b0 7b 00\n\
0   1: b1 7b 00\n\
0   2: b2 7b 00\n\
0   3: b3 7b 00\n\
0   4: b4 7b 00\n\
0   5: b5 7b 00\n\
0   6: b6 7b 00\n\
0   7: b7 7b 00\n\
0   8: b8 7b 00\n\
0   9: b9 7b 00\n\
0  10: ba 7b 00\n\
0  11: bb 7b 00\n\
0  12: bc 7b 00\n\
0  13: bd 7b 00\n\
0  14: be 7b 00\n\
0  15: bf 7b 00\n\
0   0: c0 4f\n\
0   0: 90 3c 7f\n\
49920   1: c1 4f\n\
49920   1: 91 40 1f\n\
99840   1: 81 40 40\n\
99840   2: c2 4f\n\
99840   2: 92 43 3f\n\
149760   2: 82 43 40\n\
149760   3: c3 4f\n\
149760   3: 93 34 7f\n\
199680   3: 83 34 40\n\
249600   0: 80 3c 7f\n\
249600 ...closed.\n"),__LINE__,_T(__FILE__)));

	sleep(1);

	mutabor::InputDeviceClass::BatchPlay();

	CPPUNIT_ASSERT(out->Check(_T("0 Opened...\n\
0   0: e0 00 40\n\
0   0: b0 7a 00\n\
0   0: b0 7d 00\n\
0   0: b0 7f 00\n\
0   0: b0 65 00\n\
0   0: b0 64 00\n\
0   0: b0 06 02\n\
0   0: b0 26 00\n\
0   1: e1 00 40\n\
0   1: b1 7a 00\n\
0   1: b1 7d 00\n\
0   1: b1 7f 00\n\
0   1: b1 65 00\n\
0   1: b1 64 00\n\
0   1: b1 06 02\n\
0   1: b1 26 00\n\
0   2: e2 00 40\n\
0   2: b2 7a 00\n\
0   2: b2 7d 00\n\
0   2: b2 7f 00\n\
0   2: b2 65 00\n\
0   2: b2 64 00\n\
0   2: b2 06 02\n\
0   2: b2 26 00\n\
0   3: e3 00 40\n\
0   3: b3 7a 00\n\
0   3: b3 7d 00\n\
0   3: b3 7f 00\n\
0   3: b3 65 00\n\
0   3: b3 64 00\n\
0   3: b3 06 02\n\
0   3: b3 26 00\n\
0   4: e4 00 40\n\
0   4: b4 7a 00\n\
0   4: b4 7d 00\n\
0   4: b4 7f 00\n\
0   4: b4 65 00\n\
0   4: b4 64 00\n\
0   4: b4 06 02\n\
0   4: b4 26 00\n\
0   5: e5 00 40\n\
0   5: b5 7a 00\n\
0   5: b5 7d 00\n\
0   5: b5 7f 00\n\
0   5: b5 65 00\n\
0   5: b5 64 00\n\
0   5: b5 06 02\n\
0   5: b5 26 00\n\
0   6: e6 00 40\n\
0   6: b6 7a 00\n\
0   6: b6 7d 00\n\
0   6: b6 7f 00\n\
0   6: b6 65 00\n\
0   6: b6 64 00\n\
0   6: b6 06 02\n\
0   6: b6 26 00\n\
0   7: e7 00 40\n\
0   7: b7 7a 00\n\
0   7: b7 7d 00\n\
0   7: b7 7f 00\n\
0   7: b7 65 00\n\
0   7: b7 64 00\n\
0   7: b7 06 02\n\
0   7: b7 26 00\n\
0   8: e8 00 40\n\
0   8: b8 7a 00\n\
0   8: b8 7d 00\n\
0   8: b8 7f 00\n\
0   8: b8 65 00\n\
0   8: b8 64 00\n\
0   8: b8 06 02\n\
0   8: b8 26 00\n\
0   9: e9 00 40\n\
0   9: b9 7a 00\n\
0   9: b9 7d 00\n\
0   9: b9 7f 00\n\
0   9: b9 65 00\n\
0   9: b9 64 00\n\
0   9: b9 06 02\n\
0   9: b9 26 00\n\
0  10: ea 00 40\n\
0  10: ba 7a 00\n\
0  10: ba 7d 00\n\
0  10: ba 7f 00\n\
0  10: ba 65 00\n\
0  10: ba 64 00\n\
0  10: ba 06 02\n\
0  10: ba 26 00\n\
0  11: eb 00 40\n\
0  11: bb 7a 00\n\
0  11: bb 7d 00\n\
0  11: bb 7f 00\n\
0  11: bb 65 00\n\
0  11: bb 64 00\n\
0  11: bb 06 02\n\
0  11: bb 26 00\n\
0  12: ec 00 40\n\
0  12: bc 7a 00\n\
0  12: bc 7d 00\n\
0  12: bc 7f 00\n\
0  12: bc 65 00\n\
0  12: bc 64 00\n\
0  12: bc 06 02\n\
0  12: bc 26 00\n\
0  13: ed 00 40\n\
0  13: bd 7a 00\n\
0  13: bd 7d 00\n\
0  13: bd 7f 00\n\
0  13: bd 65 00\n\
0  13: bd 64 00\n\
0  13: bd 06 02\n\
0  13: bd 26 00\n\
0  14: ee 00 40\n\
0  14: be 7a 00\n\
0  14: be 7d 00\n\
0  14: be 7f 00\n\
0  14: be 65 00\n\
0  14: be 64 00\n\
0  14: be 06 02\n\
0  14: be 26 00\n\
0  15: ef 00 40\n\
0  15: bf 7a 00\n\
0  15: bf 7d 00\n\
0  15: bf 7f 00\n\
0  15: bf 65 00\n\
0  15: bf 64 00\n\
0  15: bf 06 02\n\
0  15: bf 26 00\n\
0   0: b0 7b 00\n\
0   1: b1 7b 00\n\
0   2: b2 7b 00\n\
0   3: b3 7b 00\n\
0   4: b4 7b 00\n\
0   5: b5 7b 00\n\
0   6: b6 7b 00\n\
0   7: b7 7b 00\n\
0   8: b8 7b 00\n\
0   9: b9 7b 00\n\
0  10: ba 7b 00\n\
0  11: bb 7b 00\n\
0  12: bc 7b 00\n\
0  13: bd 7b 00\n\
0  14: be 7b 00\n\
0  15: bf 7b 00\n\
0   0: c0 4f\n\
0   0: 90 3c 7f\n\
49920   1: c1 4f\n\
49920   1: 91 40 1f\n\
99840   1: 81 40 40\n\
99840   2: c2 4f\n\
99840   2: 92 43 3f\n\
149760   2: 82 43 40\n\
149760   3: c3 4f\n\
149760   3: 93 34 7f\n\
199680   3: 83 34 40\n\
249600   0: 80 3c 7f\n\
249600 ...closed.\n"),__LINE__,_T(__FILE__)));
	out->Destroy();
	out=NULL;
	route->Destroy();
	route = NULL;
}

void OutputMidiFileTest::setUp() 
{ 
// change DEBUGA to DEBUG in case you need the debug output
#ifdef DEBUGA
	debugFlags::flags.timer = true;
	debugFlags::flags.midiio = true;
	debugFlags::flags.midifile = true;
#else 
#ifdef DEBUG
	debugFlags::flags.timer = false;
	debugFlags::flags.midiio = false;
	debugFlags::flags.midifile = false;
#endif
#endif
	std::clog << "Running setUp()" << std::endl;

	initialize_boxes();
	GlobalReset();
	CPPUNIT_ASSERT(mutabor::InputDeviceClass::GetDeviceList().empty());
	CPPUNIT_ASSERT(mutabor::OutputDeviceClass::GetDeviceList().empty());
	CPPUNIT_ASSERT(mutabor::RouteClass::GetRouteList().empty());

	route = mutabor::RouteFactory::Create();
	connect(route, 0);
	box = &mut_box[route->GetBox()];

	mutabor::CurrentTime.UseRealtime(true);
	out = static_cast<mutabor::OutputMidiFile *>(mutabor::DeviceFactory::CreateOutput(mutabor::DTMidiFile).get());
	out->SetName(_T("test_output.mid"));
	out->SetBendingRange(2);
	//out = new midicmnOutputDevice(3,_T("Test"));
	guard = out;

	connect(route, guard);
	route->SetOutputFrom (0);
	route->SetOutputTo (15);
	route->OutputAvoidDrumChannel (true);
}

void OutputMidiFileTest::tearDown()
{ 
#ifdef DEBUG
	debugFlags::flags.timer = false;
	debugFlags::flags.midifile = false;
#endif
	out -> Destroy();
	out = NULL;
	guard = NULL;
	route -> Destroy();
	route = NULL;

	CPPUNIT_ASSERT(mutabor::InputDeviceClass::GetDeviceList().empty());
	CPPUNIT_ASSERT(mutabor::OutputDeviceClass::GetDeviceList().empty());
	CPPUNIT_ASSERT(mutabor::RouteClass::GetRouteList().empty());

}


void OutputMidiFileTest::testNoteOnOff()
{
	CPPUNIT_ASSERT( out );
	out->Open();
/*
	CPPUNIT_ASSERT( out->Check(_T("Opened...\n"
				      "  0: e0 00 40\n"
				      "  0: b0 7a 00\n"
				      "  0: b0 7d 00\n"
				      "  0: b0 7f 00\n"
				      "  1: e1 00 40\n"
				      "  1: b1 7a 00\n"
				      "  1: b1 7d 00\n"
				      "  1: b1 7f 00\n"
				      "  2: e2 00 40\n"
				      "  2: b2 7a 00\n"
				      "  2: b2 7d 00\n"
				      "  2: b2 7f 00\n"
				      "  3: e3 00 40\n"
				      "  3: b3 7a 00\n"
				      "  3: b3 7d 00\n"
				      "  3: b3 7f 00\n"
				      "  4: e4 00 40\n"
				      "  4: b4 7a 00\n"
				      "  4: b4 7d 00\n"
				      "  4: b4 7f 00\n"
				      "  5: e5 00 40\n"
				      "  5: b5 7a 00\n"
				      "  5: b5 7d 00\n"
				      "  5: b5 7f 00\n"
				      "  6: e6 00 40\n"
				      "  6: b6 7a 00\n"
				      "  6: b6 7d 00\n"
				      "  6: b6 7f 00\n"
				      "  7: e7 00 40\n"
				      "  7: b7 7a 00\n"
				      "  7: b7 7d 00\n"
				      "  7: b7 7f 00\n"
				      "  8: e8 00 40\n"
				      "  8: b8 7a 00\n"
				      "  8: b8 7d 00\n"
				      "  8: b8 7f 00\n"
				      "  9: e9 00 40\n"
				      "  9: b9 7a 00\n"
				      "  9: b9 7d 00\n"
				      "  9: b9 7f 00\n"
				      " 10: ea 00 40\n"
				      " 10: ba 7a 00\n"
				      " 10: ba 7d 00\n"
				      " 10: ba 7f 00\n"
				      " 11: eb 00 40\n"
				      " 11: bb 7a 00\n"
				      " 11: bb 7d 00\n"
				      " 11: bb 7f 00\n"
				      " 12: ec 00 40\n"
				      " 12: bc 7a 00\n"
				      " 12: bc 7d 00\n"
				      " 12: bc 7f 00\n"
				      " 13: ed 00 40\n"
				      " 13: bd 7a 00\n"
				      " 13: bd 7d 00\n"
				      " 13: bd 7f 00\n"
				      " 14: ee 00 40\n"
				      " 14: be 7a 00\n"
				      " 14: be 7d 00\n"
				      " 14: be 7f 00\n"
				      " 15: ef 00 40\n"
				      " 15: bf 7a 00\n"
				      " 15: bf 7d 00\n"
				      " 15: bf 7f 00\n")) );
*/
	/* check all permutations */

	DEBUGLOG(midiio,_T("123"));

	out->NoteOn(box,56,96,route.get(),0,cd);
//	CPPUNIT_ASSERT( out->Check(_T("  0: b0 40 00\n  0: 90 38 60\n") ) );
	out->NoteOn(box,60,97,route.get(),0,cd);
//	CPPUNIT_ASSERT( out->Check(_T("  1: b1 40 00\n  1: 91 3c 61\n") ) );
	out->NoteOn(box,63,98,route.get(),0,cd);
//	CPPUNIT_ASSERT( out->Check(_T("  2: b2 40 00\n  2: 92 3f 62\n") ) );

	usleep(200000);
	out->NoteOff(box,56,53,route.get(),0,false);
//	CPPUNIT_ASSERT( out->Check(_T("  0: 80 38 35\n")) );
	out->NoteOff(box,60,54,route.get(),0,false);
//	CPPUNIT_ASSERT( out->Check(_T("  1: 81 3c 36\n")) );
	out->NoteOff(box,63,55,route.get(),0,false);
//	CPPUNIT_ASSERT( out->Check(_T("  2: 82 3f 37\n")) );

	usleep(200000);
	DEBUGLOG(midiio,_T("132"));

	out->NoteOn(box,56,96,route.get(),0,cd);
//	CPPUNIT_ASSERT( out->Check(_T("  3: b3 40 00\n  3: 93 38 60\n") ) );
	out->NoteOn(box,60,97,route.get(),0,cd);
//	CPPUNIT_ASSERT( out->Check(_T("  4: b4 40 00\n  4: 94 3c 61\n") ) );
	out->NoteOn(box,63,98,route.get(),0,cd);
//	CPPUNIT_ASSERT( out->Check(_T("  5: b5 40 00\n  5: 95 3f 62\n") ) );

	usleep(200000);
	out->NoteOff(box,56,53,route.get(),0,false);
//	CPPUNIT_ASSERT( out->Check(_T("  3: 83 38 35\n")) );
	out->NoteOff(box,63,55,route.get(),0,false);
//	CPPUNIT_ASSERT( out->Check(_T("  5: 85 3f 37\n")) );
	out->NoteOff(box,60,54,route.get(),0,false);
//	CPPUNIT_ASSERT( out->Check(_T("  4: 84 3c 36\n")) );

	DEBUGLOG(midiio,_T("213"));

	usleep(200000);
	out->NoteOn(box,56,96,route.get(),0,cd);
//	CPPUNIT_ASSERT( out->Check(_T("  6: b6 40 00\n  6: 96 38 60\n") ) );
	out->NoteOn(box,60,97,route.get(),0,cd);
//	CPPUNIT_ASSERT( out->Check(_T("  7: b7 40 00\n  7: 97 3c 61\n") ) );
	out->NoteOn(box,63,98,route.get(),0,cd);
//	CPPUNIT_ASSERT( out->Check(_T("  8: b8 40 00\n  8: 98 3f 62\n") ) );

	out->NoteOff(box,60,54,route.get(),0,false);
//	CPPUNIT_ASSERT( out->Check(_T("  7: 87 3c 36\n")) );
	out->NoteOff(box,56,53,route.get(),0,false);
//	CPPUNIT_ASSERT( out->Check(_T("  6: 86 38 35\n")) );
	out->NoteOff(box,63,55,route.get(),0,false);
//	CPPUNIT_ASSERT( out->Check(_T("  8: 88 3f 37\n")) );

	usleep(200000);
	DEBUGLOG(midiio,_T("231"));

	out->NoteOn(box,56,96,route.get(),0,cd);
//	CPPUNIT_ASSERT( out->Check(_T(" 10: ba 40 00\n 10: 9a 38 60\n") ) );
	out->NoteOn(box,60,97,route.get(),0,cd);
//	CPPUNIT_ASSERT( out->Check(_T(" 11: bb 40 00\n 11: 9b 3c 61\n") ) );
	out->NoteOn(box,63,98,route.get(),0,cd);
//	CPPUNIT_ASSERT( out->Check(_T(" 12: bc 40 00\n 12: 9c 3f 62\n") ) );

	usleep(200000);
	out->NoteOff(box,60,54,route.get(),0,false);
//	CPPUNIT_ASSERT( out->Check(_T(" 11: 8b 3c 36\n")) );
	out->NoteOff(box,63,55,route.get(),0,false);
//	CPPUNIT_ASSERT( out->Check(_T(" 12: 8c 3f 37\n")) );
	out->NoteOff(box,56,53,route.get(),0,false);
//	CPPUNIT_ASSERT( out->Check(_T(" 10: 8a 38 35\n")) );

	usleep(200000);
	DEBUGLOG(midiio,_T("312"));

	out->NoteOn(box,56,96,route.get(),0,cd);
//	CPPUNIT_ASSERT( out->Check(_T(" 13: bd 40 00\n 13: 9d 38 60\n") ) );
	out->NoteOn(box,60,97,route.get(),0,cd);
//	CPPUNIT_ASSERT( out->Check(_T(" 14: be 40 00\n 14: 9e 3c 61\n") ) );
	out->NoteOn(box,63,98,route.get(),0,cd);
//	CPPUNIT_ASSERT( out->Check(_T(" 15: bf 40 00\n 15: 9f 3f 62\n") ) );

	usleep(200000);
	out->NoteOff(box,63,55,route.get(),0,false);
//	CPPUNIT_ASSERT( out->Check(_T(" 15: 8f 3f 37\n")) );
	// check sending note on with velocity = 0 
	out->NoteOff(box,56,53,route.get(),0,true);
//	CPPUNIT_ASSERT( out->Check(_T(" 13: 9d 38 00\n")) );
	out->NoteOff(box,60,54,route.get(),0,false);
//	CPPUNIT_ASSERT( out->Check(_T(" 14: 8e 3c 36\n")) );

	usleep(200000);
	DEBUGLOG(midiio,_T("321"));

	// Add check for NULL as tone system parameter
	out->NoteOn(NULL,56,96,route.get(),0,cd);
//	CPPUNIT_ASSERT( out->Check(_T("  0: 90 38 60\n") ) );
	out->NoteOn(NULL,60,97,route.get(),0,cd);
//	CPPUNIT_ASSERT( out->Check(_T("  1: 91 3c 61\n") ) );
	out->NoteOn(NULL,63,98,route.get(),0,cd);
//	CPPUNIT_ASSERT( out->Check(_T("  2: 92 3f 62\n") ) );

	usleep(200000);
	out->NoteOff(NULL,63,55,route.get(),0,false);
//	CPPUNIT_ASSERT( out->Check(_T("  2: 82 3f 37\n")) );
	out->NoteOff(NULL,60,54,route.get(),0,false);
//	CPPUNIT_ASSERT( out->Check(_T("  1: 81 3c 36\n")) );
	out->NoteOff(NULL,56,53,route.get(),0,false);
//	CPPUNIT_ASSERT( out->Check(_T("  0: 80 38 35\n")) );




	out->Close();
//	DEBUGLOG(midiio,_T("|%s|"),((mutString)(out->getOut())).c_str());
//	CPPUNIT_ASSERT( out->Check(_T("...closed.\n")) );
}

///\}

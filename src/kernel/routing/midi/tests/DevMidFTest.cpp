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

#include "wx/mstream.h"

#include "src/kernel/routing/midi/midicmn.cpp"
template class mutabor::CommonMidiOutput<mutabor::DebugMidiOutputProvider, mutabor::OutputDeviceClass>;

void  InputMidiFileTest::testBatchPlay1()
{
#ifdef DEBUG
//	debugFlags::flags.timer = true;
//	debugFlags::flags.midiio = true;
#endif

	// input device is set up during setUp
	CPPUNIT_ASSERT(mutabor::InputDeviceClass::GetDeviceList().size()==1);
	CPPUNIT_ASSERT(mutabor::OutputDeviceClass::GetDeviceList().empty());
	CPPUNIT_ASSERT(mutabor::RouteClass::GetRouteList().empty());
	CPPUNIT_ASSERT(mutabor::BoxClass::GetBoxList().empty());

	mutabor::ScopedOutputDevice guard;
	midicmnOutputDevice * out;
	mutabor::ScopedBox box(NULL);
	mutabor::ScopedRoute  route;
	mutabor::ChannelData cd;

	route = mutabor::RouteFactory::Create();
	box = mutabor::BoxFactory::Create(mutabor::Box0,0);
	connect(route,box);

	mutabor::CurrentTime.UseRealtime(true);
	out = new midicmnOutputDevice(_T("Test"));
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

	mutabor::CurrentTime.UseRealtime(false);
	mutabor::CurrentTime = 0;

	CPPUNIT_ASSERT((out -> Open()));
	CPPUNIT_ASSERT(box -> Open());
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
	CPPUNIT_ASSERT(out->Check(_T("\
0   0: c0 4f\n\
0   0: 90 3c 7f\n"),__LINE__,_T(__FILE__)));

	CPPUNIT_ASSERT(delta == 49920);
	delta = in -> PrepareNextEvent();
	CPPUNIT_ASSERT(out->Check(_T("\
0   1: c1 4f\n\
0   1: 91 40 1f\n"),__LINE__,_T(__FILE__)));
	CPPUNIT_ASSERT(delta == 49920);
	delta = in -> PrepareNextEvent();
	CPPUNIT_ASSERT(out->Check(_T("0   1: 81 40 40\n\
0   2: c2 4f\n\
0   2: 92 43 3f\n"),__LINE__,_T(__FILE__)));
	CPPUNIT_ASSERT(delta == 49920);
	delta = in -> PrepareNextEvent();
	CPPUNIT_ASSERT(out->Check(_T("0   2: 82 43 40\n\
0   3: c3 4f\n\
0   3: 93 34 7f\n"),__LINE__,_T(__FILE__)));
	CPPUNIT_ASSERT(delta == 49920);
	delta = in -> PrepareNextEvent();
	CPPUNIT_ASSERT(out->Check(_T("0   3: 83 34 40\n"),__LINE__,_T(__FILE__)));
	CPPUNIT_ASSERT(delta == 49920);
	delta = in -> PrepareNextEvent();
	CPPUNIT_ASSERT(out->Check(_T("0   0: 80 3c 7f\n"),__LINE__,_T(__FILE__)));
	CPPUNIT_ASSERT(delta == MUTABOR_NO_DELTA);

	in->Close();
	box->Close();
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
}


void  InputMidiFileTest::testBug019010_2()
{
#ifdef DEBUG
//	debugFlags::flags.timer = true;
//	debugFlags::flags.midiio = true;
//	debugFlags::flags.midifile = true;
#endif

	// input device is created during setUp
	CPPUNIT_ASSERT(mutabor::InputDeviceClass::GetDeviceList().size() == 1);
	CPPUNIT_ASSERT(mutabor::OutputDeviceClass::GetDeviceList().empty());
	CPPUNIT_ASSERT(mutabor::RouteClass::GetRouteList().empty());
	CPPUNIT_ASSERT(mutabor::BoxClass::GetBoxList().empty());

	mutabor::ScopedOutputDevice guard;
	midicmnOutputDevice * out;
	mutabor::ScopedBox box(NULL);
	mutabor::ScopedRoute  route;
	mutabor::ChannelData cd;

	route = mutabor::RouteFactory::Create();
	box = mutabor::BoxFactory::Create(mutabor::Box0,0);
	connect(route,box);

	mutabor::CurrentTime.UseRealtime(true);
	out = new midicmnOutputDevice(_T("Test"));
	out->SetBendingRange(2);
	//out = new midicmnOutputDevice(3,_T("Test"));
	guard = out;

	connect(route,guard);
	route->SetOutputFrom (0);
	route->SetOutputTo (15);
	route->OutputAvoidDrumChannel (true);

	connect(route, in);

	CPPUNIT_ASSERT( in );
	in -> SetName(_T(SRCDIR) _T("/bug019010.mid"));


	// First check: Input device provides the correct delta times
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
	DEBUGLOG(midiio,_T("delta = %d"),delta);
	CPPUNIT_ASSERT(out->Check(_T(""),__LINE__,_T(__FILE__)));
	CPPUNIT_ASSERT(delta == 1086);

	delta = in -> PrepareNextEvent();
	DEBUGLOG(midiio,_T("delta = %d"),delta);
	CPPUNIT_ASSERT(out->Check(_T(""),__LINE__,_T(__FILE__)));
	CPPUNIT_ASSERT(delta == 1954800);

	delta = in -> PrepareNextEvent();
	DEBUGLOG(midiio,_T("delta = %d"),delta);
	CPPUNIT_ASSERT(out->Check(_T(""),__LINE__,_T(__FILE__)));
	CPPUNIT_ASSERT(delta == 14725074);

	delta = in -> PrepareNextEvent();
	DEBUGLOG(midiio,_T("delta = %d"),delta);
	CPPUNIT_ASSERT(out->Check(_T(""),__LINE__,_T(__FILE__)));
	CPPUNIT_ASSERT(delta == 130320);

	delta = in -> PrepareNextEvent();
	DEBUGLOG(midiio,_T("delta = %d"),delta);
	CPPUNIT_ASSERT(out->Check(_T(""),__LINE__,_T(__FILE__)));
	CPPUNIT_ASSERT(delta == 130200);

	delta = in -> PrepareNextEvent();
	DEBUGLOG(midiio,_T("delta = %d"),delta);
	CPPUNIT_ASSERT(out->Check(_T(""),__LINE__,_T(__FILE__)));
	CPPUNIT_ASSERT(delta == 4769600);

	delta = in -> PrepareNextEvent();
	DEBUGLOG(midiio,_T("delta = %d"),delta);
	CPPUNIT_ASSERT(out->Check(_T("0   0: 90 3c 7f\n"),
				  __LINE__,_T(__FILE__)));
	CPPUNIT_ASSERT(delta == 6287200);

	delta = in -> PrepareNextEvent();
	DEBUGLOG(midiio,_T("delta = %d"),delta);
	CPPUNIT_ASSERT(out->Check(_T(""),__LINE__,_T(__FILE__)));
	CPPUNIT_ASSERT(delta == 845040);

	delta = in -> PrepareNextEvent();
	DEBUGLOG(midiio,_T("delta = %d"),delta);
	CPPUNIT_ASSERT(out->Check(_T(""),__LINE__,_T(__FILE__)));
	CPPUNIT_ASSERT(delta == 120000);

	delta = in -> PrepareNextEvent();
	DEBUGLOG(midiio,_T("delta = %d"),delta);
	CPPUNIT_ASSERT(out->Check(_T(""),__LINE__,_T(__FILE__)));
	CPPUNIT_ASSERT(delta == 123960);

	delta = in -> PrepareNextEvent();
	DEBUGLOG(midiio,_T("delta = %d"),delta);
	CPPUNIT_ASSERT(out->Check(_T(""),__LINE__,_T(__FILE__)));
	CPPUNIT_ASSERT(delta == 3222960);

	delta = in -> PrepareNextEvent();
	DEBUGLOG(midiio,_T("delta = %d"),delta);
	CPPUNIT_ASSERT(out->Check(_T("\
0   1: 91 40 1f\n\
"),__LINE__,_T(__FILE__)));
	CPPUNIT_ASSERT(delta == 10330000);

	delta = in -> PrepareNextEvent();
	DEBUGLOG(midiio,_T("delta = %d"),delta);
	CPPUNIT_ASSERT(out->Check(_T("\
0   1: 81 40 40\n\
"),__LINE__,_T(__FILE__)));
	CPPUNIT_ASSERT(delta == 10330000);

	delta = in -> PrepareNextEvent();
	DEBUGLOG(midiio,_T("delta = %d"),delta);
	CPPUNIT_ASSERT(out->Check(_T("\
0   2: 92 43 3f\n\
"),__LINE__,_T(__FILE__)));
	CPPUNIT_ASSERT(delta == 10330000);

	delta = in -> PrepareNextEvent();
	DEBUGLOG(midiio,_T("delta = %d"),delta);
	CPPUNIT_ASSERT(out->Check(_T("0   2: 82 43 40\n"),__LINE__,_T(__FILE__)));
	CPPUNIT_ASSERT(delta == 7809480);

	delta = in -> PrepareNextEvent();
	DEBUGLOG(midiio,_T("delta = %d"),delta);
	CPPUNIT_ASSERT(out->Check(_T(""),__LINE__,_T(__FILE__)));
	CPPUNIT_ASSERT(delta == 6100000);

	delta = in -> PrepareNextEvent();
	DEBUGLOG(midiio,_T("delta = %d"),delta);
	CPPUNIT_ASSERT(out->Check(_T("\
0   3: 93 34 7f\n\
"),__LINE__,_T(__FILE__)));
	CPPUNIT_ASSERT(delta == 200000);

	delta = in -> PrepareNextEvent();
	DEBUGLOG(midiio,_T("delta = %d"),delta);
	CPPUNIT_ASSERT(out->Check(_T(""),__LINE__,_T(__FILE__)));
	CPPUNIT_ASSERT(delta == 146280);

	delta = in -> PrepareNextEvent();
	DEBUGLOG(midiio,_T("delta = %d"),delta);
	CPPUNIT_ASSERT(out->Check(_T(""),__LINE__,_T(__FILE__)));
	CPPUNIT_ASSERT(delta == 148080);

	delta = in -> PrepareNextEvent();
	DEBUGLOG(midiio,_T("delta = %d"),delta);
	CPPUNIT_ASSERT(out->Check(_T(""),__LINE__,_T(__FILE__)));
	CPPUNIT_ASSERT(delta == 150000);

	delta = in -> PrepareNextEvent();
	DEBUGLOG(midiio,_T("delta = %d"),delta);
	CPPUNIT_ASSERT(out->Check(_T(""),__LINE__,_T(__FILE__)));
	CPPUNIT_ASSERT(delta == 151800);

	delta = in -> PrepareNextEvent();
	DEBUGLOG(midiio,_T("delta = %d"),delta);
	CPPUNIT_ASSERT(out->Check(_T(""),__LINE__,_T(__FILE__)));
	CPPUNIT_ASSERT(delta == 153840);

	delta = in -> PrepareNextEvent();
	DEBUGLOG(midiio,_T("delta = %d"),delta);
	CPPUNIT_ASSERT(out->Check(_T(""),__LINE__,_T(__FILE__)));
	CPPUNIT_ASSERT(delta == 155760);

	delta = in -> PrepareNextEvent();
	DEBUGLOG(midiio,_T("delta = %d"),delta);
	CPPUNIT_ASSERT(out->Check(_T(""),__LINE__,_T(__FILE__)));
	CPPUNIT_ASSERT(delta == 157800);

	delta = in -> PrepareNextEvent();
	DEBUGLOG(midiio,_T("delta = %d"),delta);
	CPPUNIT_ASSERT(out->Check(_T(""),__LINE__,_T(__FILE__)));
	CPPUNIT_ASSERT(delta == 159960);

	delta = in -> PrepareNextEvent();
	DEBUGLOG(midiio,_T("delta = %d"),delta);
	CPPUNIT_ASSERT(out->Check(_T(""),__LINE__,_T(__FILE__)));
	CPPUNIT_ASSERT(delta == 12104960);

	delta = in -> PrepareNextEvent();
	DEBUGLOG(midiio,_T("delta = %d"),delta);
	CPPUNIT_ASSERT(out->Check(_T("0   3: 83 34 40\n"),__LINE__,_T(__FILE__)));
	CPPUNIT_ASSERT(delta == 13510000);

	delta = in -> PrepareNextEvent();
	DEBUGLOG(midiio,_T("delta = %d"),delta);
	CPPUNIT_ASSERT(out->Check(_T("0   0: 80 3c 7f\n"),__LINE__,_T(__FILE__)));
	CPPUNIT_ASSERT(delta == MUTABOR_NO_DELTA);

	in->Close();
	out->Close();
	CPPUNIT_ASSERT(out->Check(_T("0 ...closed.\n"),__LINE__,_T(__FILE__)));

}


void  InputMidiFileTest::testBug019010()
{
#ifdef DEBUG
//	debugFlags::flags.timer = true;
//	debugFlags::flags.midiio = true;
//	debugFlags::flags.midifile = true;
#endif

	// input device is set up during setUp
	CPPUNIT_ASSERT(mutabor::InputDeviceClass::GetDeviceList().size() == 1);
	CPPUNIT_ASSERT(mutabor::OutputDeviceClass::GetDeviceList().empty());
	CPPUNIT_ASSERT(mutabor::RouteClass::GetRouteList().empty());
	CPPUNIT_ASSERT(mutabor::BoxClass::GetBoxList().empty());

	mutabor::ScopedOutputDevice guard;
	midicmnOutputDevice * out;
	mutabor::ScopedBox box(NULL);
	mutabor::ScopedRoute  route;
	mutabor::ChannelData cd;

	route = mutabor::RouteFactory::Create();
	box = mutabor::BoxFactory::Create(mutabor::Box0,0);
	connect(route,box);

	mutabor::CurrentTime.UseRealtime(true);
	out = new midicmnOutputDevice(_T("Test"));
	out->SetBendingRange(2);
	//out = new midicmnOutputDevice(3,_T("Test"));
	guard = out;

	connect(route,guard);
	route->SetOutputFrom (0);
	route->SetOutputTo (15);
	route->OutputAvoidDrumChannel (true);

	connect(route, in);

	CPPUNIT_ASSERT( in );
	in -> SetName(_T(SRCDIR) _T("/bug019010.mid"));


	// First check: Input device provides the correct delta times
	mutabor::CurrentTime.UseRealtime(false);
	mutabor::CurrentTime = 0;

//	in -> Play(wxTHREAD_JOINABLE);
	mutabor::InputDeviceClass::BatchPlay();

	CPPUNIT_ASSERT(out->Check(_T("\
0 Opened...\n\
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
21711080   0: 90 3c 7f\n\
32310240   1: 91 40 1f\n\
42640240   1: 81 40 40\n\
52970240   2: 92 43 3f\n\
63300240   2: 82 43 40\n\
77209720   3: 93 34 7f\n\
90738200   3: 83 34 40\n\
104248200   0: 80 3c 7f\n\
104248200 ...closed.\n\
"),__LINE__,_T(__FILE__)));

	sleep(1);

	mutabor::InputDeviceClass::BatchPlay();

	CPPUNIT_ASSERT(out->Check(_T("\
0 Opened...\n\
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
21711080   0: 90 3c 7f\n\
32310240   1: 91 40 1f\n\
42640240   1: 81 40 40\n\
52970240   2: 92 43 3f\n\
63300240   2: 82 43 40\n\
77209720   3: 93 34 7f\n\
90738200   3: 83 34 40\n\
104248200   0: 80 3c 7f\n\
104248200 ...closed.\n\
"),__LINE__,_T(__FILE__)));
}


void  InputMidiFileTest::testControllerPlay()
{
#ifdef DEBUG
//	debugFlags::flags.timer = true;
//	debugFlags::flags.midiio = true;
//	debugFlags::flags.midifile = true;
#endif

	// input device is set up during setUp
	CPPUNIT_ASSERT(mutabor::InputDeviceClass::GetDeviceList().size() == 1);
	CPPUNIT_ASSERT(mutabor::OutputDeviceClass::GetDeviceList().empty());
	CPPUNIT_ASSERT(mutabor::RouteClass::GetRouteList().empty());
	CPPUNIT_ASSERT(mutabor::BoxClass::GetBoxList().empty());

	mutabor::ScopedOutputDevice guard;
	midicmnOutputDevice * out;
	mutabor::ScopedBox box(NULL);
	mutabor::ScopedRoute  route;
	mutabor::ChannelData cd;

	route = mutabor::RouteFactory::Create();
	box = mutabor::BoxFactory::Create(mutabor::Box0,0);
	connect(route,box);

	mutabor::CurrentTime.UseRealtime(true);
	out = new midicmnOutputDevice(_T("Test"));
	out->SetBendingRange(2);
	//out = new midicmnOutputDevice(3,_T("Test"));
	guard = out;

	connect(route,guard);
	route->SetOutputFrom (0);
	route->SetOutputTo (15);
	route->OutputAvoidDrumChannel (true);

	connect(route, in);

	CPPUNIT_ASSERT( in );
	in -> SetName(_T(SRCDIR) _T("/controller.mid"));


	// First check: Input device provides the correct delta times
	mutabor::CurrentTime.UseRealtime(false);
	mutabor::CurrentTime = 0;

//	in -> Play(wxTHREAD_JOINABLE);
	mutabor::InputDeviceClass::BatchPlay();

	CPPUNIT_ASSERT(out->Check(_T("\
noch nicht freigegeben\n\
0 Opened...\n\
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
0   0: 90 3c 7f\n\
1   0: b0 00 37\n\
2   0: b0 00 6e\n\
3   0: b0 00 00\n\
4   0: b0 00 25\n\
5   0: b0 01 5c\n\
6   0: b0 01 13\n\
7   0: b0 01 00\n\
8   0: b0 01 4a\n\
9   0: b0 02 01\n\
10   0: b0 02 38\n\
11   0: b0 02 00\n\
12   0: b0 02 6f\n\
13   0: b0 03 26\n\
14   0: b0 03 5d\n\
15   0: b0 03 00\n\
16   0: b0 03 14\n\
17   0: b0 04 4b\n\
18   0: b0 04 02\n\
19   0: b0 04 00\n\
20   0: b0 04 39\n\
21   0: b0 05 70\n\
22   0: b0 05 27\n\
23   0: b0 05 00\n\
24   0: b0 05 5e\n\
29   0: b0 07 3a\n\
30   0: b0 07 71\n\
31   0: b0 07 00\n\
32   0: b0 07 28\n\
33   0: b0 08 5f\n\
34   0: b0 08 16\n\
35   0: b0 08 00\n\
36   0: b0 08 4d\n\
37   0: b0 09 04\n\
38   0: b0 09 3b\n\
39   0: b0 09 00\n\
40   0: b0 09 72\n\
41   0: b0 0a 29\n\
42   0: b0 0a 60\n\
43   0: b0 0a 00\n\
44   0: b0 0a 17\n\
45   0: b0 0b 4e\n\
46   0: b0 0b 05\n\
47   0: b0 0b 00\n\
48   0: b0 0b 3c\n\
49   0: b0 0c 73\n\
50   0: b0 0c 2a\n\
51   0: b0 0c 00\n\
52   0: b0 0c 61\n\
53   0: b0 0d 18\n\
54   0: b0 0d 4f\n\
55   0: b0 0d 00\n\
56   0: b0 0d 06\n\
57   0: b0 0e 3d\n\
58   0: b0 0e 74\n\
59   0: b0 0e 00\n\
60   0: b0 0e 2b\n\
61   0: b0 0f 62\n\
62   0: b0 0f 19\n\
63   0: b0 0f 00\n\
64   0: b0 0f 50\n\
65   0: b0 10 07\n\
66   0: b0 10 3e\n\
67   0: b0 10 00\n\
68   0: b0 10 75\n\
69   0: b0 11 2c\n\
70   0: b0 11 63\n\
71   0: b0 11 00\n\
72   0: b0 11 1a\n\
73   0: b0 12 51\n\
74   0: b0 12 08\n\
75   0: b0 12 00\n\
76   0: b0 12 3f\n\
77   0: b0 13 76\n\
78   0: b0 13 2d\n\
79   0: b0 13 00\n\
80   0: b0 13 64\n\
81   0: b0 14 1b\n\
82   0: b0 14 52\n\
83   0: b0 14 00\n\
84   0: b0 14 09\n\
85   0: b0 15 40\n\
86   0: b0 15 77\n\
87   0: b0 15 00\n\
88   0: b0 15 2e\n\
89   0: b0 16 65\n\
90   0: b0 16 1c\n\
91   0: b0 16 00\n\
92   0: b0 16 53\n\
93   0: b0 17 0a\n\
94   0: b0 17 41\n\
95   0: b0 17 00\n\
96   0: b0 17 78\n\
97   0: b0 18 2f\n\
98   0: b0 18 66\n\
99   0: b0 18 00\n\
100   0: b0 18 1d\n\
101   0: b0 19 54\n\
102   0: b0 19 0b\n\
103   0: b0 19 00\n\
104   0: b0 19 42\n\
105   0: b0 1a 79\n\
106   0: b0 1a 30\n\
107   0: b0 1a 00\n\
108   0: b0 1a 67\n\
109   0: b0 1b 1e\n\
110   0: b0 1b 55\n\
111   0: b0 1b 00\n\
112   0: b0 1b 0c\n\
113   0: b0 1c 43\n\
114   0: b0 1c 7a\n\
115   0: b0 1c 00\n\
116   0: b0 1c 31\n\
117   0: b0 1d 68\n\
118   0: b0 1d 1f\n\
119   0: b0 1d 00\n\
120   0: b0 1d 56\n\
121   0: b0 1e 0d\n\
122   0: b0 1e 44\n\
123   0: b0 1e 00\n\
124   0: b0 1e 7b\n\
125   0: b0 1f 32\n\
126   0: b0 1f 69\n\
127   0: b0 1f 00\n\
128   0: b0 1f 20\n\
129   0: b0 20 57\n\
130   0: b0 20 0e\n\
131   0: b0 20 00\n\
132   0: b0 20 45\n\
133   0: b0 21 7c\n\
134   0: b0 21 33\n\
135   0: b0 21 00\n\
136   0: b0 21 6a\n\
137   0: b0 22 21\n\
138   0: b0 22 58\n\
139   0: b0 22 00\n\
140   0: b0 22 0f\n\
141   0: b0 23 46\n\
142   0: b0 23 7d\n\
143   0: b0 23 00\n\
144   0: b0 23 34\n\
145   0: b0 24 6b\n\
146   0: b0 24 22\n\
147   0: b0 24 00\n\
148   0: b0 24 59\n\
149   0: b0 25 10\n\
150   0: b0 25 47\n\
151   0: b0 25 00\n\
152   0: b0 25 7e\n\
157   0: b0 27 5a\n\
158   0: b0 27 11\n\
159   0: b0 27 00\n\
160   0: b0 27 48\n\
161   0: b0 28 7f\n\
162   0: b0 28 36\n\
163   0: b0 28 00\n\
164   0: b0 28 6d\n\
165   0: b0 29 24\n\
166   0: b0 29 5b\n\
167   0: b0 29 00\n\
168   0: b0 29 12\n\
169   0: b0 2a 49\n\
170   0: b0 2a 00\n\
172   0: b0 2a 37\n\
173   0: b0 2b 6e\n\
174   0: b0 2b 25\n\
175   0: b0 2b 00\n\
176   0: b0 2b 5c\n\
177   0: b0 2c 13\n\
178   0: b0 2c 4a\n\
179   0: b0 2c 00\n\
180   0: b0 2c 01\n\
181   0: b0 2d 38\n\
182   0: b0 2d 6f\n\
183   0: b0 2d 00\n\
184   0: b0 2d 26\n\
185   0: b0 2e 5d\n\
186   0: b0 2e 14\n\
187   0: b0 2e 00\n\
188   0: b0 2e 4b\n\
189   0: b0 2f 02\n\
190   0: b0 2f 39\n\
191   0: b0 2f 00\n\
192   0: b0 2f 70\n\
193   0: b0 30 27\n\
194   0: b0 30 5e\n\
195   0: b0 30 00\n\
196   0: b0 30 15\n\
197   0: b0 31 4c\n\
198   0: b0 31 03\n\
199   0: b0 31 00\n\
200   0: b0 31 3a\n\
201   0: b0 32 71\n\
202   0: b0 32 28\n\
203   0: b0 32 00\n\
204   0: b0 32 5f\n\
205   0: b0 33 16\n\
206   0: b0 33 4d\n\
207   0: b0 33 00\n\
208   0: b0 33 04\n\
209   0: b0 34 3b\n\
210   0: b0 34 72\n\
211   0: b0 34 00\n\
212   0: b0 34 29\n\
213   0: b0 35 60\n\
214   0: b0 35 17\n\
215   0: b0 35 00\n\
216   0: b0 35 4e\n\
217   0: b0 36 05\n\
218   0: b0 36 3c\n\
219   0: b0 36 00\n\
220   0: b0 36 73\n\
221   0: b0 37 2a\n\
222   0: b0 37 61\n\
223   0: b0 37 00\n\
224   0: b0 37 18\n\
225   0: b0 38 4f\n\
226   0: b0 38 06\n\
227   0: b0 38 00\n\
228   0: b0 38 3d\n\
229   0: b0 39 74\n\
230   0: b0 39 2b\n\
231   0: b0 39 00\n\
232   0: b0 39 62\n\
233   0: b0 3a 19\n\
234   0: b0 3a 50\n\
235   0: b0 3a 00\n\
236   0: b0 3a 07\n\
237   0: b0 3b 3e\n\
238   0: b0 3b 75\n\
239   0: b0 3b 00\n\
240   0: b0 3b 2c\n\
241   0: b0 3c 63\n\
242   0: b0 3c 1a\n\
243   0: b0 3c 00\n\
244   0: b0 3c 51\n\
245   0: b0 3d 08\n\
246   0: b0 3d 3f\n\
247   0: b0 3d 00\n\
248   0: b0 3d 76\n\
249   0: b0 3e 2d\n\
250   0: b0 3e 64\n\
251   0: b0 3e 00\n\
252   0: b0 3e 1b\n\
253   0: b0 3f 52\n\
254   0: b0 3f 09\n\
255   0: b0 3f 00\n\
256   0: b0 3f 40\n\
257   0: b0 40 77\n\
258   0: b0 40 2e\n\
259   0: b0 40 00\n\
260   0: b0 40 65\n\
261   0: b0 41 1c\n\
262   0: b0 41 53\n\
263   0: b0 41 00\n\
264   0: b0 41 0a\n\
265   0: b0 42 41\n\
266   0: b0 42 78\n\
267   0: b0 42 00\n\
268   0: b0 42 2f\n\
269   0: b0 43 66\n\
270   0: b0 43 1d\n\
271   0: b0 43 00\n\
272   0: b0 43 54\n\
273   0: b0 44 0b\n\
274   0: b0 44 42\n\
275   0: b0 44 00\n\
276   0: b0 44 79\n\
277   0: b0 45 30\n\
278   0: b0 45 67\n\
279   0: b0 45 00\n\
280   0: b0 45 1e\n\
281   0: b0 46 55\n\
282   0: b0 46 0c\n\
283   0: b0 46 00\n\
284   0: b0 46 43\n\
285   0: b0 47 7a\n\
286   0: b0 47 31\n\
287   0: b0 47 00\n\
288   0: b0 47 68\n\
289   0: b0 48 1f\n\
290   0: b0 48 56\n\
291   0: b0 48 00\n\
292   0: b0 48 0d\n\
293   0: b0 49 44\n\
294   0: b0 49 7b\n\
295   0: b0 49 00\n\
296   0: b0 49 32\n\
297   0: b0 4a 69\n\
298   0: b0 4a 20\n\
299   0: b0 4a 00\n\
300   0: b0 4a 57\n\
301   0: b0 4b 0e\n\
302   0: b0 4b 45\n\
303   0: b0 4b 00\n\
304   0: b0 4b 7c\n\
305   0: b0 4c 33\n\
306   0: b0 4c 6a\n\
307   0: b0 4c 00\n\
308   0: b0 4c 21\n\
309   0: b0 4d 58\n\
310   0: b0 4d 0f\n\
311   0: b0 4d 00\n\
312   0: b0 4d 46\n\
313   0: b0 4e 7d\n\
314   0: b0 4e 34\n\
315   0: b0 4e 00\n\
316   0: b0 4e 6b\n\
317   0: b0 4f 22\n\
318   0: b0 4f 59\n\
319   0: b0 4f 00\n\
320   0: b0 4f 10\n\
321   0: b0 50 47\n\
322   0: b0 50 7e\n\
323   0: b0 50 00\n\
324   0: b0 50 35\n\
325   0: b0 51 6c\n\
326   0: b0 51 23\n\
327   0: b0 51 00\n\
328   0: b0 51 5a\n\
329   0: b0 52 11\n\
330   0: b0 52 48\n\
331   0: b0 52 00\n\
332   0: b0 52 7f\n\
333   0: b0 53 36\n\
334   0: b0 53 6d\n\
335   0: b0 53 00\n\
336   0: b0 53 24\n\
337   0: b0 54 5b\n\
338   0: b0 54 12\n\
339   0: b0 54 00\n\
340   0: b0 54 49\n\
341   0: b0 55 00\n\
342   0: b0 55 37\n\
343   0: b0 55 00\n\
344   0: b0 55 6e\n\
345   0: b0 56 25\n\
346   0: b0 56 5c\n\
347   0: b0 56 00\n\
348   0: b0 56 13\n\
349   0: b0 57 4a\n\
350   0: b0 57 01\n\
351   0: b0 57 00\n\
352   0: b0 57 38\n\
353   0: b0 58 6f\n\
354   0: b0 58 26\n\
355   0: b0 58 00\n\
356   0: b0 58 5d\n\
357   0: b0 59 14\n\
358   0: b0 59 4b\n\
359   0: b0 59 00\n\
360   0: b0 59 02\n\
361   0: b0 5a 39\n\
362   0: b0 5a 70\n\
363   0: b0 5a 00\n\
364   0: b0 5a 27\n\
365   0: b0 5b 5e\n\
366   0: b0 5b 15\n\
367   0: b0 5b 00\n\
368   0: b0 5b 4c\n\
369   0: b0 5c 03\n\
370   0: b0 5c 3a\n\
371   0: b0 5c 00\n\
372   0: b0 5c 71\n\
373   0: b0 5d 28\n\
374   0: b0 5d 5f\n\
375   0: b0 5d 00\n\
376   0: b0 5d 16\n\
377   0: b0 5e 4d\n\
378   0: b0 5e 04\n\
379   0: b0 5e 00\n\
380   0: b0 5e 3b\n\
381   0: b0 5f 72\n\
382   0: b0 5f 29\n\
383   0: b0 5f 00\n\
384   0: b0 5f 60\n\
"),__LINE__,_T(__FILE__)));

}

bool OutputMidiFileTest::CheckOut(mutString s,int line, const mutChar * file) {
	wxMemoryOutputStream * stream = new wxMemoryOutputStream();
	out->Save(*stream);
	mutString *tmp = new mutString();
	*tmp = StreamToHex(stream->GetOutputStreamBuffer());
	delete stream;
	bool retval = (*tmp == s);
	if (!retval) {
		DEBUGLOG(always,_("\n\
%s:%d: Stream check failed.\n\
\n\
Expected:\n\
|-------------------\n\
%s\
|-------------------\n\
\n\
Got:\n\
|-------------------\n\
%s\
|-------------------\n\
\n\
"),
			 file,line,s.c_str(),tmp->c_str());
	}
	delete tmp;
	return retval;
}


void OutputMidiFileTest::setUp()
{
// change DEBUGA to DEBUG in case you need the debug output
#ifdef DEBUGA
//	debugFlags::flags.timer = true;
//	debugFlags::flags.midiio = true;
//	debugFlags::flags.midifile = true;
#else
#ifdef DEBUG
//	debugFlags::flags.timer = false;
//	debugFlags::flags.midiio = false;
//	debugFlags::flags.midifile = false;
#endif
#endif
//	std::clog << "Running setUp()" << std::endl;

	// input device is already configured
	CPPUNIT_ASSERT(!mutabor::InputDeviceClass::GetDeviceList().size() == 1);
	CPPUNIT_ASSERT(mutabor::OutputDeviceClass::GetDeviceList().empty());
	CPPUNIT_ASSERT(mutabor::RouteClass::GetRouteList().empty());
	CPPUNIT_ASSERT(mutabor::BoxClass::GetBoxList().empty());

	route = mutabor::RouteFactory::Create();
	box = mutabor::BoxFactory::Create(mutabor::Box0,0);
	connect(route, box);

	mutabor::CurrentTime.UseRealtime(true);
	guard =mutabor::DeviceFactory::CreateOutput(mutabor::DTMidiFile);
	out = static_cast<mutabor::OutputMidiFile *>(guard.get());
	out->SetName(_T("test_output.mid"));
	out->SetBendingRange(2);
	//out = new midicmnOutputDevice(3,_T("Test"));

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
	if (out)
		out -> Destroy();
	out = NULL;
	guard.reset();
	route -> Destroy();
	route.reset();
	box -> Destroy();
	box.reset();

	CPPUNIT_ASSERT(mutabor::InputDeviceClass::GetDeviceList().empty());
	CPPUNIT_ASSERT(mutabor::OutputDeviceClass::GetDeviceList().empty());
	CPPUNIT_ASSERT(mutabor::RouteClass::GetRouteList().empty());
	CPPUNIT_ASSERT(mutabor::BoxClass::GetBoxList().empty());
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


void  OutputMidiFileTest::testBatchPlay1()
{
#ifdef DEBUG
//	debugFlags::flags.timer = true;
//	debugFlags::flags.midiio = true;
#endif

	wxString CheckStr;
	wxString DataStr;
	mutabor::ScopedInputDevice inguard;
	inguard = (mutabor::DeviceFactory::CreateInput(mutabor::DTMidiFile));
	mutabor::InputMidiFile * in =
		static_cast<mutabor::InputMidiFile *> (inguard.get());
	CPPUNIT_ASSERT( in );

	connect(route, inguard);

	in -> SetName(_T(SRCDIR) _T("/bug019010.mid"));
	mutabor::CurrentTime.UseRealtime(false);
	mutabor::CurrentTime = 0;

	CPPUNIT_ASSERT((out -> Open()));


	DataStr = _T("\
 04 04 02 18 08 00 e0 00  40 00 b0 7a 00 00 b0 7d   …………………… @……z………}\n\
 00 00 b0 7f 00 00 b0 65  00 00 b0 64 00 00 b0 06   …………………e ………d…………\n\
 02 00 b0 26 00 00 e1 00  40 00 b1 7a 00 00 b1 7d   ………&………… @……z………}\n\
 00 00 b1 7f 00 00 b1 65  00 00 b1 64 00 00 b1 06   …………………e ………d…………\n\
 02 00 b1 26 00 00 e2 00  40 00 b2 7a 00 00 b2 7d   ………&………… @……z………}\n\
 00 00 b2 7f 00 00 b2 65  00 00 b2 64 00 00 b2 06   …………………e ………d…………\n\
 02 00 b2 26 00 00 e3 00  40 00 b3 7a 00 00 b3 7d   ………&………… @……z………}\n\
 00 00 b3 7f 00 00 b3 65  00 00 b3 64 00 00 b3 06   …………………e ………d…………\n\
 02 00 b3 26 00 00 e4 00  40 00 b4 7a 00 00 b4 7d   ………&………… @……z………}\n\
 00 00 b4 7f 00 00 b4 65  00 00 b4 64 00 00 b4 06   …………………e ………d…………\n\
 02 00 b4 26 00 00 e5 00  40 00 b5 7a 00 00 b5 7d   ………&………… @……z………}\n\
 00 00 b5 7f 00 00 b5 65  00 00 b5 64 00 00 b5 06   …………………e ………d…………\n\
 02 00 b5 26 00 00 e6 00  40 00 b6 7a 00 00 b6 7d   ………&………… @……z………}\n\
 00 00 b6 7f 00 00 b6 65  00 00 b6 64 00 00 b6 06   …………………e ………d…………\n\
 02 00 b6 26 00 00 e7 00  40 00 b7 7a 00 00 b7 7d   ………&………… @……z………}\n\
 00 00 b7 7f 00 00 b7 65  00 00 b7 64 00 00 b7 06   …………………e ………d…………\n\
 02 00 b7 26 00 00 e8 00  40 00 b8 7a 00 00 b8 7d   ………&………… @……z………}\n\
 00 00 b8 7f 00 00 b8 65  00 00 b8 64 00 00 b8 06   …………………e ………d…………\n\
 02 00 b8 26 00 00 e9 00  40 00 b9 7a 00 00 b9 7d   ………&………… @……z………}\n\
 00 00 b9 7f 00 00 b9 65  00 00 b9 64 00 00 b9 06   …………………e ………d…………\n\
 02 00 b9 26 00 00 ea 00  40 00 ba 7a 00 00 ba 7d   ………&………… @……z………}\n\
 00 00 ba 7f 00 00 ba 65  00 00 ba 64 00 00 ba 06   …………………e ………d…………\n\
 02 00 ba 26 00 00 eb 00  40 00 bb 7a 00 00 bb 7d   ………&………… @……z………}\n\
 00 00 bb 7f 00 00 bb 65  00 00 bb 64 00 00 bb 06   …………………e ………d…………\n\
 02 00 bb 26 00 00 ec 00  40 00 bc 7a 00 00 bc 7d   ………&………… @……z………}\n\
 00 00 bc 7f 00 00 bc 65  00 00 bc 64 00 00 bc 06   …………………e ………d…………\n\
 02 00 bc 26 00 00 ed 00  40 00 bd 7a 00 00 bd 7d   ………&………… @……z………}\n\
 00 00 bd 7f 00 00 bd 65  00 00 bd 64 00 00 bd 06   …………………e ………d…………\n\
 02 00 bd 26 00 00 ee 00  40 00 be 7a 00 00 be 7d   ………&………… @……z………}\n\
 00 00 be 7f 00 00 be 65  00 00 be 64 00 00 be 06   …………………e ………d…………\n\
 02 00 be 26 00 00 ef 00  40 00 bf 7a 00 00 bf 7d   ………&………… @……z………}\n\
 00 00 bf 7f 00 00 bf 65  00 00 bf 64 00 00 bf 06   …………………e ………d…………\n\
");

	CheckStr = _T(" 4d 54 68 64 00 00 00 06  00 00 00 01 e7 28 4d 54   MThd………… ……………(MT\n\
 72 6b 00 00 02 13 00 ff  51 03 07 d0 00 00 ff 58   rk……………… Q………………X\n")
		+ DataStr + _T(" 02 00 bf 26 00 00 ff 2f  00                        ………&………/ …\n");

	CPPUNIT_ASSERT(CheckOut(CheckStr,__LINE__,_T(__FILE__)));
	CPPUNIT_ASSERT(box->Open());
	CPPUNIT_ASSERT((in -> Open()));
	CPPUNIT_ASSERT(CheckOut(CheckStr,__LINE__,_T(__FILE__)));

	in -> Play();

	CPPUNIT_ASSERT(CheckOut(CheckStr,__LINE__,_T(__FILE__)));

	mutint64 delta = in -> PrepareNextEvent();
	DEBUGLOG(midiio,_T("delta = %d, Current time = %ld"),delta,mutabor::CurrentTime.Get());
	CPPUNIT_ASSERT(CheckOut(CheckStr,__LINE__,_T(__FILE__)));
	CPPUNIT_ASSERT(delta == 1086);
	mutabor::CurrentTime += delta;

	delta = in -> PrepareNextEvent();
	DEBUGLOG(midiio,_T("delta = %d, Current time = %ld"),delta,mutabor::CurrentTime.Get());
	CPPUNIT_ASSERT(CheckOut(CheckStr,__LINE__,_T(__FILE__)));
	CPPUNIT_ASSERT(delta == 1954800);
	mutabor::CurrentTime += delta;

	delta = in -> PrepareNextEvent();
	DEBUGLOG(midiio,_T("delta = %d, Current time = %ld"),delta,mutabor::CurrentTime.Get());
	CPPUNIT_ASSERT(CheckOut(CheckStr,__LINE__,_T(__FILE__)));
	CPPUNIT_ASSERT(delta == 14725074);
	mutabor::CurrentTime += delta;

	delta = in -> PrepareNextEvent();
	DEBUGLOG(midiio,_T("delta = %d, Current time = %ld"),delta,mutabor::CurrentTime.Get());
	CPPUNIT_ASSERT(CheckOut(CheckStr,__LINE__,_T(__FILE__)));
	CPPUNIT_ASSERT(delta == 130320);
	mutabor::CurrentTime += delta;

	delta = in -> PrepareNextEvent();
	DEBUGLOG(midiio,_T("delta = %d, Current time = %ld"),delta,mutabor::CurrentTime.Get());
	CPPUNIT_ASSERT(CheckOut(CheckStr,__LINE__,_T(__FILE__)));
	CPPUNIT_ASSERT(delta == 130200);
	mutabor::CurrentTime += delta;

	delta = in -> PrepareNextEvent();
	DEBUGLOG(midiio,_T("delta = %d, Current time = %ld"),delta,mutabor::CurrentTime.Get());
	CPPUNIT_ASSERT(CheckOut(CheckStr,__LINE__,_T(__FILE__)));
	CPPUNIT_ASSERT(delta == 4769600);
	mutabor::CurrentTime += delta;

	delta = in -> PrepareNextEvent();
	DEBUGLOG(midiio,_T("delta = %d, Current time = %ld"),delta,mutabor::CurrentTime.Get());

	CheckStr = _T(" 4d 54 68 64 00 00 00 06  00 00 00 01 e7 28 4d 54   MThd………… ……………(MT\n\
 72 6b 00 00 02 19 00 ff  51 03 07 d0 00 00 ff 58   rk……………… Q………………X\n")
		+ DataStr + _T(" 02 00 bf 26 00 81 a9 4f  90 3c 7f 00 ff 2f 00      ………&………O …<………/…\n");

	CPPUNIT_ASSERT(CheckOut(CheckStr,__LINE__,_T(__FILE__)));
	CPPUNIT_ASSERT(delta == 6287200);
	mutabor::CurrentTime += delta;

	delta = in -> PrepareNextEvent();
	DEBUGLOG(midiio,_T("delta = %d, Current time = %ld"),delta,mutabor::CurrentTime.Get());
	CPPUNIT_ASSERT(CheckOut(CheckStr,__LINE__,_T(__FILE__)));
	CPPUNIT_ASSERT(delta == 845040);
	mutabor::CurrentTime += delta;

	delta = in -> PrepareNextEvent();
	DEBUGLOG(midiio,_T("delta = %d, Current time = %ld"),delta,mutabor::CurrentTime.Get());
	CPPUNIT_ASSERT(CheckOut(CheckStr,__LINE__,_T(__FILE__)));
	CPPUNIT_ASSERT(delta == 120000);
	mutabor::CurrentTime += delta;

	delta = in -> PrepareNextEvent();
	DEBUGLOG(midiio,_T("delta = %d, Current time = %ld"),delta,mutabor::CurrentTime.Get());
	CPPUNIT_ASSERT(CheckOut(CheckStr,__LINE__,_T(__FILE__)));
	CPPUNIT_ASSERT(delta == 123960);
	mutabor::CurrentTime += delta;

	delta = in -> PrepareNextEvent();
	DEBUGLOG(midiio,_T("delta = %d, Current time = %ld"),delta,mutabor::CurrentTime.Get());
	CPPUNIT_ASSERT(CheckOut(CheckStr,__LINE__,_T(__FILE__)));
	CPPUNIT_ASSERT(delta == 3222960);
	mutabor::CurrentTime += delta;

	delta = in -> PrepareNextEvent();
	DEBUGLOG(midiio,_T("delta = %d, Current time = %ld"),delta,mutabor::CurrentTime.Get());


	DataStr += _T(" 02 00 bf 26 00 81 a9 4f  90 3c 7f d2 67 91 40 1f   ………&………O …<……g…@…\n");

	CheckStr = _T(" 4d 54 68 64 00 00 00 06  00 00 00 01 e7 28 4d 54   MThd………… ……………(MT\n\
 72 6b 00 00 02 1e 00 ff  51 03 07 d0 00 00 ff 58   rk……………… Q………………X\n")
		+ DataStr + _T(" 00 ff 2f 00                                        ……/…\n");

	CPPUNIT_ASSERT(CheckOut(CheckStr,__LINE__,_T(__FILE__)));
	CPPUNIT_ASSERT(delta == 10330000);
	mutabor::CurrentTime += delta;

	delta = in -> PrepareNextEvent();
	DEBUGLOG(midiio,_T("delta = %d, Current time = %ld"),delta,mutabor::CurrentTime.Get());

	CheckStr = _T(" 4d 54 68 64 00 00 00 06  00 00 00 01 e7 28 4d 54   MThd………… ……………(MT\n\
 72 6b 00 00 02 23 00 ff  51 03 07 d0 00 00 ff 58   rk………#…… Q………………X\n")
		+ DataStr + _T(" d0 5a 81 40 40 00 ff 2f  00                        …Z…@@……/ …\n");

	CPPUNIT_ASSERT(CheckOut(CheckStr,__LINE__,_T(__FILE__)));
	CPPUNIT_ASSERT(delta == 10330000);
	mutabor::CurrentTime += delta;

	delta = in -> PrepareNextEvent();
	DEBUGLOG(midiio,_T("delta = %d, Current time = %ld"),delta,mutabor::CurrentTime.Get());

	CheckStr = _T(" 4d 54 68 64 00 00 00 06  00 00 00 01 e7 28 4d 54   MThd………… ……………(MT\n\
 72 6b 00 00 02 28 00 ff  51 03 07 d0 00 00 ff 58   rk………(…… Q………………X\n")
		+ DataStr + _T(" d0 5a 81 40 40 d0 5a 92  43 3f 00 ff 2f 00         …Z…@@…Z… C?……/…\n");


	CPPUNIT_ASSERT(CheckOut(CheckStr,__LINE__,_T(__FILE__)));
	CPPUNIT_ASSERT(delta == 10330000);
	mutabor::CurrentTime += delta;

	delta = in -> PrepareNextEvent();
	DEBUGLOG(midiio,_T("delta = %d, Current time = %ld"),delta,mutabor::CurrentTime.Get());
	CheckStr = _T(" 4d 54 68 64 00 00 00 06  00 00 00 01 e7 28 4d 54   MThd………… ……………(MT\n\
 72 6b 00 00 02 2d 00 ff  51 03 07 d0 00 00 ff 58   rk………-…… Q………………X\n")
		+ DataStr + _T("\
 d0 5a 81 40 40 d0 5a 92  43 3f d0 5a 82 43 40 00   …Z…@@…Z… C?…Z…C@…\n\
 ff 2f 00                                           …/…\n");
	CPPUNIT_ASSERT(CheckOut(CheckStr,__LINE__,_T(__FILE__)));
	CPPUNIT_ASSERT(delta == 7809480);
	mutabor::CurrentTime += delta;

	delta = in -> PrepareNextEvent();
	DEBUGLOG(midiio,_T("delta = %d, Current time = %ld"),delta,mutabor::CurrentTime.Get());
	CPPUNIT_ASSERT(CheckOut(CheckStr,__LINE__,_T(__FILE__)));
	CPPUNIT_ASSERT(delta == 6100000);
	mutabor::CurrentTime += delta;

	delta = in -> PrepareNextEvent();
	DEBUGLOG(midiio,_T("delta = %d, Current time = %ld"),delta,mutabor::CurrentTime.Get());

	DataStr += _T(" d0 5a 81 40 40 d0 5a 92  43 3f d0 5a 82 43 40 ec   …Z…@@…Z… C?…Z…C@…\n");
	CheckStr = _T(" 4d 54 68 64 00 00 00 06  00 00 00 01 e7 28 4d 54   MThd………… ……………(MT\n\
 72 6b 00 00 02 32 00 ff  51 03 07 d0 00 00 ff 58   rk………2…… Q………………X\n")
		+ DataStr + _T(" 56 93 34 7f 00 ff 2f 00                            V…4………/…\n");
	CPPUNIT_ASSERT(CheckOut(CheckStr,__LINE__,_T(__FILE__)));
	CPPUNIT_ASSERT(delta == 200000);
	mutabor::CurrentTime += delta;

	delta = in -> PrepareNextEvent();
	DEBUGLOG(midiio,_T("delta = %d, Current time = %ld"),delta,mutabor::CurrentTime.Get());
	CPPUNIT_ASSERT(CheckOut(CheckStr,__LINE__,_T(__FILE__)));
	CPPUNIT_ASSERT(delta == 146280);
	mutabor::CurrentTime += delta;

	delta = in -> PrepareNextEvent();
	DEBUGLOG(midiio,_T("delta = %d, Current time = %ld"),delta,mutabor::CurrentTime.Get());
	CPPUNIT_ASSERT(CheckOut(CheckStr,__LINE__,_T(__FILE__)));
	CPPUNIT_ASSERT(delta == 148080);
	mutabor::CurrentTime += delta;

	delta = in -> PrepareNextEvent();
	DEBUGLOG(midiio,_T("delta = %d, Current time = %ld"),delta,mutabor::CurrentTime.Get());
	CPPUNIT_ASSERT(CheckOut(CheckStr,__LINE__,_T(__FILE__)));
	CPPUNIT_ASSERT(delta == 150000);
	mutabor::CurrentTime += delta;

	delta = in -> PrepareNextEvent();
	DEBUGLOG(midiio,_T("delta = %d, Current time = %ld"),delta,mutabor::CurrentTime.Get());
	CPPUNIT_ASSERT(CheckOut(CheckStr,__LINE__,_T(__FILE__)));
	CPPUNIT_ASSERT(delta == 151800);
	mutabor::CurrentTime += delta;

	delta = in -> PrepareNextEvent();
	DEBUGLOG(midiio,_T("delta = %d, Current time = %ld"),delta,mutabor::CurrentTime.Get());
	CPPUNIT_ASSERT(CheckOut(CheckStr,__LINE__,_T(__FILE__)));
	CPPUNIT_ASSERT(delta == 153840);
	mutabor::CurrentTime += delta;

	delta = in -> PrepareNextEvent();
	DEBUGLOG(midiio,_T("delta = %d, Current time = %ld"),delta,mutabor::CurrentTime.Get());
	CPPUNIT_ASSERT(CheckOut(CheckStr,__LINE__,_T(__FILE__)));
	CPPUNIT_ASSERT(delta == 155760);
	mutabor::CurrentTime += delta;

	delta = in -> PrepareNextEvent();
	DEBUGLOG(midiio,_T("delta = %d, Current time = %ld"),delta,mutabor::CurrentTime.Get());
	CPPUNIT_ASSERT(CheckOut(CheckStr,__LINE__,_T(__FILE__)));
	CPPUNIT_ASSERT(delta == 157800);
	mutabor::CurrentTime += delta;

	delta = in -> PrepareNextEvent();
	DEBUGLOG(midiio,_T("delta = %d, Current time = %ld"),delta,mutabor::CurrentTime.Get());
	CPPUNIT_ASSERT(CheckOut(CheckStr,__LINE__,_T(__FILE__)));
	CPPUNIT_ASSERT(delta == 159960);
	mutabor::CurrentTime += delta;

	delta = in -> PrepareNextEvent();
	DEBUGLOG(midiio,_T("delta = %d, Current time = %ld"),delta,mutabor::CurrentTime.Get());
	CPPUNIT_ASSERT(CheckOut(CheckStr,__LINE__,_T(__FILE__)));
	CPPUNIT_ASSERT(delta == 12104960);
	mutabor::CurrentTime += delta;

	delta = in -> PrepareNextEvent();
	DEBUGLOG(midiio,_T("delta = %d, Current time = %ld"),delta,mutabor::CurrentTime.Get());

	CheckStr = _T(" 4d 54 68 64 00 00 00 06  00 00 00 01 e7 28 4d 54   MThd………… ……………(MT\n\
 72 6b 00 00 02 37 00 ff  51 03 07 d0 00 00 ff 58   rk………7…… Q………………X\n")
		+ DataStr + _T(" 56 93 34 7f e9 58 83 34  40 00 ff 2f 00            V…4……X…4 @……/…\n");
	CPPUNIT_ASSERT(CheckOut(CheckStr,__LINE__,_T(__FILE__)));
	CPPUNIT_ASSERT(delta == 13510000);
	mutabor::CurrentTime += delta;

	delta = in -> PrepareNextEvent();
	DEBUGLOG(midiio,_T("delta = %d, Current time = %ld"),delta,mutabor::CurrentTime.Get());
	CheckStr = _T(" 4d 54 68 64 00 00 00 06  00 00 00 01 e7 28 4d 54   MThd………… ……………(MT\n\
 72 6b 00 00 02 3c 00 ff  51 03 07 d0 00 00 ff 58   rk………<…… Q………………X\n")
		+ DataStr + _T(" 56 93 34 7f e9 58 83 34  40 e9 46 80 3c 7f 00 ff   V…4……X…4 @…F…<………\n\
 2f 00                                              /…\n");
	CPPUNIT_ASSERT(CheckOut(CheckStr,__LINE__,_T(__FILE__)));
	CPPUNIT_ASSERT(delta == MUTABOR_NO_DELTA);



	in->Close();
	CPPUNIT_ASSERT(CheckOut(CheckStr,__LINE__,_T(__FILE__)));

	out->Close();
	CPPUNIT_ASSERT(CheckOut(CheckStr,__LINE__,_T(__FILE__)));



	// First check: Input device provides the correct delta times

	mutabor::CurrentTime.UseRealtime(false);
	mutabor::CurrentTime = 0;

	CPPUNIT_ASSERT( in );
	in -> SetName(_T("test_output.mid"));
	out -> SetName(_T("test_output2.mid"));


//	in -> Play(wxTHREAD_JOINABLE);
	mutabor::InputDeviceClass::BatchPlay();


	/** \todo Make the following line unneccessary: Implement caching of
	    system states */

	CheckStr = _T("\
 4d 54 68 64 00 00 00 06  00 00 00 01 e7 28 4d 54   MThd………… ……………(MT\n\
 72 6b 00 00 02 33 00 ff  51 03 07 d0 00 00 ff 58   rk………3…… Q………………X\n\
 04 04 02 18 08 00 e0 00  40 00 b0 7a 00 00 b0 7d   …………………… @……z………}\n\
 00 00 b0 7f 00 00 b0 65  00 00 b0 64 00 00 b0 06   …………………e ………d…………\n\
 02 00 b0 26 00 00 e1 00  40 00 b1 7a 00 00 b1 7d   ………&………… @……z………}\n\
 00 00 b1 7f 00 00 b1 65  00 00 b1 64 00 00 b1 06   …………………e ………d…………\n\
 02 00 b1 26 00 00 e2 00  40 00 b2 7a 00 00 b2 7d   ………&………… @……z………}\n\
 00 00 b2 7f 00 00 b2 65  00 00 b2 64 00 00 b2 06   …………………e ………d…………\n\
 02 00 b2 26 00 00 e3 00  40 00 b3 7a 00 00 b3 7d   ………&………… @……z………}\n\
 00 00 b3 7f 00 00 b3 65  00 00 b3 64 00 00 b3 06   …………………e ………d…………\n\
 02 00 b3 26 00 00 e4 00  40 00 b4 7a 00 00 b4 7d   ………&………… @……z………}\n\
 00 00 b4 7f 00 00 b4 65  00 00 b4 64 00 00 b4 06   …………………e ………d…………\n\
 02 00 b4 26 00 00 e5 00  40 00 b5 7a 00 00 b5 7d   ………&………… @……z………}\n\
 00 00 b5 7f 00 00 b5 65  00 00 b5 64 00 00 b5 06   …………………e ………d…………\n\
 02 00 b5 26 00 00 e6 00  40 00 b6 7a 00 00 b6 7d   ………&………… @……z………}\n\
 00 00 b6 7f 00 00 b6 65  00 00 b6 64 00 00 b6 06   …………………e ………d…………\n\
 02 00 b6 26 00 00 e7 00  40 00 b7 7a 00 00 b7 7d   ………&………… @……z………}\n\
 00 00 b7 7f 00 00 b7 65  00 00 b7 64 00 00 b7 06   …………………e ………d…………\n\
 02 00 b7 26 00 00 e8 00  40 00 b8 7a 00 00 b8 7d   ………&………… @……z………}\n\
 00 00 b8 7f 00 00 b8 65  00 00 b8 64 00 00 b8 06   …………………e ………d…………\n\
 02 00 b8 26 00 00 e9 00  40 00 b9 7a 00 00 b9 7d   ………&………… @……z………}\n\
 00 00 b9 7f 00 00 b9 65  00 00 b9 64 00 00 b9 06   …………………e ………d…………\n\
 02 00 b9 26 00 00 ea 00  40 00 ba 7a 00 00 ba 7d   ………&………… @……z………}\n\
 00 00 ba 7f 00 00 ba 65  00 00 ba 64 00 00 ba 06   …………………e ………d…………\n\
 02 00 ba 26 00 00 eb 00  40 00 bb 7a 00 00 bb 7d   ………&………… @……z………}\n\
 00 00 bb 7f 00 00 bb 65  00 00 bb 64 00 00 bb 06   …………………e ………d…………\n\
 02 00 bb 26 00 00 ec 00  40 00 bc 7a 00 00 bc 7d   ………&………… @……z………}\n\
 00 00 bc 7f 00 00 bc 65  00 00 bc 64 00 00 bc 06   …………………e ………d…………\n\
 02 00 bc 26 00 00 ed 00  40 00 bd 7a 00 00 bd 7d   ………&………… @……z………}\n\
 00 00 bd 7f 00 00 bd 65  00 00 bd 64 00 00 bd 06   …………………e ………d…………\n\
 02 00 bd 26 00 00 ee 00  40 00 be 7a 00 00 be 7d   ………&………… @……z………}\n\
 00 00 be 7f 00 00 be 65  00 00 be 64 00 00 be 06   …………………e ………d…………\n\
 02 00 be 26 00 00 ef 00  40 00 bf 7a 00 00 bf 7d   ………&………… @……z………}\n\
 00 00 bf 7f 00 00 bf 65  00 00 bf 64 00 00 bf 06   …………………e ………d…………\n\
 02 00 bf 26 00 00 90 3c  7f 00 91 40 1f 00 81 40   ………&………< ………@………@\n\
 40 00 92 43 3f 00 82 43  40 00 93 34 7f 00 83 34   @……C?……C @……4………4\n\
 40 00 80 3c 7f 00 ff 2f  00                        @……<………/ …\n");

	CPPUNIT_ASSERT(CheckOut(CheckStr,__LINE__,_T(__FILE__)));
}

///\}

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
	// hold pedal comes from the sustain parameter to the contstructor
	CPPUNIT_ASSERT(out->Check(_T("\
0   0: c0 4f\n\
0   0: 90 3c 7f\n\
"),__LINE__,_T(__FILE__)));

	CPPUNIT_ASSERT(delta == 49920);
	delta = in -> PrepareNextEvent();
	CPPUNIT_ASSERT(out->Check(_T("\
0   1: c1 4f\n\
0   1: 91 40 1f\n\
"),__LINE__,_T(__FILE__)));
	CPPUNIT_ASSERT(delta == 49920);
	delta = in -> PrepareNextEvent();
	CPPUNIT_ASSERT(out->Check(_T("\
0   1: 81 40 40\n\
0   2: c2 4f\n\
0   2: 92 43 3f\n\
"),__LINE__,_T(__FILE__)));
	CPPUNIT_ASSERT(delta == 49920);
	delta = in -> PrepareNextEvent();
	CPPUNIT_ASSERT(out->Check(_T("\
0   2: 82 43 40\n\
0   3: c3 4f\n\
0   3: 93 34 7f\n\
"),__LINE__,_T(__FILE__)));
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
	CPPUNIT_ASSERT(out->Check(_T("\
0   0: 90 3c 7f\n\
"),
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


void  InputMidiFileTest::testBankSelect()
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
	in -> SetName(_T(SRCDIR) _T("/bank_select.mid"));


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
0   0: 90 3c 7f\n\
1   0: b0 00 37\n\
3   1: b1 00 37\n\
3   1: 91 40 4f\n\
4   0: b0 00 6e\n\
4   1: b1 00 6e\n\
5   1: 81 40 4e\n\
6   2: b2 00 6e\n\
6   2: 92 40 4f\n\
7   0: b0 00 00\n\
7   2: b2 00 00\n\
8   2: 82 40 4e\n\
8   3: b3 00 00\n\
8   3: 93 40 4f\n\
10   0: b0 00 25\n\
10   3: b3 00 25\n\
11   3: 83 40 4e\n\
12   4: b4 00 25\n\
12   4: 94 40 4f\n\
13   0: b0 20 57\n\
13   4: b4 20 57\n\
14   4: 84 40 4e\n\
15   5: b5 00 25\n\
15   5: b5 20 57\n\
15   5: 95 40 4f\n\
16   0: b0 20 0e\n\
16   5: b5 20 0e\n\
17   5: 85 40 4e\n\
18   6: b6 00 25\n\
18   6: b6 20 0e\n\
18   6: 96 40 4f\n\
19   0: b0 20 00\n\
19   6: b6 20 00\n\
20   6: 86 40 4e\n\
21   7: b7 00 25\n\
21   7: b7 20 00\n\
21   7: 97 40 4f\n\
22   0: b0 20 45\n\
22   7: b7 20 45\n\
23   7: 87 40 4e\n\
24   8: b8 00 25\n\
24   8: b8 20 45\n\
24   8: 98 40 4f\n\
509   0: 80 3c 40\n\
509   8: 88 40 40\n\
509 ...closed.\n\
"),__LINE__,_T(__FILE__)));

}

void  InputMidiFileTest::testAllControllerOff()
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
	in -> SetName(_T(SRCDIR) _T("/all_controller_off.mid"));


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
0   0: 90 3c 7f\n\
1   0: b0 00 37\n\
16   0: b0 03 14\n\
29   0: b0 07 3a\n\
46   0: b0 0b 05\n\
101   0: b0 19 54\n\
489   0: b0 40 00\n\
489   0: b0 42 00\n\
489   0: b0 44 00\n\
489   0: b0 45 00\n\
489   0: 80 3c 7f\n\
490   1: b1 00 37\n\
490   1: 91 40 3f\n\
490   1: b1 07 3a\n\
490   1: b1 03 00\n\
490   1: b1 0b 7f\n\
490   1: b1 19 00\n\
492   1: 81 40 3e\n\
546 ...closed.\n\
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
393   0: b0 62 61\n\
394   0: b0 62 18\n\
395   0: b0 62 00\n\
396   0: b0 62 4f\n\
397   0: b0 63 06\n\
398   0: b0 63 3d\n\
399   0: b0 63 00\n\
400   0: b0 63 74\n\
401   0: b0 64 2b\n\
402   0: b0 64 62\n\
403   0: b0 64 00\n\
404   0: b0 64 19\n\
405   0: b0 65 50\n\
406   0: b0 65 07\n\
407   0: b0 65 00\n\
408   0: b0 65 3e\n\
409   0: b0 66 75\n\
410   0: b0 66 2c\n\
411   0: b0 66 00\n\
412   0: b0 66 63\n\
413   0: b0 67 1a\n\
414   0: b0 67 51\n\
415   0: b0 67 00\n\
416   0: b0 67 08\n\
417   0: b0 68 3f\n\
418   0: b0 68 76\n\
419   0: b0 68 00\n\
420   0: b0 68 2d\n\
421   0: b0 69 64\n\
422   0: b0 69 1b\n\
423   0: b0 69 00\n\
424   0: b0 69 52\n\
425   0: b0 6a 09\n\
426   0: b0 6a 40\n\
427   0: b0 6a 00\n\
428   0: b0 6a 77\n\
429   0: b0 6b 2e\n\
430   0: b0 6b 65\n\
431   0: b0 6b 00\n\
432   0: b0 6b 1c\n\
433   0: b0 6c 53\n\
434   0: b0 6c 0a\n\
435   0: b0 6c 00\n\
436   0: b0 6c 41\n\
437   0: b0 6d 78\n\
438   0: b0 6d 2f\n\
439   0: b0 6d 00\n\
440   0: b0 6d 66\n\
441   0: b0 6e 1d\n\
442   0: b0 6e 54\n\
443   0: b0 6e 00\n\
444   0: b0 6e 0b\n\
445   0: b0 6f 42\n\
446   0: b0 6f 79\n\
447   0: b0 6f 00\n\
448   0: b0 6f 30\n\
449   0: b0 70 67\n\
450   0: b0 70 1e\n\
451   0: b0 70 00\n\
452   0: b0 70 55\n\
453   0: b0 71 0c\n\
454   0: b0 71 43\n\
455   0: b0 71 00\n\
456   0: b0 71 7a\n\
457   0: b0 72 31\n\
458   0: b0 72 68\n\
459   0: b0 72 00\n\
460   0: b0 72 1f\n\
461   0: b0 73 56\n\
462   0: b0 73 0d\n\
463   0: b0 73 00\n\
464   0: b0 73 44\n\
465   0: b0 74 7b\n\
466   0: b0 74 32\n\
467   0: b0 74 00\n\
468   0: b0 74 69\n\
469   0: b0 75 20\n\
470   0: b0 75 57\n\
471   0: b0 75 00\n\
472   0: b0 75 0e\n\
473   0: b0 76 45\n\
474   0: b0 76 7c\n\
475   0: b0 76 00\n\
476   0: b0 76 33\n\
477   0: b0 77 6a\n\
478   0: b0 77 21\n\
479   0: b0 77 00\n\
480   0: b0 77 58\n\
481   0: b0 40 00\n\
481   0: b0 42 00\n\
481   0: b0 44 00\n\
481   0: b0 45 00\n\
481   0: 80 3c 7f\n\
482   1: b1 40 65\n\
482   1: b1 42 2f\n\
482   1: b1 44 79\n\
482   1: b1 45 1e\n\
482   1: b1 00 25\n\
482   1: b1 20 45\n\
482   1: 91 40 39\n\
482   1: b1 01 4a\n\
482   1: b1 02 6f\n\
482   1: b1 03 14\n\
482   1: b1 04 39\n\
482   1: b1 05 5e\n\
482   1: b1 07 28\n\
482   1: b1 08 4d\n\
482   1: b1 09 72\n\
482   1: b1 0a 17\n\
482   1: b1 0b 3c\n\
482   1: b1 0c 61\n\
482   1: b1 0d 06\n\
482   1: b1 0e 2b\n\
482   1: b1 0f 50\n\
482   1: b1 10 75\n\
482   1: b1 11 1a\n\
482   1: b1 12 3f\n\
482   1: b1 13 64\n\
482   1: b1 14 09\n\
482   1: b1 15 2e\n\
482   1: b1 16 53\n\
482   1: b1 17 78\n\
482   1: b1 18 1d\n\
482   1: b1 19 42\n\
482   1: b1 1a 67\n\
482   1: b1 1b 0c\n\
482   1: b1 1c 31\n\
482   1: b1 1d 56\n\
482   1: b1 1e 7b\n\
482   1: b1 1f 20\n\
482   1: b1 21 6a\n\
482   1: b1 22 0f\n\
482   1: b1 23 34\n\
482   1: b1 24 59\n\
482   1: b1 25 7e\n\
482   1: b1 27 48\n\
482   1: b1 28 6d\n\
482   1: b1 29 12\n\
482   1: b1 2a 37\n\
482   1: b1 2b 5c\n\
482   1: b1 2c 01\n\
482   1: b1 2d 26\n\
482   1: b1 2e 4b\n\
482   1: b1 2f 70\n\
482   1: b1 30 15\n\
482   1: b1 31 3a\n\
482   1: b1 32 5f\n\
482   1: b1 33 04\n\
482   1: b1 34 29\n\
482   1: b1 35 4e\n\
482   1: b1 36 73\n\
482   1: b1 37 18\n\
482   1: b1 38 3d\n\
482   1: b1 39 62\n\
482   1: b1 3a 07\n\
482   1: b1 3b 2c\n\
482   1: b1 3c 51\n\
482   1: b1 3d 76\n\
482   1: b1 3e 1b\n\
482   1: b1 3f 40\n\
482   1: b1 41 0a\n\
482   1: b1 43 54\n\
482   1: b1 46 43\n\
482   1: b1 47 68\n\
482   1: b1 48 0d\n\
482   1: b1 49 32\n\
482   1: b1 4a 57\n\
482   1: b1 4b 7c\n\
482   1: b1 4c 21\n\
482   1: b1 4d 46\n\
482   1: b1 4e 6b\n\
482   1: b1 4f 10\n\
482   1: b1 50 35\n\
482   1: b1 51 5a\n\
482   1: b1 52 7f\n\
482   1: b1 53 24\n\
482   1: b1 54 49\n\
482   1: b1 55 6e\n\
482   1: b1 56 13\n\
482   1: b1 57 38\n\
482   1: b1 58 5d\n\
482   1: b1 59 02\n\
482   1: b1 5a 27\n\
482   1: b1 5b 4c\n\
482   1: b1 5c 71\n\
482   1: b1 5d 16\n\
482   1: b1 5e 3b\n\
482   1: b1 5f 60\n\
482   1: b1 62 4f\n\
482   1: b1 63 74\n\
482   1: b1 64 19\n\
482   1: b1 65 3e\n\
482   1: b1 66 63\n\
482   1: b1 67 08\n\
482   1: b1 68 2d\n\
482   1: b1 69 52\n\
482   1: b1 6a 77\n\
482   1: b1 6b 1c\n\
482   1: b1 6c 41\n\
482   1: b1 6d 66\n\
482   1: b1 6e 0b\n\
482   1: b1 6f 30\n\
482   1: b1 70 55\n\
482   1: b1 71 7a\n\
482   1: b1 72 1f\n\
482   1: b1 73 44\n\
482   1: b1 74 69\n\
482   1: b1 75 0e\n\
482   1: b1 76 33\n\
482   1: b1 77 58\n\
483   1: b1 40 00\n\
483   1: b1 42 00\n\
483   1: b1 44 00\n\
483   1: b1 45 00\n\
483   1: 81 40 39\n\
484   2: b2 40 65\n\
484   2: b2 42 2f\n\
484   2: b2 44 79\n\
484   2: b2 45 1e\n\
484   2: b2 00 25\n\
484   2: b2 20 45\n\
484   2: 92 40 3b\n\
484   2: b2 01 4a\n\
484   2: b2 02 6f\n\
484   2: b2 03 14\n\
484   2: b2 04 39\n\
484   2: b2 05 5e\n\
484   2: b2 07 28\n\
484   2: b2 08 4d\n\
484   2: b2 09 72\n\
484   2: b2 0a 17\n\
484   2: b2 0b 3c\n\
484   2: b2 0c 61\n\
484   2: b2 0d 06\n\
484   2: b2 0e 2b\n\
484   2: b2 0f 50\n\
484   2: b2 10 75\n\
484   2: b2 11 1a\n\
484   2: b2 12 3f\n\
484   2: b2 13 64\n\
484   2: b2 14 09\n\
484   2: b2 15 2e\n\
484   2: b2 16 53\n\
484   2: b2 17 78\n\
484   2: b2 18 1d\n\
484   2: b2 19 42\n\
484   2: b2 1a 67\n\
484   2: b2 1b 0c\n\
484   2: b2 1c 31\n\
484   2: b2 1d 56\n\
484   2: b2 1e 7b\n\
484   2: b2 1f 20\n\
484   2: b2 21 6a\n\
484   2: b2 22 0f\n\
484   2: b2 23 34\n\
484   2: b2 24 59\n\
484   2: b2 25 7e\n\
484   2: b2 27 48\n\
484   2: b2 28 6d\n\
484   2: b2 29 12\n\
484   2: b2 2a 37\n\
484   2: b2 2b 5c\n\
484   2: b2 2c 01\n\
484   2: b2 2d 26\n\
484   2: b2 2e 4b\n\
484   2: b2 2f 70\n\
484   2: b2 30 15\n\
484   2: b2 31 3a\n\
484   2: b2 32 5f\n\
484   2: b2 33 04\n\
484   2: b2 34 29\n\
484   2: b2 35 4e\n\
484   2: b2 36 73\n\
484   2: b2 37 18\n\
484   2: b2 38 3d\n\
484   2: b2 39 62\n\
484   2: b2 3a 07\n\
484   2: b2 3b 2c\n\
484   2: b2 3c 51\n\
484   2: b2 3d 76\n\
484   2: b2 3e 1b\n\
484   2: b2 3f 40\n\
484   2: b2 41 0a\n\
484   2: b2 43 54\n\
484   2: b2 46 43\n\
484   2: b2 47 68\n\
484   2: b2 48 0d\n\
484   2: b2 49 32\n\
484   2: b2 4a 57\n\
484   2: b2 4b 7c\n\
484   2: b2 4c 21\n\
484   2: b2 4d 46\n\
484   2: b2 4e 6b\n\
484   2: b2 4f 10\n\
484   2: b2 50 35\n\
484   2: b2 51 5a\n\
484   2: b2 52 7f\n\
484   2: b2 53 24\n\
484   2: b2 54 49\n\
484   2: b2 55 6e\n\
484   2: b2 56 13\n\
484   2: b2 57 38\n\
484   2: b2 58 5d\n\
484   2: b2 59 02\n\
484   2: b2 5a 27\n\
484   2: b2 5b 4c\n\
484   2: b2 5c 71\n\
484   2: b2 5d 16\n\
484   2: b2 5e 3b\n\
484   2: b2 5f 60\n\
484   2: b2 62 4f\n\
484   2: b2 63 74\n\
484   2: b2 64 19\n\
484   2: b2 65 3e\n\
484   2: b2 66 63\n\
484   2: b2 67 08\n\
484   2: b2 68 2d\n\
484   2: b2 69 52\n\
484   2: b2 6a 77\n\
484   2: b2 6b 1c\n\
484   2: b2 6c 41\n\
484   2: b2 6d 66\n\
484   2: b2 6e 0b\n\
484   2: b2 6f 30\n\
484   2: b2 70 55\n\
484   2: b2 71 7a\n\
484   2: b2 72 1f\n\
484   2: b2 73 44\n\
484   2: b2 74 69\n\
484   2: b2 75 0e\n\
484   2: b2 76 33\n\
484   2: b2 77 58\n\
485   2: b2 40 00\n\
485   2: b2 42 00\n\
485   2: b2 44 00\n\
485   2: b2 45 00\n\
485   2: 82 40 3b\n\
486   3: b3 40 65\n\
486   3: b3 42 2f\n\
486   3: b3 44 79\n\
486   3: b3 45 1e\n\
486   3: b3 00 25\n\
486   3: b3 20 45\n\
486   3: 93 40 3d\n\
486   3: b3 01 4a\n\
486   3: b3 02 6f\n\
486   3: b3 03 14\n\
486   3: b3 04 39\n\
486   3: b3 05 5e\n\
486   3: b3 07 28\n\
486   3: b3 08 4d\n\
486   3: b3 09 72\n\
486   3: b3 0a 17\n\
486   3: b3 0b 3c\n\
486   3: b3 0c 61\n\
486   3: b3 0d 06\n\
486   3: b3 0e 2b\n\
486   3: b3 0f 50\n\
486   3: b3 10 75\n\
486   3: b3 11 1a\n\
486   3: b3 12 3f\n\
486   3: b3 13 64\n\
486   3: b3 14 09\n\
486   3: b3 15 2e\n\
486   3: b3 16 53\n\
486   3: b3 17 78\n\
486   3: b3 18 1d\n\
486   3: b3 19 42\n\
486   3: b3 1a 67\n\
486   3: b3 1b 0c\n\
486   3: b3 1c 31\n\
486   3: b3 1d 56\n\
486   3: b3 1e 7b\n\
486   3: b3 1f 20\n\
486   3: b3 21 6a\n\
486   3: b3 22 0f\n\
486   3: b3 23 34\n\
486   3: b3 24 59\n\
486   3: b3 25 7e\n\
486   3: b3 27 48\n\
486   3: b3 28 6d\n\
486   3: b3 29 12\n\
486   3: b3 2a 37\n\
486   3: b3 2b 5c\n\
486   3: b3 2c 01\n\
486   3: b3 2d 26\n\
486   3: b3 2e 4b\n\
486   3: b3 2f 70\n\
486   3: b3 30 15\n\
486   3: b3 31 3a\n\
486   3: b3 32 5f\n\
486   3: b3 33 04\n\
486   3: b3 34 29\n\
486   3: b3 35 4e\n\
486   3: b3 36 73\n\
486   3: b3 37 18\n\
486   3: b3 38 3d\n\
486   3: b3 39 62\n\
486   3: b3 3a 07\n\
486   3: b3 3b 2c\n\
486   3: b3 3c 51\n\
486   3: b3 3d 76\n\
486   3: b3 3e 1b\n\
486   3: b3 3f 40\n\
486   3: b3 41 0a\n\
486   3: b3 43 54\n\
486   3: b3 46 43\n\
486   3: b3 47 68\n\
486   3: b3 48 0d\n\
486   3: b3 49 32\n\
486   3: b3 4a 57\n\
486   3: b3 4b 7c\n\
486   3: b3 4c 21\n\
486   3: b3 4d 46\n\
486   3: b3 4e 6b\n\
486   3: b3 4f 10\n\
486   3: b3 50 35\n\
486   3: b3 51 5a\n\
486   3: b3 52 7f\n\
486   3: b3 53 24\n\
486   3: b3 54 49\n\
486   3: b3 55 6e\n\
486   3: b3 56 13\n\
486   3: b3 57 38\n\
486   3: b3 58 5d\n\
486   3: b3 59 02\n\
486   3: b3 5a 27\n\
486   3: b3 5b 4c\n\
486   3: b3 5c 71\n\
486   3: b3 5d 16\n\
486   3: b3 5e 3b\n\
486   3: b3 5f 60\n\
486   3: b3 62 4f\n\
486   3: b3 63 74\n\
486   3: b3 64 19\n\
486   3: b3 65 3e\n\
486   3: b3 66 63\n\
486   3: b3 67 08\n\
486   3: b3 68 2d\n\
486   3: b3 69 52\n\
486   3: b3 6a 77\n\
486   3: b3 6b 1c\n\
486   3: b3 6c 41\n\
486   3: b3 6d 66\n\
486   3: b3 6e 0b\n\
486   3: b3 6f 30\n\
486   3: b3 70 55\n\
486   3: b3 71 7a\n\
486   3: b3 72 1f\n\
486   3: b3 73 44\n\
486   3: b3 74 69\n\
486   3: b3 75 0e\n\
486   3: b3 76 33\n\
486   3: b3 77 58\n\
487   3: b3 40 00\n\
487   3: b3 42 00\n\
487   3: b3 44 00\n\
487   3: b3 45 00\n\
487   3: 83 40 3d\n\
488   4: b4 40 65\n\
488   4: b4 42 2f\n\
488   4: b4 44 79\n\
488   4: b4 45 1e\n\
488   4: b4 00 25\n\
488   4: b4 20 45\n\
488   4: 94 40 3f\n\
488   4: b4 01 4a\n\
488   4: b4 02 6f\n\
488   4: b4 03 14\n\
488   4: b4 04 39\n\
488   4: b4 05 5e\n\
488   4: b4 07 28\n\
488   4: b4 08 4d\n\
488   4: b4 09 72\n\
488   4: b4 0a 17\n\
488   4: b4 0b 3c\n\
488   4: b4 0c 61\n\
488   4: b4 0d 06\n\
488   4: b4 0e 2b\n\
488   4: b4 0f 50\n\
488   4: b4 10 75\n\
488   4: b4 11 1a\n\
488   4: b4 12 3f\n\
488   4: b4 13 64\n\
488   4: b4 14 09\n\
488   4: b4 15 2e\n\
488   4: b4 16 53\n\
488   4: b4 17 78\n\
488   4: b4 18 1d\n\
488   4: b4 19 42\n\
488   4: b4 1a 67\n\
488   4: b4 1b 0c\n\
488   4: b4 1c 31\n\
488   4: b4 1d 56\n\
488   4: b4 1e 7b\n\
488   4: b4 1f 20\n\
488   4: b4 21 6a\n\
488   4: b4 22 0f\n\
488   4: b4 23 34\n\
488   4: b4 24 59\n\
488   4: b4 25 7e\n\
488   4: b4 27 48\n\
488   4: b4 28 6d\n\
488   4: b4 29 12\n\
488   4: b4 2a 37\n\
488   4: b4 2b 5c\n\
488   4: b4 2c 01\n\
488   4: b4 2d 26\n\
488   4: b4 2e 4b\n\
488   4: b4 2f 70\n\
488   4: b4 30 15\n\
488   4: b4 31 3a\n\
488   4: b4 32 5f\n\
488   4: b4 33 04\n\
488   4: b4 34 29\n\
488   4: b4 35 4e\n\
488   4: b4 36 73\n\
488   4: b4 37 18\n\
488   4: b4 38 3d\n\
488   4: b4 39 62\n\
488   4: b4 3a 07\n\
488   4: b4 3b 2c\n\
488   4: b4 3c 51\n\
488   4: b4 3d 76\n\
488   4: b4 3e 1b\n\
488   4: b4 3f 40\n\
488   4: b4 41 0a\n\
488   4: b4 43 54\n\
488   4: b4 46 43\n\
488   4: b4 47 68\n\
488   4: b4 48 0d\n\
488   4: b4 49 32\n\
488   4: b4 4a 57\n\
488   4: b4 4b 7c\n\
488   4: b4 4c 21\n\
488   4: b4 4d 46\n\
488   4: b4 4e 6b\n\
488   4: b4 4f 10\n\
488   4: b4 50 35\n\
488   4: b4 51 5a\n\
488   4: b4 52 7f\n\
488   4: b4 53 24\n\
488   4: b4 54 49\n\
488   4: b4 55 6e\n\
488   4: b4 56 13\n\
488   4: b4 57 38\n\
488   4: b4 58 5d\n\
488   4: b4 59 02\n\
488   4: b4 5a 27\n\
488   4: b4 5b 4c\n\
488   4: b4 5c 71\n\
488   4: b4 5d 16\n\
488   4: b4 5e 3b\n\
488   4: b4 5f 60\n\
488   4: b4 62 4f\n\
488   4: b4 63 74\n\
488   4: b4 64 19\n\
488   4: b4 65 3e\n\
488   4: b4 66 63\n\
488   4: b4 67 08\n\
488   4: b4 68 2d\n\
488   4: b4 69 52\n\
488   4: b4 6a 77\n\
488   4: b4 6b 1c\n\
488   4: b4 6c 41\n\
488   4: b4 6d 66\n\
488   4: b4 6e 0b\n\
488   4: b4 6f 30\n\
488   4: b4 70 55\n\
488   4: b4 71 7a\n\
488   4: b4 72 1f\n\
488   4: b4 73 44\n\
488   4: b4 74 69\n\
488   4: b4 75 0e\n\
488   4: b4 76 33\n\
488   4: b4 77 58\n\
489   4: b4 40 00\n\
489   4: b4 42 00\n\
489   4: b4 44 00\n\
489   4: b4 45 00\n\
489   4: 84 40 3f\n\
490   5: b5 40 00\n\
490   5: b5 42 00\n\
490   5: b5 44 00\n\
490   5: b5 45 00\n\
490   5: b5 00 25\n\
490   5: b5 20 45\n\
490   5: 95 40 3f\n\
490   5: b5 07 28\n\
490   5: b5 0a 17\n\
490   5: b5 46 43\n\
490   5: b5 47 68\n\
490   5: b5 48 0d\n\
490   5: b5 49 32\n\
490   5: b5 4a 57\n\
490   5: b5 4b 7c\n\
490   5: b5 4c 21\n\
490   5: b5 4d 46\n\
490   5: b5 4e 6b\n\
490   5: b5 4f 10\n\
490   5: b5 5b 4c\n\
490   5: b5 5c 71\n\
490   5: b5 5d 16\n\
490   5: b5 5e 3b\n\
490   5: b5 5f 60\n\
490   5: b5 01 00\n\
490   5: b5 02 00\n\
490   5: b5 03 00\n\
490   5: b5 04 00\n\
490   5: b5 05 00\n\
490   5: b5 08 40\n\
490   5: b5 09 00\n\
490   5: b5 0b 7f\n\
490   5: b5 0c 00\n\
490   5: b5 0d 00\n\
490   5: b5 0e 00\n\
490   5: b5 0f 00\n\
490   5: b5 10 00\n\
490   5: b5 11 00\n\
490   5: b5 12 00\n\
490   5: b5 13 00\n\
490   5: b5 14 00\n\
490   5: b5 15 00\n\
490   5: b5 16 00\n\
490   5: b5 17 00\n\
490   5: b5 18 00\n\
490   5: b5 19 00\n\
490   5: b5 1a 00\n\
490   5: b5 1b 00\n\
490   5: b5 1c 00\n\
490   5: b5 1d 00\n\
490   5: b5 1e 00\n\
490   5: b5 1f 00\n\
490   5: b5 21 00\n\
490   5: b5 22 00\n\
490   5: b5 23 00\n\
490   5: b5 24 00\n\
490   5: b5 25 00\n\
490   5: b5 27 00\n\
490   5: b5 28 00\n\
490   5: b5 29 00\n\
490   5: b5 2a 00\n\
490   5: b5 2b 7f\n\
490   5: b5 2c 00\n\
490   5: b5 2d 00\n\
490   5: b5 2e 00\n\
490   5: b5 2f 00\n\
490   5: b5 30 00\n\
490   5: b5 31 00\n\
490   5: b5 32 00\n\
490   5: b5 33 00\n\
490   5: b5 34 00\n\
490   5: b5 35 00\n\
490   5: b5 36 00\n\
490   5: b5 37 00\n\
490   5: b5 38 00\n\
490   5: b5 39 00\n\
490   5: b5 3a 00\n\
490   5: b5 3b 00\n\
490   5: b5 3c 00\n\
490   5: b5 3d 00\n\
490   5: b5 3e 00\n\
490   5: b5 3f 00\n\
490   5: b5 41 00\n\
490   5: b5 43 00\n\
490   5: b5 50 00\n\
490   5: b5 51 00\n\
490   5: b5 52 00\n\
490   5: b5 53 00\n\
490   5: b5 54 00\n\
490   5: b5 55 00\n\
490   5: b5 56 00\n\
490   5: b5 57 00\n\
490   5: b5 58 00\n\
490   5: b5 59 00\n\
490   5: b5 5a 00\n\
490   5: b5 62 7f\n\
490   5: b5 63 7f\n\
490   5: b5 64 7f\n\
490   5: b5 65 7f\n\
490   5: b5 66 00\n\
490   5: b5 67 00\n\
490   5: b5 68 00\n\
490   5: b5 69 00\n\
490   5: b5 6a 00\n\
490   5: b5 6b 00\n\
490   5: b5 6c 00\n\
490   5: b5 6d 00\n\
490   5: b5 6e 00\n\
490   5: b5 6f 00\n\
490   5: b5 70 00\n\
490   5: b5 71 00\n\
490   5: b5 72 00\n\
490   5: b5 73 00\n\
490   5: b5 74 00\n\
490   5: b5 75 00\n\
490   5: b5 76 00\n\
490   5: b5 77 00\n\
491   5: 85 40 3f\n\
492   6: b6 40 00\n\
492   6: b6 42 00\n\
492   6: b6 44 00\n\
492   6: b6 45 00\n\
492   6: b6 00 25\n\
492   6: b6 20 45\n\
492   6: 96 40 3f\n\
492   6: b6 07 28\n\
492   6: b6 0a 17\n\
492   6: b6 46 43\n\
492   6: b6 47 68\n\
492   6: b6 48 0d\n\
492   6: b6 49 32\n\
492   6: b6 4a 57\n\
492   6: b6 4b 7c\n\
492   6: b6 4c 21\n\
492   6: b6 4d 46\n\
492   6: b6 4e 6b\n\
492   6: b6 4f 10\n\
492   6: b6 5b 4c\n\
492   6: b6 5c 71\n\
492   6: b6 5d 16\n\
492   6: b6 5e 3b\n\
492   6: b6 5f 60\n\
492   6: b6 01 00\n\
492   6: b6 02 00\n\
492   6: b6 03 00\n\
492   6: b6 04 00\n\
492   6: b6 05 00\n\
492   6: b6 08 40\n\
492   6: b6 09 00\n\
492   6: b6 0b 7f\n\
492   6: b6 0c 00\n\
492   6: b6 0d 00\n\
492   6: b6 0e 00\n\
492   6: b6 0f 00\n\
492   6: b6 10 00\n\
492   6: b6 11 00\n\
492   6: b6 12 00\n\
492   6: b6 13 00\n\
492   6: b6 14 00\n\
492   6: b6 15 00\n\
492   6: b6 16 00\n\
492   6: b6 17 00\n\
492   6: b6 18 00\n\
492   6: b6 19 00\n\
492   6: b6 1a 00\n\
492   6: b6 1b 00\n\
492   6: b6 1c 00\n\
492   6: b6 1d 00\n\
492   6: b6 1e 00\n\
492   6: b6 1f 00\n\
492   6: b6 21 00\n\
492   6: b6 22 00\n\
492   6: b6 23 00\n\
492   6: b6 24 00\n\
492   6: b6 25 00\n\
492   6: b6 27 00\n\
492   6: b6 28 00\n\
492   6: b6 29 00\n\
492   6: b6 2a 00\n\
492   6: b6 2b 7f\n\
492   6: b6 2c 00\n\
492   6: b6 2d 00\n\
492   6: b6 2e 00\n\
492   6: b6 2f 00\n\
492   6: b6 30 00\n\
492   6: b6 31 00\n\
492   6: b6 32 00\n\
492   6: b6 33 00\n\
492   6: b6 34 00\n\
492   6: b6 35 00\n\
492   6: b6 36 00\n\
492   6: b6 37 00\n\
492   6: b6 38 00\n\
492   6: b6 39 00\n\
492   6: b6 3a 00\n\
492   6: b6 3b 00\n\
492   6: b6 3c 00\n\
492   6: b6 3d 00\n\
492   6: b6 3e 00\n\
492   6: b6 3f 00\n\
492   6: b6 41 00\n\
492   6: b6 43 00\n\
492   6: b6 50 00\n\
492   6: b6 51 00\n\
492   6: b6 52 00\n\
492   6: b6 53 00\n\
492   6: b6 54 00\n\
492   6: b6 55 00\n\
492   6: b6 56 00\n\
492   6: b6 57 00\n\
492   6: b6 58 00\n\
492   6: b6 59 00\n\
492   6: b6 5a 00\n\
492   6: b6 62 7f\n\
492   6: b6 63 7f\n\
492   6: b6 64 7f\n\
492   6: b6 65 7f\n\
492   6: b6 66 00\n\
492   6: b6 67 00\n\
492   6: b6 68 00\n\
492   6: b6 69 00\n\
492   6: b6 6a 00\n\
492   6: b6 6b 00\n\
492   6: b6 6c 00\n\
492   6: b6 6d 00\n\
492   6: b6 6e 00\n\
492   6: b6 6f 00\n\
492   6: b6 70 00\n\
492   6: b6 71 00\n\
492   6: b6 72 00\n\
492   6: b6 73 00\n\
492   6: b6 74 00\n\
492   6: b6 75 00\n\
492   6: b6 76 00\n\
492   6: b6 77 00\n\
493   6: 86 40 3f\n\
494   7: b7 40 00\n\
494   7: b7 42 00\n\
494   7: b7 44 00\n\
494   7: b7 45 00\n\
494   7: b7 00 25\n\
494   7: b7 20 45\n\
494   7: 97 40 3f\n\
494   7: b7 07 28\n\
494   7: b7 0a 17\n\
494   7: b7 46 43\n\
494   7: b7 47 68\n\
494   7: b7 48 0d\n\
494   7: b7 49 32\n\
494   7: b7 4a 57\n\
494   7: b7 4b 7c\n\
494   7: b7 4c 21\n\
494   7: b7 4d 46\n\
494   7: b7 4e 6b\n\
494   7: b7 4f 10\n\
494   7: b7 5b 4c\n\
494   7: b7 5c 71\n\
494   7: b7 5d 16\n\
494   7: b7 5e 3b\n\
494   7: b7 5f 60\n\
494   7: b7 01 00\n\
494   7: b7 02 00\n\
494   7: b7 03 00\n\
494   7: b7 04 00\n\
494   7: b7 05 00\n\
494   7: b7 08 40\n\
494   7: b7 09 00\n\
494   7: b7 0b 7f\n\
494   7: b7 0c 00\n\
494   7: b7 0d 00\n\
494   7: b7 0e 00\n\
494   7: b7 0f 00\n\
494   7: b7 10 00\n\
494   7: b7 11 00\n\
494   7: b7 12 00\n\
494   7: b7 13 00\n\
494   7: b7 14 00\n\
494   7: b7 15 00\n\
494   7: b7 16 00\n\
494   7: b7 17 00\n\
494   7: b7 18 00\n\
494   7: b7 19 00\n\
494   7: b7 1a 00\n\
494   7: b7 1b 00\n\
494   7: b7 1c 00\n\
494   7: b7 1d 00\n\
494   7: b7 1e 00\n\
494   7: b7 1f 00\n\
494   7: b7 21 00\n\
494   7: b7 22 00\n\
494   7: b7 23 00\n\
494   7: b7 24 00\n\
494   7: b7 25 00\n\
494   7: b7 27 00\n\
494   7: b7 28 00\n\
494   7: b7 29 00\n\
494   7: b7 2a 00\n\
494   7: b7 2b 7f\n\
494   7: b7 2c 00\n\
494   7: b7 2d 00\n\
494   7: b7 2e 00\n\
494   7: b7 2f 00\n\
494   7: b7 30 00\n\
494   7: b7 31 00\n\
494   7: b7 32 00\n\
494   7: b7 33 00\n\
494   7: b7 34 00\n\
494   7: b7 35 00\n\
494   7: b7 36 00\n\
494   7: b7 37 00\n\
494   7: b7 38 00\n\
494   7: b7 39 00\n\
494   7: b7 3a 00\n\
494   7: b7 3b 00\n\
494   7: b7 3c 00\n\
494   7: b7 3d 00\n\
494   7: b7 3e 00\n\
494   7: b7 3f 00\n\
494   7: b7 41 00\n\
494   7: b7 43 00\n\
494   7: b7 50 00\n\
494   7: b7 51 00\n\
494   7: b7 52 00\n\
494   7: b7 53 00\n\
494   7: b7 54 00\n\
494   7: b7 55 00\n\
494   7: b7 56 00\n\
494   7: b7 57 00\n\
494   7: b7 58 00\n\
494   7: b7 59 00\n\
494   7: b7 5a 00\n\
494   7: b7 62 7f\n\
494   7: b7 63 7f\n\
494   7: b7 64 7f\n\
494   7: b7 65 7f\n\
494   7: b7 66 00\n\
494   7: b7 67 00\n\
494   7: b7 68 00\n\
494   7: b7 69 00\n\
494   7: b7 6a 00\n\
494   7: b7 6b 00\n\
494   7: b7 6c 00\n\
494   7: b7 6d 00\n\
494   7: b7 6e 00\n\
494   7: b7 6f 00\n\
494   7: b7 70 00\n\
494   7: b7 71 00\n\
494   7: b7 72 00\n\
494   7: b7 73 00\n\
494   7: b7 74 00\n\
494   7: b7 75 00\n\
494   7: b7 76 00\n\
494   7: b7 77 00\n\
495   7: 87 40 3f\n\
496   8: b8 40 00\n\
496   8: b8 42 00\n\
496   8: b8 44 00\n\
496   8: b8 45 00\n\
496   8: b8 00 25\n\
496   8: b8 20 45\n\
496   8: 98 40 3f\n\
496   8: b8 07 28\n\
496   8: b8 0a 17\n\
496   8: b8 46 43\n\
496   8: b8 47 68\n\
496   8: b8 48 0d\n\
496   8: b8 49 32\n\
496   8: b8 4a 57\n\
496   8: b8 4b 7c\n\
496   8: b8 4c 21\n\
496   8: b8 4d 46\n\
496   8: b8 4e 6b\n\
496   8: b8 4f 10\n\
496   8: b8 5b 4c\n\
496   8: b8 5c 71\n\
496   8: b8 5d 16\n\
496   8: b8 5e 3b\n\
496   8: b8 5f 60\n\
496   8: b8 01 00\n\
496   8: b8 02 00\n\
496   8: b8 03 00\n\
496   8: b8 04 00\n\
496   8: b8 05 00\n\
496   8: b8 08 40\n\
496   8: b8 09 00\n\
496   8: b8 0b 7f\n\
496   8: b8 0c 00\n\
496   8: b8 0d 00\n\
496   8: b8 0e 00\n\
496   8: b8 0f 00\n\
496   8: b8 10 00\n\
496   8: b8 11 00\n\
496   8: b8 12 00\n\
496   8: b8 13 00\n\
496   8: b8 14 00\n\
496   8: b8 15 00\n\
496   8: b8 16 00\n\
496   8: b8 17 00\n\
496   8: b8 18 00\n\
496   8: b8 19 00\n\
496   8: b8 1a 00\n\
496   8: b8 1b 00\n\
496   8: b8 1c 00\n\
496   8: b8 1d 00\n\
496   8: b8 1e 00\n\
496   8: b8 1f 00\n\
496   8: b8 21 00\n\
496   8: b8 22 00\n\
496   8: b8 23 00\n\
496   8: b8 24 00\n\
496   8: b8 25 00\n\
496   8: b8 27 00\n\
496   8: b8 28 00\n\
496   8: b8 29 00\n\
496   8: b8 2a 00\n\
496   8: b8 2b 7f\n\
496   8: b8 2c 00\n\
496   8: b8 2d 00\n\
496   8: b8 2e 00\n\
496   8: b8 2f 00\n\
496   8: b8 30 00\n\
496   8: b8 31 00\n\
496   8: b8 32 00\n\
496   8: b8 33 00\n\
496   8: b8 34 00\n\
496   8: b8 35 00\n\
496   8: b8 36 00\n\
496   8: b8 37 00\n\
496   8: b8 38 00\n\
496   8: b8 39 00\n\
496   8: b8 3a 00\n\
496   8: b8 3b 00\n\
496   8: b8 3c 00\n\
496   8: b8 3d 00\n\
496   8: b8 3e 00\n\
496   8: b8 3f 00\n\
496   8: b8 41 00\n\
496   8: b8 43 00\n\
496   8: b8 50 00\n\
496   8: b8 51 00\n\
496   8: b8 52 00\n\
496   8: b8 53 00\n\
496   8: b8 54 00\n\
496   8: b8 55 00\n\
496   8: b8 56 00\n\
496   8: b8 57 00\n\
496   8: b8 58 00\n\
496   8: b8 59 00\n\
496   8: b8 5a 00\n\
496   8: b8 62 7f\n\
496   8: b8 63 7f\n\
496   8: b8 64 7f\n\
496   8: b8 65 7f\n\
496   8: b8 66 00\n\
496   8: b8 67 00\n\
496   8: b8 68 00\n\
496   8: b8 69 00\n\
496   8: b8 6a 00\n\
496   8: b8 6b 00\n\
496   8: b8 6c 00\n\
496   8: b8 6d 00\n\
496   8: b8 6e 00\n\
496   8: b8 6f 00\n\
496   8: b8 70 00\n\
496   8: b8 71 00\n\
496   8: b8 72 00\n\
496   8: b8 73 00\n\
496   8: b8 74 00\n\
496   8: b8 75 00\n\
496   8: b8 76 00\n\
496   8: b8 77 00\n\
497   8: 88 40 3f\n\
498  10: ba 40 00\n\
498  10: ba 42 00\n\
498  10: ba 44 00\n\
498  10: ba 45 00\n\
498  10: ba 00 25\n\
498  10: ba 20 45\n\
498  10: 9a 40 3f\n\
498  10: ba 07 28\n\
498  10: ba 0a 17\n\
498  10: ba 46 43\n\
498  10: ba 47 68\n\
498  10: ba 48 0d\n\
498  10: ba 49 32\n\
498  10: ba 4a 57\n\
498  10: ba 4b 7c\n\
498  10: ba 4c 21\n\
498  10: ba 4d 46\n\
498  10: ba 4e 6b\n\
498  10: ba 4f 10\n\
498  10: ba 5b 4c\n\
498  10: ba 5c 71\n\
498  10: ba 5d 16\n\
498  10: ba 5e 3b\n\
498  10: ba 5f 60\n\
498  10: ba 01 00\n\
498  10: ba 02 00\n\
498  10: ba 03 00\n\
498  10: ba 04 00\n\
498  10: ba 05 00\n\
498  10: ba 08 40\n\
498  10: ba 09 00\n\
498  10: ba 0b 7f\n\
498  10: ba 0c 00\n\
498  10: ba 0d 00\n\
498  10: ba 0e 00\n\
498  10: ba 0f 00\n\
498  10: ba 10 00\n\
498  10: ba 11 00\n\
498  10: ba 12 00\n\
498  10: ba 13 00\n\
498  10: ba 14 00\n\
498  10: ba 15 00\n\
498  10: ba 16 00\n\
498  10: ba 17 00\n\
498  10: ba 18 00\n\
498  10: ba 19 00\n\
498  10: ba 1a 00\n\
498  10: ba 1b 00\n\
498  10: ba 1c 00\n\
498  10: ba 1d 00\n\
498  10: ba 1e 00\n\
498  10: ba 1f 00\n\
498  10: ba 21 00\n\
498  10: ba 22 00\n\
498  10: ba 23 00\n\
498  10: ba 24 00\n\
498  10: ba 25 00\n\
498  10: ba 27 00\n\
498  10: ba 28 00\n\
498  10: ba 29 00\n\
498  10: ba 2a 00\n\
498  10: ba 2b 7f\n\
498  10: ba 2c 00\n\
498  10: ba 2d 00\n\
498  10: ba 2e 00\n\
498  10: ba 2f 00\n\
498  10: ba 30 00\n\
498  10: ba 31 00\n\
498  10: ba 32 00\n\
498  10: ba 33 00\n\
498  10: ba 34 00\n\
498  10: ba 35 00\n\
498  10: ba 36 00\n\
498  10: ba 37 00\n\
498  10: ba 38 00\n\
498  10: ba 39 00\n\
498  10: ba 3a 00\n\
498  10: ba 3b 00\n\
498  10: ba 3c 00\n\
498  10: ba 3d 00\n\
498  10: ba 3e 00\n\
498  10: ba 3f 00\n\
498  10: ba 41 00\n\
498  10: ba 43 00\n\
498  10: ba 50 00\n\
498  10: ba 51 00\n\
498  10: ba 52 00\n\
498  10: ba 53 00\n\
498  10: ba 54 00\n\
498  10: ba 55 00\n\
498  10: ba 56 00\n\
498  10: ba 57 00\n\
498  10: ba 58 00\n\
498  10: ba 59 00\n\
498  10: ba 5a 00\n\
498  10: ba 62 7f\n\
498  10: ba 63 7f\n\
498  10: ba 64 7f\n\
498  10: ba 65 7f\n\
498  10: ba 66 00\n\
498  10: ba 67 00\n\
498  10: ba 68 00\n\
498  10: ba 69 00\n\
498  10: ba 6a 00\n\
498  10: ba 6b 00\n\
498  10: ba 6c 00\n\
498  10: ba 6d 00\n\
498  10: ba 6e 00\n\
498  10: ba 6f 00\n\
498  10: ba 70 00\n\
498  10: ba 71 00\n\
498  10: ba 72 00\n\
498  10: ba 73 00\n\
498  10: ba 74 00\n\
498  10: ba 75 00\n\
498  10: ba 76 00\n\
498  10: ba 77 00\n\
499  10: 8a 40 3f\n\
500  11: bb 40 00\n\
500  11: bb 42 00\n\
500  11: bb 44 00\n\
500  11: bb 45 00\n\
500  11: bb 00 25\n\
500  11: bb 20 45\n\
500  11: 9b 40 3f\n\
500  11: bb 07 28\n\
500  11: bb 0a 17\n\
500  11: bb 46 43\n\
500  11: bb 47 68\n\
500  11: bb 48 0d\n\
500  11: bb 49 32\n\
500  11: bb 4a 57\n\
500  11: bb 4b 7c\n\
500  11: bb 4c 21\n\
500  11: bb 4d 46\n\
500  11: bb 4e 6b\n\
500  11: bb 4f 10\n\
500  11: bb 5b 4c\n\
500  11: bb 5c 71\n\
500  11: bb 5d 16\n\
500  11: bb 5e 3b\n\
500  11: bb 5f 60\n\
500  11: bb 01 00\n\
500  11: bb 02 00\n\
500  11: bb 03 00\n\
500  11: bb 04 00\n\
500  11: bb 05 00\n\
500  11: bb 08 40\n\
500  11: bb 09 00\n\
500  11: bb 0b 7f\n\
500  11: bb 0c 00\n\
500  11: bb 0d 00\n\
500  11: bb 0e 00\n\
500  11: bb 0f 00\n\
500  11: bb 10 00\n\
500  11: bb 11 00\n\
500  11: bb 12 00\n\
500  11: bb 13 00\n\
500  11: bb 14 00\n\
500  11: bb 15 00\n\
500  11: bb 16 00\n\
500  11: bb 17 00\n\
500  11: bb 18 00\n\
500  11: bb 19 00\n\
500  11: bb 1a 00\n\
500  11: bb 1b 00\n\
500  11: bb 1c 00\n\
500  11: bb 1d 00\n\
500  11: bb 1e 00\n\
500  11: bb 1f 00\n\
500  11: bb 21 00\n\
500  11: bb 22 00\n\
500  11: bb 23 00\n\
500  11: bb 24 00\n\
500  11: bb 25 00\n\
500  11: bb 27 00\n\
500  11: bb 28 00\n\
500  11: bb 29 00\n\
500  11: bb 2a 00\n\
500  11: bb 2b 7f\n\
500  11: bb 2c 00\n\
500  11: bb 2d 00\n\
500  11: bb 2e 00\n\
500  11: bb 2f 00\n\
500  11: bb 30 00\n\
500  11: bb 31 00\n\
500  11: bb 32 00\n\
500  11: bb 33 00\n\
500  11: bb 34 00\n\
500  11: bb 35 00\n\
500  11: bb 36 00\n\
500  11: bb 37 00\n\
500  11: bb 38 00\n\
500  11: bb 39 00\n\
500  11: bb 3a 00\n\
500  11: bb 3b 00\n\
500  11: bb 3c 00\n\
500  11: bb 3d 00\n\
500  11: bb 3e 00\n\
500  11: bb 3f 00\n\
500  11: bb 41 00\n\
500  11: bb 43 00\n\
500  11: bb 50 00\n\
500  11: bb 51 00\n\
500  11: bb 52 00\n\
500  11: bb 53 00\n\
500  11: bb 54 00\n\
500  11: bb 55 00\n\
500  11: bb 56 00\n\
500  11: bb 57 00\n\
500  11: bb 58 00\n\
500  11: bb 59 00\n\
500  11: bb 5a 00\n\
500  11: bb 62 7f\n\
500  11: bb 63 7f\n\
500  11: bb 64 7f\n\
500  11: bb 65 7f\n\
500  11: bb 66 00\n\
500  11: bb 67 00\n\
500  11: bb 68 00\n\
500  11: bb 69 00\n\
500  11: bb 6a 00\n\
500  11: bb 6b 00\n\
500  11: bb 6c 00\n\
500  11: bb 6d 00\n\
500  11: bb 6e 00\n\
500  11: bb 6f 00\n\
500  11: bb 70 00\n\
500  11: bb 71 00\n\
500  11: bb 72 00\n\
500  11: bb 73 00\n\
500  11: bb 74 00\n\
500  11: bb 75 00\n\
500  11: bb 76 00\n\
500  11: bb 77 00\n\
501  11: 8b 40 3f\n\
502  12: bc 40 00\n\
502  12: bc 42 00\n\
502  12: bc 44 00\n\
502  12: bc 45 00\n\
502  12: bc 00 25\n\
502  12: bc 20 45\n\
502  12: 9c 40 3f\n\
502  12: bc 07 28\n\
502  12: bc 0a 17\n\
502  12: bc 46 43\n\
502  12: bc 47 68\n\
502  12: bc 48 0d\n\
502  12: bc 49 32\n\
502  12: bc 4a 57\n\
502  12: bc 4b 7c\n\
502  12: bc 4c 21\n\
502  12: bc 4d 46\n\
502  12: bc 4e 6b\n\
502  12: bc 4f 10\n\
502  12: bc 5b 4c\n\
502  12: bc 5c 71\n\
502  12: bc 5d 16\n\
502  12: bc 5e 3b\n\
502  12: bc 5f 60\n\
502  12: bc 01 00\n\
502  12: bc 02 00\n\
502  12: bc 03 00\n\
502  12: bc 04 00\n\
502  12: bc 05 00\n\
502  12: bc 08 40\n\
502  12: bc 09 00\n\
502  12: bc 0b 7f\n\
502  12: bc 0c 00\n\
502  12: bc 0d 00\n\
502  12: bc 0e 00\n\
502  12: bc 0f 00\n\
502  12: bc 10 00\n\
502  12: bc 11 00\n\
502  12: bc 12 00\n\
502  12: bc 13 00\n\
502  12: bc 14 00\n\
502  12: bc 15 00\n\
502  12: bc 16 00\n\
502  12: bc 17 00\n\
502  12: bc 18 00\n\
502  12: bc 19 00\n\
502  12: bc 1a 00\n\
502  12: bc 1b 00\n\
502  12: bc 1c 00\n\
502  12: bc 1d 00\n\
502  12: bc 1e 00\n\
502  12: bc 1f 00\n\
502  12: bc 21 00\n\
502  12: bc 22 00\n\
502  12: bc 23 00\n\
502  12: bc 24 00\n\
502  12: bc 25 00\n\
502  12: bc 27 00\n\
502  12: bc 28 00\n\
502  12: bc 29 00\n\
502  12: bc 2a 00\n\
502  12: bc 2b 7f\n\
502  12: bc 2c 00\n\
502  12: bc 2d 00\n\
502  12: bc 2e 00\n\
502  12: bc 2f 00\n\
502  12: bc 30 00\n\
502  12: bc 31 00\n\
502  12: bc 32 00\n\
502  12: bc 33 00\n\
502  12: bc 34 00\n\
502  12: bc 35 00\n\
502  12: bc 36 00\n\
502  12: bc 37 00\n\
502  12: bc 38 00\n\
502  12: bc 39 00\n\
502  12: bc 3a 00\n\
502  12: bc 3b 00\n\
502  12: bc 3c 00\n\
502  12: bc 3d 00\n\
502  12: bc 3e 00\n\
502  12: bc 3f 00\n\
502  12: bc 41 00\n\
502  12: bc 43 00\n\
502  12: bc 50 00\n\
502  12: bc 51 00\n\
502  12: bc 52 00\n\
502  12: bc 53 00\n\
502  12: bc 54 00\n\
502  12: bc 55 00\n\
502  12: bc 56 00\n\
502  12: bc 57 00\n\
502  12: bc 58 00\n\
502  12: bc 59 00\n\
502  12: bc 5a 00\n\
502  12: bc 62 7f\n\
502  12: bc 63 7f\n\
502  12: bc 64 7f\n\
502  12: bc 65 7f\n\
502  12: bc 66 00\n\
502  12: bc 67 00\n\
502  12: bc 68 00\n\
502  12: bc 69 00\n\
502  12: bc 6a 00\n\
502  12: bc 6b 00\n\
502  12: bc 6c 00\n\
502  12: bc 6d 00\n\
502  12: bc 6e 00\n\
502  12: bc 6f 00\n\
502  12: bc 70 00\n\
502  12: bc 71 00\n\
502  12: bc 72 00\n\
502  12: bc 73 00\n\
502  12: bc 74 00\n\
502  12: bc 75 00\n\
502  12: bc 76 00\n\
502  12: bc 77 00\n\
503  12: 8c 40 3f\n\
504  13: bd 40 00\n\
504  13: bd 42 00\n\
504  13: bd 44 00\n\
504  13: bd 45 00\n\
504  13: bd 00 25\n\
504  13: bd 20 45\n\
504  13: 9d 40 41\n\
504  13: bd 07 28\n\
504  13: bd 0a 17\n\
504  13: bd 46 43\n\
504  13: bd 47 68\n\
504  13: bd 48 0d\n\
504  13: bd 49 32\n\
504  13: bd 4a 57\n\
504  13: bd 4b 7c\n\
504  13: bd 4c 21\n\
504  13: bd 4d 46\n\
504  13: bd 4e 6b\n\
504  13: bd 4f 10\n\
504  13: bd 5b 4c\n\
504  13: bd 5c 71\n\
504  13: bd 5d 16\n\
504  13: bd 5e 3b\n\
504  13: bd 5f 60\n\
504  13: bd 01 00\n\
504  13: bd 02 00\n\
504  13: bd 03 00\n\
504  13: bd 04 00\n\
504  13: bd 05 00\n\
504  13: bd 08 40\n\
504  13: bd 09 00\n\
504  13: bd 0b 7f\n\
504  13: bd 0c 00\n\
504  13: bd 0d 00\n\
504  13: bd 0e 00\n\
504  13: bd 0f 00\n\
504  13: bd 10 00\n\
504  13: bd 11 00\n\
504  13: bd 12 00\n\
504  13: bd 13 00\n\
504  13: bd 14 00\n\
504  13: bd 15 00\n\
504  13: bd 16 00\n\
504  13: bd 17 00\n\
504  13: bd 18 00\n\
504  13: bd 19 00\n\
504  13: bd 1a 00\n\
504  13: bd 1b 00\n\
504  13: bd 1c 00\n\
504  13: bd 1d 00\n\
504  13: bd 1e 00\n\
504  13: bd 1f 00\n\
504  13: bd 21 00\n\
504  13: bd 22 00\n\
504  13: bd 23 00\n\
504  13: bd 24 00\n\
504  13: bd 25 00\n\
504  13: bd 27 00\n\
504  13: bd 28 00\n\
504  13: bd 29 00\n\
504  13: bd 2a 00\n\
504  13: bd 2b 7f\n\
504  13: bd 2c 00\n\
504  13: bd 2d 00\n\
504  13: bd 2e 00\n\
504  13: bd 2f 00\n\
504  13: bd 30 00\n\
504  13: bd 31 00\n\
504  13: bd 32 00\n\
504  13: bd 33 00\n\
504  13: bd 34 00\n\
504  13: bd 35 00\n\
504  13: bd 36 00\n\
504  13: bd 37 00\n\
504  13: bd 38 00\n\
504  13: bd 39 00\n\
504  13: bd 3a 00\n\
504  13: bd 3b 00\n\
504  13: bd 3c 00\n\
504  13: bd 3d 00\n\
504  13: bd 3e 00\n\
504  13: bd 3f 00\n\
504  13: bd 41 00\n\
504  13: bd 43 00\n\
504  13: bd 50 00\n\
504  13: bd 51 00\n\
504  13: bd 52 00\n\
504  13: bd 53 00\n\
504  13: bd 54 00\n\
504  13: bd 55 00\n\
504  13: bd 56 00\n\
504  13: bd 57 00\n\
504  13: bd 58 00\n\
504  13: bd 59 00\n\
504  13: bd 5a 00\n\
504  13: bd 62 7f\n\
504  13: bd 63 7f\n\
504  13: bd 64 7f\n\
504  13: bd 65 7f\n\
504  13: bd 66 00\n\
504  13: bd 67 00\n\
504  13: bd 68 00\n\
504  13: bd 69 00\n\
504  13: bd 6a 00\n\
504  13: bd 6b 00\n\
504  13: bd 6c 00\n\
504  13: bd 6d 00\n\
504  13: bd 6e 00\n\
504  13: bd 6f 00\n\
504  13: bd 70 00\n\
504  13: bd 71 00\n\
504  13: bd 72 00\n\
504  13: bd 73 00\n\
504  13: bd 74 00\n\
504  13: bd 75 00\n\
504  13: bd 76 00\n\
504  13: bd 77 00\n\
505  13: 8d 40 41\n\
506  14: be 40 00\n\
506  14: be 42 00\n\
506  14: be 44 00\n\
506  14: be 45 00\n\
506  14: be 00 25\n\
506  14: be 20 45\n\
506  14: 9e 40 43\n\
506  14: be 07 28\n\
506  14: be 0a 17\n\
506  14: be 46 43\n\
506  14: be 47 68\n\
506  14: be 48 0d\n\
506  14: be 49 32\n\
506  14: be 4a 57\n\
506  14: be 4b 7c\n\
506  14: be 4c 21\n\
506  14: be 4d 46\n\
506  14: be 4e 6b\n\
506  14: be 4f 10\n\
506  14: be 5b 4c\n\
506  14: be 5c 71\n\
506  14: be 5d 16\n\
506  14: be 5e 3b\n\
506  14: be 5f 60\n\
506  14: be 01 00\n\
506  14: be 02 00\n\
506  14: be 03 00\n\
506  14: be 04 00\n\
506  14: be 05 00\n\
506  14: be 08 40\n\
506  14: be 09 00\n\
506  14: be 0b 7f\n\
506  14: be 0c 00\n\
506  14: be 0d 00\n\
506  14: be 0e 00\n\
506  14: be 0f 00\n\
506  14: be 10 00\n\
506  14: be 11 00\n\
506  14: be 12 00\n\
506  14: be 13 00\n\
506  14: be 14 00\n\
506  14: be 15 00\n\
506  14: be 16 00\n\
506  14: be 17 00\n\
506  14: be 18 00\n\
506  14: be 19 00\n\
506  14: be 1a 00\n\
506  14: be 1b 00\n\
506  14: be 1c 00\n\
506  14: be 1d 00\n\
506  14: be 1e 00\n\
506  14: be 1f 00\n\
506  14: be 21 00\n\
506  14: be 22 00\n\
506  14: be 23 00\n\
506  14: be 24 00\n\
506  14: be 25 00\n\
506  14: be 27 00\n\
506  14: be 28 00\n\
506  14: be 29 00\n\
506  14: be 2a 00\n\
506  14: be 2b 7f\n\
506  14: be 2c 00\n\
506  14: be 2d 00\n\
506  14: be 2e 00\n\
506  14: be 2f 00\n\
506  14: be 30 00\n\
506  14: be 31 00\n\
506  14: be 32 00\n\
506  14: be 33 00\n\
506  14: be 34 00\n\
506  14: be 35 00\n\
506  14: be 36 00\n\
506  14: be 37 00\n\
506  14: be 38 00\n\
506  14: be 39 00\n\
506  14: be 3a 00\n\
506  14: be 3b 00\n\
506  14: be 3c 00\n\
506  14: be 3d 00\n\
506  14: be 3e 00\n\
506  14: be 3f 00\n\
506  14: be 41 00\n\
506  14: be 43 00\n\
506  14: be 50 00\n\
506  14: be 51 00\n\
506  14: be 52 00\n\
506  14: be 53 00\n\
506  14: be 54 00\n\
506  14: be 55 00\n\
506  14: be 56 00\n\
506  14: be 57 00\n\
506  14: be 58 00\n\
506  14: be 59 00\n\
506  14: be 5a 00\n\
506  14: be 62 7f\n\
506  14: be 63 7f\n\
506  14: be 64 7f\n\
506  14: be 65 7f\n\
506  14: be 66 00\n\
506  14: be 67 00\n\
506  14: be 68 00\n\
506  14: be 69 00\n\
506  14: be 6a 00\n\
506  14: be 6b 00\n\
506  14: be 6c 00\n\
506  14: be 6d 00\n\
506  14: be 6e 00\n\
506  14: be 6f 00\n\
506  14: be 70 00\n\
506  14: be 71 00\n\
506  14: be 72 00\n\
506  14: be 73 00\n\
506  14: be 74 00\n\
506  14: be 75 00\n\
506  14: be 76 00\n\
506  14: be 77 00\n\
507  14: 8e 40 43\n\
508  15: bf 40 00\n\
508  15: bf 42 00\n\
508  15: bf 44 00\n\
508  15: bf 45 00\n\
508  15: bf 00 25\n\
508  15: bf 20 45\n\
508  15: 9f 40 45\n\
508  15: bf 07 28\n\
508  15: bf 0a 17\n\
508  15: bf 46 43\n\
508  15: bf 47 68\n\
508  15: bf 48 0d\n\
508  15: bf 49 32\n\
508  15: bf 4a 57\n\
508  15: bf 4b 7c\n\
508  15: bf 4c 21\n\
508  15: bf 4d 46\n\
508  15: bf 4e 6b\n\
508  15: bf 4f 10\n\
508  15: bf 5b 4c\n\
508  15: bf 5c 71\n\
508  15: bf 5d 16\n\
508  15: bf 5e 3b\n\
508  15: bf 5f 60\n\
508  15: bf 01 00\n\
508  15: bf 02 00\n\
508  15: bf 03 00\n\
508  15: bf 04 00\n\
508  15: bf 05 00\n\
508  15: bf 08 40\n\
508  15: bf 09 00\n\
508  15: bf 0b 7f\n\
508  15: bf 0c 00\n\
508  15: bf 0d 00\n\
508  15: bf 0e 00\n\
508  15: bf 0f 00\n\
508  15: bf 10 00\n\
508  15: bf 11 00\n\
508  15: bf 12 00\n\
508  15: bf 13 00\n\
508  15: bf 14 00\n\
508  15: bf 15 00\n\
508  15: bf 16 00\n\
508  15: bf 17 00\n\
508  15: bf 18 00\n\
508  15: bf 19 00\n\
508  15: bf 1a 00\n\
508  15: bf 1b 00\n\
508  15: bf 1c 00\n\
508  15: bf 1d 00\n\
508  15: bf 1e 00\n\
508  15: bf 1f 00\n\
508  15: bf 21 00\n\
508  15: bf 22 00\n\
508  15: bf 23 00\n\
508  15: bf 24 00\n\
508  15: bf 25 00\n\
508  15: bf 27 00\n\
508  15: bf 28 00\n\
508  15: bf 29 00\n\
508  15: bf 2a 00\n\
508  15: bf 2b 7f\n\
508  15: bf 2c 00\n\
508  15: bf 2d 00\n\
508  15: bf 2e 00\n\
508  15: bf 2f 00\n\
508  15: bf 30 00\n\
508  15: bf 31 00\n\
508  15: bf 32 00\n\
508  15: bf 33 00\n\
508  15: bf 34 00\n\
508  15: bf 35 00\n\
508  15: bf 36 00\n\
508  15: bf 37 00\n\
508  15: bf 38 00\n\
508  15: bf 39 00\n\
508  15: bf 3a 00\n\
508  15: bf 3b 00\n\
508  15: bf 3c 00\n\
508  15: bf 3d 00\n\
508  15: bf 3e 00\n\
508  15: bf 3f 00\n\
508  15: bf 41 00\n\
508  15: bf 43 00\n\
508  15: bf 50 00\n\
508  15: bf 51 00\n\
508  15: bf 52 00\n\
508  15: bf 53 00\n\
508  15: bf 54 00\n\
508  15: bf 55 00\n\
508  15: bf 56 00\n\
508  15: bf 57 00\n\
508  15: bf 58 00\n\
508  15: bf 59 00\n\
508  15: bf 5a 00\n\
508  15: bf 62 7f\n\
508  15: bf 63 7f\n\
508  15: bf 64 7f\n\
508  15: bf 65 7f\n\
508  15: bf 66 00\n\
508  15: bf 67 00\n\
508  15: bf 68 00\n\
508  15: bf 69 00\n\
508  15: bf 6a 00\n\
508  15: bf 6b 00\n\
508  15: bf 6c 00\n\
508  15: bf 6d 00\n\
508  15: bf 6e 00\n\
508  15: bf 6f 00\n\
508  15: bf 70 00\n\
508  15: bf 71 00\n\
508  15: bf 72 00\n\
508  15: bf 73 00\n\
508  15: bf 74 00\n\
508  15: bf 75 00\n\
508  15: bf 76 00\n\
508  15: bf 77 00\n\
509  15: 8f 40 45\n\
510   0: b0 00 25\n\
510   0: b0 20 45\n\
510   0: 90 40 47\n\
510   0: b0 01 00\n\
510   0: b0 03 00\n\
510   0: b0 05 00\n\
510   0: b0 08 40\n\
510   0: b0 0b 7f\n\
510   0: b0 0d 00\n\
510   0: b0 0f 00\n\
510   0: b0 11 00\n\
510   0: b0 13 00\n\
510   0: b0 15 00\n\
510   0: b0 17 00\n\
510   0: b0 19 00\n\
510   0: b0 1b 00\n\
510   0: b0 1d 00\n\
510   0: b0 1f 00\n\
510   0: b0 22 00\n\
510   0: b0 24 00\n\
510   0: b0 27 00\n\
510   0: b0 29 00\n\
510   0: b0 2b 7f\n\
510   0: b0 2d 00\n\
510   0: b0 2f 00\n\
510   0: b0 31 00\n\
510   0: b0 33 00\n\
510   0: b0 35 00\n\
510   0: b0 37 00\n\
510   0: b0 39 00\n\
510   0: b0 3b 00\n\
510   0: b0 3d 00\n\
510   0: b0 3f 00\n\
510   0: b0 43 00\n\
510   0: b0 50 00\n\
510   0: b0 52 00\n\
510   0: b0 54 00\n\
510   0: b0 56 00\n\
510   0: b0 58 00\n\
510   0: b0 5a 00\n\
510   0: b0 66 00\n\
510   0: b0 68 00\n\
510   0: b0 6a 00\n\
510   0: b0 6c 00\n\
510   0: b0 6e 00\n\
510   0: b0 70 00\n\
510   0: b0 72 00\n\
510   0: b0 74 00\n\
510   0: b0 76 00\n\
510   0: b0 02 00\n\
510   0: b0 04 00\n\
510   0: b0 09 00\n\
510   0: b0 0c 00\n\
510   0: b0 0e 00\n\
510   0: b0 10 00\n\
510   0: b0 12 00\n\
510   0: b0 14 00\n\
510   0: b0 16 00\n\
510   0: b0 18 00\n\
510   0: b0 1a 00\n\
510   0: b0 1c 00\n\
510   0: b0 1e 00\n\
510   0: b0 21 00\n\
510   0: b0 23 00\n\
510   0: b0 25 00\n\
510   0: b0 28 00\n\
510   0: b0 2a 00\n\
510   0: b0 2c 00\n\
510   0: b0 2e 00\n\
510   0: b0 30 00\n\
510   0: b0 32 00\n\
510   0: b0 34 00\n\
510   0: b0 36 00\n\
510   0: b0 38 00\n\
510   0: b0 3a 00\n\
510   0: b0 3c 00\n\
510   0: b0 3e 00\n\
510   0: b0 41 00\n\
510   0: b0 51 00\n\
510   0: b0 53 00\n\
510   0: b0 55 00\n\
510   0: b0 57 00\n\
510   0: b0 59 00\n\
510   0: b0 62 7f\n\
510   0: b0 63 7f\n\
510   0: b0 64 7f\n\
510   0: b0 65 7f\n\
510   0: b0 67 00\n\
510   0: b0 69 00\n\
510   0: b0 6b 00\n\
510   0: b0 6d 00\n\
510   0: b0 6f 00\n\
510   0: b0 71 00\n\
510   0: b0 73 00\n\
510   0: b0 75 00\n\
510   0: b0 77 00\n\
511   0: 80 40 47\n\
512   1: b1 00 25\n\
512   1: b1 20 45\n\
512   1: 91 40 49\n\
512   1: b1 01 00\n\
512   1: b1 03 00\n\
512   1: b1 05 00\n\
512   1: b1 08 40\n\
512   1: b1 0b 7f\n\
512   1: b1 0d 00\n\
512   1: b1 0f 00\n\
512   1: b1 11 00\n\
512   1: b1 13 00\n\
512   1: b1 15 00\n\
512   1: b1 17 00\n\
512   1: b1 19 00\n\
512   1: b1 1b 00\n\
512   1: b1 1d 00\n\
512   1: b1 1f 00\n\
512   1: b1 22 00\n\
512   1: b1 24 00\n\
512   1: b1 27 00\n\
512   1: b1 29 00\n\
512   1: b1 2b 7f\n\
512   1: b1 2d 00\n\
512   1: b1 2f 00\n\
512   1: b1 31 00\n\
512   1: b1 33 00\n\
512   1: b1 35 00\n\
512   1: b1 37 00\n\
512   1: b1 39 00\n\
512   1: b1 3b 00\n\
512   1: b1 3d 00\n\
512   1: b1 3f 00\n\
512   1: b1 43 00\n\
512   1: b1 50 00\n\
512   1: b1 52 00\n\
512   1: b1 54 00\n\
512   1: b1 56 00\n\
512   1: b1 58 00\n\
512   1: b1 5a 00\n\
512   1: b1 66 00\n\
512   1: b1 68 00\n\
512   1: b1 6a 00\n\
512   1: b1 6c 00\n\
512   1: b1 6e 00\n\
512   1: b1 70 00\n\
512   1: b1 72 00\n\
512   1: b1 74 00\n\
512   1: b1 76 00\n\
512   1: b1 02 00\n\
512   1: b1 04 00\n\
512   1: b1 09 00\n\
512   1: b1 0c 00\n\
512   1: b1 0e 00\n\
512   1: b1 10 00\n\
512   1: b1 12 00\n\
512   1: b1 14 00\n\
512   1: b1 16 00\n\
512   1: b1 18 00\n\
512   1: b1 1a 00\n\
512   1: b1 1c 00\n\
512   1: b1 1e 00\n\
512   1: b1 21 00\n\
512   1: b1 23 00\n\
512   1: b1 25 00\n\
512   1: b1 28 00\n\
512   1: b1 2a 00\n\
512   1: b1 2c 00\n\
512   1: b1 2e 00\n\
512   1: b1 30 00\n\
512   1: b1 32 00\n\
512   1: b1 34 00\n\
512   1: b1 36 00\n\
512   1: b1 38 00\n\
512   1: b1 3a 00\n\
512   1: b1 3c 00\n\
512   1: b1 3e 00\n\
512   1: b1 41 00\n\
512   1: b1 51 00\n\
512   1: b1 53 00\n\
512   1: b1 55 00\n\
512   1: b1 57 00\n\
512   1: b1 59 00\n\
512   1: b1 62 7f\n\
512   1: b1 63 7f\n\
512   1: b1 64 7f\n\
512   1: b1 65 7f\n\
512   1: b1 67 00\n\
512   1: b1 69 00\n\
512   1: b1 6b 00\n\
512   1: b1 6d 00\n\
512   1: b1 6f 00\n\
512   1: b1 71 00\n\
512   1: b1 73 00\n\
512   1: b1 75 00\n\
512   1: b1 77 00\n\
513   1: 81 40 49\n\
514   2: b2 00 25\n\
514   2: b2 20 45\n\
514   2: 92 40 49\n\
514   2: b2 01 00\n\
514   2: b2 03 00\n\
514   2: b2 05 00\n\
514   2: b2 08 40\n\
514   2: b2 0b 7f\n\
514   2: b2 0d 00\n\
514   2: b2 0f 00\n\
514   2: b2 11 00\n\
514   2: b2 13 00\n\
514   2: b2 15 00\n\
514   2: b2 17 00\n\
514   2: b2 19 00\n\
514   2: b2 1b 00\n\
514   2: b2 1d 00\n\
514   2: b2 1f 00\n\
514   2: b2 22 00\n\
514   2: b2 24 00\n\
514   2: b2 27 00\n\
514   2: b2 29 00\n\
514   2: b2 2b 7f\n\
514   2: b2 2d 00\n\
514   2: b2 2f 00\n\
514   2: b2 31 00\n\
514   2: b2 33 00\n\
514   2: b2 35 00\n\
514   2: b2 37 00\n\
514   2: b2 39 00\n\
514   2: b2 3b 00\n\
514   2: b2 3d 00\n\
514   2: b2 3f 00\n\
514   2: b2 43 00\n\
514   2: b2 50 00\n\
514   2: b2 52 00\n\
514   2: b2 54 00\n\
514   2: b2 56 00\n\
514   2: b2 58 00\n\
514   2: b2 5a 00\n\
514   2: b2 66 00\n\
514   2: b2 68 00\n\
514   2: b2 6a 00\n\
514   2: b2 6c 00\n\
514   2: b2 6e 00\n\
514   2: b2 70 00\n\
514   2: b2 72 00\n\
514   2: b2 74 00\n\
514   2: b2 76 00\n\
514   2: b2 02 00\n\
514   2: b2 04 00\n\
514   2: b2 09 00\n\
514   2: b2 0c 00\n\
514   2: b2 0e 00\n\
514   2: b2 10 00\n\
514   2: b2 12 00\n\
514   2: b2 14 00\n\
514   2: b2 16 00\n\
514   2: b2 18 00\n\
514   2: b2 1a 00\n\
514   2: b2 1c 00\n\
514   2: b2 1e 00\n\
514   2: b2 21 00\n\
514   2: b2 23 00\n\
514   2: b2 25 00\n\
514   2: b2 28 00\n\
514   2: b2 2a 00\n\
514   2: b2 2c 00\n\
514   2: b2 2e 00\n\
514   2: b2 30 00\n\
514   2: b2 32 00\n\
514   2: b2 34 00\n\
514   2: b2 36 00\n\
514   2: b2 38 00\n\
514   2: b2 3a 00\n\
514   2: b2 3c 00\n\
514   2: b2 3e 00\n\
514   2: b2 41 00\n\
514   2: b2 51 00\n\
514   2: b2 53 00\n\
514   2: b2 55 00\n\
514   2: b2 57 00\n\
514   2: b2 59 00\n\
514   2: b2 62 7f\n\
514   2: b2 63 7f\n\
514   2: b2 64 7f\n\
514   2: b2 65 7f\n\
514   2: b2 67 00\n\
514   2: b2 69 00\n\
514   2: b2 6b 00\n\
514   2: b2 6d 00\n\
514   2: b2 6f 00\n\
514   2: b2 71 00\n\
514   2: b2 73 00\n\
514   2: b2 75 00\n\
514   2: b2 77 00\n\
515   2: 82 40 49\n\
516   3: b3 00 25\n\
516   3: b3 20 45\n\
516   3: 93 40 4b\n\
516   3: b3 01 00\n\
516   3: b3 03 00\n\
516   3: b3 05 00\n\
516   3: b3 08 40\n\
516   3: b3 0b 7f\n\
516   3: b3 0d 00\n\
516   3: b3 0f 00\n\
516   3: b3 11 00\n\
516   3: b3 13 00\n\
516   3: b3 15 00\n\
516   3: b3 17 00\n\
516   3: b3 19 00\n\
516   3: b3 1b 00\n\
516   3: b3 1d 00\n\
516   3: b3 1f 00\n\
516   3: b3 22 00\n\
516   3: b3 24 00\n\
516   3: b3 27 00\n\
516   3: b3 29 00\n\
516   3: b3 2b 7f\n\
516   3: b3 2d 00\n\
516   3: b3 2f 00\n\
516   3: b3 31 00\n\
516   3: b3 33 00\n\
516   3: b3 35 00\n\
516   3: b3 37 00\n\
516   3: b3 39 00\n\
516   3: b3 3b 00\n\
516   3: b3 3d 00\n\
516   3: b3 3f 00\n\
516   3: b3 43 00\n\
516   3: b3 50 00\n\
516   3: b3 52 00\n\
516   3: b3 54 00\n\
516   3: b3 56 00\n\
516   3: b3 58 00\n\
516   3: b3 5a 00\n\
516   3: b3 66 00\n\
516   3: b3 68 00\n\
516   3: b3 6a 00\n\
516   3: b3 6c 00\n\
516   3: b3 6e 00\n\
516   3: b3 70 00\n\
516   3: b3 72 00\n\
516   3: b3 74 00\n\
516   3: b3 76 00\n\
516   3: b3 02 00\n\
516   3: b3 04 00\n\
516   3: b3 09 00\n\
516   3: b3 0c 00\n\
516   3: b3 0e 00\n\
516   3: b3 10 00\n\
516   3: b3 12 00\n\
516   3: b3 14 00\n\
516   3: b3 16 00\n\
516   3: b3 18 00\n\
516   3: b3 1a 00\n\
516   3: b3 1c 00\n\
516   3: b3 1e 00\n\
516   3: b3 21 00\n\
516   3: b3 23 00\n\
516   3: b3 25 00\n\
516   3: b3 28 00\n\
516   3: b3 2a 00\n\
516   3: b3 2c 00\n\
516   3: b3 2e 00\n\
516   3: b3 30 00\n\
516   3: b3 32 00\n\
516   3: b3 34 00\n\
516   3: b3 36 00\n\
516   3: b3 38 00\n\
516   3: b3 3a 00\n\
516   3: b3 3c 00\n\
516   3: b3 3e 00\n\
516   3: b3 41 00\n\
516   3: b3 51 00\n\
516   3: b3 53 00\n\
516   3: b3 55 00\n\
516   3: b3 57 00\n\
516   3: b3 59 00\n\
516   3: b3 62 7f\n\
516   3: b3 63 7f\n\
516   3: b3 64 7f\n\
516   3: b3 65 7f\n\
516   3: b3 67 00\n\
516   3: b3 69 00\n\
516   3: b3 6b 00\n\
516   3: b3 6d 00\n\
516   3: b3 6f 00\n\
516   3: b3 71 00\n\
516   3: b3 73 00\n\
516   3: b3 75 00\n\
516   3: b3 77 00\n\
517   3: 83 40 4b\n\
518   4: b4 00 25\n\
518   4: b4 20 45\n\
518   4: 94 40 4d\n\
518   4: b4 01 00\n\
518   4: b4 03 00\n\
518   4: b4 05 00\n\
518   4: b4 08 40\n\
518   4: b4 0b 7f\n\
518   4: b4 0d 00\n\
518   4: b4 0f 00\n\
518   4: b4 11 00\n\
518   4: b4 13 00\n\
518   4: b4 15 00\n\
518   4: b4 17 00\n\
518   4: b4 19 00\n\
518   4: b4 1b 00\n\
518   4: b4 1d 00\n\
518   4: b4 1f 00\n\
518   4: b4 22 00\n\
518   4: b4 24 00\n\
518   4: b4 27 00\n\
518   4: b4 29 00\n\
518   4: b4 2b 7f\n\
518   4: b4 2d 00\n\
518   4: b4 2f 00\n\
518   4: b4 31 00\n\
518   4: b4 33 00\n\
518   4: b4 35 00\n\
518   4: b4 37 00\n\
518   4: b4 39 00\n\
518   4: b4 3b 00\n\
518   4: b4 3d 00\n\
518   4: b4 3f 00\n\
518   4: b4 43 00\n\
518   4: b4 50 00\n\
518   4: b4 52 00\n\
518   4: b4 54 00\n\
518   4: b4 56 00\n\
518   4: b4 58 00\n\
518   4: b4 5a 00\n\
518   4: b4 66 00\n\
518   4: b4 68 00\n\
518   4: b4 6a 00\n\
518   4: b4 6c 00\n\
518   4: b4 6e 00\n\
518   4: b4 70 00\n\
518   4: b4 72 00\n\
518   4: b4 74 00\n\
518   4: b4 76 00\n\
518   4: b4 02 00\n\
518   4: b4 04 00\n\
518   4: b4 09 00\n\
518   4: b4 0c 00\n\
518   4: b4 0e 00\n\
518   4: b4 10 00\n\
518   4: b4 12 00\n\
518   4: b4 14 00\n\
518   4: b4 16 00\n\
518   4: b4 18 00\n\
518   4: b4 1a 00\n\
518   4: b4 1c 00\n\
518   4: b4 1e 00\n\
518   4: b4 21 00\n\
518   4: b4 23 00\n\
518   4: b4 25 00\n\
518   4: b4 28 00\n\
518   4: b4 2a 00\n\
518   4: b4 2c 00\n\
518   4: b4 2e 00\n\
518   4: b4 30 00\n\
518   4: b4 32 00\n\
518   4: b4 34 00\n\
518   4: b4 36 00\n\
518   4: b4 38 00\n\
518   4: b4 3a 00\n\
518   4: b4 3c 00\n\
518   4: b4 3e 00\n\
518   4: b4 41 00\n\
518   4: b4 51 00\n\
518   4: b4 53 00\n\
518   4: b4 55 00\n\
518   4: b4 57 00\n\
518   4: b4 59 00\n\
518   4: b4 62 7f\n\
518   4: b4 63 7f\n\
518   4: b4 64 7f\n\
518   4: b4 65 7f\n\
518   4: b4 67 00\n\
518   4: b4 69 00\n\
518   4: b4 6b 00\n\
518   4: b4 6d 00\n\
518   4: b4 6f 00\n\
518   4: b4 71 00\n\
518   4: b4 73 00\n\
518   4: b4 75 00\n\
518   4: b4 77 00\n\
519   4: 84 40 4d\n\
520   5: b5 00 25\n\
520   5: b5 20 45\n\
520   5: 95 40 4f\n\
521   5: 85 40 4f\n\
522   6: b6 00 25\n\
522   6: b6 20 45\n\
522   6: 96 40 4f\n\
523   6: 86 40 4f\n\
524   7: b7 00 25\n\
524   7: b7 20 45\n\
524   7: 97 40 4f\n\
525   7: 87 40 4f\n\
526   8: b8 00 25\n\
526   8: b8 20 45\n\
526   8: 98 40 4f\n\
527   8: 88 40 4f\n\
528  10: ba 00 25\n\
528  10: ba 20 45\n\
528  10: 9a 40 4f\n\
529  10: 8a 40 4f\n\
531  11: bb 00 25\n\
531  11: bb 20 45\n\
531  11: 9b 40 4f\n\
531  11: 8b 40 4f\n\
532  12: bc 00 25\n\
532  12: bc 20 45\n\
532  12: 9c 40 4f\n\
533  12: 8c 40 4f\n\
534  13: bd 00 25\n\
534  13: bd 20 45\n\
534  13: 9d 40 4f\n\
535  13: 8d 40 4f\n\
536  14: be 00 25\n\
536  14: be 20 45\n\
536  14: 9e 40 4f\n\
537  14: 8e 40 4f\n\
538  15: bf 00 25\n\
538  15: bf 20 45\n\
538  15: 9f 40 4f\n\
539  15: 8f 40 4f\n\
540   0: b0 00 25\n\
540   0: b0 20 45\n\
540   0: 90 40 4f\n\
541   0: 80 40 4f\n\
542   1: b1 00 25\n\
542   1: b1 20 45\n\
542   1: 91 40 4f\n\
543   1: 81 40 4f\n\
544   2: b2 00 25\n\
544   2: b2 20 45\n\
544   2: 92 40 4f\n\
545   2: 82 40 40\n\
546 ...closed.\n\
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
  04 ·  04 ·  02 ·  18 ·  08 ·  00 ·  e0 ·  00 ·    40 @  00 ·  b0 ·  7a z  00 ·  00 ·  b0 ·  7d }\n\
  00 ·  00 ·  b0 ·  7f ·  00 ·  00 ·  b0 ·  65 e    00 ·  00 ·  b0 ·  64 d  00 ·  00 ·  b0 ·  06 ·\n\
  02 ·  00 ·  b0 ·  26 &  00 ·  00 ·  e1 ·  00 ·    40 @  00 ·  b1 ·  7a z  00 ·  00 ·  b1 ·  7d }\n\
  00 ·  00 ·  b1 ·  7f ·  00 ·  00 ·  b1 ·  65 e    00 ·  00 ·  b1 ·  64 d  00 ·  00 ·  b1 ·  06 ·\n\
  02 ·  00 ·  b1 ·  26 &  00 ·  00 ·  e2 ·  00 ·    40 @  00 ·  b2 ·  7a z  00 ·  00 ·  b2 ·  7d }\n\
  00 ·  00 ·  b2 ·  7f ·  00 ·  00 ·  b2 ·  65 e    00 ·  00 ·  b2 ·  64 d  00 ·  00 ·  b2 ·  06 ·\n\
  02 ·  00 ·  b2 ·  26 &  00 ·  00 ·  e3 ·  00 ·    40 @  00 ·  b3 ·  7a z  00 ·  00 ·  b3 ·  7d }\n\
  00 ·  00 ·  b3 ·  7f ·  00 ·  00 ·  b3 ·  65 e    00 ·  00 ·  b3 ·  64 d  00 ·  00 ·  b3 ·  06 ·\n\
  02 ·  00 ·  b3 ·  26 &  00 ·  00 ·  e4 ·  00 ·    40 @  00 ·  b4 ·  7a z  00 ·  00 ·  b4 ·  7d }\n\
  00 ·  00 ·  b4 ·  7f ·  00 ·  00 ·  b4 ·  65 e    00 ·  00 ·  b4 ·  64 d  00 ·  00 ·  b4 ·  06 ·\n\
  02 ·  00 ·  b4 ·  26 &  00 ·  00 ·  e5 ·  00 ·    40 @  00 ·  b5 ·  7a z  00 ·  00 ·  b5 ·  7d }\n\
  00 ·  00 ·  b5 ·  7f ·  00 ·  00 ·  b5 ·  65 e    00 ·  00 ·  b5 ·  64 d  00 ·  00 ·  b5 ·  06 ·\n\
  02 ·  00 ·  b5 ·  26 &  00 ·  00 ·  e6 ·  00 ·    40 @  00 ·  b6 ·  7a z  00 ·  00 ·  b6 ·  7d }\n\
  00 ·  00 ·  b6 ·  7f ·  00 ·  00 ·  b6 ·  65 e    00 ·  00 ·  b6 ·  64 d  00 ·  00 ·  b6 ·  06 ·\n\
  02 ·  00 ·  b6 ·  26 &  00 ·  00 ·  e7 ·  00 ·    40 @  00 ·  b7 ·  7a z  00 ·  00 ·  b7 ·  7d }\n\
  00 ·  00 ·  b7 ·  7f ·  00 ·  00 ·  b7 ·  65 e    00 ·  00 ·  b7 ·  64 d  00 ·  00 ·  b7 ·  06 ·\n\
  02 ·  00 ·  b7 ·  26 &  00 ·  00 ·  e8 ·  00 ·    40 @  00 ·  b8 ·  7a z  00 ·  00 ·  b8 ·  7d }\n\
  00 ·  00 ·  b8 ·  7f ·  00 ·  00 ·  b8 ·  65 e    00 ·  00 ·  b8 ·  64 d  00 ·  00 ·  b8 ·  06 ·\n\
  02 ·  00 ·  b8 ·  26 &  00 ·  00 ·  e9 ·  00 ·    40 @  00 ·  b9 ·  7a z  00 ·  00 ·  b9 ·  7d }\n\
  00 ·  00 ·  b9 ·  7f ·  00 ·  00 ·  b9 ·  65 e    00 ·  00 ·  b9 ·  64 d  00 ·  00 ·  b9 ·  06 ·\n\
  02 ·  00 ·  b9 ·  26 &  00 ·  00 ·  ea ·  00 ·    40 @  00 ·  ba ·  7a z  00 ·  00 ·  ba ·  7d }\n\
  00 ·  00 ·  ba ·  7f ·  00 ·  00 ·  ba ·  65 e    00 ·  00 ·  ba ·  64 d  00 ·  00 ·  ba ·  06 ·\n\
  02 ·  00 ·  ba ·  26 &  00 ·  00 ·  eb ·  00 ·    40 @  00 ·  bb ·  7a z  00 ·  00 ·  bb ·  7d }\n\
  00 ·  00 ·  bb ·  7f ·  00 ·  00 ·  bb ·  65 e    00 ·  00 ·  bb ·  64 d  00 ·  00 ·  bb ·  06 ·\n\
  02 ·  00 ·  bb ·  26 &  00 ·  00 ·  ec ·  00 ·    40 @  00 ·  bc ·  7a z  00 ·  00 ·  bc ·  7d }\n\
  00 ·  00 ·  bc ·  7f ·  00 ·  00 ·  bc ·  65 e    00 ·  00 ·  bc ·  64 d  00 ·  00 ·  bc ·  06 ·\n\
  02 ·  00 ·  bc ·  26 &  00 ·  00 ·  ed ·  00 ·    40 @  00 ·  bd ·  7a z  00 ·  00 ·  bd ·  7d }\n\
  00 ·  00 ·  bd ·  7f ·  00 ·  00 ·  bd ·  65 e    00 ·  00 ·  bd ·  64 d  00 ·  00 ·  bd ·  06 ·\n\
  02 ·  00 ·  bd ·  26 &  00 ·  00 ·  ee ·  00 ·    40 @  00 ·  be ·  7a z  00 ·  00 ·  be ·  7d }\n\
  00 ·  00 ·  be ·  7f ·  00 ·  00 ·  be ·  65 e    00 ·  00 ·  be ·  64 d  00 ·  00 ·  be ·  06 ·\n\
  02 ·  00 ·  be ·  26 &  00 ·  00 ·  ef ·  00 ·    40 @  00 ·  bf ·  7a z  00 ·  00 ·  bf ·  7d }\n\
  00 ·  00 ·  bf ·  7f ·  00 ·  00 ·  bf ·  65 e    00 ·  00 ·  bf ·  64 d  00 ·  00 ·  bf ·  06 ·\n\
");

	CheckStr = _T("\
  4d M  54 T  68 h  64 d  00 ·  00 ·  00 ·  06 ·    00 ·  00 ·  00 ·  01 ·  e7 ·  28 (  4d M  54 T\n\
  72 r  6b k  00 ·  00 ·  02 ·  13 ·  00 ·  ff ·    51 Q  03 ·  07 ·  d0 ·  00 ·  00 ·  ff ·  58 X\n\
")
		+ DataStr + _T("\
  02 ·  00 ·  bf ·  26 &  00 ·  00 ·  ff ·  2f /    00 ·\n\
");

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

	CheckStr = _T("\
  4d M  54 T  68 h  64 d  00 ·  00 ·  00 ·  06 ·    00 ·  00 ·  00 ·  01 ·  e7 ·  28 (  4d M  54 T\n\
  72 r  6b k  00 ·  00 ·  02 ·  19 ·  00 ·  ff ·    51 Q  03 ·  07 ·  d0 ·  00 ·  00 ·  ff ·  58 X\n\
")
		+ DataStr + _T("\
  02 ·  00 ·  bf ·  26 &  00 ·  81 ·  a9 ·  4f O    90 ·  3c <  7f ·  00 ·  ff ·  2f /  00 ·\n\
");

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


	DataStr += _T("\
  02 ·  00 ·  bf ·  26 &  00 ·  81 ·  a9 ·  4f O    90 ·  3c <  7f ·  d2 ·  67 g  91 ·  40 @  1f ·\n\
");

	CheckStr = _T("\
  4d M  54 T  68 h  64 d  00 ·  00 ·  00 ·  06 ·    00 ·  00 ·  00 ·  01 ·  e7 ·  28 (  4d M  54 T\n\
  72 r  6b k  00 ·  00 ·  02 ·  1e ·  00 ·  ff ·    51 Q  03 ·  07 ·  d0 ·  00 ·  00 ·  ff ·  58 X\n\
")
		+ DataStr + _T("\
  00 ·  ff ·  2f /  00 ·\n\
");

	CPPUNIT_ASSERT(CheckOut(CheckStr,__LINE__,_T(__FILE__)));
	CPPUNIT_ASSERT(delta == 10330000);
	mutabor::CurrentTime += delta;

	delta = in -> PrepareNextEvent();
	DEBUGLOG(midiio,_T("delta = %d, Current time = %ld"),delta,mutabor::CurrentTime.Get());

	CheckStr = _T("\
  4d M  54 T  68 h  64 d  00 ·  00 ·  00 ·  06 ·    00 ·  00 ·  00 ·  01 ·  e7 ·  28 (  4d M  54 T\n\
  72 r  6b k  00 ·  00 ·  02 ·  23 #  00 ·  ff ·    51 Q  03 ·  07 ·  d0 ·  00 ·  00 ·  ff ·  58 X\n\
")
		+ DataStr + _T("\
  d0 ·  5a Z  81 ·  40 @  40 @  00 ·  ff ·  2f /    00 ·\n\
");

	CPPUNIT_ASSERT(CheckOut(CheckStr,__LINE__,_T(__FILE__)));
	CPPUNIT_ASSERT(delta == 10330000);
	mutabor::CurrentTime += delta;

	delta = in -> PrepareNextEvent();
	DEBUGLOG(midiio,_T("delta = %d, Current time = %ld"),delta,mutabor::CurrentTime.Get());

	CheckStr = _T("\
  4d M  54 T  68 h  64 d  00 ·  00 ·  00 ·  06 ·    00 ·  00 ·  00 ·  01 ·  e7 ·  28 (  4d M  54 T\n\
  72 r  6b k  00 ·  00 ·  02 ·  28 (  00 ·  ff ·    51 Q  03 ·  07 ·  d0 ·  00 ·  00 ·  ff ·  58 X\n\
")
		+ DataStr + _T("\
  d0 ·  5a Z  81 ·  40 @  40 @  d0 ·  5a Z  92 ·    43 C  3f ?  00 ·  ff ·  2f /  00 ·\n\
");


	CPPUNIT_ASSERT(CheckOut(CheckStr,__LINE__,_T(__FILE__)));
	CPPUNIT_ASSERT(delta == 10330000);
	mutabor::CurrentTime += delta;

	delta = in -> PrepareNextEvent();
	DEBUGLOG(midiio,_T("delta = %d, Current time = %ld"),delta,mutabor::CurrentTime.Get());
	CheckStr = _T("\
  4d M  54 T  68 h  64 d  00 ·  00 ·  00 ·  06 ·    00 ·  00 ·  00 ·  01 ·  e7 ·  28 (  4d M  54 T\n\
  72 r  6b k  00 ·  00 ·  02 ·  2d -  00 ·  ff ·    51 Q  03 ·  07 ·  d0 ·  00 ·  00 ·  ff ·  58 X\n\
")
		+ DataStr + _T("\
  d0 ·  5a Z  81 ·  40 @  40 @  d0 ·  5a Z  92 ·    43 C  3f ?  d0 ·  5a Z  82 ·  43 C  40 @  00 ·\n\
  ff ·  2f /  00 ·\n\
");
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

	DataStr += _T("\
  d0 ·  5a Z  81 ·  40 @  40 @  d0 ·  5a Z  92 ·    43 C  3f ?  d0 ·  5a Z  82 ·  43 C  40 @  ec ·\n\
");
	CheckStr = _T("\
  4d M  54 T  68 h  64 d  00 ·  00 ·  00 ·  06 ·    00 ·  00 ·  00 ·  01 ·  e7 ·  28 (  4d M  54 T\n\
  72 r  6b k  00 ·  00 ·  02 ·  32 2  00 ·  ff ·    51 Q  03 ·  07 ·  d0 ·  00 ·  00 ·  ff ·  58 X\n\
")
		+ DataStr + _T("\
  56 V  93 ·  34 4  7f ·  00 ·  ff ·  2f /  00 ·\n\
");
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

	CheckStr = _T("\
  4d M  54 T  68 h  64 d  00 ·  00 ·  00 ·  06 ·    00 ·  00 ·  00 ·  01 ·  e7 ·  28 (  4d M  54 T\n\
  72 r  6b k  00 ·  00 ·  02 ·  37 7  00 ·  ff ·    51 Q  03 ·  07 ·  d0 ·  00 ·  00 ·  ff ·  58 X\n\
")
		+ DataStr + _T("\
  56 V  93 ·  34 4  7f ·  e9 ·  58 X  83 ·  34 4    40 @  00 ·  ff ·  2f /  00 ·\n\
");
	CPPUNIT_ASSERT(CheckOut(CheckStr,__LINE__,_T(__FILE__)));
	CPPUNIT_ASSERT(delta == 13510000);
	mutabor::CurrentTime += delta;

	delta = in -> PrepareNextEvent();
	DEBUGLOG(midiio,_T("delta = %d, Current time = %ld"),delta,mutabor::CurrentTime.Get());
	CheckStr = _T("\
  4d M  54 T  68 h  64 d  00 ·  00 ·  00 ·  06 ·    00 ·  00 ·  00 ·  01 ·  e7 ·  28 (  4d M  54 T\n\
  72 r  6b k  00 ·  00 ·  02 ·  3c <  00 ·  ff ·    51 Q  03 ·  07 ·  d0 ·  00 ·  00 ·  ff ·  58 X\n\
")
		+ DataStr + _T("\
  56 V  93 ·  34 4  7f ·  e9 ·  58 X  83 ·  34 4    40 @  e9 ·  46 F  80 ·  3c <  7f ·  00 ·  ff ·\n\
  2f /  00 ·\n\
");
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
  4d M  54 T  68 h  64 d  00 ·  00 ·  00 ·  06 ·    00 ·  00 ·  00 ·  01 ·  e7 ·  28 (  4d M  54 T\n\
  72 r  6b k  00 ·  00 ·  02 ·  53 S  00 ·  ff ·    51 Q  03 ·  07 ·  d0 ·  00 ·  00 ·  ff ·  58 X\n\
  04 ·  04 ·  02 ·  18 ·  08 ·  00 ·  e0 ·  00 ·    40 @  00 ·  b0 ·  7a z  00 ·  00 ·  b0 ·  7d }\n\
  00 ·  00 ·  b0 ·  7f ·  00 ·  00 ·  b0 ·  65 e    00 ·  00 ·  b0 ·  64 d  00 ·  00 ·  b0 ·  06 ·\n\
  02 ·  00 ·  b0 ·  26 &  00 ·  00 ·  e1 ·  00 ·    40 @  00 ·  b1 ·  7a z  00 ·  00 ·  b1 ·  7d }\n\
  00 ·  00 ·  b1 ·  7f ·  00 ·  00 ·  b1 ·  65 e    00 ·  00 ·  b1 ·  64 d  00 ·  00 ·  b1 ·  06 ·\n\
  02 ·  00 ·  b1 ·  26 &  00 ·  00 ·  e2 ·  00 ·    40 @  00 ·  b2 ·  7a z  00 ·  00 ·  b2 ·  7d }\n\
  00 ·  00 ·  b2 ·  7f ·  00 ·  00 ·  b2 ·  65 e    00 ·  00 ·  b2 ·  64 d  00 ·  00 ·  b2 ·  06 ·\n\
  02 ·  00 ·  b2 ·  26 &  00 ·  00 ·  e3 ·  00 ·    40 @  00 ·  b3 ·  7a z  00 ·  00 ·  b3 ·  7d }\n\
  00 ·  00 ·  b3 ·  7f ·  00 ·  00 ·  b3 ·  65 e    00 ·  00 ·  b3 ·  64 d  00 ·  00 ·  b3 ·  06 ·\n\
  02 ·  00 ·  b3 ·  26 &  00 ·  00 ·  e4 ·  00 ·    40 @  00 ·  b4 ·  7a z  00 ·  00 ·  b4 ·  7d }\n\
  00 ·  00 ·  b4 ·  7f ·  00 ·  00 ·  b4 ·  65 e    00 ·  00 ·  b4 ·  64 d  00 ·  00 ·  b4 ·  06 ·\n\
  02 ·  00 ·  b4 ·  26 &  00 ·  00 ·  e5 ·  00 ·    40 @  00 ·  b5 ·  7a z  00 ·  00 ·  b5 ·  7d }\n\
  00 ·  00 ·  b5 ·  7f ·  00 ·  00 ·  b5 ·  65 e    00 ·  00 ·  b5 ·  64 d  00 ·  00 ·  b5 ·  06 ·\n\
  02 ·  00 ·  b5 ·  26 &  00 ·  00 ·  e6 ·  00 ·    40 @  00 ·  b6 ·  7a z  00 ·  00 ·  b6 ·  7d }\n\
  00 ·  00 ·  b6 ·  7f ·  00 ·  00 ·  b6 ·  65 e    00 ·  00 ·  b6 ·  64 d  00 ·  00 ·  b6 ·  06 ·\n\
  02 ·  00 ·  b6 ·  26 &  00 ·  00 ·  e7 ·  00 ·    40 @  00 ·  b7 ·  7a z  00 ·  00 ·  b7 ·  7d }\n\
  00 ·  00 ·  b7 ·  7f ·  00 ·  00 ·  b7 ·  65 e    00 ·  00 ·  b7 ·  64 d  00 ·  00 ·  b7 ·  06 ·\n\
  02 ·  00 ·  b7 ·  26 &  00 ·  00 ·  e8 ·  00 ·    40 @  00 ·  b8 ·  7a z  00 ·  00 ·  b8 ·  7d }\n\
  00 ·  00 ·  b8 ·  7f ·  00 ·  00 ·  b8 ·  65 e    00 ·  00 ·  b8 ·  64 d  00 ·  00 ·  b8 ·  06 ·\n\
  02 ·  00 ·  b8 ·  26 &  00 ·  00 ·  e9 ·  00 ·    40 @  00 ·  b9 ·  7a z  00 ·  00 ·  b9 ·  7d }\n\
  00 ·  00 ·  b9 ·  7f ·  00 ·  00 ·  b9 ·  65 e    00 ·  00 ·  b9 ·  64 d  00 ·  00 ·  b9 ·  06 ·\n\
  02 ·  00 ·  b9 ·  26 &  00 ·  00 ·  ea ·  00 ·    40 @  00 ·  ba ·  7a z  00 ·  00 ·  ba ·  7d }\n\
  00 ·  00 ·  ba ·  7f ·  00 ·  00 ·  ba ·  65 e    00 ·  00 ·  ba ·  64 d  00 ·  00 ·  ba ·  06 ·\n\
  02 ·  00 ·  ba ·  26 &  00 ·  00 ·  eb ·  00 ·    40 @  00 ·  bb ·  7a z  00 ·  00 ·  bb ·  7d }\n\
  00 ·  00 ·  bb ·  7f ·  00 ·  00 ·  bb ·  65 e    00 ·  00 ·  bb ·  64 d  00 ·  00 ·  bb ·  06 ·\n\
  02 ·  00 ·  bb ·  26 &  00 ·  00 ·  ec ·  00 ·    40 @  00 ·  bc ·  7a z  00 ·  00 ·  bc ·  7d }\n\
  00 ·  00 ·  bc ·  7f ·  00 ·  00 ·  bc ·  65 e    00 ·  00 ·  bc ·  64 d  00 ·  00 ·  bc ·  06 ·\n\
  02 ·  00 ·  bc ·  26 &  00 ·  00 ·  ed ·  00 ·    40 @  00 ·  bd ·  7a z  00 ·  00 ·  bd ·  7d }\n\
  00 ·  00 ·  bd ·  7f ·  00 ·  00 ·  bd ·  65 e    00 ·  00 ·  bd ·  64 d  00 ·  00 ·  bd ·  06 ·\n\
  02 ·  00 ·  bd ·  26 &  00 ·  00 ·  ee ·  00 ·    40 @  00 ·  be ·  7a z  00 ·  00 ·  be ·  7d }\n\
  00 ·  00 ·  be ·  7f ·  00 ·  00 ·  be ·  65 e    00 ·  00 ·  be ·  64 d  00 ·  00 ·  be ·  06 ·\n\
  02 ·  00 ·  be ·  26 &  00 ·  00 ·  ef ·  00 ·    40 @  00 ·  bf ·  7a z  00 ·  00 ·  bf ·  7d }\n\
  00 ·  00 ·  bf ·  7f ·  00 ·  00 ·  bf ·  65 e    00 ·  00 ·  bf ·  64 d  00 ·  00 ·  bf ·  06 ·\n\
  02 ·  00 ·  bf ·  26 &  00 ·  00 ·  90 ·  3c <    7f ·  00 ·  b0 ·  65 e  00 ·  00 ·  b0 ·  64 d\n\
  00 ·  00 ·  91 ·  40 @  1f ·  00 ·  b1 ·  65 e    00 ·  00 ·  b1 ·  64 d  00 ·  00 ·  81 ·  40 @\n\
  40 @  00 ·  92 ·  43 C  3f ?  00 ·  b2 ·  65 e    00 ·  00 ·  b2 ·  64 d  00 ·  00 ·  82 ·  43 C\n\
  40 @  00 ·  93 ·  34 4  7f ·  00 ·  b3 ·  65 e    00 ·  00 ·  b3 ·  64 d  00 ·  00 ·  83 ·  34 4\n\
  40 @  00 ·  80 ·  3c <  7f ·  00 ·  ff ·  2f /    00 ·\n\
");

	CPPUNIT_ASSERT(CheckOut(CheckStr,__LINE__,_T(__FILE__)));
}

///\}

/** \file               -*- C++ -*-
 ********************************************************************
 * Test common midi functions
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
 * \addtogroup route
 * \{
 ********************************************************************/
#include <sstream>
#include <set>
#include "src/kernel/Defs.h"
#include "src/kernel/routing/midi/tests/midicmnTest.h"
#include "src/kernel/routing/midi/midicmn-inlines.h"
#include "src/kernel/routing/Route-inlines.h"
#include "src/kernel/Runtime.cpp"

template class mutabor::CommonMidiOutput<mutabor::DebugMidiOutputProvider,
					 mutabor::minimalOutputDeviceClass>;


bool midicmnOutputDevice::unsortedCheck(const std::string & s,
					int line,
					const std::string & filename)
{
	mutUnused(line);
	mutUnused(filename);
	std::multiset<std::string> left, right;
	std::stringstream str;
	std::string cmd;
	str.str(s);
	while (getline(str, cmd)) {
		left.insert(cmd);
	}

	cmd = Out;
	str.str(cmd);
	str.clear();
	str.seekg(0);
	while (getline(str, cmd)) {
		right.insert(cmd);
	}

	bool retval = (left == right);
	if (!retval) {
		DEBUGLOG (always, "Check failed:\n%s:%d:" ,filename.c_str(),line);
		str.str("");
		std::multiset<std::string>::iterator
			lit = left.begin(),
			rit = right.begin();
		while (lit != left.end() && rit != right.end()) {
			if (lit == left.end()) {
				str << "-" << *(rit++) << std::endl;
			} else if (rit == right.end()) {
				str << "+" << *(lit++) << std::endl;
			} else if (*lit < *rit) {
				str << "+" << *(lit++) << std::endl;
			} else if (*rit < *lit) {
				str << "-" << *(rit++) << std::endl;
			} else {
				str << " " << *(lit++) << std::endl;
				rit++;
			}
		}

		DEBUGLOG (always, "Diff:\n%s" ,str.str().c_str());
	}
	Out.ClearData();
	//		retval = true;
	return retval;
}


void CommonMidiOutputTest::setUp()
{
// change DEBUGA to DEBUG in case you need the debug output
#ifdef DEBUG
//	debugFlags::flags.timer = true;
//	debugFlags::flags.midiio = true;
#endif
	CPPUNIT_ASSERT(mutabor::InputDeviceClass::GetDeviceList().empty());
	CPPUNIT_ASSERT(mutabor::OutputDeviceClass::GetDeviceList().empty());
	CPPUNIT_ASSERT(mutabor::RouteClass::GetRouteList().empty());
	CPPUNIT_ASSERT(mutabor::BoxClass::GetBoxList().empty());
	route = mutabor::RouteFactory::Create();
	box = mutabor::BoxFactory::Create(mutabor::Box0,0);
	connect(route, box);

	mutabor::CurrentTime.UseRealtime(true);
	out = new midicmnOutputDevice(("Test"));
	guard = out;

	connect(route, guard);
	route->SetOutputFrom (0);
	route->SetOutputTo (15);
	route->OutputAvoidDrumChannel (true);
}

void CommonMidiOutputTest::tearDown()
{
	guard->Destroy();
	route->Destroy();
	out = NULL;
	guard.reset();
	route.reset();
	box -> Destroy();
	box.reset();

	CPPUNIT_ASSERT(mutabor::InputDeviceClass::GetDeviceList().empty());
	CPPUNIT_ASSERT(mutabor::OutputDeviceClass::GetDeviceList().empty());
	CPPUNIT_ASSERT(mutabor::RouteClass::GetRouteList().empty());
	CPPUNIT_ASSERT(mutabor::BoxClass::GetBoxList().empty());
#ifdef DEBUG
//	mutabor::mutabor_debug_flags.timer = false;
//	mutabor::mutabor_debug_flags.midiio = false;
#endif
}


void CommonMidiOutputTest::testNoteOnOff()
{
	CPPUNIT_ASSERT( out );
	CPPUNIT_ASSERT(out->Open());
	if (!box->Compile(NULL, "")) {
		CPPUNIT_FAIL(box->get_errors());
	}
	CPPUNIT_ASSERT(box->Open());
	CPPUNIT_ASSERT( out->Check(("Opened...\n"
				      "  0: e0 00 40\n"
				      "  0: b0 7a 00\n"
				      "  0: b0 7d 00\n"
				      "  0: b0 7f 00\n"
				      "  0: b0 65 00\n"
				      "  0: b0 64 00\n"
				      "  0: b0 06 02\n"
				      "  0: b0 26 00\n"
				      "  1: e1 00 40\n"
				      "  1: b1 7a 00\n"
				      "  1: b1 7d 00\n"
				      "  1: b1 7f 00\n"
				      "  1: b1 65 00\n"
				      "  1: b1 64 00\n"
				      "  1: b1 06 02\n"
				      "  1: b1 26 00\n"
				      "  2: e2 00 40\n"
				      "  2: b2 7a 00\n"
				      "  2: b2 7d 00\n"
				      "  2: b2 7f 00\n"
				      "  2: b2 65 00\n"
				      "  2: b2 64 00\n"
				      "  2: b2 06 02\n"
				      "  2: b2 26 00\n"
				      "  3: e3 00 40\n"
				      "  3: b3 7a 00\n"
				      "  3: b3 7d 00\n"
				      "  3: b3 7f 00\n"
				      "  3: b3 65 00\n"
				      "  3: b3 64 00\n"
				      "  3: b3 06 02\n"
				      "  3: b3 26 00\n"
				      "  4: e4 00 40\n"
				      "  4: b4 7a 00\n"
				      "  4: b4 7d 00\n"
				      "  4: b4 7f 00\n"
				      "  4: b4 65 00\n"
				      "  4: b4 64 00\n"
				      "  4: b4 06 02\n"
				      "  4: b4 26 00\n"
				      "  5: e5 00 40\n"
				      "  5: b5 7a 00\n"
				      "  5: b5 7d 00\n"
				      "  5: b5 7f 00\n"
				      "  5: b5 65 00\n"
				      "  5: b5 64 00\n"
				      "  5: b5 06 02\n"
				      "  5: b5 26 00\n"
				      "  6: e6 00 40\n"
				      "  6: b6 7a 00\n"
				      "  6: b6 7d 00\n"
				      "  6: b6 7f 00\n"
				      "  6: b6 65 00\n"
				      "  6: b6 64 00\n"
				      "  6: b6 06 02\n"
				      "  6: b6 26 00\n"
				      "  7: e7 00 40\n"
				      "  7: b7 7a 00\n"
				      "  7: b7 7d 00\n"
				      "  7: b7 7f 00\n"
				      "  7: b7 65 00\n"
				      "  7: b7 64 00\n"
				      "  7: b7 06 02\n"
				      "  7: b7 26 00\n"
				      "  8: e8 00 40\n"
				      "  8: b8 7a 00\n"
				      "  8: b8 7d 00\n"
				      "  8: b8 7f 00\n"
				      "  8: b8 65 00\n"
				      "  8: b8 64 00\n"
				      "  8: b8 06 02\n"
				      "  8: b8 26 00\n"
				      "  9: e9 00 40\n"
				      "  9: b9 7a 00\n"
				      "  9: b9 7d 00\n"
				      "  9: b9 7f 00\n"
				      "  9: b9 65 00\n"
				      "  9: b9 64 00\n"
				      "  9: b9 06 02\n"
				      "  9: b9 26 00\n"
				      " 10: ea 00 40\n"
				      " 10: ba 7a 00\n"
				      " 10: ba 7d 00\n"
				      " 10: ba 7f 00\n"
				      " 10: ba 65 00\n"
				      " 10: ba 64 00\n"
				      " 10: ba 06 02\n"
				      " 10: ba 26 00\n"
				      " 11: eb 00 40\n"
				      " 11: bb 7a 00\n"
				      " 11: bb 7d 00\n"
				      " 11: bb 7f 00\n"
				      " 11: bb 65 00\n"
				      " 11: bb 64 00\n"
				      " 11: bb 06 02\n"
				      " 11: bb 26 00\n"
				      " 12: ec 00 40\n"
				      " 12: bc 7a 00\n"
				      " 12: bc 7d 00\n"
				      " 12: bc 7f 00\n"
				      " 12: bc 65 00\n"
				      " 12: bc 64 00\n"
				      " 12: bc 06 02\n"
				      " 12: bc 26 00\n"
				      " 13: ed 00 40\n"
				      " 13: bd 7a 00\n"
				      " 13: bd 7d 00\n"
				      " 13: bd 7f 00\n"
				      " 13: bd 65 00\n"
				      " 13: bd 64 00\n"
				      " 13: bd 06 02\n"
				      " 13: bd 26 00\n"
				      " 14: ee 00 40\n"
				      " 14: be 7a 00\n"
				      " 14: be 7d 00\n"
				      " 14: be 7f 00\n"
				      " 14: be 65 00\n"
				      " 14: be 64 00\n"
				      " 14: be 06 02\n"
				      " 14: be 26 00\n"
				      " 15: ef 00 40\n"
				      " 15: bf 7a 00\n"
				      " 15: bf 7d 00\n"
				      " 15: bf 7f 00\n"
				      " 15: bf 65 00\n"
				      " 15: bf 64 00\n"
				      " 15: bf 06 02\n"
				      " 15: bf 26 00\n"), __LINE__, (__FILE__)) );

	/* check all permutations */

	DEBUGLOG (midiio, "123" );

	out->NoteOn(box,56,96,route.get(),0,cd);
	CPPUNIT_ASSERT( out->Check(("  0: 90 38 60\n"), __LINE__, (__FILE__) ) );
	out->NoteOn(box,60,97,route.get(),0,cd);
	CPPUNIT_ASSERT( out->Check(("  1: 91 3c 61\n"), __LINE__, (__FILE__) ) );
	out->NoteOn(box,63,98,route.get(),0,cd);
	CPPUNIT_ASSERT( out->Check(("  2: 92 3f 62\n"), __LINE__, (__FILE__) ) );

	out->NoteOff(box,56,53,route.get(),0,false);
	CPPUNIT_ASSERT( out->Check(("  0: 80 38 35\n"), __LINE__, (__FILE__)) );
	out->NoteOff(box,60,54,route.get(),0,false);
	CPPUNIT_ASSERT( out->Check(("  1: 81 3c 36\n"), __LINE__, (__FILE__)) );
	out->NoteOff(box,63,55,route.get(),0,false);
	CPPUNIT_ASSERT( out->Check(("  2: 82 3f 37\n"), __LINE__, (__FILE__)) );

	DEBUGLOG (midiio, "132" );

	out->NoteOn(box,56,96,route.get(),0,cd);
	CPPUNIT_ASSERT( out->Check(("  3: 93 38 60\n"), __LINE__, (__FILE__) ) );
	out->NoteOn(box,60,97,route.get(),0,cd);
	CPPUNIT_ASSERT( out->Check(("  4: 94 3c 61\n"), __LINE__, (__FILE__) ) );
	out->NoteOn(box,63,98,route.get(),0,cd);
	CPPUNIT_ASSERT( out->Check(("  5: 95 3f 62\n"), __LINE__, (__FILE__) ) );

	out->NoteOff(box,56,53,route.get(),0,false);
	CPPUNIT_ASSERT( out->Check(("  3: 83 38 35\n"), __LINE__, (__FILE__)) );
	out->NoteOff(box,63,55,route.get(),0,false);
	CPPUNIT_ASSERT( out->Check(("  5: 85 3f 37\n"), __LINE__, (__FILE__)) );
	out->NoteOff(box,60,54,route.get(),0,false);
	CPPUNIT_ASSERT( out->Check(("  4: 84 3c 36\n"), __LINE__, (__FILE__)) );

	DEBUGLOG (midiio, "213" );

	out->NoteOn(box,56,96,route.get(),0,cd);
	CPPUNIT_ASSERT( out->Check(("  6: 96 38 60\n"), __LINE__, (__FILE__) ) );
	out->NoteOn(box,60,97,route.get(),0,cd);
	CPPUNIT_ASSERT( out->Check(("  7: 97 3c 61\n"), __LINE__, (__FILE__) ) );
	out->NoteOn(box,63,98,route.get(),0,cd);
	CPPUNIT_ASSERT( out->Check(("  8: 98 3f 62\n"), __LINE__, (__FILE__) ) );

	out->NoteOff(box,60,54,route.get(),0,false);
	CPPUNIT_ASSERT( out->Check(("  7: 87 3c 36\n"), __LINE__, (__FILE__)) );
	out->NoteOff(box,56,53,route.get(),0,false);
	CPPUNIT_ASSERT( out->Check(("  6: 86 38 35\n"), __LINE__, (__FILE__)) );
	out->NoteOff(box,63,55,route.get(),0,false);
	CPPUNIT_ASSERT( out->Check(("  8: 88 3f 37\n"), __LINE__, (__FILE__)) );

	DEBUGLOG (midiio, "231" );

	out->NoteOn(box,56,96,route.get(),0,cd);
	CPPUNIT_ASSERT( out->Check((" 10: 9a 38 60\n"), __LINE__, (__FILE__) ) );
	out->NoteOn(box,60,97,route.get(),0,cd);
	CPPUNIT_ASSERT( out->Check((" 11: 9b 3c 61\n"), __LINE__, (__FILE__) ) );
	out->NoteOn(box,63,98,route.get(),0,cd);
	CPPUNIT_ASSERT( out->Check((" 12: 9c 3f 62\n"), __LINE__, (__FILE__) ) );

	out->NoteOff(box,60,54,route.get(),0,false);
	CPPUNIT_ASSERT( out->Check((" 11: 8b 3c 36\n"), __LINE__, (__FILE__)) );
	out->NoteOff(box,63,55,route.get(),0,false);
	CPPUNIT_ASSERT( out->Check((" 12: 8c 3f 37\n"), __LINE__, (__FILE__)) );
	out->NoteOff(box,56,53,route.get(),0,false);
	CPPUNIT_ASSERT( out->Check((" 10: 8a 38 35\n"), __LINE__, (__FILE__)) );

	DEBUGLOG (midiio, "312" );

	out->NoteOn(box,56,96,route.get(),0,cd);
	CPPUNIT_ASSERT( out->Check((" 13: 9d 38 60\n"), __LINE__, (__FILE__) ) );
	out->NoteOn(box,60,97,route.get(),0,cd);
	CPPUNIT_ASSERT( out->Check((" 14: 9e 3c 61\n"), __LINE__, (__FILE__) ) );
	out->NoteOn(box,63,98,route.get(),0,cd);
	CPPUNIT_ASSERT( out->Check((" 15: 9f 3f 62\n"), __LINE__, (__FILE__) ) );

	out->NoteOff(box,63,55,route.get(),0,false);
	CPPUNIT_ASSERT( out->Check((" 15: 8f 3f 37\n"), __LINE__, (__FILE__)) );
	// check sending note on with velocity = 0
	out->NoteOff(box,56,53,route.get(),0,true);
	CPPUNIT_ASSERT( out->Check((" 13: 9d 38 00\n"), __LINE__, (__FILE__)) );
	out->NoteOff(box,60,54,route.get(),0,false);
	CPPUNIT_ASSERT( out->Check((" 14: 8e 3c 36\n"), __LINE__, (__FILE__)) );

	DEBUGLOG (midiio, "321" );

	// Add check for NULL as tone system parameter
	out->NoteOn(NULL,56,96,route.get(),0,cd);
	CPPUNIT_ASSERT( out->Check(("  0: 90 38 60\n"), __LINE__, (__FILE__) ) );
	out->NoteOn(NULL,60,97,route.get(),0,cd);
	CPPUNIT_ASSERT( out->Check(("  1: 91 3c 61\n"), __LINE__, (__FILE__) ) );
	out->NoteOn(NULL,63,98,route.get(),0,cd);
	CPPUNIT_ASSERT( out->Check(("  2: 92 3f 62\n"), __LINE__, (__FILE__) ) );

	out->NoteOff(NULL,63,55,route.get(),0,false);
	CPPUNIT_ASSERT( out->Check(("  2: 82 3f 37\n"), __LINE__, (__FILE__)) );
	out->NoteOff(NULL,60,54,route.get(),0,false);
	CPPUNIT_ASSERT( out->Check(("  1: 81 3c 36\n"), __LINE__, (__FILE__)) );
	out->NoteOff(NULL,56,53,route.get(),0,false);
	CPPUNIT_ASSERT( out->Check(("  0: 80 38 35\n"), __LINE__, (__FILE__)) );




	out->Close();
	DEBUGLOG (midiio, "|%s|" , str(out->getOut()));
	CPPUNIT_ASSERT( out->Check(("...closed.\n")) );
}

void CommonMidiOutputTest::testMoreNotesThanChannels()
{
	CPPUNIT_ASSERT( out );
	out->Open();
	box->Open();
	CPPUNIT_ASSERT( out->Check(("Opened...\n"
				      "  0: e0 00 40\n"
				      "  0: b0 7a 00\n"
				      "  0: b0 7d 00\n"
				      "  0: b0 7f 00\n"
				      "  0: b0 65 00\n"
				      "  0: b0 64 00\n"
				      "  0: b0 06 02\n"
				      "  0: b0 26 00\n"
				      "  1: e1 00 40\n"
				      "  1: b1 7a 00\n"
				      "  1: b1 7d 00\n"
				      "  1: b1 7f 00\n"
				      "  1: b1 65 00\n"
				      "  1: b1 64 00\n"
				      "  1: b1 06 02\n"
				      "  1: b1 26 00\n"
				      "  2: e2 00 40\n"
				      "  2: b2 7a 00\n"
				      "  2: b2 7d 00\n"
				      "  2: b2 7f 00\n"
				      "  2: b2 65 00\n"
				      "  2: b2 64 00\n"
				      "  2: b2 06 02\n"
				      "  2: b2 26 00\n"
				      "  3: e3 00 40\n"
				      "  3: b3 7a 00\n"
				      "  3: b3 7d 00\n"
				      "  3: b3 7f 00\n"
				      "  3: b3 65 00\n"
				      "  3: b3 64 00\n"
				      "  3: b3 06 02\n"
				      "  3: b3 26 00\n"
				      "  4: e4 00 40\n"
				      "  4: b4 7a 00\n"
				      "  4: b4 7d 00\n"
				      "  4: b4 7f 00\n"
				      "  4: b4 65 00\n"
				      "  4: b4 64 00\n"
				      "  4: b4 06 02\n"
				      "  4: b4 26 00\n"
				      "  5: e5 00 40\n"
				      "  5: b5 7a 00\n"
				      "  5: b5 7d 00\n"
				      "  5: b5 7f 00\n"
				      "  5: b5 65 00\n"
				      "  5: b5 64 00\n"
				      "  5: b5 06 02\n"
				      "  5: b5 26 00\n"
				      "  6: e6 00 40\n"
				      "  6: b6 7a 00\n"
				      "  6: b6 7d 00\n"
				      "  6: b6 7f 00\n"
				      "  6: b6 65 00\n"
				      "  6: b6 64 00\n"
				      "  6: b6 06 02\n"
				      "  6: b6 26 00\n"
				      "  7: e7 00 40\n"
				      "  7: b7 7a 00\n"
				      "  7: b7 7d 00\n"
				      "  7: b7 7f 00\n"
				      "  7: b7 65 00\n"
				      "  7: b7 64 00\n"
				      "  7: b7 06 02\n"
				      "  7: b7 26 00\n"
				      "  8: e8 00 40\n"
				      "  8: b8 7a 00\n"
				      "  8: b8 7d 00\n"
				      "  8: b8 7f 00\n"
				      "  8: b8 65 00\n"
				      "  8: b8 64 00\n"
				      "  8: b8 06 02\n"
				      "  8: b8 26 00\n"
				      "  9: e9 00 40\n"
				      "  9: b9 7a 00\n"
				      "  9: b9 7d 00\n"
				      "  9: b9 7f 00\n"
				      "  9: b9 65 00\n"
				      "  9: b9 64 00\n"
				      "  9: b9 06 02\n"
				      "  9: b9 26 00\n"
				      " 10: ea 00 40\n"
				      " 10: ba 7a 00\n"
				      " 10: ba 7d 00\n"
				      " 10: ba 7f 00\n"
				      " 10: ba 65 00\n"
				      " 10: ba 64 00\n"
				      " 10: ba 06 02\n"
				      " 10: ba 26 00\n"
				      " 11: eb 00 40\n"
				      " 11: bb 7a 00\n"
				      " 11: bb 7d 00\n"
				      " 11: bb 7f 00\n"
				      " 11: bb 65 00\n"
				      " 11: bb 64 00\n"
				      " 11: bb 06 02\n"
				      " 11: bb 26 00\n"
				      " 12: ec 00 40\n"
				      " 12: bc 7a 00\n"
				      " 12: bc 7d 00\n"
				      " 12: bc 7f 00\n"
				      " 12: bc 65 00\n"
				      " 12: bc 64 00\n"
				      " 12: bc 06 02\n"
				      " 12: bc 26 00\n"
				      " 13: ed 00 40\n"
				      " 13: bd 7a 00\n"
				      " 13: bd 7d 00\n"
				      " 13: bd 7f 00\n"
				      " 13: bd 65 00\n"
				      " 13: bd 64 00\n"
				      " 13: bd 06 02\n"
				      " 13: bd 26 00\n"
				      " 14: ee 00 40\n"
				      " 14: be 7a 00\n"
				      " 14: be 7d 00\n"
				      " 14: be 7f 00\n"
				      " 14: be 65 00\n"
				      " 14: be 64 00\n"
				      " 14: be 06 02\n"
				      " 14: be 26 00\n"
				      " 15: ef 00 40\n"
				      " 15: bf 7a 00\n"
				      " 15: bf 7d 00\n"
				      " 15: bf 7f 00\n"
				      " 15: bf 65 00\n"
				      " 15: bf 64 00\n"
				      " 15: bf 06 02\n"
				      " 15: bf 26 00\n"), __LINE__, (__FILE__)) );

	/* check all permutations */

	DEBUGLOG (midiio, "123" );

	out->NoteOn(box,56,96,route.get(),0,cd);
	CPPUNIT_ASSERT( out->Check(("  0: 90 38 60\n"), __LINE__, (__FILE__)) );
	out->NoteOn(box,60,97,route.get(),0,cd);
	CPPUNIT_ASSERT( out->Check(("  1: 91 3c 61\n"), __LINE__, (__FILE__)) );
	out->NoteOn(box,63,98,route.get(),0,cd);
	CPPUNIT_ASSERT( out->Check(("  2: 92 3f 62\n"), __LINE__, (__FILE__)) );

	out->NoteOn(box,56,96,route.get(),0,cd);
	CPPUNIT_ASSERT( out->Check(("  3: 93 38 60\n"), __LINE__, (__FILE__)) );
	out->NoteOn(box,60,97,route.get(),0,cd);
	CPPUNIT_ASSERT( out->Check(("  4: 94 3c 61\n"), __LINE__, (__FILE__)) );
	out->NoteOn(box,63,98,route.get(),0,cd);
	CPPUNIT_ASSERT( out->Check(("  5: 95 3f 62\n"), __LINE__, (__FILE__)) );

	out->NoteOn(box,56,96,route.get(),0,cd);
	CPPUNIT_ASSERT( out->Check(("  6: 96 38 60\n"), __LINE__, (__FILE__)) );
	out->NoteOn(box,60,97,route.get(),0,cd);
	CPPUNIT_ASSERT( out->Check(("  7: 97 3c 61\n"), __LINE__, (__FILE__)) );
	out->NoteOn(box,63,98,route.get(),0,cd);
	CPPUNIT_ASSERT( out->Check(("  8: 98 3f 62\n"), __LINE__, (__FILE__)) );

	out->NoteOn(box,56,96,route.get(),0,cd);
	CPPUNIT_ASSERT( out->Check((" 10: 9a 38 60\n"), __LINE__, (__FILE__)) );
	out->NoteOn(box,60,97,route.get(),0,cd);
	CPPUNIT_ASSERT( out->Check((" 11: 9b 3c 61\n"), __LINE__, (__FILE__)) );
	out->NoteOn(box,63,98,route.get(),0,cd);
	CPPUNIT_ASSERT( out->Check((" 12: 9c 3f 62\n"), __LINE__, (__FILE__)) );

	out->NoteOn(box,56,96,route.get(),0,cd);
	CPPUNIT_ASSERT( out->Check((" 13: 9d 38 60\n"), __LINE__, (__FILE__)) );
	out->NoteOn(box,60,97,route.get(),0,cd);
	CPPUNIT_ASSERT( out->Check((" 14: 9e 3c 61\n"), __LINE__, (__FILE__)) );
	out->NoteOn(box,63,98,route.get(),0,cd);
	CPPUNIT_ASSERT( out->Check((" 15: 9f 3f 62\n"), __LINE__, (__FILE__)) );


	out->NoteOn(box,64,99,route.get(),0,cd);
	CPPUNIT_ASSERT( out->Check(("  0: 80 38 40\n  0: 90 40 63\n"), __LINE__, (__FILE__)) );
	out->NoteOn(box,65,100,route.get(),0,cd);
	CPPUNIT_ASSERT( out->Check(("  3: 83 38 40\n  3: 93 41 64\n"), __LINE__, (__FILE__)) );
	out->NoteOn(box,66,101,route.get(),0,cd);
	CPPUNIT_ASSERT( out->Check(("  6: 86 38 40\n  6: 96 42 65\n"), __LINE__, (__FILE__)) );

	out->NoteOn(box,67,102,route.get(),0,cd);
	CPPUNIT_ASSERT( out->Check((" 10: 8a 38 40\n 10: 9a 43 66\n"), __LINE__, (__FILE__)) );
	out->NoteOn(box,68,103,route.get(),0,cd);
	CPPUNIT_ASSERT( out->Check(("  1: 81 3c 40\n  1: 91 44 67\n"), __LINE__, (__FILE__)) );
	out->NoteOn(box,69,104,route.get(),0,cd);
	CPPUNIT_ASSERT( out->Check(("  4: 84 3c 40\n  4: 94 45 68\n"), __LINE__, (__FILE__)) );

	out->NoteOn(box,70,105,route.get(),0,cd);
	CPPUNIT_ASSERT( out->Check(("  7: 87 3c 40\n  7: 97 46 69\n"), __LINE__, (__FILE__)) );
	out->NoteOn(box,71,106,route.get(),0,cd);
	CPPUNIT_ASSERT( out->Check((" 11: 8b 3c 40\n 11: 9b 47 6a\n"), __LINE__, (__FILE__)) );
	out->NoteOn(box,72,107,route.get(),0,cd);
	CPPUNIT_ASSERT( out->Check((" 14: 8e 3c 40\n 14: 9e 48 6b\n"), __LINE__, (__FILE__)) );

	out->NoteOn(box,73,108,route.get(),0,cd);
	CPPUNIT_ASSERT( out->Check(("  2: 82 3f 40\n  2: 92 49 6c\n"), __LINE__, (__FILE__)) );
	out->NoteOn(box,74,109,route.get(),0,cd);
	CPPUNIT_ASSERT( out->Check(("  5: 85 3f 40\n  5: 95 4a 6d\n"), __LINE__, (__FILE__)) );
	out->NoteOn(box,75,110,route.get(),0,cd);
	CPPUNIT_ASSERT( out->Check(("  8: 88 3f 40\n  8: 98 4b 6e\n"), __LINE__, (__FILE__)) );

	out->NoteOn(box,76,111,route.get(),0,cd);
	CPPUNIT_ASSERT( out->Check(("  0: 80 40 40\n  0: 90 4c 6f\n"), __LINE__, (__FILE__)) );
	out->NoteOn(box,77,112,route.get(),0,cd);
	CPPUNIT_ASSERT( out->Check(("  3: 83 41 40\n  3: 93 4d 70\n"), __LINE__, (__FILE__)) );
	out->NoteOn(box,78,113,route.get(),0,cd);
	CPPUNIT_ASSERT( out->Check(("  6: 86 42 40\n  6: 96 4e 71\n"), __LINE__, (__FILE__)) );

 	out->Close();
 	CPPUNIT_ASSERT( out->Check((" 12: 8c 3f 40\n 13: 8d 38 40\n 15: 8f 3f 40\n 10: 8a 43 40\n  1: 81 44 40\n  4: 84 45 40\n  7: 87 46 40\n 11: 8b 47 40\n 14: 8e 48 40\n  2: 82 49 40\n  5: 85 4a 40\n  8: 88 4b 40\n  0: 80 4c 40\n  3: 83 4d 40\n  6: 86 4e 40\n...closed.\n"), __LINE__, (__FILE__)) );
}


void CommonMidiInputTest::setUp()
{
// change DEBUGA to DEBUG in case you need the debug input
#ifdef DEBUG
//	mutabor::mutabor_debug_flags.timer = true;
//	mutabor::mutabor_debug_flags.midiio = true;
#endif
	// std::clog << "Running setUp()" << std::endl;

	CPPUNIT_ASSERT(mutabor::InputDeviceClass::GetDeviceList().empty());
	CPPUNIT_ASSERT(mutabor::OutputDeviceClass::GetDeviceList().empty());
	CPPUNIT_ASSERT(mutabor::RouteClass::GetRouteList().empty());
	CPPUNIT_ASSERT(mutabor::BoxClass::GetBoxList().empty());

	route = mutabor::RouteFactory::Create();
	box = mutabor::BoxFactory::Create(mutabor::Box0,0);
	connect(route, box);

	mutabor::CurrentTime.UseRealtime(true);
	in = new midicmnInputDevice(("Test"));
	guard = in;
	out = new midicmnOutputDevice(("Test"));
	outguard = out;

	connect(route,guard);
	connect(route,outguard);
	route->SetOutputFrom (0);
	route->SetOutputTo (15);
	route->OutputAvoidDrumChannel (true);
}

void CommonMidiInputTest::tearDown()
{

	if (in) {
		in->Destroy();
	}
	if(out)
		out->Destroy();
	if(route)
		route->Destroy();
	if (box)
		box -> Destroy();
	in = NULL;
	out = NULL;
	guard.reset();
	route.reset();
	box.reset();
#ifdef DEBUG
//	mutabor::mutabor_debug_flags.timer = false;
	mutabor::mutabor_debug_flags.midiio = false;
#endif
}


void CommonMidiInputTest::testPanic()
{
	CPPUNIT_ASSERT( in );
	out->Open();
	box->Open();
	CPPUNIT_ASSERT( out->Check(("Opened...\n"
				      "  0: e0 00 40\n"
				      "  0: b0 7a 00\n"
				      "  0: b0 7d 00\n"
				      "  0: b0 7f 00\n"
				      "  0: b0 65 00\n"
				      "  0: b0 64 00\n"
				      "  0: b0 06 02\n"
				      "  0: b0 26 00\n"
				      "  1: e1 00 40\n"
				      "  1: b1 7a 00\n"
				      "  1: b1 7d 00\n"
				      "  1: b1 7f 00\n"
				      "  1: b1 65 00\n"
				      "  1: b1 64 00\n"
				      "  1: b1 06 02\n"
				      "  1: b1 26 00\n"
				      "  2: e2 00 40\n"
				      "  2: b2 7a 00\n"
				      "  2: b2 7d 00\n"
				      "  2: b2 7f 00\n"
				      "  2: b2 65 00\n"
				      "  2: b2 64 00\n"
				      "  2: b2 06 02\n"
				      "  2: b2 26 00\n"
				      "  3: e3 00 40\n"
				      "  3: b3 7a 00\n"
				      "  3: b3 7d 00\n"
				      "  3: b3 7f 00\n"
				      "  3: b3 65 00\n"
				      "  3: b3 64 00\n"
				      "  3: b3 06 02\n"
				      "  3: b3 26 00\n"
				      "  4: e4 00 40\n"
				      "  4: b4 7a 00\n"
				      "  4: b4 7d 00\n"
				      "  4: b4 7f 00\n"
				      "  4: b4 65 00\n"
				      "  4: b4 64 00\n"
				      "  4: b4 06 02\n"
				      "  4: b4 26 00\n"
				      "  5: e5 00 40\n"
				      "  5: b5 7a 00\n"
				      "  5: b5 7d 00\n"
				      "  5: b5 7f 00\n"
				      "  5: b5 65 00\n"
				      "  5: b5 64 00\n"
				      "  5: b5 06 02\n"
				      "  5: b5 26 00\n"
				      "  6: e6 00 40\n"
				      "  6: b6 7a 00\n"
				      "  6: b6 7d 00\n"
				      "  6: b6 7f 00\n"
				      "  6: b6 65 00\n"
				      "  6: b6 64 00\n"
				      "  6: b6 06 02\n"
				      "  6: b6 26 00\n"
				      "  7: e7 00 40\n"
				      "  7: b7 7a 00\n"
				      "  7: b7 7d 00\n"
				      "  7: b7 7f 00\n"
				      "  7: b7 65 00\n"
				      "  7: b7 64 00\n"
				      "  7: b7 06 02\n"
				      "  7: b7 26 00\n"
				      "  8: e8 00 40\n"
				      "  8: b8 7a 00\n"
				      "  8: b8 7d 00\n"
				      "  8: b8 7f 00\n"
				      "  8: b8 65 00\n"
				      "  8: b8 64 00\n"
				      "  8: b8 06 02\n"
				      "  8: b8 26 00\n"
				      "  9: e9 00 40\n"
				      "  9: b9 7a 00\n"
				      "  9: b9 7d 00\n"
				      "  9: b9 7f 00\n"
				      "  9: b9 65 00\n"
				      "  9: b9 64 00\n"
				      "  9: b9 06 02\n"
				      "  9: b9 26 00\n"
				      " 10: ea 00 40\n"
				      " 10: ba 7a 00\n"
				      " 10: ba 7d 00\n"
				      " 10: ba 7f 00\n"
				      " 10: ba 65 00\n"
				      " 10: ba 64 00\n"
				      " 10: ba 06 02\n"
				      " 10: ba 26 00\n"
				      " 11: eb 00 40\n"
				      " 11: bb 7a 00\n"
				      " 11: bb 7d 00\n"
				      " 11: bb 7f 00\n"
				      " 11: bb 65 00\n"
				      " 11: bb 64 00\n"
				      " 11: bb 06 02\n"
				      " 11: bb 26 00\n"
				      " 12: ec 00 40\n"
				      " 12: bc 7a 00\n"
				      " 12: bc 7d 00\n"
				      " 12: bc 7f 00\n"
				      " 12: bc 65 00\n"
				      " 12: bc 64 00\n"
				      " 12: bc 06 02\n"
				      " 12: bc 26 00\n"
				      " 13: ed 00 40\n"
				      " 13: bd 7a 00\n"
				      " 13: bd 7d 00\n"
				      " 13: bd 7f 00\n"
				      " 13: bd 65 00\n"
				      " 13: bd 64 00\n"
				      " 13: bd 06 02\n"
				      " 13: bd 26 00\n"
				      " 14: ee 00 40\n"
				      " 14: be 7a 00\n"
				      " 14: be 7d 00\n"
				      " 14: be 7f 00\n"
				      " 14: be 65 00\n"
				      " 14: be 64 00\n"
				      " 14: be 06 02\n"
				      " 14: be 26 00\n"
				      " 15: ef 00 40\n"
				      " 15: bf 7a 00\n"
				      " 15: bf 7d 00\n"
				      " 15: bf 7f 00\n"
				      " 15: bf 65 00\n"
				      " 15: bf 64 00\n"
				      " 15: bf 06 02\n"
				      " 15: bf 26 00\n"), __LINE__, (__FILE__)) );
	in->Open();

	/* check all permutations */

	DEBUGLOG (midiio, "123" );

	in->NoteOn(0,56,96);
	CPPUNIT_ASSERT( out->Check(("  0: 90 38 60\n"), __LINE__, (__FILE__) ) );
	in->NoteOn(0,60,97);
	CPPUNIT_ASSERT( out->Check(("  1: 91 3c 61\n"), __LINE__, (__FILE__) ) );
	in->NoteOn(0,63,98);
	CPPUNIT_ASSERT( out->Check(("  2: 92 3f 62\n"), __LINE__, (__FILE__) ) );

	in->NoteOff(0,56,53);
	CPPUNIT_ASSERT( out->Check(("  0: 80 38 35\n"), __LINE__, (__FILE__) ) );
	in->NoteOff(0,60,54);
	CPPUNIT_ASSERT( out->Check(("  1: 81 3c 36\n"), __LINE__, (__FILE__) ) );
	in->NoteOff(0,63,55);
	CPPUNIT_ASSERT( out->Check(("  2: 82 3f 37\n"), __LINE__, (__FILE__) ) );

	DEBUGLOG (midiio, "132" );

	in->NoteOn(0,56,96);
	CPPUNIT_ASSERT( out->Check(("  3: 93 38 60\n"), __LINE__, (__FILE__) ) );
	in->NoteOn(0,60,97);
	CPPUNIT_ASSERT( out->Check(("  4: 94 3c 61\n"), __LINE__, (__FILE__) ) );
	in->NoteOn(0,63,98);
	CPPUNIT_ASSERT( out->Check(("  5: 95 3f 62\n"), __LINE__, (__FILE__) ) );

	in->NoteOff(0,56,53);
	CPPUNIT_ASSERT( out->Check(("  3: 83 38 35\n"), __LINE__, (__FILE__) ) );
	in->NoteOff(0,63,55);
	CPPUNIT_ASSERT( out->Check(("  5: 85 3f 37\n"), __LINE__, (__FILE__) ) );
	in->NoteOff(0,60,54);
	CPPUNIT_ASSERT( out->Check(("  4: 84 3c 36\n"), __LINE__, (__FILE__) ) );

	DEBUGLOG (midiio, "213" );

	in->NoteOn(0,56,96);
	CPPUNIT_ASSERT( out->Check(("  6: 96 38 60\n"), __LINE__, (__FILE__) ) );
	in->NoteOn(0,60,97);
	CPPUNIT_ASSERT( out->Check(("  7: 97 3c 61\n"), __LINE__, (__FILE__) ) );
	in->NoteOn(0,63,98);
	CPPUNIT_ASSERT( out->Check(("  8: 98 3f 62\n"), __LINE__, (__FILE__) ) );

	in->NoteOff(0,60,54);
	CPPUNIT_ASSERT( out->Check(("  7: 87 3c 36\n"), __LINE__, (__FILE__) ) );
	in->NoteOff(0,56,53);
	CPPUNIT_ASSERT( out->Check(("  6: 86 38 35\n"), __LINE__, (__FILE__) ) );
	in->NoteOff(0,63,55);
	CPPUNIT_ASSERT( out->Check(("  8: 88 3f 37\n"), __LINE__, (__FILE__) ) );

	DEBUGLOG (midiio, "231" );

	in->NoteOn(0,56,96);
	CPPUNIT_ASSERT( out->Check((" 10: 9a 38 60\n"), __LINE__, (__FILE__) ) );
	in->NoteOn(0,60,97);
	CPPUNIT_ASSERT( out->Check((" 11: 9b 3c 61\n"), __LINE__, (__FILE__) ) );
	in->NoteOn(0,63,98);
	CPPUNIT_ASSERT( out->Check((" 12: 9c 3f 62\n"), __LINE__, (__FILE__) ) );

	in->NoteOff(0,60,54);
	CPPUNIT_ASSERT( out->Check((" 11: 8b 3c 36\n"), __LINE__, (__FILE__) ) );
	in->NoteOff(0,63,55);
	CPPUNIT_ASSERT( out->Check((" 12: 8c 3f 37\n"), __LINE__, (__FILE__) ) );
	in->NoteOff(0,56,53);
	CPPUNIT_ASSERT( out->Check((" 10: 8a 38 35\n"), __LINE__, (__FILE__) ) );

	DEBUGLOG (midiio, "312" );

	in->NoteOn(0,56,96);
	CPPUNIT_ASSERT( out->Check((" 13: 9d 38 60\n"), __LINE__, (__FILE__) ) );
	in->NoteOn(0,60,97);
	CPPUNIT_ASSERT( out->Check((" 14: 9e 3c 61\n"), __LINE__, (__FILE__) ) );
	in->NoteOn(0,63,98);
	CPPUNIT_ASSERT( out->Check((" 15: 9f 3f 62\n"), __LINE__, (__FILE__) ) );

	in->NoteOff(0,63,55);
	CPPUNIT_ASSERT( out->Check((" 15: 8f 3f 37\n"), __LINE__, (__FILE__) ) );
	// check sending note on with velocity = 0
	in->NoteOff(0,56,53);
	CPPUNIT_ASSERT( out->Check((" 13: 8d 38 35\n"), __LINE__, (__FILE__) ) );
	in->NoteOff(0,60,54);
	CPPUNIT_ASSERT( out->Check((" 14: 8e 3c 36\n"), __LINE__, (__FILE__) ) );

	DEBUGLOG (midiio, "321" );

	// Add check for NULL as tone system parameter
	in->NoteOn(0,56,96);
	CPPUNIT_ASSERT( out->Check(("  0: 90 38 60\n"), __LINE__, (__FILE__) ) );
	in->NoteOn(0,60,97);
	CPPUNIT_ASSERT( out->Check(("  1: 91 3c 61\n"), __LINE__, (__FILE__) ) );
	in->NoteOn(0,63,98);
	CPPUNIT_ASSERT( out->Check(("  2: 92 3f 62\n"), __LINE__, (__FILE__) ) );

	in->NoteOff(0,63,55);
	CPPUNIT_ASSERT( out->Check(("  2: 82 3f 37\n"), __LINE__, (__FILE__) ) );
	in->NoteOff(0,60,54);
	CPPUNIT_ASSERT( out->Check(("  1: 81 3c 36\n"), __LINE__, (__FILE__) ) );
	in->NoteOff(0,56,53);
	CPPUNIT_ASSERT( out->Check(("  0: 80 38 35\n"), __LINE__, (__FILE__) ) );

	// now collect data
	DEBUGLOG (midiio, "123" );
	in->NoteOn(0,56,96);
	CPPUNIT_ASSERT( out->Check(("  3: 93 38 60\n"), __LINE__, (__FILE__) ) );
	in->NoteOn(0,60,97);
	CPPUNIT_ASSERT( out->Check(("  5: 95 3c 61\n"), __LINE__, (__FILE__) ) );
	in->NoteOn(0,63,98);
	CPPUNIT_ASSERT( out->Check(("  4: 94 3f 62\n"), __LINE__, (__FILE__) ) );

	DEBUGLOG (midiio, "132" );

	in->NoteOn(0,56,96);
	CPPUNIT_ASSERT( out->Check(("  7: 97 38 60\n"), __LINE__, (__FILE__) ) );
	in->NoteOn(0,60,97);
	CPPUNIT_ASSERT( out->Check(("  6: 96 3c 61\n"), __LINE__, (__FILE__) ) );
	in->NoteOn(0,63,98);
	CPPUNIT_ASSERT( out->Check(("  8: 98 3f 62\n"), __LINE__, (__FILE__) ) );

	DEBUGLOG (midiio, "213" );

	in->NoteOn(0,56,96);
	CPPUNIT_ASSERT( out->Check((" 11: 9b 38 60\n"), __LINE__, (__FILE__) ) );
	in->NoteOn(0,60,97);
	CPPUNIT_ASSERT( out->Check((" 12: 9c 3c 61\n"), __LINE__, (__FILE__) ) );
	in->NoteOn(0,63,98);
	CPPUNIT_ASSERT( out->Check((" 10: 9a 3f 62\n"), __LINE__, (__FILE__) ) );

	DEBUGLOG (midiio, "231" );

	in->NoteOn(0,56,96);
	CPPUNIT_ASSERT( out->Check((" 15: 9f 38 60\n"), __LINE__, (__FILE__) ) );
	in->NoteOn(0,60,97);
	CPPUNIT_ASSERT( out->Check((" 13: 9d 3c 61\n"), __LINE__, (__FILE__) ) );
	in->NoteOn(0,63,98);
	CPPUNIT_ASSERT( out->Check((" 14: 9e 3f 62\n"), __LINE__, (__FILE__) ) );

	DEBUGLOG (midiio, "312" );

	in->NoteOn(0,56,96);
	CPPUNIT_ASSERT( out->Check(("  2: 92 38 60\n"), __LINE__, (__FILE__) ) );
	in->NoteOn(0,60,97);
	CPPUNIT_ASSERT( out->Check(("  1: 91 3c 61\n"), __LINE__, (__FILE__) ) );
	in->NoteOn(0,63,98);
	CPPUNIT_ASSERT( out->Check(("  0: 90 3f 62\n"), __LINE__, (__FILE__) ) );

	DEBUGLOG (midiio, "321" );

	// Add check for NULL as tone system parameter
	in->NoteOn(0,56,96);
	CPPUNIT_ASSERT( out->Check(("  2: 82 38 40\n  2: 92 38 60\n"), __LINE__, (__FILE__) ) );
	in->NoteOn(0,60,97);
	CPPUNIT_ASSERT( out->Check(("  2: 82 38 40\n  2: 92 3c 61\n"), __LINE__, (__FILE__) ) );
	in->NoteOn(0,63,98);
	CPPUNIT_ASSERT( out->Check(("  3: 83 38 40\n  3: 93 3f 62\n"), __LINE__, (__FILE__) ) );

	in->NoteOff(0,56,53);
	CPPUNIT_ASSERT( out->Check(("  7: 87 38 35\n"), __LINE__, (__FILE__) ) );
	in->NoteOff(0,60,54);
	CPPUNIT_ASSERT( out->Check(("  1: 81 3c 36\n"), __LINE__, (__FILE__) ) );
	in->NoteOff(0,63,55);
	CPPUNIT_ASSERT( out->Check(("  0: 80 3f 37\n"), __LINE__, (__FILE__) ) );

	in->Panic(mutabor::midi::DEFAULT_PANIC);
	CPPUNIT_ASSERT( out->unsortedCheck(("\
  2: b2 40 00\n\
  3: b3 40 00\n\
  4: b4 40 00\n\
  5: b5 40 00\n\
  6: b6 40 00\n\
  8: b8 40 00\n\
 10: ba 40 00\n\
 11: bb 40 00\n\
 12: bc 40 00\n\
 13: bd 40 00\n\
 14: be 40 00\n\
 15: bf 40 00\n\
  2: b2 42 00\n\
  3: b3 42 00\n\
  4: b4 42 00\n\
  5: b5 42 00\n\
  6: b6 42 00\n\
  8: b8 42 00\n\
 10: ba 42 00\n\
 11: bb 42 00\n\
 12: bc 42 00\n\
 13: bd 42 00\n\
 14: be 42 00\n\
 15: bf 42 00\n\
  2: b2 44 00\n\
  3: b3 44 00\n\
  4: b4 44 00\n\
  5: b5 44 00\n\
  6: b6 44 00\n\
  8: b8 44 00\n\
 10: ba 44 00\n\
 11: bb 44 00\n\
 12: bc 44 00\n\
 13: bd 44 00\n\
 14: be 44 00\n\
 15: bf 44 00\n\
  2: b2 45 00\n\
  3: b3 45 00\n\
  4: b4 45 00\n\
  5: b5 45 00\n\
  6: b6 45 00\n\
  8: b8 45 00\n\
 10: ba 45 00\n\
 11: bb 45 00\n\
 12: bc 45 00\n\
 13: bd 45 00\n\
 14: be 45 00\n\
 15: bf 45 00\n\
  3: 83 3f 62\n\
  4: 84 3f 62\n\
  8: 88 3f 62\n\
 10: 8a 3f 62\n\
 14: 8e 3f 62\n\
  2: 82 3c 61\n\
  5: 85 3c 61\n\
  6: 86 3c 61\n\
 12: 8c 3c 61\n\
 13: 8d 3c 61\n\
 11: 8b 38 60\n\
 15: 8f 38 60\n\
"),
				   __LINE__,
				   (__FILE__) ) );

	in->NoteOff(0,56,53);
	CPPUNIT_ASSERT( out->Check((""), __LINE__, (__FILE__) ) );
	in->NoteOff(0,63,55);
	CPPUNIT_ASSERT( out->Check((""), __LINE__, (__FILE__) ) );
	in->NoteOff(0,60,54);
	CPPUNIT_ASSERT( out->Check((""), __LINE__, (__FILE__) ) );

	in->NoteOff(0,60,54);
	CPPUNIT_ASSERT( out->Check((""), __LINE__, (__FILE__) ) );
	in->NoteOff(0,56,53);
	CPPUNIT_ASSERT( out->Check((""), __LINE__, (__FILE__) ) );
	in->NoteOff(0,63,55);
	CPPUNIT_ASSERT( out->Check((""), __LINE__, (__FILE__) ) );

	in->NoteOff(0,60,54);
	CPPUNIT_ASSERT( out->Check((""), __LINE__, (__FILE__) ) );
	in->NoteOff(0,63,55);
	CPPUNIT_ASSERT( out->Check((""), __LINE__, (__FILE__) ) );
	in->NoteOff(0,56,53);
	CPPUNIT_ASSERT( out->Check((""), __LINE__, (__FILE__) ) );

	in->NoteOff(0,63,55);
	CPPUNIT_ASSERT( out->Check((""), __LINE__, (__FILE__) ) );
	// check sending note on with velocity = 0
	in->NoteOff(0,56,53);
	CPPUNIT_ASSERT( out->Check((""), __LINE__, (__FILE__) ) );
	in->NoteOff(0,60,54);
	CPPUNIT_ASSERT( out->Check((""), __LINE__, (__FILE__) ) );

	in->NoteOff(0,63,55);
	CPPUNIT_ASSERT( out->Check((""), __LINE__, (__FILE__) ) );
	in->NoteOff(0,60,54);
	CPPUNIT_ASSERT( out->Check((""), __LINE__, (__FILE__) ) );
	in->NoteOff(0,56,53);
	CPPUNIT_ASSERT( out->Check((""), __LINE__, (__FILE__) ) );

	in->Close();
	out->Close();
	DEBUGLOG (midiio, "|%s|" , str(out->getOut()));
	CPPUNIT_ASSERT( out->Check(("...closed.\n"), __LINE__, (__FILE__) ) );
}

void CommonMidiInputTest::testGlobalPanic()
{
	CPPUNIT_ASSERT( in );
	out->Open();
	box->Open();
	CPPUNIT_ASSERT( out->Check(("Opened...\n"
				      "  0: e0 00 40\n"
				      "  0: b0 7a 00\n"
				      "  0: b0 7d 00\n"
				      "  0: b0 7f 00\n"
				      "  0: b0 65 00\n"
				      "  0: b0 64 00\n"
				      "  0: b0 06 02\n"
				      "  0: b0 26 00\n"
				      "  1: e1 00 40\n"
				      "  1: b1 7a 00\n"
				      "  1: b1 7d 00\n"
				      "  1: b1 7f 00\n"
				      "  1: b1 65 00\n"
				      "  1: b1 64 00\n"
				      "  1: b1 06 02\n"
				      "  1: b1 26 00\n"
				      "  2: e2 00 40\n"
				      "  2: b2 7a 00\n"
				      "  2: b2 7d 00\n"
				      "  2: b2 7f 00\n"
				      "  2: b2 65 00\n"
				      "  2: b2 64 00\n"
				      "  2: b2 06 02\n"
				      "  2: b2 26 00\n"
				      "  3: e3 00 40\n"
				      "  3: b3 7a 00\n"
				      "  3: b3 7d 00\n"
				      "  3: b3 7f 00\n"
				      "  3: b3 65 00\n"
				      "  3: b3 64 00\n"
				      "  3: b3 06 02\n"
				      "  3: b3 26 00\n"
				      "  4: e4 00 40\n"
				      "  4: b4 7a 00\n"
				      "  4: b4 7d 00\n"
				      "  4: b4 7f 00\n"
				      "  4: b4 65 00\n"
				      "  4: b4 64 00\n"
				      "  4: b4 06 02\n"
				      "  4: b4 26 00\n"
				      "  5: e5 00 40\n"
				      "  5: b5 7a 00\n"
				      "  5: b5 7d 00\n"
				      "  5: b5 7f 00\n"
				      "  5: b5 65 00\n"
				      "  5: b5 64 00\n"
				      "  5: b5 06 02\n"
				      "  5: b5 26 00\n"
				      "  6: e6 00 40\n"
				      "  6: b6 7a 00\n"
				      "  6: b6 7d 00\n"
				      "  6: b6 7f 00\n"
				      "  6: b6 65 00\n"
				      "  6: b6 64 00\n"
				      "  6: b6 06 02\n"
				      "  6: b6 26 00\n"
				      "  7: e7 00 40\n"
				      "  7: b7 7a 00\n"
				      "  7: b7 7d 00\n"
				      "  7: b7 7f 00\n"
				      "  7: b7 65 00\n"
				      "  7: b7 64 00\n"
				      "  7: b7 06 02\n"
				      "  7: b7 26 00\n"
				      "  8: e8 00 40\n"
				      "  8: b8 7a 00\n"
				      "  8: b8 7d 00\n"
				      "  8: b8 7f 00\n"
				      "  8: b8 65 00\n"
				      "  8: b8 64 00\n"
				      "  8: b8 06 02\n"
				      "  8: b8 26 00\n"
				      "  9: e9 00 40\n"
				      "  9: b9 7a 00\n"
				      "  9: b9 7d 00\n"
				      "  9: b9 7f 00\n"
				      "  9: b9 65 00\n"
				      "  9: b9 64 00\n"
				      "  9: b9 06 02\n"
				      "  9: b9 26 00\n"
				      " 10: ea 00 40\n"
				      " 10: ba 7a 00\n"
				      " 10: ba 7d 00\n"
				      " 10: ba 7f 00\n"
				      " 10: ba 65 00\n"
				      " 10: ba 64 00\n"
				      " 10: ba 06 02\n"
				      " 10: ba 26 00\n"
				      " 11: eb 00 40\n"
				      " 11: bb 7a 00\n"
				      " 11: bb 7d 00\n"
				      " 11: bb 7f 00\n"
				      " 11: bb 65 00\n"
				      " 11: bb 64 00\n"
				      " 11: bb 06 02\n"
				      " 11: bb 26 00\n"
				      " 12: ec 00 40\n"
				      " 12: bc 7a 00\n"
				      " 12: bc 7d 00\n"
				      " 12: bc 7f 00\n"
				      " 12: bc 65 00\n"
				      " 12: bc 64 00\n"
				      " 12: bc 06 02\n"
				      " 12: bc 26 00\n"
				      " 13: ed 00 40\n"
				      " 13: bd 7a 00\n"
				      " 13: bd 7d 00\n"
				      " 13: bd 7f 00\n"
				      " 13: bd 65 00\n"
				      " 13: bd 64 00\n"
				      " 13: bd 06 02\n"
				      " 13: bd 26 00\n"
				      " 14: ee 00 40\n"
				      " 14: be 7a 00\n"
				      " 14: be 7d 00\n"
				      " 14: be 7f 00\n"
				      " 14: be 65 00\n"
				      " 14: be 64 00\n"
				      " 14: be 06 02\n"
				      " 14: be 26 00\n"
				      " 15: ef 00 40\n"
				      " 15: bf 7a 00\n"
				      " 15: bf 7d 00\n"
				      " 15: bf 7f 00\n"
				      " 15: bf 65 00\n"
				      " 15: bf 64 00\n"
				      " 15: bf 06 02\n"
				      " 15: bf 26 00\n"), __LINE__, (__FILE__)) );
	in->Open();

	/* check all permutations */

	DEBUGLOG (midiio, "123" );

	in->NoteOn(0,56,96);
	CPPUNIT_ASSERT( out->Check(("  0: 90 38 60\n"), __LINE__, (__FILE__) ) );
	in->NoteOn(0,60,97);
	CPPUNIT_ASSERT( out->Check(("  1: 91 3c 61\n"), __LINE__, (__FILE__) ) );
	in->NoteOn(0,63,98);
	CPPUNIT_ASSERT( out->Check(("  2: 92 3f 62\n"), __LINE__, (__FILE__) ) );

	in->NoteOff(0,56,53);
	CPPUNIT_ASSERT( out->Check(("  0: 80 38 35\n"), __LINE__, (__FILE__) ) );
	in->NoteOff(0,60,54);
	CPPUNIT_ASSERT( out->Check(("  1: 81 3c 36\n"), __LINE__, (__FILE__) ) );
	in->NoteOff(0,63,55);
	CPPUNIT_ASSERT( out->Check(("  2: 82 3f 37\n"), __LINE__, (__FILE__) ) );

	DEBUGLOG (midiio, "132" );

	in->NoteOn(0,56,96);
	CPPUNIT_ASSERT( out->Check(("  3: 93 38 60\n"), __LINE__, (__FILE__) ) );
	in->NoteOn(0,60,97);
	CPPUNIT_ASSERT( out->Check(("  4: 94 3c 61\n"), __LINE__, (__FILE__) ) );
	in->NoteOn(0,63,98);
	CPPUNIT_ASSERT( out->Check(("  5: 95 3f 62\n"), __LINE__, (__FILE__) ) );

	in->NoteOff(0,56,53);
	CPPUNIT_ASSERT( out->Check(("  3: 83 38 35\n"), __LINE__, (__FILE__) ) );
	in->NoteOff(0,63,55);
	CPPUNIT_ASSERT( out->Check(("  5: 85 3f 37\n"), __LINE__, (__FILE__) ) );
	in->NoteOff(0,60,54);
	CPPUNIT_ASSERT( out->Check(("  4: 84 3c 36\n"), __LINE__, (__FILE__) ) );

	DEBUGLOG (midiio, "213" );

	in->NoteOn(0,56,96);
	CPPUNIT_ASSERT( out->Check(("  6: 96 38 60\n"), __LINE__, (__FILE__) ) );
	in->NoteOn(0,60,97);
	CPPUNIT_ASSERT( out->Check(("  7: 97 3c 61\n"), __LINE__, (__FILE__) ) );
	in->NoteOn(0,63,98);
	CPPUNIT_ASSERT( out->Check(("  8: 98 3f 62\n"), __LINE__, (__FILE__) ) );

	in->NoteOff(0,60,54);
	CPPUNIT_ASSERT( out->Check(("  7: 87 3c 36\n"), __LINE__, (__FILE__) ) );
	in->NoteOff(0,56,53);
	CPPUNIT_ASSERT( out->Check(("  6: 86 38 35\n"), __LINE__, (__FILE__) ) );
	in->NoteOff(0,63,55);
	CPPUNIT_ASSERT( out->Check(("  8: 88 3f 37\n"), __LINE__, (__FILE__) ) );

	DEBUGLOG (midiio, "231" );

	in->NoteOn(0,56,96);
	CPPUNIT_ASSERT( out->Check((" 10: 9a 38 60\n"), __LINE__, (__FILE__) ) );
	in->NoteOn(0,60,97);
	CPPUNIT_ASSERT( out->Check((" 11: 9b 3c 61\n"), __LINE__, (__FILE__) ) );
	in->NoteOn(0,63,98);
	CPPUNIT_ASSERT( out->Check((" 12: 9c 3f 62\n"), __LINE__, (__FILE__) ) );

	in->NoteOff(0,60,54);
	CPPUNIT_ASSERT( out->Check((" 11: 8b 3c 36\n"), __LINE__, (__FILE__) ) );
	in->NoteOff(0,63,55);
	CPPUNIT_ASSERT( out->Check((" 12: 8c 3f 37\n"), __LINE__, (__FILE__) ) );
	in->NoteOff(0,56,53);
	CPPUNIT_ASSERT( out->Check((" 10: 8a 38 35\n"), __LINE__, (__FILE__) ) );

	DEBUGLOG (midiio, "312" );

	in->NoteOn(0,56,96);
	CPPUNIT_ASSERT( out->Check((" 13: 9d 38 60\n"), __LINE__, (__FILE__) ) );
	in->NoteOn(0,60,97);
	CPPUNIT_ASSERT( out->Check((" 14: 9e 3c 61\n"), __LINE__, (__FILE__) ) );
	in->NoteOn(0,63,98);
	CPPUNIT_ASSERT( out->Check((" 15: 9f 3f 62\n"), __LINE__, (__FILE__) ) );

	in->NoteOff(0,63,55);
	CPPUNIT_ASSERT( out->Check((" 15: 8f 3f 37\n"), __LINE__, (__FILE__) ) );
	// check sending note on with velocity = 0
	in->NoteOff(0,56,53);
	CPPUNIT_ASSERT( out->Check((" 13: 8d 38 35\n"), __LINE__, (__FILE__) ) );
	in->NoteOff(0,60,54);
	CPPUNIT_ASSERT( out->Check((" 14: 8e 3c 36\n"), __LINE__, (__FILE__) ) );

	DEBUGLOG (midiio, "321" );

	// Add check for NULL as tone system parameter
	in->NoteOn(0,56,96);
	CPPUNIT_ASSERT( out->Check(("  0: 90 38 60\n"), __LINE__, (__FILE__) ) );
	in->NoteOn(0,60,97);
	CPPUNIT_ASSERT( out->Check(("  1: 91 3c 61\n"), __LINE__, (__FILE__) ) );
	in->NoteOn(0,63,98);
	CPPUNIT_ASSERT( out->Check(("  2: 92 3f 62\n"), __LINE__, (__FILE__) ) );

	in->NoteOff(0,63,55);
	CPPUNIT_ASSERT( out->Check(("  2: 82 3f 37\n"), __LINE__, (__FILE__) ) );
	in->NoteOff(0,60,54);
	CPPUNIT_ASSERT( out->Check(("  1: 81 3c 36\n"), __LINE__, (__FILE__) ) );
	in->NoteOff(0,56,53);
	CPPUNIT_ASSERT( out->Check(("  0: 80 38 35\n"), __LINE__, (__FILE__) ) );

	// now collect data
	DEBUGLOG (midiio, "123" );
	in->NoteOn(0,56,96);
	CPPUNIT_ASSERT( out->Check(("  3: 93 38 60\n"), __LINE__, (__FILE__) ) );
	in->NoteOn(0,60,97);
	CPPUNIT_ASSERT( out->Check(("  5: 95 3c 61\n"), __LINE__, (__FILE__) ) );
	in->NoteOn(0,63,98);
	CPPUNIT_ASSERT( out->Check(("  4: 94 3f 62\n"), __LINE__, (__FILE__) ) );

	DEBUGLOG (midiio, "132" );

	in->NoteOn(0,56,96);
	CPPUNIT_ASSERT( out->Check(("  7: 97 38 60\n"), __LINE__, (__FILE__) ) );
	in->NoteOn(0,60,97);
	CPPUNIT_ASSERT( out->Check(("  6: 96 3c 61\n"), __LINE__, (__FILE__) ) );
	in->NoteOn(0,63,98);
	CPPUNIT_ASSERT( out->Check(("  8: 98 3f 62\n"), __LINE__, (__FILE__) ) );

	DEBUGLOG (midiio, "213" );

	in->NoteOn(0,56,96);
	CPPUNIT_ASSERT( out->Check((" 11: 9b 38 60\n"), __LINE__, (__FILE__) ) );
	in->NoteOn(0,60,97);
	CPPUNIT_ASSERT( out->Check((" 12: 9c 3c 61\n"), __LINE__, (__FILE__) ) );
	in->NoteOn(0,63,98);
	CPPUNIT_ASSERT( out->Check((" 10: 9a 3f 62\n"), __LINE__, (__FILE__) ) );

	DEBUGLOG (midiio, "231" );

	in->NoteOn(0,56,96);
	CPPUNIT_ASSERT( out->Check((" 15: 9f 38 60\n"), __LINE__, (__FILE__) ) );
	in->NoteOn(0,60,97);
	CPPUNIT_ASSERT( out->Check((" 13: 9d 3c 61\n"), __LINE__, (__FILE__) ) );
	in->NoteOn(0,63,98);
	CPPUNIT_ASSERT( out->Check((" 14: 9e 3f 62\n"), __LINE__, (__FILE__) ) );

	DEBUGLOG (midiio, "312" );

	in->NoteOn(0,56,96);
	CPPUNIT_ASSERT( out->Check(("  2: 92 38 60\n"), __LINE__, (__FILE__) ) );
	in->NoteOn(0,60,97);
	CPPUNIT_ASSERT( out->Check(("  1: 91 3c 61\n"), __LINE__, (__FILE__) ) );
	in->NoteOn(0,63,98);
	CPPUNIT_ASSERT( out->Check(("  0: 90 3f 62\n"), __LINE__, (__FILE__) ) );

	DEBUGLOG (midiio, "321" );

	// Add check for NULL as tone system parameter
	in->NoteOn(0,56,96);
	CPPUNIT_ASSERT( out->Check(("  2: 82 38 40\n  2: 92 38 60\n"), __LINE__, (__FILE__) ) );
	in->NoteOn(0,60,97);
	CPPUNIT_ASSERT( out->Check(("  2: 82 38 40\n  2: 92 3c 61\n"), __LINE__, (__FILE__) ) );
	in->NoteOn(0,63,98);
	CPPUNIT_ASSERT( out->Check(("  3: 83 38 40\n  3: 93 3f 62\n"), __LINE__, (__FILE__) ) );

	in->NoteOff(0,56,53);
	CPPUNIT_ASSERT( out->Check(("  7: 87 38 35\n"), __LINE__, (__FILE__) ) );
	in->NoteOff(0,60,54);
	CPPUNIT_ASSERT( out->Check(("  1: 81 3c 36\n"), __LINE__, (__FILE__) ) );
	in->NoteOff(0,63,55);
	CPPUNIT_ASSERT( out->Check(("  0: 80 3f 37\n"), __LINE__, (__FILE__) ) );

	mutabor::Panic(mutabor::midi::DEFAULT_PANIC);
	CPPUNIT_ASSERT( out->unsortedCheck(("\
  2: b2 40 00\n\
  3: b3 40 00\n\
  4: b4 40 00\n\
  5: b5 40 00\n\
  6: b6 40 00\n\
  8: b8 40 00\n\
 10: ba 40 00\n\
 11: bb 40 00\n\
 12: bc 40 00\n\
 13: bd 40 00\n\
 14: be 40 00\n\
 15: bf 40 00\n\
  2: b2 42 00\n\
  3: b3 42 00\n\
  4: b4 42 00\n\
  5: b5 42 00\n\
  6: b6 42 00\n\
  8: b8 42 00\n\
 10: ba 42 00\n\
 11: bb 42 00\n\
 12: bc 42 00\n\
 13: bd 42 00\n\
 14: be 42 00\n\
 15: bf 42 00\n\
  2: b2 44 00\n\
  3: b3 44 00\n\
  4: b4 44 00\n\
  5: b5 44 00\n\
  6: b6 44 00\n\
  8: b8 44 00\n\
 10: ba 44 00\n\
 11: bb 44 00\n\
 12: bc 44 00\n\
 13: bd 44 00\n\
 14: be 44 00\n\
 15: bf 44 00\n\
  2: b2 45 00\n\
  3: b3 45 00\n\
  4: b4 45 00\n\
  5: b5 45 00\n\
  6: b6 45 00\n\
  8: b8 45 00\n\
 10: ba 45 00\n\
 11: bb 45 00\n\
 12: bc 45 00\n\
 13: bd 45 00\n\
 14: be 45 00\n\
 15: bf 45 00\n\
  3: 83 3f 62\n\
  4: 84 3f 62\n\
  8: 88 3f 62\n\
 10: 8a 3f 62\n\
 14: 8e 3f 62\n\
  2: 82 3c 61\n\
  5: 85 3c 61\n\
  6: 86 3c 61\n\
 12: 8c 3c 61\n\
 13: 8d 3c 61\n\
 11: 8b 38 60\n\
 15: 8f 38 60\n\
  0: b0 78 00\n\
  1: b1 78 00\n\
  2: b2 78 00\n\
  3: b3 78 00\n\
  4: b4 78 00\n\
  5: b5 78 00\n\
  6: b6 78 00\n\
  7: b7 78 00\n\
  8: b8 78 00\n\
  9: b9 78 00\n\
 10: ba 78 00\n\
 11: bb 78 00\n\
 12: bc 78 00\n\
 13: bd 78 00\n\
 14: be 78 00\n\
"),
				   __LINE__,
				   (__FILE__) ) );

	in->NoteOff(0,56,53);
	CPPUNIT_ASSERT( out->Check((""), __LINE__, (__FILE__) ) );
	in->NoteOff(0,63,55);
	CPPUNIT_ASSERT( out->Check((""), __LINE__, (__FILE__) ) );
	in->NoteOff(0,60,54);
	CPPUNIT_ASSERT( out->Check((""), __LINE__, (__FILE__) ) );

	in->NoteOff(0,60,54);
	CPPUNIT_ASSERT( out->Check((""), __LINE__, (__FILE__) ) );
	in->NoteOff(0,56,53);
	CPPUNIT_ASSERT( out->Check((""), __LINE__, (__FILE__) ) );
	in->NoteOff(0,63,55);
	CPPUNIT_ASSERT( out->Check((""), __LINE__, (__FILE__) ) );

	in->NoteOff(0,60,54);
	CPPUNIT_ASSERT( out->Check((""), __LINE__, (__FILE__) ) );
	in->NoteOff(0,63,55);
	CPPUNIT_ASSERT( out->Check((""), __LINE__, (__FILE__) ) );
	in->NoteOff(0,56,53);
	CPPUNIT_ASSERT( out->Check((""), __LINE__, (__FILE__) ) );

	in->NoteOff(0,63,55);
	CPPUNIT_ASSERT( out->Check((""), __LINE__, (__FILE__) ) );
	// check sending note on with velocity = 0
	in->NoteOff(0,56,53);
	CPPUNIT_ASSERT( out->Check((""), __LINE__, (__FILE__) ) );
	in->NoteOff(0,60,54);
	CPPUNIT_ASSERT( out->Check((""), __LINE__, (__FILE__) ) );

	in->NoteOff(0,63,55);
	CPPUNIT_ASSERT( out->Check((""), __LINE__, (__FILE__) ) );
	in->NoteOff(0,60,54);
	CPPUNIT_ASSERT( out->Check((""), __LINE__, (__FILE__) ) );
	in->NoteOff(0,56,53);
	CPPUNIT_ASSERT( out->Check((""), __LINE__, (__FILE__) ) );

	in->Close();
	out->Close();
	DEBUGLOG (midiio, "|%s|" ,str(out->getOut()));
	CPPUNIT_ASSERT( out->Check(("...closed.\n"), __LINE__, (__FILE__) ) );
}

///\}

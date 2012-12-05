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
#include "src/kernel/routing/midi/tests/DevMidFTest.h"
#include "src/kernel/routing/midi/midicmn-inlines.h"
#include "src/kernel/routing/Route-inlines.h"


  
void OutputMidiFileTest::setUp() 
{ 
// change DEBUGA to DEBUG in case you need the debug output
#ifdef DEBUGA
	debugFlags::flags.timer = true;
	debugFlags::flags.midiio = true;
	debugFlags::flags.midifile = true;
#else 
	debugFlags::flags.timer = false;
	debugFlags::flags.midiio = false;
	debugFlags::flags.midifile = false;
#endif
	std::clog << "Running setUp()" << std::endl;

	initialize_boxes();
	GlobalReset();
	route = mutabor::RouteFactory::Create();
	route->Attatch(0);
	box = &mut_box[route->GetBox()];

	RealTime = true;
	out = static_cast<mutabor::OutputMidiFile *>(mutabor::DeviceFactory::CreateOutput(mutabor::DTMidiFile).get());
	out->SetName(_T("test_output.mid"));
	out->SetBendingRange(2);
	//out = new midicmnOutputDevice(3,_T("Test"));
	guard = out;

	route->Attatch (guard);
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
	out = NULL;
	guard = NULL;
	route = NULL;
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

	out->NoteOff(box,56,53,route.get(),0,false);
//	CPPUNIT_ASSERT( out->Check(_T("  0: 80 38 35\n")) );
	out->NoteOff(box,60,54,route.get(),0,false);
//	CPPUNIT_ASSERT( out->Check(_T("  1: 81 3c 36\n")) );
	out->NoteOff(box,63,55,route.get(),0,false);
//	CPPUNIT_ASSERT( out->Check(_T("  2: 82 3f 37\n")) );

	DEBUGLOG(midiio,_T("132"));

	out->NoteOn(box,56,96,route.get(),0,cd);
//	CPPUNIT_ASSERT( out->Check(_T("  3: b3 40 00\n  3: 93 38 60\n") ) );
	out->NoteOn(box,60,97,route.get(),0,cd);
//	CPPUNIT_ASSERT( out->Check(_T("  4: b4 40 00\n  4: 94 3c 61\n") ) );
	out->NoteOn(box,63,98,route.get(),0,cd);
//	CPPUNIT_ASSERT( out->Check(_T("  5: b5 40 00\n  5: 95 3f 62\n") ) );

	out->NoteOff(box,56,53,route.get(),0,false);
//	CPPUNIT_ASSERT( out->Check(_T("  3: 83 38 35\n")) );
	out->NoteOff(box,63,55,route.get(),0,false);
//	CPPUNIT_ASSERT( out->Check(_T("  5: 85 3f 37\n")) );
	out->NoteOff(box,60,54,route.get(),0,false);
//	CPPUNIT_ASSERT( out->Check(_T("  4: 84 3c 36\n")) );

	DEBUGLOG(midiio,_T("213"));

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

	DEBUGLOG(midiio,_T("231"));

	out->NoteOn(box,56,96,route.get(),0,cd);
//	CPPUNIT_ASSERT( out->Check(_T(" 10: ba 40 00\n 10: 9a 38 60\n") ) );
	out->NoteOn(box,60,97,route.get(),0,cd);
//	CPPUNIT_ASSERT( out->Check(_T(" 11: bb 40 00\n 11: 9b 3c 61\n") ) );
	out->NoteOn(box,63,98,route.get(),0,cd);
//	CPPUNIT_ASSERT( out->Check(_T(" 12: bc 40 00\n 12: 9c 3f 62\n") ) );

	out->NoteOff(box,60,54,route.get(),0,false);
//	CPPUNIT_ASSERT( out->Check(_T(" 11: 8b 3c 36\n")) );
	out->NoteOff(box,63,55,route.get(),0,false);
//	CPPUNIT_ASSERT( out->Check(_T(" 12: 8c 3f 37\n")) );
	out->NoteOff(box,56,53,route.get(),0,false);
//	CPPUNIT_ASSERT( out->Check(_T(" 10: 8a 38 35\n")) );

	DEBUGLOG(midiio,_T("312"));

	out->NoteOn(box,56,96,route.get(),0,cd);
//	CPPUNIT_ASSERT( out->Check(_T(" 13: bd 40 00\n 13: 9d 38 60\n") ) );
	out->NoteOn(box,60,97,route.get(),0,cd);
//	CPPUNIT_ASSERT( out->Check(_T(" 14: be 40 00\n 14: 9e 3c 61\n") ) );
	out->NoteOn(box,63,98,route.get(),0,cd);
//	CPPUNIT_ASSERT( out->Check(_T(" 15: bf 40 00\n 15: 9f 3f 62\n") ) );

	out->NoteOff(box,63,55,route.get(),0,false);
//	CPPUNIT_ASSERT( out->Check(_T(" 15: 8f 3f 37\n")) );
	// check sending note on with velocity = 0 
	out->NoteOff(box,56,53,route.get(),0,true);
//	CPPUNIT_ASSERT( out->Check(_T(" 13: 9d 38 00\n")) );
	out->NoteOff(box,60,54,route.get(),0,false);
//	CPPUNIT_ASSERT( out->Check(_T(" 14: 8e 3c 36\n")) );

	DEBUGLOG(midiio,_T("321"));

	// Add check for NULL as tone system parameter
	out->NoteOn(NULL,56,96,route.get(),0,cd);
//	CPPUNIT_ASSERT( out->Check(_T("  0: 90 38 60\n") ) );
	out->NoteOn(NULL,60,97,route.get(),0,cd);
//	CPPUNIT_ASSERT( out->Check(_T("  1: 91 3c 61\n") ) );
	out->NoteOn(NULL,63,98,route.get(),0,cd);
//	CPPUNIT_ASSERT( out->Check(_T("  2: 92 3f 62\n") ) );

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

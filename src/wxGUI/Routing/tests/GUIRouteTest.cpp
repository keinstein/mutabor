/** \file               -*- C++ -*-
 ********************************************************************
 * Description
 *
 * Copyright:   (c) 2012 Tobias Schlemmer
 * \author  Tobias Schlemmer <keinstein@users.berlios.de>
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
 * \addtogroup tests
 * \{
 ********************************************************************/
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/portability/Stream.h>
//#include "src/kernel/Runtime.h"

#include "src/wxGUI/Routing/tests/GUIRouteTest.h"
#include "src/wxGUI/Routing/DebugRoute.h"
#include "src/wxGUI/MutRouteWnd.h"

#include "wx/frame.h"

#include "src/kernel/routing/Route-inlines.h"

using namespace mutabor;
using namespace mutaborGUI;

void GUIRouteTest::setUp() 
{ 
// change DEBUGA to DEBUG in case you need the debug output
#ifdef DEBUGA
//		debugFlags::flags.timer = true;
//		debugFlags::flags.midifile = true;
#endif
//		RealTime = true;
}
  
void GUIRouteTest::tearDown()
{ 
#ifdef DEBUG
//		debugFlags::flags.timer = false;
//		debugFlags::flags.midifile = false;
#endif
//		in = NULL;
}
  
void GUIRouteTest::testConnect()
{ 	  
	ScopedOutputDevice out1, out2;
	ScopedRoute r1, r2;
	ScopedInputDevice in1, in2;
	ScopedBox MyNoBox;

	std::auto_ptr<wxWindow> parent(new wxFrame(0,wxID_ANY,_T("Test")));
	MutRouteWnd * wnd;

	out1 = DeviceFactory::CreateOutput(DTMidiFile,_T("testmidi_output1.mid"));
	out2 = DeviceFactory::CreateOutput(DTMidiFile,_T("testmidi_output2.mid"));
	MyNoBox = BoxFactory::Create(mutabor::NoBox);
	r1 = RouteFactory::Create();
	r2 = RouteFactory::Create();
	in1 = DeviceFactory::CreateInput(DTMidiFile,_T("testmidi_input1.mid"));
	in2 = DeviceFactory::CreateInput(DTMidiFile,_T("testmidi_input2.mid"));

	DebugCheckRoutes();
 
	connect (r1,out1);
	CPPUNIT_ASSERT(out1->nRoutes() == 1);
	CPPUNIT_ASSERT(out1->GetRoutes().front() == r1);
	CPPUNIT_ASSERT(r1->GetOutputDevice() == out1);
	DebugCheckRoutes();
	reconnect (r1,out1,out2);
	CPPUNIT_ASSERT(out1->nRoutes() == 0);
	CPPUNIT_ASSERT(out2->nRoutes() == 1);
	CPPUNIT_ASSERT(out2->GetRoutes().front() == r1);
	CPPUNIT_ASSERT(r1->GetOutputDevice() == out2);
	DebugCheckRoutes();
	CPPUNIT_ASSERT(out2->GetRoutes().front() == r1);
	reconnect (r1,out2,out1);
	CPPUNIT_ASSERT(out1->nRoutes() == 1);
	CPPUNIT_ASSERT(out2->nRoutes() == 0);
	CPPUNIT_ASSERT(out1->GetRoutes().front() == r1);
	CPPUNIT_ASSERT(r1->GetOutputDevice() == out1);
	DebugCheckRoutes();
	CPPUNIT_ASSERT(out1->GetRoutes().front() == r1);
	disconnect (r1,out1);
	DebugCheckRoutes();
	connect(r1,MyNoBox);
	DebugCheckRoutes();
	CPPUNIT_ASSERT(MyNoBox->GetRoutes().front() == r1);
	CPPUNIT_ASSERT(r1->GetBox() == MyNoBox);
	


	DebugCheckRoutes();
 
	connect (r1,in1);
	CPPUNIT_ASSERT(in1->nRoutes() == 1);
	CPPUNIT_ASSERT(in1->GetRoutes().front() == r1);
	CPPUNIT_ASSERT(r1->GetInputDevice() == in1);
	DebugCheckRoutes();
	reconnect (r1,in1,in2);
	CPPUNIT_ASSERT(in1->nRoutes() == 0);
	CPPUNIT_ASSERT(in2->nRoutes() == 1);
	CPPUNIT_ASSERT(in2->GetRoutes().front() == r1);
	CPPUNIT_ASSERT(r1->GetInputDevice() == in2);
	DebugCheckRoutes();
	CPPUNIT_ASSERT(in2->GetRoutes().front() == r1);
	reconnect (r1,in2,in1);
	CPPUNIT_ASSERT(in1->nRoutes() == 1);
	CPPUNIT_ASSERT(in2->nRoutes() == 0);
	CPPUNIT_ASSERT(in1->GetRoutes().front() == r1);
	CPPUNIT_ASSERT(r1->GetInputDevice() == in1);
	DebugCheckRoutes();
	CPPUNIT_ASSERT(in1->GetRoutes().front() == r1);
	disconnect (r1,in1);
	DebugCheckRoutes();

	wnd = new MutRouteWnd(parent.get());

	DebugCheckRoutes();
 
	connect (r1,out1);
	CPPUNIT_ASSERT(out1->nRoutes() == 1);
	CPPUNIT_ASSERT(out1->GetRoutes().front() == r1);
	CPPUNIT_ASSERT(r1->GetOutputDevice() == out1);
	DebugCheckRoutes();
	reconnect (r1,out1,out2);
	CPPUNIT_ASSERT(out1->nRoutes() == 0);
	CPPUNIT_ASSERT(out2->nRoutes() == 1);
	CPPUNIT_ASSERT(out2->GetRoutes().front() == r1);
	CPPUNIT_ASSERT(r1->GetOutputDevice() == out2);
	DebugCheckRoutes();
	CPPUNIT_ASSERT(out2->GetRoutes().front() == r1);
	reconnect (r1,out2,out1);
	CPPUNIT_ASSERT(out1->nRoutes() == 1);
	CPPUNIT_ASSERT(out2->nRoutes() == 0);
	CPPUNIT_ASSERT(out1->GetRoutes().front() == r1);
	CPPUNIT_ASSERT(r1->GetOutputDevice() == out1);
	DebugCheckRoutes();
	CPPUNIT_ASSERT(out1->GetRoutes().front() == r1);
	reconnect (out1,r1,r2);
	CPPUNIT_ASSERT(out1->nRoutes() == 1);
	CPPUNIT_ASSERT(out1->GetRoutes().front() == r2);
	CPPUNIT_ASSERT(r1->GetOutputDevice() == NULL);
	CPPUNIT_ASSERT(r2->GetOutputDevice() == out1);
	DebugCheckRoutes();
	CPPUNIT_ASSERT(out1->GetRoutes().front() == r2);
	disconnect (r2,out1);
	DebugCheckRoutes();


	DebugCheckRoutes();
 
	connect (r1,in1);
	CPPUNIT_ASSERT(in1->nRoutes() == 1);
	CPPUNIT_ASSERT(in1->GetRoutes().front() == r1);
	CPPUNIT_ASSERT(r1->GetInputDevice() == in1);
	DebugCheckRoutes();
	reconnect (r1,in1,in2);
	CPPUNIT_ASSERT(in1->nRoutes() == 0);
	CPPUNIT_ASSERT(in2->nRoutes() == 1);
	CPPUNIT_ASSERT(in2->GetRoutes().front() == r1);
	CPPUNIT_ASSERT(r1->GetInputDevice() == in2);
	DebugCheckRoutes();
	CPPUNIT_ASSERT(in2->GetRoutes().front() == r1);
	reconnect (r1,in2,in1);
	CPPUNIT_ASSERT(in1->nRoutes() == 1);
	CPPUNIT_ASSERT(in2->nRoutes() == 0);
	CPPUNIT_ASSERT(in1->GetRoutes().front() == r1);
	CPPUNIT_ASSERT(r1->GetInputDevice() == in1);
	DebugCheckRoutes();
	CPPUNIT_ASSERT(in1->GetRoutes().front() == r1);
	reconnect (in1,r1,r2);
	CPPUNIT_ASSERT(in1->nRoutes() == 1);
	CPPUNIT_ASSERT(in1->GetRoutes().front() == r2);
	CPPUNIT_ASSERT(r1->GetInputDevice() == NULL);
	CPPUNIT_ASSERT(r2->GetInputDevice() == in1);
	DebugCheckRoutes();
	CPPUNIT_ASSERT(in1->GetRoutes().front() == r2);
	disconnect (r2,in1);
	CPPUNIT_ASSERT(in1->nRoutes() == 0);
	CPPUNIT_ASSERT(r1->GetInputDevice() == NULL);
	DebugCheckRoutes();

	delete wnd;


	/* this is done automatically:
	in1 -> Destroy();
	in2 -> Destroy();
	r1 -> Destroy();
	r2 -> Destroy();
	out1 -> Destroy();
	out2 -> Destroy();
	*/
}

///\}

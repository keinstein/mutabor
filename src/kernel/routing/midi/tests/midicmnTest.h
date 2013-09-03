/** \file               -*- C++ -*-
 ********************************************************************
 * Test common midi functions
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

#if (!defined(MIDICMNTEST_H) && !defined(PRECOMPILE)) \
	|| (!defined(MIDICMNTEST_H_PRECOMPILED))
#ifndef PRECOMPILE
#define MIDICMNTEST_H
#endif

// ---------------------------------------------------------------------------
// headers
// ---------------------------------------------------------------------------

#include "src/kernel/Defs.h"

#ifndef MIDICMNTEST_H_PRECOMPILED
#define MIDICMNTEST_H_PRECOMPILED

// system headers which do seldom change

/// not for headers
#ifdef __BORLANDC__
    #pragma hdrstop
#endif


#include "src/kernel/treestorage.h"
#include "src/kernel/routing/midi/midicmn.h"

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/portability/Stream.h>
#include "src/kernel/Runtime.h"


class  midicmnOutputDevice:public mutabor::CommonMidiOutput<mutabor::DebugMidiOutputProvider,mutabor::OutputDeviceClass> {
public:
	typedef mutabor::CommonMidiOutput<mutabor::DebugMidiOutputProvider,mutabor::OutputDeviceClass> base;

	midicmnOutputDevice(wxString name, 
			    int id = -1, 
			    int bendingRange = 2):base(name,id,bendingRange) {}
	~midicmnOutputDevice() {}
	mutabor::DebugMidiOutputProvider & getOut() { return Out; }

// fix pure virtual functions:
	void Save(mutabor::tree_storage&) {}
	void Save(mutabor::tree_storage&, const mutabor::RouteClass*) {}
	void Load(mutabor::tree_storage&) {}
	void Load(mutabor::tree_storage&, mutabor::RouteClass*) {}
	void AddTime(frac) {}
	int GetMaxChannel() const { return 15; }
	int GetMinChannel() const { return 0; }
	bool Check(mutString s,int line = -1, mutString filename = _T(__FILE__)) {
		bool retval = (s == (mutString)Out);
		if (!retval) {
			DEBUGLOG(midiio,_T("Check failed:\n%s:%d:"),filename.c_str(),line);
			DEBUGLOG(midiio,_T("Expected:\n%s"),s.c_str());
			DEBUGLOG(midiio,_T("Got:\n%s"), mutString(Out).c_str());
		}
		Out.ClearData();
//		retval = true;
		return retval;
	}
};

class CommonMidiOutputTest : public CPPUNIT_NS::TestFixture 
{
	CPPUNIT_TEST_SUITE( CommonMidiOutputTest );
	CPPUNIT_TEST( testNoteOnOff );
	CPPUNIT_TEST( testMoreNotesThanChannels );
	CPPUNIT_TEST_SUITE_END();

public:

	CommonMidiOutputTest()
	{
	}

	virtual ~CommonMidiOutputTest()
	{
	}

	int countTestCases () const
	{ 
		abort();
		return 1; 
	}
  
	void setUp();
	void tearDown();

	void testNoteOnOff();
	void testMoreNotesThanChannels();

protected:
	mutabor::OutputDevice guard;
	midicmnOutputDevice * out;
	mutabor::Route  route;
	mutabor::Box box;
	mutabor::ChannelData cd;
};

class  midicmnInputDevice:public mutabor::CommonMidiInput<mutabor::InputDeviceClass> {
public:
	typedef mutabor::CommonMidiInput<mutabor::InputDeviceClass> base;

	midicmnInputDevice( wxString name = wxEmptyString):base(name) {}
	~midicmnInputDevice() {}

// fix pure virtual functions:
	void Save(mutabor::tree_storage&) {}
	void Save(mutabor::tree_storage&, const mutabor::RouteClass*) {}
	void Load(mutabor::tree_storage&) {}
	void Load(mutabor::tree_storage&, mutabor::RouteClass*) {}
	bool Open () { isOpen = true; return true; }
	proceed_bool shouldProceed(mutabor::Route R, DWORD midiCode,  int data =0) { return ProceedYes; }
	proceed_bool shouldProceed(mutabor::Route R, 
				   const std::vector<unsigned char > * midiCode,  
				   int data =0) { return ProceedYes; }

	void NoteOn(int channel, int inkey, int velocity) {
		Proceed(mutabor::midi::NOTE_ON | (channel & 0x0f)| ((inkey & 0x7f) << 8)  | (velocity & 0x7f) << 16);
	}
	void NoteOff(int channel, int inkey, int velocity) {
		Proceed(mutabor::midi::NOTE_OFF | (channel & 0x0f)| ((inkey & 0x7f) << 8)  | (velocity & 0x7f) << 16);
	}

};

class CommonMidiInputTest : public CPPUNIT_NS::TestFixture 
{
	CPPUNIT_TEST_SUITE( CommonMidiInputTest );
	CPPUNIT_TEST( testPanic );
	CPPUNIT_TEST( testGlobalPanic );
	CPPUNIT_TEST_SUITE_END();

public:

	CommonMidiInputTest()
	{
	}

	virtual ~CommonMidiInputTest()
	{
	}

	int countTestCases () const
	{ 
		abort();
		return 1; 
	}
  
	void setUp();
	void tearDown();

	void testPanic();
	void testGlobalPanic();

protected:
	mutabor::InputDevice guard;
	mutabor::OutputDevice outguard;
	midicmnOutputDevice * out;
	midicmnInputDevice * in;
	mutabor::Route  route;
	mutabor::Box box;
	mutabor::ChannelData cd;
};

#endif // precompiled
#endif // header loaded
///\}

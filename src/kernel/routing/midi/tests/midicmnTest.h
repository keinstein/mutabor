/** \file               -*- C++ -*-
 ********************************************************************
 * Test common midi functions
 *
 * Copyright:   (c) 2012 Tobias Schlemmer
 * \author  Tobias Schlemmer <keinstein@users.sourceforge.net>
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
#include "src/kernel/Frac.h"
#include "src/kernel/routing/midi/midicmn.h"

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/portability/Stream.h>
#include "src/kernel/Runtime.h"

class  midicmnOutputDevice:
	public mutabor::CommonMidiOutput<mutabor::DebugMidiOutputProvider,
					 mutabor::minimalOutputDeviceClass> {
public:
	typedef mutabor::CommonMidiOutput<mutabor::DebugMidiOutputProvider,
					  mutabor::minimalOutputDeviceClass> base;

	midicmnOutputDevice(std::string name,
			    int id = -1,
			    int bendingRange = 2):base(name,id,bendingRange) {}
	~midicmnOutputDevice() {}
	mutabor::DebugMidiOutputProvider & getOut() { return Out; }

// fix pure virtual functions:
	void Save(mutabor::tree_storage&) {}
	void Save(mutabor::tree_storage&, const mutabor::RouteClass*) {}
	void Load(mutabor::tree_storage&) {}
	void Load(mutabor::tree_storage&, mutabor::RouteClass*) {}
	void do_AddTime(mutabor::frac time) { mutUnused(time); }
	int GetMaxChannel() const { return 15; }
	int GetMinChannel() const { return 0; }
	bool Check(const std::string & s,
		   int line = -1,
		   const std::string & filename = (__FILE__)) {
		mutUnused(line);
		mutUnused(filename);
		bool retval = (s == (std::string)Out);
		if (!retval) {
			DEBUGLOG (always, "Check failed:\n%s:%d:" ,filename.c_str(),line);
			DEBUGLOG (always, "Expected:\n%s" ,MakePrintableC(s).c_str());
			DEBUGLOG (always, "Got:\n%s" , MakePrintableC(std::string(Out)).c_str());
		}
		Out.ClearData();
//		retval = true;
		return retval;
	}
	bool unsortedCheck(const std::string & s,
			   int line = -1,
			   const std::string & filename = (__FILE__));
};

class CommonMidiOutputTest : public CPPUNIT_NS::TestFixture
{
	CPPUNIT_TEST_SUITE( CommonMidiOutputTest );
	CPPUNIT_TEST( testNoteOnOff );
	CPPUNIT_TEST( testMoreNotesThanChannels );
	CPPUNIT_TEST_SUITE_END();

public:

	CommonMidiOutputTest():out(0)
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

	midicmnInputDevice( std::string name = ""):base(name) {
		channel_data.resize(16);
		// reserve a hash table that is large enough to hold all data
		// as rehashing leads to unpredictable results.
		current_keys.rehash(32);
	}
	~midicmnInputDevice() {}

// fix pure virtual functions:
	void Save(mutabor::tree_storage&) {}
	void Save(mutabor::tree_storage&, const mutabor::RouteClass*) {}
	void Load(mutabor::tree_storage&) {}
	void Load(mutabor::tree_storage&, mutabor::RouteClass*) {}
	bool Open () { isOpen = true; return true; }
	proceed_bool shouldProceed(mutabor::Route R,
				   uint32_t midiCode,
				   int data =0) {
		mutUnused(R);
		mutUnused(midiCode);
		mutUnused(data);
		return ProceedYes;
	}
	proceed_bool shouldProceed(mutabor::Route R,
				   const std::vector<unsigned char > & midiCode,
				   int data =0) {
		mutUnused(R);
		mutUnused(midiCode);
		mutUnused(data);
		return ProceedYes;
	}

	void NoteOn(int channel, int inkey, int velocity) {
		std::vector <unsigned char > message(3);
		message[0] = mutabor::midi::NOTE_ON | (channel & 0x0f);
		message[1] = inkey & 0x7f;
		message[2] = velocity & 0x7f;
		Proceed(message);
	}
	void NoteOff(int channel, int inkey, int velocity) {
		std::vector <unsigned char > message(3);
		message[0] = mutabor::midi::NOTE_OFF | (channel & 0x0f);
		message[1] = inkey & 0x7f;
		message[2] = velocity & 0x7f;
		Proceed(message);
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

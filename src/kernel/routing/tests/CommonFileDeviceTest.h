/** \file               -*- C++ -*-
********************************************************************
* Test for file device timer
*
* Copyright:   (c) 2012 TU Dresden
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
* \addtogroup tests
* \{
********************************************************************/
// availlable groups: GUI, route, kernel, muwx, debug, docview


#include "src/kernel/Defs.h"
#include "src/kernel/routing/CommonFileDevice-inlines.h"
#include "src/kernel/routing/Route-inlines.h"
#include "src/kernel/routing/timing.h"
#include "src/kernel/routing/thread.h"
#include <cstdlib>
#include "cppunit/extensions/HelperMacros.h"


class testCommonFileDeviceTimer: public mutabor::CommonFileInputDevice {
public:
	long i;
	long max;
	long min;
	mutint64 lasttime;
	mutint64 firsttime; 
	mutint64 pausetime;
	mutabor::Mutex timelock;
	testCommonFileDeviceTimer():CommonFileInputDevice(),i(0) {
		//		SetThreadKind(wxTHREAD_JOINABLE);
	}
	virtual ~testCommonFileDeviceTimer() {}
	void Play() {
		{
			mutabor::ScopedLock lock(timelock);
			mutabor::CurrentTime.UseRealtime(true);
			max = 0; min = 100000; i= 0;
			lasttime = mutabor::CurrentTime.Get();
		}
		CommonFileInputDevice::Play();
		{
			mutabor::ScopedLock lock(timelock);
			firsttime += lasttime - pausetime;
		}
		DEBUGLOG (timer, "Paused for %ld μs" ,(long) lasttime-pausetime);
	}

	void Pause() {
		CommonFileInputDevice::Pause();
		{
			mutabor::ScopedLock lock(timelock);
			pausetime = mutabor::CurrentTime.Get();
		}
	}

	bool Open() {
		{
			mutabor::ScopedLock lock(timelock);
			firsttime = lasttime = pausetime = mutabor::CurrentTime.Get();
		}
		return CommonFileInputDevice::Open();
	}

	void Stop() {
		CommonFileInputDevice::Stop();
		// check the overall time
		mutint64 time = mutabor::CurrentTime.Get() - firsttime;
		DEBUGLOG (timer, "Stopped at time: %ld μs" ,(long)time);
		CPPUNIT_ASSERT(time <= ((mutint64)1000*i*(i-1))/2+30000);
		CPPUNIT_ASSERT(time >= ((mutint64)1000*i*(i-1))/2-30000);
	}

	mutint64 PrepareNextEvent() {
		mutabor::ScopedLock lock(timelock);
		/* race condition: Mode should be DevicePlay, but it
		   may be any error free state as the device might
		   have been paused or stopped already. */
		CPPUNIT_ASSERT(Mode == mutabor::DevicePlay || 
			       Mode == mutabor::DevicePause || 
			       Mode == mutabor::DeviceStop);
		mutint64 newtime = mutabor::CurrentTime.Get();
		mutint64 tl = newtime;
//		tl = tl - (lasttime + (mutint64)(i*(i+1))/2);
		tl = tl - lasttime;
		mutint64 deviation =  tl - (mutint64) i*1000;
		if (max < deviation)  max = deviation;
		if (min > deviation || min == 0) min = deviation;
		DEBUGLOG (timer, "deviation = %ld, min = %ld, max = %ld" , (long)deviation, (long)min, (long)max);
		if (deviation > 10000) {
			std::cerr << "Too slow: (" << i << "^2 + " << i << ") / 2 = " << (i*(i+1))/2 
				  << " Runtime: " << tl << "μs" << std::endl;
			CPPUNIT_ASSERT(deviation <= 10000);
		}
		if (deviation < -10000) {
			std::cerr << "Too fast: (" << i << "^2 + " << i << ") / 2 = " << (i*(i+1))/2 
				  << " Runtime: " << tl << "μs" << std::endl;
			CPPUNIT_ASSERT(deviation >= -10000);
		}

		lasttime = newtime;
		if (++i<100) {
			DEBUGLOG (timer, "Returning %ldμs" ,(unsigned long)(i*1000));
			DEBUGLOG (timer, "Time spent in function: %ldμs" , (long)(mutabor::CurrentTime.Get()-newtime));
			return (mutint64)(i * 1000);
		}
		return GetNO_DELTA();
	}

	void Save(mutabor::tree_storage&, const mutabor::RouteClass*){}
	void Load(mutabor::tree_storage&, mutabor::RouteClass*){}
	virtual mutabor::ChannelData & GetChannelData(const mutabor::InputDeviceClass::current_keys_type::entry & key) const
	{ 
		return const_cast<mutabor::ChannelData & >(Cd);
	}

protected:
	static const mutabor::ChannelData Cd;
};

class CommonFileDeviceTest : public CPPUNIT_NS::TestFixture {
	CPPUNIT_TEST_SUITE( CommonFileDeviceTest );
	CPPUNIT_TEST( testTimer );
	CPPUNIT_TEST_SUITE_END();
	
public:
	CommonFileDeviceTest()
	{
	}

	virtual ~CommonFileDeviceTest()
	{
	}

	int countTestCases () const
	{ 
		return 1; 
	}
  
	void setUp() 
	{ 
		// change DEBUGA to DEBUG in case you need the debug output
#ifdef DEBUG
		//                debugFlags::flags.timer = true;
		isDebugFlag(thread) = true;
		// debugFlags::flags.midifile = true;
#endif
	}

	void tearDown()
		{
		}

#if __WXMSW__
	void usleep(int waitTime) {
		mutint64 time = waitTime;
		mutabor::CurrentTime.Sleep(time);
	}	
#endif
	
	void testTimer()
	{
		testCommonFileDeviceTimer * tim = new testCommonFileDeviceTimer();
		CPPUNIT_ASSERT(tim);
		mutabor::ScopedInputDevice prevent_from_deletion;
		prevent_from_deletion = tim;
		DEBUGLOG (timer, "Opening..." );
		tim->Open();
		CPPUNIT_ASSERT(tim->GetMode()==mutabor::DeviceStop);
		DEBUGLOG (timer, "Opened." );
		tim->Play();
		DEBUGLOG (timer, "Cheking play: mode = %d" , (int)tim->GetMode());
		CPPUNIT_ASSERT(tim->GetMode()==mutabor::DevicePlay);
		DEBUGLOG (timer, "Sleeping 2000μs" );
		mutint64 sleped = mutabor::CurrentTime.Get();
		usleep(2000);
		DEBUGLOG (timer, "Slept 2000μs" );
		sleped = mutabor::CurrentTime.Get() - sleped;
		DEBUGLOG (timer, "In fact it was %ldms" , (long)sleped);
		CPPUNIT_ASSERT(tim->GetMode()==mutabor::DevicePlay);
		DEBUGLOG (timer, "pausing" );
		tim->Pause();
		CPPUNIT_ASSERT(tim->GetMode()==mutabor::DevicePause);
		usleep(2000);
		CPPUNIT_ASSERT(tim->GetMode()==mutabor::DevicePause);
		tim->Pause();
		CPPUNIT_ASSERT(tim->GetMode()==mutabor::DevicePlay);
		usleep(2000);
		CPPUNIT_ASSERT(tim->GetMode()==mutabor::DevicePlay);
		tim->Pause();
		CPPUNIT_ASSERT(tim->GetMode()==mutabor::DevicePause);
		usleep(2000);
		CPPUNIT_ASSERT(tim->GetMode()==mutabor::DevicePause);
		tim->Play();
		CPPUNIT_ASSERT(tim->GetMode()==mutabor::DevicePlay);
		wxThread::ExitCode e = tim->WaitForDeviceFinish();
		//			std::clog << "Deviation min: " << tim->min << " max: " << tim->max << std::endl;
		CPPUNIT_ASSERT(e == 0); 
	}

	void sleepaftertests() {
		usleep(200000);
	}
};
///\}

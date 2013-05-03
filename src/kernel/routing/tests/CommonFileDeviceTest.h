/** \file               -*- C++ -*-
********************************************************************
* Test for file device timer
*
* $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/templates/template.cpp,v 1.5 2011/09/27 20:13:26 keinstein Exp $
* Copyright:   (c) 2012 TU Dresden
* \author  Tobias Schlemmer <keinstein@users.berlios.de>
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
#include "src/kernel/routing/CommonFileDevice-inlines.h"
#include "src/kernel/routing/Route-inlines.h"
#include <cstdlib>


class testCommonFileDeviceTimer: public mutabor::CommonFileInputDevice {
protected:
	wxStopWatch sw;
public:
	long i;
	long max;
	long min;
	testCommonFileDeviceTimer():CommonFileInputDevice(),i(0),sw() {
	}
	virtual ~testCommonFileDeviceTimer() {}
	void Play() {
		CurrentTimer.UseRealtime(true);
		max = 0; min = 100000; i= 0;
		CommonFileInputDevice::Play(wxTHREAD_JOINABLE );
		sw.Start();
	}

	void Pause() {
		CommonFileInputDevice::Pause();
	}

	bool Open() {
		sw.Start();
		CommonFileInputDevice::Open();
	}

	void Stop() {
		CommonFileInputDevice::Stop();
		if (sw.Time() > (i*(i-1))/2+30) {
			std::clog << "Played too long!" << std::endl;
			exit (1);
		}
		std::clog << "Played " << sw.Time() << "ms (goal is " << (i*(i-1))/2 << "ms)" << std::endl;
		if (sw.Time() < (i*(i-1))/2-30) {
			std::clog << "Played too short!" << std::endl;
			exit (1);
		}
		std::clog << "Played " << sw.Time() << "ms (goal is " << (i*(i-1))/2 << "ms)" << std::endl;
		sw.Pause();
	}
	mutint64 PrepareNextEvent() {
		mutint64 tl = wxGetLocalTimeMillis().GetValue();
		tl = tl - (referenceTime + (mutint64)(i*(i+1))/2);
		if (max < tl)  max = tl;
		if (min > tl || min == 0) min = tl;
		if (tl > 10) {
			std::cerr << "Too slow: (" << i << "^2 + " << i << ") / 2 = " << (i*(i+1))/2 
				  << " Runtime: " << tl << "ms" << std::endl;
			exit(3);
		}
		if (++i<100) {
			return (mutint64)(i * 1000);
		}
		return GetNO_DELTA();
	}

	void Save(tree_storage&, const mutabor::RouteClass*){}
	void Load(tree_storage&, mutabor::RouteClass*){}
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
	
	void testTimer()
		{
			testCommonFileDeviceTimer * tim = new testCommonFileDeviceTimer();
			CPPUNIT_ASSERT(tim);
			mutabor::InputDevice prevent_from_deletion(tim);
			tim->Open();
			CPPUNIT_ASSERT(tim->GetMode()==mutabor::DeviceStop);
			tim->Play();
			CPPUNIT_ASSERT(tim->GetMode()==mutabor::DevicePlay);
			usleep(2000);
			CPPUNIT_ASSERT(tim->GetMode()==mutabor::DevicePlay);
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
	
};
///\}

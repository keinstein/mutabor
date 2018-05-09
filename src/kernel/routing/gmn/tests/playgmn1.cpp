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
#include "src/kernel/routing/gmn/DevGIS.h"
#include "src/kernel/routing/CommonFileDevice-inlines.h"
#include "src/kernel/routing/Route-inlines.h"
#include "src/kernel/routing/timing.h"
#include <cstdlib>
#include <iostream>
//#include "src/wxGUI/TestInitializer.h"

#if 0
// Skip the GUI related checks from DebugRoute.cpp
#define no_wxGUI 1
#include "src/wxGUI/Routing/DebugRoute.cpp"
#undef no_wxGUI
#endif

/// not for headers
#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifdef __WXMSW__
#define sleep(x) Sleep(1000*x)
#endif


/*
class testCommonFileDeviceTimer: public mutabor::CommonFileInputDevice {
protected:
	wxStopWatch sw;
public:
	unsigned long i;
	unsigned long max;
	unsigned long min;
	testCommonFileDeviceTimer():CommonFileInputDevice(),i(0),sw() {
	}
	virtual ~testCommonFileDeviceTimer() {}
	void Play() {
		RealTime = true;
		max = 0; min = 100000;
		CommonFileInputDevice::Play(wxTHREAD_JOINABLE );
		sw.Start();
	}

	void Stop() {
		CommonFileInputDevice::Stop();
		if (sw.Time() > 30) {
			std::clog << "Played too long!" << std::endl;
			exit (1);
		}
		sw.Pause();
		exit(0);
	}
	mutint64 PrepareNextEvent() {
		mutint64 tmp = wxGetLocalTimeMillis();
		tmp = tmp - (referenceTime + mutint64((i*(i+1))/2));
		unsigned int tl = tmp.GetLo();
		if (max < tl)  max = tl;
		if (min > tl || min == 0) min = tl;
		if (tmp.GetHi() || tmp.GetLo() > 10) {
			std::cerr << "Too slow: (" << i << "^2 + " << i << ") / 2 = " << (i*(i+1))/2 
				  << " Runtime: " << tmp.GetHi() << "," << tmp.GetLo() << "ms" << std::endl;
			exit(3);
		}
		++i;
		if (i<100) {
			return (i*(i+1))/2;
		}
		return GetNO_DELTA();
	}

	void Save(tree_storage&, const mutabor::RouteClass*){}
	void Load(tree_storage&, mutabor::RouteClass*){}
};
*/

class myDevice: public mutabor::InputGis {
public:
	myDevice(): InputGis() {
		//		SetThreadKind(wxTHREAD_JOINABLE);
	}
	virtual void Stop() {
		std::clog << "Stopping..." << std::endl;
		mutabor::InputGis::Stop();
		std::clog << "Stopped" << std::endl;
	}	
	virtual bool Open() {
		std::clog << "Opening..." << std::endl;
		bool ret = mutabor::InputGis::Open();
		std::clog << "Opened." << std::endl;
		return ret;
	}	
	virtual void Close() {
		std::clog << "Closing..." << std::endl;
		mutabor::InputGis::Close();
		std::clog << "Closed." << std::endl;
	}
	virtual void Play() {
		std::clog << "Starting..." << std::endl;
		mutabor::CurrentTime.UseRealtime(true);
		mutabor::InputGis::Play();
		std::clog << "Started." << std::endl;
	}
	virtual void Pause() {
		std::clog << "Pausing..." << std::endl;
		mutabor::InputGis::Pause();
		std::clog << "Paused." << std::endl;
	}

};

int main(/* int argc, char **argv */)
{
#ifdef DEBUG
//	debugFlags::flags.timer = true;
//	debugFlags::flags.gmnfile = true;
	isDebugFlag(thread) = true;
#endif
	//	mutwxInitializer initializer;

	mutabor::InitDeviceFactories();
	mutabor::ScopedInputDevice in;
	in = static_cast<mutabor::InputDeviceClass *>(new myDevice());
//	mutabor::InputDevice in(mutabor::DeviceFactory::CreateInput(mutabor::DTMidiFile));
	if (!in) {
		DEBUGLOG2(always,("Class construction failed."));
		exit(-1);
	}
	in -> SetName(SRCDIR "/gmn1_source.gmn");
//	mutabor::InputDevice prevent_from_deletion(in);
	if (!(in -> Open())) {
		DEBUGLOG2(always,("Open failed. Exiting."));
		exit(1);
	}
	in -> Play();
	in -> Close();

	//e = in->WaitForDeviceFinish();
	//int e = 0;
//	std::clog << "Deviation min: " << tim->min << " max: " << tim->max << std::endl;
	return 0;
}
///\}

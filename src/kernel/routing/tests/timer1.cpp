/** \file               -*- C++ -*-
********************************************************************
* Test for file device timer
*
* $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/templates/template.cpp,v 1.5 2011/09/27 20:13:26 keinstein Exp $
* Copyright:   (c) 2012 TU Dresden
* \author  Tobias Schlemmer <keinstein@users.sourceforge.net>
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
#include "src/kernel/debug.h"
#include "src/kernel/routing/CommonFileDevice-inlines.h"
#include "src/kernel/routing/Route-inlines.h"
#include "src/kernel/routing/Device.h"
#include <cstdlib>
#include <iostream>

// Skip the GUI related checks from DebugRoute.cpp
#if 0
#define no_wxGUI 1
#include "src/wxGUI/Routing/DebugRoute.cpp"
#undef no_wxGUI
#include "src/wxGUI/TestInitializer.h"
#endif


#ifdef __WXMSW__
#define sleep(x) Sleep(1000*x)
#endif

#if 0
#include <wx/app.h>
#include <wx/stopwatch.h>
#include <wx/time.h>
#endif

/// not for headers
#ifdef __BORLANDC__
#pragma hdrstop
#endif

class testCommonFileDeviceTimer: public mutabor::CommonFileInputDevice {
public:
	typedef boost::chrono::milliseconds milliseconds;
	typedef boost::chrono::high_resolution_clock clocktype;
	typedef clocktype::time_point     time_point;

	time_point firsttime,lasttime;
	boost::atomic<milliseconds> i;
	boost::atomic<milliseconds> max;
	boost::atomic<milliseconds> min;
	testCommonFileDeviceTimer():CommonFileInputDevice(),i(milliseconds(0)) {
		//		SetThreadKind(wxTHREAD_JOINABLE);
	}
	virtual ~testCommonFileDeviceTimer() {}
	void Play() {
		std::cerr << "Play()" << std::endl;
		mutabor::CurrentTime.UseRealtime(true);
		max = milliseconds(0); min = milliseconds::max(); i= milliseconds(0);
		CommonFileInputDevice::Play();
		firsttime = lasttime = clocktype::now();
	}

	bool Open() {
		std::cerr << "Open()" << std::endl;
		lasttime = clocktype::now();
		return CommonFileInputDevice::Open();
	}

	void Stop() {
		std::cerr << "Stop()" << std::endl;
		CommonFileInputDevice::Stop();
		std::cerr << std::endl;

		if (firsttime == time_point())
			return;

		time_point::duration runtime = clocktype::now() - firsttime;
		milliseconds time_goal = (i.load(boost::memory_order_relaxed)*
					  (i.load(boost::memory_order_relaxed).count()-1))/2;
		std::cerr << "i reached " << i.load(boost::memory_order_relaxed) << std::endl;
		std::cerr << "Played " << runtime << " (goal is " << time_goal << ")" << std::endl;
		if ( runtime > (time_goal + milliseconds(30))) {
			std::cerr << "Played too long!" << std::endl;
			exit (1);
		}
		if (runtime < (time_goal-milliseconds(30))) {
			std::cerr << "Played too short!" << std::endl;
			exit (1);
		}
	}

	mutabor::microseconds PrepareNextEvent() {
		std::cerr << "PrepareNextEvent()" << std::endl;
		time_point tlp = clocktype::now();
		milliseconds tl = boost::chrono::duration_cast<milliseconds>(tlp - (lasttime))
			- i.load(boost::memory_order_relaxed);
			//+ (i*(i.count()+1))/2;
		if (max.load(boost::memory_order_relaxed) < tl)  max = tl;
		if (min.load(boost::memory_order_relaxed) > tl ) min = tl;
		if (tl > milliseconds(10)) {
			std::cerr << "Too slow: (" << i.load(boost::memory_order_relaxed)
				  << "^2 + " << i.load(boost::memory_order_relaxed) << ") / 2 = "
				  << (i.load(boost::memory_order_relaxed)
				      *(i.load(boost::memory_order_relaxed).count()+1))/2
				  << " Runtime: " << tl << std::endl;
			exit(3);
		}
		lasttime = tlp;
		if ((i=i.load(boost::memory_order_relaxed) + milliseconds(1))<milliseconds(100)) {
			std::cerr << "... " << i.load(boost::memory_order_relaxed) << " ... " << std::flush;
			return i.load(boost::memory_order_relaxed);
		}
		return NO_DELTA();
	}

	virtual void Save (mutabor::tree_storage & config,
			   const mutabor::RouteClass * route) {
		mutUnused(config);
		mutUnused(route);
	}
	virtual void Load (mutabor::tree_storage & config,
			   mutabor::RouteClass * route) {
		mutUnused(config);
		mutUnused(route);
	}

	virtual mutabor::ChannelData & GetChannelData(const mutabor::InputDeviceClass::current_keys_type::entry & key) const
	{
		mutUnused(key);
		return const_cast<mutabor::ChannelData & >(Cd);
	}

protected:
	static const mutabor::ChannelData Cd;
};

const mutabor::ChannelData testCommonFileDeviceTimer::Cd(0);


int main(/* int argc, char **argv */)
{
#ifdef DEBUG
	mutabor::mutabor_debug_flags.timer = false;
	mutabor::mutabor_debug_flags.thread = false;
#endif
	//mutwxInitializer initializer;

	testCommonFileDeviceTimer * tim = new testCommonFileDeviceTimer();
	mutabor::ScopedInputDevice guard;
	guard = tim;
	if (tim == NULL) {
		std::cerr << "Class construction failed." << std::endl;
		exit(-1);
	}
	mutabor::InputDevice prevent_from_deletion(tim);
	std::cerr << "Opening device..." << std::endl;
	tim->Open();
	std::cerr << "Starting playback..." << std::endl;
	tim->Play();

	int e = tim->WaitForDeviceFinish();
	std::cerr << "Closing device..." << std::endl;
	testCommonFileDeviceTimer::milliseconds min = tim->min, max = tim->max;
	tim->Close();
	std::cerr << "Deviation min: " << min << " max: " << max << std::endl;

	return e;
}
///\}

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


// Skip the GUI related checks from DebugRoute.cpp
#define no_wxGUI 1
#include "src/wxGUI/Routing/DebugRoute.cpp"
#undef no_wxGUI


/// not for headers
#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifdef __WXMSW__
#define sleep(x) Sleep(1000*x)
#endif

#include <wx/app.h>


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
		RealTime = true;
		max = 0; min = 100000; i= 0;
		CommonFileInputDevice::Play(wxTHREAD_JOINABLE );
		sw.Start();
	}

	bool Open() {
		sw.Start();
		CommonFileInputDevice::Open();
	}

	void Stop() {
		CommonFileInputDevice::Stop();
		std::clog << std::endl;
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
			std::clog << "." << i << std::flush;
			return (mutint64)(i * 1000);
		}
		return GetNO_DELTA();
	}

	void Save(tree_storage&, const mutabor::RouteClass*){}
	void Load(tree_storage&, mutabor::RouteClass*){}
};

int main(int argc, char **argv)
{
	wxApp::CheckBuildOptions(WX_BUILD_OPTIONS_SIGNATURE, "program");
#ifdef DEBUG
	debugFlags::flags.timer = true;
#endif

	wxInitializer initializer;
	if ( !initializer )
	{
		fprintf(stderr, "Failed to initialize the wxWidgets library, aborting.");
		return -1;
	}

	testCommonFileDeviceTimer * tim = new testCommonFileDeviceTimer();
	if (tim == NULL) {
		std::clog << "Class construction failed." << std::endl;
		exit(-1);
	}
	mutabor::InputDevice prevent_from_deletion(tim);
	tim->Open();
	tim->Play();

	wxThread::ExitCode e = tim->WaitForDeviceFinish();
	std::clog << "Deviation min: " << tim->min << " max: " << tim->max << std::endl;
	return (intptr_t)e; 
}
///\}

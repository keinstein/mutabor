/** \file               -*- C++ -*-
********************************************************************
* Test for file device timer
*
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
#include "src/kernel/routing/midi/DevMidF.h"
#include "src/kernel/routing/CommonFileDevice-inlines.h"
#include <cstdlib>
#include <wx/app.h>

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

class myDevice: public mutabor::InputMidiFile {
	virtual void Stop() {
		std::clog << "Stopping..." << std::endl;
		mutabor::InputMidiFile::Stop();
		std::clog << "Stopped" << std::endl;
	}	
	virtual bool Open() {
		std::clog << "Opening..." << std::endl;
		bool ret = mutabor::InputMidiFile::Open();
		std::clog << "Opened." << std::endl;
		return ret;
	}	
	virtual void Close() {
		std::clog << "Closing..." << std::endl;
		mutabor::InputMidiFile::Close();
		std::clog << "Closed." << std::endl;
	}
	virtual void Play() {
		std::clog << "Starting..." << std::endl;
		mutabor::CurrentTime.UseRealtime(true);
		mutabor::InputMidiFile::Play();
		std::clog << "Started." << std::endl;
	}
	virtual void Pause() {
		std::clog << "Pausing..." << std::endl;
		mutabor::InputMidiFile::Pause();
		std::clog << "Paused." << std::endl;
	}

};

int main(int argc, char **argv)
{
#ifdef DEBUG
	//	debugFlags::flags.timer = true;
	//	debugFlags::flags.midifile = true;
#endif
	wxApp::CheckBuildOptions(WX_BUILD_OPTIONS_SIGNATURE, "program");

	wxInitializer initializer;
	if ( !initializer )
	{
		fprintf(stderr, "Failed to initialize the wxWidgets library, aborting.");
		return -1;
	}

	mutabor::InitDeviceFactories();
	mutabor::InputDevice in(new myDevice());
//	mutabor::InputDevice in(mutabor::DeviceFactory::CreateInput(mutabor::DTMidiFile));
	if (!in) {
		std::clog << "Class construction failed." << std::endl;
		exit(-1);
	}
	in -> SetName(("+-*”„“"));
//	mutabor::InputDevice prevent_from_deletion(in);
	if (!(in -> Open())) {
		std::clog << "Open faild. Exiting." << std::endl;
		exit(0);
	}
	return 1; 
}
///\}

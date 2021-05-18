/** \file               -*- C++ -*-
********************************************************************
* Test for file device timer
*
* Copyright:   (c) 2012 Tobias Schlemmer
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
*
*
********************************************************************
* \addtogroup tests
* \{
********************************************************************/
// availlable groups: GUI, route, kernel, muwx, debug, docview


#include "src/kernel/Defs.h"
#include "src/kernel/routing/midi/DevMidF.h"
#include "src/kernel/routing/Route-inlines.h"
#include "src/kernel/routing/CommonFileDevice-inlines.h"
#include <cstdlib>
#include <iostream>

/// not for headers
#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifdef __WXMSW__
#define sleep(x) Sleep(1000*x)
#endif



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


int main(/* int argc, char **argv */)
{
#ifdef DEBUG
//	debugFlags::flags.timer = true;
//	debugFlags::flags.midifile = true;
#endif
	try {
		mutabor::InitDeviceFactories();
	} catch (const mutabor::RouteFactory::FactoryAlreadySet & e) {
		std::cerr << boost::current_exception_diagnostic_information();
		return 1;
	} catch (const mutabor::error::unreachable_exception & e) {
		std::cerr << boost::current_exception_diagnostic_information();
		return 1;
	}
	mutabor::CurrentTime.UseRealtime(false);
	mutabor::CurrentTime.Set(mutabor::microseconds(0));
	
	mutabor::ChannelData cd;
	mutabor::Route route;
	try {
		route = mutabor::RouteFactory::Create();
	} catch (const mutabor::RouteFactory::RouteFactoryNotSet & e) {
		std::cerr << boost::current_exception_diagnostic_information();
		return 1;
	}

	mutabor::Box box;
	try {
		box = mutabor::BoxFactory::Create(mutabor::Box0,0);
	} catch (const mutabor::BoxFactory::FactoryNotFound & e) {
		std::cerr << boost::current_exception_diagnostic_information();
		return 1;
	}
	connect(route, box);

	mutabor::OutputDevice guard;
	try {
		guard = mutabor::DeviceFactory::CreateOutput(mutabor::DTMidiFile);
	} catch (const mutabor::DeviceFactory::FactoryNotFound & e) {
		std::cerr << boost::current_exception_diagnostic_information();
		return 1;
	} catch (const mutabor::error::unreachable_exception & e) {
		std::cerr << boost::current_exception_diagnostic_information();
		return 1;
	}
//	mutabor::InputDevice in(mutabor::DeviceFactory::CreateInput(mutabor::DTMidiFile));
	if (!guard) {
		std::clog << "Class construction failed." << std::endl;
		exit(-1);
	}

	mutabor::OutputMidiFile * out = static_cast<mutabor::OutputMidiFile *>(guard.get());
	out->SetName(("test_linear.mid"));
	try {
		out->SetBendingRange(2);
	} catch (const mutabor::TrackData::delta_length_error & e) {
		std::cerr << boost::current_exception_diagnostic_information();
		return 1;
	} catch (const mutabor::error::unreachable_exception & e) {
		std::cerr << boost::current_exception_diagnostic_information();
		return 1;
	} catch (const boost::lock_error & e) {
		std::cerr << boost::current_exception_diagnostic_information();
		return 1;
	}

	connect(route, guard);
	route->SetOutputFrom (0);
	route->SetOutputTo (0);
	route->OutputAvoidDrumChannel (true);

	try {
		if (!(out -> Open())) {
			std::clog << "Open failed. Exiting." << std::endl;
			exit(1);
		}

		for (size_t i = 0 ; i <0x80; i++) {
			out->NoteOn(box, i, 0x40, route.get(), 0, cd);
			mutabor::CurrentTime = boost::chrono::milliseconds(250)*i+boost::chrono::milliseconds(125);
			out->NoteOff(box, i, 0x40, route.get(), 0, false);
			mutabor::CurrentTime = boost::chrono::milliseconds(250)*(i+1);
		}
	} catch (const boost::lock_error & e) {
		std::cerr << boost::current_exception_diagnostic_information();
		return 1;
	}
	
	out->Destroy();
	out = NULL;
	guard.reset();
		
	route -> Destroy();
	route.reset();
	box -> Destroy();
	box.reset();

	return 0;
}
///\}

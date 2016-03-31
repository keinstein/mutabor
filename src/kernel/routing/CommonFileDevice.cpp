/** \file               -*- C++ -*-
 ********************************************************************
 * File player class which solves common tasks of file related devices such as MIDI file players.
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
 * \addtogroup route
 * \{
 ********************************************************************/
// availlable groups: GUI, route, kernel, muwx, debug, docview

#include "src/kernel/Defs.h"
#include "src/kernel/routing/CommonFileDevice.h"
#include "src/kernel/routing/CommonFileDevice-inlines.h"
#include "src/kernel/routing/Route-inlines.h"
#include "src/kernel/routing/Box.h"

#include <boost/exception/diagnostic_information.hpp>

/// not for headers
#ifdef __BORLANDC__
    #pragma hdrstop
#endif

namespace mutabor {

	CommonFileOutputDevice::operator std::string() const {
		std::string s = OutputDeviceClass::operator std::string() +
			boost::str(boost::format("\n  Name = %s\n  session_id = %lu\n  routefile_id = %d")
				   % Name.c_str() % (unsigned long)session_id() % routefile_id);
		return s;
	}


	wxThread::ExitCode CommonFileInputDevice::exception_error() {
		std::string str = boost::current_exception_diagnostic_information();
		Stop();
		Mode=DeviceKilled;
		print_stacktrace(true);
		runtime_error(mutabor::runtime_error,
			      (_mut("The playback thread has been killed.\n\
Please report the error to the developers and include (if possible)\n	\
the current file and the following information:\n") + str).c_str());

		return (void *)Mode;
	}


#if __WXMSW__ && 0
	void CALLBACK CommonFileInputDevice::ostimer::Callback(PVOID lpParam, BOOLEAN TimerOrWaitFired)
	{
		static_cast<MidiTimer *>(lpParam)->Notify();
	}
	HANDLE CommonFileInputDevice::ostimer::TimerQueue = NULL;
#endif

}


///\}

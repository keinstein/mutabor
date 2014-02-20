/** \file               -*- C++ -*-
 ********************************************************************
 * Timing issues. Includes central timer.
 *
 * Copyright:   (c) 2013 Tobias Schlemmer
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
// availlable groups: GUI, route, kernel, muwx, debug, docview

#include <stdexcept>
#include "src/kernel/routing/timing.h"

/// not for headers
#ifdef __BORLANDC__
    #pragma hdrstop
#endif

namespace mutabor {
// CurrentTime ------------------------------------------------------
	CurrentTimer CurrentTime;

	std::pair<uint8_t,uint8_t> timing_params::get_MIDI_tick_signature() {
		std::pair<uint8_t,uint8_t> retval;
		mutint64 quotient;
		if (!is_fixed_ticks) {
			retval.first = (quarter_divisions >> 8)& 0xFF;
			retval.second = quarter_divisions & 0xFF;
			DEBUGLOG(midifile,_T("%lx: %x %x"),
				 quarter_divisions, 
				 retval.first,
				 retval.second);
			return retval;
		} else if (fps) {
			retval.first = (-fps) & 0xFF;
			mutint64 myfps = (fps == 29 ? 30:fps);
			quotient = quarter_divisions / myfps;
			retval.second = quotient & 0xFF;
			if (quarter_divisions % myfps) {
				BOOST_THROW_EXCEPTION( std::range_error(gettext_noop("frame rate does not divide time divisiens")));
			}
			
		} else { 
			if (!(quarter_divisions % 30)) 
				fps = 30;
			else if (!(quarter_divisions % 25)) 
				fps = 25;
			else if (!(quarter_divisions % 24)) 
				fps = 24;
			else {
				BOOST_THROW_EXCEPTION( std::range_error(gettext_noop("frame rate does not divide time divisiens")));
			}

			quotient = quarter_divisions / fps;
			retval.first = (-fps) & 0xff;
			retval.second = quotient & 0xFF;
		}

		if (quotient > 0xFF) {
			BOOST_THROW_EXCEPTION( std::range_error(gettext_noop("time division is too high for current frame rate")));
		}

		DEBUGLOG(midifile,_T("%lx: %x %x"),
			 quarter_divisions,
			 retval.first,
			 retval.second);
		return retval;
	}

	void timing_params::set_MIDI_tick_signature(uint8_t bfps, uint8_t bcount) {
		if (!(bfps & 0x80)) {
			// quarter divisions
			if (!bfps && ! bcount) 
				BOOST_THROW_EXCEPTION( std::range_error(gettext_noop("Trying to set bad midi header parameters")));
			quarter_divisions = (((int) bfps) << 8) + bcount;
			is_fixed_ticks = false;
			return;
		}
		if (! bcount) 
			BOOST_THROW_EXCEPTION( std::range_error(gettext_noop("Trying to set bad midi header parameters")));
		is_fixed_ticks = true;
		fps = 0x100 - (int) bfps;
		if (fps == 29) fps = 30; // ignoring NTSC 29.97Hz frame dropping should be ok.
		quarter_divisions = (mutint64)fps * (mutint64)bcount;
	}

	wxString timing_params::TowxString() {
		return wxString::Format(_T("\
is_fixed_ticks = %d, fps = %d, quarter_divisions = %ld, quarter_duration = %ld"),
					is_fixed_ticks, fps, quarter_divisions, quarter_duration);
	}


	
}

///\}

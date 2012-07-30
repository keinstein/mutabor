/** \file               -*- C++ -*-
 ********************************************************************
 * File player class which solves common tasks of file related devices such as MIDI file players.
 *
 * $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/templates/template.cpp,v 1.5 2011/09/27 20:13:26 keinstein Exp $
 * Copyright:   (c) 2012 Tobias Schlemmer
 * \author  Tobias Schlemmer <keinstein@users.berlios.de>
 * \date 
 * $Date$
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
 * \addtogroup route
 * \{
 ********************************************************************/
// availlable groups: GUI, route, kernel, muwx, debug, docview

#include "src/kernel/Defs.h"
#include "src/kernel/routing/CommonFileDevice.h"
#include "src/kernel/routing/CommonFileDevice-inlines.h"

/// not for headers
#ifdef __BORLANDC__
    #pragma hdrstop
#endif

namespace mutabor {

	unsigned long CommonFileOutputDevice::NRT_Speed=0l;

#if __WXMSW__ && 0
	void CALLBACK CommonFileInputDevice::ostimer::Callback(PVOID lpParam, BOOLEAN TimerOrWaitFired) 
	{
		static_cast<MidiTimer *>(lpParam)->Notify();
	}
	HANDLE CommonFileInputDevice::ostimer::TimerQueue = NULL;
#endif
}


///\}

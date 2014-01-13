/** \file               -*- C++ -*-
 ********************************************************************
 * Description
 *
 * Copyright:   (c) 2013 Tobias Schlemmer
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
 * \addtogroup tests
 * \{
 ********************************************************************/
// availlable groups: GUI, route, kernel, muwx, debug, docview, config, docview

// ---------------------------------------------------------------------------
// headers
// ---------------------------------------------------------------------------

#include "src/kernel/Defs.h"
#include "src/kernel/routing/tests/RouteTest.h"
#include "src/kernel/routing/midi/DevMidF.h"
#include "src/kernel/routing/Route-inlines.h"


/// not for headers
#ifdef __BORLANDC__
    #pragma hdrstop
#endif


void RouteTest::testDestroyAll() {
	mutabor::InputDevice In = mutabor::DeviceFactory::CreateInput(mutabor::DTMidiFile);
	mutabor::OutputDevice Out = mutabor::DeviceFactory::CreateOutput(mutabor::DTMidiFile);
	mutabor::Route r = mutabor::RouteFactory::Create();
	mutabor::Box box = mutabor::BoxFactory::Create(mutabor::Box0,0);
	connect(r,In);
	connect(r,Out);
	connect(r,box);
	In = NULL;
	Out = NULL;
	box = NULL;
	r = NULL;
	mutabor::InputDeviceClass::ClearDeviceList();
	mutabor::OutputDeviceClass::ClearDeviceList();
	mutabor::RouteClass::ClearRouteList();
	mutabor::BoxClass::ClearBoxList();
}
///\}

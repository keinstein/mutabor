/** \file               -*- C++ -*-
********************************************************************
* Description
*
* Copyright:   (c) 2016 Tobias Schlemmer
* \author  Tobias Schlemmer <keinstein@users.sf.net>
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
* \addtogroup debug
* \{
********************************************************************/
/* available groups: GUI, Parser, route, kernel, debug, docview, config, GUIroute */

/* we guard a little bit complicated to ensure the references are set right
 */

#include "src/wxGUI/TestInitializer.h"

/* system headers which do seldom change */
#include "wx/app.h"
/** not for headers */
#ifdef __BORLANDC__
#pragma hdrstop
#endif

mutwxInitializer::mutwxInitializer()
{
	wxApp::CheckBuildOptions(WX_BUILD_OPTIONS_SIGNATURE, "program");

	initializer = new wxInitializer;
	if ( !(*initializer) ) {
		fprintf(stderr, "Failed to initialize the wxWidgets library, aborting.");
		exit(255);
	}
}

mutwxInitializer::~mutwxInitializer() {
	delete initializer;
}



/** \} */

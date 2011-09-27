// -*-C++ -*-
/** \file
 ********************************************************************
 * Input device shape for reading GUIDO files in the route window.
 *
 * $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/muwx/Routing/OutputGuidoFileDeviceShape.cpp,v 1.4 2011/09/27 20:13:25 keinstein Exp $
 * \author Rüdiger Krauße <krausze@mail.berlios.de>,
 * Tobias Schlemmer <keinstein@users.berlios.de>
 * \date 2009/11/23
 * $Date: 2011/09/27 20:13:25 $
 * \version $Revision: 1.4 $
 * \license GPL
 *
 * $Log: OutputGuidoFileDeviceShape.cpp,v $
 * Revision 1.4  2011/09/27 20:13:25  keinstein
 * * Reworked route editing backend
 * * rewireing is done by RouteClass/GUIRoute now
 * * other classes forward most requests to this pair
 * * many bugfixes
 * * Version change: We are reaching beta phase now
 *
 * Revision 1.3  2011-02-20 22:35:59  keinstein
 * updated license information; some file headers have to be revised, though
 *
 * Revision 1.2  2010-11-21 13:15:50  keinstein
 * merged experimental_tobias
 *
 * Revision 1.1.2.3  2010-04-15 09:28:43  keinstein
 * changing routes works, but is not honoured by MIDI, yet
 *
 * Revision 1.1.2.2  2010/03/30 08:38:27  keinstein
 * added rudimentary command line support
 * changed debug system to allow selection of messages via command line
 * further enhancements to the route dialogs
 *
 * Revision 1.1.2.1  2010/01/14 10:16:43  keinstein
 * added output device shapes
 *
 * Revision 1.1.2.2  2010/01/11 12:51:52  keinstein
 * fix some problems due to splitting MutRouteShapes.{cpp,h}
 *
 * Revision 1.1.2.1  2009/11/30 12:08:57  keinstein
 * split MutRouteShapes into several files into directory Routing
 *
 * MutRouteShapes.cpp,v
 * Revision 1.1.2.3  2009/11/03 15:07:07  keinstein
 * Compile on Ubuntu 9.10
 * remove several interface and implementation pragmas
 * fixed some file names for case insensitive filesystems
 *
 * Revision 1.1.2.2  2009/11/03 12:39:31  keinstein
 * input device dialog: Allow to edit input devices
 * fix a bug on Mac OS X, that prevented Mutabor from starting if no MIDI device is availlable
 *
 * Revision 1.1.2.1  2009/08/10 11:23:12  keinstein
 * merged from wrong tree
 *
 * Revision 1.2  2009/08/10 11:15:47  keinstein
 * some steps towards new route window
 *
 * Revision 1.1  2008/11/03 15:31:54  keinstein
 * Added to the system
 *
 *
 ********************************************************************
 *\addtogroup route
 *\{
 ********************************************************************/
#include "Defs.h"
#include "OutputGuidoFileDeviceShape.h"
#include "muwx/Routing/GUIRoute-inlines.h"
//#include "MutApp.h"
//#include "MutIcon.h"
//#include "MutRouteWnd.h"
//#include "OutputDevDlg.h"
//#include "Device.h"

using namespace mutabor;

namespace mutaborGUI {

	void MutOutputGuidoFileDeviceShape::InitializeDialog(OutputDevDlg * out) const
	{
		wxASSERT(device);
		wxASSERT(device->GetType() == DTGis);
		wxASSERT(out);
		out -> SetType(DTGis);
		out -> SetGUIDOFile(device->GetName());
	}

	bool MutOutputGuidoFileDeviceShape::readDialog (OutputDevDlg * out)
	{
		wxASSERT(device);
		wxASSERT(device->GetType() == DTGis);
		wxASSERT(out);
		wxASSERT (out -> GetType() == DTGis);
		DEBUGLOG (other,_T ("File %s"),  (out -> GetGUIDOFile()).c_str());
		device->SetName (out -> GetGUIDOFile());
		SetLabel (device->GetName());
		return true;
	}

	wxPanel * MutOutputGuidoFileDeviceShape::GetOutputFilterPanel(wxWindow * parent, 
								      Route  route) const
	{
		GisOutputFilterPanel * panel = new GisOutputFilterPanel(parent);
		if (!panel) return NULL;
		// Room for actions
		return panel;
	}


	void MutOutputGuidoFileDeviceShape::ReadOutputFilterPanel(wxWindow * panel, Route  route)
	{
		GisOutputFilterPanel * pan = dynamic_cast<GisOutputFilterPanel *> (panel);
		if (!pan) {
			UNREACHABLEC;
			return;
		}
		// Room for actions
	
	}



	IMPLEMENT_DYNAMIC_CLASS(MutOutputGuidoFileDeviceShape, MutOutputDeviceShape)
}
/*
 * \}
 */

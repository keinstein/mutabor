// -*-C++ -*-
/** \file
 ********************************************************************
 * Devices base classes. Icons used in route window.
 *
 * $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/muwx/Routing/RouteIcons.cpp,v 1.7 2011/10/22 16:32:39 keinstein Exp $
 * \author Rüdiger Krauße <krausze@mail.berlios.de>,
 * Tobias Schlemmer <keinstein@users.berlios.de>
 * \date 2009/11/23
 * $Date: 2011/10/22 16:32:39 $
 * \version $Revision: 1.7 $
 * \license GPL
 *
 * $Log: RouteIcons.cpp,v $
 * Revision 1.7  2011/10/22 16:32:39  keinstein
 * commit to continue debugging on Linux/wine
 *
 * Revision 1.6  2011-09-27 20:13:25  keinstein
 * * Reworked route editing backend
 * * rewireing is done by RouteClass/GUIRoute now
 * * other classes forward most requests to this pair
 * * many bugfixes
 * * Version change: We are reaching beta phase now
 *
 * Revision 1.5  2011-09-08 16:51:21  keinstein
 * Set foreground color in box status windows
 * Fix updating box status windows
 * update RtMidi (includes Jack compilation mode)
 *
 * Revision 1.4  2011-02-20 22:35:59  keinstein
 * updated license information; some file headers have to be revised, though
 *
 * Revision 1.3  2011-01-11 00:42:27  keinstein
 * Fix a bug preventing Mutabor from starting on Win32 due to wrong usage of wxIcon/wxICON
 *
 * Revision 1.2  2010-11-21 13:15:50  keinstein
 * merged experimental_tobias
 *
 * Revision 1.1.2.3  2010-02-15 12:08:21  keinstein
 * intermediate update for backup progress
 *
 * Revision 1.1.2.2  2010/01/11 12:51:52  keinstein
 * fix some problems due to splitting MutRouteShapes.{cpp,h}
 *
 * Revision 1.1.2.1  2009/11/30 12:08:57  keinstein
 * split MutRouteShapes into several files into directory Routing
 *
 * MutRouteShapes.h,v 
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
#include "RouteIcons.h"
#include "BoxShape.h"
#include "MutApp.h"

#include "wx/image.h"
#include "Icon/DevUnknown.xpm"

namespace mutaborGUI {

	MutIcon DevUnknownBitmap;
	MutIcon MidiInputDevBitmap;
	MutIcon NewInputDevBitmap;
	MutIcon MidiOutputDevBitmap;
	MutIcon NewOutputDevBitmap;
	MutIcon MidiFileBitmap;
	MutIcon GuidoFileBitmap;
	MutIcon BoxBitmap;
	MutIcon NewBoxBitmap;
	MutIcon ActiveChannelBitmap;
	MutIcon PassiveChannelBitmap;


	static void initMutIcon(MutIcon & icon, 
				const wxString & filename,
				const wxBitmapType type) 
	{
		if (!icon.IsOk())
			if(!icon.LoadFile(filename,type))
				icon = DevUnknownBitmap;
	}

	bool initMutIconShapes() 
	{
		DevUnknownBitmap = MutICON(wxIcon(devunknown_xpm));
		if (!DevUnknownBitmap.IsOk()) return false;
  
		initMutIcon(MidiInputDevBitmap,
			    wxGetApp().GetResourceName (_T ("InputDevice.png")),
			    wxBITMAP_TYPE_PNG);
		initMutIcon(NewInputDevBitmap,
			    wxGetApp ().GetResourceName (_T ("NewInputDevice.png")),
			    wxBITMAP_TYPE_PNG);
		initMutIcon(MidiOutputDevBitmap,
			    wxGetApp ().GetResourceName (_T ("OutputDevice.png")),
			    wxBITMAP_TYPE_PNG);
		initMutIcon(NewOutputDevBitmap,
			    wxGetApp ().GetResourceName (_T ("NewOutputDevice.png")),
			    wxBITMAP_TYPE_PNG);
		initMutIcon(MidiFileBitmap,
			    wxGetApp ().GetResourceName (_T ("MidiFile.png")),
			    wxBITMAP_TYPE_PNG);
		initMutIcon(GuidoFileBitmap,
			    wxGetApp ().GetResourceName (_T ("GuidoFile.png")),
			    wxBITMAP_TYPE_PNG);
		initMutIcon(BoxBitmap,
			    wxGetApp ().GetResourceName (_T ("TuningBox.png")),
			    wxBITMAP_TYPE_PNG);
		initMutIcon(ActiveChannelBitmap,
			    wxGetApp ().GetResourceName (_T ("ActiveChannel.png")),
			    wxBITMAP_TYPE_PNG);
		initMutIcon(PassiveChannelBitmap,
			    wxGetApp ().GetResourceName (_T ("PassiveChannel.png")),
			    wxBITMAP_TYPE_PNG);
		initMutIcon(NewBoxBitmap,
			    wxGetApp ().GetResourceName (_T ("TuningBox.png")),
			    wxBITMAP_TYPE_PNG);
		initBoxColours();	
		return true;
	}
}

/*
 * \}
 */

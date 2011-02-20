// -*- C++ -*-
/** \file
 ********************************************************************
 * Box shape for route window.
 *
 * $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/muwx/Routing/BoxChannelShape.h,v 1.3 2011/02/20 22:35:58 keinstein Exp $
 * \author Rüdiger Krauße <krausze@mail.berlios.de>,
 * Tobias Schlemmer <keinstein@users.berlios.de>
 * \date 1998
 * $Date: 2011/02/20 22:35:58 $
 * \version $Revision: 1.3 $
 * \license GPL
 *
 * $Log: BoxChannelShape.h,v $
 * Revision 1.3  2011/02/20 22:35:58  keinstein
 * updated license information; some file headers have to be revised, though
 *
 * Revision 1.2  2010-11-21 13:15:48  keinstein
 * merged experimental_tobias
 *
 * Revision 1.1.2.8  2010-06-15 14:30:14  keinstein
 * allow deleting of input devices in route window
 * several bug fixes
 * rudimentary box deletion support
 *
 * Revision 1.1.2.7  2010/06/02 11:20:09  keinstein
 * Route.h:
 * 	new enum BoxType
 * 	new box type NewBox
 *
 * IconShape.cpp:
 * 	Hide shape in MutIconShape::DeleteSelf
 *
 * MutChild.h:
 * 	Changes on the increment value for Clientsize
 *
 * MutLogicWnd:
 * 	smaller whitespace fixes
 *
 * MutRouteWnd.cpp:
 * 	save sizerflags for MutBoxShape too
 *
 * BoxChannelShape.cpp:
 * 	rename CreateRouteShape to CreateRoutePanel
 * 	replace some wxDynamicCast by dynamic_cast
 * 	add Box “New Box“ if current box is not found
 * 	delete Route if route panel is disabled
 *
 * BoxChannelShape.h:
 * 	Update BoxShape layout  if necessary
 *
 * BoxDlg.cpp:
 * 	RoutePanel::AddBox: allow NULL boxShape
 * 	Fix Bug that didn't preselect GUIDO boxes and Through mode
 *
 * BoxShape.cpp:
 * 	fix color mapping for box numbers (shift right by 1 bit).
 * 	Add MutBoxShape::sizerFlags
 * 	SetBoxId: New function
 * 	Use SetBoxId for setting Box Id an Label in sync
 * 	AddChannel: call Layout()
 * 	implement replacement in DoLeftDblClick (enables New Box)
 * 	ShowBoxDialog: use dynamic_cast
 * 	ReadDialog: Add Channel only if new route is enabled (not deleted)
 * 	ReplaceSelfBy: new function (Unreachable as only needed for
 * 		class NewMutBoxShape)
 *
 * NewBoxShape.cpp/.h:
 * 	replaceSelfBy: new function
 * 	initialize Box id as NewBox
 *
 * *.po/mutabor.pot/ *.gmo
 *  	Sync with sources
 *
 * Revision 1.1.2.6  2010/05/07 11:40:28  keinstein
 * actual_settings
 *
 * Revision 1.1.2.5  2010/04/15 09:28:43  keinstein
 * changing routes works, but is not honoured by MIDI, yet
 *
 * Revision 1.1.2.4  2010/03/30 08:40:15  keinstein
 * added rudimentary command line support
 * changed debug system to allow selection of messages via command line
 * further enhancements to the route dialogs
 *
 * Revision 1.1.2.3  2010/02/15 12:08:21  keinstein
 * intermediate update for backup progress
 *
 * Revision 1.1.2.2  2010/01/14 09:34:24  keinstein
 * Checkin searching for a bug
 *
 * Revision 1.1.2.1  2009/11/30 12:08:57  keinstein
 * split MutRouteShapes into several files into directory Routing
 *
 * MutRouteShapes.h,v
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

#ifndef BOXCHANNELSHAPE_H
#define BOXCHANNELSHAPE_H

//#include <map>

//#include "wx/defs.h"
//#include "wx/icon.h"
//#include "wx/stattext.h"

#include "IconShape.h"
#include "Device.h"
#include "InputDeviceShape.h"
class InputFilterPanel;
class RoutePanel;
class OutputFilterPanel;
class MutRouteWnd;

// OutputDeviceShape.h loads BoxChannelShape.h, so we must define the class here.
class MutOutputDeviceShape;

class MutBoxChannelShape:public MutIconShape
{
	Route *route;
	MutInputDeviceShape * input;
	MutOutputDeviceShape * output;
	virtual MutIcon & GetMutIcon ();

public:

	MutBoxChannelShape (wxWindow * p = NULL, wxWindowID id = wxID_ANY, 
			    Route * r=NULL):MutIconShape(),route(r),input(NULL),output(NULL)
	{
		Create (p, id, r);
	}

	bool Create (wxWindow * p = NULL, wxWindowID id = wxID_ANY, 
		     Route * r=NULL)
	{ 
		route = r;
		if (!r) return false;
		r->setUserData (this);
		return MutIconShape::Create(p,id);
	}
	
	virtual ~MutBoxChannelShape()
	{
		if (route) {
			wxASSERT (route->getUserData() == this);
			route->setUserData (NULL);
		}
		DEBUGLOG(routing,_T("Parent is %p"),m_parent);
		if (m_parent) {
			m_parent->InvalidateBestSize();
			m_parent->SetInitialSize(wxDefaultSize);
			m_parent->Layout();		
		}
	}
	
	void SetInput(MutInputDeviceShape * device);
	MutInputDeviceShape * GetInput() { return input; }
	Route * GetRoute() const { return route; }
	void SetOutput(MutOutputDeviceShape * device, 
				   bool changeRoute = false);
	MutOutputDeviceShape * GetOutput() { return output; }

	void AddPossibleOutput(MutOutputDeviceShape * device);

	static void CreateRoutePanel(MutBoxChannelShape * channel, MutRouteWnd * parentwin, wxWindow * routeWindow, int selectBox);
	static void InitializeInputFilter(InputFilterPanel * panel, 
					  MutRouteWnd * par,
					  MutBoxChannelShape * shape = NULL);
	static void InitializeRoute(RoutePanel * panel, 
				    MutRouteWnd * par,
				    MutBoxChannelShape * shape = NULL,
				    int selectBox = NoBox);
		
	static void InitializeOutputFilter(OutputFilterPanel * panel, 
					  MutRouteWnd * par,
					  MutBoxChannelShape * shape = NULL);
	virtual void ReadPanel(RoutePanel * panel);

	virtual void DrawLines(wxDC & dc, const wxPoint & parentPosition) const;
	virtual wxPoint GetPerimeterPoint(const wxPoint &i,
					  const wxPoint &o,
					  const wxPoint & parentPosition) const;
	virtual void Refresh(bool eraseBackground = true, const wxRect* rect = NULL);
	/// Detaches the channel from a box shape.
	/**
	 * This function detaches a channel from its containing Box. The shape is not deteted.
	 */
	void DetachChannel();
};

WX_DECLARE_LIST (MutBoxChannelShape, MutBoxChannelShapeList);

#endif				/* BOXCHANNELSHAPE_H */
/*
 * \}
 */

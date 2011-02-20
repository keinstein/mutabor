// -*- C++ -*-
/** \file
 ********************************************************************
 * Box shape for route window.
 *
 * $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/muwx/Routing/BoxShape.h,v 1.3 2011/02/20 22:35:58 keinstein Exp $
 * \author Rüdiger Krauße <krausze@mail.berlios.de>,
 * Tobias Schlemmer <keinstein@users.berlios.de>
 * \date 1998
 * $Date: 2011/02/20 22:35:58 $
 * \version $Revision: 1.3 $
 * \license GPL
 *
 * $Log: BoxShape.h,v $
 * Revision 1.3  2011/02/20 22:35:58  keinstein
 * updated license information; some file headers have to be revised, though
 *
 * Revision 1.2  2010-11-21 13:15:48  keinstein
 * merged experimental_tobias
 *
 * Revision 1.1.2.8  2010-11-14 21:28:38  keinstein
 * implement loading and saving old files with new routing system
 *
 * Revision 1.1.2.7  2010-08-10 15:54:30  keinstein
 * new, direct route configuration on init
 *
 * Revision 1.1.2.6  2010/06/15 14:30:14  keinstein
 * allow deleting of input devices in route window
 * several bug fixes
 * rudimentary box deletion support
 *
 * Revision 1.1.2.5  2010/06/02 11:20:09  keinstein
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
 * Revision 1.1.2.4  2010/03/30 08:40:15  keinstein
 * added rudimentary command line support
 * changed debug system to allow selection of messages via command line
 * further enhancements to the route dialogs
 *
 * Revision 1.1.2.3  2010/02/15 12:08:21  keinstein
 * intermediate update for backup progress
 *
 * Revision 1.1.2.2  2010/01/11 12:51:52  keinstein
 * fix some problems due to splitting MutRouteShapes.{cpp,h}
 *
 * Revision 1.1.2.1  2009/11/30 12:08:57  keinstein
 * split MutRouteShapes into several files into directory Routing
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

#ifndef BOXSHAPE_H
#define BOXSHAPE_H

//#include <map>

//#include "wx/defs.h"
//#include "wx/icon.h"
//#include "wx/stattext.h"
#include "Defs.h"

#include "BoxChannelShape.h"
#include "BoxIconShape.h"
#include "Device.h"

#include "wx/colour.h"

wxColor BoxColor(int nr);
void initBoxColors();

class MutBoxShape:public MutBoxIconShape
{
protected:
	MutBoxIconShape * m_icon;
	wxSizer * channels;
	static wxSizerFlags sizerFlags;
	int boxId;
	static int maxBoxId;
	
public:
	MutBoxShape():MutBoxIconShape(),m_icon(NULL),channels(NULL),boxId(NoBox) {}

	MutBoxShape(wxStaticBox *box, int orient):
		MutBoxIconShape()
	{
		STUBC;
	}

	MutBoxShape(wxWindow * parent,wxWindowID wid, int Id=NoBox):
		MutBoxIconShape()
	{
		Create(parent,wid,Id);
	}
  
	virtual ~MutBoxShape()
	{ 
//		delete channels; 
	}
	
	bool Create(wxWindow * parent,wxWindowID wid, int Id=NoBox);

	static void SetSizerFlags (wxSizerFlags flags) {sizerFlags = flags; }
  static const wxSizerFlags & GetSizerFlags() { return sizerFlags; }

	virtual void DoLeftDblClick();
	void LeftDblClickEvent (wxMouseEvent & event) {
		DoLeftDblClick();
	}
	
	BoxDlg * ShowBoxDialog() const;
	virtual void InitializeDialog(BoxDlg * dlg) const;

		
	virtual MutBoxChannelShape * AddChannel(MutBoxChannelShape * channel);
	virtual MutBoxChannelShape * AddChannel(Route * route);
	virtual MutBoxChannelShape * AddChannel(RoutePanel * panel);
	
	virtual bool HasChannel(Route * route);

	virtual void AddPossibleOutput(MutOutputDeviceShape * device);
	

//	virtual void SetLabel(const wxString &s);

//	virtual void RecalcSizes();
//	virtual wxSize CalcMin();

	//  override to hide/show the static box as well
//	virtual void ShowItems (bool show);
	virtual void DrawLines(wxDC & dc);
  
	virtual bool Detach( wxWindow *window );
	virtual bool Detach( wxSizer *sizer ) 
	{
		if (channels) 
			return channels -> Detach(sizer); 
		else 
			return false;
	}
	virtual bool Detach( int index ) 
	{ 
		if (channels) 
			return channels -> Detach(index);
		else 
			return false;
	}
	virtual bool replaceSelfBy (MutBoxShape  * newshape);
	virtual bool DetachBox ();
	
	virtual bool readDialog (BoxDlg * box);
	virtual bool CanHandleType (int  type) { return true; }
	int GetBoxId() const { return boxId; }
private:
	void SetBoxId(int Id, bool layout=true);
	DECLARE_CLASS(MutBoxShape)
	DECLARE_EVENT_TABLE();
};

WX_DECLARE_LIST (MutBoxShape, MutBoxShapeList);


#endif				/* BOXSHAPE_H */
/*
 * \}
 */

// -*-C++ -*-

/** \file
********************************************************************
* Box shape for route window.
*
* $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/muwx/Routing/BoxShape.cpp,v 1.2 2010/11/21 13:15:48 keinstein Exp $
* \author Rüdiger Krauße <krausze@mail.berlios.de>,
* Tobias Schlemmer <keinstein@users.berlios.de>
* \date 2009/11/23
* $Date: 2010/11/21 13:15:48 $
* \version $Revision: 1.2 $
*
* $Log: BoxShape.cpp,v $
* Revision 1.2  2010/11/21 13:15:48  keinstein
* merged experimental_tobias
*
* Revision 1.1.2.17  2010-09-30 16:26:26  keinstein
* remove global variables routewindow and frame
* move route loading and route saving into MutRouteWnd
* implement MutRouteWnd::InitShapes.
* Destroy Route children before loading new route configuration (still some crashes)
*
* Revision 1.1.2.16  2010-09-29 15:06:40  keinstein
* Reset config before saving routing information and fix two bugs concerned with the deletion of boxes
*
* Revision 1.1.2.15  2010-09-29 13:03:30  keinstein
* config can be stored and restored with new treeconfig
*
* Revision 1.1.2.14  2010-09-15 17:58:02  keinstein
* old configuration can be loaded again.
*
* Revision 1.1.2.13  2010-08-10 15:54:30  keinstein
* new, direct route configuration on init
*
* Revision 1.1.2.12  2010-07-06 09:06:26  keinstein
* allow empty input and output devices in routes
*
* Revision 1.1.2.11  2010/06/16 08:53:24  keinstein
* make deletion of boxes in box window work
*
* Revision 1.1.2.10  2010/06/15 14:30:14  keinstein
* allow deleting of input devices in route window
* several bug fixes
* rudimentary box deletion support
*
* Revision 1.1.2.9  2010/06/02 11:20:09  keinstein
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
* Revision 1.1.2.8  2010/05/07 11:40:28  keinstein
* actual_settings
*
* Revision 1.1.2.7  2010/04/26 15:53:06  keinstein
* BoxDlg reacts on “Remove Route”. Implementation of routing must be checked.;
*
* Revision 1.1.2.6  2010/04/15 09:28:43  keinstein
* changing routes works, but is not honoured by MIDI, yet
*
* Revision 1.1.2.5  2010/03/30 08:38:27  keinstein
* added rudimentary command line support
* changed debug system to allow selection of messages via command line
* further enhancements to the route dialogs
*
* Revision 1.1.2.4  2010/02/22 10:14:02  keinstein
* transfer files to other computer
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
#include "Global.h"
//#include "wx/wx.h"
#include "BoxShape.h"
#include "DebugRoute.h"
//#include "MutApp.h"
//#include "MutIcon.h"
//#include "MutRouteWnd.h"
//#include "InputDevDlg.h"
//#include "Device.h"

wxColour BoxColors[MAX_BOX];

void initBoxColors() {
	for (int i = 1; i<= MAX_BOX; i++) {
		int r = ((i & 0x01) << 7 ) | ((i & 0x08) << 3) | ((i & 0x40) >> 1);
		r = r?r-1:0;
		int g = ((i & 0x02) << 6 ) | ((i & 0x10) << 2) | ((i & 0x80) >> 2);
		g = g?g-1:0;
		int b = ((i & 0x04) << 5 ) | ((i & 0x20) << 1) | ((i & 0x100) >> 3);
		b = b?b-1:0;
		DEBUGLOG2(other,_T("Box %d color %x,%x,%x"),i-1,r,g,b);
		BoxColors[i-1]=wxColour(r,g,b);
	}
}

/*
  wxColour BoxColors[MAX_BOX]  =
  {
  wxColour(0xFF, 0x00, 0x00),
  wxColour(0x00, 0xFF, 0x00),
  wxColour(0x80, 0x80, 0xFF),
  wxColour(0xFF, 0xFF, 0x00),
  wxColour(0x00, 0xFF, 0xFF),
  wxColour(0xFF, 0x00, 0xFF),
  wxColour(0xC0, 0xC0, 0xC0),
  wxColour(0x40, 0x80, 0x80),
  wxColour(0x00, 0x80, 0x00),
  wxColour(0x80, 0xFF, 0x00),
  wxColour(0xFF, 0xFF, 0x80),
  };
*/
wxColour BoxColor(int nr)
{

	DEBUGLOG2(other,_T("Color for box %d requested"),nr);
	if ( nr == GmnBox )
		return wxNullColour;
	else if (nr == NoBox) 
		return wxNullColour;
	//	nr %= 11;
	nr %= MAX_BOX;
	if (nr < 0) nr += MAX_BOX;
	DEBUGLOG2(other,_T("Returning Color for Box number %d"),nr);
	return BoxColors[nr];

}



static inline wxSize GetStaticBoxSize( MutBoxIconShape *box )
{
	// this has to be done platform by platform as there is no way to
	// guess the thickness of a wxStaticBox border
	wxSize s  = box->DoGetBestSize();
	DEBUGLOGTYPE(other,*box,_T("Best Size: %dx%d"),s.x,s.y);
	return s;
}

IMPLEMENT_CLASS(MutBoxShape, MutBoxIconShape)

BEGIN_EVENT_TABLE(MutBoxShape, MutBoxIconShape)
EVT_LEFT_DCLICK(MutBoxShape::LeftDblClickEvent)
//EVT_CLOSE(MutDeviceShape::DeleteSelfEvent)
END_EVENT_TABLE()

wxSizerFlags MutBoxShape::sizerFlags;
int MutBoxShape::maxBoxId = Box0 - 1;


/// TODO: fix tab order
bool MutBoxShape::Create(wxWindow * parent,wxWindowID wid, int Id)
{
	MutBoxIconShape::Create(parent,wid);
	channels = new wxBoxSizer(wxVERTICAL);
	SetSizer(channels);
	SetAutoLayout(true);
//	m_icon = new MutBoxIconShape(this,-1);
	m_icon = this;
	SetBoxId(Id,false);
	if (!m_icon) return false;
	return true;
}


void MutBoxShape::SetBoxId(int Id, bool layout) {
	boxId = Id;
	if (boxId >= maxBoxId) maxBoxId = boxId + 1;
	if (m_icon) {
		switch (boxId) {
			case NewBox:
				m_icon->SetLabel(_("New Box"));
				m_icon->SetBackgroundStyle(wxBG_STYLE_SYSTEM);
				break;
			case NoBox:
				m_icon->SetLabel(_("No Box / Though mode"));
				m_icon->SetBackgroundStyle(wxBG_STYLE_SYSTEM);
				break;
			case GmnBox:
				m_icon->SetLabel(_("GUIDO Box"));
				m_icon->SetBackgroundColour(BoxColor(boxId));
				break;
			default:
				m_icon->SetLabel(wxString::Format(_("Box %d"),
								  boxId));
				m_icon->SetBackgroundColour(BoxColor(boxId));
				break;
		}
		if (layout) {
			InvalidateBestSize();
			SetInitialSize(wxDefaultSize);
			m_parent->Layout();
		}
	}
	
}


MutBoxChannelShape * MutBoxShape::AddChannel(MutBoxChannelShape * channel) {
	if (channel) {
		channels->Add(channel,0,wxALIGN_CENTER_HORIZONTAL | wxEXPAND);
#ifdef DEBUG
		wxSize s = channel->GetBestSize();
		DEBUGLOG (other, _T("channel best size: %dx%d"),s.x,s.y);
#endif		
		InvalidateBestSize();
		SetInitialSize(wxDefaultSize);
		m_parent->Layout();
	}
	return channel;
}

MutBoxChannelShape * MutBoxShape::AddChannel(Route * route)
{
	DEBUGLOG (other, _T("Adding route %p to window %p"),route, m_parent);
	MutBoxChannelShape * channel = 
		new MutBoxChannelShape(this, wxID_ANY, route);
	
	return AddChannel(channel);
}

MutBoxChannelShape * MutBoxShape::AddChannel(RoutePanel * panel) {
	Route * route  = new Route (NULL,NULL, RTall, -1,-1, boxId, false);
	
# if 0
	MutBoxChannelShape * channel = new MutBoxChannelShape(this, wxID_ANY, route);
	channel -> ReadPanel(panel);


	return AddChannel(channel);
# endif
	MutBoxChannelShape * channel = AddChannel(route);
	if (channel) channel->ReadPanel(panel);
	return channel;
}

bool MutBoxShape::HasChannel(Route * route) {
	wxSizerItemList & list = channels->GetChildren();
	for (wxSizerItemList::iterator i = list.begin() ; i!= list.end() ; i++) {
		MutBoxChannelShape * channel = static_cast<MutBoxChannelShape *> ((*i)->GetWindow());
		wxASSERT(dynamic_cast<MutBoxChannelShape *>(channel));
		wxASSERT(dynamic_cast<MutBoxChannelShape *>((*i)->GetWindow()));
		if (channel->GetRoute() == route) return true;
	}
	return false;
}

void MutBoxShape::AddPossibleOutput(MutOutputDeviceShape * device) {
	wxSizerItemList list = channels->GetChildren();
	for (wxSizerItemList::iterator i = list.begin(); 
	     i != (list.end()); i++)
	{
      
		MutBoxChannelShape * channel = (MutBoxChannelShape *) ((*i)->GetWindow());
		wxASSERT(dynamic_cast<MutBoxChannelShape *>(channel));
		wxASSERT(dynamic_cast<MutBoxChannelShape *>((*i)->GetWindow()));
		channel->AddPossibleOutput(device);
	}
}


void MutBoxShape::DrawLines(wxDC & dc) 
{
	wxSizerItemList list = channels->GetChildren();
	for (wxSizerItemList::iterator i = list.begin(); 
	     i != (list.end()); i++)
	{
      
		MutBoxChannelShape * channel = static_cast<MutBoxChannelShape *> ((*i)->GetWindow());
		wxASSERT(dynamic_cast<MutBoxChannelShape *>(channel));
		wxASSERT(dynamic_cast<MutBoxChannelShape *>((*i)->GetWindow()));
		channel->DrawLines(dc, GetPosition());
	}
}

bool MutBoxShape::Detach( wxWindow *window )
{
	// avoid deleting m_staticBox in our dtor if it's being detached from the
	// sizer (which can happen because it's being already destroyed for
	// example)
	if ( window == m_icon )
	{
		UNREACHABLEC;
		m_icon = NULL;
	}

	return channels -> Detach( window );
}

void MutBoxShape::DoLeftDblClick() {
	BoxDlg * box = ShowBoxDialog();
	wxASSERT(box);
	
	if (!box) return;
	int Res = box->ShowModal();
	bool destroySelf = false;
	
	if (Res == wxID_OK) {
		int type = box->GetBoxType();
		
		if (CanHandleType (type)) {
			readDialog (box);
		} else {
			// MutBoxShape newbox = MutInputDeviceShape::CreateShape (type);
			MutBoxShape * newbox = new MutBoxShape(m_parent, wxID_ANY, type);
			if (newbox) {
				newbox->readDialog(box);
				destroySelf = replaceSelfBy(newbox);
//				m_parent->SetInitialSize(wxDefaultSize);
//				m_parent->InvalidateBestSize();
			}
		}
	} else if (Res == wxID_REMOVE) {
		destroySelf = DetachBox();
	}
	
	box->Destroy();
	
	// Signalize to delete this control
	// Unfortunately WXMAC segfaults if we use Destroy(), here.
	if (destroySelf) DeleteSelf();
	
	if (m_parent) {
		m_parent->Layout();
		Refresh(true);
		m_parent->Refresh(true);
	} else 	Refresh(true);
	
	DebugCheckRoutes();
}

/// Constructs the box configuration dialog.
/**
 * \todo use value “unknown” for dynamic dialog creation
 *
 */
BoxDlg * MutBoxShape::ShowBoxDialog() const{
	MutRouteWnd * parentwin = dynamic_cast<MutRouteWnd *>(GetParent());
	wxASSERT(parentwin);
	if (!parentwin) return NULL;
	
	BoxDlg * box = new BoxDlg (parentwin);
	wxASSERT(box);
	if (!box) return NULL;

	wxWindow * routeWindow = box->GetRouteWindow();
	wxASSERT(routeWindow);
	if (!routeWindow) {
		box->Destroy();
		return NULL;
	}
	wxGridSizer * routeSizer = dynamic_cast<wxGridSizer *> (routeWindow->GetSizer());
	
	if (!routeSizer) {
		if (routeWindow->GetSizer()) UNREACHABLEC;
		
		routeSizer = new wxGridSizer(4);
		if (!routeSizer) box->Destroy(); return NULL;
		routeWindow->SetSizer(routeSizer);		
	}
	
	wxSizerItemList list = channels->GetChildren();
	for (wxSizerItemList::iterator i = list.begin(); 
	     i != (list.end()); i++) {
		wxASSERT(dynamic_cast<MutBoxChannelShape *> ((*i) -> GetWindow()));
		MutBoxChannelShape::CreateRoutePanel(static_cast<MutBoxChannelShape *> ((*i)->GetWindow()),
						     parentwin, routeWindow, GetBoxId());
	}
	 
	InitializeDialog(box);

	routeWindow->Layout();
	routeWindow->FitInside();
	box->Layout();
	box->Fit();
	box->CenterOnParent(wxBOTH);
	
	return box;
}

void MutBoxShape::InitializeDialog(BoxDlg * dlg) const {
	wxASSERT(dlg);
	dlg->SetBoxType(boxId);
	if (boxId >= Box0) 
		dlg->SetBoxNumber(boxId);
	else
		dlg->SetBoxNumber(maxBoxId);
}

bool MutBoxShape::readDialog (BoxDlg * box) {
	wxASSERT(box);
	if (!box) return false;
	int type = box->GetBoxType();
	switch (type) {
		case NoBox:
		case GmnBox:
			SetBoxId(type);
			break;
		default:
			SetBoxId(box->GetBoxNumber());
			break;
	}
	
	wxWindow * routeWindow = box->GetRouteWindow();
	wxASSERT(routeWindow);
	if (!routeWindow) {
		return false;
	}
	
	wxWindowList & routePanels = routeWindow->GetChildren();
	for (wxWindowList::iterator i = routePanels.begin(); 
	     i != routePanels.end(); i++) {
		RoutePanel * panel = dynamic_cast<RoutePanel *> (*i);
		if (!panel) continue;
		wxASSERT(dynamic_cast<RoutePanel *> (*i));
		MutBoxChannelShape * channel = panel -> GetChannel();
		if (!channel && panel->IsEnabled()) 
			channel = AddChannel(panel);
		if (channel) {
			channel -> ReadPanel(panel);
		}
	}
	return true;
}

bool MutBoxShape::replaceSelfBy (MutBoxShape  * newshape)
{
	wxASSERT (newshape);
	
	// this is only used in NewMutBoxShape so far.
	// But we need it, when we implement other Box types
	UNREACHABLEC;
	
/*
	for(Route * route = newshape->device->ReplaceDevice (device);
	    route; route = route->Next) 
	{
		void * p = route->getUserData();
		wxASSERT (wxDynamicCast (p,MutBoxChannelShape));
		MutBoxChannelShape * channel = (MutBoxChannelShape *) p;
		
		wxASSERT (channel->GetInput() == this);
		channel->SetInput (newshape);
		
		
	}
	
	delete device;
	device = NULL;
	
	newshape->MoveBeforeInTabOrder (this);
	
	wxSizer * sizer = GetContainingSizer();
	sizer -> Replace (this, newshape, false);
	
	if (FindFocus()==this) {
		m_parent->Layout();
		m_parent->FitInside();
		m_parent->SetVirtualSize(wxDefaultSize);
		newshape->SetFocus();
	}
	
	Hide();	
	return true;
 */
	return false;
}

bool MutBoxShape::DetachBox() {
	wxSizerItemList &list = channels->GetChildren();
	for (wxSizerItemList::iterator i = list.begin(); 
	     i != (list.end()); i++) {
		MutBoxChannelShape * channel = dynamic_cast<MutBoxChannelShape *> ((*i) -> GetWindow());
		wxASSERT(channel);
		channel->DetachChannel();
	}
	return true;
}




#include "wx/listimpl.cpp"
WX_DEFINE_LIST (MutBoxShapeList);

/*
 * \}
 */
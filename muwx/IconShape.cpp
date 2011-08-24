// -*-C++ -*-

/** \file
********************************************************************
* Icon shape.
*
* $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/muwx/IconShape.cpp,v 1.5 2011/08/24 21:19:36 keinstein Exp $
* \author Rüdiger Krauße <krausze@mail.berlios.de>,
* Tobias Schlemmer <keinstein@users.berlios.de>
* \date 1998
* $Date: 2011/08/24 21:19:36 $
* \version $Revision: 1.5 $
* \license GPL
*
* $Log: IconShape.cpp,v $
* Revision 1.5  2011/08/24 21:19:36  keinstein
* first run with 2.9.2+
*
* Revision 1.4  2011-02-20 22:35:57  keinstein
* updated license information; some file headers have to be revised, though
*
* Revision 1.3  2010-12-11 02:10:09  keinstein
* make 2.9.1 build but Mutabor crashes still at runtime in an infinite recursion :-(
*
* Revision 1.2  2010-11-21 13:15:47  keinstein
* merged experimental_tobias
*
* Revision 1.1.2.7  2010-06-15 14:30:14  keinstein
* allow deleting of input devices in route window
* several bug fixes
* rudimentary box deletion support
*
* Revision 1.1.2.6  2010/06/02 11:20:08  keinstein
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
* Revision 1.1.2.5  2010/05/07 11:40:28  keinstein
* actual_settings
*
* Revision 1.1.2.4  2010/03/30 08:38:26  keinstein
* added rudimentary command line support
* changed debug system to allow selection of messages via command line
* further enhancements to the route dialogs
*
* Revision 1.1.2.3  2010/02/15 12:08:20  keinstein
* intermediate update for backup progress
*
* Revision 1.1.2.2  2010/01/14 09:34:24  keinstein
* Checkin searching for a bug
*
* Revision 1.1.2.1  2009/11/30 12:08:57  keinstein
* split MutRouteShapes into several files into directory Routing
*
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
#include "wx/defs.h"
//#include "wx/wx.h"
#include "IconShape.h"
//#include "MutApp.h"
//#include "MutIcon.h"
//#include "MutRouteWnd.h"
//#include "InputDevDlg.h"
//#include "Device.h"


IMPLEMENT_DYNAMIC_CLASS(MutIconShape, MutPanel)

BEGIN_EVENT_TABLE(MutIconShape, MutPanel)
  EVT_PAINT(MutIconShape::OnPaint)
  EVT_SET_FOCUS(MutIconShape::OnGetFocus)
  EVT_KILL_FOCUS(MutIconShape::OnKillFocus)
  EVT_CLOSE(MutIconShape::DeleteSelfEvent)
END_EVENT_TABLE()

bool MutIconShape::Create (wxWindow * parent, wxWindowID id)
{
	DEBUGLOG (other,_T (""));
	//    Enable(true);
	//		  SetBackgroundColour(BoxColor(GetId()));
	if (!MutPanel::Create(parent,id,wxDefaultPosition,wxDefaultSize,wxBORDER_RAISED | wxTAB_TRAVERSAL)) return false;
	Icon = GetMutIcon();
	wxASSERT(Icon.IsOk());
	SetAutoLayout(true);
	//	Layout();
	
	
	return true;
}



wxSize MutIconShape::DoGetBestSize() const 
{
	//  wxSize s(GetWindowBorderSize());
	wxSize s(0,0);
	wxSize s1(0,0);
	DEBUGLOG (other, _T("best size: %dx%d"),s.x,s.y);
//	return s;
	
	
	if (staticText) s += staticText->GetBestSize();
	DEBUGLOG (other, _T("staticText %p best size: %dx%d"),&staticText,s.x,s.y);
	if (GetIcon().IsOk()) {
		s.x = std::max (Icon.GetWidth(), s.x);
		int h = Icon.GetHeight();
		s.y += h;
	}

	if (GetSizer()) {
		s1 = GetSizer()->CalcMin();
		DEBUGLOG (other, _T("our %p sizer best size: %dx%d"),this,s1.x,s1.y);
		s.x = std::max(s.x,s1.x);
		s.y += std::max(s1.y,0);
	}
	s1 = GetSize() - GetClientSize();
	s.x += wxMax(0, s1.x);
	s.y += wxMax(0, s1.y);
	
	s1 = MutPanel::DoGetBestSize();
	DEBUGLOG (other, _T("our %p parent best size: %dx%d"),this,s1.x,s1.y);
	
	s1.x = std::max(s.x,s1.x);
	s1.y = std::max(s.y,s1.y);
	
	DEBUGLOG (other, _T("our %p best size: %dx%d"),this,s.x,s.y);
	wxConstCast(this,MutIconShape)->SetMinSize(s1);
	return s1;
}


void MutIconShape::SetFocus() {
	MutPanel::SetFocus();
	DEBUGLOG (other, _T(""));
	SetWindowStyle((GetWindowStyle() & ~ wxBORDER_RAISED)| wxBORDER_SUNKEN);
	GetContainingSizer()->Layout();
	Refresh();
}

void MutIconShape::OnGetFocus(wxFocusEvent & event)
{
	DEBUGLOG (other, _T(""));
	SetFocus();
}

void MutIconShape::OnKillFocus(wxFocusEvent & event)
{
	DEBUGLOG (other, _T(""));
	SetWindowStyle((GetWindowStyle() & ~ wxBORDER_SUNKEN) | wxBORDER_RAISED);
	wxSizer * sizer = GetContainingSizer();
	if (sizer) sizer->Layout();
	Refresh();
}


void MutIconShape::OnPaint( wxPaintEvent& WXUNUSED(event) )
{
	wxPaintDC dc(this);
	PrepareDC(dc);
	OnDraw(dc);
}

void MutIconShape::OnDraw (wxDC & dc) 
{
	wxRect size = GetRect();
	DEBUGLOG (other, _T("Checking icon"));

	if (!GetIcon().IsOk()) {
		SetIcon(GetMutIcon());
		DEBUGLOG (other, _T("Checking icon again"));

	}
	DEBUGLOG (other, _T("Icon ok."));

	int x = 0, y = 0;
	if (GetIcon().IsOk()) {
		DEBUGLOG (other, _T("Size: %dx%d"),GetIcon().GetHeight(),
			 GetIcon().GetWidth());
		x = (size.width-GetIcon().GetWidth())/2;
		dc.DrawIcon(GetIcon(), x, y);
	}

	DEBUGLOG (other, _T("Focus %p and this %p"),FindFocus(),this);
/*  Draw a black bock around focused item 
	if (FindFocus() == this) {
		DEBUGLOG (other, _T("Painting Box"));
		dc.SetPen(*wxBLACK_PEN);
		dc.SetBrush(*wxTRANSPARENT_BRUSH);
		dc.DrawRectangle(0,0,size.width,size.height);
	}
*/
}

wxPoint MutIconShape::GetPerimeterPoint(const wxPoint &i,const wxPoint &o) const {
	wxRect r = GetRect();
	DEBUGLOG (other, _T("Rect: (%d,%d) -- (%d,%d)"),r.x,r.y,r.x+r.width,r.y+r.height);
	DEBUGLOG (other, _T("Points: i = (%d,%d), o = (%d, %d)"),i.x,i.y,o.x,o.y);
	wxRect ir = GetIconRect();
#ifdef DEBUG
	std::cerr.flush();
	wxASSERT(r.Contains(i));
#endif

	wxPoint p;

	if (r.x+r.width <= o.x) {
		p.x = r.x + r.width;
		p.y = r.y + ir.height/2;
	} else if (r.x >= o.y) {
		p.x = r.x;
		p.y = r.y + ir.height/2;
	} else if (r.y <= o.y) {
		p.x = r.x + r.width/2;
		p.y = r.y;
	} else if (r.y + r.height >= o.y) {
		p.x = r.x + r.width/2;
		p.y = r.y + r.height;
	} else p = o;

	return p;
}

void MutIconShape::LineTo(wxDC &dc, const wxPoint & p)  const
{
	wxRect rect = GetRect();
	wxPoint p1(rect.x + rect.width/2, rect.y + Icon.GetHeight()/2);
	dc.DrawLine(p1,p);
}


bool MutIconShape::Recompute() 
{
	return true;
}

bool MutIconShape::Layout() {
	int w = 0, h = 0, y = Icon.GetHeight();
	GetVirtualSize(&w, &h);
	if (staticText) {
		staticText->Move(0,y);
		staticText->CentreOnParent(wxHORIZONTAL);
		wxSize s = staticText->GetSize();
		y += s.y;
	}
	// If there is a sizer, use it instead of the constraints
	if ( GetSizer() )
	{
		DEBUGLOG (other, _T("sizer"));
		GetSizer()->SetDimension( 0, y, w, h );
		PRINTSIZER(GetSizer());
	}
#if wxUSE_CONSTRAINTS
	else
	{
		DEBUGLOG (other, _T("constraints"));
		SatisfyConstraints(); // Find the right constraints values
		SetConstraintSizes(); // Recursively set the real window sizes
	}
#endif
	return true;
}

void MutIconShape::DeleteSelf()
{
	Hide();
	wxCloseEvent event(wxEVT_CLOSE_WINDOW, m_windowId);
	event.SetEventObject(this);
	event.SetCanVeto(false);
	
	GetEventHandler()->AddPendingEvent(event);
}

/*
 * \}
 */

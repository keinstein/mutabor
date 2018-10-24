// -*-C++ -*-

/** \file
********************************************************************
* Icon shape.
*
* \author Rüdiger Krauße,
* Tobias Schlemmer <keinstein@users.sourceforge.net>
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
*\addtogroup GUI
*\{
********************************************************************/

#include "src/kernel/Defs.h"
#include "src/wxGUI/IconShape.h"
#include "wx/defs.h"
#include "wx/sizer.h"
#include "wx/graphics.h"
#include "wx/dcclient.h"
#include "wx/dcmemory.h"
#include "wx/dcprint.h"
#include "wx/dcgraph.h"
#include <algorithm>
//#include "MutApp.h"
//#include "MutIcon.h"
//#include "MutRouteWnd.h"
//#include "InputDevDlg.h"
//#include "Device.h"

/** wx >= 2.9.0 uses its own template support
    \todo Check out how wxWidgets 2.9 supports templates */


#if wxCHECK_VERSION(4,0,0)
// look
#warning Check out how to use templates with IMPLEMENT_DYNAMIC_CLASS
#warning Check out how to use templates with BEGIN_EVENT_TABLE

#elif wxCHECK_VERSION(2,8,10)
// Checked version is 2.8.10
#else
#warning Your wxWidgets version may be too old template support. Expect compiler errors.
#endif


/*
// derive from MutPanel
IMPLEMENT_DYNAMIC_CLASS(MutIconShapeClass<MutPanel>, MutPanel)

BEGIN_EVENT_TABLE(MutIconShapeClass<MutPanel>, MutPanel)
  EVT_PAINT(MutIconShapeClass<MutPanel>::OnPaint)
  EVT_SET_FOCUS(MutIconShapeClass<MutPanel>::OnGetFocus)
  EVT_KILL_FOCUS(MutIconShapeClass<MutPanel>::OnKillFocus)
  EVT_CLOSE(MutIconShapeClass<MutPanel>::DeleteSelfEvent)
  EVT_LEFT_DOWN(MutIconShapeClass<MutPanel>::OnMouseClick)
END_EVENT_TABLE()

// derive from wxControl
IMPLEMENT_DYNAMIC_CLASS(MutIconShapeClass<wxControl>, wxControl)

BEGIN_EVENT_TABLE(MutIconShapeClass<wxControl>, wxControl)
  EVT_PAINT(MutIconShapeClass<wxControl>::OnPaint)
  EVT_SET_FOCUS(MutIconShapeClass<wxControl>::OnGetFocus)
  EVT_KILL_FOCUS(MutIconShapeClass<wxControl>::OnKillFocus)
  EVT_CLOSE(MutIconShapeClass<wxControl>::DeleteSelfEvent)
  EVT_LEFT_DOWN(MutIconShapeClass<wxControl>::OnMouseClick)
END_EVENT_TABLE()


*/


BEGIN_EVENT_TABLE_TEMPLATE1(MutIconShapeClass, T, T)
EVT_SIZE(MutIconShapeClass::OnSize)
  EVT_PAINT(MutIconShapeClass::OnPaint)
  EVT_SET_FOCUS(MutIconShapeClass::OnGetFocus)
  EVT_KILL_FOCUS(MutIconShapeClass::OnKillFocus)
//  EVT_CLOSE(MutIconShapeClass::DeleteSelfEvent)
  EVT_LEFT_DOWN(MutIconShapeClass::OnMouseClick)
EVT_MOVE(MutIconShapeClass::OnMove)
EVT_SIZE(MutIconShapeClass::OnSize)
END_EVENT_TABLE()

// common part of the macros below
#define wxIMPLEMENT_CLASS_COMMON_TEMPLATE1(name, basename, baseclsinfo2, func, T1) \
	template<>						\
	wxClassInfo name<T1>::ms_classInfo(wxT(#name "<" #T1 ">"),	\
					   &basename::ms_classInfo,	\
					   baseclsinfo2,		\
					   (int) sizeof(name<T1>),	\
					   (wxObjectConstructorFn) func); \
	template<>							\
	wxClassInfo *name<T1>::GetClassInfo() const			\
        { return &name<T1>::ms_classInfo; }

#define wxIMPLEMENT_CLASS_COMMON1_TEMPLATE1(name, basename, func, T1)	\
	wxIMPLEMENT_CLASS_COMMON_TEMPLATE1(name, basename, NULL, func, T1)


    // Single inheritance with one base class

#define IMPLEMENT_ABSTRACT_CLASS_TEMPLATE1(name, basename, T1)	\
    wxIMPLEMENT_CLASS_COMMON1_TEMPLATE1(name, basename, NULL, T1)


    // Single inheritance with one base class
#define IMPLEMENT_DYNAMIC_CLASS_TEMPLATE1(name, basename, T1)		\
	template<>							\
	wxObject* name<T1>::wxCreateObject()				\
        { return new name<T1>; }					\
	wxIMPLEMENT_CLASS_COMMON1_TEMPLATE1(name, basename,		\
					    name<T1>::wxCreateObject, T1)


IMPLEMENT_DYNAMIC_CLASS_TEMPLATE1(MutIconShapeClass, wxControl, wxControl)
IMPLEMENT_DYNAMIC_CLASS_TEMPLATE1(MutIconShapeClass, MutPanel, MutPanel)
//template wxClassInfo MutIconShapeClass<wxControl>::ms_classInfo;
/*
template<> wxClassInfo MutIconShapeClass<wxControl>::ms_classInfo
(wxT("MutIconShapeClass<wxControl>"),
	     &wxControl::ms_classInfo,
	     NULL,
	     (int) sizeof(MutIconShapeClass<wxControl>),
	     (wxObjectConstructorFn) NULL);

*/
/*
template<typename T>
wxClassInfo MutIconShapeClass<T>::ms_classInfo(wxT("MutIconShapeClass<T>"),
					       &T::ms_classInfo,
					       NULL,
					       (int) sizeof(MutIconShapeClass<T>),
					       (wxObjectConstructorFn) NULL);

template<typename T>
wxClassInfo *MutIconShapeClass<T>::GetClassInfo() const
{ return &MutIconShapeClass<T>::ms_classInfo; }
*/

// general case

/* used macros:  */
/*
#if 0
#define wxIMPLEMENT_CLASS_COMMON(name,basename,baseclsinfo2,func)	\
	wxClassInfo name::ms_classInfo(wxT(#name),			\
				       &basename::ms_classInfo,		\
				       baseclsinfo2,			\
				       (int) sizeof(name),		\
				       (wxObjectConstructorFn) func);	\
	wxClassInfo *name::GetClassInfo() const { return &name::ms_classInfo; }

#define wxIMPLEMENT_CLASS_COMMON1(name,basename,func)		\
	wxIMPLEMENT_CLASS_COMMON(name, basename, NULL, func)

#define IMPLEMENT_DYNAMIC_CLASS(name,basename)				\
	wxIMPLEMENT_CLASS_COMMON1(name, basename, name::wxCreateObject) \
	wxObject* name::wxCreateObject() { return new name; }
#endif

template<class T>
wxClassInfo MutIconShapeClass<T>::ms_classInfo(L"MutIconShapeClass<T>",
					  &T::ms_classInfo, __null,
					  (int) sizeof(MutIconShapeClass),
					  (wxObjectConstructorFn)
					  MutIconShapeClass<T>::wxCreateObject);

template<class T>
wxClassInfo *MutIconShapeClass<T>::GetClassInfo() const
{
	return &MutIconShapeClass<T>::ms_classInfo;
}

template<class T>
wxObject* MutIconShapeClass<T>::wxCreateObject()
{
	return new MutIconShapeClass;
}
// end of IMPLEMENT_DYNAMIC_CLASS



// BEGIN_EVENT_TABLE (the other macros should work without problems)
#if 0 // used macro:
#define BEGIN_EVENT_TABLE(theClass,baseClass)				\
	const wxEventTable theClass::sm_eventTable = {			\
		&baseClass::sm_eventTable,				\
		&theClass::sm_eventTableEntries[0]			\
	};								\
	const wxEventTable *theClass::GetEventTable() const {		\
		return &theClass::sm_eventTable;			\
	}								\
	wxEventHashTable theClass::sm_eventHashTable(theClass::sm_eventTable); \
	wxEventHashTable &theClass::GetEventHashTable() const {		\
		return theClass::sm_eventHashTable;			\
	}								\
	const wxEventTableEntry theClass::sm_eventTableEntries[] = {
#define TS_END_EVENT_TABLE }
#endif

template <class T>
const wxEventTable MutIconShapeClass<T>::sm_eventTable = {
	&T::sm_eventTable,
	&MutIconShapeClass<T>::sm_eventTableEntries[0]
};

template <class T>
const wxEventTable *MutIconShapeClass<T>::GetEventTable() const
{
	return &MutIconShapeClass<T>::sm_eventTable;
}

template <class T>
wxEventHashTable MutIconShapeClass<T>::sm_eventHashTable(MutIconShapeClass<T>::sm_eventTable);


template <class T>
wxEventHashTable &MutIconShapeClass<T>::GetEventHashTable() const
{
	return MutIconShapeClass<T>::sm_eventHashTable;
}

template <class T>
const wxEventTableEntry MutIconShapeClass<T>::sm_eventTableEntries[] = {
  EVT_PAINT(MutIconShapeClass<T>::OnPaint)
  EVT_SET_FOCUS(MutIconShapeClass<T>::OnGetFocus)
  EVT_KILL_FOCUS(MutIconShapeClass<T>::OnKillFocus)
  EVT_CLOSE(MutIconShapeClass<T>::DeleteSelfEvent)
  EVT_LEFT_DOWN(MutIconShapeClass<T>::OnMouseClick)
END_EVENT_TABLE()

*/


template<typename T>
bool MutIconShapeClass<T>::Create (wxWindow * parent, wxWindowID id, long style)
{
	TRACEC;
	//    Enable(true);
	//		  SetBackgroundColour(BoxColor(GetId()));
	Icon = GetMutIcon(); // this must be before create
	mutASSERT(Icon.IsOk());
	if (!parenttype::Create(parent,
			      id,
			      wxDefaultPosition,
			      wxDefaultSize,
			      style)) return false;

	maxBorderSize = this->GetWindowBorderSize()/2;
	if (style & (wxBORDER_RAISED | wxBORDER_SUNKEN)) {
		this->SetWindowStyle(
				     (this->GetWindowStyle() & ~ wxBORDER_MASK)| wxBORDER_SUNKEN);
		wxSize tmpBorderSize = this->GetWindowBorderSize()/2;
		maxBorderSize.IncTo(tmpBorderSize);

		this->SetWindowStyle(
				     (this->GetWindowStyle() & ~ wxBORDER_MASK)| wxBORDER_NONE);
		tmpBorderSize = this->GetWindowBorderSize()/2;
		maxBorderSize.IncTo(tmpBorderSize);
		maxBorderSize.IncTo(wxSize(0,0));
		maxBorderSize.IncBy(wxSize(1,1));
	}
#if __WXGTK__
	borderOffset = wxSize(0,0);
#else
	borderOffset = maxBorderSize;
//#else
//	borderOffset = maxBorderSize - tmpBorderSize;
#endif
	return true;
}


template<typename T>
bool MutIconShapeClass<T>::Destroy()
{
	this->Hide();
	wxSizer * sizer = this->GetContainingSizer();
	if (sizer) {
		sizer->Detach(this);
		this->SetSizer(NULL);
	}

	if ( !wxPendingDelete.Member(this) )
        wxPendingDelete.Append(this);

	return true;
}


template<typename T>
wxSize MutIconShapeClass<T>::DoGetBestSize() const
{
	//  wxSize s(GetWindowBorderSize()/2);
	wxSize s(0,0);
	wxSize s1(0,0);
	DEBUGLOG (other, "best size: %dx%d" ,s.x,s.y);
//	return s;


	if (staticText) s += staticText->GetBestSize();
	DEBUGLOG (other, "staticText %p best size: %dx%d" ,(void*)&staticText,s.x,s.y);
	if (GetIcon().IsOk()) {
		s.x = std::max (Icon.GetWidth(), s.x);
		int h = Icon.GetHeight();
		s.y += h;
	}

	if (this->GetSizer()) {
		s1 = this->GetSizer()->CalcMin();
		DEBUGLOG (other, "our %p sizer best size: %dx%d" ,(void*)this,s1.x,s1.y);
		s.x = std::max(s.x,s1.x);
		s.y += std::max(s1.y,0);
	}

#ifdef DEBUG
	wxSize s2 = this->GetSize() - this->GetClientSize();
	s2.IncTo(wxSize(0,0));

	DEBUGLOG (gui, "s1: (%d,%d), maxBorderSize: (%d,%d)" ,
		 s2.x,s2.y,2*maxBorderSize.x,2*maxBorderSize.y);
	mutASSERT(!maxBorderSize.x || s2.x <= 2*maxBorderSize.x);
	mutASSERT(!maxBorderSize.y || s2.y <= 2*maxBorderSize.y);
#endif

	s += maxBorderSize + maxBorderSize;

	// s1 = MutPanel::DoGetBestSize();
        // call to base class not needed.
	DEBUGLOG (other, "our %p parent best size: %dx%d" ,(void*)this,s1.x,s1.y);

	s1.IncTo(s);

	DEBUGLOG (other, "our %p best size: %dx%d" ,(void*)this,s.x,s.y);
	wxConstCast(this,MutIconShapeClass<T>)->SetMinSize(s1);
	this->CacheBestSize(s1);
	return s1;
}


template<typename T>
  void MutIconShapeClass<T>::UpdateBorder (long flag) {
#if __WXMSW__
	  mutUnused(flag);
	// MS Windows does not allow to change the border syle
	// So we handle the border in OnSize()
	this->Refresh(true);
	return;
#else
	this->Freeze();
	this->SetWindowStyle((this->GetWindowStyle() & ~(long)wxBORDER_MASK)|flag);
//	wxSizer * sizer = GetContainingSizer();

//	this->GetParent()->Layout();
//	this->GetParent()->InvalidateBestSize();
#if __WXGTK__
	borderOffset = wxSize(0,0);
//#elif __WXMAC__
#else
	borderOffset = maxBorderSize - this->GetWindowBorderSize()/2;
#endif
	this->InvalidateBestSize();

	if (this->GetParent())
		this->GetParent()->Layout();
	Layout();
	if (!this->IsShown()) {
		this->Thaw();
		return;
	}

	wxSizer * sizer = this->GetSizer();
	if (sizer)
		sizer->SetSizeHints(this);
	this->Fit();

	wxPoint pos = this->GetPosition();
	pos -= maxBorderSize;
	wxSize size = this->GetSize();
	size += maxBorderSize + maxBorderSize;
//	ClearPerimeterPoints();
	this->GetParent()->RefreshRect(wxRect(pos.x,pos.y,size.x,size.y));
#if __WXGTK__
	this->Refresh(true);
//	this->Update();
#endif
	this->GetParent()->Update();
	this->Thaw();
#endif
}

template<typename T>
void MutIconShapeClass<T>::GotFocus() {
#ifdef DEBUG
	DEBUGLOG (other, "Current focus is at" );
	wxWindow * focuswin =wxWindow::FindFocus();
	if (focuswin) {
		DEBUGLOGTYPE (other,
			      (*(focuswin)),
			      (" focus has objet %p"),
			      (void*)wxWindow::FindFocus());
	} else
		DEBUGLOG (other, "NULL pointer" );
#endif
/*
	parenttype::SetFocus();
#ifdef DEBUG
	DEBUGLOG (other, "Current focus is at" );
	focuswin =wxWindow::FindFocus();
	if (focuswin) {
		DEBUGLOGTYPE (other,
			      (*(focuswin)),
			      (" focus has objet %p"),
			      wxWindow::FindFocus());
	} else
		DEBUGLOG (other, "NULL pointer" );
#endif
*/
	UpdateBorder(wxBORDER_SUNKEN);
}



template<typename T>
void MutIconShapeClass<T>::LostFocus()
{
	TRACEC;
	UpdateBorder(wxBORDER_NONE);
}


template<typename T>
void MutIconShapeClass<T>::OnGetFocus(wxFocusEvent & event)
{
	TRACEC;
	GotFocus();
	event.Skip();
}

template<typename T>
void MutIconShapeClass<T>::OnKillFocus(wxFocusEvent & event)
{
	TRACEC;
	LostFocus();
	event.Skip();
}

template<typename T>
void MutIconShapeClass<T>::OnMouseClick(wxMouseEvent & event)
{
	mutUnused(event);
	TRACEC;
	this->SetFocus();
}

  // not configured to use constraints
  template<typename T>
  void MutIconShapeClass<T>::OnSize(wxSizeEvent& event)
  {
//    if (this->GetAutoLayout())
	  Layout();
	  event.Skip();
}

template<typename T>
void MutIconShapeClass<T>::OnMove( wxMoveEvent & event )
{
//	ClearPerimeterPoints();
//	GetParent()->Refresh();
	event.Skip();
}

template<typename T>
void MutIconShapeClass<T>::OnPaint( wxPaintEvent& WXUNUSED(event) )
{
	wxPaintDC dc(this);
	this->PrepareDC(dc);
	this->OnDraw(dc);
}

/* dc should be either wxWindowDC (and we create a graphicscontext) or
   preferable a wxGCDC object that has already a graphics context */
template<typename T>
void MutIconShapeClass<T>::OnDraw (wxDC & dc)
{
	wxRect size = this->GetClientSize();
#if __WXMSW__
	if (wxWindow::FindFocus() == this) {
		// MSW doesn't allow to change the border
		for (int i = 0 ; i < maxBorderSize.x - 1 ; i++) {
			dc.DrawLine(i,i,size.width-i,i);
			dc.DrawLine(i,size.height-i,size.width-i,size.height-i);
		}
		for (int i = 0 ; i < maxBorderSize.y - 1 ; i++) {
			dc.DrawLine(size.width-i,i,size.width-i,size.height-i);
			dc.DrawLine(i,i,i,size.height-i);
		}
	}
#endif

	DEBUGLOG (other, "Checking icon" );

	if (!GetIcon().IsOk()) {
		SetIcon(GetMutIcon());
		DEBUGLOG (other, "Checking icon again" );

	}
	DEBUGLOG (other, "Icon ok." );

	int y = borderOffset.y;
	wxPoint center(size.width/2,y + GetIcon().GetHeight()/2);
#ifdef DEBUG
	if (isDebugFlag(window_positions)) {
		wxRect r = this->GetScreenRect();
		wxPoint o = this->GetClientAreaOrigin();
		DEBUGLOG(window_positions,
			 ("Origin: (%d,%d), ScreenRect: +(%d,%d),%dx%d"),
			 o.x,
			 o.y,
			 r.x,
			 r.y,
			 r.width,
			 r.height);
	}
#endif


	wxGraphicsContext * gc = NULL;
	{
		wxGCDC * d = dynamic_cast<wxGCDC *>(&dc);
		if (d) gc = d->GetGraphicsContext();
	}
	if (!gc) {
		wxWindowDC * d = dynamic_cast<wxWindowDC *>(&dc);
		if (d) gc = wxGraphicsContext::Create(*d);
	}
	if (!gc) {
		wxMemoryDC * d = dynamic_cast<wxMemoryDC *>(&dc);
		if (d) gc = wxGraphicsContext::Create(*d);
	}
	if (!gc) {
		wxPrinterDC * d = dynamic_cast<wxPrinterDC *>(&dc);
		if (d) gc = wxGraphicsContext::Create(*d);
	}
	if (!gc) {
		gc = wxGraphicsContext::Create(this);
	}

	if (gc) {
		wxPen pen(*wxBLACK,2);
		gc->SetPen(pen);

		for (mutpointlist::iterator i = usedperimeterpoints.begin();
		     i != usedperimeterpoints.end();++i) {
			DrawPerimeterPoint(*gc,center, *i);
		}
		delete gc;
	}

	if (GetIcon().IsOk()) {
		int x = 0;
		DEBUGLOG (other, "Size: %dx%d" ,GetIcon().GetHeight(),
			 GetIcon().GetWidth());
		x = (size.width-GetIcon().GetWidth())/2;
#if __WXMAC__
		x -= maxBorderSize.x - borderOffset.x;
#endif
		dc.DrawIcon(GetIcon(), x, y);
	}


	DEBUGLOG (other, "Focus %p and this %p" ,(void*)this->FindFocus(),(void*)this);
}

template<typename T>
wxPoint MutIconShapeClass<T>::GetPerimeterPoint(const wxPoint &direction) const {
	wxRect iconRect = this->GetIconRect();
	DEBUGLOG (routinggui, "Icon rect: x=%d, y=%d, w=%d, h=%d" ,iconRect.x,iconRect.y,iconRect.width,iconRect.height);
	wxPoint iconCenter(iconRect.x+iconRect.width/2,
			   iconRect.y+iconRect.height/2);
	DEBUGLOG (routinggui, "center = (%d,%d)" , iconCenter.x, iconCenter.y);
	wxSize bordersize = (this->GetSize()-this->GetClientSize()).Scale(0.5,0.5);

	wxPoint upperLeft = - this->GetClientAreaOrigin() - bordersize;
	wxPoint lowerRight = upperLeft + this->GetSize();
	wxPoint dir2 = direction + this->GetClientSize()/2;
#if 0
	//	wxPoint inner = ScreenToClient(i); unused
	wxPoint myoffset = this->GetPositionInWindow(paintingWindow);
	wxPoint outer = o - myoffset;
	DEBUGLOG (routinggui, "outer (%d,%d) is in device (%d,%d)" ,o.x,o.y,outer.x,outer.y);
/*
	wxRect screenRect = this->GetScreenRect();
	// transform Screen rect to upper left and
	wxPoint upperLeft(this->ScreenToClient(wxPoint(screenRect.x,screenRect.y)));
	wxPoint lowerRight(this->ScreenToClient(wxPoint(screenRect.x+screenRect.width,screenRect.y+screenRect.height)));
*/
	wxRect screenRect = this->GetClientRect();
	wxPoint upperLeft(screenRect.x,screenRect.y);
	wxPoint lowerRight(screenRect.x+screenRect.width,screenRect.y+screenRect.height);
	DEBUGLOG (routinggui, "Rectangle: (%d,%d) -- (%d,%d)" ,upperLeft.x, upperLeft.y, lowerRight.x, lowerRight.y);
#endif

	wxPoint perimeterpoint(0,0);
	if (lowerRight.x <= dir2.x) {
		perimeterpoint.x = lowerRight.x;
		perimeterpoint.y = iconCenter.y;
	} else if (dir2.x <= upperLeft.x) {
		perimeterpoint.x = upperLeft.x;
		perimeterpoint.y = iconCenter.y;
	} else if (dir2.y <= upperLeft.y) {
		perimeterpoint.x = iconCenter.x;
		perimeterpoint.y = upperLeft.y;
	} else if (lowerRight.y <= dir2.y) {
		perimeterpoint.x = iconCenter.x;
		perimeterpoint.y = lowerRight.y;
	} else {
		/* inside our area */
		perimeterpoint = iconCenter;
	}

	mutpointlist::iterator pos = std::find(usedperimeterpoints.begin(),
					       usedperimeterpoints.end(),
					       perimeterpoint);
	if (pos == usedperimeterpoints.end())
		usedperimeterpoints.push_back(perimeterpoint);

	return perimeterpoint;


#if 0
	wxPoint retval = perimeterpoint + myoffset;

	DEBUGLOG (routinggui, "perimeter point (%d,%d), returning (%d,%d)" ,
		 perimeterpoint.x,perimeterpoint.y,retval.x,retval.y);

	return retval;
#endif

#if 0
	wxRect r = this->GetRect();
	DEBUGLOG (other, "Rect: (%d,%d) -- (%d,%d)" ,r.x,r.y,r.x+r.width,r.y+r.height);
	DEBUGLOG (other, "Points: i = (%d,%d), o = (%d, %d)" ,i.x,i.y,o.x,o.y);
	wxRect ir = this->GetIconRect();
#ifdef DEBUG
	std::cerr.flush();
	mutASSERT(r.Contains(i));
#endif

	wxPoint p;
	int xoffset = 0;
#if __WXMAC__ && 0
	xoffset = this->GetWindowBorderSize().x/2;
#endif

	r.y += borderOffset.y;
#if __WXMAC__
	r.y += maxBorderSize.y - borderOffset.y;
#endif
	if (r.x+r.width <= o.x) {
		p.x = r.x + r.width + xoffset;
		p.y = ir.y + ir.height/2;
	} else if (r.x >= o.x) {
		p.x = r.x - xoffset;
		p.y = ir.y + ir.height/2;
	} else if (r.y <= o.y) {
		p.x = r.x + r.width/2;
		p.y = r.y;
	} else if (r.y + r.height >= o.y) {
		p.x = r.x + r.width/2;
		p.y = r.y + r.height;
	} else p = o;


	mutpointlist::iterator pos = std::find(usedperimeterpoints.begin(),
					       usedperimeterpoints.end(),
					       p);
	if (pos == usedperimeterpoints.end())
		usedperimeterpoints.push_back(p);

#if __WXGTK__ && 0
	p.y += maxBorderSize.y - this->GetWindowBorderSize().y / 2;
#endif
	return p;
#endif
}

template<typename T>
void MutIconShapeClass<T>::DrawPerimeterPoint(wxGraphicsContext & gc,
					      const wxPoint & center,
					      wxPoint p) const
{
	DEBUGLOG(window_positions,"DrawPerimeterPoint (%d,%d)",p.x,p.y);
	wxGraphicsPath path = gc.CreatePath();
	path.MoveToPoint(center);
	path.AddLineToPoint(p);
	gc.StrokePath(path);
  }



template<typename T>
wxPoint MutIconShapeClass<T>::GetPositionInWindow(const wxWindow * win) const {
	wxPoint p(0,0);
	const wxWindow * tmp = this;
	DEBUGLOG(window_positions,
		 ("============================================"));
	while (tmp && tmp != win) {
#if 0
		p += tmp->GetClientAreaOrigin();
		wxSize border = (tmp->GetSize() - tmp->GetClientSize());
		p += border.Scale(0.5,0.5);
#endif
		p += tmp->GetPosition();
		p += tmp->ClientToWindowSize(wxSize(0,0)).Scale(0.5,0.5);


#ifdef DEBUG
		if (isDebugFlag(window_positions)) {
			wxRect r = tmp->GetScreenRect();
			wxPoint o = tmp->GetClientAreaOrigin();
			wxSize b = tmp->GetWindowBorderSize();
			DEBUGLOG(window_positions,
				 ("Origin: (%d,%d), p: (%d,%d), border: (%d,%d)"),
				 o.x,
				 o.y,
				 p.x,
				 p.y,
				 b.GetWidth(),
				 b.GetHeight());
			DEBUGLOG(window_positions,
				 "Screen Rect: +(%d,%d),%dx%d",
				 r.x,
				 r.y,
				 r.width,
				 r.height);
			r = tmp->GetClientRect();
			DEBUGLOG(window_positions,
				 "Client Rect: +(%d,%d),%dx%d",
				 r.x,
				 r.y,
				 r.width,
				 r.height);
			r = tmp->GetRect();
			DEBUGLOG(window_positions,
				 "Window Rect: +(%d,%d),%dx%d",
				 r.x,
				 r.y,
				 r.width,
				 r.height);
			b = tmp->ClientToWindowSize(wxSize(0,0));
			DEBUGLOG(window_positions,
				 "Delta Size: +(%d,%d)",
				 b.GetWidth(),
				 b.GetHeight());
		DEBUGLOG(window_positions,
				 ("--------------------------------------------"));
		}
#endif


		tmp = tmp->GetParent();
	}

#ifdef DEBUG
		if (isDebugFlag(window_positions)) {
			wxRect r = tmp->GetScreenRect();
			wxPoint o = tmp->GetClientAreaOrigin();
			wxSize b = tmp->GetWindowBorderSize();
			DEBUGLOG(window_positions,
				 ("Origin: (%d,%d), p: (%d,%d), border: (%d,%d)"),
				 o.x,
				 o.y,
				 p.x,
				 p.y,
				 b.GetWidth(),
				 b.GetHeight());
			DEBUGLOG(window_positions,
				 "Screen Rect: +(%d,%d),%dx%d",
				 r.x,
				 r.y,
				 r.width,
				 r.height);
			r = tmp->GetClientRect();
			DEBUGLOG(window_positions,
				 "Client Rect: +(%d,%d),%dx%d",
				 r.x,
				 r.y,
				 r.width,
				 r.height);
			r = tmp->GetRect();
			DEBUGLOG(window_positions,
				 "Window Rect: +(%d,%d),%dx%d",
				 r.x,
				 r.y,
				 r.width,
				 r.height);
			b = tmp->ClientToWindowSize(wxSize(0,0));
			DEBUGLOG(window_positions,
				 "Delta Size: +(%d,%d)",
				 b.GetWidth(),
				 b.GetHeight());
		DEBUGLOG(window_positions,
				 ("============================================"));
		}
#endif

	return tmp ? p:wxPoint(0,0);
}


template<typename T>
bool MutIconShapeClass<T>::Recompute()
{
	return true;
}

template<typename T>
bool MutIconShapeClass<T>::Layout() {
	ClearPerimeterPoints();
	wxRect rect = this->GetClientRect();
	int w = rect.width, h = rect.height,
		y = Icon.GetHeight() +	borderOffset.y;

	w -= 2* borderOffset.x;
	h -= 2* borderOffset.y;
	if (staticText) {
//		y+= Icon.GetHeight();
		staticText->Move(borderOffset.x,y);
		staticText->CentreOnParent(wxHORIZONTAL);
		wxSize s = staticText->GetSize();
		y += s.y;
	}
	// If there is a sizer, use it instead of the constraints
	if ( this->GetSizer() )
	{
		DEBUGLOG (other, "sizer" );
		wxRect sizerrect(borderOffset.x,y,w,h);
#if __WXMAC__   //adjust the sizer to the right size inside
		sizerrect=wxRect(0,y,rect.width,rect.height);
		sizerrect.x -= maxBorderSize.x - borderOffset.x;
//		sizerrect.width -= 2*sizerrect.x;
#endif
		this->GetSizer()->SetDimension( sizerrect.x,
						sizerrect.y,
						sizerrect.width,
						sizerrect.height );
		PRINTSIZER(this->GetSizer());
	}
#if 0 // \todo implement this if it is needed
// the constraints destroy the window placement
#if wxUSE_CONSTRAINTS
	else
	{
		DEBUGLOG (other, "constraints" );
		this->SatisfyConstraints(); // Find the right constraints values
		this->SetConstraintSizes(); // Recursively set the real window sizes
	}
#endif
#endif
	return true;
}

template<typename T>
void MutIconShapeClass<T>::DeleteSelf()
{
	this->Destroy();
	return;

#if 0
	// old mouse event proof implementation
	// has been used as long as we handled the event
	// inside the mouse event handler;
	Hide();
	wxCloseEvent event(wxEVT_CLOSE_WINDOW, m_windowId);
	event.SetEventObject(this);
	event.SetCanVeto(false);

	GetEventHandler()->AddPendingEvent(event);
#endif
}

template class MutIconShapeClass<wxControl>;
template class MutIconShapeClass<MutPanel>;


/*
 * \}
 */

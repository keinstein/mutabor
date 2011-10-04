// -*-C++ -*-

/** \file
********************************************************************
* Icon shape.
*
* $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/muwx/IconShape.cpp,v 1.13 2011/10/04 20:09:16 keinstein Exp $
* \author Rüdiger Krauße <krausze@mail.berlios.de>,
* Tobias Schlemmer <keinstein@users.berlios.de>
* \date 1998
* $Date: 2011/10/04 20:09:16 $
* \version $Revision: 1.13 $
* \license GPL
*
* $Log: IconShape.cpp,v $
* Revision 1.13  2011/10/04 20:09:16  keinstein
* Clean up focus handling a little bit.
* Change perimeter point handling a little bit. Need at least one night to
* get overthought.
*
* Revision 1.12  2011-10-04 17:16:13  keinstein
* make program compile on Mac (wx 2.9) and fix some memory corruption
*
* Revision 1.11  2011-10-04 05:38:44  keinstein
* some configuration fixes
*
* Revision 1.10  2011-10-03 15:50:21  keinstein
* Fix focus issues in the route window. This includes:
*  * Using templates to describe the base class of MutIconShape.
*  * Rename MutIconShape->MutIconShapeClass.
*  * typedef MutIconShapeClass<wxControl> MutIconShape
*  * Expand the control container macros in MutPanel.
*  * Disable most of the control container behaviour as we don't need it, currently
*  * Focus NewInputDevice on window creation.
*  * MutBoxChannelShape focuses its parent on focus (which can be done only by mouse so far).
*  * Display focused Window with sunken border
*
* Revision 1.9  2011-09-30 18:07:04  keinstein
* * make compile on windows
* * s/wxASSERT/mutASSERT/g to get assert handler completely removed
* * add ax_boost_base for boost detection
*
* Revision 1.8  2011-09-30 09:10:24  keinstein
* Further improvements in the routing system.
*
* Revision 1.7  2011-09-29 05:26:58  keinstein
* debug intrusive_ptr
* fix storage and retrieving of input/output devices in treestorage
* save maximum border size in icons
* Apply the calculated offset in IconShape (box and box channels still missing)
* Fix debug saving and restoring route information/route window on activation
* Add wxWANTS_CHARS to MutEditWindow
*
* Revision 1.6  2011-09-27 20:13:22  keinstein
* * Reworked route editing backend
* * rewireing is done by RouteClass/GUIRoute now
* * other classes forward most requests to this pair
* * many bugfixes
* * Version change: We are reaching beta phase now
*
* Revision 1.5  2011-08-24 21:19:36  keinstein
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
#include "IconShape.h"
#include "wx/defs.h"
#include "wx/sizer.h"
#include "wx/dc.h"
#include "wx/dcclient.h"
#include <algorithm>
//#include "MutApp.h"
//#include "MutIcon.h"
//#include "MutRouteWnd.h"
//#include "InputDevDlg.h"
//#include "Device.h"

/** wx >= 2.9.0 uses its own template support
    \todo Check out how wxWidgets 2.9 supports templates */


#if wxCHECK_VERSION(2,9,0) 
#warning Check out how to use templates with IMPLEMENT_DYNAMIC_CLASS
#warning Check out how to use templates with BEGIN_EVENT_TABLE

#elif wxCHECK_VERSION(2,8,10)
// Checked version is 2.8.10
#else 
#warning Your wxWidgets version may be too old template support. Expect compiler errros.
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


IMPLEMENT_DYNAMIC_CLASS_TEMPLATE1(MutIconShapeClass, wxControl, wxControl);
IMPLEMENT_DYNAMIC_CLASS_TEMPLATE1(MutIconShapeClass, MutPanel, MutPanel);
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
bool MutIconShapeClass<T>::Create (wxWindow * parent, wxWindowID id)
{
	DEBUGLOG (other,_T (""));
	//    Enable(true);
	//		  SetBackgroundColour(BoxColor(GetId()));
	Icon = GetMutIcon(); // this must be before create
	mutASSERT(Icon.IsOk());
	if (!parenttype::Create(parent,
			      id,
			      wxDefaultPosition,
			      wxDefaultSize,
			      wxBORDER_RAISED | wxTAB_TRAVERSAL)) return false;

	maxBorderSize = this->GetWindowBorderSize();
	this->SetWindowStyle(
		(this->GetWindowStyle() & ~ wxBORDER_MASK)| wxBORDER_SUNKEN);
	wxSize tmpBorderSize = this->GetWindowBorderSize();
	maxBorderSize.IncTo(tmpBorderSize);

	this->SetWindowStyle(
		(this->GetWindowStyle() & ~ wxBORDER_MASK)| wxBORDER_NONE);
	tmpBorderSize = this->GetWindowBorderSize();
	maxBorderSize.IncTo(tmpBorderSize);
	maxBorderSize.IncTo(wxSize(0,0));
	maxBorderSize.IncBy(wxSize(1,1));
//	borderOffset = maxBorderSize - tmpBorderSize;
	borderOffset = maxBorderSize;
	return true;
}



template<typename T>
wxSize MutIconShapeClass<T>::DoGetBestSize() const 
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

	if (this->GetSizer()) {
		s1 = this->GetSizer()->CalcMin();
		DEBUGLOG (other, _T("our %p sizer best size: %dx%d"),this,s1.x,s1.y);
		s.x = std::max(s.x,s1.x);
		s.y += std::max(s1.y,0);
	}
#ifdef DEBUG
	s1 = this->GetSize() - this->GetClientSize();
	s1.IncTo(wxSize(0,0));

	DEBUGLOG(gui,_T("s1: (%d,%d), maxBorderSize: (%d,%d)"),
		 s1.x,s1.y,2*maxBorderSize.x,2*maxBorderSize.y);
	mutASSERT(!maxBorderSize.x || s1.x <= 2*maxBorderSize.x);
	mutASSERT(!maxBorderSize.y || s1.y <= 2*maxBorderSize.y);
#endif

	s += maxBorderSize + maxBorderSize;
	
	// s1 = MutPanel::DoGetBestSize();
        // call to base class not needed.
	DEBUGLOG (other, _T("our %p parent best size: %dx%d"),this,s1.x,s1.y);
	
	s1.IncTo(s);

	DEBUGLOG (other, _T("our %p best size: %dx%d"),this,s.x,s.y);
	wxConstCast(this,MutIconShapeClass<T>)->SetMinSize(s1);
	this->CacheBestSize(s1);
	return s1;
}


template<typename T>
  void MutIconShapeClass<T>::UpdateBorder (long flag) {
	this->SetWindowStyle((this->GetWindowStyle() & ~(long)wxBORDER_MASK)|flag);
//	borderOffset = maxBorderSize - GetWindowBorderSize();
	borderOffset = maxBorderSize;
//	wxSizer * sizer = GetContainingSizer();

//	this->GetParent()->Layout();
//	this->GetParent()->InvalidateBestSize();
	this->Layout();
	this->InvalidateBestSize();

	wxSizer * sizer = this->GetSizer();
	if (sizer) 
		sizer->SetSizeHints(this);
	this->Fit();

	wxPoint pos = this->GetPosition();
	pos -= maxBorderSize;
	wxSize size = this->GetSize();
	size += maxBorderSize + maxBorderSize;
	this->GetParent()->RefreshRect(wxRect(pos.x,pos.y,size.x,size.y));
//	this->GetParent()->Update();
}

template<typename T>
void MutIconShapeClass<T>::GotFocus() {
#ifdef DEBUG
	DEBUGLOG (other, _T("Current focus is at"));
	wxWindow * focuswin =wxWindow::FindFocus();
	if (focuswin) {
		DEBUGLOGTYPE (other,
			      (*(focuswin)),
			      _T(" focus has objet %p"),
			      wxWindow::FindFocus());
	} else
		DEBUGLOG(other,_T("NULL pointer"));
#endif
/*
	parenttype::SetFocus();
#ifdef DEBUG
	DEBUGLOG (other, _T("Current focus is at"));
	focuswin =wxWindow::FindFocus();
	if (focuswin) {
		DEBUGLOGTYPE (other,
			      (*(focuswin)),
			      _T(" focus has objet %p"),
			      wxWindow::FindFocus());
	} else
		DEBUGLOG(other,_T("NULL pointer"));
#endif
*/
	UpdateBorder(wxBORDER_SUNKEN);
}



template<typename T>
void MutIconShapeClass<T>::LostFocus()
{
	DEBUGLOG (other, _T(""));
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
void MutIconShapeClass<T>::OnPaint( wxPaintEvent& WXUNUSED(event) )
{
	wxPaintDC dc(this);
	this->PrepareDC(dc);
	this->OnDraw(dc);
}

template<typename T>
void MutIconShapeClass<T>::OnDraw (wxDC & dc) 
{
	wxRect size = this->GetRect();
	DEBUGLOG (other, _T("Checking icon"));

	if (!GetIcon().IsOk()) {
		SetIcon(GetMutIcon());
		DEBUGLOG (other, _T("Checking icon again"));

	}
	DEBUGLOG (other, _T("Icon ok."));

	int x = 0, y = borderOffset.y;
	if (GetIcon().IsOk()) {
		DEBUGLOG (other, _T("Size: %dx%d"),GetIcon().GetHeight(),
			 GetIcon().GetWidth());
		x = (size.width-GetIcon().GetWidth())/2;
		dc.DrawIcon(GetIcon(), x, y);
	}

	wxPoint center(size.width/2,y + GetIcon().GetHeight()/2);
	wxPoint origin(size.x,size.y);
	for (mutpointlist::iterator i = usedperimeterpoints.begin();
	     i != usedperimeterpoints.end();i++) {
		dc.DrawLine(center, *i-origin);
	}

	DEBUGLOG (other, _T("Focus %p and this %p"),this->FindFocus(),this);
/*  Draw a black bock around focused item 
	if (FindFocus() == this) {
		DEBUGLOG (other, _T("Painting Box"));
		dc.SetPen(*wxBLACK_PEN);
		dc.SetBrush(*wxTRANSPARENT_BRUSH);
		dc.DrawRectangle(0,0,size.width,size.height);
	}
*/
}

template<typename T>
wxPoint MutIconShapeClass<T>::GetPerimeterPoint(const wxPoint &i,const wxPoint &o) const {
	wxRect r = this->GetRect();
	DEBUGLOG (other, _T("Rect: (%d,%d) -- (%d,%d)"),r.x,r.y,r.x+r.width,r.y+r.height);
	DEBUGLOG (other, _T("Points: i = (%d,%d), o = (%d, %d)"),i.x,i.y,o.x,o.y);
	wxRect ir = this->GetIconRect();
#ifdef DEBUG
	std::cerr.flush();
	mutASSERT(r.Contains(i));
#endif

	wxPoint p;

	r.y += borderOffset.y;
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


	mutpointlist::iterator pos = std::find(usedperimeterpoints.begin(),
					       usedperimeterpoints.end(),
					       p);
	if (pos == usedperimeterpoints.end())
		usedperimeterpoints.push_back(p);

#ifdef __WXGTK__
	p.y += maxBorderSize.y - this->GetWindowBorderSize().y;
#endif

	return p;
}

template<typename T>
void MutIconShapeClass<T>::LineTo(wxDC &dc, const wxPoint & p,
	const wxRect & screenpos)  const
{
	wxRect rect = this->GetRect();
	wxPoint p1(rect.x + rect.width/2, 
		   rect.y + Icon.GetHeight()/2 + borderOffset.y);
	wxPoint origin(screenpos.x,screenpos.y);
	dc.DrawLine(p1+origin,p+origin);
}


template<typename T>
bool MutIconShapeClass<T>::Recompute() 
{
	return true;
}

template<typename T>
bool MutIconShapeClass<T>::Layout() {
	int w = 0, h = 0, y = Icon.GetHeight() + borderOffset.y;
	this->GetVirtualSize(&w, &h);
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
		DEBUGLOG (other, _T("sizer"));
		this->GetSizer()->SetDimension( borderOffset.x, y, w, h );
		PRINTSIZER(this->GetSizer());
	}
#if 0 // \todo implement this if it is needed
// the constraints destroy the window placement
#if wxUSE_CONSTRAINTS
	else
	{
		DEBUGLOG (other, _T("constraints"));
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

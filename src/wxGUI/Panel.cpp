/** \file 
 ********************************************************************
 * Mutabor Panel. Panel based on wxControl and wxPanel
 * Most code comes from wxPanel and has been rewritten in order to 
 * be a subclass of wxControl.
 *
 * Note: License change towards (L)GPL is explicitly allowed for wxWindows license.
 *
 * $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/src/wxGUI/Panel.cpp,v 1.11 2011/11/16 14:07:03 keinstein Exp $
 * Copyright:   (c) 2008 TU Dresden
 * \author Julian Smart,  Tobias Schlemmer <keinstein@users.berlios.de>
 * \date 
 * $Date: 2011/11/16 14:07:03 $
 * \version $Revision: 1.11 $
 * \license GPL
 *
 * $Log: Panel.cpp,v $
 * Revision 1.11  2011/11/16 14:07:03  keinstein
 * passed make distcheck on linux
 * addedd some osdep files to the archive
 *
 * Revision 1.10  2011-11-02 14:31:59  keinstein
 * fix some errors crashing Mutabor on Windows
 *
 * Revision 1.9  2011-10-22 16:32:39  keinstein
 * commit to continue debugging on Linux/wine
 *
 * Revision 1.8  2011-10-03 20:34:05  keinstein
 * fix compiling with wx 2.9
 *
 * Revision 1.7  2011-10-03 15:50:21  keinstein
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
 * Revision 1.6  2011-09-30 09:10:25  keinstein
 * Further improvements in the routing system.
 *
 * Revision 1.5  2011-09-29 05:26:59  keinstein
 * debug intrusive_ptr
 * fix storage and retrieving of input/output devices in treestorage
 * save maximum border size in icons
 * Apply the calculated offset in IconShape (box and box channels still missing)
 * Fix debug saving and restoring route information/route window on activation
 * Add wxWANTS_CHARS to MutEditWindow
 *
 * Revision 1.4  2011-09-27 20:13:24  keinstein
 * * Reworked route editing backend
 * * rewireing is done by RouteClass/GUIRoute now
 * * other classes forward most requests to this pair
 * * many bugfixes
 * * Version change: We are reaching beta phase now
 *
 * Revision 1.3  2011-02-20 22:35:58  keinstein
 * updated license information; some file headers have to be revised, though
 *
 *
 *
 ********************************************************************
 * \addtogroup src/wxGUI
 * \{
 ********************************************************************/

// ============================================================================
// declarations
// ============================================================================

// ----------------------------------------------------------------------------
// headers
// ----------------------------------------------------------------------------


#include "src/wxGUI/Panel.h"
#include "wx/object.h"
#include "wx/font.h"
#include "wx/colour.h"
#include "wx/settings.h"
#include "wx/log.h"
#include "wx/panel.h"
#include "wx/containr.h"
#include "wx/sizer.h"

#ifdef __BORLANDC__
    #pragma hdrstop
#endif

// ----------------------------------------------------------------------------
// wxWin macros
// ----------------------------------------------------------------------------

#if wxUSE_EXTENDED_RTTI
WX_DEFINE_FLAGS( MutPanelStyle )

wxBEGIN_FLAGS( MutPanelStyle )
    // new style border flags, we put them first to
    // use them for streaming out
    wxFLAGS_MEMBER(wxBORDER_SIMPLE)
    wxFLAGS_MEMBER(wxBORDER_SUNKEN)
    wxFLAGS_MEMBER(wxBORDER_DOUBLE)
    wxFLAGS_MEMBER(wxBORDER_RAISED)
    wxFLAGS_MEMBER(wxBORDER_STATIC)
    wxFLAGS_MEMBER(wxBORDER_NONE)

    // old style border flags
    wxFLAGS_MEMBER(wxSIMPLE_BORDER)
    wxFLAGS_MEMBER(wxSUNKEN_BORDER)
    wxFLAGS_MEMBER(wxDOUBLE_BORDER)
    wxFLAGS_MEMBER(wxRAISED_BORDER)
    wxFLAGS_MEMBER(wxSTATIC_BORDER)
    wxFLAGS_MEMBER(wxBORDER)

    // standard window styles
    wxFLAGS_MEMBER(wxTAB_TRAVERSAL)
    wxFLAGS_MEMBER(wxCLIP_CHILDREN)
    wxFLAGS_MEMBER(wxTRANSPARENT_WINDOW)
    wxFLAGS_MEMBER(wxWANTS_CHARS)
    wxFLAGS_MEMBER(wxFULL_REPAINT_ON_RESIZE)
    wxFLAGS_MEMBER(wxALWAYS_SHOW_SB )
    wxFLAGS_MEMBER(wxVSCROLL)
    wxFLAGS_MEMBER(wxHSCROLL)

wxEND_FLAGS( MutPanelStyle )

IMPLEMENT_DYNAMIC_CLASS_XTI(MutPanel, wxControl,"Panel.h")

wxBEGIN_PROPERTIES_TABLE(MutPanel)
    wxPROPERTY_FLAGS( WindowStyle , 
		      MutPanelStyle , long , 
		      SetWindowStyleFlag , GetWindowStyleFlag , 
		      EMPTY_MACROVALUE, 0 /*flags*/ , 
		      wxT("Helpstring") , wxT("group")) // style
// style wxTAB_TRAVERSAL
wxEND_PROPERTIES_TABLE()

wxBEGIN_HANDLERS_TABLE(MutPanel)
wxEND_HANDLERS_TABLE()

wxCONSTRUCTOR_5( MutPanel , 
		 wxWindow* , 
		 Parent , 
		 wxWindowID , 
		 Id , 
		 wxPoint , 
		 Position , 
		 wxSize , Size , 
		 long , 
		 WindowStyle )

#else
IMPLEMENT_DYNAMIC_CLASS(MutPanel, wxControl)
#endif

BEGIN_EVENT_TABLE(MutPanel, wxControl)
    EVT_SIZE(MutPanel::OnSize)

//    WX_EVENT_TABLE_CONTROL_CONTAINER(MutPanel)
EVT_SET_FOCUS(MutPanel::OnFocus) 
EVT_CHILD_FOCUS(MutPanel::OnChildFocus) 

// Currently we do not need to traverse each client separately
// so we disable this, here:
// EVT_NAVIGATION_KEY(MutPanel::OnNavigationKey)
END_EVENT_TABLE()

// ============================================================================
// implementation
// ============================================================================

//WX_DELEGATE_TO_CONTROL_CONTAINER(MutPanel, wxControl)

void MutPanel::OnNavigationKey( wxNavigationKeyEvent& event ) 
{ 
	mutUnused(event);
// (works on wx2.8.10)	m_container.HandleOnNavigationKey(event); 
} 

void MutPanel::RemoveChild(wxWindowBase *child) { 
//	m_container.HandleOnWindowDestroy(child); 
	wxControl::RemoveChild(child); 
} 

void MutPanel::SetFocus() { 
	wxControl::SetFocus();
//	if ( !m_container.DoSetFocus() ) wxControl::SetFocus(); 
} 
void MutPanel::SetFocusIgnoringChildren() { 
	wxControl::SetFocus(); 
} 
void MutPanel::OnChildFocus(wxChildFocusEvent& event) {
	mutUnused(event);
	wxFocusEvent ev;
	wxPostEvent(this,ev);
//	m_container.SetLastFocus(event.GetWindow()); 
//	event.Skip(); 
} 

void MutPanel::OnFocus(wxFocusEvent& event) { 
	//	SetFocus();
	event.Skip();
	return;
//	m_container.HandleOnFocus(event); 
} 
bool MutPanel::AcceptsFocus() const { 
	return IsEnabled() && IsShown();
//	return m_container.AcceptsFocus(); 
}



// ----------------------------------------------------------------------------
// wxPanel creation
// ----------------------------------------------------------------------------

void MutPanel::Init()
{
    m_container.SetContainerWindow(this);
}

bool MutPanel::Create(wxWindow *parent,
		      wxWindowID winid,
		      const wxPoint& pos,
		      const wxSize& size,
		      long style,
		      const wxValidator& validator,
		      const wxString& name)
{
	if (!wxControl::Create( parent, winid, pos, size, style, validator, name))
		return false;
	
	// so we don't have too much problems with background style settings.
	SetBackgroundStyle(wxBG_STYLE_SYSTEM);
	    
	// so that non-solid background renders correctly under GTK+:
	SetThemeEnabled(true);

#if defined(__WXWINCE__) && (defined(__POCKETPC__) || defined(__SMARTPHONE__))
	// Required to get solid control backgrounds under WinCE
	SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_WINDOW));
#endif

// wxGTK
	SetBackgroundStyle(wxBG_STYLE_COLOUR);
	SetBackgroundColour(wxNullColour);

	return true;
}

MutPanel::~MutPanel()
{
}

bool MutPanel::Destroy() 
{
	Hide();
	wxSizer * sizer = GetContainingSizer();
	if (sizer) {
		sizer->Detach(this);
		SetSizer(NULL);
	}

	wxWindow * parent = GetParent();
	if (parent) {
		parent->RemoveChild(this);
	}

	if ( !wxPendingDelete.Member(this) )
        wxPendingDelete.Append(this);
	
	return true;
}


void MutPanel::InitDialog()
{
	wxInitDialogEvent event(GetId());
	event.SetEventObject(this);
	GetEventHandler()->ProcessEvent(event);
}

// ----------------------------------------------------------------------------
// event handlers
// ----------------------------------------------------------------------------

void MutPanel::OnSize(wxSizeEvent& event)
{
    if (GetAutoLayout())
        Layout();
#if wxUSE_CONSTRAINTS
#if defined(__WXPM__) && 0
    else
    {
        // Need to properly move child windows under OS/2

        PSWP                        pWinSwp = GetSwp();

        if (pWinSwp->cx == 0 && pWinSwp->cy == 0 && pWinSwp->fl == 0)
        {
            // Uninitialized

            ::WinQueryWindowPos(GetHWND(), pWinSwp);
        }
        else
        {
            SWP                     vSwp;
            int                     nYDiff;

            ::WinQueryWindowPos(GetHWND(), &vSwp);
            nYDiff = pWinSwp->cy - vSwp.cy;
            MoveChildren(nYDiff);
            pWinSwp->cx = vSwp.cx;
            pWinSwp->cy = vSwp.cy;
        }
    }
#endif
#endif // wxUSE_CONSTRAINTS

    event.Skip();
}


///\}

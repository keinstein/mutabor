/** \file 
 ********************************************************************
 * Mutabor Panel. Panel based on wxControl and wxPanel
 * Most code comes from wxPanel and has been rewritten in order to 
 * be a subclass of wxControl.
 *
 * Note: License change towards (L)GPL is explicitly allowed for wxWindows license.
 *
 * Copyright:   (c) 2008 TU Dresden
 * \author Julian Smart,  Tobias Schlemmer <keinstein@users.sourceforge.net>
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
 * \addtogroup GUI
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
#if wxCHECK_VERSION(2,9,0)
	SetBackgroundStyle(wxBG_STYLE_SYSTEM);
#else
	SetBackgroundStyle(wxBG_STYLE_COLOUR);
#endif
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

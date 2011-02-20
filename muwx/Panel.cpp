/** \file 
 ********************************************************************
 * Mutabor Panel. Panel based on wxControl and wxPanel
 * Most code comes from wxPanel and has been rewritten in order to 
 * be a subclass of wxControl.
 *
 * Note: License change towards (L)GPL is explicitly allowed for wxWindows license.
 *
 * $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/muwx/Panel.cpp,v 1.3 2011/02/20 22:35:58 keinstein Exp $
 * Copyright:   (c) 2008 TU Dresden
 * \author Julian Smart,  Tobias Schlemmer <keinstein@users.berlios.de>
 * \date 
 * $Date: 2011/02/20 22:35:58 $
 * \version $Revision: 1.3 $
 * \license GPL
 *
 * $Log: Panel.cpp,v $
 * Revision 1.3  2011/02/20 22:35:58  keinstein
 * updated license information; some file headers have to be revised, though
 *
 *
 *
 ********************************************************************
 * \addtogroup muwx
 * \{
 ********************************************************************/

// ============================================================================
// declarations
// ============================================================================

// ----------------------------------------------------------------------------
// headers
// ----------------------------------------------------------------------------

// For compilers that support precompilation, includes "wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
    #pragma hdrstop
#endif

#ifndef WX_PRECOMP
    #include "wx/object.h"
    #include "wx/font.h"
    #include "wx/colour.h"
    #include "wx/settings.h"
    #include "wx/log.h"
    #include "wx/panel.h"
    #include "wx/containr.h"
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
    wxPROPERTY_FLAGS( WindowStyle , MutPanelStyle , long , SetWindowStyleFlag , GetWindowStyleFlag , EMPTY_MACROVALUE, 0 /*flags*/ , wxT("Helpstring") , wxT("group")) // style
// style wxTAB_TRAVERSAL
wxEND_PROPERTIES_TABLE()

wxBEGIN_HANDLERS_TABLE(MutPanel)
wxEND_HANDLERS_TABLE()

wxCONSTRUCTOR_5( MutPanel , wxWindow* , Parent , wxWindowID , Id , wxPoint , Position , wxSize , Size , long , WindowStyle )

#else
IMPLEMENT_DYNAMIC_CLASS(MutPanel, wxControl)
#endif

BEGIN_EVENT_TABLE(MutPanel, wxControl)
    EVT_SIZE(MutPanel::OnSize)

    WX_EVENT_TABLE_CONTROL_CONTAINER(MutPanel)
END_EVENT_TABLE()

// ============================================================================
// implementation
// ============================================================================

WX_DELEGATE_TO_CONTROL_CONTAINER(MutPanel, wxControl)

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

	return true;
}

MutPanel::~MutPanel()
{
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

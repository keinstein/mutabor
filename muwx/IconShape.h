// -*- C++ -*-

/** \file
 ********************************************************************
 * Icon shape.
 *
 * $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/muwx/IconShape.h,v 1.9 2011/10/04 05:38:44 keinstein Exp $
 * \author Rüdiger Krauße <krausze@mail.berlios.de>,
 * Tobias Schlemmer <keinstein@users.berlios.de>
 * \date 1998
 * $Date: 2011/10/04 05:38:44 $
 * \version $Revision: 1.9 $
 * \license GPL
 *
 * $Log: IconShape.h,v $
 * Revision 1.9  2011/10/04 05:38:44  keinstein
 * some configuration fixes
 *
 * Revision 1.8  2011-10-03 15:50:21  keinstein
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
 * Revision 1.7  2011-09-30 18:07:04  keinstein
 * * make compile on windows
 * * s/wxASSERT/mutASSERT/g to get assert handler completely removed
 * * add ax_boost_base for boost detection
 *
 * Revision 1.6  2011-09-29 05:26:58  keinstein
 * debug intrusive_ptr
 * fix storage and retrieving of input/output devices in treestorage
 * save maximum border size in icons
 * Apply the calculated offset in IconShape (box and box channels still missing)
 * Fix debug saving and restoring route information/route window on activation
 * Add wxWANTS_CHARS to MutEditWindow
 *
 * Revision 1.5  2011-09-27 20:13:22  keinstein
 * * Reworked route editing backend
 * * rewireing is done by RouteClass/GUIRoute now
 * * other classes forward most requests to this pair
 * * many bugfixes
 * * Version change: We are reaching beta phase now
 *
 * Revision 1.4  2011-02-20 22:35:57  keinstein
 * updated license information; some file headers have to be revised, though
 *
 * Revision 1.3  2010-12-13 00:27:53  keinstein
 * compiles in linux as well as in mingw
 *
 * Revision 1.2  2010-11-21 13:15:47  keinstein
 * merged experimental_tobias
 *
 * Revision 1.1.2.3  2010-03-30 08:38:27  keinstein
 * added rudimentary command line support
 * changed debug system to allow selection of messages via command line
 * further enhancements to the route dialogs
 *
 * Revision 1.1.2.2  2010/02/15 12:08:20  keinstein
 * intermediate update for backup progress
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

#if (!defined(MUWX_ICONSHAPE_H) && !defined(PRECOMPILE)) \
	|| (!defined(MUWX_ICONSHAPE_H_PRECOMPILED))
#ifndef PRECOMPILE
#define MUWX_ICONSHAPE_H
#endif

// ---------------------------------------------------------------------------
// headers
// ---------------------------------------------------------------------------

#include "Defs.h"
#include "Panel.h"
#include "MutIcon.h"
//#include "Device.h"

#ifndef MUWX_ICONSHAPE_H_PRECOMPILED
#define MUWX_ICONSHAPE_H_PRECOMPILED



//#include <map>

#include "wx/defs.h"
#include "wx/icon.h"
#include "wx/stattext.h"


/// An icon control with static text
template<class T = wxControl>
class MutIconShapeClass:public T
{
public: typedef T parenttype;
protected:
        /// the icon
        MutIcon Icon;
	wxStaticText * staticText;
	wxSize maxBorderSize, borderOffset;
	mutable mutpointlist usedperimeterpoints;

public:
	
	MutIconShapeClass():parenttype(),Icon(),staticText(NULL) { }

	MutIconShapeClass(wxWindow * parent, wxWindowID id):parenttype(),
								  Icon(),
								  staticText(NULL)
	{
		Create(parent, id);
	}
	
	bool Create (wxWindow * parent, wxWindowID id = wxID_ANY);
	
	virtual ~MutIconShapeClass() {}
	

	void SetIcon(const MutIcon & icon) {
		Icon = icon;
	}

	const MutIcon & GetIcon () const {
		return Icon;
	}

	void SetLabel(const wxString & st ) {
		if (!staticText) 
			staticText = new wxStaticText(this,wxID_ANY,_T(""));
		mutASSERT(staticText);
		if (!staticText) return;
		wxControl::SetLabel(st); // stores only a string and invalidates
		// the best size
		staticText->SetLabel(st);
	}
	/// Calculates the Icon to be used.
	virtual MutIcon & GetMutIcon ()  { return MutNullIcon; }
  
	virtual wxSize DoGetBestSize() const;

	virtual void UpdateBorder(long flag);
	virtual void SetFocus() ;
	virtual void KillFocus() ;
        // calls layout for layout constraints and sizers
	void OnSize(wxSizeEvent& event);
	void OnGetFocus(wxFocusEvent & event) ;
	void OnKillFocus(wxFocusEvent & event); 
	
	void OnMouseClick(wxMouseEvent & event);

	void         OnPaint (wxPaintEvent &event ) ;
	virtual void OnDraw (wxDC & dc);
	virtual wxPoint GetPerimeterPoint( const wxPoint &i,
					   const wxPoint &o ) const;
	virtual wxRect GetIconRect() const 
	{
		wxRect r = static_cast<parenttype const *>(this)->GetRect();
		int iw = Icon.GetWidth();
		return wxRect(r.x + (r.width - iw)/2, 
			      r.y+borderOffset.y,
			      iw,
			      Icon.GetHeight());
	}
	
	virtual void LineTo (wxDC & dc , 
			     const wxPoint & p,
			     const wxRect & screenpos) const;
	virtual bool Recompute();
	
	virtual bool Layout();

	virtual bool AcceptsFocus() const {
		return this->IsShown() && this->IsEnabled();
	}

	//  virtual bool AcceptsFocus() const { return true; }
	void DeleteSelf() __attribute__ ((deprecated));
	void DeleteSelfEvent(wxCloseEvent & event) __attribute__((deprecated))
		{
		DEBUGLOG(other, _T("Destroying"));
		this->Destroy();
	}	

	void ClearPerimeterPoints() {
		usedperimeterpoints.clear();
	}
private:
	DECLARE_DYNAMIC_CLASS_NO_COPY(MutIconShapeClass)
	DECLARE_EVENT_TABLE() 
};

typedef MutIconShapeClass<wxControl> MutIconShape;


#endif				/* precompiled */
#endif				/* ICONSHAPE_H */
/*
 * \}
 */

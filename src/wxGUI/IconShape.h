// -*- C++ -*-
/** \file
 ********************************************************************
 * Icon shape.
 *
 * $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/src/wxGUI/IconShape.h,v 1.14 2011/11/04 15:02:03 keinstein Exp $
 * \author Rüdiger Krauße <krausze@mail.berlios.de>,
 * Tobias Schlemmer <keinstein@users.berlios.de>
 * \date 1998
 * $Date: 2011/11/04 15:02:03 $
 * \version $Revision: 1.14 $
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

#include "src/kernel/Defs.h"
#include "src/wxGUI/Panel.h"
#include "src/wxGUI/MutIcon.h"
//#include "Device.h"

#ifndef MUWX_ICONSHAPE_H_PRECOMPILED
#define MUWX_ICONSHAPE_H_PRECOMPILED



//#include <map>

#include "wx/defs.h"
#include "wx/icon.h"
#include "wx/stattext.h"


class NoTabStaticText:public wxStaticText {
public:
	NoTabStaticText(wxWindow * parent,
		wxWindowID id,
		const wxString & name):wxStaticText(parent,id,name) {}
	virtual ~NoTabStaticText() {}
	bool AcceptsFocusFromKeyboard() { return false; }
};

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
	
	virtual bool Destroy();

	void SetIcon(const MutIcon & icon) {
		Icon = icon;
	}

	const MutIcon & GetIcon () const {
		return Icon;
	}

	void SetLabel(const wxString & st ) {
		if (!staticText) 
			staticText = new NoTabStaticText(this,wxID_ANY,_T(""));
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
	virtual void LostFocus() ;
	virtual void GotFocus() ;
        // calls layout for layout constraints and sizers
	void OnSize(wxSizeEvent& event);
	void OnGetFocus(wxFocusEvent & event) ;
	void OnKillFocus(wxFocusEvent & event); 
	
	void OnMouseClick(wxMouseEvent & event);

	void         OnPaint (wxPaintEvent &event ) ;
	void OnMove(wxMoveEvent &event);
	virtual void OnDraw (wxDC & dc);
	virtual wxPoint GetPerimeterPoint( const wxPoint &i,
					   const wxPoint &o, 
					   wxWindow * paintingWindow ) const;
	virtual void DrawPerimeterPoint(wxDC & dc, 
					const wxPoint & center, 
					wxPoint p) const;
	virtual wxRect GetIconRect() const 
	{
		wxRect r = this->GetClientSize();
		int iw = Icon.GetWidth();

		r.x += maxBorderSize.x;
		r.y += maxBorderSize.y;

		return wxRect((r.width - iw)/2, 
			      0,
			      iw,
			      Icon.GetHeight());
	}

        /** 
	 * Tries to find the correct position of the window in a parent window.
	 * 
	 * \param win parent window.
	 * 
	 * \return position in win
	 */
	virtual wxPoint GetPositionInWindow(const wxWindow * win) const;

	virtual void LineTo (wxDC & dc , 
			     const wxPoint & p,
			     const wxRect & screenpos) const;
	virtual bool Recompute();
	
	virtual bool Layout();
	virtual void Fit() {
		this->SetSize(this->GetBestSize());
	}

	virtual bool AcceptsFocus() const {
		return this->IsShown() && this->IsEnabled();
	}

	//  virtual bool AcceptsFocus() const { return true; }
	void DeleteSelf() __attribute__ ((deprecated));
	void DeleteSelfEvent(wxCloseEvent & event) __attribute__((deprecated))
	{
		mutUnused(event);
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

// -*- C++ -*-

/** \file
 ********************************************************************
 * Icon shape.
 *
 * $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/muwx/IconShape.h,v 1.2 2010/11/21 13:15:47 keinstein Exp $
 * \author Rüdiger Krauße <krausze@mail.berlios.de>,
 * Tobias Schlemmer <keinstein@users.berlios.de>
 * \date 1998
 * $Date: 2010/11/21 13:15:47 $
 * \version $Revision: 1.2 $
 *
 * $Log: IconShape.h,v $
 * Revision 1.2  2010/11/21 13:15:47  keinstein
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

#ifndef ICONSHAPE_H
#define ICONSHAPE_H



//#include <map>

#include "wx/defs.h"
#include "wx/icon.h"
#include "wx/stattext.h"

#include "Panel.h"
#include "MutIcon.h"
//#include "Device.h"

/// An icon control with static text
class MutIconShape:public MutPanel
{
protected:
        /// the icon
        MutIcon Icon;
	wxStaticText * staticText;
	
public:
	
	MutIconShape():MutPanel(),Icon(),staticText(NULL) { }

	MutIconShape(wxWindow * parent, wxWindowID id):MutPanel(),
								  Icon(),
								  staticText(NULL)
	{
		Create(parent, id);
	}
	
	bool Create (wxWindow * parent, wxWindowID id = wxID_ANY);
	
	virtual ~MutIconShape() {}
	

	void SetIcon(const MutIcon & icon) {
		Icon = icon;
	}

	const MutIcon & GetIcon () const {
		return Icon;
	}

	void SetLabel(const wxString & st ) {
	  if (!staticText) staticText = new wxStaticText(this,wxID_ANY,_T(""));
	  wxASSERT(staticText);
	  if (!staticText) return;
	  wxControl::SetLabel(st);
	  staticText->SetLabel(m_label);
	}
	/// Calculates the Icon to be used.
	virtual MutIcon & GetMutIcon ()  { return MutNullIcon; }
  
	virtual wxSize DoGetBestSize() const;

	void OnGetFocus(wxFocusEvent & event) ;
	virtual void SetFocus() ;
	void OnKillFocus(wxFocusEvent & event); 

	void         OnPaint( wxPaintEvent &event ) ;
	virtual void OnDraw (wxDC & dc);
	virtual wxPoint GetPerimeterPoint(const wxPoint &i,
					  const wxPoint &o) const;
	virtual wxRect GetIconRect() const 
	{
		wxRect r = GetRect();
		int iw = Icon.GetWidth();
		return wxRect(r.x + (r.width - iw)/2, r.y,
			      iw,Icon.GetHeight());
	}
	
	virtual void LineTo(wxDC & dc , const wxPoint & p) const;
	virtual bool Recompute();
	
	virtual bool Layout();

	//  virtual bool AcceptsFocus() const { return true; }
	void DeleteSelf();
	void DeleteSelfEvent(wxCloseEvent & event) {
		DEBUGLOG(other, _T("Destroying"));
		Destroy();
	}	
private:
	DECLARE_DYNAMIC_CLASS_NO_COPY(MutIconShape)
	DECLARE_EVENT_TABLE() 
};



#endif				/* ICONSHAPE_H */
/*
 * \}
 */

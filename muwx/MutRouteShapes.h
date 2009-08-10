// -*- C++ -*-

/** \file
 ********************************************************************
 * Devices Basisklassen.
 *
 * $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/muwx/Attic/MutRouteShapes.h,v 1.2 2009/08/10 11:15:47 keinstein Exp $
 * \author Rüdiger Krauße <krausze@mail.berlios.de>,
 * Tobias Schlemmer <keinstein@users.berlios.de>
 * \date 1998
 * $Date: 2009/08/10 11:15:47 $
 * \version $Revision: 1.2 $
 *
 * $Log: MutRouteShapes.h,v $
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

#ifndef MUTROUTESHAPES_H
#define MUTROUTESHAPES_H

#include <map>

#include "wx/defs.h"
//#include "wx/ogl/ogl.h"
#include "wx/icon.h"
#include "wx/stattext.h"

#include "MutIcon.h"
#include "Device.h"

extern MutIcon NewInputDevBitmap;
extern MutIcon MidiInputDevBitmap;
extern MutIcon NewOutputDevBitmap;
extern MutIcon MidiOutputDevBitmap;
extern MutIcon MidiFileBitmap;
extern MutIcon BoxBitmap;
extern MutIcon NewBoxBitmap;
extern MutIcon ActiveChannelBitmap;
extern MutIcon PassiveChannelBitmap;
#ifdef __WXMAC__
extern MutIcon MutNullIcon; 
#else
#define MutNullIcon wxNullIcon;
#endif

class MutDeviceShape;
class MutBoxShape;

WX_DECLARE_LIST (MutDeviceShape, MutDeviceShapeList);
WX_DECLARE_LIST (MutBoxShape, MutBoxShapeList);


bool initMutIconShapes();
wxColor BoxColor(int nr);

/// An icon control with static text
class MutIconShape:public wxControl
{
protected:
        /// the icon
        MutIcon Icon;
	wxStaticText * staticText;
	
public:
	/// Calculates the Icon to be used.
	virtual MutIcon & GetMutIcon ()  { return MutNullIcon; }
	
	MutIconShape():wxControl(),Icon(),staticText(NULL) {}

	MutIconShape(wxWindow * parent, wxWindowID id = wxID_ANY):wxControl(),
								  Icon(),
								  staticText(NULL)
		{
			Create(parent, id);
		}
	
	bool Create (wxWindow * parent, wxWindowID id = wxID_ANY)
		{
			//    Enable(true);
			//		  SetBackgroundColour(BoxColor(GetId()));
			bool state = wxControl::Create(parent,id);
			if (state) {
				Icon = GetMutIcon();
				wxASSERT(Icon.IsOk());
				Layout();
			}
			return state;
		}
	
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
  
	virtual wxSize DoGetBestSize() const;
	virtual void DoSetSize(int x, int y,
			       int width, int height,
			       int sizeFlags = wxSIZE_AUTO);

	//  virtual void DoSetClientSize(int width, int height);
	
	void OnGetFocus(wxFocusEvent & event) ;
	void OnKillFocus(wxFocusEvent & event); 

	void         OnPaint( wxPaintEvent &event ) ;
	virtual void OnDraw (wxDC & dc);
	virtual wxPoint GetPerimeterPoint(const wxPoint i,
					  const wxPoint o) const;
	virtual wxRect GetIconRect() const 
		{
			wxRect r = GetRect();
			int iw = Icon.GetWidth();
			return wxRect(r.x + (r.width - iw)/2, r.y,
				      iw,Icon.GetHeight());
		}
	
	virtual void LineTo(wxDC & dc , wxPoint & p);
	virtual bool Recompute();
	
	virtual bool Layout();

	//  virtual bool AcceptsFocus() const { return true; }

private:
        DECLARE_DYNAMIC_CLASS(wxStaticBitmap)
	DECLARE_EVENT_TABLE() 
};

class MutDeviceShape:public MutIconShape
{
	//	wxFileName filename;
	class strptrless {
	public:
		bool operator () (wxString * a, wxString * b) {
			if (a == b) return true;
			if (a == NULL) return true;
			if (b == NULL) return false;
			return (*a <= *b);
		}
	};

public:

	typedef std::map<wxString *, MutDeviceShape *, strptrless> 
	stringmaptype;
	typedef stringmaptype::iterator stringmapiterator;
  
	MutDeviceShape():MutIconShape() 
		{
		}
	MutDeviceShape (wxWindow * parent, wxWindowID id, 
			const wxString & name = wxEmptyString):
		MutIconShape()
		{
			Create(parent, id, name);
		}

    
	bool Create (wxWindow * parent, wxWindowID id, 
		     const wxString & name = wxEmptyString)
		{
			bool state = MutIconShape::Create (parent,id);
			if (state) SetLabel(name);
			return state;
		}
	
	virtual bool Recompute();
	virtual Route * getRoutes() = 0;
	virtual void DoLeftDblClick() = 0;
	void LeftDblClickEvent (wxMouseEvent & event) {
		DoLeftDblClick();
	}

protected:
	void RemoveFromStringMap(stringmaptype & sm) {
		std::pair<stringmapiterator,stringmapiterator> 
			bounds = sm.equal_range(&m_label);
		for (stringmapiterator it = bounds.first; 
		     it != bounds.second; ++it) {
			if ((*it).second == this) {
				stringmapiterator it1 = it;
				it++;
				sm.erase(it1);
			}
		}
	}

	void InsertSelfToStringMap(stringmaptype & sm) {
		sm.insert(std::make_pair(&m_label,this)); 
	}

private:
  DECLARE_DYNAMIC_CLASS(MutIconShape);
  DECLARE_EVENT_TABLE();
};

class InputDevDlg;

class MutInputDeviceShape:public MutDeviceShape
{
protected: 
	InDevice *device;
	static stringmaptype stringmap;
	static wxSizerFlags sizerFlags;

public:

	MutInputDeviceShape():MutDeviceShape() {
		device = NULL;
	}

	MutInputDeviceShape (wxWindow * parent, wxWindowID id, const wxString &
	                     name):MutDeviceShape ()
	{
		device = NULL;
	}


	MutInputDeviceShape (wxWindow * parent, wxWindowID id, InDevice * d):
		MutDeviceShape() {
		Create (parent, id, d);
	}

	virtual ~MutInputDeviceShape();

	bool Create (wxWindow * parent, wxWindowID id, const wxString &
	                     name)
	{
	  device = NULL;
	  return MutDeviceShape::Create (parent, id, name);
	}

	bool Create (wxWindow * parent, wxWindowID id, InDevice * d);
	static MutInputDeviceShape * CreateShape(wxWindow * parent,
						 wxWindowID id,
						 InDevice * d);
	MutInputDeviceShape * CreateShape (InDevice * d) 
		{
			return CreateShape (m_parent, wxID_ANY,d);
		}

	static void SetSizerFlags (wxSizerFlags flags) {sizerFlags = flags; }

	void SetLabel(const wxString & st );

	MutIcon & GetMutIcon ()
	{
		return MidiInputDevBitmap;
	}

	Route * getRoutes()
	{
		if (!device) return NULL;
		return device->GetRoutes();
	}

	void SetDevice (InDevice * d) {
		wxASSERT (d);
		device = d;
		wxASSERT (device->getUserData());
		device -> setUserData (this);
	}
	
	InDevice * GetDevice() { return device; }

	virtual void DoLeftDblClick();
	InputDevDlg * ShowDeviceDialog();

protected: 
	virtual void InitializeDialog(InputDevDlg * in) { }
	virtual bool readDialog (InputDevDlg * in) { 
		wxASSERT (false);
		return false; 
	}
	virtual bool replaceSelfBy (MutInputDeviceShape  * newshape);
	virtual bool CanHandleType (DevType  type) { return false; }

private:
	DECLARE_DYNAMIC_CLASS(MutDeviceShape);
};

class MutNewInputDeviceShape:public MutInputDeviceShape
{

public:
	MutNewInputDeviceShape():MutInputDeviceShape() {}

	MutNewInputDeviceShape (wxWindow * parent, wxWindowID id):MutInputDeviceShape() 
		{
			Create(parent, id);
		}

	bool Create (wxWindow * parent, wxWindowID id)
		{
			return MutInputDeviceShape::Create (parent,id,_("New Input device"));
		}

	MutIcon & GetMutIcon ()
		{
			return NewInputDevBitmap;
		}

protected:
	virtual void InitializeDialog(InputDevDlg * in);
	virtual bool replaceSelfBy (MutInputDeviceShape  * newshape);

private:
	DECLARE_DYNAMIC_CLASS(MutInputDeviceShape);
};

class MutInputMidiFileDeviceShape:public MutInputDeviceShape
{
public:
	MutInputMidiFileDeviceShape():MutInputDeviceShape() {}
	MutInputMidiFileDeviceShape (wxWindow * parent,
				     wxWindowID id, 
				     InDevice * d):
		MutInputDeviceShape() {
		Create (parent,id,d);
	}
	bool Create (wxWindow * parent, wxWindowID id, InDevice * d)
		{
			return MutInputDeviceShape::Create(parent,id,d);
		}

	virtual MutIcon & GetMutIcon () 
		{
			DEBUGLOG(_T(""));
			return MidiFileBitmap;
		}
protected: 
	virtual void InitializeDialog(InputDevDlg * in);
	virtual bool readDialog (InputDevDlg * in);
	virtual bool CanHandleType (DevType  type) { return type == DTMidiFile; }


private:
	DECLARE_DYNAMIC_CLASS(MutInputMidiFileDeviceShape);

};

class MutInputMidiDeviceShape:public MutInputDeviceShape
{
public:
	MutInputMidiDeviceShape():MutInputDeviceShape() {}
	MutInputMidiDeviceShape (wxWindow * parent,
				     wxWindowID id, 
				     InDevice * d):
		MutInputDeviceShape() {
		Create (parent,id,d);
	}
	bool Create (wxWindow * parent, wxWindowID id, InDevice * d)
		{
			return MutInputDeviceShape::Create(parent,id,d);
		}

	virtual MutIcon & GetMutIcon () 
		{
			DEBUGLOG(_T(""));
			return MidiInputDevBitmap;
		}
protected: 
	virtual void InitializeDialog(InputDevDlg * in);
	virtual bool readDialog (InputDevDlg * in);
	virtual bool CanHandleType (DevType  type) { return type == DTMidiPort; }


private:
	DECLARE_DYNAMIC_CLASS(MutInputMidiDeviceShape);

};


class MutOutputDeviceShape:public MutDeviceShape
{
	OutDevice *device;

public:
	MutOutputDeviceShape():MutDeviceShape(),device(NULL) { }


	MutOutputDeviceShape (wxWindow * parent, wxWindowID id, 
			      const wxString & name) {
		Create (parent, id, name);
	}
	
	MutOutputDeviceShape (wxWindow * parent, wxWindowID id, OutDevice * d):
		MutDeviceShape() {
		Create (parent, id,  d);
	}

	virtual ~MutOutputDeviceShape() 
		{
			if (device) {
				wxASSERT (device -> getUserData() == this);
				device -> setUserData (NULL);
			}
		}


	bool Create (wxWindow * parent, wxWindowID id, 
		     const wxString & name)
		{
			device = NULL;
			return MutDeviceShape::Create (parent,id, name);
		}

	bool Create (wxWindow * parent, wxWindowID id, OutDevice * d);
	
	MutIcon & GetMutIcon ()
		{
			return MidiOutputDevBitmap;
		}
	
	Route * getRoutes()
		{
			return NULL;
		}

	OutDevice * GetDevice() 
		{
			return device;
		}

	void DoLeftDblClick();
};


class MutNewOutputDeviceShape:public MutOutputDeviceShape
{
	
public:
	MutNewOutputDeviceShape (wxWindow * parent, wxWindowID id):
		MutOutputDeviceShape() 
		{
			Create (parent,id);
		}


	bool Create (wxWindow * parent, 
		     wxWindowID id)
		{
			return MutOutputDeviceShape::Create (parent,
							     id,
							     _("New Output device"));
		}


	MutIcon & GetMutIcon ()
		{
			return NewOutputDevBitmap;
		}
};

class MutBoxShape;

class MutBoxChannelShape:public MutIconShape
{
	Route *route;
	MutInputDeviceShape * input;
	MutOutputDeviceShape * output;
	virtual MutIcon & GetMutIcon ();

public:

	MutBoxChannelShape (wxWindow * p = NULL, wxWindowID id = wxID_ANY, 
			    Route * r=NULL):MutIconShape() 
		{
			Create (p, id, r);
		}

	bool Create (wxWindow * p = NULL, wxWindowID id = wxID_ANY, 
		     Route * r=NULL)
		{ 
			route = r;
			if (!r) return false;
			r->setUserData (this);
			return MutIconShape::Create(p,id);
		}

	virtual ~MutBoxChannelShape()
		{
			if (route) {
				wxASSERT (route->getUserData() == this);
				route->setUserData (NULL);
			}
		}

	void SetInput(MutInputDeviceShape * device);
	void SetOutput(MutOutputDeviceShape * device);
	void AddPossibleOutput(MutOutputDeviceShape * device);
	virtual void DrawLines(wxDC & dc);

};

WX_DECLARE_LIST (MutBoxChannelShape, MutBoxChannelShapeList);

class MutBoxIconShape:public MutIconShape
{
public:
	MutBoxIconShape(wxWindow * parent = NULL, wxWindowID id = wxID_ANY):
		MutIconShape() 
		{
			Create (parent, id);
		}

	bool Create (wxWindow * parent = NULL, wxWindowID id = wxID_ANY)
		{
			return MutIconShape::Create(parent, id);
		}


	/*  bool Create( wxWindow *parent,
	    wxWindowID id,
	    const wxString &label,
	    const wxPoint &pos = wxDefaultPosition,
	    const wxSize &size = wxDefaultSize,
	    long style = 0,
	    const wxString &name = wxStaticBoxNameStr );
	*/

	void GetBordersForSizer(int &borderTop, int &borderOther) const;
 
	virtual void OnDraw (wxDC & dc);
	virtual bool Layout();

	MutIcon & GetMutIcon () {
		wxASSERT(BoxBitmap.IsOk());
		return BoxBitmap;
	}



	// returning true from here ensures that we act as a container window for
	// our children
	virtual bool IsStaticBox() const { return true; }
	
private: 
};

class MutBoxShape:public wxBoxSizer
{
protected:
	MutBoxIconShape * m_icon;
	wxBoxSizer * channels;
	int id;

public:
	MutBoxShape():wxBoxSizer(wxVERTICAL),m_icon(NULL),channels(NULL), id(-1) {}

	MutBoxShape(wxStaticBox *box, int orient):
		wxBoxSizer(orient)
		{
			wxASSERT(false);
		}

	MutBoxShape(wxWindow * parent,wxWindowID wid, int Id=-1):
		wxBoxSizer(wxVERTICAL)
		{
			Create(parent,wid,Id);
		}
  
	bool Create(wxWindow * parent,wxWindowID wid, int Id=-1)
		{
			m_icon = new MutBoxIconShape(parent,wid);
			if (m_icon) {
				id = Id;
				m_icon->SetContainingSizer(this);
				m_icon->SetLabel(wxString::Format(_("Box %d"),
								  id));
				m_icon->SetBackgroundColour(BoxColor(Id));
			} else return false;
			channels = this;
			return true;
		}

	virtual MutBoxChannelShape * AddChannel(Route * route);
	virtual void AddPossibleOutput(MutOutputDeviceShape * device);
	
	virtual ~MutBoxShape()
		{ delete m_icon; }


	virtual void SetLabel(const wxString &s);

	virtual void RecalcSizes();
	virtual wxSize CalcMin();

	//  override to hide/show the static box as well
	virtual void ShowItems (bool show);
	virtual void DrawLines(wxDC & dc);
  
	virtual bool Detach( wxWindow *window );
	virtual bool Detach( wxSizer *sizer ) 
		{
			return wxBoxSizer::Detach(sizer); 
		}
	virtual bool Detach( int index ) 
		{ 
			return wxBoxSizer::Detach(index);
		}

private:
	DECLARE_CLASS(MutBoxShape)
	DECLARE_NO_COPY_CLASS(MutBoxShape)
};


class NewMutBoxShape:public MutBoxShape
{
	virtual MutIcon& GetMutIcon();

public:
	NewMutBoxShape(wxWindow * parent, wxWindowID id):MutBoxShape()
		{
			Create (parent, id);
		}

	bool Create (wxWindow * parent, wxWindowID id)
		{ 
			bool status = MutBoxShape::Create(parent, id);
			if (status) {
				SetLabel(_("New Box"));
			}
			return status;
		}

	virtual ~NewMutBoxShape() {}
private:
	DECLARE_CLASS(NewMutBoxShape)
	DECLARE_NO_COPY_CLASS(NewMutBoxShape)
};

//typedef MutDeviceShape* MutDeviceShapePtr;

#endif				/* MUTROUTESHAPES_H */
/*
 * \}
 */

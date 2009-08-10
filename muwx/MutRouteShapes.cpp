// -*-C++ -*-

/** \file
********************************************************************
* Devices Basisklassen.
*
* $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/muwx/Attic/MutRouteShapes.cpp,v 1.2 2009/08/10 11:15:47 keinstein Exp $
* \author Rüdiger Krauße <krausze@mail.berlios.de>,
* Tobias Schlemmer <keinstein@users.berlios.de>
* \date 1998
* $Date: 2009/08/10 11:15:47 $
* \version $Revision: 1.2 $
*
* $Log: MutRouteShapes.cpp,v $
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
#include "wx/wx.h"
#include "MutRouteShapes.h"
#include "MutApp.h"
#include "MutIcon.h"
#include "MutRouteWnd.h"
#include "InputDevDlg.h"
#include "Device.h"


#pragma implementation

MutIcon DevUnknownBitmap;
MutIcon MidiInputDevBitmap;
MutIcon NewInputDevBitmap;
MutIcon MidiOutputDevBitmap;
MutIcon NewOutputDevBitmap;
MutIcon MidiFileBitmap;
MutIcon BoxBitmap;
MutIcon NewBoxBitmap;
MutIcon ActiveChannelBitmap;
MutIcon PassiveChannelBitmap;
#ifdef __WXMAC__
MutIcon MutNullIcon;
#endif
#include "Icon/DevUnknown.xpm"

IMPLEMENT_DYNAMIC_CLASS(MutIconShape, wxControl)
IMPLEMENT_ABSTRACT_CLASS(MutDeviceShape, MutIconShape)
IMPLEMENT_DYNAMIC_CLASS(MutInputDeviceShape, MutDeviceShape)
IMPLEMENT_DYNAMIC_CLASS(MutNewInputDeviceShape, MutInputDeviceShape)
IMPLEMENT_DYNAMIC_CLASS(MutInputMidiFileDeviceShape, MutInputDeviceShape)
IMPLEMENT_DYNAMIC_CLASS(MutInputMidiDeviceShape, MutInputDeviceShape)
IMPLEMENT_CLASS(MutBoxShape, wxBoxSizer)
IMPLEMENT_CLASS(NewMutBoxShape, MutBoxShape)

/*
 * wxStaticBitmap
 */

BEGIN_EVENT_TABLE(MutIconShape, wxStaticText)
EVT_PAINT(MutIconShape::OnPaint)
EVT_SET_FOCUS(MutIconShape::OnGetFocus)
EVT_KILL_FOCUS(MutIconShape::OnKillFocus)
END_EVENT_TABLE()

wxColour BoxColors[MAX_BOX];

static void initBoxColors() {
	for (int i = 1; i<= MAX_BOX; i++) {
		int r = ((i & 0x01) << 8 ) | ((i & 0x08) << 4) | ((i & 0x40));
		r = r?r-1:0;
		int g = ((i & 0x02) << 7 ) | ((i & 0x10) << 3) | ((i & 0x80) >> 1);
		g = g?g-1:0;
		int b = ((i & 0x04) << 6 ) | ((i & 0x20) << 2) | ((i & 0x100) >> 2);
		b = b?b-1:0;
		DEBUGLOG2(_T("Box %d color %x,%x,%x"),i-1,r,g,b);
		BoxColors[i-1]=wxColour(r,g,b);
	}
}


static void initMutIcon(MutIcon & icon, 
			const wxString & filename,
			const wxBitmapType type) 
{
	if (!icon.IsOk())
		if(!icon.LoadFile(filename,type))
			icon = DevUnknownBitmap;
}

bool initMutIconShapes() 
{
	DevUnknownBitmap = MutIcon(wxICON(devunknown));
	if (!DevUnknownBitmap.IsOk()) return false;
  
	initMutIcon(MidiInputDevBitmap,
		    wxGetApp().GetResourceName (_T ("InputDevice.png")),
		    wxBITMAP_TYPE_PNG);
	initMutIcon(NewInputDevBitmap,
		    wxGetApp ().GetResourceName (_T ("NewInputDevice.png")),
		    wxBITMAP_TYPE_PNG);
	initMutIcon(MidiOutputDevBitmap,
		    wxGetApp ().GetResourceName (_T ("OutputDevice.png")),
		    wxBITMAP_TYPE_PNG);
	initMutIcon(NewOutputDevBitmap,
		    wxGetApp ().GetResourceName (_T ("NewOutputDevice.png")),
		    wxBITMAP_TYPE_PNG);
	initMutIcon(MidiFileBitmap,
		    wxGetApp ().GetResourceName (_T ("MidiFile.png")),
		    wxBITMAP_TYPE_PNG);
	initMutIcon(BoxBitmap,
		    wxGetApp ().GetResourceName (_T ("TuningBox.png")),
		    wxBITMAP_TYPE_PNG);
	initMutIcon(ActiveChannelBitmap,
		    wxGetApp ().GetResourceName (_T ("ActiveChannel.png")),
		    wxBITMAP_TYPE_PNG);
	initMutIcon(PassiveChannelBitmap,
		    wxGetApp ().GetResourceName (_T ("PassiveChannel.png")),
		    wxBITMAP_TYPE_PNG);
	initMutIcon(NewBoxBitmap,
		    wxGetApp ().GetResourceName (_T ("TuningBox.png")),
		    wxBITMAP_TYPE_PNG);
	initBoxColors();
	return true;
}

/*
  wxColour BoxColors[MAX_BOX]  =
  {
  wxColour(0xFF, 0x00, 0x00),
  wxColour(0x00, 0xFF, 0x00),
  wxColour(0x80, 0x80, 0xFF),
  wxColour(0xFF, 0xFF, 0x00),
  wxColour(0x00, 0xFF, 0xFF),
  wxColour(0xFF, 0x00, 0xFF),
  wxColour(0xC0, 0xC0, 0xC0),
  wxColour(0x40, 0x80, 0x80),
  wxColour(0x00, 0x80, 0x00),
  wxColour(0x80, 0xFF, 0x00),
  wxColour(0xFF, 0xFF, 0x80),
  };
*/
wxColour BoxColor(int nr)
{

	DEBUGLOG2(_T("Color for box %d requested"),nr);
	if ( nr == GmnBox )
		return wxNullColour;
	//	nr %= 11;
	nr %= MAX_BOX;
	if (nr < 0) nr += MAX_BOX;
	DEBUGLOG2(_T("Returning Color for Box number %d"),nr);
	return BoxColors[nr];

}

wxSize MutIconShape::DoGetBestSize() const 
{
	//  wxSize s(GetWindowBorderSize());
	wxSize s(0,0);
	if (staticText) s += staticText->GetBestSize();
	DEBUGLOG(_T("%p Best Size: %dx%d"),&staticText,s.x,s.y);
	if (GetIcon().IsOk()) {
		s.x = std::max (Icon.GetWidth(), s.x);
		s.y += GetIcon().GetHeight();
	} 
	DEBUGLOG(_T("%p Best Size: %dx%d"),this,s.x,s.y);
	return s;
}

void MutIconShape::DoSetSize(int x, int y,
			     int width, int height,
			     int sizeFlags)
{
	wxControl::DoSetSize(x,y,width,height,sizeFlags);
	Layout();
}

/*
  void DoSetClientSize(int width, int height) 
  {
  wxControl::DoSetClientSize(width, height);
  Layout();
  }
*/

void MutIconShape::OnGetFocus(wxFocusEvent & event)
{
	DEBUGLOG(_(""));
	Refresh();
}

void MutIconShape::OnKillFocus(wxFocusEvent & event)
{
	DEBUGLOG(_(""));
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
	DEBUGLOG(_T("Checking icon"));

	if (!GetIcon().IsOk()) {
		SetIcon(GetMutIcon());
		DEBUGLOG(_T("Checking icon again"));

	}
	DEBUGLOG(_T("Icon ok."));

	int x, y;
	x = 0;
	y = 0;
	if (GetIcon().IsOk()) {
		DEBUGLOG(_T("Size: %dx%d"),GetIcon().GetHeight(),
			 GetIcon().GetWidth());
		x = (size.width-GetIcon().GetWidth())/2;
		dc.DrawIcon(GetIcon(), x, y);
	}

	DEBUGLOG(_T("Focus %p and this %p"),FindFocus(),this);
	if (FindFocus() == this) {
		DEBUGLOG(_T("Painting Box"));
		dc.SetPen(*wxBLACK_PEN);
		dc.SetBrush(*wxTRANSPARENT_BRUSH);
		dc.DrawRectangle(0,0,size.width,size.height);
	}
}

wxPoint MutIconShape::GetPerimeterPoint(const wxPoint i,const wxPoint o) const {
	wxRect r = GetRect();
	wxRect ir = GetIconRect();
	wxASSERT(r.Contains(i));

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

void MutIconShape::LineTo(wxDC &dc, wxPoint & p) 
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
	if (staticText) {
		staticText->Move(0,Icon.GetHeight());
		staticText->CentreOnParent(wxHORIZONTAL);
	}
	return true;
}


BEGIN_EVENT_TABLE(MutDeviceShape, MutIconShape)
EVT_LEFT_DCLICK(MutDeviceShape::LeftDblClickEvent)
END_EVENT_TABLE()

bool MutDeviceShape::Recompute() 
{
	SetIcon(GetMutIcon());
	//  SetLabel (filename.GetFullName());
	return GetIcon().IsOk();
}

bool MutInputDeviceShape:: Create (wxWindow * parent, wxWindowID id, InDevice * d)
{
	device = d;
	if (!d) return false;

	d->setUserData (this);

	DEBUGLOG (_T ("Checking icon"));
	wxASSERT(MidiInputDevBitmap.IsOk());
	
	return MutDeviceShape::Create (parent, id, d->GetName());
}

MutInputDeviceShape * MutInputDeviceShape::CreateShape(wxWindow * parent,
						       wxWindowID id,
						       InDevice * d)
{
	DEBUGLOGTYPE(MutInputDeviceShape,_T("Creating device shape"));
        wxASSERT (d);
	if (!d) return NULL;

	DEBUGLOGTYPE(*d,_T("Device Type"));
	switch (d->GetType()) {
	case DTMidiPort:
		DEBUGLOGTYPE(MutInputDeviceShape,_T("Creating MIDI device shape"));
		return new MutInputMidiDeviceShape(parent,id,d);
	case DTMidiFile:
		DEBUGLOGTYPE(MutInputDeviceShape,_T("Creating MIDI  file device shape"));
		return new MutInputMidiFileDeviceShape(parent,id,d);
	case DTGis:
	default:
		return NULL; 
	}
}

MutInputDeviceShape::~MutInputDeviceShape() {
	RemoveFromStringMap(stringmap);
	if (device) {
		wxASSERT (device -> getUserData() == this);
		device -> setUserData (NULL);
	}
}

void MutInputDeviceShape::SetLabel(const wxString & st ) {
	RemoveFromStringMap(stringmap);
	MutDeviceShape::SetLabel(st);
	InsertSelfToStringMap(stringmap);
}

void MutInputDeviceShape::DoLeftDblClick() {
	InputDevDlg * in = ShowDeviceDialog();
	int Res = in->ShowModal();
	bool destroySelf = false;
	if (Res == wxID_OK) {
		DevType type = in->GetType();
		if (CanHandleType (type)) {
			readDialog (in);
		} else {
			InDevice * indev = InDevice::CreateDevice (type);
			if (indev) {
				MutInputDeviceShape * newdev = 
					MutInputDeviceShape::CreateShape (indev);
				newdev -> readDialog (in);
				destroySelf = replaceSelfBy (newdev);
				m_parent->FitInside();
				m_parent->Refresh();

			}
		}
	}

	in->Destroy();
	if (destroySelf) Destroy();
}

InputDevDlg * MutInputDeviceShape::ShowDeviceDialog() {
	InputDevDlg * in = new InputDevDlg (m_parent);
	int nMidi = rtmidiin->getPortCount();

#ifdef RTMIDI
	nMidi = rtmidiin->getPortCount();

	if ( nMidi )  {
#ifdef __WXMSW__
		wxString portName;
#else
		std::string portName;
#endif

		for (int i = 0; i < nMidi; i++) {
			try {
				portName = rtmidiin->getPortName(i);
#ifdef __WXMSW__
				in->AppendPortChoice(portName);
#else
				in->AppendPortChoice(muT(portName.c_str()));
#endif
			} catch (RtError &error) {
				error.printMessage();
				break;
			}
		}
	} else
		in->AppendPortChoice(_("no device"));
#else
	/*    nMidi = midiInGetNumDevs();
	      if ( nMidi )
	      {
	      for (int i = 0; i < nMidi; i++)
	      {
	      MIDIINCAPS miin;
	      midiInGetDevCaps(i, &miin, sizeof(MIDIINCAPS));
	      DataR0.Device.AddString(miin.szPname);
	      }
	      }
	      else
	      DataR0.Device.AddString("no device");*/
#endif
	//		in->SetType(DTUnknown);
	in->SetMidiDevice(0);
	in->SetMidiFile(wxEmptyString);
	in->SetGUIDOFile(wxEmptyString);

	InitializeDialog(in);
		
	in->Fit();

	return in;
}

bool MutInputDeviceShape::replaceSelfBy (MutInputDeviceShape  * newshape)
{
	wxASSERT (false);
}

MutInputDeviceShape::stringmaptype MutInputDeviceShape::stringmap;
wxSizerFlags MutInputDeviceShape::sizerFlags;

void MutNewInputDeviceShape::InitializeDialog(InputDevDlg * in)
{
	in -> SetType(DTNotSet);
}

bool MutNewInputDeviceShape::replaceSelfBy (MutInputDeviceShape  * newshape)
{
	// the "New device" icon won't be replaced, so we just append the device
	GetContainingSizer()->Add (newshape,sizerFlags);
	return false;
}

void MutInputMidiFileDeviceShape::InitializeDialog(InputDevDlg * in)
{
	wxASSERT(device);
	wxASSERT(device->GetType() == DTMidiFile);
	wxASSERT(in);
	in -> SetType(DTMidiFile);
	in -> SetMidiFile(device->GetName());
}

bool MutInputMidiFileDeviceShape::readDialog (InputDevDlg * in)
{
	wxASSERT(device);
	wxASSERT(device->GetType() == DTMidiFile);
	wxASSERT(in);
	wxASSERT (in -> GetType() == DTMidiFile);
	device->SetName (in -> GetMidiFile());
	SetLabel (device->GetName());
}

void MutInputMidiDeviceShape::InitializeDialog(InputDevDlg * in)
{
	wxASSERT(device);
	wxASSERT(device->GetType() == DTMidiPort);
	wxASSERT(in);
	InMidiPort * dev = dynamic_cast<InMidiPort *> (device);
	wxASSERT (dev);
	in -> SetType(DTMidiPort);
	in -> SetMidiDevice(dev->GetDevId());
}

bool MutInputMidiDeviceShape::readDialog (InputDevDlg * in)
{
	wxASSERT(device);
	wxASSERT(device->GetType() == DTMidiPort);
	wxASSERT(in);
	wxASSERT (in -> GetType() == DTMidiPort);
	InMidiPort * dev = dynamic_cast<InMidiPort *> (device);
	wxASSERT (dev);
	dev->SetDevId (in -> GetMidiDevice());
	SetLabel (dev->GetName());
}

bool MutOutputDeviceShape:: Create (wxWindow * parent, wxWindowID id, OutDevice * d)
{
	device = d;
	if (!d) return false;

	d->setUserData (this);

	DEBUGLOG (_T ("Checking icon"));
	wxASSERT(MidiOutputDevBitmap.IsOk());
	
	return MutDeviceShape::Create (parent, id, d->GetName());
}

void MutOutputDeviceShape::DoLeftDblClick() {

}

MutIcon& MutBoxChannelShape::GetMutIcon()
{

	DEBUGLOG(_T("Checking icons"));

	wxASSERT(ActiveChannelBitmap.IsOk () && PassiveChannelBitmap.IsOk ());

	if (route && (route -> Active)) {
		return ActiveChannelBitmap;
	} else {
		return PassiveChannelBitmap;
	}
}

void MutBoxChannelShape::SetInput(MutInputDeviceShape * device) {
	input = device;
}

void MutBoxChannelShape::SetOutput(MutOutputDeviceShape * device) {
	output = device;
}

void MutBoxChannelShape::AddPossibleOutput(MutOutputDeviceShape * device) {
	OutDevice * out;
	if (route) out = route->Out; else out = NULL;
	if (!out) return;
	if (device->GetDevice() == out) SetOutput(device);
}


void MutBoxChannelShape::DrawLines(wxDC & dc) 
{
	wxRect m_rect = GetRect();
	if (input) {
		wxRect rect = input->GetRect();
		wxPoint p2(m_rect.x+m_rect.width/2,m_rect.y+Icon.GetHeight()/2);
		wxPoint p1(input->GetPerimeterPoint(wxPoint(rect.x+rect.width/2,
							    rect.y+rect.height/2),
						    p2));
		p2 = GetPerimeterPoint(p2,p1);
		input -> LineTo(dc,p1);
		dc.DrawLine(p1,p2);
		LineTo(dc,p2);
	}

	if (output) {
		wxRect rect = output->GetRect();
		wxPoint p2(m_rect.x+m_rect.width/2,m_rect.y+Icon.GetHeight()/2);
		wxPoint p1(output->GetPerimeterPoint(wxPoint(rect.x+rect.width/2,
							     rect.y+rect.height/2),
						     p2));
		p2 = GetPerimeterPoint(p2,p1);
		output -> LineTo(dc,p1);
		dc.DrawLine(p1,p2);
		LineTo(dc,p2);
	}
}


/*
  bool MutBoxIconShape::Create( wxWindow *parent,
  wxWindowID id,
  const wxString& label,
  const wxPoint& pos,
  const wxSize& size,
  long style,
  const wxString& name )
  {
  return inherited::Create(parent,id,pos,size,style,name);
  m_needParent = TRUE;

  if (!PreCreation( parent, pos, size ) ||
  !CreateBase( parent, id, pos, size, style, wxDefaultValidator, name ))
  {
  wxFAIL_MSG( wxT("wxStaticBox creation failed") );
  return FALSE;
  }

  m_widget = GTKCreateFrame(label);
  wxControl::SetLabel(label);

  m_parent->DoAddChild( this );

  PostCreation(size);

  // need to set non default alignment?
  gfloat xalign;
  if ( style & wxALIGN_CENTER )
  xalign = 0.5;
  else if ( style & wxALIGN_RIGHT )
  xalign = 1.0;
  else // wxALIGN_LEFT
  xalign = 0.0;

  if ( style & (wxALIGN_RIGHT | wxALIGN_CENTER) ) // left alignment is default
  gtk_frame_set_label_align(GTK_FRAME( m_widget ), xalign, 0.5);

  // in order to clip the label widget, we must connect to the size allocate
  // signal of this GtkFrame after the default GTK+'s allocate size function
  g_signal_connect_after (m_widget, "size_allocate",
  G_CALLBACK (gtk_frame_size_allocate), this);

  return TRUE;
  }
*/

void MutBoxIconShape::GetBordersForSizer(int &borderTop, int &borderOther) const
{
	const int BORDER = 5; // FIXME: hardcoded value

	wxSize s = DoGetBestSize();
	DEBUGLOG(_T("Best Size: %dx%d"),s.x,s.y);
	/*	if (GetIcon().IsOk()) {
		s.x = std::max (GetIcon().GetWidth(), s.x);
		s.y += GetIcon().GetHeight();
		}
		return s;
	*/
	borderTop = s.y;
	borderOther = 0;
}

void MutBoxIconShape::OnDraw (wxDC & dc) 
{
	DEBUGLOG(_T("Checking icon"));

	if (!GetIcon().IsOk()) {
		SetIcon(GetMutIcon());
		DEBUGLOG(_T("Checking icon again"));

	}
	DEBUGLOG(_T("Icon ok."));

	int x, y;
	x = 0;
	y = 0;
	wxRect size = GetRect();
	if (staticText) y += staticText->GetSize().y;
	if (GetIcon().IsOk()) {
		DEBUGLOG(_T("Size: %dx%d"),GetIcon().GetHeight(),
			 GetIcon().GetWidth());
		x = (size.width-GetIcon().GetWidth())/2;
		dc.DrawIcon(GetIcon(), x, y);
	}

	DEBUGLOG(_T("Focus %p and this %p"),FindFocus(),this);
	if (FindFocus() == this) {
		DEBUGLOG(_T("Painting Box"));
		dc.SetPen(*wxBLACK_PEN);
		dc.SetBrush(*wxTRANSPARENT_BRUSH);
		dc.DrawRectangle(0,0,size.width,size.height);
	}
}

bool MutBoxIconShape::Layout() {
	if (staticText) {
		staticText->Move(0,0);
		staticText->CentreOnParent(wxHORIZONTAL);
	}
	return true;
}


static inline wxSize GetStaticBoxSize( MutBoxIconShape *box )
{
	// this has to be done platform by platform as there is no way to
	// guess the thickness of a wxStaticBox border
	wxSize s  = box->DoGetBestSize();
	DEBUGLOGTYPE(*box,_T("Best Size: %dx%d"),s.x,s.y);
	return s;
}

void MutBoxShape::SetLabel(const wxString & s) 
{ 
	if (m_icon) m_icon->SetLabel(s);
}


void MutBoxShape::RecalcSizes()
{
	int top_border, other_border;
	wxSize size(GetStaticBoxSize(m_icon));

	m_icon->SetSize( m_position.x, m_position.y, m_size.x, m_size.y );

	wxPoint old_pos( m_position );
	m_position.y += size.y;
	wxSize old_size( m_size );
	m_size.y -= size.y;

	wxBoxSizer::RecalcSizes();

	m_position = old_pos;
	m_size = old_size;
}

wxSize MutBoxShape::CalcMin()
{
	wxSize size(GetStaticBoxSize(m_icon));
	wxSize ret( wxBoxSizer::CalcMin() );

	ret.x = std::max(size.x,ret.x);
	ret.y += size.y;

	return ret;
}

void MutBoxShape::ShowItems( bool show )
{
	m_icon->Show( show );
	wxBoxSizer::ShowItems( show );
}

void MutBoxShape::DrawLines(wxDC & dc) 
{
	wxSizerItemList list = GetChildren();
	for (wxSizerItemList::iterator i = list.begin(); 
	     i != (list.end()); i++)
	{
      
		MutBoxChannelShape * channel = (MutBoxChannelShape *) ((*i)->GetWindow());
		wxASSERT(dynamic_cast<MutBoxChannelShape *>(channel));
		wxASSERT(dynamic_cast<MutBoxChannelShape *>((*i)->GetWindow()));
		channel->DrawLines(dc);
	}
}

bool MutBoxShape::Detach( wxWindow *window )
{
	// avoid deleting m_staticBox in our dtor if it's being detached from the
	// sizer (which can happen because it's being already destroyed for
	// example)
	if ( window == m_icon )
	{
		m_icon = NULL;
	}

	return wxSizer::Detach( window );
}


MutBoxChannelShape * MutBoxShape::AddChannel(Route * route)
{
	DEBUGLOG(_T("Adding route %p to window %p"),route, m_containingWindow);
	MutBoxChannelShape * channel = 
		new MutBoxChannelShape(m_containingWindow,
				       wxID_ANY,
				       route);
	channels->Add(channel);
	return channel;
}

void MutBoxShape::AddPossibleOutput(MutOutputDeviceShape * device) {
	wxSizerItemList list = GetChildren();
	for (wxSizerItemList::iterator i = list.begin(); 
	     i != (list.end()); i++)
	{
      
		MutBoxChannelShape * channel = (MutBoxChannelShape *) ((*i)->GetWindow());
		wxASSERT(dynamic_cast<MutBoxChannelShape *>(channel));
		wxASSERT(dynamic_cast<MutBoxChannelShape *>((*i)->GetWindow()));
		channel->AddPossibleOutput(device);
	}
}


MutIcon& NewMutBoxShape::GetMutIcon()
{

	DEBUGLOG(_T("Checking icon"));
	wxASSERT(NewBoxBitmap.IsOk ());
	return NewBoxBitmap;
}

#include <wx/listimpl.cpp>
WX_DEFINE_LIST (MutBoxChannelShapeList);
WX_DEFINE_LIST (MutDeviceShapeList);
WX_DEFINE_LIST (MutBoxShapeList);


/*
 * \}
 */

/////////////////////////////////////////////////////////////////////////////
// Name:        MutApp.cpp
// Purpose:     Mutabor Application
// Author:      R. Krauﬂe
// Modified by:
// Created:     12.08.05
// Copyright:   (c) R. Krauﬂe
// Licence:     wxWindows license
/////////////////////////////////////////////////////////////////////////////

// ---------------------------------------------------------------------------
// headers
// ---------------------------------------------------------------------------

// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
    #pragma hdrstop
#endif

#ifndef WX_PRECOMP
    #include "wx/wx.h"
//    #include "wx/mdi.h"
#endif

#include "Defs.h"
#include <stdio.h>
#include "Runtime.h"
//#include "edevice.h"
//#include "Help.rh"
#include "mhDefs.h"
#include "MutRouteWnd.h"
#include "InputDevDlg.h"
#include "InputFilterDlg.h"
#include "BoxDlg.h"
#include "OutputFilterDlg.h"
#include "OutputDevDlg.h"

#ifndef RTMIDI
#ifndef MMSYSTEM_H
  #define MMSYSTEM_H
//  #define WINVER 0x030a
  #include <mmsystem.h>
#endif
#endif

//#include "Mutabor.rh"
#include "Device.h"
#include "MidiKern.h"

//#if !defined(__WXMSW__)
#include "Icon/DevUnknown.xpm"
#include "Icon/DevMidiPort.xpm"
#include "Icon/DevMidiFile.xpm"
#include "Icon/DevGMN.xpm"
#include "Icon/NewPlop.xpm"
#include "Icon/PlayPlop.xpm"
#include "Icon/PausePlop.xpm"
#include "Icon/ErrorPlop.xpm"
#include "Icon/AddStop.xpm"
#include "Icon/AddPlay.xpm"
#include "Icon/AddPause.xpm"
#include "Icon/AddStopDis.xpm"
//#endif

#ifdef RTMIDI
  #include "RtMidi.h"
  extern RtMidiOut *rtmidiout;
  extern RtMidiIn *rtmidiin;
#endif

#define xd 32 // Devicelogo
#define yd 32

#define xb 24 // Box
#define yb 24

#define ydt 4 // Text
#define yt 16

#define yh 12 // Headline

#define yr (yd+ydt+yt+yz) // Route

#define BACKGROUND *wxLIGHT_GREY // Background color

#define RT_INDEVICE  0
#define RT_INFILTER  1
#define RT_BOX       2
#define RT_OUTFILTER 3
#define RT_OUTDEVICE 4
#define RT_PLAYBUTTON 5
#define RT_STOPBUTTON 6

#define FILENAMELENGTH 200
#define POINT_IN(p, x1, y1, xl, yl) \
(x1 <= p.x && p.x < x1+xl && y1 < p.y && p.y < y1+yl)

DevType IsDT;  // Info f¸r Inputfilter

extern int curBox;
/*wx
void RightButtonMenu(TWindow *win, TPoint &point);
*/
// help functions ---------------------------------------------------

#define max(a, b) ((a) < (b) ? (b) : (a))

int GetTextWidth(wxDC& dc, const wxString &s)
{
	wxCoord w, h;
	dc.GetTextExtent(s, &w, &h);
	return w;
}
/* lieber nicht wg. unicode
int GetTextWidth(wxDC& dc, char *s)
{
	wxString s1 = muT(s);
	return GetTextWidth(dc, s1);
}*/

// TextPin
void TextPin(wxDC &dc, int xm, int y, int xl, const wxString &s, char withBox)
{
	if ( withBox )
		dc.DrawRectangle(xm-xl/2, y, xl, yt);
	wxString s1 = s;
	int w = GetTextWidth(dc, s1);
	while ( s1.Length() > 3 )
	{
		if ( (w = GetTextWidth(dc, s1)) < xl )
			break;
		s1 = s1.Mid(4).Prepend(_T("..."));
	}
	dc.SetBackgroundMode(wxTRANSPARENT);
	dc.DrawText(s1, xm
		-w/2, y+2);
	dc.SetBackgroundMode(wxSOLID);
}

/* Lieber nicht (unicode)
void TextPin(wxDC &dc, int xm, int y, int xl, char *s, char withBox)
{
	wxString s1 = muT(s);
	TextPin(dc, xm, y, xl, s1, withBox);
}*/

// von - bis als string

wxString sRange(int from, int to)
{
  if ( from == to )
    return wxString::Format(_T("%d"), from);
  else if ( from < to )
    return wxString::Format(_("%d -- %d"), from, to);
  return _("--");
}

// Box

wxColour BoxColors[11] =
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

wxColour BoxColor(int nr)
{
  if ( nr == GmnBox )
    return wxColour(0xFF, 0xFF, 0xFF);
  nr %= 11;
  return BoxColors[nr];
}

void PrintBox(wxDC &dc, int xm, int ym, int nr, char active, int x3)
{
  if ( nr == -2 )
    return;

  wxString s(_T("x"));
  if ( nr >= 0 )
    s.Printf(_T("%d"), nr);
  wxBrush Brush = wxBrush(BoxColor(nr));

  dc.SetBrush(Brush);
  if ( !active ) {
    int xv = (x3+xb+2*xz) / 4, yv = (yb+yr) / 4;
    dc.SetPen(wxPen(BACKGROUND, 1));
    dc.DrawLine(xm, ym, xm-xv, ym);
    dc.SetPen(*wxBLACK_PEN);
    dc.DrawLine(xm-xv, ym, xm-xv, ym+yv);
    dc.DrawLine(xm-xv, ym+yv, xm+xv, ym+yv);
    dc.DrawLine(xm+xv, ym+yv, xm+xv, ym);
  } else
    dc.SetPen(wxPen(*wxBLACK, 2));
  dc.DrawRectangle(xm-xb/2, ym-yb/2, xb, yb);
  dc.SetPen(wxNullPen);
  dc.SetBrush(wxNullBrush);
  wxCoord w, h;
  dc.GetTextExtent(s, &w, &h);
  dc.SetBackgroundMode(wxTRANSPARENT);
  dc.DrawText(s, xm - w/2, ym-h/2);
  dc.SetBackgroundMode(wxSOLID);
}

/*
// TNRadioButton - notifying radio button ---------------------------
class TNRadioButton : public TRadioButton
{
  public:
    TNRadioButton(TWindow* parent, int resourceId, TGroupBox *group, TModule* module = 0)
     : TRadioButton(parent, resourceId, group, module) {};
  protected:
    void BNClicked()
    {
      TRadioButton::BNClicked();
      Parent->SendMessage(WM_COMMAND, CM_UPDATE);
    }
    DECLARE_RESPONSE_TABLE(TNRadioButton);
};

DEFINE_RESPONSE_TABLE1(TNRadioButton, TRadioButton)
  EV_NOTIFY_AT_CHILD (BN_CLICKED, BNClicked),
END_RESPONSE_TABLE;

// TNComboBox - notifying combo box ---------------------------------
class TNComboBox : public TComboBox
{
  public:
    TNComboBox(TWindow* parent, int ResourceId, uint textLen = 0, TModule* module = 0)
     : TComboBox(parent, ResourceId, textLen, module) {}
  protected:
    void EvPaint()
    {
      TComboBox::EvPaint();
      Parent->SendMessage(WM_COMMAND, CM_UPDATE);
    }
    DECLARE_RESPONSE_TABLE(TNComboBox);
};

DEFINE_RESPONSE_TABLE1(TNComboBox, TComboBox)
  EV_WM_PAINT,
END_RESPONSE_TABLE;

// TNEdit - notifying edit filed ---------------------------------
class TNEdit : public TEdit
{
  public:
    TNEdit(TWindow* parent, int ResourceId, uint textLen = 0, TModule* module = 0)
     : TEdit(parent, ResourceId, textLen, module) {}
  protected:
    void EvPaint()
    {
      TEdit::EvPaint();
      Parent->SendMessage(WM_COMMAND, CM_UPDATE);
    }
    DECLARE_RESPONSE_TABLE(TNEdit);
};

DEFINE_RESPONSE_TABLE1(TNEdit, TEdit)
  EV_WM_PAINT,
END_RESPONSE_TABLE;

// TRouteDialog - little popup dialogs ------------------------------

class TRouteDialog : public TGraySetupDialog
{
  public:
    TRouteDialog(TWindow* parent, int kind, void *buf, int helpNr, int x, int y);
    virtual void SetupWindow();
    void UpDate();
    void CmSearch();
  protected:
    int Kind;
    TGroupBox *TGB1, *TGB2;
    TNRadioButton *R1, *R2, *R3, *R4, *R5;
    TEdit *E1, *E2;
    TComboBox *C1, *C2;
    TButton *B1;
    TStatic *S1;
    TCheckBox *CB1;
	  DECLARE_RESPONSE_TABLE(TRouteDialog);
};

DEFINE_RESPONSE_TABLE1(TRouteDialog, TGraySetupDialog)
  EV_COMMAND(CM_UPDATE, UpDate),
  EV_COMMAND(IDR_BUTTON01, CmSearch),
END_RESPONSE_TABLE;

TResId RouteDialogId[5] = { IDD_R0, IDD_R1, IDD_R2, IDD_R3, IDD_R0 };

TRouteDialog::TRouteDialog(TWindow* parent, int kind, void *buf, int helpNr, int x, int y)
 : TGraySetupDialog(parent, RouteDialogId[kind], buf, helpNr, x, y)
{
  Kind = kind;
  switch ( kind )
  {
    case 0:
    case 4:
      TGB1 = new TGroupBox(this, IDR_GROUPBOX01);
      TGB2 = new TGroupBox(this, IDR_GROUPBOX02);
      C1 = new TNComboBox(this, IDR_COMBOBOX01);
      E1 = new TEdit(this, IDR_EDIT01, FILENAMELENGTH);
      C2 = new TComboBox(this, IDR_COMBOBOX02);
      E2 = new TEdit(this, IDR_EDIT02, 4);
      B1 = new TButton(this, IDR_BUTTON01);
      S1 = new TStatic(this, IDR_STATIC1);
      break;
    case 1:
      TGB1 = new TGroupBox(this, IDR_GROUPBOX11);
      TGB2 = new TGroupBox(this, IDR_GROUPBOX12);
      R1 = new TNRadioButton(this, IDR_RADIOBUTTON11, TGB1);
      R2 = new TNRadioButton(this, IDR_RADIOBUTTON12, TGB1);
      R3 = new TNRadioButton(this, IDR_RADIOBUTTON13, TGB1);
      R4 = new TNRadioButton(this, IDR_RADIOBUTTON14, TGB1);
      E1 = new TEdit(this, IDR_EDIT11, 4);
      E2 = new TEdit(this, IDR_EDIT12, 4);
      break;
    case 2:
      TGB1 = new TGroupBox(this, IDR_GROUPBOX21);
      TGB2 = new TGroupBox(this, IDR_GROUPBOX22);
      R1 = new TNRadioButton(this, IDR_RADIOBUTTON21, TGB1);
      R2 = new TNRadioButton(this, IDR_RADIOBUTTON22, TGB1);
      R3 = new TNRadioButton(this, IDR_RADIOBUTTON23, TGB1);
      E1 = new TEdit(this, IDR_EDIT21, 4);
      E1->SetValidator(new TRangeValidator(0, 255));
      R4 = new TNRadioButton(this, IDR_RADIOBUTTON24, TGB2);
      R5 = new TNRadioButton(this, IDR_RADIOBUTTON25, TGB2);
      break;
    case 3:
      E1 = new TNEdit(this, IDR_EDIT31, 4);
      E1->SetValidator(new TRangeValidator(0, 15));
      E2 = new TNEdit(this, IDR_EDIT32, 4);
      E2->SetValidator(new TRangeValidator(0, 15));
      CB1 = new TCheckBox(this, IDR_CHECKBOX31);
      break;
  }
}

void TRouteDialog::SetupWindow()
{
  TGraySetupDialog::SetupWindow();
  if ( Kind == 4 )
    SetCaption("Output device");
  if ( Kind == 1)
    if ( IsDT == DTGis )
      R3->SetCaption("box tag");
    else
      R4->SetCaption((IsDT == DTMidiFile) ? "track" : "key range");
  UpDate();
}

void TRouteDialog::CmSearch()
{
  TOpenSaveDialog::TData *FileData =
    ( C1->GetSelIndex() == 1 ) ? &MidiFileData : &GmnFileData;
  E1->GetLine(FileData->FileName,  FILENAMELENGTH, 0);
  FileData->Flags = OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT|OFN_EXPLORER;
  if ( !Kind )
    FileData->Flags |= OFN_FILEMUSTEXIST;
  if (TFileOpenDialog(this, *FileData).Execute() == IDOK)
  {
    E1->DeleteLine(0);
    E1->Insert(FileData->FileName);
  }
}

#define SHOW(val) \
  Show((val) ? SW_SHOWNA : SW_HIDE)
void TRouteDialog::UpDate()
{
  char *TGB2Captions[3] = { "Device name", "Midi file name", "GUIDO file name" };
  int sel;
  switch ( Kind )
  {
    case 0:
    case 4:
      sel = C1->GetSelIndex(); // 0 = MIDIPORT
      TGB2->SetCaption(TGB2Captions[sel]);
      E1->SHOW(sel);
      B1->SHOW(sel);
      C2->SHOW(!sel);
      S1->SHOW(sel != 2 && Kind == 4);
      E2->SHOW(sel != 2 && Kind == 4);
      break;
    case 1:
      E1->EnableWindow( R1->GetCheck() != BF_CHECKED && R2->GetCheck() != BF_CHECKED);
      E2->EnableWindow( R1->GetCheck() != BF_CHECKED && R2->GetCheck() != BF_CHECKED);
      //R4->SHOW(IsDT != DTMidiPort);
      break;
    case 2:
      E1->EnableWindow( R1->GetCheck() == BF_CHECKED );
      R4->EnableWindow( R3->GetCheck() != BF_CHECKED );
      R5->EnableWindow( R3->GetCheck() != BF_CHECKED );
      break;
    case 3:
      char s1[20], s2[20];
      E1->GetText(s1, 19); E2->GetText(s2, 19);
      CB1->EnableWindow( atoi(s1) <= DRUMCHANNEL && DRUMCHANNEL <= atoi(s2));
      break;
  }
}

// TRouteWin --------------------------------------------------------
*/

BEGIN_EVENT_TABLE(MutRouteWnd, wxScrolledWindow)
	EVT_SIZE(MutRouteWnd::OnSize)
	EVT_LEFT_DOWN(MutRouteWnd::OnLeftDown)
	EVT_LEFT_DCLICK(MutRouteWnd::OnLeftDClick)
END_EVENT_TABLE()

/*DEFINE_RESPONSE_TABLE1(TRouteWin, TWindow)
  EV_WM_CHAR,
  EV_WM_SIZE,
  EV_WM_LBUTTONDOWN,
  EV_WM_LBUTTONDBLCLK,
  EV_WM_RBUTTONDOWN,
END_RESPONSE_TABLE;

TFont RouteFont(8, 0, 0, 0, FW_NORMAL,
  false, false, false, 1, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
  DEFAULT_QUALITY, DEFAULT_PITCH|FF_DONTCARE, "MS Sans Serif");
*/

wxFont RouteFont(10, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);

MutRouteWnd::MutRouteWnd(wxWindow *parent, const wxPoint& pos, const wxSize& size)
 : wxScrolledWindow(parent, -1, pos, size)
{
/*  TWindow::Attr.Style |= WS_GROUP | WS_CLIPCHILDREN|
				WS_CLIPSIBLINGS | WS_VSCROLL | WS_HSCROLL | WS_BORDER;
  Scroller = new TScroller(this, 1, 1, 0, 0);
  Attr.AccelTable = IDA_ROUTE;*/
	DevIcon[DTUnknown] = new ICON(devunknown);
	DevIcon[DTMidiPort] = new ICON(devmidiport);
	DevIcon[DTMidiFile] = new ICON(devmidifile);
	DevIcon[DTGis] = new ICON(devgmn);
	ConIcon[0] = new wxBitmap(AddStop_xpm);//, wxBITMAP_TYPE_XPM);
	ConIcon[1] = new wxBitmap(AddPlay_xpm);//, wxBITMAP_TYPE_XPM);
	ConIcon[2] = new wxBitmap(AddPause_xpm);//, wxBITMAP_TYPE_XPM);
	ConIcon[3] = new wxBitmap(AddStopDis_xpm);//, wxBITMAP_TYPE_XPM);
	PlopIcon[0] = new ICON(newplop);
	PlopIcon[1] = new ICON(playplop);
	PlopIcon[2] = new ICON(pauseplop);
	PlopIcon[3] = new ICON(errorplop);
	x1 = 80; x2 = 80; x3 = 30; x4 = 80; x5 = 80;
	SetBackgroundColour(BACKGROUND);
}
/*
void TRouteWin::SetupWindow()
{
  TWindow::SetupWindow();
  SetWindowFont(HFONT(RouteFont), false);
//  NewInstrument();
}

bool TRouteWin::CanClose()
{
  WriteRoutes(&RouteConfig);
  return true;
}

// Reaktion auf Computertastatur

void TRouteWin::EvChar(uint key, uint repeatCount, uint flags)
{
  TWindow::EvChar(key, repeatCount, flags);
  if ( LogicOn )
  {
    if ( 'A' <= key && key <= 'z' || key == VK_TAB
         || key == VK_UP || key == VK_DOWN
         || key == VK_LEFT || key == VK_RIGHT )
    {
      pubTaste = key;
      if ( IsOpen(WK_LOGIC, curBox) )
        GetWinAttr(WK_LOGIC, curBox)->Win->SendMessage(WM_COMMAND, CM_TASTE);
      else
        KeyboardAnalyseSimple(curBox, key);
    }
  }
}
*/

void MutRouteWnd::OnDraw(wxDC& dc)
{
  // x1 und x5 berechnen
  wxSize R = GetClientSize();
  int t1 = 50;
  int t5 = 50;

  for (EDevice *In = InEDevices; In; In = In->Next) {
    t1 = max(t1, GetTextWidth(dc, In->Name));
    for (ERoute *R = In->Routes; R; R = R->Next)
      if ( R->Out )
	t5 = max(t5, GetTextWidth(dc, R->Out->Name));
  }
  x1 = max((int)(R.GetWidth() - 10*xz - 30 - 80 - 80) / 2, 50);
  x5 = x1;
  if ( x1 < t1 || x5 < t5 )
    {
      int s = x5+x1;
      x1 = s*t1/(t1+t5);
      x5 = s*t5/(t1+t5);
    }
  // Mittelpunkte
  int y = yh + yz+yd/2;
  int z1 = xz+x1/2;
  int z2 = 3*xz+x1+x2/2;
  int z3 = 5*xz+x1+x2+x3/2;
  int z4 = 7*xz+x1+x2+x3+x4/2;
  int z5 = 9*xz+x1+x2+x3+x4+x5/2;
  int z1t = z1;  // f¸r Textplop
  if ( z1-xd/2-20 < 2 )
    z1 = xd/2+22; // evtl. verschieben wegen Play-Plops
  wxString s;
  dc.SetFont(RouteFont);
  dc.SetBackgroundMode(wxSOLID);
  wxPen GrayPen(wxColour(0xee, 0xee, 0xee), 1);
  for (REUSE(EDevice*) In = InEDevices; In; In = In->Next) {
    
    // first line segment
    dc.SetPen(*wxBLACK_PEN);
    dc.SetBrush(*wxWHITE_BRUSH);
    dc.DrawLine(z1, y, 2*xz+x1, y);
 
    // InDevice 
    dc.DrawIcon(*DevIcon[In->DT], z1-xd/2, y-yd/2);

    // InDevice Name
    TextPin(dc, z1t, y+yd/2+ydt, x1, In->Name, 0);

    // Mode 
    if ( LogicOn ) {
      if ( In->Mode == -1 )
	dc.DrawIcon(*PlopIcon[0], z1, y-20);
      else if ( In->Mode == 3 )
	dc.DrawIcon(*PlopIcon[3], z1, y-20);
      else if ( In->DT >= DTMidiFile ) {
	/*TODO				memDC.SelectObject(*ConIcon[(In->Mode == 1) ? 2 : 1]);
	  dc.BitBlt(z1-xd/2-20, y-16, 14, 14, memDC, 0, 0, SRCCOPY);
	  memDC.SelectObject(*ConIcon[(In->Mode) ? 0 : 3]);
	  dc.BitBlt(z1-xd/2-20, y+2, 14, 14, memDC, 0, 0, SRCCOPY);
	  if ( In->Mode > 0 )
	  dc.DrawIcon(z1, y-20, *PlopIcon[In->Mode]);*/
	dc.DrawBitmap(*ConIcon[(In->Mode == 1) ? 2 : 1],
		      z1-xd/2-20, y-16, false);
	dc.DrawBitmap(*ConIcon[(In->Mode) ? 0 : 3], 
		      z1-xd/2-20, y+2, false);
	if ( In->Mode > 0 )
	  dc.DrawIcon(*PlopIcon[In->Mode], z1, y-20);
      }
    }

    // Routes
    int n = In->nRoutes(), yl = 0;
    if ( n > 1 )
      yl = (n-1)*yr;
    dc.DrawLine(2*xz+x1, y, 2*xz+x1, y+yl);
    for (ERoute *R = In->Routes; R; R = R->Next) {
      // Line
      dc.DrawLine(2*xz+x1, y, z5, y);

      // Filter
      switch ( R->Type ) {
      case RTall:
	s = _("all");
	break;
      case RTelse:
	s = _("else");
	break;
      case RTchannel:
	if ( In->DT == DTGis )
	  s = wxString::Format(_("box: %s"), sRange(R->IFrom, R->ITo).c_str());
	else
	  s = wxString::Format(_("channel: %s"), 
			       sRange(R->IFrom, R->ITo).c_str());
	break;
      case RTstaff:
	if ( In->DT == DTGis)
	  s = wxString::Format(_("staff: %s"), sRange(R->IFrom, R->ITo).c_str());
	else if ( In->DT == DTMidiPort )
	  s = wxString::Format(_("keys: %s"), sRange(R->IFrom, R->ITo).c_str());
	else
	  s = wxString::Format(_("track: %s"), sRange(R->IFrom, R->ITo).c_str());
	break;
      }

      TextPin(dc, z2, y-yt/2, x2, s, 1);

      // Box
      PrintBox(dc, z3, y, R->Box, R->Active, x3);
      dc.SetPen(*wxBLACK_PEN); // reset Pen

      // Filter
      if ( R->OFrom != -1 && R->Out && R->Out->DT != DTGis ) {
	s = wxString::Format(_("channel: %s"), 
			     sRange(R->OFrom, R->OTo).c_str());
	dc.SetPen(*wxBLACK_PEN);
	dc.SetBrush(*wxWHITE_BRUSH);
	TextPin(dc, z4, y-yt/2, x4, s, 1);
      }

      // OutDevice
      if ( R->Out ) {
	dc.DrawIcon(*DevIcon[R->Out->DT], z5-xd/2, y-yd/2);
	TextPin(dc, z5, y+yd/2+ydt, x5, R->Out->Name, 0);
      }
      y+=yr;
    }
    //    if ( In->Routes ) {
      dc.SetPen(GrayPen);
      dc.SetBrush(*wxTRANSPARENT_BRUSH);
      dc.DrawRectangle(z2-x2/2, y-yt/2-26, x2, yt-26);
      //}
    if ( !n )
      y += yr;
    y += yz;
  }
  dc.SetPen(GrayPen);
  dc.SetBrush(*wxTRANSPARENT_BRUSH);
  dc.DrawRectangle(z1-xd/2, y-yd/2, xd, yd);
  SetVirtualSize(CalcXl(), CalcYl());
}


void MutRouteWnd::OnSize(wxSizeEvent& event)
{
	Refresh();
	SetVirtualSize(CalcXl(), CalcYl());
	event.Skip();
}


/*
void TRouteWin::RePaint()
{
  TRect R = GetClientRect();
  Scroller->SetRange((CalcXl() - R.right) / Scroller->XUnit, (CalcYl()-R.bottom) / Scroller->YUnit);
  CorrectScroller();
  Invalidate();
  PostMessage(WM_PAINT);
}

void TRouteWin::CorrectScroller()
{
  TWindow *Win = GetWindowPtr(GetFocus());
  int xw = Win->Attr.X, yw = Win->Attr.Y;
  int xl = Attr.W, yl = Attr.H;
  int dx = 0, dy = 0;
/wx*  // rechte untere Ecke im Bild ???
  if ( xw + MUTTAGX > xl ) dx = xw + MUTTAGX - xl;
  if ( yw + MUTTAGY > yl ) dy = yw + MUTTAGY - yl;
  // linke obere Ecke im Bild ??? (dominierend)
  if ( xw < 0 ) dx = xw;
  if ( yw < 0 ) dy = yw;
  Scroller->ScrollBy(dx / Scroller->XUnit, dy / Scroller->YUnit); *wx/
}

/wx*
// keyboardanalyse, Fenster aufr‰umen, Logiken lesen und anzeigen
void TRouteWin::UpDate(int thekey, bool isLogicKey)
{
  // Analyse zuerst
  keyboard_analyse(thekey, isLogicKey);
  curTaste[curInstr][isLogicKey] = thekey;
  TWindow *ToFocus = NULL;
  if ( isLogicKey )
	   curTaste[curInstr][0] = 0;
  // alte TMutTag-s lˆschen
  ChildBroadcastMessage(WM_CLOSE);
  // neue erstellen
  char isLogic, s[100], s1[100], key, isOpen;
  TWindow *aWin;
  nTags = 0;
  if ( GetMutTag(isLogic, s, s1, key, true) )
  do
  {
    nTags++;
	 if ( (isOpen = (key == curTaste[curInstr][isLogic])) != 0 )
      if ( isLogic )
      {
        SetString(&(curLogic[curInstr]), s);
		  if ( !s1[0] )
		    if ( !curTS[curInstr] )
            sprintf(s1, "(INITIAL)");
          else if ( curTS[curInstr][0] != '[' )
            sprintf(s1, "[%s]", curTS[curInstr]);
			 else strcpy(s1, curTS[curInstr]);
		  SetString(&(curTS[curInstr]), s1);
	   }
		else
	     SetString(&(curTS[curInstr]), s);
	 aWin = new TMutTag(this, isLogic, isOpen,	10, 10, key, s, GetModule());
    if ( isOpen ) ToFocus = aWin;
  }
  while ( GetMutTag(isLogic, s, s1, key, false) );
  // neue TMutTag-s aktivieren
  CreateChildren();
  // Fokus setzen
  if ( !ToFocus )
	   ToFocus = GetFirstChild();
  ToFocus->SetFocus();
  // Tags anordnen
  SendMessage(WM_SIZE);
  SetFocusPos();
  Parent->SendMessage(WM_COMMAND, CM_SBREFRESH);
  MutWinOk = true;
}

// Reaktion auf neues aktuelles Instrument
void TRouteWin::NewInstrument()
{
  // Titel setzen
  sprintf(sHelp, "Logic: %s - Instrument %d", CompiledFile,
    curInstr + 1);
  Parent->SetCaption(sHelp);
  // Tags updaten
  UpDate(0, true);
}            *wx/
*/
int MutRouteWnd::CalcYl()
{
  int yl = yh+yz;
  for (EDevice *In = InEDevices; In; In = In->Next)
  {
    yl += yr+yz;
    int n = In->nRoutes();
    if ( n > 1 )
      yl += (n-1)*yr;
  }
  return yl+yr;
}

bool MutRouteWnd::CheckPoint(wxPoint point, EDevice **in, ERoute **r, int &token, bool &needNew)
{
  int y = yh + yz, ya, n;
  int z1 = xz+x1/2;
  int z2 = 3*xz+x1+x2/2;
  int z3 = 5*xz+x1+x2+x3/2;
  int z4 = 7*xz+x1+x2+x3+x4/2;
  int z5 = 9*xz+x1+x2+x3+x4+x5/2;
  if ( z1-xd/2-20 < 2 )
    z1 = xd/2+22; // evtl. verschieben wegen Play-Plops
  // get Device
  if ( point.y < y && z1-x1/2 <= point.x && point.x <= z1+x1/2 )
  {
    *in = InEDevices;
    token = RT_INDEVICE;
    needNew = TRUE;
    return 1;
  }
  if ( point.y < y )
    return 0;
  for (*in = InEDevices; *in; *in = (*in)->Next)
  {
    ya = yr+yz;
    n = (*in)->nRoutes();
    if ( n > 1 )
      ya += (n-1)*yr;
    if ( point.y < y+ya )
      break;
    y += ya;
  }
  if ( !*in && z1-x1/2 <= point.x && point.x <= z1+x1/2 )
  {
    token = RT_INDEVICE;
    needNew = TRUE;
    return 1;
  }
  if ( !*in )
    return 0;
  // recalc to "middle-y"
  y += yd/2;
  n = (point.y-y+yr-yb/2-1)/yr; // number of route
  ya = y+n*yr;                  // y of Route
  *r = (*in)->GetRoute(n);
  // check for indevice
  token = RT_INDEVICE;
  needNew = FALSE;
//  if ( POINT_IN(point, z1-xd/2, y-yd/2, xd, yd) ||
//    POINT_IN(point, z1-x1/2, y+yd/2+ydt, x1, yt) )
  if ( LogicOn && POINT_IN(point, z1-xd/2-20, y-16, 14, 14) )
  {
    token = RT_PLAYBUTTON;
    return 1;
  }
  if ( LogicOn && POINT_IN(point, z1-xd/2-20, y+2, 14, 14) )
  {
    token = RT_STOPBUTTON;
    return 1;
  }
  if ( POINT_IN(point, z1-x1/2, y-yd/2, x1, yd+ydt+yt) )
    return 1;
  if ( z1-x1/2 <= point.x && point.x <= z1+x1/2 )
  {
    *in = (*in)->Next;
    needNew = TRUE;
    return 1;
  }
  // check for in-filter
  token = RT_INFILTER;
  if ( POINT_IN(point, z2-x2/2, ya-yt/2, x2, yt) )
    return 1;
  if ( z2-x2/2 <= point.x && point.x <= z2+x2/2 )
  {
    needNew = TRUE;
    return 1;
  }
  // check for box
  token = RT_BOX;
  if ( POINT_IN(point, z3-xb/2, ya-yb/2, xb, yb) )
    return 1;
  // check for out-filter
  token = RT_OUTFILTER;
  if ( POINT_IN(point, z4-x4/2, ya-yt/2, x4, yt) )
    return 1;
  // check for outdevice
  token = RT_OUTDEVICE;
  if ( POINT_IN(point, z5-xd/2, ya-yd/2, xd, yd) ||
    POINT_IN(point, z5-x5/2, ya+yd/2+ydt, x5, yt) )
    return 1;
  return 0;
}

void MutRouteWnd::OnLeftDown(wxMouseEvent &event)
{
  EDevice *In=0;
  ERoute *R=0;
  bool NeedNew;
  int Token;
  // Punkt auf absolute Fensterkoordinaten umrechnen
  wxPoint rp;
  CalcUnscrolledPosition(event.GetX(), event.GetY(), &rp.x, &rp.y);
  // Box erwischt ?
  if ( !CheckPoint(rp, &In, &R, Token, NeedNew) )
    return;
  if ( !R || NeedNew )
    return;
  if ( R->Box >= 0 ) {
    wxCommandEvent event1(wxEVT_COMMAND_MENU_SELECTED, CM_BOX);
    event1.SetId(R->Box);
    GetParent()->ProcessEvent(event1);
  }
  if ( In->DT < DTMidiPort )
    return;
  if ( Token == RT_PLAYBUTTON ) {
    if ( In->Mode == MutaborDevicePlay ) // Pause
      In->Mode = MutaborDevicePause;
    else                 // Play
      In->Mode = MutaborDevicePlay;
    InDeviceAction(In->Nr, In->Mode);
    //RePaint();
    Refresh(); // Reicht das auch?
  }
  if ( Token == RT_STOPBUTTON ) {
    if ( In->Mode != MutaborDeviceStop ) {
      In->Mode = MutaborDeviceStop;
      InDeviceAction(In->Nr, In->Mode);
      //RePaint();
      Refresh(); // Reicht das auch?
    }
  }
}

void MutRouteWnd::OnLeftDClick(wxMouseEvent &event)
{
  EDevice *In=NULL;
  ERoute *R=NULL, **R1 = NULL;
  bool NeedNew;
  int Token, Res = wxID_CANCEL;
  wxPoint rp;

  CalcUnscrolledPosition(event.GetX(), event.GetY(), &rp.x, &rp.y);
  if ( !CheckPoint(rp, &In, &R, Token, NeedNew) )
    return;
  if ( !R && Token > RT_INFILTER )
    return;
  int nMidi;
  /*if ( LogicOn )
    {
    wxMessageBox(_("Stop the logics, before you edit the routes!"), _("Not yet!") , wxOK | wxICON_STOP);
    return;
    }*/

  switch ( Token ) {
  case RT_INDEVICE: 
    {	// evtl. neues Device anlegen
      if ( NeedNew ) {
	In = NewDevice(&InEDevices, DTUnknown, wxEmptyString, 0, 0, In);
	Refresh();//RePaint();
      }
      InputDevDlg in(this);
      // ComboBoxen f¸llen
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
	    in.AppendPortChoice(portName);
#else						
	    in.AppendPortChoice(muT(portName.c_str()));
#endif
	  }
	  catch (RtError &error) {
	    error.printMessage();
	    break;
	  }
	}
      } else
	in.AppendPortChoice(_("no device"));
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
      in.SetType(DTUnknown);
      in.SetMidiDevice(0);
      in.SetMidiFile(wxEmptyString);
      in.SetGUIDOFile(wxEmptyString);
      // fill with datas
      DevType type = DTUnknown;
      in.SetType( In->DT );
      switch ( In->DT ) {
      case DTGis:
	in.SetGUIDOFile(In->Name);
	break;
      case DTMidiPort:
	in.SetMidiDevice(In->DevId);
	break;
      case DTMidiFile:
	in.SetMidiFile(In->Name);
	break;
      case DTNotSet:
	wxLogWarning(_("Unexpected value: DTNotSet"));
	break;
      case DTUnknown:
	break;
      default:
	wxLogError(_("Unexpected device type: %d"), In->DT); 
      }

      Res = in.ShowModal();

      if ( Res == wxID_OK ) {
	DEBUGLOG(_T("Got value %d"),in.GetType());
	type = in.GetType();
	switch (type) {
	case DTMidiPort:
	  NewDevice(&InEDevices, 
		    DTMidiPort, 
		    in.GetPortString(in.GetMidiDevice()), 
		    in.GetMidiDevice(), In, In);
	  break;
	case DTMidiFile:
	  NewDevice(&InEDevices, DTMidiFile, in.GetMidiFile(), 0, In, In);
	  break;
	case DTGis:
	  NewDevice(&InEDevices, DTGis, in.GetGUIDOFile(), 0, In, In);
	  break;
	case DTNotSet:
	case DTUnknown:
	  break;
	default:
	  wxLogWarning(_("Unexpected value: %d"),type);
	}
      } else if ( Res == wxID_REMOVE || (NeedNew && Res == wxCANCEL) )
	  NewDevice(&InEDevices, DTNotSet, wxEmptyString, 0, In, 0);
	break;
    }
    case RT_INFILTER:
      {
	// evtl. neue Route anlegen
	if ( !R )
	  NeedNew = TRUE;
	if ( NeedNew ) {
	  // als Adresse ermitteln
	  for (R1 = &In->Routes; *R1; R1 = &((*R1)->Next))
	    if ( *R1 == R )
	      break;
	  R = new ERoute(RTall, 0, 0, -2, 0, 0, 0, 15);
	  R->Next = *R1;
	  *R1 = R;
	  Refresh();//RePaint();
	}
	//
	IsDT = In->DT;
	InputFilterDlg dlg(this, In->DT);
	dlg.SetType(R->Type);
	dlg.SetFrom(R->IFrom);
	dlg.SetTo(R->ITo);
	dlg.UpdateLayout(R->Type);
	Res = dlg.ShowModal();
	if ( Res == wxID_OK ) {
	  R->Type = (RouteType)dlg.GetType();
	  R->IFrom = dlg.GetFrom();
	  R->ITo = dlg.GetTo();
	}
	else if ( Res == wxID_REMOVE || (NeedNew && Res == wxID_CANCEL) )
	  for (R1 = &(In->Routes); *R1; R1 = &((*R1)->Next))
	    if ( *R1 == R ) {
	      *R1 = R->Next;
	      R->Next = 0;
	      break;
	    }
	break;
      }
    case RT_BOX:
      {
	BoxDlg dlg(this);
	// fill with datas
	dlg.SetBoxNr(0);
	int Type = 0;
	if ( R->Box == NoBox )
	  Type = 2;
	else if ( R->Box == GmnBox )
	  Type = 1;
	else {
	  Type = 0;
	  dlg.SetBoxNr(R->Box);
	}
	dlg.SetBoxType(Type);
	dlg.ctrlBox1->SetValue(Type == 0);
	dlg.ctrlBox2->SetValue(Type == 1);
	dlg.ctrlBox3->SetValue(Type == 2);
	dlg.SetMode(!R->Active);
	dlg.UpdateLayout(Type);
	Res = dlg.ShowModal();
	if ( Res == wxID_OK ) {
	  switch ( dlg.GetBoxType() ) {
	  case 0: R->Box = dlg.GetBoxNr(); break;
	  case 1: R->Box = GmnBox; break;
	  case 2: R->Box = NoBox; break;
	  }
	  R->Active = !dlg.GetMode();
	}
	break;
      }
    case RT_OUTFILTER:
      {
	OutputFilterDlg dlg(this);
	dlg.SetFrom(R->OFrom);
	dlg.SetTo(R->OTo);
	dlg.SetAvoidDrumChannel(R->ONoDrum);
	Res = dlg.ShowModal();
	if ( Res == wxID_OK ) {
	  R->OFrom = dlg.GetFrom();
	  R->OTo = dlg.GetTo();
	  R->ONoDrum = dlg.GetAvoidDrumChannel();
	}
	break;
      }
    case RT_OUTDEVICE:
      EDevice *Out = R->Out;
      // evtl. neues Device anlegen
      if ( !Out ) {
	Out = NewDevice(&OutEDevices, DTUnknown, wxEmptyString, 0, 0, 0);
	R->Out = Out;
	Refresh(); //RePaint();
	NeedNew = TRUE;
      }
      // ComboBoxen f¸llen
      OutputDevDlg out(this);
#ifdef RTMIDI
      nMidi = rtmidiout->getPortCount();
      if ( nMidi ) {
#ifdef __WXMSW__
	wxString portName;
#else
	std::string portName;
#endif
	for (int i = 0; i < nMidi; i++)  {
	  try {
	    portName = rtmidiout->getPortName(i);
#ifdef __WXMSW__
	    out.ctrlMidiDevice->Append(portName);
#else	
	    out.ctrlMidiDevice->Append(muT(portName.c_str()));
#endif
	  }
	  catch (RtError &error) {
	    error.printMessage();
	    break;
	  }
	}
      }
      else
	out.ctrlMidiDevice->Append(_("no device"));
#else
      nMidi = midiOutGetNumDevs();
      if ( nMidi ) {
	for (int i = 0; i < nMidi; i++) {
	  MIDIOUTCAPS miout;
	  midiOutGetDevCaps(i, &miout, sizeof(MIDIOUTCAPS));
	  DataR0.Device.AddString(miout.szPname);
	}
      }
      else
        DataR0.Device.AddString("no device");
#endif
      out.SetType(0);
      out.SetMidiDevice(0);
      out.SetMidiDeviceBending(2);
      out.SetMidiFile(wxEmptyString);
      out.SetMidiFileBending(2);
      out.SetGUIDOFile(wxEmptyString);
      // fill with datas
      int type = 0;
      switch ( Out->DT ) {
      case DTGis:
	out.SetType(type = 2);
	out.SetGUIDOFile(Out->Name);
	break;
      case DTMidiPort:
	out.SetMidiDevice(Out->DevId);
	out.SetMidiDeviceBending(Out->BendingRange);
	break;
      case DTMidiFile:
	out.SetType(type = 1);
	out.SetMidiFile(Out->Name);
	out.SetMidiFileBending(Out->BendingRange);
	break;
      case DTNotSet:
	wxLogWarning(_("Unexpected value: DTNotSet"));
	break;
      case DTUnknown:
	break;
      default:
	wxLogError(_("Unexpected device type: %d"), Out->DT); 
      }
      out.UpdateLayout(type);
      Res = out.ShowModal();
      if ( Res == wxID_OK ) {
	int type = out.GetType();
	if ( type == 0 ) {
	  Out = NewDevice(&OutEDevices, 
			  DTMidiPort, 
			  out.ctrlMidiDevice->GetString(out.GetMidiDevice()), 
			  out.GetMidiDevice(), Out, Out);
	  Out->BendingRange = out.GetMidiDeviceBending();
	}
	else if ( type == 1 ) {
	  Out = NewDevice(&OutEDevices,
			  DTMidiFile, 
			  out.GetMidiFile(), 
			  0, Out, Out);
	  Out->BendingRange = out.GetMidiFileBending();
	}
	else			
	  Out = NewDevice(&OutEDevices, DTGis, out.GetGUIDOFile(), 0, Out, Out);
      }
      else if ( Res == wxID_REMOVE || (NeedNew && Res == wxCANCEL) )
	Out = 0; // NewDevice(&OutEDevices, DTNotSet, "", 0, Out, 0);  nicht lˆschen, kˆnnte ja noch eine andere Route verwenden
      R->Out = Out;
      break;
    }
    // evtl. neu zeichnen
    if ( Res == wxID_OK || Res == wxID_REMOVE || NeedNew )
      Refresh();//RePaint();
  }
/*
  void TRouteWin::EvRButtonDown(uint, TPoint& point)
  {
  if ( LogicOn )
  RightButtonMenu(this, point);
  }
*/

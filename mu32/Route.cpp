// ------------------------------------------------------------------
// Mutabor 3, 1998, R.Krauﬂe
// Routenfenster Klasse
// ------------------------------------------------------------------

// TRouteWin --------------------------------------------------------

#include <owl/pch.h>
#include <owl/radiobut.H>
#include <owl/combobox.H>
#include <owl/edit.H>
#include <owl/groupbox.h>
#include <owl/scroller.h>
#include <owl/validate.h>
#include <winsys/color.h>


#include <stdio.h>
#include "Runtime.h"
#include "Help.rh"

#ifndef RTMIDI
#ifndef MMSYSTEM_H
  #define MMSYSTEM_H
//  #define WINVER 0x030a
  #include <mmsystem.h>
#endif
#endif

#include "Route.h"
#include "Mutabor.rh"
#include "Gray.h"
#include "mutwin.h"
#include "mdimutch.h"
#include "MidiKern.h"

#ifdef RTMIDI
  #include "RtMidi.h"
  extern RtMidiOut *rtmidiout;
  extern RtMidiOut *rtmidiin;
#endif

#define xd 32 // Devicelogo
#define yd 32

#define xb 24 // Box
#define yb 24

#define ydt 4 // Text
#define yt 16

#define yh 12 // Headline

#define yr (yd+ydt+yt+yz) // Route

#define BACKGROUND TColor::LtGray // Background color

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
void RightButtonMenu(TWindow *win, TPoint &point);

// help functions ---------------------------------------------------

// TextPin
void TextPin(TDC &dc, int xm, int y, int xl, char *s, char withBox)
{
  if ( withBox )
  {
    dc.Rectangle(xm-xl/2, y, xm+xl/2, y+yt);
  }
  char s2[400], *s1 = s2;
  strncpy(s2, s, 399);
  TSize Size;
  while ( s1[0] )
  {
    Size = dc.GetTextExtent(s1, strlen(s1));
    if ( Size.cx < xl )
      break;
    s1 = &s1[1];
    if ( s1[0] )
      s1[0] = '.';
    else
      continue;
    if ( s1[1] )
      s1[1] = '.';
    else
      continue;
    if ( s1[2] )
      s1[2] = '.';
    else
      continue;
  }
  dc.SetBkMode(TRANSPARENT);
  dc.TextOut(xm-Size.cx/2, y+2, s1);
  dc.SetBkMode(OPAQUE);
}

// von - bis als string
char sRangeHelp[20];

char *sRange(int from, int to)
{
  if ( from == to )
    sprintf(sRangeHelp, "%d", from);
  else if ( from < to )
    sprintf(sRangeHelp, "%d - %d", from, to);
  else
    strcpy(sRangeHelp, "-");
  return sRangeHelp;
}

// Box

TColor BoxColors[11] =
{
  PALETTERGB(0xFF, 0x00, 0x00),
  PALETTERGB(0x00, 0xFF, 0x00),
  PALETTERGB(0x80, 0x80, 0xFF),
  PALETTERGB(0xFF, 0xFF, 0x00),
  PALETTERGB(0x00, 0xFF, 0xFF),
  PALETTERGB(0xFF, 0x00, 0xFF),
  PALETTERGB(0xC0, 0xC0, 0xC0),
  PALETTERGB(0x40, 0x80, 0x80),
  PALETTERGB(0x00, 0x80, 0x00),
  PALETTERGB(0x80, 0xFF, 0x00),
  PALETTERGB(0xFF, 0xFF, 0x80),
};

TColor BoxColor(int nr)
{
  if ( nr == GmnBox )
    return PALETTERGB(0xFF, 0xFF, 0xFF);
  nr %= 11;
  return BoxColors[nr];
}

void PrintBox(TDC &dc, int xm, int ym, int nr, char active, int x3)
{
  if ( nr == -2 )
    return;
  char s[5] = "x";
  if ( nr >= 0 )
    sprintf(s, "%d", nr);
  TBrush Brush = TBrush(BoxColor(nr));
  dc.SelectObject(Brush);
  if ( !active )
  {
    int xv = (x3+xb+2*xz) / 4, yv = (yb+yr) / 4;
    dc.SelectObject(TPen(BACKGROUND, 1));
    dc.MoveTo(xm, ym);
    dc.LineTo(xm-xv, ym);
    dc.RestorePen();
    dc.SelectObject(TPen(RGB(0,0,0), 1, PS_SOLID));
    dc.LineTo(xm-xv, ym+yv);
    dc.LineTo(xm+xv, ym+yv);
    dc.LineTo(xm+xv, ym);
  }
  else
  {
    dc.SelectObject(TPen(RGB(0,0,0), 2, PS_SOLID));
  }
  dc.Rectangle(xm-xb/2, ym-yb/2, xm+xb/2, ym+yb/2);
  dc.RestorePen();
  dc.RestoreBrush();
  TSize Size = dc.GetTextExtent(s, strlen(s));
  dc.SetBkMode(TRANSPARENT);
  dc.TextOut(xm - Size.cx/2, ym-Size.cy/2, s);
  dc.SetBkMode(OPAQUE);
}

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

DEFINE_RESPONSE_TABLE1(TRouteWin, TWindow)
  EV_WM_CHAR,
  EV_WM_SIZE,
  EV_WM_LBUTTONDOWN,
  EV_WM_LBUTTONDBLCLK,
  EV_WM_RBUTTONDOWN,
END_RESPONSE_TABLE;

TFont RouteFont(8, 0, 0, 0, FW_NORMAL,
  false, false, false, 1, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
  DEFAULT_QUALITY, DEFAULT_PITCH|FF_DONTCARE, "MS Sans Serif");

TRouteWin::TRouteWin(TWindow *parent, TModule *module)
 : TWindow(parent, "Routes", module)
{
  TWindow::Attr.Style |= WS_GROUP | WS_CLIPCHILDREN|
				WS_CLIPSIBLINGS | WS_VSCROLL | WS_HSCROLL | WS_BORDER;
  Scroller = new TScroller(this, 1, 1, 0, 0);
  Attr.AccelTable = IDA_ROUTE;
  DevIcon[DTUnknown] = new TIcon(GetModule()->GetInstance(), (TResId)ICON_RUNKNOWN);
  DevIcon[DTMidiPort] = new TIcon(GetModule()->GetInstance(), (TResId)ICON_RMIDIPORT);
  DevIcon[DTMidiFile] = new TIcon(GetModule()->GetInstance(), (TResId)ICON_RMIDIFILE);
  DevIcon[DTGis] = new TIcon(GetModule()->GetInstance(), (TResId)ICON_RGMN);
  ConIcon[0] = new TBitmap(*GetApplication(), IDI_STOP);
  ConIcon[1] = new TBitmap(*GetApplication(), IDI_PLAY);
  ConIcon[2] = new TBitmap(*GetApplication(), IDI_PAUSE);
  ConIcon[3] = new TBitmap(*GetApplication(), IDI_STOPDIS);
  PlopIcon[0] = new TIcon(GetModule()->GetInstance(), (TResId)IDI_NEWPLOP);
  PlopIcon[1] = new TIcon(GetModule()->GetInstance(), (TResId)IDI_PLAYPLOP);
  PlopIcon[2] = new TIcon(GetModule()->GetInstance(), (TResId)IDI_PAUSEPLOP);
  PlopIcon[3] = new TIcon(GetModule()->GetInstance(), (TResId)IDI_ERRORPLOP);
  x1 = 80; x2 = 80; x3 = 30; x4 = 80; x5 = 80;
  SetBkgndColor(BACKGROUND);
}

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

/*
void TRouteWin::CmTaste()
{
  int key = pubTaste;
  if ( key == VK_TAB )
  {
	   HWND Handle = GetWindowPtr(GetFocus())->GetNextWindow(GW_HWNDNEXT);
	   if ( Handle )
		    GetWindowPtr(Handle)->SetFocus();
	   else
		    GetFirstChild()->SetFocus();
      SetFocusPos();
	   CorrectScroller();
  }
  else if ( key == VK_UP )
	   MoveFocus(0, -1);
  else if ( key == VK_DOWN )
	   MoveFocus(0, +1);
  else if ( key == VK_LEFT )
	   MoveFocus(-1, 0);
  else if ( key == VK_RIGHT )
	   MoveFocus(+1, 0);
  else if ( key == VK_SPACE )
  {
    TWindow *Win = FirstThat(HasPosition, FocusPos);
    if ( Win ) Win->SetFocus();
    CorrectScroller();
    SetFocusPos();
  }
  else
  {
	   // Buchstabentaste
	   // Umwandeln in Groﬂbuchstaben
	   if ( 'a' <= key && key <= 'z' ) key += 'A' - 'a';
	   // ermiteln, ob Logik
	   char isLogic = IsLogicKey(key);
	   if ( isLogic == 2 ) return;
	   // Update aufrufen
	   UpDate(key, isLogic);
  }
}
*/

void TRouteWin::EvSize(uint sizeType, TSize &size)
{
  TWindow::EvSize(sizeType, size);
//  TWindow *Win = GetFirstChild();
  TRect R = GetClientRect();
/*  int nx = R.right / MUTTAGX, ny = R.bottom / MUTTAGY;
  bool quer = R.right > R.bottom;
  if ( nx * ny < nTags ) // Scroller notwendig
  {
    if  ( !nx ) nx = 1;
    if  ( !ny ) ny = 1;
    if ( quer ) nx = (nTags + ny -1) / ny;
  }
  int x = 0, y = 0, xi = 0;
  while ( Win )
  {
	   Win->MoveWindow(x - Scroller->XPos*Scroller->XUnit, y - Scroller->YPos*Scroller->YUnit, MUTTAGX, MUTTAGY, true);
	   x += MUTTAGX;
    xi++;
	   if ( xi == nx )
	   {
      x = 0; xi = 0;
      y += MUTTAGY;
  	 }
	   HWND Handle = Win->GetNextWindow(GW_HWNDNEXT);
	   if ( Handle )
		    Win = GetWindowPtr(Handle);
	   else
		    Win = 0;
  }
  if ( !x ) y -= MUTTAGY;
  if ( quer ) */
  RedrawWindow(0, 0);
  Scroller->SetRange((CalcXl() - R.right) / Scroller->XUnit, (CalcYl()-R.bottom) / Scroller->YUnit);
  CorrectScroller();
};

void TRouteWin::Paint(TDC& dc, bool erase, TRect& rect)
{
  // x1 und x5 berechnen
  TRect R = GetClientRect();
  int t1 = 50;
  int t5 = 50;
  for (EDevice *In = InEDevices; In; In = In->Next)
  {
    TSize Size = dc.GetTextExtent(In->Name, strlen(In->Name));
    t1 = max(t1, Size.cx);
    for (ERoute *R = In->Routes; R; R = R->Next)
      if ( R->Out )
      {
        Size = dc.GetTextExtent(R->Out->Name, strlen(R->Out->Name));
        t5 = max(t5, Size.cx);
      }
  }
  x1 = max((int)(R.right - 10*xz - 30 - 80 - 80) / 2, 50);
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
  char s[100];
  dc.SelectObject((HFONT) RouteFont);
  dc.SetBkMode(OPAQUE);
  TPen GreyPen(RGB(208, 208, 208), 1, PS_SOLID);
  for (EDevice *In = InEDevices; In; In = In->Next)
  {
    dc.SelectStockObject(BLACK_PEN);
    dc.SelectStockObject(WHITE_BRUSH);
    dc.MoveTo(z1, y);
    dc.LineTo(2*xz+x1, y);
    // InDevice zeichnen
    dc.DrawIcon(z1-xd/2, y-yd/2, *DevIcon[In->DT]);
    TextPin(dc, z1t, y+yd/2+ydt, x1, In->Name, 0);
    // Mode zeichnen
    if ( LogicOn )
    {
      TMemoryDC memDC(dc);
      if ( In->Mode == -1 )
        dc.DrawIcon(z1, y-20, *PlopIcon[0]);
      else if ( In->Mode == 3 )
        dc.DrawIcon(z1, y-20, *PlopIcon[3]);
      else if ( In->DT >= DTMidiFile )
      {
        memDC.SelectObject(*ConIcon[(In->Mode == 1) ? 2 : 1]);
        dc.BitBlt(z1-xd/2-20, y-16, 14, 14, memDC, 0, 0, SRCCOPY);
        memDC.SelectObject(*ConIcon[(In->Mode) ? 0 : 3]);
        dc.BitBlt(z1-xd/2-20, y+2, 14, 14, memDC, 0, 0, SRCCOPY);
        if ( In->Mode > 0 )
          dc.DrawIcon(z1, y-20, *PlopIcon[In->Mode]);
      }
    }
    // Route zeichnen
    int n = In->nRoutes(), yl = 0;
    if ( n > 1 )
      yl = (n-1)*yr;
    dc.LineTo(2*xz+x1, y+yl);
    for (ERoute *R = In->Routes; R; R = R->Next)
    {
      // Line
      dc.MoveTo(2*xz+x1, y);
      dc.LineTo(z5, y);
      // Filter
      switch ( R->Type )
      {
        case RTall:
          strcpy(s, "all");
          break;
        case RTelse:
          strcpy(s, "else");
          break;
        case RTchannel:
          if ( In->DT == DTGis )
            sprintf(s, "box: %s", sRange(R->IFrom, R->ITo));
          else
            sprintf(s, "channel: %s", sRange(R->IFrom, R->ITo));
          break;
        case RTstaff:
          if ( In->DT == DTGis)
            sprintf(s, "staff: %s", sRange(R->IFrom, R->ITo));
          else if ( In->DT == DTMidiPort )
            sprintf(s, "keys: %s", sRange(R->IFrom, R->ITo));
          else
            sprintf(s, "track: %s", sRange(R->IFrom, R->ITo));
          break;
      }
      TextPin(dc, z2, y-yt/2, x2, s, 1);
      // Box
      PrintBox(dc, z3, y, R->Box, R->Active, x3);
      // Filter
      if ( R->OFrom != -1 && R->Out && R->Out->DT != DTGis )
      {
        sprintf(s, "channel: %s", sRange(R->OFrom, R->OTo));
        TextPin(dc, z4, y-yt/2, x4, s, 1);
      }
      // OutDevice
      if ( R->Out )
      {
        dc.DrawIcon(z5-xd/2, y-yd/2, *DevIcon[R->Out->DT]);
        TextPin(dc, z5, y+yd/2+ydt, x5, R->Out->Name, 0);
      }
      y+=yr;
    }
    if ( In->Routes )
    {
      dc.SelectObject((HPEN) GreyPen);
      dc.SelectStockObject(NULL_BRUSH);
      dc.Rectangle(z2-x2/2, y-yt/2-26, z2+x2/2, y+yt/2-26);
    }
    if ( !n ) y += yr;
    y += yz;
  }
  dc.SelectObject((HPEN) GreyPen);
  dc.SelectStockObject(NULL_BRUSH);
  dc.Rectangle(z1-xd/2, y-yd/2, z1+xd/2, y+yd/2);
}

void TRouteWin::RePaint()
{
  TRect R = GetClientRect();
  Scroller->SetRange((CalcXl() - R.right) / Scroller->XUnit, (CalcYl()-R.bottom) / Scroller->YUnit);
  CorrectScroller();
  Invalidate();
  PostMessage(WM_PAINT);
}

// Reaktion auf geklickte TMutTag-s
/*
void TRouteWin::CmMutTag()
{
  TMutTag *MutTag = (TMutTag*)GetWindowPtr(GetFocus());
  UpDate(MutTag->GetKey(), MutTag->GetIsLogic());
}

void TRouteWin::MoveFocus(int vx, int vy)
{
  TWindow *Win = GetWindowPtr(GetFocus());
  int pos[2] = { Win->Attr.X + vx * MUTTAGX, Win->Attr.Y + vy * MUTTAGY };
  Win = FirstThat(HasPosition, pos);
  if ( Win ) Win->SetFocus();
  SetFocusPos();
  CorrectScroller();
}
*/
void TRouteWin::CorrectScroller()
{
  TWindow *Win = GetWindowPtr(GetFocus());
  int xw = Win->Attr.X, yw = Win->Attr.Y;
  int xl = Attr.W, yl = Attr.H;
  int dx = 0, dy = 0;
/*  // rechte untere Ecke im Bild ???
  if ( xw + MUTTAGX > xl ) dx = xw + MUTTAGX - xl;
  if ( yw + MUTTAGY > yl ) dy = yw + MUTTAGY - yl;
  // linke obere Ecke im Bild ??? (dominierend)
  if ( xw < 0 ) dx = xw;
  if ( yw < 0 ) dy = yw;
  Scroller->ScrollBy(dx / Scroller->XUnit, dy / Scroller->YUnit); */
}

void TRouteWin::SetFocusPos()
{
/*  TWindow *Win = GetWindowPtr(GetFocus());
  FocusPos[0] = Win->Attr.X;
  FocusPos[1] = Win->Attr.Y; */
}
/*
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
}            */

int TRouteWin::CalcYl()
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

bool TRouteWin::CheckPoint(TPoint point, EDevice **in, ERoute **r, int &token, bool &needNew)
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

void TRouteWin::EvLButtonDown(UINT modKeys, TPoint& point)
{
  EDevice *In;
  ERoute *R;
  bool NeedNew;
  int Token;
  // Punkt auf absolute Fensterkoordinaten umrechnen
  TPoint rp = point;
  rp.x += Scroller->XPos*Scroller->XUnit;
  rp.y += Scroller->YPos*Scroller->YUnit;
  // Box erwischt ?
  if ( !CheckPoint(rp, &In, &R, Token, NeedNew) )
    return;
  if ( !R || NeedNew )
    return;
  if ( R->Box >= 0 )
  {
    GetApplication()->GetMainWindow()->SendMessage(CM_BOX, R->Box, 0);
  }
  if ( In->DT < DTMidiPort )
    return;
  if ( Token == RT_PLAYBUTTON )
  {
    if ( In->Mode == 1 ) // Pause
      In->Mode = 2;
    else                 // Play
      In->Mode = 1;
    InDeviceAction(In->Nr, In->Mode);
    RePaint();
  }
  if ( Token == RT_STOPBUTTON )
  {
    if ( In->Mode != 0 ) // Stop
    {
      In->Mode = 0;
      InDeviceAction(In->Nr, In->Mode);
      RePaint();
    }
  }
}

void TRouteWin::EvLButtonDblClk(UINT modKeys, TPoint& point)
{
  EDevice *In;
  ERoute *R, **R1;
  bool NeedNew;
  int Token, Res;
  TPoint rp = point;
  rp.x += Scroller->XPos*Scroller->XUnit;
  rp.y += Scroller->YPos*Scroller->YUnit;
  if ( !CheckPoint(rp, &In, &R, Token, NeedNew) )
    return;
  if ( !R && Token > RT_INFILTER )
    return;
  int nMidi, i;
/*  if ( LogicOn )
  {
    MessageBox("Stop the logics, before you edit the routes!", "Not yet!" , MB_OK | MB_ICONSTOP);
    return;
  }*/
  DevType DevInTypes[3] = { DTMidiPort, DTMidiFile, DTGis };
  // Datentypen f¸r die Dialoge
  struct TDataR0
  {
    TComboBoxData Type;
    char FileName[FILENAMELENGTH];
    TComboBoxData Device;
    char BendingRange[4];
  } DataR0;
  struct TDataR1
  {
    uint16 Type[4];
    char From[4];
    char To[4];
  } DataR1;
  struct TDataR2
  {
    uint16 nrBox;
    uint16 gmnBox;
    uint16 noBox;
    char boxNr[4];
    uint16 active;
    uint16 passiv;
  } DataR2;
  struct TDataR3
  {
    char From[4];
    char To[4];
    uint16 avoidDrumChannel;
  } DataR3;
  void *Datas[5] = { &DataR0, &DataR1, &DataR2, &DataR3, &DataR0};
  TRouteDialog dia(this, Token, Datas[Token], DE_R0+Token, point.x, point.y);
  switch ( Token )
  {
    case RT_INDEVICE:
      // evtl. neues Device anlegen
      if ( NeedNew )
      {
        In = NewDevice(&InEDevices, DTUnknown, "", 0, 0, In);
        RePaint();
      }
      // ComboBoxen f¸llen
      DataR0.Type.AddString("Midi device");
      DataR0.Type.AddString("Midi file");
      DataR0.Type.AddString("GUIDO file");
#ifdef RTMIDI
      nMidi = rtmidiin->getPortCount();
      if ( nMidi )
      {
        std::string portName;
        for (int i = 0; i < nMidi; i++)
        {
          try {
            portName = rtmidiin->getPortName(i);
            DataR0.Device.AddString(portName.c_str());
          }
          catch (RtError &error) {
            error.printMessage();
            break;
          }
        }
      }
      else
        DataR0.Device.AddString("no device");
#else
      nMidi = midiInGetNumDevs();
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
        DataR0.Device.AddString("no device");
#endif
      DataR0.Type.Select(0);
      DataR0.Device.Select(0);
      DataR0.FileName[0] = 0;
      // fill with datas
      switch ( In->DT )
      {
        case DTGis:
          DataR0.Type.Select(2);
          strcpy(DataR0.FileName, In->Name);
          break;
        case DTMidiPort:
          DataR0.Device.Select(In->DevId);
          break;
        case DTMidiFile:
          DataR0.Type.Select(1);
          strcpy(DataR0.FileName, In->Name);
          break;
      }
      Res = dia.Execute();
      if ( Res == IDOK )
      {
        if ( DataR0.Type.GetSelIndex() == 0 )
          DataR0.Device.GetSelString(DataR0.FileName, FILENAMELENGTH);
        NewDevice(&InEDevices, DevInTypes[DataR0.Type.GetSelIndex()], DataR0.FileName,
          DataR0.Device.GetSelIndex(), In, In);
      }
      else if ( Res == IDR_ERASE01 || (NeedNew && Res == IDCANCEL) )
        NewDevice(&InEDevices, -1, "", 0, In, 0);
      break;
    case RT_INFILTER:
      // evtl. neue Route anlegen
      if ( !R )
        NeedNew = TRUE;
      if ( NeedNew )
      {
        // als Adresse ermitteln
        for (R1 = &In->Routes; *R1; R1 = &((*R1)->Next))
          if ( *R1 == R )
            break;
        R = new ERoute(RTall, 0, 0, -2, 0, 0, 0, 15);
        R->Next = *R1;
        *R1 = R;
        RePaint();
      }
      //
      IsDT = In->DT;
      for (i = 0; i < 4; i++)
        DataR1.Type[i] = ( i == R->Type );
      sprintf(DataR1.From, "%d", R->IFrom);
      sprintf(DataR1.To, "%d", R->ITo);
      Res = dia.Execute();
      if ( Res == IDOK )
      {
        for (i = 0; i < 4; i++)
          if ( DataR1.Type[i] )
            R->Type = i;
        R->IFrom = atoi(DataR1.From);
        R->ITo = atoi(DataR1.To);
      }
      else if ( Res == IDR_ERASE01 || (NeedNew && Res == IDCANCEL) )
        for (R1 = &(In->Routes); *R1; R1 = &((*R1)->Next))
          if ( *R1 == R )
          {
            *R1 = R->Next;
            R->Next = 0;
            break;
          }
      break;
    case RT_BOX:
      DataR2.nrBox = false;
      DataR2.gmnBox = false;
      DataR2.noBox = false;
      strcpy(DataR2.boxNr, "");
      // fill with datas
      if ( R->Box == NoBox )
        DataR2.noBox = true;
      else if ( R->Box == GmnBox )
        DataR2.gmnBox = true;
      else
      {
        DataR2.nrBox = true;
        sprintf(DataR2.boxNr, "%d", R->Box);
      }
      DataR2.active = R->Active;
      DataR2.passiv = !R->Active;
      Res = dia.Execute();
      if ( Res == IDOK )
      {
         if ( DataR2.nrBox )
         {
           char s[10];
           strcpy(s, DataR2.boxNr);
           R->Box = atoi(s);
         }
         if ( DataR2.gmnBox )
           R->Box = GmnBox;
         if ( DataR2.noBox )
         {
           R->Box = NoBox;
           DataR2.active = 0;
         }
         R->Active = DataR2.active;
      }
      break;
    case RT_OUTFILTER:
      sprintf(DataR3.From, "%d", R->OFrom);
      sprintf(DataR3.To, "%d", R->OTo);
      DataR3.avoidDrumChannel = R->ONoDrum;
      Res = dia.Execute();
      if ( Res == IDOK )
      {
        R->OFrom = atoi(DataR3.From);
        R->OTo = atoi(DataR3.To);
        R->ONoDrum = DataR3.avoidDrumChannel;
      }
      break;
    case RT_OUTDEVICE:
      EDevice *Out = R->Out;
      // evtl. neues Device anlegen
      if ( !Out )
      {
        Out = NewDevice(&OutEDevices, DTUnknown, "", 0, 0, 0);
        R->Out = Out;
        RePaint();
        NeedNew = TRUE;
      }
      // ComboBoxen f¸llen
      DataR0.Type.AddString("Midi device");
      DataR0.Type.AddString("Midi file");
      DataR0.Type.AddString("GUIDO file");
#ifdef RTMIDI
      nMidi = rtmidiout->getPortCount();
      if ( nMidi )
      {
        std::string portName;
        for (int i = 0; i < nMidi; i++)
        {
          try {
            portName = rtmidiout->getPortName(i);
            DataR0.Device.AddString(portName.c_str());
          }
          catch (RtError &error) {
            error.printMessage();
            break;
          }
        }
      }
      else
        DataR0.Device.AddString("no device");
#else
      nMidi = midiOutGetNumDevs();
      if ( nMidi )
      {
        for (int i = 0; i < nMidi; i++)
        {
          MIDIOUTCAPS miout;
          midiOutGetDevCaps(i, &miout, sizeof(MIDIOUTCAPS));
          DataR0.Device.AddString(miout.szPname);
        }
      }
      else
        DataR0.Device.AddString("no device");
#endif
      DataR0.Type.Select(0);
      DataR0.Device.Select(0);
      strcpy(DataR0.FileName, "");
      // fill with datas
      switch ( Out->DT )
      {
        case DTGis:
          DataR0.Type.Select(2);
          strcpy(DataR0.FileName, Out->Name);
          break;
        case DTMidiPort:
          DataR0.Device.Select(Out->DevId);
          break;
        case DTMidiFile:
          DataR0.Type.Select(1);
          strcpy(DataR0.FileName, Out->Name);
          break;
      }
      sprintf(DataR0.BendingRange, "%d", Out->BendingRange);
      Res = dia.Execute();
      if ( Res == IDOK )
      {
        if ( DataR0.Type.GetSelIndex() == 0 )
          DataR0.Device.GetSelString(DataR0.FileName, FILENAMELENGTH);
        Out = NewDevice(&OutEDevices, DevInTypes[DataR0.Type.GetSelIndex()], DataR0.FileName,
          DataR0.Device.GetSelIndex(), Out, Out);
        Out->BendingRange = atoi(DataR0.BendingRange);
      }
      else if ( Res == IDR_ERASE01 || (NeedNew && Res == IDCANCEL) )
      {
//        NewDevice(&OutDevices, -1, "", 0, Out, 0); nicht lˆschen, kˆnnte ja noch eine andere Route verwenden
        Out = 0;
      }
      R->Out = Out;
      break;
  }
  // evtl. neu zeichnen
  if ( Res == IDOK || Res == IDR_ERASE01 || NeedNew )
    RePaint();
}

void TRouteWin::EvRButtonDown(uint, TPoint& point)
{
  if ( LogicOn )
    RightButtonMenu(this, point);
}


// ------------------------------------------------------------------
// Mutabor 2.win, 1997, R.Krauße
// Play-Window für MIDI-Wiedergabe
// ------------------------------------------------------------------

#include <windows.h>
#include <owl\slider.h>
#include <owl\slider.rh>
#include <owl\mdi.h>
#include "playwin.h"
#include <math.h>
#include "mutabor.rh"
#include "mdimutch.h"

#ifndef WINVER
//  #define WINVER 0x030A
#endif

#include <mmsystem.h>

#define ID_SCROLL    150         // Scroll bar
#define TIMER_ID     264         // Unique timer ID.
#define MCI_PARM2(p) ((long)(void far*)&p)

#define SM_OPEN	  201     // Open menu
#define SM_EXIT	  202

#define SM_REWIND 301     // Control menu
#define SM_PLAY   302
#define SM_STOP   303



#define PLAY_WINDOW_W 400
#define PLAY_WINDOW_H 100

#define STORE_CARET               \
  TPoint p;                       \
  GetCaretPos(p);

#define RESTORE_CARET             \
  ReposAndPlay(GetPosition());    \
  if ( ActiveWinKind != WK_PLAY ) \
    SetCaretPos(p.x, p.y);


UINT  DeviceId = 0;              // The global Midiform device opened handle
BOOL  FlushNotify = FALSE;

TMDIChild *PlayWin;
char MidiFile[100] = "MIDI.$$$";

//----------------------------------------------------------------------------

class TSoundBar : public THSlider {
  public:
	 TSoundBar(TWindow* parent, int id, int x, int y, int w, int h,
				  TModule* module = 0)
			: THSlider(parent, id, x, y, w, h, IDB_HSLIDERTHUMB, module)
			 { SetBkgndColor(RGB(196, 196, 196)); }

	 void    SetInfo(int ratio, long length);

	 //
	 // Override TScrollBars virtual functions
	 //
	 void    SBLineUp();
	 void    SBLineDown();
	 void    SBPageUp();
	 void    SBPageDown();
	 void    SBThumbPosition(int thumbPos);
	 void    SBTop();
	 void    SBBottom();
    void    SetPosition(int thumbPos);

  private:
	 int     MidiRatio;
	 long    MidiLength;

	 void    ReposAndPlay(long newPos);
};


void
TSoundBar::ReposAndPlay(long newPos)
{
  MCI_PLAY_PARMS    MciPlayParm;
  MCI_SEEK_PARMS    MciSeekParm;
  MCI_SET_PARMS     MciSetParm;
  MCI_OPEN_PARMS    MciOpenParm;
  MCI_GENERIC_PARMS MciGenParm;

  // Only allow SEEK if playing.
  //
  if (!DeviceId)
	  return;

  // Close the currently playing Midi.
  //
  FlushNotify = TRUE;
  MciGenParm.dwCallback = 0;
  mciSendCommand(DeviceId, MCI_STOP, MCI_WAIT, MCI_PARM2(MciGenParm));
  mciSendCommand(DeviceId, MCI_CLOSE, MCI_WAIT, MCI_PARM2(MciGenParm));

  // Open the Midi again and seek to new position.
  //
  MciOpenParm.dwCallback = 0;
  MciOpenParm.wDeviceID = DeviceId;
  #if !defined(__WIN32__)
	 MciOpenParm.wReserved0 = 0;
  #endif
  MciOpenParm.lpstrDeviceType = "sequencer";
  MciOpenParm.lpstrElementName = MidiFile;
  MciOpenParm.lpstrAlias = 0;

  if (mciSendCommand(DeviceId, MCI_OPEN, MCI_WAIT | MCI_OPEN_ELEMENT | MCI_OPEN_TYPE, MCI_PARM2(MciOpenParm))) {
		  MessageBox("Open Error", "Sound Play", MB_OK);
		  return;
	  }
  DeviceId = MciOpenParm.wDeviceID;

  // Our time scale is in MILLISECONDS
  //
  MciSetParm.dwTimeFormat = MCI_FORMAT_MILLISECONDS;
  if (mciSendCommand(DeviceId, MCI_SET, MCI_SET_TIME_FORMAT, MCI_PARM2(MciSetParm))) {
	  MessageBox("Set Time Error", "Sound Play", MB_OK);
	  return;
  }

  // Compute new position, remember the scrollbar range has been scaled based
  // on MidiRatio.
  //
  MciSeekParm.dwCallback = 0;
  MciSeekParm.dwTo = (newPos*MidiRatio > MidiLength) ? MidiLength :
																		 newPos*MidiRatio;
  if (mciSendCommand(DeviceId, MCI_SEEK, MCI_TO, MCI_PARM2(MciSeekParm))) {
	 MessageBox("Seek Error", "Sound Play", MB_OK);
	 return;
  }

///  MciPlayParm.dwCallback = (long)HWindow;
  MciPlayParm.dwCallback = (long)(Parent->HWindow);
  MciPlayParm.dwFrom = 0;
  MciPlayParm.dwTo = 0;
  if (mciSendCommand(DeviceId, MCI_PLAY, MCI_NOTIFY, MCI_PARM2(MciPlayParm))) {
	 MessageBox("Play Error", "Sound Play", MB_OK);
	 return;
  }
}

void
TSoundBar::SetInfo(int ratio, long length)
{
  MidiRatio = ratio;
  MidiLength = length;
}

void
TSoundBar::SBLineUp()
{
  STORE_CARET
  THSlider::SBLineUp();
  RESTORE_CARET
}

void
TSoundBar::SBLineDown()
{
  STORE_CARET
  THSlider::SBLineDown();
  RESTORE_CARET
}

void
TSoundBar::SBPageUp()
{
  STORE_CARET
  THSlider::SBPageUp();
  RESTORE_CARET
}

void
TSoundBar::SBPageDown()
{
  STORE_CARET
  THSlider::SBPageDown();
  RESTORE_CARET
}

void
TSoundBar::SBThumbPosition(int thumbPos)
{
  STORE_CARET
  THSlider::SBThumbPosition(thumbPos);
  RESTORE_CARET
}

void
TSoundBar::SBTop()
{
  STORE_CARET
  THSlider::SBTop();
  RESTORE_CARET
}

void
TSoundBar::SBBottom()
{
  STORE_CARET
  THSlider::SBBottom();
  RESTORE_CARET
}

void TSoundBar::SetPosition(int thumbPos)
{
  STORE_CARET
  THSlider::SetPosition(thumbPos);
  if ( ActiveWinKind != WK_PLAY ) 
    SetCaretPos(p.x, p.y);
}

//----------------------------------------------------------------------------

class TPlayWindow : public TFrameWindow {
  public:
	 TPlayWindow(TWindow* parent, const char far* title, const char far* midiTitle);
	 ~TPlayWindow();
  protected:

	 void        SetupWindow();

	 LRESULT     MciNotify(WPARAM, LPARAM);
    HBRUSH      EvCtlColor(HDC hDC, HWND hWndChild, UINT ctlType);
	 void        EvPaint();
	 void        EvTimer(UINT id);

	 void        CmFileExit();
	 void        CmPlayMidi();
	 void        CmStopMidi();
  public:
	 void        CmFileOpen();

  private:
	 int         Running;
	 int         Pause;
	 UINT        TimeGoing;
	 int         MidiRatio;
	 long        MidiLength;
    char        MidiTitle[100];
	 TSoundBar*  SoundBar;

	 MCI_GENERIC_PARMS MciGenParm;
	 MCI_OPEN_PARMS    MciOpenParm;
	 MCI_PLAY_PARMS    MciPlayParm;
	 MCI_STATUS_PARMS  MciStatusParm;
	 MCI_SET_PARMS     MciSetParm;

	 void        GetDeviceInfo();
	 void        StopMidi();
	 void        StopMCI();

    virtual bool CanClose();

  DECLARE_RESPONSE_TABLE(TPlayWindow);
};

DEFINE_RESPONSE_TABLE1(TPlayWindow, TFrameWindow)
  EV_MESSAGE(MM_MCINOTIFY, MciNotify),
  EV_WM_PAINT,
  EV_WM_CTLCOLOR,
  EV_COMMAND(SM_OPEN, CmFileOpen),
  EV_COMMAND(SM_EXIT, CmFileExit),
  EV_COMMAND(SM_PLAY, CmPlayMidi),
  EV_COMMAND(SM_STOP, CmStopMidi),
  EV_WM_TIMER,
END_RESPONSE_TABLE;


TPlayWindow::TPlayWindow(TWindow* parent, const char far* title, const char far* midiTitle)
  : TFrameWindow(parent, title)
{
  Attr.Style |= WS_CHILD | WS_VISIBLE | WS_THICKFRAME;
  Running = 0;
  Pause = 0;
  MidiLength = MidiRatio = 0;
  strcpy(MidiTitle, midiTitle);

  SoundBar = new TSoundBar(this, ID_SCROLL, 50, 40, 300, 40);

  SetBkgndColor(RGB(196, 196, 196));
}

void
TPlayWindow::SetupWindow()
{
  TFrameWindow::SetupWindow();
  SoundBar->SetRange(0, 0);
  SoundBar->SetRuler(0);
  CmFileOpen();
}

TPlayWindow::~TPlayWindow()
{
  StopMCI();
}

HBRUSH TPlayWindow::EvCtlColor(HDC hDC, HWND hWndChild, UINT ctlType)
{
  switch (ctlType) {
	 case CTLCOLOR_STATIC:
		SetBkColor(hDC, RGB(196, 196, 196));
		return (HBRUSH)GetStockObject(NULL_BRUSH);
/*	 case CTLCOLOR_BTN:
		SetBkMode(hDC, TRANSPARENT);
		return (HBRUSH)GetStockObject(NULL_BRUSH); */
	 default:
		return TFrameWindow::EvCtlColor(hDC, hWndChild, ctlType);
  }
}

//
// EvPaint member function responds to WM_PAINT messages
//
void
TPlayWindow::EvPaint()
{
  TPaintDC paintDC(HWindow);
  paintDC.SetBkColor(RGB(196, 196, 196));

  // TMidi-Titel
  paintDC.TextOut(5, 5, MidiTitle);
  // ZeitSkala
  if ( MidiLength < 60000 )
    paintDC.TextOut(160, 20, "Seconds:", 8);
  else
    paintDC.TextOut(160, 20, "Minutes:", 8);
  paintDC.TextOut(50, 22, "0", 1);
  char buffer[10];
  if ( !MidiLength )
	 strcpy(buffer, "Unknown");
  if ( MidiLength < 60000 )
	 wsprintf(buffer, "%ld.%02ld", MidiLength/1000, (MidiLength%1000)/10);
  else
	 wsprintf(buffer, "%ld:%02ld.%02ld",
      MidiLength/60000,
      (MidiLength%60000)/1000,
      (MidiLength%1000)/10);
  paintDC.TextOut(315, 22, buffer, strlen(buffer));
}

void
TPlayWindow::GetDeviceInfo()
{
  MIDIOUTCAPS MidiOutCaps;

  if (!midiOutGetDevCaps(DeviceId, &MidiOutCaps, sizeof(MidiOutCaps))) {
	 MessageBox("GetDevCaps Error", "Play Midi", MB_OK);
	 return;
  }
}

//
// Play the Midi...
//
void
TPlayWindow::CmPlayMidi()
{
  if (!Running) {
	 //
	 // MCI APIs to open a device and play a .WAV file, using
	 // notification to close
	 //
	 memset(&MciOpenParm, 0, sizeof MciOpenParm);

	 MciOpenParm.lpstrElementName = MidiFile;
	 MciOpenParm.lpstrDeviceType = "sequencer";

	 if (mciSendCommand(0, MCI_OPEN, MCI_WAIT | MCI_OPEN_ELEMENT | MCI_OPEN_TYPE,
							  MCI_PARM2(MciOpenParm))) {
		MessageBox(
			"Open Error - could not open output device.",
			"Sound Play", MB_OK);
		  return;
	 }
	 DeviceId = MciOpenParm.wDeviceID;

	 // The time format in this demo is in Samples.
	 //
	 MciSetParm.dwCallback = 0;
	 MciSetParm.dwTimeFormat = MCI_FORMAT_MILLISECONDS;
	 if (mciSendCommand(DeviceId, MCI_SET, MCI_SET_TIME_FORMAT, MCI_PARM2(MciSetParm))) {
		MessageBox("SetTime Error", "Sound Play", MB_OK);
		return;
	 }

	 MciPlayParm.dwCallback = (long)HWindow;
	 MciPlayParm.dwFrom = 0;
	 MciPlayParm.dwTo = 0;
	 mciSendCommand(DeviceId, MCI_PLAY, MCI_NOTIFY, MCI_PARM2(MciPlayParm));

	 // Modify the menu to toggle PLAY to STOP, and enable PAUSE.
	 //
///    TMenu menu(HWindow);
///    menu.ModifyMenu(SM_PLAY, MF_STRING, SM_PLAY, "P&ause\tCtrl+A");
///    menu.EnableMenuItem(SM_STOP, MF_ENABLED);

	 // Make sure the Play/Stop toggle menu knows we're Running.
	 //
	 Running = TRUE;

	 // Start a timer to show our progress through the Midiform file.
	 //
	 TimeGoing = SetTimer(TIMER_ID, 200, 0);

  } else {
	 if (!Pause) {
		// Pause the playing.
		//
		MciGenParm.dwCallback = 0;
		mciSendCommand(DeviceId, MCI_PAUSE, MCI_WAIT, MCI_PARM2(MciGenParm));

		// Toggle Pause menu to Resume.
		//
///      TMenu menu(HWindow);
///      menu.ModifyMenu(SM_PLAY, MF_STRING, SM_PLAY, "&Play\tCtrl+P");
///      Pause = TRUE;

	 } else {
		// Resume the playing.
		//
		MciGenParm.dwCallback = 0;
		mciSendCommand(DeviceId, MCI_RESUME, MCI_WAIT, MCI_PARM2(MciGenParm));

		// Toggle Resume menu to Pause.
		//
///      TMenu menu(HWindow);
///      menu.ModifyMenu(SM_PLAY, MF_STRING, SM_PLAY, "P&ause\tCtrl+A");
///      Pause = FALSE;
	 }
  }
}

void
TPlayWindow::CmStopMidi()
{
  StopMidi();
}

void
TPlayWindow::StopMCI()
{
  if (TimeGoing)       // if Timer is Running, then kill it now.
	 TimeGoing = !KillTimer(TIMER_ID);

  // Stop playing the Midiform file and close the Midiform device.
  //
  MciGenParm.dwCallback = 0;
  mciSendCommand(DeviceId, MCI_STOP, MCI_WAIT, MCI_PARM2(MciGenParm));
  mciSendCommand(DeviceId, MCI_CLOSE, MCI_WAIT,MCI_PARM2(MciGenParm));

  Running = FALSE;
  DeviceId = 0;
}

//
// Reset the menus to Play menu and gray the Pause menu.
//
void
TPlayWindow::StopMidi()
{
  if (DeviceId) {
	 StopMCI();
///    TMenu menu(HWindow);
///    menu.ModifyMenu(SM_PLAY, MF_STRING, SM_PLAY, "&Play\tCtrl+P");
  }
}

void
TPlayWindow::CmFileOpen()
{
	MidiLength = 0;
		MidiRatio = 0;
		SoundBar->SetPosition(0);
		Invalidate();
  CmPlayMidi();
}

void
TPlayWindow::CmFileExit()
{
  CloseWindow();
}

//
// Response function MM_MCINOTIFY message when MCI_PLAY is complete.
//
LRESULT
TPlayWindow::MciNotify(WPARAM, LPARAM)
{
  if (!FlushNotify)   // Internal STOP/CLOSE, from thumb re-pos?
  {
	 StopMidi();

	 // Make sure the thumb is at the end. There could be some WM_TIMER
	 // messages on the queue when we kill it, thereby flushing WM_TIMER's
	 // from the message queue.
	 //
	 int   loVal, hiVal;
	 SoundBar->GetRange(loVal, hiVal);
	 SoundBar->SetPosition(hiVal);
	 Parent->PostMessage(WM_COMMAND, CM_MIDISTOP);
///	 Parent->PostMessage(WM_COMMAND, WM_CLOSE);
  }
  else
	 FlushNotify = FALSE;          // Yes, so ignore the close.
  return 0;
}

void
TPlayWindow::EvTimer(UINT)
{
  if (!FlushNotify) {               // Internal STOP/CLOSE, from thumb re-pos?
	 MciStatusParm.dwCallback = 0;   // No, normal close.
	 MciStatusParm.dwItem = MCI_STATUS_LENGTH;
	 mciSendCommand (DeviceId, MCI_STATUS, MCI_STATUS_ITEM, MCI_PARM2(MciStatusParm));

	 if (MidiLength != MciStatusParm.dwReturn) {
		Invalidate();  // First time it's different update the scrollbar nums
		MidiLength = MciStatusParm.dwReturn;
	 }

	 // Compute the length and ratio and update SoundBar info.
	 //
	 MidiRatio = int((MidiLength + 16000/2) / 16000);
	 if (!MidiRatio)
		MidiRatio = 1;

	 SoundBar->SetInfo(MidiRatio, MidiLength);
	 SoundBar->SetRange(0, int(MidiLength / MidiRatio));
	 SoundBar->SetRuler(int((MidiLength / MidiRatio) / 10));

	 // Update the current position.
	 //
	 MciStatusParm.dwCallback = 0;
	 MciStatusParm.dwItem = MCI_STATUS_POSITION;
	 mciSendCommand(DeviceId, MCI_STATUS, MCI_STATUS_ITEM, MCI_PARM2(MciStatusParm));

	 SoundBar->SetPosition(int(MciStatusParm.dwReturn / MidiRatio));
  }

  FlushNotify = FALSE;          // Yes, ignore this close.
}

bool TPlayWindow::CanClose()
{
  StopMidi();
  return true;
}

// ------------------------------------------------------------------

class TMDIPlayChild : public TMDIMutChild
{
  public:
    TMDIPlayChild(TMDIClient *parent, const char far *title, TWindow *client);
  protected:
    void EvGetMinMaxInfo(MINMAXINFO far& mminfo);
  DECLARE_RESPONSE_TABLE(TMDIPlayChild);
};

DEFINE_RESPONSE_TABLE1(TMDIPlayChild, TMDIMutChild)
  EV_WM_GETMINMAXINFO,
END_RESPONSE_TABLE;


TMDIPlayChild::TMDIPlayChild(TMDIClient *parent, const char far *title, TWindow *client)
 : TMDIMutChild(WK_PLAY, *parent, title, client)
{
  Attr.Style &= ~WS_MAXIMIZEBOX & ~WS_MINIMIZEBOX & ~WS_SYSMENU;
  TRect R = parent->GetClientRect();
  if ( R.right > PLAY_WINDOW_W )
    Attr.X = R.left + R.right - PLAY_WINDOW_W;
  Attr.Y = R.top;
  Attr.W = PLAY_WINDOW_W;
  Attr.H = PLAY_WINDOW_H;
}

void
TMDIPlayChild::EvGetMinMaxInfo(MINMAXINFO far& mminfo)
{
  mminfo.ptMinTrackSize.x = PLAY_WINDOW_W;
  mminfo.ptMinTrackSize.y = PLAY_WINDOW_H;
  mminfo.ptMaxTrackSize.x = PLAY_WINDOW_W;
  mminfo.ptMaxTrackSize.y = PLAY_WINDOW_H;
}

// ------------------------------------------------------------------

TMDIChild *newPlayWin(TMDIClient* parent, const char far* title, const char far* midiTitle)
{
  PlayWin = new TMDIPlayChild(parent, title, new TPlayWindow(parent, title, midiTitle));
  PlayWin->Create();
  return PlayWin;
}


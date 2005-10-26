// TGrayDialog ------------------------------------------------------
// auf dem Bildschirm zentrierter Dialog mit grauem Hintergrund

#include "Gray.h"
#include "Mutabor.rh"
#include "diahlp.h"

#define H_TASKBAR 35

const char HlpFile[] = "MUTABOR.HLP";

DEFINE_RESPONSE_TABLE1(TGrayDialog, TDialog)
  EV_COMMAND(CM_HELPCOMMON, CmHelpCommon),
  EV_COMMAND(IDHELP_, CmHelpCommon),
  EV_COMMAND(IDR_ERASE01, CmErase),
  EV_COMMAND(IDR_ERASE02, CmErase),
//  EV_WM_CTLCOLOR,
END_RESPONSE_TABLE;

TGrayDialog::TGrayDialog(TWindow* parent, TResId resId, int helpNr, int x, int y, TModule* module)
 : TDialog(parent, resId, module)
{
//  SetBkgndColor(RGB(196, 196, 196));
  HelpNr = helpNr;
  X = x;
  Y = y;
//TW  Attr.AccelTable = IDA_GRAYDIALOG;
}

void TGrayDialog::SetupWindow()
{
  TDialog::SetupWindow();

  HWND desk = GetDesktopWindow();
  if ( desk )
  {
	   TRect R;
	   ::GetClientRect(desk, &R);
    if ( Y == -1 )
    {
      TWindow::Attr.X = (R.right - TWindow::Attr.W) / 2;
	     TWindow::Attr.Y = (R.bottom - TWindow::Attr.H) / 2;
    }
    else
    {
      TPoint p = TPoint(X,Y);
      Parent->ClientToScreen(p);
      TWindow::Attr.X = p.x +10;
	     TWindow::Attr.Y = p.y + 10;
    }
    if ( TWindow::Attr.X+TWindow::Attr.W > R.right )
      TWindow::Attr.X = R.right-TWindow::Attr.W;
    if ( TWindow::Attr.Y+TWindow::Attr.H+H_TASKBAR > R.bottom )
      TWindow::Attr.Y = R.bottom-TWindow::Attr.H-H_TASKBAR;
    if ( TWindow::Attr.X < 0 )
      TWindow::Attr.X = 0;
    if ( TWindow::Attr.Y < 0 )
      TWindow::Attr.Y = 0;
  }
  MoveWindow(TWindow::Attr.X, TWindow::Attr.Y,
  	 TWindow::Attr.W, TWindow::Attr.H, false);
}

void TGrayDialog::CmHelpCommon()
{
  WinHelp(HlpFile, HELP_CONTEXT, HelpNr);
}

void TGrayDialog::CmErase()
{
  CloseWindow(IDR_ERASE01);
}
/*
HBRUSH TGrayDialog::EvCtlColor(HDC hDC, HWND hWndChild, UINT ctlType)
{
  switch (ctlType)
  {
	   case CTLCOLOR_STATIC:
		    SetBkColor(hDC, RGB(196, 196, 196));
		    return (HBRUSH)GetStockObject(NULL_BRUSH);
	   case CTLCOLOR_BTN:
		    SetBkMode(hDC, TRANSPARENT);
	    	return (HBRUSH)GetStockObject(NULL_BRUSH);
	   default:
		    return TDialog::EvCtlColor(hDC, hWndChild, ctlType);
  }
}
*/
bool TGrayDialog::DialogFunction(UINT uMsg, WPARAM wParam,  LPARAM lParam)
{

	// Create an array of control identifiers and context identifiers.

const DWORD aHelpIDs[]=
{
	CM_ROUTELOAD,	IDH_106_115,	// Mutabor-Box: "Mode" (Button)
	CM_ROUTESAVE,	IDH_107_116,	// Output filter: "Channel" (Button)
	CM_INDEVPAUSE,	IDH_104_120,	// Input device: "" (Edit)
	121,	IDH_104_121,	// Input device: "" (Edit)
	122,	IDH_105_122,	// Input filter: "" (Edit)
	CM_HELPINDEX,	IDH_105_123,	// Input filter: "" (Edit)
	IDM_EDITFILE_DOC,	IDH_105_100,	// Input filter: "all" (Button)
	CM_HELPONHELP,	IDH_106_124,	// Mutabor-Box: "" (Edit)
//9	IDC_STATICBITMAP1,	IDH_105_101,	// Input filter: "else" (Button)
	IDR_EDIT31,	IDH_107_125,	// Output filter: "" (Edit)
	IDR_EDIT32,	IDH_107_126,	// Output filter: "" (Edit)
	CM_EXECUTE,	IDH_105_102,	// Input filter: "channel" (Button)
	IDA_ROUTE,	IDH_105_103,	// Input filter: "staff" (Button)
	150,	IDH_104_150,	// Input device: "Löschen" (Button)
	CM_COMPILE,	IDH_106_104,	// Mutabor-Box: "box number" (Button)
	151,	IDH_105_151,	// Input filter: "Löschen" (Button)
	CM_ACTIVATE,	IDH_106_105,	// Mutabor-Box: "GUIDO-File" (Button)
	152,	IDH_104_152,	// Input device: "Durchsuchen" (Button)
	CM_STOP,	IDH_106_106,	// Mutabor-Box: "no Box / thru-mode" (Button)
	CM_HELPCONTEXT,	IDH_104_130,	// Input device: "" (ComboBox)
	CM_PANIC,	IDH_106_107,	// Mutabor-Box: "active" (Button)
	CM_OWM,	IDH_106_108,	// Mutabor-Box: "passive" (Button)
	155,	IDH_101_155,	// Setup: "Windows" (Button)
	IDSD_RADIOTS1,	IDH_101_156,	// Setup: "  as &tone system " (Button)
	CM_TOGGLETS,	IDH_104_110,	// Input device: "Type" (Button)
	IDSD_RADIOTS2,	IDH_101_157,	// Setup: "  as &relations  " (Button)
	CM_TOGGLEACT,	IDH_104_111,	// Input device: "I" (Button)
	IDSD_CHECKSE,	IDH_101_158,	// Setup: " save &editorfiles " (Button)
	CM_CAW,	IDH_105_112,	// Input filter: "Type" (Button)
	159,	IDH_101_159,	// Setup: "Tone system" (Button)
	CM_SETUP,	IDH_105_113,	// Input filter: "Range" (Button)
	IDSD_CHECKCB,	IDH_101_160,	// Setup: " use color bars" (Button)
	114,	IDH_106_114,	// Mutabor-Box: "Box" (Button)
//  IDR_EDIT31, IDR_EDIT31_H,
//  IDR_EDIT32, IDR_EDIT32_H,
  IDR_CHECKBOX31, IDR_CHECKBOX31_H,
	0, 0
};

	switch (uMsg) {
    case WM_HELP:
        ::WinHelp((HWND)(((LPHELPINFO) lParam)->hItemHandle), HlpFile,
            HELP_WM_HELP, (DWORD) (LPSTR) aHelpIDs);

        break;
	    case WM_CONTEXTMENU:
	        ::WinHelp((HWND) wParam, HlpFile, HELP_CONTEXTMENU,
	            (DWORD) (LPVOID) aHelpIDs);
	        break;
      default:
         return TDialog::DialogFunction(uMsg, wParam, lParam);
	}

	return FALSE;
}

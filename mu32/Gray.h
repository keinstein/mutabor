#ifndef GRAY_H
#define GRAY_H

#include <owl/pch.h>


// TGrayDialog ------------------------------------------------------
// auf dem Bildschirm zentrierter Dialog mit grauem Hintergrund

class TGrayDialog : public TDialog
{
  public:
    TGrayDialog(TWindow* parent, TResId resId, int helpNr, int x = -1, int y = -1, TModule* module = 0);
    void SetupWindow();
  protected:
    int HelpNr, X, Y;
    TPoint Point;
    void CmHelpCommon();
    void CmErase();
//    HBRUSH EvCtlColor(HDC, HWND hWndChild, UINT ctlType);
    virtual bool DialogFunction(UINT uMsg, WPARAM wParam,  LPARAM lParam);
	  DECLARE_RESPONSE_TABLE(TGrayDialog);
};

// TGraySetupDialog -----------------------------------------------------

class TGraySetupDialog : public TGrayDialog
{
  public:
    TGraySetupDialog(TWindow* parent, TResId resId, void *buf, int helpNr, int x = -1, int y = -1)
    : TGrayDialog(parent, resId, helpNr, x, y)
  	{
      SetTransferBuffer(buf);
      TransferData(tdSetData);
    };
  	void CmOk()
	  {
	   	TransferData(tdGetData);
	    TDialog::CmOk();
  	}
};

#endif

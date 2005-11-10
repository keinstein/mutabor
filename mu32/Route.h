// ------------------------------------------------------------------
// Mutabor 3, 1998, R.Krauﬂe
// Routenfenster Klasse
// ------------------------------------------------------------------

#ifndef ROUTE_H
#define ROUTE_H

#include <owl/OPENSAVE.H>
#include "EDevice.h"

#define xz 5 // Zwischenr‰ume
#define yz 5

// TRouteWin ----------------------------------------------------------
// Fenster, das die Routen enth‰lt

class TRouteWin : public TWindow
{
  public:
	  TRouteWin(TWindow *parent, TModule *module);
    void RePaint();
    int FocusPos[2];
  private:
	  char FileName[200];
    int nTags;
    int x1, x2, x3, x4, x5;
    TIcon *DevIcon[4];
    TBitmap *ConIcon[4];
    TIcon *PlopIcon[4];
  protected:
    virtual void SetupWindow();
    virtual bool CanClose();
	  virtual void EvChar(uint key, uint repeatCount, uint flags);
	  void EvSize(uint sizeType, TSize &size);
    virtual void Paint(TDC& dc, bool erase, TRect& rect);
	  void CorrectScroller();
    void SetFocusPos();
    int CalcXl() { return x1+x2+x3+x4+x5+10*xz; }
    int CalcYl();
    bool CheckPoint(TPoint point, EDevice **in, ERoute **r, int &token, bool &needNew);
    void EvLButtonDown(UINT modKeys, TPoint& point);
    void EvLButtonDblClk(UINT modKeys, TPoint& point);
    void EvRButtonDown(uint modKeys, TPoint& point);
	 DECLARE_RESPONSE_TABLE(TRouteWin);
};

extern bool LogicOn;
extern TOpenSaveDialog::TData MidiFileData;
extern TOpenSaveDialog::TData GmnFileData;
TColor BoxColor(int nr);

#endif


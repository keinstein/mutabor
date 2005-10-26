/////////////////////////////////////////////////////////////////////////////
// Name:        MutTextBox.h
// Purpose:     Textbox for Lists
// Author:      R. Krauﬂe
// Modified by:
// Created:     01.09.05
// Copyright:   (c) R. Krauﬂe
// Licence:     wxWindows license
/////////////////////////////////////////////////////////////////////////////

#ifndef MUTTEXTBOX_H
#define MUTTEXTBOX_H

#include <wx/textctrl.h>
#include "MutChild.h"

class MutTextBox : public wxTextCtrl {
  public:
	MutTextBox(wxWindow* parent = NULL, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize);
	void NewText(char *s, bool newTitle = false);
//    TControl *ColorBar1, *ColorBar2;
	int ColorBox;
	void OnClose(wxCloseEvent& event);
  protected:
/*	  void EvSize(uint sizeType, TSize &size);
	  void EvChar(uint key, uint repeatCount, uint flags);
	void EvSetFocus(HWND hWndLostFocus);
	void EvRButtonDown(uint modKeys, TPoint& point);*/
	int Box() { return PARENT_BOX; }
	DECLARE_EVENT_TABLE()
};

#endif
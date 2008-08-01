// -*- C++ -*-
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

#include <wx/listbox.h>
#include "Global.h"
// #include "MutChild.h"

enum WinKind { WK_KEY = 0, WK_TS, WK_ACT, WK_LOGIC, WK_ROUTE, WK_EDIT, WK_NULL };

inline WinKind operator++(WinKind & k)
{ return k = WinKind(int(k) + 1); }

inline WinKind operator++(WinKind & k,int)
{ WinKind l=k; ++k; return l; }


class WinAttr
{
 public:
  wxWindow * Win;  // 0 = nicht offen
  char Wanted;   // 0 = nicht wanted
  //  int X, Y, W, H;     // W = 0 ... noch nicht benutzt, d.h. undefiniert
  int Box;
  WinAttr(char wanted = 0, int box = -1) {
    Wanted = wanted;
    Box = box;
    //      X = Y = H = W = 0;
    Win = NULL;
  }
};

WX_DECLARE_OBJARRAY(WinAttr, ArrayOfWinAttr);


class MutTextBox : public wxListBox {
protected:
  WinKind winKind;
  WinAttr *winAttr;
public:
  MutTextBox(  WinKind k,
	       WinAttr *a, 
	       wxWindow* parent = NULL, 
	     wxWindowID id=-1, 
	     const wxPoint& pos = wxDefaultPosition, 
	     const wxSize& size = wxDefaultSize);
  void NewText(char *s, bool newTitle = false);
  void NewText(wxString s, bool newTitle = false);
  int ColorBox;
  void OnClose(wxCloseEvent& event);
  WinKind GetKind() { return winKind; }
protected:
  int Box() { return winAttr->Box; }
	DECLARE_EVENT_TABLE()
};

#endif

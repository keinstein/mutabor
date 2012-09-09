/** \file 
 ********************************************************************
 * Textbox for Lists
 *
 * Copyright:   (c) 2008 TU Dresden
 * \author   R. Krauﬂe
 * Tobias Schlemmer <keinstein@users.berlios.de>
 * \date 2005/08/12
 * $Date: 2011/11/02 14:31:59 $
 * \version $Revision: 1.22 $
 * \license GPL
 *
 *
 *
 ********************************************************************
 * \addtogroup src/wxGUI
 * \{
 ********************************************************************/


// ===========================================================================
// declarations
// ===========================================================================

// ---------------------------------------------------------------------------
// headers
// ---------------------------------------------------------------------------

#include "src/kernel/Defs.h"

#include <iostream>

#include "wx/tokenzr.h"

#include "src/wxGUI/MutTextBox.h"
#include "src/wxGUI/MutFrame.h"
#include "src/wxGUI/GUIBoxData.h"
#include "src/wxGUI/Routing/BoxShape.h"
#include "src/kernel/routing/Route-inlines.h"
#include "src/kernel/GrafKern.h"
#include "src/kernel/MidiKern.h"
#include "src/wxGUI/Action.h"


#ifdef __BORLANDC__
#pragma hdrstop
#endif

using mutaborGUI::BoxData;
using namespace mutaborGUI;

wxString TextBoxTitle[] =
        { N_("Current keys"), N_("Tone system"), N_("Actions") };
// needs wxGetTranslation();

BEGIN_EVENT_TABLE(MutTextBox, wxListBox)
        EVT_MENU(CM_UPDATEUI, MutTextBox::UpdateUI)
	EVT_CLOSE(MutTextBox::OnClose)
END_EVENT_TABLE()

wxString ListInit[1] = { _("<init>") };

MutTextBox::MutTextBox(WinKind k,
                       int boxId,
                       wxWindow* parent,
                       wxWindowID id,

                       const wxPoint& pos,
                       const wxSize& size):
		wxListBox(parent, id, pos, size, 1, ListInit),
		winKind(k),
		box(boxId)
{
	DEBUGLOG (other, _T(""));
	SetBackgroundStyle(wxBG_STYLE_COLOUR);
//	SetBackgroundColour(*wxWHITE);
	SetForegroundColour(BoxTextColour(box));
	SetBackgroundColour(BoxColour(box));
}


void MutTextBox::OnClose(wxCloseEvent& event)

{
	mutUnused(event);
	mutASSERT(WK_KEY <= winKind && winKind < WK_NULL);
	DEBUGLOG (other, _T("winKind: %d"), winKind);
        BoxData & boxdata = BoxData::GetBox(box);
	if ( LogicOn ) {
                switch (winKind) {
                case WK_KEY: 
                        boxdata.WantKeyWindow(false);
                        break;
                case WK_TS: 
                        boxdata.WantTonesystemWindow(false);
                        break;
                case WK_ACT: 
                        boxdata.WantActionsWindow(false);
                        break;
                case WK_LOGIC:
                        wxLogWarning(_("Unexpected value: WK_LOGIC"));
			UNREACHABLEC;
                        break;
                case WK_ROUTE:
                        wxLogWarning(_("Unexpected value: WK_ROUTE"));
			UNREACHABLEC;
                        break;
                case WK_EDIT:
                        wxLogWarning(_("Unexpected value: WK_EDIT"));
			UNREACHABLEC;
                        break;
                case WK_NULL:
                        wxLogWarning(_("Unexpected value: WK_NULL"));
			UNREACHABLEC;
                        break;
                default:
                        wxLogError(_("Unexpected window kind: %d"), winKind);
			UNREACHABLEC;
                }
        } 
        Destroy();
}


// Updaten
void MutTextBox::UpdateUI(wxCommandEvent& WXUNUSED(event)) 
{
               switch (winKind) {
                case WK_KEY: 
                        GetKeys(asTS);
                        break;
                case WK_TS: 
                        GetToneSystem(asTS);
                        break;
                case WK_ACT:
                        TakeOverActions();
                        if (CAW) {
                                GetAllActions();
                        } else {
                                GetBoxActions();
                        }
                        break;
                case WK_LOGIC:
                        wxLogWarning(_("Unexpected value: WK_LOGIC"));
			UNREACHABLEC;
                        break;
                case WK_ROUTE:
                        wxLogWarning(_("Unexpected value: WK_ROUTE"));
			UNREACHABLEC;
                        break;
                case WK_EDIT:
                        wxLogWarning(_("Unexpected value: WK_EDIT"));
			UNREACHABLEC;
                        break;
                case WK_NULL:
                        wxLogWarning(_("Unexpected value: WK_NULL"));
			UNREACHABLEC;
                        break;
                default:
                        wxLogError(_("Unexpected window kind: %d"), winKind);
			UNREACHABLEC;
                }        
}


static inline long get_frequency (long key, tone_system * tonesys) {
	if (!tonesys) return 0;
	long retval = tonesys->ton[GET_INDEX(key,tonesys)];
	if (!retval)  return 0;
	return ((long) tonesys->periode) * GET_ABSTAND(key,tonesys)  + retval;
}

void MutTextBox::GetKeys(bool asTS) 
{
	wxString keys;
	
	mutabor_box_type * b = BoxData::GetBox(box).GetNonGUIBox();
	if (b == NULL || !b) return;
	Clear();
	
	if (!b->key_count) return;
	tone_system * tonsys = b->tonesystem;

	for (mutabor_key_type * key = mutabor_find_key_in_box(b,0), 
		     * last_key = key;
	     key != NULL; 
	     key = mutabor_find_key_in_box(b,key->next)) {

		int lt = key->number;
		long freq;
		double cents;
		
		if ( (freq=get_frequency( lt ,tonsys ))!=0) {
			if (asTS) {
				cents = LONG_TO_CENT(freq);
			} else {
				int last_lt = last_key->number;
				long delta = freq -  get_frequency(last_lt, tonsys); 
				cents = LONG_TO_CENT(freq);
				last_key = key;

			}
			keys.Printf(_("%2d : %8.1f Hz (%6.2lf HT) [ch: %d]"),
				    lt,
				    LONG_TO_HERTZ(freq),
				    cents,
				    mutabor::GetChannel(box, lt));
		} else {
			keys.Printf(_("%2d : empty"),lt);
		}
		Append(keys);
	}
}

void MutTextBox::GetToneSystem(bool asTS) 
{
	wxString keys;
	
	mutabor_box_type * b = BoxData::GetBox(box).GetNonGUIBox();
	if (b == NULL || !b) return;

	tone_system * tonsys = b->tonesystem;
	if (!tonsys || tonsys == NULL) return;

	Clear();
		

	keys.Printf(_("Anchor = %d"),tonsys->anker);
	Append(keys);
	keys.Printf(_("Width = %d"),tonsys->breite);
	Append(keys);
	keys.Printf(_("Period = %.1f HT"),
		    LONG_TO_CENT(tonsys->periode));
	Append(keys);

	
	size_t i = 0;
	for (;i<tonsys->breite && tonsys->ton[i]==0;i++);
	if (!asTS) {
		keys.Printf(_("Reference = %d"),i);
		Append(keys);
	}
	
	long freq, ref = tonsys->ton[i];

	for (int i=0;i<tonsys->breite;i++) {
		if ( (freq=tonsys->ton[i])!=0) {
			if (!asTS) freq -= ref;
			keys.Printf(_("%2d : %8.1f Hz (%6.2lf HT)"),
				    i, 
				    LONG_TO_HERTZ(tonsys->ton[i]) ,
				    LONG_TO_CENT(freq) );
		} else {
			keys.Printf(_("%2d : empty"),i);
		}
		Append(keys);
	}
}

void MutTextBox::GetAllActions () 
{
	/** \todo write this code */
	NewText(GenerateCAWString());
}

void MutTextBox::GetBoxActions() 
{
	/** \todo write this code */
	NewText(GenerateACTString(box));
}

void MutTextBox::NewText(char *s, bool newTitle)
{
	mutASSERT(WK_KEY <= winKind && winKind < WK_NULL);
	DEBUGLOG (other, _T(""));
	// Text in Liste
	Clear();
	char s1[2000];
	int i = 0, j = 0;

	while ( s[i] ) {
		if ( s[i] == '\r' || s[i] == '\n' ) {
			s1[j] = 0;

			if ( j )
				Append(wxString(muT(s1)));

			j = 0;

			i++;
		} else
			s1[j++] = s[i++];
	}

	s1[j] = 0;

	if ( j )
		Append(wxString(muT(s1)));

	// Scrollen, falls Aktion-Window
	if ( winKind == WK_ACT )
		SetSelection(GetCount()-1);

	// Farbbalken ggf. korrigieren
	/*  if ( GetTopIndex() == 0 && PARENT_KIND != WK_ACT )
	  {
	    ColorBar1->MoveWindow(1, 1, 1000, 1, true);
	    ColorBar2->MoveWindow(1, 1, 1, 1000, true);
	  }*/
}

void MutTextBox::NewText(const wxString &s, bool newTitle)
{
	DEBUGLOG (other, _T("s=%s; newTitle=%d; winKind=%d"),s.c_str(),newTitle,winKind);
	mutASSERT(WK_KEY <= winKind && winKind < WK_NULL);

	Freeze();
	// Text in Liste
	Clear();

	wxStringTokenizer tokenizer(s,_T("\r\n"));

	while (tokenizer.HasMoreTokens())
		Append(tokenizer.GetNextToken());
	Thaw();


	// Scrollen, falls Aktion-Window
	if ( winKind == WK_ACT )
		SetSelection(GetCount()-1);

	// Farbbalken ggf. korrigieren
	/*  if ( GetTopIndex() == 0 && PARENT_KIND != WK_ACT )
	  {
	    ColorBar1->MoveWindow(1, 1, 1000, 1, true);
	    ColorBar2->MoveWindow(1, 1, 1, 1000, true);
	  }*/
}


wxString MutTextBox::MakeTitle() const {
	if (winKind == WK_ACT && CAW) {
		return _("Actions - all boxes");
	} else {
		return wxString::Format(wxGetTranslation(_("%s - Box %d")),
					(const wxChar *)wxGetTranslation(TextBoxTitle[winKind]),
					box);
	}
}


/*wx void MutTextBox::EvSize(uint sizeType, TSize &size)
{
  TListBox::EvSize(sizeType, size);
  TRect R = GetWindowRect();
  TRect RC = ColorBar1->GetWindowRect();
  if ( GetTopIndex() == 0 )
  {
    ColorBar1->MoveWindow(1, 1, 1000, 1, true);
    ColorBar2->MoveWindow(1, 1, 1, 1000, true);
  }
}
*/

/*wx void MutTextBox::EvChar(uint key, uint repeatCount, uint flags)
{
  TListBox::EvChar(key, repeatCount, flags);
  if ( 'A' <= key && key <= 'z' || key == VK_TAB
       || key == VK_UP || key == VK_DOWN
       || key == VK_LEFT || key == VK_RIGHT )
  {
    pubTaste = key;
    if ( IsOpen(WK_LOGIC, Box()) )
      GetWinAttr(WK_LOGIC, Box())->Win->SendMessage(WM_COMMAND, CM_TASTE);
    else
      KeyboardAnalyseSimple(Box(), key);
  }
}*/

/*wx void MutTextBox::EvSetFocus(HWND hWndLostFocus)
{
  TListBox::EvSetFocus(hWndLostFocus);
}

void
MutTextBox::EvRButtonDown(uint, TPoint& point)
{
  RightButtonMenu(this, point);
}*/




///\}

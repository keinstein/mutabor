/** \file 
 ********************************************************************
 * Textbox for Lists
 *
 * Copyright:   (c) 2008-2011 TU Dresden
 *               changes after 2011/11 (c) by the authors
 * \author   R. Krauße
 * Tobias Schlemmer <keinstein@users.sourceforge.net>
 * \license GPL
 *
 *    This program is free software; you can redistribute it and/or modify
 *    it under the terms of the GNU General Public License as published by
 *    the Free Software Foundation; either version 2 of the License, or
 *    (at your option) any later version.
 *
 *    This program is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License for more details.
 *
 *    You should have received a copy of the GNU General Public License
 *    along with this program; if not, write to the Free Software
 *    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 *
 ********************************************************************
 * \addtogroup GUI
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
#include "wx/log.h"

#include "src/wxGUI/MutTextBox.h"
#include "src/wxGUI/MutFrame.h"
#include "src/wxGUI/GUIBoxData.h"
#include "src/wxGUI/Routing/BoxShape.h"
#include "src/kernel/routing/Route-inlines.h"
#include "src/kernel/MidiKern.h"


#ifdef __BORLANDC__
#pragma hdrstop
#endif

using mutaborGUI::BoxData;
using namespace mutaborGUI;

const wxString TextBoxTitle[] = { 
	wxString(N_("Current keys")), 
	wxString(N_("Tone system")), 
	wxString(N_("Actions")) };
// needs wxGetTranslation();

BEGIN_EVENT_TABLE(MutTextBox, wxListBox)
        EVT_MENU(CM_UPDATEUI, MutTextBox::UpdateUI)
	EVT_CLOSE(MutTextBox::OnClose)
END_EVENT_TABLE()


MutTextBox::MutTextBox(WinKind k,
                       mutabor::Box & b,
                       wxWindow* parent,
                       wxWindowID id,

                       const wxPoint& pos,
                       const wxSize& size):
		wxListBox(),
		ChangedCallback(b),
		winKind(k),
		box(b)
{
	wxString initlist[] = { _("<init>")  };
	Create(parent, id, pos, size, 1, initlist);
	TRACEC;
#if wxCHECK_VERSION(2,9,0)
	SetBackgroundStyle(wxBG_STYLE_ERASE);
#else
	SetBackgroundStyle(wxBG_STYLE_COLOUR);
#endif
//	SetBackgroundColour(*wxWHITE);
	if (box) {
		BoxData * guibox = ToGUIBase(box);
		SetForegroundColour(guibox->GetTextColour());
		SetBackgroundColour(guibox->GetBackgroundColour());
	}
}


void MutTextBox::OnClose(wxCloseEvent& event)

{
	mutUnused(event);
	mutASSERT(WK_KEY <= winKind && winKind < WK_NULL);
	DEBUGLOG (other, "winKind: %d" , winKind);
        BoxData * boxdata = ToGUIBase(box);
	if ( LogicOn ) {
                switch (winKind) {
                case WK_KEY:
			mutASSERT(dynamic_cast<MutTextBox *> (boxdata->GetKeyWindow()) == this);
                        boxdata->WantKeyWindow(false);
                        break;
                case WK_TS:
			mutASSERT(dynamic_cast<MutTextBox *> (boxdata->GetTonesystemWindow()) == this);
                        boxdata->WantTonesystemWindow(false);
                        break;
                case WK_ACT:
			mutASSERT(dynamic_cast<MutTextBox *> (boxdata->GetActionsWindow()) == this);
                        boxdata->WantActionsWindow(false);
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
void MutTextBox::UpdateUI(wxCommandEvent& event)
{
	if (Ok && winKind != WK_ACT) return;
	Ok = true;
	switch (winKind) {
	case WK_KEY:
		GetKeys();
		break;
	case WK_TS:
		GetToneSystem(asTS);
		break;
	case WK_ACT: {
		wxString action = event.GetString();
		if (!action.IsEmpty()) {
			Append(action);
			SetSelection(GetCount()-1);
		}
	}
		break;
	case WK_LOGIC:
		wxLogWarning(_("Unexpected value: WK_ROUTE"));
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

void MutTextBox::BoxChangedAction(const char * a) {
	if (winKind != WK_ACT) {
		return;
	}
	wxCommandEvent event(wxEVT_COMMAND_MENU_SELECTED,
			     CM_UPDATEUI);
#if wxCHECK_VERSION(2,9,0)
	event.SetString(a);
#else
	event.SetString(wxString::FromUTF8(a));
#endif
	wxPostEvent(this,event);
}

void MutTextBox::BoxChangedAction(int flags) {
	bool sendflags = false;

	switch (winKind) {
	case WK_KEY:
		sendflags = flags & ChangedCallback::KeysChanged;
		break;
	case WK_TS:
		sendflags = flags & ChangedCallback::BoxChanged;
		break;
	case WK_ACT:
		sendflags = flags & ChangedCallback::ActionChanged;
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
	}
	if (sendflags) {
		Ok = false;
		wxCommandEvent event(wxEVT_COMMAND_MENU_SELECTED,
				     CM_UPDATEUI);
		wxPostEvent(this,event);
	}
}



#if 0
static inline long get_frequency (long key, tone_system * tonesys) {
	if (!tonesys) return 0;
	long retval = tonesys->ton[GET_INDEX(key,tonesys)];
	if (!retval)  return 0;
	return ((long) tonesys->periode) * GET_ABSTAND(key,tonesys)  + retval;
}
#endif

void MutTextBox::GetKeys()
{
	wxString keys;

	if (!box) return;
	Freeze();
	Clear();

	mutabor::BoxClass::current_tone_list tones = box->GetCurrentTones();
	for (size_t i = 0; i < tones.size(); i++) {
		switch (tones[i].flag) {
		case mutabor::box_support::tone_entry::sounding:
#if 0
			/* we cant use %z for now. See http://trac.wxwidgets.org/ticket/14311 for details */
			keys.Printf(_("%2z : %8.1lf Hz (%6.2lf HT) [ch: %d, id: %z]"),
				    i,
				    mutabor_convert_pitch_to_frequency(tones[i].pitch),
				    tones[i].pitch,
				    tones[i].channel,
				    (unsigned long)tones[i].id);
#else
			/* implement multiple channels for each route one */
			keys.Printf(_("%3d : %8.1lf Hz (%6.2lf HT) [ch: %d, id: %lu]"),
				tones[i].index,
				mutabor_convert_pitch_to_frequency(tones[i].pitch),
				tones[i].pitch,
				tones[i].channel,
				(unsigned long)tones[i].id);
#endif
			break;
		case mutabor::box_support::tone_entry::silent:
			keys.Printf(_("%3d : empty"),tones[i].index);
			break;
		case mutabor::box_support::tone_entry::invalid:
			keys.Printf(_("%3d : invalid tone"),tones[i].index);
			break;
		default:
			keys.Printf(_("%3d : (unknown type %d)"),
				    tones[i].index,(int)(tones[i].flag));
		}
		Append(keys);
	}
	Thaw();
}

void MutTextBox::GetToneSystem(bool asTS)
{
	wxString keys;

	mutabor::box_support::tone_system tonesys = box->GetToneSystem();
	Freeze();

	Clear();


	keys.Printf(_("Anchor = %d"), tonesys.anchor);
	Append(keys);
	keys.Printf(_("Width = %u"), (unsigned)tonesys.tones.size());
	Append(keys);
	keys.Printf(_("Period = %.1f HT"), tonesys.period);
	Append(keys);

	if (tonesys.tones.size() < 1) {
		Append(_("No tones."));
		Thaw();
		return;
	}
	size_t i;
	double reference = 0.0l;
	if (!asTS) {
		for (i = 0 ; i < tonesys.tones.size(); i++) {
			if (tonesys.tones[i].flag ==
			    mutabor::box_support::tone_entry::sounding) {
				reference = tonesys.tones[i].pitch;
				break;
			}
		}
		keys.Printf(_("Reference = %d HT"),i);
		Append(keys);
	}

	for (i = 0 ; i < tonesys.tones.size(); i++) {
		double pitch, frequency;
		switch(tonesys.tones[i].flag) {
		case mutabor::box_support::tone_entry::sounding:
			pitch = tonesys.tones[i].pitch;
			frequency =
				mutabor_convert_pitch_to_frequency(pitch);
			if (!asTS) pitch -= reference;
			keys.Printf(_("%2lu : %8.1lf Hz (%6.2lf HT)"),
				    (unsigned long)i,
				    frequency,
				    pitch );
			break;
		case mutabor::box_support::tone_entry::silent:
			keys.Printf(_("%2lu : empty"),
				    (unsigned long)i);
			break;
		case mutabor::box_support::tone_entry::invalid:
			keys.Printf(_("%2lu : invalid tone"),
				    (unsigned long)i);
			break;
		default:
			keys.Printf(_("%2lu : (unknown type %d)"),
				    (unsigned long)i,
				    (int) ( tonesys.tones[i].flag));
		}
		Append(keys);
	}
	Thaw();

}

#if 0
/** \todo remove this code */
void MutTextBox::GetAllActions ()
{
	NewText(GenerateCAWString());
}

void MutTextBox::GetBoxActions()
{
	NewText(GenerateACTString(box));
}

void MutTextBox::NewText(char *s, bool newTitle)
{
	mutASSERT(WK_KEY <= winKind && winKind < WK_NULL);
	TRACEC;
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
	DEBUGLOG (other, "s=%s; newTitle=%d; winKind=%d" ,s.c_str(),newTitle,winKind);
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
#endif


wxString MutTextBox::MakeTitle() const {
	if (winKind == WK_ACT && CAW) {
		return _("Actions - all boxes");
	} else {
		return wxString::Format(wxGetTranslation(_("%s - %s")),
					(const wxChar *)wxGetTranslation(TextBoxTitle[winKind]),
					(const wxChar *)(box?box->GetLabel():wxString(_("unknown"))));
	}
}



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

///\}

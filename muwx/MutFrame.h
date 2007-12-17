/////////////////////////////////////////////////////////////////////////////
// Name:        MutFrame.h
// Purpose:     Mutabor Frame
// Author:      R. Krauﬂe
// Modified by:
// Created:     12.08.05
// Copyright:   (c) R. Krauﬂe
// Licence:     wxWindows license
/////////////////////////////////////////////////////////////////////////////

#ifndef MUTFRAME_H
#define MUTFRAME_H

#include "Global.h"
#include "MutChild.h"
#include "MutEditFile.h"
#include "wx/aui/aui.h"
#include "wx/toolbar.h"

class MutFrame : public wxFrame
{
public:
    MutFrame(wxWindow *parent, const wxWindowID id, const wxString& title,
            const wxPoint& pos, const wxSize& size,
			 const long style);
			 
	~MutFrame();

    void InitToolBar(wxToolBar* toolBar);

//    void OnSize(wxSizeEvent& event);
	void PassEventToEditor(wxCommandEvent &event);
    void EventPassOn(wxCommandEvent& event);
    void OnNewWindow(wxCommandEvent& event);
    void OnQuit(wxCommandEvent& event);
    void OnClose(wxCloseEvent& event);

	void CmFileNew(wxCommandEvent& WXUNUSED(event));
	void CmFileOpen(wxCommandEvent& WXUNUSED(event));

	void OpenFile(wxString path);

	void CmDoActivate(wxCommandEvent& event);
	void CmStop(wxCommandEvent& WXUNUSED(event));
	void CmPanic(wxCommandEvent& WXUNUSED(event));
    void CeActivate(wxUpdateUIEvent& event);
    void CeStop(wxUpdateUIEvent& event);

	void CmRoutes(wxCommandEvent& event);

    void CmToggleKey(wxCommandEvent& WXUNUSED(event));
    void CmToggleTS(wxCommandEvent& WXUNUSED(event));
    void CmToggleAct(wxCommandEvent& WXUNUSED(event));
    void CmToggleOWM(wxCommandEvent& WXUNUSED(event));
    void CmToggleCAW(wxCommandEvent& WXUNUSED(event));
    void CeToggleKey(wxUpdateUIEvent& event);
    void CeToggleTS(wxUpdateUIEvent& event);
    void CeToggleAct(wxUpdateUIEvent& event);
    void CeToggleOWM(wxUpdateUIEvent& event);
    void CeToggleCAW(wxUpdateUIEvent& event);

    // Recorder-Knˆpfe
	void CmInDevStop(wxCommandEvent& WXUNUSED(event));
	void CmInDevPlay(wxCommandEvent& WXUNUSED(event));
	void CmInDevPause(wxCommandEvent& WXUNUSED(event));
	void CeInDevStop(wxUpdateUIEvent& event);
	void CeInDevPlay(wxUpdateUIEvent& event);
	void CeInDevPause(wxUpdateUIEvent& event);

	// Idle
	void UpdateUI(wxCommandEvent& WXUNUSED(event));
	void OnIdle(wxIdleEvent& WXUNUSED(event));
	void OnActivate(wxActivateEvent& event);
	void OnEraseBackground(wxEraseEvent& event);
	void OnSize(wxSizeEvent& event);
	wxAuiDockArt* MutFrame::GetDockArt();

	MutChild* NewFrame(WinKind winKind, int box, const wxString &frameName, wxIcon icon, const wxString &title = wxEmptyString);
	void WindowSize(MutChild *win);
	void SaveState();
	void RestoreState();

	void LogicWinOpen(int box);
	void ToggleTextBox(WinKind kind);
	void TextBoxOpen(WinKind kind, int box);
	void CmSelectBox();
	void CmCloseChild();

    void SetStatus(int WXUNUSED(imgNr))
    {
      //StatusGadget->SelectImage(curStatusImg = imgNr, true);
    }
	
	wxRect DetermineFrameSize ();
  private:
    int curStatusImg;

	wxAuiManager auimanager;

	wxWindow *client;

    DECLARE_EVENT_TABLE()
};

// globals

extern bool asTS;
extern bool SaveEditor;
extern bool UseColorBars;
extern bool OWM; // One Window Mode
extern bool CAW; // Common Action Window
extern bool LogicOn;
extern int curBox;

extern wxString CompiledFile;

extern wxString curLogic[MAX_BOX];
extern wxString curTS[MAX_BOX];
extern int curTaste[MAX_BOX][2];

#endif

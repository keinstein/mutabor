/////////////////////////////////////////////////////////////////////////////
// Name:        Action.cpp
// Purpose:     Actions at UI
// Author:      R. Krauße
// Modified by:
// Created:     01.09.05
// Copyright:   (c) R. Krauße
// Licence:     wxWindows license
/////////////////////////////////////////////////////////////////////////////

#ifndef MUTROUTEWND_H
#define MUTROUTEWND_H

#include "wx/scrolwin.h"
//#include "EDevice.h"

#define xz 5 // Zwischenräume
#define yz 5

// RouteWin ----------------------------------------------------------
// Fenster, das die Routen enthält

class MutRouteWnd : public wxScrolledWindow
{

public:

	MutRouteWnd(wxWindow *parent, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize);

	/*    void RePaint();
	    int FocusPos[2];
	  private:
		wxString FileName;
	    int nTags;*/

private:
	int spacex,spacey;
	int x1, x2, x3, x4, x5;
	wxIcon * DevIcon[4];
	wxBitmap *ConIcon[4];
	wxIcon * PlopIcon[4];
        wxSizer * InputSizer;
        wxSizer * OutputSizer;
        wxSizer * BoxSizer;
        MutDeviceShapeList InputDevices, OutputDevices;

	MutBoxShape *BoxPTRs[MAX_BOX];
	MutBoxShapeList Boxes;
	
	
	struct MurFileDataType
	{
		wxFileName name;
		muConvAuto autoConverter;
	};
	
	static MurFileDataType MurFileData;
	
	
	
	void createInputDevices(wxSizerFlags flags);
	void createBoxes(wxSizerFlags flags);
        void createOutputDevices(wxSizerFlags flags);
public:
	/// interactive route loading
	/**
	 * This function opens a file open dialog in order to load a route configuration from disk storage.
	 * \argument event (wxCommandEvent) event to be processed
	 */
	static void CmRouteLoad(wxCommandEvent& event);
	
	/// save routes to disk.
	/**
	 * This function saves the current routing conifiguriton into a file on disk storage.
	 * \argument event (wxCommandEvent) event to be processed
	 */
	static void CmRouteSave(wxCommandEvent& event);
	
	/// save routes with a new file name
	/**
	 * This function opens a file save dialog in order to save a route configuration to disk storage.
	 * \argument event (wxCommandEvent) event to be processed
	 */
	static void CmRouteSaveAs(wxCommandEvent& event);
	
	
	/// fills the window with the corresponding shapes.
	/**
	 * This function is used to initialize the window with the current
	 * routing information. It creates the shapes for devices, routes and new objects.
	 */
	void InitShapes();
	void InitDevices();
	void ClearDevices();
	
	/// Adds an input device shape
	/**
	   \param device (MutInputDeviceShape *) device to be added
	   \param flags (wxSizerFlages &) Sizer flags, which shall be applied
	*/
	bool AddInputDevice(MutInputDeviceShape * device, const wxSizerFlags & flags) {
		wxASSERT(InputSizer);
		InputSizer -> Add(device,flags);
		Layout();
		FitInside();
		SetVirtualSize(wxDefaultSize);
		return true;
	}

	/// Clears all input device shapes
	void ClearInputDevices();
	
	/// Adds an output device shape
	/**
	   \param device (MutInputDeviceShape *) device to be added
	   \param flags (wxSizerFlages &) Sizer flags, which shall be applied
	*/
	bool AddOutputDevice(MutOutputDeviceShape * device, const wxSizerFlags & flags) {
		wxASSERT(OutputSizer);
		OutputSizer -> Add(device, flags);
		Layout();
		FitInside();
		SetVirtualSize(wxDefaultSize);
		return true;
	}
	/// Clears all output device shapes
	void ClearOutputDevices();
	
	/// Adds a box shape
	/**
	   \param box (MutInputDeviceShape *) box to be added
	   \param flags (wxSizerFlages &) Sizer flags, which shall be applied
	*/
	bool AddBox(MutBoxShape * box, const wxSizerFlags & flags) {
		wxASSERT(BoxSizer);
		BoxSizer -> Add(box,flags);
		Layout();
		SetVirtualSize(wxDefaultSize);
		FitInside();
		Boxes.Append(box);
		return true;
	}

	/// Clears all box shapes
	void ClearBoxes();
	
	wxSizer * GetInputDevices() const 
	{
		return InputSizer;
	}
	
	wxSizer * GetBoxes() const 
	{
		return BoxSizer;
	}
	
	wxSizer * GetOutputDevices() const 
	{
		return OutputSizer;
	}
	
	virtual void OnDraw(wxDC& dc);

	//	void OnSize(wxSizeEvent& event);

	/*  protected:
	   virtual void SetupWindow();
	   virtual bool CanClose();
	virtual void EvChar(uint key, uint repeatCount, uint flags);
	void CorrectScroller();
	   void SetFocusPos();*/
	/*
	int CalcXl()
	{
		return x1+x2+x3+x4+x5+10*xz;
	}

	int CalcYl();

	bool CheckPoint(wxPoint point, EDevice **in, ERoute **r, 
			int &token, bool &needNew);
	void OnLeftDown(wxMouseEvent &event);
	void OnLeftDClick(wxMouseEvent &event);
	    void EvLButtonDblClk(UINT modKeys, TPoint& point);
	    void EvRButtonDown(uint modKeys, TPoint& point);*/

public:
	DECLARE_EVENT_TABLE()
};

extern bool LogicOn;


#endif

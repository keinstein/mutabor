// -*- C++ -*-
/** \file
 ********************************************************************
 * Devices Basisklassen.
 *
 * $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/muwx/Routing/InputDeviceShape.h,v 1.3 2011/02/20 22:35:58 keinstein Exp $
 * \author Rüdiger Krauße <krausze@mail.berlios.de>,
 * Tobias Schlemmer <keinstein@users.berlios.de>
 * \date 2009/11/23
 * $Date: 2011/02/20 22:35:58 $
 * \version $Revision: 1.3 $
 * \license GPL
 *
 * $Log: InputDeviceShape.h,v $
 * Revision 1.3  2011/02/20 22:35:58  keinstein
 * updated license information; some file headers have to be revised, though
 *
 * Revision 1.2  2010-11-21 13:15:49  keinstein
 * merged experimental_tobias
 *
 * Revision 1.1.2.9  2010-11-14 21:28:38  keinstein
 * implement loading and saving old files with new routing system
 *
 * Revision 1.1.2.8  2010-06-15 14:30:15  keinstein
 * allow deleting of input devices in route window
 * several bug fixes
 * rudimentary box deletion support
 *
 * Revision 1.1.2.7  2010/04/15 09:28:43  keinstein
 * changing routes works, but is not honoured by MIDI, yet
 *
 * Revision 1.1.2.6  2010/03/30 15:57:58  keinstein
 * added editing of existing routes to boxDlg
 *
 * Revision 1.1.2.5  2010/03/30 08:38:27  keinstein
 * added rudimentary command line support
 * changed debug system to allow selection of messages via command line
 * further enhancements to the route dialogs
 *
 * Revision 1.1.2.4  2010/01/14 18:14:20  keinstein
 * fix usage of installation prefix
 * MutInputDeviceShape/MutOutputDeviceShape:
 *     use GetType for type checking in OnChoiceSelected
 *     make InitalizeDialog const
 * MutNewOutputDeviceShape: add InitializeDialog and ReplaceSelfBy
 *
 * Revision 1.1.2.3  2010/01/14 09:34:24  keinstein
 * Checkin searching for a bug
 *
 * Revision 1.1.2.2  2010/01/11 12:51:52  keinstein
 * fix some problems due to splitting MutRouteShapes.{cpp,h}
 *
 * Revision 1.1.2.1  2009/11/30 12:08:57  keinstein
 * split MutRouteShapes into several files into directory Routing
 *
 * MutRouteShapes.h,v
 * Revision 1.1.2.2  2009/11/03 12:39:31  keinstein
 * input device dialog: Allow to edit input devices
 * fix a bug on Mac OS X, that prevented Mutabor from starting if no MIDI device is availlable
 *
 * Revision 1.1.2.1  2009/08/10 11:23:12  keinstein
 * merged from wrong tree
 *
 * Revision 1.2  2009/08/10 11:15:47  keinstein
 * some steps towards new route window
 *
 * Revision 1.1  2008/11/03 15:31:54  keinstein
 * Added to the system
 *
 *
 ********************************************************************
 *\addtogroup route
 *\{
 ********************************************************************/

#ifndef INPUTDEVICESHAPE_H
#define INPUTDEVICESHAPE_H

//#include <map>

#include "wx/defs.h"
//#include "wx/icon.h"
//#include "wx/stattext.h"

#include "RouteIcons.h"
#include "DeviceShape.h"
#include "InputDevDlg.h"

class InputFilterPanel;
class MutBoxChannelShape;

class MutInputDeviceShape:public MutDeviceShape{
protected: 
	InDevice *device;
//	static stringmaptype stringmap;
	static wxSizerFlags sizerFlags;

public:

	MutInputDeviceShape():MutDeviceShape() {
		device = NULL;
	}

	MutInputDeviceShape (wxWindow * parent, wxWindowID id, const wxString &
	                     name):MutDeviceShape ()
	{
		device = NULL;
		Create (parent, id, name);
	}


	MutInputDeviceShape (wxWindow * parent, wxWindowID id, InDevice * d):
		MutDeviceShape() {
		Create (parent, id, d);
	}

	virtual ~MutInputDeviceShape();

	bool Create (wxWindow * parent, wxWindowID id, const wxString &
	                     name)
	{
		DEBUGLOG (other,_T (""));
		device = NULL;
		return MutDeviceShape::Create (parent, id, name);
	}

	bool Create (wxWindow * parent, wxWindowID id, InDevice * d);

	static MutInputDeviceShape * CreateShape(wxWindow * parent,
						 wxWindowID id,
						 InDevice * d);

	MutInputDeviceShape * CreateShape (InDevice * d) 
        {
		DEBUGLOG (other,_T (""));
		return CreateShape (m_parent, wxID_ANY,d);
	}

	static void SetSizerFlags (wxSizerFlags flags) {sizerFlags = flags; }
  static const wxSizerFlags & GetSizerFlags() { return sizerFlags; }

	void SetLabel(const wxString & st );

	MutIcon & GetMutIcon ()
	{
		return MidiInputDevBitmap;
	}

	Route * getRoutes()
	{
		if (!device) return NULL;
		return device->GetRoutes();
	}
		
	virtual void AddRoute(Route * route);
	virtual void RemoveRoute(Route * route);

	void SetDevice (InDevice * d) {
		wxASSERT (d);
		device = d;
		wxASSERT (device->getUserData());
		device -> setUserData (this);
	}
	
	InDevice * GetDevice() { return device; }

	virtual void DoLeftDblClick();
	InputDevDlg * ShowDeviceDialog();
	virtual wxPanel * GetInputFilterPanel(wxWindow * parent, Route * route) const
	{ 
		ABSTRACT_FUNCTIONC;
		return NULL; 
	}
	
	virtual void ReadInputFilterPanel(wxWindow * panel, Route * route) 
	{
		ABSTRACT_FUNCTIONC;
		return;
	}
	virtual void ReadPanel(InputFilterPanel * panel, MutBoxChannelShape * channel);

protected: 
	virtual void InitializeDialog(InputDevDlg * in) const { }
	virtual bool readDialog (InputDevDlg * in) { 
		wxASSERT (false);
		return false; 
	}
	/// detach device
	/** Detaches the device from any route and deletes the device. 
	 * \return true if the corresponding device has been removed and we can delete the Shape.
	 */
	virtual bool DetachDevice ();
	virtual bool replaceSelfBy (MutInputDeviceShape  * newshape);
	virtual bool CanHandleType (DevType  type) { return false; }

private:
	DECLARE_DYNAMIC_CLASS(MutDeviceShape);
};

#endif				/* INPUTDEVICESHAPE_H */
/*
 * \}
 */

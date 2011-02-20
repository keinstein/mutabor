/** \file */// -*- C++ -*-
/********************************************************************
 * Output device shape for route window.
 *
 * $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/muwx/Routing/OutputDeviceShape.h,v 1.3 2011/02/20 22:35:59 keinstein Exp $
 * \author Rüdiger Krauße <krausze@mail.berlios.de>,
 * Tobias Schlemmer <keinstein@users.berlios.de>
 * \date 2009/11/23
 * $Date: 2011/02/20 22:35:59 $
 * \version $Revision: 1.3 $
 * \license GPL
 *
 * $Log: OutputDeviceShape.h,v $
 * Revision 1.3  2011/02/20 22:35:59  keinstein
 * updated license information; some file headers have to be revised, though
 *
 * Revision 1.2  2010-11-21 13:15:50  keinstein
 * merged experimental_tobias
 *
 * Revision 1.1.2.12  2010-11-14 21:28:38  keinstein
 * implement loading and saving old files with new routing system
 *
 * Revision 1.1.2.11  2010-06-29 08:24:57  keinstein
 * searching
 *
 * Revision 1.1.2.10  2010/06/22 15:05:45  keinstein
 * debugging segfault in route check after replacement of MutOutputDevice
 *
 * Revision 1.1.2.9  2010/06/21 14:28:12  keinstein
 * implement deletion of output devices
 *
 * Revision 1.1.2.8  2010/05/07 11:40:28  keinstein
 * actual_settings
 *
 * Revision 1.1.2.7  2010/04/15 09:28:43  keinstein
 * changing routes works, but is not honoured by MIDI, yet
 *
 * Revision 1.1.2.6  2010/03/30 08:38:27  keinstein
 * added rudimentary command line support
 * changed debug system to allow selection of messages via command line
 * further enhancements to the route dialogs
 *
 * Revision 1.1.2.5  2010/02/15 12:08:21  keinstein
 * intermediate update for backup progress
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

#ifndef OUTPUTDEVICESHAPE_H
#define OUTPUTDEVICESHAPE_H

//#include <map>

#include "wx/defs.h"
//#include "wx/icon.h"
//#include "wx/stattext.h"

#include "DeviceShape.h"
#include "OutputDevDlg.h"
#include "BoxChannelShape.h"

class MutOutputDeviceShape:public MutDeviceShape
{
protected:
	static wxSizerFlags sizerFlags;
	OutDevice *device;
	MutBoxChannelShapeList routes;

public:
	MutOutputDeviceShape():MutDeviceShape(),device(NULL) { }


	MutOutputDeviceShape (wxWindow * parent, wxWindowID id, 
			      const wxString & name) {
		Create (parent, id, name);
	}
	
	MutOutputDeviceShape (wxWindow * parent, wxWindowID id, OutDevice * d):
		MutDeviceShape() {
		Create (parent, id,  d);
	}

	virtual ~MutOutputDeviceShape() 
		{
			if (device) {
				wxASSERT (device -> getUserData() == this);
				device -> setUserData (NULL);
			}
			DEBUGLOG(other, _T("Deleting."));
		}


	bool Create (wxWindow * parent, wxWindowID id, 
		     const wxString & name)
		{
			device = NULL;
			return MutDeviceShape::Create (parent,id, name);
		}

	bool Create (wxWindow * parent, wxWindowID id, OutDevice * d);


	
	static MutOutputDeviceShape * CreateShape(wxWindow * parent,
						 wxWindowID id,
						 OutDevice * d);

	MutOutputDeviceShape * CreateShape (OutDevice * d) 
        {
		DEBUGLOG (other,_T (""));
		return CreateShape (m_parent, wxID_ANY,d);
	}

	static void SetSizerFlags (wxSizerFlags flags) 
        {
	        sizerFlags = flags; 
	}
  static const wxSizerFlags & GetSizerFlags() { return sizerFlags; }

	void SetLabel(const wxString & st );        

	MutIcon & GetMutIcon ()
	{
		return MidiOutputDevBitmap;
	}
	
	virtual void AddRoute(Route * route);
	virtual void AddRoute(MutBoxChannelShape * route) {
		wxASSERT(route->GetRoute()->getUserData() == route);
		AddRoute(route->GetRoute());
	}
	virtual void RemoveRoute(Route * route);
	virtual void RemoveRoute(MutBoxChannelShape * route) {
		wxASSERT(route->GetRoute()->getUserData() == route);
		RemoveRoute(route->GetRoute());
	}
	
	Route * getRoutes()
	{
		UNREACHABLEC;
		abort();
	}
	const MutBoxChannelShapeList & getRoutesList()
	{
		return routes;
	}
	
	OutDevice * GetDevice() 
	{
		return device;
	}

	virtual void DoLeftDblClick();

	OutputDevDlg * ShowDeviceDialog();

	virtual wxPanel * GetOutputFilterPanel(wxWindow * parent, Route * route) const
	{ 
		ABSTRACT_FUNCTIONC;
		return NULL; 
	}
	
	virtual void ReadOutputFilterPanel(wxWindow * panel, Route * route)
	{
		ABSTRACT_FUNCTIONC;
	}	
	virtual void ReadPanel(OutputFilterPanel * panel, MutBoxChannelShape * channel);
	
protected:
	virtual void InitializeDialog(OutputDevDlg * out) const
		{
			DEBUGLOG(other, _T("Initializing only generic OutputDeviceShape"));
		}

	virtual bool readDialog (OutputDevDlg * out) { 
		wxASSERT (false);
		return false; 
	}

	/// detach device
	/** Detaches the device from any route and deletes the device. 
	 * \return true if the corresponding device has been removed and we can delete the Shape.
	 */
	virtual bool DetachDevice ();
	virtual bool replaceSelfBy (MutOutputDeviceShape  * newshape);

	virtual bool CanHandleType (DevType  type) = 0;

private:
	DECLARE_ABSTRACT_CLASS(MutDeviceShape);
};

#endif				/* OUTPUTDEVICESHAPE_H */
/*
 * \}
 */

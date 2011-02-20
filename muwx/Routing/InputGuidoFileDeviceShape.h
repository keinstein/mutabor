// -*- C++ -*-
/** \file
 ********************************************************************
 * Devices Basisklassen.
 *
 * $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/muwx/Routing/InputGuidoFileDeviceShape.h,v 1.3 2011/02/20 22:35:58 keinstein Exp $
 * \author Rüdiger Krauße <krausze@mail.berlios.de>,
 * Tobias Schlemmer <keinstein@users.berlios.de>
 * \date 1998
 * $Date: 2011/02/20 22:35:58 $
 * \version $Revision: 1.3 $
 * \license GPL
 *
 * $Log: InputGuidoFileDeviceShape.h,v $
 * Revision 1.3  2011/02/20 22:35:58  keinstein
 * updated license information; some file headers have to be revised, though
 *
 * Revision 1.2  2010-11-21 13:15:49  keinstein
 * merged experimental_tobias
 *
 * Revision 1.1.2.5  2010-03-30 15:57:58  keinstein
 * added editing of existing routes to boxDlg
 *
 * Revision 1.1.2.4  2010/03/30 08:38:27  keinstein
 * added rudimentary command line support
 * changed debug system to allow selection of messages via command line
 * further enhancements to the route dialogs
 *
 * Revision 1.1.2.3  2010/02/15 12:08:21  keinstein
 * intermediate update for backup progress
 *
 * Revision 1.1.2.2  2010/01/14 18:14:20  keinstein
 * fix usage of installation prefix
 * MutInputDeviceShape/MutOutputDeviceShape:
 *     use GetType for type checking in OnChoiceSelected
 *     make InitalizeDialog const
 * MutNewOutputDeviceShape: add InitializeDialog and ReplaceSelfBy
 *
 * Revision 1.1.2.1  2009/11/30 12:08:57  keinstein
 * split MutRouteShapes into several files into directory Routing
 *
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

#ifndef INPUTGUIDOFILEDEVICESHAPE_H
#define INPUTGUIDOFILEDEVICESHAPE_H

//#include <map>

//#include "wx/defs.h"
//#include "wx/icon.h"
//#include "wx/stattext.h"

#include "MutIcon.h"
#include "InputMidiDeviceShape.h"
//#include "Device.h"

class MutInputGuidoFileDeviceShape:public MutInputDeviceShape
{
public:
	MutInputGuidoFileDeviceShape():MutInputDeviceShape() {}
	MutInputGuidoFileDeviceShape (wxWindow * parent,
				     wxWindowID id, 
				     InDevice * d):
		MutInputDeviceShape() {
		Create (parent,id,d);
	}
	bool Create (wxWindow * parent, wxWindowID id, InDevice * d)
		{
			return MutInputDeviceShape::Create(parent,id,d);
		}

	virtual MutIcon & GetMutIcon () 
		{
			DEBUGLOG(other, _T(""));
			return GuidoFileBitmap;
		}

	void SetLabel(const wxString & st ) {
		fileName = st;
		fileName.Normalize();
		MutInputDeviceShape::SetLabel (fileName.GetFullName());
	}

	virtual wxPanel * GetInputFilterPanel(wxWindow * parent, Route * route) const;
	virtual void ReadInputFilterPanel(wxWindow * panel, Route * route);
	
protected: 
	virtual void InitializeDialog(InputDevDlg * in) const;
	virtual bool readDialog (InputDevDlg * in);
	virtual bool CanHandleType (DevType  type) { return type == DTGis; }

	wxFileName fileName;

private:
	DECLARE_DYNAMIC_CLASS(MutInputGuidoFileDeviceShape);

};
#endif				/* INPUTGUIDOFILEDEVICESHAPE_H */
/*
 * \}
 */

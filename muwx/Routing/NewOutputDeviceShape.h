// -*- C++ -*-
/** \file
 ********************************************************************
 * New output device shape for route window.
 *
 * $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/muwx/Routing/NewOutputDeviceShape.h,v 1.3 2011/02/20 22:35:59 keinstein Exp $
 * \author Rüdiger Krauße <krausze@mail.berlios.de>,
 * Tobias Schlemmer <keinstein@users.berlios.de>
 * \date 2009/11/23
 * $Date: 2011/02/20 22:35:59 $
 * \version $Revision: 1.3 $
 * \license GPL
 *
 * $Log: NewOutputDeviceShape.h,v $
 * Revision 1.3  2011/02/20 22:35:59  keinstein
 * updated license information; some file headers have to be revised, though
 *
 * Revision 1.2  2010-11-21 13:15:49  keinstein
 * merged experimental_tobias
 *
 * Revision 1.1.2.4  2010-05-07 11:40:28  keinstein
 * actual_settings
 *
 * Revision 1.1.2.3  2010/03/30 08:40:15  keinstein
 * added rudimentary command line support
 * changed debug system to allow selection of messages via command line
 * further enhancements to the route dialogs
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

#ifndef NEWOUTPUTDEVICESHAPE_H
#define NEWOUTPUTDEVICESHAPE_H

//#include <map>

//#include "wx/defs.h"
//#include "wx/icon.h"
//#include "wx/stattext.h"

#include "OutputDeviceShape.h"
//#include "Device.h"

class MutNewOutputDeviceShape:public MutOutputDeviceShape
{
	
public:
	MutNewOutputDeviceShape():MutOutputDeviceShape() {}

	MutNewOutputDeviceShape (wxWindow * parent, wxWindowID id):
		MutOutputDeviceShape() 
	{
		Create (parent,id);
	}


	bool Create (wxWindow * parent, 
		     wxWindowID id)
	{
		return MutOutputDeviceShape::Create (parent,
						     id,
						     _("New Output device"));
	}


	MutIcon & GetMutIcon ()
	{
		return NewOutputDevBitmap;
	}
protected:
	virtual void InitializeDialog(OutputDevDlg * out) const;
	virtual bool replaceSelfBy (MutOutputDeviceShape  * newshape);
	virtual bool CanHandleType (DevType  type) { return false; }
	
private:
	DECLARE_DYNAMIC_CLASS(MutOutputDeviceShape);
};

#endif				/* NEWOUTPUTDEVICESHAPE_H */
/*
 * \}
 */

// -*- C++ -*-

/** \file
 ********************************************************************
 * New input device shape for route window.
 *
 * $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/muwx/Routing/NewInputDeviceShape.h,v 1.2 2010/11/21 13:15:49 keinstein Exp $
 * \author Rüdiger Krauße <krausze@mail.berlios.de>,
 * Tobias Schlemmer <keinstein@users.berlios.de>
 * \date 2009/11/23
 * $Date: 2010/11/21 13:15:49 $
 * \version $Revision: 1.2 $
 *
 * $Log: NewInputDeviceShape.h,v $
 * Revision 1.2  2010/11/21 13:15:49  keinstein
 * merged experimental_tobias
 *
 * Revision 1.1.2.2  2010-01-14 18:14:20  keinstein
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

#ifndef NEWINPUTDEVICESHAPE_H
#define NEWINPUTDEVICESHAPE_H

//#include <map>

//#include "wx/defs.h"
//#include "wx/icon.h"
//#include "wx/stattext.h"

#include "InputDeviceShape.h"
//#include "Device.h"


class MutNewInputDeviceShape:public MutInputDeviceShape
{

public:
	MutNewInputDeviceShape():MutInputDeviceShape() {}

	MutNewInputDeviceShape (wxWindow * parent, wxWindowID id):MutInputDeviceShape() 
		{
			Create(parent, id);
		}

	bool Create (wxWindow * parent, wxWindowID id)
		{
			return MutInputDeviceShape::Create (parent,id,_("New Input device"));
		}

	MutIcon & GetMutIcon ()
		{
			return NewInputDevBitmap;
		}

protected:
	virtual void InitializeDialog(InputDevDlg * in) const;
	virtual bool replaceSelfBy (MutInputDeviceShape  * newshape);

private:
	DECLARE_DYNAMIC_CLASS(MutInputDeviceShape);
};

#endif				/* NEWINPUTDEVICESHAPE_H */
/*
 * \}
 */

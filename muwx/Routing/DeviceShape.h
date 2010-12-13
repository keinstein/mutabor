// -*- C++ -*-

/** \file
 ********************************************************************
 * Device shape base class for route window.
 *
 * $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/muwx/Routing/DeviceShape.h,v 1.3 2010/12/13 00:27:53 keinstein Exp $
 * \author Rüdiger Krauße <krausze@mail.berlios.de>,
 * Tobias Schlemmer <keinstein@users.berlios.de>
 * \date 1998
 * $Date: 2010/12/13 00:27:53 $
 * \version $Revision: 1.3 $
 *
 * $Log: DeviceShape.h,v $
 * Revision 1.3  2010/12/13 00:27:53  keinstein
 * compiles in linux as well as in mingw
 *
 * Revision 1.2  2010-11-21 13:15:48  keinstein
 * merged experimental_tobias
 *
 * Revision 1.1.2.5  2010-03-30 08:38:27  keinstein
 * added rudimentary command line support
 * changed debug system to allow selection of messages via command line
 * further enhancements to the route dialogs
 *
 * Revision 1.1.2.4  2010/02/15 12:08:21  keinstein
 * intermediate update for backup progress
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

#ifndef DEVICESHAPE_H
#define DEVICESHAPE_H

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <map>

//#include "wx/defs.h"
//#include "wx/ogl/ogl.h"
//#include "wx/icon.h"
//#include "wx/stattext.h"

#include "DeviceShape.h"
#include "IconShape.h"
#include "Route.h"
//#include "Device.h"

class InputDevDlg;

class MutDeviceShape:public MutIconShape
{
	//	wxFileName filename;
	class strptrless {
	public:
		bool operator () (wxString * a, wxString * b) {
			if (a == b) return true;
			if (a == NULL) return true;
			if (b == NULL) return false;
			return (*a <= *b);
		}
	};

public:

	typedef std::map<wxString *, MutDeviceShape *, strptrless> 
	stringmaptype;
	typedef stringmaptype::iterator stringmapiterator;
  
	MutDeviceShape():MutIconShape() 
		{
		}
	MutDeviceShape (wxWindow * parent, wxWindowID id, 
			const wxString & name = wxEmptyString):
		MutIconShape()
		{
			Create(parent, id, name);
		}

	virtual ~MutDeviceShape() {}
 
	bool Create (wxWindow * parent, wxWindowID id, 
		     const wxString & name = wxEmptyString)
		{


			DEBUGLOG(other, _T(""));
			DEBUGLOG(other, _T("Name %s"),name.c_str());
			bool state = MutIconShape::Create (parent,id);
			if (state) SetLabel(name);
			return state;
		}
	
	virtual bool Recompute();
	virtual Route * getRoutes() = 0;
	virtual void DoLeftDblClick() = 0;
	void LeftDblClickEvent (wxMouseEvent & event) {
		DoLeftDblClick();
	}

#if 0
protected:
	void RemoveFromStringMap(stringmaptype & sm) {
		std::pair<stringmapiterator,stringmapiterator> 
			bounds = sm.equal_range(&m_label);
		for (stringmapiterator it = bounds.first; 
		     it != bounds.second; ++it) {
			if ((*it).second == this) {
				stringmapiterator it1 = it;
				it++;
				sm.erase(it1);
			}
		}
	}

	void InsertSelfToStringMap(stringmaptype & sm) {
		sm.insert(std::make_pair(&m_label,this)); 
	}
#endif
private:
  DECLARE_DYNAMIC_CLASS(MutIconShape);
  DECLARE_EVENT_TABLE();
};

WX_DECLARE_LIST (MutDeviceShape, MutDeviceShapeList);

#endif				/* DEVICESHAPE_H */
/*
 * \}
 */

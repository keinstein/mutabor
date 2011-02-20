// -*- C++ -*-
/** \file
 ********************************************************************
 * MIDI file input device shape.
 *
 * $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/muwx/Routing/OutputMidiFileDeviceShape.h,v 1.3 2011/02/20 22:35:59 keinstein Exp $
 * \author Rüdiger Krauße <krausze@mail.berlios.de>,
 * Tobias Schlemmer <keinstein@users.berlios.de>
 * \date 2009/11/23
 * $Date: 2011/02/20 22:35:59 $
 * \version $Revision: 1.3 $
 * \license GPL
 *
 * $Log: OutputMidiFileDeviceShape.h,v $
 * Revision 1.3  2011/02/20 22:35:59  keinstein
 * updated license information; some file headers have to be revised, though
 *
 * Revision 1.2  2010-11-21 13:15:50  keinstein
 * merged experimental_tobias
 *
 * Revision 1.1.2.3  2010-04-15 09:28:43  keinstein
 * changing routes works, but is not honoured by MIDI, yet
 *
 * Revision 1.1.2.2  2010/03/30 08:38:27  keinstein
 * added rudimentary command line support
 * changed debug system to allow selection of messages via command line
 * further enhancements to the route dialogs
 *
 * Revision 1.1.2.1  2010/01/14 10:16:43  keinstein
 * added output device shapes
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

#ifndef OUTPUTMIDIFILEDEVICESHAPE_H
#define OUTPUTMIDIFILEDEVICESHAPE_H

//#include <map>

//#include "wx/defs.h"
//#include "wx/icon.h"
//#include "wx/stattext.h"

#include "OutputDeviceShape.h"
//#include "Device.h"


class MutOutputMidiFileDeviceShape:public MutOutputDeviceShape
{
public:
	MutOutputMidiFileDeviceShape():MutOutputDeviceShape() {}
	MutOutputMidiFileDeviceShape (wxWindow * parent,
				     wxWindowID id, 
				     OutDevice * d):
		MutOutputDeviceShape() 
		{
			Create (parent,id,d);
		}

	bool Create (wxWindow * parent, wxWindowID id, OutDevice * d)
		{
			DEBUGLOG (other,_T (""));
			bool ret = MutOutputDeviceShape::Create(parent,id,d);
			DEBUGLOG (other,_T (""));
			return ret;
		}

	virtual MutIcon & GetMutIcon () 
		{
			DEBUGLOG(other, _T(""));
			return MidiFileBitmap;
		}

	void SetLabel(const wxString & st ) {
		fileName = st;
		fileName.Normalize();
		MutOutputDeviceShape::SetLabel (fileName.GetFullName());
	}

	virtual wxPanel * GetOutputFilterPanel(wxWindow * parent, Route * route) const;
	virtual void ReadOutputFilterPanel(wxWindow * panel, Route * route);

protected: 
	virtual void InitializeDialog(OutputDevDlg * out) const;
	virtual bool readDialog (OutputDevDlg * out);
	virtual bool CanHandleType (DevType  type) { return type == DTMidiFile; }

	wxFileName fileName;

private:
	DECLARE_DYNAMIC_CLASS(MutOutputMidiFileDeviceShape);

};
#endif				/* OutputMidiFileDeviceShape_H */
/*
 * \}
 */

// -*- C++ -*-
/** \file
 ********************************************************************
 * MIDI input device shape for route window.
 *
 * $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/muwx/Routing/InputMidiDeviceShape.h,v 1.3 2011/02/20 22:35:58 keinstein Exp $
 * \author Rüdiger Krauße <krausze@mail.berlios.de>,
 * Tobias Schlemmer <keinstein@users.berlios.de>
 * \date 2009/11/23
 * $Date: 2011/02/20 22:35:58 $
 * \version $Revision: 1.3 $
 * \license GPL
 *
 * $Log: InputMidiDeviceShape.h,v $
 * Revision 1.3  2011/02/20 22:35:58  keinstein
 * updated license information; some file headers have to be revised, though
 *
 * Revision 1.2  2010-11-21 13:15:49  keinstein
 * merged experimental_tobias
 *
 * Revision 1.1.2.4  2010-03-30 15:57:58  keinstein
 * added editing of existing routes to boxDlg
 *
 * Revision 1.1.2.3  2010/03/30 08:38:27  keinstein
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

#ifndef INPUTMIDIDEVICESHAPE_H
#define INPUTMIDIDEVICESHAPE_H

//#include <map>

//#include "wx/defs.h"
//#include "wx/icon.h"
//#include "wx/stattext.h"

#include "InputDeviceShape.h"
//#include "Device.h"

class MidiInputFilterPanel : public MidiInputFilterPanelBase {
public:
	MidiInputFilterPanel(wxWindow * parent):MidiInputFilterPanelBase(parent) {}
	/**
	 * TODO: set limits according to changes: min.max = max.value and max.min = min.value
	 */
	void SetFromChannel(int current, int min, int max) {
		from_channel->SetRange(min,max);
		from_channel->SetValue(current);
	}
	int GetFromChannel() const{ return from_channel->GetValue(); }
	
	void SetToChannel(int current, int min, int max) {
		to_channel->SetRange(min,max);
		to_channel->SetValue(current);
	}
	int GetToChannel() const{ return to_channel->GetValue(); }
	
	void SetFromKey(int current, int min, int max) {
		from_key->SetRange(min,max);
		from_key->SetValue(current);
	}
	int GetFromKey() const{ return from_key->GetValue(); }
	
	void SetToKey(int current, int min, int max) {
		to_key->SetRange(min,max);
		to_key->SetValue(current);
	}
	int GetToKey() const { return to_key->GetValue(); }
	
	void SetRouteType(RouteType routetype) {
		wxPanel * panel;
		switch (routetype) {
			case RTall: panel = all_panel; break;
			case RTchannel: panel = channel_panel; break;
			case RTstaff: panel = key_panel; break;
			case RTelse: panel = else_panel; break;
			default:
				UNREACHABLEC;
				std::cerr << "MidiInputFilterPanel::SetRouteType: invaid route type " 
				<< routetype << std::endl;
				abort();
		}
		for (size_t i = 0 ; i < type->GetPageCount(); i++) {
			if (type -> GetPage(i) != panel) continue;
			type->SetSelection(i);
		}
	}
	
	RouteType GetRouteType() const {
		wxWindow * window = type->GetCurrentPage();
		if (window == all_panel)
			return RTall;
		else if (window == channel_panel)
			return RTchannel;
		else if (window == key_panel)
			return RTstaff;
		else if (window == else_panel)
				return RTelse;
		else {
			UNREACHABLEC;
			return RTall;
		}
	}
};

class MutInputMidiDeviceShape:public MutInputDeviceShape
{
public:
	MutInputMidiDeviceShape():MutInputDeviceShape() {}
	MutInputMidiDeviceShape (wxWindow * parent,
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
			return MidiInputDevBitmap;
		}
	
	virtual wxPanel * GetInputFilterPanel(wxWindow * parent, Route * route) const;
	virtual void ReadInputFilterPanel(wxWindow * panel, Route * route);


protected: 
	virtual void InitializeDialog(InputDevDlg * in) const;
	virtual bool readDialog (InputDevDlg * in);
	virtual bool CanHandleType (DevType  type) { return type == DTMidiPort; }


private:
	DECLARE_DYNAMIC_CLASS(MutInputMidiDeviceShape);

};

#endif				/* INPUTMIDIDEVICESHAPE_H */
/*
 * \}
 */

// -*- C++ -*-
/** \file
 ********************************************************************
 * Devices Basisklassen.
 *
 * $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/muwx/Routing/OutputGuidoFileDeviceShape.h,v 1.6 2011/11/02 14:32:00 keinstein Exp $
 * \author Rüdiger Krauße <krausze@mail.berlios.de>,
 * Tobias Schlemmer <keinstein@users.berlios.de>
 * \date 1998
 * $Date: 2011/11/02 14:32:00 $
 * \version $Revision: 1.6 $
 * \license GPL
 *
 * $Log: OutputGuidoFileDeviceShape.h,v $
 * Revision 1.6  2011/11/02 14:32:00  keinstein
 * fix some errors crashing Mutabor on Windows
 *
 * Revision 1.5  2011-10-02 16:58:42  keinstein
 * * generate Class debug information when compile in debug mode
 * * InputDeviceClass::Destroy() prevented RouteClass::Destroy() from clearing references -- fixed.
 * * Reenable confirmation dialog when closing document while the logic is active
 * * Change debug flag management to be more debugger friendly
 * * implement automatic route/device deletion check
 * * new debug flag --debug-trace
 * * generate lots of tracing output
 *
 * Revision 1.4  2011-09-27 20:13:25  keinstein
 * * Reworked route editing backend
 * * rewireing is done by RouteClass/GUIRoute now
 * * other classes forward most requests to this pair
 * * many bugfixes
 * * Version change: We are reaching beta phase now
 *
 * Revision 1.3  2011-02-20 22:35:59  keinstein
 * updated license information; some file headers have to be revised, though
 *
 * Revision 1.2  2010-11-21 13:15:50  keinstein
 * merged experimental_tobias
 *
 * Revision 1.1.2.4  2010-04-15 09:28:43  keinstein
 * changing routes works, but is not honoured by MIDI, yet
 *
 * Revision 1.1.2.3  2010/03/30 08:38:27  keinstein
 * added rudimentary command line support
 * changed debug system to allow selection of messages via command line
 * further enhancements to the route dialogs
 *
 * Revision 1.1.2.2  2010/02/15 12:08:21  keinstein
 * intermediate update for backup progress
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

/* we guard a little bit complicated to ensure the references are set right
 */

#if (!defined(MUWX_ROUTING_OUTPUTGUIDOFILEDEVICESHAPE_H) && !defined(PRECOMPILE)) \
	|| (!defined(MUWX_ROUTING_OUTPUTGUIDOFILEDEVICESHAPE_H_PRECOMPILED))
#ifndef PRECOMPILE
#define MUWX_ROUTING_OUTPUTGUIDOFILEDEVICESHAPE_H
#endif

// ---------------------------------------------------------------------------
// headers
// ---------------------------------------------------------------------------

#include "mu32/Defs.h"
#include "muwx/MutIcon.h"
#include "muwx/Routing/OutputDeviceShape.h"
//#include "Device.h"


#ifndef MUWX_ROUTING_OUTPUTGUIDOFILEDEVICESHAPE_H_PRECOMPILED
#define MUWX_ROUTING_OUTPUTGUIDOFILEDEVICESHAPE_H_PRECOMPILED

// system headers which do seldom change

//#include <map>

//#include "wx/defs.h"
//#include "wx/icon.h"
//#include "wx/stattext.h"
namespace mutaborGUI {

	typedef GisOutputFilterPanelBase GisOutputFilterPanel;

	class MutOutputGuidoFileDeviceShape:public MutOutputDeviceShape
	{
		friend class GUIGisFactory;
	protected:
		MutOutputGuidoFileDeviceShape():MutOutputDeviceShape() {}
		MutOutputGuidoFileDeviceShape (wxWindow * parent,
					       wxWindowID id, 
					       mutabor::OutputDevice d):
			MutOutputDeviceShape() {
			Create (parent,id,d);
		}
	public:
		bool Create (wxWindow * parent, wxWindowID id, mutabor::OutputDevice d)
			{
				return MutOutputDeviceShape::Create(parent,id,d);
			}

		virtual MutIcon & GetMutIcon () 
			{
				DEBUGLOG(other, _T(""));
				return GuidoFileBitmap;
			}

		void SetLabel(const wxString & st ) {
			fileName = st;
			fileName.Normalize();
			MutOutputDeviceShape::SetLabel (fileName.GetFullName());
		}
	
		virtual wxPanel * GetOutputFilterPanel(wxWindow * parent, 
						       mutabor::Route & route) const;
		virtual void ReadOutputFilterPanel(wxWindow * panel, 
						   mutabor::Route & route);


	protected: 
		virtual void InitializeDialog(OutputDevDlg * out) const;
		virtual bool readDialog (OutputDevDlg * out);
		virtual bool CanHandleType (mutabor::DevType  type) { 
			return type == mutabor::DTGis; 
		}

		wxFileName fileName;

	private:
		DECLARE_DYNAMIC_CLASS(MutOutputGuidoFileDeviceShape);

	};
}
#endif				/* OUTPUTGUIDOFILEDEVICESHAPE_H_PRECOMPILED */
#endif				/* OUTPUTGUIDOFILEDEVICESHAPE_H */
/*
 * \}
 */

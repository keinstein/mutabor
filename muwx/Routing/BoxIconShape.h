// -*- C++ -*-

/** \file
 ********************************************************************
 * Box icon shape for route window.
 *
 * $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/muwx/Routing/BoxIconShape.h,v 1.8 2011/10/04 17:16:14 keinstein Exp $
 * \author Rüdiger Krauße <krausze@mail.berlios.de>,
 * Tobias Schlemmer <keinstein@users.berlios.de>
 * \date 2009/11/23
 * $Date: 2011/10/04 17:16:14 $
 * \version $Revision: 1.8 $
 * \license GPL
 *
 * $Log: BoxIconShape.h,v $
 * Revision 1.8  2011/10/04 17:16:14  keinstein
 * make program compile on Mac (wx 2.9) and fix some memory corruption
 *
 * Revision 1.7  2011-10-03 15:50:21  keinstein
 * Fix focus issues in the route window. This includes:
 *  * Using templates to describe the base class of MutIconShape.
 *  * Rename MutIconShape->MutIconShapeClass.
 *  * typedef MutIconShapeClass<wxControl> MutIconShape
 *  * Expand the control container macros in MutPanel.
 *  * Disable most of the control container behaviour as we don't need it, currently
 *  * Focus NewInputDevice on window creation.
 *  * MutBoxChannelShape focuses its parent on focus (which can be done only by mouse so far).
 *  * Display focused Window with sunken border
 *
 * Revision 1.6  2011-09-30 18:07:05  keinstein
 * * make compile on windows
 * * s/wxASSERT/mutASSERT/g to get assert handler completely removed
 * * add ax_boost_base for boost detection
 *
 * Revision 1.5  2011-09-27 20:13:24  keinstein
 * * Reworked route editing backend
 * * rewireing is done by RouteClass/GUIRoute now
 * * other classes forward most requests to this pair
 * * many bugfixes
 * * Version change: We are reaching beta phase now
 *
 * Revision 1.4  2011-09-08 16:51:21  keinstein
 * Set foreground color in box status windows
 * Fix updating box status windows
 * update RtMidi (includes Jack compilation mode)
 *
 * Revision 1.3  2011-02-20 22:35:58  keinstein
 * updated license information; some file headers have to be revised, though
 *
 * Revision 1.2  2010-11-21 13:15:48  keinstein
 * merged experimental_tobias
 *
 * Revision 1.1.2.3  2010-02-15 12:08:21  keinstein
 * intermediate update for backup progress
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

#if (!defined(MUWX_ROUTING_BOXICONSHAPE_H) && !defined(PRECOMPILE)) \
	|| (!defined(MUWX_ROUTING_BOXICONSHAPE_H_PRECOMPILED))
#ifndef PRECOMPILE
#define MUWX_ROUTING_BOXICONSHAPE_H
#endif

// ---------------------------------------------------------------------------
// headers
// ---------------------------------------------------------------------------

#include "Defs.h"
#include "IconShape.h"
#include "RouteIcons.h"

#ifndef MUWX_ROUTING_BOXICONSHAPE_H_PRECOMPILED
#define MUWX_ROUTING_BOXICONSHAPE_H_PRECOMPILED

// system headers which do seldom change

//#include <map>

//#include "wx/defs.h"
//#include "wx/icon.h"
//#include "wx/stattext.h"

//#include "Device.h"

namespace mutaborGUI {
	class MutBoxIconShape:public MutIconShapeClass<MutPanel>
	{
	public:
		MutBoxIconShape():MutIconShapeClass<MutPanel>() {}
	
		MutBoxIconShape(wxWindow * parent, wxWindowID id = wxID_ANY):
			MutIconShapeClass<MutPanel>() 
			{
				Create (parent, id);
			}

		virtual ~MutBoxIconShape() {}
	
		bool Create (wxWindow * parent = NULL, wxWindowID id = wxID_ANY)
			{
				return MutIconShapeClass<MutPanel>::Create(parent, id);
			}

		virtual bool SetForegroundColour (const wxColour & colour) 
			{
				if (staticText)
					staticText->SetForegroundColour(colour);
				return MutIconShapeClass<MutPanel>::SetForegroundColour(colour);
			}

		/*  bool Create( wxWindow *parent,
		    wxWindowID id,
		    const wxString &label,
		    const wxPoint &pos = wxDefaultPosition,
		    const wxSize &size = wxDefaultSize,
		    long style = 0,
		    const wxString &name = wxStaticBoxNameStr );
		*/

		void GetBordersForSizer(int &borderTop, int &borderOther) const;
 
		virtual void OnDraw (wxDC & dc);
		virtual bool Layout();

		MutIcon & GetMutIcon () {
			mutASSERT(BoxBitmap.IsOk());
			return BoxBitmap;
		}



		// returning true from here ensures that we act as a container window for
		// our children
		//virtual bool IsStaticBox() const { return true; }
	
	private: 
	};

}
#endif				/* BOXICONSHAPE_H_PRECOMPILED */
#endif				/* BOXICONSHAPE_H */
/*
 * \}
 */

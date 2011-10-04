// -*- C++ -*-
/** \file
 ********************************************************************
 * Box shape for route window.
 *
 * $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/muwx/Routing/BoxShape.h,v 1.9 2011/10/04 05:38:44 keinstein Exp $
 * \author Rüdiger Krauße <krausze@mail.berlios.de>,
 * Tobias Schlemmer <keinstein@users.berlios.de>
 * \date 1998
 * $Date: 2011/10/04 05:38:44 $
 * \version $Revision: 1.9 $
 * \license GPL
 *
 * $Log: BoxShape.h,v $
 * Revision 1.9  2011/10/04 05:38:44  keinstein
 * some configuration fixes
 *
 * Revision 1.8  2011-10-03 17:42:41  keinstein
 * Open the configuration dialog on key press in the route window
 * Accept entering nothing in the input/output device dialog
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
 * Revision 1.6  2011-10-02 16:58:42  keinstein
 * * generate Class debug information when compile in debug mode
 * * InputDeviceClass::Destroy() prevented RouteClass::Destroy() from clearing references -- fixed.
 * * Reenable confirmation dialog when closing document while the logic is active
 * * Change debug flag management to be more debugger friendly
 * * implement automatic route/device deletion check
 * * new debug flag --debug-trace
 * * generate lots of tracing output
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
 * Revision 1.1.2.8  2010-11-14 21:28:38  keinstein
 * implement loading and saving old files with new routing system
 *
 * Revision 1.1.2.7  2010-08-10 15:54:30  keinstein
 * new, direct route configuration on init
 *
 * Revision 1.1.2.6  2010/06/15 14:30:14  keinstein
 * allow deleting of input devices in route window
 * several bug fixes
 * rudimentary box deletion support
 *
 * Revision 1.1.2.5  2010/06/02 11:20:09  keinstein
 * Route.h:
 * 	new enum BoxType
 * 	new box type NewBox
 *
 * IconShape.cpp:
 * 	Hide shape in MutIconShape::DeleteSelf
 *
 * MutChild.h:
 * 	Changes on the increment value for Clientsize
 *
 * MutLogicWnd:
 * 	smaller whitespace fixes
 *
 * MutRouteWnd.cpp:
 * 	save sizerflags for MutBoxShape too
 *
 * BoxChannelShape.cpp:
 * 	rename CreateRouteShape to CreateRoutePanel
 * 	replace some wxDynamicCast by dynamic_cast
 * 	add Box “New Box“ if current box is not found
 * 	delete Route if route panel is disabled
 *
 * BoxChannelShape.h:
 * 	Update BoxShape layout  if necessary
 *
 * BoxDlg.cpp:
 * 	RoutePanel::AddBox: allow NULL boxShape
 * 	Fix Bug that didn't preselect GUIDO boxes and Through mode
 *
 * BoxShape.cpp:
 * 	fix color mapping for box numbers (shift right by 1 bit).
 * 	Add MutBoxShape::sizerFlags
 * 	SetBoxId: New function
 * 	Use SetBoxId for setting Box Id an Label in sync
 * 	AddChannel: call Layout()
 * 	implement replacement in DoLeftDblClick (enables New Box)
 * 	ShowBoxDialog: use dynamic_cast
 * 	ReadDialog: Add Channel only if new route is enabled (not deleted)
 * 	ReplaceSelfBy: new function (Unreachable as only needed for
 * 		class NewMutBoxShape)
 *
 * NewBoxShape.cpp/.h:
 * 	replaceSelfBy: new function
 * 	initialize Box id as NewBox
 *
 * *.po/mutabor.pot/ *.gmo
 *  	Sync with sources
 *
 * Revision 1.1.2.4  2010/03/30 08:40:15  keinstein
 * added rudimentary command line support
 * changed debug system to allow selection of messages via command line
 * further enhancements to the route dialogs
 *
 * Revision 1.1.2.3  2010/02/15 12:08:21  keinstein
 * intermediate update for backup progress
 *
 * Revision 1.1.2.2  2010/01/11 12:51:52  keinstein
 * fix some problems due to splitting MutRouteShapes.{cpp,h}
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

#if (!defined(MUWX_ROUTING_BOXSHAPE_H) && !defined(PRECOMPILE)) \
	|| (!defined(MUWX_ROUTING_BOXSHAPE_H_PRECOMPILED))
#ifndef PRECOMPILE
#define MUWX_ROUTING_BOXSHAPE_H
#endif

// ---------------------------------------------------------------------------
// headers
// ---------------------------------------------------------------------------

#include "Defs.h"
#include "GUIBoxData.h"
#include "GUIRoute.h"
#include "muwx/Routing/BoxChannelShape.h"
#include "BoxIconShape.h"
#include "Device.h"

#ifndef MUWX_ROUTING_BOXSHAPE_H_PRECOMPILED
#define MUWX_ROUTING_BOXSHAPE_H_PRECOMPILED

// system headers which do seldom change
// we must break some recursion
//#include <map>

//#include "wx/defs.h"
//#include "wx/icon.h"
//#include "wx/stattext.h"

#include "wx/colour.h"
#include "wx/sizer.h"

namespace mutaborGUI {
	class BoxDlg;
	class MutBoxChannelShape;
	class MutOutputDeviceShape;
	class RoutePanel;

	const wxColour & BoxColour(int nr);
	const wxColour & BoxTextColour(int nr);
	void initBoxColours();

	class MutBoxShape:public MutBoxIconShape
	{
	protected:
		MutBoxIconShape * m_icon;
		wxSizer * channels;
		static wxSizerFlags sizerFlags;
		int boxId;
		static int maxBoxId;
	
	public:
		MutBoxShape():MutBoxIconShape(),m_icon(NULL),channels(NULL),
			      boxId(NoBox) {}

		MutBoxShape(wxStaticBox *box, int orient):
			MutBoxIconShape()
			{
				STUBC;
			}

		MutBoxShape(wxWindow * parent,wxWindowID wid, int Id = NoBox):
			MutBoxIconShape()
			{
				Create(parent,wid,Id);
			}
  
		virtual ~MutBoxShape()
			{ 
//		delete channels; 
			}
	
		bool Create(wxWindow * parent,wxWindowID wid, int Id = NoBox);

		static void SetSizerFlags (wxSizerFlags flags) {sizerFlags = flags; }
		static const wxSizerFlags & GetSizerFlags() { return sizerFlags; }

		virtual void DoLeftDblClick();

		virtual void SetFocus() {
			SetFocusIgnoringChildren();
			UpdateBorder(wxBORDER_SUNKEN);
		}

		virtual bool SetBackgroundColour(const wxColour& colour);
		/// Get a double click and prepare for execution of the command
		/** Since programs might produce segmentation faults
		    when the object is deleted during processing of mouse
		    events, we send us a new event using the event queue.
		*/
		void LeftDblClickEvent (wxMouseEvent & event) { 
			wxCommandEvent command(wxEVT_COMMAND_MENU_SELECTED,
					       CM_LEFT_DOUBLE_CLICK); 
			wxPostEvent(this,command); 
		}
		/// Process a double click
		/** Since programs might produce segmentation faults
		    when the object is deleted during processing of mouse
		    events, we send us a new event using the event queue.
		*/
		void CmLeftDblClick (wxCommandEvent& event) {
			DoLeftDblClick(); 
		}

		void OnKeyDown (wxKeyEvent & event);

		BoxDlg * ShowBoxDialog() const;
		virtual void InitializeDialog(BoxDlg * dlg) const;

		
		virtual MutBoxChannelShape * AddChannel(mutabor::Route & route);
		virtual MutBoxChannelShape * AddChannel(RoutePanel * panel);

		virtual MutBoxChannelShape * Add(MutBoxChannelShape * channel);
		virtual bool Remove(MutBoxChannelShape * shape);
	
		virtual bool HasChannel(const mutabor::Route & route);

		virtual void AddPossibleOutput(MutOutputDeviceShape * device);
	

//	virtual void SetLabel(const wxString &s);

//	virtual void RecalcSizes();
//	virtual wxSize CalcMin();

		//  override to hide/show the static box as well
//	virtual void ShowItems (bool show);

		virtual void Add(BoxData * box);
		virtual bool Remove(BoxData * box);
		
		void Attatch(BoxData * box) {
			box->Attatch(this);
		}
		bool Detatch(BoxData * box) {
			return box->Detatch(this);
		}
		bool Delete(BoxData * box) {
			return box->Delete(this);
		}

		virtual void DrawLines(wxDC & dc, const wxRect & screenpos);
  
		virtual bool Detach( wxWindow *window );
		virtual bool Detach( wxSizer *sizer ) 
			{
				if (channels) 
					return channels -> Detach(sizer); 
				else 
					return false;
			}
		virtual bool Detach( int index ) 
			{ 
				if (channels) 
					return channels -> Detach(index);
				else 
					return false;
			}
		virtual bool replaceSelfBy (MutBoxShape  * newshape);
		virtual bool DetachBox ();
	
		virtual bool readDialog (BoxDlg * box);
		virtual bool CanHandleType (int  type) { return true; }
		int GetBoxId() const { return boxId; }

		wxSizer * GetChannels() const { return channels; }
	private:
		void SetBoxId(int Id, bool layout=true);
		DECLARE_CLASS(MutBoxShape)
		DECLARE_EVENT_TABLE();
	};

	typedef std::list <MutBoxShape *> MutBoxShapeList;

}
#endif				/* BOXSHAPE_H_PRECOMPILED */
#endif				/* BOXSHAPE_H */
/*
 * \}
 */

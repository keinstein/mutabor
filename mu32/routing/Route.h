// -*- C++ -*-

/** \file
 ********************************************************************
 * Routing. Mutabor Core.
 *
 * $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/mu32/routing/Route.h,v 1.2 2010/11/21 13:15:46 keinstein Exp $
 * \author Rüdiger Krauße <krausze@mail.berlios.de>,
 * Tobias Schlemmer <keinstein@users.berlios.de>
 * \date 1998
 * $Date: 2010/11/21 13:15:46 $
 * \version $Revision: 1.2 $
 *
 * $Log: Route.h,v $
 * Revision 1.2  2010/11/21 13:15:46  keinstein
 * merged experimental_tobias
 *
 * Revision 1.1.2.4  2010-09-29 13:03:30  keinstein
 * config can be stored and restored with new treeconfig
 *
 * Revision 1.1.2.3  2010-09-15 17:58:01  keinstein
 * old configuration can be loaded again.
 *
 * Revision 1.1.2.2  2010-08-10 15:54:29  keinstein
 * new, direct route configuration on init
 *
 * Revision 1.3.2.9  2010-07-06 09:06:26  keinstein
 * allow empty input and output devices in routes
 *
 * Revision 1.3.2.8  2010/06/15 14:30:14  keinstein
 * allow deleting of input devices in route window
 * several bug fixes
 * rudimentary box deletion support
 *
 * Revision 1.3.2.7  2010/06/02 11:20:08  keinstein
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
 * Revision 1.3.2.6  2010/04/15 09:28:43  keinstein
 * changing routes works, but is not honoured by MIDI, yet
 *
 * Revision 1.3.2.5  2010/03/30 15:57:58  keinstein
 * added editing of existing routes to boxDlg
 *
 * Revision 1.3.2.4  2010/03/30 08:40:15  keinstein
 * added rudimentary command line support
 * changed debug system to allow selection of messages via command line
 * further enhancements to the route dialogs
 *
 * Revision 1.3.2.3  2010/02/15 12:08:20  keinstein
 * intermediate update for backup progress
 *
 * Revision 1.3.2.2  2010/01/14 09:34:24  keinstein
 * Checkin searching for a bug
 *
 * Revision 1.3.2.1  2009/08/04 11:30:49  keinstein
 * removed mut.h
 *
 *
 ********************************************************************
 *\addtogroup route
 *\{
 ********************************************************************/

#ifndef MUTABOR_ROUTE_H
#define MUTABOR_ROUTE_H

#include "Defs.h"

#ifdef WX
#include "wx/config.h"
#endif

#include "treestorage.h"
// Route ------------------------------------------------------------


enum BoxType
{
	NewBox = -3,
	NoBox,
	GmnBox,
	Box0
};

/// Type of route input filter
enum RouteType
{
        RTall, RTelse, RTchannel, RTstaff
};

extern const mutString RTName[];

class OutDevice;
class InDevice;

class Route
{
	// private members: access only via access functions for debugging purposes
	/*
        void * userdata;
	Route *Next;
	OutDevice *Out;
	 */
	WATCHEDPTR(void,routing,Route) userdata;
	WATCHEDPTR(Route,routing,Route) Next;
	WATCHEDPTR(OutDevice,routing,Route) Out;
	WATCHEDPTR(InDevice,routing,Route) In;
	WATCHEDPTR(Route,routing,Route) globalNext;
	static WATCHEDPTR(Route,routing,Route) routeList;
	int Id;
	int inputid;
	int outputid;
public:
	RouteType Type;
	int IFrom, ITo;
	int Box;
	bool Active;
	int OFrom, OTo;
	bool ONoDrum;
        static int maxRouteId;



	Route(
	      InDevice * in = NULL,
	      OutDevice *out = NULL,
	      RouteType type = RTall,
	      int iFrom = -1,
	      int iTo = -1,
	      int box = -1,
	      bool active = false,
	      int oFrom = -1,
	      int oTo = -1,
	      bool oNoDrum = true,
	      Route *next = 0):userdata(this,_T("userdata")),
	Next(this,_T("Next"),next),
	Out(this,_T("Out"),out),
	In(this,_T("In"),in),
	globalNext(this,_T("Global Next"),NULL)
	{
		Type = type;
		IFrom = iFrom;
		ITo = iTo;
		Box = box;
		Active = active;
		OFrom = oFrom;
		OTo = oTo;
		ONoDrum = oNoDrum;
		Id = NextRouteId();
		AppendToRouteList(this);
	}

	virtual ~Route()
	{
		DEBUGLOG(routing,_T("deleting chain from %p"));
		if ( Next ) delete Next;
		DEBUGLOG(routing,_T("deleting %p"));
		RemoveFromRouteList(this);
	}

	/// Write the route settings into a tree based configuration.
	/** \argument config (tree_storage &) configuration where the route settings will be stored
	 */
	virtual void Save(tree_storage & config);

	/// Read the route into from a tree based configuration.
	/** \argument config (tree_storage &) configuration where the route settings will be read from
	 */
	virtual void Load(tree_storage & config);
	
        static unsigned int NextRouteId() {
                return maxRouteId++;
        }


	char Check(int i)
	{
		return (IFrom <= i && i <= ITo);
	}
        
        void setUserData (void * data) 
	{ 
		userdata = data; 
	}

        void * getUserData() const 
	{ 
		return userdata; 
	}

	OutDevice  * GetOutDevice() const {
		return Out;
	}

	void SetOutDevice (OutDevice * out) 
	{
		Out = out;
	}
	
	InDevice  * GetInDevice() const {
		return In;
	}
	
	void SetInDevice (InDevice * in) 
	{
		In = in;
		for (Route * route = GetNext(); route; route=route->GetNext())
			route -> In = in;
	}
	
	void SetInputId(int Id)
	{
		inputid = Id;
	}
	
	
	bool GetActive() const 
	{
		return Active;
	}
	
	void SetActive(bool active) 
	{
		Active = active;
	}
	
	int GetBox() const
	{
		return Box;
	}
	
	void SetBox(int box)
	{
		Box = box;
	}
	
	RouteType GetType() const
	{
		return Type;
	}
	
	void SetType(RouteType type)
	{
		Type = type;
	}
	
	const mutString & GetTypeName()
	{
		return RTName[Type];
	}
	
	int GetInputFrom() const
	{
		return IFrom;
	}
	
	void SetInputFrom(int i)
	{
		IFrom = i;
	}
	
	int GetOutputFrom() const
	{
		return OFrom;
	}
	
	void SetOutputFrom(int o)
	{
		OFrom = o;
	}
	
	int GetInputTo() const
	{
		return ITo;
	}
	
	void SetInputTo(int i)
	{
		ITo = i;
	}
	
	int GetOutputTo() const
	{
		return OTo;
	}
	
	void SetOutputTo(int o)
	{
		OTo = o;
	}
	
	
	bool OutputAvoidDrumChannel() const
	{
		return ONoDrum;
	}
	void OutputAvoidDrumChannel(bool avoid) 
	{
		ONoDrum = avoid;
	}
	
	Route * GetNext() const
	{
		return Next;
	}
	void SetNext(Route * route)
	{
		Next = route;
		for (Route * r = GetNext(); r; r=r->GetNext())
			r -> In = In;
	}
	
	int GetId() const
	{
		return Id;
	}
	
	static Route * GetRouteList() 
	{
		return routeList;
	}
	
	Route * GetGlobalNext()
	{
		return globalNext;
	}
	
	/// Initialize the internal device identifiers.
	/** This function sets the internal device ids of 
	 *  all input devices, starting from 0 and 
	 *  incrementing by 1
	 */
	static void InitializeIds();

	/// Save the current routes in a tree storage.
	/** This function saves all routes in a tree based storage.
	 *  \argument config (tree_storage *) storage driver to use for saving.
	 */
	static void SaveRoutes(tree_storage & config);

	/// Load the current routes from a tree storage.
	/** This function loads all routs from a tree based storage.
	 *  \argument config (tree_storage *) storage driver to use for saving.
	 */
	static void LoadRoutes(tree_storage & config);
protected:
	static void AppendToRouteList (Route * route);
	static void RemoveFromRouteList (Route * route);
};

extern const mutString DevTypeName[];

/// load the routes from a tree based configuration
/** \param config conifiguration to be read from
 */
void LoadRoutes(tree_storage & config);

/// write the routes to the configuration
/** \param config configuration to be written to
 */
void SaveRoutes(tree_storage & config);


#endif

/*
 * \}
 */


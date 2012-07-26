/** \file
 ********************************************************************
 * Devices Basisklassen.
 *
 * $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/mu32/EDevice.h,v 1.13 2011/09/27 20:13:21 keinstein Exp $
 * \author Rüdiger Krauße <krausze@mail.berlios.de>
 * Tobias Schlemmer <keinstein@users.berlios.de>
 * \date $Date: 2011/09/27 20:13:21 $
 * \version $Revision: 1.13 $
 * \license GPL
 *
 * $Log: EDevice.h,v $
 * Revision 1.13  2011/09/27 20:13:21  keinstein
 * * Reworked route editing backend
 * * rewireing is done by RouteClass/GUIRoute now
 * * other classes forward most requests to this pair
 * * many bugfixes
 * * Version change: We are reaching beta phase now
 *
 * Revision 1.12  2011-09-05 11:30:07  keinstein
 * Some code cleanups moving some global box arrays into class mutaborGUI::BoxData
 * Restore perspective on logic start
 *
 * Revision 1.11  2011-02-20 22:35:55  keinstein
 * updated license information; some file headers have to be revised, though
 *
 * Revision 1.10  2010-11-21 13:15:44  keinstein
 * merged experimental_tobias
 *
 * Revision 1.9.2.5  2010-09-29 13:03:30  keinstein
 * config can be stored and restored with new treeconfig
 *
 * Revision 1.9.2.4  2010-09-15 17:58:01  keinstein
 * old configuration can be loaded again.
 *
 * Revision 1.9.2.3  2010-08-10 15:54:29  keinstein
 * new, direct route configuration on init
 *
 * Revision 1.9.2.2  2010/03/30 08:38:27  keinstein
 * added rudimentary command line support
 * changed debug system to allow selection of messages via command line
 * further enhancements to the route dialogs
 *
 * Revision 1.9.2.1  2009/08/04 11:30:49  keinstein
 * removed mut.h
 *
 * Revision 1.9  2008/10/01 09:28:25  keinstein
 * Better multibyte wxString support
 *
 * Revision 1.8  2008/07/21 08:59:38  keinstein
 * recoded
 * Use symbolic enum values for device modes.
 *
 * Revision 1.7  2008/06/30 08:07:45  keinstein
 * Get default port name only if midi devices are attached on startup to prevent crashes
 * Check for device existence when routes are created.
 *
 * Revision 1.6  2008/03/11 10:37:34  keinstein
 * Holyday edition
 * put CM_xxx in an enum
 * use wx constants
 * document mutframe
 * some white space formattings
 * make route saving more system specific
 * many other fixes
 *
 * Revision 1.5  2008/01/25 09:07:48  keinstein
 * Make route file reading/writing wchar compatible
 * charset conversion
 * Read and write routes to wxConfigBase compatible config files
 *
 * Revision 1.4  2005/11/10 17:54:01  keinstein
 * created debian installer
 *
 * Revision 1.3  2005/11/07 19:42:54  keinstein
 * Some additional changes
 *
 ********************************************************************
 *\addtogroup route
 *\{
 ********************************************************************/

#ifndef EDEVICE_H
#define EDEVICE_H

#include <cstring>
#include "Global.h"

#include "wx/string.h"
#include "wx/config.h"
#include "Device.h"
#include "DevGIS.h"
#include "DevMidi.h"
#include "DevMidF.h"
#include "Runtime.h"

class EDevice;

/// input devices for GUI

extern EDevice *InEDevices;

/// output devices for GUI
extern EDevice *OutEDevices;

#define INIT_BENDINGRANGE 2

// Route ------------------------------------------------------------

/// defind two box types;
#define NoBox  -2
#define GmnBox -1

/// linked list of routes
/** \TODO inherit from Route
 */

class ERoute
{

public:
	/// next element
	ERoute *Next;
	/// identifier
	char Id;
	/// type
	RouteType Type;
	/// input start channel
	int IFrom;
	/// input end channel
	int ITo;
	/// Mutabor box
	int Box;
	/// shall the box be controlled by the events?
	bool Active;
	/// output device
	EDevice *Out;
	/// output start channel
	int OFrom;
	/// output end channel
	int OTo;
	/// avoid drum channel?
	bool ONoDrum;

	/// constructor
	/**
	    \param type device type
	    \param iFrom input starting channel
	    \param iTo input end channel
	    \param box box which shall act on the stream
	    \param active shall the stream modify the state of the mutabor box?
	    \param out output device
	    \param oFrom output starting channel
	    \param oTo output end channel
	    \param oNoDrum avoid drum channel
	*/
	ERoute(RouteType type,
	       int iFrom, int iTo,
	       int box, bool active,
	       EDevice *out, int oFrom = -1, int oTo = -1, bool oNoDrum = true)
	{
		Type = type;
		IFrom = iFrom;
		ITo = iTo;
		Box = box;
		Active = active;
		Out = out;
		OFrom = oFrom;
		OTo = oTo;
		ONoDrum = oNoDrum;
		Next = 0;
	}

	/// destructor
	/** Deletes descendents
	 */
	~ERoute()
	{
		if ( Next ) delete Next;
	}

	/// create a new Route containing our data.
	/** \return pointer to the new route
	 */
	Route * newRoute();
};

/// linked list of devices
/** \TODO inherit from InDevice/OutDevice
 */

class EDevice
{

public:
	/// next device
	EDevice *Next;
	/// name of the device
	wxString Name;
	/// type of the device
	DevType DT;
	/// routes, which are influenced by the device
	ERoute *Routes;
	/// identifier
	int DevId;
	/// Bending range of the output device
	int BendingRange;
	/// Number
	int Nr;
	/// Mode
	MutaborModeType Mode;

	/// Constructor
	/**
	   This constructor disables any special effects.
	   \param dt device type
	   \param name name of the device
	   \param devId identifier of the device
	*/

	EDevice(DevType dt, const wxString& name = wxEmptyString, int devId = 0)
	{
		DT = dt;
		Name = name;
		Next = 0;
		Routes = 0;
		DevId = devId;
		BendingRange = INIT_BENDINGRANGE;
		Mode = MutaborDeviceUnregistered;
		Nr = -1;
	}

	/// Destructor
	/**
	    Remove the routes if necessary.
	    Delete the tail of the list before quitting.
	*/
	~EDevice()
	{
		if ( Routes )
			delete Routes;

		if ( Next )
			delete Next;
	}

	/// find a route to a given number
	/**
	   \param nr Index indicating which route to return
	*/
	ERoute *GetRoute(int nr);

	/// return the number of routes.
	/**
	   \return number of routes associated with the device
	*/
	int nRoutes();

	/// adds a route to the device
	/**
	    \param route route to be added;
	*/
	void AddRoute(ERoute *route);

	/// return the name of the device
	/** This function returns the name of the device.  All spaces (' ')
	    are replaced by '_'.
	    \return name of the device.
	 */
	wxString GetName(); // mit ' ' -> '_'

	/// return an output device
	/** This function creates an output device according to the
	    current configuration */
	OutDevice * newOutDevice()
	{
		DEBUGLOG(other,_T("Device Type: %d"),DT);
		switch (DT) {
			case DTNotSet:
				wxLogError(_("Device type not set"));
				return NULL;

			case DTUnknown:
				wxLogError(_("Unknown device."));
				return NULL;
				break;
				//3 ??
				
			case DTGis:
				STUBC;
				return new OutGis(Name,0);
				break;
				
			case DTMidiPort:
				return new OutMidiPort(Name, DevId, BendingRange);
				break;

			case DTMidiFile:
				return new OutMidiFile(Name, DevId, BendingRange);
				break;
				
			default:
				UNREACHABLEC;
				wxLogError(_("Unknown device type %d."), DT);
				return NULL;
		}
	}

	/// return an input device
	/** This function creates an input device according to the
	    current configuration */
	InDevice * newInDevice()
	{
		switch (DT) {

		case DTNotSet:
			wxLogError(_("Device type not set"));

			return NULL;

		case DTUnknown:
			wxLogError(_("Unknown device."));

			return NULL;

			//3 ??

		case DTGis:
			Mode = MutaborDeviceStop;

			return new InGis(Name, _T("GIS"));

			break;

		case DTMidiPort:
			return new InMidiPort(Name, DevId);

			break;

		case DTMidiFile:
			Mode = MutaborDeviceStop;

			return new InMidiFile(Name, 0);

			break;

		default:
			wxLogError(_("Unknown device type %d."),DT);

			return NULL;
		}
	}

};

// Funktionen -------------------------------------------------------
inline Route * ERoute::newRoute()
{
	if (Box == -2)
		Active = false;

	OutDevice * o;

	if (Out) o = GetOut(Out->DevId);
	else o = NULL;

#ifdef DEBUG
	DEBUGLOG(other,_T("Out: %x, o: %x"),Out,o);

#endif
	return new Route(NULL, o, 
			 Type,
	                 IFrom, ITo,
	                 Box, Active,
			 OFrom, OTo, ONoDrum);

}

/// create a new device.
/**
   \param List list where the device should be added
   \param dt type of the new device
   \param name name of the new device
   \param devId identifier of the new device
   \param oldPos old position of the device (will be removed or overwritten)
   \param newPos new position of the devices
*/
EDevice* NewDevice(EDevice **List,
                   DevType dt,
                   const wxString& name,
                   int devId,
                   EDevice *oldPos = 0,
                   EDevice *newPos = 0);

/// read the routes from the configuration
/** \param config configuration to be read
 */
void ScanRoutes(char *config);

/// read the routes from the configuration
/** \param config configuration to be read
 */
void ScanRoutes(const wxString& config);

/// read the routes from the configuration
/** \param config configuration to be read
 */
void ScanRoutes(wxConfigBase * config);

/// write the routes to the configuration
/** \param config configuration to be written to
 */
void WriteRoutes(char **config);

/// write the routes to the configuration
/** \param config configuration to be written to
 */
void WriteRoutes(wxString &config);

/// write the routes to the configuration
/** \param config configuration to be written to
 */
void WriteRoutes(wxConfigBase *config);

/// which mutabor boxes are used at all?
extern bool mut_box[MAX_BOX].used;

/// synchronizes \c BoxUsed with the routes
void CheckBoxesUsed();

/// translate the GUI routing information to mutabor
void ScanDevices();

#endif /* EDEVICE_H */
/** \} */

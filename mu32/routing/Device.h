// -*- C++ -*-

/** \file
 ********************************************************************
 * Routing. Mutoabor Core.
 *
 * $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/mu32/routing/Device.h,v 1.4 2010/12/13 00:27:53 keinstein Exp $
 * \author Rüdiger Krauße <krausze@mail.berlios.de>,
 * Tobias Schlemmer <keinstein@users.berlios.de>
 * \date 1998
 * $Date: 2010/12/13 00:27:53 $
 * \version $Revision: 1.4 $
 *
 * $Log: Device.h,v $
 * Revision 1.4  2010/12/13 00:27:53  keinstein
 * compiles in linux as well as in mingw
 *
 * Revision 1.3  2010-11-21 23:39:00  keinstein
 * some corrections for allowing debuild to complete
 *
 * Revision 1.2  2010-11-21 13:15:45  keinstein
 * merged experimental_tobias
 *
 * Revision 1.1.2.7  2010-11-18 21:46:14  keinstein
 * MutFrame: get rid of OnIdle (this may break something, but saves much more CPU cycles
 * Some further steps to get rid of EDevice*
 *
 * Revision 1.1.2.6  2010-11-14 21:28:38  keinstein
 * implement loading and saving old files with new routing system
 *
 * Revision 1.1.2.5  2010-09-29 15:06:40  keinstein
 * Reset config before saving routing information and fix two bugs concerned with the deletion of boxes
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
 * Revision 1.9.2.13  2010-07-06 09:06:26  keinstein
 * allow empty input and output devices in routes
 *
 * Revision 1.9.2.12  2010/06/22 15:05:45  keinstein
 * debugging segfault in route check after replacement of MutOutputDevice
 *
 * Revision 1.9.2.11  2010/06/21 14:28:12  keinstein
 * implement deletion of output devices
 *
 * Revision 1.9.2.10  2010/06/15 14:30:14  keinstein
 * allow deleting of input devices in route window
 * several bug fixes
 * rudimentary box deletion support
 *
 * Revision 1.9.2.9  2010/05/07 11:40:27  keinstein
 * actual_settings
 *
 * Revision 1.9.2.8  2010/04/26 15:53:05  keinstein
 * BoxDlg reacts on “Remove Route”. Implementation of routing must be checked.;
 *
 * Revision 1.9.2.7  2010/04/20 17:41:38  keinstein
 * One step towards using Mutabor: Activation of a logic now honours the state of the Device Editor.
 *
 * Revision 1.9.2.6  2010/04/15 09:28:43  keinstein
 * changing routes works, but is not honoured by MIDI, yet
 *
 * Revision 1.9.2.5  2010/03/30 08:40:15  keinstein
 * added rudimentary command line support
 * changed debug system to allow selection of messages via command line
 * further enhancements to the route dialogs
 *
 * Revision 1.9.2.4  2010/02/15 12:08:20  keinstein
 * intermediate update for backup progress
 *
 * Revision 1.9.2.3  2010/01/14 09:34:24  keinstein
 * Checkin searching for a bug
 *
 * Revision 1.9.2.2  2009/11/03 12:39:30  keinstein
 * input device dialog: Allow to edit input devices
 * fix a bug on Mac OS X, that prevented Mutabor from starting if no MIDI device is availlable
 *
 * Revision 1.9.2.1  2009/08/04 11:30:49  keinstein
 * removed mut.h
 *
 *
 ********************************************************************
 *\addtogroup route
 *\{
 ********************************************************************/



#ifndef DEVICE_H
#define DEVICE_H

#include "Defs.h"

#define DRUMCHANNEL 9  // Schlagzeugkanal bei General Midi (Kanal 9, bzw. 10)

enum MutaborModeType {
        MutaborDeviceUnregistered = -1,
        MutaborDeviceStop,
        MutaborDevicePlay,
        MutaborDevicePause,
        MutaborDeviceCompileError,
        MutaborDeviceTimingError
};

#include "GIS.h"
#include "Route.h"
#include "wx/stopwatch.h"



class OutDevice;

class InDevice;

extern char InDevChanged;

// Device Typen
enum DevType
{
        DTNotSet = -1, DTUnknown, DTMidiPort, DTMidiFile, DTGis
};

#define DeviceMaxType DTGis+1

// channel data -----------------------------------------------------

class ChannelData
{

public:
	int Sound;          // -1 = noch nicht verwendet
	char Sustain;
	int BankSelectMSB;  // -1 .. noch nicht benutzt
	int BankSelectLSB;  // -1 .. noch nicht benutzt
	long Pitch;         // 0 = ungepitcht, kann durchaus auch negativ sein
	ChannelData(int sound = -1, char sustain = 0)
	{
		Sound = sound;
		Sustain = sustain;
		BankSelectMSB = -1;
		BankSelectLSB = -1;
		Pitch = 0;
	}

	void Reset()
	{
		Sound = -1;
		Sustain = 0;
		BankSelectMSB = -1;
		BankSelectLSB = -1;
	}

	bool operator ==(ChannelData &cd)
	{
		return ( Sound == -1 || cd.Sound == -1 || Sound == cd.Sound ) &&
		       ( Sustain == -1 || cd.Sustain == -1 || Sustain == cd.Sustain ) &&
		       ( BankSelectMSB == -1 || cd.BankSelectMSB == -1 || BankSelectMSB == cd.BankSelectMSB ) &&
		       ( BankSelectLSB == -1 || cd.BankSelectLSB == -1 || BankSelectLSB == cd.BankSelectLSB );
	}
};


class Device
{
private:
        void * userdata;
	int Id;
protected:
	int DevId;
	mutString Name;
public:
	
        Device():userdata(NULL),Id(-1),DevId(-1),Name(mutEmptyString) { }
	
	Device(int id, int devid, mutString name = mutEmptyString):userdata(NULL),Id(id),DevId(devid),Name(name) {}
	
	virtual ~Device() {	}
	
	/// Save current device settings in a tree storage
	/** \argument config (tree_storage) storage class, where the data will be saved.
	 */
	virtual void Save (tree_storage & config) = 0;
	
	/// Save route settings (filter settings) for a given route
	/** Some route settings (e.g. filter settings) are device type 
	 * specific. This function saves them in a tree storage.
	 * \argument config (tree_storage *) Storage class, where the data will be saved.
	 * \argument route (Route *) Route whos data shall be saved.
	 */
	virtual void Save (tree_storage & config, const Route * route) = 0;
	
	/// Load current device settings from a tree storage
	/** \argument config (tree_storage) storage class, where the data will be loaded from.
	 */
	virtual void Load (tree_storage & config) = 0;
	
	/// Loade route settings (filter settings) for a given route
	/** Some route settings (e.g. filter settings) are device type 
	 * specific. This function loads them from a tree storage.
	 * \argument config (tree_storage *) Storage class, where the data will be restored from.
	 * \argument route (Route *) Route whos data shall be loaded.
	 */
	virtual void Load (tree_storage & config, Route * route) = 0;
	
        
	void setUserData (void * data) {
                userdata = data; 
        }
        void * getUserData() const { return userdata; }

	const wxString & GetName() const
	{
		return Name;
	}
	
        virtual void SetName(const wxString & s) 
	{
		Name = s;
	}
	
	int GetDevId() const
	{
		return DevId;
	}
	
	virtual void SetDevId(int id)
	{
		DevId = id;
	}
	
	int GetId() const
	{
		return Id;
	}

	virtual void ReadData(wxConfigBase * config) {};
	virtual void WriteData(wxConfigBase * config) {};	
	
        virtual mutString GetTypeName () const {
                return _("Device base class");
        }

#ifdef WX
	virtual wxString TowxString() const {
		return wxString::Format(_T("Device base class. userdata = %p"), userdata);
	}
#endif
protected:
	void SetId(int id)
	{
		Id = id;
	}
};

// Output devices ---------------------------------------------------

class OutDevice: public Device
{
	// private members: access only via access functions for debugging purposes
	/*
	OutDevice *Next;
	static OutDevice * deviceList;
	 */
	WATCHEDPTR(OutDevice,routing,OutDevice) Next;
	static WATCHEDPTR(OutDevice,routing,OutDevice) deviceList;

public:
	OutDevice():Device(),Next(this,_T("Next"))	
	{
		AppendToDeviceList(this);
	}

	OutDevice(int devId, mutString name, int id = -1):Device(id, devId, name),Next(this,_T("Next")) 
	{
		AppendToDeviceList(this);
	}

	virtual ~OutDevice()
	{
		DEBUGLOG(routing,_T("this = %p"),this);
		TruncateDeviceList (this);
		OutDevice * root = deviceList;
		deviceList = NULL;
		
		if ( Next ) delete Next;
		
		deviceList = root;
	}

        static OutDevice * CreateDevice (DevType type);
	static OutDevice * CreateDevice(DevType type, const mutString & name, int id);
	
	virtual bool Open() = 0;
	virtual void Close() = 0;
	
	virtual void NoteOn(int box, int taste, int velo, Route *r,
	                    int channel, ChannelData *cd) = 0;
	virtual void NoteOff(int box, int taste, int velo, Route *r,
	                     int channel) = 0;
	virtual void NotesCorrect(int box) = 0;
	virtual void Sustain(char on, int channel) = 0;
	virtual int  GetChannel(int taste) = 0;
	virtual void Gis(GisToken *token, char turn) = 0;
	virtual void AddTime(frac time) = 0;
	virtual void MidiOut(DWORD data, char n) = 0;
	virtual void MidiOut(BYTE *p, char n) = 0;
	virtual void Quite(Route *r) = 0;
	virtual void Panic() {};

	virtual bool NeedsRealTime()
	{
		return false;
	}

	virtual DevType GetType() const
	{
		return DTUnknown;
	}

	static OutDevice * GetDeviceList() { return deviceList ; }

	void SetNext(OutDevice * N) {
		Next = N;		
	}

	OutDevice * GetNext() const {
		return Next;
	}

        virtual mutString GetTypeName () const {
		return _("Undefined output device");
        }
#ifdef WX
	virtual wxString TowxString() const {
		return wxString::Format(_T("Output device: %s (Id: %d)\n  userdata = %p\n  Next = %p"),
					GetTypeName().c_str(),DevId,(void *)getUserData(),(OutDevice *)Next);
	}
#endif
	
	void Destroy() {
		RemoveFromDeviceList(this);
		delete this;
	}

	
	static OutDevice * Get(int devid) { return GetInDeviceList(devid); }

	/// Initialize the internal device identifiers.
	/** This function sets the internal device ids of 
	 *  all output devices, starting from 0 and 
	 *  incrementing by 1
	 */
	static void InitializeIds();
	
	static void SaveDevices(tree_storage & config);

	/// Load the current devices from a tree based storage.
	/** This function reads all input devices from a tree based storage.
	 *  \argument config (tree_storage &) storage driver to use for loading.
	 */
	static void LoadDevices(tree_storage & config);

	/// Scan the list of input devices for a given id.
	/** \argument id (int) id to scan for
	 *  \return (OutDevice) pointer to the input device with the given id if found, NULL else.
	 */
	static OutDevice * GetDevice(int id);

protected:
	static void AppendToDeviceList (OutDevice * dev);
	static void RemoveFromDeviceList (OutDevice * dev);
	static void TruncateDeviceList (OutDevice * dev);
	static OutDevice * GetInDeviceList(int devid);
	
};

// Input devices -------------------------------------------------
class InDevice: public Device
{
	// private members: access only via access functions for debugging purposes
	/*
	InDevice *Next;
	static InDevice * deviceList;
	Route *Routes;
	 */
	WATCHEDPTR(InDevice, routing, InDevice) Next;
	static WATCHEDPTR(InDevice,routing,InDevice) deviceList;
	WATCHEDPTR(Route,routing,InDevice) Routes;
protected:
	enum MutaborModeType Mode;

public:
	InDevice():Device(), Next(this,_T("Next")), Routes(this,_T("Routes")), Mode(MutaborDeviceStop)
	{
		AppendToDeviceList (this);
	}
	
	InDevice(int devId, mutString name = mutEmptyString, MutaborModeType mode = MutaborDeviceStop, int id = -1):
	Device(id, devId, name), Next(this,_T("Next")), Routes(this,_T("Routes")), Mode(mode)
	{
		AppendToDeviceList(this);
	}

	virtual ~InDevice()
	{
		DEBUGLOG(routing,_T("%p deleting route %p"),this,(Route *)Routes);
		if ( Routes ) delete Routes;

		TruncateDeviceList (this);
		InDevice * root = deviceList;
		deviceList = NULL;

		DEBUGLOG(routing,_T("%p deleting Next %p"),this,(InDevice *)Next);
		if ( Next ) delete Next;

		deviceList = root;
		DEBUGLOG(routing,_T("deleting %p"),this);
	}

        static InDevice * CreateDevice (DevType type);
	static InDevice * CreateDevice(DevType type, const mutStringRef name, int id);
	
	Route *GetMoveRoutes();
	Route *GetRoute(int nr);   // counting starts with 0
	int nRoutes();
	virtual bool Open() = 0;
	virtual void Close() = 0;
	virtual void Stop() = 0;
	virtual void Play() = 0;
	virtual void Pause() = 0;
	//	  virtual frac ReadOn(frac time) = 0;
	virtual void AddRoute(Route *route);

	virtual void SetRoute(Route * route) 
	{ 
		Routes = route; 
		if (route)
			route->SetInDevice(this);
	}

	Route *GetRoutes()
	{
		return Routes;
	}

	void Quite(); // all Routes quite
	virtual bool NeedsRealTime()
	{
		return false;
	}

	virtual DevType GetType() const
	{
		return DTUnknown;
	}
	
	virtual Route * ReplaceDevice (InDevice * dev);
	
  void SetMode(MutaborModeType m) { Mode = m; }

	MutaborModeType GetMode()
	{
		return Mode;
	}
	
	static InDevice * GetDeviceList() { return deviceList ; }
	
	InDevice * GetNext() const 
	{ 
		return Next; 
	}
	
	void SetNext(InDevice * n) 
	{
		Next = n;
	}

        virtual mutString GetTypeName () const {
		return _("Undefined input device");
        }

#ifdef WX
	virtual wxString TowxString() const {
		return wxString::Format(_T("Input device: %s (Id: %d)\n  userdata = %x\n  Next = %x\n  Mode = %d"),
					GetTypeName().c_str(),DevId,getUserData(),GetNext(),Mode);
	}
#endif
	void Destroy() {
		RemoveFromDeviceList(this);
		delete this;
	}
	
	/// Initialize the internal device identifiers.
	/** This function sets the internal device ids of 
	 *  all input devices, starting from 0 and 
	 *  incrementing by 1
	 */
	static void InitializeIds();

	
	/// Save the current devices in a tree based storage.
	/** This function saves all input devices in a tree storage.
	 *  \argument config (tree_storage &) storage driver to use for saving.
	 */
	static void SaveDevices(tree_storage & config);
	
	/// Load the current devices from a tree based storage.
	/** This function reads all input devices from a tree based storage.
	 *  \argument config (tree_storage &) storage driver to use for loading.
	 */
	static void LoadDevices(tree_storage & config);
	
	/// Scan the list of input devices for a given id.
	/** \argument id (int) id to scan for
	 *  \return (InDevice) pointer to the input device with the given id if found, NULL else.
	 */
	static InDevice * GetDevice(int id);
	
protected:
	static void AppendToDeviceList (InDevice * dev);
	static void RemoveFromDeviceList (InDevice * dev);
	static void TruncateDeviceList (InDevice * dev);
};

class CurrentTimer: public wxStopWatch
{
public:
	CurrentTimer(long t = 0):wxStopWatch()
	{
		Start(t);
	}
	
	virtual ~CurrentTimer() {}

	void Set(long t = 0)
	{
		Start(t);
	}

	CurrentTimer& operator = (long t)
	{
		Start(t);
		return * this;
	}

	virtual void  Notify() 
	{
		STUBC;
	}

	operator unsigned int ()
	{
		return (unsigned int) Time();
	}
	
	operator long ()
	{
		return Time();
	}
};

extern CurrentTimer CurrentTime;

void StartCurrentTime();

void StopCurrentTime();

// functions --------------------------------------------------------



void OutNotesCorrect(int box);

bool OutOpen();

void OutClose();

void OutAddTime(frac time);

bool InOpen();

void InClose();

bool NeedsRealTime();

//frac InReadOn(frac time);

void MidiOut(int box, DWORD data, char n = -1);

void NotesCorrect(int box);

int GetChannel(int box, int taste);

#endif

/*
 * \}
 */

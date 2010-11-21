// #################################################################
// Mutabor, GIS - devices
// ##################################################################

#ifndef DEVGIS_H
#define DEVGIS_H

//#include "Global.h"
#include "Device.h"
#include "GIS_Head.h"
//#include "Interpre.h"

extern mutString CurrentId;

extern mutString CurrentSep;

// OutGis -----------------------------------------------------------

class OutGis : public OutDevice
{

protected:
	GisWriteHead *Head;
public:

	OutGis(): OutDevice()
	{
		Head = 0;
	}

	OutGis(mutString Id, int devId) : OutDevice(devId, Id)
	{
		Head = new GisWriteHead(0, Id);
	}

	virtual ~OutGis()
	{
		delete Head;
	}
	
	/// Save current device settings in a tree storage
	/** \argument config (tree_storage) storage class, where the data will be saved.
	 */
	virtual void Save (tree_storage & config);
	
	/// Save route settings (filter settings) for a given route
	/** Some route settings (e.g. filter settings) are device type 
	 * specific. This function saves them in a tree storage.
	 * \argument config (tree_storage *) Storage class, where the data will be saved.
	 * \argument route (Route *) Route whos data shall be saved.
	 */
	virtual void Save (tree_storage & config, const Route * route);
	
	/// Load current device settings from a tree storage
	/** \argument config (tree_storage) storage class, where the data will be loaded from.
	 */
	virtual void Load (tree_storage & config);
	
	/// Loade route settings (filter settings) for a given route
	/** Some route settings (e.g. filter settings) are device type 
	 * specific. This function loads them from a tree storage.
	 * \argument config (tree_storage *) Storage class, where the data will be restored from.
	 * \argument route (Route *) Route whos data shall be loaded.
	 */
	virtual void Load (tree_storage & config, Route * route);

	
	virtual bool Open()
	{
		return false;
	}

	virtual void Close()
	{
		CloseAllSubs(Head);
	};

	virtual void NoteOn(int box, int taste, int velo,
	                    Route *r, int channel, ChannelData *cd)
	{};

	virtual void NoteOff(int box, int taste,
	                     int velo, Route *r, int channel)
	{};

	virtual void NotesCorrect(int box)
	{};

	virtual void Sustain(char on, int channel)
	{};

	virtual int  GetChannel(int taste)
	{
		return -1;
	}

	virtual void Gis(GisToken *token, char turn);
	virtual void MidiOut(DWORD data, char n)
	{};

	virtual void MidiOut(BYTE *p, char n)
	{};

	virtual void AddTime(frac time)
	{
		Head->AddTime(time);
	}

	virtual void Quite(Route *r)
	{};

	virtual DevType GetType() const
	{
		return DTGis;
	}

	virtual mutString GetTypeName () const {
		return _("GIS output file.");
	}

#ifdef WX
	virtual wxString TowxString() const {
		return OutDevice::TowxString() +
		wxString::Format(_T("\n  Name = %s"),
				 Name.c_str());
	}
#endif
	
};

// InGis ------------------------------------------------------------

class InGis : public InDevice
{

protected:
	wxString Id;
	GisToken *Data;
	GisReadArtHead *Head;

        class GisTimer : public wxTimer
	{
		InGis * file;
                
	public:
		GisTimer(InGis * f) : wxTimer(),file(f)
		{}

		void Notify()
		{
			file->IncDelta();
		}
	};

	GisTimer timer;

public:

	InGis()
                : InDevice(),Id(),timer(this)
	{
		Head = 0;
		Data = 0;
	}

	InGis(const wxString &name, const wxString &id)
			: InDevice(-1,name),Id(id),timer(this)
	{
		Head = 0;
		Data = 0;
	}
	InGis(const mutString & name, int id):InDevice(id,name),Id(),timer(this)
	{
		Head = 0;
		Data = 0;
	}
	
	virtual ~InGis() {}
	
	/// Save current device settings in a tree storage
	/** \argument config (tree_storage) storage class, where the data will be saved.
	 */
	virtual void Save (tree_storage & config);
	
	/// Save route settings (filter settings) for a given route
	/** Some route settings (e.g. filter settings) are device type 
	 * specific. This function saves them in a tree storage.
	 * \argument config (tree_storage *) Storage class, where the data will be saved.
	 * \argument route (Route *) Route whos data shall be saved.
	 */
	virtual void Save (tree_storage & config, const Route * route);
	
	
	/// Load current device settings from a tree storage
	/** \argument config (tree_storage) storage class, where the data will be loaded from.
	 */
	virtual void Load (tree_storage & config);
	
	/// Loade route settings (filter settings) for a given route
	/** Some route settings (e.g. filter settings) are device type 
	 * specific. This function loads them from a tree storage.
	 * \argument config (tree_storage *) Storage class, where the data will be restored from.
	 * \argument route (Route *) Route whos data shall be loaded.
	 */
	virtual void Load (tree_storage & config, Route * route);

	
	virtual bool Open();

	virtual void Close();
	virtual void Stop();
	virtual void Play();
	virtual void Pause();
	void Proceed(GisReadArtHead *h, char turn, Route *route);
	void ProceedRoute(GisReadArtHead *h, char turn);
	virtual long ReadOn(long delta);
	/*		{
	return GisReadArtHeadOn(&Head, time, Proceed);
	}*/

	virtual DevType GetType() const
	{
		return DTGis;
	}

	void IncDelta();

	virtual mutString GetTypeName () const {
		return _("GIS input file.");
	}

#ifdef WX
	virtual wxString TowxString() const {
		return InDevice::TowxString() +
		wxString::Format(_T("\n  Id: %s\n  actDelta = %ld\n  minDelta = %ld\n  TimerId = %d\n  Busy = %d"),
				 Id.c_str());
	}
#endif
	

private:
	long actDelta;  // in ticks
	long minDelta;  // in ticks
	UINT TimerId;
	BOOL Busy;
//    long SpeedFactor;
//    frac LastDelta;

};

#endif


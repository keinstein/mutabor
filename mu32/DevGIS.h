// #################################################################
// Mutabor, GIS - devices
// ##################################################################

#ifndef DEVGIS_H
#define DEVGIS_H

//#include "Global.h"
#include "Device.h"
#include "GIS_Head.h"
//#include "Interpre.h"

extern char *CurrentId;
extern char *CurrentSep;

// OutGis -----------------------------------------------------------

class OutGis : public OutDevice
{
  public:
  	 GisWriteHead *Head;
	   OutGis(char *Id)
	   : OutDevice()
	   {
	    	Head = new GisWriteHead(0, Id);
	   }
	   ~OutGis()
	   {
		    delete Head;
	   }
	   virtual bool Open() { return true; }
	   virtual void Close()
	   {
	    	CloseAllSubs(Head);
	   };
	   virtual void NoteOn(int box, int taste, int velo, Route *r, int channel, ChannelData *cd){};
	   virtual void NoteOff(int box, int taste, int velo, Route *r, int channel){};
	   virtual void NotesCorrect(int box){};
 	   virtual void Sustain(char on, int channel) {};
		 virtual int  GetChannel(int taste) { return -1; }
	   virtual void Gis(GisToken *token, char turn);
 	   virtual void MidiOut(DWORD data, char n) {};
  	 virtual void MidiOut(BYTE *p, char n) {};
	   virtual void AddTime(frac time)
	   {
	    	Head->AddTime(time);
	   }
     virtual void Quite(Route *r) {};
	   virtual char* GetName() { return "GisDevice In Test"; }
	   virtual DevType GetType() const { return DTGis; }
};

// InGis ------------------------------------------------------------

class InGis : public InDevice
{
  protected:
  	 char Id[30];
     char Name[180];
  	 GisToken *Data;
  	 GisReadArtHead *Head;
  public:
  	InGis(char *name, char *id)
	  : InDevice()
	  {
	    strcpy(Name, name);
	    strcpy(Id, id);
	    Head = 0;
      Data = 0;
	  }
	  virtual bool Open();
    virtual void Close();
	  virtual void Stop();
	  virtual void Play();
	  virtual void Pause();
    void Proceed(GisReadArtHead *h, char turn, Route *route);
    void ProceedRoute(GisReadArtHead *h, char turn);
    virtual long ReadOn(long delta);
  /*	 {
 	return GisReadArtHeadOn(&Head, time, Proceed);
	 }*/
	   virtual char* GetName() { return Id; }
	   virtual DevType GetType() const { return DTGis; }
    void IncDelta();
  private:
    long actDelta;  // in ticks
    long minDelta;  // in ticks
    UINT TimerId;
    BOOL Busy;
//    long SpeedFactor;
//    frac LastDelta;

};

#endif

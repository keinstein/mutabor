// -*- C++ -*-

/** \file
 ********************************************************************
 * Routing. Compatibility functions.
 *
 * $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/mu32/routing/RouteCompat.cpp,v 1.2 2010/11/21 13:15:46 keinstein Exp $
 * \author Rüdiger Krauße <krausze@mail.berlios.de>,
 * Tobias Schlemmer <keinstein@users.berlios.de>
 * \date 1998
 * $Date: 2010/11/21 13:15:46 $
 * \version $Revision: 1.2 $
 *
 * $Log: RouteCompat.cpp,v $
 * Revision 1.2  2010/11/21 13:15:46  keinstein
 * merged experimental_tobias
 *
 * Revision 1.1.2.2  2010-11-14 21:28:38  keinstein
 * implement loading and saving old files with new routing system
 *
 * Revision 1.1.2.1  2010-10-15 18:15:15  keinstein
 * Add commandline option --enable-xcode and XCode detection to configure
 *
 *
 ********************************************************************
 *\addtogroup route
 *\{
 ********************************************************************/

#include "Route.h"

namespace compat30 {

  /**\todo: implement a converter to TreeConfig */

	
#define GETLINE if ( !GetLine(config, i, s) ) return
	
	static OutDevice * GetOut(int nr)
	{
		if ( nr < 0 )
			return 0;
		OutDevice *Out = OutDevice::GetDevice(nr);
		return Out;
	}
	
	
	/// parse a string representation of a route type
	/** This function returns the numeric route type to a string representation
	 \param type String (array of \c mutChar)
	 \return numeric id of the route type
	 */
	static RouteType Str2RT(mutChar *type)
	{
		int i;
		
		for (i = 3; i > 0; i--)
			if
#ifndef WX
				( !strncmp(type, RTName[i], strlen(RTName[i])) )
#else
				( !wxStricmp(type, RTName[i])) //, strlen(RTName[i])) )
#endif
				break;
		
		return (RouteType) i;
	}
	
	
	static DevType Str2DT(const mutStringRef type)
	{
		wxString DTName[] =  { _T(""), _T("MIDIPORT"), _T("MIDIFILE"), _T("GMN") };
		int i;
		DEBUGLOG2(other,_T("Comparing %s"),type.c_str());
		
		for (i = 3; i > 0; i--) {
			DEBUGLOG2(other,_T("Testing %s"), DTName[i].c_str() );
			
			if ( type.StartsWith(DTName[i]) )
				break;
		}
		
		return (DevType)i;
	}
	
	
	static bool GetLine(const mutStringRef p, size_t& i,mutStringRef s)
	{
		size_t l = p.Length();
	start:
		if ( i >= l )
			return false;
		while ( i < l && wxString(_T(" \t\n\r")).Find(p.GetChar(i)) != -1 )
			i++;
		if ( i >= l )
			return false;
		size_t i1 = i;
		int i2 = p.find(_T("\n"), i1);
		if ( i2 == -1 ) {
			i = l;
			s = p.Mid(i1);
		} else {
			s = p.Mid(i1, i2-i1);
			i = (size_t) i2;
		}
		
		s = s.Trim();
		if ( s.Length() == 0 || s.StartsWith(_T("#")) )
			goto start;
		
		return true;
	}
	
	
	void LoadRoutes(const mutStringRef config)
	{
	  bool error = false;

		DEBUGLOG2(routing,_T(""));
		InDevice * InDevices = InDevice::GetDeviceList();
		OutDevice * OutDevices = OutDevice::GetDeviceList();

		// emty lists
		if ( InDevices) {
			delete InDevices;
			InDevices = NULL;
		}
		if ( OutDevices ) {
			delete OutDevices;
			OutDevices = NULL;
		}
		while (Route * routes = Route::GetRouteList())
		  delete routes;
		
		// Zerlegen von config
		wxString s;
		size_t i = 0;
		GETLINE;
		
		DEBUGLOG2(routing,_T("+%s"),s.c_str());
		
		while ( !s.StartsWith(_T("OUTPUT")) ) {
			GETLINE;
			DEBUGLOG2(other,_T("+%s"),s.c_str());
		}
		
		GETLINE;
		DEBUGLOG2(routing,_T("+%s"),s.c_str());
		// Output lesen
		while ( !s.StartsWith(_T("INPUT")) ) {
			mutChar Type[80], Name[400];
			int DevId, BendingRange;
			
			DEBUGLOG2(routing,_T("a%s"),s.c_str());
#if (wxUSE_UNICODE || wxUSE_WCHAR_T)
			int test = SSCANF(s.c_str(), _T("%ls \"%l[^\"]\" %d %d"),
					  Type, Name, &DevId, &BendingRange);
			if ( test < 2 )
				test = SSCANF(s.c_str(), _T("%ls %ls %d %d"),
					      Type, Name, &DevId, &BendingRange);

			if ( test < 3 ) {
			  error = true;
			}
#else
			int test = SSCANF(s.c_str(), _T("%s \"%[^\"]\" %d %d"),
					  Type, Name, &DevId, &BendingRange);
			if ( test < 2 )
				test = SSCANF(s.c_str(), _T("%s %s %d %d"),
					      Type, Name, &DevId, &BendingRange);
			if ( test < 3 ) {
			  error = true;
			}
#endif
			DEBUGLOG2(routing,_T("%d parameters read: Type = '%s', Name = '%s', devid = %d, bendingrange = %d"),test,Type,Name,DevId,BendingRange);
			DEBUGLOG2(routing,_T("Name = '%s'"),(wxString(Name).c_str()));
			OutDevice *Out = 
			  OutDevice::CreateDevice(Str2DT(muT(Type)),
						  Name, DevId);
			
			switch (Str2DT(muT(Type))) {
			case DTMidiPort:
			  if (test < 4)
			    error = true;
			  else {
			    OutMidiPort * dev = 
			      dynamic_cast<OutMidiPort *>(Out);
			    if (!dev) 
			      UNREACHABLE;
			    else 
			      dev -> SetBendingRange (BendingRange);
			  }
			  break;
			case DTMidiFile:
			  if (test < 4)
			    error = true;
			  else {
			    OutMidiFile * dev = 
			      dynamic_cast<OutMidiFile *>(Out);
			    if (!dev) 
			      UNREACHABLE;
			    else 
			      dev -> SetBendingRange (BendingRange);
			  }
			  break;
			case DTUnknown:
			case DTGis:
			default:
			  if (test >= 4) error = true;
			}
 
			GETLINE;
			DEBUGLOG2(other,_T("+%s"),s.c_str());
		}

		OutDevice::InitializeIds();
		
		GETLINE;
		DEBUGLOG2(routing,_T("+%s"),s.c_str());
		// Input lesen
		
		while ( 1 ) {
			// Device lesen
			mutChar Type[40], Name[400];
			//wxString Type, Name;
			int DevId = -1;
#if (wxUSE_UNICODE || wxUSE_WCHAR_T)
			int test = SSCANF(s, _T("%ls \"%l[^\"]\" %d"),
					  Type, Name, &DevId);
			if ( test < 2 )
				test = SSCANF(s, _T("%ls %ls %d"),
					      Type, Name, &DevId);
			if ( test < 3 ) {
			  error = 1;
			}
			
#else
			int test = SSCANF(s, _T("%s \"%[^\"]\" %d"),
					  Type, Name, &DevId);
			if ( test < 2 )
				test = SSCANF(s, _T("%s %s %d"),
					      Type, Name, &DevId);

			if ( test < 3 ) {
			  error = 1;
			}
			
#endif
			DEBUGLOG2(routing,_T("%d input parameters read: Type = '%s', Name = '%s', DevId = %d"), test, Type, Name, DevId);
			InDevice *In = InDevice::CreateDevice(Str2DT(muT(Type)), 
							    Name, DevId);
			GETLINE;
			DEBUGLOG2(routing,_T("+%s"),s.c_str());
			
			// Routen lesen
			while ( Str2DT(s) == DTUnknown ) {
				// Route lesen
				mutChar Type[40];
				int IFrom = 0, ITo = 0, Box = 0, BoxActive = 0,
				OutDev = -1, OFrom = -1, OTo = -1, ONoDrum = 1;
#if (wxUSE_UNICODE || wxUSE_WCHAR_T)
				test = SSCANF(s.c_str(),
					      _T("%ls %d %d %d %d %d %d %d %d"),
					      Type, &IFrom, &ITo, &Box, &BoxActive,
					      &OutDev, &OFrom, &OTo, &ONoDrum);
				
				if ( test < 9 ) {
				  error = true;
				}
				
#else
				test = SSCANF(s.c_str(),
					      _T("%s %d %d %d %d %d %d %d %d"),
					      Type, &IFrom, &ITo, &Box,
					      &BoxActive, &OutDev, &OFrom, &OTo,
					      &ONoDrum);
				
				if ( test < 9 ) {
				  error = true;
				}
				
#endif
				DEBUGLOG2(routing,_T("%d parameters read: Type = '%s', IFrom = %d, ITo = %d"),test, Type, IFrom, ITo);
				DEBUGLOG2(routing,_T("    Box = %d, BoxActive= %d, OutDev = %d, OFrom = %d, OTo = %d, ONoDrum = %d"), Box, BoxActive, OutDev, OFrom, OTo, ONoDrum);

				In->AddRoute(new Route(In,GetOut(OutDev),
						       Str2RT(Type),
						       IFrom, ITo, Box,
						       BoxActive, 
						       OFrom, OTo, ONoDrum));
				GETLINE;
				DEBUGLOG2(routing,_T("+%s"),s.c_str());
			}
		}
	}
	
	
	/* old default routing file:
	 OUTPUT
	 MIDIPORT MIDIPORT_OUT 0 2
	 INPUT
	 MIDIPORT MIDIPORT_IN 0
	 ALL 0 0 0 1 0 0 15
	 */
	
	
	void SaveRoutes(mutStringRef config)
	{
		/// \TODO reimplement WriteRoutes
		STUB;

		Route::InitializeIds();
	
		// clean config
		config = wxEmptyString;
		// remove unused output devices
		OutDevice *Out;
		InDevice *In;
	
		// Output schreiben
		config << _T("OUTPUT\n");
	
		for ( Out = OutDevice::GetDeviceList(); Out; 
		      Out = Out->GetNext()) {

		  wxString sName = Out->GetName();
			
			if ( sName.Find(_T(" ")) )
				sName.Prepend(_T("\"")) << _T("\"");
		
			switch ( Out->GetType() ) {
					
				case DTUnknown:
				  config << wxString::Format(_T("  UNKNOWN %s\n"),
							     sName.c_str());
					
					break;
					
				case DTMidiPort:
				  {
				    OutMidiPort * MidiOut = 
				      dynamic_cast <OutMidiPort *>(Out);
				    if (MidiOut)
				      config << wxString::Format(_T("  MIDIPORT %s %d %d\n"),
								 sName.c_str(), 
								 Out->Device::GetId(),
								 MidiOut->GetBendingRange());
				  else 
				    UNREACHABLE;
				  }
				  break;
					
				case DTMidiFile:
				  {
				    OutMidiFile * MidiFile = 
				      dynamic_cast <OutMidiFile *>(Out);
				    if (MidiFile)
				      config << wxString::Format(_T("  MIDIFILE %s %d %d\n"),
								 sName.c_str(), 
								 0,
								 MidiFile->GetBendingRange());
				    else
				      UNREACHABLE;
				  }
				  break;
					
				case DTGis:
					config << wxString::Format(_T("  GMN %s\n"), sName.c_str());
					
					break;
					
				case DTNotSet:
					wxLogWarning(_("Device found, but device type not set."));
			}
		}
	
		DEBUGLOG2(routing,_T("WriteConfig: %s"), (config.c_str()));
	
		// Input schreiben
		config << _T("INPUT\n");
		
		for ( In = InDevice::GetDeviceList(); In; In = In->GetNext()) {
		  wxString sName = In->GetName();
			
			if ( sName.Find(_T(" ")) )
				sName.Prepend(_T("\"")) << _T("\"");
		
			switch ( In->GetType() ) {
					
				case DTUnknown:
					config << wxString::Format(_T("  UNKNOWN %s\n"), sName.c_str());
					
					break;
				
				case DTGis:
					config << wxString::Format(_T("  GMN %s\n"), sName.c_str());
				
					break;
				
				case DTMidiPort:
				  config << wxString::Format(_T("  MIDIPORT %s %d\n"), sName.c_str(), In->GetDevId());
					
					break;
				
				case DTMidiFile:
					config << wxString::Format(_T("  MIDIFILE %s\n"), sName.c_str());
				
					break;
				
				case DTNotSet:
					wxLogWarning(_("Device found but device type not set."));
					
				break;
			}
		
			// Routen schreiben
			for (Route *R = In->GetRoutes(); R; R = R->GetNext()) {
			  Device * dev = R->GetOutDevice();
			  int OutNr;
			  OutNr = (dev ? dev->GetId(): -1);
			  config << wxT("    ") << RTName[R->Type]  <<
			    wxString::Format(_T(" %d %d  %d %d  %d  %d %d %d\n"),
					     R->IFrom, 
					     R->ITo, 
					     R->Box, 
					     R->Active, 
					     OutNr,
					     R->OFrom, 
					     R->OTo, 
					     R->ONoDrum ? 1 : 0);
			}
		}
		
		DEBUGLOG2(routing,_T("WriteRoutes: %s"), (config.c_str()));
	}
}

/// \}

// -*- C++ -*-

/** \file
 ********************************************************************
 * Routing. Compatibility functions.
 *
 * \author Rüdiger Krauße <krausze@mail.berlios.de>,
 * Tobias Schlemmer <keinstein@users.berlios.de>
 * \date 1998
 * $Date: 2011/11/02 14:31:57 $
 * \version $Version$
 * \license GPL
 *
 *    This program is free software; you can redistribute it and/or modify
 *    it under the terms of the GNU General Public License as published by
 *    the Free Software Foundation; either version 2 of the License, or
 *    (at your option) any later version.
 *
 *    This program is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License for more details.
 *
 *    You should have received a copy of the GNU General Public License
 *    along with this program; if not, write to the Free Software
 *    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 *
 ********************************************************************
 *\addtogroup route
 *\{
 ********************************************************************/

#include "src/kernel/routing/Route-inlines.h"
#include "src/kernel/routing/Device.h"
#include "src/kernel/routing/midi/DevMidi.h"
#include "src/kernel/routing/midi/DevMidF.h"
#include "wx/log.h"

using namespace mutabor;
namespace compat30 {

  /**\todo: implement a converter to TreeConfig */

	
#define GETLINE if ( !GetLine(config, i, s) ) return
	
	static inline OutputDevice GetOut(int nr)
	{
		if ( nr < 0 )
			return 0;
		OutputDevice Out = OutputDeviceClass::GetDevice(nr, Device::IDTypeFile);
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
		
		TRACE;

		// empty lists
		TRACE;
		InputDeviceClass::ClearDeviceList();
		TRACE;
		OutputDeviceClass::ClearDeviceList();
		TRACE;
		RouteClass::ClearRouteList();
		TRACE;
		BoxClass::ClearBoxList();
		TRACE;
 		
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
			int test = SSCANF(s.c_str(), _T("%s \"%[^\"]\" %d %d"),
					  Type, Name, &DevId, &BendingRange);
			if ( test < 2 )
				test = SSCANF(s.c_str(), _T("%s %s %d %d"),
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
			OutputDevice Out = 
				DeviceFactory::CreateOutput(Str2DT(Type), 
							    Name);
			
			switch (Str2DT(Type)) {
			case DTMidiPort:
				if (test < 4)
					error = true;
				else {
					OutputMidiPort * dev = 
						dynamic_cast<OutputMidiPort *>(Out.get());
					if (!dev) 
						UNREACHABLE;
					else {
						dev -> SetDevId(DevId);
						dev -> SetBendingRange (BendingRange);
					}
				}
				break;
			case DTMidiFile:
				if (test < 4)
					error = true;
				else {
					OutputMidiFile * dev = 
						dynamic_cast<OutputMidiFile *>(Out.get());
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

		OutputDeviceClass::InitializeIds();
		
		GETLINE;
		DEBUGLOG2(routing,_T("+%s"),s.c_str());
		// Input lesen
		
		while ( 1 ) {
			// Device lesen
			mutChar Type[40], Name[400];
			//wxString Type, Name;
			int DevId = -1;
#if (wxUSE_UNICODE || wxUSE_WCHAR_T)
			int test = SSCANF(s, _T("%s \"%[^\"]\" %d"),
					  Type, Name, &DevId);
			if ( test < 2 )
				test = SSCANF(s, _T("%s %s %d"),
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
			InputDevice In = 
				DeviceFactory::CreateInput(Str2DT(Type), 
							   (mutString)Name);

			switch (Str2DT(Type)) {
			case DTMidiPort:
				static_cast<InputMidiPort *>(In.get()) -> SetDevId(DevId);
			case DTNotSet:
			case DTUnknown:
			case DTMidiFile:
			case DTGis:
			default:
				/* do nothing, here */
				;
			}
			GETLINE;
			DEBUGLOG2(routing,_T("+%s"),s.c_str());
			
			// Routen lesen
			while ( Str2DT(s) == DTUnknown ) {
				// Route lesen
				mutChar Type[40];
				int IFrom = 0, ITo = 0, boxid = 0, BoxActive = 0,
				OutDev = -1, OFrom = -1, OTo = -1, ONoDrum = 1;
#if (wxUSE_UNICODE || wxUSE_WCHAR_T)
				test = SSCANF(s.c_str(),
					      _T("%s %d %d %d %d %d %d %d %d"),
					      Type, &IFrom, &ITo, &boxid, &BoxActive,
					      &OutDev, &OFrom, &OTo, &ONoDrum);
				
				if ( test < 9 ) {
				  error = true;
				}
				
#else
				test = SSCANF(s.c_str(),
					      _T("%s %d %d %d %d %d %d %d %d"),
					      Type, &IFrom, &ITo, &boxid,
					      &BoxActive, &OutDev, &OFrom, &OTo,
					      &ONoDrum);
				
				if ( test < 9 ) {
				  error = true;
				}
				
#endif
				DEBUGLOG2(routing,_T("%d parameters read: Type = '%s', IFrom = %d, ITo = %d"),test, Type, IFrom, ITo);
				DEBUGLOG2(routing,_T("    boxid = %d, BoxActive= %d, OutDev = %d, OFrom = %d, OTo = %d, ONoDrum = %d"), boxid, BoxActive, OutDev, OFrom, OTo, ONoDrum);

				OutputDevice Out = GetOut(OutDev);
				Box box = BoxClass::GetOrCreateBox(boxid);
				Route r(RouteFactory::Create(In, Out,
							     Str2RT(Type),
							     IFrom, ITo, box,
							     BoxActive, 
							     OFrom, OTo, ONoDrum != 0));
				In->Add(r);
				GETLINE;
				DEBUGLOG2(routing,_T("+%s"),s.c_str());
			}
		}
		if (error) {
			STUB;
		}
		return;
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

		RouteClass::InitializeIds();
	
		// clean config
		config = wxEmptyString;
		// remove unused output devices
		OutputDevice Out;
		InputDevice In;
	
		// Output schreiben
		config << _T("OUTPUT\n");
		
		const OutputDeviceList & OutDevices =
			OutputDeviceClass::GetDeviceList();

		for ( OutputDeviceList::const_iterator Out = OutDevices.begin();
		      Out != OutDevices.end(); Out++) {

			wxString sName = (*Out)->GetName();
			
			if ( sName.Find(_T(" ")) )
				sName.Prepend(_T("\"")) << _T("\"");
		
			switch ( (*Out)->GetType() ) {
					
			case DTUnknown:
				config << wxString::Format(_T("  UNKNOWN %s\n"),
							   sName.c_str());
					
				break;
					
			case DTMidiPort:
			{
				OutputMidiPort * MidiOut = 
					dynamic_cast <OutputMidiPort *>((*Out).get());
				if (MidiOut)
					config << wxString::Format(_T("  MIDIPORT %s %d %d\n"),
								   sName.c_str(), 
								   (*Out)->get_routefile_id(),
								   MidiOut->GetBendingRange());
				else 
					UNREACHABLE;
			}
			break;
					
			case DTMidiFile:
			{
				OutputMidiFile * MidiFile = 
					dynamic_cast <OutputMidiFile *>((*Out).get());
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
		
		const InputDeviceList & InDevices = 
			InputDeviceClass::GetDeviceList();
		for ( InputDeviceList::const_iterator In = InDevices.begin(); 
		      In != InDevices.end(); In++) {
			wxString sName = (*In)->GetName();
			
			if ( sName.Find(_T(" ")) )
				sName.Prepend(_T("\"")) << _T("\"");
		
			switch ( (*In)->GetType() ) {
					
				case DTUnknown:
					config << wxString::Format(_T("  UNKNOWN %s\n"), sName.c_str());
					
					break;
				
				case DTGis:
					config << wxString::Format(_T("  GMN %s\n"), sName.c_str());
				
					break;
				
				case DTMidiPort:
				  config << wxString::Format(_T("  MIDIPORT %s %d\n"), sName.c_str(), 
							     static_cast<InputMidiPort *>((*In).get())->GetDevId());
					
					break;
				
				case DTMidiFile:
					config << wxString::Format(_T("  MIDIFILE %s\n"), sName.c_str());
				
					break;
				
				case DTNotSet:
					wxLogWarning(_("Device found but device type not set."));
					
				break;
			}
		
			// Routen schreiben
			routeListType & routes = (*In)->GetRoutes();
			for (routeListType::iterator R = routes.begin();
			     R!= routes.end(); R++) {
				Device * dev = (*R)->GetOutputDevice().get();
				int OutNr;
				OutNr = (dev ? dev->get_routefile_id(): -1);
				config << wxT("    ") << RTName[(*R)->GetType()]  <<
					wxString::Format(_T(" %d %d  %d %d  %d  %d %d %d\n"),
							 (*R)->GetInputFrom(), 
							 (*R)->GetInputTo(), 
							 ((*R)->GetBox()?
							  (*R)->GetBox()->get_routefile_id():
							  NoBox), 
							 (*R)->GetActive(), 
							 OutNr,
							 (*R)->GetOutputFrom(), 
							 (*R)->GetOutputTo(), 
							 (*R)->OutputAvoidDrumChannel() ? 1 : 0);
			}
		}
		
		DEBUGLOG2(routing,_T("WriteRoutes: %s"), (config.c_str()));
	}
}

/// \}

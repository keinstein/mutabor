// -*- C++ -*-

/** \file
 ********************************************************************
 * Routing. Compatibility functions.
 *
 * \author Rüdiger Krauße <krausze@mail.berlios.de>,
 * Tobias Schlemmer <keinstein@users.sourceforge.net>
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
#include <boost/algorithm/string.hpp>
#include <locale>

using namespace mutabor;
namespace compat30 {

  /**\todo: implement a converter to TreeConfig */


#define GETLINE if ( !GetLine(config, i, s) ) return
	static std::locale nolocale ("C");

	static inline OutputDevice GetOut(int nr)
	{
		if ( nr < 0 )
			return 0;
		OutputDevice Out = OutputDeviceClass::GetDevice(nr, Device::IDTypeFile);
		return Out;
	}


	/// parse a string representation of a route type
	/** This function returns the numeric route type to a string representation
	 \param type String (array of \c char)
	 \return numeric id of the route type
	 */
	static RouteType Str2RT(char * type)
	{
		int i;

		for (i = 3; i > 0; i--)
			if (!strncmp(type, RTName[i].data(), RTName[i].length()) )
				break;

		return (RouteType) i;
	}


	static DevType Str2DT(const std::string type)
	{
		std::string DTName[] =  { (""), ("MIDIPORT"), ("MIDIFILE"), ("GMN") };
		int i;
		DEBUGLOG2(other,("Comparing %s"),type.c_str());

		for (i = 3; i > 0; i--) {
			DEBUGLOG2(other,("Testing %s"), DTName[i].c_str() );

			if ( type.substr(0,DTName[i].length()) == (DTName[i]) )
				break;
		}

		return (DevType)i;
	}



	static inline bool find_in_string(const std::string &haystack, char needle) {
		return haystack.find(needle) != std::string::npos;
	}

	static bool GetLine(const std::string & p, size_t& i,std::string & s)
	{
		size_t l = p.length();
	start:
		if ( i >= l )
			return false;
		while ( i < l && find_in_string(" \t\n\r",p[i]))
			i++;
		if ( i >= l )
			return false;
		size_t i1 = i;
		int i2 = p.find(("\n"), i1);
		if ( i2 == -1 ) {
			i = l;
			s = p.substr(i1);
		} else {
			s = p.substr(i1, i2-i1);
			i = (size_t) i2;
		}

		boost::trim(s,nolocale);
		if ( s.empty() || s[0] == '#')
			goto start;

		return true;
	}


	void LoadRoutes(const std::string & config)
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
		std::string s;
		size_t i = 0;
		GETLINE;

		DEBUGLOG2(routing,("+%s"),s.c_str());

		while ( s.substr(0,6) != "OUTPUT") {
			GETLINE;
			DEBUGLOG2(other,("+%s"),s.c_str());
		}

		GETLINE;
		DEBUGLOG2(routing,("+%s"),s.c_str());
		// Output lesen
		while ( s.substr(0,5) != "INPUT") {
			std::vector<char> Type(s.length()+1), Name(s.length()+1);
			int DevId, BendingRange;

			DEBUGLOG2(routing,("a%s"),s.c_str());

			int test = std::sscanf(s.c_str(), ("%s \"%[^\"]\" %d %d"),
					       Type.data(), Name.data(), &DevId, &BendingRange);
			if ( test < 2 )
				test = std::sscanf(s.c_str(), ("%s %s %d %d"),
						   Type.data(), Name.data(), &DevId, &BendingRange);

			if ( test < 3 ) {
			  error = true;
			}
			DEBUGLOG2(routing,("%d parameters read: Type = '%s', Name = '%s', devid = %d, bendingrange = %d"),
				  test,(const char *)Type.data(),(const char * )Name.data(),DevId,BendingRange);
			DEBUGLOG2(routing,("Name = '%s'"),(std::string(Name.data()).c_str()));
			OutputDevice Out =
				DeviceFactory::CreateOutput(Str2DT(Type.data()),
							    Name.data());

			switch (Str2DT(Type.data())) {
			case DTMidiPort:
				if (test < 4)
					error = true;
				else {
					OutputMidiPort * dev =
						dynamic_cast<OutputMidiPort *>(Out.get());
					if (!dev)
						UNREACHABLE;
					else if (rtmidiout) {
						rtmidi::PortList list = rtmidiout->getPortList();
						rtmidi::PortList::iterator i = list.begin();
						while (DevId && ++i != list.end()) DevId--;
						if (i != list.end())
							dev -> SetDevId(*i);
					}
					dev -> SetBendingRange (BendingRange);
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
			DEBUGLOG2(other,("+%s"),s.c_str());
		}

		OutputDeviceClass::InitializeIds();

		GETLINE;
		DEBUGLOG2(routing,("+%s"),s.c_str());
		// Input lesen

		while ( 1 ) {
			// Device lesen
			std::vector<char> Type(s.length()+1), Name(s.length()+1);
			//std::string Type, Name;
			int DevId = -1;
			int test = std::sscanf(s.c_str(), ("%s \"%[^\"]\" %d"),
					       Type.data(), Name.data(), &DevId);
			if ( test < 2 )
				test = std::sscanf(s.c_str(), ("%s %s %d"),
						   Type.data(), Name.data(), &DevId);
			if ( test < 3 ) {
			  error = 1;
			}

			DEBUGLOG2(routing,("%d input parameters read: Type = '%s', Name = '%s', DevId = %d"),
				  test, (const char *)Type.data(), (const char *)Name.data(), DevId);
			InputDevice In =
				DeviceFactory::CreateInput(Str2DT(Type.data()),
							   (std::string)Name.data());

			switch (Str2DT(Type.data())) {
			case DTMidiPort: {
				if (rtmidiin) {
					rtmidi::PortList list = rtmidiin->getPortList();
					rtmidi::PortList::iterator i = list.begin();
					while (DevId && ++i != list.end()) DevId--;
					if (i != list.end())
						static_cast<InputMidiPort *>(In.get()) -> SetDevId(*i);
				}
			}
			case DTNotSet:
			case DTUnknown:
			case DTMidiFile:
			case DTGis:
			default:
				/* do nothing, here */
				;
			}
			GETLINE;
			DEBUGLOG2(routing,("+%s"),s.c_str());

			// Routen lesen
			while ( Str2DT(s) == DTUnknown ) {
				// Route lesen
				std::vector<char> Type(s.length()+1);
				int IFrom = 0, ITo = 0, boxid = 0, BoxActive = 0,
				OutDev = -1, OFrom = -1, OTo = -1, ONoDrum = 1;
				test = std::sscanf(s.c_str(),
						   ("%s %d %d %d %d %d %d %d %d"),
						   Type.data(), &IFrom, &ITo, &boxid, &BoxActive,
						   &OutDev, &OFrom, &OTo, &ONoDrum);

				if ( test < 9 ) {
					error = true;
				}

				DEBUGLOG2(routing,("%d parameters read: Type = '%s', IFrom = %d, ITo = %d"),
					  test, (const char *)Type.data(), IFrom, ITo);
				DEBUGLOG2(routing,("    boxid = %d, BoxActive= %d, OutDev = %d, OFrom = %d, OTo = %d, ONoDrum = %d"), boxid, BoxActive, OutDev, OFrom, OTo, ONoDrum);

				OutputDevice Out = GetOut(OutDev);
				Box box = BoxClass::GetOrCreateBox(boxid);
				Route r(RouteFactory::Create(In, Out,
							     Str2RT(Type.data()),
							     IFrom, ITo, box,
							     BoxActive,
							     OFrom, OTo, ONoDrum != 0));
				In->Add(r);
				GETLINE;
				DEBUGLOG2(routing,("+%s"),s.c_str());
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


	void SaveRoutes(std::string & config)
	{
		/// \TODO reimplement WriteRoutes
		STUB;

		RouteClass::InitializeIds();

		// clean config
		config = "";
		// remove unused output devices
		OutputDevice Out;
		InputDevice In;

		// Output schreiben
		config += ("OUTPUT\n");

		const OutputDeviceList & OutDevices =
			OutputDeviceClass::GetDeviceList();

		for ( OutputDeviceList::const_iterator Out = OutDevices.begin();
		      Out != OutDevices.end(); Out++) {

			std::string sName = (*Out)->GetName();

			if ( sName.find((" ")) != std::string::npos)
				sName = "\"" + sName + "\"";

			switch ( (*Out)->GetType() ) {

			case DTUnknown:
				config += boost::str(boost::format("  UNKNOWN %s\n")%
							   sName.c_str());

				break;

			case DTMidiPort:
			{
				OutputMidiPort * MidiOut =
					dynamic_cast <OutputMidiPort *>((*Out).get());
				if (MidiOut)
					config += boost::str(boost::format("  MIDIPORT %s %d %d\n")
							     % sName.c_str()
							     % (*Out)->get_routefile_id()
							     % MidiOut->GetBendingRange());
				else
					UNREACHABLE;
			}
			break;

			case DTMidiFile:
			{
				OutputMidiFile * MidiFile =
					dynamic_cast <OutputMidiFile *>((*Out).get());
				if (MidiFile)
					config += boost::str(boost::format("  MIDIFILE %s %d %d\n")
							     % sName.c_str()
							     % 0
							     % MidiFile->GetBendingRange());
				else
					UNREACHABLE;
			}
			break;

			case DTGis:
				config += boost::str(boost::format("  GMN %s\n")% sName.c_str());

				break;

			case DTNotSet:
				UNREACHABLE;
			}
		}

		DEBUGLOG2(routing,("WriteConfig: %s"), (config.c_str()));

		// Input schreiben
		config += ("INPUT\n");

		const InputDeviceList & InDevices =
			InputDeviceClass::GetDeviceList();
		for ( InputDeviceList::const_iterator In = InDevices.begin();
		      In != InDevices.end(); In++) {
			std::string sName = (*In)->GetName();

			if ( sName.find((" ")) != std::string::npos )
				sName = "\"" + sName + "\"";

			switch ( (*In)->GetType() ) {

			case DTUnknown:
				config += boost::str(boost::format("  UNKNOWN %s\n") % sName.c_str());

				break;

			case DTGis:
				config += boost::str(boost::format("  GMN %s\n") % sName.c_str());

				break;

			case DTMidiPort: {
				int nr = 0;
				if (rtmidiin) {
					rtmidi::PortList list = rtmidiin->getPortList();
					std::string port = static_cast<InputMidiPort *>((*In).get())->GetDevId()
						-> getName( rtmidi::PortDescriptor::INCLUDE_API |
							    rtmidi::PortDescriptor::UNIQUE_PORT_NAME |
							    rtmidi::PortDescriptor::SESSION_PATH );
					for (rtmidi::PortList::iterator i = list.begin();
					     i != list.end(); ++i) {
						if ((*i)-> getName( rtmidi::PortDescriptor::INCLUDE_API |
								    rtmidi::PortDescriptor::UNIQUE_PORT_NAME |
								    rtmidi::PortDescriptor::SESSION_PATH ) == port)
							break;
						++nr;
					}
				}

				config += boost::str(boost::format("  MIDIPORT %s %d\n")
						     % sName.c_str()
						     % nr);

				break;
			}

			case DTMidiFile:
				config += boost::str(boost::format("  MIDIFILE %s\n") % sName.c_str());

				break;

			case DTNotSet:
				UNREACHABLE;

				break;
			}

			// Routen schreiben
			routeListType & routes = (*In)->GetRoutes();
			for (routeListType::iterator R = routes.begin();
			     R!= routes.end(); R++) {
				Device * dev = (*R)->GetOutputDevice().get();
				int OutNr;
				OutNr = (dev ? dev->get_routefile_id(): -1);
				config += "    " + RTName[(*R)->GetType()]  +
					boost::str(boost::format(" %d %d  %d %d  %d  %d %d %d\n")
						   % (*R)->GetInputFrom()
						   % (*R)->GetInputTo()
						   % ((*R)->GetBox()?
						      (*R)->GetBox()->get_routefile_id():
						      NoBox)
						   % (*R)->GetActive()
						   % OutNr
						   % (*R)->GetOutputFrom()
						   % (*R)->GetOutputTo()
						   % ((*R)->OutputAvoidDrumChannel() ? 1 : 0));
			}
		}

		DEBUGLOG2(routing,("WriteRoutes: %s"), (config.c_str()));
	}
}

/// \}

// -*- C++ -*-

/** \file
 ********************************************************************
 * Devices for routing. Mutabor Core.
 *
 * \author Rüdiger Krauße <krausze@mail.berlios.de>,
 * Tobias Schlemmer <keinstein@users.berlios.de>
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
 * \bug Chord hold currently holds all notes. It must be saved note specific.
 ********************************************************************
 *\addtogroup route
 *\{
 ********************************************************************/

#include "src/kernel/Defs.h"
#include "src/kernel/routing/Device.h"
#include "src/kernel/routing/midi/DevMidi.h"
#include "src/kernel/routing/midi/DevMidF.h"
#include "src/kernel/routing/gmn/DevGIS.h"
#include <algorithm>
#include <queue>
#include <stdarg.h>
#include "src/kernel/routing/Device-inlines.h"
#include "src/kernel/routing/Route-inlines.h"
#include "src/kernel/routing/Route.h"
#include "src/kernel/routing/Box.h"


namespace mutabor {

	void ChannelData::MidiReset() {
		/* RP 15 spec is availlable at http://www.midi.org/techspecs/rp15.php */
		controller_vector::iterator start = controller.begin();
		for (controller_vector::iterator i = start;
		     i != controller.end();
		     ++i) {
			int value = *i;
			if (value < 0)
				continue;
			int ctrl = i-start;
			int newvalue = midi::get_default_controller_value(ctrl);
			if (newvalue >= 0) {
				set_controller(ctrl,newvalue);
			}
		}
		// we do not send the reset controllers message so we
		// may not forget the changed controllers

		// first_unchanged = 0;
		// looped = false;

		// program change should not be reset
		// Sound = -1;

		// bank should not be reset
		// bank_coarse = -1;
		//bank_fine = -1;

		bend = 0;

		// todo:
		// channel pressure = 0
		// polyphonic pressure = 0 for all notes
	}

	template <> size_t idtype<Device>::idpool(0);

	void Device::runtime_error(int type, const std::string & message) {
		std::string t = mutabor::to_string((mutabor::error_type)type);
		std::cerr << t << ": " << message << std::endl;
	}


	Device::operator std::string() const {
		std::string routeString;
		for (routeListType::const_iterator r = routes.begin();
		     r != routes.end(); r++)
			routeString += boost::str(boost::format(" %d:(%d->%d->%d)") 
						  % ((*r)->get_routefile_id())
						  % ((*r)->GetDeviceId(InputDevice()))
						  % ((*r)->GetBox()?(*r)->GetBox()->get_routefile_id():NoBox)
						  % ((*r)->GetDeviceId(OutputDevice())));


		return boost::str(boost::format("\nDevice:\n\
   session_id    = %lu\n\
   routefile_id  = %d\n\
   userdata      = %p\n\
   Name          = '%s'\n\
   Flags:        dirty:%d, isOpen:%d\n				      \
   Routes:       %s\n")
				  % (unsigned long)session_id()
				  % routefile_id
				  % userdata 
				  % Name
				  % dirty
				  % isOpen
				  % routeString);
	}

	template <class T, class P, class L>
	CommonTypedDeviceAPI<T,P,L>::~CommonTypedDeviceAPI()
	{
		// if there are remaining pointers we have other problems.
		DEBUGLOG (routing, "this = %p" ,(void*)this);
#ifdef Debug
		listttype::iterator i = FindInDeviceList(this);
		if (i != deviceList.end()) {
			UNREACHABLEC;
			deviceList.erase(i);
		}
#endif
		debug_destruct_class(this);
		TRACEC;
	}

	template <class T, class P, class L>
	void CommonTypedDeviceAPI<T,P,L>::Add(Route & route) {
		DEBUGLOG (smartptr, "Route; %p" ,(void*)route.get());
#ifdef DEBUG
		routeListType::const_iterator i =
			std::find(routes.begin(),routes.end(),route);
		mutASSERT(i == routes.end());
		mutASSERT(IsInDeviceList(static_cast<thistype *>(this)));
#endif
		TRACEC;
		routes.push_back(route);
		DEBUGLOG (smartptr, "Route; %p saved" ,(void*)route.get());
	}

	template <class T, class P, class L>
	bool CommonTypedDeviceAPI<T,P,L>::Replace(Route & oldroute,
						  Route & newroute) {
		DEBUGLOG (smartptr, "oldroute; %p, newroute; %p" ,
			 (void*)oldroute.get(),(void*)newroute.get());
		bool found = CommonTypedDeviceAPI<T,P,L>::Remove(oldroute);
		mutASSERT(found);
		if (found)
			CommonTypedDeviceAPI<T,P,L>::Add(newroute);

		DEBUGLOG (smartptr, "oldroute; %p, newroute; %p" ,
			 (void*)oldroute.get(),(void*)newroute.get());
		return found;
	}

	template <class T, class P, class L>
	bool CommonTypedDeviceAPI<T,P,L>::Remove(Route & route) {
		DEBUGLOG (smartptr, "Route: %p (%d)" ,
			 (void*)route.get(),
			 (int)intrusive_ptr_get_refcount(route.get()));
		bool found = routes.erase(route);
		mutASSERT(found);
		DEBUGLOG (smartptr, "Route; %p (%d)" ,(void*)route.get(),
			 (int)intrusive_ptr_get_refcount(route.get()));
		return found;
	}

	template <class T, class P, class L>
	bool CommonTypedDeviceAPI<T,P,L>::MoveRoutes (DevicePtr & newclass) {
		// We use the slow approach here in order to allow
		// overloading of he connection and disconnection
		// routines.
		TRACEC;
		if (!newclass->routes.empty()) {
			UNREACHABLEC;
			return false;
		}
		bool open = IsOpen();
		// Flawfinder: ignore
		if (open) {
			if (!newclass->IsOpen()) newclass->Open();
		}
		DevicePtr thisptr(static_cast<thistype *>(this));
		routeListType::iterator i;
		while ((i = routes.begin()) != routes.end()) {
			reconnect(*i, thisptr, newclass);
		}
		TRACEC;
		return true;
	}

	template <class T, class P, class L>
	void CommonTypedDeviceAPI<T,P,L>::InitializeIds()
	{
		TRACET(thistype);
		size_t nr = 0;
		for (typename listtype::iterator i = deviceList.begin();
		     i != deviceList.end();
		     i++) {
			(*i)->set_routefile_id(nr);
			routeListType & list = (*i)->routes;
			for (routeListType::iterator j = list.begin();
			     j != list.end();
			     j++) {
				thistype * ptr = NULL;
				(*j)->SetDeviceId(nr, ptr);
			}
			nr++;
		}
	        TRACET(thistype);
	}

	template <class T, class P, class L>
	typename CommonTypedDeviceAPI<T,P,L>::DevicePtr
	CommonTypedDeviceAPI<T,P,L>::GetDevice(int id, devidtype kind)
	{
		for (typename listtype::iterator i = deviceList.begin();
		     i != deviceList.end();
		     i++) {
			int devid;
			switch (kind) {
			case IDTypeSession:
				devid = (*i)->get_session_id();
				break;
			case IDTypeFile:
				devid = (*i)->get_routefile_id();
				break;
			case IDTypeHardware:
			default:
				UNREACHABLECT(thistype);
				return *(deviceList.end());
			}
			if (devid == id) {
				return (*i);
			}
		}
		return NULL;
	}


	template <class T, class P, class L>
	int CommonTypedDeviceAPI<T,P,L>::MoveInList(int count) {
		if (!count) return -1;
		thistype * dev = static_cast <thistype *> (this);
		typename listtype::base_container list;
		deviceList.copy_to(list);
		typename listtype::base_container::iterator pos = std::find(list.begin(),
								       list.end(),
								       dev);

		if (pos == list.end()) return -1;
		int current_pos = pos - list.begin();
		typename listtype::base_container::iterator newpos;
		if (current_pos + count <= 0) {
			newpos = list.begin();
			count = -1;
		} else 	if ((size_t)(current_pos + count) >= list.size()) {
			newpos = list.end() - 1;
			count = 1;
		} else {
			newpos = pos + count;
		}
		if (newpos == list.end()) --newpos;
		if (count > 0)
			std::rotate (pos, newpos, newpos + 1);
		else
			std::rotate (newpos, pos, pos + 1);
		int retval =  newpos - list.begin();
		deviceList.swap(list);
		return retval;

	}


	template <class T, class P, class L>
	CommonTypedDeviceAPI<T,P,L>::operator std::string() const {
		return Device::operator std::string()
			+ boost::str(boost::format("\
CommonTypedDeviceAPI:\n\
   ptrct    = %d\n\
") % (int)intrusive_ptr_get_refcount(this));
	}

// protected:

	template <class T, class P, class L>
	void CommonTypedDeviceAPI<T,P,L>::AppendToDeviceList (DevicePtr dev)
	{
#ifdef DEBUG
		typename listtype::iterator i =
			FindInDeviceList(dev);
		if (i != deviceList.end()) {
			UNREACHABLECT(listtype);
		}
#endif
		deviceList.push_back(dev);
	}

	template <class T, class P, class L>
	void CommonTypedDeviceAPI<T,P,L>::RemoveFromDeviceList (DevicePtr dev)
	{
			deviceList.erase(dev);
	}

	template <class T, class P, class L>
	void CommonTypedDeviceAPI<T,P,L>::TruncateDeviceList (DevicePtr dev)
	{
		STUB;
		return;
#if 0
		if (!deviceList) return;

		if (deviceList == dev) {
			deviceList = NULL;
			return;
		}

		DevicePtr d = deviceList ;
		while (d->GetNext() && d->GetNext() != dev) {
			d = d->GetNext();
		}
		if (d->GetNext()) {
			d -> SetNext(NULL);
		}
#endif
	}

	template class CommonTypedDeviceAPI<OutputDeviceClass>;
	template class CommonTypedDeviceAPI<InputDeviceClass>;


	OutputDeviceClass::operator std::string() const {
		return CommonTypedDeviceAPI<OutputDeviceClass>::
			operator std::string() + "\
OutputDeviceClass:\n\
   no data.\n\
";

	}

	bool InputDeviceClass::last_was_stop = true;

	void InputDeviceClass::DoSilenceKeys(bool remove) {
		current_keys_type::iterator i;
		size_t j = 0;
		DEBUGLOG (routing, "" );
		for (i = current_keys.begin();i!= current_keys.end();i++) {
			for (const int * k = midi::get_holds();
			     *k >= 0; k++) {
				i->route->Controller(*k,
						     midi::CONTROLLER_OFF,
						     i->unique_id);
			}
			i->route->NoteOff(i->key,i->velocity,i->unique_id);
			j++;
		}
		DEBUGLOG (routing, "silenced %lu keys" ,(unsigned long)j);
		if (remove) {
			current_keys.clear();
		}
	}

	/** \todo move implementation to midicmn and Co. */
	void InputDeviceClass::ResumeKeys() {
		ScopedLock lock(write_lock);

		DEBUGLOG (routing, "" );
		current_keys_type::iterator i;
		size_t j = 0;
		for (i = current_keys.begin();i!= current_keys.end();i++) {
			DEBUGLOG (routing, "(key = %d, channel = %lu, id = %lu)" ,
				 i->key,
				 (unsigned long)i->route->get_session_id(),
				 (unsigned long)i->unique_id);
			for (const int * k = midi::get_holds();
			     *k >= 0; k++) {
				i->route->Controller(*k,
						     GetChannelData(*i).get_controller(*k),
						     i->unique_id);
			}
			i->route->NoteOn(i->key,
					 i->velocity,
					 i->unique_id,
					 *i->settings,
					 i->userdata);
			j++;
		}
		DEBUGLOG (routing, "revived %lu keys" ,(unsigned long)j);
	}


	void InputDeviceClass::Panic(int type, size_t unique_id)
	{
		ScopedLock lock(write_lock);

		current_keys_type tmp;
		current_keys_type::iterator i;

		for (i = current_keys.begin();i!= current_keys.end();i++) {
			if (i->unique_id != unique_id) continue;
			tmp.add(*i);
		}
		while ((i = tmp.begin())!= tmp.end()) {
			for (const int * j = midi::get_holds();
			     *j >= 0; j++) {
				i->route->Controller(*j,
						     midi::CONTROLLER_OFF,
						     i->unique_id);
			}
			// Maps have constant entries
			DoNoteOff(const_cast<Route &>(i->route),
				i->key,i->velocity,i->unique_id);
			tmp.remove(i);
		}

		InputDevice self = this;
		for (routeListType::iterator j = routes.begin(); j!= routes.end(); j++) {
			(*j)->Panic(type,unique_id);

		}
	}

	void InputDeviceClass::Panic(int type) {
		ScopedLock lock(write_lock);
		DoSilenceKeys(true);

		for (routeListType::iterator j = routes.begin(); j!= routes.end(); j++) {
			(*j)->Panic(type);
		}
	}


	/// \todo {find a better place for BatchPlay and RealtimePlay:
	/// we should not reference CurrentTime from
	/// Device.{h,cpp,-inlines.h} }
	bool InputDeviceClass::BatchPlay() {
		// Note::keep this function in sync with Activate (Runtime.cpp)
		typedef std::pair <mutint64, InputDevice> queue_element;
		typedef std::priority_queue< queue_element,
					     std::deque<queue_element>,
					     std::greater<queue_element> > batch_queue;
		// Currenttime is used by output devices to keep track of the time
		/// \todo implement event types that use timestamps
		CurrentTime.UseRealtime(false);
		CurrentTime.Set(0);


		OpenAll(OpenAllOutDevices | OpenAllInDevices);

		batch_queue queue;

		for (InputDeviceList::iterator i = deviceList.begin();
		     i != deviceList.end(); i++) {
			(*i)->Play();
			queue.push(queue_element(0,*i));
		}

		mutASSERT(CurrentTime.Get() == 0);

		while (!queue.empty()) {
			queue_element element = queue.top();
			queue.pop();
			mutASSERT(element.first >= CurrentTime.Get());
			CurrentTime = element.first;
			mutint64 delta = element.second->PrepareNextEvent();
			if (delta != MUTABOR_NO_DELTA) {
				mutASSERT(delta >= 0);
				element.first += delta;
				queue.push(element);
			}
		}

		for (InputDeviceList::iterator i = deviceList.begin();
		     i != deviceList.end(); i++) {
			(*i)->Stop();
		}

		mutabor::CurrentTime.Stop();
		mutabor::InClose();
		// mutabor::BoxClose(); // will be handled otherways.
		mutabor::OutClose();

//		GlobalReset();



		return true;
	}

	void InputDeviceClass::RealtimePlay() {
		last_was_stop = false;
		for (InputDeviceList::iterator i = deviceList.begin();
		     i != deviceList.end(); i++) {
			(*i)->Play();
		}
	}


	InputDeviceClass::operator std::string() const {
		return (CommonTypedDeviceAPI<InputDeviceClass>::
			operator std::string()) + boost::str(boost::format("\
InputDeviceClass:\n\
   Mode     = %d\n\
") % Mode);

	}

	DeviceFactory::factorylist DeviceFactory::factories;

	DeviceFactory::DeviceFactory(size_t type) {
		if (factories.size() <= type) {
			factories.resize(type+1,NULL);
		}
		if (factories[type]) {
			UNREACHABLEC;
			return;
		}
		factories[type] = this;

	}

	DeviceFactory::~DeviceFactory() {}

	void DeviceFactory::LoadOutputDevices(tree_storage & config)
	{
#ifdef DEBUG
		std::string oldpath = config.GetPath();
#endif
		config.toLeaf("OutputDevices");

		int i = config.toFirstLeaf("Device");
		while (i != wxNOT_FOUND) {
			DEBUGLOGTYPE(config,OutputDeviceClass,"Loading output device with id %d",i);
			DevType type = (DevType) config.Read("Type", DTMidiPort);
			OutputDevice out = DeviceFactory::CreateOutput(type);
			if (!out) continue;
			out -> set_routefile_id(i);
			std::string name = config.Read("Type Name",
						    "Midi output device");
			DEBUGLOGTYPE(config,
				     OutputDeviceClass,
				     "device type name '%s' == '%s'?",
				     name,
				     (out->GetTypeName()));
			mutASSERT(name == out->GetTypeName());
			out -> Load(config);
			i = config.toNextLeaf("Device");
		}

		config.toParent(2);
		mutASSERT(oldpath == config.GetPath());
	}

	void DeviceFactory::SaveOutputDevices(tree_storage & config)
	{
#ifdef DEBUG
		std::string oldpath = config.GetPath();
#endif
		config.toLeaf("OutputDevices");

		const OutputDeviceList & list =
			OutputDeviceClass::GetDeviceList();
		for (OutputDeviceList::const_iterator out = list.begin();
		     out != list.end(); out++) {
			config.toLeaf("Device",
				      static_cast<Device *>((*out).get())->get_routefile_id());
			config.Write("Type",(*out)->GetType());
			config.Write("Type Name",(*out)->GetTypeName());
			(*out) -> Save (config);
			config.toParent();
		}

		config.toParent();
		mutASSERT(oldpath == config.GetPath());
	}

	void DeviceFactory::LoadInputDevices(tree_storage & config)
	{
#ifdef DEBUG
		std::string oldpath = config.GetPath();
#endif
		config.toLeaf("InputDevices");

		int i = config.toFirstLeaf("Device");
		while (i != wxNOT_FOUND) {
			DevType type = (DevType) config.Read("Type", DTMidiPort);
			TRACE;
			InputDevice in = CreateInput(type);
			TRACE;
			in -> Device::set_routefile_id(i);
#ifdef DEBUG
			std::string name = config.Read("Type Name",
						    "Midi input device");
			DEBUGLOGTYPE(config,
				     InputDeviceClass,
				     ("device type name '%s' == '%s'?"),
				     name,
				     (in->GetTypeName()));
			mutASSERT(name == in -> GetTypeName());
#endif
			in -> Load(config);
			TRACE;
			i = config.toNextLeaf("Device");
		}

		config.toParent(2);
		mutASSERT(oldpath == config.GetPath());
	}

	void DeviceFactory::SaveInputDevices(tree_storage & config)
	{
#ifdef DEBUG
		std::string oldpath = config.GetPath();
#endif
		config.toLeaf("InputDevices");


		TRACE;
		const InputDeviceList & list = InputDeviceClass::GetDeviceList();
		for (InputDeviceList::const_iterator in = list.begin();
		     in != list.end(); in++) {
			config.toLeaf("Device",(*in)->get_routefile_id());
			config.Write("Type",(*in)->GetType());
			config.Write("Type Name",(*in)->GetTypeName());
			(*in) -> Save (config);
			config.toParent();
		}
		TRACE;

		config.toParent();
		mutASSERT(oldpath == config.GetPath());
	}

	void DeviceFactory::DoLoadOutputDevices(tree_storage & config) const
	{
		STUBC;
	}

	void DeviceFactory::DoSaveOutputDevices(tree_storage & config) const
	{
		STUBC;
	}

	void DeviceFactory::DoLoadInputDevices(tree_storage & config) const
	{
		STUBC;
	}

	void DeviceFactory::DoSaveInputDevices(tree_storage & config) const
	{
		STUBC;
	}


	void InitDeviceFactories() {
		new BoxFactory;
		new RouteFactory;
		new MidiPortFactory;
		new MidiFileFactory;
		new GisFactory;
	}




	// functions --------------------------------------------------------

	bool OutOpen()
	{
		const OutputDeviceList& list = OutputDeviceClass::GetDeviceList();
		DEBUGLOG2(midiio,("count: %d"),(int)list.size());
		for (OutputDeviceList::const_iterator Out = list.begin();
		     Out != list.end(); Out++)
			if ( !(*Out)->Open() ) {
				for (OutputDeviceList::const_iterator Out1
					     = list.begin();
				     Out1 != Out; Out1++)
					(*Out1)->Close();

				return false;
			}

		return true;
	}

	void OutClose()
	{
		const OutputDeviceList& list = OutputDeviceClass::GetDeviceList();
		for (OutputDeviceList::const_iterator Out = list.begin();
		     Out != list.end(); Out++)
			(*Out)->Close();
	}

	void OutAddTime(frac time)
	{
		const OutputDeviceList& list = OutputDeviceClass::GetDeviceList();
		for (OutputDeviceList::const_iterator Out = list.begin();
		     Out != list.end(); Out++)
			(*Out)->AddTime(time);
	}

	bool InOpen()
	{
		TRACE;
		const InputDeviceList& list = InputDeviceClass::GetDeviceList();
		for (InputDeviceList::const_iterator In = list.begin();
		     In != list.end(); In++)
			if ( !(*In)->Open() ) {
				for (InputDeviceList::const_iterator In1 = list.begin();
				     In1 != In; In1++)
					(*In1)->Close();

				DEBUGLOGBASE(other,"",("Opening failed"));

				return false;
			}

		TRACE;
		return true;
	}

	void InClose()
	{
		TRACE;
		const InputDeviceList& list = InputDeviceClass::GetDeviceList();
		for (InputDeviceList::const_iterator In = list.begin();
		     In != list.end(); In++)
			(*In)->Close();
		TRACE;
	}

	bool NeedsRealTime()
	{
		TRACE;
		const OutputDeviceList& listo = OutputDeviceClass::GetDeviceList();
		for (OutputDeviceList::const_iterator Out = listo.begin();
		     Out != listo.end(); Out++)
			if ( (*Out)->NeedsRealTime() ) {
				TRACE;
				return true;
			}

		const InputDeviceList& listi = InputDeviceClass::GetDeviceList();
		for (InputDeviceList::const_iterator In = listi.begin();
		     In != listi.end(); In++)
			if ( (*In)->NeedsRealTime() ) {
				TRACE;
				return true;
			}

		TRACE;
		return false;
	}



}

/// \}


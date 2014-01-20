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
 *
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
	template <> size_t idtype<Device>::idpool(0);

	void Device::runtime_error(int type, const mutStringRef message, va_list & args) {
#if wxCHECK_VERSION(2,9,0)
		mutString t = mutabor::to_string((mutabor::error_type)type);
#else
		mutString t = mutString::FromUTF8(mutabor::to_string((mutabor::error_type)type));
#endif
		mutPrintf(_T("%s: "),(const mutChar *)(t));
		mutVPrintf(message,args);
	}
	

#ifdef WX
	wxString Device::TowxString() const {
		wxString routeString;
		for (routeListType::const_iterator r = routes.begin();
		     r != routes.end(); r++)
			routeString += wxString::Format(_T(" %d:(%d->%d->%d)"),
							(*r)->get_routefile_id(),
							(*r)->GetDeviceId(InputDevice()),
							(*r)->GetBox()?(*r)->GetBox()->get_routefile_id():NoBox,
							(*r)->GetDeviceId(OutputDevice()));
		

		return wxString::Format(_T("\nDevice:\n\
   session_id    = %lu\n\
   routefile_id  = %d\n\
   userdata      = %p\n\
   Name          = '%s'\n\
   Flags:        dirty:%d, isOpen:%d\n\
   Routes:       %s\n"),
					(unsigned long)session_id(),
					routefile_id,
					userdata,
					(const wxChar *) Name,
					dirty,isOpen,
					(const wxChar *) routeString);
	}
#endif
	

	template <class T, class P, class L>
	CommonTypedDeviceAPI<T,P,L>::~CommonTypedDeviceAPI()
	{
		// if there are remaining pointers we have other problems.
		DEBUGLOG(routing,_T("this = %p"),(void*)this);
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
		DEBUGLOG(smartptr,_T("Route; %p"),(void*)route.get());
#ifdef DEBUG
		routeListType::const_iterator i = 
			find(routes.begin(),routes.end(),route);
		mutASSERT(i == routes.end());
		mutASSERT(IsInDeviceList(static_cast<thistype *>(this)));
#endif
		TRACEC;
		routes.push_back(route);
		DEBUGLOG(smartptr,_T("Route; %p saved"),(void*)route.get());
	}

	template <class T, class P, class L>
	bool CommonTypedDeviceAPI<T,P,L>::Replace(Route & oldroute, 
						  Route & newroute) {
		DEBUGLOG(smartptr,_T("oldroute; %p, newroute; %p"),
			 (void*)oldroute.get(),(void*)newroute.get());
		bool found = CommonTypedDeviceAPI<T,P,L>::Remove(oldroute);
		mutASSERT(found);
		if (found) 
			CommonTypedDeviceAPI<T,P,L>::Add(newroute);

		DEBUGLOG(smartptr,_T("oldroute; %p, newroute; %p"),
			 (void*)oldroute.get(),(void*)newroute.get());
		return found;
	}

	template <class T, class P, class L>
	bool CommonTypedDeviceAPI<T,P,L>::Remove(Route & route) {
		DEBUGLOG(smartptr,_T("Route: %p (%d)"),
			 (void*)route.get(),
			 (int)intrusive_ptr_get_refcount(route.get()));
		routeListType::iterator i = 
			std::find(routes.begin(),routes.end(),route);
		bool found = (i != routes.end());
		mutASSERT(found);
		if (found) {
			(*i).reset();// list can save some memory for reuse,
			// but route must be deleted
			routes.erase(i);
		}
		DEBUGLOG(smartptr,_T("Route; %p (%d)"),(void*)route.get(),
			 (int)intrusive_ptr_get_refcount(route.get()));
		return found;
	}

	template <class T, class P, class L>
	bool CommonTypedDeviceAPI<T,P,L>::MoveRoutes (DevicePtr & newclass) {
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
		typename listtype::iterator pos = FindInDeviceList(DevicePtr(dev));

		if (pos == deviceList.end()) return -1;
		int current_pos = pos - deviceList.begin();
		typename listtype::iterator newpos;
		if (current_pos + count <= 0) {
			newpos = deviceList.begin();
			count = -1;
		} else 	if (current_pos + count >= deviceList.size()) {
			newpos = deviceList.end() - 1;
			count = 1;
		} else {
			newpos = pos + count;
		}
 		if (newpos == deviceList.end()) --newpos;
		if (count > 0) 
			std::rotate (pos, newpos, newpos + 1);
		else 
			std::rotate (newpos, pos, pos + 1);
		return newpos - deviceList.begin();
		
	}


#ifdef WX
	template <class T, class P, class L>
	wxString CommonTypedDeviceAPI<T,P,L>::TowxString() const {
		return Device::TowxString() 
			+ wxString::Format(_T("\
CommonTypedDeviceAPI:\n\
   ptrct    = %d\n\
"),(int)intrusive_ptr_get_refcount(this));
	}
#endif

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
		typename listtype::iterator i = 
			FindInDeviceList(dev);
		if (i == deviceList.end()) {
			UNREACHABLECT(listtype);
		} else 	
			deviceList.erase(i);
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


#ifdef WX
	wxString OutputDeviceClass::TowxString() const {
		return CommonTypedDeviceAPI<OutputDeviceClass>::
			TowxString() + wxString::Format(_T("\
OutputDeviceClass:\n\
   no data.\n\
"));

	}
#endif

	void InputDeviceClass::DoSilenceKeys(bool remove) {
		current_keys_type::iterator i;
		size_t j = 0;
		DEBUGLOG(always,_T(""));
		for (i = current_keys.begin();i!= current_keys.end();i++) {
			i->route->NoteOff(i->key,i->velocity,i->unique_id);
			j++;
		}
		DEBUGLOG(always,_T("silenced %lu keys"),(unsigned long)j);
		if (remove) {
			current_keys.clear();
		}
	}

	void InputDeviceClass::ResumeKeys() {
		ScopedLock lock(write_lock);

		DEBUGLOG(always,_T(""));
		current_keys_type::iterator i;
		size_t j = 0;
		for (i = current_keys.begin();i!= current_keys.end();i++) {
			DEBUGLOG(always,_T("(key = %d, channel = %lu, id = %lu)"),
				 i->key,
				 (unsigned long)i->route->get_session_id(),
				 (unsigned long)i->unique_id);
			i->route->NoteOn(i->key,
					 i->velocity,
					 i->unique_id,
					 *i->settings,
					 i->userdata);
			j++;
		}
		DEBUGLOG(always,_T("revived %lu keys"),(unsigned long)j);
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
			// Maps have constant entries
			DoNoteOff(const_cast<Route &>(i->route),
				i->key,i->velocity,i->unique_id);
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
		

		OpenAll();

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
		mutabor::BoxClose();
		mutabor::OutClose();

//		GlobalReset();

		return true;
	}

	void InputDeviceClass::RealtimePlay() {
		for (InputDeviceList::iterator i = deviceList.begin();
		     i != deviceList.end(); i++) {
			(*i)->Play();
		}
	}


#ifdef WX
	wxString InputDeviceClass::TowxString() const {
		return (CommonTypedDeviceAPI<InputDeviceClass>::
			TowxString()) + wxString::Format(_T("\
InputDeviceClass:\n\
   Mode     = %d\n\
"),Mode);

	}
#endif

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
		wxString oldpath = config.GetPath();
#endif
		config.toLeaf(_T("OutputDevices"));
	
		int i = config.toFirstLeaf(_T("Device"));
		while (i != wxNOT_FOUND) {
			DEBUGLOGTYPE(config,OutputDeviceClass,_T("Loading output device with id %d"),i);
			DevType type = (DevType) config.Read(_T("Type"), DTMidiPort);
			OutputDevice out = DeviceFactory::CreateOutput(type);
			if (!out) continue;
			out -> set_routefile_id(i);
			wxString name = config.Read(_T("Type Name"),
						    _T("Midi output device"));
			DEBUGLOGTYPE(config,
				     OutputDeviceClass,
				     _T("device type name '%s' == '%s'?"),
				     (const mutChar *)name,
				     (const mutChar *)(out->GetTypeName()));
			mutASSERT(name == out->GetTypeName());
			out -> Load(config);
			i = config.toNextLeaf(_T("Device"));
		}
	
		config.toParent(2);
		mutASSERT(oldpath == config.GetPath());
	}

	void DeviceFactory::SaveOutputDevices(tree_storage & config)
	{
#ifdef DEBUG
		wxString oldpath = config.GetPath();
#endif
		config.toLeaf(_T("OutputDevices"));
	
		const OutputDeviceList & list = 
			OutputDeviceClass::GetDeviceList();
		for (OutputDeviceList::const_iterator out = list.begin(); 
		     out != list.end(); out++) {
			config.toLeaf(_T("Device"),
				      static_cast<Device *>((*out).get())->get_routefile_id());
			config.Write(_T("Type"),(*out)->GetType());
			config.Write(_T("Type Name"),(*out)->GetTypeName());
			(*out) -> Save (config);
			config.toParent();
		}
	
		config.toParent();
		mutASSERT(oldpath == config.GetPath());
	}

	void DeviceFactory::LoadInputDevices(tree_storage & config)
	{
#ifdef DEBUG
		wxString oldpath = config.GetPath();
#endif
		config.toLeaf(_T("InputDevices"));
	
		int i = config.toFirstLeaf(_T("Device"));
		while (i != wxNOT_FOUND) {
			DevType type = (DevType) config.Read(_T("Type"), DTMidiPort);
			TRACE;
			InputDevice in = CreateInput(type);
			TRACE;
			in -> Device::set_routefile_id(i);
#ifdef DEBUG
			wxString name = config.Read(_T("Type Name"),
						    _T("Midi input device"));
			DEBUGLOGTYPE(config,
				     InputDeviceClass,
				     _T("device type name '%s' == '%s'?"),
				     (const mutChar *)name,
				     (const mutChar *)(in->GetTypeName()));
			mutASSERT(name == in -> GetTypeName());
#endif
			in -> Load(config);
			TRACE;
			i = config.toNextLeaf(_T("Device"));
		}
	
		config.toParent(2);
		mutASSERT(oldpath == config.GetPath());
	}

	void DeviceFactory::SaveInputDevices(tree_storage & config)
	{
#ifdef DEBUG
		wxString oldpath = config.GetPath();
#endif
		config.toLeaf(_T("InputDevices"));
	

		TRACE;
		const InputDeviceList & list = InputDeviceClass::GetDeviceList();
		for (InputDeviceList::const_iterator in = list.begin();
		     in != list.end(); in++) {
			config.toLeaf(_T("Device"),(*in)->get_routefile_id());
			config.Write(_T("Type"),(*in)->GetType());
			config.Write(_T("Type Name"),(*in)->GetTypeName());
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
		DEBUGLOG2(midiio,_T("count: %d"),(int)list.size());
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

				DEBUGLOGBASE(other,"",_T("Opening failed"));

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


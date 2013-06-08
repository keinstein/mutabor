// -*- C++ -*-

/** \file
 ********************************************************************
 * Devices for routing. Mutabor Core.
 *
 * $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/src/kernel/routing/Device.cpp,v 1.13 2011/11/02 14:31:57 keinstein Exp $
 * \author Rüdiger Krauße <krausze@mail.berlios.de>,
 * Tobias Schlemmer <keinstein@users.berlios.de>
 * \date 1998
 * $Date: 2011/11/02 14:31:57 $
 * \version $Revision: 1.13 $
 * \license GPL
 *
 *
 *
 ********************************************************************
 *\addtogroup route
 *\{
 ********************************************************************/
// ------------------------------------------------------------------
// Mutabor 3, 1998, R.Krauße
// Devices Basisklassen
// ------------------------------------------------------------------

#include "src/kernel/routing/Device.h"
#include "src/kernel/routing/midi/DevMidi.h"
#include "src/kernel/routing/midi/DevMidF.h"
#include "src/kernel/routing/gmn/DevGIS.h"
#include <algorithm>
#include <queue>
#include "src/kernel/routing/Device-inlines.h"
#include "src/kernel/routing/Route-inlines.h"
#include "src/kernel/routing/Route.h"


namespace mutabor {
#ifdef WX
	wxString Device::TowxString() const {
		wxString routeString;
		for (routeListType::const_iterator r = routes.begin();
		     r != routes.end(); r++)
			routeString += wxString::Format(_T(" %d:(%d->%d->%d)"),
							(*r)->GetId(),
							(*r)->GetDeviceId(InputDevice()),
							(*r)->GetBox(),
							(*r)->GetDeviceId(OutputDevice()));
		

		return wxString::Format(_T("\nDevice:\n\
   id       = %d\n\
   userdata = %p\n\
   DevId    = %d\n\
   Name     = '%s'\n\
   Flags:     dirty:%d, isOpen:%d\n\
   Routes:   %s\n"),
					Id,
					userdata,
					DevId,
					(const wxChar *) Name,
					dirty,isOpen,
					(const wxChar *) routeString);
	}
#endif
	

	template <class T, class P, class L>
	CommonTypedDeviceAPI<T,P,L>::~CommonTypedDeviceAPI()
	{
		// if there are remaining pointers we have other problems.
		DEBUGLOG(routing,_T("this = %p"),this);
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
		DEBUGLOG(smartptr,_T("Route; %p"),route.get());
#ifdef DEBUG
		routeListType::const_iterator i = 
			find(routes.begin(),routes.end(),route.get());
		mutASSERT(i == routes.end());
		mutASSERT(IsInDeviceList(static_cast<thistype *>(this)));
#endif
		TRACEC;
		routes.push_back(route);
		DEBUGLOG(smartptr,_T("Route; %p saved"),route.get());
	}

	template <class T, class P, class L>
	bool CommonTypedDeviceAPI<T,P,L>::Replace(Route & oldroute, 
						  Route & newroute) {
		DEBUGLOG(smartptr,_T("oldroute; %p, newroute; %p"),
			 oldroute.get(),newroute.get());
		bool found = CommonTypedDeviceAPI<T,P,L>::Remove(oldroute);
		mutASSERT(found);
		if (found) 
			CommonTypedDeviceAPI<T,P,L>::Add(newroute);

		DEBUGLOG(smartptr,_T("oldroute; %p, newroute; %p"),
			 oldroute.get(),newroute.get());
		return found;
	}

	template <class T, class P, class L>
	bool CommonTypedDeviceAPI<T,P,L>::Remove(Route & route) {
		DEBUGLOG(smartptr,_T("Route: %p (%d)"),
			 route.get(),
			 intrusive_ptr_get_refcount(route.get()));
		routeListType::iterator i = 
			std::find(routes.begin(),routes.end(),route.get());
		bool found = (i != routes.end());
		mutASSERT(found);
		if (found) {
			(*i) = NULL;// list can save some memory for reuse,
			// but route must be deleted
			routes.erase(i);
		}
		DEBUGLOG(smartptr,_T("Route; %p (%d)"),route.get(),
			 intrusive_ptr_get_refcount(route.get()));
		return found;
	}

	template <class T, class P, class L>
	bool CommonTypedDeviceAPI<T,P,L>::MoveRoutes (DevicePtr & newclass) {
		DEBUGLOG(smartptr,_T(""));
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
		DEBUGLOG(smartptr,_T(""));
		return true;
	}
		
#if 0
	template <class T, class P, class L>
	Route CommonTypedDeviceAPI<T,P,L>::GetRoute(int nr)// Nummern beginnen mit 0
	{
		mutASSERT(nr >= 0);
		routeTypeList::iterator i = routes.begin();
		while (nr--) {
			if (i++ == routes.end()) return NULL;
		}
		return *i;
	}
#endif

	template <class T, class P, class L>
	void CommonTypedDeviceAPI<T,P,L>::InitializeIds()
	{
		DEBUGLOGTYPE(smartptr,thistype,_T(""));
		size_t nr = 0;
		for (typename listtype::iterator i = deviceList.begin();
		     i != deviceList.end();
		     i++) {
			(*i)->Device::SetId(nr);
			routeListType & list = (*i)->routes;
			for (routeListType::iterator j = list.begin();
			     j != list.end();
			     j++) {
				thistype * ptr = NULL;
				(*j)->SetDeviceId(nr, ptr);
			}
			nr++;
		}
		DEBUGLOGTYPE(smartptr,thistype,_T(""));
	}

	template <class T, class P, class L>
	typename CommonTypedDeviceAPI<T,P,L>::DevicePtr 
	CommonTypedDeviceAPI<T,P,L>::GetDevice(int id)
	{
		for (typename listtype::iterator i = deviceList.begin();
		     i != deviceList.end();
		     i++) {
			if ((*i)->Device::GetId() == id) {
				return (*i);
			}
		}
		return NULL;
	}

	template <class T, class P, class L>
	void CommonTypedDeviceAPI<T,P,L>::AppendToDeviceList (DevicePtr dev) 
	{
#ifdef DEBUG
		typename listtype::iterator i = 
			std::find(deviceList.begin(),
				  deviceList.end(),
				  dev);
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
			std::find(deviceList.begin(),
				  deviceList.end(),
				  dev);
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



#ifdef WX
	template <class T, class P, class L>
	wxString CommonTypedDeviceAPI<T,P,L>::TowxString() const {
		return Device::TowxString() 
			+ wxString::Format(_T("\
CommonTypedDeviceAPI:\n\
   ptrct    = %d\n\
"),intrusive_ptr_get_refcount(this));
	}
#endif

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
	
	void InputDeviceClass::Destroy() {
		TRACEC;
		if (IsOpen()) Close();
		TRACEC;
		CommonTypedDeviceAPI<InputDeviceClass>::Destroy();
		TRACEC;
	}

	void InputDeviceClass::Panic(bool global) {
		current_keys_type::iterator i;
		while ((i = current_keys.begin())!= current_keys.end()) {
			i->route->NoteOff(i->key,i->velocity,i->unique_id);
			current_keys.remove(i);
		}

		if (global) {
			for (routeListType::iterator j = routes.begin(); j!= routes.end(); j++) {
				(*j)->Panic();
			}
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
		
		if (!mutabor::OutOpen())
			return false;
		
		if (!mutabor::InOpen() ) {
			mutabor::OutClose();
			return false;
		}

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
		mutabor::OutClose();

		GlobalReset();

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
			out -> Device::SetId(i);
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
				      static_cast<Device *>((*out).get())->GetId());
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
			in -> Device::SetId(i);
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
			config.toLeaf(_T("Device"),(*in)->Device::GetId());
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
		new RouteFactory;
		new MidiPortFactory;
		new MidiFileFactory;
		new GisFactory;
	}




	// functions --------------------------------------------------------

	bool OutOpen()
	{
		const OutputDeviceList& list = OutputDeviceClass::GetDeviceList(); 
		DEBUGLOG2(midiio,_T("count: %d"),list.size());
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


	void MidiOut(mutabor_box_type * box, struct midiliste * outliste)
	{
		DEBUGLOG2(smartptr,_T(""));

		size_t laenge = midi_list_laenge(outliste);
		BYTE * data = (BYTE *)malloc(laenge * sizeof(BYTE));
		struct midiliste * cursor = outliste;
		BYTE * bcursor=data;
		while (cursor != NULL) {
			(*bcursor++) = (BYTE) cursor->midi_code;
			cursor = cursor -> next;
		}
	       
		const routeListType & list = RouteClass::GetRouteList();
		for (routeListType::const_iterator R = list.begin(); 
		     R != list.end(); R++) {
			OutputDevice out;
			if ( (*R)->GetBox() == box->id && 
			     (out = (*R)->GetOutputDevice())) {
				out -> MidiOut(data, laenge);
			}
		}

		free(data);
	}

	void NotesCorrect(mutabor_box_type * box)
	{
		const routeListType & list = RouteClass::GetRouteList();
		for (routeListType::const_iterator route = list.begin();
		     route != list.end(); route++) {
			if ((*route)->GetBox() == box->id)
				(*route)->NotesCorrect();
		}
	}

	int GetChannel(int box, int key, int channel, int id)
	{
		DEBUGLOG2(midiio,_T(""));
		const routeListType & list = RouteClass::GetRouteList();
		for (routeListType::const_iterator R = list.begin(); 
		     R != list.end(); R++) {
			OutputDevice out;
			if ( (*R)->GetBox() == box
			     && (channel == (*R)->GetId())
			     && (out = (*R)->GetOutputDevice())) {
				int c = out->GetChannel(key,channel,id);
				
				if ( c != -1 ) {
					DEBUGLOG2(midiio,_T(""));
					return c;
				}
			}
		}
		DEBUGLOG2(midiio,_T(""));
		return -1;
	}

	
}

/// \}


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
 * $Log: Device.cpp,v $
 * Revision 1.13  2011/11/02 14:31:57  keinstein
 * fix some errors crashing Mutabor on Windows
 *
 * Revision 1.12  2011-10-02 16:58:40  keinstein
 * * generate Class debug information when compile in debug mode
 * * InputDeviceClass::Destroy() prevented RouteClass::Destroy() from clearing references -- fixed.
 * * Reenable confirmation dialog when closing document while the logic is active
 * * Change debug flag management to be more debugger friendly
 * * implement automatic route/device deletion check
 * * new debug flag --debug-trace
 * * generate lots of tracing output
 *
 * Revision 1.11  2011-09-30 18:07:04  keinstein
 * * make compile on windows
 * * s/wxASSERT/mutASSERT/g to get assert handler completely removed
 * * add ax_boost_base for boost detection
 *
 * Revision 1.10  2011-09-30 09:10:24  keinstein
 * Further improvements in the routing system.
 *
 * Revision 1.9  2011-09-29 05:26:58  keinstein
 * debug intrusive_ptr
 * fix storage and retrieving of input/output devices in treestorage
 * save maximum border size in icons
 * Apply the calculated offset in IconShape (box and box channels still missing)
 * Fix debug saving and restoring route information/route window on activation
 * Add wxWANTS_CHARS to MutEditWindow
 *
 * Revision 1.8  2011-09-28 07:35:53  keinstein
 * Make distclean happy
 *
 * Revision 1.7  2011-09-27 20:13:21  keinstein
 * * Reworked route editing backend
 * * rewireing is done by RouteClass/GUIRoute now
 * * other classes forward most requests to this pair
 * * many bugfixes
 * * Version change: We are reaching beta phase now
 *
 * Revision 1.6  2011-09-09 09:29:10  keinstein
 * fix loading of routing configuration
 *
 * Revision 1.5  2011-09-04 12:02:08  keinstein
 * require wxWidgets 2.8.5 configure.in
 *
 * Revision 1.4  2011-02-20 22:35:56  keinstein
 * updated license information; some file headers have to be revised, though
 *
 * Revision 1.3  2010-12-11 02:10:08  keinstein
 * make 2.9.1 build but Mutabor crashes still at runtime in an infinite recursion :-(
 *
 * Revision 1.2  2010-11-21 13:15:45  keinstein
 * merged experimental_tobias
 *
 * Revision 1.1.2.5  2010-09-30 16:26:26  keinstein
 * remove global variables routewindow and frame
 * move route loading and route saving into MutRouteWnd
 * implement MutRouteWnd::InitShapes.
 * Destroy Route children before loading new route configuration (still some crashes)
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
#include "src/kernel/routing/Device-inlines.h"
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
		bool found = Remove(oldroute);
		mutASSERT(found);
		if (found) 
			Add(newroute);

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
		bool found = i != routes.end();
		mutASSERT(found);
		(*i) = NULL;// list can save some memory for reuse,
		            // but route must be deleted
		routes.erase(i);
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
		if (open) {
			if (!newclass->IsOpen()) newclass->Open();
		}
		DevicePtr thisptr(static_cast<thistype *>(this));
		routeListType::iterator i;
		while ((i = routes.begin()) != routes.end()) {
			boost::const_pointer_cast<RouteClass>(*i)
				->Reconnect(thisptr, newclass);
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

        // CurrentTime ------------------------------------------------------
	CurrentTimer CurrentTime;

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

	void InputDeviceClass::Quite()
	{
		DEBUGLOG(smartptr,_T(""));
		for (routeListType::iterator R = routes.begin(); 
		     R != routes.end(); R++)
			if ((*R)->GetOutputDevice() )
				(*R)->GetOutputDevice()->Quite(R->get());
		DEBUGLOG(smartptr,_T(""));
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





	// functions --------------------------------------------------------
	// set timer
	void StartCurrentTime()
	{
		CurrentTime.Start(0);
	}

        // reset timer
	void StopCurrentTime()
	{
		// not needed any more
		//CurrentTime.Stop();
	}

	void OutNotesCorrect(int box)
	{
		const OutputDeviceList& list = OutputDeviceClass::GetDeviceList(); 
		for (OutputDeviceList::const_iterator Out = list.begin();
		     Out != list.end(); Out++)
			(*Out)->NotesCorrect(box);
	}

	bool OutOpen()
	{
		const OutputDeviceList& list = OutputDeviceClass::GetDeviceList(); 
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


	void MidiOut(int box, DWORD data, char n)
	{
		DEBUGLOG2(smartptr,_T(""));
		const routeListType & list = RouteClass::GetRouteList();
		for (routeListType::const_iterator R = list.begin(); 
		     R != list.end(); R++) {
			OutputDevice out;
			if ( (*R)->GetBox() == box && 
			     (out = (*R)->GetOutputDevice())) {
				out -> MidiOut(data, n);
			}
		}
		DEBUGLOG2(smartptr,_T(""));
	}

	void NotesCorrect(int box)
	{
		const OutputDeviceList& list = OutputDeviceClass::GetDeviceList(); 
		for (OutputDeviceList::const_iterator Out = list.begin();
		     Out != list.end(); Out++)
			(*Out)->NotesCorrect(box);
	}

	int GetChannel(int box, int taste)
	{
		DEBUGLOG2(smartptr,_T(""));
		const routeListType & list = RouteClass::GetRouteList();
		for (routeListType::const_iterator R = list.begin(); 
		     R != list.end(); R++) {
			OutputDevice out;
			if ( (*R)->GetBox() == box
			     && (out = (*R)->GetOutputDevice())) {
				int c = out->GetChannel(taste);
				
				if ( c != -1 ) {
					DEBUGLOG2(smartptr,_T(""));
					return c;
				}
			}
		}
		DEBUGLOG2(smartptr,_T(""));
		return -1;
	}

}

/// \}


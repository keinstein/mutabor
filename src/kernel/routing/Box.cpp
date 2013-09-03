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

#include "src/kernel/routing/Box.h"
#include <algorithm>
#include <queue>
#include "src/kernel/routing/Box-inlines.h"
#include "src/kernel/routing/Route-inlines.h"
#include "src/kernel/routing/Route.h"

// Old C-style Box internals
#include "src/kernel/box.h"
#include "src/kernel/Global.h"
#include "src/kernel/TabGen.h"
#include "src/kernel/Parser.h"
#include "src/kernel/Runtime.h"
#include "src/kernel/Execute.h"
#include "src/kernel/Hilfs.h"
#include "src/kernel/Interval.h"


namespace mutabor {
	using namespace hidden;
	template <> size_t idtype<BoxClass>::idpool(0);
	BoxListType BoxClass::boxList;
	int BoxClass::nextboxid = Box0;

#ifdef WX
	wxString BoxClass::TowxString() const {
		wxString routeString;
		for (routeListType::const_iterator r = routes.begin();
		     r != routes.end(); r++)
			routeString += wxString::Format(_T(" %d:(%d->%d->%d)"),
							(*r)->get_routefile_id(),
							(*r)->GetDeviceId(InputDevice()),
							(*r)->GetBoxId(),
							(*r)->GetDeviceId(OutputDevice()));
		

		return wxString::Format(_T("\nBox:\n\
   session_id    = %lu\n\
   routefile_id  = %d\n\
   routes: %s\n"),
					(unsigned long)session_id(),
					routefile_id,routeString.c_str());
	}
#endif
	

	BoxClass::~BoxClass()
	{
		// if there are remaining pointers we have other problems.
		DEBUGLOG(routing,_T("this = %p"),(void*)this);
		if (open) Close();
#ifdef Debug
		listttype::iterator i = FindInBoxList(this);
		if (i != boxList.end()) {
			UNREACHABLEC;
			deviceList.erase(i);
		}
#endif		
		debug_destruct_class(this);
		TRACEC;
		if (box) free(box);
	}

	void BoxClass::set_routefile_id(int id) {
		BoxLock lock(this);

		if (id == NewBox) {
			id = nextboxid++;
		} else if (id >= nextboxid)
			nextboxid = id + 1;
		routefile_id = id;
		mutASSERT(box);
		if (!box) return;
		box->id = routefile_id;
	}

	void BoxClass::Save (tree_storage & config) {
	}

	void BoxClass::Save (tree_storage & config, 
		   const RouteClass * route) {
	}

	void BoxClass::Load (tree_storage & config) {
	}

	void BoxClass::Load (tree_storage & config, 
			     RouteClass * route) {
	}

	void BoxClass::Add(Route & route) {
		BoxLock lock(this);
		DEBUGLOG(smartptr,_T("Route; %p"),(void*)route.get());
#ifdef DEBUG
		routeListType::const_iterator i = 
			find(routes.begin(),routes.end(),route);
		mutASSERT(i == routes.end());
		mutASSERT(IsInBoxList(this));
#endif
		TRACEC;
		routes.push_back(route);
		DEBUGLOG(smartptr,_T("Route; %p saved"),(void*)route.get());
	}

	bool BoxClass::Replace(Route & oldroute, Route & newroute) {
		DEBUGLOG(smartptr,_T("oldroute; %p, newroute; %p"),
			 (void*)oldroute.get(),(void*)newroute.get());
		bool found = Remove(oldroute);
		mutASSERT(found);
		if (found) 
			Add(newroute);

		DEBUGLOG(smartptr,_T("oldroute; %p, newroute; %p"),
			 (void*)oldroute.get(),(void*)newroute.get());
		return found;
	}

	bool BoxClass::Remove(Route & route) {
		BoxLock lock(this);
		DEBUGLOG(smartptr,_T("Route: %p (%d)"),
			 (void*)route.get(),
			 (int)intrusive_ptr_get_refcount(route.get()));
		routeListType::iterator i = 
			std::find(routes.begin(),routes.end(),route);
		bool found = (i != routes.end());
		mutASSERT(found);
		if (found) {
			(*i) = NULL;// list can save some memory for reuse,
			// but route must be deleted
			routes.erase(i);
		}
		DEBUGLOG(smartptr,_T("Route; %p (%d)"),(void*)route.get(),
			 (int)intrusive_ptr_get_refcount(route.get()));
		return found;
	}

	bool BoxClass::MoveRoutes (Box & newclass) {
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
		Box thisptr(this);
		routeListType::iterator i;
		while ((i = routes.begin()) != routes.end()) {
			reconnect(*i, thisptr, newclass);
		}
		TRACEC;
		return true;
	}

	void BoxClass::InitializeIds()
	{
		return;
#if 0
		/* currently, the user provides the numeric ids, so we don't need to deal with that problem */
		TRACET(thistype);
		size_t nr = 0;
		for (typename listtype::iterator i = deviceList.begin();
		     i != deviceList.end();
		     i++) {
			(*i)->set_file_id(nr);
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
#endif
	}

	Box BoxClass::GetBox(int id, boxidtype kind)
	{
		for (typename listtype::iterator i = boxList.begin();
		     i != boxList.end();
		     i++) {
			int devid;
			switch (kind) {
			case IDTypeSession:
				devid = (*i)->get_session_id();
				break;
			case IDTypeFile:
				devid = (*i)->get_routefile_id();
				break;
			default:
				UNREACHABLECT(BoxClass);
				return *(boxList.end());
			}
			if (devid == id) {
				return (*i);
			}
		}
		return NULL;
	}


	int BoxClass::MoveInList(int count) {
		if (!count) return -1;
		typename listtype::iterator pos = FindInBoxList(Box(this));

		if (pos == boxList.end()) return -1;
		typename listtype::iterator newpos = pos + count;
		if (newpos == boxList.end()) --newpos;
		if (count > 0) 
			std::rotate (pos, newpos, newpos + 1);
		else 
			std::rotate (newpos, pos, pos + 1);
		return newpos - boxList.begin();
		
	}

// protected:

	void BoxClass::AppendToBoxList (Box b) 
	{
#ifdef DEBUG
		typename listtype::iterator i = 
			FindInBoxList(b);
		if (i != boxList.end()) {
			UNREACHABLECT(listtype);
		}
#endif
		boxList.push_back(b);
	}

	void BoxClass::RemoveFromBoxList (Box b) 
	{
		typename listtype::iterator i = 
			FindInBoxList(b);
		if (i == boxList.end()) {
			UNREACHABLECT(listtype);
		} else 	
			boxList.erase(i);
	}

	void BoxClass::TruncateBoxList (Box dev) 
	{
		STUB;
		return;
#if 0
		if (!boxList) return;
        
		if (boxList == dev) {
			boxList = NULL; 
			return;
		}
	
		DevicePtr d = boxList ;
		while (d->GetNext() && d->GetNext() != dev) {
			d = d->GetNext();
		}
		if (d->GetNext()) {
			d -> SetNext(NULL);
		}
#endif
	}


	void BoxClass::Panic() {
		BoxLock lock(this);
		mutASSERT(open);
		hidden::mutabor_reset_keys(box);
	}

	void BoxClass::Reset() {
		hidden::mutabor_reset_box(box);
#if 0
		hidden::mutabor_reset_action_trace(box);
#endif
	}


	bool BoxClass::Open() {
		BoxLock lock(this);
		Reset();
		// hidden::mutabor_reset_action_trace(box);
		open = true;
		return true;
	}

	void BoxClass::Close() {
		BoxLock lock(this);
		Reset();
		open = false;
	}

	struct BoxClass_CallReset {
		void operator () (Box & box) {
			box->Reset();
		}
	};

	struct BoxClass_CallOpen{
		bool ok;
		BoxClass_CallOpen():ok(true) {}
		void operator () (Box & box) {
			if (ok)
				ok = box->Open();
		}
	};


	struct BoxClass_CallClose{
		void operator () (Box & box) {
			box->Close();
		}
	};

	void BoxClass::CloseAll() {
		BoxClass_CallClose callclose;
		std::for_each(boxList.begin(),boxList.end(),callclose);
	}


	bool BoxClass::ActivateAll(bool realtime) {
		CurrentTime.UseRealtime(realtime);
		mutabor::CurrentTime = 0;
		BoxClass_CallReset callreset;

		std::for_each(boxList.begin(),boxList.end(),callreset);
		//AktionenInit();

		// In batch mode Batch Play handles open and close.
		if (realtime)
			return OpenAll();
		else return true;
	}
	
	void  BoxClass::StopAll() {
		mutabor::CurrentTime.Stop();
		mutabor::InClose();
		mutabor::OutClose();
		
	}
	
	bool BoxClass::Compile(CompileCallback * callback, const char * logic) {
		set_callback callback_holder(this,callback);
		if (!setjmp(weiter_gehts_nach_compilerfehler)) {
			loesche_syntax_speicher(box);
			//			init_yylex ();

			mutabor_programm_einlesen (box, logic);
			
			if (callback) {
				callback->SetStatus(logik_list_laenge(box->file->list_of_logiken),
						    ton_list_laenge(box->file->list_of_toene),
						    umstimmungs_list_laenge(box->file->list_of_umstimmungen),
						    tonsystem_list_laenge(box->file->list_of_tonsysteme),
						    intervall_list_laenge(box->file->list_of_intervalle),
						    box->scanner->anzahl_eingelesene_zeichen);

				//	 show_line_number(-1);

				callback->SetStatus(_("Generating tables"));
				callback->Refresh();
			}

			mutabor_tabellen_generator(box);


			if (callback) {
				callback->SetStatus(_("Translation successful"));
				callback->SetMessage(_("No error occured."));
				callback->Refresh();
			}
			return true;
		} else {
			//show_line_number(-1);
			if (callback) {
				callback->SetStatus(_("Translation interrupted."));
				callback->SetMessage(get_errors());
				callback->Refresh();
			}

			return false;
		}
	}

	void BoxClass::MidiOut(struct midiliste * outliste) {
		size_t laenge = midi_list_laenge(outliste);
		midi_string data(laenge);
		struct midiliste * cursor = outliste;
		uint8_t * bcursor = data.data();
		while (cursor != NULL) {
			(*bcursor++) = (uint8_t) cursor->midi_code;
			cursor = cursor -> next;
		}
	       
		for (routeListType::const_iterator R = routes.begin(); 
		     R != routes.end(); R++) {
			(*R) -> MidiOut(data);
		}
	}

	void BoxClass::UpdateTones()
	{
		for (routeListType::const_iterator route = routes.begin();
		     route != routes.end(); route++) {
			(*route)->UpdateTones();
		}
	}


	int BoxClass::GetChannel(int key, size_t channel, size_t id)
	{
		for (routeListType::const_iterator R = routes.begin(); 
		     R != routes.end(); R++) {
			int c = (*R)->GetChannel(key,channel,id);
			
			if ( c != midi::NO_CHANNEL ) {
				TRACE;
				return c;
			}
		}
		return midi::NO_CHANNEL;
	}

	inline static bool is_logic_key(struct keyboard_ereignis * e, int key) {
		while (e) {
			if ( key == e->taste )
				return e->the_logik_to_expand != NULL;
			e = e->next;
		}
		return false;
	}

	bool BoxClass::IsLogicKey(int key) {
		if (is_logic_key(box->file->global_keystrokes, key))
			return true;
		return is_logic_key(box->current_logic->keystroke_list, key);
	}


	long BoxClass::get_frequency(int note) {
		if (!box) return LONG_MIN;
		return mutabor_get_note_frequency(note, box->tonesystem);
	}


	int BoxClass::get_index(int note) {
		if (!box) return INT_MIN;
		return mutabor_get_note_index(note, box->tonesystem);
	}

	int BoxClass::get_distance(int note) {
		if (!box) return INT_MIN;
		return mutabor_get_note_distance(note, box->tonesystem);
	}

	void BoxClass::runtime_error(bool iswarning, const char * message) {
		fprintf(stderr,"%s: %s\n",(iswarning?_mut("Warning"):_mut("Error")),message);
	}

	BoxClass::BoxClass(int id): box(NULL),
				    session_id(),
				    routefile_id(Box0),
				    routes(),
				    open (false),
				    current_logic(),
				    current_tonesystem(),
				    current_key_tonesystem(0),
				    current_key_logic(0),
				    updateflags(0),
				    callbacks(),
				    current_compile_callback(NULL),
				    mutex() {
		AppendToBoxList(this);
		box = (mutabor_box_type *) malloc(sizeof(mutabor_box_type));
		if (!box) return;
		mutabor_initialize_box(box,id);
		box->userdata = this;
		set_routefile_id(id);
	}

	struct doexecute_flags {
		unsigned int flags;
		doexecute_flags(unsigned int f):flags(f) {}
		void operator () (BoxClass::ChangedCallback * callback) {
			callback->BoxChangedAction(flags);
		}
	};
	struct doexecute_action {
		BoxClass::ChangedCallback::action * action;
		doexecute_action(BoxClass::ChangedCallback::action * a):action(a) {}
		void operator () (BoxClass::ChangedCallback * callback) {
			callback->BoxChangedAction(action);
		}
	};

	void BoxClass::ExecuteCallbacks(unsigned int flags) {
		doexecute_flags doit(flags);
		std::for_each(callbacks.begin(),callbacks.end(),doit);
	}

	void BoxClass::ExecuteCallbacks(ChangedCallback::action * action) {
		doexecute_action doit(action);
		std::for_each(callbacks.begin(),callbacks.end(),doit);
	}


	void BoxClass::UpdateCallback(struct mutabor_box_type * b, unsigned int flags) {
		unsigned int newflags = 0;
		if (flags & mutabor::hidden::mutabor_box_changed) newflags |= ChangedCallback::BoxChanged;
		if (flags & mutabor::hidden::mutabor_logic_changed) newflags |= ChangedCallback::LogicChanged;
		if (flags & mutabor::hidden::mutabor_keys_changed) newflags |= ChangedCallback::KeysChanged;
		if (flags & mutabor::hidden::mutabor_action_changed) newflags |= ChangedCallback::ActionChanged;
		((BoxClass *)b->userdata) -> updateflags |= newflags;
	}


	void BoxClass::MidiOutCallback(struct mutabor::hidden::mutabor_box_type * b, 
				       struct mutabor::hidden::midiliste * outliste) {
		BoxClass * box = (BoxClass *)b -> userdata;
		if (!box) return;
		box->MidiOut(outliste);
	}

	void BoxClass::compile_callback(struct mutabor_box_type * b, int line_number) {
		BoxClass * box = (BoxClass *)b -> userdata;
		if (box->current_compile_callback) {
			box->current_compile_callback->SetLine(line_number);
		}
	}

	static void error_callback(mutabor_box_type * b, bool iswarning,
			      const char * message) {
		
		BoxClass * box = (BoxClass *)b -> userdata;
		box->runtime_error(iswarning,message);
	}

#warning implement logic locking
	static void lock_callback(mutabor_logic_parsed * logic) {
		std::cerr << "warning: logic locking is not implemented" << std::endl;
	}

#warning implement logic unlocking
	static void unlock_callback(mutabor_logic_parsed * logic) {
		std::cerr << "warning: logic unlocking is not implemented" << std::endl;
	}


	void BoxClass::log_action(mutabor_box_type * b, 
				  struct mutabor::hidden::do_aktion * action) {
		
		BoxClass * box = (BoxClass *)b -> userdata;
		box->ExecuteCallbacks(action);
	}

	struct mutabor::hidden::mutabor_callback_type BoxClass::backend_callbacks  = {
		BoxClass::UpdateCallback,
		BoxClass::MidiOutCallback,
		error_callback,
		BoxClass::compile_callback,
		log_action,
		lock_callback,
		unlock_callback
	};
	


	BoxFactory::factorylist BoxFactory::factories;

	BoxFactory::BoxFactory(size_t type) {
		if (type < 0) type = 0;
		if (factories.size() <= type) {
			factories.resize(type+1,NULL);
		}
		if (factories[type]) {
			UNREACHABLEC;
			return;
		}
		factories[type] = this;
		
	}

	BoxFactory::~BoxFactory() {}

	void BoxFactory::LoadBoxes(tree_storage & config)
	{
#ifdef DEBUG
		wxString oldpath = config.GetPath();
#endif
		config.toLeaf(_T("Boxes"));
	
		int i = config.toFirstLeaf(_T("Box"));
		while (i != wxNOT_FOUND) {
			DEBUGLOGTYPE(config,BoxClass,_T("Loading box device with id %d"),i);
			int type = config.Read(_T("Type"), NoBox);
			Box b = BoxFactory::Create(type);
			if (!b) continue;
			b -> set_file_id(i);
			b -> Load(config);
			i = config.toNextLeaf(_T("Box"));
		}
	
		config.toParent(2);
		mutASSERT(oldpath == config.GetPath());
	}

	void BoxFactory::SaveBoxes(tree_storage & config)
	{
#ifdef DEBUG
		wxString oldpath = config.GetPath();
#endif
		config.toLeaf(_T("Boxes"));
	
		const BoxListType & list = 
			BoxClass::GetBoxList();
		for (BoxListType::const_iterator b = list.begin(); 
		     b != list.end(); b++) {
			int id = (*b)->get_routefile_id();
			config.toLeaf(_T("Box"), id);
			config.Write(_T("Type"), (*b)->GetType() );
			config.Write(_T("Type Name"),(*b)->GetTypeName());
			(*b) -> Save (config);
			config.toParent();
		}
	
		config.toParent();
		mutASSERT(oldpath == config.GetPath());
	}


	BoxClass * BoxFactory::DoCreateBox(int id) const {
		BoxClass * box = new BoxClass(id);
		if (!box) throw BoxNotCreated();
		return box;
	}

	void BoxFactory::DoLoadBoxes(tree_storage & config) const
	{
		STUBC;
	}

	void BoxFactory::DoSaveBoxes(tree_storage & config) const
	{
		STUBC;
	}


	struct dopanic_type {
		void operator () (InputDevice in) {
			in->Panic();
		}
		void operator () (Box box) {
			box->Panic();
		}
		void operator () (OutputDevice out) {
			out->Panic();
		}
	};

	void  Panic() {
		dopanic_type dopanic;
	
		const InputDeviceList & inlist = InputDeviceClass::GetDeviceList();
		std::for_each(inlist.begin(),inlist.end(),dopanic);

		const BoxListType & boxlist = BoxClass::GetBoxList();
		std::for_each(boxlist.begin(),boxlist.end(),dopanic);
	
		const OutputDeviceList & outlist = OutputDeviceClass::GetDeviceList();
		std::for_each(outlist.begin(),outlist.end(),dopanic);
	}


	bool OpenAll() {
		BoxClass_CallOpen callopen;
		if (!mutabor::OutOpen())
			return false;

		BoxListType & boxList = const_cast<BoxListType &>(BoxClass::GetBoxList());
		std::for_each(boxList.begin(),boxList.end(),callopen);
		if (!callopen.ok) {
			BoxClass::CloseAll();
			OutClose();
			return false;
		}
		
		if (!InOpen() ) {
			BoxClass::CloseAll();
			OutClose();
			return false;
		}

#if 0
		if ( !ok ) {
			wxMessageBox(Fmeldung, _("Activation error"), wxOK | wxICON_ASTERISK );

			return false;
		}
#endif
		return true;
	}


	void initialize_box_data() 
	{
		mutabor_set_callbacks(& BoxClass::backend_callbacks);
	}
	
}

/// \}


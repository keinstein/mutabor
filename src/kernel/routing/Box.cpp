// -*- C++ -*-

/** \file
 ********************************************************************
 * Devices for routing. Mutabor Core.
 *
 * \author Rüdiger Krauße <krausze@mail.berlios.de>,
 * Tobias Schlemmer <keinstein@users.sourceforge.net>
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
#include "src/kernel/Interpre.h"
#include "src/kernel/Hilfs.h"
#include "src/kernel/Interval.h"
#include "src/kernel/routing/watchdog.h"

namespace mutabor {
	using namespace hidden;
	template <> size_t idtype<BoxClass>::idpool(1);
	BoxListType BoxClass::boxList;
	int BoxClass::nextboxid = Box0;

	BoxClass::operator std::string() const {
		std::string routeString;
		for (routeListType::const_iterator r = routes.begin();
		     r != routes.end(); r++)
			routeString += boost::str(boost::format((" %d:(%d->%d->%d)"))
						  % (*r)->get_routefile_id()
						  % (*r)->GetDeviceId(InputDevice())
						  % (*r)->GetBoxId()
						  %(*r)->GetDeviceId(OutputDevice()));


		return boost::str(boost::format("\nBox:\n\
   session_id    = %lu\n\
   routefile_id  = %d\n\
   routes: %s\n") % (unsigned long)session_id()
				  % routefile_id
				  % routeString.c_str());
	}


	BoxClass::~BoxClass()
	{
		// if there are remaining pointers we have other problems.
		DEBUGLOG (routing, "this = %p" ,(void*)this);
		if (open) Close();
		mutASSERT(!loopguard);
#ifdef DEBUG
		// prevent from endless destroy loop
		intrusive_ptr_add_ref(this);
		intrusive_ptr_add_ref(this);
		BoxListType::iterator i = FindInBoxList(this);
		if (i != boxList.end()) {
			UNREACHABLEC;
			//		boxList.erase(i);
		}
#endif
		TRACEC;
		debug_destruct_class(this);
		if (box) {
			mutabor_delete_box(box);
		}
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
		mutUnused(config);
	}

	void BoxClass::Save (tree_storage & config,
		   const RouteClass * route) {
		mutUnused(config);
		mutUnused(route);
	}

	void BoxClass::Load (tree_storage & config) {
		mutUnused(config);
	}

	void BoxClass::Load (tree_storage & config,
			     RouteClass * route) {
		mutUnused(config);
		mutUnused(route);
	}

	void BoxClass::Add(Route & route) {
		BoxLock lock(this);
		DEBUGLOG (smartptr, "Route; %p" ,(void*)route.get());
#ifdef DEBUG
		routeListType::const_iterator i =
			std::find(routes.begin(),routes.end(),route);
		mutASSERT(i == routes.end());
		mutASSERT(IsInBoxList(this));
#endif
		TRACEC;
		routes.push_back(route);
		DEBUGLOG (smartptr, "Route; %p saved" ,(void*)route.get());
	}

	bool BoxClass::Replace(Route & oldroute, Route & newroute) {
		DEBUGLOG (smartptr, "oldroute; %p, newroute; %p" ,
			 (void*)oldroute.get(),(void*)newroute.get());
		bool found = Remove(oldroute);
		mutASSERT(found);
		if (found)
			Add(newroute);

		DEBUGLOG (smartptr, "oldroute; %p, newroute; %p" ,
			 (void*)oldroute.get(),(void*)newroute.get());
		return found;
	}

	bool BoxClass::Remove(Route & route) {
		BoxLock lock(this);
		DEBUGLOG (smartptr, "Route: %p (%d)" ,
			 (void*)route.get(),
			 (int)intrusive_ptr_get_refcount(route.get()));
		bool found =
			routes.erase(route);
		mutASSERT(found);
		DEBUGLOG (smartptr, "Route; %p (%d)" ,(void*)route.get(),
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
		TRACET(BoxClass);
		size_t nr = 0;
		for (typename listtype::iterator i = boxList.begin();
		     i != boxList.end();
		     i++) {
			/* currently, the user provides the numeric ids, so we don't need to change them */
			//(*i)->set_routefile_id(nr);
			nr = (*i)->get_routefile_id();
			routeListType & list = (*i)->routes;
			for (routeListType::iterator j = list.begin();
			     j != list.end();
			     j++) {
				//thistype * ptr = NULL;
				(*j)->SetBoxId(nr);
			}
			//		nr++;
		}
		return;
#if 0
		for (typename listtype::iterator i = deviceList.begin();
		     i != deviceList.end();
		     i++) {
			(*i)->set_routexfile_id(nr);
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
		int current_pos = pos - boxList.begin();
		typename listtype::iterator newpos;
		if (current_pos + count <= 0) {
			newpos = boxList.begin();
			count = -1;
		} else 	if ((size_t)(current_pos + count) >= boxList.size()) {
			newpos = boxList.end() - 1;
			count = 1;
		} else {
			newpos = pos + count;
		}

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
		DEBUGLOG2(routing,("Adding box %p"),b.get());
		print_stacktrace(isDebugFlag(smartptr));
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
		mutUnused(dev);
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


	void BoxClass::Panic(Route r, int type, size_t unique_id)
	{
		mutUnused(r);
		mutUnused(type);
		mutUnused(unique_id);
#ifdef DEBUG
		BoxLock lock(this);

		size_t channel = r -> get_session_id();
		mutabor_note_type * key;
		size_t index = 0;
		while ((key = hidden::mutabor_find_key_in_box(box,
							      index))
		       != NULL) {
			if (key -> channel == channel
			    && key -> id == unique_id)
				break;
			index = key->next;
		}

		mutASSERT(key == NULL);
#endif

	}

	void BoxClass::Panic(Route r, int type)
	{
		mutUnused(r);
		mutUnused(type);
#ifdef DEBUG
		BoxLock lock(this);

		size_t channel = r -> get_session_id();
		mutabor_note_type * key;
		size_t index = 0;
		while ((key = hidden::mutabor_find_key_in_box(box,
							      index))
		       != NULL) {
			if (key -> channel == channel)
				break;
			index = key->next;
		}

		if (key != NULL) {
			DEBUGLOG (routing, "(key = %d, channel = %lu, id = %lu)" ,
				 key->number,
				 key->channel,
				 key->id);

		}
		mutASSERT(key == NULL);
#endif

	}

	void BoxClass::Panic(int type) {
		mutUnused(type);
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


	bool BoxClass::DoOpen() {
		Reset();


		/* creating threads might be expensive. So we
		   create it here, as Play() must be
		   considered to be a realtime function
		   synchronized with other devices */
		try {
			mutASSERT(!loopguard);
			loopguard = new watchdog<Box>(this,
						      loop_timeout);
			if (!loopguard) {
				Close();
				return false;
			}
		} catch (boost::thread_resource_error & e) {
			DEBUGLOG(thread,
				 "Thread %s could not aquire thread resources for loopguard",
				 Thread::get_current_string_id().c_str());
			delete loopguard;
			loopguard = NULL;
			Close();
			return false;
		} catch (std::exception & e) {
			DEBUGLOG(thread,
				 "Thread %s got an exception while creating loopguard: %s",
				 Thread::get_current_string_id().c_str(),
				 e.what());
			delete loopguard;
			loopguard = NULL;
			Close();
			return false;
		} catch (...) {
			delete loopguard;
			loopguard = NULL;
			Close();
			return false;
		}
		loopguard->Run();
		// hidden::mutabor_reset_action_trace(box);
		return true;
	}

	void BoxClass::DoClose() {
		Reset();
		mutASSERT(loopguard);
		if (loopguard) {
			loopguard -> request_exit();
			delete loopguard;
			loopguard = NULL;
			mutASSERT(loopguard == NULL);
		}
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

	bool OpenAll(int mode) {
		BoxClass_CallOpen callopen;
		bool openout = mode & OpenAllOutDevices;
		bool openboxes = mode & OpenAllBoxes;
		bool openin  = mode & OpenAllInDevices;
		if (openout)
			if (!mutabor::OutOpen())
				return false;

		if (openboxes) {
			BoxListType & boxList = const_cast<BoxListType &>(BoxClass::GetBoxList());
			std::for_each(boxList.begin(),boxList.end(),callopen);
			if (!callopen.ok) {
				BoxClass::CloseAll();
				if (openout)
					OutClose();
				return false;
			}
		}

		if (openin) {
			if (!InOpen() ) {
				if (openboxes)
					BoxClass::CloseAll();
				if (openout)
					OutClose();
				return false;
			}
		}


#if 0
		if ( !ok ) {
			wxMessageBox(Fmeldung, _mut("Activation error"), wxOK | wxICON_ASTERISK );

			return false;
		}
#endif
		return true;
	}

	void BoxClass::CloseAll() {
		BoxClass_CallClose callclose;
		std::for_each(boxList.begin(),boxList.end(),callclose);
	}


	bool BoxClass::ActivateAll(bool realtime) {
		CurrentTime.UseRealtime(realtime);
		mutabor::CurrentTime.Reset();
		BoxClass_CallReset callreset;

		std::for_each(boxList.begin(),boxList.end(),callreset);
		//AktionenInit();

		// In batch mode Batch Play handles open and close.
		bool retval = OpenAll(OpenAllBoxes
				      | (realtime?
					 OpenAllOutDevices
					 | OpenAllInDevices
					 : 0)) ;

		if (!boxList.empty()) {
			mutabor::Box b = boxList.front();
			if (b) b->Activate();
		}
		return retval;
	}

	void  BoxClass::StopAll() {
		mutabor::CurrentTime.Stop();
		mutabor::InClose();
		mutabor::OutClose();
		CloseAll();
	}

	static inline void append_triggers (BoxClass::logic_list & list,
					    mutabor_box_type * box,
					    struct mutabor::hidden::logik * logic,
					    struct keyboard_ereignis * keystrokes) {
		for (struct keyboard_ereignis * i = keystrokes;
		     i ; i=i->next) {
			const char * start_tuning = (i->the_logik_to_expand && i->the_logik_to_expand->parser_tuning?
						     i->the_logik_to_expand->parser_tuning->u.aktion_aufruf.name:
						     (i->aktion?i->aktion->name:i->name));
			BoxClass::logic_entry entry = {
				((i->the_logik_to_expand == NULL)?
				 BoxClass::logic_entry::none:
				 ((i->the_logik_to_expand == logic)?
				  BoxClass::logic_entry::CurrentLogic :
				  BoxClass::logic_entry::Logic)),
				(box->last_trigger.type
				 == mutabor::hidden::any_trigger::key &&
				 box->last_trigger.u.key_trigger == i),
				(i->name?i->name:""),
				(start_tuning?start_tuning:""),
				i->taste,
				{ mutabor::hidden::any_trigger::key, i }
				};
			list.push_back(entry);
		}
	}

	static inline void append_triggers (BoxClass::logic_list & list,
					    mutabor_box_type * box,
					    struct mutabor::hidden::logik * logic,
					    struct harmonie_ereignis * harmonies) {
		for (struct harmonie_ereignis * i = harmonies;
		     i ; i=i->next) {
			mutabor::hidden::any_trigger trigger;
			trigger.type = mutabor::hidden::any_trigger::harmony;
			trigger.u.harmony_trigger = i;
			BoxClass::logic_entry entry = {
				((i->the_logik_to_expand == NULL)?
				 BoxClass::logic_entry::none:
				 ((i->the_logik_to_expand == logic)?
				  BoxClass::logic_entry::CurrentLogic :
				  BoxClass::logic_entry::Logic)),
				(box->last_trigger.type ==
				 mutabor::hidden::any_trigger::harmony &&
				 box->last_trigger.u.harmony_trigger == i),
				i->name,
				(i->the_logik_to_expand && i->the_logik_to_expand->parser_tuning
				 ?i->the_logik_to_expand->parser_tuning->u.aktion_aufruf.name:
				 (i->aktion?i->aktion->name:i->name)),
				-1,
				trigger
				};
			list.push_back(entry);
		}
	}

	static inline void append_triggers (BoxClass::logic_list & list,
					    mutabor_box_type * box,
					    struct mutabor::hidden::logik * logic,
					    struct midi_ereignis * midis) {
		for (struct midi_ereignis * i = midis;
		     i ; i=i->next) {
			mutabor::hidden::any_trigger trigger;
			trigger.type = mutabor::hidden::any_trigger::midi;
			trigger.u.midi_trigger = i;
			BoxClass::logic_entry entry = {
				((i->the_logik_to_expand == NULL)?
				 BoxClass::logic_entry::none:
				 ((i->the_logik_to_expand == logic)?
				  BoxClass::logic_entry::CurrentLogic :
				  BoxClass::logic_entry::Logic)),
				(box->last_trigger.type == mutabor::hidden::any_trigger::midi &&
				 box->last_trigger.u.midi_trigger == i),
				i->name,
				(i->the_logik_to_expand && i->the_logik_to_expand->parser_tuning?
				 i->the_logik_to_expand->parser_tuning->u.aktion_aufruf.name:
				 (i->aktion?i->aktion->name:i->name)),
				-1,
				trigger
				};
			list.push_back(entry);
		}
	}

	BoxClass::logic_list BoxClass::GetLogics () {
		ScopedLock<> lock(mutex);
		logic_list retval;
		if (!box) return retval;
		struct mutabor_logic_parsed * file = box->file;
		if (!file) return retval;
		// no file means no logic (implying no current logic)

		struct mutabor::hidden::logik * logic = box->current_logic;
		append_triggers (retval, box, logic, file->global_keystrokes );
		append_triggers (retval, box, logic, file->global_harmonies  );
		append_triggers (retval, box, logic, file->global_midi_inputs);
		if (logic) {
			append_triggers(retval, box, logic, logic->keystroke_list );
			append_triggers(retval, box, logic, logic->harmony_list   );
			append_triggers(retval, box, logic, logic->midi_input_list);
		}
		return retval;
	}

	box_support::tone_system BoxClass::GetToneSystem () {
		ScopedLock<> lock(mutex);
		box_support::tone_system retval;
		retval.anchor = 60;
		retval.period = 1;
		if (!box) return retval;
		struct mutabor_logic_parsed * file = box->file;
		if (!file) return retval;
		// no file means no logic (implying no current logic)

		hidden::tone_system * system = box->tonesystem;
		if (!system)
			return retval;
		retval.anchor = system->anker;
		retval.period =
			mutabor_get_pitch_from_interval(system->periode);
		int width = system -> breite;
		if (width <= 0)
			return retval;
		retval.tones.resize(width);
		mutASSERT(width <= MUTABOR_KEYRANGE_MAX_WIDTH);
		for (int i = 0 ; i < width; i++) {
			mutabor_tone t = system->ton[i];
			switch (mutabor_get_tone_type(t)) {
			case mutabor_empty_tone:
				break;
			case mutabor_invalid_tone:
				retval.tones[i].flag = box_support::tone_entry::invalid;
				break;
			case mutabor_active_tone:
			default:
				retval.tones[i] =
					box_support::tone_entry(mutabor_get_pitch_from_tone(t));
			}
		}
		return retval;
	}

	BoxClass::current_tone_list BoxClass::GetCurrentTones()
	{
		ScopedLock<> lock(mutex);
		current_tone_list retval;
		if (!box) return retval;
		struct mutabor_logic_parsed * file = box->file;
		if (!file) return retval;
		// no file means no logic (implying no current logic)

		int count = box->key_count;
		if (!count) return retval;
		retval.resize(count);

		size_t i = 0;
		for (mutabor_note_type * key = mutabor_find_key_in_box(box,0);
		     key != NULL;
		     key = mutabor_find_key_in_box(box,key->next)) {

			int index = key->number;
			tone t = get_frequency(index);

			switch (t.get_type()) {
			case mutabor_empty_tone:
				retval[i].index = index;
				break;
			case mutabor_invalid_tone:
				retval[i].flag=box_support::tone_entry::invalid;
				break;
			default:
				retval[i] = current_tone_entry(index,
							       mutabor_get_pitch_from_tone(t),
							       key->id,
							       GetChannel(index, key->channel, key->id));
			}
			++i;
		}
		return retval;
	}

	bool BoxClass::Compile(CompileCallback * callback, const char * logic) {

		set_callback callback_holder(this,callback);
		if (!setjmp(weiter_gehts_nach_compilerfehler)) {
			mutabor_box_clear_logic(box);
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

				callback->SetStatus(_mut("Generating tables"));
				callback->RefreshDlg();
			}

			mutabor_clear_box_scanner(box);

			expand_decition_tree(box);


			if (callback) {
				callback->SetStatus(_mut("Translation successful"));
				callback->SetMessage(_mut("No error occured."));
				callback->RefreshDlg();
			}
			return true;
		} else {
			//show_line_number(-1);
			if (callback) {
				callback->SetStatus(_mut("Translation interrupted."));
				callback->SetMessage(get_errors());
				callback->RefreshDlg();
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


	BoxClass::tone BoxClass::get_frequency(int note) {
		if (!box)
			return tone();
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

	void BoxClass::runtime_error(error_type type, const char * message) {
	    fprintf(stderr,"%s: %s\n",to_string(type),message);
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
				    mutex(),
				    logic_timing(-1),
				    loop_timeout(500000),
				    loopguard(0)
	{
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
		const char * action;
		doexecute_action(const char * a):action(a) {}
		void operator () (BoxClass::ChangedCallback * callback) {
			callback->BoxChangedAction(action);
		}
	};

	void BoxClass::ExecuteCallbacks(unsigned int flags) {
		doexecute_flags doit(flags);
		std::for_each(callbacks.begin(),callbacks.end(),doit);
	}

	void BoxClass::ExecuteCallbacks(const char * action) {
		doexecute_action doit(action);
		std::for_each(callbacks.begin(),callbacks.end(),doit);
	}


	std::string BoxClass::ActionToString(mutabor::BoxClass::ChangedCallback::action * action) {
		std::string retval = action->name;
		return retval;
	}



	void BoxClass::UpdateCallback(mutabor_box_type * b, unsigned int flags) {
		unsigned int newflags = 0;
		if (flags & mutabor::hidden::mutabor_box_changed) newflags |= ChangedCallback::BoxChanged;
		if (flags & mutabor::hidden::mutabor_logic_changed) newflags |= ChangedCallback::LogicChanged;
		if (flags & mutabor::hidden::mutabor_keys_changed) newflags |= ChangedCallback::KeysChanged;
		if (flags & mutabor::hidden::mutabor_action_changed) newflags |= ChangedCallback::ActionChanged;
		reinterpret_cast<BoxClass *>(b -> userdata) -> updateflags |= newflags;
	}


	void BoxClass::MidiOutCallback(mutabor::hidden::mutabor_box_type * b,
				       struct mutabor::hidden::midiliste * outliste) {
		BoxClass * box =
			reinterpret_cast<BoxClass *>(b -> userdata);
		if (!box) return;
		box->MidiOut(outliste);
	}

	void BoxClass::compile_callback(mutabor_box_type * b, int line_number) {
		BoxClass * box =
			reinterpret_cast<BoxClass *>(b -> userdata);
		if (box->current_compile_callback) {
			box->current_compile_callback->SetLine(line_number);
		}
	}

	static void error_callback(mutabor_box_type * b, error_type type,
			      const char * message) {

		BoxClass * box =
			reinterpret_cast<BoxClass *>(b -> userdata);
		box->runtime_error(type, message);
	}

	void BoxClass::lock_callback(mutabor_logic_parsed * logic) {
		if (!logic->mutex) {
			logic->mutex = new Mutex<>;
		}
		if (logic->mutex) {
			static_cast<Mutex<> *>(logic->mutex)->Lock();
		}
	}

	void BoxClass::unlock_callback(mutabor_logic_parsed * logic) {
		mutASSERT(logic->mutex);
		if (logic->mutex) {
			static_cast<Mutex<> *>(logic->mutex)->Unlock();
		}
	}

	void BoxClass::free_mutex_callback(mutabor_logic_parsed * logic) {
		mutASSERT(logic->mutex);
		if (logic->mutex) {
			Mutex<> * m = static_cast<Mutex<> *>(logic->mutex);
			delete m;
		}
	}


	void BoxClass::log_action(mutabor_box_type * b,
				  const char * action) {

		BoxClass * box =
			reinterpret_cast<BoxClass *>(b -> userdata);
		box->ExecuteCallbacks(action);
	}

	struct mutabor::hidden::mutabor_callback_type BoxClass::backend_callbacks  = {
		BoxClass::UpdateCallback,
		BoxClass::MidiOutCallback,
		error_callback,
		BoxClass::compile_callback,
		BoxClass::log_action,
		BoxClass::lock_callback,
		BoxClass::unlock_callback,
		BoxClass::free_mutex_callback
	};



	BoxFactory::factorylist BoxFactory::factories;

	BoxFactory::BoxFactory(size_t type) {
		// if (type < 0) type = 0;
		if (factories.size() <= type) {
			factories.resize(type+1,
					 NULL);
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
		std::string oldpath = config.GetPath();
#endif
		config.toLeaf(("Boxes"));
		const int NOT_FOUND = config.getNOT_FOUND();
		int i = config.toFirstLeaf(("Box"));
		while (i != NOT_FOUND) {
			DEBUGLOGTYPE(config,BoxClass,("Loading box device with id %d"),i);
			int type = config.Read(("Type"), NoBox);
			Box b = BoxFactory::Create(type);
			if (!b) continue;
			b -> set_routefile_id(i);
			b -> Load(config);
			i = config.toNextLeaf(("Box"));
		}

		config.toParent(2);
		mutASSERT(oldpath == config.GetPath());
	}

	void BoxFactory::SaveBoxes(tree_storage & config)
	{
#ifdef DEBUG
		std::string oldpath = config.GetPath();
#endif
		config.toLeaf(("Boxes"));

		const BoxListType & list =
			BoxClass::GetBoxList();
		for (BoxListType::const_iterator b = list.begin();
		     b != list.end(); b++) {
			int id = (*b)->get_routefile_id();
			config.toLeaf(("Box"), id);
			config.Write(("Type"), (*b)->GetType() );
			config.Write(("Type Name"),(*b)->GetTypeName());
			(*b) -> Save (config);
			config.toParent();
		}

		config.toParent();
		mutASSERT(oldpath == config.GetPath());
	}


	BoxClass * BoxFactory::DoCreateBox(int id) const {
		BoxClass * box = new BoxClass(id);
		if (!box) BOOST_THROW_EXCEPTION(BoxNotCreated());
		return box;
	}

	void BoxFactory::DoLoadBoxes(tree_storage & config) const
	{
		mutUnused(config);
		STUBC;
	}

	void BoxFactory::DoSaveBoxes(tree_storage & config) const
	{
		mutUnused(config);
		STUBC;
	}


	struct dopanic_type {
		dopanic_type(int t):type(t) {}
		int type;
		void operator () (InputDevice in) {
			in->Panic(type);
		}
		void operator () (Box box) {
			box->Panic(type);
		}
		void operator () (OutputDevice out) {
			out->Panic(type);
		}
	};

	void  Panic(int type) {
		dopanic_type dopanic(type);

		const InputDeviceList & inlist = InputDeviceClass::GetDeviceList();
		std::for_each(inlist.begin(),inlist.end(),dopanic);

		const BoxListType & boxlist = BoxClass::GetBoxList();
		std::for_each(boxlist.begin(),boxlist.end(),dopanic);

		const OutputDeviceList & outlist = OutputDeviceClass::GetDeviceList();
		std::for_each(outlist.begin(),outlist.end(),dopanic);
	}



	void initialize_box_data()
	{
		mutabor_set_callbacks(& BoxClass::backend_callbacks);
	}

}

/// \}


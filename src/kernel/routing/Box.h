// -*- C++ -*-

/** \file
 ********************************************************************
 * Mutabor Box for C++. Mutabor Core.
 *
 * \author Tobias Schlemmer <keinstein@users.sourceforge.net>
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

/* we guard a little bit complicated to ensure the references are set right
 */

#if (!defined(ROUTING_BOX_H) && !defined(PRECOMPILE)) \
	|| (!defined(ROUTING_BOX_H_PRECOMPILED))
#ifndef PRECOMPILE
#define ROUTING_BOX_H
#endif

// ---------------------------------------------------------------------------
// headers
// ---------------------------------------------------------------------------

#define HIDE_MUTABOR_C_API

#include "src/kernel/Defs.h"
#include "src/kernel/treestorage.h"
//#include "src/kernel/routing/thread.h"
#include "src/kernel/boost-interface.h"
//#include "src/kernel/routing/watchdog.h"
#include "src/kernel/routing/Route.h"
#include "src/kernel/Execute.h"
#include "src/kernel/box.h"
#include "src/kernel/routing/box_support.h"

#ifndef ROUTING_BOX_H_PRECOMPILED
#define ROUTING_BOX_H_PRECOMPILED

// system headers which do seldom change
//#include <boost/intrusive_ptr.hpp>
// we need asprintf
#ifndef _GNU_SOURCE
#define _GNU_SOURCE 1
#endif

#include <vector>
#include <list>
#include <algorithm>
#include <sstream>
#include <stdarg.h>
#include <stdio.h>
#include "boost/format.hpp"


namespace mutaborGUI {
	class BoxData;
}

namespace mutabor {
	template <class T> class watchdog;
	namespace hidden {
		extern "C" {
			// struct mutabor_box_type;
			struct keyboard_ereignis;
			struct midi_ereignis;
			struct harmonie_ereignis;
			typedef struct keyboard_ereignis keyboard_action;
			typedef struct midi_ereignis     midi_action;
			typedef struct harmonie_ereignis harmony_action;
			struct any_trigger;
			struct midiliste;
		}
	}
	using hidden::mutabor_box_type;
	using hidden::keyboard_ereignis;
	using hidden::keyboard_action;
	using hidden::midi_ereignis;
	using hidden::midi_action;
	using hidden::harmonie_ereignis;
	using hidden::harmony_action;
	using hidden::any_trigger;
	using hidden::midiliste;


	using hidden::generic_warning;
	using hidden::compiler_warning;
	using hidden::runtime_warning;
	using hidden::generic_error;
	using hidden::internal_error;
	using hidden::compiler_error;
	using hidden::runtime_error;


        typedef hidden::mutabor_error_type error_type;

        inline const char * to_string(error_type type) {
	    return hidden::mutabor_error_type_to_string(type);
	}


	enum BoxType
	{
		MIN_BOX = -3,
		NewBox = -3,
		NoBox,
		GmnBox,
		Box0 = 0
	};

	class BoxClass;
	typedef boost::intrusive_ptr<BoxClass> Box;
	typedef std::vector<Box> BoxListType;


	class BoxClass
	{
	public:

		enum interval_type_constants {
			invalid_interval = hidden::mutabor_invalid_interval,
			active_interval = hidden::mutabor_active_interval,
			empty_interval = hidden::mutabor_empty_interval,
			invalid_tone = hidden::mutabor_invalid_tone,
			active_tone = hidden::mutabor_active_tone,
			empty_tone = hidden::mutabor_empty_tone
		};
		class tone: public hidden::mutabor_tone {
		public:
			typedef  hidden::mutabor_tone base;

			tone(): base() {
				active = hidden::mutabor_invalid_tone;
				value = 0;
			}
			tone (base t):base(t) {}
			tone (int inkey): base ()
			{
				active = hidden::mutabor_active_tone;
				value = ((mutint64)inkey) << 24;
			}

			bool is_ok() {
				return active != hidden::mutabor_invalid_tone;
			}

			bool is_active() {
				return active == hidden::mutabor_active_tone;
			}

			bool is_empty() {
				return active == hidden::mutabor_empty_tone;
			}

			interval_type_constants get_type() const {
				return (interval_type_constants)
					hidden::mutabor_get_tone_type(*this);
			}

			static constexpr long get_semitone() {
				return 0x1000000;
			}
			static constexpr long get_quartertone() {
				return 0x800000;
			}

			/**
			 * Return the microtonal part of the in fixed
			 * point integer format. This format has been
			 * chosen as some device backends need some
			 * space for additional calculations. On the
			 * other hand the 24 bit provides much room to
			 * avoid rounding errors in the logic.
			 *
			 * \return Microtonal part in fixed point
			 * format with 24 bits after the
			 * comma. I.e. 0x1000000 denotes one pitch.
			 */
			long get_bend() const {
				return value & 0xFFFFFF;
			}
			long get_pitch() const {
				return value >> 24;
			}
			mutint64 get_value () const {
				return value;
			}
			void add_value(mutint64 & retval) const {
				if (active == hidden::mutabor_active_tone) {
					retval += value;
				}
			}

			bool operator == (const tone & t) const {
				return active == t.active && value == t.value;
			}
		};

		typedef tone interval;

		enum  boxidtype {
			IDTypeSession,
			IDTypeFile
		};

		struct ChangedCallback {
			typedef mutabor::hidden::do_aktion action;
			Box box;
			enum ChangedFlags {
				BoxChanged = 1,
				LogicChanged = 2,
				KeysChanged = 4,
				ActionChanged = 8
			};
			ChangedCallback(Box & b):box(b) {
				if (b) b->Register(this);
			}
			~ChangedCallback() {
				if (box)
					box->Unregister(this);
			}
			virtual void SetBox(Box & b) {
				if (b == box) return;
				if (box)
					box->Unregister(this);
				box = b;
				if (box)
					box->Register(this);
			}
			virtual void BoxChangedAction(int flags) = 0;
			virtual void BoxChangedAction(const char * mutUNUSED(action)) {}
		};

		typedef BoxListType listtype;

		virtual ~BoxClass();

		size_t get_session_id() const {
			return session_id;
		}

		virtual BoxType GetType() {
			return routefile_id >= Box0 ? Box0 : (BoxType) routefile_id;
		}

		virtual std::string GetTypeName() {
			switch (GetType()) {
			case NewBox:
				return _mut("New box");
			case NoBox:
				return _mut("No box");
			case GmnBox:
				return _mut("GUIDO Music Notation box");
			case Box0:
				return _mut("Mutabor box");
			}
			return _mut("Unknown box type");
		}

		virtual std::string GetLabel() {
			switch (GetType()) {
			case NewBox:
				return _mut("New box");
			case NoBox:
				return _mut("No box");
			case GmnBox:
				return _mut("GUIDO box");
			case Box0:
				return (boost::format(_mut("Box %d"))
					% get_routefile_id()).str();
			}
			return _mut("Unknown box type");
		}

		bool IsNormal() {
			return routefile_id >= Box0;
		}

		int get_routefile_id() const {
			return routefile_id;
		}

		virtual void set_routefile_id(int id);

		static int GetNextFreeBox() {
			return nextboxid;
		}

		/// Save current device settings in a tree storage
		/** \argument config (tree_storage) storage class, where the data will be saved.
		 */
		virtual void Save (tree_storage & config);

		/// Save route settings (filter settings) for a given route
		/** Some route settings (e.g. filter settings) are device type
		 * specific. This function saves them in a tree storage.
		 * \argument config (tree_storage *) Storage class, where the data will be saved.
		 * \argument route (Route) Route whos data shall be saved.
		 */
		virtual void Save (tree_storage & config,
				   const RouteClass * route);

		/// Load current device settings from a tree storage
		/** \argument config (tree_storage) storage class, where the data will be loaded from.
		 */
		virtual void Load (tree_storage & config);

		/// Load route settings (filter settings) for a given route
		/** Some route settings (e.g. filter settings) are device type
		 * specific. This function loads them from a tree storage.
		 * \argument config (tree_storage *) Storage class, where the data will be restored from.
		 * \argument route (Route) Route whos data shall be loaded.
		 */
		virtual void Load (tree_storage & config,
				   RouteClass * route);


		/// add a route
		virtual void Add(Route & route);
		/// replace a route
		virtual bool Replace(Route & oldRoute, Route & newRoute);
                /// remove a route
		virtual bool Remove(Route & route);
		/// Move routes to another device
		virtual bool MoveRoutes (Box & newclass);


		const routeListType & GetRoutes() const {
			return routes;
		}

		routeListType & GetRoutes() {
			return routes;
		}


		static const listtype & GetBoxList() {
			return boxList ;
		}



		/// Scan the list of Boxes for a given id.
		/** \argument id (int) id to scan for
		 *  \return (Box) pointer to the input device with the given id if found, NULL else.
		 */
		static Box GetBox(int id, boxidtype kind);


		/**
		 * Return the box that is associated with the corrent id. In case such a box does not
		 * exist the box is created
		 *
		 * \param id  Id to be fetched.
		 *
		 * \return Box that has been found or created
		 */
		static Box GetOrCreateBox(int id);

		/**
		 * Move the box in the box list.
		 *
		 * \param count Number of places the box should be
		 * moved up. Negative values indicate downwards
		 * direction.
		 *
		 * \return new position in the box list.
		 */
		virtual	int MoveInList(int count);

		static void ClearBoxList() {
			while (!boxList.empty()) {
#ifdef DEBUG
				Box d = boxList.front();
#endif
				boxList.front()->Destroy();
#ifdef DEBUG
				mutASSERT(boxList.empty() ||
					 d != boxList.front());
#endif
			}
		}

		/**
		 * Disconnect the device from all pairings with routes GUI data or something else.
		 *
		 * This function should be extended in subclasses so
		 * that after calling it only temporary pointers
		 * (variables in functions or temporary objects) point
		 * to the object.
		 */
		virtual void DisconnectFromAll();


		/// reset the device if requested
		virtual void Panic(int type);
		virtual void Panic(Route r, int type);
		virtual void Panic(Route r, int type, size_t unique_id);
		virtual void Reset();

#if 0
#if defined(_MSC_VER)
#pragma warning(push) // Save warning settings.
#pragma warning(disable : 4100) // Disable unreferenced formal parameter warnings
#endif
		virtual void ReadData(wxConfigBase * config) {};
		virtual void WriteData(wxConfigBase * config) {};
#if defined(_MSC_VER)
#pragma warning(pop) // Restore warnings to previous state.
#endif
#endif

		bool Open() {
			try {
				BoxLock lock(this);
				if (!open)
					open = DoOpen();
				return open;
			} catch (boost::lock_error & e) {
				UNREACHABLEC;
				throw;
			}
		}

		void Close() {
			try {
				BoxLock lock(this);
				if (open)
					DoClose();
				open = false;
			} catch (boost::lock_error & e) {
				UNREACHABLEC;
				// try to recover without locking
				if (open)
					DoClose();
				open = false;
				throw;
			}
		}

		virtual bool DoOpen();
		virtual void DoClose();
		bool IsOpen() { return open; }

		/**
		 * Close all boxes.
		 * This function deactivates all boxes.
		 *
		 */
		static void CloseAll();

		/**
		 * Activate all boxes. This resets the action traces of all boxes.
		 * \note Code should be taken from MutFrame::DoActivate
		 *
		 * \param isRealtime Shall non-realtime devices (e.g.,
		 * file devices) act in realtime mode or not
		 *
		 * \retval true if Activation succeeded
		 * \retval false otherwise
		 */
		static bool ActivateAll(bool isRealtime);

		/**
		 * Stop all boxes. This resets the action traces of all boxes.
		 * \note Code should be taken from Stop()
		 */
		static void StopAll();

		struct logic_entry {
			enum { none, Logic, CurrentLogic } flags;
			bool active;
			std::string name;
			std::string startTuning;
			int key;
			struct any_trigger trigger;
		};

		typedef std::list<logic_entry> logic_list;

		/**
		 * Get a list of currently defined logics.
		 * \note: this function replaces GetMutTag() from Runtime.cpp
		 *
		 * \return List of logic descriptions.
		 */
		logic_list GetLogics();

		box_support::tone_system GetToneSystem();


		struct current_tone_entry: public box_support::tone_entry {
			int index;
			size_t id;
			int channel;
			current_tone_entry():box_support::tone_entry(),
					     index(-1),
					     id(0),
					     channel(-7) {}
			current_tone_entry(int ind,
					   double p,
					   size_t i,
					   int c):box_support::tone_entry(p),
						  index(ind),
						  id (i),
						  channel(c) {}
		};

		typedef std::vector<current_tone_entry> current_tone_list;

		current_tone_list GetCurrentTones();

		// this mimics CompDlg
		struct CompileCallback {
			virtual void RefreshDlg() = 0;
			virtual void SetStatus(std::string status) = 0;
			virtual void SetMessage(std::string message) = 0;
			virtual void SetStatus(int logics,
					       int tones,
					       int tunings,
					       int tone_systems,
					       int intervals,
					       int characters) = 0;
			virtual void SetLine(int number) = 0;
		};

		bool Compile(CompileCallback * callback, const char * logic);
		static void compile_callback(mutabor_box_type * b, int line_number);

		void MidiAnalysis(const std::vector<unsigned char > &midiCode) {
			scoped_watchdog lock(this);
			hidden::MidiAnalysis(box, midiCode.data(), midiCode.size());
		}

		void MidiOut(struct midiliste * outliste);
		static void MidiOutCallback(mutabor::hidden::mutabor_box_type * b,
				     struct mutabor::hidden::midiliste * outliste);
		/**
		 * Update the currently playing tones to the current tone system.
		 * \note this function was formerly defined as \c NotesCorrect
		 *
		 */
		void UpdateTones();

		/**
		 * Get the MIDI channel of a given tone
		 *
		 * \param note     Note that has been received
		 * \param channel  Internal unique channel id
		 * \param id       Internal unique Note id
		 *
		 * \return MIDI channel of the note
		 */
		int GetChannel(int key, size_t channel, size_t id);


		void AddNote(int note, size_t id, size_t channel, void * userdata) {
			scoped_watchdog lock(this);
			hidden::AddKey(box, note, id, channel, userdata);
		}

		void DeleteNote(int note, size_t id, int channel) {
			scoped_watchdog lock(this);
			hidden::DeleteKey(box, note, id, channel);
		}

		enum KeyboardFlags {
			KeyboardNoLogic,              // Execute only logics
			KeyboardLogic,                // Execute only tone systems
			KeyboardAny                   // Any possible action
		};

		bool IsLogicKey(int key);

		/**
		 * Execute the action associated with a key that is
		 * pressed on the computer keyboard
		 *
		 * \param key    Key that has been pressed.
		 * \param flags  Flags which type of action should be taken.
		 */
		void KeyboardAnalysis(int key, KeyboardFlags flags) {
			scoped_watchdog lock(this);
			switch (flags) {
			case KeyboardNoLogic:
			case KeyboardLogic:
				hidden::KeyboardAnalyse(box,key,flags == KeyboardLogic);
				break;
			case KeyboardAny:
				hidden::KeyboardAnalyseSimple(box, key);
				break;
			}
		}

		/**
		 * Execute the actions that are associated with the
		 * characters of a string.  \note: The character “&”
		 * denotes that the following character will not be a
		 * logic.
		 *
		 * \param keys
		 */
		void KeyboardAnalysis(const std::string keys) {
			scoped_watchdog lock(this);
			hidden::KeyboardIn(box,keys.c_str());
		}

		tone get_frequency(int note);
		int get_index(int note);
		int get_distance(int note);

		/**
		 * Ignore the watchdog action
		 * this is helpful for debugging.
		 *
		 * \param flag true to forbid interruption by watchdog
		 */
		void make_uninterruptible (bool flag = true) {
			box->flags.uninterruptible = flag;
		}


		/**
		 * Break the execution of any running logic loops.
		 *
		 * \param allow_resume if true allow the next call to
		 * the logic to resume logic execution
		 */
		void interrupt_logic (bool allow_resume = true) {
			if (box && !box->flags.uninterruptible) {
				box->flags.break_logic = 1;
				box->flags.auto_reset_break_logic = allow_resume;
			}
		}

		/**
		 * Allow the execution of logic actions after this
		 * function has been disabled.
		 *
		 */
		void resume_logic () {
			if (box)
				box->flags.auto_reset_break_logic = 1;
		}

		void SetLogic(Box b) {
			hidden::mutabor_set_logic(box,b->box->file);
		}

#if 0
		/// Sets the name of the currently active logic
		/** \param s std::string name of the logic
		*/
		void SetLogicName(const std::string & s) { current_logic = s; }
		/// Returns the name of the currently active logic
		/** \return std::string name of the logic
		 */
		std::string GetLogicName() const { return current_logic; }



		/// Sets the name of the currently active tone system
		/** \param s std::string name of the tone system
		*/
		void SetTonesystem(const std::string & s) { current_tonesystem = s; }
		/// Returns the name of the currently active tone system
		/** \return std::string name of the tone system
		 */
		std::string GetTonesystem() const { return current_tonesystem; }




		/// Sets the key of the currently active tone system
		/** \param nr int number of the key
		*/
		void SetKeyTonesystem(int nr) { current_key_tonesystem = nr; }
		/// Returns the key of the currently active tone system
		/** \return int number of the key
		 */
		int GetKeyTonesystem() const { return current_key_tonesystem; }

		/// Sets the key of the currently active logic
		/** \param nr int number of the key
		*/
		void SetKeyLogic(int nr) { current_key_logic = nr; }
		/// Returns the key of the currently active tone system
		/** \return int key of the tone system
		 */
		int GetKeyLogic() const { return current_key_logic; }
#endif

		/**
		 * Activate the current box.
		 * This method is called when a box is being activated. Its implementation
		 * should be done in the user code. Otherwise its just a no-op function.
		 */
		virtual void Activate () {}

		/**
		 * Destroy the current object.
		 * This function is
		 * called when an object shall be deleted. It clears
		 * up all references to itself so that it will be deleted if it is not needed anymore.
		 *
		 * This functions detatches the device from all routes and calls DoDestroy() afterwards.
		 * Finally the Device is going to removed from the device list.
		 */
		virtual void Destroy();

		/// Initialize the internal device identifiers.
		/** This function sets the internal device ids of
		 *  all output devices, starting from 0 and
		 *  incrementing by 1
		 */
		static void InitializeIds();

		operator std::string() const;

		/// Process an error message (doing the real work)
		virtual void runtime_error(error_type type, const char * message);

		/**
		 * Format and process a runtime error message or warning.
		 *
		 * \param type    error type.
		 * \param format  Format string
		 */
		void issue_error(error_type type, const char * format, ...) {
			char * formatted;
			va_list args;
			bool allocated = true;
			va_start(args,format);
			if (vasprintf(&formatted,format,args) == -1) {
				allocated = false;
				formatted = (char *)_mut("Error in Error: Could not allocate buffer for error message.");
				if (!formatted) {
					formatted =
						(char *) "Error in Error: Could not allocate buffer for error message.";
				}
			}
			va_end(args);
			runtime_error(type,formatted);
			if (allocated)
				free(formatted);
		}

	        /// Return the collected errors and warnings.
		/**
		 * This function is a prototype for potential error message collection in
		 * the GUI part.
		 *
		 * \return a string containing the collected error messages
		 */
		virtual const std::string get_errors() {
			static std::string nothing = "";
			return nothing;
		}
		std::string ActionToString(ChangedCallback::action * action);
		static void log_action(mutabor_box_type * box, const char * action);
		static void UpdateCallback(mutabor_box_type * b, unsigned int flags);
		static void lock_callback(hidden::mutabor_logic_parsed * logic);
		static void unlock_callback(hidden::mutabor_logic_parsed * logic);
		static void free_mutex_callback(hidden::mutabor_logic_parsed * logic);

		void dog_watching() {
			int counter;
			{ // lock the mutex as short as possible.
				ScopedLock<> lock(logic_timing_mutex);
				if (logic_timing >= 0) {
					counter = logic_timing++;
				} else return;
			}

			if (counter > 5) {
				interrupt_logic(true);
				issue_error(hidden::runtime_error,
					      _mut("Timeout while executing logic in box %d."),
					      get_routefile_id());
			} else if (counter == 1) {
				issue_error(hidden::runtime_warning,
					      _mut("The logic in box %d is too slow."),
					      get_routefile_id());
			}
		}

		template<class T>
		void remove_watchdog(T dog) {
			mutUnused(dog);
			mutASSERT(dog == loopguard);
			loopguard = NULL;
		}

	protected:
		struct BoxLock: public ScopedLock<> {
			Box box;
			BoxLock(BoxClass * b):ScopedLock(b->mutex),
					      box(b) {
				if (b && b->box && b->box->flags.auto_reset_break_logic)
					b->box->flags.break_logic = 0;
			}
			~BoxLock() {
				box->UpdateTones();
				box->ExecuteCallbacks(box->updateflags);
			}
		};

		struct scoped_watchdog: public BoxLock {
			scoped_watchdog(BoxClass * b):BoxLock(b) {
				ScopedLock(box->logic_timing_mutex);
				box->logic_timing = 0;
			}
			~scoped_watchdog() {
				try {
					ScopedLock(box->logic_timing_mutex);
					box->logic_timing = -1;
				} catch (const boost::lock_error & e) {
					box->logic_timing = -1; // danger!
					box->issue_error(::mutabor::error::runtime_error,
							 _mut("Internal Error:\nPlease, send the following information to the developers:\n:%d:%s:~scoped_watchdog()\n%s"),
							 __FILE__,
							 __LINE__,
							 boost::diagnostic_information(e).c_str());
				}
			}
		};
	        static listtype boxList;
		static int nextboxid;
		friend class ::mutaborGUI::BoxData;
		friend class BoxFactory;
		friend void initialize_box_data();
		mutabor_box_type * box;
		idtype<BoxClass> session_id;
		int routefile_id;
		routeListType routes;
		bool open ;
		bool compile_error;
		std::string current_logic;
		std::string current_tonesystem;
		int current_key_tonesystem; // 0
		int current_key_logic; // 1
		unsigned int updateflags;
		std::list<ChangedCallback *> callbacks;
		class set_callback {
			BoxClass * box;
		public:
			set_callback(BoxClass * b,
				     CompileCallback * callback):box(b) {
				box->current_compile_callback = callback;
			}
			~set_callback() {
				box->current_compile_callback = NULL;
			}
		};
		CompileCallback * current_compile_callback;
		static mutabor::hidden::mutabor_callback_type backend_callbacks;
		Mutex<> mutex;
		int logic_timing;
		Mutex<> logic_timing_mutex;
		mutint64 loop_timeout;
		watchdog<Box> * loopguard;

		BoxClass(int id = -1);

		void Register(ChangedCallback * callback) {
			callbacks.push_back(callback);
		}
		void Unregister(ChangedCallback * callback) {
			callbacks.remove(callback);
		}

		void ExecuteCallbacks(unsigned int flags);
		void ExecuteCallbacks(const char * action);



		static void AppendToBoxList (Box dev);
		static void RemoveFromBoxList (Box  dev);
		static typename listtype::iterator FindInBoxList (Box b) {
			typename listtype::iterator i =
				std::find(boxList.begin(),
					  boxList.end(),
					  b);
			return i;
		}
		static bool IsInBoxList (const Box b) {
			return FindInBoxList(b) != boxList.end();
		}
		static void TruncateBoxList (Box dev);




	private:
		REFPTR_INTERFACE;
	};



	class BoxFactory {
	public:
		struct BoxNotCreated:public std::exception {};
		struct FactoryNotFound:public std::exception {
			int id;
			std::string message_;
			FactoryNotFound(int i):std::exception(), id(i) {
				std::ostringstream writer(message_);
				writer << "Factory for box type " << i << " has not been registered.";
				message_ = writer.str();
			}

			virtual ~FactoryNotFound() throw () {}

			//! Returns the thrown error message as a c-style string.
			virtual const char* what( void ) const throw() { return message_.c_str(); }

		};

		BoxFactory(size_t id = 0);
		virtual ~BoxFactory();

		static Box Create(int type, int id = NewBox) {
			if (id == NewBox && type != Box0) {
				id = type;
			}

			if (type < 0) type = 0;
			mutASSERT(type >= 0);
			if (factories.size() <=(size_t) type) {
				BOOST_THROW_EXCEPTION(FactoryNotFound(type));
				UNREACHABLECT(BoxFactory);
				return NULL;
			}
			if (!factories[type])
				BOOST_THROW_EXCEPTION(FactoryNotFound(type));
			return factories[type]->DoCreateBox(id);
		}

		static void Destroy() {
			if (!factories.empty()) {
				for (factorylist::iterator i = factories.begin();
				     i != factories.end(); i++) {
				        BoxFactory * factory = *i;
					if (factory)
						delete factory;
				}
				factories.clear();
			} else
				UNREACHABLECT(BoxFactory);
		}


		/// load the routes from a tree based configuration
		/** \param config conifiguration to be read from
		 */
		static void LoadBoxes(tree_storage & config);

		/// write the routes to the configuration
		/** \param config configuration to be written to
		 */
		static void SaveBoxes(tree_storage & config);


	protected:
		struct factorylist:public std::vector<BoxFactory *> {
			typedef std::vector<BoxFactory *> base;
			factorylist():base() {}
			~factorylist() {
				for (base::iterator i = begin();
				     i != end ();
				     i++) {
					if (*i) {
						delete (*i);
						*i = 0;
					}
				}
			}
		};
		static factorylist factories;

		virtual size_t GetType() const { return Box0; };

		virtual BoxClass * DoCreateBox (int id = -1) const;

		/// load the routes from a tree based configuration
		/** \param config conifiguration to be read from
		 */
		virtual void DoLoadBoxes(tree_storage & config) const;

		/// write the routes to the configuration
		/** \param config configuration to be written to
		 */
		virtual void DoSaveBoxes(tree_storage & config) const;
	};

	//	void InitBoxFactories();

	class ScopedBox: public Box {
	public:
		~ScopedBox() {
			if (get())
				get()->Destroy();
		}

		ScopedBox(BoxClass * rhs):Box(rhs) {}
		ScopedBox(const Box & rhs):Box(rhs) {}

		ScopedBox & operator = (BoxClass * rhs) {
			(*(static_cast<Box *>(this))) = rhs;
			return *this;
		}
		ScopedBox & operator = (const Box & rhs) {
			(*(static_cast<Box *>(this))) = rhs;
			return *this;
		}
	};


	inline Box BoxClass::GetOrCreateBox(int id) {
		Box b = GetBox(id,IDTypeFile);
		if (b) return b;
		else if (id > Box0)
			return BoxFactory::Create(Box0,id);
		else return BoxFactory::Create(id);
	}

	void  Panic(int type);

	inline void BoxClose()
	{
		const BoxListType& list = BoxClass::GetBoxList();
		for (BoxListType::const_iterator b = list.begin();
		     b != list.end(); b++)
			(*b)->Close();
	}

	enum {
		OpenAllBoxes      = 0x01,
		OpenAllOutDevices = 0x02,
		OpenAllInDevices  = 0x04
	};

	bool OpenAll(int mode);
	void initialize_box_data();
}

#endif /* precompiled */
#endif

/*
 * \}
 */

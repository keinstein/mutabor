/** \file   -*- C++ -*-
 ***********************************************************************
 * Input device selection dialog.
 *
 * Copyright:   (c) R. Krauße, TU Dresden,
 *              2013 Tobias Schlemmer
 * \author R. Krauße,
 *         Tobias Schlemmer <keinstein@users.sourceforge.net>
 * \license: GPL
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
 *\addtogroup GUIroute
 *\{
 ********************************************************************/

/* we guard a little bit complicated to ensure the references are set right
 */

#if (!defined(MUWX_ROUTING_OUTPUTDEVDLG_H) && !defined(PRECOMPILE)) \
	|| (!defined(MUWX_ROUTING_OUTPUTDEVDLG_H_PRECOMPILED))
#ifndef PRECOMPILE
#define MUWX_ROUTING_OUTPUTDEVDLG_H
#endif

// ---------------------------------------------------------------------------
// headers
// ---------------------------------------------------------------------------

#include "src/kernel/Defs.h"
#include "src/wxGUI/resourceload.h"
#include "src/kernel/routing/Device.h"
#include "src/kernel/routing/midi/DevMidi.h"

#ifndef MUWX_ROUTING_OUTPUTDEVDLG_H_PRECOMPILED
#define MUWX_ROUTING_OUTPUTDEVDLG_H_PRECOMPILED

// system headers which do seldom change

/*!
 * Includes
 */

#include "wx/xrc/xmlres.h"
#include "wx/html/htmlwin.h"
#include "wx/statline.h"
#include "wx/filepicker.h"
#include "wx/valgen.h"
#include "wx/valtext.h"

namespace mutaborGUI {

        class OutputDevDlg: public OutputDevDlgBase
	{
		DECLARE_DYNAMIC_CLASS( OutputDevDlg )
		DECLARE_EVENT_TABLE()

			protected:
			wxSizer *Container,* TypeBox, *PortBox, *MidiFileBox, *GuidoFileBox;

		struct TypeData:wxClientData
		{
			mutabor::DevType nr;
                        TypeData(mutabor::DevType i):wxClientData(),
						     nr(i)
			{
                        }

			virtual ~TypeData() {}

			bool operator == (mutabor::DevType i)
			{
				return i == nr;
			}

			operator mutabor::DevType()
			{
				return nr;
			}
		};

		struct PortData:wxClientData
		{
                        rtmidi::PortPointer port;
                        PortData(rtmidi::PortPointer &p):wxClientData(),
							 port(p)
			{
				DEBUGLOG(routinggui,"Creating Port data");
                        }

			virtual ~PortData() {
				DEBUGLOG(routinggui,"Deleting PortData");
			}

			bool operator == (rtmidi::PortPointer p)
			{
                                 return port == p;
                        }

			operator rtmidi::PortPointer()
			{
                                return port;
                        }
		};

		int FindType (mutabor::DevType t);

	public:
		/// Constructors
		OutputDevDlg( wxWindow* parent = NULL);

		/// Destructor
		virtual ~OutputDevDlg() {}

		/// wxEVT_COMMAND_CHOICE_SELECTED event handler for ID_CHOICE
		void OnChoiceSelected( wxCommandEvent& event );

		/// wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_BUTTON
		void OnRemoveClick( wxCommandEvent& event );

		void OnFileChanged ( wxFileDirPickerEvent & event );

		void UpdateLayout(mutabor::DevType type);

		void SelectMidiDevice (int n) {
			PortChoice->SetSelection(n);
		}

                void SetMidiDevice(const rtmidi::PortPointer &value)

		{
			DEBUGLOG (other, "%p" ,&(*value));
			int choices = PortChoice->GetCount();
			for (int i = 0 ; i < choices ; i++) {
				PortData * entry = static_cast<PortData *>(PortChoice->GetClientObject(i));
				if (entry && entry->port == value) {
					PortChoice->SetSelection(i);
					break;
				}
			}
			Update();
		}

		rtmidi::PortPointer GetMidiDevice(int p) const {
			mutASSERT (dynamic_cast<PortData *>(PortChoice->GetClientObject(p)));
			PortData * obj = static_cast<PortData *>(PortChoice->GetClientObject(p));

			if (obj) return  *obj;
			else return NULL;
		}

		rtmidi::PortPointer GetMidiDevice() const
		{
			int p = PortChoice->GetSelection();
			if (p == wxNOT_FOUND) return NULL;
			return GetMidiDevice(p);

		}

		void AppendPortChoice (rtmidi::PortPointer &p)
		{
			PortChoice->Append (p->getName(),
					    new PortData(p));
		}
		void AppendPortChoiceNoDevice()
		{
			PortChoice->Append(_("no device"));
		}



		wxString GetMidiFile() const
			{
				return MidiFilePicker->GetPath() ;
			}

		void SetMidiFile(wxString value) {
			DEBUGLOG(other, (const char *)value.ToUTF8());
			MidiFilePicker->SetPath(value);
			InvalidateBestSize();
			SetInitialSize(wxDefaultSize);
			Update();
			DEBUGLOG (other, "done" );
		}

		wxString GetGUIDOFile() const
			{
				return GuidoFilePicker->GetPath() ;
			}

		void SetGUIDOFile(wxString value)

			{
				DEBUGLOG(other, (const char *) value.ToUTF8());
				GuidoFilePicker->SetPath(value);
				Update();
			}

		mutabor::DevType GetType() const
			{
				int Type = DeviceChoice->GetSelection();
				if (Type == wxNOT_FOUND) return mutabor::DTNotSet;

				mutASSERT (dynamic_cast<TypeData *>(DeviceChoice->GetClientObject(Type)));
				TypeData * obj = (TypeData *)DeviceChoice->GetClientObject(Type);

				if (obj) return  *obj;
				else return mutabor::DTNotSet;
			}

		void SetType(mutabor::DevType value)

			{
				DEBUGLOG (other, "%d" ,value);
				UpdateLayout(value);
				Update();
			}

		long GetMidiBendingRange() {
			return MidiBendingRange->GetValue();
		}

		void SetMidiBendingRange (long i) {
			MidiBendingRange->SetValue (i);
		}

		long GetMidiFileBendingRange() {
			return MidiFileBendingRange->GetValue();
		}

		void SetMidiFileBendingRange (long i) {
			MidiFileBendingRange->SetValue (i);
		}

		/// Retrieves bitmap resources
		wxBitmap GetBitmapResource (const wxString& name );

		/// Retrieves icon resources
		wxIcon GetIconResource (const wxString& name );

		/// Should we show tooltips?
		static bool ShowToolTips ();
	};
}
#endif
// _OUTPUTDEVDLG_H_PRECOMPILED
#endif
// _OUTPUTDEVDLG_H_

/*
 * \}
 */

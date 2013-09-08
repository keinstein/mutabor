/** \file               -*- C++ -*-
 ********************************************************************
 * Test BoxClass
 *
 * Copyright:   (c) 2013 Tobias Schlemmer
 * \author  Tobias Schlemmer <keinstein@users.berlios.de>
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
 * \addtogroup kernel
 * \{
 ********************************************************************/

#include "src/kernel/box.h"
#include "src/kernel/routing/tests/BoxTest.h"
#include "src/wxGUI/generic/muconvauto.h"
#include "wx/ffile.h"
#include <stdarg.h>
/// not for headers
#ifdef __BORLANDC__
    #pragma hdrstop
#endif



extern "C" {
    static void error_callback(mutabor::hidden::mutabor_box_type * b, mutabor::error_type type,
			   const char * message) {
	mutabor::BoxClass * box = (mutabor::BoxClass *)b -> userdata;
	box->runtime_error(type,message);
	//	CPPUNIT_ASSERT(iswarning);
	CPPUNIT_FAIL("Syntax errors and warnings should not be issued during these kinds of tests!");
}
}

static void lock_callback(typename mutabor::hidden::mutabor_logic_parsed * logic) {
	std::cerr << "warning: logic locking is not implemented" << std::endl;
}

static void unlock_callback(mutabor::hidden::mutabor_logic_parsed * logic) {
	std::cerr << "warning: logic unlocking is not implemented" << std::endl;
}


struct mutabor::hidden::mutabor_callback_type test_backend_callbacks  = {
	mutabor::BoxClass::UpdateCallback,
	mutabor::BoxClass::MidiOutCallback,
	error_callback,
	mutabor::BoxClass::compile_callback,
	mutabor::BoxClass::log_action,
	lock_callback,
	unlock_callback
};



struct MyCompileCallback:public mutabor::BoxClass::CompileCallback {
	void Refresh() {}
	void SetStatus(mutString status) {
		DEBUGLOG(kernel_parser,_T("INFO: %s"), (const wxChar *)status);
	}
	void SetMessage(mutString status) {
		DEBUGLOG(kernel_parser,_T("INFO: %s"), (const wxChar *)status);
	}
	void SetStatus(int logics, 
		       int tones, 
		       int tunings,
		       int tone_systems,
		       int intervals,
		       int characters) {}
	void SetLine(int number) {}
};

const mutChar * logic_file_names [] = {
	_T("/Examples/german/Cdur.mut"),
	_T("/Examples/german/Instr.mut"),
	_T("/Examples/german/Demo-utf8.mut"),
	_T("/Examples/german/Extern.mut"),
	_T("/Examples/german/Demos.mut"),
	_T("/Examples/german/Demo.mut"),
	_T("/Examples/german/Nix.mut"),
	_T("/Examples/german/Cohen.mut"),
	_T("/Examples/german/Midi.mut"),
	_T("/Examples/english/extern.mut"),
	_T("/Examples/english/instr.mut"),
	_T("/Examples/english/cdur.mut"),
	_T("/Examples/english/nix.mut"),
	_T("/Examples/english/demo.mut"),
	_T("/Examples/english/demos.mut"),
	_T("/Examples/english/cohen.mut"),
	_T("/Examples/english/midi.mut"),
	_T("/Examples/english/tutorial.mut"),
	NULL
};

static muConvAuto autoConverter;


void BoxTest::setUp() 
{ 
	// change DEBUGA to DEBUG in case you need the debug output
#ifdef DEBUGA
	//		debugFlags::flags.timer = true;
	//		debugFlags::flags.midifile = true;
#endif
	//		RealTime = true;
	mutabor_set_callbacks(& test_backend_callbacks);
}
  
void BoxTest::tearDown()
{ 
#ifdef DEBUG
	//		debugFlags::flags.timer = false;
	//		debugFlags::flags.midifile = false;
#endif
	//		in = NULL;
}
  

void BoxTest::testParser() {
	MyCompileCallback callback;
	mutabor::Box Box0 = mutabor::BoxFactory::Create(mutabor::Box0,mutabor::BoxClass::GetNextFreeBox());
	char * logic_string;
	CPPUNIT_ASSERT(Box0->Compile(&callback, ""));

	for (size_t i = 0 ; logic_file_names[i] ; i++ ) {
		wxString name = top_srcdir;
		name += logic_file_names[i];

		std::cerr << name.ToUTF8() << std::endl;
		wxFile file(name);
		CPPUNIT_ASSERT(file.IsOpened());
		wxFileOffset length = file.Length();
		logic_string = (char *) malloc(length+1);
		CPPUNIT_ASSERT(file.Read(logic_string, length) == length);
		logic_string[length] = 0;
		CPPUNIT_ASSERT(Box0->Compile(&callback, logic_string));
		free(logic_string);
		logic_string = NULL;
	}
}

void BoxTest::testCopyPLay() {
	MyCompileCallback callback;
	mutabor::Box Box0 = mutabor::BoxFactory::Create(mutabor::Box0,mutabor::BoxClass::GetNextFreeBox());
	mutabor::Box Box1 = mutabor::BoxFactory::Create(mutabor::Box0,mutabor::BoxClass::GetNextFreeBox());
	mutabor::Box Box2 = mutabor::BoxFactory::Create(mutabor::Box0,mutabor::BoxClass::GetNextFreeBox());
	char * logic_string;


	wxString name = top_srcdir;
	name += _T("/src/kernel/tests/all.mut");
	
	wxFile file(name);
	CPPUNIT_ASSERT(file.IsOpened());
	wxFileOffset length = file.Length();
	logic_string = (char *) malloc(length+1);
	CPPUNIT_ASSERT(file.Read(logic_string, length) == length);
	logic_string[length] = 0;

	CPPUNIT_ASSERT(Box0->Compile(&callback, logic_string));
	free(logic_string);
	logic_string = NULL;

	Box1->SetLogic(Box0);
	Box0->Destroy();
	Box0 = NULL;
	Box2->SetLogic(Box1);
	Box2->Destroy();
	Box2 = NULL;
	
	Box1->KeyboardAnalysis(_T("&N")); // activate the Tonnetz
	
	Box1->AddNote(60,0,0,NULL);
	Box1->AddNote(64,0,0,NULL);
	Box1->AddNote(67,0,0,NULL);
	Box1->DeleteNote(67,0,0);
	Box1->AddNote(69,0,0,NULL);
	Box1->DeleteNote(64,0,0);
	Box1->AddNote(65,0,0,NULL);

	/* do some more sophisticated test */
	
	Box1->DeleteNote(60,0,0);
	Box1->DeleteNote(65,0,0);
	Box1->DeleteNote(69,0,0);
}


///\}

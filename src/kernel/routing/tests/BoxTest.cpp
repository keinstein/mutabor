/** \file               -*- C++ -*-
 ********************************************************************
 * Test BoxClass
 *
 * Copyright:   (c) 2013 Tobias Schlemmer
 * \author  Tobias Schlemmer <keinstein@users.sourceforge.net>
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
 * \addtogroup tests
 * \{
 ********************************************************************/

#include "src/kernel/box.h"
#include "src/kernel/routing/tests/BoxTest.h"
#include <stdarg.h>
/// not for headers
#ifdef __BORLANDC__
    #pragma hdrstop
#endif

extern const char * top_srcdir;


extern "C" {
    static void error_callback(mutabor::hidden::mutabor_box_type * b, mutabor::error_type type,
			   const char * message) {
	mutabor::BoxClass * box = (mutabor::BoxClass *)b -> userdata;
	box->runtime_error(type,message);
	//	CPPUNIT_ASSERT(iswarning);
	CPPUNIT_FAIL("Syntax errors and warnings should not be issued during these kinds of tests!");
}
}



struct mutabor::hidden::mutabor_callback_type test_backend_callbacks  = {
	mutabor::BoxClass::UpdateCallback,
	mutabor::BoxClass::MidiOutCallback,
	error_callback,
	mutabor::BoxClass::compile_callback,
	mutabor::BoxClass::log_action,
	mutabor::BoxClass::lock_callback,
	mutabor::BoxClass::unlock_callback,
	mutabor::BoxClass::free_mutex_callback
};



struct MyCompileCallback:public mutabor::BoxClass::CompileCallback {
	void RefreshDlg() {}
	void SetStatus(std::string status) {
		mutUnused(status);
		DEBUGLOG(kernel_parser,("INFO: %s"), status);
	}
	void SetMessage(std::string status) {
		mutUnused(status);
		DEBUGLOG(kernel_parser,("INFO: %s"), status);
	}
	void SetStatus(int logics, 
		       int tones, 
		       int tunings,
		       int tone_systems,
		       int intervals,
		       int characters) {
		mutUnused(logics);
		mutUnused(tones);
		mutUnused(tunings);
		mutUnused(tone_systems);
		mutUnused(intervals);
		mutUnused(characters);
	}
	void SetLine(int number) { mutUnused(number); }
};

const char * logic_file_names [] = {
	("/Examples/german/Cdur.mut"),
	("/Examples/german/Instr.mut"),
	("/Examples/german/Demo-utf8.mut"),
	("/Examples/german/Extern.mut"),
	("/Examples/german/Demos.mut"),
	("/Examples/german/Demo.mut"),
	("/Examples/german/Nix.mut"),
	("/Examples/german/Cohen.mut"),
	("/Examples/german/Midi.mut"),
	("/Examples/english/extern.mut"),
	("/Examples/english/instr.mut"),
	("/Examples/english/cdur.mut"),
	("/Examples/english/nix.mut"),
	("/Examples/english/demo.mut"),
	("/Examples/english/demos.mut"),
	("/Examples/english/cohen.mut"),
	("/Examples/english/midi.mut"),
	("/Examples/english/tutorial.mut"),
	NULL
};

//static muConvAuto autoConverter;


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
	mutabor::ScopedBox Box0 = mutabor::BoxFactory::Create(mutabor::Box0,mutabor::BoxClass::GetNextFreeBox());
	char * logic_string;
	CPPUNIT_ASSERT(Box0->Compile(&callback, ""));

	for (size_t i = 0 ; logic_file_names[i] ; i++ ) {
		std::string name = top_srcdir;
		name += logic_file_names[i];

		std::cerr << name.c_str() << std::endl;
		std::ifstream file(name.c_str());
		CPPUNIT_ASSERT(file.is_open());
		file.seekg(0, std::ios::end);
		std::streampos length = file.tellg();
		file.seekg(0, std::ios::beg);
		logic_string = (char *) malloc((size_t)length+1);
		CPPUNIT_ASSERT(file.read(logic_string, length).gcount() == length);
		logic_string[length] = 0;
		CPPUNIT_ASSERT(Box0->Compile(&callback, logic_string));
		free(logic_string);
		logic_string = NULL;
	}
}

void BoxTest::testCopyPLay() {
	MyCompileCallback callback;
	mutabor::ScopedBox Box0 = mutabor::BoxFactory::Create(mutabor::Box0,mutabor::BoxClass::GetNextFreeBox());
	mutabor::ScopedBox Box1 = mutabor::BoxFactory::Create(mutabor::Box0,mutabor::BoxClass::GetNextFreeBox());
	mutabor::ScopedBox Box2 = mutabor::BoxFactory::Create(mutabor::Box0,mutabor::BoxClass::GetNextFreeBox());
	char * logic_string;


	std::string name = top_srcdir;
	name += ("/src/kernel/tests/all.mut");
	
	std::ifstream file(name.c_str());
	CPPUNIT_ASSERT(file.is_open());
	file.seekg(0, std::ios::end);
	std::streampos length = file.tellg();
	file.seekg(0, std::ios::beg);
	logic_string = (char *) malloc((size_t)length+1);
	CPPUNIT_ASSERT(file.read(logic_string, length).gcount() == length);
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
	
	Box1->KeyboardAnalysis(("&N")); // activate the Tonnetz
	
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

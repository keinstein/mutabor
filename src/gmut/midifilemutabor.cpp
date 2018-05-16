// Copyright Vladimir Prus 2002-2004.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

/* The simplest usage of the library.
 */

#include <boost/program_options.hpp>
#include "boost/locale.hpp"
#include "boost/filesystem.hpp"
#include "boost/filesystem/fstream.hpp"
namespace po = boost::program_options;
namespace fs = boost::filesystem;

#include "src/kernel/Defs.h"
#include "src/kernel/routing/midi/DevMidF.h"
#include "src/kernel/routing/Route.h"
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

#include "src/kernel/routing/Route-inlines.h"

using namespace std;

namespace mutaborGUI {
	void DebugCheckRoutes() {
	}
}

#define STR_too_many_positional_options_error				\
	_mut("too many positional options have been specified on the command line")
#define STR_reading_file					\
	_mut("can not read options configuration file '%s'")
#define STR_multiple_values						\
	/* xgettext:no-c-format */					\
	_mut("option '%canonical_option%' only takes a single argument")
#define STR_multiple_occurrences					\
	/* xgettext:no-c-format */					\
	_mut("option '%canonical_option%' cannot be specified more than once")
#define STR_required_option						\
	/* xgettext:no-c-format */					\
	_mut("the option '%canonical_option%' is required but missing")
#define STR_unknown_option					\
	/* xgettext:no-c-format */				\
	_mut("unrecognised option '%canonical_option%'")
#define STR_ambiguous_option					\
	/* xgettext:no-c-format */				\
	_mut("option '%canonical_option%' is ambiguous")

#define mut_catch_exception(ex)						\
	catch (po::ex & e) {						\
		e.m_error_template = STR_ ## ex;			\
		cerr << boost::format(_mut("Error: %s")) % e.what()	\
		     << std::endl					\
		     << std::endl;					\
		do_help(desc,*av);					\
		return 1;						\
	}

/* global variables that may be filled by the command line */
std::string outputfile;
std::string inputfile;
std::string logicfile;
std::string startkeys;

void do_help(po::options_description & desc, const char * name)
{
	cout << (boost::format(_mut("Synopsis: %s [options]  input-file[.mid] [output-file[.mid] [logic-file[.mut]]] [start-keys]"))
		 % name) << endl << endl;
	cout << desc << "\n";
}


std::ostream & operator << (std::ostream & o,
			    const std::vector < std::string >  & v) {
	if (v.empty()) return o;
	std::vector<std::string>::const_iterator i = v.begin();
	o << *i;
	while (++i != v.end()) {
		o << ", " << *i;
	}
	return o;
}

mutabor::InputDevice inguard;
mutabor::InputMidiFile * in;
mutabor::OutputDevice outguard;
mutabor::OutputMidiFile * out;
mutabor::Route  route;
mutabor::Box box;
mutabor::ChannelData cd;

#if __WXMSW__
void usleep(int waitTime) {
	__int64 time1 = 0, time2 = 0, freq = 0;

	QueryPerformanceCounter((LARGE_INTEGER *) &time1);
	QueryPerformanceFrequency((LARGE_INTEGER *)&freq);

	do {
		QueryPerformanceCounter((LARGE_INTEGER *) &time2);
	} while((time2-time1) < waitTime);
}

void sleep(int waitTime) {
	usleep(waitTime * 1000);
}
#endif

struct MyCompileCallback:public mutabor::BoxClass::CompileCallback {
	void RefreshDlg() {}
	void SetStatus(std::string status) {
		mutUnused(status);
		std::cout << status << std::endl;
	}
	void SetMessage(std::string status) {
		mutUnused(status);
		std::cerr << status << std::endl;
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
	void SetLine(int number) {
		mutUnused(number);
	}
};

void add_options(po::options_description & desc,
		 po::positional_options_description & p,
		 po::variables_map vm) {
	mutUnused(vm);
		desc.add_options()
			("help", _mut("produce this help message"))
			("input-file,i", po::value<std::string>(&inputfile),
			 _mut("Input MIDI file"))
			("output-file,o",
			 po::value<std::string>(&outputfile),
			 _mut("Output MIDI file"))
			("logic-file,l",
			 po::value<std::string>(&logicfile),
			 _mut("Mutabor Logic file"))
			("start-keys,k",
			 po::value<std::string>(&startkeys),
			 _mut("Execute the given keys before starting the MIDI playback"))
#ifdef DEBUG
#define N_
#define DEBUGFLAG(flag,description) \
			("debug-"#flag, po::bool_switch()->implicit_value(true)->notifier(::mutabor::debugFlags::set ## flag()), _mut(description))
#include "src/kernel/debugFlags.h"
#undef DEBUGFLAG
#endif
			;

		p.add("input-file", 1).add("output-file",1).add("logic-file",1).add("start-keys",1);
}



int main(int ac, char* av[])
{
	try {
		mutabor::InitDeviceFactories();

		boost::locale::generator gen;
		gen.add_messages_path(LOCALEDIR);
		gen.add_messages_domain("mutabor");
		locale::global(gen(""));
		po::options_description desc(_mut("Allowed options"));
		po::positional_options_description p;
		po::variables_map vm;

		add_options(desc,p,vm);


		try {
			po::store(po::command_line_parser(ac, av).
				  options(desc).positional(p).run(), vm);
			po::notify(vm);
		}
		catch (po::too_many_positional_options_error & e) {
			cerr << STR_too_many_positional_options_error
			     << std::endl
			     << std::endl;
			do_help(desc,*av);
			return 1;
		}
		mut_catch_exception(multiple_values)
		mut_catch_exception(multiple_occurrences)
		mut_catch_exception(required_option)
		mut_catch_exception(unknown_option)
		mut_catch_exception(ambiguous_option)
		catch(exception& e) {
			cerr << "error: " << e.what() << "\n";
			do_help(desc,*av);
			return 1;
		}

		route = mutabor::RouteFactory::Create();
		box = mutabor::BoxFactory::Create(mutabor::Box0,0);
		connect(route, box);

		mutabor::CurrentTime.UseRealtime(false);
		outguard =mutabor::DeviceFactory::CreateOutput(mutabor::DTMidiFile);
		out = static_cast<mutabor::OutputMidiFile *>(outguard.get());
		out->SetBendingRange(2);
		//out = new midicmnOutputDevice(3,("Test"));

		connect(route, outguard);
		route->SetOutputFrom (0);
		route->SetOutputTo (15);
		route->OutputAvoidDrumChannel (true);



		inguard = (mutabor::DeviceFactory::CreateInput(mutabor::DTMidiFile));
		in = static_cast<mutabor::InputMidiFile *> (inguard.get());

		connect(route, inguard);


		if (vm.count("help")) {
			do_help(desc,*av);
			return 0;
		}

		if (inputfile.empty() || outputfile.empty()) {
			do_help(desc,*av);
			return 1;
		}
		in -> SetName(inputfile);
		out -> SetName(outputfile);

		errno = 0;
		std::ifstream file(logicfile.c_str());
		if (!file.is_open()) {
			cerr << boost::format(_mut("Error: Could not open logic file `%s'.")) % logicfile
			     << std::endl;
			cerr << strerror(errno) << std::endl;
			return 1;
		}
		file.seekg(0, std::ios::end);
		std::streampos length = file.tellg();
		file.seekg(0, std::ios::beg);
		char * logic_string = (char *) malloc((size_t)length+1);
		if (!(file.read(logic_string, length).gcount() == length)) {
			cerr << boost::format(_mut("Error: Could not read logic file `%s'.")) % logicfile
			     << std::endl;
			cerr << strerror(errno) << std::endl;
			return 1;
		}
		logic_string[length] = 0;

		MyCompileCallback callback;
		if (!box->Compile(&callback, logic_string)) {
			cerr << boost::format(_mut("Error: Could not compile logic file `%s'.")) % logicfile
			     << std::endl;
			return 1;
		}

		free(logic_string);
		logic_string = NULL;

		route->SetActive(true);

		box -> Open();

		box -> KeyboardAnalysis(startkeys);
		mutabor::InputDeviceClass::BatchPlay();

		in -> Close();
		box -> Close();
		out -> Close();

		if (out)
			out -> Destroy();
		out = NULL;
		outguard.reset();
		route -> Destroy();
		route.reset();
		box -> Destroy();
		box.reset();
		in -> Destroy();
		in = NULL;
		inguard.reset();
	}
	catch(exception& e) {
		cerr << "error: " << e.what() << "\n";
		return 1;
	}
	catch(...) {
		cerr << "Exception of unknown type!\n";
	}


	return 0;
}

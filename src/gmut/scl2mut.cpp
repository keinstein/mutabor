// Copyright Vladimir Prus 2002-2004.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

/* The simplest usage of the library.
 */

#include "src/kernel/routing/thread.h"
/* avoid circular dependency problems
boost/program_options.hpp
 -> boost/lexical_cast.hpp
 -> libintl.h
 -> debug.h
 -> thread.h
 -> boost/lexical_cast.hpp
*/
#include <boost/program_options.hpp>
#include "boost/locale.hpp"
#include "boost/filesystem.hpp"
#include "boost/filesystem/fstream.hpp"
namespace po = boost::program_options;
namespace fs = boost::filesystem;

#include "src/kernel/Defs.h"
#include "src/kernel/parsers/scala/scala.h"
#include <iostream>
#include <iterator>
#include <string>
#include <vector>
using namespace std;

#ifdef DEBUG
// avoid linker errors in this single threaded application
extern "C" {
	void mutabor_debug_lock() {}
	void mutabor_debug_unlock() {}
}
namespace mutabor {
	extern "C" {

		struct mutabor_debug_flagtype mutabor_debug_flags;
		debugFlags debugFlagInitialiser;

		mutabor::debugFlags::debugFlags()
		{
#define DEBUGFLAG(flag,description)					\
			mutabor::mutabor_debug_flags.flag = false;
#include "src/kernel/debugFlags.h"
#undef DEBUGFLAG
			mutabor::mutabor_debug_flags.always = true;
			// manual overrides for debug purposes
			//	flags.smartptr = true;
		}

	}
	Mutex<> debugmutex;
}

#endif


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
std::string kbmfile;
mutabor::scala_parser::mutabor_writer_options options;

ostream * output = NULL;
istream * input = NULL, *keymapinput = NULL;



void do_help(po::options_description & desc, const char * name)
{
	cout << (boost::format(_mut("Synopsis: %s [options]  input-file[.scl] [output-file[.mut]]"))
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

void run() {
	std::string s;

	input->seekg(0, std::ios::end);
	streampos pos = input->tellg();
	if (pos > 0)
		s.reserve(pos);
	input->seekg(0, std::ios::beg);

	s.assign((std::istreambuf_iterator<char>(*input)),
		   std::istreambuf_iterator<char>());

	mutabor::scala_parser::parser scparser(s,inputfile);
	if (keymapinput) {
		s.clear();
		keymapinput->seekg(0, std::ios::end);
		streampos pos = keymapinput->tellg();
		if (pos > 0)
			s.reserve(pos);
		keymapinput->seekg(0, std::ios::beg);

		s.assign((std::istreambuf_iterator<char>(*keymapinput)),
			 std::istreambuf_iterator<char>());
		scparser.load_keymap(s,kbmfile);
	} else {
		scparser.make_keymap();
	}

	scparser.write_mutabor(*output,options);
}
int main(int ac, char* av[])
{
	try {
		boost::locale::generator gen;
		gen.add_messages_path(LOCALEDIR);
		gen.add_messages_domain("mutabor");
		locale::global(gen(""));
		po::options_description desc(_mut("Allowed options"));
		po::positional_options_description p;
		po::variables_map vm;

		desc.add_options()
			("help", _mut("produce this help message"))
			("kbm-file,k", po::value<std::string>(&kbmfile),
			 _mut("Use .kbm file"))
			("prefix,p",
			 po::value<std::string>(&options.prefix)
			 ->default_value(std::string(_mut("scala"))),
			 _mut("Prefix interval identifiers with arg"))
			("tone-prefix,t",
			 po::value<std::string>(&options.tone_prefix)
			 ->default_value(std::string(_mut("scala_tone"))),
			 _mut("Prefix tone identifiers with arg"))
			("tonesystem,n",
			 po::value<std::string>(&options.tonesystem_name)
			 ->default_value(std::string(_mut("scala_tonesystem"))),
			 _mut("Set the name of the generated tone system to arg"))
			("logic,l",
			 po::value<std::string>(&options.logic_name)
			 ->default_value(std::string(_mut("scala_logic"))),
			 _mut("Set the name of the generated logic to arg"))
			//			("input-file,i", po::value<std::vector<std::string> >()->required(),  "files to compile")
			("input-file,i", po::value<std::string>(&inputfile),  _mut(".scl file that shall be converted"))
			("output-file,o", po::value<std::string>(&outputfile),  _mut("filename of the mutabor logic"))
#ifdef DEBUG
#define N_
#define DEBUGFLAG(flag,description) \
			("debug-"#flag, po::bool_switch()->implicit_value(true)->notifier(::mutabor::debugFlags::set ## flag()), _mut(description))
#include "src/kernel/debugFlags.h"
#undef DEBUGFLAG
#endif
			;

		p.add("input-file", 1).add("output-file",1);

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

		if (vm.count("help")) {
			do_help(desc,*av);
			return 0;
		}

		if (inputfile.empty()) {
			input = &cin;
			inputfile = "<stdin>";
		} else {
			fs::path p(inputfile);
			input = new fs::ifstream(p, std::ios::in);
		}

		if (!kbmfile.empty()) {
			fs::path p(kbmfile);
			keymapinput = new fs::ifstream(p, std::ios::in);
		}

		if (outputfile.empty()) {
			output = &cout;
			outputfile = "<stdout>";
		} else {
			fs::path p(outputfile);
			output = new fs::ofstream(p, std::ios::out);
		}
		run();
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

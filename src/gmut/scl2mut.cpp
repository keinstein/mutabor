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
	struct Mutex {} ;
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

		Mutex debugmutex;
	}
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
std::string krbfile;
std::string prefix;


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

void run(std::istream & i,
	 std::ostream & o,
	 const std::string & filename) {
	std::string s;

	i.seekg(0, std::ios::end);
	streampos pos = i.tellg();
	if (pos > 0)
		s.reserve(pos);
	i.seekg(0, std::ios::beg);

	s.assign((std::istreambuf_iterator<char>(i)),
		   std::istreambuf_iterator<char>());

	mutabor::scala_parser::parser scparser(s,filename);
	mutabor::scala_parser::parser::mutabor_writer_options w;
	w.prefix = prefix;
	scparser.write_mutabor(o,w);
}

void openout_and_run(std::istream & i, const std::string & filename) {
		if (!outputfile.empty()) {
			fs::path p(outputfile);
			fs::ofstream os(p, std::ios::out);
			run(i,os,filename);
		} else {
			run(i,cout,filename);
		}
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
			("krb-file,k", po::value<std::string>(&krbfile), _mut("Use .krb file instead of the on with the same name as the input"))
			("prefix,p", po::value<std::string>(&prefix)->default_value(std::string("scala")),
			 _mut("Prefix identifiers with arg"))
			//			("input-file,i", po::value<std::vector<std::string> >()->required(),  "files to compile")
			("input-file,i", po::value<std::string>(&inputfile),  _mut(".scl file that shall be converted"))
			("output-file,o", po::value<std::string>(&outputfile),  _mut("filename of the mutabor logic"))
#ifdef DEBUG
#define N_
#define DEBUGFLAG(flag,description) \
			("debug-"#flag, po::value<bool>()->notifier(::mutabor::debugFlags::set ## flag()), _mut(description))
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

		if (!inputfile.empty()) {
			fs::path p(inputfile);
			fs::ifstream is(p, std::ios::in);
			openout_and_run(is,inputfile);
		} else {
			openout_and_run(cin,"<stdin>");
		}
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

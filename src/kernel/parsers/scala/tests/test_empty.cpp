#include "src/wxGUI/TestInitializer.h"
#include "src/kernel/parsers/scala/scala.h"
#include "src/kernel/parsers/scala/scale_parser.hh"
#include "src/kernel/parsers/scala/scale_lexer.h"
#include "src/kernel/parsers/scala/scala-inlines.h"
using namespace mutabor;
using namespace mutabor::scala_parser;

struct test_parser: public parser {
	test_parser(const std::string & s,
		    const std::string & f):parser(s,f) {};
	virtual ~test_parser() {}
};

int main ()
{
	mutwxInitializer initializer;
	interval_pattern cmp("Constant tone system",0);
#ifdef DEBUG
	isDebugFlag(sclparser) =true;
#endif
	test_parser p("\
Constant tone system\n\
0","test1");
	std::cout << "p" << std::endl
		  << p.get_intervals() << std::endl
		  << "cmp" << std::endl
		  << cmp << std::endl << std::flush;
	mutASSERT(p.get_intervals() == cmp);


	p.load_keymap("\
0\n\
0\n\
127\n\
60\n\
69\n\
440.0\n\
12\n\
","testmap1");
	keymap kcmp;
	kcmp.count = 0;
	kcmp.first_key = 0;
	kcmp.last_key = 127;
	kcmp.reference = 69;
	kcmp.anchor = 60;
	kcmp.reference_frequency = 440.0;
	kcmp.repetition_interval = 12;

	std::cout << "p" << std::endl
		  << p.get_keys() << std::endl
		  << "kcmp" << std::endl
		  << kcmp << std::endl << std::flush;
	mutASSERT(p.get_keys() == kcmp);

	p.load_keymap("\
0\n\
0\n\
127\n\
60\n\
69\n\
440.0\n\
12","testmap1");

	std::cout << "p" << std::endl
		  << p.get_keys() << std::endl
		  << "kcmp" << std::endl
		  << kcmp << std::endl << std::flush;
	mutASSERT(p.get_keys() == kcmp);

	return 0;
}

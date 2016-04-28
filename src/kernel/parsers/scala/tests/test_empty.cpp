#include "src/wxGUI/TestInitializer.h"
#include "src/kernel/parsers/scala/scala.h"
#include "src/kernel/parsers/scala/scale_parser.hh"
#include "src/kernel/parsers/scala/scale_lexer.h"
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
	test_parser p("\
Constant tone system\n\
0","test1");
	std::cout << "p" << std::endl
		  << p.get_intervals() << std::endl
		  << "cmp" << std::endl
		  << cmp << std::endl << std::flush;
	mutASSERT(p.get_intervals() == cmp);

	return 0;
}

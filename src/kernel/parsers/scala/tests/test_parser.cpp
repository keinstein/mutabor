#include "src/kernel/parsers/scala/scala.h"
using namespace mutabor;
using namespace mutabor::scala_parser;

class test_parser: public string_parser {
	test_parser(const std::string & s):string_parser(s) {};
	virtual ~test_parser() {}
}

int int_main {
	interval_pattern cmp("Constant tone system",0);
	string_parser p("\
Constant tone system\n\
0");
	mutASSERT(p.get_intervals == cmp);

}

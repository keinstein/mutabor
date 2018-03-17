#include "src/wxGUI/TestInitializer.h"
#include "src/kernel/parsers/scala/scala.h"
#include "src/kernel/parsers/scala/scale_parser.hh"
#include "src/kernel/parsers/scala/scale_lexer.h"
#include "src/kernel/parsers/scala/scala-inlines.h"
using namespace mutabor;
using namespace mutabor::scala_parser;

struct test_parser: public parser {
	test_parser(const std::string & s,
		    const std::string & f):parser(s,s) { mutUnused(f); };
	virtual ~test_parser() {}
	void parse(const std::string & s,
		   const std::string & f)
	{
		intervals = interval_pattern();
		if (bison_parser) {
			delete bison_parser;
			bison_parser = NULL;
		}
		if (lexer) {
			delete lexer;
			lexer = NULL;
		}
		parser::parse(s,f);
	}
};

int main ()
{
	mutwxInitializer initializer;
	interval_pattern cmp("Constant tone system",0);
	cmp.comment1 = " comment 1 ";
	const char * scala = "\
! comment 1 \n\
Constant tone system\n\
0";
	std::cout << scala << std::endl << std::endl;
	test_parser p(scala,"test1");
	std::cout << "p" << std::endl
		  << p.get_intervals() << std::endl
		  << "cmp" << std::endl
		  << cmp << std::endl << std::flush;
	mutASSERT(p.get_intervals() == cmp);

	cmp.comment2 = " comment 2 ";
	scala = "\
! comment 1 \n\
Constant tone system\n\
! comment 2 \n\
0";
	std::cout << scala << std::endl << std::endl;
	p.parse(scala,"test2");
		
	std::cout << "p" << std::endl
		  << p.get_intervals() << std::endl
		  << "cmp" << std::endl
		  << cmp << std::endl << std::flush;
	mutASSERT(p.get_intervals() == cmp);

	cmp.comment1 = "";
	scala = "\
Constant tone system\n\
! comment 2 \n\
0";
	std::cout << scala << std::endl << std::endl;
	p.parse(scala,"test2");
		
	std::cout << "p" << std::endl
		  << p.get_intervals() << std::endl
		  << "cmp" << std::endl
		  << cmp << std::endl << std::flush;
	mutASSERT(p.get_intervals() == cmp);

	return 0;
}

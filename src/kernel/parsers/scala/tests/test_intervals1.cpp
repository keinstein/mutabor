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

bool check_interval_patterns (const interval_pattern & o,
			       const interval_pattern & r) {
	std::cerr << "name: " << (r.name == o.name?"ok":"fail") << std::endl;
	std::cerr << "count: " << (r.count == o.count?"ok":"fail") << std::endl;
	std::cerr << "intervals: " << (r.intervals == o.intervals?"ok":"fail") << std::endl;
	std::cerr << "comment1: " << (r.comment1 == o.comment1?"ok":"fail") << std::endl;
	std::cerr << "comment2: " << (r.comment2 == o.comment2?"ok":"fail") << std::endl;
	std::cerr << "count_comment: " << (r.count_comment==o.count_comment?"ok":"fail") << std::endl;
	std::cerr << "garbage: " << (r.garbage == o.garbage?"ok":"fail") << std::endl;
	return o == r;
}


int main ()
{
	mutwxInitializer initializer;
	interval_pattern cmp("Constant tone system",12);
	cmp.intervals.push_back(interval(1));
	cmp.intervals.push_back(interval(2,3));
	cmp.intervals.push_back(interval(4.5));
	cmp.intervals.push_back(interval(6,7));
	cmp.intervals.push_back(interval(8));
	cmp.intervals.push_back(interval(9.10));
	cmp.intervals.push_back(interval(11));
	cmp.intervals.push_back(interval(12));
	cmp.intervals.push_back(interval(13,14));
	cmp.intervals.push_back(interval(15,16));
	cmp.intervals.push_back(interval(17.18));
	cmp.intervals.push_back(interval(19.20));

	const char * scala = "\
Constant tone system\n\
12\n\
1\n\
2/3\n\
4.5\n\
6/7\n\
8\n\
9.10\n\
11\n\
12\n\
13/14\n\
15/16\n\
17.18\n\
19.20";

	
	std::cout << scala << std::endl << std::endl;
	test_parser p(scala,"test1");
	std::cout << "p" << std::endl
		  << p.get_intervals() << std::endl
		  << "cmp" << std::endl
		  << cmp << std::endl << std::flush;
	
	mutASSERT(check_interval_patterns(p.get_intervals(), cmp));

	scala = "\
Constant tone system\n\
12\n\
1\n\
2/3\n\
4.5\n\
6/7\n\
8\n\
9.10\n\
11\n\
12\n\
13/14\n\
15/16\n\
17.18\n\
19.20\n\
";

	
	std::cout << scala << std::endl << std::endl;
	p.parse(scala,"test2");
	std::cout << "p" << std::endl
		  << p.get_intervals() << std::endl
		  << "cmp" << std::endl
		  << cmp << std::endl << std::flush;
	mutASSERT(check_interval_patterns(p.get_intervals(), cmp));

	cmp.garbage = "ditarenditaen";
	scala = "\
Constant tone system\n\
12\n\
1\n\
2/3\n\
4.5\n\
6/7\n\
8\n\
9.10\n\
11\n\
12\n\
13/14\n\
15/16\n\
17.18\n\
19.20\n\
ditarenditaen";

	
	std::cout << scala << std::endl << std::endl;
	p.parse(scala,"test3");
	std::cout << "p" << std::endl
		  << p.get_intervals() << std::endl
		  << "cmp" << std::endl
		  << cmp << std::endl << std::flush;
	mutASSERT(check_interval_patterns(p.get_intervals(), cmp));

	cmp.intervals[0].description =" c1";
	cmp.intervals[1].description =" irgendwas";
	cmp.intervals[2].description =" nochäwas";
	cmp.intervals[3].description =" tirantra";
	cmp.intervals[4].description =" itdaendia";
	cmp.intervals[5].description =" indaetrina";
	cmp.intervals[6].description =" ditarnedtriade";
	cmp.intervals[7].description =" iaetiaend";
	cmp.intervals[8].description ="!";
	cmp.intervals[9].description ="itiraseit";
	cmp.intervals[10].description =" idaternid";
	cmp.intervals[11].description =" ! ditraendai";
	cmp.garbage.clear();
	
	scala = "\
Constant tone system\n\
12\n\
1 c1\n\
2/3 irgendwas\n\
4.5 nochäwas\n\
6/7 tirantra\n\
8 itdaendia\n\
9.10 indaetrina\n\
11 ditarnedtriade\n\
12 iaetiaend\n\
13/14!\n\
15/16itiraseit\n\
17.18 idaternid\n\
19.20 ! ditraendai";
	std::cout << scala << std::endl << std::endl;
	p.parse(scala,"test4");
		
	std::cout << "p" << std::endl
		  << p.get_intervals() << std::endl
		  << "cmp" << std::endl
		  << cmp << std::endl << std::flush;
	mutASSERT(check_interval_patterns(p.get_intervals(), cmp));

	scala = "\
Constant tone system\n\
12\n\
1 c1\n\
2/3 irgendwas\n\
4.5 nochäwas\n\
6/7 tirantra\n\
8 itdaendia\n\
9.10 indaetrina\n\
11 ditarnedtriade\n\
12 iaetiaend\n\
13/14!\n\
15/16itiraseit\n\
17.18 idaternid\n\
19.20 ! ditraendai\n\
";
	std::cout << scala << std::endl << std::endl;
	p.parse(scala,"test5");
		
	std::cout << "p" << std::endl
		  << p.get_intervals() << std::endl
		  << "cmp" << std::endl
		  << cmp << std::endl << std::flush;
	mutASSERT(check_interval_patterns(p.get_intervals(), cmp));

	cmp.garbage = "ditarenditaen";

	scala = "\
Constant tone system\n\
12\n\
1 c1\n\
2/3 irgendwas\n\
4.5 nochäwas\n\
6/7 tirantra\n\
8 itdaendia\n\
9.10 indaetrina\n\
11 ditarnedtriade\n\
12 iaetiaend\n\
13/14!\n\
15/16itiraseit\n\
17.18 idaternid\n\
19.20 ! ditraendai\n\
ditarenditaen";
	std::cout << scala << std::endl << std::endl;
	p.parse(scala,"test6");
		
	std::cout << "p" << std::endl
		  << p.get_intervals() << std::endl
		  << "cmp" << std::endl
		  << cmp << std::endl << std::flush;
	mutASSERT(check_interval_patterns(p.get_intervals(), cmp));

	return 0;
}

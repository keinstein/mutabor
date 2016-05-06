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
	void load_keymap(const std::string & s,
		   const std::string & f)
	{
		keys = keymap();
		if (bison_parser) {
			delete bison_parser;
			bison_parser = NULL;
		}
		if (lexer) {
			delete lexer;
			lexer = NULL;
		}
		parser::load_keymap(s,f);
	}
};

bool check_keymaps (const keymap & o,
		    const keymap & r) {
	return o == r;
}


int main ()
{
	isDebugFlag(sclparser) =true;
	mutwxInitializer initializer;
	keymap cmp;
	cmp.count = 1;
	cmp.first_key = 0;
	cmp.last_key = 127;
	cmp.reference = 60;
	cmp.anchor = 69;
	cmp.reference_frequency = 440.0;
	cmp.repetition_interval = 12;
	cmp.keys.push_back(key(1));

	const char * scala = "\
1\n\
0\n\
127\n\
60\n\
69\n\
440.0\n\
12\n\
1";

	
	std::cout << scala << std::endl << std::endl;
	test_parser p("\n0",".scl");
	p.load_keymap(scala,"test1");
	std::cout << "p" << std::endl
		  << p.get_keys() << std::endl
		  << "cmp" << std::endl
		  << cmp << std::endl << std::flush;
	
	mutASSERT(check_keymaps(p.get_keys(), cmp));

	cmp.count.comment = " Constant tone system";
	scala = "\
! Constant tone system\n\
1\n\
0\n\
127\n\
60\n\
69\n\
440.0\n\
12\n\
1\n\
";

	
	std::cout << scala << std::endl << std::endl;
	p.load_keymap(scala,"test2");
	std::cout << "p" << std::endl
		  << p.get_keys() << std::endl
		  << "cmp" << std::endl
		  << cmp << std::endl << std::flush;
	mutASSERT(check_keymaps(p.get_keys(), cmp));

	cmp.garbage = "ditarenditaen";
	cmp.keys.push_back(key());
	cmp.keys.push_back(key(5));
	cmp.keys.push_back(key(2));
	cmp.count.value = 4;
	scala = "\
! Constant tone system\n\
4\n\
0\n\
127\n\
60\n\
69\n\
440.0\n\
12\n\
1\n\
x\n\
5\n\
2\n\
ditarenditaen";

	
	std::cout << scala << std::endl << std::endl;
	p.load_keymap(scala,"test3");
	std::cout << "p" << std::endl
		  << p.get_keys() << std::endl
		  << "cmp" << std::endl
		  << cmp << std::endl << std::flush;
	mutASSERT(check_keymaps(p.get_keys(), cmp));

	cmp.keys[0].description =" c1";
	cmp.keys[1].description ="!";
	cmp.keys[2].description ="itiraseit";
	cmp.keys[3].description =" idaternid";
	cmp.keys[3].comment = " Auto";
	
	scala = "\
! Constant tone system\n\
4\n\
0\n\
127\n\
60\n\
69\n\
440.0\n\
12\n\
1 c1\n\
x!\n\
5itiraseit\n\
! Auto\n\
2 idaternid\n\
ditarenditaen";

	std::cout << scala << std::endl << std::endl;
	p.load_keymap(scala,"test4");
		
	std::cout << "p" << std::endl
		  << p.get_keys() << std::endl
		  << "cmp" << std::endl
		  << cmp << std::endl << std::flush;
	mutASSERT(check_keymaps(p.get_keys(), cmp));

	return 0;
}

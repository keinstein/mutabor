#include "src/kernel/routing/thread.h"
#include <iostream>
#include <cassert>

boost::mutex printmutex;
using namespace mutabor;

void print_stack_size() {
#ifndef WIN32
	pthread_attr_t attr;
	size_t stacksize;

	pthread_attr_init(&attr);
	pthread_attr_getstacksize(&attr, &stacksize); 
	
	{
		boost::unique_lock<boost::mutex> lock(printmutex);
		std::cerr << "Stack size: " << stacksize << std::endl;
	}
#endif
}

void print_status (const char * s) {
	boost::unique_lock<boost::mutex> lock(printmutex);
	std::cerr << s << std::endl;
}

class test_thread: public Thread {
public:
	virtual ~test_thread() {}


	thread_state get_command() { return command; }
	thread_state get_state()   { return state;   }
private:
	int Entry() {
		print_status("Entry()");

		print_stack_size();

		assert(state == thread_running);
		
		return 0;
	}
	void OnExit() {
		boost::unique_lock<boost::mutex> lock(printmutex);
		std::cerr << "OnExit()" << std::endl;
		assert(state == thread_ending);
	}
};

int main() {
	test_thread test;
	print_status("Before Run");
	assert(test.get_command() == Thread::thread_initialized);
	assert(test.get_state() == Thread::thread_initialized);
	test.Run();
	assert(test.get_command() == Thread::thread_running);
	print_status("After Run");
	int retval = test.Wait();
	{
		boost::unique_lock<boost::mutex> lock(printmutex);
		std::cerr << "Wait returns: " << retval << std::endl;
	}
	assert(test.get_state() == Thread::thread_finished);
	return 0;
}

	

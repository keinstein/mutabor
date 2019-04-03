#include "src/kernel/routing/thread.h"
#include <iostream>
#include <cassert>
#include <cstdlib>

boost::mutex printmutex;
using namespace mutabor;

void print_stack_size() {
#ifndef WIN32
	pthread_attr_t attr;
	size_t stacksize;

	pthread_attr_init(&attr);
	pthread_attr_getstacksize(&attr, &stacksize);

	try {
		boost::unique_lock<boost::mutex> lock(printmutex);
		std::cerr << "Stack size: " << stacksize << std::endl;
	} catch (const boost::lock_error & e) {
		std::cerr << boost::current_exception_diagnostic_information();
		exit(1);
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
	int Entry() throw() {
		print_status("Entry()");

		print_stack_size();

		assert(state == thread_running);

		return 0;
	}
	void OnExit() throw() {
		try {
			boost::unique_lock<boost::mutex> lock(printmutex);
			std::cerr << "OnExit()" << std::endl;
			assert(state == thread_ending);
		}  catch (const boost::lock_error & e) {
			std::cerr << boost::current_exception_diagnostic_information();
			exit(1);
		}
	}
};

int main() {
	test_thread test;
	print_status("Before Run");
	assert(test.get_command() == Thread::thread_initialized);
	assert(test.get_state() == Thread::thread_initialized);
	try {
		test.Run();
	} catch (const boost::condition_error & e) {
		std::cerr << boost::current_exception_diagnostic_information();
		return 1;
	}

	assert(test.get_command() == Thread::thread_running);
	print_status("After Run");
	int retval;
	try {
		retval = test.Wait();
	} catch (const boost::condition_error & e) {
		std::cerr << boost::current_exception_diagnostic_information();
		return 1;
	}

	try {
		boost::unique_lock<boost::mutex> lock(printmutex);
		std::cerr << "Wait returns: " << retval << std::endl;
	} catch (const boost::lock_error & e) {
		std::cerr << boost::current_exception_diagnostic_information();
		return 1;
	}
	assert(test.get_state() == Thread::thread_finished);
	return 0;
}



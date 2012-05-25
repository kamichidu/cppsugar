#include <time/stop_watch.hpp>
#include <iostream>
#include <unistd.h>

using namespace lib::time;

int main(int argc, char* argv[]){
	stop_watch sw= 1e-3;

	sw.start();
	sleep(1);
	sw.stop();

	std::cout << "time: " << sw.time() << std::endl;

	return 0;
}


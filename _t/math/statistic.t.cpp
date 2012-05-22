#include <math/statistic.hpp>
#include <assert.h>
#include <cmath>

using namespace lib::math;

int main(int argc, char* argv[]){
	statistic<int> stat({1, 2, 3, 4, 5, 6, 7, 8, 9, 10});

	assert(stat.min() == 1 && "min != 1");
	assert(stat.max() == 10 && "max != 10");
	assert(abs(stat.mean() - 5.5) < 0.01 && "mean != 5.5");
	assert(stat.size() == 10 && "size != 10");
	
	return 0;
}



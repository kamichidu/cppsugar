#include <math/vector.hpp>

using namespace lib::math;

int main(int argc, char* argv[]){
	vector<3> v0, v1;

	v0[0]= 1.; v0[1]= 2.; v0[2]= 3.;
	v1[0]= 1.; v1[1]= 2.; v1[2]= 3.;

	auto const v2= v0 + v1;
	auto const v3= v0 - v1;
	auto const v4= v0.dot_product(v1);

	return 0;
}


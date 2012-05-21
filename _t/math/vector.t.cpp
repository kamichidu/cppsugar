#include <math/vector.hpp>

using namespace lib::math;

vector<3> create(){
	return vector<3>();
}

int main(int argc, char* argv[]){
	vector<3> v0, v1;

	v0[0]= 1.; v0[1]= 2.; v0[2]= 3.;
	v1[0]= 1.; v1[1]= 2.; v1[2]= 3.;

	auto const v2= v0 + v1;
	auto const v3= v0 - v1;
	auto const d0= v0.dot_product(v1);

	auto const v5= create();

	auto const v6= vector<3>(v5);

	return 0;
}


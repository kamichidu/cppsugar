#include <stdio.h>
#include <math/matrix.hpp>

using namespace lib::math;

int main(int argc, char* argv[]){
	matrix<3, 3> m0, m1;

	m0[0][0]= 1.; m0[0][1]= 2.; m0[0][2]= 3.;
	m0[1][0]= 4.; m0[1][1]= 5.; m0[1][2]= 6.;
	m0[2][0]= 7.; m0[2][1]= 8.; m0[2][2]= 9.;

	m1[0][0]= 1.; m1[0][1]= 2.; m1[0][2]= 3.;
	m1[1][0]= 4.; m1[1][1]= 5.; m1[1][2]= 6.;
	m1[2][0]= 7.; m1[2][1]= 8.; m1[2][2]= 9.;

	auto added= m0 + m1;

	printf(
		"%2.2f %2.2f %2.2f\n"
		"%2.2f %2.2f %2.2f\n"
		"%2.2f %2.2f %2.2f\n", 
			added[0][0], added[0][1], added[0][2],
			added[1][0], added[1][1], added[1][2],
			added[2][0], added[2][1], added[2][2]);


	return 0;
}



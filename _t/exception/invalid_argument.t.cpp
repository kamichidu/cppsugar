#include <exception/illegal_arguments.hpp>
#include <wchar.h>

using namespace lib::exception;

int main(int argc, char* argv[]){
	invalid_argument<wchar_t> e(L"hello?");

	if(!(L"hello?" == e.what()))
		fprintf(stderr, "illegal_arguments#what() does not return correct text.");

	invalid_argument<wchar_t> copy(e);

	return 0;
}


#include <iostream>
#include <string>
#include "argparse.h"
#include "err_handler.h"

using namespace std;

int main(int argc, char** argv) {
	if (argc > MAX_ARGS_POSSIBLE) {
		err_handler::handle_error(ARG_ERR);
	}
	// array for storing cmd params
	string params[MAX_ARGS_POSSIBLE];

	// extract params to array
   	for (int i = 0; i < argc; i++) {
		// skip name of program
		if (i == 0) {
			continue;
		}
		params[i] = (string) argv[i];
	}
	
	// create argparse object
	try {
		argparse args(params, argc);
	} catch (const char* msg) {
		cerr << msg << endl;
	}
}

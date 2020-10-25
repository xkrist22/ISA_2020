#include <iostream>
#include <string>
#include "argparse.h"

using namespace std;

int main(int argc, char** argv) {
	// array for storing cmd params
	string params[argparse::MAX_ARGS];
	if (argc > argparse::MAX_ARGS) {
		exit(1);
	}
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

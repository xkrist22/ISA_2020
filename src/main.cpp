#include <iostream>
#include <string>
#include "argparse.h

using namespace std;

int main(int argc, char** argv) {
	string[6] params;
    for (int i = 0; i < argc; i++) {
        params[i] = argv[i];
	}
    for (int i = 0; i < argc; i++) {
        cout << params[i];
    }
}
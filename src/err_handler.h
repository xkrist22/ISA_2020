#ifndef err_handler_H
#define err_handler_H

#include <string>
using namespace std;

class err_handler {
public:
	static const int EXIT_OK = 0;
	// unknown argument loaded error
    static const int ARG_ERR = 1;
    // ip format unknown error
    static const int IP_ERR = 2;
    // unknown domain name error
    static const int DOMAIN_NAME_ERR = 3;
    // undefined port number error
    static const int PORT_ERR = 4;
    // filter file not exists error
    static const int FILTER_FILE_NOT_EXIST_ERR = 5;
    // filter file structure error
    static const int FILTER_FILE_STRUCTURE_ERR = 6;
    err_handler(int err_code);
private:
    void print_help();
};

#endif // argparse_H

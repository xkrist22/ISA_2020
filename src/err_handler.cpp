#include <iostream>
#include <string>
#include "err_handler.h"

using namespace std;

void err_handler::handle_error(int err_code) {
    // help is printed when args are incorrect
    if (err_code == ARG_ERR) {
	// if program gets bad arguments, program terminates
        cerr << "Arguments error!\n";
    } else if (err_code == IP_OR_DOMAIN_NAME_ERR) {
	// if ip address or domain name is invalid, program terrminates
	cerr << "DNS server IP address or domain name error!\n";
    } else if (err_code == PORT_ERR) {
	// if there are problems with port number, program uses default settings
	cerr << "Port number error, using default port!\n";
	return;
    } else if (err_code == FILTER_FILE_NOT_EXIST_ERR) {
	// if filter file does not exists, program terminates
	cerr << "Filter file does not exists!\n";
    } else if (err_code == FILTER_FILE_STRUCTURE_ERR) {
	// if filter file contains bad line, it is skipped
	cerr << "Bad structure in filter file, skipping line!\n";
	return;
    }

    print_help();
    exit(err_code);
}


void err_handler::print_help() {
    cerr << "dns program:\n";
    cerr << "\tprogram filter questions of A type. If domain in question is in filter file, then";
    cerr << "program will discard the DNS message. Else it resend question to specific DNS server";
    cerr << "and return answer from server.\n\n";
    cerr << "Usage:\n";
    cerr << "\tdns -s server [-p port] -f filter_file\n";
    cerr << "\t-s server: IP address or domain name of DNS server\n";
    cerr << "\t-p port: number of port, where program waits for questions\n";
    cerr << "\t-f filter_file: name of file containing domains to filter\n\n";
    cerr << "Note:\n";
    cerr << "\tProgram uses only A type and implements only UDP protocol.\n";
    cerr << "\tIf program get unknown parameter, it is skipped.\n\n";
}

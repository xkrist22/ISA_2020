#include <iostream>
#include <string>
#include <regex>
#include "argparse.h"

using namespace std;

err_handler::err_handler(int err_code) {
    // help is printed when args are incorrect
    if (err_code == ARG_ERR) {
        cerr << "Arguments error!\n"
        this.print_help();
        exit(err_code);
    } else
}

void err_handler::print_help() {
    cerr << "dns program:\n"
    cerr << "\tprogram filter questions of A type. If domain in question is in filter file, then"
    cerr << "\tprogram will discard the DNS message. Else it resend question to specific DNS server"
    cerr << "\tand return answer from server.\n\n"
    cerr << "Usage:\n"
    cerr << "\tdns -s server [-p port] -f filter_file\n"
    cerr << "\t-s server: IP address or domain name of DNS server\n"
    cerr << "\t-p port: number of port, where program waits for questions\n"
    cerr << "\t-f filter_file: name of file containing domains to filter\n\n"
    cerr << "Limits:\n"
    cerr << "\tProgram uses only A type and implements only UDP protocol.\n\n"
}
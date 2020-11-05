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
	} else if (err_code == SERVER_SOCKET_OPEN_ERR) {
		// if program cannot open socket, program terminates
		cerr << "Opening of the UDP socket failed!\n";
	} else if (err_code == SERVER_SOCKET_BIND_ERR) {
		// if program cannot bind socket, program terminates
		cerr << "Binding of the UDP socket failed!\n";
	} else if (err_code == SERVER_INPUT_DATA_ERR) {
		// if program detects problem during recieving data, it terminates NORMALLY
		cerr << "Problem during recieving, server terminates!\n";
	} else if (err_code == SERVER_CANNOT_SEND_DATA_ERR) {
		// if program cannot send data, program terminates
		cerr << "Problems with sending data to client, server terminates!\n";
	} else if (err_code == SERVER_SEND_DATA_PARTIALLY_ERR) {
		// if program send only part of data, program terminates
		cerr << "Problems with sending data to client - buffer written partially, server terminates!\n";
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
	cerr << "\tdns -s server [-p port] -f filter_file -v\n";
	cerr << "\t-s server: IP address or domain name of DNS server\n";
	cerr << "\t-p port: number of port, where program waits for questions\n";
	cerr << "\t-f filter_file: name of file containing domains to filter\n";
	cerr << "\t-v: turn on verbose mode\n\n";
	cerr << "Note:\n";
	cerr << "\tProgram uses only A type and implements only UDP protocol.\n";
	cerr << "\tIf program get unknown parameter, it is skipped.\n\n";
}

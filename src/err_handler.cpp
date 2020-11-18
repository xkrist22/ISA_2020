#include <iostream>
#include <string>
#include <errno.h>
#include <stdio.h>
#include "err_handler.h"

using namespace std;

void err_handler::handle_error(int err_code) {
	// help is printed when args are incorrect
	if (err_code == RUN_HELP) {
		;//pass
	} else if (err_code == ARG_ERR) {
		// if program gets bad arguments, program terminates
		cerr << "USAGE:\n";
	} else if (err_code == IP_OR_DOMAIN_NAME_ERR) {
		// if ip address or domain name is invalid, program terrminates
		cerr << " *** DNS server IP address or domain name error!\n";
	} else if (err_code == PORT_ERR) {
		// if there are problems with port number, program uses default settings
		cerr << " *** Port number error, using default port!\n";
		return;
	} else if (err_code == FILTER_FILE_NOT_EXIST_ERR) {
		// if filter file does not exists, program terminates
		cerr << " *** Filter file does not exists!\n";
	} else if (err_code == FILTER_FILE_STRUCTURE_ERR) {
		// if filter file contains bad line, it is skipped
		cerr << " *** Bad structure in filter file, skipping line!\n";
		return;
	} else if (err_code == SERVER_SOCKET_OPEN_ERR) {
		// if program cannot open socket, program terminates
		cerr << " *** Opening of the server UDP socket failed!\n";
	} else if (err_code == SERVER_SOCKET_BIND_ERR) {
		// if program cannot bind socket, program terminates
		cerr << " *** Binding of the server UDP socket failed!\n";
	} else if (err_code == SERVER_INPUT_DATA_ERR) {
		// if program detects problem during recieving data, it terminates NORMALLY
		cerr << " *** Problem during recieving data, server terminates!\n";
	} else if (err_code == SERVER_CANNOT_SEND_DATA_ERR) {
		// if program cannot send data, program terminates
		cerr << " *** Problems with sending data to client, server terminates!\n";
	} else if (err_code == SERVER_SEND_DATA_PARTIALLY_ERR) {
		// if program send only part of data, program terminates
		cerr << " *** Problems with sending data to client - buffer written partially, server terminates!\n";
	} else if (err_code == CLIENT_SOCKET_OPEN_ERR) {
		// if program cannot open client socket, program waits for another dns packet
		cerr << " *** Opening of the client UDP socket failed!\n";
		return;
	} else if (err_code == CLIENT_SOCKET_CONNECT_ERR) {
		// if program cannot connect socket, program waits for another dns packet
		cerr << " *** Connecting of the client UDP socket failed!\n";
		return;
	} else if (err_code == CLIENT_CANNOT_SEND_DATA_ERR) {
		// if program cannot connect socket, program waits for another dns packet
		cerr << " *** Problems with sending data to server!\n";
		return;
	} else if (err_code == CLIENT_SEND_DATA_PARTIALLY_ERR) {
		// if program cannot send data, program waits for another dns packet
		cerr << " *** Problems with sending data to client - buffer written partially!\n";
		return;
	} else if (err_code == CLIENT_RECIEVING_DATA_ERROR) {
		// if program cannot recieve data, program waits for another dns packet
		cerr << " *** Problems during recieving of data!\n";
		return;
	} else if (err_code == SOCK_NAME_ERR) {
		// if program cannot get socket name, program waits for another dns packet
		cerr << " *** Problems with socket!\n";
		return;
	} else if (err_code == SERVER_RECIEVING_DATA_ERR) {
		// if program cannot get data from client, program waits for another dns packet
		cerr << " *** Problems with recieving data from client!\n";
		return;
	} else {
		// if unknown error code is loaded, program terminates
		// NOTE: unknown error should not occur!
		cerr << " *** Unknown error code!\n";
	}
	cerr << " *** errno info: " << strerror(errno) << "\n";
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

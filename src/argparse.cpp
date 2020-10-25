#include <iostream>
#include <string>
#include <regex>
#include "argparse.h"

using namespace std;

argparse::argparse(string cmd_arg_arr[6], int num_of_args) {
	// default values
	this->port = 53;
	this->filter_file_name = "";
	this->dns_ip = "";
	this->dns_domain_name = "";

	bool load_server = false;
	bool load_port = false;
	bool load_filter_file_name = false;

	// load data from cmd into argparse object
	for (int i = 0; i < num_of_args; i++) {
		if (load_server) {
			// loads server ip or domain name
			this->dns_ip = cmd_arg_arr[i];
			load_server = false;
		} else if (load_port) {
			// loads server port
			this->port = stoi(cmd_arg_arr[i]);
			load_port = false;
		} else if (load_filter_file_name) {
			// loads filter file name
			this->filter_file_name = cmd_arg_arr[i];
			load_filter_file_name = false;
		}

		if (cmd_arg_arr[i] == "-s") {
			// activate loading server ip or domain name
			load_server = true;
		} else if (cmd_arg_arr[i] == "-p") {
			// activete loading port number
			load_port = true;
		} else if (cmd_arg_arr[i] == "-f") {
			// activate loading filter file name
			load_filter_file_name = true;
		}
	}

	// check if filter file name was loaded
	if (this->filter_file_name == "") {
		throw "Filter file name missing";
	// chekc if DNS server IP or domain name was loaded
	} else if (this->dns_ip == "" and this->dns_domain_name == "") {
		throw "DNS ip or domain name missing";
	}
}

string argparse::get_server_ip() {
	return this->dns_ip;
}

string argparse::get_server_domain_name() {
	return this->dns_domain_name;
}

int argparse::get_server_port() {
	return this->port;
}

string argparse::get_filter_file_name() {
	return this->filter_file_name;
}

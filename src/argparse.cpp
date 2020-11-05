#include <iostream>
#include <string>
#include "argparse.h"
#include "err_handler.h"
#include "func.h"

using namespace std;

argparse::argparse(string cmd_arg_arr[6], int num_of_args) {
	// default values
	this->port = DEFAULT_PORT_NUM;
	this->filter_file_name = "";
	this->dns_ip = "";
	this->dns_domain_name = "";

	bool load_server = false;
	bool load_port = false;
	bool load_filter_file_name = false;

	if (num_of_args < MIN_ARGS_POSSIBLE || num_of_args > MAX_ARGS_POSSIBLE) {
		err_handler::handle_error(ARG_ERR);
	}
	// load data from cmd into argparse object
	for (int i = 0; i < num_of_args; i++) {
		if (load_server) {
			if (func::valid_ip_addr(cmd_arg_arr[i])) {
				// loads server ip
				this->dns_ip = cmd_arg_arr[i];
			} else if (func::valid_domain_name(cmd_arg_arr[i])) {
				// loads server domain name
				this->dns_domain_name = cmd_arg_arr[i];
			} else {
				// value is not domain name or ip address
				err_handler::handle_error(ARG_ERR);
			}
			load_server = false;
		} else if (load_port) {
			try {
				// loads server port
				this->port = stoi(cmd_arg_arr[i]);
			} catch (invalid_argument &e) {
				// if port is not number, program uses default port number
				err_handler::handle_error(PORT_ERR);
				this->port = DEFAULT_PORT_NUM;
			}
			// check if port is in defined range
			if (this->port < MIN_PORT_NUM || this->port > MAX_PORT_NUM) {
				// if port is out of range, program uses default port number
				err_handler::handle_error(PORT_ERR);
				this->port = DEFAULT_PORT_NUM;
			}
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

	if (this->filter_file_name == "") {
		err_handler::handle_error(FILTER_FILE_NOT_EXIST_ERR);
	}
	if (this->dns_ip == "" && this->dns_domain_name == "") {
		err_handler::handle_error(IP_OR_DOMAIN_NAME_ERR);
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

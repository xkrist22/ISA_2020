#include <iostream>
#include <string>
#include "argparse.h"
#include "err_handler.h"
#include "func.h"
#include "filter.h"
#include "server.h"
#include "client.h"


using namespace std;

int main(int argc, char **argv) {
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
	argparse args(params, argc);
	filter f(args.get_filter_file_name());
	server s = server(args.get_server_port(), args.get_server_ip(), args.get_filter_file_name());
	s.run_server();
	
	/*
	client c = client(args.get_server_port(), args.get_server_ip());
	c.send_data(string("Toto jsou DATA!"));
	c.close_socket();
	*/
}

#ifndef argparse_H
#define argparse_H

#include <string>
using namespace std;

class argparse {
public:
	static const int MAX_ARGS = 7;
	argparse(string cmd_arg_arr[6], int num_of_args);
	string get_server_ip();
	string get_server_domain_name();
	int get_server_port();
	string get_filter_file_name();
private:
	string dns_ip;
	string dns_domain_name;
	int port;
	string filter_file_name;
};

#endif // argparse_H

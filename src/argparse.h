/**
 * @file argparse.h
 * @author Jiri Kristof, xkrist22
 * FIT VUT ISA project – DNS resolver
 *
 * File contains class argparse
 */

#ifndef argparse_H
#define argparse_H

#include <string>

#define DEFAULT_PORT_NUM 53
using namespace std;

/**
 * Class argparse
 *
 * class contains methods for parsing params from terminal
 */
class argparse {
	public:
		static const int MAX_ARGS = 7;
		/**
		 * Constructor of the argparse objects
		 * @param cmd_arg_arr  array containing params given from terminal
		 * @param num_of_args number of params given from terminal
		 */
		argparse(string cmd_arg_arr[6], int num_of_args);
		/**
		 * Getter method for returning DNS server IP
		 * @return string containing IP address of server. If IP address is not set, returns empty string
		 */
		string get_server_ip();
		/**
		 * Getter method for returning port number
		 * @return selected port number
		 */
		int get_server_port();
		/**
		 * Getter method for returning filter file name
		 * @return name of the file with URLs to filter
		 */
		string get_filter_file_name();
	private:
		string dns_ip;
		int port;
		string filter_file_name;
		bool verbose_enable;
};

#endif // argparse_H

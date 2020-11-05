/**
 * @file err_handler.h
 * @author Jiri Kristof, xkrist22
 * FIT VUT ISA project – DNS resolver
 *
 * File contains class err_handler
 */

#ifndef err_handler_H
#define err_handler_H

#include <string>

/* ***************
 * ERROR CODES
 * ***************/
// no error
#define EXIT_OK 0
// unknown argument loaded error
#define ARG_ERR 1
// ip format unknown error
#define IP_OR_DOMAIN_NAME_ERR 2
// undefined port number error
#define PORT_ERR 3
// filter file not exists error
#define FILTER_FILE_NOT_EXIST_ERR 4
// filter file structure error
#define FILTER_FILE_STRUCTURE_ERR 5
// opening server socket error
#define SERVER_SOCKET_OPEN_ERR 6
// binding server socket error
#define SERVER_SOCKET_BIND_ERR 7
// input network data error
#define SERVER_INPUT_DATA_ERR 8
// server cannot send data error
#define SERVER_CANNOT_SEND_DATA_ERR 9
// server send only part of data
#define SERVER_SEND_DATA_PARTIALLY_ERR 10
using namespace std;

/**
 * Class err_handler
 *
 * class contains methods for handling errors
 */
class err_handler {
	public:
        /**
         * Static method for handling errors
         * @param err_code code specifying error
         */
		static void handle_error(int err_code);
	private:
        /**
         * Method for printing help. Help is printed automatically after some errors
         */
		static void print_help();
};

#endif // err_handler_H

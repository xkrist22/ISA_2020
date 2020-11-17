/**
 * @file verbose.h
 * @author Jiri Kristof, xkrist22
 * FIT VUT ISA project – DNS resolver
 *
 * File contains class verbose
 */

#ifndef verbose_H
#define verbose_H

#include <string>
#include <iostream>

/* ***************
 * ARGPARSE STATE
 * ***************/
#define FILE_NAME_SET 0
#define USER_PORT_SET 1
#define DNS_SERVER_IP_SET 2
#define DNS_DOMAIN_NAME_SET 3

/* ***************
 * FILTER STATE
 * ***************/
#define FILE_FOUND 0
#define FILE_EXTRACTED 1

/* ***************
 * SERVER STATE
 * ***************/
#define SERVER_SOCKET_OPEN 0
#define SERVER_SOCKET_BIND 1
#define MSG_RECIEVED 2
#define MSG_SENT 3
#define MSG_FILTERED 4
#define MSG_TYPE_NOT_IMPLEMENTED 5
#define SERVER_START_STATE 6

/* ***************
 * CLIENT STATE
 * ***************/
#define CLIENT_SOCKET_OPEN 0
#define CLIENT_SOCKET_CONNECT 1
#define MSG_RESEND 2
#define MSG_ANSWERED 3
#define CLIENT_SOCKET_CLOSE 4

/* ***************
 * QUESTION STATE
 * ***************/
#define QUESTION_FILTERED 0
#define QUESTION_RESEND 1
#define QUESTION_ANSWERED 2

using namespace std;

class verbose {
public:
	/**
	 * Method for printing state of argparser
	 * @param atgparse_state code representing state of argparser
	 * @param info additional info
	 */
	static void print_argparse_state(int atgparse_state, string info);

	/**
	 * Method for printing state of filter file parser
	 * @param filter_state code representing state of filter file parser
	 * @param info additional info
	 */
	static void print_filter_state(int filter_state, string info);

	/**
	 * Method for printing state of server
	 * @param server_state code representing state of server
	 * @param info additional info
	 */
	static void print_server_state(int server_state, string info);

	/**
	 * Method for printing state of client
	 * @param client_state code representing state of client
	 * @param info additional info
	 */
	static void print_client_state(int client_state, string info);

	/**
	 * Method for printing state of question answering
	 * @param question_state code representing state of question answering
	 */
	static void print_question_state(int question_state);

	/**
	 * Method for printing info while terminating program
	 */
	static void print_terminating();

	// true, if verbose mode is enabled
	static bool is_enable;
};

#endif // verbose_H

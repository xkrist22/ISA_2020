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

/* ***************
 * QUESTION STATE
 * ***************/
#define QUESTION_FILTERED 0
#define QUESTION_RESEND 1
#define QUESTION_ANSWERED 2

using namespace std;

class verbose {
	public:
		static void print_argparse_state(int atgparse_state, string info);
		static void print_filter_state(int filter_state, string info);
		static void print_server_state(int server_state, string info);
		static void print_question_state(bool is_filtered);
		static void print_terminating();
		static bool is_enable;
};

#endif // verbose_H

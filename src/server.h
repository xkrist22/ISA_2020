/**
 * @file server.h
 * @author Jiri Kristof, ckrist22
 * FIT VUT ISA project - DNS resolver
 *
 * File contains class server
 */ 

#ifndef server_H
#define server_H

// std C libs
#include <string>

// network libs
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <ctype.h>
#include <err.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFER_SIZE 512

using namespace std;

class server {
	public:
		server(int port_num, string ip_addr);
		void run_server();
	private:
		void open_and_bind_socket();
		void parse_msg();
		struct sockaddr_in server_socket;
		struct sockaddr_in client_socket;
		int socket_descriptor;
		int ip_version;
};

#endif // server_H

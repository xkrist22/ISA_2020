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
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// network libs
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <ctype.h>
#include <err.h>
#include <netdb.h>

// size of buffer where is stored data from packet
// Maximal size of udp dns packet is 512b
#define BUFFER_SIZE 512

using namespace std;

/**
 * Class server
 *
 * class contains method for creating server and realizing server procedures
 */
class server {
public:
	/**
	 * Constructor of server object
	 * @param port_num number of port where server will be listening
	 * @param ip_addr ip address of DNS server for resolving dns packets
	 */
	server(int port_num, string ip_addr);

	/**
	 * Method starts server, waits for packets and process them
	 */
	void run_server();

private:
	/**
	 * Method for opening and binding socket
	 */
	void open_and_bind_socket();

	/**
	 * Method for parsing data from dns packet
	 * @return true, of dns packet is supported, else returns false
	 */
	bool parse_msg();

	struct sockaddr_in server_socket;
	struct sockaddr_in client_socket;
	int socket_descriptor;
	int ip_version;
};

#endif // server_H

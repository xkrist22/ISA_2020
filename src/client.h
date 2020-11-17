/**
 * @file client.h
 * @author Jiri Kristof, ckrist22
 * FIT VUT ISA project - DNS resolver
 *
 * File contains class client
 */

#ifndef client_H
#define client_H

// std C libs
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
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
#define BUFFER_SIZE 256

using namespace std;

/**
 * Class server
 *
 * class contains method for creating server and realizing server procedures
 */
class client {
public:
	/**
	 * Constructor of server object
	 * @param port_num number of port where server will be listening
	 * @param ip_addr ip address of DNS server for resolving dns packets
	 */
	client(int port_num, string ip_addr);

	/**
	 * Method sends data to selected server via selected port
	 * @param data data to be send
	 *
	 * @return string containing answer from server
	 */
	char* send_data(char data[BUFFER_SIZE], int* ret_size);

	/**
	 * Method for closing socket
	 */
	void close_socket();


private:
	/**
	 * Method for opening and connecting socket
	 */
	void open_and_connect_socket();

	/**
	 * Method for parsing data from dns packet
	 * @return true, of dns packet is supported, else returns false
	 */

	struct sockaddr_in server_socket;
	struct sockaddr_in local_socket;
	struct hostent *serverent;
	int socket_descriptor;
	int ip_version;
};

#endif // server_H

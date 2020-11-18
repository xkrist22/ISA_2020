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
#include <cstdint>

#include "filter.h"

// size of buffer where is stored data from packet
// Maximal size of udp dns packet is 512b
#define BUFFER_SIZE 256
#define DNS_PORT_NUM 53
#define HEADER_LEN 12
#define TYPE_A 1

#define RCODE_MASK 0b1000000110000000

// struct for dns head flags
typedef struct dns_flags {

	u_int16_t rcode :4;
	u_int16_t z :3;
	u_int16_t ra :1;
	u_int16_t rd :1;
	u_int16_t tc :1;
	u_int16_t aa :1;
	u_int16_t opcode :4;
	u_int16_t qr :1;
/*
	u_int16_t qr :1;
	u_int16_t opcode :4;
	u_int16_t aa :1;
	u_int16_t tc :1;
	u_int16_t rd :1;
	u_int16_t ra :1;
	u_int16_t z :3;
	u_int16_t rcode :4;
*/
} dns_flags;


// struct for dns head
typedef struct dns_header {
	u_int16_t id;
	u_int16_t flags;
	u_int16_t qdcount;
	u_int16_t ancount;
	u_int16_t nscount;
	u_int16_t arcount;
} dns_header;

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
	server(int port_num, string ip_addr, string filter_file_name);

	/**
	 * Method starts server, waits for packets and process them
	 */
	void run_server();

private:
	/**
	 * Method for opening and binding socket
	 */
	void open_and_bind_socket();

	struct sockaddr_in server_socket;
	struct sockaddr_in client_socket;
	int socket_descriptor;
	string dns_ip_addr;
	int ip_version;

	filter* f;
};

#endif // server_H

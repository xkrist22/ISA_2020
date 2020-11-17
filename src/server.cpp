#include "server.h"
#include "verbose.h"
#include "func.h"
#include "err_handler.h"
#include "client.h"
#include "filter.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

using namespace std;

server::server(int port_num, string ip_addr, string filter_file_name) {
	// save filter
	this->f = new filter(filter_file_name);

	// set ip protocol version
	if (func::valid_ip_addr(ip_addr) == IPV4) {
		this->server_socket.sin_family = AF_INET;
		this->ip_version = AF_INET;
	} else if (func::valid_ip_addr(ip_addr) == IPV6) {
		this->server_socket.sin_family = AF_INET6;
		this->ip_version = AF_INET6;
	}
	this->dns_ip_addr = ip_addr;
	
	// set interface - listening on any interface
	this->server_socket.sin_addr.s_addr = htonl(INADDR_ANY);
	this->server_socket.sin_port = htons(port_num);
	open_and_bind_socket();
}


void server::open_and_bind_socket() {
	// open socket
	if ((this->socket_descriptor = socket(this->ip_version, SOCK_DGRAM, 0)) == -1) {
		err_handler::handle_error(SERVER_SOCKET_OPEN_ERR);
	}
	verbose::print_server_state(SERVER_SOCKET_OPEN, "");
	
	// bind socket to port
	if (bind(this->socket_descriptor, (struct sockaddr *) &this->server_socket, sizeof(this->server_socket)) == -1) {
		err_handler::handle_error(SERVER_SOCKET_BIND_ERR);
	}
	verbose::print_server_state(SERVER_SOCKET_BIND, to_string(ntohs(this->server_socket.sin_port)));
}


void server::run_server() {
	socklen_t length = sizeof(this->client_socket);

	int bytes_num;
	char temp_buffer[BUFFER_SIZE];
	int sending_control_value;
	char* data;
	// recieving data
	while ((bytes_num = recvfrom(this->socket_descriptor, temp_buffer, BUFFER_SIZE, 0, (struct sockaddr *) &this->client_socket, &length)) >= 0) {
		verbose::print_server_state(SERVER_START_STATE, "");
		if (bytes_num == -1) {
			err_handler::handle_error(SERVER_RECIEVING_DATA_ERR);
			
			// send error packet TODO
			
			continue;
		}
		verbose::print_server_state(MSG_RECIEVED, inet_ntoa(this->client_socket.sin_addr));
		
		// extract header from DNS packet
		dns_header head;
		memcpy(&head, temp_buffer, HEADER_LEN);

		/*
		 * After header there is domain name. Instead of dots, there are
		 * numbers defining length of next label of domain name.
		 * With these lengths program extracts domain name
		 * If length is 0, then domain name ends!
		 */
		int stop_num = (int) temp_buffer[HEADER_LEN];
		int start_num = HEADER_LEN + 1;
		string domain_name;
		while(true) {
			int i = start_num;
			for (i; i < start_num + stop_num; i++) {
				domain_name.push_back((char) temp_buffer[i]);
			}
			// define new length
			start_num = start_num + stop_num + 1;
			stop_num = (int) temp_buffer[start_num - 1];
			// if extracted length is 0, iteration ends
			if (stop_num == 0) {
				break;
			}
			// add dot after label
			domain_name.push_back('.');
		}

		// check if query is A type
		int type = (int) temp_buffer[start_num + 1];
		if (type != TYPE_A) {
			// send not implemented dns packet
			verbose::print_server_state(MSG_TYPE_NOT_IMPLEMENTED, domain_name);
			
			// answering the questions
			

			// after sending packet, wait for another dns packet
			continue;
		}

		// check if domain name is in filter
		if (this->f->should_be_filtered(domain_name)) {
			verbose::print_server_state(MSG_FILTERED, domain_name);
			
			// after sending refused packet, wait for another dns packet
			continue;
		} else {
			// resend question
			client c = client(DNS_PORT_NUM, this->dns_ip_addr);
			char* data_buffer;
			int ret_len;
			data_buffer = c.send_data(temp_buffer, &ret_len);
			c.close_socket();
			strcpy(temp_buffer, data_buffer);

			// answering the questions
			sending_control_value = sendto(this->socket_descriptor, data_buffer, BUFFER_SIZE, 0, (struct sockaddr *) &this->client_socket, length);

			// checking if answer was send
			if (sending_control_value == -1) {
				err_handler::handle_error(SERVER_CANNOT_SEND_DATA_ERR);
			} else if (sending_control_value != bytes_num) {
				err_handler::handle_error(SERVER_SEND_DATA_PARTIALLY_ERR);
			} else {
				verbose::print_server_state(MSG_SENT, inet_ntoa(this->client_socket.sin_addr));
			}
		}

		strcpy(temp_buffer, "\0");
	}
	// close server socket
	close(this->socket_descriptor);
	verbose::print_terminating();
	err_handler::handle_error(SERVER_INPUT_DATA_ERR);
}


void parse_msg() {
	;
}

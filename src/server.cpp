#include "server.h"
#include "verbose.h"
#include "func.h"
#include "err_handler.h"

using namespace std;

server::server(int port_num, string ip_addr) {
	// set ip protocol version
	if (func::valid_ip_addr(ip_addr) == IPV4) {
		this->server_socket.sin_family = AF_INET;
		this->ip_version = AF_INET;
	} else if (func::valid_ip_addr(ip_addr) == IPV6) {
		this->server_socket.sin_family = AF_INET6;
		this->ip_version = AF_INET6;
	}

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
	if (bind(this->socket_descriptor, (struct sockaddr*)&this->server_socket, sizeof(this->server_socket)) == -1) {
		err_handler::handle_error(SERVER_SOCKET_BIND_ERR);
	}
	verbose::print_server_state(SERVER_SOCKET_BIND, to_string(ntohs(this->server_socket.sin_port)));
}


void server::run_server() {
	socklen_t length = sizeof(this->client_socket);
	int bytes_num;
	char temp_buffer[BUFFER_SIZE];
	int sending_control_value;
	while ((bytes_num = recvfrom(this->socket_descriptor, temp_buffer, BUFFER_SIZE, 0, (struct sockaddr*)&this->client_socket, &length)) >= 0) {
		verbose::print_server_state(MSG_RECIEVED, inet_ntoa(this->client_socket.sin_addr));
		sending_control_value = sendto(this->socket_descriptor, temp_buffer, bytes_num, 0, (struct sockaddr*)&this->client_socket, length);
		if (sending_control_value == -1) {
			err_handler::handle_error(SERVER_CANNOT_SEND_DATA_ERR);
		} else if (sending_control_value != bytes_num) {
			err_handler::handle_error(SERVER_SEND_DATA_PARTIALLY_ERR);
		} else {
			verbose::print_server_state(MSG_SENT, inet_ntoa(this->client_socket.sin_addr));
		}
	}
	// close server socket
	close(this->socket_descriptor);
	verbose::print_terminating();
	err_handler::handle_error(SERVER_INPUT_DATA_ERR);
}
	

void parse_msg() {
	;
}

#include "err_handler.h"
#include "func.h"
#include "verbose.h"
#include "client.h"


using namespace std;

client::client(int port_num, string ip_addr) {
	// clean server socket
	memset(&this->server_socket, 0, sizeof(this->server_socket));

	// set ip protocol version
	if (func::valid_ip_addr(ip_addr) == IPV4) {
		this->server_socket.sin_family = AF_INET;
		this->ip_version = AF_INET;
	} else if (func::valid_ip_addr(ip_addr) == IPV6) {
		this->server_socket.sin_family = AF_INET6;
		this->ip_version = AF_INET6;
	}


	// loads IP address into hostent structure
	if ((serverent = gethostbyname(ip_addr.c_str())) == NULL) {
		err_handler::handle_error(IP_OR_DOMAIN_NAME_ERR);
	}

	// set IP address to server socket
	memcpy(&this->server_socket.sin_addr, this->serverent->h_addr, this->serverent->h_length);

	// set server port
	this->server_socket.sin_port = htons(port_num);

	open_and_connect_socket();
}


void client::open_and_connect_socket() {
	// create socket
	if ((this->socket_descriptor = socket(AF_INET, SOCK_DGRAM , 0)) == -1) {
		err_handler::handle_error(CLIENT_SOCKET_OPEN_ERR);
	}
	verbose::print_client_state(CLIENT_SOCKET_OPEN, "");

	// create UDP packet
	if (connect(this->socket_descriptor, (struct sockaddr *)&this->server_socket, sizeof(this->server_socket))  == -1) {
		err_handler::handle_error(CLIENT_SOCKET_CONNECT_ERR);
	}
	verbose::print_client_state(CLIENT_SOCKET_CONNECT, "");
}


char* client::send_data(char data[BUFFER_SIZE], int *ret_size) {
	socklen_t len = sizeof(this->server_socket);
	static char temp_buffer[BUFFER_SIZE];
	strcpy(temp_buffer, data);
	// send data to server
	int i = sendto(this->socket_descriptor, temp_buffer, sizeof(temp_buffer), 0, (struct sockaddr*) &this->server_socket, len);

	if (getsockname(this->socket_descriptor,(struct sockaddr*) &this->local_socket, &len) == -1) {
		err_handler::handle_error(SOCK_NAME_ERR);
		return "";
	}


	// check if data was sent correctly
	if (i == -1) {
		err_handler::handle_error(CLIENT_CANNOT_SEND_DATA_ERR);
		return "";

	} else if (i != sizeof(temp_buffer)) {
		err_handler::handle_error(CLIENT_SEND_DATA_PARTIALLY_ERR);
		return "";
	}
	verbose::print_client_state(MSG_RESEND, "");

	if ((*ret_size = recvfrom(this->socket_descriptor, temp_buffer, BUFFER_SIZE, 0, (struct sockaddr*) &this->local_socket, &len)) == -1) {
		err_handler::handle_error(CLIENT_RECIEVING_DATA_ERROR);
		return "";
	}

	verbose::print_client_state(MSG_ANSWERED, "");
	
	return temp_buffer;
}


void client::close_socket() {
	close(this->socket_descriptor);
	verbose::print_client_state(CLIENT_SOCKET_CLOSE, "");
}


#include "verbose.h"

using namespace std;

// define value
bool verbose::is_enable = false;

void verbose::print_argparse_state(int argparse_state, string info) {
	if (!is_enable) {
		return;
	}
	if (argparse_state == FILE_NAME_SET) {
		cout << " * Filter file name set: " << info << ".\n";
	} else if (argparse_state == USER_PORT_SET) {
		cout << " * User port number set: " << info << ".\n";
	} else if (argparse_state == DNS_SERVER_IP_SET) {
		cout << " * DNS IP address set: " << info << ".\n";
	}
}

void verbose::print_filter_state(int filter_state, string info) {
	if (!is_enable) {
		return;
	}
	if (filter_state == FILE_FOUND) {
		cout << " * Filter file " << info << " found, extracting info.\n";
	} else if (filter_state == FILE_EXTRACTED) {
		cout << " * Data from filter file " << info << " extracted.\n";
	}
}


void verbose::print_server_state(int server_state, string info) {
	if (!is_enable) {
		return;
	}
	if (server_state == SERVER_SOCKET_OPEN) {
		cout << " * UDP socket opened.\n";
	} else if (server_state == SERVER_SOCKET_BIND) {
		cout << " * UDP server socket bind to port: " << info << ".\n";
	} else if (server_state == MSG_RECIEVED) {
		cout << " * server recieves message from: " << info << ".\n";
	} else if (server_state == MSG_SENT) {
		cout << " * server sends message to: " << info << ".\n";
	}
}


void verbose::print_question_state(int question_state) {
	if (!is_enable) {
		return;
	}
	if (question_state == QUESTION_FILTERED) {
		cout << "Question filtered.\n";
	} else if (question_state == QUESTION_RESEND) {
		cout << "Question resend.\n";
	} else if (question_state == QUESTION_ANSWERED) {
		cout << "Question answered\n";
	}
}


void verbose::print_terminating() {
	if (!is_enable) {
		return;
	}
	cout << " * UDP socket closed\n";
	cout << " * Terminating program\n\n";
}

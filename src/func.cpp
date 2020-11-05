#include <iostream>
#include <string>
#include <regex>
#include "func.h"

using namespace std;

int func::valid_ip_addr(string ip_addr) {
	// regex for validating IPv4
	regex ipv4_regex("(([0-9]|[1-9][0-9]|1[0-9][0-9]|2[0-4][0-9]|25[0-5])\\.){3}([0-9]|[1-9][0-9]|1[0-9][0-9]|2[0-4][0-9]|25[0-5])");
	// regex for validating IPv6
	regex ipv6_regex("((([0-9a-fA-F]){1,4})\\:){7}([0-9a-fA-F]){1,4}");
	if (regex_match(ip_addr, ipv4_regex)) {
		return IPV4;
	} else if (regex_match(ip_addr, ipv6_regex)) {
		return IPV6;
	} else {
		return 0;
	}
}


bool func::valid_domain_name(string domain_name) {
	// regex for validating domain names
	regex domain_name_regex("(?:[a-z0-9](?:[a-z0-9-]{0,61}[a-z0-9])?\\.)+[a-z0-9][a-z0-9-]{0,61}[a-z0-9]");
	if (regex_match(domain_name, domain_name_regex)) {
		return true;
	} else {
		return false;
	}
}


bool func::is_numeric_string(string str) {
	for (int i = 0; i < str.length(); i++) {
		if (str[i] < '0' || str[i] > '9') {
			return false;
		}
	}
	return true;
}

string func::trim(string str) {
	return rtrim(ltrim(str));
}


string func::ltrim(string str) {
	return regex_replace(str, regex("^\\s+"), string(""));
}


string func::rtrim(string str) {
	return regex_replace(str, regex("\\s+$"), string(""));
}

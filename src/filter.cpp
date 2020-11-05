#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include "filter.h"
#include "err_handler.h"
#include "func.h"

using namespace std;

filter::filter(string filter_file_name) {
	string line;
	// create object for reading from file
	ifstream file;
	file.open(filter_file_name);

	// check file
	if (!file.is_open()) {
		err_handler::handle_error(FILTER_FILE_NOT_EXIST_ERR);
	}

	// read lines
	while (getline(file, line)) {
		line = func::trim(line);
		// skip lines which begin with # character or are empty
		if (line == "") {
			continue;
		}
		if (line.substr(0, 1) == "#") {
			continue;
		}
		add_to_filter(line);
	}

}


void filter::add_to_filter(string domain_name) {
	domain_name_filter_data.push_back(domain_name);
}


bool filter::is_in_filter(string domain_name) {
	if (find(domain_name_filter_data.begin(), domain_name_filter_data.end(), domain_name) !=
		domain_name_filter_data.end()) {
		return true;
	} else {
		return false;
	}
}


int filter::get_filter_size() {
	return domain_name_filter_data.size();
}


bool filter::filter_exists() {
	if (domain_name_filter_data.empty()) {
		return false;
	} else {
		return true;
	}
}


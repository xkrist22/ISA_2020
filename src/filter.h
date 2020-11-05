/**
 * @file filter.h
 * @author Jiri Kristof, xkrist22
 * FIT VUT ISA project – DNS resolver
 *
 * File contains class filter
 *
 */

#ifndef filter_H
#define filter_H

#include <string>
#include <vector>

using namespace std;

class filter {
public:
	/**
	 * Constructor of the filter object
	 * @param filter_file_name name of file containing domain names to filter
	 */
	filter(string filter_file_name);

	/**
	* Method for determining if given domain name is in filter
	* @param domain_name domain name which will be search in filter
	* @return true, if given domain name is in filter, else returns false
	*/
	bool is_in_filter(string domain_name);

	/**
	 * Getter method for getting filter length
	 * @return length of filter vector data
	 */
	int get_filter_size();

	/**
	 * Method for determining if there are any domain name to filter
	 * @return true, if filter contains at least one domain name, else returns false
	 */
	bool filter_exists();

	/**
	 * Method for determining if domain should be filtered. Method checks also for subdomains
	 * @param domain_name domain name for checking
	 * @return true, if domain should be filtered, else returns false
	 */
	bool should_be_filtered(string domain_name);

private:
	// vector for storing domain names to be filtered
	vector <string> domain_name_filter_data;

	/**
	 * Method for adding domain name into filter
	 * @param domain_name domain name which should be added to filter
	 */
	void add_to_filter(string domain_name);
};

#endif // filter_H

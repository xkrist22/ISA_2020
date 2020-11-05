/**
 * @file func.h
 * @author Jiri Kristof, xkrist22
 * FIT VUT ISA project – DNS resolver
 *
 * File contains class function
 */

#ifndef func_H
#define func_H

#include <string>

/* ***************
 * VALIDITY CONSTANTS
 * ***************/
#define MIN_PORT_NUM 0
#define MAX_PORT_NUM 65535
#define MIN_ARGS_POSSIBLE 5
#define MAX_ARGS_POSSIBLE 7

/* ***************
 * INTERNAL CODES
 * ***************/
#define IPV4 4
#define IPV6 6

using namespace std;

/**
 * Class function
 *
 * class contains methods for validating values, editing strings, ...
 */
class func {
public:
	/**
	 * Method for validating given IP address
	 * @param ip_addr string containing IP address for checking
			* @return 4, if IP address is valid IPv4; 6, if IP address is valid IPv6; else returns 0
	 */
	static int valid_ip_addr(string ip_addr);

	/**
	 * Method validates format of domain name
	 * @param domain_name domain name for checking
	 * @return true, if string can represent domain name, else return false
	 */
	static bool valid_domain_name(string domain_name);

	/**
	 * Method determines, if string contains only digits, or not
	 * @param str string to be checked
	 * @return true, if string contains only numbers, else return false
	 */
	static bool is_numeric_string(string str);

	/**
	* Method for removing leading and trailing spaces
	* @param str string to be trimmed
	* @return trimmed string
	*/
	static string trim(string str);

	static string ltrim(string str);

	static string rtrim(string str);

private:
	const string WHITESPACE = " \r\t\f\v\n";
};

#endif // func_H

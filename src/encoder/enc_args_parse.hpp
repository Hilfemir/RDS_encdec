#ifndef ENC_ARGS_PARSE_HPP
#define ENC_ARGS_PARSE_HPP

#include <string>

using namespace std;

class AlternativeFrequencies {
public:
	u_int8_t f1;
	u_int8_t f2;

	/**
	* @brief Parse the input string into two floats and store them
	* in the respective variables.
	*
	* The input string must be in the format "float,float". If the
	* format is not correct, the program exits with an error message.
	*
	* @param input - input string
	*/
	void parse_input(string input);
};


class Arguments {
public:
	string group;
	u_int16_t pi;
	u_int16_t pty;
	bool tp;
	bool ms;
	bool ta;
	AlternativeFrequencies af;
	string ps;
	string rt;
	bool ab;

	/**
	* @brief Constructor
	*/
	Arguments();

	/**
 	* @brief Parse arguments
 	*
	* Parses the arguments and stores them in the respective variables.
	*
 	* @param argc - number of arguments
 	* @param argv - array of arguments
 	*/
	void parse_args(int argc, char *argv[]);

	/**
 	* @brief Print all arguments (mostly for debugging purposes)
 	*/
	void print_args();

	/**
 	* @brief Print help message and exit with code 0
 	*/
	void print_help_and_exit();

	/**
 	* @brief Check whether the arg is a flag
 	* 
 	* All flags must be provided with a value. This function is called
 	* when parsing a certain flag and checks whether there are two flags
 	* in a row.
 	*
 	* @param arg - arg following the currently parsed flag (so argv[i+1])
 	*
 	* @return true if the arg is a flag, false otherwise
 	*/
	bool is_flag(string arg);

	/**
	* @brief Get the value of the argument
	*
	* Gets the value of the argument following the currently parsed flag.
	*
	* @param argc - number of arguments
	* @param argv - array of arguments
	* @param i - index of the currently parsed argument
	*
	* @return value of the argument
	*/
	string get_arg_value(int argc, char *argv[], int &i);
	
	void check_regex(string input);
};

class ArgumentsCheck {
public:
	bool group;
	bool pi;
	bool pty;
	bool tp;
	bool ms;
	bool ta;
	bool af;
	bool ps;
	bool rt;
	bool ab;

	/**
	 * @brief Constructor
	 */
	ArgumentsCheck();

	/**
	 * @brief Check if all required arguments are provided for each
	 * respective group
	 *
	 * Exits the program with an error message if any of the required
	 * arguments are missing. Otherwise does nothing.
	 *
	 * @param group_name - group name (0A or 2A)
	 */
	void check_required(string group_name);
	
	/**
	 * @brief Check if the argument is not provided multiple times
	 *
	 * Exits the program with an error message if the argument is provided
	 * multiple times. Otherwise does nothing.
	 *
	 * @param flag - flag to check
	 */
	void check_duplicate(bool flag);
};

#endif //ENC_ARGS_PARSE_HPP

#include "utilities.hpp"

void error(int ret_code, string message) {
	if (!message.empty()) {
		cerr << "Error: " << message << endl;
	}
	exit(ret_code);
}

/*------------------------------------------------------------*/

u_int16_t str_to_uint16(string str) {
	u_int16_t result;

	try {
		int tmp = stoi(str); //convert to standard int

		//check if the value is in range
		if (tmp < 0 || tmp > 65535) {
			error(1, "Argument value out of range");
		}

		//cast to u_int16_t
		result = static_cast<u_int16_t>(tmp);
	}
	catch (...) {
		error(1, "Invalid argument value");
	}

	return result;
}

/*------------------------------------------------------------*/

bool str_to_bool(string str) {
	if (str == "1") {
		return true;
	}
	else if (str == "0") {
		return false;
	}
	else {
		error(1, "Invalid argument value");
		return false; //to suppress warning
	}
}

/*------------------------------------------------------------*/

string pad_string(string str, int length) {
	if (str.length() > length) {
		error(1, "String too long");
	}

	return str + string(length - str.length(), ' ');
}
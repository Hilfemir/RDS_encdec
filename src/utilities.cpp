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
		return false; //to suppress a warning
	}
}

/*------------------------------------------------------------*/

string pad_string(string str, u_int64_t length) {
	if (str.length() > length) {
		error(1, "String too long");
	}

	return str + string(length - str.length(), ' ');
}

/*------------------------------------------------------------*/

string calculate_crc(string input) {
	//x^10 + x^8 + x^7 + x^5 + x^4 + x^3 + 1
	string generator = "00110111001";
	int gen_length = generator.length();

	//pad the input with zeros
	string padded_input = input + string(gen_length - 1, '0');

	//calculate the remainder
	string remainder = modulo2_division(padded_input, generator);

	return remainder;
}

/*------------------------------------------------------------*/

string modulo2_division(string dividend, string divisor) {
	string remainder = dividend;

	//iterate over the dividend
	for (u_int64_t i = 0; i <= remainder.length() - divisor.length(); ++i) {
		//if the current bit is 1, perform the XOR operation
		if (remainder[i] == '1') {
			for (u_int64_t j = 0; j < divisor.length(); ++j) {
				remainder[i + j] = remainder[i + j] == divisor[j] ? '0' : '1';
			}
		}
	}

	return remainder.substr(remainder.length() - divisor.length() + 1);
}

/*------------------------------------------------------------*/

string create_checkword(string crc, string offset_type) {
	string checkword = "";
	map<string, string> offset_words = {
		{"A", "0011111100"},
		{"B", "0110011000"},
		{"C", "0101101000"},
		{"D", "0110110100"}
	};

	string block_offset = offset_words[offset_type];

	//calculate the checkword
	for (u_int64_t i = 0; i < crc.length(); i++) {
		checkword += crc[i] == block_offset[i] ? '0' : '1';
	}

	return checkword;
}
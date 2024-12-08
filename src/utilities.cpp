#include "utilities.hpp"

#include <bitset>

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

u_int16_t binstr_to_uint16(string str) {
	if (str.length() < 16) {
		//pad the string with zeros (does not affect the value)
		str = string(16 - str.length(), '0') + str;
	}
	
	bitset<16> bits(str);
	return static_cast<u_int16_t>(bits.to_ulong());
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

	//xor the CRC with the offset word
	for (u_int64_t i = 0; i < crc.length(); i++) {
		checkword += crc[i] == block_offset[i] ? '0' : '1';
	}

	return checkword;
}

/*------------------------------------------------------------*/

list<string> split_group(string group) {
	list<string> blocks = {};

	for (int i = 0; i < 4; i++) {
		string part = group.substr(i*26, 26);
		blocks.push_back(part);
	}

	return blocks;
}

/*------------------------------------------------------------*/

int block_placement(string block) {
	map<string, int> offset_positions = {
		{"A", 0},
		{"B", 1},
		{"C", 2},
		{"D", 3}
	};

	//split the block into information part and checkword part
	string info = block.substr(0, 16);
	string checkword = block.substr(16);

	//calculate the checkword for the information part
	string block_crc = calculate_crc(info);
	for (string offset_type : {"A", "B", "C", "D"}) {
		string tmp = create_checkword(block_crc, offset_type);

		//if the checkword matches the one in the block,
		//return the expected position of the block
		if (tmp == checkword) {
			return offset_positions[offset_type];
		}
	}

	//if none of the checkwords match, the block is corrupted
	error(2, "Message is corrupted (crc check failed)");
	return -1; //to suppress a warning
}

/*------------------------------------------------------------*/

void reorder_blocks(string group, string* reordered_group) {
	//split the group into 4 blocks
	list<string> blocks = split_group(group);

	//the blocks may come in a mixed order
	//in that case they will be reordered correctly
	//and stored into this array
	string final_blocks[4] = {"", "", "", ""};

	//iterate through the blocks
	for (string block : blocks) {
		//calculate crc to ensure the recieved data is correct,
		//check if the block is at the right place
		//and retrieve the correct position of the block within the group
		int index = block_placement(block);

		//check for duplicate blocks
		if (final_blocks[index] != "") {
			error(1, "Duplicate block detected (two blocks with the same crc)");
		}
		final_blocks[index] = block;

		//store the block in the reordered group
		reordered_group[index] = block;
	}
}

/*------------------------------------------------------------*/

string determine_group_type(string group) {
	map<string, string> group_types = {
		{"00000", "0A"},
		{"00100", "2A"}
	};

	//reorder the blocks
	string reordered_group[4];
	reorder_blocks(group, reordered_group);
	
	//the group type is stored at the beginning of the second block
	string type_encoded = reordered_group[1].substr(0, 5);
	try {
		return group_types.at(type_encoded);
	}
	catch (...) {
		error(1, "Unknown group type (only support group types 0A and 2A)");
		return ""; //to suppress a warning
	}
}
#include "dec_common.hpp"

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

/*------------------------------------------------------------*/

void validate_message(bool* group_recieved, int arr_size) {
	if (!group_recieved[0]) {
		error(1, "Missing part of message");
	}

	//the message will be recieved in up to 4/16 parts depending on the group type
	//however, it may be less than that if the message is shorter
	//the main idea here is that there should be no gaps in the recieved parts (group addresses)
	//examples:
	// 0 1 2 3 - correct
	// 0 1 2   - correct
	// 0 1 3   - error: missing part 2
	bool zero_encountered = false;
	for (int i = 0; i < arr_size; i++) {
		if (zero_encountered && group_recieved[i]) {
			error(1, "Missing part of message");
		}

		if (!group_recieved[i]) {
			zero_encountered = true;
		}
	}
}

/*------------------------------------------------------------*/

string create_final_message(string* message_parts, int arr_size) {
		//concatenate the parts of the message and store them in the ps variable of the first group
		string ret = "";
		for (int i = 0; i < arr_size; i++) {
			ret += message_parts[i];
		}

		//strip any trailing spaces
		ret = ret.substr(0, ret.find_last_not_of(' ') + 1);

		//add quotation marks around the message
		ret = "\"" + ret + "\"";

		return ret;
}
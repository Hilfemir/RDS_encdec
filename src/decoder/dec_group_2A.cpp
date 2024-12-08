#include "dec_group_2A.hpp"
#include "dec_common.hpp"

Group2A::Group2A() {
	pi = 0;
	gt = "";
	tp = "";
	pty = 0;
	ab = "";
	address = 0;
	rt = "";
}

/*------------------------------------------------------------*/

void Group2A::decode(string encoded_group) {
	//get the correct order of blocks
	string ordered_group[4];
	reorder_blocks(encoded_group, ordered_group);

	//decode the blocks
	decode_block0(ordered_group[0]);
	decode_block1(ordered_group[1]);
	decode_rt_block(ordered_group[2]);
	decode_rt_block(ordered_group[3]);
}

/*------------------------------------------------------------*/

void Group2A::decode_block0(string block) {
	//first block contains program identification code
	string info = block.substr(0, 16);
	pi = binstr_to_uint16(info);
}

/*------------------------------------------------------------*/

void Group2A::decode_block1(string block) {
	map<string, string> group_types = {
		{"00000", "0A"},
		{"00100", "2A"}
	};

	string info = block.substr(0, 16);

	//group type
	string encoded_group = info.substr(0, 5);
	try {
		gt = group_types.at(encoded_group);
	}
	catch (...) {
		error(1, "Unknown group type (only support group types 0A and 2A)");
	}

	//traffic program
	tp = info.substr(5, 1);

	//program type
	string encoded_pty = info.substr(6, 5);
	pty = binstr_to_uint16(encoded_pty);

	//alternative frequency flag
	ab = info.substr(11, 1);

	//address
	string encoded_address = info.substr(12, 4);
	address = binstr_to_uint16(encoded_address);

	//this should never happen but just in case
	if (address > 15) {
		error(1, "Invalid address in one of the groups");
	}
}

/*------------------------------------------------------------*/

void Group2A::decode_rt_block(string block) {
	string info = block.substr(0, 16);

	//every rt block contains 2 characters
	string enc_c1 = info.substr(0, 8);
	string enc_c2 = info.substr(8, 8);

	//convert the binary strings to characters
	char c1 = static_cast<char>(binstr_to_uint16(enc_c1));
	char c2 = static_cast<char>(binstr_to_uint16(enc_c2));

	//store the characters as one string
	rt += string(1, c1) + string(1, c2);
}

/*------------------------------------------------------------*/

void Group2A::print_info() {
	cout << "PI: " << pi << endl;
	cout << "GT: " << gt << endl;
	cout << "TP: " << tp << endl;
	cout << "PTY: " << pty << endl;
	cout << "A/B: " << ab << endl;
	cout << "RT: " << rt << endl;
}

/*------------------------------------------------------------*/

void Group2A::compare_groups(Group2A group) {
	if (pi != group.pi) {
		error(1, "PI mismatch");
	}
	if (gt != group.gt) {
		error(1, "GT mismatch");
	}
	if (tp != group.tp) {
		error(1, "TP mismatch");
	}
	if (pty != group.pty) {
		error(1, "PTY mismatch");
	}
	if (ab != group.ab) {
		error(1, "A/B flag mismatch");
	}
}

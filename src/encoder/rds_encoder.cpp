#include "enc_group_0A.hpp"

#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
	Arguments args;
	args.parse_args(argc, argv);
	string output = "";

	if (args.group == "0A") {
		//create 4 0A groups and encode them
		for (int i = 0; i < 4; i++) {
			Group0A groupA(args);
			groupA.encode_part(i);
			output += groupA.encoded_string;
		}
	}

	cout << output << endl;

	return 0;
}
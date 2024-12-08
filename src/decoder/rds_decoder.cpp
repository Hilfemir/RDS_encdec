#include <iostream>

#include "../utilities.hpp"
#include "dec_args_parse.hpp"
#include "dec_group_0A.hpp"

using namespace std;

int main(int argc, char *argv[]) {
	string input = parse_args(argc, argv);
	//int num_groups = check_input_correctness(input);

	//this group will be used to determine the type of the group
	//
	//Group0A first_group;
	//first_group.decode(input.substr(0, 104));

	string group_type = determine_group_type(input.substr(0, 104));

	if (group_type == "0A") {
		Group0A first_group;
		first_group.decode(input.substr(0, 104));
		first_group.print_info();
	}
	else if (group_type == "2A") {
		//Group2A first_group;
		//second_group.decode(input.substr(0, 104));
		//second_group.print_info();
	}
	else {
		error(1, "Invalid group type");
	}

	return 0;
}
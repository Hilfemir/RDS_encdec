#include <iostream>

#include "../utilities.hpp"
#include "dec_args_parse.hpp"

using namespace std;

int main(int argc, char *argv[]) {
	string input = parse_args(argc, argv);
	int num_groups = check_input_correctness(input);

	cout << num_groups << endl;
}
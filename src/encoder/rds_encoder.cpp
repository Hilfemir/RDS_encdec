#include "enc_args_parse.hpp"

int main(int argc, char *argv[]) {
	Arguments args;
	args.parse_args(argc, argv);

	args.print_args();

	return 0;
}
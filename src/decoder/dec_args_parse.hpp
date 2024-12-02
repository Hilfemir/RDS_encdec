#include <string>

using namespace std;

string parse_args(int argc, char *argv[]);

/**
 * @brief Check if the input is a sequence of 0s and 1s
 * and if its length is a multiple of 104 (each group is 104 bits long).
 * If any of the conditions is not met, the program will exit with an error.
 *
 * @param input The input binary string
 *
 * @return number of recieved groups
 */
int check_input_correctness(string input);
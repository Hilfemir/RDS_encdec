/**
 * @file dec_args_parse.cpp
 * @brief Implementation of the argument parsing functions for the decoder.
 * @author Michal Blazek, BUT FIT
 * @date 2024
 */

#include <iostream>

#include "../utilities.hpp"
#include "dec_args_parse.hpp"

using namespace std;

string parse_args(int argc, char *argv[]) {
    string input = "";

    if (argc > 3) {
        error(1, "Too many arguments. Use --help for more information");
    }

    if (argc <= 1) {
        error(1, "No arguments supplied. Use --help for more information");
    }

    if ((argv[1] == string("-h")) | (argv[1] == string("--help") )) {
        cout << "Usage: rds-decoder [--help] -b <b>" << endl << endl;
        cout << "Arguments:" << endl;
        cout << "-b <b> - binary string to be decoded (should be n*104 long)" << endl;
        exit(0);
    }

    if (argv[1] != string("-b")) {
        error(1, "Invalid arguments. Use --help for more information");
    }

    if (argc != 3) {
        error(1, "Must provide value for the -b flag.");
    }

    return argv[2];
}

int check_input_correctness(string input) {
    if (input.length() % 104 != 0) {
        error(1, "Input length is not a multiple of 104.");
    }

    int length = input.length(); //to suppress a warning about signed/unsigned comparison

    for (int i = 0; i < length; i++) {
        if (input[i] != '0' && input[i] != '1') {
            error(1, "The input string may only contain 0s and 1s.");
        }
    }

    return input.length() / 104;
}
/**
 * @file rds_encoder.cpp
 * @brief Main file of the encoder.
 * @author Michal Blazek, BUT FIT
 * @date 2024
 */

#include "enc_group_0A.hpp"
#include "enc_group_2A.hpp"

#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
    Arguments args;
    args.parse_args(argc, argv);
    string output = "";

    if (args.group == "0A") {
        //transfering 8 characters, 2 per group	
        //-> create 4 0A groups and encode them
        for (int i = 0; i < 4; i++) {
            Group0A groupA(args);
            groupA.encode_part(i);
            output += groupA.encoded_string;
        }
    }
    else if (args.group == "2A") {
        //transfering 64 characters, 4 per group
        //-> create 16 2A groups and encode them
        for (int i = 0; i < 16; i++) {
            Group2A groupA(args);
            groupA.encode_part(i);
            output += groupA.encoded_string;
        }
    }

    cout << output << endl;

    return 0;
}
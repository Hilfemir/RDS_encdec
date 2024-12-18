/**
 * @file dec_decoder.cpp
 * @brief Implementation of the main function for the decoder.
 * @author Michal Blazek, BUT FIT
 * @date 2024
 */

#include <iostream>

#include "../utilities.hpp"
#include "dec_args_parse.hpp"
#include "dec_group_0A.hpp"
#include "dec_group_2A.hpp"
#include "dec_common.hpp"

using namespace std;

int main(int argc, char *argv[]) {
    string input = parse_args(argc, argv);
    int num_groups = check_input_correctness(input); //number of recieved groups

    string group_type = determine_group_type(input.substr(0, 104));

    if (group_type == "0A") {
        //check if the recieved string is too long
        if (num_groups > 4) {
            error(1, "Too many groups recieved (more than 4)");
        }

        int arr_size = 4;
        //the message will be recieved in up to 4 parts
        string message[arr_size] = {"", "", "", ""};

        //used to check if the recieved groups form a valid message
        bool group_recieved[arr_size] = {false, false, false, false};

        //decode the first group
        //the first group will be used as a standard
        //to compare the rest of the groups with
        Group0A first_group;
        first_group.decode(input.substr(0, 104));
        
        //use the address as an index to the arrays above
        group_recieved[first_group.address] = true;
        message[first_group.address] = first_group.ps;

        //decode the remaining groups
        for (int i = 1; i < num_groups; i++) {
            string current_group = input.substr(i * 104, 104);
            Group0A group;
            group.decode(current_group);

            //check if the data in the group is valid (same as the first group)
            first_group.compare_groups(group);

            //check if the group is not a duplicate
            if (group_recieved[group.address]) {
                error(1, "Duplicate group detected (two groups with the same address)");
            }

            //store the part of the message and mark the group as recieved
            group_recieved[group.address] = true;
            message[group.address] = group.ps;
        }

        //check if all parts of the message were recieved
        validate_message(group_recieved, arr_size);

        //store the whole message in the ps var of the first group (so we can print it)
        first_group.ps = create_final_message(message, arr_size);

        //print the decoded info
        first_group.print_info();
    }


    else if (group_type == "2A") {
        //check if the recieved string is too long
        if (num_groups > 16) {
            error(1, "Too many groups recieved (more than 16)");
        }

        int arr_size = 16;
        //the message will be recieved in up to 4 parts
        string message[arr_size] = {"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""};

        //used to check if the recieved groups form a valid message
        bool group_recieved[arr_size] = {
            false, false, false, false, 
            false, false, false, false, 
            false, false, false, false, 
            false, false, false, false
        };

        //decode the first group
        //the first group will be used as a standard
        //to compare the rest of the groups with
        Group2A first_group;
        first_group.decode(input.substr(0, 104));

        //use the address as an index to the arrays above
        group_recieved[first_group.address] = true;
        message[first_group.address] = first_group.rt;

        //decode the remaining groups
        for (int i = 1; i < num_groups; i++) {
            string current_group = input.substr(i * 104, 104);
            Group2A group;
            group.decode(current_group);

            //check if the data in the group is valid (same as the first group)
            first_group.compare_groups(group);

            //check if the group is not a duplicate
            if (group_recieved[group.address]) {
                error(1, "Duplicate group detected (two groups with the same address)");
            }

            //store the part of the message and mark the group as recieved
            group_recieved[group.address] = true;
            message[group.address] = group.rt;
        }

        //check if all parts of the message were recieved
        validate_message(group_recieved, arr_size);

        //store the whole message in the ps var of the first group (so we can print it)
        first_group.rt = create_final_message(message, arr_size);

        //print the decoded info
        first_group.print_info();
    }
    else {
        error(1, "Invalid group type");
    }

    return 0;
}
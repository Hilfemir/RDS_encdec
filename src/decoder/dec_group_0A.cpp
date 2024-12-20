/**
 * @file dec_group_0A.cpp
 * @brief Implementation of the Group 0A decoder functions.
 * @author Michal Blazek, BUT FIT
 * @date 2024
 */

#include <iostream>
#include <list>
#include <sstream>
#include <iomanip>

#include "dec_group_0A.hpp"
#include "../utilities.hpp"
#include "dec_common.hpp"

using namespace std;

Group0A::Group0A() {
    pi = 0;
    gt = "";
    tp = "";
    pty = 0;
    ta = "";
    ms = "";
    di = "0";
    address = 0;
    af = "";
    ps = "";
}

/*------------------------------------------------------------*/

void Group0A::decode(string encoded_group) {
    //get the correct order of blocks
    string ordered_group[4];
    reorder_blocks(encoded_group, ordered_group);

    //decode the blocks
    decode_block0(ordered_group[0]);
    decode_block1(ordered_group[1]);
    decode_block2(ordered_group[2]);
    decode_block3(ordered_group[3]);
}

/*------------------------------------------------------------*/

void Group0A::decode_block0(string block) {
    //first block contains program identification code
    string info = block.substr(0, 16);
    pi = binstr_to_uint16(info);
}

/*------------------------------------------------------------*/

void Group0A::decode_block1(string block) {
    map<string, string> group_types = {
        {"00000", "0A"},
        {"00100", "2A"}
    };

    map<string, string> ta_types = {
        {"0", "Inactive"},
        {"1", "Active"}
    };

    map<string, string> ms_types = {
        {"0", "Speech"},
        {"1", "Music"}
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

    if (pty > 31) {
        error(1, "Invalid program type");
    }

    //traffic announcement
    string encoded_ta = info.substr(11, 1);
    ta = ta_types.at(encoded_ta);

    //music/speech switch
    string encoded_ms = info.substr(12, 1);
    ms = ms_types.at(encoded_ms);

    //address
    string encoded_address = info.substr(14, 2);
    address = binstr_to_uint16(encoded_address);

    //this should never happen but just in case
    if (address > 3) {
        error(1, "Invalid address in one of the groups");
    }
}

/*------------------------------------------------------------*/

void Group0A::decode_block2(string block) {
    string info = block.substr(0, 16);

    //decoding the alternative frequencies
    //a lot of the times the af are set to 0
    //so it is worth it to check for that
    if (info == "0000000000000000") {
        af = "0.0, 0.0";
    }

    else {
        //there are 2 alternative frequencies
        string encoded_af1 = info.substr(0, 8);
        string encoded_af2 = info.substr(8, 8);

        //convert the binary strings to integers
        u_int16_t uiaf1 = binstr_to_uint16(encoded_af1);
        u_int16_t uiaf2 = binstr_to_uint16(encoded_af2);

        //calculate the actual frequencies
        //(x * 10) - 875 = y -> x = (y + 875) / 10
        float faf1 = (uiaf1 + 875) / 10.0;
        float faf2 = (uiaf2 + 875) / 10.0;
        
        //cut the floats to 1 decimal place
        stringstream saf1;
        saf1 << fixed << setprecision(1) << faf1;
        stringstream saf2;
        saf2 << fixed << setprecision(1) << faf2;
        
        //store the frequencies as one string
        af = saf1.str() + ", " + saf2.str();
    }
}

/*------------------------------------------------------------*/

void Group0A::decode_block3(string block) {
    string info = block.substr(0, 16);

    //each group contains 2 characters of the program service name
    string enc_c1 = info.substr(0, 8);
    string enc_c2 = info.substr(8, 8);

    //convert the binary strings to characters
    char c1 = static_cast<char>(binstr_to_uint16(enc_c1));
    char c2 = static_cast<char>(binstr_to_uint16(enc_c2));

    //store the characters as one string
    ps = string(1, c1) + string(1, c2);
}

/*------------------------------------------------------------*/

void Group0A::print_info() {
    cout << "PI: " << pi << endl;
    cout << "GT: " << gt << endl;
    cout << "TP: " << tp << endl;
    cout << "PTY: " << pty << endl;
    cout << "TA: " << ta << endl;
    cout << "MS: " << ms << endl;
    cout << "DI: " << di << endl;
    cout << "AF: " << af << endl;
    cout << "PS: " << ps << endl;
}

/*------------------------------------------------------------*/

void Group0A::compare_groups(Group0A group) {
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
    if (ta != group.ta) {
        error(1, "TA mismatch");
    }
    if (ms != group.ms) {
        error(1, "MS mismatch");
    }
    if (di != group.di) {
        error(1, "DI mismatch");
    }
}
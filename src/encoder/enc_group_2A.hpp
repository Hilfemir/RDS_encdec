/**
 * @file enc_group_2A.hpp
 * @brief Declaration of the Group 2A encoder.
 * @author Michal Blazek, BUT FIT
 * @date 2024
 */

#ifndef ENC_GROUP_2A_HPP
#define ENC_GROUP_2A_HPP

#include "enc_args_parse.hpp"
#include <bitset>

class Group2A {
public:
    Arguments args;
    string encoded_string;
    string enc_pi;
    string enc_checkA;
    string enc_g = "00100";
    string enc_tp;
    string enc_pty;
    string enc_ab;
    string enc_addr;
    string enc_checkB;
    string enc_rt1;
    string enc_checkC;
    string enc_rt2;
    string enc_checkD;

    /**
     * @brief Constructor
     *
     * @param args - arguments
     */
    Group2A(Arguments args);

    /**
     * @brief Encode the arguments
     *
     * Encodes the arguments into a string of 104 bits.
     * The string is stored in the encoded_string variable.
     *
     * @param addr - address of the group
     */
    void encode_part(int addr);
};

#endif //ENC_GROUP_2A_HPP
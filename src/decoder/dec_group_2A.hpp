/**
 * @file dec_group_2A.hpp
 * @brief Header file for the Group 2A decoder functions.
 * @author Michal Blazek, BUT FIT
 * @date 2024
 */

#ifndef DEC_GROUP_2A_HPP
#define DEC_GROUP_2A_HPP

#include <string>

using namespace std;

class Group2A {
public:
    u_int16_t pi;
    string gt;
    string tp;
    u_int16_t pty;
    string ab;
    u_int16_t address;
    string rt;

    //constructor
    Group2A();

    void decode(string encoded_group);
    void decode_block0(string block);
    void decode_block1(string block);
    void decode_rt_block(string block); //blocks 2 and 3 contain the same type of info
    void print_info();

    /**
     * @brief compare the decoded info with another group
     *
     * If there are any differences, raise an error
     * Otherwise, do nothing
     *
     * @param group the group to compare with
     */
    void compare_groups(Group2A group);
};

#endif //DEC_GROUP_2A_HPP
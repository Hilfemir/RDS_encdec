/**
 * @file dec_group_0A.hpp
 * @brief Header file for the Group 0A decoder functions.
 * @author Michal Blazek, BUT FIT
 * @date 2024
 */

#ifndef DEC_GROUP_0A_HPP
#define DEC_GROUP_0A_HPP

#include <string>

using namespace std;

class Group0A {
public:
    u_int16_t pi;
    string gt;
    string tp;
    u_int16_t pty;
    string ta;
    string ms;
    string di;
    u_int16_t address;
    string af;
    string ps;

    //constructor
    Group0A();

    /**
     * @brief decode the group
     *
     * @param encoded_group the group to decode
     */
    void decode(string encoded_group);
    void decode_block0(string block);
    void decode_block1(string block);
    void decode_block2(string block);
    void decode_block3(string block);
    void print_info();

    /**
     * @brief compare the decoded info with another group
     *
     * If there are any differences, raise an error
     * Otherwise, do nothing
     *
     * @param group the group to compare with
     */
    void compare_groups(Group0A group);
};

#endif //DEC_GROUP_0A_HPP
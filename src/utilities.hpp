#ifndef UTILITIES_HPP
#define UTILITIES_HPP

#include <string>
#include <iostream>
#include <map>
#include <list>

using namespace std;

void error(int ret_code, string message);
u_int16_t str_to_uint16(string str);
bool str_to_bool(string str);
u_int16_t binstr_to_uint16(string str);
string pad_string(string str, u_int64_t length);
string calculate_crc(string input);
string modulo2_division(string dividend, string divisor);
string create_checkword(string crc, string offset_type);
list<string> split_group(string group);
/**
 * @brief calculate crc and determine which part of the group this block belongs to
 * 
 * @param block 26-char long binary string - one block of the currently decoded group
 *
 * @return int 0-3 - actual order of the block within the group (according to the crc)
 *
 */
int block_placement(string block);
void reorder_blocks(string group, string* reordered_group);
string determine_group_type(string group);

#endif //UTILITIES_HPP

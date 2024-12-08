#ifndef DEC_COMMON_HPP
#define DEC_COMMON_HPP

#include "../utilities.hpp"

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
void validate_message(bool* group_recieved, int arr_size);
string create_final_message(string* message_parts, int arr_size);

#endif //DEC_COMMON_HPP
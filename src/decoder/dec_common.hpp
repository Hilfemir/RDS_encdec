/**
 * @file dec_common.hpp
 * @brief Header file for the common functions for the decoder.
 * @author Michal Blazek, BUT FIT
 * @date 2024
 */

#ifndef DEC_COMMON_HPP
#define DEC_COMMON_HPP

#include "../utilities.hpp"

/**
 * @brief Split a group into its parts
 *
 * @param group The group to split
 *
 * @return A list of the parts of the group
 */
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

/**
 * @brief reorder the blocks of the group according to their order
 * 
 * @param group 4 blocks of the group
 * @param reordered_group 4 blocks of the group reordered according to their order
 *
 */
void reorder_blocks(string group, string* reordered_group);

/**
 * @brief determine the type of the group
 * 
 * @param group 4 blocks of the group
 *
 * @return string type of the group
 *
 */
string determine_group_type(string group);

/**
 * @brief validate the message
 * 
 * @param group_recieved array of booleans indicating which groups were recieved
 * @param arr_size size of the array
 *
 */
void validate_message(bool* group_recieved, int arr_size);

/**
 * @brief create the final message from the parts
 * 
 * @param message_parts array of strings containing the parts of the message
 * @param arr_size size of the array
 *
 * @return string final message
 *
 */
string create_final_message(string* message_parts, int arr_size);

#endif //DEC_COMMON_HPP
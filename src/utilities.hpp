/**
 * @file utilities.hpp
 * @brief Declaration of utility functions.
 * @author Michal Blazek, BUT FIT
 * @date 2024
 */

#ifndef UTILITIES_HPP
#define UTILITIES_HPP

#include <string>
#include <iostream>
#include <map>
#include <list>

using namespace std;

/**
 * @brief Function to print the error message and exit the program
 *
 * @param ret_code The return code to exit with
 * @param message The error message to print
 */
void error(int ret_code, string message);

/**
 * @brief Convert a string to a uint16_t
 *
 * @param str The string to convert
 *
 * @return The converted uint16_t
 */
u_int16_t str_to_uint16(string str);

/**
 * @brief Convert a string to bool
 *
 * @param str The string to convert
 *
 * @return The converted bool
 */
bool str_to_bool(string str);

/**
 * @brief Convert a binary string to a uint16_t
 *
 * @param str The binary string (a string of 0s and 1s) to convert
 *
 * @return The converted uint16_t
 */
u_int16_t binstr_to_uint16(string str);

/**
 * @brief Pad a string with whitespaces to a certain length
 *
 * @param str The string to pad
 * @param length The length to pad the string to
 *
 * @return The padded string
 */
string pad_string(string str, u_int64_t length);

/**
 * @brief Calculate the CRC of a block
 *
 * @param input The block to calculate the CRC of
 *
 * @return The CRC of the block
 */
string calculate_crc(string input);

/**
 * @brief Perform the modulo-2 division of two binary strings
 *
 * @param dividend The dividend of the division
 * @param divisor The divisor of the division
 *
 * @return The result of the division
 */
string modulo2_division(string dividend, string divisor);

/**
 * @brief Create a checkword for a block
 *
 * @param crc The CRC of the block
 * @param offset_type The type of offset word to use ('A', 'B', 'C', or 'D')
 *
 * @return The checkword for the block
 */
string create_checkword(string crc, string offset_type);

#endif //UTILITIES_HPP

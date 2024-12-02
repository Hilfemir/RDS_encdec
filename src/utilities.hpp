#ifndef UTILITIES_HPP
#define UTILITIES_HPP

#include <string>
#include <iostream>
#include <map>

using namespace std;

void error(int ret_code, string message);
u_int16_t str_to_uint16(string str);
bool str_to_bool(string str);
string pad_string(string str, u_int64_t length);
string calculate_crc(string input);
string modulo2_division(string dividend, string divisor);
string create_checkword(string crc, string offset_type);

#endif //UTILITIES_HPP

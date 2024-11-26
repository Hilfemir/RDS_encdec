#include <string>
#include <iostream>

using namespace std;

void error(int ret_code, string message);
u_int16_t str_to_uint16(string str);
bool str_to_bool(string str);
string pad_string(string str, u_int64_t length);
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

	void decode(string encoded_group);
	void decode_block0(string block);
	void decode_block1(string block);
	void decode_block2(string block);
	void decode_block3(string block);
	void decode_af(string block);
	void print_info();
};

#endif //DEC_GROUP_0A_HPP
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

	Group2A(Arguments args);

	void encode_part(int addr);
};

#endif //ENC_GROUP_2A_HPP
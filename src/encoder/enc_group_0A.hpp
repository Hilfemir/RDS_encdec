#ifndef ENC_GROUP_0A_HPP
#define ENC_GROUP_0A_HPP

#include <bitset>
#include "enc_args_parse.hpp"

class Group0A {
public:
	Arguments args;
	string encoded_string;
	string enc_pi;
	string enc_checkA;
	string enc_g = "00000";
	string enc_tp;
	string enc_pty;
	string enc_ta;
	string enc_ms;
	string enc_di = "0";
	string enc_addr;
	string enc_checkB;
	string enc_af;
	string enc_checkC;
	string enc_ps;
	string enc_checkD;

	Group0A(Arguments args);

	void encode_part(int addr);
};

#endif //ENC_GROUP_0A_HPP
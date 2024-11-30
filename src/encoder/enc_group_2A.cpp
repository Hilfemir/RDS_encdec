#include "enc_group_2A.hpp"
#include "../utilities.hpp"

Group2A::Group2A(Arguments args) {
	this->args = args;
}

void Group2A::encode_part(int addr) {
	//need to encode 4 characters per address, eg.:
	//addr = 1 -> first two chars on index 4 (addr*4) and 5 (addr*4+1)
	//         -> second two chars on index 6 (addr*4+2) and 7 (addr*4+3)
	//addr = 2 -> first two chars on index 8 (addr*4) and 9 (addr*4+1)
	//         -> second two chars on index 10 (addr*4+2) and 11 (addr*4+3)
	int adjusted_addr = addr * 4;

	//encode PI
	bitset<16> pi(args.pi);
	enc_pi = pi.to_string();

	//encode checkword A
	string crc_a = calculate_crc(enc_pi);
	enc_checkA = create_checkword(crc_a, "A");

	//encode TP
	enc_tp = args.tp ? "1" : "0";
	
	//encode PTY
	enc_pty = bitset<5>(args.pty).to_string();

	//encode AB
	enc_ab = args.ab ? "1" : "0";

	//encode address
	enc_addr = bitset<4>(addr).to_string();

	//encode checkword B
	string info_b = enc_g + enc_tp + enc_pty + enc_ab + enc_addr;
	string crc_b = calculate_crc(info_b);
	enc_checkB = create_checkword(crc_b, "B");

	//encode radiotext segment 1
	string rt1 = args.rt.substr(adjusted_addr, 2);
	enc_rt1 = "";
	for (char c : rt1) {
		unsigned char ascii_c = static_cast<unsigned char>(c);
		enc_rt1 += bitset<8>(ascii_c).to_string();
	}

	//encode checkword C
	string crc_c = calculate_crc(enc_rt1);
	enc_checkC = create_checkword(crc_c, "C");

	//encode radiotext segment 2
	string rt2 = args.rt.substr(adjusted_addr+2, 2);
	enc_rt2 = "";
	for (char c : rt2) {
		unsigned char ascii_c = static_cast<unsigned char>(c);
		enc_rt2 += bitset<8>(ascii_c).to_string();
	}

	//encode checkword D
	string crc_d = calculate_crc(enc_rt2);
	enc_checkD = create_checkword(crc_d, "D");

	//concatenate all fields
	encoded_string = enc_pi + enc_checkA + info_b + enc_checkB + enc_rt1 + enc_checkC + enc_rt2 + enc_checkD;
}
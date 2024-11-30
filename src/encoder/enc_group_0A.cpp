#include "enc_group_0A.hpp"
#include "../utilities.hpp"

Group0A::Group0A(Arguments args) {
	this->args = args;
}

void Group0A::encode_part(int addr) {
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

	//encode TA
	enc_ta = args.ta ? "1" : "0";

	//encode MS
	enc_ms = args.ms ? "1" : "0";

	//encode address
	enc_addr = bitset<2>(addr).to_string();

	//encode checkword B
	string info_b = enc_g + enc_tp + enc_pty + enc_ta + enc_ms + enc_di + enc_addr;
	string crc_b = calculate_crc(info_b);
	enc_checkB = create_checkword(crc_b, "B");

	//encode AF
	if (addr == 0) {
		enc_af = bitset<8>(args.af.f1).to_string(); //1st alt. freq.
		enc_af += bitset<8>(args.af.f2).to_string(); //append the other one
	}
	else {
		enc_af = "0000000000000000";
	}

	//encode checkword C
	string crc_c = calculate_crc(enc_af);
	enc_checkC = create_checkword(crc_c, "C");

	//encode 2 chars from the ps string corresponding to the current address
	string ps_part = args.ps.substr(addr * 2, 2);
	enc_ps = "";
	for (char c : ps_part) {
		unsigned char ascii_c = static_cast<unsigned char>(c);
		enc_ps += bitset<8>(ascii_c).to_string();
	}

	//encode checkword D
	string crc_d = calculate_crc(enc_ps);
	enc_checkD = create_checkword(crc_d, "D");

	//concatenate all fields
	encoded_string = enc_pi + enc_checkA + info_b + enc_checkB + enc_af + enc_checkC + enc_ps + enc_checkD;
	//encoded_string = enc_ps + enc_checkD;
}
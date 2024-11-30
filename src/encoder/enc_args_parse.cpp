#include "enc_args_parse.hpp"
#include "../utilities.hpp"

void AlternativeFrequencies::parse_input(string input) {
	size_t commaPos = input.find(','); //get index of the comma

	//check if the comma fas found
	if (commaPos == string::npos) {
		error(1, "Invalid alternative frequencies format");
	}

	//split the string
	string part1 = input.substr(0, commaPos);
	string part2 = input.substr(commaPos + 1);

	//convert the substrings to floats
	float ff1;
	float ff2;
	try {
		ff1 = stof(part1);
		ff2 = stof(part2);
	}
	catch (...) {
		error(1, "Invalid alternative frequencies format");
	}

	//check if the values are in the expected range
	if ((ff1 < 87.6) | (ff2 < 87.6)) {
		error(1, "The lowest allowed alternative frequency is 87.6 MHz");
	}

	if ((ff1 > 113.0) | (ff2 > 113.0)) {
		error(1, "The highest allowed alternative frequency is 113.0 MHz");
	}

	//convert the floats to u_int8_t
	f1 = (u_int8_t) ((ff1 * 10) - 875);
	f2 = (u_int8_t) ((ff2 * 10) - 875);
}

/*------------------------------------------------------------*/

Arguments::Arguments() {
	group = "";
	pi = 0;
	pty = 0;
	tp = false;
	ms = false;
	ta = false;
	af = AlternativeFrequencies();
	af.f1 = 0;
	af.f2 = 0;
	ps = "";
	rt = "";
	ab = false;
}

/*------------------------------------------------------------*/

void Arguments::parse_args(int argc, char *argv[]) {
	ArgumentsCheck args_check = ArgumentsCheck();

	if (argc > 17) {
		error(1, "Too many arguments");
	}

	if (argc <= 1) {
		error(1, "No arguments supplied. Use --help for more information");
	}
	
	string first_arg = argv[1];
	if (first_arg == "--help" || first_arg == "-h") {
		print_help_and_exit();
	}

	for (int i = 1; i < argc; i++) {
		string arg = argv[i];

		if (arg == "-g") {
			args_check.check_duplicate(args_check.group);
			args_check.group = true;

			string value = get_arg_value(argc, argv, i);
			group = value;

			if (! (group == "0A" || group == "2A")) {
				error(1, "Group (-g) must be 0A or 2A");
			}
		}

		else if (arg == "-pi") {
			args_check.check_duplicate(args_check.pi);
			args_check.pi = true;

			string value = get_arg_value(argc, argv, i);
			pi = str_to_uint16(value);
		}

		else if (arg == "-pty") {
			args_check.check_duplicate(args_check.pty);
			args_check.pty = true;

			string value = get_arg_value(argc, argv, i);
			pty = str_to_uint16(value);

			if (pty > 31) {
				error(1, "Program type (-pty) must be between 0 and 31");
			}
		}

		else if (arg == "-tp") {
			args_check.check_duplicate(args_check.tp);
			args_check.tp = true;

			string value = get_arg_value(argc, argv, i);
			tp = str_to_bool(value);
		}

		else if (arg == "-ms") {
			args_check.check_duplicate(args_check.ms);
			args_check.ms = true;

			string value = get_arg_value(argc, argv, i);
			ms = str_to_bool(value);
		}

		else if (arg == "-ta") {
			args_check.check_duplicate(args_check.ta);
			args_check.ta = true;

			string value = get_arg_value(argc, argv, i);
			ta = str_to_bool(value);
		}

		else if (arg == "-af") {
			args_check.check_duplicate(args_check.af);
			args_check.af = true;

			string value = get_arg_value(argc, argv, i);
			af.parse_input(value);
		}

		else if (arg == "-ps") {
			args_check.check_duplicate(args_check.ps);
			args_check.ps = true;

			string value = get_arg_value(argc, argv, i);
			ps = pad_string(value, 8);
		}

		else if (arg == "-rt") {
			args_check.check_duplicate(args_check.rt);
			args_check.rt = true;

			string value = get_arg_value(argc, argv, i);
			rt = pad_string(value, 64);
		}

		else if (arg == "-ab") {
			args_check.check_duplicate(args_check.ab);
			args_check.ab = true;

			string value = get_arg_value(argc, argv, i);
			ab = str_to_bool(value);
		}

		else {
			error(1, "Unknown argument " + arg);
		}
	}

	args_check.check_required(group);
}

/*------------------------------------------------------------*/

void Arguments::print_args() {
	cout << "Group: " << group << endl;
	cout << "PI: " << pi << endl;
	cout << "PTY: " << pty << endl;
	cout << "TP: " << tp << endl;
	cout << "MS: " << ms << endl;
	cout << "TA: " << ta << endl;
	cout << "AF: " << af.f1 << ", " << af.f2 << endl;
	cout << "PS: " << ps << endl;
	cout << "RT: " << rt << endl;
	cout << "AB: " << ab << endl;
}

/*------------------------------------------------------------*/

void Arguments::print_help_and_exit() {
	cout << "Usage: rds-encoder [--help] [arguments]" << endl << endl;

	cout << "Arguments:" << endl;
	cout << "-g <g> - RDS Group (either '0A' or '2A')" << endl << endl;

	cout << "Common flags for both groups:" << endl;
	cout << "-pi <pi> - Program indentification (int value 0-65535)" << endl;
	cout << "-pty <pty> - Program type (int value 0-31)" << endl << endl;

	cout << "Group 0A-specific flags:" << endl;
	cout << "-tp <tp> - Traffic Program (0 or 1)" << endl;
	cout << "-ms <ms> - Music/Speech (0=speech, 1=music)" << endl;
	cout << "-ta <ta> - Traffic Announcement (0 or 1)" << endl;
	cout << "-af <f1>,<f2> - Alternative Frequencies (float,float)" << endl;
	cout << "-ps <ps> - Program Service (max. 8-char long string)" << endl << endl;

	cout << "Group 2A-specific flags:" << endl;
	cout << "-rt <rt> - Radio Text (max. 64-char long string)" << endl;
	cout << "-ab <ab> - Radio Text A/B flag (0 or 1)" << endl << endl;

	cout << "The group argument is mandatory, so are the common flags for both groups. The group-specific flags are then all mandatory for their respective groups. Only one group can be selected and supplying flags specific for the other group will result in an error. Failing to supply all mandatory arguments will also result in an error." << endl;
	exit(0);
}

/*------------------------------------------------------------*/

bool Arguments::is_flag(string arg) {
	if (arg == "-g" || arg == "-pi" || 
	    arg == "-pty" || arg == "-tp" || 
		arg == "-ms" || arg == "-ta" || 
		arg == "-af" || arg == "-ps" || 
		arg == "-rt" || arg == "-ab") {
		return true;
	}
	else {
		return false;
	}
}

/*------------------------------------------------------------*/

string Arguments::get_arg_value(int argc, char *argv[], int &i) {
	if (i + 1 >= argc) {
		error(1, "Missing argument value");
	}

	string next_arg = argv[++i];

	if (is_flag(next_arg)) {
		error(1, "Missing argument value");
	}

	return next_arg;
}

/*------------------------------------------------------------*/

ArgumentsCheck::ArgumentsCheck() {
	group = false;
	pi = false;
	pty = false;
	tp = false;
	ms = false;
	ta = false;
	af = false;
	ps = false;
	rt = false;
	ab = false;
}

/*------------------------------------------------------------*/

void ArgumentsCheck::check_required(string group_name) {
	if (! ((group_name == "0A" && group &&
	       pi && pty &&
		   tp && ms &&
		   ta && af && 
		   ps && !rt && !ab) || 
		   (group_name == "2A" && group &&
		   pi && pty &&
		   tp && !ms &&
		   !ta && !af &&
		   !ps && rt && ab))) {
		error(1, "Invalid arguments. Use --help for more information");
	}
}

/*------------------------------------------------------------*/

void ArgumentsCheck::check_duplicate(bool flag) {
	if (flag) {
		error(1, "Duplicate argument");
	}
}
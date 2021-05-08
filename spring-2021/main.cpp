#include <iostream>
#include <fstream>
#include "State.h"

using namespace std;


int main(int argc, char **argv)
{
	if (argc > 2) {
		cerr << "Usage:\n\t" << argv[0] << "\n\t" << argv[0] << " <input_file>\n";
		exit(1);
	}

	ifstream infile;
	if (argc == 2) {
		infile.open(argv[1]);
		if (!infile.is_open()) {
			cerr << "Can't open file \"" << argv[1] << "\" for reading\n";
			exit(1);
		}
	}
	istream &in = (argc == 2)? infile : cin;
	
	Map::init();
	State state(in);
	while (state.read(in))
	{
		state.process();
		if (argc == 2) { exit(0); }
	}
}

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

#include "State.h"
#include "Solver.h"

using namespace std;

/**
 * Save humans, destroy zombies!
 **/

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
	
	State state;
	Solver solver;
	while (state.read(in))
	{
		solver.processNextState(state);
		#ifdef INPUT_FILE
		exit(0);
		#endif
	}
}

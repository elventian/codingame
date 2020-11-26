#include "Solver.h"
#include <chrono>

double getTimePassed() {
	static std::chrono::steady_clock::time_point t0;
	std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();
    double res = std::chrono::duration_cast<std::chrono::microseconds>(now - t0).count() / 1000.0;
	t0 = now;
	return res;
}

void Solver::processNextState(const State &state)
{
	std::cerr << state << std::endl;
	
	std::cout << "E" << std::endl;
}

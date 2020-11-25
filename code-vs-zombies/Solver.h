#ifndef SOLVER_H
#define SOLVER_H

#include "State.h" 

class Solver
{
public:
	void processNextState(const State &state);
private:
	void simulate(State &state) const;
};

#endif // SOLVER_H

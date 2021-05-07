#ifndef SOLVER_H
#define SOLVER_H

#include "State.h" 

class Solver
{
public:
	void processNextState(const State &state);
private:
	void minimax(const State &originState, int maxDepth = 10) const;
};

#endif // SOLVER_H

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
	getTimePassed();
	State stateCopy = state;
	simulate(stateCopy);
	Ash &ash = stateCopy.ash();
	std::list<Human *> humansToSave;
	
	for (Human *h: stateCopy.getHumans()) {
		if (h->turnsToDeath() < ash.turnsToReach(h->pos())) { continue; } //cannot save
		humansToSave.push_back(h);
	}
	
	if (humansToSave.empty()) {}
	
	humansToSave.sort(
		[](const Human *h1, const Human *h2) {
			return h1->turnsToDeath() < h2->turnsToDeath();
		}
	);
	
	Coord2 nextPos = humansToSave.empty() ? 
		state.getZombies().front()->pos() :
		humansToSave.front()->killedBy().front()->pos();
	
	std::cout << nextPos.x() << " " << nextPos.y() << std::endl;
	std::cerr << "Done in " << getTimePassed() << " ms" << std::endl;
}

void Solver::simulate(State &state) const
{
	std::list<Human *> humans = state.getHumans();
	while (!humans.empty()) {
		for (Zombie *z: state.getZombies()) {
			z->move(humans);
		}
		for (Zombie *z: state.getZombies()) {
			z->eat(humans);
		}
		
		for (auto it = humans.begin(); it != humans.end(); it++) {
			if ((*it)->dead()) {
				auto destrIt = it;
				it++;
				humans.erase(destrIt);
			}
		}
	}
}

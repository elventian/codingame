#include "Solver.h"
#include <chrono>
#include <functional>

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
	
	/*const CoordsSet &coords = state.cellsToCheck();
	if (coords.count(state.unit().pos() + Direction::offset(Direction::Right))) 
		{ std::cout << "A" << std::endl; }
	else if (coords.count(state.unit().pos() + Direction::offset(Direction::Down)))
		{ std::cout << "D" << std::endl; }
	else if (coords.count(state.unit().pos() + Direction::offset(Direction::Left)))
		{ std::cout << "E" << std::endl; }
	else  { std::cout << "C" << std::endl; }
	return;*/
	
	const CoordsSet &targetCoords = state.cellsToCheck();
	const UnitsList &enemies = state.enemies();
	const Map *map = state.map();
	CoordsSet violated;
	for (const Unit &u: enemies) {
		violated.insert(u.pos());
		for (const Coord2 &c: u.pos().getAdjacent()) {
			violated.insert(c);
		}
	}
	
	std::function<bool (CoordsList &, Coord2 &)> found = 
		[&targetCoords, this] (CoordsList &, Coord2 &coord) {
			return targetCoords.count(coord);
	};
	
	std::function<bool (CoordsList &, Coord2 &)> canPass = 
		[map, this] (CoordsList &path, Coord2 &coord) {
			(void) path;
			Cell::State cell = map->getState(coord);
			return cell == Cell::Empty;
	};
	
	std::function<std::vector<Coord2> (CoordsList &)> getAdjacent =
		[&violated] (CoordsList &path) {
		std::vector<Coord2> res;
		for (const Coord2 &c: path.back().getAdjacent()) {
			if (!violated.count(c)) {
				res.insert(res.begin(), c);
				//res.push_back(c);
			}
		}
		return res;
	};
	
	CoordsList path = state.map()->getPath(state.unit().pos(), found, canPass, getAdjacent);
	
	if (!path.empty()) {
		Coord2 nextCoord = path.front();
		Direction dir(state.unit().pos(), nextCoord);
		
		char action = 'E'; //could be done with Direction::getChar, but I don't want to change chars in lib
		if (dir == Direction(Direction::Up)) { action = 'C';}
		else if (dir == Direction(Direction::Right)) { action = 'A';}
		else if (dir == Direction(Direction::Down)) { action = 'D';}
		std::cout << action << std::endl;
	}
	else { std::cout << "B" << std::endl; }
}

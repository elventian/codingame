#include "Coord2.h"
#include <algorithm>
#include <cmath>


int Coord2::manhDist(const Coord2 &other) const {
	int dx = std::abs(x() - other.x());
	int dy = std::abs(y() - other.y());
	return dx + dy;
}


int Coord2::squaredDist(const Coord2 &other) const {
	int dx = x() - other.x();
	int dy = y() - other.y();
	return dx*dx + dy*dy;
}

int Coord2::dist(const Coord2 &other) const { 
	return sqrt(squaredDist(other)); 
}


int Coord2::chebyshevDist(const Coord2 &other) const {
	int dx = std::abs(x() - other.x());
	int dy = std::abs(y() - other.y());
	return std::max(dx, dy);
}

Coord2 Coord2::toGrid(int gridStep) const {
	Coord2 res = *this / gridStep;
	if (c[X] < 0 && (c[X] % gridStep) != 0) res.c[X]--;
	if (c[Y] < 0 && (c[Y] % gridStep) != 0) res.c[Y]--;
	return res * gridStep;
}

Coord2 Coord2::toInGrid(int gridStep) const {
	Coord2 onGrid = toGrid(gridStep);
	return *this - onGrid;
}

std::vector<Coord2> Coord2::getAdjacent() const {
	std::vector<Coord2> res;
	res.push_back(Coord2(x() - 1, y()));
	res.push_back(Coord2(x() + 1, y()));
	res.push_back(Coord2(x(), y() - 1));
	res.push_back(Coord2(x(), y() + 1));
	return res;
}


std::ostream &operator<<(std::ostream &strm, const Coord2 &coord) {
	strm << "(" << coord.x() << ", " << coord.y() << ")";
	return strm;
}


std::istream &operator>>(std::istream &strm, Coord2 &coord) {
	strm >> (int &)coord.x() >> (int &)coord.y();
	return strm;
}

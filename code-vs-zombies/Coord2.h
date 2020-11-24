#ifndef DISCRCOORD2_H
#define DISCRCOORD2_H

#include <iostream>
#include <vector>
#include <list>
#include <set>

class Coord2 {
public:
	enum Axis {	X, Y, AxesNum };
	
	Coord2() { c[X] = c[Y] = 0; }
	Coord2(int x, int y) { c[X] = x; c[Y] = y; }
	Coord2(const Coord2 &other) { *this = other; }
	
	int operator[](int axis) const { return c[axis]; }
	int &operator[](int axis) { return c[axis]; }
	int x() const { return c[X]; }
	int y() const { return c[Y]; }
	int &x() { return c[X]; }
	int &y() { return c[Y]; }
	bool operator<(const Coord2& other) const { return x() < other.x() ||
		(x() == other.x() && y() < other.y()); }
	bool operator!=(const Coord2& other) const { return x() != other.x() || y() != other.y(); }
	bool operator==(const Coord2 &other) const { return x() == other.x() && y() == other.y(); }
	Coord2 operator+(const Coord2 &other) const {
		return Coord2(x() + other.x(), y() + other.y());
	}
	Coord2 operator+=(const Coord2 &other) {
		*this = other + *this;
		return *this;
	}
	Coord2 operator-(const Coord2 &other) const {
		return Coord2(x() - other.x(), y() - other.y());
	}
	Coord2 operator+(const int n) const { return Coord2(x() + n, y() + n); }
	Coord2 operator*(int mult) const { return Coord2(x()*mult, y()*mult); }
	Coord2 operator*(const Coord2 &mult) const { return Coord2(x()*mult.x(), y()*mult.y()); }
	Coord2 operator/(int divisor) const { return Coord2(x()/divisor, y()/divisor); }
	int manhDist(const Coord2 &other) const;
	int squaredDist(const Coord2 &other) const;
	int dist(const Coord2 &other) const;
	int chebyshevDist(const Coord2 &other) const;
	Coord2 toGrid(int gridStep) const;
	Coord2 toInGrid(int gridStep) const;
	std::vector<Coord2> getAdjacent() const;
	bool isAdjacent(const Coord2 &other) const { return manhDist(other) == 1; }
	bool isInBoundaries(const Coord2 &from, const Coord2 &to) const { 
		return x()>= from.x() && y() >= from.y() && 
			   x()<= to.x() && y() <= to.y();
	}
	Coord2 &normalize() {
		if (x()) { x() = x() / abs(x()); }
		if (y()) { y() = y() / abs(y()); }
		return *this;
	}
	
	private:
		int c[AxesNum];
};


std::ostream &operator<<(std::ostream &strm, const Coord2 &coord);
std::istream &operator>>(std::istream &strm, Coord2 &coord);


typedef Coord2 Size2;
typedef std::vector<Coord2> CoordsVector;
typedef std::list<Coord2> CoordsList;
typedef std::set<Coord2> CoordsSet;


#endif // DISCRCOORD2_H

#ifndef UNIT_H
#define UNIT_H

#include "Coord2.h"

class Unit {
public:
	Unit(const Coord2 &pos): m_pos(pos) {}
protected:
	Coord2 m_pos;
};

#endif // UNIT_H

#ifndef UNIT_H
#define UNIT_H

#include "Coord2.h"

class Unit 
{
public:
	Unit(int id = 0, int x = 0, int y = 0) { 
		m_id = id;
		m_pos = Coord2(x, y); 
	}
	const Coord2 &pos() const { return m_pos; }
	int id() const { return m_id; }
protected:
	Coord2 m_pos;
	int m_id;
};

#endif // UNIT_H

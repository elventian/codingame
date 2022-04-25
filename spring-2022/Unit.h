#ifndef UNIT_H
#define UNIT_H

#include "Coord2.h"
class Monster;

class Unit
{
public:
	Unit(int id, Coord2 pos, int shieldTime, bool isControlled):
		m_id(id), m_pos(pos), m_shieldTime(shieldTime), m_isControlled(isControlled) {}
	const Coord2 &pos() const { return m_pos; }
	int distance(const Monster *monster) const;
protected:
	int m_id;
	Coord2 m_pos;
	int m_shieldTime; //Count down until shield spell fades
	bool m_isControlled; //Is entity under a control spell
};

#endif // UNIT_H

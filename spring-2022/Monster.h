#ifndef MONSTER_H
#define MONSTER_H

#include "Coord2.h"

class Monster
{
public:
	Monster(int id, Coord2 pos, int hp, Coord2 trajectory, bool isNearBase, bool isThreatForMyBase, bool isThreatForOpBase):
		m_id(id), m_pos(pos), m_health(hp), m_trajectory(trajectory), m_isNearBase(isNearBase),
		m_isThreatForMyBase(isThreatForMyBase), m_isThreatForOpBase(isThreatForOpBase) {}
	const Coord2 &pos() const { return m_pos; }
protected:
	int m_id;
	Coord2 m_pos;
	int m_health;
	Coord2 m_trajectory;
	bool m_isNearBase;
	bool m_isThreatForMyBase;
	bool m_isThreatForOpBase;
};

#endif // MONSTER_H

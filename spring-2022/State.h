#ifndef STATE_H
#define STATE_H

#include <fstream>
#include "Coord2.h"
class Unit;
class Monster;

class State
{
public:
	State(std::istream &in);
	void read(std::istream &in);
	void process();
protected:
	const Coord2 mapSize = Coord2(17630, 900);
	Coord2 m_base;
	Coord2 m_opbase;
	int m_health;
	int m_mana;
	int m_ophealth;
	int m_opmana;
	int m_unitsNum;
	std::vector<Unit *> m_units;
	std::vector<Unit *> m_opunits;
	std::vector<Monster *> m_monsters;
	
	void clear();
	void applyOffenceStrategy(Unit *unit);
	void applyDefenceStrategy(Unit *unit);
};

#endif // STATE_H

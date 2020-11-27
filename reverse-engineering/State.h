#ifndef STATE_H
#define STATE_H

#include <iostream>
#include <list>
#include "Unit.h"
#include "Map.h"

class State
{
	friend std::ostream &operator<<(std::ostream &out, const State &state);
public:
	State() {}
	~State() { 
		clear(); 
		delete m_map;
	}
	
	bool read(std::istream &in);
	const Map *map() const { return m_map; }
	const Unit &unit() const { return m_unit; }
	const CoordsSet &cellsToCheck() const { return m_needCheck; }
	const UnitsList &enemies() const { return m_enemies; }
	
protected:
	void clear();
	
	int m_unitsNum = 0;
	Map *m_map;
	Unit m_unit;
	UnitsList m_enemies;
	CoordsSet m_needCheck;
	CoordsSet m_checked;
	CoordsSet m_empty;
};

#endif // STATE_H

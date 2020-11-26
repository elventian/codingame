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
	
protected:
	void clear();
	
	int m_unitsNum = 0;
	Map *m_map;
	Unit m_unit;
	std::list<Unit> m_enemies;
};

#endif // STATE_H

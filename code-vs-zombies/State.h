#ifndef STATE_H
#define STATE_H

#include <iostream>
#include <list>
#include "Unit.h"

class State
{
public:
	State() {}
	~State() { clear(); }
	State(const State &other);
	
	bool read(std::istream &in);
	const std::list<Zombie *> &getZombies() const { return m_zombies; }	
	std::list<Zombie *> &getZombies() { return m_zombies; }	
	const std::list<Human *> &getHumans() const { return m_humans; }
	std::list<Human *> &getHumans() { return m_humans; }
	const Unit &ash() const { return m_ash; }
	Ash &ash() { return m_ash; }
	
protected:
	Ash m_ash;
	std::list<Zombie *> m_zombies;
	std::list<Human *> m_humans;
	
	void clear();
};

#endif // STATE_H

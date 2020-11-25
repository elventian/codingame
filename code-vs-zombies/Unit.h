#ifndef UNIT_H
#define UNIT_H

#include "Coord2.h"

class Zombie;
class Human;

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
	int m_speed = 0;
};

class Zombie: public Unit 
{
	using Unit::Unit;
public:
	void move(const std::list<Human *> &units);
	void eat(std::list<Human *> &units);
private:
	std::list<Coord2> m_path;
	const int m_speed = 400;
};

class Human: public Unit 
{
	using Unit::Unit;
public:
	void setEatenBy(Zombie *zombie, int turnId) {
		m_killedBy.push_back(zombie);
		m_turnOfDeath = turnId;
	}
	bool dead() { return m_turnOfDeath != 0; }
	int turnsToDeath() const { return m_turnOfDeath; }
	const std::list<Zombie *> &killedBy() const { return m_killedBy; }
private:
	std::list<Zombie *> m_killedBy;
	int m_turnOfDeath = 0;
};

class Ash: public Unit
{
	using Unit::Unit;
public:
	Ash(int x = 0, int y = 0) : Unit(-1, x, y) {}
	int turnsToReach(const Coord2 &point) const;
protected:
	static const int m_speed = 2000;
	static const int m_shotRange = 1000;
};

#endif // UNIT_H

#include "State.h"

State::State(const State &other)
{
	for (Zombie *z: other.m_zombies) {
		m_zombies.push_back(new Zombie(*z));
	}
	
	for (Human *u: other.m_humans) {
		m_humans.push_back(new Human(*u));
	}
}

bool State::read(std::istream &in)
{
	clear();
	
	int x;
	int y;
	in >> x >> y; in.ignore();
	std::cerr << x << " " << y << std::endl;
	m_ash = Ash(x, y);
	int humanCount;
	in >> humanCount; in.ignore();
	std::cerr << humanCount << std::endl;
	for (int i = 0; i < humanCount; i++) {
		int humanId;
		int humanX;
		int humanY;
		in >> humanId >> humanX >> humanY; in.ignore();
		std::cerr << humanId << " " << humanX << " " << humanY << std::endl;
		Human *human = new Human(humanId, humanX, humanY);
		m_humans.push_back(human);
	}
	int zombieCount;
	in >> zombieCount; in.ignore();
	std::cerr << zombieCount << std::endl;
	for (int i = 0; i < zombieCount; i++) {
		int zombieId;
		int zombieX;
		int zombieY;
		int zombieXNext;
		int zombieYNext;
		in >> zombieId >> zombieX >> zombieY >> zombieXNext >> zombieYNext; in.ignore();
		std::cerr << zombieId << " " << zombieX << " " << zombieY << " " <<
			zombieXNext << " " << zombieYNext << std::endl;
		Zombie *zombie = new Zombie(zombieId, zombieXNext, zombieYNext);
		m_zombies.push_back(zombie);
	}
	return true;
}

void State::clear()
{
	for (Zombie *z: m_zombies) { delete z; }
	for (Unit *u: m_humans) { delete u; }
	m_zombies.clear();
	m_humans.clear();
}





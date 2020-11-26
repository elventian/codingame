#include "State.h"

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>


bool State::read(std::istream &in)
{
	static bool firstCall = true;
	int mapWidth, mapHeight;
	
	if (firstCall) {
		firstCall = false;
		
		in >> mapHeight; in.ignore();
		in >> mapWidth; in.ignore();
		in >> m_unitsNum; in.ignore();
		m_map = new Map(mapWidth, mapHeight);
	}
	else {
		mapHeight = m_map->getSize().y(); mapWidth = m_map->getSize().x();
	}
	
	clear();

	std::string wallU, wallR, wallD, wallL;
	in >> wallU; in.ignore();
	in >> wallR; in.ignore();
	in >> wallD; in.ignore();
	in >> wallL; in.ignore();
	
	std::cerr << mapHeight << std::endl << mapWidth << std::endl << m_unitsNum << std::endl;
	std::cerr << wallU << std::endl << wallR << std::endl << wallD << std::endl << wallL << std::endl;	
	
	for (int i = 0; i < m_unitsNum; i++) {
		int unitX, unitY;
		in >> unitX >> unitY; in.ignore();
		std::cerr << unitX << " " << unitY << std::endl;
		
		Unit unit(i, unitX, unitY);
		
		if (i == m_unitsNum - 1) {
			m_unit = unit;
		}
		else {
			m_enemies.push_back(unit);
		}
		m_map->setState(unit.pos(), Cell::Empty);
	}
	
	m_map->setState(m_unit.pos() + Direction::offset(Direction::Up), Cell::stateFromStr(wallU));
	m_map->setState(m_unit.pos() + Direction::offset(Direction::Right), Cell::stateFromStr(wallR));
	m_map->setState(m_unit.pos() + Direction::offset(Direction::Down), Cell::stateFromStr(wallD));
	m_map->setState(m_unit.pos() + Direction::offset(Direction::Left), Cell::stateFromStr(wallL));
	
	return true;
}
	
void State::clear()
{
	m_enemies.clear();
}
	
std::ostream &operator<<(std::ostream &out, const State &state)
{
	for (int y = state.m_map->getSize().y() - 1; y >= 0; y--) {
		for (int x = 0; x < state.m_map->getSize().x(); x++) {
			Cell::State cell = state.m_map->getState(Coord2(x, y));
			if (cell == Cell::Wall) { out << "█"; }
			else if (cell == Cell::Empty) { out << " "; }
			else { out << "░";}
		}
		out << std::endl;
	}
	return out;
}

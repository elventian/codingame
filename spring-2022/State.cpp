#include "State.h"
#include "Monster.h"
#include "Unit.h"
#include <iostream>
#include <algorithm>

State::State(std::istream &in)
{
	int base_x; // The corner of the map representing your base
	int base_y;
	in >> base_x >> base_y; in.ignore();
	std::cerr << base_x << " " << base_y << std::endl;
	m_base = Coord2(base_x, base_y);
	m_opbase = mapSize - m_base;
	in >> m_unitsNum; in.ignore();
	std::cerr << m_unitsNum << std::endl;
}

void State::read(std::istream &in)
{
	clear();
	std::cerr << m_base.x() << " " << m_base.y() << std::endl;
	std::cerr << m_unitsNum << std::endl;
	in >> m_health >> m_mana; in.ignore();
	std::cerr << m_health << " " << m_mana << std::endl;
	in >> m_ophealth >> m_opmana; in.ignore();
	std::cerr << m_ophealth << " " << m_opmana << std::endl;
	int entity_count; // Amount of heros and monsters you can see
	in >> entity_count; in.ignore();
	std::cerr << entity_count << std::endl;
	
	for (int i = 0; i < entity_count; i++) {
		int id; // Unique identifier
		int type; // 0=monster, 1=your hero, 2=opponent hero
		int x; // Position of this entity
		int y;
		int shield_life; // Ignore for this league; Count down until shield spell fades
		int is_controlled; // Ignore for this league; Equals 1 when this entity is under a control spell
		int health; // Remaining health of this monster
		int vx; // Trajectory of this monster
		int vy;
		int near_base; // 0=monster with no target yet, 1=monster targeting a base
		int threat_for; // Given this monster's trajectory, is it a threat to 1=your base, 2=your opponent's base, 0=neither
		in >> id >> type >> x >> y >> shield_life >> is_controlled >> health >> vx >> vy >> near_base >> threat_for; in.ignore();
		std::cerr << id << " " << type << " " <<  x  << " " << y << " " << shield_life << " " << 
			is_controlled << " " << health << " " << vx << " " << vy << " " << near_base << " " << 
			threat_for << std::endl;
		if (type == 0) {
			Monster *monster = new Monster(id, Coord2(x,y), health, Coord2(vx,vy), near_base, threat_for == 1, threat_for == 2);
			m_monsters.push_back(monster);
		}
		else {
			Unit *unit = new Unit(id, Coord2(x,y), shield_life, is_controlled);
			if (type == 1) { m_units.push_back(unit); }
			else { m_opunits.push_back(unit); }
		}
	}
}

void State::process()
{
	std::sort(m_monsters.begin(), m_monsters.end(), [this] (Monster *m1, Monster *m2) {
		return m1->pos().squaredDist(m_base) < m2->pos().squaredDist(m_base);
	});

	for (int i = 0; i < m_unitsNum; i++) {
		bool action_done = false;
		if (m_monsters.empty()) { std::cout << "WAIT" << std::endl; action_done = true; }
		else if (m_mana >= 10) {
			for (Monster *m: m_monsters) {
				if (m_units[i]->distance(m) <= 1280) {
					std::cout << "SPELL WIND " << m_opbase.x() << " " << m_opbase.y() << std::endl;
					m_mana -= 10;
					action_done = true;
					break;
				}
			}
		}
		if (!action_done) { 
			std::cout << "MOVE " << m_monsters.front()->pos().x() << " " << m_monsters.front()->pos().y() << std::endl;
			m_monsters.erase(m_monsters.begin());
			action_done = true;
		}
	}
}

void State::clear()
{
	for (Unit *u: m_units) { delete u; }
	for (Unit *u: m_opunits) { delete u; }
	for (Monster *m: m_monsters) { delete m; }
	m_units.clear();
	m_opunits.clear();
	m_monsters.clear();
}

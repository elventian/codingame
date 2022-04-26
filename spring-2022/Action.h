#ifndef ACTION_H
#define ACTION_H

#include <string>
#include <list>
#include "Coord2.h"

class Action
{
public:
	enum Type { Wait, Move, Wind, Control, Shield, ActionsNum };
	
	Action() { m_type = Wait; }
	Action(Type type, const Coord2 &pos) : m_type(type), m_pos(pos) {}
	Action(Type type, int id) : m_type(type), m_target(id) {}
	Action(Type type, const Coord2 &pos, int id) : m_type(type), m_pos(pos), m_target(id) {}
	
	std::string toStr() const {
		switch (m_type) {
			case Move: return "MOVE " + std::to_string(m_pos.x()) + " " + std::to_string(m_pos.y());
			case Wind: return "SPELL WIND " + std::to_string(m_pos.x()) + " " + std::to_string(m_pos.y());
			case Control: return "SPELL CONTROL " + std::to_string(m_target) + " " + 
				std::to_string(m_pos.x()) + " " + std::to_string(m_pos.y());
			case Shield: return "SPELL SHIELD " + std::to_string(m_target);
			default: return "WAIT";
		}
	}
	
	Type type() const { return m_type; }
	
	static int applyRange(Type type) {
		switch (type) {
			case Move: return 800;
			case Wind: return 1280;
			case Shield: return 2200;
			case Control: return 2200;
			default: return -1;
		}
	}
	
private:
	Type m_type;
	Coord2 m_pos;
	int m_target;
};

typedef std::list<Action> ActionsList;

#endif // ACTION_H






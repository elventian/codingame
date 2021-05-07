#ifndef ACTION_H
#define ACTION_H

#include "Direction.h"

class Action 
{
public:
	Action(const Direction &dir = Direction::NoDir): m_dir(dir) {}
	char toChar() const {
		char action = 'E';
		if (m_dir == Direction(Direction::Up)) { action = 'C';}
		else if (m_dir == Direction(Direction::Right)) { action = 'A';}
		else if (m_dir == Direction(Direction::Down)) { action = 'D';}
		return action;
	}
private:
	Direction m_dir;
};

#endif // ACTION_H

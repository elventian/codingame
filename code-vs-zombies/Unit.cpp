#include "Unit.h"
#include "Line2.h"
#include <limits>

void Zombie::move(const std::list<Human *> &units)
{
	auto closest = units.begin();
	int minDist = std::numeric_limits<int>::max();
	for (auto it = units.begin(); it != units.end(); it++) {
		int dist = m_pos.squaredDist((*it)->pos());
		if (dist < minDist) {
			minDist = dist;
			closest = it;
		}
	}
	Line2 step(m_pos, (*closest)->pos());
	m_pos = step.getPointAt(m_speed);
	m_path.push_back(m_pos);
	#ifdef INPUT_FILE
	std::cerr << "Zombie "<< m_id << " moves to human " << (*closest)->id() << " " << pos() << std::endl;
	#endif
}

void Zombie::eat(std::list<Human *> &units)
{
	for (Human *h: units) {
		if (m_pos.dist(h->pos()) <= m_speed) {
			int turnId = m_path.size() + 2;
			h->setEatenBy(this, turnId);
			#ifdef INPUT_FILE
			std::cerr << turnId << ": Human " << h->id() << " destroyed" << std::endl;
			#endif
		}
	}
}

int Ash::turnsToReach(const Coord2 &point) const
{
	return round(sqrt(m_pos.squaredDist(point)) / m_speed);
}

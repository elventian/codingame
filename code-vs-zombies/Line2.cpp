#include "Line2.h"

Coord2 Line2::getPointAt(int offsetFromStart) const
{
	Coord2 delta = m_p[1] - m_p[0];
	if (delta == Coord2(0, 0)) { return m_p[0]; }
	
	double length = len();	
	return m_p[0] + Coord2(delta.x() * offsetFromStart / length, delta.y() * offsetFromStart / length);
}


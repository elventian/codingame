#ifndef LINE2_H
#define LINE2_H

#include "Coord2.h"
#include <math.h>

class Line2 
{
public:
	Line2(const Coord2 &p1 = Coord2(), const Coord2 &p2 = Coord2()) { m_p[0] = p1; m_p[1] = p2; }
	Coord2 getPointAt(int offsetFromStart) const;
	double len() const { return sqrt(m_p[0].squaredDist(m_p[1]));}
	
private:
	Coord2 m_p[2];
};

#endif // LINE2_H

#include "Unit.h"
#include "Monster.h"

int Unit::distance(const Monster *monster) const
{
	return monster->pos().dist(pos());
}

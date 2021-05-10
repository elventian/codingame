#ifndef CELL_H
#define CELL_H

#include <vector>
#include <cstring>
#include "Hex.h"
#include "Tree.h"

class Cell: public Hex
{
public:
	Cell(int id = 0, int q = 0, int r = 0) : Hex(q, r), m_id(id) {}
	void clear() { 
		memset(m_shadowPower, 0, sizeof(m_shadowPower));
	}
	int id() const { return m_id; }
	int richness() const { return m_richness; }
	int richnessPoints() const { return 2 * (m_richness - 1); }
	void setRichness(int richness) { m_richness = richness;	}
	int shadowPower(Dir dir) const { return m_shadowPower[dir];	}
	void setShadowPower(Dir dir, int shadowPower) { m_shadowPower[dir] = shadowPower; }
	
private:
	int m_id;
	int m_richness;
	int m_shadowPower[DirsNum];
};

typedef std::vector<Cell> CellVector;

#endif // CELL_H

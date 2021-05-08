#ifndef CELL_H
#define CELL_H

#include <vector>
#include "Hex.h"
#include "Tree.h"

class Cell: public Hex
{
public:
	Cell(int id = 0, int q = 0, int r = 0) : Hex(q, r), m_id(id), m_tree(nullptr) {}
	void clear() { 
		m_tree = nullptr; 
		m_shadowPower = 0;
	}
	int id() const { return m_id; }
	int richness() const { return m_richness; }
	void setRichness(int richness) { m_richness = richness;	}
	Tree *tree() const { return m_tree; }
	void addTree(Tree *tree) { m_tree = tree; }
	
	int shadowPower() const { return m_shadowPower;	}
	void setShadowPower(int shadowPower) { m_shadowPower = shadowPower; }
	
private:
	int m_id;
	int m_richness;
	int m_shadowPower;
	Tree *m_tree;
};

typedef std::vector<Cell> CellVector;

#endif // CELL_H

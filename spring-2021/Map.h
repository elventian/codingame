#ifndef MAP_H
#define MAP_H

#include "Cell.h"
#include <map>

class Map
{
public:
	Map();
	void clear();
	Cell &operator[](int index) { return m_cells[index]; }
	Cell &operator[](Hex hexCoord) { return m_cells[m_cellIdByCoord[hexCoord]]; }
	CellVector::iterator begin() { return m_cells.begin(); }
	CellVector::iterator end() { return m_cells.end(); }
	int size() const { return m_cells.size(); }
	void updateShadows(Hex::Dir sunDir);
private:
	CellVector m_cells;
	std::map<Hex, int> m_cellIdByCoord;
};

#endif // MAP_H

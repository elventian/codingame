#ifndef MAP_H
#define MAP_H

#include "Cell.h"

class Map
{
public:
	Map();
	void clear();
	Cell &operator[](int index) { return m_cells[index]; }
	CellVector::iterator begin() { return m_cells.begin(); }
	CellVector::iterator end() { return m_cells.end(); }
	int size() const { return m_cells.size(); }
private:
	CellVector m_cells;
};

#endif // MAP_H

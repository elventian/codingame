#ifndef MAP_H
#define MAP_H

#include "Cell.h"
#include <map>

class Map
{
public:
	Map();
	static void init();
	void clear();
	Cell &operator[](int index) { return m_cells[index]; }
	const Cell &operator[](int index) const { return m_cells[index]; }
	Cell &operator[](Hex hexCoord) { return m_cells[m_cellIdByCoord[hexCoord]]; }
	const Cell &operator[](Hex hexCoord) const { return m_cells[m_cellIdByCoord[hexCoord]]; }
	int indexByHex(Hex hexCoord) const { return m_cellIdByCoord[hexCoord]; }
	CellVector::iterator begin() { return m_cells.begin(); }
	CellVector::iterator end() { return m_cells.end(); }
	int size() const { return m_cells.size(); }
	void updateShadows();
	int sunPoints(const Tree *tree, Hex::Dir dir) const;
	HexList seedCells(const Tree *tree) const;
private:
	CellVector m_cells;
	static std::map<Hex, int> m_cellIdByCoord;
	bool contains(Hex hexCoord) const { return m_cellIdByCoord.count(hexCoord); }
};

#endif // MAP_H

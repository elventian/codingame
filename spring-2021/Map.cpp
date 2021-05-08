#include "Map.h"

Map::Map()
{
	m_cellIdByCoord[Hex(0, 0)] = 0;
	m_cellIdByCoord[Hex(0, 1)] = 1;
	m_cellIdByCoord[Hex(-1, 1)] = 2;
	m_cellIdByCoord[Hex(-1, 0)] = 3;
	m_cellIdByCoord[Hex(0, -1)] = 4;
	m_cellIdByCoord[Hex(1, -1)] = 5;
	m_cellIdByCoord[Hex(1, 0)] = 6;
	m_cellIdByCoord[Hex(0, 2)] = 7;
	m_cellIdByCoord[Hex(-1, 2)] = 8;
	m_cellIdByCoord[Hex(-2, 2)] = 9;
	m_cellIdByCoord[Hex(-2, 1)] = 10;
	m_cellIdByCoord[Hex(-2, 0)] = 11;
	m_cellIdByCoord[Hex(-1, -1)] = 12;
	m_cellIdByCoord[Hex(0, -2)] = 13;
	m_cellIdByCoord[Hex(1, -2)] = 14;
	m_cellIdByCoord[Hex(2, -2)] = 15;
	m_cellIdByCoord[Hex(2, -1)] = 16;
	m_cellIdByCoord[Hex(2, 0)] = 17;
	m_cellIdByCoord[Hex(1, 1)] = 18;
	m_cellIdByCoord[Hex(1, 2)] = 19;
	m_cellIdByCoord[Hex(0, 3)] = 20;
	m_cellIdByCoord[Hex(-1, 3)] = 21;
	m_cellIdByCoord[Hex(-2, 3)] = 22;
	m_cellIdByCoord[Hex(-3, 3)] = 23;
	m_cellIdByCoord[Hex(-3, 2)] = 24;
	m_cellIdByCoord[Hex(-3, 1)] = 25;
	m_cellIdByCoord[Hex(-3, 0)] = 26;
	m_cellIdByCoord[Hex(-2, -1)] = 27;
	m_cellIdByCoord[Hex(-1, -2)] = 28;
	m_cellIdByCoord[Hex(0, -3)] = 29;
	m_cellIdByCoord[Hex(1, -3)] = 30;
	m_cellIdByCoord[Hex(2, -3)] = 31;
	m_cellIdByCoord[Hex(3, -3)] = 32;
	m_cellIdByCoord[Hex(3, -2)] = 33;
	m_cellIdByCoord[Hex(3, -1)] = 34;
	m_cellIdByCoord[Hex(3, 0)] = 35;
	m_cellIdByCoord[Hex(2, 1)] = 36;
	
	m_cells.resize(m_cellIdByCoord.size());
	
	for (auto p: m_cellIdByCoord)
	{
		m_cells[p.second] = Cell(p.second, p.first.q(), p.first.r());
	}
}

void Map::clear()
{
	for (Cell &c: m_cells) {
		c.clear();
	}
}

void Map::updateShadows(Hex::Dir sunDir)
{
	for (Cell &c: m_cells) {
		Tree *tree = c.tree();
		if (tree) {
			int shadowPower = tree->size();
			for (Hex h: c.neighbours(sunDir, shadowPower)) {
				if (m_cellIdByCoord.count(h))
				{
					(*this)[h].setShadowPower(shadowPower);
				}
			}
		}
	}
}

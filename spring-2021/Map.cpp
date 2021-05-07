#include "Map.h"

Map::Map()
{
	m_cells.push_back(Cell(0, 0, 0));
	m_cells.push_back(Cell(1, 0, 1));
	m_cells.push_back(Cell(2, -1, 1));
	m_cells.push_back(Cell(3, -1, 0));
	m_cells.push_back(Cell(4, 0, -1));
	m_cells.push_back(Cell(5, 1, -1));
	m_cells.push_back(Cell(6, 1, 0));
	m_cells.push_back(Cell(7, 0, 2));
	m_cells.push_back(Cell(8, -1, 2));
	m_cells.push_back(Cell(9, -2, 2));
	m_cells.push_back(Cell(10, -2, 1));
	m_cells.push_back(Cell(11, -2, 0));
	m_cells.push_back(Cell(12, -1, -1));
	m_cells.push_back(Cell(13, 0, -2));
	m_cells.push_back(Cell(14, 1, -2));
	m_cells.push_back(Cell(15, 2, -2));
	m_cells.push_back(Cell(16, 2, -1));
	m_cells.push_back(Cell(17, 2, 0));
	m_cells.push_back(Cell(18, 1, 1));
	m_cells.push_back(Cell(19, 1, 2));
	m_cells.push_back(Cell(20, 0, 3));
	m_cells.push_back(Cell(21, -1, 3));
	m_cells.push_back(Cell(22, -2, 3));
	m_cells.push_back(Cell(23, -3, 3));
	m_cells.push_back(Cell(24, -3, 2));
	m_cells.push_back(Cell(25, -3, 1));
	m_cells.push_back(Cell(26, -3, 0));
	m_cells.push_back(Cell(27, -2, -1));
	m_cells.push_back(Cell(28, -1, -2));
	m_cells.push_back(Cell(29, 0, -3));
	m_cells.push_back(Cell(30, 1, -3));
	m_cells.push_back(Cell(31, 2, -3));
	m_cells.push_back(Cell(32, 3, -3));
	m_cells.push_back(Cell(33, 3, -2));
	m_cells.push_back(Cell(34, 3, -1));
	m_cells.push_back(Cell(35, 3, 0));
	m_cells.push_back(Cell(36, 2, 1));
}

void Map::clear()
{
	for (Cell &c: m_cells) {
		c.clear();
	}
}

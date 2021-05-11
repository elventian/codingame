#include "Map.h"

std::map<Hex, int> Map::m_cellIdByCoord;
std::vector<int> Map::m_cellValue;
std::vector<int> Map::m_cellsOfValue;

void Map::init()
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
	m_cellIdByCoord[Hex(0, 3)] = 19;
	m_cellIdByCoord[Hex(-1, 3)] = 20;
	m_cellIdByCoord[Hex(-2, 3)] = 21;
	m_cellIdByCoord[Hex(-3, 3)] = 22;
	m_cellIdByCoord[Hex(-3, 2)] = 23;
	m_cellIdByCoord[Hex(-3, 1)] = 24;
	m_cellIdByCoord[Hex(-3, 0)] = 25;
	m_cellIdByCoord[Hex(-2, -1)] = 26;
	m_cellIdByCoord[Hex(-1, -2)] = 27;
	m_cellIdByCoord[Hex(0, -3)] = 28;
	m_cellIdByCoord[Hex(1, -3)] = 29;
	m_cellIdByCoord[Hex(2, -3)] = 30;
	m_cellIdByCoord[Hex(3, -3)] = 31;
	m_cellIdByCoord[Hex(3, -2)] = 32;
	m_cellIdByCoord[Hex(3, -1)] = 33;
	m_cellIdByCoord[Hex(3, 0)] = 34;
	m_cellIdByCoord[Hex(2, 1)] = 35;
	m_cellIdByCoord[Hex(1, 2)] = 36;
	
	m_cellValue.resize(m_cellIdByCoord.size());
}

Map::Map()
{
	m_cells.resize(m_cellIdByCoord.size());
	m_cellsOfValue.resize(Hex::DirsNum + 1);
	
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
	m_myTrees.clear();
	m_oppTrees.clear();
}

int Map::mirrorCellIndex(int cellIndex) const
{
	return indexByHex((*this)[cellIndex].mirror());
}

void Map::updateShadows()
{
	updateShadows(m_myTrees);
	updateShadows(m_oppTrees);
}

void Map::updateShadows(const Tree &tree)
{
	int shadowPower = tree.size();
	for (int i = 0; i < Hex::DirsNum; i++)
	{
		Hex::Dir dir = (Hex::Dir) i;
		Cell &treeCell = (*this)[tree.cellIndex()];
		for (Hex h: treeCell.neighbours(dir, shadowPower)) {
			if (contains(h) && (*this)[h].shadowPower(dir) < shadowPower)
			{
				(*this)[h].setShadowPower(dir, shadowPower);
			}
		}
	}
}

void Map::updateShadows(const TreeList &trees)
{
	for (const Tree &tree: trees) {
		updateShadows(tree);
	}
}

int Map::sunPoints(const Tree &tree, Hex::Dir dir) const
{
	int treeSize = tree.size();
	return (treeSize > m_cells[tree.cellIndex()].shadowPower(dir)) ? treeSize : 0;
}

int Map::sunPoints(Hex::Dir dir) const
{
	int res = 0;
	for (const Tree &tree: m_myTrees) {
		res += sunPoints(tree, dir);
	}
	return res;
}

std::list<int> Map::seedCells(const Tree &tree) const
{
	std::list<int> res;
	
	for (Hex h: m_cells[tree.cellIndex()].neighbours(tree.size())) {
		if (contains(h) && (*this)[h].richness() > 0 && !hasTree(h)) {
			res.push_back(indexByHex(h));
		}
	}
	return res;
}

void Map::completeTreeAt(int cellIndex)
{
	for (auto it = m_myTrees.begin(); it != m_myTrees.end(); it++)
	{
		if (it->cellIndex() == cellIndex) {
			m_myTrees.erase(it);
			return;
		}
	}
}

bool Map::hasTree(Hex coord) const
{
	for (const Tree &tree: m_myTrees) {
		if (tree.cellIndex() == indexByHex(coord)) { return true; }
	}
	for (const Tree &tree: m_oppTrees) {
		if (tree.cellIndex() == indexByHex(coord)) { return true; }
	}
	return false;
}

int Map::treesNum(int treeSize) const
{
	int res = 0;
	for (const Tree &tree: m_myTrees)
	{
		if (tree.size() == treeSize) { res++; }
	}
	return res;
}

Tree *Map::myTree(int cellIndex)
{
	for (Tree &tree: m_myTrees) {
		if (tree.cellIndex() == cellIndex) { return &tree;}
	}
	return nullptr;
}

void Map::nextTurn()
{
	for (Tree &tree: m_myTrees) {
		tree.wake();
	}
}

#include <iostream>
void Map::recalcCellValues()
{
	std::fill(m_cellsOfValue.begin(), m_cellsOfValue.end(), 0);
	for (Cell &c: m_cells) {
		Tree tree(c.id(), 1);
		m_cellValue[c.id()] = 0;
		if (hasTree(c)) continue;
		for (int i = 0; i < Hex::DirsNum; i++) {
			m_cellValue[c.id()] += sunPoints(tree, (Hex::Dir)i);
		}
		m_cellsOfValue[m_cellValue[c.id()]]++;
	}
}

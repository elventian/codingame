#ifndef MAP_H
#define MAP_H

#include "Cell.h"
#include <map>

class Map
{
public:
	Map();
	static void init();
	static int cellsOfValue(int value) { return m_cellsOfValue[value]; }
	static int valueOfCell(int cellIndex) { return m_cellValue[cellIndex]; }
	void clear();
	Cell &operator[](int index) { return m_cells[index]; }
	Cell &operator[](Hex hexCoord) { return m_cells[m_cellIdByCoord[hexCoord]]; }
	const Cell &operator[](Hex hexCoord) const { return m_cells[m_cellIdByCoord[hexCoord]]; }
	int indexByHex(Hex hexCoord) const { return m_cellIdByCoord[hexCoord]; }
	const Cell &getCellOf(const Tree *tree) const { return (*this)[tree->cellIndex()]; }
	int mirrorCellIndex(int cellIndex) const;
	bool contains(Hex hexCoord) const { return m_cellIdByCoord.count(hexCoord); }
	
	CellVector::iterator begin() { return m_cells.begin(); }
	CellVector::iterator end() { return m_cells.end(); }
	int size() const { return m_cells.size(); }
	void updateShadows();
	void updateShadows(const Tree &tree);
	int sunPoints(const Tree &tree, Hex::Dir dir) const;
	int sunPoints(Hex::Dir dir) const;
	std::list<int> seedCells(const Tree &tree) const;
	void addTree(const Tree &tree) { 
		if (tree.isMine()) { m_myTrees.push_back(tree); }
		else { m_oppTrees.push_back(tree); }
	}
	void completeTreeAt(int cellIndex);
	bool hasTree(Hex coord) const;
	int treesNum(int treeSize) const;
	Tree *myTree(int cellIndex);
	TreeList &myTrees() { return m_myTrees; }
	TreeList &opponentTrees() { return m_oppTrees; }
	int richnessPoints(int cellIndex) const { return m_cells[cellIndex].richnessPoints(); }
	void nextTurn();
	
	void recalcCellValues();
private:
	CellVector m_cells;
	TreeList m_myTrees;
	TreeList m_oppTrees;
	static std::map<Hex, int> m_cellIdByCoord;
	static std::vector<int> m_cellValue;
	static std::vector<int> m_cellsOfValue;
	
	const Cell &operator[](int index) const { return m_cells[index]; }
	void updateShadows(const TreeList &trees);
};

#endif // MAP_H

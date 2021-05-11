#ifndef TREE_H
#define TREE_H

#include <list>

class Tree
{
public:
	Tree(int cellIndex, int size, int isMine = true, int isDormant = true): 
		m_cellIndex(cellIndex), m_size(size), m_isMine(isMine), m_isDormant(isDormant) {}
	
	static const int maxSize = 3;
	int size() const { return m_size; }
	int sunPoints() const { return m_size; }
	bool isMine() const { return m_isMine; }
	bool isDormant() const { return m_isDormant; }
	int cellIndex() const {	return m_cellIndex;	}
	bool canGrow() const { return !isDormant() && size() < maxSize; }
	bool canComplete() const { return !isDormant() && size() == maxSize; }
	bool canPlant() const { return !isDormant() && size() > 0; }
	int turnsToComplete() const { return maxSize - size() + 1; }
	bool isSeed() const { return m_size == 0; }
	void grow() { m_size++; m_isDormant = true; }
	void seed() { m_isDormant = true; }
	void wake() { m_isDormant = false; }
	
private:
	int m_cellIndex;
	int m_size;
	bool m_isMine;
	bool m_isDormant;
};

typedef std::list<Tree> TreeList;

#endif // TREE_H



#ifndef TREE_H
#define TREE_H

#include <list>

class Tree
{
public:
	Tree(int cellIndex, int size, int isMine, int isDormant): 
		m_cellIndex(cellIndex), m_size(size), m_isMine(isMine), m_isDormant(isDormant) {}
	
	int size() const { return m_size; }
	int sunPoints() const { return m_size; }
	bool isMine() const { return m_isMine; }
	bool isDormant() const { return m_isDormant; }
	int cellIndex() const {	return m_cellIndex;	}
	bool canGrow() const { return !isDormant() && size() < maxSize; }
	bool canPlant() const { return !isDormant() && size() > 0; }
	Tree *grow() const {
		Tree *res = new Tree(*this);
		res->m_size++;
		return res;
	}
	
private:
	int m_cellIndex;
	int m_size;
	bool m_isMine;
	bool m_isDormant;
	static const int maxSize = 3;
};

typedef std::list<const Tree *> TreeList;

#endif // TREE_H



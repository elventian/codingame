#ifndef TREE_H
#define TREE_H

#include <list>

class Tree
{
public:
	Tree(int size, int isMine, int isDormant): m_size(size), m_isMine(isMine), m_isDormant(isDormant) {}
	
	int size() const { return m_size; }
	bool isMine() const { return m_isMine; }
	bool isDormant() const { return m_isDormant; }
	
private:
	int m_size;
	bool m_isMine;
	bool m_isDormant;
};

typedef std::list<Tree *> TreeList;

#endif // TREE_H

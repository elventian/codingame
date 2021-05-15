#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include "Tree.h"
#include <cstring>

class Configuration 
{
public:
	Configuration() {}
	Configuration(const TreeList &trees) {
		memset(m_treesBySize, 0, sizeof(m_treesBySize));
		for (const Tree tree: trees) {
			m_treesBySize[tree.size()]++;
		}
	}
	Configuration(int m_day) {
		(void)m_day;
		m_treesBySize[0] = 1;
		m_treesBySize[1] = 3;
		m_treesBySize[2] = 3;
		m_treesBySize[3] = 3;
	}
	Configuration operator-(const Configuration &other) {
		Configuration res;
		for (int i = 0; i < Tree::maxSize + 1; i++) {
			res.m_treesBySize[i] = m_treesBySize[i] - other.m_treesBySize[i];
		}
		return res;
	}
	int treesOfSize(int size) const {
		return m_treesBySize[size];
	}
private:
	int m_treesBySize[Tree::maxSize + 1];
};

#endif // CONFIGURATION_H

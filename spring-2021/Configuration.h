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
		if (m_day < 13) {
			m_treesBySize[0] = 1; m_treesBySize[1] = 1; m_treesBySize[2] = 2; m_treesBySize[3] = 4;
		}
		else {
			m_treesBySize[0] = 0; m_treesBySize[1] = 0; m_treesBySize[2] = 0; m_treesBySize[3] = 4;
		}
	}
	Configuration operator-(const Configuration &other) {
		Configuration res;
		for (int i = 0; i < Tree::maxSize + 1; i++) {
			res.m_treesBySize[i] = m_treesBySize[i] - other.m_treesBySize[i];
		}
		return res;
	}
	int extraTrees(const Configuration &other) {
		int res = 0;
		for (int i = 0; i < Tree::maxSize + 1; i++) {
			int diff = m_treesBySize[i] - other.m_treesBySize[i];
			if (diff > 0) { res += diff; }
		}
		return res;
	}
	bool achieved(const Configuration &other) {
		for (int i = 0; i < Tree::maxSize + 1; i++) {
			if (other.m_treesBySize[i] - m_treesBySize[i] > 0) { return false; }
		}
		return true;
	}
	int actionsToAchieve(const Configuration &other) {
		int reqTrees = 0;
		int actions = 0;
		for (int i = Tree::maxSize; i >= 0; i--) {
			int diff = other.m_treesBySize[i] - m_treesBySize[i] + reqTrees;
			if (diff > 0) {
				actions += diff;
				reqTrees = diff;
			}
		}
		return actions;
	}
	int treesOfSize(int size) const {
		return m_treesBySize[size];
	}
private:
	int m_treesBySize[Tree::maxSize + 1];
};

#endif // CONFIGURATION_H

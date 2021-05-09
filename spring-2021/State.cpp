#include "State.h"

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>


State::State(std::istream &in)
{
	int numberOfCells; // 37
	in >> numberOfCells; in.ignore();
	for (int i = 0; i < numberOfCells; i++) {
		int index; // 0 is the center cell, the next cells spiral outwards
		int richness; // 0 if the cell is unusable, 1-3 for usable cells
		int neigh0; // the index of the neighbouring cell for each direction
		int neigh1;
		int neigh2;
		int neigh3;
		int neigh4;
		int neigh5;
		in >> index >> richness >> neigh0 >> neigh1 >> neigh2 >> neigh3 >> neigh4 >> neigh5; in.ignore();
		m_map[i].setRichness(richness);
	}
}

bool State::read(std::istream &in)
{
	m_map.clear();
	TreeList myTrees, oppTrees;
	in >> m_day; in.ignore();	
	
	std::cerr << m_map.size() << std::endl;
	for (Cell &c: m_map)
	{
		std::cerr << c.id() << " " << c.richness() << " 0 0 0 0 0 0" << std::endl;
	}
	std::cerr << m_day << std::endl;
	in >> m_nutrients; in.ignore(); std::cerr << m_nutrients << std::endl;
	in >> m_sun >> m_score; in.ignore(); std::cerr << m_sun << " " << m_score << std::endl;
	in >> m_oppSun >> m_oppScore >> m_oppIsWaiting; in.ignore(); 
	std::cerr << m_oppSun << " " << m_oppScore << " " << m_oppIsWaiting << std::endl;
	int numberOfTrees; // the current amount of trees
	in >> numberOfTrees; in.ignore(); std::cerr << numberOfTrees << std::endl;
	for (int i = 0; i < numberOfTrees; i++) {
		int cellIndex; // location of this tree
		int size; // size of this tree: 0-3
		bool isMine; // 1 if this is your tree
		bool isDormant; // 1 if this tree is dormant
		in >> cellIndex >> size >> isMine >> isDormant; in.ignore();
		std::cerr << cellIndex << " " << size << " " << isMine << " " <<  isDormant << std::endl;
		if (!isMine) {
			const Tree *prevTree = nullptr;
			for (const Tree *t: m_oppTrees) {
				if (t->cellIndex() == cellIndex) {
					prevTree = t;
					break;
				}
			}
			if (!prevTree || prevTree->size() > size) {
				if (m_day == 0 && m_oppTrees.size() == 0) { }
				else {
					std::cerr << "New tree detected at " << cellIndex << std::endl;
					actions.push_back(Action(Action::Seed, m_map.mirrorCellIndex(cellIndex)));
				}
			}
			else if (prevTree->size() < size) {
				std::cerr << "Grow detected at " << cellIndex << std::endl;
				actions.push_back(Action(Action::Grow, m_map.mirrorCellIndex(cellIndex)));
			}
		}
		Tree *t = new Tree(cellIndex, size, isMine, isDormant);
		if (isMine) { myTrees.push_back(t); }
		else { oppTrees.push_back(t); }
		m_map[cellIndex].addTree(t);
	}
	int numberOfPossibleMoves;
	in >> numberOfPossibleMoves; in.ignore(); std::cerr << "0" << std::endl;
	for (int i = 0; i < numberOfPossibleMoves; i++) {
		std::string possibleMove;
		std::getline(in, possibleMove);
	}
	
	for (const Tree *oldTree: m_oppTrees) {
		bool completed = true;
		for (const Tree *newTree: oppTrees) {
			if (oldTree->cellIndex() == newTree->cellIndex() && oldTree->size() <= newTree->size()) {
				completed = false;
				break;
			}
		}
		if (completed) {
			std::cerr << "Complete detected at " << oldTree->cellIndex() << std::endl;
			actions.push_front(Action(Action::Complete, m_map.mirrorCellIndex(oldTree->cellIndex())));
		}
	}
	
	clear();
	m_oppTrees.splice(m_oppTrees.begin(), oppTrees);
	m_myTrees.splice(m_myTrees.begin(), myTrees);
	
	return true;
}

State::~State()
{
	for (const Tree *t: m_newTrees) { delete t; }
}

void State::clear()
{
	for (const Tree *t: m_myTrees) { delete t; }
	for (const Tree *t: m_oppTrees) { delete t; }
	m_myTrees.clear();
	m_oppTrees.clear();	
}

int State::growCost(int treeSize) const
{
	return (1 << treeSize) - 1 + treesNum(treeSize);
}

int State::growCost(const Tree *tree) const
{
	return growCost(tree->size() + 1);
}

int State::completeCost(const Tree *tree) const
{
	int res = 4;
	for (int i = tree->size(); i < Tree::maxSize; i++) {
		res += (1 << i) - 1;
	}
	return res;
}

int State::treesNum(int treeSize) const
{
	int res = 0;
	for (const Tree *tree: m_myTrees)
	{
		if (tree->size() == treeSize) { res++; }
	}
	return res;
}

void State::grow(const Tree *tree)
{
	m_sun -= growCost(tree);
	Tree *newTree = tree->grow();
	m_newTrees.push_back(newTree);
	m_myTrees.push_back(newTree);
	m_myTrees.remove(tree);
	m_map[newTree->cellIndex()].addTree(newTree);
}

void State::plant(Hex pos)
{
	m_sun -= growCost(0);
	Tree *newTree = new Tree(m_map.indexByHex(pos), 0, true, true);
	m_newTrees.push_back(newTree);
	m_myTrees.push_back(newTree);
	m_map[newTree->cellIndex()].addTree(newTree);
}

void State::evaluate()
{
	int treesPotential = 0;
	int expectedSunPoints = 0;
	
	for (const Tree *tree: m_myTrees) {
		for (int dayOffset = 1; dayOffset + m_day < daysNum; dayOffset++) {
			expectedSunPoints += m_map.sunPoints(tree, Hex::nextDir(getSunDir(), dayOffset));
		}
	}
	
	float sunPerTurn = expectedSunPoints / float(daysNum - m_day - 1);
	
	for (const Tree *tree: m_myTrees) {
		int cost = completeCost(tree);
		int turnsToComplete = std::max(int(ceil(cost / sunPerTurn)), tree->turnsToComplete());
		int expectedNutrition = m_nutrients - turnsToComplete;
		int expectedVictoryPoints = (m_map.getCellOf(tree).richnessPoints() + expectedNutrition) * vpCoeff;
		treesPotential += expectedVictoryPoints - cost;
	}
	m_value = treesPotential + m_sun;
}

void State::process()
{
	m_map.updateShadows();
	
	if (m_day == daysNum - 1) {
		for (const Tree *tree: m_myTrees) {
			actions.push_front(Action(Action::Complete, tree->cellIndex()));
		}
	}
	
	for (auto it = actions.begin(); it != actions.end(); it++) {
		Action &action = *it;
		if (action.type() == Action::Complete) {
			const Tree *tree = m_map[action.cellId()].tree();
			if (tree && tree->isMine() && tree->canComplete() && m_sun >= completeCost(tree)) {
				std::cout << "COMPLETE " << action.cellId() << std::endl;
				actions.erase(it);
				return;
			}
		}
		else if (action.type() == Action::Grow) {
			const Tree *tree = m_map[action.cellId()].tree();
			if (tree && tree->isMine() && tree->canGrow() && m_sun >= growCost(tree)) {
				std::cout << "GROW " << action.cellId() << std::endl;
				actions.erase(it);
				return;
			}
		}
		else if (action.type() == Action::Seed) {
			if (m_sun >= growCost(0))
			{
				for (int i = 1; i < Tree::maxSize; i++) {
					HexList neighbours = m_map[action.cellId()].neighbours(i);
					for (Hex h: neighbours) {
						if (m_map.contains(h) && m_map[h].tree()) {
							const Tree *tree = m_map[h].tree();
							if (tree->isMine() && tree->size() >= i && tree->canPlant()) {
								std::cout << "SEED " << m_map[h].tree()->cellIndex()
									<< " " << action.cellId() << std::endl;
								actions.erase(it);
								return;
							}
						}
					}
				}
			}
		}
	}
	
	std::cout << "WAIT" << std::endl;
	
}

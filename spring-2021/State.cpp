#include "State.h"

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <queue>
#include <math.h>

char *State::pool = new char[State::poolSize * sizeof(State)];
State *State::nextFree = reinterpret_cast<State *>(State::pool);

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
		m_map.addTree(Tree(cellIndex, size, isMine, isDormant));
	}
	int numberOfPossibleMoves;
	in >> numberOfPossibleMoves; in.ignore(); std::cerr << "0" << std::endl;
	for (int i = 0; i < numberOfPossibleMoves; i++) {
		std::string possibleMove;
		std::getline(in, possibleMove);
	}
		
	return true;
}

int State::growCost(int treeSize) const
{
	return (1 << treeSize) - 1 + m_map.treesNum(treeSize);
}

int State::growCost(const Tree &tree) const
{
	return growCost(tree.size() + 1);
}

int State::completeCost(const Tree *tree) const
{
	int res = m_completeCost;
	for (int i = tree->size(); i < Tree::maxSize; i++) {
		res += (1 << i) - 1;
	}
	return res;
}

void State::evaluate()
{
	int treesPotential = 0;
	int expectedSunPoints = 0;
	int expectedOppSunPoints = 0;
	
	for (const Tree &tree: m_map.myTrees()) {
		for (int dayOffset = 1; dayOffset + m_day < daysNum; dayOffset++) {
			expectedSunPoints += m_map.sunPoints(tree, Hex::nextDir(getSunDir(), dayOffset));
		}
		treesPotential += m_map.richnessPoints(tree.cellIndex()) * vpCoeff;
		for (int i = m_map.valueOfCell(tree.cellIndex()) + 1; i <= Hex::DirsNum; i++) {
			treesPotential -= m_map.cellsOfValue(i);	
		}
	}
	
	for (const Tree &tree: m_map.opponentTrees()) {
		for (int dayOffset = 1; dayOffset + m_day < daysNum; dayOffset++) {
			expectedOppSunPoints += m_map.sunPoints(tree, Hex::nextDir(getSunDir(), dayOffset));
		}
	}
	
	/*float sunPerTurn = expectedSunPoints / float(daysNum - m_day - 1);
	
	int turnsToComplete = 0;
	for (const Tree *tree: m_myTrees) {
		int cost = completeCost(tree);
		turnsToComplete += std::max(int(ceil(cost / sunPerTurn)), tree->turnsToComplete());
		int expectedNutrition = m_nutrients - turnsToComplete;
		int expectedVictoryPoints = (m_map.getCellOf(tree).richnessPoints() + expectedNutrition) * vpCoeff;
		treesPotential += expectedVictoryPoints - cost;
	}*/
	m_value = m_sun + expectedSunPoints + treesPotential + m_score * vpCoeff - expectedOppSunPoints;
}

class StateCmp 
{
public:
	bool operator() (State *node1, State *node2) const {
		return node1->value() < node2->value();
	}
};

void State::process()
{
	State::resetMemoryPool();
	m_map.updateShadows();
	m_map.recalcCellValues();
	evaluate();
	std::cerr << "Base value = " << m_value << std::endl;
	
	std::priority_queue<State *, std::vector<State *>, StateCmp> searchQueue;
	State *root = State::create(*this);
	State *node = nullptr;
	searchQueue.push(root);
	const int depth = std::min(5, daysNum - m_day);
	
	while (!searchQueue.empty()) {
		node = searchQueue.top();
		searchQueue.pop();
		
		if (node->actions.size() > 0) {
			std::cerr << "------------- VALUE = " << node->m_value << " sun = " << node->m_sun << std::endl;
			int i = 0;
			for (Action action: node->actions) {
				std::cerr << i << " " << action.toStr() << std::endl; 
				if (action.type() == Action::Wait) { i++; }
			}
		}
		
		if (node->m_day - m_day >= depth) { break; }
		
		for (Tree &tree: node->m_map.myTrees()) {
			int cost = node->growCost(tree);
			int cellIndex = tree.cellIndex();
			if (tree.canGrow() && node->m_sun >= cost) {
				State *nextNode = State::create(*node);
				Tree *nextTree = nextNode->m_map.myTree(cellIndex);
				nextNode->m_sun -= cost;
				nextTree->grow();
				nextNode->m_map.updateShadows(*nextTree);
				nextNode->evaluate();
				nextNode->addAction(Action(Action::Grow, cellIndex));
				searchQueue.push(nextNode);
			}
			
			cost = node->growCost(0);
			if (tree.canPlant() && node->m_sun >= cost) {
				std::list<int> &&seedCells = node->m_map.seedCells(tree);
				for (int seedCell: seedCells) {
					State *nextNode = State::create(*node);
					Tree *nextTree = nextNode->m_map.myTree(tree.cellIndex());
					nextTree->seed();
					nextNode->m_sun -= cost;
					nextNode->m_map.addTree(Tree(seedCell, 0));
					nextNode->evaluate();
					nextNode->addAction(Action(Action::Seed, seedCell, cellIndex));
					searchQueue.push(nextNode);
				}
			}
			
			cost = m_completeCost;
			if (tree.canComplete() && node->m_sun >= cost) {
				State *nextNode = State::create(*node);
				nextNode->m_map.completeTreeAt(cellIndex);
				nextNode->m_map.updateShadows();
				nextNode->m_score += nextNode->m_map.richnessPoints(cellIndex) + nextNode->m_nutrients;
				nextNode->m_nutrients--;
				nextNode->m_sun -= cost;
				nextNode->evaluate();
				nextNode->addAction(Action(Action::Complete, cellIndex));
				searchQueue.push(nextNode);
			}
		}
		
		if (node->m_day < daysNum) {
			node->addAction(Action());
			node->m_day++;
			node->m_sun += node->m_map.sunPoints(node->getSunDir());
			node->m_map.nextTurn();
			searchQueue.push(node);
		}
	}
	
	Action action = (node && !node->actions.empty()) ? node->actions.front() : Action();
	std::cout << action.toStr() << std::endl;
	
}

void State::apply(Action action)
{
	/*if (action.type() == Action::Complete) {
		const Tree *tree = m_map[action.cellId()].tree();
		if (tree && tree->isMine() && tree->canComplete() && m_sun >= completeCost(tree)) {
			std::cout << "COMPLETE " << action.cellId() << std::endl;
			return;
		}
	}
	else if (action.type() == Action::Grow) {
		const Tree *tree = m_map[action.cellId()].tree();
		if (tree && tree->isMine() && tree->canGrow() && m_sun >= growCost(tree)) {
			std::cout << "GROW " << action.cellId() << std::endl;
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
							return;
						}
					}
				}
			}
		}
	}*/
	
	std::cout << action.toStr() << std::endl;
}

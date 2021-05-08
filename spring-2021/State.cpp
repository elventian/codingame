#include "State.h"

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>


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
	clear();
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
		Tree *t = new Tree(cellIndex, size, isMine, isDormant);
		if (isMine) { m_myTrees.push_back(t) ;}
		else { m_oppTrees.push_back(t); }
		m_map[cellIndex].addTree(t);
	}
	int numberOfPossibleMoves;
	in >> numberOfPossibleMoves; in.ignore(); std::cerr << "0" << std::endl;
	for (int i = 0; i < numberOfPossibleMoves; i++) {
		std::string possibleMove;
		std::getline(in, possibleMove);
	}
	
	return true;
}

State::~State()
{
	for (const Tree *t: m_newTrees) { delete t; }
}

void State::clear()
{
	m_map.clear();
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
	Tree *newTree = new Tree(m_map.indexByHex(pos), 1, true, true);
	m_newTrees.push_back(newTree);
	m_myTrees.push_back(newTree);
	m_map[newTree->cellIndex()].addTree(newTree);
}

void State::process()
{
	m_map.updateShadows();
	evaluate();
	std::cerr << "Base value = " << m_value << std::endl;
	int bestValue = m_value;
	std::string bestAction = "WAIT";
	for (const Tree *tree: m_myTrees) {
		if (tree->canGrow() && growCost(tree) <= m_sun)	{
			State nextState(*this); //destructor will delete grown trees!
			nextState.grow(tree);
			nextState.evaluate();
			std::cerr << "Grow " << tree->cellIndex() << " : " << nextState.m_value << " points" << std::endl;
			if (bestValue <= nextState.m_value) {
				bestValue = nextState.m_value;
				bestAction = "GROW " +  std::to_string(tree->cellIndex());
			}
		}
		if (tree->canPlant() && growCost(0) <= m_sun) {
			HexList &&seedCells = m_map.seedCells(tree);
			for (Hex h: seedCells) {
				State nextState(*this); //destructor will delete planted seeds!
				nextState.plant(h);
				nextState.evaluate();
				std::cerr << "Plant " << m_map.indexByHex(h) << " : " << nextState.m_value << " points" << std::endl;
				if (bestValue <= nextState.m_value) {
					bestValue = nextState.m_value;
					bestAction = "SEED " +  std::to_string(tree->cellIndex()) + " " 
						+ std::to_string(m_map.indexByHex(h));
				}
			}
		}
	}

	std::cout << bestAction << std::endl;	
	//std::cout << "WAIT" << std::endl;	
}

void State::evaluate()
{
	int expectedSunPoints = 0;
	for (const Tree *tree: m_myTrees) {
		for (int curDay = 0; curDay < Hex::DirsNum && curDay + m_day < daysNum; curDay++) {
			expectedSunPoints += m_map.sunPoints(tree, Hex::nextDir((Hex::Dir)curDay, m_day));
		}
	}
	m_value = expectedSunPoints + m_sun;
}

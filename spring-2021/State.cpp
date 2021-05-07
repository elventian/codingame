#include "State.h"

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>


State::State(std::istream &in)
{
	clear();
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
		Tree *t = new Tree(size, isMine, isDormant);
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

void State::clear()
{
	m_map.clear();
	for (Tree *t: m_myTrees) { delete t; }
	for (Tree *t: m_oppTrees) { delete t; }
	m_myTrees.clear();
	m_oppTrees.clear();	
}


void State::process()
{
	std::cout << "WAIT" << std::endl;
}

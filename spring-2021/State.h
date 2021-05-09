#ifndef STATE_H
#define STATE_H

#include <iostream>
#include <list>
#include <vector>
#include <limits>
#include "Map.h"
#include "Action.h"

class State
{
	friend std::ostream &operator<<(std::ostream &out, const State &state);
public:
	State(std::istream &in);
	~State();
	bool read(std::istream &in);
	void process();
	void clear();
private:
	Map m_map;
	int m_day;
	int m_nutrients;
	int m_sun;
	int m_score;
	int m_oppSun;
	int m_oppScore;
	int m_oppIsWaiting;  // whether your opponent is asleep until the next day
	TreeList m_myTrees;
	TreeList m_oppTrees;
	TreeList m_newTrees;
	const int daysNum = 24;
	const int vpCoeff = 3;
	int m_value;
	ActionsList actions;
	
	Hex::Dir getSunDir() const { return Hex::nextDir(Hex::DirS, m_day); }
	int growCost(int treeSize) const;
	int growCost(const Tree *tree) const;
	int completeCost(const Tree *tree) const;
	int treesNum(int treeSize) const;
	void evaluate();
	void grow(const Tree *tree);
	void plant(Hex pos);
	
};

#endif // STATE_H

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
	bool read(std::istream &in);
	void process();
	int value() const { return m_value; }
private:
	Map m_map;
	int m_day;
	int m_nutrients;
	int m_sun;
	int m_score;
	int m_oppSun;
	int m_oppScore;
	int m_oppIsWaiting;  // whether your opponent is asleep until the next day
	const int daysNum = 24;
	const int vpCoeff = 3;
	const int m_completeCost = 4;
	int m_value;
	ActionsList actions;
	//Pool
	static const int poolSize = 10000;
	static char *pool;
	static State *nextFree;
	static State *create(const State &other) {
		return new(nextFree++) State(other);
	}
	static void resetMemoryPool() {
		nextFree = reinterpret_cast<State *>(State::pool);
	}
	
	Hex::Dir getSunDir() const { return Hex::nextDir(Hex::DirS, m_day); }
	int growCost(int treeSize) const;
	int growCost(const Tree &tree) const;
	int completeCost(const Tree *tree) const;
	int treesNum(int treeSize) const;
	void evaluate();
	void apply(Action action);
	void addAction(Action action) { actions.push_back(action); }
	
};

#endif // STATE_H

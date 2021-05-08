#ifndef STATE_H
#define STATE_H

#include <iostream>
#include <list>
#include <vector>
#include <limits>
#include "Map.h"

class State
{
	friend std::ostream &operator<<(std::ostream &out, const State &state);
public:
	State(std::istream &in);
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
	
	const int daysNum = 24;
	
	Hex::Dir getSunDir() const { return Hex::nextDir(Hex::DirSE, m_day); }
};

#endif // STATE_H

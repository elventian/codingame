#ifndef STATE_H
#define STATE_H

#include <iostream>
#include <list>
#include <vector>
#include <limits>
#include "Unit.h"
#include "Action.h"
#include "Map.h"

class State
{
	friend std::ostream &operator<<(std::ostream &out, const State &state);
public:
	~State() { 
		clear(); 
		delete m_map;
	}
	
	bool read(std::istream &in);
	const Map *map() const { return m_map; }
	const Unit &unit() const { return m_unit; }
	const CoordsSet &cellsToCheck() const { return m_needCheck; }
	const UnitsList &enemies() const { return m_enemies; }
	bool isTerminal() const { return lost(); }
	bool lost() const;
	int unitsNum() const { return m_unitsNum; }
	
protected:
	void clear();
	
	int m_unitsNum = 0;
	Map *m_map;
	Unit m_unit;
	UnitsList m_enemies;
	CoordsSet m_needCheck;
	CoordsSet m_checked;
	CoordsSet m_empty;
};

class MinimaxState: public State 
{
public:
	static MinimaxState *create(const State &other) {
		MinimaxState *res = new(nextFree++) MinimaxState(other);
		return res;
	}
	
	static MinimaxState *create(MinimaxState *parent, int unitId, const Action &action) {
		MinimaxState *res = new(nextFree++) MinimaxState(*parent);
		res->m_parent = parent;
		res->m_action = action;
		res->m_agentId = unitId;
		parent->m_children.push_back(res);
		res->m_depth = parent->m_depth + 1;
		parent->m_value = isAgentMaximizing(unitId) ? 
			std::numeric_limits<float>::min(): 
			std::numeric_limits<float>::max();
		return res;
	}
	
	static void reset(int agentsNum) {
		nextFree = reinterpret_cast<MinimaxState *>(MinimaxState::pool);
		agentsRoles.assign(agentsNum, false);
	}
	
	static void registerMaximizingAgent(int agentId) {
		agentsRoles[agentId] = true;
	}
	
	static bool isAgentMaximizing(int agentId) { return agentsRoles[agentId]; }
	
	int depth() const { return m_depth; }
	void evaluate();
	
private:	
	MinimaxState(const State &other): State(other) {
		m_parent = nullptr;
		m_depth = 0;
	}
	
	static const int poolSize = 10000;
	static char *pool;
	static MinimaxState *nextFree;
	static std::vector<bool> agentsRoles;

protected:
	int m_agentId;
	Action m_action;
	MinimaxState *m_parent;
	std::list<MinimaxState *> m_children;
	int m_depth;
	float m_value;
	bool m_prune = false; //alpha-beta pruning activated for state (by sibling)
	
	void propagateValue();
};

#endif // STATE_H

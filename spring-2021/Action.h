#ifndef ACTION_H
#define ACTION_H

#include <string>
#include <list>

class Action
{
public:
	enum Type { Wait, Seed, Grow, Complete, ActionsNum };
	
	Action() { m_type = Wait; }
	Action(Type type, int cellId) : m_cellId(cellId), m_type(type) {}
	Action(Type type, int cellId, int parentCellId): 
		m_cellId(cellId), m_parentCellId(parentCellId), m_type(type) {}
	int cellId() const { return m_cellId; }
	Type type() const { return m_type; }
	
	int parentCellId() const { return m_parentCellId; }
	void setParentCellId(int parentCellId) { m_parentCellId = parentCellId; }
	std::string toStr() const {
		switch (m_type) {
			case Seed: return "SEED " + std::to_string(m_parentCellId) + " " + std::to_string(m_cellId);
			case Grow: return "GROW " + std::to_string(m_cellId);
			case Complete: return "COMPLETE " + std::to_string(m_cellId);
			default: return "WAIT";
		}
	}
	
private:
	int m_cellId;
	int m_parentCellId;
	Type m_type;
};

typedef std::list<Action> ActionsList;

#endif // ACTION_H






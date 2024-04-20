#pragma once
#include "../DataStructures/LinkedListStack.h"
#include "../DataStructures/priQueue.h"
#include "Army.h"

class Unit;
class EarthArmy : public Army {
	priQueue<Unit*> earthGunnery;
	LinkedListStack<Unit*> earthTanks;
	LinkedQueue<Unit*> earthSoldiers;
	int tankCount;
	int gunnerCount;
	int soldierCount;
public:
	EarthArmy();
	bool addUnit(Unit* unit, bool isNew = false);
	bool getUnit(UNIT_TYPE type, Unit*& unit);
	bool peek(UNIT_TYPE type, Unit*& unit);
	void print();
	int getSoldierCount();
	~EarthArmy();
};

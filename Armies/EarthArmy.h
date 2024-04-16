#pragma once
#include <iostream>
#include "../DataStructures/LinkedListStack.h"
#include "../DataStructures/priQueue.h"
#include "Army.h"
using namespace std;


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
	bool getUnit(UNIT_TYPE type, Unit*& unit, bool rear = false);
	void print();
	int getSoldierCount();
	//void decrementCount(Unit*& unit);
};

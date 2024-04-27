#ifndef EARTH_ARMY_H
#define EARTH_ARMY_H

#include "../DataStructures/LinkedListStack.h"
#include "../DataStructures/priQueue.h"
#include "../DataStructures/LinkedQueue.h"
#include "Army.h"

class Unit;
class EarthArmy : public Army {
	priQueue<Unit*> earthGunnery;
	LinkedListStack<Unit*> earthTanks;
	LinkedQueue<Unit*> earthSoldiers;
	LinkedListStack<Unit*> HL;
	int tankCount;
	int gunnerCount;
	int soldierCount;
	int healCount;
public:
	EarthArmy();
	bool addUnit(Unit* unit, bool isNew = false);
	bool getUnit(UNIT_TYPE type, Unit*& unit);
	bool peek(UNIT_TYPE type, Unit*& unit);
	void fight();
	void print();
	bool isAlive();
	int getTotalSoldierCount();
	int getTotalGunneryCount();
	int getTotalTankCount();
	int getTotalHealCount();
	int getSoldierCount();
	~EarthArmy();
};

#endif
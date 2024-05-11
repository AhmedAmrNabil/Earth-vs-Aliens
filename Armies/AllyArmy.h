#ifndef ALLY_ARMY_H
#define ALLY_ARMY_H
#include "Army.h"
#include "../DataStructures/LinkedQueue.h"

class AllyArmy : public Army {
	LinkedQueue<Unit*>saverUnits;
	int saversCount;
public:
	bool addUnit(Unit* unit, bool isNew = false);
	bool getUnit(UNIT_TYPE type, Unit*& unit);
	bool peek(UNIT_TYPE type, Unit*& unit);
	bool fight();
	void print();
	int getSoldierCount();
	bool isAlive();

};

#endif

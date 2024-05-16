#ifndef ALLY_ARMY_H
#define ALLY_ARMY_H
#include "Army.h"
#include "../DataStructures/LinkedQueue.h"

class AllyArmy : public Army {
	LinkedQueue<Unit*>saverUnits;
	int saversCount;
public:
	AllyArmy();
	bool addUnit(Unit* unit, bool isNew = false);
	bool getUnit(UNIT_TYPE type, Unit*& unit);
	bool peek(UNIT_TYPE type, Unit*& unit);
	bool attack();
	void print();
	int getSaverCount();
	bool isAlive();
	~AllyArmy();

};

#endif

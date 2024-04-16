#pragma once

#include "../DataStructures/ArrayMonster.h"
#include "../DataStructures/LinkedDeque.h"
#include "./Army.h"


class Unit;
class AlienDrone;
class AlienSoldier;
class AlienArmy : public Army {
	ArrayMonster alienMonsters;
	LinkedDeque<Unit*> alienDrones;
	LinkedQueue<Unit*> alienSoldiers;
	int monsterCount;
	int soldierCount;
	int droneCount;
public:
	AlienArmy();

	bool addUnit(Unit* unit, bool isNew = false);
	bool getUnit(UNIT_TYPE type, Unit*& unit, bool rear = false);
	void print();
	int getSoldierCount();
	//void decrementCount(Unit*& unit);
};

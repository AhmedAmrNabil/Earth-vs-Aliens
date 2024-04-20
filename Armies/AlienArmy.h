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
	bool insertRear;
	bool peekRear;
public:
	AlienArmy();

	bool addUnit(Unit* unit, bool isNew = false);
	bool getUnit(UNIT_TYPE type, Unit*& unit);
	bool peek(UNIT_TYPE type, Unit*& unit);
	void print();
	int getSoldierCount();
	~AlienArmy();
};

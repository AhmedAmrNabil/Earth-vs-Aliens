#ifndef ALIEN_ARMY_H
#define ALIEN_ARMY_H

#include "../DataStructures/ArrayMonster.h"
#include "../DataStructures/LinkedDeque.h"
#include "../DataStructures/LinkedQueue.h"
#include "./Army.h"

class Unit;
class AlienArmy : public Army {
	ArrayMonster alienMonsters;
	LinkedDeque<Unit*> alienDrones;
	LinkedQueue<Unit*> alienSoldiers;
	bool insertRear;
	bool peekRear;

	// Total units count for each unit type
	int monsterCount;
	int soldierCount;
	int droneCount;
public:
	AlienArmy();
	bool addUnit(Unit* unit, bool isNew = false);
	bool getUnit(UNIT_TYPE type, Unit*& unit);
	bool peek(UNIT_TYPE type, Unit*& unit);
	bool attack();
	void print();
	bool isAlive();
	int getSoldierCount(); // Current soldier count for getting soldier ratio

	// Getter for total units count for each unit type
	int getTotalSoldierCount();
	int getTotalMonsterCount();
	int getTotalDroneCount();
	~AlienArmy();
};

#endif

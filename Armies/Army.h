#pragma once

#include <iostream>
#include "../BattleUnits/Unit.h"
#include "../DataStructures/LinkedQueue.h"
//#include "../BattleUnits/Soldier.h"
#include "../BattleUnits/EarthTank.h"
//#include "../BattleUnits/EarthGunner.h"
#include "../BattleUnits/AlienMonster.h"
#include "../BattleUnits/AlienDrone.h"

using namespace std;
class Soldier;
class Army {
	static LinkedQueue <Unit*> KilledUnits;
protected:
	LinkedQueue <Soldier*> Soldiers;
public:
	virtual bool addUnit(UNIT_TYPE type, int joinTime, int health, int power, int attackCapacity) = 0;
	virtual bool addExisting(UNIT_TYPE type, Unit* unit) = 0;
	bool getSoldier(Soldier*& alienSoldier) 
	{
		if (Soldiers.isEmpty()) return false;
		Soldiers.dequeue(alienSoldier);
		return true;
	}
	void addToKilled(Unit* killedUnit)
	{
		KilledUnits.enqueue(killedUnit);
	}
	virtual void print() = 0;
};
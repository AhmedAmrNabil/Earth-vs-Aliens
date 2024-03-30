#pragma once

#include <iostream>
#include "../BattleUnits/Unit.h"
#include "../DataStructures/LinkedQueue.h"
#include "../BattleUnits/Soldier.h"
#include "../BattleUnits/EarthTank.h"
//#include "../BattleUnits/EarthGunner.h"
#include "../BattleUnits/AlienMonster.h"
#include "../BattleUnits/AlienDrone.h"

using namespace std;
class Army {

public:
	virtual bool addUnit(UNIT_TYPE type, int joinTime, int health, int power, int attackCapacity) = 0;
	virtual bool addExisting(UNIT_TYPE type, Unit* unit) = 0;
	bool getSoldier(Unit*& alienSoldier) {};
	void addToKilled(Unit* killedUnit) {};
	void addAttacked(UNIT_TYPE type, Unit* attackedUnit) {};


};
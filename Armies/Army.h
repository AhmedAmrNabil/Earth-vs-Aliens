#include <iostream>
#include "LinkedQueue.h"
// #include "Stack.h"
#include "Soldier.h"
#include "EarthTank.h"
#include "EarthGunner.h"
#include "AlienMonster.h"
#include "AlienDrone.h"
using namespace std;
class Army {
private:
	// LinkedQueue <Soldier> soldiers;

public:
	virtual bool addUnit(UNIT_TYPE type, int joinTime, int health, int power, int attackCapacity);
	virtual bool addUnit(UNIT_TYPE type,Unit* unit);
	bool getSoldier(Unit* alienSoldier);
    void addToKilled(Unit* killedUnit);
	void addAttacked(UNIT_TYPE type,Unit* attackedUnit);
	

};
#pragma once

#include <iostream>

#include "../BattleUnits/Unit.h"
#include "../DataStructures/LinkedQueue.h"

using namespace std;
class Soldier;
class Army {
    static LinkedQueue<Unit*> killedUnits;

   protected:
    LinkedQueue<Soldier*> soldiers;
    int soldierCount;
   public:
    Army() {
        soldierCount = 0;
    }
    virtual bool addUnit(UNIT_TYPE type, int joinTime, int health, int power, int attackCapacity) = 0;
    virtual bool addExisting(UNIT_TYPE type, Unit* unit) = 0;
    virtual bool getUnit(UNIT_TYPE type, Unit*& unit, Unit*& unit2) = 0;
    void addToKilled(Unit* killedUnit) {
        killedUnits.enqueue(killedUnit);
    }
    virtual void print() = 0;
};
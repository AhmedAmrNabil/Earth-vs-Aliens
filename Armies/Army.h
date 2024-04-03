#pragma once

#include <iostream>

#include "../BattleUnits/Unit.h"
#include "../DataStructures/LinkedQueue.h"

using namespace std;
class Soldier;
class Army {
    LinkedQueue<Unit*>* killedUnits;

   public:
    Army() {
    }
    virtual bool addUnit(Unit* unit) = 0;
    virtual bool getUnit(UNIT_TYPE type, Unit*& unit, Unit*& unit2) = 0;
    virtual void print() = 0;
    void setKilledList(LinkedQueue <Unit*>* killed) {
        killedUnits = killed; 
    }
    virtual int getSoldierCount() = 0;
};
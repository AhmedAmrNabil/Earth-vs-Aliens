#pragma once

#include "../BattleUnits/Unit.h"
#include "../DataStructures/LinkedQueue.h"

class Army {
   public:
    Army(){}
    virtual bool addUnit(Unit* unit,bool isNew = false) = 0;
    virtual bool getUnit(UNIT_TYPE type, Unit*& unit) = 0;
    virtual bool peek(UNIT_TYPE type, Unit*& unit) = 0;
    virtual void print() = 0;
    virtual int getSoldierCount() = 0;
    virtual ~Army() {};
    //virtual void decrementCount(Unit*& unit) = 0;
};
#ifndef ARMY_H
#define ARMY_H

#include "../BattleUnits/Unit.h"

class Army {
   public:
    Army(){}
    virtual bool addUnit(Unit* unit,bool isNew = false) = 0;
    virtual bool getUnit(UNIT_TYPE type, Unit*& unit) = 0;
    virtual bool peek(UNIT_TYPE type, Unit*& unit) = 0;
    virtual bool fight() = 0;
    virtual void print() = 0;
    virtual bool isAlive() = 0;
    virtual ~Army() {};
};

#endif
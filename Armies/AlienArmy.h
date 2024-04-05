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
    AlienArmy() : Army() {
        monsterCount = 0;
        droneCount = 0;
        soldierCount = 0;
    }
   
    bool addUnit(Unit* unit);
    bool getUnit(UNIT_TYPE type, Unit*& unit, Unit*& unit2);
    void print();
    int getSoldierCount();
    void decrementCount(Unit*& unit);
};

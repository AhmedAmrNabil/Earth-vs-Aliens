#pragma once

#include "../DataStructures/ArrayMonster.h"
#include "./Army.h"
#include "../DataStructures/LinkedDeque.h"


class Unit;
class AlienDrone;
class AlienSoldier;
class AlienArmy : public Army {
    ArrayMonster alienMonsters;
    LinkedDeque<AlienDrone*> alienDrones;
    LinkedQueue<AlienSoldier*> alienSoldiers;
    int monsterCount;
    int soldierCount;
    int droneCount;
   public:
    AlienArmy() : Army() {
        monsterCount = 0;
        droneCount = 0;
        soldierCount = 0;
    }
   
    bool addUnit(UNIT_TYPE type, Unit* unit);
    bool getUnit(UNIT_TYPE type, Unit*& unit, Unit*& unit2);
    void print();
};

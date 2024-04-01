#pragma once

#include "../BattleUnits/Unit.h"
#include "../BattleUnits/AlienDrone.h"
#include "../BattleUnits/AlienMonster.h"
#include "../BattleUnits/Soldier.h"
#include "../DataStructures/ArrayMonster.h"
#include "./Army.h"

class AlienArmy : public Army {
    ArrayMonster arrayMonster;

   public:
    bool addUnit(UNIT_TYPE type, int joinTime, int health, int power, int attackCapacity) {
        switch (type)
        {
        case S:
        {
            Soldier* alienSoldier = new Soldier(joinTime, health, power, attackCapacity);
            if (alienSoldier == nullptr) return false;
            soldiers.enqueue(alienSoldier);
            break;
        }
        case AM:
        {
            AlienMonster* alienMonster = new AlienMonster(joinTime, health, power, attackCapacity);
            if (alienMonster == nullptr) return false;
            arrayMonster.insert(alienMonster);
            break;
        }
        case AD:
        {
            AlienDrone* alienDrone = new AlienDrone(joinTime, health, power, attackCapacity);
            if (alienDrone == nullptr) return false;
            break;
        }
        }
        return true;
    }
    bool addExisting(UNIT_TYPE type, Unit* unit) {
        switch (type)
        {
        case S:
        {
            Soldier* S1 = dynamic_cast<Soldier*>(unit);
            if (S1)
                soldiers.enqueue(S1);
        } break;

        case AM:
        {
            AlienMonster* A1 = dynamic_cast<AlienMonster*>(unit);
            if (A1)
                arrayMonster.insert(A1);
            break;
        }
        case AD:
        {
            AlienDrone* alienDrone = dynamic_cast<AlienDrone*>(unit);
            break;
        }
        }
    }
    bool getUnit(UNIT_TYPE type, Unit*& unit, Unit*& unit2) 
    {
        switch (type) 
        {
        case S: 
        {
            if (soldiers.isEmpty())return false;
            Soldier* S1 = nullptr;
            soldiers.dequeue(S1);
            unit = dynamic_cast<Unit*>(S1);
            unit2 = nullptr;
            break;
        } 
        case AM: 
        {
            if (arrayMonster.isEmpty())return false;
            AlienMonster* AM = nullptr;
            arrayMonster.pick(AM);
            unit = dynamic_cast<Unit*>(AM);
            unit2 = nullptr;
            break;
        }
        case AD: 
        {
            //AlienDrone* alienDrone = new AlienDrone(joinTime, health, power, attackCapacity);
            //if (alienDrone == nullptr) return false;
            break;
        } 
        }
    }
};
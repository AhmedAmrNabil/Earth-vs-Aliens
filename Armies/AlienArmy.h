#pragma once

#include "../BattleUnits/Unit.h"
#include "../BattleUnits/AlienDrone.h"
#include "../BattleUnits/AlienMonster.h"
#include "../DataStructures/ArrayMonster.h"
#include "../BattleUnits/AlienSoldier.h"
#include "./Army.h"
#include "../DataStructures/LinkedDeque.h"

class AlienArmy : public Army {
    ArrayMonster alienMonsters;
    LinkedDeque<AlienDrone*> alienDrones;
    LinkedQueue<AlienSoldier*> alienSoldiers;
    int monsterCount;
    int soldierCount;
    int droneCount;
   public:
    AlienArmy(LinkedQueue <Unit*>* killed) : Army(killed) {
        monsterCount = 0;
        droneCount = 0;
        soldierCount = 0;
        lastAlienId = 2000;
    }
    bool addUnit(UNIT_TYPE type, int joinTime, int health, int power, int attackCapacity) {
        switch (type)
        {
        case AS:
        {
            AlienSoldier* alienSoldier = new AlienSoldier(lastAlienId++, joinTime, health, power, attackCapacity);
            if (alienSoldier == nullptr) return false;
            alienSoldiers.enqueue(alienSoldier);
            soldierCount++;
            break;
        }
        case AM:
        {
            AlienMonster* alienMonster = new AlienMonster(lastAlienId++, joinTime, health, power, attackCapacity);
            if (alienMonster == nullptr) return false;
            alienMonsters.insert(alienMonster);
            monsterCount++;
            break;
        }
        case AD:
        {
            AlienDrone* alienDrone = new AlienDrone(lastAlienId++,joinTime, health, power, attackCapacity);
            if (alienDrone == nullptr) return false;
            droneCount++;
            alienDrones.enqueue(alienDrone);
            break;
        }
        }
        return true;
    }
    bool addExisting(UNIT_TYPE type, Unit* unit) {
        switch (type)
        {
        case AS:
        {
            AlienSoldier* S1 = dynamic_cast<AlienSoldier*>(unit);
            if (S1) {
                alienSoldiers.enqueue(S1);
                soldierCount++;
            }
        } break;

        case AM:
        {
            AlienMonster* A1 = dynamic_cast<AlienMonster*>(unit);
            if (A1) {
                alienMonsters.insert(A1);
                monsterCount++;
            }
            break;
        }
        case AD:
        {
            AlienDrone* A2= dynamic_cast<AlienDrone*>(unit);
            if (A2) {
                alienDrones.enqueue(A2);
                droneCount++;
            }
            break;
        }
        }
        return true;
    }
    bool getUnit(UNIT_TYPE type, Unit*& unit, Unit*& unit2) 
    {
        switch (type) 
        {
        case AS: 
        {
            if (alienSoldiers.isEmpty())return false;
            AlienSoldier* S1 = nullptr;
            alienSoldiers.dequeue(S1);
            unit = dynamic_cast<Unit*>(S1);
            unit2 = nullptr;
            soldierCount--;
            break;
        } 
        case AM: 
        {
            if (alienMonsters.isEmpty())return false;
            AlienMonster* AM = nullptr;
            alienMonsters.pick(AM);
            unit = dynamic_cast<Unit*>(AM);
            unit2 = nullptr;
            monsterCount--;
            break;
        }
        case AD: 
        {
            if (alienDrones.isEmpty())return false;
            AlienDrone* AD1 = nullptr;
            AlienDrone* AD2 = nullptr;
            alienDrones.dequeue(AD1);
            alienDrones.dequeueRear(AD2);
            unit = dynamic_cast<Unit*>(AD1);
            unit2 = dynamic_cast<Unit*>(AD2);
            droneCount--;
            break;
        } 
        }
        return true;
    }
    void print() {

    }
};

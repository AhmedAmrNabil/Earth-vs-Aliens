#pragma once
#include <iostream>
#include "../DataStructures/LinkedListStack.h"
#include "../BattleUnits/EarthGunner.h"
#include "../BattleUnits/EarthTank.h"
#include "../BattleUnits/Soldier.h"
#include "../BattleUnits/Unit.h"
#include "../DataStructures/priQueue.h"
#include "Army.h"
using namespace std;

class Soldier;

class EarthArmy : public Army {
    priQueue<EarthGunner*> earthGunnery;
    LinkedListStack<EarthTank*> earthTanks;

   public:
    bool addUnit(UNIT_TYPE type, int joinTime, int health, int power, int attackCapacity) {
        switch (type) {
            case S:
            {
                Soldier* earthSoldier = new Soldier(joinTime, health, power, attackCapacity);
                soldiers.enqueue(earthSoldier);
                break;
            }
            case ET:
            {
                EarthTank* tank = new EarthTank(joinTime, health, power, attackCapacity);
                earthTanks.push(tank);
                break;
            }
            case EG: {
                EarthGunner* earthGunner = new EarthGunner(joinTime, health, power, attackCapacity);
                earthGunnery.enqueue(earthGunner, earthGunner->getPriority());
                break;
            }
        }
    }
    bool addExisting(UNIT_TYPE type, Unit* unit) {
        switch (type) {
            case S:
            {
                Soldier* S1 = dynamic_cast<Soldier*>(unit);
                if (S1)
                    soldiers.enqueue(S1);
                break;
            }
            case ET:
            {
                EarthTank* T1 = dynamic_cast<EarthTank*>(unit);
                if (T1)
                    earthTanks.push(T1);
                break;
            }
            case EG:
            {
                EarthGunner* G1 = dynamic_cast<EarthGunner*>(unit);
                if (G1)
                    earthGunnery.enqueue(G1, G1->getPriority());
                break;
            }
        }
    }

    bool getUnit(UNIT_TYPE type, Unit*& unit,Unit*& unit2) {
        switch (type) {
            case (S):
            {
                if (soldiers.isEmpty()) return false;
                Soldier* s1;
                soldiers.dequeue(s1);
                unit = dynamic_cast<Unit*>(s1);
                break;
            }
            case (EG):
            {
                if (earthGunnery.isEmpty()) return false;
                EarthGunner* Gunner;
                int priority;
                earthGunnery.dequeue(Gunner, priority);
                unit = dynamic_cast<Unit*>(Gunner);
                return true;
            }
            case (ET):
            {
                if (earthTanks.isEmpty()) return false;
                EarthTank* tank1;
                earthTanks.pop(tank1);
                unit = dynamic_cast<Unit*>(tank1);
                break;
            }
        }
        unit2 = nullptr;
        return true;
    }
};
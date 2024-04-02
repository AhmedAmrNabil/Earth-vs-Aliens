#pragma once
#include <iostream>
#include "../DataStructures/LinkedListStack.h"
#include "../BattleUnits/EarthGunner.h"
#include "../BattleUnits/EarthTank.h"
#include "../BattleUnits/EarthSoldier.h"
#include "../BattleUnits/Unit.h"
#include "../DataStructures/priQueue.h"
#include "Army.h"
using namespace std;

class EarthArmy : public Army {
    priQueue<EarthGunner*> earthGunnery;
    LinkedListStack<EarthTank*> earthTanks;
    LinkedQueue<EarthSoldier*> earthSoldiers;
    int tankCount;
    int gunnerCount;
    int soldierCount;
   public:
    EarthArmy(LinkedQueue <Unit*>* killed): Army(killed) {
        tankCount = 0;
        gunnerCount = 0;
        soldierCount = 0;
        lastEarthId = 1;
    }
    bool addUnit(UNIT_TYPE type, int joinTime, int health, int power, int attackCapacity) {
        switch (type) {
            case ES:
            {
                EarthSoldier* earthSoldier = new EarthSoldier(lastEarthId++,joinTime, health, power, attackCapacity);
                earthSoldiers.enqueue(earthSoldier);
                soldierCount++;
                break;
            }
            case ET:
            {
                EarthTank* tank = new EarthTank(lastEarthId++, joinTime, health, power, attackCapacity);
                earthTanks.push(tank);
                tankCount++;
                break;
            }
            case EG: {
                EarthGunner* earthGunner = new EarthGunner(lastEarthId++, joinTime, health, power, attackCapacity);
                earthGunnery.enqueue(earthGunner, earthGunner->getPriority());
                gunnerCount++;
                break;
            }
        }
        return true;
    }
    bool addExisting(UNIT_TYPE type, Unit* unit) {
        switch (type) {
            case ES:
            {
                EarthSoldier* S1 = dynamic_cast<EarthSoldier*>(unit);
                if (S1) {
                    earthSoldiers.enqueue(S1);
                    soldierCount++;
                }
                break;
            }
            case ET:
            {
                EarthTank* T1 = dynamic_cast<EarthTank*>(unit);
                if (T1) {
                    earthTanks.push(T1);
                    tankCount++;
                }
                break;
            }
            case EG:
            {
                EarthGunner* G1 = dynamic_cast<EarthGunner*>(unit);
                if (G1) {
                    earthGunnery.enqueue(G1, G1->getPriority());
                    gunnerCount++;
                }
                break;
            }
        }
        return true;
    }

    bool getUnit(UNIT_TYPE type, Unit*& unit,Unit*& unit2) {
        switch (type) {
            case (ES):
            {
                if (earthSoldiers.isEmpty()) return false;
                EarthSoldier* s1;
                earthSoldiers.dequeue(s1);
                unit = dynamic_cast<Unit*>(s1);
                soldierCount--;
                break;
            }
            case (EG):
            {
                if (earthGunnery.isEmpty()) return false;
                EarthGunner* Gunner;
                int priority;
                earthGunnery.dequeue(Gunner, priority);
                unit = dynamic_cast<Unit*>(Gunner);
                gunnerCount--;
                return true;
                break;
            }
            case (ET):
            {
                if (earthTanks.isEmpty()) return false;
                EarthTank* tank1;
                earthTanks.pop(tank1);
                unit = dynamic_cast<Unit*>(tank1);
                tankCount--;
                break;
            }
        }
        unit2 = nullptr;
        return true;
    }
    void print() {
        cout << "============== Earth Army Alive Units =============\n";
        cout << soldierCount << "  ES";
        earthSoldiers.print();
        cout << endl;
        cout << tankCount << "  ET";
        earthTanks.print();
        cout << endl;
        cout << gunnerCount << "  EG";
        earthGunnery.print();
        cout << endl;
    }
};

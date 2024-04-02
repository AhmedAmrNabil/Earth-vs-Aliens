#pragma once
#include <iostream>
#include "../DataStructures/LinkedListStack.h"
#include "../DataStructures/priQueue.h"
#include "Army.h"
using namespace std;


class Unit;
class EarthGunner;
class EarthTank;
class EarthSoldier;
class EarthArmy : public Army {
    priQueue<EarthGunner*> earthGunnery;
    LinkedListStack<EarthTank*> earthTanks;
    LinkedQueue<EarthSoldier*> earthSoldiers;
    int tankCount;
    int gunnerCount;
    int soldierCount;
   public:
    EarthArmy(): Army() {
        tankCount = 0;
        gunnerCount = 0;
        soldierCount = 0;
    }
    
    bool addUnit(UNIT_TYPE type, Unit* unit);
    bool getUnit(UNIT_TYPE type, Unit*& unit, Unit*& unit2);

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

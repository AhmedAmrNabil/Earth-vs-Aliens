#include "AlienArmy.h"
#include "../BattleUnits/AlienDrone.h"
#include "../BattleUnits/AlienSoldier.h"
#include "../BattleUnits/AlienMonster.h"

bool AlienArmy::addUnit(Unit* unit) {
    UNIT_TYPE type = unit->getType();
    switch (type)
    {
        case AS:
        {
            //AlienSoldier* S1 = dynamic_cast<AlienSoldier*>(unit);
            if (unit) {
                alienSoldiers.enqueue(unit);
                soldierCount++;
            }
        } break;

        case AM:
        {

            //AlienMonster* A1 = dynamic_cast<AlienMonster*>(unit);
            if (unit) {
                alienMonsters.insert(unit);
                monsterCount++;
            }
            break;
        }
        case AD:
        {
            //AlienDrone* A2 = dynamic_cast<AlienDrone*>(unit);
            if (unit) {
                alienDrones.enqueue(unit);
                droneCount++;
            }
            break;
        }
    }
    return true;
}


bool AlienArmy::getUnit(UNIT_TYPE type, Unit*& unit, Unit*& unit2)
{
    switch (type)
    {
        case AS:
        {
            if (alienSoldiers.isEmpty())return false;
            Unit* S1 = nullptr;
            alienSoldiers.dequeue(S1);
            //unit = dynamic_cast<Unit*>(S1);
            unit = S1;
            unit2 = nullptr;
            break;
        }
        case AM:
        {
            if (alienMonsters.isEmpty())return false;
            Unit* AM = nullptr;
            alienMonsters.pick(AM);
            //unit = dynamic_cast<Unit*>(AM);
            unit = AM;
            unit2 = nullptr;
            break;
        }
        case AD:
        {
            if (alienDrones.isEmpty())return false;
            Unit* AD1 = nullptr;
            Unit* AD2 = nullptr;
            alienDrones.dequeue(AD1);
            alienDrones.dequeueRear(AD2);
            /*unit = dynamic_cast<Unit*>(AD1);
            unit2 = dynamic_cast<Unit*>(AD2); */
            unit = AD1;
            unit2 = AD2;
            break;
        }
    }
    return true;
}

void AlienArmy::print()
{
    cout << "============== Alien Army Alive Units =============\n";
    cout << soldierCount << "\tAS ";
    alienSoldiers.print();
    cout << endl;
    cout << monsterCount << "\tAM ";
    alienMonsters.print();
    cout << endl;
    cout << droneCount << "\tAD ";
    alienDrones.print();
    cout << endl;
}

int AlienArmy::getSoldierCount()
{
    return soldierCount;
}

void AlienArmy::decrementCount(Unit*& unit) {
    switch (unit->getType()) {
    case(AS):
        if(soldierCount > 0)--soldierCount;
        break;
    case(AM):
        if (monsterCount > 0)--monsterCount;
        break;
    case(AD):
        if (droneCount > 0)--droneCount;
        break;
    }
}
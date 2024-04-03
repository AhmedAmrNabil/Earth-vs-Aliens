#include "EarthArmy.h"

#include "../BattleUnits/EarthGunner.h"
#include "../BattleUnits/EarthSoldier.h"
#include "../BattleUnits/EarthTank.h"


bool EarthArmy::addUnit(Unit* unit) {
    UNIT_TYPE type = unit->getType();
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

bool EarthArmy::getUnit(UNIT_TYPE type, Unit*& unit, Unit*& unit2) {
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

void EarthArmy::print()
{
    cout << "============== Earth Army Alive Units =============\n";
    cout << soldierCount << "\tES ";
    earthSoldiers.print();
    cout << endl;
    cout << tankCount << "\tET ";
    earthTanks.print();
    cout << endl;
    cout << gunnerCount << "\tEG ";
    earthGunnery.print();
    cout << endl;
}

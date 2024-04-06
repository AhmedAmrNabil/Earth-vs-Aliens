#include "AlienArmy.h"

#include "../BattleUnits/Unit.h"

bool AlienArmy::addUnit(Unit* unit) {
    if (unit == nullptr) return false;
    UNIT_TYPE type = unit->getType();
    bool inserted = false;
    switch (type) {
        case AS: {
            inserted = alienSoldiers.enqueue(unit);
            if (inserted)
                ++soldierCount;
            break;
        }

        case AM: {
            inserted = alienMonsters.insert(unit);
            if (inserted)
                ++monsterCount;
            break;
        }
        case AD: {
            inserted = alienDrones.enqueue(unit);
            if (inserted)
                ++droneCount;
            break;
        }
    }
    return inserted;
}

bool AlienArmy::getUnit(UNIT_TYPE type, Unit*& unit, Unit*& unit2) {
    unit2 = nullptr;
    switch (type) {
        case AS: {
            if (alienSoldiers.isEmpty()) return false;
            alienSoldiers.dequeue(unit);
            break;
        }
        case AM: {
            if (alienMonsters.isEmpty()) return false;
            alienMonsters.pick(unit);
            break;
        }
        case AD: {
            if (alienDrones.isEmpty()) return false;
            alienDrones.dequeue(unit);
            alienDrones.dequeueRear(unit2);
            break;
        }
    }
    return true;
}

void AlienArmy::print() {
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

int AlienArmy::getSoldierCount() {
    return soldierCount;
}

void AlienArmy::decrementCount(Unit*& unit) {
    if (unit == nullptr) return;
    switch (unit->getType()) {
        case (AS):
            if (soldierCount > 0) --soldierCount;
            break;
        case (AM):
            if (monsterCount > 0) --monsterCount;
            break;
        case (AD):
            if (droneCount > 0) --droneCount;
            break;
    }
}
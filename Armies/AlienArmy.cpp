#include "AlienArmy.h"

#include "../BattleUnits/Unit.h"

bool AlienArmy::addUnit(Unit* unit) {
    bool inserted = false;
    UNIT_TYPE type = unit->getType();
    switch (type) {
        case AS: {
            if (unit) {
                inserted = alienSoldiers.enqueue(unit);
                ++soldierCount;
            }
        } break;

        case AM: {
            if (unit) {
                inserted = alienMonsters.insert(unit);
                ++monsterCount;
            }
            break;
        }
        case AD: {
            if (unit) {
                inserted = alienDrones.enqueue(unit);
                ++droneCount;
            }
            break;
        }
    }
    return inserted;
}

bool AlienArmy::getUnit(UNIT_TYPE type, Unit*& unit, Unit*& unit2) {
    bool extracted = false;
    unit2 = nullptr;
    switch (type) {
        case AS: {
            if (alienSoldiers.isEmpty()) return false;
            extracted = alienSoldiers.dequeue(unit);
            break;
        }
        case AM: {
            if (alienMonsters.isEmpty()) return false;
            extracted = alienMonsters.pick(unit);
            break;
        }
        case AD: {
            if (alienDrones.isEmpty()) return false;
            extracted = alienDrones.dequeue(unit);
            alienDrones.dequeueRear(unit2);
            break;
        }
    }
    return extracted;
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
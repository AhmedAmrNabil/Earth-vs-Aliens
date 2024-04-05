#include "EarthArmy.h"

#include "../BattleUnits/Unit.h"

bool EarthArmy::addUnit(Unit* unit) {
    UNIT_TYPE type = unit->getType();
	bool inserted = false;
    switch (type) {
        case ES: {
            if (unit) {
                inserted = earthSoldiers.enqueue(unit);
                ++soldierCount;
            }
            break;
        }
        case ET: {
            if (unit) {
                inserted = earthTanks.push(unit);
                ++tankCount;
            }
            break;
        }
        case EG: {
            if (unit) {
                inserted = earthGunnery.enqueue(unit, unit->getPriority());
                ++gunnerCount;
            }
            break;
        }
    }
    return inserted;
}

bool EarthArmy::getUnit(UNIT_TYPE type, Unit*& unit, Unit*& unit2) {
	bool extracted = false;
    switch (type) {
        case (ES): {
            if (earthSoldiers.isEmpty()) return false;
            extracted = earthSoldiers.dequeue(unit);
            break;
        }
        case (EG): {
			int priority;
            if (earthGunnery.isEmpty()) return false;
			extracted = earthGunnery.dequeue(unit,priority);
            break;
        }
        case (ET): {
            if (earthTanks.isEmpty()) return false;
            extracted = earthTanks.pop(unit);
            break;
        }
    }
    unit2 = nullptr;
    return extracted;
}

void EarthArmy::print() {
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

int EarthArmy::getSoldierCount() {
    return soldierCount;
}

void EarthArmy::decrementCount(Unit*& unit) {
	if(unit == nullptr)return;
    switch (unit->getType()) {
        case (ES):
            if (soldierCount > 0) --soldierCount;
            break;
        case (ET):
            if (tankCount > 0) --tankCount;
            break;
        case (EG):
            if (gunnerCount > 0) --gunnerCount;
            break;
    }
}
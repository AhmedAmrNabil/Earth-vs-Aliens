#include "EarthArmy.h"

#include "../BattleUnits/Unit.h"

bool EarthArmy::addUnit(Unit* unit) {
    if(unit == nullptr)return false;
    UNIT_TYPE type = unit->getType();
	bool inserted = false;
    switch (type) {
        case ES: {
                inserted = earthSoldiers.enqueue(unit);
                if(inserted)
                    ++soldierCount;
            break;
        }
        case ET: {
                inserted = earthTanks.push(unit);
                if(inserted)
                    ++tankCount;
            break;
        }
        case EG: {
                inserted = earthGunnery.enqueue(unit, unit->getPriority());
                if(inserted)
                    ++gunnerCount;
            break;
        }
    }
    return inserted;
}

bool EarthArmy::getUnit(UNIT_TYPE type, Unit*& unit,bool rear = false) {
    switch (type) {
        case (ES): {
            if (earthSoldiers.isEmpty()) return false;
            earthSoldiers.dequeue(unit);
            break;
        }
        case (EG): {
			int priority;
            if (earthGunnery.isEmpty()) return false;
			earthGunnery.dequeue(unit,priority);
            break;
        }
        case (ET): {
            if (earthTanks.isEmpty()) return false;
            earthTanks.pop(unit);
            break;
        }
    }
    return true;
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
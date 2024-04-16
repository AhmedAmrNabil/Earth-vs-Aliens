#include "EarthArmy.h"

#include "../BattleUnits/Unit.h"
EarthArmy::EarthArmy() : Army() {
	tankCount = 0;
	gunnerCount = 0;
	soldierCount = 0;
}

bool EarthArmy::addUnit(Unit* unit,bool isNew) {
	if (unit == nullptr)return false;
	UNIT_TYPE type = unit->getType();
	bool inserted = false;
	switch (type) {
	case ES: {
		inserted = earthSoldiers.enqueue(unit);
		if (inserted && isNew)
			++soldierCount;
		break;
	}
	case ET: {
		inserted = earthTanks.push(unit);
		if (inserted && isNew)
			++tankCount;
		break;
	}
	case EG: {
		inserted = earthGunnery.enqueue(unit, unit->getPriority());
		if (inserted && isNew)
			++gunnerCount;
		break;
	}
	}
	return inserted;
}

bool EarthArmy::getUnit(UNIT_TYPE type, Unit*& unit, bool rear) {
	switch (type) {
	case (ES): {
		if (earthSoldiers.isEmpty()) return false;
		earthSoldiers.dequeue(unit);
		break;
	}
	case (EG): {
		int priority;
		if (earthGunnery.isEmpty()) return false;
		earthGunnery.dequeue(unit, priority);
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
	cout << earthSoldiers.getCount() << "\tES ";
	earthSoldiers.print();
	cout << endl;
	cout << earthTanks.getCount() << "\tET ";
	earthTanks.print();
	cout << endl;
	cout << earthGunnery.getCount() << "\tEG ";
	earthGunnery.print();
	cout << endl;
}

int EarthArmy::getSoldierCount() {
	return soldierCount;
}

//void EarthArmy::decrementCount(Unit*& unit) {
//	if (unit == nullptr)return;
//	switch (unit->getType()) {
//	case (ES):
//		if (soldierCount > 0) --soldierCount;
//		break;
//	case (ET):
//		if (tankCount > 0) --tankCount;
//		break;
//	case (EG):
//		if (gunnerCount > 0) --gunnerCount;
//		break;
//	}
//}
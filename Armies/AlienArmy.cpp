#include "AlienArmy.h"

#include "../BattleUnits/Unit.h"

AlienArmy::AlienArmy() {
	monsterCount = 0;
	droneCount = 0;
	soldierCount = 0;
}


bool AlienArmy::addUnit(Unit* unit, bool isNew) {
	if (unit == nullptr) return false;
	UNIT_TYPE type = unit->getType();
	bool inserted = false;
	switch (type) {
	case AS: {
		inserted = alienSoldiers.enqueue(unit);
		if (inserted && isNew)
			++soldierCount;
		break;
	}

	case AM: {
		inserted = alienMonsters.insert(unit);
		if (inserted && isNew)
			++monsterCount;
		break;
	}
	case AD: {
		inserted = alienDrones.enqueue(unit);
		if (inserted && isNew)
			++droneCount;
		break;
	}
	}
	return inserted;
}

bool AlienArmy::getUnit(UNIT_TYPE type, Unit*& unit, bool rear) {
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
		if (rear)
			alienDrones.dequeueRear(unit);
		else
			alienDrones.dequeue(unit);
		break;
	}
	}
	return true;
}

void AlienArmy::print() {
	cout << "============== Alien Army Alive Units =============\n";
	cout << alienSoldiers.getCount() << "\tAS ";
	alienSoldiers.print();
	cout << endl;
	cout << alienMonsters.getCount() << "\tAM ";
	alienMonsters.print();
	cout << endl;
	cout << alienDrones.getCount() << "\tAD ";
	alienDrones.print();
	cout << endl;
}

int AlienArmy::getSoldierCount() {
	return soldierCount;
}

//void AlienArmy::decrementCount(Unit*& unit) {
//	if (unit == nullptr) return;
//	switch (unit->getType()) {
//	case (AS):
//		if (soldierCount > 0) --soldierCount;
//		break;
//	case (AM):
//		if (monsterCount > 0) --monsterCount;
//		break;
//	case (AD):
//		if (droneCount > 0) --droneCount;
//		break;
//	}
//}
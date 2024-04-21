#include "EarthArmy.h"
#include "../BattleUnits/Unit.h"
#include "../BattleUnits/EarthGunnery.h"
EarthArmy::EarthArmy() : Army() {
	tankCount = 0;
	gunnerCount = 0;
	soldierCount = 0;
}

bool EarthArmy::addUnit(Unit* unit, bool isNew) {
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
		int priority;
		EarthGunnery* earthGunner = dynamic_cast<EarthGunnery*>(unit);
		if (earthGunner != nullptr) {
			priority = earthGunner->getPriority();
			inserted = earthGunnery.enqueue(unit, priority);
			if (inserted && isNew)
				++gunnerCount;
		}
		break;
	}
	}
	return inserted;
}

bool EarthArmy::getUnit(UNIT_TYPE type, Unit*& unit) {
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

bool EarthArmy::peek(UNIT_TYPE type, Unit*& unit)
{
	switch (type) {
	case (ES): {
		if (earthSoldiers.isEmpty()) return false;
		earthSoldiers.peek(unit);
		break;
	}
	case (EG): {
		int priority;
		if (earthGunnery.isEmpty()) return false;
		earthGunnery.peek(unit, priority);
		break;
	}
	case (ET): {
		if (earthTanks.isEmpty()) return false;
		earthTanks.peek(unit);
		break;
	}
	}
	return true;
}

void EarthArmy::fight(Game* game)
{
	Unit *S,*T,*G;
	int pri;
	if(earthSoldiers.peek(S)){
		cout << "ES " << S << " shots ";
		S->attack();
		cout << "\n";
	}
	if (earthTanks.peek(T)) {
		cout << "ET " << T << " shots ";
		T->attack();
		cout << "\n";
	}
	if (earthGunnery.peek(G, pri)) {
		cout << "EG " << G << " shots ";
		G->attack();
		cout << "\n";
	}
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
	return earthSoldiers.getCount();
}

EarthArmy::~EarthArmy() {
	Unit* unit;
	int pri;
	while (earthSoldiers.dequeue(unit))
	{
		if (unit != nullptr)
			delete unit;
	}
	while (earthTanks.pop(unit)) 
	{
		if (unit != nullptr)
			delete unit;
	}
	while (earthGunnery.dequeue(unit, pri)) 
	{
		if (unit != nullptr)
			delete unit;
	}
}

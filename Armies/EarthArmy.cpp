#include "EarthArmy.h"
#include "../BattleUnits/Unit.h"
#include "../BattleUnits/EarthGunnery.h"

EarthArmy::EarthArmy() : Army() {
	tankCount = 0;
	gunnerCount = 0;
	soldierCount = 0;
	healCount = 0;
}

bool EarthArmy::addUnit(Unit* unit, bool isNew) {
	if (unit == nullptr)return false;
	UNIT_TYPE type = unit->getType();
	bool inserted = false;
	switch (type) {
	case HU: {
		inserted = HL.push(unit);
		if (inserted && isNew)
			++healCount;
		break;
	}
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
	case HU: {
		if (HL.isEmpty()) return false;
		HL.pop(unit);
		break;
	}
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
	case HU: {
		if (HL.isEmpty()) return false;
		HL.peek(unit);
		break;
	}
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

bool EarthArmy::fight()
{
	bool soldierAttack = false;
	bool tankAttack = false;
	bool gunneryAttack = false;
	Unit *S,*T,*G,*H;
	int pri;
	if (HL.pop(H)) {
		H->attack();
		if (!H->isDead())
			HL.push(H);
	}
	
	if(earthSoldiers.peek(S))
		soldierAttack = S->attack();
	
	if (earthTanks.peek(T)) 
		tankAttack = T->attack();
	
	if (earthGunnery.peek(G, pri)) 
		gunneryAttack = G->attack();
	return soldierAttack || tankAttack || gunneryAttack;
	
}

void EarthArmy::print() {
	cout << "\t============== Earth Army Alive Units =============\n";
	cout << "\t" << HL.getCount() << "\tHU ";
	HL.print();
	cout << endl;
	cout <<"\t" << earthSoldiers.getCount() << "\tES ";
	earthSoldiers.print();
	cout << endl;
	cout << "\t" << earthTanks.getCount() << "\tET ";
	earthTanks.print();
	cout << endl;
	cout << "\t" << earthGunnery.getCount() << "\tEG ";
	earthGunnery.print();
	cout << endl;
}

int EarthArmy::getSoldierCount() {
	return earthSoldiers.getCount();
}

int EarthArmy::getTotalSoldierCount() {
	return soldierCount;
}
int EarthArmy::getTotalGunneryCount() {
	return gunnerCount;
}
int EarthArmy::getTotalTankCount() {
	return tankCount;
}
int EarthArmy::getTotalHealCount() {
	return healCount;
}


bool EarthArmy::isAlive() {
	int totalCount = earthSoldiers.getCount() + earthTanks.getCount() + earthGunnery.getCount() ;
	return totalCount > 0;
}

EarthArmy::~EarthArmy() {
	Unit* unit;
	int pri;
	while (HL.pop(unit))
	{
		if (unit != nullptr)
			delete unit;
	}
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

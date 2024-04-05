#include "EarthArmy.h"

#include "../BattleUnits/EarthGunner.h"
#include "../BattleUnits/EarthSoldier.h"
#include "../BattleUnits/EarthTank.h"


bool EarthArmy::addUnit(Unit* unit) {
	UNIT_TYPE type = unit->getType();
	switch (type) {
	case ES:
	{
		//EarthSoldier* S1 = dynamic_cast<EarthSoldier*>(unit);
		if (unit) {
			earthSoldiers.enqueue(unit);
			soldierCount++;
		}
		break;
	}
	case ET:
	{
		//EarthTank* T1 = dynamic_cast<EarthTank*>(unit);
		if (unit) {
			earthTanks.push(unit);
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
		Unit* s1;
		earthSoldiers.dequeue(s1);
		//unit = dynamic_cast<Unit*>(s1);
		unit = s1;
		break;
	}
	case (EG):
	{
		if (earthGunnery.isEmpty()) return false;
		EarthGunner* Gunner;
		int priority;
		earthGunnery.dequeue(Gunner, priority);
		unit = dynamic_cast<Unit*>(Gunner);
		break;
	}
	case (ET):
	{
		if (earthTanks.isEmpty()) return false;
		Unit* tank1;
		earthTanks.pop(tank1);
		//unit = dynamic_cast<Unit*>(tank1);
		unit = tank1;
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

int EarthArmy::getSoldierCount()
{
	return soldierCount;
}

void EarthArmy::decrementCount(Unit*& unit) {
	switch (unit->getType()) {
		case(ES):
			if (soldierCount > 0)--soldierCount;
			break;
		case(ET):
			if (tankCount > 0)--tankCount;
			break;
		case(EG):
			if (gunnerCount > 0)--gunnerCount;
			break;
	}
}
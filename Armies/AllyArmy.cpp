#include "AllyArmy.h"
#include "../BattleUnits/Unit.h"

AllyArmy::AllyArmy() : Army() {
	saversCount = 0;
}

bool AllyArmy::addUnit(Unit* unit, bool isNew) {
	if (unit == nullptr)return false;
	bool inserted = saverUnits.enqueue(unit);
	if (inserted && isNew)++saversCount;
	return inserted;
}

bool AllyArmy::getUnit(UNIT_TYPE type, Unit*& unit) {
	if (saverUnits.isEmpty()) return false;
	saverUnits.dequeue(unit);
	return true;
}

bool AllyArmy::peek(UNIT_TYPE type, Unit*& unit) {
	if (saverUnits.isEmpty()) return false;
	saverUnits.peek(unit);
	return true;
}

bool AllyArmy::fight() {
	bool saverAttack = false;
	Unit* saver;

	if (saverUnits.peek(saver))
		saverAttack = saver->attack();

	return saverAttack;

}

int AllyArmy::getSaverCount() {
	return saverUnits.getCount();
}

void AllyArmy::print() {
	cout << "\t============== Ally Army Alive Units ==============\n";
	cout << "\t" << saverUnits.getCount() << "\tSU ";
	saverUnits.print();
	cout << endl;
}

bool AllyArmy::isAlive() {
	return saverUnits.getCount() > 0;
}

AllyArmy::~AllyArmy() {
	Unit* unit;
	while (saverUnits.dequeue(unit))
	{
		if (unit != nullptr)
			delete unit;
	}
}
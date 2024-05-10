#include "AlienArmy.h"

#include "../BattleUnits/Unit.h"

AlienArmy::AlienArmy() {
	monsterCount = 0;
	droneCount = 0;
	soldierCount = 0;
	insertRear = false;
	peekRear = false;
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
		if (insertRear)
			inserted = alienDrones.enqueue(unit);
		else
			inserted = alienDrones.enqeueFront(unit);
		if (inserted) {
			insertRear = !insertRear;
			if(isNew)
				++droneCount;
		}
		
		break;
	}
	}
	return inserted;
}

bool AlienArmy::getUnit(UNIT_TYPE type, Unit*& unit) {
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
		if (!insertRear) alienDrones.dequeueRear(unit);
		else alienDrones.dequeue(unit);
		insertRear = !insertRear;
		break;
	}
	}
	return true;
}
bool AlienArmy::peek(UNIT_TYPE type, Unit*& unit) {
	switch (type) 
	{
	case AS: 
	{
		if (alienSoldiers.isEmpty()) return false;
		alienSoldiers.peek(unit);
		break;
	}
	case AM:
	{
		if (alienMonsters.isEmpty()) return false;
		alienMonsters.peek(unit);
		break;
	}
	case AD: 
	{
		if (alienDrones.isEmpty()) return false;
		if (peekRear)
			alienDrones.peekRear(unit);
		else
			alienDrones.peek(unit);
		peekRear = !peekRear;
		break;
	}
	}
	return true;
}
bool AlienArmy::fight()
{
	bool soliderAttack = false;
	bool monsterAttack = false;
	bool droneAttack1 = false;
	bool droneAttack2 = false;
	Unit* M, * D1,*D2, * S;
	if (alienSoldiers.peek(S)) 
	{
		soliderAttack = S->attack();
	}
	if (alienMonsters.peek(M))
	{
		monsterAttack = M->attack();
	}
	if (alienDrones.peek(D1) && alienDrones.peekRear(D2) && D1 != D2) 
	{
		droneAttack1 = D1->attack();
		droneAttack2 = D2->attack();
	}
	return soliderAttack || monsterAttack || droneAttack1 || droneAttack2;
}
void AlienArmy::print() {
	cout << "\t============== Alien Army Alive Units =============\n";
	cout << "\t" << alienSoldiers.getCount() << "\tAS ";
	alienSoldiers.print();
	cout << endl;
	cout << "\t" << alienMonsters.getCount() << "\tAM ";
	alienMonsters.print();
	cout << endl;
	cout << "\t" << alienDrones.getCount() << "\tAD ";
	alienDrones.print();
	cout << endl;
}

int AlienArmy::getSoldierCount() {
	return alienSoldiers.getCount();
}

int AlienArmy::getTotalSoldierCount() {
	return soldierCount;
}

int AlienArmy::getTotalMonsterCount() {
	return monsterCount;
}

int AlienArmy::getTotalDroneCount() {
	return droneCount;
}

bool AlienArmy::isAlive() {
	int totalCount = alienSoldiers.getCount() + alienMonsters.getCount() + alienDrones.getCount();
	return totalCount > 0;
}

AlienArmy::~AlienArmy() {
	Unit* unit;
	while (alienSoldiers.dequeue(unit))
	{
		if (unit != nullptr)
			delete unit;
	}
	while (alienDrones.dequeue(unit))
	{
		if (unit != nullptr)
			delete unit;
	}
	while (alienMonsters.pick(unit))
	{
		if (unit != nullptr)
			delete unit;
	}
}

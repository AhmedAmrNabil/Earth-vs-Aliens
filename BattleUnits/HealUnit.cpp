#include "HealUnit.h"
#include "../Game.h"
#include "../DataStructures/LinkedQueue.h"


HealUnit::HealUnit(Game* game, int joinTime, double health, double power, int attackCapacity)
	: Unit(game, HU, joinTime, health, power, attackCapacity)
{
}

bool HealUnit::attack()
{
	bool attacked = false;
	if (game->isUMLEmpty()) return false;
	int timestep = game->getTimestep();
	Unit* unit;
	LinkedQueue<Unit*> tempList;
	LinkedQueue<Unit*> total;
	int healCount = this->getAttackCapacity();
	while (healCount) {
		if (game->getfromUML(unit)) {
			unit->getHealed(this);
			total.enqueue(unit);
			if (!unit->isLow()) game->addEarthUnit(unit);
			else tempList.enqueue(unit);
			--healCount;
			attacked = true;
		}
		else break;
	}
	if (!total.isEmpty() && game->isInteractive()) {
		cout << "\tHU " << this << " healed ";
		cout << "\t";
		total.print();
		cout << endl;
	}
	while (!tempList.isEmpty()) {
		tempList.dequeue(unit);
		game->handleUnit(unit);
	}
	while (!total.isEmpty()) {
		total.dequeue(unit);
	}
	if(healCount != this->getAttackCapacity()) { 
		this->decrementHealth(this->health,timestep);
		game->handleUnit(this);
	}
	return attacked;
}

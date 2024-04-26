#include "HealUnit.h"
#include "../Game.h"
#include "../DataStructures/LinkedQueue.h"


HealUnit::HealUnit(Game* game, int joinTime, double health, double power, int attackCapacity)
	: Unit(game, ET, joinTime, health, power, attackCapacity)
{
}

void HealUnit::attack()
{
	int timestep = game->getTimestep();
	Unit* unit;
	LinkedQueue<Unit*> tempList;
	int healCount = this->getAttackCapacity();
	while (healCount) {
		if (game->getfromUML(unit)) {
			unit->getHealed(this);
			if (!unit->isLow()) game->addEarthUnit(unit);
			else tempList.enqueue(unit);
			--healCount;
		}
		else break;
	}
	if (!tempList.isEmpty()) {
		cout << "\tHU " << this << " healed ";
		cout << "\t";
		tempList.print();
		cout << endl;
	}
	while (!tempList.isEmpty()) {
		tempList.dequeue(unit);
		game->handleUnit(unit);
	}
	//if(healCount != this->getAttackCapacity()) { 
		//this->health = 0; 
		//game->handleUnit(this);
	//}
}

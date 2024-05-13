#include "HealUnit.h"
#include "../Game.h"
#include "../DataStructures/LinkedQueue.h"
#include "EarthSoldier.h"

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
			EarthSoldier* soldier = dynamic_cast<EarthSoldier*>(unit);
			if (soldier && (soldier->isInfected() && !soldier->isImmune())) {
				soldier->setImmunity(true);
				game->decrementInfected();
				game->addToUML(unit , game->getTimestep());
			}
			else {
				unit->getHealed(this);
				total.enqueue(unit);
				if (!unit->isLow()) game->addEarthUnit(unit);
				else tempList.enqueue(unit);
				--healCount;
				attacked = true;
			}
		}
		else break;
	}
	if (game->isInteractive() && !tempList.isEmpty()) {
		string attackedIds = "\tHU ";
		attackedIds += this;
		attackedIds += " healed\t";
		if (tempList.dequeue(unit)) {
			attackedIds += "[";
			game->handleUnit(unit);
			attackedIds += unit;
			while (!tempList.isEmpty()) {
				tempList.dequeue(unit);
				game->handleUnit(unit);
				attackedIds += ", ";
				attackedIds += unit;
			}
			attackedIds += "]";
		}
		attackedIds += '\n';
		game->addToAttacked(attackedIds);
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

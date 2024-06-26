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

			// Check if infected to heal only half of the intended heal value
			if (soldier && (soldier->isInfected() && !soldier->isImmune())) {
				soldier->getHealed(this, true);
				if (!soldier->isLow()) {
					soldier->setImmunity(true);
					game->decrementInfected();
					game->addEarthUnit(unit);
					if (!soldier->isHealedBefore()) {
						soldier->setFullyHealed();
						game->incrementHealCount();
					}
				}
				else tempList.enqueue(unit);
			}
			else {
				unit->getHealed(this , false);
				if (!unit->isLow()) { 
					game->addEarthUnit(unit); 
					game->incrementHealCount();
					if (!unit->isHealedBefore()) {
						unit->setFullyHealed();
						game->incrementHealCount();
					}
				}
				else tempList.enqueue(unit);
			}
			total.enqueue(unit);
			--healCount;
			attacked = true;
		}
		else break;
	}

	// Prints the healed Units
	if (game->isInteractive() && !total.isEmpty()) {
		string attackedIds = "\tHU ";
		attackedIds += this;
		attackedIds += " healed\t";
		if (total.dequeue(unit)) {
			attackedIds += "[";
			attackedIds += unit;
			while (!total.isEmpty()) {
				total.dequeue(unit);
				attackedIds += ", ";
				attackedIds += unit;
			}
			attackedIds += "]";
		}
		attackedIds += '\n';
		game->addToAttacked(attackedIds);
	}

	// Handle healed units if the game is in silent mode
	while (!tempList.isEmpty()) {
		tempList.dequeue(unit);
		game->handleUnit(unit);
	}
	while (!total.isEmpty()) {
		total.dequeue(unit);
	}

	// Kills the heal unit if it healed someone
	if(healCount != this->getAttackCapacity()) { 
		this->decrementHealth(this->health,timestep);
		game->handleUnit(this);
	}
	return attacked;
}

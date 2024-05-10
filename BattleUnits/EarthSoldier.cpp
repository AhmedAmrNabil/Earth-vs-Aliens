#include "EarthSoldier.h"
#include "../Game.h"
#include "../DataStructures/LinkedQueue.h"


EarthSoldier::EarthSoldier(Game* game, int joinTime, double health, double power, int attackCapacity)
	: Unit(game, ES, joinTime, health, power, attackCapacity) {
	infected = false;
	immune = false;
}

bool EarthSoldier::attack() {
	int timestep = game->getTimestep();
	bool attacked = false;
	Unit* enemyUnit;
	LinkedQueue<Unit*> tempList;
	int soldierCount = this->getAttackCapacity();
	while (soldierCount) {
		if (!this->infected) {
			if (game->getAlienUnit(AS, enemyUnit)) {
				enemyUnit->getAttacked(this, timestep);
				tempList.enqueue(enemyUnit);
				attacked = true;
			}
			else break;
		}
		else {
			if (game->getEarthUnit(ES, enemyUnit)) {
				if (enemyUnit != this) {
					tempList.enqueue(enemyUnit);
					enemyUnit->getAttacked(this, timestep);
					attacked = true;
				}
				else game->handleUnit(enemyUnit);
			}
			else break;
		}
		--soldierCount;
	}
	Unit* infectUnit;
	if (!tempList.isEmpty() && game->isInteractive()) {
		cout << "\tES " << this << " shots ";
		cout << "\t";
		tempList.print();
		cout << endl;
	}
	while (!tempList.isEmpty()) {
		tempList.dequeue(enemyUnit);
		game->handleUnit(enemyUnit);
	}
	if (this->infected) 
	{
		if (game->spreadInfect(infectUnit)) {
			EarthSoldier* s1 = dynamic_cast<EarthSoldier*>(infectUnit);
			s1->setInfected(true);
			game->addEarthUnit(infectUnit);
			game->incrementInfected();
		}
	}
	return attacked;
}

bool EarthSoldier::isInfected()
{
	return infected;
}

void EarthSoldier::setInfected(bool b)
{
	infected = b;
}

bool EarthSoldier::isImmune()
{
	return immune;
}

void EarthSoldier::setImmunity(bool b)
{
	immune = b;
}

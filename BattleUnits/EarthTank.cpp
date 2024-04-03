#include "EarthTank.h"

void EarthTank::attack(Game* game, int timestep)
{
	Unit* monster;
	Unit* soldier;
	Unit* tmp;
	bool monstersOnly = true;
	if (game->getSoldierRatio() < 30) monstersOnly = false;
	clearAttacked();
	for (int i = 0; i < this->getAttackCapacity(); ++i) {
		if (game->getAlienUnit(AM, monster, tmp))
		{
			monster->getAttacked(this, timestep);
			attackedUnits.enqueue(monster);
			if (monster->isDead())
				game->addToKilled(monster);
			else
				game->addToTemp(monster);
		}
		if (game->getSoldierRatio() > 80) monstersOnly = true;
		if (!monstersOnly) {
			if (game->getAlienUnit(AS, soldier, tmp))
			{
				soldier->getAttacked(this, timestep);
				attackedUnits.enqueue(soldier);
				if (soldier->isDead())
					game->addToKilled(soldier);
				else
					game->addToTemp(monster);
			}
		}
	}
}

#include "EarthTank.h"

void EarthTank::attack(Game* game, int timestep)
{
	Unit* monster;
	Unit* soldier;
	Unit* tmp;
	bool monstersOnly = true;  
	LinkedQueue<Unit*> temp;
	ArrayMonster tmpMonsters;
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
				tmpMonsters.insert(monster);
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
					temp.enqueue(soldier);
			}
		}
	}
	while (!temp.isEmpty())
	{
		temp.dequeue(soldier);
		game->addAlienUnit(soldier);
	}
	while (!tmpMonsters.isEmpty())
	{
		tmpMonsters.pick(monster);
		game->addAlienUnit(monster);
	}
}

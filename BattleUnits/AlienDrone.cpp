#include "AlienDrone.h"
#include "../Game.h"


void AlienDrone::attack(Game* game, int timestep)
{
	LinkedListStack<Unit*> tempEarthTanks;
	Unit* T1 = nullptr;
	Unit* G1 = nullptr;
	for (int i = 0; i < this->getAttackCapacity(); ++i)
	{
		if (game->getEarthUnit(ET, T1))
		{
			T1->getAttacked(this, timestep);
			if (T1->isDead())
				game->addToKilled(T1);
			else
				tempEarthTanks.push(T1);
		}
		if (game->getEarthUnit(EG, G1))
		{
			G1->getAttacked(this, timestep);
			if (G1->isDead())
				game->addToKilled(G1);
			else
				game->addEarthUnit(EG, G1);

		}
	}
	Unit* temp = nullptr;
	while (!tempEarthTanks.isEmpty())
	{
		tempEarthTanks.pop(temp);
		game->addEarthUnit(ET, temp);
	}
}

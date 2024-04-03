#include "AlienDrone.h"
#include "../Game.h"


void AlienDrone::attack(Game* game, int timestep)
{
	
	Unit* tank = nullptr;
	Unit* gunnery = nullptr;
	for (int i = 0; i < this->getAttackCapacity(); ++i)
	{
		if (game->getEarthUnit(ET, tank))
		{
			tank->getAttacked(this, timestep);
			if (tank->isDead())
				game->addToKilled(tank);
			else
				game->addToTemp(tank);
		}
		if (game->getEarthUnit(EG, gunnery))
		{
			gunnery->getAttacked(this, timestep);
			if (gunnery->isDead())
				game->addToKilled(gunnery);
			else
				game->addToTemp(gunnery);

		}
	}
	
}

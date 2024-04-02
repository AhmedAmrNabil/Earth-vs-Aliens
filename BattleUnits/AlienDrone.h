#pragma once
#include "../Game.h"
#include "../DataStructures/LinkedListStack.h"

class AlienDrone :public Unit
{
public:
	AlienDrone(int id, int joinTime, int health, int power, int attackCapacity) 
		:Unit(AM, id,joinTime, health, power, attackCapacity)
	{}
	void attack(Game* game, int timestep) 
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
					game->addExistingEarthUnit(EG, G1);

			}
		}
		Unit* temp = nullptr;
		while (!tempEarthTanks.isEmpty())
		{
			tempEarthTanks.pop(temp);
			game->addExistingEarthUnit(ET, temp);
		}
	}
	
};
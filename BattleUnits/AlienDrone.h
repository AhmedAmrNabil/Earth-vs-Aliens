#pragma once

class AlienDrone :public Unit
{
public:
	AlienDrone(int joinTime, int health, int power, int attackCapacity) :Unit(AM, joinTime, health, power, attackCapacity)
	{}
	void attack(Army* enemyArmy, int timestep) 
	{
		LinkedListStack<Unit*> tempEarthTanks;
		Unit* T1 = nullptr;
		Unit* G1 = nullptr;
		Unit* tmp;
		for (int i = 0; i < this->getAttackCapacity(); ++i) 
		{
			if (enemyArmy->getUnit(ET, T1, tmp))
			{
				T1->getAttacked(this, timestep);
				if (T1->isDead())
					enemyArmy->addToKilled(T1);
				else
					tempEarthTanks.push(T1);
			}
			if (enemyArmy->getUnit(EG, G1, tmp))
			{
				G1->getAttacked(this, timestep);
				if (G1->isDead())
					enemyArmy->addToKilled(G1);
				else
					enemyArmy->addExisting(EG, G1);

			}
		}
		Unit* temp = nullptr;
		while (!tempEarthTanks.isEmpty())
		{
			tempEarthTanks.pop(temp);
			enemyArmy->addExisting(ET, temp);
		}
	}
	bool isAlien() override { return true; };
};
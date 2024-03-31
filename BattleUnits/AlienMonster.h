#pragma once

class AlienMonster:public Unit
{
public:
	AlienMonster(int joinTime, int health, int power, int attackCapacity) :
		Unit(AM, joinTime, health, power, attackCapacity)
	{
		int safan = 8;
	}
	void attack(Army* enemyArmy, int timestep) 
	{

	}
	
};
#pragma once
#include "Unit.h"
#include "../Game.h"

class EarthTank : public Unit 
{

public:
	EarthTank(int id, int joinTime, int health, int power, int attackCapacity) :
		Unit(ET,id, joinTime, health, power, attackCapacity) {};
	void attack(Game* enemyArmy, int timestep) {};
};
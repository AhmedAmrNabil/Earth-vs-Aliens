#pragma once
#include "Unit.h"

class EarthTank : public Unit 
{
	bool isAlien() override { return false; };

public:
	EarthTank(int joinTime, int health, int power, int attackCapacity) :
		Unit(ET, joinTime, health, power, attackCapacity) {

	};
	void attack(Army* enemyArmy, int timestep) {

	}

	
};
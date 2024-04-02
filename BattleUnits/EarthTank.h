#pragma once
#include "Unit.h"

class EarthTank : public Unit 
{
	bool isAlien() override { return false; };

public:
	EarthTank(int id, int joinTime, int health, int power, int attackCapacity) :
		Unit(ET,id, joinTime, health, power, attackCapacity) {

	};
	void attack(Army* enemyArmy, int timestep) {

	}

	
};
#pragma once

#include "../Armies/Army.h"
#include "../DataStructures/LinkedQueue.h"
#include "Unit.h"
#include "../Game.h"

class EarthGunner : public Unit
{
public:
	EarthGunner(int id, int joinTime, int health, int power, int attackCapacity)
		: Unit(EG, id, joinTime, health, power, attackCapacity) {};

	void attack(Game* game, int timestep);
	int getPriority();
};
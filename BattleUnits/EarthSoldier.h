#ifndef EARTH_SOLDIER_H_
#define EARTH_SOLDIER_H_

#include "../Armies/Army.h"
#include "../DataStructures/LinkedQueue.h"
#include "Unit.h"
#include "../Game.h"

class EarthSoldier : public Unit {
public:
	EarthSoldier(int id, int joinTime, int health, int power, int attackCapacity)
		: Unit(ES, id, joinTime, health, power, attackCapacity) {
	};

	void attack(Game* game, int timestep) override;
};

#endif
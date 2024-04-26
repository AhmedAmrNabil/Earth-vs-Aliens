#ifndef EARTH_TANK_H
#define EARTH_TANK_H

#include "Unit.h"

class EarthTank : public Unit 
{

public:
	EarthTank(Game* game, int joinTime, int health, int power, int attackCapacity);
	void attack() override;
};

#endif
#pragma once
#include "Unit.h"
#include "../Game.h"

class EarthTank : public Unit 
{

public:
	EarthTank(Game* game, int joinTime, int health, int power, int attackCapacity);
	void attack() override;
};
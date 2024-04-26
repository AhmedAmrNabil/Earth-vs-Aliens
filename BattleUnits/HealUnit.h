#pragma once
#include "Unit.h"
class HealUnit : public Unit {
public:
	HealUnit(Game* game, int joinTime, int health, int power, int attackCapacity);
	void attack();
};

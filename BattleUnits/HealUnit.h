#ifndef HEAL_UNIT_H
#define HEAL_UNIT_H
#include "Unit.h"

class HealUnit : public Unit {
public:
	HealUnit(Game* game, int joinTime, double health, double power, int attackCapacity);
	void attack();
};

#endif
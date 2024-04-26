#ifndef HEAL_UNIT_H
#define HEAL_UNIT_H
#include "Unit.h"

class HealUnit : public Unit {
public:
	HealUnit(Game* game, int joinTime, int health, int power, int attackCapacity);
	void attack();
};

#endif
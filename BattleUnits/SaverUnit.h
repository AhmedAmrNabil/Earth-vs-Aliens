#ifndef SAVER_UNIT_H
#define SAVER_UNIT_H
#include "Unit.h"

class SaverUnit : public Unit {
public:
	SaverUnit(Game* game, int joinTime, double health, double power, int attackCapacity);
	bool attack();
};

#endif
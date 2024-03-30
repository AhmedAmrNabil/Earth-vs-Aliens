#pragma once

#include "../BattleUnits/Unit.h"
#include "./Army.h"

class AlienArmy:public Army {
   public:
    bool getDronePair(Unit*& drone1,Unit*& drone2);
};
#include "Army.h"
#include "../BattleUnits/Soldier.h"

class AlienArmy:public Army {
   public:
    bool getDronePair(Unit* drone1,Unit* drone2);
};
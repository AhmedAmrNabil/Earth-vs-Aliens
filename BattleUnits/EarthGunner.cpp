#include "EarthGunner.h"

#include "../Game.h"

void EarthGunner::attack(Game* game, int timestep) {
    Unit* drone1;
    Unit* drone2 = nullptr;
    clearAttacked();
    LinkedQueue<Unit*> temp;
    for (int i = 0; i < this->getAttackCapacity(); ++i) {
        if (game->getAlienUnit(AD, drone1, drone2)) {
            drone1->getAttacked(this, timestep);
            attackedUnits.enqueue(drone1);
            if (drone1->isDead())
                game->addToKilled(drone1);
            else
                temp.enqueue(drone1);
        }

        if (drone2 != nullptr) {
            drone2->getAttacked(this, timestep);
            attackedUnits.enqueue(drone2);
            if (drone2->isDead())
                game->addToKilled(drone2);
            else
                temp.enqueue(drone2);
        }
    }
    while (!temp.isEmpty()) 
    {
        temp.dequeue(drone2);
        game->addAlienUnit(drone2);
    }
}

int EarthGunner::getPriority() {
    return power * sqrt(health);
}

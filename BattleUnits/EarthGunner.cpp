#include "EarthGunner.h"

#include "../Game.h"

EarthGunner::EarthGunner(int id, int joinTime, int health, int power, int attackCapacity)
    : Unit(EG, id, joinTime, health, power, attackCapacity) {
    priority = power * sqrt(health);
};

void EarthGunner::attack(Game* game, int timestep) {
    clearAttacked();
    Unit* drone1 = nullptr;
    Unit* drone2 = nullptr;
    Unit* monster = nullptr;
    Unit* tmp;
    LinkedQueue<Unit*> tempDrone;
    LinkedQueue<Unit*> tempMonster;

    int monsterCount = this->getAttackCapacity() / 2;
    int droneCount = this->getAttackCapacity() - monsterCount;
    while (monsterCount > 0) {
        if (game->getAlienUnit(AM, monster, tmp)) {
            monster->getAttacked(this, timestep);
            attackedIDs.enqueue(monster->getId());
            if (monster->isDead())
                game->addToKilled(monster);
            else
                tempMonster.enqueue(monster);
        }
        --monsterCount;
    }

    while (droneCount / 2 > 0) {
        if (game->getAlienUnit(AD, drone1, drone2)) {
            drone1->getAttacked(this, timestep);
            attackedIDs.enqueue(drone1->getId());
            if (drone1->isDead())
                game->addToKilled(drone1);
            else
                tempDrone.enqueue(drone1);
        }
        if (drone2 != nullptr) {
            drone2->getAttacked(this, timestep);
            attackedIDs.enqueue(drone2->getId());
            if (drone2->isDead())
                game->addToKilled(drone2);
            else
                tempDrone.enqueue(drone2);
        }
        --droneCount;
    }

    if (droneCount) {
        if (game->getAlienUnit(AD, drone1, drone2)) {
            drone1->getAttacked(this, timestep);
            if (drone1->isDead())
                game->addToKilled(drone1);
            else
                tempDrone.enqueue(drone1);
        }
    }

    while (!tempDrone.isEmpty()) {
        tempDrone.dequeue(drone1);
        game->addAlienUnit(drone1);
    }
    while (!tempMonster.isEmpty()) {
        tempMonster.dequeue(monster);
        game->addAlienUnit(monster);
    }
}

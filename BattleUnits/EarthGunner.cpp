#include "EarthGunner.h"

#include "../Game.h"

EarthGunner::EarthGunner(int joinTime, int health, int power, int attackCapacity)
    : Unit(EG, joinTime, health, power, attackCapacity) {
    priority = power * sqrt(health);
};

void EarthGunner::attack(Game* game, int timestep) {
    clearAttacked();
    Unit* drone = nullptr;
    Unit* monster = nullptr;
    LinkedQueue<Unit*> tempDrone;
    LinkedQueue<Unit*> tempMonster;

    int monsterCount = this->getAttackCapacity() / 2;
    int dronesCount = this->getAttackCapacity() - monsterCount;
    int dronesAttacked = 0;
    while (monsterCount > 0) {
        if (game->getAlienUnit(AM, monster)) {
            monster->getAttacked(this, timestep);
            attackedIDs.enqueue(monster->getId());
            if (monster->isDead())
                game->addToKilled(monster);
            else
                tempMonster.enqueue(monster);
        }
        --monsterCount;
    }

    while (dronesAttacked < dronesCount) {
        if (game->getAlienUnit(AD, drone, dronesAttacked % 2)) {
            drone->getAttacked(this, timestep);
            attackedIDs.enqueue(drone->getId());
            if (drone->isDead())
                game->addToKilled(drone);
            else
                tempDrone.enqueue(drone);
        }
        ++dronesAttacked;
    }

    while (!tempDrone.isEmpty()) {
        tempDrone.dequeue(drone);
        game->addAlienUnit(drone);
    }
    while (!tempMonster.isEmpty()) {
        tempMonster.dequeue(monster);
        game->addAlienUnit(monster);
    }
}

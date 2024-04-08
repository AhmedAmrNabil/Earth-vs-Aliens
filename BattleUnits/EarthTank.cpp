#include "EarthTank.h"

EarthTank::EarthTank(int id, int joinTime, int health, int power, int attackCapacity)
    : Unit(ET, id, joinTime, health, power, attackCapacity) {
    priority = 1;
}
void EarthTank::attack(Game* game, int timestep) {
    Unit* monster;
    Unit* soldier;
    bool monstersOnly = true;
    LinkedQueue<Unit*> temp;
    ArrayMonster tmpMonsters;
    if (game->getSoldierRatio() < 30) monstersOnly = false;
    clearAttacked();
    for (int i = 0; i < this->getAttackCapacity(); ++i) {
        if (game->getAlienUnit(AM, monster)) {
            monster->getAttacked(this, timestep);
            attackedIDs.enqueue(monster->getId());
            if (monster->isDead())
                game->addToKilled(monster);
            else
                tmpMonsters.insert(monster);
        }
        if (game->getSoldierRatio() > 80) monstersOnly = true;
        if (!monstersOnly) {
            if (game->getAlienUnit(AS, soldier)) {
                soldier->getAttacked(this, timestep);
                attackedIDs.enqueue(soldier->getId());
                if (soldier->isDead())
                    game->addToKilled(soldier);
                else
                    temp.enqueue(soldier);
            }
        }
    }
    while (!temp.isEmpty()) {
        temp.dequeue(soldier);
        game->addAlienUnit(soldier);
    }
    while (!tmpMonsters.isEmpty()) {
        tmpMonsters.pick(monster);
        game->addAlienUnit(monster);
    }
}

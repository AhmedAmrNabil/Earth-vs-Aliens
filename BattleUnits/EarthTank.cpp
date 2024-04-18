#include "EarthTank.h"

EarthTank::EarthTank(Game* game,int joinTime, int health, int power, int attackCapacity)
    : Unit(game, ET, joinTime, health, power, attackCapacity) {
}
void EarthTank::attack() {
    int timestep = game->getTimestep();
    Unit* monster;
    Unit* soldier;
    bool monstersOnly = true;
    LinkedQueue<Unit*> temp;
    ArrayMonster tmpMonsters;
    if (game->getSoldierRatio() < 30) monstersOnly = false;
    for (int i = 0; i < this->getAttackCapacity(); ++i) {
        if (game->getAlienUnit(AM, monster)) {
            monster->getAttacked(this, timestep);
            if (monster->isDead())
                game->addToKilled(monster);
            else
                tmpMonsters.insert(monster);
        }
        if (game->getSoldierRatio() > 80) monstersOnly = true;
        if (!monstersOnly) {
            if (game->getAlienUnit(AS, soldier)) {
                soldier->getAttacked(this, timestep);
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

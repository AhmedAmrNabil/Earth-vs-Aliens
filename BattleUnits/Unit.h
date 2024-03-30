#pragma once
#include <cmath>
enum UNIT_TYPE {
    S,
    ET,
    EG,
    AM,
    AD
};

class Army;
class Unit {
    static int lastId;
    int id;
    UNIT_TYPE type;
    int joinTime;
    int health;
    int power;
    int attackCapacity;

   public:
    Unit(UNIT_TYPE type, int joinTime, int health, int power, int attackCapacity) : type(type), joinTime(joinTime), health(health), power(power), attackCapacity(attackCapacity) {
        this->id = lastId;
        ++lastId;
    }

    virtual void attack(Army* enemyArmy) = 0;

    void getAttacked(Unit* enemyUnit) {
        health -= (enemyUnit->power * enemyUnit->health / 100) / sqrt(this->health);
        if (health < 0) health = 0;
    }

    bool isDead() { return health == 0; }

    int getAttackCapacity() { return this->attackCapacity; }
    
};

int Unit::lastId = 0;
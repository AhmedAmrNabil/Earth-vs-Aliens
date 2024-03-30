#pragma once
#include <cmath>
#include "../DataStructures/LinkedQueue.h"

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
	int firstAttackedTime;
	int health;
	int power;
	int attackCapacity;

protected:
	LinkedQueue <Unit*>attackedUnits;
	void clearAttacked(){
		Unit* tmp;
		while(attackedUnits.dequeue(tmp));
	}

public:
	Unit(UNIT_TYPE type, int joinTime, int health, int power, int attackCapacity) : type(type), joinTime(joinTime), health(health), power(power), attackCapacity(attackCapacity) {
		this->id = lastId;
		++lastId;
		firstAttackedTime = -1;
	};

	virtual void attack(Army* enemyArmy, int timestamp) = 0;

	void getAttacked(Unit* enemyUnit, int timestamp) {
		health -= (enemyUnit->power * enemyUnit->health / 100) / sqrt(this->health);
		if (health < 0) health = 0;
		if (firstAttackedTime == -1) firstAttackedTime = timestamp;
	};

	bool isDead() { return health == 0; };

	int getAttackCapacity() { return this->attackCapacity; };
};

int Unit::lastId = 0;